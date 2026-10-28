{*
* Copyright (c) 2009,Shanda Online Billing Platform Center
* All rights reserved.
*
* File name:sdoa4server.h
* Summary:Interface function definitions
* Current version:2.0
* Author:SNDA
* Completion date:2009-02-23
*
* Changes:Final 2.0 public interface
* Modified:2009-03-10
*}

unit sdoa4server;

interface

uses
  Windows;

{$DEFINE USE_SDOARSA}
  
const
{$IFDEF MSWINDOWS}
  DLLNAME_SDOA4SERVER     = 'SDOA4ServerDLL.dll';
{$ENDIF}
{$IFDEF LINUX}
  DLLNAME_SDOA4SERVER     = 'libSDOA4Server.so';
{$ENDIF}
    
const
  SDOA_ITEM_SEND_REQUEST   = $01000001;
  SDOA_DEPOSIT_REQUEST     = $01000003;

type
  SNDAIID = Pointer;

  { ISDUnknown }
  
  ISDUnknown = class
    function QueryInterface(iid: SNDAIID; var ppv): HRESULT; virtual; stdcall; abstract;
    function _Reserved(): ULONG; virtual; stdcall; abstract;
    function Release(): ULONG; virtual; stdcall; abstract;
  end;

  { ISDOAMsg }

  ISDOAMsg = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //Name: GetValue
    //Description: Get the value of the specified field in a message
    //Parameters:
    //  [in]szKey:         Data key
    //Returns:                 Value for the key, or NULL if the key is absent
    //----------------------------------------------------------------------------------------
    function GetValue(const szKey: PAnsiChar): PAnsiChar; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: SetValue
    //Description: Add a field value to a message
    //Parameters:
    //  [in]szKey:         Data key
    //  [in]szValue:       Data value
    //Returns:                 0 on success; other values indicate failure, usually a data length overflow
    //----------------------------------------------------------------------------------------
    function SetValue(const szKey, szValue: PAnsiChar): Integer; virtual; stdcall; abstract;

  end;

  { ISDOAUserInfoAuthen }
  
  //---------------------------------------------------------------------------------------
  //Name: UserInfoCallback
  //Description: Authentication information callback implemented by the SDK user
  //Parameters:
  //  [out]nResult:          Result code (see the error documentation for details)
  //  [out]nUniqueId:        Correlation ID
  //  [in/out]pMsg:          Message parsing and setting interface
  //Returns: None
  //----------------------------------------------------------------------------------------
  TUserInfoCallback = function(nResult: Integer; nUniqueId: Cardinal; pMsg: ISDOAMsg): Integer; stdcall;

  ISDOAUserInfoAuthen = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //Name: Initialize
    //Description: Initialize
    //Parameters:
    //  [in]szConfPath:    Configuration file; NULL selects the default ConfClt.conf
    //  [in]pCallbackFunc: Callback function address
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function Initialize(const szConfPath: PAnsiChar; pCallbackFunc: TUserInfoCallback): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: AsyncGetUserInfo
    //Description: Get the authentication result asynchronously (set the callback with Initialize)
    //Parameters:
    //  [in]sessionId:     Token or SessionId to validate
    //  [in]clientIp:      Client IP address
    //  [in]nUniqueId:     Unique token ID
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function AsyncGetUserInfo(const szSessionId, szEndpointIp: PAnsiChar; nUniqueId: Cardinal): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: SyncGetUserInfo
    //Description: Get the authentication result synchronously
    //Parameters:
    //  [in]sessionId:     Token or SessionId to validate
    //  [in]clientIp:      Client IP address
    //  [in/out]pMsg:      Returned user information
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function SyncGetUserInfo(const szSessionId, szEndpointIp: PAnsiChar; nUniqueId: Cardinal; pMsg: ISDOAMsg): Integer; virtual; stdcall; abstract;

  end;

{$IFDEF USE_SDOARSA}

  { ISDOARSASign }

  ISDOARSASign  = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //Name: InitialPriKey
    //Description: Initialize RSA signing with the private key file used to sign orders
    //Parameters:
    //  [in]szPriKeyFile:  Private key file name (absolute or relative path)
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function InitialPriKey(const szPriKeyFile: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //Name: Sign
    //Description: Sign order parameters with the merchant private key and return the signature
    //Parameters:
    //  [in]szData:        Data to sign
    //  [in]nDataLength:   Length of the data to sign
    //  [out]szSignature:  Signature, 512 bytes long.
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function Sign(const szData: PAnsiChar; nDataLength: Integer; szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //Name: InitialPubKey
    //Description: Initialize RSA signature verification with the public key file
    //Parameters:
    //  [in]szPubKeyFile:  Public key file name (absolute or relative path)
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function InitialPubKey(const szPubKeyFile: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //Name: VerifySignature
    //Description: Verify item delivery notification parameters submitted to the Shanda billing interface using the Shanda public key
    //Parameters:
    //  [in]szData:        Source data to verify
    //  [in]nDataLength:   Length of the source data to verify
    //  [in]szSignature:   Signature to verify
    //Returns:                 0 on success; nonzero on failure;
    //----------------------------------------------------------------------------------------
    function VerifySignature(const szData: PAnsiChar; nDataLength: Integer; const szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

  end;

{$ENDIF} //ifdef USE_SDOARSA

//---------------------------------------------------------------------------------------
//Name: RecvMsgCallback
//Description: Order information callback implemented by the SDK user
//Parameters:
//  nMsgType:              Message type: item delivery or top-up; see itemproto.h
//  pRequest:              Request message object: ISDOAMsg containing only the body; see itemproto.h
//  pResponse:             Callback response: ISDOAMsg containing only the body; see itemproto.h
//Returns:                     None
//----------------------------------------------------------------------------------------

  { ISDOAOrderHandler }

  TRecvMsgCallback = function(nMsgType: Integer; pRequest: ISDOAMsg; pResponse: ISDOAMsg): Integer; stdcall;
  //2009-8-28
  TAsyncMsgCallback = function(nMsgType: Integer; nMsgFrom: Integer;nMsgSeq: Integer;pRequest: ISDOAMsg): Integer; stdcall;

  ISDOAOrderHandler = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //Name: Initialize
    //Description: Initialize the Quanfutong client
    //Parameters:
    //  [in]szConfPath:    Configuration file; NULL selects the default ConfClt.conf
    //  [in]pCallbackFunc: Message processing callback
    //Returns:                 0 on success; nonzero on failure;
    //                      -10225001 Configuration file does not exist
    //                      -10225002 Failed to generate authorization configuration
    //                      -10225003 Failed to initialize the authorization SDK
    //                      -10225004 Failed to create the network dispatch thread
    //                      -10225005 Failed to create the local listening socket
    //                      -10225006 Failed to create the callback thread
    //----------------------------------------------------------------------------------------
    function Initialize(const szConfPath: PAnsiChar; pCallbackFunc: TRecvMsgCallback): Integer; virtual; stdcall; abstract;


    //2009-8-28
    //----------------------------------------------------------------------------------------
    //Name: InitializeEx
    //Description: Initialize the Quanfutong client with asynchronous responses for deferred delivery; call either this or Initialize, not both
    //Parameters:
    //	[in]szConfPath:    Configuration file; NULL selects the default sdoa4server.ini
    //	[in]pCallbackFunc: Message processing callback
    //Returns:                 0 on success; nonzero on failure;
    //						-10225000 Already initialized
    //                      -10225001 Configuration file does not exist
    //                      -10225002 Failed to generate authorization configuration
    //                      -10225003 Failed to initialize the authorization SDK
    //                      -10225004 Failed to create the network dispatch thread
    //                      -10225005 Failed to create the local listening socket
    //                      -10225006 Failed to create the callback thread
    //----------------------------------------------------------------------------------------
    function InitializeEx(const szConfPath: PAnsiChar; pCallbackFunc: TAsyncMsgCallback): Integer; virtual; stdcall; abstract;



    //----------------------------------------------------------------------------------------
    //Name: CreateOrderInfo
    //Description: Create order information
    //Parameters:
    //  [in]nType:         1: billing information; 2: item delivery information
    //Returns:                 Order information; 0 on failure
    //                      Nonzero ULONG object pointer
    //----------------------------------------------------------------------------------------
    function CreateOrderInfo(nType: Integer): ULONG; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //Name: DestroyOrderInfo
    //Description: Destroy order information
    //Parameters:
    //  [in]pOrderInfo:    Order information
    //Returns:                 0 on success; no other result
    //----------------------------------------------------------------------------------------
    function DestroyOrderInfo(pOrderInfo: ULONG): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: SetOrderInfoValue
    //Description: Add a value to order information
    //Parameters:
    //  [in]pOrderInfo:    Order information
    //  [in]szKey[in]:     Data key
    //  [in]szValue:       Data value
    //Returns: 0               Success; no other result
    //----------------------------------------------------------------------------------------
    function SetOrderInfoValue(pOrderInfo: ULONG; const szKey, szValue: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: BuildOrderUrl
    //Description: Sign order information and return the corresponding HTTP request
    //Parameters:
    //  [in]pOrderInfo:    Billing object
    //  [out]szUrl:        HTTP request URL, at most 2048 bytes, e.g. char szUrl[2048]
    //Returns:                 0 on success; no other result
    //----------------------------------------------------------------------------------------
    function BuildOrderUrl(pOrderInfo: ULONG; szUrl: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: SignData
    //Description: Sign a data packet
    //Parameters:
    //  [in]szData:        Data to sign
    //  [in]nDataLength:   Length of the data to sign
    //  [out]szSignature:  Return a 32-byte packet signature plus a null terminator; provide 33 bytes, e.g. char szUrl[33]
    //Returns:                 0 on success; nonzero on failure;
    //                      -10225007 Failure
    //----------------------------------------------------------------------------------------
    function SignData(const szData: PAnsiChar; nDataLength: Integer; szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: VerifySignature
    //Description: Verify a data packet signature
    //Parameters:
    //  [in]szData:        Source data to verify
    //  [in]nLen:          Length of the source data to verify
    //  [in]szOriginalSign:Signature to verify
    //Returns:                 0 on success; nonzero on failure;
    //                      -10225008  Failure
    //----------------------------------------------------------------------------------------
    function VerifySignature(const szData: PAnsiChar; nDataLength: Integer; const szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //Name: GetUniqueId
    //Description: Get a unique ID
    //Parameters:
    //  [out]szUniqueId:   Output buffer for a 32-byte unique ID plus a null terminator; provide 33 bytes, e.g. char szUrl[33]
    //Returns:                 0 on success; nonzero on failure;
    //                      -10225009  Parameter is NULL
    //----------------------------------------------------------------------------------------
    function GetUniqueId(szUniqueId: PAnsiChar): Integer; virtual; stdcall; abstract;


    //2009-8-28
    //---------------------------------------------------------------------------------------
    //Name: SendResponse
    //Description: Send a response asynchronously
    //Parameters:
    //	nMsgType:              Message type from the AsyncMsgCallback callback
    //	nMsgFrom:              Message source from AsyncMsgCallback; pass it when sending the response.
    //	nMsgSeq:               Message sequence from AsyncMsgCallback; pass it when sending the response
    //Returns:                      0 on success; nonzero on failure;
    //							-10225010	orderid does not exist or is NULL
    //							-10225011	Network disconnected
    //							-10225012	Message source does not exist, usually after a network disconnect
    //----------------------------------------------------------------------------------------
    function SendResponse(nMsgType: Integer; nMsgFrom: Integer; nMsgSeq: Integer; pResponse: ISDOAMsg): Integer; virtual; stdcall; abstract;




    //----------------------------------------------------------------------------------------
    //Name: UnInitialize
    //Description: Uninitialize the Quanfutong client
    //Parameters:
    //  None
    //Returns:                 0 on success; no other failure result;
    //----------------------------------------------------------------------------------------
    function UnInitialize(): Integer; virtual; stdcall; abstract;

  end;

function sdoaCreateMsg(): ISDOAMsg; stdcall; external DLLNAME_SDOA4SERVER;
function sdoaCreateUserInfoAuthen(): ISDOAUserInfoAuthen; stdcall; external DLLNAME_SDOA4SERVER;
{$IFDEF USE_SDOARSA}
function sdoaCreateRSASign(): ISDOARSASign; stdcall; external DLLNAME_SDOA4SERVER;
{$ENDIF}
function sdoaCreateOrderHandler(): ISDOAOrderHandler; stdcall; external DLLNAME_SDOA4SERVER;

implementation

end.
