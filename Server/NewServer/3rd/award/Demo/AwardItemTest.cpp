// AwardItemTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AwardItemTest.h"
#include "AwardItemTestDlg.h"
#include <fstream>
#include "sotsapi.h"
#include "awardinfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void HandleSotsCallback(ULONG, char*, char*, INT32);

SOTSCLIENTINFO		cltinfo;

FunRmInitialize          pRmInitialize        ;
FunRmTerminate           pRmTerminate         ;
FunRmAsynCall            pRmAsynCall          ;
FunRmGetSotsUniqueId     pRmGetSotsUniqueId   ;

void HandleSotsCallback1(ULONG, char*, char*, INT32);

FunRmInitialize          pRmInitialize1        ;
FunRmTerminate           pRmTerminate1         ;
FunRmAsynCall            pRmAsynCall1          ;
FunRmGetSotsUniqueId     pRmGetSotsUniqueId1   ;

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestApp

BEGIN_MESSAGE_MAP(CAwardItemTestApp, CWinApp)
	//{{AFX_MSG_MAP(CAwardItemTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestApp construction

CAwardItemTestApp::CAwardItemTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAwardItemTestApp object

CAwardItemTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAwardItemTestApp initialization

BOOL CAwardItemTestApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//
	// Initialize UMP enviroment
	//
	HINSTANCE hInst = LoadLibrary("sotsapi.dll");
	pRmInitialize = (FunRmInitialize)GetProcAddress(hInst, "SotsInitialize");
	pRmTerminate = (FunRmTerminate)GetProcAddress(hInst, "SotsTerminate");
	pRmAsynCall = (FunRmAsynCall)GetProcAddress(hInst, "SotsAsynCall");
	pRmGetSotsUniqueId = (FunRmGetSotsUniqueId)GetProcAddress(hInst, "GetSotsUniqueId");

	char inifile[256];
	::GetModuleFileName(NULL, inifile, 256);
	CString strFileName(inifile);
	CString strFilePath = strFileName.Left(strFileName.ReverseFind('\\'));
	CString strIniFile = strFilePath + "\\ToolsGetConfig.ini";
	
	//SetCurrentDirectory((LPCTSTR)strFilePath);

	if (pRmInitialize((LPCTSTR)strIniFile, HandleSotsCallback) != 1)
	{
		AfxMessageBox("初始化SOST失败！");
		return FALSE;
	}

	CAwardItemTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void HandleSotsCallback(ULONG handle, char* pServiceName, char *pData, INT32 len)
{
	int i = 0;

	//
	// Get configuration. Don't Change.
	//
	if (strcmp(pServiceName, SVCSOTSSYSTEM) == 0)
	{
		char msgInfo[2048];
			
		SotsClientInfoDef *p = (SotsClientInfoDef *)msgInfo;
		memcpy(msgInfo,pData,len);
		if (p->msgHead.msgType == TYPESOTSCLIENTINFO)
		{
			memcpy(&cltinfo,&p->msgBody,sizeof(SOTSCLIENTINFO));
		}
		return ;
	}

	//
	// Get reply message
	//
	if (handle != 0)
	{
		MsgHeadDef *pHead = (MsgHeadDef *)pData;
		int msgType = ntohl(pHead->msgType);
		if (msgType == GOLDAWARDAUTHENRES)
		{
			GoldAwardAuthenInfoResDef *p = (GoldAwardAuthenInfoResDef *)pData;
			
			int r = ntohl(p->msgBody.result);
			if ( r < 0 || r > 1)
			{
				//
				// UMP server return error
				//
				return;
			}
			if (r == 0 || r == 1)
			{
				//
				// Get ItemInfo.
				//
				int len = 0;
				for (int j=0; j<ntohl(p->msgBody.itemKindCount); j++)
				{
					char * tmpBuf = p->msgBody.itemInfo + len;
    				ItemInfoDef *q = (ItemInfoDef *)tmpBuf;

					char tmp[200];
					sprintf(tmp, "(%s, %d, %s)", q->itemId, ntohl(q->itemNum), q->itemAttr);

					// Get duration from q->itemAttr (format: "D:100").
					char *p = strstr(q->itemAttr, "D:");
					if (p == NULL)
					{
						// No duration
					}
					else
					{
						int duration = atoi(p+2);
					}
					
					int itemLen ;
					if ((ntohl(q->itemAttrLen) % 4) == 0)
					{
						itemLen = ntohl(q->itemAttrLen) ;
					}
					else
					{
						itemLen = (ntohl(q->itemAttrLen)/4 + 1) * 4;
					}
	    			
					len += sizeof(ItemInfoDef) - 4 + itemLen;
				}
				
				//
				// Handle ItemInfo
				//


				//
				// Send ack to UMP server.
				//
				char buf[2048];
				GoldAwardAckInfoDef *awardAck = (GoldAwardAckInfoDef *)buf;
				awardAck->msgHead.msgType = htonl(4);
				awardAck->msgHead.callTime = htonl(time(NULL));
				awardAck->msgHead.version = p->msgHead.version;
				awardAck->msgHead.msgLen = htonl(sizeof(awardAck));

				pRmGetSotsUniqueId(awardAck->msgHead.msgId, 33);
				strcpy(awardAck->msgBody.orderId, p->msgBody.orderId);  // Copy orderId from UMP server
				strcpy(awardAck->msgBody.userId, p->msgBody.userId);	// Copy userId from UMP server
				
				awardAck->msgBody.uidType = htonl(2);			// Set user account type
				awardAck->msgBody.itemKindCount = 0;			// Set default value
				awardAck->msgBody.itemInfoLen = 0;				// Set default value
			
				awardAck->msgBody.confirm = htonl(0);			// 0-succ, other-fail
				strcpy(awardAck->msgBody.description, "OK");	// OK or FAIL

				len = sizeof(GoldAwardAckInfoDef) - 4 + 0;		// Caculate message size
				awardAck->msgHead.msgLen = htonl(len);
				awardAck->msgHead.msgType = htonl(GOLDAWARDACK);
				ULONG hRpc = pRmAsynCall(SVCAWARDITEM, (char *)awardAck, len, 4);
			}
		}
	}
}

int CAwardItemTestApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	pRmTerminate();
	return CWinApp::ExitInstance();
}
