#ifndef __SDO_LOGIN_H__
#define __SDO_LOGIN_H__

#include <Windows.h>

/* release snda login sdk */
void DestroySDOLogin();

/* load snda login sdk */
void LoadSDOLogin();

/* callback of login sdk */
int CALLBACK OnLogin(int nErrorCode, const struct SDOLLoginResult* pLoginResult, int nUserData, int nReserved);

/* show login dialog */
void ShowLoginDialog();
UBOOL SDOOpenWindow(LPCWSTR pwcsWinType, LPCWSTR pwcsWinName, LPCWSTR pwcsSrc, int nLeft, int nTop,int nWidth, int nHeight, LPCWSTR pwcsMode);


void ShowSDOLoginDialogWnd(bool bForce=false);
void HideSDOLoginDialogWnd();

void MoveSDOLoginWindow(INT x, int y);

extern bool g_isSDOLogin;

#endif