#include "define.h"
#include "process_error.h"
#include "profile.h"

#include "openssl/rsa.h"
#include "openssl/obj_mac.h"
#include "openssl/md5.h"

/*The sudrsa solution simulates RSA key encryption and decryption of a buffer and tests four methods*/
/*1. Encrypt with the public key and decrypt with the private key*/
/*2. Encrypt with the private key and decrypt with the public key*/
/*3. Sign with the private key and verify with the public key*/
/*4. Sign and verify using ASN1_OCTET_STRING*/


UINT32	dwTargetID = 12345; // Content prepended to plaintext; may be arbitrary
				
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

	UINT32 dwBuffer[1024] = {0};		//	Store the constructed string
	unsigned char md[16] = {0};			// Temporarily store the plaintext digest

	unsigned char uszEnc[1024] = {0};	// Temporarily store the signed digest
	UINT32  nBufferLength = 0;			// Temporarily store the length of the signature verification digest

	nRetCode = CLog::GetInstance().Init( "RSATest", lltAll, lotConsole | lotFile, TRUE, 0 );
	LOG_PROCESS_ERROR(nRetCode);
	
	/*-----------------------Sign with the private key and verify with the public key------------------------------------------*/

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
		After clearing p, q and d, signing fails but verification succeeds
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
		Check the above fields against signing, verification and encryption
	*/

	/*
		memset(&(pKey->meth->flags), 0, sizeof(pKey->meth->flags));
		pKey->meth->name = NULL;
		pKey->meth->app_data = NULL;
		pKey->e = NULL;
		Verify that n, meth and e cannot be cleared during decryption
	*/


	// Create a new empty key and copy n and e into it
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


	/*-------------------------------------Encrypt with the public key and decrypt with the private key-------------------------------------------------*/

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
 
 
	/*---------------------------------------Encrypt with the private key and decrypt with the public key---------------------------------------*/

 	PROFILE_START();
 
 	PROFILE_POINT(1);
 
 	nEncLen = RSA_private_encrypt(nMsgLen1, ucMsg, ucEnc, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nEncLen >= 0);
 
 	PROFILE_POINT(1);
 
 	nDecLen = RSA_public_decrypt(nEncLen, ucEnc, ucDec, pKey, RSA_PKCS1_PADDING);
 	PROCESS_ERROR(nDecLen >= 0);
 
 	PROFILE_END();
 

	/*-----------------------------Sign and verify using ASN1_OCTET_STRING-------------------------------------------*/

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

