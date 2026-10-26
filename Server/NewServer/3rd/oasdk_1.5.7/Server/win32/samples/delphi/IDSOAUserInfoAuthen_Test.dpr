program IDSOAUserInfoAuthen_Test;

{$APPTYPE CONSOLE}

uses
  Windows,
  SysUtils,
  sdoa4server in 'sdoa4server.pas';

var
  g_szBuf: array[0..1023] of AnsiChar;

function DoUserInfoCallback(nResult: Integer; nUniqueId: Cardinal; pMsg: ISDOAMsg): Integer; stdcall;
begin
//  if (nUniqueId mod 1000 = 0) then
//  begin
    Writeln(Format('PTID=:%s'^M^J'SNDAID=:%s'^M^J'UID=:%s'^M^J'IDCARD=:%s'^M^J'Return is:%d'^M^J'uniqueId is:%d',
                   [pMsg.GetValue('PTID'), pMsg.GetValue('SNDAID'), pMsg.GetValue('UID'), pMsg.GetValue('IDCARD'), nResult, nUniqueId]));
//  end;

  Result := 0;
end;
  
var
  pUserAuthen: ISDOAUserInfoAuthen;
  strToken: AnsiString;
  nSuccess, nFail: Integer;
  i: Integer;
  b: Integer;
begin
  strToken := '4B8017BC3A6C403FB902D19812C47F42';
  FillChar(g_szBuf, SizeOf(g_szBuf), 0);

  pUserAuthen := sdoaCreateUserInfoAuthen();
  pUserAuthen.Initialize('sdoa4server.ini', @DoUserInfoCallback);

  nSuccess := 0;
  nFail := 0;

  for i := 0 to 1000000 do
  begin
    b := pUserAuthen.AsyncGetUserInfo(PAnsiChar(strToken), '61.172.241.98', i);
    if b = 0 then
    begin
      Inc(nSuccess);
    end
    else 
    begin
      Inc(nFail);
    end;
  end;
  Writeln(Format('success = %d'^M^J'fail = %d', [nSuccess, nFail]));

{$IFDEF MSWINDOWS}
  Readln(System.Input);
{$ENDIF}
{$IFDEF LINUX}
  Sleep(20);
  Writeln('sleep over');
{$ENDIF}
end.
