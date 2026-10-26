/**********************************************************************

Filename    :   Platform_Mac_GL.mm
Content     :   Platform::App implementation for Mac/GL.
Created     :   Jan 10, 2008
Authors     :   

Copyright   :   (c) 2010 Scaleform Corp. All Rights Reserved.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

**********************************************************************/

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <unistd.h>
#import <sys/stat.h>

#include "Platform.h"
#include "GFx/GFx_Loader.h"
#include "Kernel/SF_System.h"
#include "Kernel/SF_WString.h"
#include "Kernel/SF_HeapNew.h"
#include "Kernel/SF_SysFile.h"

#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/GL/GL_HAL.h"

//------------------------------------------------------------------------

using namespace Scaleform;
using namespace Scaleform::Platform;

#define Point Render::Point
#define Size  Render::Size

#define ShiftMask    (1<<17)
#define ControlMask  (1<<18)
#define Mod1Mask     (1<<19)
#define Mod2Mask     (1<<21)
#define LockMask     (1<<16)

static bool InitApplication(AppImpl *app);
static void keyEvent(AppImpl *pWin, NSEvent *event, int down);

static KeyModifiers getModifiers(unsigned int macmods)
{
    KeyModifiers mods;
    if (macmods & ShiftMask)
        mods.SetShiftPressed(true);
    if (macmods & ControlMask)
        mods.SetCtrlPressed(true);
    if (macmods & Mod1Mask)
        mods.SetAltPressed(true);
    if (macmods & Mod2Mask)
        mods.SetNumToggled(true);
    if (macmods & LockMask)
        mods.SetCapsToggled(true);
    return mods;
}


@interface SF_NSApp : NSApplication
{
    NSRunLoop*        loop;
    AppImpl*          pApp;
}
-(void) beginEvents;
-(void) endEvents;
-(void) setApp: (AppImpl *) app;
@end

@interface SF_NSView : NSOpenGLView
{
    AppImpl*      pWin;
    NSCursor*     pCursor;
}
@property (nonatomic, retain) NSCursor* pCursor;
-(void) setWin:(AppImpl *) app;
@end

//------------------------------------------------------------------------

namespace Scaleform { namespace Platform {


// ***** AppImpl

class AppImpl : public Device::Window, public AppImplBase
{
public:
    AppImpl(AppBase* app)
        : AppImplBase(app),
          NeedPaint(true),
          BlockOnSize(false)
    {
        Created = false;
        CursorEnabled = true;
        distantPast = [NSDate distantPast];
        Modifiers = 0;
        win = 0;
        ctx = 0;
        view = 0;
    }

    // Window Interface
    virtual void* GetHandle() { return win; }
    virtual void  GetViewConfig(ViewConfig *config) const { *config = Config; }
    virtual void  ConfigureWindow(ViewConfig& newConfig);    
    
    bool          setupWindow(const String& title, const ViewConfig& config);
    void          failSetupWindow(const char* cause);
    bool          setupFullscreen();

	// AppImplBase
	void          SetWindowTitle(const String& title);
    virtual void  killWindow();
protected:
    virtual void  updateConfig();


public:
    bool            Created;
    unsigned int    Modifiers;

    // Window location saved when going full-screen.
    ViewConfig      OldConfig;

    bool            NeedPaint, BlockOnSize, CursorEnabled;

    //NSCursor*        pCursor;
    SF_NSView*         view;
    NSWindow*        win;
    NSOpenGLContext* ctx;
    NSDate*          distantPast;
};


bool AppImpl::setupWindow(const String& title, const ViewConfig& config)
{
    if (!NSApp)
        InitApplication(this);

    Title  = title;
    Config = config;
    
    if (Created)
        return false;

    Modifiers = 0;
    
    if (Config.HasFlag(View_FullScreen))
        return setupFullscreen();

    SF_ASSERT(Config.HasFlag(View_Size));

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    if (!Config.HasFlag(View_Pos))
    {
        Config.WindowPos.x = (CGDisplayPixelsWide(kCGDirectMainDisplay) - Config.ViewSize.Width) / 2;
        Config.WindowPos.y = (CGDisplayPixelsHigh(kCGDirectMainDisplay) - Config.ViewSize.Height) / 2;
    }

    NSPoint wpos = {Config.WindowPos.x, Config.WindowPos.y};
    NSRect rect = {{0, 0}, {Config.ViewSize.Width, Config.ViewSize.Height}};
    win = [[NSWindow alloc] initWithContentRect:rect styleMask:NSTitledWindowMask|NSResizableWindowMask|
           NSMiniaturizableWindowMask|NSClosableWindowMask
           backing:NSBackingStoreBuffered defer: NO];
    [win setViewsNeedDisplay:NO];
    [win setFrameOrigin:wpos];

    [win setTitle:[NSString stringWithUTF8String:title.ToCStr()]];

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
    
    view = [[SF_NSView alloc] initWithFrame:rect pixelFormat:fmt];
    view.pCursor = [NSCursor arrowCursor];
    [view setWin:0];
    [view setAutoresizingMask: NSViewWidthSizable | NSViewHeightSizable ];
    [win setContentView: view];
    [win makeFirstResponder: view];
    [win setDelegate: view];

    if (Config.HasFlag(View_WindowDropFiles))
        [win registerForDraggedTypes:[NSArray arrayWithObjects: NSFilenamesPboardType, nil]];
    
    ctx = [view openGLContext];
    /* Synchronize flips to vsync
    long value = 1;
    [ ctx setValues: &value forParameter: NSOpenGLCPSwapInterval ];
    */

    [ctx setView:view];
    [view release];
    [fmt release];

    [win makeKeyAndOrderFront:win];
    [win setAcceptsMouseMovedEvents: YES];
    [view setWin:this];
    [win orderFrontRegardless];

    rect = [[win contentView] bounds];
    Config.ViewSize.Width = int(rect.size.width);
    Config.ViewSize.Height = int(rect.size.height);

    Created = 1;

    [pool release];

    updateConfig();
    return true;
}

bool AppImpl::setupFullscreen()
{
    if (Created)
        return 0;

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    int attr[16];
    int nattr = 6;

    attr[0] = NSOpenGLPFADoubleBuffer;
    attr[1] = NSOpenGLPFAAccelerated;
    attr[2] = NSOpenGLPFANoRecovery;
    attr[3] = NSOpenGLPFAFullScreen;
    attr[4] = NSOpenGLPFAScreenMask;
    attr[5] = CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay);

    attr[nattr++] = NSOpenGLPFAStencilSize;
    attr[nattr++] = 8;
    attr[nattr++] = NSOpenGLPFADepthSize;
    attr[nattr++] = 16;
    attr[nattr] = 0;

    NSOpenGLPixelFormat *fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute *)attr];

    ctx = [[NSOpenGLContext alloc] initWithFormat:fmt shareContext:nil];
    [fmt release];

    CGCaptureAllDisplays();

    [ctx setFullScreen];
    [pool release];

    Created = 1;
    Config.ViewSize.Width = CGDisplayPixelsWide(kCGDirectMainDisplay);
    Config.ViewSize.Height = CGDisplayPixelsHigh(kCGDirectMainDisplay);
    
    return 1;
}

void AppImpl::failSetupWindow(const char* cause)
{
}

void AppImpl::killWindow()
{
    if (!Created)
        return;

    // restore the original display if we're in fullscreen mode
    if (Config.HasFlag(View_FullScreen))
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        [ctx flushBuffer];
        glClear(GL_COLOR_BUFFER_BIT);
        [ctx flushBuffer];

        [NSOpenGLContext clearCurrentContext];
        [ctx clearDrawable];
        [ctx release];
        ctx = 0;

        CGReleaseAllDisplays();
        Created = 0;
    }
    else
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [win close];
        [pool release];
        win = 0;
        view = 0;
        ctx = 0;
        Created = 0;
    }
}

void AppImpl::ConfigureWindow(ViewConfig& config)
{
    if (config.HasFlag(View_FullScreen) != Config.HasFlag(View_FullScreen))
    {
        killWindow();
        setupWindow(Title, config);
    }
    else
    {
        BlockOnSize = true;
        
        Config = config;
        BlockOnSize = false;
    }
}


void AppImpl::updateConfig()
{
    if (win)
    {
        NSRect rect = [[win contentView] bounds];
        Config.SetSize(int(rect.size.width), int(rect.size.height));
        Config.SetPos(int(rect.origin.x), int(rect.origin.y));
    }
}

void AppImpl::SetWindowTitle(const String& title)
{
    if (win)
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        [win setTitle:[NSString stringWithUTF8String:title.ToCStr()]];
        [pool release];
        Title = title;
    }
}



class DeviceImpl : public NewOverrideBase<Stat_Default_Mem>
{
public:
    DeviceImpl(Render::ThreadCommandQueue *commandQueue);
    ~DeviceImpl();

    bool adjustViewConfig(ViewConfig* config);

    bool initGraphics(const ViewConfig& config, Device::Window* window, ThreadId renderThreadId = 0);
    bool reconfigureGraphics(const ViewConfig& config);
    void shutdownGraphics();

    void updateStatus();
    
    bool takeScreenShot(const String& filename);

    AppImpl*                pWindow;
    Ptr<Render::GL::HAL>    pHal;
    DeviceStatus            Status;
};


DeviceImpl::DeviceImpl(Render::ThreadCommandQueue *commandQueue)
 : pWindow(0), pHal(0), Status(Device_NeedInit)
{
    pHal = *SF_NEW Render::GL::HAL(commandQueue);
}

DeviceImpl::~DeviceImpl()
{
    pHal.Clear();
}


bool DeviceImpl::adjustViewConfig(ViewConfig* config)
{
    if (config->HasFlag(View_Size))
    {
        if (config->ViewSize.Width < 1)
            config->ViewSize.Width = 1;
        if (config->ViewSize.Height< 1)
            config->ViewSize.Height= 1;
    }
    config->SetFlag(View_Stereo, false);

    return true;
}


bool DeviceImpl::initGraphics(const ViewConfig& config, Device::Window* window,
                              ThreadId renderThreadId)
{
    if (!pHal || !window)
        return false;

    pWindow = (AppImpl*) window;

    [pWindow->ctx makeCurrentContext];

    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    glPushAttrib(GL_ALL_ATTRIB_BITS);


    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.
    if (!pHal->InitHAL(Render::GL::HALInitParams(0, renderThreadId)))
    {
        shutdownGraphics();
        pWindow = 0;
        return false;
    }

    Status = Device_Ready;
    return true;
}

bool DeviceImpl::reconfigureGraphics(const ViewConfig& config)
{
    [pWindow->ctx makeCurrentContext];
    bool result = pHal->ResetContext();
    return result;
}


void DeviceImpl::shutdownGraphics()
{
    if (pHal)
        pHal->ShutdownHAL();

    pWindow = 0;
    Status = Device_NeedInit;
}

void DeviceImpl::updateStatus()
{
}


//------------------------------------------------------------------------
Device::Device(Render::ThreadCommandQueue *commandQueue)
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
    pImpl->updateStatus();
    return pImpl->Status;
}

UInt32 Device::GetCaps() const
{
    return DeviceCap_Wireframe;
}

//------------------------------------------------------------------------
bool Device::GraphicsConfigOnMainThread() const
{
    return false;
}

bool Device::AdjustViewConfig(ViewConfig* config)
{
    return pImpl->adjustViewConfig(config);
}

bool Device::InitGraphics(const ViewConfig& config, Device::Window* window,
                          ThreadId renderThreadId)
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
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    if (scissorEnabled)
        glEnable(GL_SCISSOR_TEST);
}

int AppBase::GetDisplayCount()
{
    return 1;
}

Device::Window* Device::CreateGraphicsWindow(int WindowId, const ViewConfig&)
{
    return 0;
}

void Device::SetWindow(Window*)
{
}

void Device::PresentFrame(unsigned)
{
    [pImpl->pWindow->ctx flushBuffer];
}

void Device::BeginFrame()
{
    [pImpl->pWindow->ctx makeCurrentContext];
}

void Device::SetWireframe(bool wireframeEnable)
{
    if (wireframeEnable)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
}

bool mkdirRecursive(const String& path)
{
    String newPath = path;
    if ( mkdir( newPath.ToCStr(), S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO ) != 0 && errno == ENOENT )
    {
        newPath.Remove( newPath.GetLength()-1 ); // remove '/'
        if ( !mkdirRecursive( newPath.GetPath() ) )
            return false;
        if ( mkdir( path.ToCStr(), S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO ) != 0 )
        {
            SF_DEBUG_MESSAGE2(1, "Could not make directory: %s (errno=%d)\n", path.ToCStr(), errno);
            return false;
        }        
    }    
    return true;
}
    
bool Device::TakeScreenShot(const String& filename)
{
#ifdef SF_ENABLE_LIBPNG
    [pImpl->pWindow->ctx flushBuffer];    
    
    // Create the directory if it doesn't exist.
    if ( ! mkdirRecursive(filename.GetPath() ))
        return false;
    
    GLint viewportInfo[4];
    glGetIntegerv(GL_VIEWPORT, viewportInfo);

    UByte* pixelMemory = (UByte*)SF_ALLOC(sizeof(UByte)*viewportInfo[2]*(viewportInfo[3]+1)*3, Stat_Default_Mem);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(viewportInfo[0], viewportInfo[1], viewportInfo[2], viewportInfo[3], GL_RGB, GL_UNSIGNED_BYTE, pixelMemory );
    if ( glGetError() != 0 )
    {
        SF_FREE(pixelMemory);
        return false;
    }
    
    // Reverse the scanlines, so they're not upsidedown.
    UByte* extraLine = pixelMemory + viewportInfo[2]*viewportInfo[3]*3;
    unsigned linesize = viewportInfo[2]*3;
    for (int sl = 0; sl < viewportInfo[3]/2; sl++ )
    {
        memcpy(extraLine, pixelMemory + sl* linesize, linesize );
        memcpy(pixelMemory + sl* linesize, pixelMemory + (viewportInfo[3]-sl-1) * linesize, linesize );
        memcpy(pixelMemory + (viewportInfo[3]-sl-1) * linesize, extraLine, linesize );
    }
    
    // Now actually save it.
    Render::ImageData data;
    data.Initialize(Render::Image_R8G8B8, (UPInt)viewportInfo[2], (UPInt)viewportInfo[3], (UPInt)viewportInfo[2]*3, (UByte*)pixelMemory);
    String actualFilename = filename;
    if ( actualFilename.GetExtension().CompareNoCase(".png") )
        actualFilename.AppendString(".png");
    
    bool success = Render::PNG::FileWriter::WriteImage<SysFile>(actualFilename, data);
    SF_FREE(pixelMemory);
    return success;
#else
    SF_UNUSED(filename);
    return false;
#endif
    
}


//------------------------------------------------------------------------
// ***** AppBase

AppBase::AppBase()
 :  Cursor(true),
    ShuttingDown(false)
{
    pImplBase = pImpl = SF_NEW AppImpl(this);
    pDevice = 0;
}
AppBase::~AppBase()
{
    delete pImpl;
}

void AppBase::SetOrientationMode(bool)
{
}

//------------------------------------------------------------------------

// This call cleans up the application and kills the window.
void AppBase::Shutdown()
{
    ShuttingDown = true;
}

bool AppBase::IsPadConnected(unsigned)
{
    return false;
}

void AppBase::BringWindowToFront()
{
    if (pImpl->win)
    {        
        [pImpl->win makeKeyAndOrderFront:pImpl->win];
        [pImpl->win orderFrontRegardless];
    }
}

Device::Window* AppBase::GetDeviceWindow() const
{
    return pImpl;
}

bool AppBase::IsConsole()
{
    return false;
}

// Amount (multiple of size) to reduce viewport by to fit in visible area on TVs.
// This is a floating point value such as 0.1 for 10% safe frame border.
Size<float> AppBase::GetSafeArea()
{
    return Size<float>(0.0f);
}

const char* AppBase::GetDefaultFilePath()
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    char *path = strdup([[[NSBundle mainBundle] bundlePath] UTF8String]);
    [pool release];
    return path;
}

String AppBase::GetContentDirectory()
{
    return "";
}

int AppBase::GetMouseCount()
{
    return 1;
}
int AppBase::GetKeyboardCount()
{
    return 1;
}

UInt32 AppBase::GetCaps() const
{
    return 0;
}


// Application Main function
int AppBase::AppMain(int argc, char* argv[])
{    
   // Scaleform::System initSFSystem;

    // Parse and handle command line arguments.
    InitArgDescriptions(&pImpl->Arguments);
    if (!OnArgs(pImpl->Arguments, pImpl->Arguments.ParseCommandLine(argc, argv)))
        return 0;
    
    // Initialize application and its window.
    ViewConfig config(Device::GetDefaultViewSize());
    ApplyViewConfigArgs(&config, GetArgs());
    if (!OnInit(config))
    {
        return 0;
    }

    // Application / Player message loop.

    while (!ShuttingDown)
    {
        NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
        NSDate            *date = pImpl->distantPast;

        if (pImpl->FrameTime != 0.0f)
        {
            UInt64  ticks = Timer::GetTicks();
                
            if ((pImpl->NextUpdateTicks > ticks) && !pImpl->NeedPaint)
            {
                UInt64   waitTicks = pImpl->NextUpdateTicks - ticks;
                date = [NSDate dateWithTimeIntervalSinceNow: double(waitTicks)/1000000.0];
            }
        }

        NSEvent *  event = [NSApp  nextEventMatchingMask: NSAnyEventMask
                            untilDate: date
                            inMode: NSDefaultRunLoopMode
                            dequeue: YES];

        if(event != nil)
        {
            if (pImpl->Config.HasFlag(View_FullScreen))
            {
                switch ([event type])
                {
                default:
                    break;

                case NSLeftMouseDown:
                case NSRightMouseDown:
                case NSOtherMouseDown:
                    {
                        NSPoint pt = [event locationInWindow];
                        OnMouseButton(0, [event buttonNumber], 1,
                                      Point<int>(int(pt.x), int(pImpl->Config.ViewSize.Height-pt.y)),
                                      getModifiers(pImpl->Modifiers));
                    }
                    break;
                case NSLeftMouseUp:
                case NSRightMouseUp:
                case NSOtherMouseUp:
                    {
                        NSPoint pt = [event locationInWindow];
                        OnMouseButton (0, [event buttonNumber], 0, 
                                       Point<int>(int(pt.x), int(pImpl->Config.ViewSize.Height-pt.y)),
                                       getModifiers(pImpl->Modifiers));
                    }
                    break;

                case NSLeftMouseDragged:
                case NSRightMouseDragged:
                case NSOtherMouseDragged:
                case NSMouseMoved:
                    {
                        NSPoint pt = [event locationInWindow];
                        OnMouseMove (0, Point<int>(int(pt.x), int(pImpl->Config.ViewSize.Height-pt.y)), getModifiers(pImpl->Modifiers));
                    }
                    break;

                case NSScrollWheel:
                    {
                        NSPoint pt = [event locationInWindow];
                        float mw = [event deltaY];
                        if (mw < 0) mw--;
                        else if (mw > 0) mw++;
                        OnMouseWheel (0, mw, Point<int>(int(pt.x), int(pImpl->Config.ViewSize.Height-pt.y)), getModifiers(pImpl->Modifiers));
                    }
                    break;

                case NSKeyDown:
                    keyEvent(pImpl,event,1);
                    break;
                case NSKeyUp:
                    keyEvent(pImpl,event,0);
                    break;
                case NSFlagsChanged:
                    {
                        unsigned int mods = [event modifierFlags];
                        if (mods != pImpl->Modifiers)
                        {
                            if ((mods & (1<<17)) != (pImpl->Modifiers & (1<<17)))
                                OnKey(0, Key::Shift, 0, mods & (1<<17), getModifiers(mods));
                            if ((mods & (1<<18)) != (pImpl->Modifiers & (1<<18)))
                                OnKey(0, Key::Control, 0, mods & (1<<18), getModifiers(mods));
                            if ((mods & (1<<19)) != (pImpl->Modifiers & (1<<19)))
                                OnKey(0, Key::Alt, 0, mods & (1<<19), getModifiers(mods));
                        }
                        pImpl->Modifiers = mods;

                    }
                    break;
                }
            }
            else
                [NSApp sendEvent: event];
        }
        [pool release];

        OnUpdateFrame(true);
    }

    OnShutdown();

    return 0;
}

SystemCursorManager::SystemCursorManager(bool systemCursorAvailable) :
    SystemCursorState(systemCursorAvailable, true),
    pImpl(0)

{
}

SystemCursorManager::~SystemCursorManager()
{
}

void SystemCursorManager::update(bool forceSet)
{
}


}} // Scaleform::Platform


static bool InitApplication(AppImpl *app)
{
    NSApp = [SF_NSApp sharedApplication];
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [NSApp setApp:app];
    [NSApp setDelegate:NSApp];
    [NSBundle loadNibNamed:@"MainMenu" owner:NSApp];
    [NSApp beginEvents];
    [pool release];
    
    return 1;
}


@implementation SF_NSApp
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
-(void) setApp:(AppImpl *) app
{
    pApp = app;
}
-(void) terminate:(id) sender
{
    pApp->pApp->Shutdown();
}

-(BOOL) application:(NSApplication *) app openFile:(NSString *)filename
{
    if (pApp && pApp->Created)
    {
        char *fn = strdup([filename UTF8String]);
        pApp->pApp->OnDropFiles(fn);
        free(fn);
    }
    return 1;
}
@end

@implementation SF_NSView
@synthesize pCursor;
-(void) setWin:(AppImpl *) app
{
    pWin = app;
}

static struct 
{
    wchar_t macKey;
    KeyCode appKey;
    bool    charEvent;
} KeyCodeMap[] = 
{
    {127,                       Key::Backspace, false},
    {L'\t',                     Key::Tab, true},
    {L'\r',                     Key::Return, true},
    {L' ',                      Key::Space, true},
    {NSPageUpFunctionKey,       Key::PageUp, false},
    {NSPageDownFunctionKey,     Key::PageDown, false},
    {NSEndFunctionKey,          Key::End, false},
    {NSHomeFunctionKey,         Key::Home, false},
    {NSLeftArrowFunctionKey,    Key::Left, false},
    {NSUpArrowFunctionKey,      Key::Up, false},
    {NSRightArrowFunctionKey,   Key::Right, false},
    {NSDownArrowFunctionKey,    Key::Down, false},
    {NSInsertFunctionKey,       Key::Insert, false},
    {NSDeleteFunctionKey,       Key::Delete, false},
    {NSHelpFunctionKey,         Key::Help, false},
    {NSScrollLockFunctionKey,   Key::ScrollLock, false},
    {NSPauseFunctionKey,        Key::Pause, false},
    {L'[',            Key::BracketLeft, true},
    {L']',            Key::BracketRight, true},
/*    {L';',            Key::Semicolon, true},
    {L'=',            Key::Equal, true},
    {L',',            Key::Comma, true},
    {L'-',            Key::Minus, true},
    {L'.',            Key::Period, true},
    {L'/',            Key::Slash, true},
    {L'|',            Key::Bar, true},
    {L'\\',           Key::Backslash, true},
    {L'"',            Key::Quote, true},

    {L'\'',           Key::Quote, true},
    {L'~',           Key::Quote, true},
    {L'?',           Key::Quote, true},
    {L'!',           Key::Quote, true},
    {L'@',           Key::Quote, true},
    {L'#',           Key::Quote, true},*/
};

static void keyEvent(AppImpl *pWin, NSEvent *event, int down)
{
    NSString *chars = [event characters];
    NSString *codes = [event charactersIgnoringModifiers];
    int mods = [event modifierFlags];

    if ([chars length] == 1)
    {
        int key = [codes characterAtIndex:0];
        int code = [event keyCode];
        KeyCode kc = Key::None;
        wchar_t wchar = 0;
        
        switch (code)
        {
        case 0x35: kc = Key::Escape; break;
        case 0x38: case 0x3c: kc = Key::Shift; break;
        case 0x3b: case 0x3e: kc = Key::Control; break;
        case 0x3a: case 0x3d: kc = Key::Alt; break;

        default:
            wchar = [chars characterAtIndex:0];
            if (key >= 'a' && key <= 'z')
                key += 'A' - 'a';

            if (key >= 'A' && key <= 'Z')
            {
                kc = (KeyCode) ((key - 'A') + Key::A);
            }
            else if (key >= '0' && key <= '9')
            {
                kc = (KeyCode) ((key - '0') + Key::Num0);
            }
            else if (key >= NSF1FunctionKey && key <= NSF15FunctionKey)
            {
                kc = (KeyCode) ((key - NSF1FunctionKey) + Key::F1);
                wchar = 0;
            }
            else 
            {
                for (int i = 0; KeyCodeMap[i].macKey != 0; i++)
                {
                    if (key == KeyCodeMap[i].macKey)
                    {
                        kc = KeyCodeMap[i].appKey;
                        if (!KeyCodeMap[i].charEvent)
                            wchar = 0;
                        break;
                    }
                }
            }
        }
        //printf(" %d %d %d %d\n", key, kc, wchar, down);
        pWin->pApp->OnKey(0, kc, wchar, down, getModifiers(mods));
    }
    else
        for (unsigned int i = 0; i < [chars length]; i++)
        {
            wchar_t wchar = [chars characterAtIndex:i];
            //printf("!! %d %d\n", wchar, down);
            pWin->pApp->OnKey(0, Key::None, wchar, down, getModifiers(mods));
        }
}

-(void) keyDown:(NSEvent *)event { keyEvent(pWin,event, 1); }
-(void) keyUp:(NSEvent *)event { keyEvent(pWin,event,0); }
-(void) flagsChanged:(NSEvent *)event
{
    unsigned int mods = [event modifierFlags];
    if (mods != pWin->Modifiers)
    {
        if ((mods & (1<<17)) != (pWin->Modifiers & (1<<17)))
            pWin->pApp->OnKey(0, Key::Shift, 0, mods & (1<<17), getModifiers(mods));
        if ((mods & (1<<18)) != (pWin->Modifiers & (1<<18)))
            pWin->pApp->OnKey(0, Key::Control, 0, mods & (1<<18), getModifiers(mods));
        if ((mods & (1<<19)) != (pWin->Modifiers & (1<<19)))
            pWin->pApp->OnKey(0, Key::Alt, 0, mods & (1<<19), getModifiers(mods));
    }
    pWin->Modifiers = mods;
}

-(void) mouseDown:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        pWin->pApp->OnMouseButton (0, [event buttonNumber], 1, Point<int>(int(pt.x), int([self bounds].size.height-pt.y)), getModifiers(pWin->Modifiers));
    }
}
-(void) mouseUp:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        pWin->pApp->OnMouseButton (0, [event buttonNumber], 0, Point<int>(int(pt.x), int([self bounds].size.height-pt.y)), getModifiers(pWin->Modifiers));
    }
}
-(void) scrollWheel:(NSEvent *)event
{
    if (pWin)
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        float mw = [event deltaY];
        if (mw < 0) mw--;
        else if (mw > 0) mw++;
        pWin->pApp->OnMouseWheel (0, mw, Point<int>(int(pt.x), int([self bounds].size.height-pt.y)), getModifiers(pWin->Modifiers));
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
        pWin->pApp->OnMouseMove (0, Point<int>(int(pt.x), int([self bounds].size.height-pt.y)), getModifiers(pWin->Modifiers));
    }
}
-(void) mouseDragged:(NSEvent *)event { [self mouseMoved:event]; }
-(void) rightMouseDragged:(NSEvent *)event { [self mouseMoved:event]; }
-(void) otherMouseDragged:(NSEvent *)event { [self mouseMoved:event]; }

-(NSDragOperation)draggingEntered:(id <NSDraggingInfo>)sender {
    NSPasteboard *pboard;
    NSDragOperation sourceDragMask;
    sourceDragMask = [sender draggingSourceOperationMask];
    pboard = [sender draggingPasteboard];

    if (pWin && [[pboard types] containsObject:NSFilenamesPboardType])
        return NSDragOperationGeneric;

    return NSDragOperationNone;
}
-(BOOL)performDragOperation:(id <NSDraggingInfo>)sender {
    NSPasteboard *pboard;
    NSDragOperation sourceDragMask;
    sourceDragMask = [sender draggingSourceOperationMask];
    pboard = [sender draggingPasteboard];
    if (pWin && [[pboard types] containsObject:NSFilenamesPboardType])
    {
        NSArray *files = [pboard propertyListForType:NSFilenamesPboardType];
        if ([files count] >= 1)
        {
            char *fn = strdup([[files objectAtIndex:0] UTF8String]);
            pWin->pApp->OnDropFiles(fn);
            free(fn);
            return YES;
        }
    }
    return NO;
}

-(void) resetCursorRects
{
    [self addCursorRect:[self visibleRect] cursor:pCursor];
}

-(void) windowDidResize:(NSNotification *)event
{
    if (pWin)
    {
        NSRect rect = [[[event object] contentView] bounds];
        pWin->pApp->OnSize(Size<unsigned >(unsigned(rect.size.width), unsigned(rect.size.height)));
    }
}
-(BOOL) windowShouldClose:(id)sender
{
    pWin->pApp->Shutdown();
    return NO;
}

@end

//------------------------------------------------------------------------

int main(int argc, char** argv)
{    
    Scaleform::Platform::AppBase* app = Scaleform::Platform::AppBase::CreateInstance();
    int result = app->AppMain(argc, argv);
    Scaleform::Platform::AppBase::DestroyInstance(app);

    return result;
}

