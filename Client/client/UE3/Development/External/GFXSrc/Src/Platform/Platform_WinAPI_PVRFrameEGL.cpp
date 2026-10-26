/**********************************************************************

Access      :   Public
Filename    :   Platform_WinAPI_GLES10.cpp
Content     :   OpenGLES 1.0 Platform Support under Win32 (emulation)
Created     :   2011
Authors     :   Bart Muzzin

Copyright   :   (c) 2003-2011 Scaleform Corp. All Rights Reserved.

Licensees may use this file in accordance with the valid Scaleform
Commercial License Agreement provided with the software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

**********************************************************************/


#if defined(SF_USE_GLES2)
#include "Render/GL/GL_HAL.h"
#elif defined(SF_USE_GLES)
#include "Render/GL/GLES11_HAL.h"
#endif
#include "Platform.h"

#if !defined(SF_USE_EGL)
    #error Must use EGL in Platform with OpenGL ES 1.1.
#endif

#define     OVERSIZE            1.0f

namespace Scaleform { namespace Platform {

 // Video mode
#define  SF_APP_GL_COLOR_BITS         32

class DeviceImpl : public NewOverrideBase<Stat_Default_Mem>
{
public:
    DeviceImpl(Render::ThreadCommandQueue* commandQueue);
    ~DeviceImpl();

    bool adjustViewConfig(ViewConfig* config);

    bool initGraphics(const ViewConfig& config, Device::Window* window, ThreadId renderThreadId );
    bool reconfigureGraphics(const ViewConfig& config);
    void shutdownGraphics();

    void setVSync(bool isEnabled);
    void setFSAA( bool isEnabled);
    bool setupPixelFormat(const ViewConfig& config);
    bool setFullScreenMode(const ViewConfig& config);
    bool checkFSAASupport(const ViewConfig& config);
    
    Device::Window*      pWindow;
    Ptr<Render::GL::HAL> pHal;
    DeviceStatus         Status;

    // OpenGL Variables
    HWND       hWnd;
    HDC        hDC;
    EGLDisplay hEGLDisplay;
    EGLConfig  hEGLConfig;
    EGLContext hEGLContext;
    EGLSurface hEGLSurface;
    bool     FSAASupported;
};


DeviceImpl::DeviceImpl(Render::ThreadCommandQueue* commandQueue)
 : pWindow(0), 
   pHal(0),
   Status(Device_NeedInit),
   hWnd(0),
   hDC(0), 
   hEGLDisplay(0),
   hEGLConfig(0),
   hEGLContext(0),
   hEGLSurface(0),
   FSAASupported(false)
{
    pHal = *SF_NEW Render::GL::HAL(commandQueue);
}

DeviceImpl::~DeviceImpl()
{
    pHal.Clear();
}



void DeviceImpl::setVSync(bool isEnabled)
{
    eglSwapInterval(hEGLDisplay, isEnabled ? 0 : 1);
}

void DeviceImpl::setFSAA( bool isEnabled)
{
#if !defined(SF_USE_GLES) && !defined(SF_USE_GLES2)
    if ( FSAASupported && isEnabled )
        glEnable(GL_MULTISAMPLE_ARB);
    else
        glDisable(GL_MULTISAMPLE_ARB);
#else
    SF_UNUSED(isEnabled);
#endif
}

bool DeviceImpl::setFullScreenMode(const ViewConfig& config)
{
    // If we're in fullscreen mode, set up the display
    if (config.ViewFlags & View_FullScreen)
    {
        // Set up the device mode structure
        DEVMODE screenSettings;
        memset(&screenSettings,0,sizeof(screenSettings));

        screenSettings.dmSize       = sizeof(screenSettings);
        screenSettings.dmPelsWidth  = config.ViewSize.Width;
        screenSettings.dmPelsHeight = config.ViewSize.Height;
        screenSettings.dmBitsPerPel = SF_APP_GL_COLOR_BITS;    // bits per pixel
        screenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Attempt to switch to the resolution and bit depth we've selected
        if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            return false;
        }
    }
    return true;
}

class ScopedTempWindow
{
public:
    ScopedTempWindow(HWND wnd) : hWnd(wnd) { }
    ~ScopedTempWindow() { ::DestroyWindow(hWnd); }
    HWND hWnd;
};

// We need to create a temporary window, and GL context, to query whether FSAA
// is available or not. The window is destroyed immediately afterwards.
bool DeviceImpl::checkFSAASupport(const ViewConfig& config)
{
    SF_UNUSED(config);
    FSAASupported = false;
    return FSAASupported;
}

// Sets up the pixel format according to the settings. Note that, FSAA is supported
// then the pixel format is always choosen to be an FSAA compatible one, so that,
// we can toggle FSAA by simply changing the GL_MULTISAMPLE_ARB state.
bool DeviceImpl::setupPixelFormat(const ViewConfig& config)
{   
    EGLint configCount;
    const EGLint maxConfigs = 64;

    EGLConfig configs[maxConfigs];
    eglGetConfigs(hEGLDisplay, configs, maxConfigs, &configCount);
    hEGLConfig = configs[0];
    for ( int c = 0; c < configCount; ++c )
    {
        EGLint cbits, sbits, dbits;
        eglGetConfigAttrib(hEGLDisplay, configs[c], EGL_BUFFER_SIZE, &cbits );
        eglGetConfigAttrib(hEGLDisplay, configs[c], EGL_DEPTH_SIZE, &dbits );
        eglGetConfigAttrib(hEGLDisplay, configs[c], EGL_STENCIL_SIZE, &sbits );

        // want a stencil buffer if available.
        if ( config.BitDepth && cbits == (int)config.BitDepth && sbits > 0)
        {
            hEGLConfig = configs[c];
            break;
        }
        else if ( sbits > 0 ) 
            hEGLConfig = configs[c];
    }

    return true;
}

bool DeviceImpl::adjustViewConfig(ViewConfig* config)
{
    if ( config->HasFlag(View_FullScreen) )
    {
        if ( !config->HasFlag(View_Size) )
        {
            int screenW = ::GetSystemMetrics(SM_CXSCREEN);
            int screenH = ::GetSystemMetrics(SM_CYSCREEN);
            config->SetSize(screenW, screenH);
        }


        config->SetPos(0,0);
    }
    else
    {
        if ( config->HasFlag(View_Size))
        {
            config->ViewSize = config->ViewSize.ExpandedTo(1,1);
        }
    }
    return true;
}

bool DeviceImpl::initGraphics(const ViewConfig& config, Device::Window* window, ThreadId renderThreadId )
{
    if (!pHal || !window)
        return false;

    pWindow = window;
    hWnd    = (HWND)window->GetHandle();

    if ((hDC = GetDC(hWnd)) == 0)
    {
        MessageBoxA(NULL,"Unable to create device context",
                    "OpenGLApp Error", MB_OK | MB_ICONEXCLAMATION);      
        return false;
    }

    EGLint major, minor;
    hEGLDisplay = eglGetDisplay( hDC );
    if ( !eglInitialize(hEGLDisplay, &major, &minor) )
    {
        MessageBoxA(NULL,"Unable to initialize EGL",
            "OpenGLApp Error", MB_OK | MB_ICONEXCLAMATION);      
        return false;
    }

    // Determine FSAA support.
    FSAASupported = checkFSAASupport(config);

    // Setup fullscreen (if requested).
    if (!setFullScreenMode(config))
    {
        MessageBoxA(NULL, "Unable to set fullscreen mode",
            "OpenGLApp Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    // Setup pixel format.
    if (!setupPixelFormat(config))
    {
        MessageBoxA(NULL, "Unable to set pixel format",
            "OpenGLApp Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    // Create OpenGL rendering context and make it active.
    if ((hEGLContext = eglCreateContext(hEGLDisplay, hEGLConfig, EGL_NO_CONTEXT, 0 ))== EGL_NO_CONTEXT)
    {
        MessageBoxA(NULL, "Unable to create OpenGL rendering context",
            "OpenGLApp Error",MB_OK | MB_ICONEXCLAMATION);
        return false;
    }


    hEGLSurface = eglCreateWindowSurface(hEGLDisplay, hEGLConfig, hWnd, 0);
    if ( hEGLSurface == EGL_NO_SURFACE )
    {
        MessageBoxA(NULL, "Unable to create OpenGL surface",
            "OpenGLApp Error",MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

    if (!eglMakeCurrent(hEGLDisplay, hEGLSurface, EGL_NO_SURFACE, hEGLContext ))
    {
        MessageBoxA(NULL,"Unable to activate OpenGL rendering context",
            "OpenGLApp Error", MB_OK | MB_ICONEXCLAMATION);
        return false;
    }

#ifdef SF_USE_GLES
    // Setup matrices.
    glMatrixMode(GL_PROJECTION);
    glOrthof(-OVERSIZE, OVERSIZE, OVERSIZE, -OVERSIZE, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
#endif

    // Set VSync, depending on the flag
    setVSync(config.HasFlag(View_VSync));

    // Set FSAA, if requested (and available).
    setFSAA(config.HasFlag(View_FSAA));

    // Configure renderer.
    Render::GL::HALInitParams params(0, renderThreadId);
    if (!pHal->InitHAL(params))
    {
        shutdownGraphics();
        return false;
    }

    Status = Device_Ready;
    return true;
}

bool DeviceImpl::reconfigureGraphics(const ViewConfig& config)
{
    // Set VSync, depending on the flag
    setVSync(config.HasFlag(View_VSync));

    // Set FSAA, if requested (and available).
    setFSAA(config.HasFlag(View_FSAA));

    return true;
}

void DeviceImpl::shutdownGraphics()
{
    if (pHal)
        pHal->ShutdownHAL();

    Status = Device_NeedInit;
    pWindow = 0;
    hWnd = 0;

    eglMakeCurrent(hEGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(hEGLDisplay, hEGLSurface);
    eglDestroyContext(hEGLDisplay, hEGLContext);
    eglTerminate(hEGLDisplay);

    hEGLSurface = 0;
    hEGLContext = 0;
    hEGLConfig  = 0;
    hEGLDisplay = 0;
}

//------------------------------------------------------------------------
Device::Device(Render::ThreadCommandQueue *commandQueue )
{
    pImpl = SF_NEW DeviceImpl(commandQueue);
}

Device::~Device()
{
    delete pImpl;
}

Render::HAL* Device::GetHAL() const
{
    return pImpl->pHal;
}

DeviceStatus Device::GetStatus() const
{
    return pImpl->Status;
}

bool Device::GraphicsConfigOnMainThread() const
{
    // GL does not require that the window config happens on the main thread.
    return false;
}

bool Device::AdjustViewConfig(ViewConfig* config)
{
    return pImpl->adjustViewConfig(config);
}

bool Device::InitGraphics(const ViewConfig& config, Device::Window* window, ThreadId renderThreadId )
{
    return pImpl->initGraphics(config, window, renderThreadId);
}

bool Device::ReconfigureGraphics(const ViewConfig& config)
{
    return pImpl->reconfigureGraphics(config);
}

void Device::ShutdownGraphics()
{
    pImpl->shutdownGraphics();
}

Size<unsigned> Device::GetDefaultViewSize()
{
    return Size<unsigned>(1024, 768);
}

//------------------------------------------------------------------------

static void Color32ToFloat(float *prgba, unsigned int color)
{
    float scalar = 1.0f / 255.0f;
    prgba[3] =  (color >> 24) * scalar;
    prgba[0] =  ((color >> 16) & 0xFF) * scalar;
    prgba[1] =  ((color >> 8) & 0xFF) * scalar;
    prgba[2] =  (color & 0xFF) * scalar;
}

void Device::Clear(UInt32 color)
{
    float   rgba[4];
    GLboolean scissorEnabled = glIsEnabled(GL_SCISSOR_TEST);
    if (scissorEnabled)
        glDisable(GL_SCISSOR_TEST);
    Color32ToFloat(rgba, color);
    glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    if (scissorEnabled)
        glEnable(GL_SCISSOR_TEST);
}

void Device::BeginFrame()
{
}

void Device::PresentFrame(unsigned)
{
    SF_AMP_SCOPE_RENDER_TIMER("Device::PresentFrame", Amp_Profile_Level_Low);
    ::SwapBuffers(pImpl->hDC);
}

void Device::SetWireframe(bool flag)
{
    // TODO:
    SF_UNUSED(flag);
}

void Device::SetWindow(Window*)
{

}

bool Device::TakeScreenShot(const String& )
{
    return false;
}

int AppBase::GetDisplayCount()
{
    return 1;
}

}} // Scaleform::Platform
