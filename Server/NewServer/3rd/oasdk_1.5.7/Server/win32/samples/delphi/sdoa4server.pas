{*
* Copyright (c) 2009,盛大在线 计费平台中心
* All rights reserved.
*
* 文件名称：sdoa4server.h
* 摘    要：各接口函数定义
* 当前版本：2.0
* 作    者：SNDA
* 完成日期：2009年2月23日
*
* 修改内容：2.0最终对外接口
* 修改时间：2009年3月10日
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
    //名称：GetValue
    //描述：获取指定消息内指定字段的值
    //参数：
    //  [in]szKey：         数据关键字
    //返回：                关键字对应的内容，没有该关键字返回NULL
    //----------------------------------------------------------------------------------------
    function GetValue(const szKey: PAnsiChar): PAnsiChar; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：SetValue
    //描述：给指定消息添加指定字段的值
    //参数：
    //  [in]szKey：         数据关键字
    //  [in]szValue：       数据值
    //返回：                0成功，其他失败（一般为数据长度溢出）
    //----------------------------------------------------------------------------------------
    function SetValue(const szKey, szValue: PAnsiChar): Integer; virtual; stdcall; abstract;

  end;

  { ISDOAUserInfoAuthen }
  
  //---------------------------------------------------------------------------------------
  //名称：UserInfoCallback
  //描述：认证信息回调处理函数，由sdk使用方实现
  //参数：
  //  [out]nResult：          返回消息结果(具体错误类型说明参见相关错误文档)
  //  [out]nUniqueId：        关联ID
  //  [in/out]pMsg：          消息解析设置接口
  //返回：无
  //----------------------------------------------------------------------------------------
  TUserInfoCallback = function(nResult: Integer; nUniqueId: Cardinal; pMsg: ISDOAMsg): Integer; stdcall;

  ISDOAUserInfoAuthen = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //名称：Initialize
    //描述：初始化
    //参数：
    //  [in]szConfPath：    配置文件，如果为NULL则使用缺省的ConfClt.conf配置文件
    //  [in]pCallbackFunc： 回调函数地址
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function Initialize(const szConfPath: PAnsiChar; pCallbackFunc: TUserInfoCallback): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：AsyncGetUserInfo
    //描述：异步获取认证结果(通过Initialize设置回调函数)
    //参数：
    //  [in]sessionId：     需要验证的Token或者SessionId
    //  [in]clientIp：      客户端IP
    //  [in]nUniqueId：     token唯一id
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function AsyncGetUserInfo(const szSessionId, szEndpointIp: PAnsiChar; nUniqueId: Cardinal): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：SyncGetUserInfo
    //描述：同步获取认证结果
    //参数：
    //  [in]sessionId：     需要验证的Token或者SessionId
    //  [in]clientIp：      客户端IP
    //  [in/out]pMsg：      返回的用户信息    
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function SyncGetUserInfo(const szSessionId, szEndpointIp: PAnsiChar; nUniqueId: Cardinal; pMsg: ISDOAMsg): Integer; virtual; stdcall; abstract;

  end;

{$IFDEF USE_SDOARSA}

  { ISDOARSASign }

  ISDOARSASign  = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //名称：InitialPriKey
    //描述：指定订单进行RSA签名时所需的私钥文件位置，初始化RSA私钥签名接口
    //参数：
    //  [in]szPriKeyFile：  私钥文件名(全路径或相对路径)
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function InitialPriKey(const szPriKeyFile: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //名称：Sign
    //描述：基于商户私钥对订单参数进行签名，获得签名字符串
    //参数：
    //  [in]szData：        要签名的数据
    //  [in]nDataLength：   要签名的数据长度 
    //  [out]szSignature：  签名,长度512Byte.
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function Sign(const szData: PAnsiChar; nDataLength: Integer; szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //名称：InitialPubKey
    //描述：指定订单进行RSA签名验证时所需的公钥文件位置，初始化RSA公钥验证接口
    //参数：
    //  [in]szPubKeyFile：  公钥文件名(全路径或相对路径)
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function InitialPubKey(const szPubKeyFile: PAnsiChar): Integer; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //名称：VerifySignature
    //描述：基于盛大公钥对盛大计费接口提交的道具发送通知参数进行验证
    //参数：
    //  [in]szData：        待验证源数据
    //  [in]nDataLength：   待验证源数据长度 
    //  [in]szSignature：   待验证签名
    //返回：                0 成功；!0 失败；
    //----------------------------------------------------------------------------------------
    function VerifySignature(const szData: PAnsiChar; nDataLength: Integer; const szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

  end;

{$ENDIF} //ifdef USE_SDOARSA

//---------------------------------------------------------------------------------------
//名称：RecvMsgCallback
//描述：订单信息回调处理函数，由sdk使用方实现
//参数：
//  nMsgType：              消息类型：目前有道具和充值两个消息，定义参照itemproto.h
//  pRequest：              请求消息对象：参照接口ISDOAMsg，内容只包含包体 定义参照itemproto.h
//  pResponse：             回调处理完后应答：参照接口ISDOAMsg，内容只包含包体 定义参照itemproto.h
//返回：                    无
//----------------------------------------------------------------------------------------

  { ISDOAOrderHandler }

  TRecvMsgCallback = function(nMsgType: Integer; pRequest: ISDOAMsg; pResponse: ISDOAMsg): Integer; stdcall;
  //2009-8-28
  TAsyncMsgCallback = function(nMsgType: Integer; nMsgFrom: Integer;nMsgSeq: Integer;pRequest: ISDOAMsg): Integer; stdcall;

  ISDOAOrderHandler = class(ISDUnknown)

    //----------------------------------------------------------------------------------------
    //名称：Initialize
    //描述：初始化全付通客户端
    //参数：
    //  [in]szConfPath：    配置文件，如果为NULL则使用缺省的ConfClt.conf配置文件
    //  [in]pCallbackFunc： 消息处理回调函数
    //返回：                0 成功；!0 失败；
    //                      -10225001 配置文件不存在
    //                      -10225002 生成授权配置文件失败
    //                      -10225003 授权SDK初始化失败
    //                      -10225004 创建网络调度线程失败
    //                      -10225005 创建本地侦听SOCKET失败
    //                      -10225006 创建回调线程失败
    //----------------------------------------------------------------------------------------
    function Initialize(const szConfPath: PAnsiChar; pCallbackFunc: TRecvMsgCallback): Integer; virtual; stdcall; abstract;


    //2009-8-28
    //----------------------------------------------------------------------------------------
    //名称：InitializeEx
    //描述：初始化全付通客户端，后发货采用异步应答方式。和Initialize只允许调用一个
    //参数：
    //	[in]szConfPath：    配置文件，如果为NULL则使用缺省的sdoa4server.ini配置文件
    //	[in]pCallbackFunc： 消息处理回调函数
    //返回：                0 成功；!0 失败；
    //						-10225000 已经初始化
    //                      -10225001 配置文件不存在
    //                      -10225002 生成授权配置文件失败
    //                      -10225003 授权SDK初始化失败
    //                      -10225004 创建网络调度线程失败
    //                      -10225005 创建本地侦听SOCKET失败
    //                      -10225006 创建回调线程失败
    //----------------------------------------------------------------------------------------
    function InitializeEx(const szConfPath: PAnsiChar; pCallbackFunc: TAsyncMsgCallback): Integer; virtual; stdcall; abstract;



    //----------------------------------------------------------------------------------------
    //名称：CreateOrderInfo
    //描述：创建订单信息
    //参数：
    //  [in]nType：         1.扣费信息，2.道具发送信息
    //返回：                订单信息，0 失败
    //                      !0为ULONG对象指针
    //----------------------------------------------------------------------------------------
    function CreateOrderInfo(nType: Integer): ULONG; virtual; stdcall; abstract;
  
    //----------------------------------------------------------------------------------------
    //名称：DestroyOrderInfo
    //描述：销毁订单信息
    //参数：
    //  [in]pOrderInfo：    订单信息
    //返回：                0 成功，无其他返回
    //----------------------------------------------------------------------------------------
    function DestroyOrderInfo(pOrderInfo: ULONG): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：SetOrderInfoValue
    //描述：往订单信息添加值
    //参数：
    //  [in]pOrderInfo：    订单信息
    //  [in]szKey[in]：     数据关键字
    //  [in]szValue：       数据值
    //返回：0               成功 无其他返回
    //----------------------------------------------------------------------------------------
    function SetOrderInfoValue(pOrderInfo: ULONG; const szKey, szValue: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：BuildOrderUrl
    //描述：签名订单信息，并返回相应http请求内容
    //参数：
    //  [in]pOrderInfo：    扣费对象
    //  [out]szUrl：        http请求URL,最大2048字节如：char szUrl[2048]
    //返回：                0成功，无其他返回
    //----------------------------------------------------------------------------------------
    function BuildOrderUrl(pOrderInfo: ULONG; szUrl: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：SignData
    //描述：数据包签名
    //参数：
    //  [in]szData：        要签名的数据
    //  [in]nDataLength：   要签名的数据长度 
    //  [out]szSignature：  返回32字节的数据包签名,32字节结尾加上'\0'，即需要33字节空间如char szUrl[33]
    //返回：                0 成功；!0 失败；
    //                      -10225007 失败
    //----------------------------------------------------------------------------------------
    function SignData(const szData: PAnsiChar; nDataLength: Integer; szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：VerifySignature
    //描述：数据包签名校验
    //参数：
    //  [in]szData：        待验证源数据
    //  [in]nLen：          待验证源数据长度
    //  [in]szOriginalSign：待验证签名
    //返回：                0 成功；!0 失败；
    //                      -10225008  失败
    //----------------------------------------------------------------------------------------
    function VerifySignature(const szData: PAnsiChar; nDataLength: Integer; const szSignature: PAnsiChar): Integer; virtual; stdcall; abstract;

    //----------------------------------------------------------------------------------------
    //名称：GetUniqueId
    //描述：获取唯一ID
    //参数：
    //  [out]szUniqueId：   唯一ID输出地址,32字节结尾加上'\0'，即需要33字节空间，如char szUrl[33]
    //返回：                0 成功；!0 失败；
    //                      -10225009  参数为NULL
    //----------------------------------------------------------------------------------------
    function GetUniqueId(szUniqueId: PAnsiChar): Integer; virtual; stdcall; abstract;


    //2009-8-28
    //---------------------------------------------------------------------------------------
    //名称：SendResponse
    //描述：异步发送应答响应
    //参数：
    //	nMsgType：              AsyncMsgCallback 回调获得的消息类型
    //	nMsgFrom：              AsyncMsgCallback 消息来源，发送应答时需要作为参数传入。
    //	nMsgSeq：               AsyncMsgCallback 消息序列号，发送应答时需要作为参数传入
    //返回：                     0 成功；!0 失败；
    //							-10225010	orderid不存在为NULL
    //							-10225011	网络断开
    //							-10225012	消息发送源不存在，一般为网络断开后
    //----------------------------------------------------------------------------------------
    function SendResponse(nMsgType: Integer; nMsgFrom: Integer; nMsgSeq: Integer; pResponse: ISDOAMsg): Integer; virtual; stdcall; abstract;




    //----------------------------------------------------------------------------------------
    //名称：UnInitialize
    //描述：全付通客户端卸载
    //参数：
    //  无
    //返回：                0 成功；无其他返回失败；
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
