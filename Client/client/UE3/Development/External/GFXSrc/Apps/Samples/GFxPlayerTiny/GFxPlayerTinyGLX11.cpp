/**************************************************************************

Filename    :   GFxPlayerTinyGLX11.cpp
Content     :   Tiny GFxPlayer sample for X11.
Created     :   March 27, 2008
Authors     :   Michael Antonov, Dmitry Polenur

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/


// GFx includes
#include "GFx_Kernel.h"
#include "GFx.h"
#include "Kernel/SF_File.h"

#include "Render/GL/GL_HAL.h"
#include "GFx/GFx_AS2Support.h"
#include "GFx/GFx_AS3Support.h"

#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/ImageFiles/DDS_ImageFile.h"
#include "Render/ImageFiles/JPEG_ImageFile.h"
#include "Render/ImageFiles/TGA_ImageFile.h"

#include "GFx/AS3/AS3_Global.h"

// System includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#undef None

namespace SF = Scaleform;
using namespace Scaleform;
using namespace Scaleform::Render;
using namespace Scaleform::GFx;

// SWF Filename we will load by default.
#define FXPLAYER_FILENAME   "Bin/Data/AS2/Samples/Window.swf"
// Window title to use for the application.
#define FXPLAYER_APP_TITLE  "Scaleform GFxPlayerTinyGLX11 v" GFX_VERSION_STRING


// ***** FxPlayerTiny Application Class

// FxPlayerTiny class encapsulates all of the system setup and GFxPlayer
// program state needed for playback. FxPlayerTiny is created in main() /
// WinMain() and contains most of the program logic in its Run function.

class FxPlayerTiny
{

    // Scaleform GFx object pointers.
    Ptr<MovieDef>       pMovieDef;
    Ptr<Movie>          pMovie;
    MovieDisplayHandle  hMovieDisplay;
    Ptr<GL::HAL>        pRenderHAL;
    Ptr<Renderer2D>     pRenderer;
    UInt32              MovieLastTime;

    // Toggle states.
    bool                    AAEnabled;
    bool                    Paused;         // Set when the movie is paused in the player.    
    bool                    Wireframe;
    bool                    QuitFlag;

    enum
    {
        WmProtocols = 0,
        WmDeleteWindow,
        NumAtoms
    };

    Display*    pDisp;
    Window      win;
    GLXContext  ctx;
    Atom        Atoms[NumAtoms];
    XVisualInfo*            pvis;

    // Playback filename and window size.
    String               FileName;
    int                     Width;
    int                     Height;
    int                     WWidth, WHeight;
    int                     WXpos, WYpos;

public:
    
    FxPlayerTiny(const char* pfilename);    
    ~FxPlayerTiny();

    // Initialize the player and run playback loop.
    int     Run();
    // Advance playback and render a frame.
    void    AdvanceAndDisplay();
    void    DisplayFrame();

    // Input handler functions. Process mouse and keyboard and pass 
    // appropriate GFxEvent notifications to GFxMovieView::HandleEvent.
    bool    ProcessMessages();
    void    KeyEvent(unsigned key, unsigned ch, unsigned info, bool down);
    void    OnKey(unsigned key, unsigned uchar, unsigned info, bool downFlag);
    void    OnMouse(GFx::Event::EventType eventType, unsigned button, int x, int y);

    // System window and rendering setup.
    bool    SetupWindow(const String& name); 
};


// A sample implementation of GFxFSCommandHandler. Users can install such a
// handler to receive notifications from fscommand() calls in ActionScript.
// Note that in many cases it is better to use GFxExternalInterface instead
// since it allows for better argument passing through ExternalInterface.call.
class FxPlayerFSCommandHandler : public FSCommandHandler
{
public:
    virtual void Callback(Movie* pmovie, const char* pcommand, const char* parg)
    {
        printf("Command: %s, Args: %s\n", pcommand, parg);
    }
};



// ***** FxPlayerTiny Class Implementation

FxPlayerTiny::FxPlayerTiny(const char* pfilename)
{
    AAEnabled       = 1;
    Paused          = 0;
    FileName        = pfilename;
    Wireframe       = 0;

    Width           = 800;
    Height          = 600;

    pDisp           = 0;
    ctx             = 0;
    win             = 0;
}

FxPlayerTiny::~FxPlayerTiny()
{

}


// File opener class.
class FxPlayerFileOpener : public FileOpener 
{
public:
    virtual File* OpenFile(const char *purl) 
    {
        return new SysFile(purl);
    }
};


// Called from main() after settings are initialized to execute
// most of the program logic. Responsible for setting up the window,
// loading movies and containing the playback/message loop.
int FxPlayerTiny::Run()
{
    if (!SetupWindow(String(FXPLAYER_APP_TITLE " ") + FileName))
        return 1;
   
    // Create and Configure GFxLoader.   
    Loader loader;

    // Developers set states on the loader to modify loading and playback behavior.
    // If you need to load files from a custom package, for example, you can 
    // create a GFxFileOpener derived class that loads files in a custom way.
    // Here GFxFileOpener and GFxFSCommandHandler are set for sample purposes.    
    Ptr<FileOpener> pfileOpener = *new FxPlayerFileOpener;
    loader.SetFileOpener(pfileOpener); 
    Ptr<FSCommandHandler> pcommandHandler = *new FxPlayerFSCommandHandler;
    loader.SetFSCommandHandler(pcommandHandler);

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

    
    Ptr<ASSupport> pAS2Support = *new GFx::AS2Support();
    loader.SetAS2Support(pAS2Support);

    Ptr<ASSupport> pASSupport = *new GFx::AS3Support();
    loader.SetAS3Support(pASSupport);


    pRenderHAL = *new Render::GL::HAL();

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.
    if (!pRenderHAL->InitHAL(GL::HALInitParams()))
        return 1;
    
    // Create renderer.
    if (!(pRenderer = *new Render::Renderer2D(pRenderHAL.GetPtr())))
        return 1;

    // Load the movie file and create its instance.
    if (!(pMovieDef = *loader.CreateMovie(FileName)))
        return 1; 
    
    if (!(pMovie = *pMovieDef->CreateInstance()))
        return 1;

    hMovieDisplay = pMovie->GetDisplayHandle();

    // Set playback view to span the entire window.
    pMovie->SetViewport(Width, Height, 0,0, Width, Height);

    // If you wanted to use the movie as a transparent HUD overlay, you would
    // set Background Alpha to 0. We don't need to do this for player sample.
    // pMovie->SetBackgroundAlpha(0.0f);

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


// Advances GFx animation and draws the scene.
void FxPlayerTiny::AdvanceAndDisplay()
{
    // Clear the back buffer to a black color.
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (pMovie)
    {
        // Set Wireframe
        glPolygonMode(GL_FRONT_AND_BACK, Wireframe ? GL_LINE : GL_FILL);

        UInt32  time    = Timer::GetTicks()/1000;
        float   delta   = ((float)(time - MovieLastTime)) / 1000.0f;

        // Advance time and display the movie.
        if (!Paused)
            pMovie->Advance(delta);

        DisplayFrame();

        MovieLastTime = time;
    }

    // Present the back buffer contents to the display. 
    glXSwapBuffers(pDisp, win);

    SF_AMP_CODE(AmpServer::GetInstance().AdvanceFrame());
}

void FxPlayerTiny::DisplayFrame()
{
    pRenderer->BeginFrame();
    if (hMovieDisplay.NextCapture(pRenderer->GetContextNotify()))
    {
        pRenderer->Display(hMovieDisplay);
    }
    pRenderer->EndFrame();
}


// OnKey handles system keys by first interpreting some Ctrl+Key combinations
// in a special way and passing the rest of them to the movie.
void    FxPlayerTiny::OnKey(unsigned keyCode, unsigned ch, unsigned mods, bool downFlag)
{
    if (!pMovie)
        return;

    bool    ctrl = (mods & ControlMask);

    if (keyCode == XK_Control_L || keyCode == XK_Control_R)
    {
        return;
    }

    if (ctrl && downFlag)
    {

        switch(keyCode)
        {
        case 'W':
            Wireframe = !Wireframe;
            break;

        case 'A':
            AAEnabled = ! AAEnabled;
            if (pMovie)
	    {
	        pMovie->SetEdgeAAMode(AAEnabled ?
				      Render::EdgeAA_On : Render::EdgeAA_Disable);
            }
            break;

        case 'P':
            Paused = !Paused;
            break;
        }
    }
    else
    { // if (!ctrl)

        // Inform the player about keystroke
        if (!ctrl)
            KeyEvent(keyCode, ch, mods, downFlag);
    }


}

// Helper used to convert key codes and route them to GFxPlayer
void    FxPlayerTiny::KeyEvent(unsigned key, unsigned uchar, unsigned mods, bool down)
{
    Key::Code    c((Key::Code)key);
    //AB, in the case key is not found in the table let give a chance to
    // plain key code, not just return Key::VoidSymbol;

    if (key < 127)
    {
        c = (Key::Code) ((key - 'A') + Key::A);
    }
    else if (key >= XK_F1 && key <= XK_F15)
    {
        c = (Key::Code) ((key - XK_F1) + Key::F1);
    }
    else
    {
        // many keys don't correlate, so just use a look-up table.
        static struct //!AB added static modifier
        {
            int         vk;
            Key::Code    gs;
        } table[] =
        {
            { XK_Return,    Key::Return },
            { XK_Escape,    Key::Escape },
            { XK_Left,      Key::Left },
            { XK_Right,     Key::Right },
            { XK_Up,        Key::Up },
            { XK_Down,      Key::Down },
            { XK_Delete,    Key::Delete },
            { XK_BackSpace, Key::Backspace },

            // @@ TODO fill this out some more
            { 0, Key::None }
        };

        for (int i = 0; table[i].vk != 0; i++)
        {
            if (key == (unsigned)table[i].vk)
            {
                c = table[i].gs;
                break;
            }
        }
    }

    if (c != Key::None)
    {
        if (pMovie)
        {
            if (uchar < 32)
                uchar = 0;
            GFx::KeyEvent event(down ? GFx::Event::KeyDown : KeyEvent::KeyUp, c,
                uchar <= 127 ? uchar : 0, uchar < 0xf700 ? uchar : 0);
            /*
            event.SpecialKeysState.SetShiftPressed((mods & ShiftMask) ? 1: 0);
            event.SpecialKeysState.SetCtrlPressed((mods & ControlMask) ? 1: 0);
            event.SpecialKeysState.SetAltPressed((mods & Mod1Mask) ? 1: 0);
            event.SpecialKeysState.SetNumToggled((mods & Mod2Mask) ? 1: 0);
            event.SpecialKeysState.SetCapsToggled((mods & LockMask) ? 1: 0);
            */
            pMovie->HandleEvent(event);
        }
    }
}

void    FxPlayerTiny::OnMouse(GFx::Event::EventType eventType, unsigned button, int x, int y)
{
    if (pMovie)
    {
        MouseEvent mevent(eventType, button, (float)x, (float)y);
        pMovie->HandleEvent(mevent);
    }
}

// Setup Application Window
bool FxPlayerTiny::SetupWindow(const String& name)
{
    if (!pDisp)
    {
        pDisp = XOpenDisplay(0);
        if (!pDisp)
        {
            printf("Cannot open display: %s\n", XDisplayName(0));
            return 0;
        }

        char *atoms[] = {"WM_PROTOCOLS", "WM_DELETE_WINDOW"};

        XInternAtoms(pDisp, atoms, NumAtoms, 0, Atoms);
    }

    if (!ctx)
    {
        int attr[] = {GLX_RGBA, GLX_DOUBLEBUFFER,
                      GLX_STENCIL_SIZE, 8,
                      GLX_DEPTH_SIZE, 16,
                      0};

        pvis = glXChooseVisual(pDisp, DefaultScreen(pDisp), attr);

        if (!pvis)
        {
            printf("glXChooseVisual failed\n");
            return 0;
        }
        ctx = glXCreateContext(pDisp, pvis, 0, 1);
    }

    XSetWindowAttributes winattr;
    winattr.event_mask = ButtonPressMask|ButtonReleaseMask|KeyPressMask|KeyReleaseMask|ButtonMotionMask|PointerMotionMask|
        PointerMotionHintMask|StructureNotifyMask;
    winattr.border_pixel = 0;
    winattr.colormap = XCreateColormap(pDisp, DefaultRootWindow(pDisp), pvis->visual, AllocNone);

    win = XCreateWindow(pDisp, DefaultRootWindow(pDisp), 100,100, Width, Height, 0, pvis->depth,
        InputOutput, pvis->visual, CWEventMask | CWBorderPixel | CWColormap, &winattr);

    XStoreName(pDisp, win, FXPLAYER_APP_TITLE);
    XSetWMProtocols(pDisp, win, &Atoms[WmDeleteWindow], 1);

    XSizeHints size;
    size.flags = PSize|PMinSize|PMaxSize;
    size.x = size.y = 100;
    size.width = size.min_width = size.max_width = Width;
    size.height = size.min_height = size.max_height = Height;
    XSetNormalHints(pDisp, win, &size);

    XMapRaised(pDisp, win);

    glXMakeCurrent(pDisp, win, ctx);

    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);

    return 1;
}

static const int mousebuttons[5] = {0, 2, 1, 3, 4};

// Message processing function to be called in the 
// application loops.
bool FxPlayerTiny::ProcessMessages()
{
    while (XPending(pDisp))
    {
        XEvent event;

        XNextEvent(pDisp, &event);

        switch (event.type)
        {
        case ButtonPress:
            OnMouse(GFx::Event::MouseDown, mousebuttons[event.xbutton.button-1], event.xbutton.x, event.xbutton.y);
            break;
        case ButtonRelease:
            OnMouse(GFx::Event::MouseUp, mousebuttons[event.xbutton.button-1], event.xbutton.x, event.xbutton.y);
            break;

        case MotionNotify:
            {
                while (XCheckTypedWindowEvent(pDisp, event.xmotion.window, MotionNotify, &event));
                Window rw, cw;
                int rx, ry, x, y;
                unsigned mods;
                if (XQueryPointer(pDisp, win, &rw, &cw, &rx, &ry, &x, &y, &mods))
                    OnMouse(GFx::Event::MouseMove, 0, event.xmotion.x, event.xmotion.y);
            }
            break;

        case KeyPress:
        case KeyRelease:
            {
                char chars[16];
                KeySym code;
                int n = XLookupString(&event.xkey, chars, sizeof(chars)-1, &code, 0);

                if (code >= 'a' && code <= 'z')
                    code += ('A' - 'a');

                for (int i = 0; i < n; i++)
                    OnKey(code, chars[i], event.xkey.state, event.type == KeyPress);
                if (n == 0)
                    OnKey(code, 0, event.xkey.state, event.type == KeyPress);
            }
            break;

        case ConfigureNotify:
            WWidth = event.xconfigure.width;
            WHeight = event.xconfigure.height;
            WXpos = event.xconfigure.x;
            WYpos = event.xconfigure.y;
            break;

        case ClientMessage:
            if (event.xclient.message_type == Atoms[WmProtocols] &&
                Atom(event.xclient.data.l[0]) == Atoms[WmDeleteWindow])
                QuitFlag = 1;
            break;
        }
    }

    return !QuitFlag;
}


// ***** main() -  Application entry point.

// The main function implementation creates the FxPlayerTiny class,
// passes it the filename and calls Run. FxPlayerTiny::Run is responsible
// for all of the rendering setup and movie playback.

int main(int argc, char *argv[])
{
    GFx::System gfxInit;

    int result = 1;
    {  
        FxPlayerTiny player(argc >= 2 ? argv[1] : FXPLAYER_FILENAME);   
        result = player.Run();
    }

    return result;
}
