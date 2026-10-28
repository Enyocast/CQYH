// D3D7CppTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "D3D7CppTest.h"
#include <ddraw.h>
#include <d3d.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 
#include "SDOA4Client.h"
#include "SDOADx7.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
// Current window size
int						g_WinWidth = 640;
int						g_WinHeight = 480;
HWND					g_MainWin_hWnd = 0;
BOOL					g_bIsWindow = TRUE;		// Whether windowed mode is enabled
BOOL					g_bVSync = TRUE;		// Whether vertical sync is enabled
BOOL					g_DeviceLost = FALSE;	// Whether the device is lost
BOOL					g_bIsSizeMove = FALSE;
IDirect3D7*				g_pDirect3D		= NULL;
IDirect3DDevice7*		g_pDevice7		= NULL;
IDirectDraw7*			g_pDirectDraw7	= NULL;
IDirectDrawSurface7*	g_pFrontBuffer	= NULL;
IDirectDrawSurface7*	g_pBackBuffer	= NULL;
IDirectDrawClipper*		g_pClipper		= NULL;

/* Integration-related global variables  begin*/
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx7*			g_SDOADx7 = NULL;
ISDOAApp*			g_SDOAApp = NULL;
/* Integration-related global variables  end*/

#define SAFE_RELEASE(x) {if (x){ x->Release(); x = NULL;}}

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL				InitDevice();
void				FreeDevice();
void				FlipWindowed();
void				Flip();
BOOL				MayRender();
void				OnDeviceLost(); // Notify device loss
void				OnDeviceReset();// Notify device reset
void				Render();

void				OpenIGW();
void				CloseIGW();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_D3D7CPPTEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_D3D7CPPTEST);

	// Load IGW
	OpenIGW();
	if (igwInitialize)
	{	// Indicate that loading succeeded
		SetWindowText(g_MainWin_hWnd, "D3D Tutorial [加载IGW组件成功]");
	}	
	
	if (!InitDevice())
	{
		MessageBox(g_MainWin_hWnd, "创建D3D7设备错误", "提示", MB_OK);
		PostQuitMessage(0);// Exit after displaying the error
	}

	// Enter the message loop
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{ // Render when there are no messages
			if (g_DeviceLost == TRUE)
			{	// Retry recovery slowly while the device is lost to avoid excessive CPU use
				Sleep(100);
			}
			if(g_pDevice7)
			{// Device creation succeeded
				Render();// Rendering
			}// if(g_pDevice7)
		}
	}// while
	// Release IGW
	CloseIGW();
	FreeDevice();
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	//wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.style			= CS_CLASSDC;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_D3D7CPPTEST);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName	= (LPCTSTR)IDC_D3D7CPPTEST;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   g_MainWin_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   0, 0, g_WinWidth, g_WinHeight, NULL, NULL, hInstance, NULL);

   RECT rtCurRect;
   GetClientRect(g_MainWin_hWnd, &rtCurRect);
   // CreateWindow size includes the title bar and borders; set the client area size precisely below
   SetWindowPos(g_MainWin_hWnd, HWND_TOP, 0, 0, 
	   g_WinWidth - (rtCurRect.right - rtCurRect.left) + g_WinWidth, 
	   g_WinHeight - (rtCurRect.bottom - rtCurRect.top) + g_WinHeight, SWP_NOZORDER + SWP_NOACTIVATE);

   if (!g_MainWin_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_MainWin_hWnd, nCmdShow);
   UpdateWindow(g_MainWin_hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(g_SDOADx7) 
	{	// Pass the message to IGW for processing
		LRESULT lResult = 0; 
		if (g_SDOADx7->OnWindowProc( hWnd, message, wParam, lParam, &lResult ) == SDOA_OK ) 
		{ 			
			return lResult; 
		} 
	}
	//PAINTSTRUCT ps;
	//HDC hdc;

	switch (message) 
	{
	case WM_ENTERSIZEMOVE:
		g_bIsSizeMove = TRUE;
		break;
	case WM_EXITSIZEMOVE:
		g_bIsSizeMove = FALSE;
		break;
	case WM_SYSKEYDOWN:
		{
			DWORD dwMask = (1 << 29);
			bool bAltDown = ( (lParam & dwMask) != 0 );
			if (bAltDown && (VK_RETURN == wParam))
			{	// Recreate everything when switching between fullscreen and windowed modes
				g_bIsWindow = !g_bIsWindow;
				OutputDebugString("MsgProc WM_SYSKEYDOWN ALT+ENTER begin\n");

				FreeDevice();
				if (!InitDevice())
				{
					MessageBox(g_MainWin_hWnd, "创建D3D7设备错误", "提示", MB_OK);
					PostQuitMessage(0);// Exit after displaying the error
				}

				OutputDebugString("MsgProc WM_SYSKEYDOWN ALT+ENTER end\n");
				return 0;
			}
		}
	case WM_PAINT:
		//hdc = BeginPaint(hWnd, &ps);
		//// TODO: Add any drawing code here...
		//EndPaint(hWnd, &ps);
		if (g_bIsSizeMove && g_bIsWindow)
		{// Moving
			Render();
		}
		break;
	case WM_DESTROY:
		
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL CreateFrontBuffer()
{
	BOOL bResult = FALSE;
	DDSURFACEDESC2 FrontDesc;
	
	ZeroMemory( &FrontDesc, sizeof(FrontDesc) );
	FrontDesc.dwSize = sizeof(FrontDesc);
	if (g_bIsWindow)
	{
		FrontDesc.dwFlags = DDSD_CAPS;
		FrontDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}
	else
	{
		FrontDesc.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		FrontDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_3DDEVICE;
		FrontDesc.dwBackBufferCount = 1;
	}

	bResult = SUCCEEDED(g_pDirectDraw7->CreateSurface(&FrontDesc, &g_pFrontBuffer, NULL));
	if (bResult)
	{
		bResult = SUCCEEDED(g_pFrontBuffer->GetSurfaceDesc(&FrontDesc));
	}
	return bResult;
}

BOOL CreateBackBuffer()
{
	BOOL bResult = FALSE;
	DDSURFACEDESC2 BackDesc;
	ZeroMemory( &BackDesc, sizeof(BackDesc) );
	BackDesc.dwSize = sizeof(BackDesc);
	if (g_bIsWindow)
	{
		BackDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		BackDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		BackDesc.dwWidth = g_WinWidth;
		BackDesc.dwHeight = g_WinHeight;
		bResult = SUCCEEDED(g_pDirectDraw7->CreateSurface(&BackDesc, &g_pBackBuffer, NULL));
	}
	else
	{
		DDSCAPS2 BackCaps;
		ZeroMemory( &BackCaps, sizeof(BackCaps) );
		BackCaps.dwCaps = DDSCAPS_BACKBUFFER;
		// Release the acquired g_pBackBuffer before g_pFrontBuffer
		bResult = SUCCEEDED(g_pFrontBuffer->GetAttachedSurface(&BackCaps, &g_pBackBuffer));		
	}
	return bResult;
}

BOOL CreateClipper()
{
	BOOL bResult = FALSE;
	bResult = SUCCEEDED(g_pDirectDraw7->CreateClipper(0, &g_pClipper, NULL));
	if (bResult)
	{
		g_pClipper->SetHWnd(0, g_MainWin_hWnd);
		bResult = SUCCEEDED(g_pFrontBuffer->SetClipper(g_pClipper));
		SAFE_RELEASE(g_pClipper);
	}
	return bResult;
}

BOOL InitDevice()
{ // Create the D3D7 device
	BOOL bResult = FALSE;	
	bResult = SUCCEEDED(DirectDrawCreateEx( NULL, (void**)&g_pDirectDraw7, IID_IDirectDraw7, NULL ));
	if (!bResult)
	{
		return bResult;
	}
	bResult = SUCCEEDED(g_pDirectDraw7->QueryInterface(IID_IDirect3D7, (void**)&g_pDirect3D));
	if (!bResult)
	{
		SAFE_RELEASE(g_pDirect3D);
		SAFE_RELEASE(g_pDirectDraw7);
		return bResult;
	}
	DWORD nFlags;
	if (g_bIsWindow == TRUE)
	{
		nFlags = DDSCL_NORMAL;
	}
	else
	{
		nFlags = DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT;
	}

	bResult = SUCCEEDED(g_pDirectDraw7->SetCooperativeLevel(g_MainWin_hWnd, nFlags));
	if (!bResult)
	{
		SAFE_RELEASE(g_pDirect3D);
		SAFE_RELEASE(g_pDirectDraw7);
		return bResult;
	}
	if (g_bIsWindow)	
	{	// Windowed mode
		SetWindowLong(g_MainWin_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(g_MainWin_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
	}
	else
	{	// Fullscreen mode
		SetWindowLong(g_MainWin_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(g_MainWin_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
	}

	if (!g_bIsWindow)
	{
		bResult = SUCCEEDED(g_pDirectDraw7->SetDisplayMode(g_WinWidth, g_WinHeight, 32, 0, 0));
		if (!bResult)
		{
			bResult = SUCCEEDED(g_pDirectDraw7->SetDisplayMode(g_WinWidth, g_WinHeight, 16, 0, 0));
		}
		if (!bResult)
		{
			SAFE_RELEASE(g_pDirect3D);
			SAFE_RELEASE(g_pDirectDraw7);
			return bResult;
		}
	}

	bResult = CreateFrontBuffer();
	if (!bResult)
	{
		SAFE_RELEASE(g_pDirect3D);
		SAFE_RELEASE(g_pDirectDraw7);
		return bResult;
	}

	bResult = CreateBackBuffer();
	if (!bResult)
	{
		SAFE_RELEASE(g_pDirect3D);
		SAFE_RELEASE(g_pDirectDraw7);
		return bResult;
	}

	bResult = CreateClipper();
	if (!bResult)
	{
		SAFE_RELEASE(g_pDirect3D);
		SAFE_RELEASE(g_pDirectDraw7);
		return bResult;
	}

	bResult = SUCCEEDED(g_pDirect3D->CreateDevice(IID_IDirect3DHALDevice, g_pBackBuffer, &g_pDevice7));
	if (!bResult)
	{
		FreeDevice();
	}

	if (bResult && g_SDOADx7)
	{
		g_SDOADx7->Initialize(g_pDevice7, g_pDirectDraw7, g_pFrontBuffer, g_pBackBuffer, false, g_MainWin_hWnd);
	}

	return bResult;
}

void FreeDevice()
{
	if (g_SDOADx7)
	{
		g_SDOADx7->Finalize();
	}

	if (g_pDirectDraw7 && (!g_bIsWindow))
	{
		g_pDirectDraw7->RestoreDisplayMode();
	}
	SAFE_RELEASE(g_pDirect3D);
	SAFE_RELEASE(g_pDevice7);
	SAFE_RELEASE(g_pDirectDraw7);
    OutputDebugString("FreeDevice Free g_pBackBuffer begin \n");
	SAFE_RELEASE(g_pBackBuffer);
	OutputDebugString("FreeDevice Free g_pBackBuffer end \n");

	OutputDebugString("FreeDevice Free g_pFrontBuffer begin \n");
	SAFE_RELEASE(g_pFrontBuffer);
	OutputDebugString("FreeDevice Free g_pFrontBuffer end \n");
	SAFE_RELEASE(g_pClipper);
}

void FlipWindowed()
{
	WINDOWINFO tmpWinInfo;
	ZeroMemory( &tmpWinInfo, sizeof(tmpWinInfo) );
	tmpWinInfo.cbSize = sizeof(tmpWinInfo);
	if (!GetWindowInfo(g_MainWin_hWnd, &tmpWinInfo)) 
	{
		return;
	}
	RECT tmpWinRect = tmpWinInfo.rcClient;
	HMONITOR DestMonitor = MonitorFromWindow(g_MainWin_hWnd, MONITOR_DEFAULTTONEAREST);
	if (DestMonitor)
	{
		MONITORINFO tmpMonInfo;
		ZeroMemory(&tmpMonInfo, sizeof(tmpMonInfo));
		tmpMonInfo.cbSize = sizeof(tmpMonInfo);
		GetMonitorInfo(DestMonitor, &tmpMonInfo);
		tmpWinRect.left = tmpWinRect.left - tmpMonInfo.rcMonitor.left;
		tmpWinRect.top = tmpWinRect.top - tmpMonInfo.rcMonitor.top;
		tmpWinRect.right = tmpWinRect.right - tmpMonInfo.rcMonitor.left;
		tmpWinRect.bottom = tmpWinRect.bottom - tmpMonInfo.rcMonitor.top;
	}
	if (g_bVSync)
		g_pDirectDraw7->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, 0);
	g_pFrontBuffer->Blt(&tmpWinRect, g_pBackBuffer, NULL, DDBLT_WAIT, NULL);
}

void Flip()
{
	if (g_bVSync)
		g_pFrontBuffer->Flip(NULL, DDFLIP_WAIT);
	else
		g_pFrontBuffer->Flip(NULL, DDFLIP_WAIT | DDFLIP_NOVSYNC);
}

void OnDeviceLost()
{
	OutputDebugString("OnDeviceLost\n");
	if (g_SDOADx7)
		g_SDOADx7->OnDeviceLost();
}

void OnDeviceReset()
{
	OutputDebugString("OnDeviceReset\n");
	if(g_pFrontBuffer)
		g_pFrontBuffer->Restore();
	if (g_pBackBuffer)
		g_pBackBuffer->Restore();
	if (g_SDOADx7)
		g_SDOADx7->OnDeviceReset();
}

BOOL MayRender()
{
	BOOL bResult = FALSE;
	if (g_pDirectDraw7)
	{
		HRESULT tmpHS = g_pDirectDraw7->TestCooperativeLevel();
		BOOL bIsLost = FAILED(tmpHS);
		BOOL bNeedReset = ((g_DeviceLost)&&(!bIsLost))||((g_bIsWindow)&&(tmpHS = DDERR_WRONGMODE));
		if (bIsLost && (!g_DeviceLost))
		{
			OnDeviceLost();
			g_DeviceLost = TRUE;
			return bResult;
		}
		if ((g_DeviceLost && (! bIsLost)) || (bIsLost && bNeedReset))
		{
			OnDeviceReset();// Notify device reset; since reset may fail, allow it only after the next successful check
			g_DeviceLost = FALSE;
			return bResult;
		}
		bResult = TRUE;
	}
	return bResult;
}

void Render()
{
	if (MayRender())
	{// Render when allowed
		if (SUCCEEDED(g_pDevice7->Clear(0, NULL, D3DCLEAR_TARGET, 0, 0.0f, 0)))
		{
			if (SUCCEEDED(g_pDevice7->BeginScene()))
			{
				if (g_SDOADx7)
					g_SDOADx7->RenderEx();

				g_pDevice7->EndScene();
			}
			if (g_bIsWindow)
				FlipWindowed();
			else
				Flip();

		}
	}
}


/* Release IGW */
void CloseIGW()
{
	if (g_SDOADx7)
	{
		g_SDOADx7->Release();
		g_SDOADx7 = NULL;
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
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}
	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}
	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
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
					SDOA_RENDERTYPE_D3D7,  // Client graphics engine type: D3D7
					1,                     // Maximum simultaneous players on one machine (usually 1; for example, KOF uses 2)
					-1,                    // Game area ID; pass -1 when unavailable
					-1                     // Game group ID; pass -1 when unavailable

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// Component initialized successfully

					igwGetModule(__uuidof(ISDOADx7), (void**)&g_SDOADx7);
					igwGetModule(__uuidof(ISDOAApp), (void**)&g_SDOAApp);

					if ( (!g_SDOADx7) || (!g_SDOAApp))
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
