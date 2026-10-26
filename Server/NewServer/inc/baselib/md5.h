#ifndef _MD5_H_
#define _MD5_H_

struct md5_ctx;

extern md5_ctx* md5_init(void);
extern void md5_update(md5_ctx* context, UINT8* input, unsigned int inputLen);
extern void md5_final(UINT8 digest[16], md5_ctx* context);

extern void calc_md5(UINT8 byDigest[16], UINT8* pInput, UINT32 dwInLen);

#endif	// _MD5_H_