// AODGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "AODGame.h"
#include "interface.h"
#include <strsafe.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND g_gameHWND = NULL;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


HINSTANCE          g_hInstSDOLDll = 0;
LPSDOLInitialize    SDOLInitialize = NULL;
LPSDOLGetModule     SDOLGetModule = NULL;
LPSDOLTerminal      SDOLTerminal = NULL;

ISDOLLogin*			g_SDOLogin = NULL;

/* release snda login sdk */
void DestroySDOLogin()
{
	if (g_SDOLogin)
	{
		g_SDOLogin->Release();
		g_SDOLogin = NULL;
	}

	if (SDOLTerminal)
	{  // first to call SDOLTerminal
		SDOLTerminal();
		SDOLTerminal = NULL;
	}

	if (g_hInstSDOLDll)
	{
		FreeLibrary(g_hInstSDOLDll);
		g_hInstSDOLDll = 0;
	}
	SDOLInitialize = NULL;
}

/* load snda login sdk */
void LoadSDOLogin()
{
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileNameW( NULL, strExePath, MAX_PATH );

	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{	// get directory of exe
		StringCchCopyW( strExeName, MAX_PATH, &strLastSlash[1] );
		*strLastSlash = 0;
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	WCHAR strGameWidgetDll[MAX_PATH] = {0};
	StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\sdo\\sdologinentry.dll", strExePath );

	DestroySDOLogin();

	if ( GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF )
	{	// load library "sdologinentry.dll"
		g_hInstSDOLDll = LoadLibraryW(strGameWidgetDll);
		if (g_hInstSDOLDll)
		{
			SDOLInitialize = (LPSDOLInitialize)GetProcAddress( g_hInstSDOLDll, "SDOLInitialize" );
			SDOLGetModule = (LPSDOLGetModule)GetProcAddress( g_hInstSDOLDll, "SDOLGetModule" );
			SDOLTerminal = (LPSDOLTerminal)GetProcAddress( g_hInstSDOLDll, "SDOLTerminal" );
			if ( SDOLInitialize && SDOLGetModule && SDOLTerminal)
			{
				// load successfully
				SDOLAppInfo tmpAppInfo = {
					sizeof(SDOLAppInfo),   // size of struct
					736,		            // unique ID of APP, assigned by SDG
					L"AODGame",               // APP name
					L"0.1.2.0",            // version of game client
					1,                     // Area ID, assigned by SDG
					1                      // Group ID, assigned by SDG
				};

				if (SDOLInitialize(&tmpAppInfo) == SDOL_ERRORCODE_OK)
				{ //  initialize snda login sdk successfully

					SDOLGetModule(__uuidof(ISDOLLogin), (void**)&g_SDOLogin);

					if ((!g_SDOLogin))
						DestroySDOLogin();

				}
				else
					DestroySDOLogin();
			}
			else
				DestroySDOLogin();
		}
	}
}

/* callback of login sdk */
int CALLBACK OnLogin(int nErrorCode, const SDOLLoginResult* pLoginResult, int nUserData, int nReserved) 
{ 
	SDOLLoginResult loginResult;

	if (SDOL_ERRORCODE_OK == nErrorCode) 
	{ 
		loginResult = *pLoginResult; // login result, including sessionid
		SendMessage(g_gameHWND, WM_ACTIVATEAPP, 1,0);
		ShowWindow( g_gameHWND, SW_SHOW );		
		SetForegroundWindow(g_gameHWND);
	} 
	else if (SDOL_ERRORCODE_LOGINCANCEL == nErrorCode)
	{
		ExitProcess(0);
	}
	return SDOL_LOGINRESULT_CLOSE; //close login dialog according to this message
} 

/* show login dialog */
void ShowLoginDialog()
{
	if (g_SDOLogin)
	{
		HWND hMainWin = g_gameHWND;
		SendMessage(hMainWin, WM_ACTIVATEAPP, 0,0);
		g_SDOLogin->SetOwnerWindow(hMainWin);
		g_SDOLogin->ShowLoginDialog(OnLogin, 0, 0);
	}
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	/* load snda login sdk */
	LoadSDOLogin();	

// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_AODGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, SW_HIDE))
	{
		return FALSE;
	}

	if (SDOLInitialize)
	{	
		HWND hMainWin = g_gameHWND;
		SetWindowTextW(hMainWin, L"EmptyProject [EmptyProject [加载SDO Login组件成功]]");
	}	

	/* show login dialog before the main window rendered of game client */
	ShowLoginDialog();

 	

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_AODGAME));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	/* release snda login sdk */
	DestroySDOLogin();

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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_AODGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_AODGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_gameHWND = hWnd;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
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
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
