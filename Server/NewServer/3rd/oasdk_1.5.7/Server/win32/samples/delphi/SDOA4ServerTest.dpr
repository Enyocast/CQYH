program SDOA4ServerTest;

{$APPTYPE CONSOLE}

uses
  Windows,
  SysUtils,
  sdoa4server in 'sdoa4server.pas';

var
  pOrderHandle: ISDOAOrderHandler;


//回调函数体响应异步处理
function FunOrderInfoCallback(nMsgType: Integer; nMsgFrom: Integer;nMsgSeq: Integer;pReq: ISDOAMsg): Integer; stdcall;
const
{$J+}
  i: Integer = 0;
{$J-}
var
  pszMsg: PAnsiChar;
  nGoodNum: Integer;
  nSdId: Integer;
	descMsg, appendix: AnsiString;
  pRes:ISDOAMsg;
begin
  Writeln(Format('orderid=%s', ['AsyncCallBack']));
  i := 0;
	case nMsgType of
	  SDOA_ITEM_SEND_REQUEST:
      begin  //道具发送请求处理
        pszMsg := pReq.GetValue('orderId');
        if (pszMsg <> nil) then
          Writeln(Format('orderid=%s', [pszMsg]));

        pszMsg := pReq.GetValue('payStatus');
        if (pszMsg <> nil) then
          Writeln(Format('payStatus=%s', [pszMsg]));

        pszMsg := pReq.GetValue('sendTimes');
        if (pszMsg <> nil) then
          Writeln(Format('sendTimes=%s', [pszMsg]));

        pszMsg := pReq.GetValue('callTime');
        if (pszMsg <> nil) then
          Writeln(Format('callTime=%s', [pszMsg]));

        pszMsg := pReq.GetValue('userId');
        if (pszMsg <> nil) then
        begin
          nSdId := StrToInt(pszMsg);
          Writeln(Format('userId=%d', [nSdId]));
        end;

        pszMsg := pReq.GetValue('goodsNum');
        if (pszMsg <> nil) then
        begin
          nGoodNum := StrToInt(pszMsg);
          Writeln(Format('goodsNum=%d', [nGoodNum]));
        end;

        pszMsg := pReq.GetValue('goodsInfo');
        if (pszMsg <> nil) then
          Writeln(Format('goodsInfo=%s', [pszMsg]));

        pszMsg := pReq.GetValue('indication');
        if (pszMsg <> nil) then
          Writeln(Format('indication=%s', [pszMsg]));

        Writeln(Format('payErrorMsg=%s', [pReq.GetValue('payErrorMsg')]));

        Inc(i);        

        pRes := sdoaCreateMsg();
        // 返回处理应答信息
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);
        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
	      pRes.SetValue('descMsg', PAnsiChar(descMsg));
	      pRes.SetValue('appendix', PAnsiChar(appendix));

        //异步返回应答
        pOrderHandle.SendResponse(nMsgType, nMsgFrom, nMsgSeq, pRes);
        pRes.Release();
      end;

    SDOA_DEPOSIT_REQUEST:
      begin //充值请求处理
        //serviceId=XX^$^areaId=XX^$^groupId=XX^$^depPayType=XX^$^depValue=XX^$^orderId[32]=XX^$^
        //userId=XX^$^callTime=XX^$^indication

        pszMsg := pReq.GetValue('appId');
        if (pszMsg <> nil) then
          Writeln(Format('appId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('areaId');
        if (pszMsg <> nil) then
          Writeln(Format('areaId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('groupId');
        if (pszMsg <> nil) then
          Writeln(Format('groupId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('depValue');
        if (pszMsg <> nil) then
          Writeln(Format('depValue=%s', [pszMsg]));

        pszMsg := pReq.GetValue('orderId');
        if (pszMsg <> nil) then
          Writeln(Format('orderId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('userId');
        if (pszMsg <> nil) then
          Writeln(Format('userId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('callTime');
        if (pszMsg <> nil) then
          Writeln(Format('callTime=%s', [pszMsg]));

        pszMsg := pReq.GetValue('indication');
        if (pszMsg <> nil) then
          Writeln(Format('indication=%s', [pszMsg]));

        Inc(i);

        pRes := sdoaCreateMsg();
        // 返回处理应答信息
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);
        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
	      pRes.SetValue('descMsg', PAnsiChar(descMsg));
	      pRes.SetValue('appendix', PAnsiChar(appendix));

        //异步返回应答
        pOrderHandle.SendResponse(nMsgType, nMsgFrom, nMsgSeq, pRes);
        pRes.Release();
      end;
  end;

//  Writeln(Format('recv message length=%d', [reqLen]));
	Result := 0;
end;


//回调函数体内处理
function DoMsgHandle(nMsgType: Integer; pReq: ISDOAMsg; pRes: ISDOAMsg): Integer; stdcall;
const
{$J+}
  i: Integer = 0;
{$J-}
var
  pszMsg: PAnsiChar;
  nGoodNum: Integer;
  nSdId: Integer;
	descMsg, appendix: AnsiString;
begin
	case nMsgType of

	  SDOA_ITEM_SEND_REQUEST:
      begin  //道具发送请求处理
        pszMsg := pReq.GetValue('orderId');
        if (pszMsg <> nil) then
          Writeln(Format('orderid=%s', [pszMsg]));

        pszMsg := pReq.GetValue('payStatus');
        if (pszMsg <> nil) then
          Writeln(Format('payStatus=%s', [pszMsg]));

        pszMsg := pReq.GetValue('sendTimes');
        if (pszMsg <> nil) then
          Writeln(Format('sendTimes=%s', [pszMsg]));

        pszMsg := pReq.GetValue('callTime');
        if (pszMsg <> nil) then
          Writeln(Format('callTime=%s', [pszMsg]));

        pszMsg := pReq.GetValue('userId');
        if (pszMsg <> nil) then
        begin
          nSdId := StrToInt(pszMsg);
          Writeln(Format('userId=%d', [nSdId]));
        end;

        pszMsg := pReq.GetValue('goodsNum');
        if (pszMsg <> nil) then
        begin
          nGoodNum := StrToInt(pszMsg);
          Writeln(Format('goodsNum=%d', [nGoodNum]));
        end;

        pszMsg := pReq.GetValue('goodsInfo');
        if (pszMsg <> nil) then
          Writeln(Format('goodsInfo=%s', [pszMsg]));

        pszMsg := pReq.GetValue('indication');
        if (pszMsg <> nil) then
          Writeln(Format('indication=%s', [pszMsg]));

        Writeln(Format('payErrorMsg=%s', [pReq.GetValue('payErrorMsg')]));

        Inc(i);

        // 返回处理应答信息
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);

        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
	      pRes.SetValue('descMsg', PAnsiChar(descMsg));
	      pRes.SetValue('appendix', PAnsiChar(appendix));
      end;

    SDOA_DEPOSIT_REQUEST:
      begin //充值请求处理
        //serviceId=XX^$^areaId=XX^$^groupId=XX^$^depPayType=XX^$^depValue=XX^$^orderId[32]=XX^$^
        //userId=XX^$^callTime=XX^$^indication

        pszMsg := pReq.GetValue('appId');
        if (pszMsg <> nil) then
          Writeln(Format('appId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('areaId');
        if (pszMsg <> nil) then
          Writeln(Format('areaId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('groupId');
        if (pszMsg <> nil) then
          Writeln(Format('groupId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('depValue');
        if (pszMsg <> nil) then
          Writeln(Format('depValue=%s', [pszMsg]));

        pszMsg := pReq.GetValue('orderId');
        if (pszMsg <> nil) then
          Writeln(Format('orderId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('userId');
        if (pszMsg <> nil) then
          Writeln(Format('userId=%s', [pszMsg]));

        pszMsg := pReq.GetValue('callTime');
        if (pszMsg <> nil) then
          Writeln(Format('callTime=%s', [pszMsg]));

        pszMsg := pReq.GetValue('indication');
        if (pszMsg <> nil) then
          Writeln(Format('indication=%s', [pszMsg]));

        Inc(i);

        // 返回处理应答信息
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);

        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
	      pRes.SetValue('descMsg', PAnsiChar(descMsg));
	      pRes.SetValue('appendix', PAnsiChar(appendix));
      end;
  end;

//  Writeln(Format('recv message length=%d', [reqLen]));
	Result := 0;
end;

var
  nTest: Integer = 1;
  
var
  obj: ULONG;
  szId: array[0..32] of AnsiChar;
  szUrl: array[0..2047] of AnsiChar;
begin
  if nTest = 1 then
  begin
		//创建订单处理对象实例
    pOrderHandle := sdoaCreateOrderHandler;

		//初始化全付通客户端/
		pOrderHandle.Initialize('ConfClt.conf', @DoMsgHandle);


		//创建订单信息演示，返回的obj需要DestroyOrderInfo，销毁
		//当玩家有扣费请求过来是需要使用，根据不同的请求生成不同的订单信息
		//具体设置的值需要参照相关协议文档
		obj := pOrderHandle.CreateOrderInfo(1);
		if obj = 0 then Exit;

		//生成唯一订单号码函数演示 函数内生成
		pOrderHandle.GetUniqueId(szId);
		Writeln(Format('qftGetUniqueId = %s', [szId]));

		pOrderHandle.SetOrderInfoValue(obj , 'orderId', szId);
		pOrderHandle.SetOrderInfoValue(obj , 'userId', 'test');
		pOrderHandle.SetOrderInfoValue(obj , 'amount', '32');
		pOrderHandle.SetOrderInfoValue(obj , 'payType', '1');
		pOrderHandle.SetOrderInfoValue(obj , 'goodsNum', '2');
		pOrderHandle.SetOrderInfoValue(obj , 'goodsInfo', '1098,1,1#1099,1,1');
		pOrderHandle.SetOrderInfoValue(obj , 'indication', 'test');

		//对数据签名并生成URL参数串，szUrl用于返回给客户端
		pOrderHandle.BuildOrderUrl(obj, szUrl);
		Writeln(Format('szUrl=%s', [szUrl]));

		//销毁订单信息 
		pOrderHandle.DestroyOrderInfo(obj); 
		while True do
    {$IFDEF MSWINDOWS}
            Sleep(1000);
    {$ENDIF}
    {$IFDEF LINUX}
            Sleep(1);
    {$ENDIF}
		//全付通客户端卸载
		pOrderHandle.UnInitialize();

		//释放资源
		pOrderHandle.Release();
  end
  else if nTest = 2 then  //InitializeEX 异步处理订单应答模式
  begin
    //创建订单处理对象实例
    pOrderHandle := sdoaCreateOrderHandler;

		//初始化全付通客户端，传入异步响应订单应答回调函数/
		pOrderHandle.InitializeEX('ConfClt.conf', @FunOrderInfoCallback);


		//创建订单信息演示，返回的obj需要DestroyOrderInfo，销毁
		//当玩家有扣费请求过来是需要使用，根据不同的请求生成不同的订单信息
		//具体设置的值需要参照相关协议文档
		obj := pOrderHandle.CreateOrderInfo(1);
		if obj = 0 then Exit;

		//生成唯一订单号码函数演示 函数内生成
		pOrderHandle.GetUniqueId(szId);
		Writeln(Format('qftGetUniqueId = %s', [szId]));

		pOrderHandle.SetOrderInfoValue(obj , 'orderId', szId);
		pOrderHandle.SetOrderInfoValue(obj , 'userId', 'test');
		pOrderHandle.SetOrderInfoValue(obj , 'amount', '32');
		pOrderHandle.SetOrderInfoValue(obj , 'payType', '1');
		pOrderHandle.SetOrderInfoValue(obj , 'goodsNum', '2');
		pOrderHandle.SetOrderInfoValue(obj , 'goodsInfo', '1098,1,1#1099,1,1');
		pOrderHandle.SetOrderInfoValue(obj , 'indication', 'test');

		//对数据签名并生成URL参数串，szUrl用于返回给客户端
		pOrderHandle.BuildOrderUrl(obj, szUrl);
		Writeln(Format('szUrl=%s', [szUrl]));

		//销毁订单信息 
		pOrderHandle.DestroyOrderInfo(obj); 
		while True do
    {$IFDEF MSWINDOWS}
            Sleep(1000);
    {$ENDIF}
    {$IFDEF LINUX}
            Sleep(1);
    {$ENDIF}
		//全付通客户端卸载
		pOrderHandle.UnInitialize();

		//释放资源
		pOrderHandle.Release();
  end;




end.
