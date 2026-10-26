//--------------------------------------------------------------------------------------
// File: EmptyProject.cpp
//
// Empty starting point for new Direct3D applications
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#include "dxstdafx.h"
#include "resource.h"
#include "DXUTgui.h"
#include "Oleauto.h"
#include "comutil.h"
#include <time.h>
//#pragma comment(lib, "comsupp.lib")

#include "SDOA4Client.h"
#include "SDOADx9.h"

/* 接入相关全局变量  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx9*			g_SDOADx9 = NULL;
ISDOAApp*			g_SDOAApp = NULL;
ISDOAAppUtils*		g_SDOAAppUtils = NULL;
ISDOAClientService* g_SDOAClientService = NULL;

/* 释放IGW */
void CloseIGW()
{
	if (g_SDOADx9)
	{
		g_SDOADx9->Release();
		g_SDOADx9 = NULL;
	}

	if (g_SDOAApp)
	{
		g_SDOAApp->Release();
		g_SDOAApp = NULL;
	}

	if (g_SDOAAppUtils)
	{
		g_SDOAAppUtils->Release();
		g_SDOAAppUtils = NULL;
	}

	if (g_SDOAClientService)
	{
		g_SDOAClientService->Release();
		g_SDOAClientService = NULL;
	}

	if (igwTerminal)
	{  // 释放DLL前总是先调用igwTerminal
		igwTerminal();
		igwTerminal = NULL;
	}
	if (g_hInstIGWDll)
	{
		FreeLibrary(g_hInstIGWDll);
		g_hInstIGWDll = 0;
	}
	igwInitialize = NULL;
}

/* 加载IGW */
void OpenIGW()
{
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileNameW( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{	// 得到EXE所在路径
		StringCchCopyW( strExeName, MAX_PATH, &strLastSlash[1] );
		*strLastSlash = 0;
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	WCHAR strGameWidgetDll[MAX_PATH] = {0};
	StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\GameWidget.dll", strExePath );

	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}

	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"E:\\Worke\\Ez\\IGP\\demo&prototype\\allsnap\\bin\\GameWidget.dll" );
	}


	CloseIGW();

	if ( GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF )
	{	// 找到组件则加载	
		g_hInstIGWDll = LoadLibraryW(strGameWidgetDll);
		if (g_hInstIGWDll)
		{
			igwInitialize = (LPigwInitialize)GetProcAddress( g_hInstIGWDll, "igwInitialize" );
			igwGetModule = (LPigwGetModule)GetProcAddress( g_hInstIGWDll, "igwGetModule" );
			igwTerminal = (LPigwTerminal)GetProcAddress( g_hInstIGWDll, "igwTerminal" );
			if ( igwInitialize && igwGetModule && igwTerminal)
			{
				// 加载成功

				// 注意AppInfo类型所有字段必须填
				AppInfo tmpAppInfo = {
					sizeof(AppInfo),       // 结构体大小，方便扩展
					9999,                  // 接入应用ID，从开发者网站中申请
					L"龙潭虎穴OnLine",     // 应用名称
					L"0.1.2.0",            // 应用客户端当前版本号
					SDOA_RENDERTYPE_D3D9,  // 客户端支持的图形引擎类型，这里同时支持d3d9和d3d8
					1,                     // 可同时在一台机器上游戏的最大人数（通常为1，例如:KOF应该是2）
					-1,                    // 游戏区ID，不可用时传入-1
					-1                     // 游戏组ID，不可用时传入-1

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// 初始化组件成功

					// 获取组件接口					
					igwGetModule(__uuidof(ISDOADx9), (void**)&g_SDOADx9);
					igwGetModule(__uuidof(ISDOAApp), (void**)&g_SDOAApp);
					igwGetModule(__uuidof(ISDOAAppUtils), (void**)&g_SDOAAppUtils);
					igwGetModule(__uuidof(ISDOAClientService), (void**)&g_SDOAClientService);					

					if ( (!g_SDOADx9) || (!g_SDOAApp) || (!g_SDOAAppUtils) || (!g_SDOAClientService))
						CloseIGW();

				}
				else // 初始化失败清除环境
					CloseIGW();
			}
			else  // 加载DLL失败清除环境
				CloseIGW();
		}
	}
	
	
}


CDXUTDialogResourceManager	g_DialogResourceManager; // manager for shared resources of dialogs
CDXUTDialog					g_GameAudioSet;          // 模拟音量控制

#define IDC_AUDIOSOUNDLABEL		1
#define IDC_AUDIOEFFECTLABEL	2
#define IDC_AUDIOSOUND			3
#define IDC_AUDIOEFFECT			4
#define IDC_BALANCE				5
#define IDC_BALANCELABEL		6

//--------------------------------------------------------------------------------------
// Rejects any devices that aren't acceptable by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsDeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, 
                                  D3DFORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
    // Typically want to skip backbuffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3DObject(); 
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                    AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING, 
                    D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}


//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, const D3DCAPS9* pCaps, void* pUserContext )
{
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_MANAGED resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnCreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;
	V_RETURN( g_DialogResourceManager.OnCreateDevice( pd3dDevice ) );
	if (g_SDOADx9)
	{	// 初始化IGW内部图形引擎
		D3DPRESENT_PARAMETERS d3dpp = DXUTGetPresentParameters ();
		g_SDOADx9->Initialize( pd3dDevice, &d3dpp, FALSE );
	}
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3DPOOL_DEFAULT resources here 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnResetDevice( IDirect3DDevice9* pd3dDevice, 
                                const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
	HRESULT hr;
	V_RETURN( g_DialogResourceManager.OnResetDevice() );
	g_GameAudioSet.SetLocation( 10, 10 );
	g_GameAudioSet.SetSize( 180, 180 );
	
	if(g_SDOADx9)
	{	// 通知IGW d3d设备重置成功
		D3DPRESENT_PARAMETERS d3dpp = DXUTGetPresentParameters () ;	
		g_SDOADx9->OnDeviceReset ( &d3dpp ) ;
	}

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
}


//--------------------------------------------------------------------------------------
// Render the scene 
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 45, 50, 170), 1.0f, 0) );

	g_GameAudioSet.OnRender( fElapsedTime );
    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		/* 绘制IGW界面 */
		if (g_SDOADx9)
			g_SDOADx9->RenderEx();

        V( pd3dDevice->EndScene() );
    }
}

BOOL isSDOLogin = false; // 注意一定要是BOOL类型，不能为bool否则可能会导致问题
LoginResult loginResult;

BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved) 
{ // 注意该回调返回true则关闭登录对话框，否则登录对话框仍然显示
	
	isSDOLogin = (SDOA_ERRORCODE_OK == nErrorCode); 
	if (isSDOLogin) 
	{ 
		loginResult = *pLoginResult;
		// 登录成功后,把用户使用的游戏角色信息传入IGW
		if (g_SDOAApp)
		{
			RoleInfo tmpRoleInfo = { sizeof(RoleInfo), L"美貌仙子", 0 } ;
			g_SDOAApp->SetRoleInfo(&tmpRoleInfo);  // 设置角色信息，可多次调用，只要用户切换了角色就调用通知IGW
		}
	} 

	if (SDOA_ERRORCODE_SHOWMESSAGE == nErrorCode)
	{ // 登录错误消息处理
		if (nReserved != 0)
		{
			LoginMessage* pCurLoginMsg = (LoginMessage*)nReserved;
			if (pCurLoginMsg->dwSize >= sizeof(LoginMessage))
			{ // 兼容性处理 
				// 修改错误提示对话框标题
				//SysReAllocString(pCurLoginMsg->pbstrTitle, L"[测试游戏错误提示]");

				// 此时返回FALSE则使用默认提示

				// 此时返回TRUE则使用自定义的提示
				//isSDOLogin = TRUE;
				//::MessageBox(0, *pCurLoginMsg->pbstrContent, *pCurLoginMsg->pbstrTitle, MB_OK);
			}
		}
	}
	return isSDOLogin; // 常规逻辑，登录成功则关闭登录对话框
} 

//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	if(g_SDOADx9) 
	{	// 把消息交给IGW模块处理 
		LRESULT lResult; 
		if (g_SDOADx9->OnWindowProc( hWnd, uMsg, wParam, lParam, &lResult ) == SDOA_OK ) 
		{ 
			*pbNoFurtherProcessing = true;// 不让自身再处理消息 
			return lResult; 
		} 
	} 



	if ( (UINT)SDOA_WM_CLIENT_RUN == uMsg )
	{
		// 此刻可以开始登录
		if (g_SDOAApp)
		{
			g_SDOAApp->ShowLoginDialog(OnLogin, 0, 0);
			SDOAWinProperty tmpWinPro;
			tmpWinPro.nLeft = 10;
			tmpWinPro.nTop = 10;
			if ( g_SDOAApp->GetWinProperty(L"igwUserLoginDialog", &tmpWinPro) == SDOA_OK)
			{
				if ( g_SDOAApp->SetWinProperty(L"igwUserLoginDialog", &tmpWinPro) == SDOA_OK)
				{
					tmpWinPro.nTop = 10;
				}
				else
				{
					tmpWinPro.nTop = 20;
				}

			}

			
		}
	}
	
	// Always allow dialog resource manager calls to handle global messages
	// so GUI state is updated correctly
	*pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing )
		return 0;

	*pbNoFurtherProcessing = g_GameAudioSet.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing )
		return 0;

    return 0;
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
	g_DialogResourceManager.OnLostDevice();

	/* 通知IGW d3d设备丢失 */
	if(g_SDOADx9)
		g_SDOADx9->OnDeviceLost();
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
	g_DialogResourceManager.OnDestroyDevice();

	/* 释放IGW图形引擎 */
	if (g_SDOADx9)
		g_SDOADx9->Finalize();
}

void CALLBACK QueryCallback(int nRetCode, int nUserData)
{ // 异步查询的回调
	if (g_SDOAClientService)
	{
		if (nRetCode != SDOA_OK)
		{
			g_GameAudioSet.GetStatic( IDC_BALANCELABEL )->SetText( L"查询失败" );
			BSTR bstrRetKey = SysAllocString(L"descMsg");
			BSTR bstrRetValue = NULL;
			g_SDOAClientService->GetValue(bstrRetKey, &bstrRetValue);
			_bstr_t strRet = bstrRetValue;
			LPCWSTR szRet = strRet;

			WCHAR strErrotTitle[100] = {0};
			StringCchPrintfW( strErrotTitle, 100, L"错误信息(%d)", nRetCode);

			::MessageBox(0, szRet, strErrotTitle, MB_OK);	 
			SysFreeString(bstrRetKey);
			SysFreeString(bstrRetValue);
		}
		else
		{
			BSTR bstrKey = SysAllocString(L"BalanceInfo");
			BSTR bstrValue = NULL;
			g_SDOAClientService->GetValue(bstrKey, &bstrValue);
			_bstr_t b = bstrValue;
			LPCWSTR t = b;
			g_GameAudioSet.GetStatic( IDC_BALANCELABEL )->SetText( t );
			SysFreeString(bstrKey);
			SysFreeString(bstrValue);			
		}
	}
}

//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
	{
	case IDC_AUDIOSOUND:
		int g_dwNumSound;
		g_dwNumSound = ((CDXUTSlider*)pControl)->GetValue();
		WCHAR wszAudioSoundBuf[256];
		StringCchPrintf( wszAudioSoundBuf, 256, L"音乐音量： %u", g_dwNumSound );
		g_GameAudioSet.GetStatic( IDC_AUDIOSOUNDLABEL )->SetText( wszAudioSoundBuf );
		if (g_SDOAAppUtils)
		{
			g_SDOAAppUtils->NodifyAudioChanged();
		}

		break;
	case IDC_AUDIOEFFECT:
		int g_dwNumEffect;
		g_dwNumEffect = ((CDXUTSlider*)pControl)->GetValue();
		WCHAR wszAudioEffectBuf[256];
		StringCchPrintf( wszAudioEffectBuf, 256, L"音效音量： %u", g_dwNumEffect );
		g_GameAudioSet.GetStatic( IDC_AUDIOEFFECTLABEL )->SetText( wszAudioEffectBuf );
		if (g_SDOAAppUtils)
		{
			g_SDOAAppUtils->NodifyAudioChanged();
		}

		break;
	case IDC_BALANCE:
		// 必须接口存在且登录成功后才可调用该接口，例如：查询余额
		if (isSDOLogin)
		{
			if (g_SDOAClientService)
			{
				// 调用前设置参数

				// 订单编号 (请根据实际单号填写，这里仅是样例代码)
				BSTR bstrOrderIdName = SysAllocString(L"orderId");
				BSTR bstrOrderIdValue = SysAllocString(L"01234567890123456789012345678912");
				if (g_SDOAClientService->SetValue(bstrOrderIdName, bstrOrderIdValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue orderId Error! \n");
				}
				SysFreeString(bstrOrderIdValue);
				SysFreeString(bstrOrderIdName);

				// 商户编码 (根据实际情况填写)
				BSTR bstrSpIdName = SysAllocString(L"spId");
				BSTR bstrSpIdValue = SysAllocString(L"10075");
				if (g_SDOAClientService->SetValue(bstrSpIdName, bstrSpIdValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue spId Error! \n");
				}
				SysFreeString(bstrSpIdName);
				SysFreeString(bstrSpIdValue);


				// 货币类型
				BSTR bstrPayTypeName = SysAllocString(L"payType");
				BSTR bstrPayTypeValue = SysAllocString(L"1");
				if (g_SDOAClientService->SetValue(bstrPayTypeName, bstrPayTypeValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue payType Error! \n");
				}
				SysFreeString(bstrPayTypeName);
				SysFreeString(bstrPayTypeValue);
				// 命令类型
				BSTR bstrCmdTypeName = SysAllocString(L"cmdType");
				BSTR bstrCmdTypeValue = SysAllocString(L"1");
				if (g_SDOAClientService->SetValue(bstrCmdTypeName, bstrCmdTypeValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue cmdType Error! \n");
				}
				SysFreeString(bstrCmdTypeName);
				SysFreeString(bstrCmdTypeValue);
				// 调用时间
				BSTR bstrCallTimeName = SysAllocString(L"callTime");
				WCHAR strTime[50] = {0};
				SYSTEMTIME sys;
				GetLocalTime( &sys );
				StringCchPrintfW( strTime, 50, L"%.4d-%.2d-%.2d %.2d:%.2d:%.2d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond );
				//OutputDebugStr(strTime);
				BSTR bstrCallTimeValue = SysAllocString(strTime);
				if (g_SDOAClientService->SetValue(bstrCallTimeName, bstrCallTimeValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue callTime Error! \n");
				}
				SysFreeString(bstrCallTimeName);
				SysFreeString(bstrCallTimeValue);
				// 附加指令
				BSTR bstrIndicationName = SysAllocString(L"indication");
				BSTR bstrIndicationValue = SysAllocString(L"");
				if (g_SDOAClientService->SetValue(bstrIndicationName, bstrIndicationValue) == SDOA_FALSE)
				{
					OutputDebugStr(L"SetValue indication Error! \n");
				}
				SysFreeString(bstrIndicationName);
				SysFreeString(bstrIndicationValue);


				BSTR bstrServiceName = SysAllocString(L"UserBalance");
				if ( g_SDOAClientService->AsyncQuery(bstrServiceName, QueryCallback, 0) == SDOA_OK )
					g_GameAudioSet.GetStatic( IDC_BALANCELABEL )->SetText( L"开始查询" );
				else
					g_GameAudioSet.GetStatic( IDC_BALANCELABEL )->SetText( L"查询失败" );
				SysFreeString(bstrServiceName);

			}
		}
		else
		{
			g_GameAudioSet.GetStatic( IDC_BALANCELABEL )->SetText( L"登录成功后才可用！" );
		}
		break;

	}
}

//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
	g_GameAudioSet.Init( &g_DialogResourceManager );

	g_GameAudioSet.SetCallback( OnGUIEvent );
	int iY = 10;
	g_GameAudioSet.AddStatic( IDC_AUDIOSOUNDLABEL, L"音乐音量:0", 35, iY += 20, 125, 22);
	g_GameAudioSet.AddSlider( IDC_AUDIOSOUND, 10, iY += 20, 150, 10, 0, 100, 0);
	g_GameAudioSet.AddStatic( IDC_AUDIOEFFECTLABEL, L"音效音量:0", 35, iY += 20, 125, 22);
	g_GameAudioSet.AddSlider( IDC_AUDIOEFFECT, 10, iY += 20, 150, 10, 10, 100, 0);

	g_GameAudioSet.AddButton( IDC_BALANCE, L"查询余额", 10, iY += 20, 80, 26);
	g_GameAudioSet.AddStatic( IDC_BALANCELABEL, L"", 95, iY, 120, 22);
	
}

void WINAPI TestSetAudioSoundVolume(DWORD NewVolume)
{ // 测试设置音乐音量，仅模拟个数值变化
	DWORD tmpValue;
	if (NewVolume >= 100)
	{
		tmpValue = 100;
	}
	else
	{
		tmpValue = NewVolume;
	}
	WCHAR wszAudioSoundBuf[256];
	StringCchPrintf( wszAudioSoundBuf, 256, L"音乐音量： %u", tmpValue );

	g_GameAudioSet.GetStatic( IDC_AUDIOSOUNDLABEL )->SetText( wszAudioSoundBuf );
	g_GameAudioSet.GetSlider( IDC_AUDIOSOUND )->SetValue(tmpValue);

}

DWORD WINAPI TestGetAudioSoundVolume()
{
	return g_GameAudioSet.GetSlider( IDC_AUDIOSOUND )->GetValue();
}

void WINAPI TestSetAudioEffectVolume(DWORD NewVolume)
{ // 测试设置音效音量，仅模拟个数值变化
	DWORD tmpValue;
	if (NewVolume >= 100)
	{
		tmpValue = 100;
	}
	else
	{
		tmpValue = NewVolume;
	}
	WCHAR wszAudioEffectBuf[256];
	StringCchPrintf( wszAudioEffectBuf, 256, L"音效音量： %u", tmpValue );

	g_GameAudioSet.GetStatic( IDC_AUDIOEFFECTLABEL )->SetText( wszAudioEffectBuf );
	g_GameAudioSet.GetSlider( IDC_AUDIOEFFECT )->SetValue(tmpValue);
}

DWORD WINAPI TestGetAudioEffectVolume()
{
	return g_GameAudioSet.GetSlider( IDC_AUDIOEFFECT )->GetValue();
}



//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	/* 加载IGW */
	OpenIGW();

    // Set the callback functions
    DXUTSetCallbackDeviceCreated( OnCreateDevice );
    DXUTSetCallbackDeviceReset( OnResetDevice );
    DXUTSetCallbackDeviceLost( OnLostDevice );
    DXUTSetCallbackDeviceDestroyed( OnDestroyDevice );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameRender( OnFrameRender );
    DXUTSetCallbackFrameMove( OnFrameMove );
   
    // TODO: Perform any application-level initialization here
	InitApp();

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true, true ); // Parse the command line, handle the default hotkeys, and show msgboxes
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"EmptyProject" );
    DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 640, 480, IsDeviceAcceptable, ModifyDeviceSettings );

	if (igwInitialize)
	{	// 说明加载成功，表示下......
		HWND hMainWin = DXUTGetHWND();
		SetWindowTextW(hMainWin, L"EmptyProject [加载IGW组件成功]");
	}		

	if (g_SDOAAppUtils)
	{  // 设置音量控制回调函数
		g_SDOAAppUtils->SetAudioSetting(TestGetAudioSoundVolume, TestSetAudioSoundVolume, TestGetAudioEffectVolume, TestSetAudioEffectVolume);
	}

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here
	if (isSDOLogin && g_SDOAApp)
	{ // 登录成功，退出时要登出
		g_SDOAApp->Logout();
	}

	/* 释放IGW */
	CloseIGW();

    return DXUTGetExitCode();
}


