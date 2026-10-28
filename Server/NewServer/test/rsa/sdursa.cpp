#include "define.h"
#include "process_error.h"
#include "profile.h"

#include "openssl/rsa.h"
#include "openssl/obj_mac.h"
#include "openssl/md5.h"

/*解决方案sudrsa模拟使用rsakey对buffer进行加解密，本解决方案测试了四种不同的方法*/
/*1.使用公钥加密，用私钥解密*/
/*2.使用私钥加密，用公钥解密*/
/*3.使用私钥签名，用公钥验证*/
/*4.ASN1_OCTET_STRING类型的签名和验证*/


UINT32	dwTargetID = 12345; // 明文前填充内容，可为任意内容
				
UINT32  dwAttr[] = {123,234,345,456,567,123,234,345,456,567,123,234,345,\
					456,567,123,234,345,456,567,123,234,345,456,567,123,234,345,456,567,123,234,\
					345,456,567,123,234,345,456,567,123,234,345,456,567,123,234,345,456,567,123,\
					234,345,456,567,123,234,345,456,567,123,234,345,456,567,123,234,345,456,567,\
					123,234,345,456,567,123,234,345,456,567,123,234,345,456,567,123,234,345,456,\
					567,123,234,345,456,567,123,234,345,456,567};


int main(int argc, char *argv[])
{ 
	INT32 nRetCode =0;
 	INT32 nSize = 0;
	INT32 nAttrCount =  sizeof(dwAttr) / sizeof(dwAttr[0]);

	UINT32 dwBuffer[1024] = {0};		//	用于存储构造的字符串 
	unsigned char md[16] = {0};			// 暂时存放摘要明文

 	unsigned char uszEnc[1024] = {0};	// 暂时存放签名后的摘要
	UINT32  nBufferLength = 0;			// 暂时存放签名验证摘要的长度

	nRetCode = CLog::GetInstance().Init( "RSATest", lltAll, lotConsole | lotFile, TRUE, 0 );
	LOG_PROCESS_ERROR(nRetCode);
	
	/*-----------------------使用私钥签名，用公钥验证------------------------------------------*/

	PROFILE_START();

	RSA* pKey = RSA_generate_key(RsaKeyBit, 1, NULL, NULL);
	PROCESS_ERROR(pKey);;

	PROFILE_POINT(1);

	nSize = sizeof(dwTargetID) + sizeof(dwAttr);
	memset(dwBuffer , 0, sizeof(dwBuffer));

	memcpy(dwBuffer, &dwTargetID, sizeof(dwTargetID));
	memcpy(dwBuffer + 1, dwAttr, sizeof(dwAttr));

	MD5((unsigned char*)dwAttr, nSize, md);

	/*
		memset(pKey->p, 0, sizeof(pKey->p));
		memset(pKey->q, 0, sizeof(pKey->q));
		memset(pKey->d, 0, sizeof(pKey->d));
		pKey->n = NULL;
		pKey->p = NULL;
		pKey->q = NULL;
		pKey->d = NULL;
		p q d 抹去以后，签名时不成功，但是验证时成功
	*/

	nRetCode = RSA_sign(NID_md5, md, sizeof(md) , uszEnc, &nBufferLength, pKey);
	PROCESS_ERROR(nRetCode);

	/*
		pKey->version = 0;
		pKey->pad = 0;
		pKey->flags = 0;
		pKey->references = 0;
		pKey->dmp1 = NULL;
		pKey->dmq1 = NULL;
		pKey->iqmp = NULL;
		memset(&pKey->ex_data, 0, sizeof(pKey->ex_data));
		pKey->_method_mod_n = NULL;
 		pKey->_method_mod_p = NULL;
		pKey->_method_mod_q = NULL;
		pKey->_method_mod_n = NULL;
		pKey->engine = NULL;
		pKey->bignum_data = NULL;
		pKey->blinding = NULL;
		pKey->p = NULL;
		pKey->mt_blinding = NULL;
		验证以上内容跟签名 验证 加密
	*/

	/*
		memset(&(pKey->meth->flags), 0, sizeof(pKey->meth->flags));
		pKey->meth->name = NULL;
		pKey->meth->app_data = NULL;
		pKey->e = NULL;
		验证 n  meth和 e 在解密的时候不能抹去
	*/


	// 重新生成一个空钥匙，将n e 拷贝过来
	RSA* pPublicKey = RSA_new();

	pPublicKey->n = (BIGNUM*)malloc(sizeof(BIGNUM));
	pPublicKey->e = (BIGNUM*)malloc(sizeof(BIGNUM));
	pPublicKey->n->d = (BN_ULONG*)malloc(sizeof(pKey->n->d)*pKey->n->dmax);
	pPublicKey->e->d = (BN_ULONG*)malloc(sizeof(pKey->e->d)*pKey->e->dmax);

	memcpy(pPublicKey->n->d, pKey->n->d, sizeof(pKey->n->d)*pKey->n->dmax);
	memcpy(pPublicKey->e->d, pKey->e->d, sizeof(pKey->e->d)*pKey->e->dmax);

	pPublicKey->n->dmax = pKey->n->dmax;
	pPublicKey->n->flags = pKey->n->flags;
	pPublicKey->n->neg = pKey->n->neg;
	pPublicKey->n->top = pKey->n->top;

	pPublicKey->e->dmax = pKey->e->dmax;
	pPublicKey->e->flags = pKey->e->flags;
	pPublicKey->e->neg = pKey->e->neg;
	pPublicKey->e->top = pKey->e->top;

	nRetCode = RSA_verify(NID_md5, md, sizeof(md), uszEnc, nBufferLength, pPublicKey);
	PROCESS_ERROR(nRetCode);

	PROFILE_END();


 	/*-------------------------------------使用公钥加密，用私解密-------------------------------------------------*/

	INT32 nEncLen = 0;
	INT32 nDecLen = 0;
	INT32 nMsgLen1 = 0;

	UCHAR ucMsg[1024] = {0};
	UCHAR ucEnc[1024] = {0};
	UCHAR ucDec[1024] = {0};

	PROFILE_START();
 	PROCESS_ERROR(pKey);
 
 	PROFILE_POINT(1);
 
	memcpy(ucMsg, dwAttr, sizeof(dwAttr));	
	nMsgLen1 = sizeof(dwAttr);

 	nEncLen = RSA_public_encrypt(nMsgLen1, ucMsg, ucEnc, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nEncLen >= 0);
 
 	PROFILE_POINT(1);
 
 	nDecLen = RSA_private_decrypt(nEncLen, (unsigned char*)ucEnc, (unsigned char*)ucDec, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nDecLen >= 0);
 
 	PROFILE_POINT(1);
 
 	PROFILE_END();
 
 
	/*---------------------------------------使用私钥加密，用公钥解密---------------------------------------*/

 	PROFILE_START();
 
 	PROFILE_POINT(1);
 
 	nEncLen = RSA_private_encrypt(nMsgLen1, ucMsg, ucEnc, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nEncLen >= 0);
 
 	PROFILE_POINT(1);
 
 	nDecLen = RSA_public_decrypt(nEncLen, ucEnc, ucDec, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nDecLen >= 0);
 
 	PROFILE_END();
 

	/*-----------------------------ASN1_OCTET_STRING类型的签名和验证-------------------------------------------*/

 	PROFILE_START();
 
 	PROFILE_POINT(1);
 
	UINT32 dwLength = 0;

 	nEncLen = RSA_sign_ASN1_OCTET_STRING(114, ucMsg, nMsgLen1, uszEnc, &dwLength, pKey);
 	PROCESS_ERROR(nEncLen >= 0);
 
 	PROFILE_POINT(1);
 
 	nDecLen = RSA_verify_ASN1_OCTET_STRING(114, ucEnc, nEncLen, ucDec, 1024, pKey);
 	PROCESS_ERROR(nDecLen >= 0);
 
 	PROFILE_END();

 
 	RSA_free(pKey);
 	return 1;

Exit0:
	return 0;
}

