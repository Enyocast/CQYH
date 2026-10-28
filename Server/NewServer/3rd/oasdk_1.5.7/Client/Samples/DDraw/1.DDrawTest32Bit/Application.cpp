#include "Application.h"
#include <stdio.h>
#include "windows.h"

#define SAFE_RELEASE(x) {if (x){ x->Release(); x = NULL;}}

const int WINDOW_WIDTH  = 800;
const int WINDOW_HEIGHT = 600;

CApplication* theApp = NULL;

CApplication::CApplication(HINSTANCE AInstance)
:m_hInstance( AInstance )
{
    theApp = this;
    m_hWnd = NULL;
    m_pDirectDraw = NULL;
    m_pMainSurface = NULL;
    m_pBackSurface = NULL;
    m_pClipper = NULL;

    m_bIsSDOLogin = false;
	m_bIsFullScreen = false;
}

CApplication::~CApplication()
{

    ShutdownDDraw();
    ShutdownWindow();
    theApp = NULL;
}

bool CApplication::Initialize()
{
    if (!InitWindow())
    {
        OutputDebugString("Initialize window failed\n");
        return false;
    }

    if (!InitDDraw(false))
    {		
        OutputDebugString("Initialize ddraw failed\n");
		ShutdownDDraw();
        return false;
    }

    return true;
}

LRESULT WINAPI OnWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return theApp->WindowProc( hWnd, uMsg, wParam, lParam );
}

char* EncodeParam(LPSTR AData, int ASize, bool AQueryStr = true, bool AUseUTF8 = false);

LRESULT CApplication::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch ( uMsg )
    {
    case WM_DESTROY:
        ::PostQuitMessage( 0 );
        return 0;

	case WM_SYSKEYDOWN:
		{
			DWORD dwMask = (1 << 29);
			bool bAltDown = ( (lParam & dwMask) != 0 );

			if (bAltDown && (VK_RETURN == wParam))
			{	// Switch between fullscreen and windowed modes
				ShutdownDDraw();
				m_bIsFullScreen = !m_bIsFullScreen;
				if (m_bIsFullScreen)
					::SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
				else
				{
					::SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
					::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
				}

				if (!InitDDraw(m_bIsFullScreen))
				{
					ShutdownDDraw();
				}
			}
			return 0;
		}

    case WM_KEYDOWN:
        if ( VK_ESCAPE == wParam )
        {
            ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
            return 0;
        }
		else
            return ::DefWindowProc( hWnd, uMsg, wParam, lParam );

    default:
        return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
}

char* ConvertGBKToUtf8(char* s)
{

    int len = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL,0);
    unsigned short * wszUtf8 = new unsigned short[len + 1];
	
    memset((void *)wszUtf8, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, s, -1, (LPWSTR)wszUtf8, len);

    len = WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)wszUtf8, -1, NULL, 0, NULL, NULL); 
    char *szUtf8=new char[len + 1];

    memset(szUtf8, 0, len + 1);
    WideCharToMultiByte (CP_UTF8, 0, (LPWSTR)wszUtf8, -1, szUtf8, len, NULL,NULL);    
    delete[] wszUtf8;

    return szUtf8;
}

char* URLEncode(LPCSTR src, int ASize, bool AQueryStr)
{
    char* result = new char[1024];
    int n = 0;
    for (int i = 0; i < ASize; i++)
    {
        if (src[i] >= 'A' && src[i] <= 'Z')
        {
            result[n++] = src[i];
            continue;
        }

        if (src[i] >= 'a' && src[i] <= 'z')
        {
            result[n++] = src[i];
            continue;
        }

        if (src[i] >= '0' && src[i] <= '9')
        {
            result[n++] = src[i];
            continue;
        }

        if (src[i] == '-' || src[i] == '_' || src[i] == '.')
        {
            result[n++] = src[i];
            continue;
        }

        if (src[i] == ' ')
        {
            if (AQueryStr)
                result[n++] = '+';
            else
            {
                result[n++] = '%';
                result[n++] = '2';
                result[n++] = '0';
            }
            continue;
        }
        
        result[n++] = '%';

        //char buf[2];
        //sprintf(&result[n], "%x", src[i]);
        n += 2;
        //result[n++] = buf[0];
        //result[n++] = buf[1];
    }

    char* temp = new char[n + 1];
    ::CopyMemory(temp, result, n);
    temp[n] = 0;
    delete[] result;
    return temp;
}

char* EncodeParam(LPSTR AData, int ASize, bool AQueryStr, bool AUseUTF8)
{
    if (AUseUTF8)
    {
        char* utf8 = ConvertGBKToUtf8(AData);
        char* result = URLEncode(utf8, (int)strlen(utf8), AQueryStr);
        delete[] utf8;
        return result;
    }
    else
    {
        return URLEncode(AData, ASize, AQueryStr);
    }
}

bool CApplication::InitWindow()
{
    ::ZeroMemory(&m_WndCls, sizeof(m_WndCls));
    m_WndCls.cbSize = sizeof(m_WndCls);
    m_WndCls.hbrBackground = HBRUSH(::GetStockObject(BLACK_BRUSH));
    m_WndCls.hCursor = ::LoadCursor(0, IDC_ARROW);
    m_WndCls.hIcon = ::LoadIcon(0, IDI_APPLICATION);
    m_WndCls.hIconSm = m_WndCls.hIcon;
    m_WndCls.hInstance = m_hInstance;
    m_WndCls.lpfnWndProc = OnWindowProc;
    m_WndCls.lpszClassName = "IGW DDraw Sample";
    m_WndCls.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

    if (0 == ::RegisterClassEx(&m_WndCls))
        return false;

    DWORD wndStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;
    RECT rt = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    ::AdjustWindowRect(&rt, wndStyle, FALSE);
    int width = rt.right - rt.left;
    int height = rt.bottom - rt.top;

    m_hWnd = ::CreateWindowEx( 0, 
                               "IGW DDraw Sample", 
                               "IGW DDraw Sample",
                               wndStyle, 
                               (int)CW_USEDEFAULT,
                               (int)CW_USEDEFAULT, 
                               width, 
                               height,
                               NULL, 
                               NULL, 
                               m_hInstance, 
                               NULL
                               );
    if ( 0 == m_hWnd )
    {
        ::UnregisterClass( "IGW DDraw Sample", m_hInstance );
        return false;
    }

    return true;
}

void CApplication::ShutdownWindow()
{
    if ( m_hWnd != 0 )
    {
        ::UnregisterClass( "IGW DDraw Sample", m_hInstance );
        m_hWnd = NULL;
    }
}

bool CApplication::InitDDraw(bool AFullScreen)
{
	m_bIsFullScreen = AFullScreen;
    OutputDebugString("InitDDraw begin\n");
    DirectDrawCreateEx( NULL, (void**)&m_pDirectDraw, IID_IDirectDraw7, NULL );
    if ( !m_pDirectDraw )
        return false;

	if (m_bIsFullScreen)
	{
		if FAILED(m_pDirectDraw->SetCooperativeLevel( m_hWnd,  DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE))
		{
			OutputDebugString("InitDDraw FAILED(m_pDirectDraw->SetCooperativeLevel\n");
			return false;
		}

		//DDSURFACEDESC2 ddSurfaceDesc;
		//::ZeroMemory(&ddSurfaceDesc, sizeof(ddSurfaceDesc));
		//if FAILED(m_pDirectDraw->GetDisplayMode(&ddSurfaceDesc))
		//{
		//	OutputDebugString("InitDDraw FAILED(m_pDirectDraw->GetDisplayMode\n");
		//	return false;
		//}


		if FAILED(m_pDirectDraw->SetDisplayMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0))
		{
			OutputDebugString("InitDDraw FAILED(m_pDirectDraw->SetDisplayMode\n");
			return false;
		}

		DDSURFACEDESC2 dds;
		::ZeroMemory(&dds, sizeof(dds));
		dds.dwSize = sizeof(dds);
		dds.dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
		dds.dwBackBufferCount = 1;
		dds.ddsCaps.dwCaps = DDSCAPS_COMPLEX | DDSCAPS_FLIP | DDSCAPS_PRIMARYSURFACE | DDSCAPS_SYSTEMMEMORY;
		if FAILED(m_pDirectDraw->CreateSurface(&dds, &m_pMainSurface, NULL))
		{
			OutputDebugString("InitDDraw FAILED(m_pDirectDraw->CreateSurface\n");
			return false;
		}

		dds.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
		if FAILED(m_pMainSurface->GetAttachedSurface(&dds.ddsCaps, &m_pBackSurface))
		{
			OutputDebugString("InitDDraw FAILED(m_pMainSurface->GetAttachedSurface\n");
			return false;
		}
	}
	else
	{
		if FAILED(m_pDirectDraw->SetCooperativeLevel( m_hWnd,  DDSCL_NORMAL) )
		{
			return false;
		}

		DDSURFACEDESC2 ddsd;
		::ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		if FAILED(m_pDirectDraw->CreateSurface(&ddsd, &m_pMainSurface, NULL))
		{
			return false;
		}

		::ZeroMemory(&ddsd, sizeof(ddsd));
		ddsd.dwSize = sizeof(ddsd);
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.dwWidth = WINDOW_WIDTH;
		ddsd.dwHeight = WINDOW_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		if FAILED(m_pDirectDraw->CreateSurface(&ddsd, &m_pBackSurface, NULL))
		{
			return false;
		}

		if FAILED( m_pDirectDraw->CreateClipper(0, &m_pClipper, NULL ))
		{
			return false;
		}
		m_pClipper->SetHWnd( 0, m_hWnd );
		m_pMainSurface->SetClipper( m_pClipper );
	}
	OutputDebugString("InitDDraw end\n");
    return true;
}

void CApplication::ShutdownDDraw()
{
    SAFE_RELEASE(m_pClipper);
    SAFE_RELEASE(m_pBackSurface);
    SAFE_RELEASE(m_pMainSurface);
    SAFE_RELEASE(m_pDirectDraw);
	OutputDebugString("ShutdownDDraw\n");
}


void CApplication::Run()
{
    ::ShowWindow( m_hWnd, SW_SHOW );
    ::UpdateWindow( m_hWnd );

    MSG msg;
    while (true)
    {
        if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
            {
                break;
            }
            else
            {
                ::TranslateMessage( &msg );
                ::DispatchMessage( &msg );
            }
        }
        else
        {
			if (m_pMainSurface)
			{
				if ( m_pMainSurface->IsLost() == DDERR_SURFACELOST )
				{
					OutputDebugString("m_pMainSurface->Restore()\n");
					if (m_pMainSurface->Restore() != DD_OK)
					{						
						Restore();
					}
				}
			}
			if (m_pBackSurface)
			{
				if ( m_pBackSurface->IsLost() == DDERR_SURFACELOST )
				{
					OutputDebugString("m_pBackSurface->Restore()\n");
					if (m_pBackSurface->Restore() != DD_OK)
					{
						Restore();
					}
				}
			}

			if ( (m_pDirectDraw == NULL) || (m_pMainSurface == NULL))
			{
				Sleep(50);
				Restore(); 
			}

            FrameMove();
            Render();
        }
    }
}

void CApplication::FrameMove()
{
	if (!m_pDirectDraw)
		return;

    DDBLTFX bltFx;
    ::ZeroMemory(&bltFx, sizeof(bltFx));
    bltFx.dwSize = sizeof(bltFx);
    bltFx.dwFillColor = 0xff0000ff;
    if FAILED(m_pBackSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &bltFx))
        ::OutputDebugString("blt back surface failed");

	if ( !m_bIsFullScreen )
	{
		//Used in windowed mode
		RECT rt;
		::GetClientRect( m_hWnd, &rt );

		POINT pt = { rt.left, rt.top };
		::ClientToScreen( m_hWnd, &pt );
		rt.left = pt.x;
		rt.top = pt.y;
		rt.right = rt.left + WINDOW_WIDTH;
		rt.bottom = rt.top + WINDOW_HEIGHT;
		m_pMainSurface->Blt( &rt, m_pBackSurface, NULL, DDBLT_WAIT, NULL );
	}
}

void CApplication::Render()
{
    if (m_bIsFullScreen && m_pMainSurface)
	{
		while FAILED(m_pMainSurface->Flip(NULL, DDFLIP_NOVSYNC))
			::OutputDebugString("flip failed");
	}
}

void CApplication::Restore()
{
	ShutdownDDraw();
	
	if (m_bIsFullScreen)
		::SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	else
	{
		::SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
		::SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
	}

	if (!InitDDraw(m_bIsFullScreen))
	{
		ShutdownDDraw();
	}
}