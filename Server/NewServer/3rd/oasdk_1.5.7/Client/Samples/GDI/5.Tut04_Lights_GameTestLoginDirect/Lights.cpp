//-----------------------------------------------------------------------------
// File: Lights.cpp
//
// Desc: Rendering 3D geometry is much more interesting when dynamic lighting
//       is added to the scene. To use lighting in D3D, you must create one or
//       lights, setup a material, and make sure your geometry contains surface
//       normals. Lights may have a position, a color, and be of a certain type
//       such as directional (light comes from one direction), point (light
//       comes from a specific x,y,z coordinate and radiates in all directions)
//       or spotlight. Materials describe the surface of your geometry,
//       specifically, how it gets lit (diffuse color, ambient color, etc.).
//       Surface normals are part of a vertex, and are needed for the D3D's
//       internal lighting calculations.
//
// Copyright (c) 2000-2001 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
// If app hasn't choosen, set to work with Windows 98, Windows Me, Windows 2000, Windows XP and beyond

#include <Windows.h>
#include <d3dx8.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>        // For StringCch
#include "SDOA4Client.h"
#include "SDOADx8.h"


/* Integration-related global variables  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx8*			g_SDOADx8 = NULL;
ISDOAApp2*			g_SDOAApp = NULL;

char				g_szSessionID[128];
char				g_szAdditional[128];
bool				g_hasLoginParam = false;


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D8             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE8       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER8 g_pVB        = NULL; // Buffer to hold vertices
D3DPRESENT_PARAMETERS	d3dpp;
bool					g_DeviceLost = false;

// A structure for our custom vertex type. We added a normal, and omitted the
// color (which is provided by the material)
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The 3D position for the vertex
    D3DXVECTOR3 normal;   // The surface normal for the vertex
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)

/* Release IGW */
void CloseIGW()
{
	if (g_SDOADx8)
	{
		g_SDOADx8->Release();
		g_SDOADx8 = NULL;
	}

	if (g_SDOAApp)
	{
		g_SDOAApp->Release();
		g_SDOAApp = NULL;
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
					SDOA_RENDERTYPE_D3D8,  // Graphics engine type supported by the client
					1,                     // Maximum simultaneous players on one machine (usually 1; for example, KOF uses 2)
					-1,                    // Game area ID; pass -1 when unavailable
					-1                     // Game group ID; pass -1 when unavailable

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// Component initialized successfully

					// Get the component interface
					igwGetModule(__uuidof(ISDOADx8), (void**)&g_SDOADx8);
					igwGetModule(__uuidof(ISDOAApp2), (void**)&g_SDOAApp);
					if ( (!g_SDOADx8) || (!g_SDOAApp))
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

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate8( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Get the current desktop display mode, so we can set up a back
    // buffer of the same format
    D3DDISPLAYMODE d3ddm;
    if( FAILED( g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.hDeviceWindow = hWnd;// IGW always uses this to obtain the game main window

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn off culling
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
    // Create the vertex buffer.
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer. We are algorithmically generating a cylinder
    // here, including the normals, which are used for lighting.
    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (BYTE**)&pVertices, 0 ) ) )
        return E_FAIL;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(50-1);
        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
        pVertices[2*i+0].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
        pVertices[2*i+1].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
    }
    g_pVB->Unlock();

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    if( g_pVB != NULL )
        g_pVB->Release();
	
    if( g_pd3dDevice != NULL )
	{
      int k;
	  char szTmp[128];

	  k =  g_pd3dDevice->Release();
	  _snprintf(szTmp, sizeof(szTmp), "\ng_pd3dDevice->Release()  %d\n", k);
	  OutputDebugString(szTmp);
	  int b;
	  b = k;

	}

    if( g_pD3D != NULL )
        g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // For our world matrix, we will just leave it as the identity
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity( &matWorld );
    D3DXMatrixRotationX( &matWorld, timeGetTime()/500.0f );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 3.0f,-5.0f ),
                                  &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                                  &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}




//-----------------------------------------------------------------------------
// Name: SetupLights()
// Desc: Sets up the lights and materials for the scene.
//-----------------------------------------------------------------------------
VOID SetupLights()
{
    // Set up a material. The material here just has the diffuse and ambient
    // colors set to yellow. Note that only one material can be used at a time.
    D3DMATERIAL8 mtrl;
    ZeroMemory( &mtrl, sizeof(D3DMATERIAL8) );
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
    g_pd3dDevice->SetMaterial( &mtrl );

    // Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DXVECTOR3 vecDir;
    D3DLIGHT8 light;
    ZeroMemory( &light, sizeof(D3DLIGHT8) );
    light.Type       = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 1.0f;
    light.Diffuse.b  = 1.0f;
    vecDir = D3DXVECTOR3(cosf(timeGetTime()/350.0f),
                         1.0f,
                         sinf(timeGetTime()/350.0f) );
    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    g_pd3dDevice->SetLight( 0, &light );
    g_pd3dDevice->LightEnable( 0, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // Finally, turn on some ambient light.
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    // Begin the scene
    g_pd3dDevice->BeginScene();

    // Setup the lights and materials
    SetupLights();

    // Setup the world, view, and projection matrices
    SetupMatrices();

    // Render the vertex buffer contents
    g_pd3dDevice->SetStreamSource( 0, g_pVB, sizeof(CUSTOMVERTEX) );
    g_pd3dDevice->SetVertexShader( D3DFVF_CUSTOMVERTEX );
    g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );

	if (g_SDOADx8)
		g_SDOADx8->RenderEx();
    // End the scene
    g_pd3dDevice->EndScene();


    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

BOOL isSDOLogin = false; // Use BOOL, not bool, to avoid potential problems
LoginResult loginResult;

BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved) 
{ // This callback closes the login dialog if it returns true; otherwise the dialog remains visible

	isSDOLogin = (SDOA_OK == nErrorCode); 
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


//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(g_SDOADx8) 
	{	// Pass the message to IGW for processing
		LRESULT lResult = 0; 
		if (g_SDOADx8->OnWindowProc( hWnd, msg, wParam, lParam, &lResult ) == SDOA_OK ) 
		{ 			
			return lResult; 
		} 
	} 

	if ((!g_hasLoginParam) && (SDOA_WM_CLIENT_RUN == msg))
	{	// Show the login dialog
		if (g_SDOAApp)
		{
			g_SDOAApp->ShowLoginDialog(OnLogin, 0, 0);
		}
	}

  switch( msg )
	{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
  return DefWindowProc( hWnd, msg, wParam, lParam );

}

void CALLBACK OnLostDevice()
{
	/* Notify D3D device loss */
	if( g_pVB != NULL )
	{
		g_pVB->Release();
		g_pVB = NULL;
	}
	if (g_SDOADx8)
		g_SDOADx8->OnDeviceLost();
}

void CALLBACK OnResetDevice()
{
	/* Notify successful D3D device reset */
	InitGeometry();
	// Turn off culling
	g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	if (g_SDOADx8)
		g_SDOADx8->OnDeviceReset(&d3dpp);
}



//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	//////////////////////////////////////////////////////////////////////////

	LPWSTR *szArglist;
	int nArgs;
	int i;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if( NULL == szArglist )
	{
		OutputDebugString("CommandLineToArgvW failed\n");
	}
	else 
	{
		char szTmp[512]={0};
		for( i=0; i<nArgs; i++) 
		{ // Output all arguments
			//printf("%d: %ws\n", i, szArglist[i]);
			_snprintf(szTmp, sizeof(szTmp), "\n%d: %ws\n", i, szArglist[i]);
			OutputDebugString(szTmp);
		}

		if (nArgs >= 3)
		{
			OutputDebugString("\n\n !!! Launcher Start!!! \n\n");
			_snprintf(g_szSessionID,  sizeof(g_szSessionID), "%ws", szArglist[1]);
			_snprintf(g_szAdditional, sizeof(g_szAdditional), "%ws", szArglist[2]);

			_snprintf(szTmp, sizeof(szTmp), "\n SessionID = %s\n",g_szSessionID);
			OutputDebugString(szTmp);
			_snprintf(szTmp, sizeof(szTmp), "\n Additional = %s\n",g_szAdditional);
			OutputDebugString(szTmp);

			g_hasLoginParam = true;			 
		}
		else
		{// Indicate that there are no arguments
			g_hasLoginParam = false;
			OutputDebugString("\n Normal Start! \n");
		}
	}

	// Free memory allocated for CommandLineToArgvW arguments.

	LocalFree(szArglist);


	// Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, LoadCursor( NULL, IDC_ARROW ), NULL, NULL,
                      "D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 04: Lights",
                              WS_OVERLAPPEDWINDOW, 100, 100, 800, 600,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL );


    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		/* Load IGW */
		OpenIGW();
		if (igwInitialize)
		{	// Indicate that loading succeeded
			SetWindowText(hWnd, "D3D Tutorial [加载IGW组件成功]");
		}	

		if (g_SDOADx8)
		{	// Initialize the IGW graphics engine
			g_SDOADx8->Initialize(g_pd3dDevice, &d3dpp, false);
		}

		if (g_SDOAApp && g_hasLoginParam)
		{
			g_SDOAApp->LoginDirect(g_szSessionID, g_szAdditional, 0);
		}

        // Create the geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );                    
					DispatchMessage( &msg );
                }
                else
				{	// Handle device loss simply
					if (g_DeviceLost)
					{	// Retry recovery slowly while the device is lost to avoid excessive CPU use
						Sleep(50);
					}
					switch (g_pd3dDevice->TestCooperativeLevel())
					{
					case D3D_OK:
						{	// 
							Render();
							g_DeviceLost = false;
							break;
						}
						
					case D3DERR_DEVICELOST:
						{
							if ( !g_DeviceLost )
							{
								OnLostDevice();
								g_DeviceLost = true;
							}							
							break;
						}
					case D3DERR_DEVICENOTRESET:
						{
							if ( g_pd3dDevice->Reset( &d3dpp ) == D3D_OK )
							{
								OnResetDevice();
								g_DeviceLost = false;
							}
							break;
						}
					}                    
				}
            }
        }
    }

	if (g_SDOADx8)
	{	// Release the IGW graphics engine
		g_SDOADx8->Finalize();
	}

	if (isSDOLogin && g_SDOAApp)
	{	// Log out after successful login
		g_SDOAApp->Logout();
	}

	/* Release IGW */
	CloseIGW();

    // Clean up everything and exit the app
    Cleanup();
    UnregisterClass( "D3D Tutorial", wc.hInstance );
	
    return 0;
}



