#ifndef _RSA_SIGN_H_
#define _RSA_SIGN_H_
//
//typedef struct rsa_st RSA;
//
//#define RSA_KEY_LENGTH	(512)
//#define RSA_KEY_E       (3)
//
//struct BIG_NUM_DATA
//{
//    UINT64  d[RSA_KEY_LENGTH / sizeof(UINT64) / 8];
//    int     top;
//    int     dmax;
//    int     neg;
//    int     flags;
//};
//
//RSA* RSA_GenetateKey();
//
//BOOL RSA_SignUp(RSA* pPrivateKey, const unsigned char* pContext, INT32 nContextSize, unsigned char* pSign, UINT32& nSignLength);
//BOOL RSA_Verify(RSA* pPuclicKey,  UCHAR* pContext, INT32 nContextSize,  UCHAR* pVerify, UINT32 nVerifyLength);
//
//RSA* RSA_NewKey();
//void RSA_FreeKey(RSA* pKey);
//
//BOOL RSA_FromKey2Data(RSA* pKey, BIG_NUM_DATA* pData, BOOL bPublic);
//BOOL RSA_FromData2Key(BIG_NUM_DATA* pData, RSA* pKey, BOOL bPublic);

#endif //_RSA_SIGN_H_S