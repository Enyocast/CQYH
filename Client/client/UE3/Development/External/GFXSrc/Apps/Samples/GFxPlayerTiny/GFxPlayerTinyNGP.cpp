/**************************************************************************

Filename    :   GFxPlayerTinyNGP.cpp
Content     :   Tiny GFxPlayer sample for NGP.
Created     :   March 13, 2008
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

// GFx Includes
#include "GFx_Kernel.h"
#include "GFx.h"

#include "Render/Renderer2D.h"
#include "Render/NGP/NGP_MemoryManager.h"
#include "Render/NGP/NGP_HAL.h"

#include "Render/ImageFiles/JPEG_ImageFile.h"
#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/ImageFiles/TGA_ImageFile.h"
#include "Render/ImageFiles/DDS_ImageFile.h"
#include "Render/ImageFiles/GXT_ImageFile.h"

#include "GFx/AS3/AS3_Global.h"

// NGP includes
#include <ctrl.h>
#include <touch.h>
#include <kernel.h>
#include <display.h>

#include <libsysmodule.h>
#include <razor_capture.h>


const char		sceUserMainThreadName[]		= "Scaleform App";
int				sceUserMainThreadPriority	= SCE_KERNEL_DEFAULT_PRIORITY_USER;
unsigned int	sceUserMainThreadStackSize	= 512 * 1024;
unsigned int	sceLibcHeapSize	= 256 << 20;

// SWF filename we will load by default.
#define FXPLAYER_FILENAME   "host0:/FxPlayer/Window.swf"

namespace SF = Scaleform;
using namespace Scaleform;
using namespace Render;
using namespace GFx;

// ***** FxPlayerTiny Application Class

// FxPlayerTiny class encapsulates all of the system setup and GFxPlayer
// program state needed for playback. FxPlayerTiny is created in main() /
// WinMain() and contains most of the program logic in its Run function.

class FxPlayerTiny
{
    // Scaleform GFx object pointers.
    Ptr<MovieDef>           pMovieDef;
    Ptr<Movie>              pMovie;
	Ptr<Render::NGP::HAL>   pRenderHAL;
	Ptr<Render::Renderer2D> pRenderer;

	MovieDisplayHandle      hMovieDisplay;
    UInt32                  MovieLastTime;

    // Toggle states.
    bool    Wireframe; 
    bool    ControlKeyDown;
    bool    AAEnabled;
    bool    Paused;

    // Playback filename and window size.
    String  FileName;
    int     Width;
    int     Height;
    int     MouseX, MouseY;
    int     MouseXadj, MouseYadj;

    bool    VerboseAction;

    // Input
    struct PadData
    {    
        SceCtrlData     pad;
        int             MouseX, MouseY;
        float           MouseXadj, MouseYadj;
        bool            PadConnected;

        bool    LStickLeft, LStickRight, LStickUp, LStickDown;
        bool    nLStickLeft, nLStickRight, nLStickUp, nLStickDown;

        float   LastLx, LastLy, LastRx, LastRy;

        UInt64  LastMsgTime, LastRepeatTime, RepeatDelay;

        PadData() :
        MouseX(0), MouseY(0),
            MouseXadj(0), MouseYadj(0),
            PadConnected(false)        
        {
            memset(&pad, 0, sizeof(pad));
            pad.lx = pad.ly = 0x80;
            pad.rx = pad.ry = 0x80;

            LastLx = LastLy = LastRx = LastRy = 2;

            LStickLeft = LStickRight = LStickUp = LStickDown = false;
            nLStickLeft = nLStickRight = nLStickUp = nLStickDown = false;
            LastRepeatTime = RepeatDelay = 0;
            LastMsgTime = Timer::GetTicks();
        }
    } Pad;

    SceTouchPanelInfo TouchPanel;
    SceTouchData      Touch;
    int               TouchPrimaryId;

    SceInt16          SwipeTouchX, SwipeTouchY;
    SceInt16          LastTouchX, LastTouchY;


    // Graphics state
    enum
    {
        FRAME_BUFFERS = 2
    };
    SceGxmContext*              GxmCtx;
    NGP::MemoryManager*         pMemManager;

    void*                       DispBuffer[FRAME_BUFFERS];
    SceGxmColorSurface          DispSurface[FRAME_BUFFERS];
    SceGxmSyncObject*           DispSync[FRAME_BUFFERS];
    void*                       DepthBuffer;
    SceGxmDepthStencilSurface   DepthSurface;
    unsigned                    BackBuffer, FrontBuffer;
    SceGxmRenderTarget*         RenderTarget;

    Render::RenderTarget*       pDisplayRT;

    SceGxmRenderTargetParams    RTParams;
    SceGxmContextParams         ContextParams;
    SceGxmNotification          Notify;
	SceGxmMultisampleMode       MultisampleMode;

public:
    FxPlayerTiny(const char* pfilename, bool verboseAction);
    ~FxPlayerTiny();

    // Initialize the player and run playback loop.
    int     Run();
    // Advance playback and render a frame.
    void    AdvanceAndDisplay();
    void    Display();

    // Input handler functions. Process mouse and keyboard and pass 
    // appropriate Event notifications to Movie::HandleEvent.
    bool    ProcessMessages();
    void    OnPad(unsigned controllerIdx, Key::Code keyCode, bool downFlag);
    void    OnPadStick(unsigned controllerIndex, PadKeyCode padCode, float xpos, float ypos);

    void OnMouseButton(unsigned mouseIndex, unsigned button, bool downFlag, const Point<int>& mousePos);    
    void OnMouseMove(unsigned mouseIndex, const Point<int>& mousePos, KeyModifiers mods);
    void OnMouseWheel(unsigned mouseIndex, float zdelta, const Point<int>& mousePos, KeyModifiers mods);

    void OnTouchBegin(unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary);
    void OnTouchEnd(unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary);
    void OnTouchMove(unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary);

    void            OnGesture(UInt32 gestureMask, const Point<int>& pos, 
        const PointF& translationDelta,
        const PointF& scaleDelta,
        float rotationDelta);
   
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

class GFxPlayerLog : public GFx::Log
{
public:
    // We override this function in order to do custom logging.
    virtual void LogMessageVarg(LogMessageType messageType, const char* pfmt, va_list argList)
    {
        SF_UNUSED(messageType);
        // Output log to console
        vprintf(pfmt, argList);
    }
};


// ***** FxPlayerTiny Class Implementation

FxPlayerTiny::FxPlayerTiny(const char* pfilename, bool verboseAction)
{
    AAEnabled = 1;
    Paused    = 0;
    FileName  = pfilename;

    MouseX    = 100;
    MouseY    = 100;
    MouseXadj = 0;
    MouseYadj = 0;

    FileName      = pfilename;
    VerboseAction = verboseAction;

    memset(DispSync, 0, sizeof(DispSync));
    pMemManager = 0;
}

#define DISPLAY_WIDTH				960
#define DISPLAY_HEIGHT				544
#define DISPLAY_PITCH               1024

FxPlayerTiny::~FxPlayerTiny()
{
    SF_FREE_ALIGN(ContextParams.hostMem);
    for (int i = 0; i < FRAME_BUFFERS; i++)
    {
        if ( pMemManager )
            pMemManager->Free(DispBuffer[i], 4*DISPLAY_PITCH * DISPLAY_HEIGHT);
        if ( DispSync[i] )
            sceGxmSyncObjectDestroy(DispSync[i]);
    }

#if (SCE_PSP2_SDK_VERSION < 0x00996000)
    SF_FREE(RTParams.hostMem);
#endif

    // Destroy the renderer/HAL before deleting the memory manager.
    pRenderer = 0;
    pRenderHAL = 0;

    delete pMemManager;
}

// Called from main()/WinMain() after settings are initialized to execute
// most of the program logic. Responsible for setting up the window,
// loading movies and containing the playback/message loop.
int FxPlayerTiny::Run()
{    
    if (!SetupWindow())
        return 1;

    // Create and Configure Loader.   
    Loader loader;
	loader.SetLog(Ptr<GFx::Log>(*new GFxPlayerLog()));

    // Developers set states on the loader to modify loading and playback behavior.
    // If you need to load files from a custom package, for example, you can 
    // create a FileOpener derived class that loads files in a custom way.
    // Here FileOpener and FSCommandHandler are set for sample purposes.    
    Ptr<FileOpener> pfileOpener = *new FileOpener;
    loader.SetFileOpener(pfileOpener); 
    Ptr<FSCommandHandler> pcommandHandler = *new FxPlayerFSCommandHandler;
    loader.SetFSCommandHandler(pcommandHandler);

    SF::Ptr<GFx::ImageFileHandlerRegistry> pimgReg = *new GFx::ImageFileHandlerRegistry();
#ifdef SF_ENABLE_LIBJPEG
    pimgReg->AddHandler(&SF::Render::JPEG::FileReader::Instance);
#endif
#ifdef SF_ENABLE_LIBPNG
    pimgReg->AddHandler(&SF::Render::PNG::FileReader::Instance);
#endif
    pimgReg->AddHandler(&SF::Render::TGA::FileReader::Instance);
    pimgReg->AddHandler(&SF::Render::DDS::FileReader::Instance);
    pimgReg->AddHandler(&SF::Render::GXT::FileReader::Instance);
	loader.SetImageFileHandlerRegistry(pimgReg);

    // AS2 support
	Ptr<ASSupport> pAS2Support = *new GFx::AS2Support();
	loader.SetAS2Support(pAS2Support);
    // AS3 support
    Ptr<ASSupport> pASSupport = *new GFx::AS3Support();
    loader.SetAS3Support(pASSupport);

    // Load the movie file and create its instance.
    if (!(pMovieDef = *loader.CreateMovie(FileName)))
        return 1;
    if (!(pMovie = *pMovieDef->CreateInstance()))
        return 1;

    pMovie->SetMouseCursorCount(1);
	hMovieDisplay = pMovie->GetDisplayHandle();

	pRenderHAL = *new Render::NGP::HAL();

    volatile UInt32* pNotify = sceGxmGetNotificationRegion();
    Notify.address = pNotify;

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.    
    if (!pRenderHAL->InitHAL(Render::NGP::HALInitParams(GxmCtx, Notify, pMemManager)))
        return 1;

    // Create the default rendertarget. This is required on NGP.
    pDisplayRT = SF_NEW Render::RenderTarget(0, RBuffer_Default, ImageSize(DISPLAY_WIDTH, DISPLAY_HEIGHT) );

    NGP::HALData::UpdateData(pDisplayRT, 0, ImageSize(DISPLAY_WIDTH, DISPLAY_HEIGHT), RenderTarget, MultisampleMode,
        DispSurface[BackBuffer], &DepthSurface, DispSync[BackBuffer] );

    if ( !pRenderHAL->SetRenderTarget(pDisplayRT, false))
        return 1;

    // Create renderer.
    if (!(pRenderer = *new Render::Renderer2D(pRenderHAL.GetPtr())))
        return 1;

    // Set playback view to span the entire window.
    pMovie->SetViewport(Width, Height, 0, 0, Width, Height);

    // Store initial timing, so that we can determine
    // how much to advance Flash playback.
    MovieLastTime = Timer::GetTicks() / 1000;

    // Application / Player message loop.
    while (1)
    {
        if (!ProcessMessages())
            break;            
        AdvanceAndDisplay();
    }

    return 0;
}


// Advances GFx animation and draws the scene.
void FxPlayerTiny::AdvanceAndDisplay()
{
    NGP::HALData::UpdateData(pDisplayRT, 0, ImageSize(DISPLAY_WIDTH, DISPLAY_HEIGHT), RenderTarget, MultisampleMode,
        DispSurface[BackBuffer], &DepthSurface, DispSync[BackBuffer] );
    pRenderHAL->SetRenderTarget(pDisplayRT, false);

    sceGxmBeginScene(GxmCtx, 0, RenderTarget, 0, 0, DispSync[BackBuffer], &DispSurface[BackBuffer], &DepthSurface);

    // GFx rendering    
    if (pMovie)
    {
        UInt32 time  = Timer::GetTicks() / 1000;
        float  delta = ((float)(time - MovieLastTime)) / 1000.0f;

        // Advance time and display the movie.
        if (!Paused)
            pMovie->Advance(delta);

        Display();

        MovieLastTime = time;
    }

    if (pRenderHAL->IsSceneActive())
        sceGxmEndScene(GxmCtx, 0, &Notify);

    SceDisplayFrameBuf frame;
    frame.base = DispBuffer[BackBuffer];
    frame.width = DISPLAY_WIDTH;
    frame.height = DISPLAY_HEIGHT;
    frame.pitch = DISPLAY_PITCH;
    frame.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
    frame.size = sizeof(SceDisplayFrameBuf);

    sceGxmPadHeartbeat(&DispSurface[BackBuffer], DispSync[BackBuffer]);

    int result = sceGxmDisplayQueueAddEntry(DispSync[FrontBuffer], DispSync[BackBuffer], &frame);
    SF_ASSERT(result == SCE_OK);

    FrontBuffer = BackBuffer;
    BackBuffer = (BackBuffer + 1) % FRAME_BUFFERS;

    SF_AMP_CODE(AmpServer::GetInstance().AdvanceFrame());
}

void FxPlayerTiny::Display()
{
    pRenderer->BeginFrame();
    if (hMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
    {
        pRenderer->Display(hMovieDisplay);
    }
    pRenderer->EndFrame();
}

void FxPlayerTiny::OnPad(unsigned controllerIdx, Key::Code keyCode, bool downFlag)
{
    if (!pMovie)
        return;

    KeyEvent event(downFlag ? GFx::Event::KeyDown : GFx::Event::KeyUp, keyCode);
    pMovie->HandleEvent(event);
}

void FxPlayerTiny::OnPadStick(unsigned controllerIndex, PadKeyCode padCode, float xpos, float ypos)
{
    GamePadAnalogEvent event(padCode, xpos, ypos, controllerIndex);
    if (pMovie)
        pMovie->HandleEvent(event);
}

void FxPlayerTiny::OnTouchBegin(unsigned id, const Point<int>& p, const Point<int>& contact, bool primary)
{
    TouchEvent event(GFx::Event::TouchBegin, id, p.x, p.y, contact.x, contact.y, primary);

    if (pMovie)
        pMovie->HandleEvent(event);
}
void FxPlayerTiny::OnTouchEnd(unsigned id, const Point<int>& p, const Point<int>& contact, bool primary)
{
    TouchEvent event(GFx::Event::TouchEnd, id, p.x, p.y, contact.x, contact.y, primary);

    if (pMovie)
        pMovie->HandleEvent(event);
}
void FxPlayerTiny::OnTouchMove(unsigned id, const Point<int>& p, const Point<int>& contact, bool primary)
{
    TouchEvent event(GFx::Event::TouchMove, id, p.x, p.y, contact.x, contact.y, primary);

    if (pMovie)
        pMovie->HandleEvent(event);
}

void FxPlayerTiny::OnGesture(UInt32 gestureMask, const Point<int>& p, 
                               const PointF& translation,
                               const PointF& scale,
                               float rotation)
{
    GestureEvent event(gestureMask & GestureEvent::GestureBit_Swipe ? GFx::Event::GestureSimple
        : GFx::Event::Gesture, gestureMask, p.x, p.y,
        translation.x, translation.y, scale.x, scale.y, rotation);

    if (pMovie)
        pMovie->HandleEvent(event);
}

void FxPlayerTiny::OnMouseButton(unsigned mouseIndex, unsigned button, bool downFlag, const Point<int> &p)
{
    if (pMovie)
    {
        MouseEvent event(downFlag ? GFx::Event::MouseDown : GFx::Event::MouseUp, button, p.x, p.y, 0);
        pMovie->HandleEvent(event);
    }
}

void FxPlayerTiny::OnMouseMove(unsigned mouseIndex, const Point<int> &p, KeyModifiers modifiers)
{
    if (pMovie)
    {
        MouseEvent event(GFx::Event::MouseMove, 0, p.x, p.y, 0);
        pMovie->HandleEvent(event);
    }
}

// Setup Application Window and initialize graphics

static void present(const void *framebuf)
{
    SceDisplayFrameBuf* pframebuf = (SceDisplayFrameBuf*) framebuf;

    sceDisplayWaitSetFrameBufMulti(2);
    sceDisplaySetFrameBuf(pframebuf, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
    sceDisplayWaitSetFrameBuf();
}

bool FxPlayerTiny::SetupWindow()
{
    Touch.reportNum = 0;

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITALANALOG);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);

    Width = DISPLAY_WIDTH;
    Height = DISPLAY_HEIGHT;

    sceSysmoduleLoadModule(SCE_SYSMODULE_RAZOR_CAPTURE);

    MultisampleMode = SCE_GXM_MULTISAMPLE_NONE;

    SceGxmInitializeParams gxmParams;
    memset(&gxmParams, 0, sizeof(SceGxmInitializeParams));
    gxmParams.flags							= 0;
    gxmParams.displayQueueMaxPendingCount	= 2;
    gxmParams.displayQueueCallback			= present;
    gxmParams.displayQueueCallbackDataSize	= sizeof(SceDisplayFrameBuf);
    gxmParams.parameterBufferSize			= SCE_GXM_DEFAULT_PARAMETER_BUFFER_SIZE;

    int result = sceGxmInitialize(&gxmParams);
    SF_ASSERT(result == SCE_OK);

    pMemManager = new NGP::MemoryManager(Memory::GetGlobalHeap(), 64<<20, 64<<20, 64<<20);

    memset(&ContextParams, 0, sizeof(SceGxmContextParams));

    ContextParams.hostMemSize = 32<<20;
    ContextParams.hostMem = SF_MEMALIGN(ContextParams.hostMemSize, 4096, Stat_Default_Mem);
    ContextParams.vdmRingBufferMemSize = SCE_GXM_DEFAULT_VDM_RING_BUFFER_SIZE;
    ContextParams.vertexRingBufferMemSize = SCE_GXM_DEFAULT_VERTEX_RING_BUFFER_SIZE;
    ContextParams.fragmentRingBufferMemSize = SCE_GXM_DEFAULT_FRAGMENT_RING_BUFFER_SIZE;
    ContextParams.fragmentUsseRingBufferMemSize = SCE_GXM_DEFAULT_FRAGMENT_USSE_RING_BUFFER_SIZE;
    ContextParams.vdmRingBufferMem = pMemManager->Alloc(ContextParams.vdmRingBufferMemSize, 16, Memory_NGP_MainUncached);
    ContextParams.vertexRingBufferMem = pMemManager->Alloc(ContextParams.vertexRingBufferMemSize, 16, Memory_NGP_MainUncached);
    ContextParams.fragmentRingBufferMem = pMemManager->Alloc(ContextParams.fragmentRingBufferMemSize, 16, Memory_NGP_MainUncached);
    ContextParams.fragmentUsseRingBufferMem = pMemManager->AllocUsse(ContextParams.fragmentUsseRingBufferMemSize, Memory_NGP_Fragment, 0,
        &ContextParams.fragmentUsseRingBufferOffset);
    result = sceGxmCreateContext(&ContextParams, &GxmCtx);
    SF_ASSERT(result == SCE_OK);

    for (int i = 0; i < FRAME_BUFFERS; i++)
    {
        DispBuffer[i] = pMemManager->Alloc(4*DISPLAY_PITCH * DISPLAY_HEIGHT, SCE_GXM_COLOR_SURFACE_ALIGNMENT, Memory_NGP_CDRAM);

         result = sceGxmColorSurfaceInit(&DispSurface[i], SCE_GXM_COLOR_FORMAT_A8B8G8R8, SCE_GXM_COLOR_SURFACE_LINEAR,
            MultisampleMode != SCE_GXM_MULTISAMPLE_NONE ? SCE_GXM_COLOR_SURFACE_SCALE_MSAA_DOWNSCALE : SCE_GXM_COLOR_SURFACE_SCALE_NONE,
            SCE_GXM_OUTPUT_REGISTER_SIZE_32BIT, DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_PITCH, DispBuffer[i]);
        SF_ASSERT(result == SCE_OK);


        sceGxmSyncObjectCreate(&DispSync[i]);
    }

    UPInt depthPitch = (DISPLAY_WIDTH + SCE_GXM_TILE_SIZEX - 1) & ~(SCE_GXM_TILE_SIZEX - 1);
	if (MultisampleMode == SCE_GXM_MULTISAMPLE_4X)
        depthPitch *= 2;
    UPInt depthSize = depthPitch * 4 * (DISPLAY_HEIGHT + SCE_GXM_TILE_SIZEY - 1) & ~SCE_GXM_TILE_SIZEY;
	if (MultisampleMode == SCE_GXM_MULTISAMPLE_2X)
        depthSize *= 2;
    DepthBuffer = pMemManager->Alloc(depthSize, SCE_GXM_DEPTHSTENCIL_SURFACE_ALIGNMENT, Memory_NGP_MainUncached);
    result = sceGxmDepthStencilSurfaceInit(&DepthSurface, SCE_GXM_DEPTH_STENCIL_FORMAT_S8D24, SCE_GXM_DEPTH_STENCIL_SURFACE_TILED,
        depthPitch, DepthBuffer, 0);
    SF_ASSERT(result == SCE_OK);

    sceGxmDepthStencilSurfaceSetForceStoreMode(&DepthSurface, SCE_GXM_DEPTH_STENCIL_FORCE_STORE_ENABLED);
    sceGxmDepthStencilSurfaceSetForceLoadMode(&DepthSurface, SCE_GXM_DEPTH_STENCIL_FORCE_LOAD_ENABLED);

    SceDisplayFrameBuf framebuf;
    memset(&framebuf, 0x00, sizeof(SceDisplayFrameBuf));
    framebuf.size        = sizeof(SceDisplayFrameBuf);
    framebuf.base        = DispBuffer[0];
    framebuf.pitch       = DISPLAY_PITCH;
    framebuf.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;
    framebuf.width       = DISPLAY_WIDTH;
    framebuf.height      = DISPLAY_HEIGHT;
    sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
    sceDisplayWaitSetFrameBuf();

    BackBuffer = 0;
    FrontBuffer = 1;

    memset(&RTParams, 0, sizeof(SceGxmRenderTargetParams));
    RTParams.flags				= 0;
    RTParams.width				= DISPLAY_WIDTH;
    RTParams.height				= DISPLAY_HEIGHT;
    RTParams.scenesPerFrame		= 8;
    RTParams.multisampleMode	= MultisampleMode;

    UInt32 gpuMemSize;
#if (SCE_PSP2_SDK_VERSION < 0x00996000)
    sceGxmGetRenderTargetMemSizes(&RTParams, &RTParams.hostMemSize, &gpuMemSize);
    RTParams.hostMem	    	= SF_ALLOC(RTParams.hostMemSize, Stat_Default_Mem);
#else
    sceGxmGetRenderTargetMemSize(&RTParams, &gpuMemSize);
#endif
    RTParams.driverMemBlock		= sceKernelAllocMemBlock("GFxMainRT", SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE, gpuMemSize, 0);

    result = sceGxmCreateRenderTarget(&RTParams, &RenderTarget);
    SF_ASSERT(result == SCE_OK);

    return 1;
}

#define GAMEPAD_DEADZONE 20

static float NormalizePadStick(int x)
{
    if (x > 128 + GAMEPAD_DEADZONE)
        return float(x - (127 + GAMEPAD_DEADZONE)) / float(128 - GAMEPAD_DEADZONE);
    else if (x < 128 - GAMEPAD_DEADZONE)
        return float(x - (128 - GAMEPAD_DEADZONE)) / float(128 - GAMEPAD_DEADZONE);
    else
        return 0;
}

// Map pad key values to our keycodes.

static Key::Code keymap[16] =
{
    Key::Space,  Key::None,     Key::None, Key::Return, Key::Up, Key::Right, Key::Down, Key::Left,
    Key::PageUp, Key::PageDown, Key::None, Key::None,   Key::T,  Key::O,     Key::X,    Key::S
};

// Message processing function to be called in the application loops.
bool FxPlayerTiny::ProcessMessages()
{
    SceCtrlData pad;

    if (sceCtrlReadBufferPositive(0, &pad, 1) > 0)
    {
        UInt64 msgtime = pad.timeStamp;
        float delta = (msgtime - Pad.pad.timeStamp) / 1000000.0f;
        int mbutton = -1;
        bool didrepeat = 0;

        for (int j = 0; j < 16; j++)
        {
            if ((Pad.pad.buttons & (1 << j)) != (pad.buttons & (1 << j))) {
                if (keymap[j] == Key::X)
                    mbutton = (pad.buttons & (1 << j)) ? 1 : 0;
                else
                {
                    if (keymap[j] == Key::Space && (pad.buttons & (1 << j)))
                        sceRazorCaptureSetTriggerNextFrame("host0:gfx.sgx");

                    OnPad(0, keymap[j], (pad.buttons & (1 << j)) ? 1 : 0);
                    Pad.RepeatDelay = 350000;
                    didrepeat = 1;
                }
            }
            else if ((Pad.pad.buttons & (1 << j)) && (pad.buttons & (1 << j))
                && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay
                && (keymap[j] != Key::X))
            {
                Pad.RepeatDelay = 100000;
                OnPad(0, keymap[j], 1);
                didrepeat = 1;
            }
        }

        bool curR = ((pad.lx & 0xF8) >= 192);
        bool oldR = ((Pad.pad.lx & 0xF8) >= 192);
        bool curL = ((pad.lx & 0xF8) <= 64);
        bool oldL = ((Pad.pad.lx & 0xF8) <= 64);
        bool curD = ((pad.ly & 0xF8) >= 192);
        bool oldD = ((Pad.pad.ly & 0xF8) >= 192);
        bool curU = ((pad.ly & 0xF8) <= 64);
        bool oldU = ((Pad.pad.ly & 0xF8) <= 64);

        Pad.nLStickLeft = Pad.nLStickRight = Pad.nLStickUp = Pad.nLStickDown = false;
        if (curR)
        {
            if (oldR && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //OnPad(k, Key::Right, 0);
                OnPad(0, Key::Right, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldL)
                OnPad(0, Key::Left, 0);
            if (oldL || !oldR)
            {
                OnPad(0, Key::Right, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickRight = true;
        }
        if (curL)
        {
            if (oldL && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //OnPad(k, Key::Left, 0);
                OnPad(0, Key::Left, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldR)
                OnPad(0, Key::Right, 0);
            if (oldR || !oldL)
            {
                OnPad(0, Key::Left, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickLeft = true;
        }
        if (curU)
        {
            if (oldU && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //OnPad(k, Key::Up, 0);
                OnPad(0, Key::Up, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldD)
                OnPad(0, Key::Down, 0);
            if (oldD || !oldU)
            {
                OnPad(0, Key::Up, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickUp = true;
        }
        if (curD)
        {
            if (oldD && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //OnPad(k, Key::Down, 0);
                OnPad(0, Key::Down, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldU)
                OnPad(0, Key::Up, 0);
            if (oldU || !oldD)
            {
                OnPad(0, Key::Down, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickDown = true;
        }

        if (Pad.LStickDown && !Pad.nLStickDown)
            OnPad(0, Key::Down, 0);

        if (Pad.LStickUp && !Pad.nLStickUp)
            OnPad(0, Key::Up, 0);

        if (Pad.LStickLeft && !Pad.nLStickLeft)
            OnPad(0, Key::Left, 0);

        if (Pad.LStickRight && !Pad.nLStickRight)
            OnPad(0, Key::Right, 0);

        Pad.LStickDown = Pad.nLStickDown;
        Pad.LStickLeft = Pad.nLStickLeft;
        Pad.LStickRight = Pad.nLStickRight;
        Pad.LStickUp = Pad.nLStickUp;

        float padlx = NormalizePadStick(pad.lx);
        float padly = NormalizePadStick(pad.ly);
        float padrx = NormalizePadStick(pad.rx);
        float padry = NormalizePadStick(pad.ry);
        if (padlx != Pad.LastLx || padly != Pad.LastLy)
        {
            OnPadStick(0, Pad_LT, padlx, padly);
            Pad.LastLx = padlx; Pad.LastLy = padly;
        }
        if (padrx != Pad.LastRx || padry != Pad.LastRy)
        {
            OnPadStick(0, Pad_RT, padrx, padry);
            Pad.LastRx = padrx; Pad.LastRy = padry;
        }

        if ((pad.rx & 0xF8) > 128 + GAMEPAD_DEADZONE)
            Pad.MouseXadj += (float(pad.rx & 0xF8) - 128.0f - GAMEPAD_DEADZONE) * 4.0f * delta;
        else if ((pad.rx & 0xF8) < 128 - GAMEPAD_DEADZONE)
            Pad.MouseXadj += (float(pad.rx & 0xF8) - 128.0f + GAMEPAD_DEADZONE) * 4.0f * delta;

        if ((pad.ry & 0xF8) > 128 + GAMEPAD_DEADZONE)
            Pad.MouseYadj += (float(pad.ry & 0xF8) - 128.0f - GAMEPAD_DEADZONE) * 4.0f * delta;
        else if ((pad.ry & 0xF8) < 128 - GAMEPAD_DEADZONE)
            Pad.MouseYadj += (float(pad.ry & 0xF8) - 128.0f + GAMEPAD_DEADZONE) * 4.0f * delta;

        Pad.pad = pad;

        if (fabs(Pad.MouseXadj) >= 1 || fabs(Pad.MouseYadj) >= 1) {
            Pad.MouseX += int(Pad.MouseXadj);
            Pad.MouseY += int(Pad.MouseYadj);
            Pad.MouseXadj -= int(Pad.MouseXadj);
            Pad.MouseYadj -= int(Pad.MouseYadj);
            if (Pad.MouseX < 0)
                Pad.MouseX = 0;
            if (Pad.MouseX >= int(Width))
                Pad.MouseX = Width;
            if (Pad.MouseY < 0)
                Pad.MouseY = 0;
            if (Pad.MouseY >= int(Height))
                Pad.MouseY = Height;

            OnMouseMove(0, Point<int>(Pad.MouseX, Pad.MouseY), 0);
        }
        if (mbutton != -1)
            OnMouseButton(0, 0, mbutton, Point<int>(Pad.MouseX, Pad.MouseY));

        Pad.LastMsgTime = msgtime;
        if (didrepeat)
            Pad.LastRepeatTime = msgtime;

        Pad.pad = pad;
    }

    SceTouchData touch1;
    if (sceTouchRead(SCE_TOUCH_PORT_FRONT, &touch1, 1) > 0)
    {
        if (touch1.reportNum == 1)
        {
            // Starting a swipe
            if (SwipeTouchX < 0 && SwipeTouchY < 0) 
            {
                SwipeTouchX = touch1.report->x;
                SwipeTouchY = touch1.report->y;
            }
            LastTouchX = touch1.report->x;
            LastTouchY = touch1.report->y;
        }
        else if (touch1.reportNum == 0) 
        {
            if (SwipeTouchX != -1) 
            {
                if (LastTouchX - SwipeTouchX > 500)
                {
                    OnGesture(GestureEvent::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(1, 0), PointF(0, 0), 0);
                }
                else if (LastTouchX - SwipeTouchX < 500)
                {
                    OnGesture(GestureEvent::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(-1, 0), PointF(0, 0), 0);
                }
                else if (LastTouchY - SwipeTouchY > 500)
                {
                    OnGesture(GestureEvent::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(0, 1), PointF(0, 0), 0);
                }
                else if (LastTouchY - SwipeTouchY < 500)
                {
                    OnGesture(GestureEvent::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(0, -1), PointF(0, 0), 0);    
                }           
                SwipeTouchX = -1;
            }
        }
        else
        {
            SwipeTouchX = -1;
        }

        for (int i = 0; i < touch1.reportNum; i++)
        {
            bool isMove = false;
            const SceTouchReport& pt = touch1.report[i];

            if (TouchPrimaryId < 0 && i == 0)
                TouchPrimaryId = pt.id;

            for (int j = 0; j < Touch.reportNum; j++)
                if (Touch.report[j].id == pt.id)
                {
                    Touch.report[j].id = 255;
                    isMove = true;
                    break;
                }

                Point<int> point (int(pt.x*0.5f), int(pt.y*0.5f));

                if (isMove)
                    OnTouchMove(pt.id, point, Point<int>(0,0), pt.id == TouchPrimaryId);
                else
                    OnTouchBegin(pt.id, point, Point<int>(0,0), pt.id == TouchPrimaryId);

                if (pt.id == TouchPrimaryId)
                {
                    if (isMove)
                        OnMouseMove(0, point, 0);
                    else
                        OnMouseButton(0, 0, 1, point);
                }
        }
        for (int i = 0; i < Touch.reportNum; i++)
            if (Touch.report[i].id < 255)
            {
                const SceTouchReport& pt = Touch.report[i];
                Point<int> point (int(pt.x*0.5f), int(pt.y*0.5f));

                OnTouchEnd(Touch.report[i].id, point, Point<int>(0,0), pt.id == TouchPrimaryId);
                if (pt.id == TouchPrimaryId)
                    OnMouseButton(0, 0, 0, point);
            }

            Touch = touch1;
            if (Touch.reportNum == 0)
                TouchPrimaryId = -1;
    }

    return 1;
}


// The main function implementation creates the FxPlayerTiny class,
// passes it the filename and calls Run. FxPlayerTiny::Run is responsible
// for all of the rendering setup and movie playback.
int main(int argc, char *argv[])
{
    GFx::System gfxInit;

    int result = 1;
    {
        bool verboseAction = false;
        FxPlayerTiny player(FXPLAYER_FILENAME, verboseAction);
        result = player.Run();
    }

    return result;
}
