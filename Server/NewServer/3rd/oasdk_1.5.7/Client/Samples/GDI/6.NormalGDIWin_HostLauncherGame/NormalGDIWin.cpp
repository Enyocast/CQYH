// NormalGDIWin.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "NormalGDIWin.h"
#include <strsafe.h>        // For StringCch
#include "shellapi.h"
#include "SDOA4Client.h"
#include "SDOAGDI.h"

#define MAX_LOADSTRING 100

/* Integration-related global variables  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOAGDI*			g_SDOAGDI = NULL;
ISDOAApp2*			g_SDOAApp = NULL;
char				g_szSessionID[128];
char				g_szAdditional[128];


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND g_hWnd;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/* Load IGW */
void OpenIGW();
/* Release IGW */
void CloseIGW();
/* Login callback */
BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved);
/* Used to load the game */
bool LauncherGame(LPCSTR szSessionId, LPCSTR szAdditional);
/* Update the interface */
VOID CALLBACK UpdateUITimerProc( HWND hwnd,	UINT uMsg,	UINT_PTR idEvent,	DWORD dwTime );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_NORMALGDIWIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NORMALGDIWIN));

	/* Load IGW */
	OpenIGW();
	if (igwInitialize)
	{	// Indicate that loading succeeded
		SetWindowText(g_hWnd, L"NormalGDIWin [加载IGW组件成功]");
	}

	if (g_SDOAGDI)
	{		
		g_SDOAGDI->Initialize(g_hWnd, SDOA_GDIMODE_HOST);
		// Refresh the interface periodically using a timer
		SetTimer(g_hWnd, 0, 50, UpdateUITimerProc);
	}

	
	

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	KillTimer( g_hWnd, 0 );

	if (g_SDOAGDI)
	{
		g_SDOAGDI->Finalize(g_hWnd);
	}

	/* Release IGW */
	CloseIGW();

	return (int) msg.wParam;
}

VOID CALLBACK UpdateUITimerProc( HWND hwnd,	UINT uMsg,	UINT_PTR idEvent,	DWORD dwTime )
{
	// Simple repaint mechanism
	if (g_SDOAGDI)
	{
		InvalidateRect( g_hWnd, NULL, FALSE);
	}	
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NORMALGDIWIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_NORMALGDIWIN);
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
   

   hInst = hInstance; // Store instance handle in our global variable

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   g_hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   0, 0, 640, 480, NULL, NULL, hInstance, NULL);


   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

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

	if (g_SDOAGDI)
	{// Always give IGW first access to this window’s messages

		LRESULT lIGWResult = 0;
		if (g_SDOAGDI->OnWindowProc(hWnd, message, wParam, lParam, &lIGWResult) == SDOA_OK)
		{	// Do not let the window process messages already handled
			return lIGWResult;
		}

	}

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
		HBITMAP MemBitmap;
		HDC MemDC;
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		if (g_SDOAGDI)
		{	// Draw to the specified window
			
			// Use buffered drawing to reduce flicker
			MemBitmap = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left,
				ps.rcPaint.bottom - ps.rcPaint.top);
			MemDC = CreateCompatibleDC( hdc );
			HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, MemBitmap);

			g_SDOAGDI->Render(hWnd, MemDC);// First draw to MemDC

			// Then blit to the window DC to reduce flicker
			BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top,
				ps.rcPaint.right - ps.rcPaint.left,
				ps.rcPaint.bottom - ps.rcPaint.top,
				MemDC,
				ps.rcPaint.left, ps.rcPaint.top,
				SRCCOPY);


			SelectObject(MemDC, OldBitmap);
		}
		EndPaint(hWnd, &ps);
		if (g_SDOAGDI)
		{
			DeleteDC(MemDC);
			DeleteObject(MemBitmap);
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case SDOA_WM_CLIENT_RUN:
		/* This message arrives once after GameWidget.dll loads successfully; ShowLoginDialog can be called again at any time afterward */
		if (g_SDOAApp)
		{// The login dialog can be shown when this message arrives
			g_SDOAApp->ShowLoginDialog(OnLogin, 0, 0);
		}

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


/* Release IGW */
void CloseIGW()
{
	if (g_SDOAApp)
	{
		g_SDOAApp->Release();
		g_SDOAApp = NULL;
	}

	if (g_SDOAGDI)
	{
		g_SDOAGDI->Release();
		g_SDOAGDI = NULL;
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
					SDOA_RENDERTYPE_GDI,   // Client graphics engine type; both D3D9 and D3D8 are supported here
					1,                     // Maximum simultaneous players on one machine (usually 1; for example, KOF uses 2)
					-1,                    // Game area ID; pass -1 when unavailable
					-1                     // Game group ID; pass -1 when unavailable

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// Component initialized successfully

					// Get the component interface
					igwGetModule(__uuidof(ISDOAGDI), (void**)&g_SDOAGDI);
					igwGetModule(__uuidof(ISDOAApp2), (void**)&g_SDOAApp);
					if ( (!g_SDOAGDI) || (!g_SDOAApp))
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

BOOL isSDOLogin = false; // Use BOOL, not bool, to avoid potential problems
LoginResult loginResult;

BOOL CALLBACK OnLogin(int nErrorCode, const LoginResult* pLoginResult, int nUserData, int nReserved)
{ // This callback closes the login dialog if it returns true; otherwise the dialog remains visible

	isSDOLogin = (SDOA_OK == nErrorCode); 
	if (isSDOLogin) 
	{ 
		loginResult = *pLoginResult; 
		// Always zero first
		::ZeroMemory(g_szSessionID, sizeof(g_szSessionID));
		::ZeroMemory(g_szAdditional, sizeof(g_szAdditional));
		// Make a copy
		StringCchCopyA(g_szSessionID, sizeof(g_szSessionID), pLoginResult->szSessionId);
		StringCchCopyA(g_szAdditional, sizeof(g_szAdditional), pLoginResult->szAdditional);

		// Load the specified game
		if (LauncherGame(g_szSessionID, g_szAdditional))
		{// Flash on successful login and load
			PostQuitMessage(0);
		}

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

	if (SDOA_ERRORCODE_CANCEL == nErrorCode )
	{  // Exit if the user closes the login dialog
		PostQuitMessage(0);
	}
	return isSDOLogin; // Normal behavior: close the login dialog after successful login
} 

bool LauncherGame(LPCSTR szSessionId, LPCSTR szAdditional)
{
	bool tmpResult = false;

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


	WCHAR strGameExe[MAX_PATH] = {0};  // Game executable path and file name
	WCHAR strGamePath[MAX_PATH] = {0}; // Game executable directory
	StringCchPrintfW( strGameExe, MAX_PATH, L"%s\\Lights.exe", strExePath );
	StringCchPrintfW( strGamePath, MAX_PATH, L"%s\\", strExePath );

	if ( !(GetFileAttributesW(strGameExe) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameExe, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\Lights.exe", strExePath );
		StringCchPrintfW( strGamePath, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\", strExePath );
	}
	if ( !(GetFileAttributesW(strGameExe) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameExe, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\Release\\Lights.exe", strExePath );
		StringCchPrintfW( strGamePath, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\Release\\", strExePath );
	}
	
	if ( !(GetFileAttributesW(strGameExe) != 0xFFFFFFFF) )
	{ // If it is absent from the executable path, try another path
		StringCchPrintfW( strGameExe, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\Debug\\Lights.exe", strExePath );
		StringCchPrintfW( strGamePath, MAX_PATH, L"%s\\..\\..\\5.Tut04_Lights_GameTestLoginDirect\\Debug\\", strExePath );
	}

	if ( GetFileAttributesW(strGameExe) != 0xFFFFFFFF )
	{  // Load the target executable if found
		WCHAR strParam[512] = {0};

		WCHAR tmpStrSessionId[1024] = {0};
		WCHAR tmpStrAdditional[1024] = {0};

		// Convert the string
		int iLen = 0;
		iLen = MultiByteToWideChar(CP_ACP, 0, szSessionId, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, szSessionId, -1, tmpStrSessionId, iLen);

		iLen = MultiByteToWideChar(CP_ACP, 0, szAdditional, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, szAdditional, -1, tmpStrAdditional, iLen);
		
		StringCchPrintfW( strParam, 512, L"\"%s\" \"%s\"", tmpStrSessionId, tmpStrAdditional);
		

		ShellExecute(NULL, L"open", strGameExe, strParam, strGamePath, SW_SHOWNORMAL);
		tmpResult = true;
	}


	return tmpResult;
}