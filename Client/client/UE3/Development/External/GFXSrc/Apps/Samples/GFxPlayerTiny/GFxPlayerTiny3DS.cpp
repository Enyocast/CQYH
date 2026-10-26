/**************************************************************************

Filename    :   GFxPlayerTiny3DS.cpp
Content     :   Tiny FxPlayer sample for 3DS
Created     :   March 27, 2008
Authors     :   Michael Antonov, Dmitry Polenur,

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

// GFx includes
#include "GFx_Kernel.h"
#include "GFx.h"

#include "Kernel/SF_Timer.h"
#include "Kernel/SF_AllocAddr.h"
#include "Render/Renderer2D.h"
#include "Render/3DS/3DS_HAL.h"
#include "Render/3DS/3DS_Texture.h"

#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/ImageFiles/DDS_ImageFile.h"

#include "GFx/AS3/AS3_Global.h"


// 3DS includes
#include <nn/os.h>
#include <nn/fnd.h>
#include <nn/init.h>
#include <nn/fs.h>
#include <nn/gx.h>
#include <nn/hid.h>
#include <nn/applet.h>
#include <gles2/gl2.h>
#include <gles2/gl2ext.h>
#include <nn/gr.h>

#include <nn/dbg.h>
#include <stdlib.h>

namespace SF = Scaleform;
using namespace Scaleform;
using namespace Scaleform::Render;
using namespace Scaleform::GFx;

// SWF Filename we will load by default.
#define FXPLAYER_UPPER_FILENAME   "rom:/FxPlayer/3DSquares.swf"
//#define FXPLAYER_UPPER_FILENAME   "rom:/FxPlayer/ImgProtocol.swf"
#define FXPLAYER_LOWER_FILENAME   "rom:/FxPlayer/Window.swf"



/////////////////////////////////////////////////////////////////////////////
// ***** FxPlayerTiny Application Class

// FxPlayerTiny class encapsulates all of the system setup and FxPlayer
// program state needed for playback. FxPlayerTiny is created in main() /
// WinMain() and contains most of the program logic in its Run function.
//
class FxPlayerTiny
{
public:
    // Scaleform Fx object pointers.
    Ptr<MovieDef>           pUpperMovieDef;
    Ptr<Movie>              pUpperMovie;
    Ptr<MovieDef>           pLowerMovieDef;
    Ptr<Movie>              pLowerMovie;
	Ptr<Render::N3DS::HAL>  pRenderHAL; 
	Ptr<Render::Renderer2D> pRenderer;
    UInt32                  MovieLastTime;

	// Context to draw

	MovieDisplayHandle      hUpperMovieDisplay;
    MovieDisplayHandle      hLowerMovieDisplay;

    // Toggle states.
    bool                    AAEnabled;
    bool                    Paused;
    bool                    QuitFlag;

    // Device state and allocator
    GLuint                  CmdList;
    nn::fnd::ExpHeap*       pDevMem;
    AllocAddr*              pVidMemA;
    AllocAddr*              pVidMemB;
    class MemoryManager*    pMemManager;

    // Frame buffers
    struct DisplayBuffer
    { 
        GLenum          Buffers[2];
        UByte*          pBuffers[2];
    };

    DisplayBuffer             Left, Right, Lower;
    UPInt                     ColorSize, DepthSize;
    void*                     pColorBuffer;
    void*                     pDepthStencil;
    N3DS::RenderTargetParams  RTParams;
    Render::RenderTarget*     pScreenRT;
    bool                      IsStereo;
    int                       Frame;

    // Input
    nn::hid::PadReader        PadReader;
    nn::hid::TouchPanelReader TouchReader;

    int                       TouchX, TouchY;
    int                       TouchDown;
    Matrix2F                  TouchMatrix;

    // window size.
    int                     Width;
    int                     Height;
    int                     LowerWidth;
    int                     LowerHeight;

    UInt64                  LastStereoCheck;

public:    
    FxPlayerTiny();    
    ~FxPlayerTiny();

    // Initialize the player and run playback loop.
    int     Run();
    // Advance playback and render a frame.
    void    AdvanceAndDisplay();
    void    Display();

    // Input handler functions. Process mouse and keyboard and pass 
    // appropriate GFxEvent notifications to FxMovieView::HandleEvent.
    bool    ProcessMessages();
    void    OnPad(Key::Code keyCode, bool downFlag);
    void    OnMouseMove(float x, float y);
    void    OnMouseButton(unsigned button, bool downFlag, float x, float y);

    // System window and rendering setup.
    bool    SetupWindow(); 
};


// A sample implementation of FSCommandHandler. Users can install such a
// handler to receive notifications from fscommand() calls in ActionScript.
// Note that in many cases it is better to use GFxExternalInterface instead
// since it allows for better argument passing through ExternalInterface.call.
class FxPlayerFSCommandHandler : public FSCommandHandler
{
public:
    virtual void Callback(Movie* pmovie, const char* pcommand, const char* parg)
    {
        // Do not log anything since we don't have a console.
        // printf("Command: %s, Args: %s", pcommand, parg);
        SF_UNUSED3(pmovie, pcommand, parg);
    }
};


/////////////////////////////////////////////////////////////////////////////
// ***** FxPlayerTiny Class Implementation

FxPlayerTiny* pApp = 0;

FxPlayerTiny::FxPlayerTiny()
{
    AAEnabled       = 1;
    Paused          = 0;

    TouchDown = 0;
    TouchX = -10;
    TouchY = -10;

    pApp = this;
}

FxPlayerTiny::~FxPlayerTiny()
{
}


/////////////////////////////////////////////////////////////////////////////
// File opener class.
//
class FxPlayerFileOpener : public FileOpener 
{
public:
    virtual File* OpenFile(const char *purl) 
    {
        return new SysFile(purl);
    }
};

/////////////////////////////////////////////////////////////////////////////
// Sample ImageCreator. This just returns a gradient texture, but this interface
// can be used to load custom-created images (such as in the 3DS ETC formats).
static const int TexBlock[8][8] =
{
    {  0,  1,  4,  5, 16, 17, 20, 21 },
    {  2,  3,  6,  7, 18, 19, 22, 23 },
    {  8,  9, 12, 13, 24, 25, 28, 29 },
    { 10, 11, 14, 15, 26, 27, 30, 31 },

    { 32, 33, 36, 37, 48, 49, 52, 53 },
    { 34, 35, 38, 39, 50, 51, 54, 55 },
    { 40, 41, 44, 45, 56, 57, 60, 61 },
    { 42, 43, 46, 47, 58, 59, 62, 63 }
};

class SampleImageCreator : public GFx::ImageCreator
{
public:
    SampleImageCreator(Render::TextureManager* ptexman) : GFx::ImageCreator(ptexman) {}

    virtual  Render::Image* LoadProtocolImage(const GFx::ImageCreateInfo& info, const String& url)
    {
        N3DS::TextureManager* pTexMan = (N3DS::TextureManager*)GetTextureManager();
        UByte* data = (UByte*)pTexMan->GetMemoryManager()->Alloc(256*256*4, 128, Memory_3DS_Device);

        for ( int y = 0; y < 256; y++ )
            for ( int x = 0; x < 256; x++ )
            {
                UByte* pblock = data + 4 * ((y&~7) * 256 + (x&~7) * 8 + TexBlock[y&7][x&7]);

                pblock[0] = 255;
                pblock[1] = 128;
                pblock[2] = 255-y;
                pblock[3] = x;
            }

        nngxUpdateBuffer(data, 256*256*4);

        return SF_NEW TextureImage(Image_R8G8B8A8, ImageSize(256,256), 0,
                                   pTexMan->CreateTexture(0, data, ImageSize(256,256), 0));
    }
};


/////////////////////////////////////////////////////////////////////////////
// Called from main() after settings are initialized to execute
// most of the program logic. Responsible for setting up the window,
// loading movies and containing the playback/message loop.
//
int FxPlayerTiny::Run()
{
    if (!SetupWindow())
        return 1;
   
    // Create and Configure GFxLoader.   
    Loader loader;

    // Developers set states on the loader to modify loading and playback behavior.
    // If you need to load files from a custom package, for example, you can 
    // create a FxFileOpener derived class that loads files in a custom way.
    // Here FxFileOpener and FxFSCommandHandler are set for sample purposes.    
    Ptr<FileOpener> pfileOpener = *new FxPlayerFileOpener;
    loader.SetFileOpener(pfileOpener); 
    Ptr<FSCommandHandler> pcommandHandler = *new FxPlayerFSCommandHandler;
    loader.SetFSCommandHandler(pcommandHandler);

    pRenderHAL = *new Render::N3DS::HAL();

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.
    // See Renderer3DS.h for more parameters.
    if (!pRenderHAL->InitHAL(Render::N3DS::HALInitParams(CmdList, pMemManager )))
        return 1;

    Ptr<ImageCreator> pimageCreator = * SF_NEW SampleImageCreator(pRenderHAL->GetTextureManager());
    loader.SetImageCreator(pimageCreator);

    // add support for various image handlers
    SF::Ptr<GFx::ImageFileHandlerRegistry> pimgReg = *new GFx::ImageFileHandlerRegistry();
#ifdef SF_ENABLE_LIBJPEG
    pimgReg->AddHandler(&SF::Render::JPEG::FileReader::Instance);
#endif
#ifdef SF_ENABLE_LIBPNG
    pimgReg->AddHandler(&SF::Render::PNG::FileReader::Instance);
#endif
    pimgReg->AddHandler(&SF::Render::TGA::FileReader::Instance);
    pimgReg->AddHandler(&SF::Render::DDS::FileReader::Instance);
    loader.SetImageFileHandlerRegistry(pimgReg);

    // AS2 support
    Ptr<ASSupport> pAS2Support = *new GFx::AS2Support();
    loader.SetAS2Support(pAS2Support);

    // AS3 support
    Ptr<ASSupport> pASSupport = *new GFx::AS3Support();
    loader.SetAS3Support(pASSupport);

    // Load the movie file and create its instance.
    if (!(pUpperMovieDef = *loader.CreateMovie(FXPLAYER_UPPER_FILENAME)))
        return 1; 
    if (!(pLowerMovieDef = *loader.CreateMovie(FXPLAYER_LOWER_FILENAME)))
        return 1; 

    if (!(pUpperMovie = *pUpperMovieDef->CreateInstance()))
        return 1;
    if (!(pLowerMovie = *pLowerMovieDef->CreateInstance()))
        return 1;

    // Only the content displayed on the lower screen receives the touch input.
    pLowerMovie->SetMouseCursorCount(1);

    hUpperMovieDisplay = pUpperMovie->GetDisplayHandle();
    hLowerMovieDisplay = pLowerMovie->GetDisplayHandle();

    // Configure a render target. One render target can be used for both left and right displays.
    RTParams.ColorSize.Width = RTParams.DepthSize.Width = nn::gx::DISPLAY0_WIDTH;
    RTParams.ColorSize.Height = RTParams.DepthSize.Height = nn::gx::DISPLAY0_HEIGHT;
    RTParams.SetColorFormat(0);
    RTParams.DepthFormat = 3;
    RTParams.SetColorBuffer(pColorBuffer);
    RTParams.SetDepthBuffer(pDepthStencil);

    pScreenRT = pRenderHAL->CreateRenderTarget(RTParams);
    pRenderHAL->SetRenderTarget(pScreenRT, 1);

    // Create renderer.
	if (!(pRenderer = *new Render::Renderer2D(pRenderHAL.GetPtr())))
		return 1;

    // Set playback view to span the entire window.
    // On 3DS an Orientation flag must be used to get normal display because the buffers are rotated.
    // When using an Orientation flag, the BufferSize should match the buffer, and the viewport rectangle
    // should match the desired content orientation.
    pUpperMovie->SetViewport(Width, Height, 0,0, Height, Width, Render::Viewport::View_Orientation_R90);
    pLowerMovie->SetViewport(Width, Height, 0,0, LowerHeight, LowerWidth, Render::Viewport::View_Orientation_R90);

    // If you wanted to use the movie as a transparent HUD overlay, you would
    // set Background Alpha to 0. We don't need to do this for player sample.
    //pUpperMovie->SetBackgroundAlpha(0.0f);

    // Stereo Display
    // GFx stereo support is based on algorithms used for larger displays; a fake
    // display size is needed to get good results on small screens.
    Render::StereoParams StereoParam;
    StereoParam.DisplayDiagInches = 15.5f;
    StereoParam.Distortion = 0.4f;
    StereoParam.EyeSeparationCm = 1.4f;

    pRenderHAL->SetStereoParams(StereoParam);

    // Store initial timing, so that we can determine
    // how much to advance Flash playback.
    MovieLastTime = Timer::GetTicks()/1000;

    // Application / Player message loop.
    while(1)
    {
        if (!ProcessMessages())
            break;

        AdvanceAndDisplay();
    }

    return 0;
}


/////////////////////////////////////////////////////////////////////////////
// Advances Fx animation and draws the scene.
//
void FxPlayerTiny::AdvanceAndDisplay()
{
    // Check if stereo has been disabled.
    UInt64 curTime = Timer::GetTicks();
    if (curTime - LastStereoCheck > 100000)
    {
        bool stereo = nn::gx::IsStereoVisionAllowed();
        if (stereo != IsStereo)
        {
            nngxSetDisplayMode(stereo ? NN_GX_DISPLAYMODE_STEREO : NN_GX_DISPLAYMODE_NORMAL);
            IsStereo = stereo;
        }
        LastStereoCheck = curTime;
    }

    nngxRunCmdlist();

    // Advance
    UInt32  time    = Timer::GetTicks()/1000;
    float   delta   = ((float)(time - MovieLastTime)) / 1000.0f;

    if (!Paused)
    {
        pUpperMovie->Advance(delta);
        pLowerMovie->Advance(delta);
    }

    MovieLastTime = time;

    Display();

    nngxWaitCmdlistDone();
    nngxStopCmdlist();

    nngxClearCmdlist();

    nngxWaitVSync(NN_GX_DISPLAY_BOTH);

    Frame = !Frame;

    SF_AMP_CODE(AmpServer::GetInstance().AdvanceFrame());
}

void FxPlayerTiny::Display()
{
    SF_AMP_SCOPE_RENDER_TIMER_ID("FxPlayerTiny::Display", Amp_Native_Function_Id_Display);

    // Rendering to Upper screen
    // The same frame buffer is used for both screens (and both sides of stereo)
    pRenderer->BeginFrame();
    nngxAddMemoryFillCommand(pColorBuffer, ColorSize, 0, 32, pDepthStencil, DepthSize, 0, 32);

    if (IsStereo)
    {
        pRenderHAL->SetStereoDisplay(Render::StereoLeft, 0);
    }
    else
    {
        pRenderHAL->SetStereoDisplay(Render::StereoCenter, 0);
    }

    if (hUpperMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
    {
        pRenderer->Display(hUpperMovieDisplay);
    }

    if (IsStereo)
    {
        nngxActiveDisplay(NN_GX_DISPLAY0);
        nngxBindDisplaybuffer(Left.Buffers[Frame]);
        nngxSplitDrawCmdlist();

        nngxAddB2LTransferCommand(pColorBuffer, Width, Height, GL_RGBA8_OES,
            Left.pBuffers[Frame], Width, Height, GL_RGBA8_OES, NN_GX_ANTIALIASE_NOT_USED, 0, 8);

        //nngxAddMemoryFillCommand(pColorBuffer, ColorSize, 0, 32, pDepthStencil, DepthSize, 0, 32);

        pRenderHAL->SetStereoDisplay(Render::StereoRight, 0);
        pRenderer->Display(hUpperMovieDisplay);

        nngxActiveDisplay(NN_GX_DISPLAY0_RIGHT);
        nngxBindDisplaybuffer(Right.Buffers[Frame]);
        nngxSplitDrawCmdlist();

        nngxAddB2LTransferCommand(pColorBuffer, Width, Height, GL_RGBA8_OES,
            Right.pBuffers[Frame], Width, Height, GL_RGBA8_OES, NN_GX_ANTIALIASE_NOT_USED, 0, 8);
    }
    else
    {
        nngxActiveDisplay(NN_GX_DISPLAY0);
        nngxBindDisplaybuffer(Left.Buffers[Frame]);
        nngxSplitDrawCmdlist();

        nngxAddB2LTransferCommand(pColorBuffer, Width, Height, GL_RGBA8_OES,
            Left.pBuffers[Frame], Width, Height, GL_RGBA8_OES, NN_GX_ANTIALIASE_NOT_USED, 0, 8);
    }
    nngxSwapBuffers(NN_GX_DISPLAY0);

    // Rendering to lower screen
    nngxAddMemoryFillCommand(pColorBuffer, ColorSize, 0xff0000ff, 32, pDepthStencil, DepthSize, 0, 32);

    pRenderHAL->SetStereoDisplay(Render::StereoCenter, 0);
    if (hLowerMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
    {
        pRenderer->Display(hLowerMovieDisplay);
    }

    nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxBindDisplaybuffer(Lower.Buffers[Frame]);
    nngxSplitDrawCmdlist();

    nngxAddB2LTransferCommand((UByte*)pColorBuffer + 4*Width*(Height-LowerHeight), Width, Height, GL_RGBA8_OES,
        Lower.pBuffers[Frame], LowerWidth, LowerHeight, GL_RGBA8_OES, NN_GX_ANTIALIASE_NOT_USED, 0, 8);
    nngxSwapBuffers(NN_GX_DISPLAY1);

    // End frame and vsync
    pRenderer->EndFrame();
}

// Graphics memory management

static void* glAlloc(GLenum area, GLenum use, GLuint id, GLsizei size)
{
    int align = 8;
    switch (use)
    {
    case NN_GX_MEM_TEXTURE:
        align = 128;
        break;

    case NN_GX_MEM_RENDERBUFFER:
        align = 64;
        break;

    case NN_GX_MEM_DISPLAYBUFFER:
    case NN_GX_MEM_COMMANDBUFFER:
    case NN_GX_MEM_VERTEXBUFFER:
        align = 16;
        break;
    }

    void *ret;
    switch (area)
    {
    case NN_GX_MEM_FCRAM:
        ret =  pApp->pDevMem->Allocate(size, align);
        break;

    case NN_GX_MEM_VRAMA:
        ret = (void*)(pApp->pVidMemA->Alloc((size + 127) >> 7) << 7);
        break;

    case NN_GX_MEM_VRAMB:
        ret = (void*)(pApp->pVidMemB->Alloc((size + 127) >> 7) << 7);
        break;

    default:
        SF_ASSERT(0);
    } 
    //nn::dbg::detail::TPrintf("alloc %x %d %d = %p\n", area, use, size, ret);
    return ret;
}

static void glFree(GLenum area, GLenum aim, GLuint id, void* addr)
{
    switch (area)
    {
    case NN_GX_MEM_FCRAM:
        return pApp->pDevMem->Free(addr);

    case NN_GX_MEM_VRAMA:
    case NN_GX_MEM_VRAMB:
        ;
    } 
}

class MemoryManager : public Render::MemoryManager
{
    void* DevStart;
    void* DevEnd;
    void* VramAStart;
    void* VramAEnd;
    void* VramBStart;
    void* VramBEnd;

public:
    MemoryManager()
    {
        DevStart   = (void*)nn::os::GetDeviceMemoryAddress();
        DevEnd     = (char*)DevStart + nn::os::GetDeviceMemorySize();
        VramAStart = (void*)nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMA);
        VramAEnd   = (void*)nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMA);
        VramBStart = (void*)nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMB);
        VramBEnd   = (void*)nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMB);
    }

    virtual void*   Alloc(UPInt size, UPInt align, MemoryType type, unsigned arena = 0)
    {
        switch (type)
        {
        case Memory_3DS_VideoA:
            return (void*)(pApp->pVidMemA->Alloc((size + 127) >> 7) << 7);
        case Memory_3DS_VideoB:
            return (void*)(pApp->pVidMemB->Alloc((size + 127) >> 7) << 7);

        default:
            return pApp->pDevMem->Allocate(size, align);
        }
    }
    virtual void    Free(void* pmem, UPInt size)
    {
        if (pmem >= DevStart && pmem <= DevEnd)
            pApp->pDevMem->Free(pmem);
        else if (pmem >= VramAStart && pmem <= VramAEnd)
            pApp->pVidMemA->Free(UPInt(pmem) >> 7, (size + 127) >> 7);
        else
            pApp->pVidMemB->Free(UPInt(pmem) >> 7, (size + 127) >> 7);
    }
};

static nn::fnd::ExpHeap* deviceMemoryHeap()
{
    static bool heapInitialized = false;
    static nn::fnd::ExpHeap DevMem;

    if (!heapInitialized)
    {
        DevMem.Initialize(nn::os::GetDeviceMemoryAddress(), nn::os::GetDeviceMemorySize(),
            nn::os::ALLOCATE_OPTION_LINEAR);
        heapInitialized = true;
    }
    return &DevMem;
}

/////////////////////////////////////////////////////////////////////////////
// Setup Application Window
//
bool FxPlayerTiny::SetupWindow()
{
    pDevMem = deviceMemoryHeap();

    void* vma = (void*)nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMA);
    void* vmb = (void*)nn::gx::GetVramStartAddr(nn::gx::MEM_VRAMB);
    pVidMemA = new AllocAddr(Memory::GetGlobalHeap());
    pVidMemB = new AllocAddr(Memory::GetGlobalHeap());
    pVidMemA->AddSegment(UPInt(vma) >> 7, (nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMA) - UPInt(vma)) >> 7);
    pVidMemB->AddSegment(UPInt(vmb) >> 7, (nn::gx::GetVramEndAddr(nn::gx::MEM_VRAMB) - UPInt(vmb)) >> 7);
    Frame = 0;
    pMemManager = new ::MemoryManager();
    LastStereoCheck = 0;

    nngxInitialize(glAlloc, glFree);
    nngxGenCmdlists(1, &CmdList);
    nngxBindCmdlist(CmdList);
    nngxCmdlistStorage(0xB0000, 128);
    nngxSetCmdlistParameteri(NN_GX_CMDLIST_RUN_MODE, NN_GX_CMDLIST_SERIAL_RUN);
    nngxRunCmdlist();

    // Size of upper screen and frame buffer
    Width = nn::gx::DISPLAY0_WIDTH;
    Height = nn::gx::DISPLAY0_HEIGHT;

    nngxActiveDisplay(NN_GX_DISPLAY0);
    nngxGenDisplaybuffers(2, Left.Buffers);

    for (unsigned i = 0; i < 2; i++)
    {
        nngxBindDisplaybuffer(Left.Buffers[i]);
        nngxDisplaybufferStorage(GL_RGBA8_OES, Width, Height, NN_GX_MEM_FCRAM);
        GLint ret;
        nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &ret);
        Left.pBuffers[i] = (UByte*)ret;
    }
    nngxDisplayEnv(0, 0);

    nngxActiveDisplay(NN_GX_DISPLAY0_RIGHT);
    nngxGenDisplaybuffers(2, Right.Buffers);

    for (unsigned i = 0; i < 2; i++)
    {
        nngxBindDisplaybuffer(Right.Buffers[i]);
        nngxDisplaybufferStorage(GL_RGBA8_OES, Width, Height, NN_GX_MEM_FCRAM);
        GLint ret;
        nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &ret);
        Right.pBuffers[i] = (UByte*)ret;
    }
    nngxDisplayEnv(0, 0);

    // lower screen
    LowerWidth = nn::gx::DISPLAY1_WIDTH;
    LowerHeight = nn::gx::DISPLAY1_HEIGHT;
    TouchMatrix = Matrix2F(0, -1, (float)LowerWidth, 1, 0, 0).Invert();

    nngxActiveDisplay(NN_GX_DISPLAY1);
    nngxGenDisplaybuffers(2, Lower.Buffers);

    for (unsigned i = 0; i < 2; i++)
    {
        nngxBindDisplaybuffer(Lower.Buffers[i]);
        nngxDisplaybufferStorage(GL_RGBA8_OES, LowerWidth, LowerHeight, NN_GX_MEM_FCRAM);
        GLint ret;
        nngxGetDisplaybufferParameteri(NN_GX_DISPLAYBUFFER_ADDRESS, &ret);
        Lower.pBuffers[i] = (UByte*)ret;
    }
    nngxDisplayEnv(0, 0);

    IsStereo = 0;

    ColorSize = nn::gx::DISPLAY0_WIDTH * nn::gx::DISPLAY0_HEIGHT * 4;
    pColorBuffer = pMemManager->Alloc(ColorSize, 128, Memory_3DS_VideoA);
    DepthSize = nn::gx::DISPLAY0_WIDTH * nn::gx::DISPLAY0_HEIGHT * 4;
    pDepthStencil = pMemManager->Alloc(DepthSize, 128, Memory_3DS_VideoB);

    nngxAddMemoryFillCommand(pColorBuffer, ColorSize, 0, 32, pDepthStencil, DepthSize, 0, 32);

    nngxInvalidateState(NN_GX_STATE_OTHERS | NN_GX_STATE_SCISSOR | NN_GX_STATE_FBACCESS | NN_GX_STATE_FRAMEBUFFER);
    nngxStartLcdDisplay();

    return 1;
}


/////////////////////////////////////////////////////////////////////////////
// Message processing function to be called in the  application loops.
//
static const Key::Code keymap[] = {
    Key::Return,
    Key::Escape,
    Key::None,
    Key::Return,
    Key::Right,
    Key::Left,
    Key::Up,
    Key::Down,
    Key::PageUp,
    Key::PageDown,
    Key::Space,
    Key::Y
};

void FxPlayerTiny::OnPad(Key::Code key, bool downFlag)
{
    if (key != Key::None)
    {
        // Pass Key events to the movie so that can be handled in ActionScript.
        KeyEvent event(downFlag ? GFx::Event::KeyDown : KeyEvent::KeyUp, key);
        pUpperMovie->HandleEvent(event);
        pLowerMovie->HandleEvent(event);
    }
}

void FxPlayerTiny::OnMouseMove(float x, float y)
{
    MouseEvent event(GFx::Event::MouseMove, 0, (float)x, (float)y, 0.0f);
    pLowerMovie->HandleEvent(event);
}

void FxPlayerTiny::OnMouseButton(unsigned button, bool downFlag, float x, float y)
{
    if (downFlag)
    {
        MouseEvent event(GFx::Event::MouseDown, button, (float)x, (float)y, 0.0f);
        pLowerMovie->HandleEvent(event);
    }
    else
    {        
        MouseEvent event(GFx::Event::MouseUp, button, (float)x, (float)y, 0.0f);
        pLowerMovie->HandleEvent(event);
    }
}

bool FxPlayerTiny::ProcessMessages()
{
    nn::hid::PadStatus pad;
    PadReader.ReadLatest(&pad);

    for (int i = 0; i < 12; i++)
    {
        if (pad.trigger & (1 << i))
        {
            OnPad(keymap[i], 1);
        }
        else if (pad.release & (1 << i))
            OnPad(keymap[i], 0);
    }

    nn::hid::TouchPanelStatus touch;
    TouchReader.ReadLatest(&touch);

    int tx = (int) ((nn::gx::DISPLAY1_WIDTH - touch.y - 15) * LowerWidth/float(nn::gx::DISPLAY1_WIDTH-30));
    int ty = (int) ((touch.x - 15) * LowerHeight/float(nn::gx::DISPLAY1_HEIGHT-30));

    if (touch.touch && (tx != TouchX || ty != TouchY))
    {
        PointF p = TouchMatrix.Transform(PointF(tx,ty));
        OnMouseMove(p.x, p.y);
        TouchX = tx;
        TouchY = ty;
    }
    if (touch.touch != TouchDown)
    {
        PointF p = TouchMatrix.Transform(PointF(TouchX,TouchY));
        OnMouseButton(0, touch.touch, p.x, p.y);
        TouchDown = touch.touch;
    }

    return 1;
}


/////////////////////////////////////////////////////////////////////////////
// ***** main() -  Application entry point.

// The main function implementation creates the FxPlayerTiny class,
// passes it the filename and calls Run. FxPlayerTiny::Run is responsible
// for all of the rendering setup and movie playback.
//

void nnMain(void)
{
    nn::fs::Initialize();
    nn::hid::Initialize();

    {
        GFx::System gfxInit;

        uptr unused;
        UPInt stackSize = 1024 * 512;
        UPInt newStackSize = stackSize - 16384;
        uptr stack = (uptr) SF_MEMALIGN(newStackSize, 4096, Stat_Default_Mem);
        nn::svc::ControlMemory(&unused, 0x10000000 - stackSize, stack, newStackSize,
            nn::os::MEMORY_OPERATION_MAP, nn::os::MEMORY_PERMISSION_READ_WRITE);

        int bufsize = nn::fs::GetRomRequiredMemorySize(6, 6);
        void *buf = SF_ALLOC(bufsize, Stat_Default_Mem);
        nn::fs::MountRom(6, 6, buf, bufsize);

        int result = 1;
        {  
            FxPlayerTiny player;   
            result = player.Run();
        }
    }
}


