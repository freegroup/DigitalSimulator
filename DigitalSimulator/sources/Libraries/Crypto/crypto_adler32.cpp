// adler32.cpp - written and placed in the public domain by Wei Dai

#include "pch.h"
#include "crypto_adler32.h"

NAMESPACE_BEGIN(CryptoPP)

void Adler32::Update(const byte *input, unsigned int length)
{
	const unsigned long BASE = 65521;

	unsigned long s1 = m_s1;
	unsigned long s2 = m_s2;

	while (length % 8 != 0)
	{
		s1 += *input++;
		s2 += s1;
		length--;
	}

	while (length > 0)
	{
		s1 += input[0]; s2 += s1;
		s1 += input[1]; s2 += s1;
		s1 += input[2]; s2 += s1;
		s1 += input[3]; s2 += s1;
		s1 += input[4]; s2 += s1;
		s1 += input[5]; s2 += s1;
		s1 += input[6]; s2 += s1;
		s1 += input[7]; s2 += s1;

		length -= 8;
		input += 8;

		if (s1 >= BASE)
			s1 -= BASE;
		if (length % 0x8000 == 0)
			s2 %= BASE;
	}

	m_s1 = (word16)s1;
	m_s2 = (word16)s2;
}

void Adler32::Final(byte *hash)
{
	hash[0] = byte(m_s2 >> 8);
	hash[1] = byte(m_s2);
	hash[2] = byte(m_s1 >> 8);
	hash[3] = byte(m_s1);

	Reset();
}

NAMESPACE_END
