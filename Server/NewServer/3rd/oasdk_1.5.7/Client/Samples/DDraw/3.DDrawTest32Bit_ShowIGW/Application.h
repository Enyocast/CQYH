#pragma once

#include <Windows.h>
#include <ddraw.h>


#define WIN32_LEAN_AND_MEAN

class CApplication
{
public:
    CApplication(HINSTANCE AInstance);
    ~CApplication();
    bool Initialize();
    void Run();
    LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    bool InitWindow();
    void ShutdownWindow();

    bool InitDDraw(bool AFullScreen);
    void ShutdownDDraw();
	void Restore();
private:
    void FrameMove();
    void Render();
private:
    HINSTANCE m_hInstance;
    WNDCLASSEX m_WndCls;
    HWND m_hWnd;
	// Passed on every frame for convenience
	LPDIRECTDRAWSURFACE m_dds;

    LPDIRECTDRAW7 m_pDirectDraw;
    LPDIRECTDRAWSURFACE7 m_pMainSurface;
    LPDIRECTDRAWSURFACE7 m_pBackSurface;
    LPDIRECTDRAWCLIPPER m_pClipper;

	bool m_bIsFullScreen;
    bool m_bIsSDOLogin;
};