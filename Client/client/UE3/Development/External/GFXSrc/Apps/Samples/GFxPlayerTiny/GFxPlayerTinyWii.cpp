/**************************************************************************

Filename    :   GFxPlayerTinyWii.cpp
Content     :   Tiny GFxPlayer sample for Wii.
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
#include "Render/Wii/Wii_MemoryManager.h"
#include "Render/Wii/Wii_HAL.h"

#include "Render/ImageFiles/JPEG_ImageFile.h"
#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/ImageFiles/TGA_ImageFile.h"

#include "GFx/AS3/AS3_Global.h"

// Wii includes
#include <revolution.h>
#include <revolution/mem.h>
#include <revolution/kpad.h>

// SWF filename we will load by default.
#define FXPLAYER_FILENAME   "FxPlayer/ScaleformLogo.swf"
// Window title to use for the application.
#define FXPLAYER_APP_TITLE  "Scaleform GFxPlayerTinyWii v" GFX_VERSION_STRING

namespace SF = Scaleform;
using namespace Scaleform;
using namespace Render;
using namespace GFx;

#define VK_RETURN '\n'
#define VK_ESCAPE 257
#define VK_LEFT   258
#define VK_RIGHT  259
#define VK_UP     260
#define VK_DOWN   261

#define GX_FIFO_SIZE (256 * 1024)

static void *mem2alloc(unsigned long size) { return SF_ALLOC(size, Stat_Default_Mem); }
static u8    mem2free(void *ptr)           { SF_FREE(ptr); return 1; }


// ***** FxPlayerTiny Application Class

// FxPlayerTiny class encapsulates all of the system setup and GFxPlayer
// program state needed for playback. FxPlayerTiny is created in main() /
// WinMain() and contains most of the program logic in its Run function.

class FxPlayerTiny
{
    GXRenderModeObj*    pRmode;
    GXRenderModeObj     Rmode;
    GXFifoObj*          pGXFifo;
    void*               pGXFifoBuf;
    UPInt               FBSize;
    static Wii::MemoryManager* pMemManager;

    // Frame buffers
    void*   pFB[2];
    int     CurFb;

    // Scaleform GFx object pointers.
    Ptr<MovieDef>           pMovieDef;
    Ptr<Movie>              pMovie;
	Ptr<Render::Wii::HAL>   pRenderHAL;
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
    void    OnKey(unsigned keyCode, bool downFlag);
    void    OnMouse(GFx::Event::EventType eventType, unsigned button, int x, int y);
    void    OnMouseMove(int x, int y);
    void    OnMouseButton(unsigned button, bool downFlag, int x, int y);
    void    HandleKeyEvent(unsigned keyCode, bool downFlag);
   
    // System window and rendering setup.
    bool    SetupWindow(const String& name);

    static void InitMemoryManager(void* mem1Start, void* mem1End)
    {
        pMemManager = new Wii::MemoryManager(Memory::GetGlobalHeap(), mem1Start, mem1End);
        SF_ASSERT(pMemManager);
    }
};

Wii::MemoryManager* FxPlayerTiny::pMemManager;


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
}

FxPlayerTiny::~FxPlayerTiny() {}


// Called from main()/WinMain() after settings are initialized to execute
// most of the program logic. Responsible for setting up the window,
// loading movies and containing the playback/message loop.
int FxPlayerTiny::Run()
{    
    if (!SetupWindow(String(FXPLAYER_APP_TITLE " ") + FileName))
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

	pRenderHAL = *new Render::Wii::HAL();

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.    
    if (!pRenderHAL->InitHAL(Wii::HALInitParams(pRmode, new Wii::RenderSync_DrawDone(), pMemManager)))
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
    // Set viewport for next frame; it may depend on the TV mode
    if (pRmode->field_rendering)
        GXSetViewportJitter(
            0.0F, 0.0F, (float)pRmode->fbWidth, (float)pRmode->efbHeight,
            0.0F, 1.0F, VIGetNextField());
    else
        GXSetViewport(
            0.0F, 0.0F, (float)pRmode->fbWidth, (float)pRmode->efbHeight,
            0.0F, 1.0F);

    GXInvalidateVtxCache();
    GXInvalidateTexAll();

    // Clear the frame buffer to black.
    GXColor prgba;

    prgba.a = 0xFF;
    prgba.r = 0;
    prgba.g = 0;
    prgba.b = 0;

    GXSetCopyClear(prgba, GX_MAX_Z24);
    GXCopyDisp(pFB[CurFb], GX_TRUE);

    // GFx rendering    
    if (pMovie)
    {
        UInt32 time  = Timer::GetTicks() / 1000;
        float  delta = ((float)(time - MovieLastTime)) / 1000.0f;

        // Advance time and display the movie.
        if (!Paused)
            pMovie->Advance(delta);

        Display();

        // Display frame buffer & swap
        VISetNextFrameBuffer(pFB[CurFb]);
        VISetBlack(0);
        VIFlush();
        VIWaitForRetrace();
        CurFb = !CurFb;

        MovieLastTime = time;
    }
    SF_AMP_CODE(AmpServer::GetInstance().AdvanceFrame());
}

void FxPlayerTiny::Display()
{
    SF_AMP_SCOPE_RENDER_TIMER_ID("FxPlayerTiny::Display", Amp_Native_Function_Id_Display);

    pRenderer->BeginFrame();

    if (hMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
        pRenderer->Display(hMovieDisplay);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXCopyDisp(pFB[CurFb], GX_TRUE);
    GXDrawDone();

    pRenderer->EndFrame();
}


// Helper function that converts Windows VK keyCode values to GFxKeyEvents
// and routes them to GFxPlayer.
void FxPlayerTiny::HandleKeyEvent(unsigned keyCode, bool downFlag)
{
    Key::Code key(Key::None);
    {
        // Use a look-up table for keys don't correlate in order,.
        static struct
        {
            int       vk;
            Key::Code gs;
        }
        table[] =
        {
            { VK_RETURN,    Key::Return },
            { VK_ESCAPE,    Key::Escape },
            { VK_LEFT,      Key::Left },
            { VK_UP,        Key::Up },
            { VK_RIGHT,     Key::Right },
            { VK_DOWN,      Key::Down },

            // TODO: fill this out some more
            { 0, Key::None }
        };

        for (int i = 0; table[i].vk != 0; i++)
        {
            if (keyCode == (unsigned)table[i].vk)
            {
                key = table[i].gs;
                break;
            }
        }
    }

    if (key != Key::None)
    {
        if (pMovie)
        {
            // Pass Key events to the movie so that can be handled in ActionScript.
            KeyEvent event(downFlag ? GFx::Event::KeyDown : KeyEvent::KeyUp, key);
            pMovie->HandleEvent(event);
        }
    }
}

// OnKey handles system keys by first interpreting some Ctrl+Key combinations
// in a special way and passing the rest of them to the movie.
void FxPlayerTiny::OnKey(unsigned keyCode, bool downFlag)
{
    if (!pMovie)
        return;

    switch (keyCode)
    {
    case VK_LEFT:
    case VK_RIGHT:
    case VK_UP:
    case VK_DOWN:
        HandleKeyEvent(keyCode, downFlag);
        return;
    case 'A':
        HandleKeyEvent(VK_RETURN, downFlag);
        return;
    case 'B':
        HandleKeyEvent(VK_ESCAPE, downFlag);
        return;
    }

    if (!downFlag)
        return;

    switch (keyCode)
    {
    case '2':
        AAEnabled = ! AAEnabled;
        // TODO: add AA enable/disable
        break;
    case 'H':
        Paused = !Paused;
        break;
    }
}

void FxPlayerTiny::OnMouse(GFx::Event::EventType eventType, unsigned button, int x, int y)
{
    if (pMovie)
    {
        MouseEvent mevent(eventType, button, (float)x, (float)y);
        pMovie->HandleEvent(mevent);
    }
}

void FxPlayerTiny::OnMouseMove(int x, int y)
{
    if (pMovie)
    {
        MouseEvent event(GFx::Event::MouseMove, 0, (float)x, (float)y, 0.0f);
        pMovie->HandleEvent(event);
    }
}

void FxPlayerTiny::OnMouseButton(unsigned button, bool downFlag, int x, int y)
{
    if (!pMovie)
        return;

    if (downFlag)
    {
        MouseEvent event(GFx::Event::MouseDown, button, (float)x, (float)y, 0.0f);
        pMovie->HandleEvent(event);
    }
    else
    {        
        MouseEvent event(GFx::Event::MouseUp, button, (float)x, (float)y, 0.0f);
        pMovie->HandleEvent(event);
    }
}

// Setup Application Window and initialize Direct3D.
bool FxPlayerTiny::SetupWindow(const String& name)
{
    pGXFifoBuf = pMemManager->Alloc(GX_FIFO_SIZE, 32, Memory_Wii_MEM1);
    pGXFifo = GXInit(pGXFifoBuf, GX_FIFO_SIZE);

    bool isdtv = VIGetDTVStatus();
    UInt32 tvf = VIGetTvFormat();
    UInt32 tvm = VIGetScanMode();

    switch (tvf)
    {
    case VI_NTSC:
        pRmode = isdtv ? &GXNtsc480Prog : &GXNtsc480IntDf;
        break;
    case VI_PAL:
        pRmode = &GXPal528IntDf;
        break;
    case VI_EURGB60:
        pRmode = isdtv ? &GXEurgb60Hz480Prog : &GXEurgb60Hz480IntDf;
        break;
    case VI_MPAL:
        pRmode = isdtv ? &GXMpal480Prog : &GXMpal480IntDf;
        break;
    default:
        OSHalt("unknown TV format\n");
        break;
    }

    GXAdjustForOverscan(pRmode, &Rmode, 0, 16);
    pRmode = &Rmode;

    FBSize = VIPadFrameBufferWidth(pRmode->fbWidth) * pRmode->xfbHeight * VI_DISPLAY_PIX_SZ;
    pFB[0] = pMemManager->Alloc(FBSize, 32, Memory_Wii_MEM1);
    pFB[1] = pMemManager->Alloc(FBSize, 32, Memory_Wii_MEM1);
    CurFb = 0;

    VIConfigure(pRmode);
    VISetBlack(1);
    VISetNextFrameBuffer(pFB[0]);
    VIFlush();
    VIWaitForRetrace();
    if (pRmode->viTVmode & 3 != tvm || tvm == VI_INTERLACE)
        VIWaitForRetrace();

    GXSetViewport(0, 0, pRmode->fbWidth, pRmode->efbHeight, 0, 1.0f);
    GXSetScissor(0, 0, pRmode->fbWidth, pRmode->efbHeight);

    float yScale = GXGetYScaleFactor(pRmode->efbHeight, pRmode->xfbHeight);
    int xfbHeight = GXSetDispCopyYScale(yScale);
    GXSetDispCopySrc(0, 0, pRmode->fbWidth, pRmode->efbHeight);
    GXSetDispCopyDst(pRmode->fbWidth, xfbHeight);
    GXSetCopyFilter(pRmode->aa, pRmode->sample_pattern, GX_TRUE, pRmode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);

    if (pRmode->aa)
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    else
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);

    GXCopyDisp(pFB[1], GX_TRUE);

    Width  = pRmode->fbWidth;
    Height = pRmode->efbHeight;

    WPADRegisterAllocator(mem2alloc, mem2free);
    KPADInit();

    return 1;
}

// Map pad key values to our keycodes.
static int keymap[13][2] = {
    {KPAD_BUTTON_LEFT, VK_LEFT}, {KPAD_BUTTON_RIGHT, VK_RIGHT},
    {KPAD_BUTTON_UP, VK_UP}, {KPAD_BUTTON_DOWN, VK_DOWN},
    {KPAD_BUTTON_PLUS, '+'}, {KPAD_BUTTON_MINUS, '-'},
    {KPAD_BUTTON_A, 'A'}, {KPAD_BUTTON_B, 'B'},
    {KPAD_BUTTON_1, '1'}, {KPAD_BUTTON_2, '2'},
	{KPAD_BUTTON_HOME, 'H'}, {KPAD_BUTTON_C, 'C'}, {KPAD_BUTTON_Z, 'Z'}
};

// Message processing function to be called in the application loops.
bool FxPlayerTiny::ProcessMessages()
{
    KPADStatus kpad[KPAD_MAX_READ_BUFS];

    unsigned n = KPADRead(0, kpad, KPAD_MAX_READ_BUFS);
    if (n > 0)
    {
        int mx = Width  * 0.5f + kpad[0].pos.x * Width  * 0.50f;
        int my = Height * 0.5f + kpad[0].pos.y * Height * 0.50f;

        if (MouseX != mx || MouseY != my)
        {
            MouseX = mx;
            MouseY = my;
            OnMouseMove(MouseX, MouseY);
        }

        for (int i = 0; i < 13; i++)
            if (kpad[0].trig & keymap[i][0])
                OnKey(keymap[i][1], 1);
            else if (kpad[0].release & keymap[i][0])
                OnKey(keymap[i][1], 0);

        if (kpad[0].trig & KPAD_BUTTON_A)
            OnMouseButton(0, 1, MouseX, MouseY);
        else if (kpad[0].release & KPAD_BUTTON_A)
            OnMouseButton(0, 0, MouseX, MouseY);
    }

    return 1;
}


// The main function implementation creates the FxPlayerTiny class,
// passes it the filename and calls Run. FxPlayerTiny::Run is responsible
// for all of the rendering setup and movie playback.
int SF_CDECL main(int argc, char *argv[])
{
    SF::GFx::System gfxInit;

    UPInt size = 14 << 20;
    UByte *m1arenaLo = (UByte*) OSGetMEM1ArenaLo();
    UByte *m1arenaHi = (UByte*) OSGetMEM1ArenaHi();

    FxPlayerTiny::InitMemoryManager(m1arenaLo, m1arenaLo + size);

    m1arenaLo += size;
    m1arenaLo = (UByte*)OSInitAlloc(m1arenaLo, m1arenaHi, 1);
    OSSetCurrentHeap(OSCreateHeap((void*)OSRoundUp32B(m1arenaLo), (void*)OSRoundDown32B(m1arenaHi)));
    OSSetMEM1ArenaLo(m1arenaHi);

    DVDInit();
    VIInit();

    int result = 1;
    {
        bool verboseAction = false;
        FxPlayerTiny player(FXPLAYER_FILENAME, verboseAction);
        result = player.Run();
    }

    return result;
}
