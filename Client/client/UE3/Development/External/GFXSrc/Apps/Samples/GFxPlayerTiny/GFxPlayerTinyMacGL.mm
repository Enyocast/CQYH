/**********************************************************************

Filename    :   GFxPlayerTinyMacGL.mm
Content     :   Tiny GFxPlayer sample for Playstattion Portable.
Created     :   March 27, 2008
Authors     :   Michael Antonov, Dmitry Polenur

Copyright   :   (c) 2001-2008 Scaleform Corp. All Rights Reserved.

Licensees may use this file in accordance with the valid Scaleform
Commercial License Agreement provided with the software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

***********************************************************************

--- GFxPlayerTiny Description ---

GFxPlayerTiny is the simplest possible GFx player implementation
provided for each target platform. The player loads a single specified
file (or "Window.swf" by default) and plays it back while handling
input. Developers should go through this sample in detail before
performing engine integration.

The sample illustrates the following concepts:
  - Performing minimal system ainitialization required
    for running GFx.
  - Creating GRendererOGL and configuring it to work with
    a pre-configured video mode.    
  - Initializing GFxLoader with renderer and other settings and
    using it to load a SWF/GFX file into a GFxMovieDef.
  - Creating a movie instance (GFxMovieView) from GFxMovieDef.
  - Playing back the movie by calling Advance and Display every frame.
  - Feeding mouse/keyboard events to the movie by calling HandleEvent.
  - Handling player-generated events by installing GFxFSCommandHandler.

**********************************************************************/


// GFx includes
#include "GFile.h"
#include "GFxPlayer.h"
#include "GFxLoader.h"
#include "GTypes.h"
#include "GSysFile.h"

#include "GTimer.h"
#include "GFxRenderConfig.h"
#include "GRendererOGL.h"

#include "GFx/AS3/AS3_Global.h"

// System includes
#define UInt32 UInt32Mac
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#undef UInt32


@class GNSView;
#define OGLMACAPP_IMPL

#define XK_Escape    0x10001
#define XK_Control_L 0x10002
#define XK_Control_R 0x10003
#define XK_Shift_L   0x10004
#define XK_Shift_R   0x10005
#define XK_Alt_L     0x10006
#define XK_Alt_R     0x10007

#define ShiftMask    (1<<17)
#define ControlMask  (1<<18)
#define Mod1Mask     (1<<19)
#define Mod2Mask     (1<<21)
#define LockMask     (1<<16)


// Video mode
#define  APP_COLOR_BITS         32
#define  APP_DEPTH_BITS         24
#define  APP_STENCIL_BITS       8
#define  APP_ACCUM_BITS         0


// SWF Filename we will load by default.
#define FXPLAYER_FILENAME   "Contents/Window.swf"
// Window title to use for the application.
#define FXPLAYER_APP_TITLE  "Scaleform GFxPlayerTinyMacGL v" GFC_FX_VERSION_STRING


// ***** FxPlayerTiny Application Class

// FxPlayerTiny class encapsulates all of the system setup and GFxPlayer
// program state needed for playback. FxPlayerTiny is created in main() 
// and contains most of the program logic in its Run function.


class FxPlayerTiny
{
public:
    // Scaleform GFx object pointers.
    GPtr<GFxMovieDef>       pMovieDef;
    GPtr<GFxMovieView>      pMovie;
    GPtr<GRendererOGL>      pRenderer;
    GPtr<GFxRenderConfig>   pRenderConfig;
    UInt32                  MovieLastTime;

    // Toggle states.
    bool                    AAEnabled;
    bool                    Paused;         // Set when the movie is paused in the player.    
    bool                    QuitFlag;
    bool                    Wireframe;


#ifdef OGLMACAPP_IMPL
    NSCursor*   pCursor;
    GNSView*    view;
    NSWindow*        win;
    NSOpenGLContext* ctx;
    NSDate*          distantPast;
#else
    void* dummy[5];
#endif

    int         Modifiers;

    // Playback filename and window size.
    GString               FileName;
    int                     Width;
    int                     Height;

public:
    
    FxPlayerTiny(const char* pfilename);    
    virtual ~FxPlayerTiny();

    // Initialize the player and run playback loop.
    int     Run();
    // Advance playback and render a frame.
    void    AdvanceAndDisplay();

    // Input handler functions. Process mouse and keyboard and pass 
    // appropriate GFxEvent notifications to GFxMovieView::HandleEvent.
    bool    ProcessMessages();
    void            KeyEvent(UInt key, UInt ch, UInt info, bool down);
    virtual void    OnKey(UInt key, UInt uchar, UInt info, bool downFlag);
    void            OnMouse(GFxEvent::EventType eventType, UInt button, SInt x, SInt y);

    char *          GetAppPath();

    // System window and rendering setup.
    bool    SetupWindow(const GString& name); 
};


// A sample implementation of GFxFSCommandHandler. Users can install such a
// handler to receive notifications from fscommand() calls in ActionScript.
// Note that in many cases it is better to use GFxExternalInterface instead
// since it allows for better argument passing through ExternalInterface.call.
class FxPlayerFSCommandHandler : public GFxFSCommandHandler
{
public:
    virtual void Callback(GFxMovieView* pmovie, const char* pcommand, const char* parg)
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
    QuitFlag        = 0;

    Width           = 800;
    Height          = 600;

    Modifiers = 0;
    distantPast = [NSDate distantPast];
}

FxPlayerTiny::~FxPlayerTiny()
{
     [distantPast release];
}

@interface GNSApp : NSApplication
{
    NSRunLoop         *loop;
    FxPlayerTiny      *pApp;
}
-(void) beginEvents;
-(void) endEvents;
-(void) setApp: (FxPlayerTiny *) app;
@end

@implementation GNSApp
-(void) beginEvents
{
    loop = [[NSRunLoop currentRunLoop] retain];
    [self finishLaunching];
    _running = 1;
};
-(void) endEvents
{
    [loop release];
};
-(void) setApp:(FxPlayerTiny *) app
{
    pApp = app;
}
-(void) terminate:(id) sender
{
    pApp->QuitFlag = 1;
}
@end

@interface GNSView : NSOpenGLView
{
    FxPlayerTiny* pWin;
    NSCursor*     pCursor;
}
-(void) setWin:(FxPlayerTiny *) app;
@end

@implementation GNSView
-(void) setWin:(FxPlayerTiny *) app
{
    pWin = app;
}

static void keyEvent(FxPlayerTiny *pWin, NSEvent *event, int down)
{
    NSString *chars = [event characters];
    NSString *codes = [event charactersIgnoringModifiers];
    int mods = [event modifierFlags];

    if ([chars length] == 1)
    {
        int key = [codes characterAtIndex:0];
        int code = [event keyCode];
        switch (code)
        {
        case 0x35: key = XK_Escape; break;
        case 0x38: case 0x3c: key = XK_Shift_L; break;
        case 0x3b: case 0x3e: key = XK_Control_L; break;
        case 0x3a: case 0x3d: key = XK_Alt_L; break;
        }

        if (key >= 'a' && key <= 'z')
            key += 'A' - 'a';
        pWin->OnKey(key, [chars characterAtIndex:0], mods, down);
    }
    else
        for (unsigned int i = 0; i < [chars length]; i++)
        {
            int key = [chars characterAtIndex:0];
            if (key >= 'a' && key <= 'z')
                key += 'A' - 'a';
            pWin->OnKey(key, [chars characterAtIndex:0], mods, down);
        }
}

-(void) keyDown:(NSEvent *)event { keyEvent(pWin,event, 1); }
-(void) keyUp:(NSEvent *)event { keyEvent(pWin,event,0); }
-(void) flagsChanged:(NSEvent *)event
{
    int mods = [event modifierFlags];
    if (mods != pWin->Modifiers)
    {
        if ((mods & (1<<17)) != (pWin->Modifiers & (1<<17)))
            pWin->OnKey(XK_Shift_L, 0, mods, mods & (1<<17));
        if ((mods & (1<<18)) != (pWin->Modifiers & (1<<18)))
            pWin->OnKey(XK_Control_L, 0, mods, mods & (1<<18));
        if ((mods & (1<<19)) != (pWin->Modifiers & (1<<19)))
            pWin->OnKey(XK_Alt_L, 0, mods, mods & (1<<19));
    }
    pWin->Modifiers = mods;
}

-(void) mouseDown:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        pWin->OnMouse(GFxEvent::MouseDown, [event buttonNumber], int(pt.x), int([self bounds].size.height-pt.y));
    }
}
-(void) mouseUp:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        pWin->OnMouse(GFxEvent::MouseUp, [event buttonNumber], int(pt.x), int([self bounds].size.height-pt.y));
    }
}
-(void) rightMouseDown:(NSEvent *)event { [self mouseDown:event]; }
-(void) otherMouseDown:(NSEvent *)event { [self mouseDown:event]; }
-(void) rightMouseUp:(NSEvent *)event { [self mouseUp:event]; }
-(void) otherMouseUp:(NSEvent *)event { [self mouseUp:event]; }
-(void) mouseMoved:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        pWin->OnMouse(GFxEvent::MouseMove, 0, int(pt.x), int([self bounds].size.height-pt.y));
    }
}
-(void) mouseDragged:(NSEvent *)event { [self mouseMoved:event]; }
-(void) rightMouseDragged:(NSEvent *)event { [self mouseMoved:event]; }
-(void) otherMouseDragged:(NSEvent *)event { [self mouseMoved:event]; }

-(void) resetCursorRects
{
    [self addCursorRect:[self visibleRect] cursor:pCursor];
}

-(BOOL) windowShouldClose:(id)sender
{
    pWin->QuitFlag = 1;
    return NO;
}

@end


static bool InitApplication(FxPlayerTiny *app)
{
    NSApp = [GNSApp sharedApplication];
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [NSApp setApp:app];
    [NSApp setDelegate:NSApp];
    [NSBundle loadNibNamed:@"MainMenu" owner:NSApp];
    [NSApp beginEvents];
    [pool release];

    return 1;
}


char* FxPlayerTiny::GetAppPath()
{
    if (!NSApp)
        InitApplication(this);

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    char *out = strdup([[[NSBundle mainBundle] bundlePath] UTF8String]);
    [pool release];
    return out;
}


// File opener class.
class FxPlayerFileOpener : public GFxFileOpener 
{
public:
    virtual GFile* OpenFile(const char *purl) 
    {
        return new GSysFile(purl);
    }
};


// Called from main() after settings are initialized to execute
// most of the program logic. Responsible for setting up the window,
// loading movies and containing the playback/message loop.
int FxPlayerTiny::Run()
{
    if (!SetupWindow(GString(FXPLAYER_APP_TITLE " ") + FileName))
        return 1;
   
    // Create and Configure GFxLoader.   
    GFxLoader loader;

    // Developers set states on the loader to modify loading and playback behavior.
    // If you need to load files from a custom package, for example, you can 
    // create a GFxFileOpener derived class that loads files in a custom way.
    // Here GFxFileOpener and GFxFSCommandHandler are set for sample purposes.    
    GPtr<GFxFileOpener> pfileOpener = *new FxPlayerFileOpener;
    loader.SetFileOpener(pfileOpener); 
    GPtr<GFxFSCommandHandler> pcommandHandler = *new FxPlayerFSCommandHandler;
    loader.SetFSCommandHandler(pcommandHandler);

     // Create renderer.
    if (!(pRenderer = *GRendererOGL::CreateRenderer()))
        return 1;

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.
    if (!pRenderer->InitHAL(GL::HALInitParams()))
        return 1;
    
    // Set renderer on loader so that it is also applied to all children.
    pRenderConfig = *new GFxRenderConfig(pRenderer, GFxRenderConfig::RF_EdgeAA);
    loader.SetRenderConfig(pRenderConfig);

    // Load the movie file and create its instance.
    if (!(pMovieDef = *loader.CreateMovie(FileName)))
        return 1; 
    
    if (!(pMovie = *pMovieDef->CreateInstance()))
        return 1;

    // Set playback view to span the entire window.
    pMovie->SetViewport(Width, Height, 0,0, Width, Height);

    // If you wanted to use the movie as a transparent HUD overlay, you would
    // set Background Alpha to 0. We don't need to do this for player sample.
    // pMovie->SetBackgroundAlpha(0.0f);

    // Store initial timing, so that we can determine
    // how much to advance Flash playback.
    MovieLastTime = GTimer::GetTicks()/1000;

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

    // *** GFx Rendering    
    if (pMovie)
    {
        // Set Wireframe
        glPolygonMode(GL_FRONT_AND_BACK, Wireframe ? GL_LINE : GL_FILL);

        UInt32  time    = GTimer::GetTicks()/1000;
        Float   delta   = ((Float)(time - MovieLastTime)) / 1000.0f;

        // Advance time and display the movie.
        if (!Paused)
            pMovie->Advance(delta);
        pMovie->Display();

        MovieLastTime = time;
    }

    // Present the back buffer contents to the display. 
    [ctx flushBuffer];
}


// OnKey handles system keys by first interpreting some Ctrl+Key combinations
// in a special way and passing the rest of them to the movie.
void    FxPlayerTiny::OnKey(UInt keyCode, UInt ch, UInt mods, bool downFlag)
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
            {
                UInt32 rendererFlags = pRenderConfig->GetRenderFlags() &
                    ~GFxRenderConfig::RF_EdgeAA;
                if (AAEnabled)
                    rendererFlags |= GFxRenderConfig::RF_EdgeAA;
                pRenderConfig->SetRenderFlags(rendererFlags);
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
void    FxPlayerTiny::KeyEvent(UInt key, UInt uchar, UInt mods, bool down)
{
    GFxKey::Code    c((GFxKey::Code)key);
    //AB, in the case key is not found in the table let give a chance to
    // plain key code, not just return GFxKey::VoidSymbol;

    if (key < 127)
    {
        c = (GFxKey::Code) ((key - 'A') + GFxKey::A);
    }
    else if (key >= NSF1FunctionKey && key <= NSF15FunctionKey)
    {
        c = (GFxKey::Code) ((key - NSF1FunctionKey) + GFxKey::F1);
    }
    else
    {
        // many keys don't correlate, so just use a look-up table.
        static struct //!AB added static modifier
        {
            wchar_t         vk;
            GFxKey::Code    gs;
        } table[] =
        {
            {127,                       GFxKey::Backspace},
            {L'\t',                     GFxKey::Tab},
            {L'\r',                     GFxKey::Return},
            {L' ',                      GFxKey::Space},
            {NSPageUpFunctionKey,       GFxKey::PageUp},
            {NSPageDownFunctionKey,     GFxKey::PageDown},
            {NSEndFunctionKey,          GFxKey::End},
            {NSHomeFunctionKey,         GFxKey::Home},
            {NSLeftArrowFunctionKey,    GFxKey::Left},
            {NSUpArrowFunctionKey,      GFxKey::Up},
            {NSRightArrowFunctionKey,   GFxKey::Right},
            {NSDownArrowFunctionKey,    GFxKey::Down},
            {NSInsertFunctionKey,       GFxKey::Insert},
            {NSDeleteFunctionKey,       GFxKey::Delete},
            {NSHelpFunctionKey,         GFxKey::Help},
            {NSScrollLockFunctionKey,   GFxKey::ScrollLock},
            {L';',            GFxKey::Semicolon},
            {L'=',            GFxKey::Equal},
            {L',',            GFxKey::Comma},
            {L'-',            GFxKey::Minus},
            {L'.',            GFxKey::Period},
            {L'/',            GFxKey::Slash},
            {L'|',            GFxKey::Bar},
            {L'[',            GFxKey::BracketLeft},
            {L'\\',           GFxKey::Backslash},
            {L']',            GFxKey::BracketRight},
            {L'"',            GFxKey::Quote},

            // @@ TODO fill this out some more
            { 0, GFxKey::VoidSymbol }
        };

        for (int i = 0; table[i].vk != 0; i++)
        {
            if (key == (UInt)table[i].vk)
            {
                c = table[i].gs;
                break;
            }
        }
    }

    if (c != GFxKey::VoidSymbol)
    {
        if (pMovie)
        {
            if (uchar < 32)
                uchar = 0;
            GFxKeyEvent event(down ? GFxEvent::KeyDown : GFxKeyEvent::KeyUp, c,
                uchar <= 127 ? uchar : 0, uchar < 0xf700 ? uchar : 0);

            event.SpecialKeysState.SetShiftPressed((mods & ShiftMask) ? 1: 0);
            event.SpecialKeysState.SetCtrlPressed((mods & ControlMask) ? 1: 0);
            event.SpecialKeysState.SetAltPressed((mods & Mod1Mask) ? 1: 0);
            event.SpecialKeysState.SetNumToggled((mods & Mod2Mask) ? 1: 0);
            event.SpecialKeysState.SetCapsToggled((mods & LockMask) ? 1: 0);
            pMovie->HandleEvent(event);
        }
    }
}


void    FxPlayerTiny::OnMouse(GFxEvent::EventType eventType, UInt button, SInt x, SInt y)
{
    if (pMovie)
    {
        GFxMouseEvent mevent(eventType, button, (Float)x, (Float)y);
        pMovie->HandleEvent(mevent);
    }
}

// Setup Application Window
bool FxPlayerTiny::SetupWindow(const GString& name)
{
    if (!NSApp)
        InitApplication(this);

    pCursor = [NSCursor arrowCursor];

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSPoint wpos = {100,100};
    NSRect rect = {{0, 0}, {Width, Height}};
    win = [[NSWindow alloc] initWithContentRect:rect styleMask:NSTitledWindowMask|NSResizableWindowMask|
           NSMiniaturizableWindowMask|NSClosableWindowMask
           backing:NSBackingStoreBuffered defer: NO];
    [win setViewsNeedDisplay:NO];
    [win setFrameOrigin:wpos];

    if (win)
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [win setTitle:[NSString stringWithUTF8String:name.ToCStr()]];
        [pool release];
    };

    int attr[16];
    int nattr = 2;

    attr[0] = NSOpenGLPFADoubleBuffer;
    attr[1] = NSOpenGLPFAAccelerated;
    attr[nattr++] = NSOpenGLPFAStencilSize;
    attr[nattr++] = 8;
    attr[nattr++] = NSOpenGLPFADepthSize;
    attr[nattr++] = 16;
    attr[nattr] = 0;

    NSOpenGLPixelFormat *fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute *)attr];

    view = [[GNSView alloc] initWithFrame:rect pixelFormat:fmt];
    [view setWin:0];
    [view setAutoresizingMask: NSViewWidthSizable | NSViewHeightSizable ];
    [win setContentView: view];
    [win makeFirstResponder: view];
    [win setDelegate: view];

    [win registerForDraggedTypes:[NSArray arrayWithObjects: NSFilenamesPboardType, nil]];

    ctx = [view openGLContext];
    /* Synchronize flips to vsync
    long value = 1;
    [ ctx setValues: &value forParameter: NSOpenGLCPSwapInterval ];
    */

    [ctx setView:view];
    [view release];
    [fmt release];

    [win makeKeyAndOrderFront:nil];
    [win setAcceptsMouseMovedEvents: YES];
    [view setWin:this];

    [ctx makeCurrentContext];

    [pool release];

    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    return 1;
}

// Message processing function to be called in the 
// application loops.
bool FxPlayerTiny::ProcessMessages()
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    NSEvent *  event = [NSApp  nextEventMatchingMask: NSAnyEventMask
                               untilDate: distantPast
                               inMode: NSDefaultRunLoopMode
                               dequeue: YES];

    if(event != nil)
    {
        [NSApp sendEvent: event];
    }
    [pool release];

    return [NSApp isRunning] && !QuitFlag;
}


// ***** main() -  Application entry point.

// The main function implementation creates the FxPlayerTiny class,
// passes it the filename and calls Run. FxPlayerTiny::Run is responsible
// for all of the rendering setup and movie playback.

int main(int argc, char *argv[])
{
    GFxSystem gfxInit;

    int result = 1;
    {
        FxPlayerTiny player(NULL);

        if (argc >= 2 && strncmp(argv[1], "-psn_", 5))
            player.FileName = argv[1];
        else
        {
            player.FileName = player.GetAppPath();
            player.FileName += "/";
            player.FileName += FXPLAYER_FILENAME;
        }

        result = player.Run();
    }

    return result;
}
