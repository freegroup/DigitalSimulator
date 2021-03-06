// zdeflate.cpp - written and placed in the public domain by Wei Dai

// Many of the algorithms and tables used here came from the deflate implementation
// by Jean-loup Gailly, which was included in Crypto++ 4.0 and earlier. I completely
// rewrote it in order to fix a bug that I could not figure out. This code
// is less clever, but hopefully more understandable and maintainable.

#include "pch.h"
#include "zdeflate.h"
#include <functional>

NAMESPACE_BEGIN(CryptoPP)

using namespace std;

LowFirstBitWriter::LowFirstBitWriter(BufferedTransformation *outQ)
	: Filter(outQ), m_counting(false), m_buffer(0), m_bitsBuffered(0)
	, m_bytesBuffered(0), m_outputBuffer(256)
{
}

void LowFirstBitWriter::StartCounting()
{
	assert(!m_counting);
	m_counting = true;
	m_bitCount = 0;
}

unsigned long LowFirstBitWriter::FinishCounting()
{
	assert(m_counting);
	m_counting = false;
	return m_bitCount;
}

void LowFirstBitWriter::PutBits(unsigned long value, unsigned int length)
{
	if (m_counting)
		m_bitCount += length;
	else
	{
		m_buffer |= value << m_bitsBuffered;
		m_bitsBuffered += length;
		assert(m_bitsBuffered <= sizeof(unsigned long)*8);
		while (m_bitsBuffered >= 8)
		{
			m_outputBuffer[m_bytesBuffered++] = (byte)m_buffer;
			if (m_bytesBuffered == m_outputBuffer.size)
			{
				AttachedTransformation()->Put(m_outputBuffer, m_bytesBuffered);
				m_bytesBuffered = 0;
			}
			m_buffer >>= 8;
			m_bitsBuffered -= 8;
		}
	}
}

void LowFirstBitWriter::FlushBitBuffer()
{
	if (m_counting)
		m_bitCount += 8*(m_bitsBuffered > 0);
	else
	{
		if (m_bytesBuffered > 0)
		{
			AttachedTransformation()->Put(m_outputBuffer, m_bytesBuffered);
			m_bytesBuffered = 0;
		}
		if (m_bitsBuffered > 0)
		{
			AttachedTransformation()->Put((byte)m_buffer);
			m_buffer = 0;
			m_bitsBuffered = 0;
		}
	}
}

HuffmanEncoder::HuffmanEncoder(const unsigned int *codeBits, unsigned int nCodes)
{
	Initialize(codeBits, nCodes);
}

struct HuffmanNode
{
	inline bool operator<(const HuffmanNode &rhs) const {return freq < rhs.freq;}
	unsigned int symbol;
	union {unsigned int parent, depth, freq;};
};

inline bool operator<(unsigned int i, const HuffmanNode &rhs) {return i < rhs.freq;}

void HuffmanEncoder::GenerateCodeLengths(unsigned int *codeBits, unsigned int maxCodeBits, const unsigned int *codeCounts, unsigned int nCodes)
{
	assert(nCodes > 0);
	assert(nCodes <= (1 << maxCodeBits));

	unsigned int i;
	SecBlock<HuffmanNode> tree(nCodes);
	for (i=0; i<nCodes; i++)
	{
		tree[i].symbol = i;
		tree[i].freq = codeCounts[i];
	}
	sort(tree.Begin(), tree.End());
	unsigned int treeBegin = upper_bound(tree.Begin(), tree.End(), 0) - tree.Begin();
	if (treeBegin == nCodes)
	{	// special case for no codes
		fill(codeBits, codeBits+nCodes, 0);
		return;
	}
	tree.Resize(nCodes + nCodes - treeBegin - 1);

	unsigned int leastLeaf = treeBegin, leastInterior = nCodes;
	for (i=nCodes; i<tree.size; i++)
	{
		unsigned int least;
		least = (leastLeaf == nCodes || (leastInterior < i && tree[leastInterior].freq < tree[leastLeaf].freq)) ? leastInterior++ : leastLeaf++;
		tree[i].freq = tree[least].freq;
		tree[least].parent = i;
		least = (leastLeaf == nCodes || (leastInterior < i && tree[leastInterior].freq < tree[leastLeaf].freq)) ? leastInterior++ : leastLeaf++;
		tree[i].freq += tree[least].freq;
		tree[least].parent = i;
	}

	tree[tree.size-1].depth = 0;
	if (tree.size >= 2)
		for (i=tree.size-2; i>=nCodes; i--)
			tree[i].depth = tree[tree[i].parent].depth + 1;
	unsigned int sum = 0;
	SecBlock<unsigned int> blCount(maxCodeBits+1);
	fill(blCount.Begin(), blCount.End(), 0);
	for (i=treeBegin; i<nCodes; i++)
	{
		unsigned int depth = STDMIN(maxCodeBits, tree[tree[i].parent].depth + 1);
		blCount[depth]++;
		sum += 1 << (maxCodeBits - depth);
	}

	unsigned int overflow = sum > (1 << maxCodeBits) ? sum - (1 << maxCodeBits) : 0;

	while (overflow--)
	{
		unsigned int bits = maxCodeBits-1;
		while (blCount[bits] == 0)
			bits--;
		blCount[bits]--;
		blCount[bits+1] += 2;
		assert(blCount[maxCodeBits] > 0);
		blCount[maxCodeBits]--;
	}

	for (i=0; i<treeBegin; i++)
		codeBits[tree[i].symbol] = 0;
	unsigned int bits = maxCodeBits;
	for (i=treeBegin; i<nCodes; i++)
	{
		while (blCount[bits] == 0)
			bits--;
		codeBits[tree[i].symbol] = bits;
		blCount[bits]--;
	}
	assert(blCount[bits] == 0);
}

void HuffmanEncoder::Initialize(const unsigned int *codeBits, unsigned int nCodes)
{
	assert(nCodes > 0);
	unsigned int maxCodeBits = *max_element(codeBits, codeBits+nCodes);
	if (maxCodeBits == 0)
		return;		// assume this object won't be used

	SecBlock<unsigned int> blCount(maxCodeBits+1);
	fill(blCount.Begin(), blCount.End(), 0);
	unsigned int i;
	for (i=0; i<nCodes; i++)
		blCount[codeBits[i]]++;

	code_t code = 0;
	SecBlock<code_t> nextCode(maxCodeBits+1);
	nextCode[1] = 0;
	for (i=2; i<=maxCodeBits; i++)
	{
		code = (code + blCount[i-1]) << 1;
		nextCode[i] = code;
	}
	assert(maxCodeBits == 1 || code == (1 << maxCodeBits) - blCount[maxCodeBits]);

	m_valueToCode.Resize(nCodes);
	for (i=0; i<nCodes; i++)
	{
		unsigned int len = m_valueToCode[i].len = codeBits[i];
		if (len != 0)
			m_valueToCode[i].code = bitReverse(nextCode[len]++) >> (8*sizeof(code_t)-len);
	}
}

inline void HuffmanEncoder::Encode(LowFirstBitWriter &writer, value_t value) const
{
	assert(m_valueToCode[value].len > 0);
	writer.PutBits(m_valueToCode[value].code, m_valueToCode[value].len);
}

Deflator::Deflator(BufferedTransformation *outQ, unsigned int deflateLevel, unsigned int log2WindowSize)
	: LowFirstBitWriter(outQ)
	, m_log2WindowSize(log2WindowSize)
	, m_literalCounts(286), m_distanceCounts(30)
	, DSIZE(1<<log2WindowSize), DMASK(DSIZE-1), HSIZE(1<<log2WindowSize), HMASK(HSIZE-1)
	, m_head(HSIZE), m_prev(DSIZE)
	, m_byteBuffer(2*DSIZE), m_matchBuffer(DSIZE/2)
{
	assert(0 <= deflateLevel && deflateLevel <= 9);
	assert(9 <= log2WindowSize && log2WindowSize <= 15);

	unsigned int codeLengths[288];
	fill(codeLengths + 0, codeLengths + 144, 8);
	fill(codeLengths + 144, codeLengths + 256, 9);
	fill(codeLengths + 256, codeLengths + 280, 7);
	fill(codeLengths + 280, codeLengths + 288, 8);
	m_staticLiteralEncoder.Initialize(codeLengths, 288);
	fill(codeLengths + 0, codeLengths + 32, 5);
	m_staticDistanceEncoder.Initialize(codeLengths, 32);

	SetDeflateLevel(deflateLevel);
	Reset();
}

void Deflator::Reset()
{
	assert(m_bitsBuffered == 0);

	m_headerWritten = false;
	m_matchAvailable = false;
	m_dictionaryEnd = 0;
	m_stringStart = 0;
	m_lookahead = 0;
	m_minLookahead = MAX_MATCH;
	m_previousMatch = 0;
	m_previousLength = 0;
	m_matchBufferEnd = 0;
	m_blockStart = 0;
	m_blockLength = 0;

	// m_prev will be initialized automaticly in InsertString
	fill(m_head.Begin(), m_head.End(), 0);

	fill(m_literalCounts.Begin(), m_literalCounts.End(), 0);
	fill(m_distanceCounts.Begin(), m_distanceCounts.End(), 0);
}

void Deflator::SetDeflateLevel(unsigned int deflateLevel)
{
	unsigned int configurationTable[10][4] = {
		/*      good lazy nice chain */
		/* 0 */ {0,    0,  0,    0},  /* store only */
		/* 1 */ {4,    3,  8,    4},  /* maximum speed, no lazy matches */
		/* 2 */ {4,    3, 16,    8},
		/* 3 */ {4,    3, 32,   32},
		/* 4 */ {4,    4, 16,   16},  /* lazy matches */
		/* 5 */ {8,   16, 32,   32},
		/* 6 */ {8,   16, 128, 128},
		/* 7 */ {8,   32, 128, 256},
		/* 8 */ {32, 128, 258, 1024},
		/* 9 */ {32, 258, 258, 4096}}; /* maximum compression */

	GOOD_MATCH = configurationTable[deflateLevel][0];
	MAX_LAZYLENGTH = configurationTable[deflateLevel][1];
	MAX_CHAIN_LENGTH = configurationTable[deflateLevel][3];

	m_deflateLevel = deflateLevel;
}

unsigned int Deflator::FillWindow(const byte *str, unsigned int length)
{
	unsigned int accepted = STDMIN(length, 2*DSIZE-(m_stringStart+m_lookahead));

	if (m_stringStart >= 2*DSIZE - MAX_MATCH)
	{
		if (m_blockStart < DSIZE)
			EndBlock(false);

		memcpy(m_byteBuffer, m_byteBuffer + DSIZE, DSIZE);

		m_dictionaryEnd = m_dictionaryEnd < DSIZE ? 0 : m_dictionaryEnd-DSIZE;
		assert(m_stringStart >= DSIZE);
		m_stringStart -= DSIZE;
		assert(m_previousMatch >= DSIZE || m_previousLength < MIN_MATCH);
		m_previousMatch -= DSIZE;
		assert(m_blockStart >= DSIZE);
		m_blockStart -= DSIZE;

		unsigned int i, j;

		for (i=0; i<HSIZE; i++)
			m_head[i] = (j=m_head[i]) < DSIZE ? 0 : j-DSIZE;

		for (i=0; i<DSIZE; i++)
			m_prev[i] = (j=m_prev[i]) < DSIZE ? 0 : j-DSIZE;

		accepted = STDMIN(accepted + DSIZE, length);
	}
	assert(accepted > 0);

	memcpy(m_byteBuffer + m_stringStart + m_lookahead, str, accepted);
	m_lookahead += accepted;
	return accepted;
}

inline unsigned int Deflator::ComputeHash(const byte *str) const
{
	assert(str+3 <= m_byteBuffer + m_stringStart + m_lookahead);
	return ((str[0] << 10) ^ (str[1] << 5) ^ str[2]) & HMASK;
}

unsigned int Deflator::LongestMatch(unsigned int &bestMatch) const
{
	assert(m_previousLength < MAX_MATCH);

	bestMatch = 0;
	unsigned int bestLength = STDMAX(m_previousLength, (unsigned int)MIN_MATCH-1);
	if (m_lookahead <= bestLength)
		return 0;

	const byte *scan = m_byteBuffer + m_stringStart, *scanEnd = scan + STDMIN((unsigned int)MAX_MATCH, m_lookahead);
	unsigned int limit = m_stringStart > (DSIZE-MAX_MATCH) ? m_stringStart - (DSIZE-MAX_MATCH) : 0;
	unsigned int current = m_head[ComputeHash(scan)];

	unsigned int chainLength = MAX_CHAIN_LENGTH;
	if (m_previousLength >= GOOD_MATCH)
		chainLength >>= 2;

	while (current > limit && --chainLength > 0)
	{
		const byte *match = m_byteBuffer + current;
		assert(scan + bestLength < m_byteBuffer + m_stringStart + m_lookahead);
		if (scan[bestLength-1] == match[bestLength-1] && scan[bestLength] == match[bestLength] && scan[0] == match[0] && scan[1] == match[1])
		{
			assert(scan[2] == match[2]);
			unsigned int len = std::mismatch(scan+3, scanEnd, match+3).first - scan;
			assert(len != bestLength);
			if (len > bestLength)
			{
				bestLength = len;
				bestMatch = current;
				if (len == (scanEnd - scan))
					break;
			}
		}
		current = m_prev[current & DMASK];
	}
	return (bestMatch > 0) ? bestLength : 0;
}

inline void Deflator::InsertString(unsigned int start)
{
	unsigned int hash = ComputeHash(m_byteBuffer + start);
	m_prev[start & DMASK] = m_head[hash];
	m_head[hash] = start;
}

void Deflator::ProcessBuffer()
{
	if (!m_headerWritten)
	{
		WritePrestreamHeader();
		m_headerWritten = true;
	}

	if (m_deflateLevel == 0)
	{
		while (m_lookahead > 0)
		{
			LiteralByte(m_byteBuffer[m_stringStart++]);
			m_lookahead--;
		}
		return;
	}

	while (m_lookahead > m_minLookahead)
	{
		while (m_dictionaryEnd < m_stringStart && m_dictionaryEnd+3 <= m_stringStart+m_lookahead)
			InsertString(m_dictionaryEnd++);

		if (m_matchAvailable)
		{
			unsigned int matchPosition, matchLength;
			bool usePreviousMatch;
			if (m_previousLength >= MAX_LAZYLENGTH)
				usePreviousMatch = true;
			else
			{
				matchLength = LongestMatch(matchPosition);
				usePreviousMatch = (m_previousLength > 0 && matchLength == 0);
			}
			if (usePreviousMatch)
			{
				MatchFound(m_stringStart-1-m_previousMatch, m_previousLength);
				m_stringStart += m_previousLength-1;
				m_lookahead -= m_previousLength-1;
				m_matchAvailable = false;
				m_previousLength = 0;
			}
			else
			{
				m_previousLength = matchLength;
				m_previousMatch = matchPosition;
				LiteralByte(m_byteBuffer[m_stringStart-1]);
				m_stringStart++;
				m_lookahead--;
			}
		}
		else
		{
			m_previousLength = LongestMatch(m_previousMatch);
			m_matchAvailable = true;
			m_stringStart++;
			m_lookahead--;
		}
	}
	assert(m_stringStart - (m_blockStart+m_blockLength) <= 1);
	if (m_minLookahead == 0 && m_matchAvailable)
	{
		LiteralByte(m_byteBuffer[m_stringStart-1]);
		m_matchAvailable = false;
	}
}

void Deflator::Put(const byte *str, unsigned int length)
{
	ProcessUncompressedData(str, length);

	unsigned int accepted = 0;
	while (accepted < length)
	{
		accepted += FillWindow(str+accepted, length-accepted);
		ProcessBuffer();
	}
}

void Deflator::Flush(bool completeFlush, int propagation)
{
	m_minLookahead = 0;
	ProcessBuffer();
	m_minLookahead = MAX_MATCH;
	EndBlock(false);
	EncodeBlock(false, STORED);
	Filter::Flush(completeFlush, propagation);
}

void Deflator::MessageEnd(int propagation)
{
	m_minLookahead = 0;
	ProcessBuffer();
	EndBlock(true);
	FlushBitBuffer();
	WritePoststreamTail();
	Filter::MessageEnd(propagation);
	Reset();
}

void Deflator::LiteralByte(byte b)
{
	m_matchBuffer[m_matchBufferEnd++].literalCode = b;
	m_literalCounts[b]++;

	if (m_blockStart+(++m_blockLength) == m_byteBuffer.size || m_matchBufferEnd == m_matchBuffer.size)
		EndBlock(false);
}

void Deflator::MatchFound(unsigned int distance, unsigned int length)
{
	static const unsigned int lengthCodes[] = {
		257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268,
		269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272,
		273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274,
		275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276,
		277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277,
		278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278,
		279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279,
		280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280,
		281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
		281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
		282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
		282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
		283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
		283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
		284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
		284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
	static const unsigned int lengthBases[] = {3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258};
	static const unsigned int distanceBases[30] = 
		{1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577};

	EncodedMatch &m = m_matchBuffer[m_matchBufferEnd++];
	unsigned int lengthCode = lengthCodes[length-3];
	m.literalCode = lengthCode;
	m.literalExtra = length - lengthBases[lengthCode-257];
	unsigned int distanceCode = upper_bound(distanceBases, distanceBases+30, distance) - distanceBases - 1;
	m.distanceCode = distanceCode;
	m.distanceExtra = distance - distanceBases[distanceCode];

	m_literalCounts[lengthCode]++;
	m_distanceCounts[distanceCode]++;

	if (m_blockStart+(m_blockLength+=length) == m_byteBuffer.size || m_matchBufferEnd == m_matchBuffer.size)
		EndBlock(false);
}

inline unsigned int CodeLengthEncode(const unsigned int *begin, 
									 const unsigned int *end, 
									 const unsigned int *& p, 
									 unsigned int &extraBits, 
									 unsigned int &extraBitsLength)
{
	unsigned int v = *p;
	if ((end-p) >= 3)
	{
		const unsigned int *oldp = p;
		if (v==0 && p[1]==0 && p[2]==0)
		{
			for (p=p+3; *p==0 && p!=end && p!=oldp+138; p++) {}
			unsigned int repeat = p - oldp;
			if (repeat <= 10)
			{
				extraBits = repeat-3;
				extraBitsLength = 3;
				return 17;
			}
			else
			{
				extraBits = repeat-11;
				extraBitsLength = 7;
				return 18;
			}
		}
		else if (p!=begin && v==p[-1] && v==p[1] && v==p[2])
		{
			for (p=p+3; *p==v && p!=end && p!=oldp+6; p++) {}
			unsigned int repeat = p - oldp;
			extraBits = repeat-3;
			extraBitsLength = 2;
			return 16;
		}
	}
	p++;
	extraBits = 0;
	extraBitsLength = 0;
	return v;
}

void Deflator::EncodeBlock(bool eof, unsigned int blockType)
{
	PutBits(eof, 1);
	PutBits(blockType, 2);

	if (blockType == STORED)
	{
		assert(m_blockStart + m_blockLength <= m_byteBuffer.size);
		FlushBitBuffer();
		AttachedTransformation()->PutWord16(m_blockLength, false);
		AttachedTransformation()->PutWord16(~m_blockLength, false);
		AttachedTransformation()->Put(m_byteBuffer + m_blockStart, m_blockLength);
	}
	else
	{
		if (blockType == DYNAMIC)
		{
			SecBlock<unsigned int> literalCodeLengths(286), distanceCodeLengths(30);
#if defined(_MSC_VER) && !defined(__MWERKS__)		// VC60 workaround
			typedef reverse_iterator<unsigned int *, unsigned int> RevIt;
#else
			typedef reverse_iterator<unsigned int *> RevIt;
#endif

			m_literalCounts[256] = 1;
			HuffmanEncoder::GenerateCodeLengths(literalCodeLengths, 15, m_literalCounts, 286);
			m_dynamicLiteralEncoder.Initialize(literalCodeLengths, 286);
			unsigned int hlit = find_if(RevIt(literalCodeLengths.End()), RevIt(literalCodeLengths.Begin()+257), bind2nd(not_equal_to<unsigned int>(), 0)).base() - (literalCodeLengths.Begin()+257);

			HuffmanEncoder::GenerateCodeLengths(distanceCodeLengths, 15, m_distanceCounts, 30);
			m_dynamicDistanceEncoder.Initialize(distanceCodeLengths, 30);
			unsigned int hdist = find_if(RevIt(distanceCodeLengths.End()), RevIt(distanceCodeLengths.Begin()+1), bind2nd(not_equal_to<unsigned int>(), 0)).base() - (distanceCodeLengths.Begin()+1);

			SecBlock<unsigned int> combinedLengths(hlit+257+hdist+1);
			memcpy(combinedLengths, literalCodeLengths, (hlit+257)*sizeof(unsigned int));
			memcpy(combinedLengths+hlit+257, distanceCodeLengths, (hdist+1)*sizeof(unsigned int));

			SecBlock<unsigned int> codeLengthCodeCounts(19), codeLengthCodeLengths(19);
			fill(codeLengthCodeCounts.Begin(), codeLengthCodeCounts.End(), 0);
			const unsigned int *p = combinedLengths.Begin(), *begin = combinedLengths.Begin(), *end = combinedLengths.End();
			while (p != end)
			{
				unsigned int code, extraBits, extraBitsLength;
				code = CodeLengthEncode(begin, end, p, extraBits, extraBitsLength);
				codeLengthCodeCounts[code]++;
			}
			HuffmanEncoder::GenerateCodeLengths(codeLengthCodeLengths, 7, codeLengthCodeCounts, 19);
			HuffmanEncoder codeLengthEncoder(codeLengthCodeLengths, 19);
			static const unsigned int border[] = {    // Order of the bit length code lengths
				16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
			unsigned int hclen = 19;
			while (hclen > 4 && codeLengthCodeLengths[border[hclen-1]] == 0)
				hclen--;
			hclen -= 4;

			PutBits(hlit, 5);
			PutBits(hdist, 5);
			PutBits(hclen, 4);

			for (unsigned int i=0; i<hclen+4; i++)
				PutBits(codeLengthCodeLengths[border[i]], 3);

			p = combinedLengths.Begin();
			while (p != end)
			{
				unsigned int code, extraBits, extraBitsLength;
				code = CodeLengthEncode(begin, end, p, extraBits, extraBitsLength);
				codeLengthEncoder.Encode(*this, code);
				PutBits(extraBits, extraBitsLength);
			}
		}

		static const unsigned int lengthExtraBits[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
			3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
		static const unsigned int distanceExtraBits[] = {
			0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
			7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
			12, 12, 13, 13};

		const HuffmanEncoder &literalEncoder = (blockType == STATIC) ? m_staticLiteralEncoder : m_dynamicLiteralEncoder;
		const HuffmanEncoder &distanceEncoder = (blockType == STATIC) ? m_staticDistanceEncoder : m_dynamicDistanceEncoder;

		for (unsigned int i=0; i<m_matchBufferEnd; i++)
		{
			unsigned int literalCode = m_matchBuffer[i].literalCode;
			literalEncoder.Encode(*this, literalCode);
			if (literalCode >= 257)
			{
				assert(literalCode <= 285);
				PutBits(m_matchBuffer[i].literalExtra, lengthExtraBits[literalCode-257]);
				unsigned int distanceCode = m_matchBuffer[i].distanceCode;
				distanceEncoder.Encode(*this, distanceCode);
				PutBits(m_matchBuffer[i].distanceExtra, distanceExtraBits[distanceCode]);
			}
		}
		literalEncoder.Encode(*this, 256);	// end of block
	}
}

void Deflator::EndBlock(bool eof)
{
	if (m_matchBufferEnd == 0 && !eof)
		return;

	if (m_deflateLevel == 0)
		EncodeBlock(eof, STORED);
	else if (m_blockLength < 128)
		EncodeBlock(eof, STATIC);
	else
	{
		unsigned int storedLen = 8*(m_blockLength+4) + RoundUpToMultipleOf(m_bitsBuffered+3, 8)-m_bitsBuffered;
		StartCounting();
		EncodeBlock(eof, STATIC);
		unsigned int staticLen = FinishCounting();
		StartCounting();
		EncodeBlock(eof, DYNAMIC);
		unsigned int dynamicLen = FinishCounting();

		if (storedLen <= staticLen && storedLen <= dynamicLen)
			EncodeBlock(eof, STORED);
		else if (staticLen <= dynamicLen)
			EncodeBlock(eof, STATIC);
		else
			EncodeBlock(eof, DYNAMIC);
	}

	m_matchBufferEnd = 0;
	m_blockStart += m_blockLength;
	m_blockLength = 0;
	fill(m_literalCounts.Begin(), m_literalCounts.End(), 0);
	fill(m_distanceCounts.Begin(), m_distanceCounts.End(), 0);
}

NAMESPACE_END
