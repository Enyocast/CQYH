program IDSOAOrderInfoHandle_Test;

{$APPTYPE CONSOLE}

uses
  Windows,
  SysUtils,
  sdoa4server in 'sdoa4server.pas';

//Callback handler
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
      begin  //Handle item delivery request
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

        // Return the response
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);

        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
        pRes.SetValue('descMsg', PAnsiChar(descMsg));
        pRes.SetValue('appendix', PAnsiChar(appendix));
      end;

    SDOA_DEPOSIT_REQUEST:
      begin //Handle top-up request
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

        // Return the response
        descMsg := Format('descMsg-%d', [i]);
        appendix := Format('appendix-%d', [i]);

        pRes.SetValue('result', '0');
        pRes.SetValue('orderId', pReq.GetValue('orderId'));
        pRes.SetValue('descMsg', PAnsiChar(descMsg));
        pRes.SetValue('appendix', PAnsiChar(appendix));
      end;
  end;
  Result := 0;
end;
  
var
  pOrderHandle: ISDOAOrderHandler;
  obj: ULONG;
  szId: array[0..32] of AnsiChar;
  szUrl: array[0..2047] of AnsiChar;
begin
  pOrderHandle := sdoaCreateOrderHandler;

  //Initialize the Quanfutong client
  pOrderHandle.Initialize('sdoa4server.ini', @DoMsgHandle);
    
  //Example of creating order information; destroy the returned obj with DestroyOrderInfo
  //Use this when a player requests payment; generate order information for the request type
  //Refer to the protocol documentation for the values to set
  obj := pOrderHandle.CreateOrderInfo(1);
  if obj = 0 then Exit;

  //Example of generating a unique order number inside the function
  pOrderHandle.GetUniqueId(szId);
  Writeln(Format('qftGetUniqueId = %s', [szId]));

  pOrderHandle.SetOrderInfoValue(obj , 'orderId', szId);
  pOrderHandle.SetOrderInfoValue(obj , 'userId', 'test');
  pOrderHandle.SetOrderInfoValue(obj , 'amount', '32');
  pOrderHandle.SetOrderInfoValue(obj , 'payType', '1');
  pOrderHandle.SetOrderInfoValue(obj , 'goodsNum', '2');
  pOrderHandle.SetOrderInfoValue(obj , 'goodsInfo', '1098,1,1#1099,1,1');
  pOrderHandle.SetOrderInfoValue(obj , 'indication', 'test');

  //Sign the data and generate URL parameters; szUrl is returned to the client
  pOrderHandle.BuildOrderUrl(obj, szUrl);
  Writeln(Format('szUrl=%s', [szUrl]));
    
  //Destroy the order information
  pOrderHandle.DestroyOrderInfo(obj);

end.
