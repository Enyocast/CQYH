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

/* Integration-related global variables  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx9*			g_SDOADx9 = NULL;
ISDOAApp*			g_SDOAApp = NULL;
ISDOACfg*			g_SDOACfg = NULL;

int					g_LogicScreenWidth  = 640;
int					g_LogicScreenHeight = 480;


/* Release IGW */
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
	{  // Always call igwTerminal before releasing the DLL
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

/* Load IGW */
void OpenIGW()
{
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileNameW( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{	// Get the EXE directory
		StringCchCopyW( strExeName, MAX_PATH, &strLastSlash[1] );
		*strLastSlash = 0;
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	WCHAR strGameWidgetDll[MAX_PATH] = {0};
	StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\GameWidget.dll", strExePath );

	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}


	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}


	CloseIGW();

	if ( GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF )
	{	// Load the component if found
		g_hInstIGWDll = LoadLibraryW(strGameWidgetDll);
		if (g_hInstIGWDll)
		{
			igwInitialize = (LPigwInitialize)GetProcAddress( g_hInstIGWDll, "igwInitialize" );
			igwGetModule = (LPigwGetModule)GetProcAddress( g_hInstIGWDll, "igwGetModule" );
			igwTerminal = (LPigwTerminal)GetProcAddress( g_hInstIGWDll, "igwTerminal" );
			if ( igwInitialize && igwGetModule && igwTerminal)
			{
				// Loaded successfully

				// All AppInfo fields must be filled in
				AppInfo tmpAppInfo = {
					sizeof(AppInfo),       // Structure size for extensibility
					9999,                  // Application ID obtained from the developer website
					L"龙潭虎穴OnLine",     // Application name
					L"0.1.2.0",            // Current application client version
					SDOA_RENDERTYPE_D3D9,  // Client graphics engine type; both D3D9 and D3D8 are supported here
					1,                     // Maximum simultaneous players on one machine (usually 1; for example, KOF uses 2)
					-1,                    // Game area ID; pass -1 when unavailable
					-1                     // Game group ID; pass -1 when unavailable

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// Component initialized successfully

					igwGetModule(__uuidof(ISDOADx9), (void**)&g_SDOADx9);
					igwGetModule(__uuidof(ISDOAApp), (void**)&g_SDOAApp);
					igwGetModule(__uuidof(ISDOACfg), (void**)&g_SDOACfg);

					if ( (!g_SDOADx9) || (!g_SDOAApp) || (!g_SDOACfg))
						CloseIGW();

				}
				else // Clean up after initialization failure
					CloseIGW();
			}
			else  // Clean up after DLL load failure
				CloseIGW();
		}
	}	
}


CDXUTDialogResourceManager	g_DialogResourceManager; // manager for shared resources of dialogs
CDXUTDialog					g_SkinColorSet;          // Simulated color adjustment controls

#define IDC_SKINCOLORHUELABEL	1
#define IDC_SKINCOLORLIGHTLABEL	2
#define IDC_SKINCOLORSATLABEL	3

#define IDC_SKINCOLORHUE		4
#define IDC_SKINCOLORLIGHT		5
#define IDC_SKINCOLORSAT		6

#define IDC_COLORREDBTN			7
#define IDC_COLORGREENBTN		8
#define IDC_COLORBLUEBTN		9

// Globals needed to draw a box
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
	// Recreate rendering resources
	IDirect3DDevice9* pd3dDevice = DXUTGetD3DDevice();
	if ( !pd3dDevice )
		return false;
	Cleanup();
	// Vertex indices
	unsigned short MyRectTriList[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	// Vertex positions
	float fWidth, fHeight;
	fWidth = g_LogicScreenWidth - 1.0f;
	fHeight = g_LogicScreenHeight - 1.0f;


	// Vertex positions
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
	{	// Initialize the IGW graphics engine
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
	{	// Notify IGW that the D3D device reset succeeded
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
		{	// Draw a simple placeholder box
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
		/* Render the IGW interface */
		if (g_SDOADx9)
			g_SDOADx9->RenderEx();

        V( pd3dDevice->EndScene() );
    }
}

BOOL isSDOLogin = false; // Use BOOL, not bool, to avoid potential problems
LoginResult loginResult;

BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved) 
{ // This callback closes the login dialog if it returns true; otherwise the dialog remains visible
	
	isSDOLogin = (SDOA_ERRORCODE_OK == nErrorCode); 
	if (isSDOLogin) 
	{ 
		loginResult = *pLoginResult; 
		// After login succeeds, pass the selected character information to IGW
		if (g_SDOAApp)
		{
			RoleInfo tmpRoleInfo = { sizeof(RoleInfo), L"美貌仙子", 0 } ;
			g_SDOAApp->SetRoleInfo(&tmpRoleInfo);  // Set character information; call again to notify IGW whenever the user changes character
		}
	} 

	if (SDOA_ERRORCODE_SHOWMESSAGE == nErrorCode)
	{ // Handle login errors
		if (nReserved != 0)
		{
			LoginMessage* pCurLoginMsg = (LoginMessage*)nReserved;
			//LoginMessage* pCurLoginMsg = reinterpret_cast<LoginMessage*>(nReserved);
			if (pCurLoginMsg->dwSize >= sizeof(LoginMessage))
			{ // Compatibility handling
				// Change the error dialog title
				//SysReAllocString(pCurLoginMsg->pbstrTitle, L"[测试游戏错误提示]");

				// Return FALSE to use the default message

				// Return TRUE to use the custom message
				//isSDOLogin = TRUE;
				//::MessageBox(0, *pCurLoginMsg->pbstrContent, *pCurLoginMsg->pbstrTitle, MB_OK);
			}
		}
	}
	return isSDOLogin; // Normal behavior: close the login dialog after successful login
} 

//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, 
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
	if(g_SDOADx9) 
	{	// Pass the message to IGW for processing
		LRESULT lResult; 
		if (g_SDOADx9->OnWindowProc( hWnd, uMsg, wParam, lParam, &lResult ) == SDOA_OK ) 
		{ 
			*pbNoFurtherProcessing = true;// Do not process the message further
			return lResult; 
		} 
	} 



	if ( (UINT)SDOA_WM_CLIENT_RUN == uMsg )
	{
		// Login can begin now
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

	/* Notify IGW of D3D device loss */
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

	/* Release the IGW graphics engine */
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
	{// Color configuration calls take effect only after receiving SDOA_WM_CLIENT_RUN
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
	/* Load IGW */
	OpenIGW();
	if (g_SDOACfg)
	{// Change the theme as early as possible for it to take effect
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
	{	// Indicate that loading succeeded
		HWND hMainWin = DXUTGetHWND();
		SetWindowTextW(hMainWin, L"EmptyProject [加载IGW组件成功]");
	}

	if (g_SDOACfg)
	{ // Set the color adjustment callback
		g_SDOACfg->SetHLSChangeCallback(TestHLSChangeCallback, 0);		
		// Set logical screen dimensions for the QuanQuan interface; -1 for both uses the back buffer size
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
		// Set the screenshot shortcut to Ctrl+Num2
		g_SDOACfg->SetSnapshootScreenHotKey(SDOA_ssCtrl, VK_NUMPAD2);
		// No screenshot shortcut
		//g_SDOACfg->SetSnapshootScreenHotKey(0, 0);

	}

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here
	if (isSDOLogin && g_SDOAApp)
	{ // Log out on exit after a successful login
		g_SDOAApp->Logout();
	}

	/* Release IGW */
	CloseIGW();

    return DXUTGetExitCode();
}


