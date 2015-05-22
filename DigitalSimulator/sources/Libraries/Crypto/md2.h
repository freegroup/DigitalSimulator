#ifndef CRYPTOPP_MD2_H
#define CRYPTOPP_MD2_H

#include "cryptlib.h"
#include "misc.h"

NAMESPACE_BEGIN(CryptoPP)

/// <a href="http://www.weidai.com/scan-mirror/md.html#MD2">MD2</a>
/** 128 Bit Hash */
class MD2 : public HashModule
{
public:
	MD2();
	void Update(const byte *input, unsigned int length);
	void Final(byte *hash);
	unsigned int DigestSize() const {return DIGESTSIZE;}

	enum {DIGESTSIZE = 16};

private:
	void Transform();
	void Init();
	SecByteBlock buf;
	unsigned int len;
};

NAMESPACE_END

#endif
