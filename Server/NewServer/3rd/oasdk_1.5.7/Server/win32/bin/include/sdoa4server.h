/*
* Copyright (c) 2009, Shanda Online Billing Platform Center
* All rights reserved.
* 
* File name: sdoa4server.h
* Summary: Interface function definitions
* Current version: 2.0
* Author: SNDA
* Completed: February 23, 2009
*
* Changes: Final public 2.0 interface
* Modified: March 10, 2009

* Changes: Added extended initialization and message response interfaces
* Modified: June 23, 2009
*/

#ifndef SDOA4SERVER_H
#define SDOA4SERVER_H

#include "sndabase.h"

#define SDOA_ITEM_SEND_REQUEST 	0X01000001
#define SDOA_DEPOSIT_REQUEST 	0X01000003

interface ISDOAMsg : ISDUnknown 
{
	//----------------------------------------------------------------------------------------
	//Name: GetValue
	//Description: Get a field value from a message
	//Parameters:
	//	[in] szKey: Data key
	//Returns: Value for the key, or NULL if absent
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(const char*)	GetValue(const char* szKey) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: SetValue
	//Description: Add a field value to a message
	//Parameters:
	//	[in] szKey: Data key
	//	[in] szValue: Data value
	//Returns: 0 on success; other values indicate failure (usually data length overflow)
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int)	SetValue(const char* szKey, const char* szValue) = 0;
};
SNDAAPI(ISDOAMsg*) sdoaCreateMsg(void);
//---------------------------------------------------------------------------------------
//Name: UserInfoCallback
//Description: Authentication callback implemented by the SDK user
//Parameters:
//	[out] nResult: Result (see error documentation for error types)
//	[out] nUniqueId: Correlation ID
//	[in/out] pMsg: Message parsing and setting interface
//Returns: Nothing
//----------------------------------------------------------------------------------------
typedef int (SNDACALLBACK *UserInfoCallback)(int nResult, unsigned long nUniqueId, ISDOAMsg *pMsg);

interface ISDOAUserInfoAuthen : ISDUnknown
{
	//----------------------------------------------------------------------------------------
	//Name: Initialize
	//Description: Initialize
	//Parameters:
	//	[in] szConfPath: Configuration file; NULL selects the default ConfClt.conf
	//	[in] pCallbackFunc: Callback function address
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) Initialize(const char *szConfPath, UserInfoCallback pCallbackFunc) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: AsyncGetUserInfo
	//Description: Get authentication result asynchronously (set callback with Initialize)
	//Parameters:
	//	[in] szSessionId: Token or session ID to validate
	//	[in] szEndpointIp: Client IP
	//	[in] nUniqueId: Unique token ID
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) AsyncGetUserInfo(const char *szSessionId, const char *szEndpointIp, const unsigned long nUniqueId) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: SyncGetUserInfo
	//Description: Get authentication result synchronously
	//Parameters:
	//	[in] szSessionId: Token or session ID to validate
	//	[in] szEndpointIp: Client IP
	//	[in] nUniqueId: Unique token ID
	//	[in/out] pMsg: Returned user information
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) SyncGetUserInfo(const char *szSessionId, const char *szEndpointIp, const unsigned long nUniqueId, ISDOAMsg* pMsg) = 0;

};
SNDAAPI(ISDOAUserInfoAuthen*) sdoaCreateUserInfoAuthen(void);

interface ISDOARSASign : ISDUnknown
{
	//----------------------------------------------------------------------------------------
	//Name: InitialPriKey
	//Description: Set the private key file for RSA order signing and initialize the signing interface
	//Parameters:
	//	[in] szPriKeyFile: Private key file name (absolute or relative path)
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) InitialPriKey(const char *szPriKeyFile) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: Sign
	//Description: Sign order parameters with the merchant private key and obtain a signature string
	//Parameters:
	//	[in] szData: Data to sign
	//	[in] nDataLength: Length of data to sign
	//	[out] szSignature: Signature, 512 bytes long
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) Sign(const char *szData, int nDataLength, char* szSignature) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: InitialPubKey
	//Description: Set the public key file for RSA order signature verification and initialize the verification interface
	//Parameters:
	//	[in] szPubKeyFile: Public key file name (absolute or relative path)
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) InitialPubKey(const char *szPubKeyFile) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: VerifySignature
	//Description: Verify item delivery notification parameters submitted by the Shanda billing interface using the Shanda public key
	//Parameters:
	//	[in] szData: Source data to verify
	//	[in] nDataLength: Length of source data to verify
	//	[in] szSignature: Signature to verify
	//Returns: 0 on success; nonzero on failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) VerifySignature(const char *szData,int nDataLength,const char* szSignature) = 0;
};
SNDAAPI(ISDOARSASign*) sdoaCreateRSASign(void);

//---------------------------------------------------------------------------------------
//Name: RecvMsgCallback
//Description: Order callback implemented by the SDK user; set it immediately
//Parameters:
//	nMsgType: Message type; item and recharge messages are defined in itemproto.h
//	pRequest: Request message object; see ISDOAMsg and the relevant protocol
//	pResponse: Response after callback processing; see ISDOAMsg and the relevant protocol
//Returns: Nothing
//----------------------------------------------------------------------------------------
typedef int (SNDACALLBACK *RecvMsgCallback)(int nMsgType, ISDOAMsg* pRequest, ISDOAMsg* pResponse);

//---------------------------------------------------------------------------------------
//Name: AsyncMsgCallback
//Description: Order callback implemented by the SDK user; call SendResponse after receiving a message
//Parameters:
//	nMsgType: Message type; pass it when sending the response
//	nMsgFrom: Message source; pass it when sending the response
//	nMsgSeq: Message sequence number; pass it when sending the response
//Returns: Nothing
//----------------------------------------------------------------------------------------
typedef int (SNDACALLBACK *AsyncMsgCallback)(int nMsgType, int nMsgFrom, int nMsgSeq, ISDOAMsg* pRequest);

interface ISDOAOrderHandler : ISDUnknown
{
	//----------------------------------------------------------------------------------------
	//Name: Initialize
	//Description: Initialize the QuanFuTong client with synchronous responses; call only one of Initialize and InitializeEx
	//Parameters:
	//	[in] szConfPath: Configuration file; NULL selects the default sdoa4server.ini
	//	[in] pCallbackFunc: Message handling callback
	//Returns: 0 on success; nonzero on failure
	//						-10225000 Already initialized
	//                      -10225001 Configuration file does not exist
	//                      -10225002 Failed to generate authorization configuration
	//                      -10225003 Failed to initialize authorization SDK
	//                      -10225004 Failed to create network dispatch thread
	//                      -10225005 Failed to create local listening socket
	//                      -10225006 Failed to create callback thread
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) Initialize(const char *szConfPath, RecvMsgCallback pCallbackFunc) = 0;

	//----------------------------------------------------------------------------------------
	//Name: InitializeEx
	//Description: Initialize the QuanFuTong client with asynchronous responses for later delivery; call only one of Initialize and InitializeEx
	//Parameters:
	//	[in] szConfPath: Configuration file; NULL selects the default sdoa4server.ini
	//	[in] pCallbackFunc: Message handling callback
	//Returns: 0 on success; nonzero on failure
	//						-10225000 Already initialized
	//                      -10225001 Configuration file does not exist
	//                      -10225002 Failed to generate authorization configuration
	//                      -10225003 Failed to initialize authorization SDK
	//                      -10225004 Failed to create network dispatch thread
	//                      -10225005 Failed to create local listening socket
	//                      -10225006 Failed to create callback thread
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) InitializeEx(const char *szConfPath, AsyncMsgCallback pCallbackFunc) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: CreateOrderInfo
	//Description: Create order information
	//Parameters:
	//	[in]nType：         1.BILLINGTYPE，2.SENDITEMTYPE, 3 SELLCURRENCYTYPE，
	//						4 SELLITEMTYPE，5 CONSIGNTYPE, 6 SDOPAYEX
	//Returns: Order information, or 0 on failure
	//                      Nonzero is a ULONG object pointer
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(ULONG) CreateOrderInfo(const int nType) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: DestroyOrderInfo
	//Description: Destroy order information
	//Parameters:
	//	[in] pOrderInfo: Order information
	//Returns: 0 on success; no other return value
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) DestroyOrderInfo(ULONG pOrderInfo) = 0;
	
	//----------------------------------------------------------------------------------------
	//Name: SetOrderInfoValue
	//Description: Add a value to order information
	//Parameters:
	//	[in] pOrderInfo: Order information
	//	[in] szKey[in]: Data key
	//	[in] szValue: Data value
	//Returns: 0 on success
	//                      -10225013 String value exceeds the field length limit
	//                      -10225014 Integer field value contains nonnumeric characters
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) SetOrderInfoValue(ULONG pOrderInfo, const char *szKey, const char *szValue) = 0;

	//----------------------------------------------------------------------------------------
	//Name: BuildOrderUrl
	//Description: Sign order information and return the corresponding HTTP request
	//Parameters:
	//	[in] pOrderInfo: Payment object
	//	[out] szUrl: HTTP request URL, at most 2048 bytes, e.g. char szUrl[2048]
	//Returns: 0 on success; no other return value
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) BuildOrderUrl(ULONG pOrderInfo, char *szUrl) = 0;

	//----------------------------------------------------------------------------------------
	//Name: SignData
	//Description: Sign the data packet
	//Parameters:
	//	[in] szData: Data to sign
	//	[in] nDataLength: Length of data to sign
	//	[out] szSignature: Returns a 32-byte packet signature plus a terminating '\0'; requires 33 bytes, e.g. char szUrl[33]
	//Returns: 0 on success; nonzero on failure
	//                      -10225007 Failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) SignData(const char* szData, const int nDataLength, char* szSignature) = 0;

	//----------------------------------------------------------------------------------------
	//Name: VerifySignature
	//Description: Verify the data packet signature
	//Parameters:
	//	[in] szData: Source data to verify
	//	[in] nDataLength: Length of source data to verify
	//	[in] szSignature: Signature to verify
	//Returns: 0 on success; nonzero on failure
	//                      -10225008	Failure
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) VerifySignature(const char* szData, const int nDataLength, const char* szSignature) = 0;

	//----------------------------------------------------------------------------------------
	//Name: GetUniqueId
	//Description: Get a unique ID
	//Parameters:
	//	[out] szUniqueId: Unique ID output, 32 bytes plus a terminating '\0'; requires 33 bytes, e.g. char szUrl[33]
	//Returns: 0 on success; nonzero on failure
	//                      -10225009	Parameter is NULL
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) GetUniqueId(char *szUniqueId) = 0;
	
	//---------------------------------------------------------------------------------------
	//Name: SendResponse
	//Description: Send a response asynchronously
	//Parameters:
	//	nMsgType: Message type received by AsyncMsgCallback
	//	nMsgFrom: Message source received by AsyncMsgCallback; pass it when sending the response
	//	nMsgSeq: Message sequence number received by AsyncMsgCallback; pass it when sending the response
	//Returns: 0 on success; nonzero on failure
	//							-10225010	orderid does not exist or is NULL
	//							-10225011	Network disconnected
	//							-10225012	Message source does not exist, usually after disconnection
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) SendResponse(int nMsgType, int nMsgFrom, int nMsgSeq, ISDOAMsg* pResponse) = 0;

	//----------------------------------------------------------------------------------------
	//Name: UnInitialize
	//Description: Shut down the QuanFuTong client
	//Parameters:
	//	None
	//Returns: 0 on success; no other failure return
	//----------------------------------------------------------------------------------------
	SNDAMETHOD(int) UnInitialize() = 0;
};
SNDAAPI(ISDOAOrderHandler*) sdoaCreateOrderHandler();

#endif
