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
#include "SDOA4Client.h"
#include "SDOADx9.h"
#include "SDOACfg.h"

/* 接入相关全局变量  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx9*			g_SDOADx9 = NULL;
ISDOAApp*			g_SDOAApp = NULL;
ISDOACfg*			g_SDOACfg = NULL;

int					g_LogicScreenWidth  = 640;
int					g_LogicScreenHeight = 480;


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

	if (g_SDOACfg)
	{
		g_SDOACfg->Release();
		g_SDOACfg = NULL;
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
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
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

					igwGetModule(__uuidof(ISDOADx9), (void**)&g_SDOADx9);
					igwGetModule(__uuidof(ISDOAApp), (void**)&g_SDOAApp);
					igwGetModule(__uuidof(ISDOACfg), (void**)&g_SDOACfg);

					if ( (!g_SDOADx9) || (!g_SDOAApp) || (!g_SDOACfg))
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
CDXUTDialog					g_SkinColorSet;          // 模拟调色控制

#define IDC_SKINCOLORHUELABEL	1
#define IDC_SKINCOLORLIGHTLABEL	2
#define IDC_SKINCOLORSATLABEL	3

#define IDC_SKINCOLORHUE		4
#define IDC_SKINCOLORLIGHT		5
#define IDC_SKINCOLORSAT		6

#define IDC_COLORREDBTN			7
#define IDC_COLORGREENBTN		8
#define IDC_COLORBLUEBTN		9

// 画个框框需要的全局变量
LPDIRECT3DVERTEXBUFFER9 g_pVB			= NULL; 
LPDIRECT3DINDEXBUFFER9	g_pIndexVB		= NULL;
struct CUSTOMVERTEX
{
	FLOAT		x, y, z, rhw;
	D3DCOLOR    color;    
	FLOAT       tu, tv;   
};

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


VOID Cleanup()
{
	if( g_pVB != NULL )
	{
		g_pVB->Release();
		g_pVB = NULL;
	}

	if ( g_pIndexVB != NULL )
	{
		g_pIndexVB->Release();
		g_pIndexVB = NULL;
	}
}

bool CreateRenderRes()
{
	// 重建绘制资源
	IDirect3DDevice9* pd3dDevice = DXUTGetD3DDevice();
	if ( !pd3dDevice )
		return false;
	Cleanup();
	// 顶点索引
	unsigned short MyRectTriList[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	// 顶点位置
	float fWidth, fHeight;
	fWidth = g_LogicScreenWidth - 1.0f;
	fHeight = g_LogicScreenHeight - 1.0f;


	// 顶点位置
	CUSTOMVERTEX MyRectVertex[4] = 
	{
		{ 0.0f,		0.0f,	0.0f, 1.0f, 0xffff0000, 0.0f, 0.0f }, // x, y, z, rhw, color, u, v
		{ fWidth,	0.0f,	0.0f, 1.0f, 0xffff0000, 1.0f, 0.0f },
		{ 0.0f,		fHeight, 0.0f, 1.0f, 0xffff0000, 0.0f, 1.0f },
		{ fWidth,	fHeight,	0.0f, 1.0f, 0xffff0000, 1.0f, 1.0f }
	};

	if( FAILED( pd3dDevice->CreateIndexBuffer(sizeof(MyRectTriList), 
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIndexVB, NULL)))
	{
		return false;
	}

	if( FAILED( pd3dDevice->CreateVertexBuffer(sizeof(MyRectVertex),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
	{
		return false;
	}

	VOID* pVertices;
	if( FAILED( g_pVB->Lock( 0, sizeof(MyRectVertex), (void**)&pVertices, 0 ) ) )
		return false;
	memcpy( pVertices, MyRectVertex, sizeof(MyRectVertex) );
	g_pVB->Unlock();

	VOID* pIndexVertices;
	if( FAILED( g_pIndexVB->Lock( 0, sizeof(MyRectTriList), (void**)&pIndexVertices, 0 ) ) )
		return false;
	memcpy( pIndexVertices, MyRectTriList, sizeof(MyRectTriList) );
	g_pIndexVB->Unlock();

	return true;
}

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
	if ( ! CreateRenderRes() )
	{
		return E_FAIL;
	}
	
	HRESULT hr;
	V_RETURN( g_DialogResourceManager.OnResetDevice() );
	g_SkinColorSet.SetLocation( 10, 10 );
	g_SkinColorSet.SetSize( 180, 180 );
	
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
	// Render the scene
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
		if (g_pVB)
		{	// 简单的画个框框，意思意思就行了
			pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
			pd3dDevice->SetIndices(g_pIndexVB);
			pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );			
			pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		}
		V( pd3dDevice->EndScene() );
	}
	g_SkinColorSet.OnRender( fElapsedTime );
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
			//LoginMessage* pCurLoginMsg = reinterpret_cast<LoginMessage*>(nReserved);
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
		}
	}
	
	// Always allow dialog resource manager calls to handle global messages
	// so GUI state is updated correctly
	*pbNoFurtherProcessing = g_DialogResourceManager.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing )
		return 0;

	*pbNoFurtherProcessing = g_SkinColorSet.MsgProc( hWnd, uMsg, wParam, lParam );
	if( *pbNoFurtherProcessing )
		return 0;

    return 0;
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnResetDevice callback here 
//--------------------------------------------------------------------------------------
void CALLBACK OnLostDevice( void* pUserContext )
{
	Cleanup();
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
	Cleanup();
	g_DialogResourceManager.OnDestroyDevice();

	/* 释放IGW图形引擎 */
	if (g_SDOADx9)
		g_SDOADx9->Finalize();
}
//--------------------------------------------------------------------------------------
// Handles the GUI events
//--------------------------------------------------------------------------------------
void CALLBACK OnGUIEvent( UINT nEvent, int nControlID, CDXUTControl* pControl, void* pUserContext )
{
	switch( nControlID )
	{
	case IDC_SKINCOLORHUE:
		int g_dwHue;
		g_dwHue = ((CDXUTSlider*)pControl)->GetValue();
		if (g_SDOACfg)
		{
			g_SDOACfg->SetHue(g_dwHue);
		}
		WCHAR wszSkinColorHueBuf[256];
		StringCchPrintf( wszSkinColorHueBuf, 256, L"色调： %d", g_dwHue );
		g_SkinColorSet.GetStatic( IDC_SKINCOLORHUELABEL )->SetText( wszSkinColorHueBuf );
		
		break;
	case IDC_SKINCOLORLIGHT:
		int g_dwLight;
		g_dwLight = ((CDXUTSlider*)pControl)->GetValue();
		if (g_SDOACfg)
		{
			g_SDOACfg->SetLightness(g_dwLight);
		}
		WCHAR wszSkinColorLightBuf[256];
		StringCchPrintf( wszSkinColorLightBuf, 256, L"亮度： %d", g_dwLight );
		g_SkinColorSet.GetStatic( IDC_SKINCOLORLIGHTLABEL )->SetText( wszSkinColorLightBuf );
		break;
	case IDC_SKINCOLORSAT:
		int g_dwSat;
		g_dwSat = ((CDXUTSlider*)pControl)->GetValue();
		if (g_SDOACfg)
		{
			g_SDOACfg->SetSaturation(g_dwSat);
		}
		WCHAR wszSkinColorSatBuf[256];
		StringCchPrintf( wszSkinColorSatBuf, 256, L"饱合度： %d", g_dwSat );
		g_SkinColorSet.GetStatic( IDC_SKINCOLORLIGHTLABEL )->SetText( wszSkinColorSatBuf );
		break;
	case IDC_COLORREDBTN:
		if (g_SDOACfg)
		{
			g_SDOACfg->SetSkinColor( 0xFFFF0000 );
		}
		break;
	case IDC_COLORGREENBTN:
		if (g_SDOACfg)
		{
			g_SDOACfg->SetSkinColor( 0xFF00FF00 );
		}
		break;
	case IDC_COLORBLUEBTN:
		if (g_SDOACfg)
		{
			g_SDOACfg->SetSkinColor( 0xFF0000FF );
		}
		break;
	}
}

//--------------------------------------------------------------------------------------
// Initialize the app 
//--------------------------------------------------------------------------------------
void InitApp()
{
	g_SkinColorSet.Init( &g_DialogResourceManager );

	g_SkinColorSet.SetCallback( OnGUIEvent );
	int iY = 10;
	g_SkinColorSet.AddStatic( IDC_SKINCOLORHUELABEL, L"色调:0", 35, iY += 20, 125, 22);
	g_SkinColorSet.AddSlider( IDC_SKINCOLORHUE, 10, iY += 20, 150, 10, -180, 180, 0);
	g_SkinColorSet.AddStatic( IDC_SKINCOLORLIGHTLABEL, L"亮度:0", 35, iY += 20, 125, 22);
	g_SkinColorSet.AddSlider( IDC_SKINCOLORLIGHT, 10, iY += 20, 150, 10, -66, 66, 0);
	g_SkinColorSet.AddStatic( IDC_SKINCOLORSATLABEL, L"饱合度:0", 35, iY += 20, 125, 22);
	g_SkinColorSet.AddSlider( IDC_SKINCOLORSAT, 10, iY += 20, 150, 10, -180, 180, 0);

	g_SkinColorSet.AddButton( IDC_COLORREDBTN, L"红色", 10, iY +=15, 180, 15, 0);
	g_SkinColorSet.AddButton( IDC_COLORGREENBTN, L"绿色", 10, iY +=15,180, 15, 0);
	g_SkinColorSet.AddButton( IDC_COLORBLUEBTN, L"蓝色", 10, iY +=15, 180, 15, 0);
}

void CALLBACK TestHLSChangeCallback(const int nHue, const int nLightness, const int nSaturation, const int nUserData)
{
	if (g_SDOACfg)
	{// 注意配置调色功能的接口必须在收到SDOA_WM_CLIENT_RUN消息之后调用才有效
		int nTmpHue, nTmpLight, nTmpSat;
		CDXUTSlider* pTmpSlider = NULL;
		WCHAR wszSkinColorBuf[256];

		pTmpSlider = g_SkinColorSet.GetSlider(IDC_SKINCOLORHUE);
		if (pTmpSlider)
		{
			pTmpSlider->SetValue( nHue );
			nTmpHue = pTmpSlider->GetValue();
			StringCchPrintf( wszSkinColorBuf, 256, L"色调： %d", nTmpHue );
			g_SkinColorSet.GetStatic( IDC_SKINCOLORHUELABEL )->SetText( wszSkinColorBuf );
		}
		pTmpSlider = g_SkinColorSet.GetSlider(IDC_SKINCOLORLIGHT);
		if (pTmpSlider)
		{
			pTmpSlider->SetValue( nLightness );
			nTmpLight = pTmpSlider->GetValue();
			StringCchPrintf( wszSkinColorBuf, 256, L"亮度： %d", nTmpLight );
			g_SkinColorSet.GetStatic( IDC_SKINCOLORLIGHTLABEL )->SetText( wszSkinColorBuf );
		}
		pTmpSlider = g_SkinColorSet.GetSlider(IDC_SKINCOLORSAT);
		if (pTmpSlider)
		{
			pTmpSlider->SetValue( nSaturation );
			nTmpSat = pTmpSlider->GetValue();
			StringCchPrintf( wszSkinColorBuf, 256, L"饱合度： %d", nTmpSat );
			g_SkinColorSet.GetStatic( IDC_SKINCOLORSATLABEL )->SetText( wszSkinColorBuf );
		}
	}
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
	if (g_SDOACfg)
	{// 变更主题必须要最早调用才有效
		BSTR bstrThemeName = SysAllocString(L"");
		if (g_SDOACfg->SetThemeName(bstrThemeName))
		{
			OutputDebugString(L"\nSDOACfg->SetThemeName OK!\n");
		}
		else
		{
			OutputDebugString(L"\nSDOACfg->SetThemeName ERROR!\n");
		}
		SysFreeString(bstrThemeName);		
	}

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
    DXUTCreateDevice( D3DADAPTER_DEFAULT, true, 800, 600, IsDeviceAcceptable, ModifyDeviceSettings );

	if (igwInitialize)
	{	// 说明加载成功，表示下......
		HWND hMainWin = DXUTGetHWND();
		SetWindowTextW(hMainWin, L"EmptyProject [加载IGW组件成功]");
	}

	if (g_SDOACfg)
	{ // 设置调色变化回调
		g_SDOACfg->SetHLSChangeCallback(TestHLSChangeCallback, 0);		
		// 设置圈圈主要界面响应的逻辑屏幕宽、高（都设置为-1时则使用的是背景缓冲大小）
		g_SDOACfg->SetLogicScreen(g_LogicScreenWidth, g_LogicScreenHeight);
		RECT tmpRect;
		g_SDOACfg->GetUseBackBufferRect(&tmpRect);
		tmpRect.bottom = 100;
		tmpRect.top = 90;
		tmpRect.left = 80;
		tmpRect.left = 10;
		g_SDOACfg->SetUseBackBufferRect(tmpRect);
		int iFunKey, iNormalKey;
		g_SDOACfg->GetSnapshootScreenHotKey( &iFunKey, &iNormalKey );
		WCHAR strMyOutput[100] = {0};
		StringCchPrintfW( strMyOutput, 100, L"\nGetSnapshootScreenHotKey iFunKey=%d, iNormalKey=%d)\n", iFunKey, iNormalKey);
		OutputDebugStringW(strMyOutput);
		// 设置截图快捷键为Ctrl+Num2
		g_SDOACfg->SetSnapshootScreenHotKey(SDOA_ssCtrl, VK_NUMPAD2);
		// 无截图快捷键
		//g_SDOACfg->SetSnapshootScreenHotKey(0, 0);

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


