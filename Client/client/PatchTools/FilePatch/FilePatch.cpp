/*====================================================================
	Created Date  :		2005-8-25
	
	Specification :  
====================================================================*/
#include "stdafx.h"
#include "FilePatch.h"
#include "FilePatchDlg.h"
#include "CheckServerDlg.h"
#include "Controls.h"
#include "Task.h"
#include "ThreadPool.h"
#include <iostream>

#include <vector>
using namespace std;

//int g_threadCnt = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFilePatchApp theApp;

BEGIN_MESSAGE_MAP(CFilePatchApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CFilePatchApp::CFilePatchApp()
{
}

BOOL CFilePatchApp::InitInstance()
{
//	_tsetlocale(LC_ALL, _T("zh-CN"));
 	_tsetlocale(LC_ALL, NULL);
// 	std::wcout.imbue(locale(""));

	HANDLE hnd = CreateMutex(NULL, FALSE, _T("AOD_Patch"));
	if(hnd)
	{
		DWORD dwR = ::WaitForSingleObject(hnd, 2000); // try 2 seconds
		if(dwR == WAIT_TIMEOUT || dwR == WAIT_ABANDONED)
		{
			CloseHandle( hnd );
			return FALSE;
		}
	}
	
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	

//	UINT winVer = 0;
	OSVERSIONINFO osinfo;
	GetVersionEx(&osinfo);

	if(osinfo.dwMajorVersion > 4)
	{
		HMODULE hMSIModule = 0;
		hMSIModule = LoadLibrary(_T("Msimg32.dll")); 
		if(hMSIModule) 
		{ 
			g_pTransparentBlt = (LPTRANSPARENTBLT) GetProcAddress(hMSIModule, "TransparentBlt"); 
		} 
	}

	srand( (unsigned)time( NULL ) );

	SYSTEM_INFO info;
	GetSystemInfo(&info);	

	//g_threadCnt = info.dwNumberOfProcessors * 2;

	g_genMD5ThreadPool = new CThreadPool(4, true, 50);
	g_compareMD5ThreadPool = new CThreadPool(info.dwNumberOfProcessors * 4, true, 50);
	g_downloadThreadPool = new CThreadPool(32, true, 50);
	g_writeFileThreadPool = new CThreadPool(info.dwNumberOfProcessors * 2, true, 100);

//
//	DWORD id = FindAppProcessID(_T("MMOGame.exe"));
//	if(id != -1)
//	{
//		if(AfxMessageBox(_T("游戏运行，请先关闭游戏才能进行更新！\n\n如果选择确定将强行非正常关闭程序！")
//			, MB_OKCANCEL | MB_ICONHAND) == IDOK
//			)
//		{
//			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
//			if(ProcessHandle)
//				TerminateProcess(ProcessHandle, 0);
//		}
//		else
//		{
//			return FALSE;
//		}
//	}
//
//	vector<SServer> vectorServers;
//
//	// Install Dir
//	TCHAR strBuffer[MAX_PATH];
//	::GetModuleFileName(NULL, strBuffer, MAX_PATH);
//	CString strTmp = strBuffer;
//	CString strPatchConfigFile = strTmp.Left( strTmp.ReverseFind('\\') + 1 );
//	strPatchConfigFile += C_IniFile;
//
//	int iServer = ::GetPrivateProfileInt(_T("Server"), _T("ServerCount"), 0, strPatchConfigFile);
//	if(iServer < 0)
//		iServer = 0;
//
//	for(int i = 0; i < iServer; ++i)
//	{
//		strTmp.Format(_T("Server%d"), i+1);
//		::GetPrivateProfileString(_T("Server")
//			, strTmp, _T("")
//			, strBuffer, MAX_PATH
//			, strPatchConfigFile
//			);
//
//		if( _tcslen(strBuffer) > 6 )
//		{
//			SServer server;
//
//			DWORD dwType;
//			if( ::AfxParseURL(strBuffer, dwType, server._strServer, server._strServerInitPath, server._dwPort)
//				&&
//				AFX_INET_SERVICE_HTTP == dwType
//				)
//			{
//				vectorServers.push_back(server);
//			}
//		}
//	}
//
//	int iValidServer = -1;
//	if(vectorServers.size() == 0)
//	{
//		AfxMessageBox( _T("没有发现更新服务器配置文件：PatchConfig.ini！\n\n也可能更新服务器配置有误！"), MB_OK | MB_ICONINFORMATION );
//		return FALSE;
//	}
//	else
//	{
//		//Show InfoUI
////		CheckServerDlg checkServerDlg;
////		checkServerDlg.Create(CheckServerDlg::IDD);
////		checkServerDlg.ShowWindow(SW_SHOW);
////		checkServerDlg.UpdateWindow();
//
//		CInternetSession		_InternetSession;
//		CHttpConnection			*_pHttpConnection;
//		_InternetSession.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5);
//
//		// 轮询Patch服务器
//		vector<SServer>::iterator it;
//		for(it = vectorServers.begin(); it != vectorServers.end(); )
//		{
//			CString strTestFile = it->_strServerInitPath + _T("index.html");
//			_pHttpConnection = _InternetSession.GetHttpConnection(it->_strServer);
//			CHttpFile *pFile = _pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET
//				, strTestFile
//				, NULL
//				, 1
//				, NULL
//				, NULL
//				, HSR_DOWNLOAD | INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_NO_AUTO_REDIRECT
//				);
//
//			if(!pFile)
//			{
//				it = vectorServers.erase(it);
//				continue;
//			}
//
//			BOOL bWebOK = FALSE;
//			try
//			{
//				if(!pFile->SendRequest())
//				{
//					pFile->Close();
//					it = vectorServers.erase(it);
//					continue;
//				}
//
//				DWORD dwStatusCode;
//				if(pFile->QueryInfoStatusCode(dwStatusCode))
//				{
//					//200-299 Success 
//					if(dwStatusCode >= 200 && dwStatusCode < 300)
//					{
//						bWebOK = TRUE;
//					}
//				}
//			}
//			catch (...)
//			{
//			}
//
//			if(!bWebOK)
//			{
//				pFile->Close();
//				it = vectorServers.erase(it);
//				continue;
//			}
//
//			pFile->Close();
//			++it;
//		}
//
//		//Hide InfoUI
////		checkServerDlg.ShowWindow(SW_HIDE);
//	}

// 	int iValidServerCount = int(vectorServers.size());
// 	if(iValidServerCount != 0)
// 	{
// 		if(iValidServerCount == 1)
// 			iValidServer = 0;
// 		else
// 		{
// 			iValidServer = rand() % iValidServerCount;
// 		}

		CFilePatchDlg dlg;
// 		dlg._strServer		= vectorServers[iValidServer]._strServer;
// 		dlg._strInitRoot	= vectorServers[iValidServer]._strServerInitPath;
// 		TCHAR strTmp[MAX_PATH];
// 		::GetPrivateProfileString(_T("AD"), _T("GotoURL")
// 			, _T("http://aod.sdo.com")
// 			, strTmp, MAX_PATH, strPatchConfigFile
// 			);
// 
// 		UINT adCnt = ::GetPrivateProfileInt(_T("AD"), _T("AdSourceCnt"), 1, strPatchConfigFile );
// 		adCnt = rand() % adCnt + 1;
// 
// 		CString adSrc;
// 		adSrc.Format(_T("AdSource%d"), adCnt);
// 
// 		dlg._strAdURL		= strTmp;
// 		::GetPrivateProfileString(_T("AD"), (LPCTSTR)adSrc
// 			, _T("http://img.dfs.sdg-china.com/m/hu5K92bV7B52XKwl10.JPG")
// 			, strTmp, MAX_PATH, strPatchConfigFile
// 			);
// 		dlg._strAdImg		= strTmp;

		//CString mkDirCmd("regsvr32");
		HINSTANCE hr = ::ShellExecute(0, _T("open"), _T("regsvr32"), _T("dhtmled.ocx /s"), NULL, SW_NORMAL);
		hr = ::ShellExecute(0, _T("open"), _T("regsvr32"), _T("triedit.dll /s"), NULL, SW_NORMAL);
		::Sleep(200);


		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
		}
		else if (nResponse == IDCANCEL)
		{
		}

		if(dlg._bPatchSuccess == TRUE)
		{
			//dlg.PatchOK();
			//::ShellExecute(0, _T("open"), _T("ShowGame.exe"), 0, _T("ClientBin"), SW_NORMAL);
			
			/*if(dlg._bShouldPatchSelf)
				::ShellExecute(0, _T("open"), _T("Lobby.exe"), _T("UpdateFilePatch"), 0, SW_NORMAL);
			else
				::ShellExecute(0, _T("open"), _T("Lobby.exe"), 0, 0, SW_NORMAL);*/
		}
		else
		{
			AfxMessageBox( _T("更新未完成，不能继续游戏！"), MB_OK | MB_ICONHAND );
			return FALSE;
		}
// 	}
// 	else
// 	{
// 		AfxMessageBox( _T("没有可用的更新服务器！"), MB_OK | MB_ICONINFORMATION );
// 		return FALSE;
// 		//::ShellExecute(0, _T("open"), _T("Lobby.exe"), 0, 0, SW_NORMAL);
// 	}

	return FALSE;
}

void DestroyThreadPool(CThreadPool* pool)
{
	pool->Destroy();
	while(pool->GetState() != Destroyed)
	{
		::Sleep(2);
	}

	delete pool;
}


int CFilePatchApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	DestroyThreadPool(g_genMD5ThreadPool);
	DestroyThreadPool(g_compareMD5ThreadPool);
	DestroyThreadPool(g_downloadThreadPool);
	DestroyThreadPool(g_writeFileThreadPool);

	return CWinApp::ExitInstance();
}
