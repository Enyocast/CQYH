#include "stdafx.h"
//
//#include "rsa_sign.h"
//
//#include "openssl/rsa.h"
//#include "openssl/obj_mac.h"
//#include "openssl/md5.h"
//#include "error_def.h"
//
//RSA* RSA_GenetateKey()
//{
//    RSA* pKey = NULL;
//
//    pKey = RSA_generate_key(RSA_KEY_LENGTH, RSA_KEY_E, NULL, NULL);
//    LOG_PROCESS_ERROR(pKey);
//
//    return pKey;
//Exit0:
//    return NULL;
//}
//
//BOOL RSA_SignUp(RSA* pPrivateKey, const unsigned char* pContext, INT32 nContextSize, unsigned char* pSign, UINT32& nSignLength)
//{	
//	INT32 nRetCode = 0;
//	unsigned char md[16] = {0}; // Store the digest
//
//	MD5(pContext, nContextSize, md);
//
//	nRetCode = RSA_sign(NID_md5, md, sizeof(md), pSign, &nSignLength, pPrivateKey);
//	PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//BOOL RSA_Verify(RSA* pPuclicKey,  UCHAR* pContext, INT32 nContextSize,  UCHAR* pVerify, UINT32 nVerifyLength)
//{
//	INT32 nRetCode = 0;
//	unsigned char md[16] = {0}; // Store the digest after md encryption
//
//	MD5(pContext, nContextSize, md);
//
//	nRetCode = RSA_verify(NID_md5, md, sizeof(md), pVerify, nVerifyLength, pPuclicKey);
//	PROCESS_ERROR(nRetCode);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
//RSA* RSA_NewKey()
//{
//    return RSA_new();
//}
//
//void RSA_FreeKey(RSA* pKey)
//{
//    LOG_PROCESS_ERROR(pKey);
//
//    RSA_free(pKey);
//
//Exit0:
//    return;
//}
//
//BOOL RSA_FromKey2Data(RSA* pKey, BIG_NUM_DATA* pData, BOOL bPublic)
//{
//    LOG_PROCESS_ERROR(pKey);
//    LOG_PROCESS_ERROR(pData);
//
//    if (bPublic)
//    {
//        memcpy(pData->d, pKey->n->d, sizeof(pData->d));
//        pData->top = pKey->n->top;
//        pData->dmax = pKey->n->dmax;
//        pData->neg = pKey->n->neg;
//        pData->flags = pKey->n->flags;
//    }
//    else
//    {
//        memcpy(pData->d, pKey->d->d, sizeof(pData->d));
//        pData->top = pKey->d->top;
//        pData->dmax = pKey->d->dmax;
//        pData->neg = pKey->d->neg;
//        pData->flags = pKey->d->flags;
//    }
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}
//
//BOOL RSA_FromData2Key(BIG_NUM_DATA* pData, RSA* pKey, BOOL bPublic)
//{
//	LOG_PROCESS_ERROR(pData);
//	LOG_PROCESS_ERROR(pKey);
//
//	if (bPublic)
//	{
//		pKey->n = BN_new();
//		LOG_PROCESS_ERROR(pKey->n);
//
//		pKey->n->dmax   = pData->dmax;
//		pKey->n->neg	= pData->neg;
//		pKey->n->top	= pData->top;
//		bn_expand2((BIGNUM*)pKey->n, pData->dmax + 1);
//		LOG_PROCESS_ERROR(pKey->n->d);
//		memcpy(pKey->n->d, pData->d, sizeof(UINT64) * pData->dmax);
//
//        pKey->e = BN_new();
//        LOG_PROCESS_ERROR(pKey->e);
//
//        BN_set_word(pKey->e, RSA_KEY_E);
//	}
//	else
//	{
//		pKey->d = BN_new();
//		LOG_PROCESS_ERROR(pKey->d);
//
//		pKey->d->dmax   = pData->dmax;
//		pKey->d->neg	= pData->neg;
//		pKey->d->top	= pData->top;
//		bn_expand2((BIGNUM*)pKey->d, pData->dmax + 1);
//		LOG_PROCESS_ERROR(pKey->d->d);
//
//		memcpy(pKey->d->d, pData->d, sizeof(UINT64) * pData->dmax);
//
//        pKey->e = BN_new();
//        LOG_PROCESS_ERROR(pKey->e);
//
//        BN_set_word(pKey->e, RSA_KEY_E);
//}
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
