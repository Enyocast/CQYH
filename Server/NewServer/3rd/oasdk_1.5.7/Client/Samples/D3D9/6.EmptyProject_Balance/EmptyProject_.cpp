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
#include "SDOA4Client.h"
#include "SDOADx9.h"


/* Integration-related global variables  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx9*			g_SDOADx9 = NULL;

/* Release IGW */
void CloseIGW()
{
	if (g_SDOADx9)
	{
		g_SDOADx9->Release();
		g_SDOADx9 = NULL;
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
					572,                   // Application ID obtained from the developer website
					L"龙潭虎穴OnLine",     // Application name
					L"0.1.2.0",            // Current application client version
					SDOA_RENDERTYPE_D3D9,  // Client graphics engine type; both D3D9 and D3D8 are supported here
					1,                     // Maximum simultaneous players on one machine (usually 1; for example, KOF uses 2)
					-1,                    // Game area ID; pass -1 when unavailable
					-1                     // Game group ID; pass -1 when unavailable

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// Component initialized successfully

					// Get the component interface
					IUnknown* tmpIUnknown = NULL;
					if (igwGetModule(__uuidof(ISDOADx9), &tmpIUnknown))
					{
						g_SDOADx9 = (LPSDOADx9)tmpIUnknown;
					}
					else // Clean up if obtaining the feature interface fails
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
CDXUTDialog					g_GameAudioSet;          // Simulated volume controls

#define IDC_AUDIOSOUNDLABEL		1
#define IDC_AUDIOEFFECTLABEL	2
#define IDC_AUDIOSOUND			3
#define IDC_AUDIOEFFECT			4

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
	HRESULT hr;
	V_RETURN( g_DialogResourceManager.OnResetDevice() );
	g_GameAudioSet.SetLocation( 10, 10 );
	g_GameAudioSet.SetSize( 180, 180 );


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

	g_GameAudioSet.OnRender( fElapsedTime );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		
		/* Render the IGW interface */
		if (g_SDOADx9)
			g_SDOADx9->RenderEx();

        V( pd3dDevice->EndScene() );
    }
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

	/* Notify IGW of D3D device loss */
	if(g_SDOADx9)
		g_SDOADx9->OnDeviceLost();
}


//--------------------------------------------------------------------------------------
// Release resources created in the OnCreateDevice callback here
//--------------------------------------------------------------------------------------
void CALLBACK OnDestroyDevice( void* pUserContext )
{
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
	{	// Indicate that loading succeeded
		HWND hMainWin = DXUTGetHWND();
		SetWindowTextW(hMainWin, L"EmptyProject [加载IGW组件成功]");
	}		

    // Start the render loop
    DXUTMainLoop();

    // TODO: Perform any application-level cleanup here

	/* Release IGW */
	CloseIGW();

    return DXUTGetExitCode();
}


