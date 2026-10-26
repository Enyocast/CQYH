/**************************************************************************

Filename    :   Platform_NGP.cpp
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Platform.h"
#include "Platform/Platform_SystemCursorManager.h"

#include "Kernel/SF_KeyCodes.h"
#include "Kernel/SF_HeapNew.h"
#include "Kernel/SF_System.h"
#include "Kernel/SF_Debug.h"

#include "Render/NGP/NGP_HAL.h"
#include "Render/NGP/NGP_MemoryManager.h"

#include <ctrl.h>
#include <touch.h>
#include <kernel.h>
#include <display.h>
#include <gxm.h>

#include <libsysmodule.h>
#include <razor_capture.h>

const char		sceUserMainThreadName[]		= "Scaleform App";
int				sceUserMainThreadPriority	= SCE_KERNEL_DEFAULT_PRIORITY_USER;
unsigned int	sceUserMainThreadStackSize	= 512 * 1024;
unsigned int	sceLibcHeapSize	= 256 << 20;


namespace Scaleform { namespace Platform {


using namespace Render;

//------------------------------------------------------------------------
// ***** AppImpl

class AppImpl : public Device::Window, public AppImplBase
{
    friend class AppBase;

    AppImpl(AppBase* app);
	~AppImpl();

    // Window Interface
    virtual void* GetHandle() { return 0; }
    virtual void  GetViewConfig(ViewConfig *config) const { *config = Config; }
    virtual void  ConfigureWindow(ViewConfig& newConfig);    
    
private:
    bool          setupWindow(const String& title, const ViewConfig& config);

    bool          processMessages();
    void          setMousePosition(const Point<unsigned> & p );

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

    bool              Created;
    bool              BlockOnSize;

    SceInt16             SwipeTouchX, SwipeTouchY;
    SceInt16             LastTouchX, LastTouchY;
};


//------------------------------------------------------------------------

static PadKeyCode keymap[16] =
{
    Pad_Select, Pad_None, Pad_None, Pad_Start, Pad_Up, Pad_Right, Pad_Down, Pad_Left,
    Pad_L1,     Pad_R1,   Pad_None, Pad_None,  Pad_T,  Pad_O,     Pad_X,    Pad_S
};


//------------------------------------------------------------------------

AppImpl::AppImpl(AppBase* app) :         
    AppImplBase(app),
    Created(false),
    SwipeTouchX(-1)
{
}

AppImpl::~AppImpl() 
{
}

#define DISPLAY_WIDTH				960
#define DISPLAY_HEIGHT				544
#define DISPLAY_PITCH               1024

#define DISPLAY_COLOR_FORMAT		SCE_GXM_COLOR_FORMAT_A8B8G8R8
#define DISPLAY_PIXEL_FORMAT		SCE_DISPLAY_PIXELFORMAT_A8B8G8R8

bool AppImpl::setupWindow(const String& title, const ViewConfig& config)
{
    Title  = title;
    Config = config;

    if (Created)
        return false;

    Point<unsigned> center(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2);
    setMousePosition(center);
    Touch.reportNum = 0;

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_DIGITALANALOG);
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);

    return true;
}

void AppImpl::ConfigureWindow(ViewConfig& newConfig)
{
    // Configures window for a new video mode.
    Config = newConfig;
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

bool AppImpl::processMessages()
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
            if ((Pad.pad.buttons & (1 << j)) != (pad.buttons & (1 << j))) 
            {
                if (keymap[j] == Pad_X && pApp->IsCursorEnabled())
                {
                    mbutton = (pad.buttons & (1 << j)) ? 1 : 0;
                }
                else
                {
                    if (keymap[j] == Pad_Select && (pad.buttons & (1 << j)))
                        sceRazorCaptureSetTriggerNextFrame("host0:gfx.sgx");

                    pApp->OnPad(0, keymap[j], (pad.buttons & (1 << j)) ? 1 : 0);
                    Pad.RepeatDelay = 350000;
                    didrepeat = 1;
                }
            }
            else if ((Pad.pad.buttons & (1 << j)) && (pad.buttons & (1 << j))
                && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay
                && (!pApp->IsCursorEnabled() || keymap[j] != Pad_X))
            {
                Pad.RepeatDelay = 100000;
                pApp->OnPad(0, keymap[j], 1);
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
                //pApp->OnPad(k, Pad_Right, 0);
                pApp->OnPad(0, Pad_Right, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldL)
                pApp->OnPad(0, Pad_Left, 0);
            if (oldL || !oldR)
            {
                pApp->OnPad(0, Pad_Right, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickRight = true;
        }
        if (curL)
        {
            if (oldL && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //pApp->OnPad(k, Pad_Left, 0);
                pApp->OnPad(0, Pad_Left, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldR)
                pApp->OnPad(0, Pad_Right, 0);
            if (oldR || !oldL)
            {
                pApp->OnPad(0, Pad_Left, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickLeft = true;
        }
        if (curU)
        {
            if (oldU && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //pApp->OnPad(k, Pad_Up, 0);
                pApp->OnPad(0, Pad_Up, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldD)
                pApp->OnPad(0, Pad_Down, 0);
            if (oldD || !oldU)
            {
                pApp->OnPad(0, Pad_Up, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickUp = true;
        }
        if (curD)
        {
            if (oldD && msgtime >= Pad.LastRepeatTime + Pad.RepeatDelay)
            {
                //pApp->OnPad(k, Pad_Down, 0);
                pApp->OnPad(0, Pad_Down, 1);
                Pad.RepeatDelay = 100000;
                didrepeat = 1;
            }
            else if (oldU)
                pApp->OnPad(0, Pad_Up, 0);
            if (oldU || !oldD)
            {
                pApp->OnPad(0, Pad_Down, 1);
                Pad.RepeatDelay = 350000;
                didrepeat = 1;
            }
            Pad.nLStickDown = true;
        }
        
        if (Pad.LStickDown && !Pad.nLStickDown)
		    pApp->OnPad(0, Pad_Down, 0);

        if (Pad.LStickUp && !Pad.nLStickUp)
            pApp->OnPad(0, Pad_Up, 0);

        if (Pad.LStickLeft && !Pad.nLStickLeft)
            pApp->OnPad(0, Pad_Left, 0);

        if (Pad.LStickRight && !Pad.nLStickRight)
            pApp->OnPad(0, Pad_Right, 0);

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
            pApp->OnPadStick(0, Pad_LT, padlx, padly);
            Pad.LastLx = padlx; Pad.LastLy = padly;
        }
        if (padrx != Pad.LastRx || padry != Pad.LastRy)
        {
            pApp->OnPadStick(0, Pad_RT, padrx, padry);
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
            if (Pad.MouseX >= int(Config.ViewSize.Width))
                Pad.MouseX = Config.ViewSize.Width;
            if (Pad.MouseY < 0)
                Pad.MouseY = 0;
            if (Pad.MouseY >= int(Config.ViewSize.Height))
                Pad.MouseY = Config.ViewSize.Height;

            pApp->OnMouseMove(0, Point<int>(Pad.MouseX, Pad.MouseY), 0);

            // Change the mouse position in the impl.
            MousePos = Point<int>(Pad.MouseX, Pad.MouseY);
        }
        if (mbutton != -1)
            pApp->OnMouseButton(0, 0, mbutton, Point<int>(Pad.MouseX, Pad.MouseY), 0);

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
                    pApp->OnGesture(0, Platform::AppBase::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(1, 0), PointF(0, 0), 0);
                }
                else if (LastTouchX - SwipeTouchX < 500)
                {
                    pApp->OnGesture(0, Platform::AppBase::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(-1, 0), PointF(0, 0), 0);
                }
                else if (LastTouchY - SwipeTouchY > 500)
                {
                    pApp->OnGesture(0, Platform::AppBase::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(0, 1), PointF(0, 0), 0);
                }
                else if (LastTouchY - SwipeTouchY < 500)
                {
                    pApp->OnGesture(0, Platform::AppBase::GestureBit_Swipe, Point<int>(LastTouchX, LastTouchY), PointF(0, -1), PointF(0, 0), 0);    
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
                pApp->OnTouchMove(0, pt.id, point, Point<int>(0,0), pt.id == TouchPrimaryId);
            else
                pApp->OnTouchBegin(0, pt.id, point, Point<int>(0,0), pt.id == TouchPrimaryId);

            if (pt.id == TouchPrimaryId)
            {
                if (isMove)
                    pApp->OnMouseMove(0, point, 0);
                else
                    pApp->OnMouseButton(0, 0, 1, point, 0);
            }
        }
        for (int i = 0; i < Touch.reportNum; i++)
            if (Touch.report[i].id < 255)
            {
                const SceTouchReport& pt = Touch.report[i];
                Point<int> point (int(pt.x*0.5f), int(pt.y*0.5f));

                pApp->OnTouchEnd(0, Touch.report[i].id, point, Point<int>(0,0), pt.id == TouchPrimaryId);
                if (pt.id == TouchPrimaryId)
                    pApp->OnMouseButton(0, 0, 0, point, 0);
            }

        Touch = touch1;
        if (Touch.reportNum == 0)
            TouchPrimaryId = -1;
    }
    return 1;
}

void AppImpl::setMousePosition(const Point<unsigned> & p ) 
{
    Pad.MouseX = p.x;
    Pad.MouseY = p.y;
}

//------------------------------------------------------------------------
// ***** AppBase

AppBase::AppBase() :
    Cursor(false),
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

void AppBase::Shutdown()
{
    ShuttingDown = true;
}

void AppBase::BringWindowToFront()
{
}

Device::Window* AppBase::GetDeviceWindow() const
{
    return pImpl;
}

bool AppBase::IsConsole()
{
    return true;
}

UInt32 AppBase::GetCaps() const
{
    return 0;
}

Size<float> AppBase::GetSafeArea()
{
    return Size<float>(0.0f);
}

const char* AppBase::GetDefaultFilePath()
{
    return "host0:/FxPlayer/";
}

String AppBase::GetContentDirectory()
{
    return GetDefaultFilePath();
}

int AppBase::GetMouseCount()
{
    return 1;
}

int AppBase::GetKeyboardCount()
{
    return 0;
}

bool AppBase::IsPadConnected(unsigned pad)
{
	return (pad == 0);
}

// Application Main function
int AppBase::AppMain(int argc, char* argv[])
{    
    // Scaleform::System initSFSystem;

    // Parse and handle command line arguments.
    InitArgDescriptions(&pImplBase->Arguments);
    if (!OnArgs(pImplBase->Arguments, pImplBase->Arguments.ParseCommandLine(argc, argv)))
        return 0;

    // Initialize application and its window.
    ViewConfig config(Device::GetDefaultViewSize());
    ApplyViewConfigArgs(&config, GetArgs());
    if (!OnInit(config))
    {
        return 0;
    }

    // Application / Player message loop.
    pImpl->NextUpdateTicks = Timer::GetTicks() + pImpl->FrameTimeTicks;

    while(!IsShuttingDown())
    {
        // Wait for Update time if necessary; consider timing wrap-around.
        pImpl->processMessages();

        if (pImpl->FrameTime != 0.0f)
        {
            UInt64  ticks = Timer::GetTicks();
            if (pImpl->NextUpdateTicks > ticks)
            {
                UPInt waitUs = pImpl->NextUpdateTicks - ticks;
                sceKernelDelayThread(waitUs);
                continue;
            }
            pImpl->NextUpdateTicks = ticks + pImpl->FrameTimeTicks;
        }
        OnUpdateFrame(true);
    }

    OnShutdown();

    return 0;
}


//------------------------------------------------------------------------
// ***** Directory

class DirectoryImpl : public DirectoryImplBase
{
public:
    DirectoryImpl(const String& path, const String& pattern) :
        DirectoryImplBase(path, pattern) { }

    virtual void ReadDirectory(const String& path, const String& pattern);
};

void DirectoryImpl::ReadDirectory(const String& path, const String& pattern)
{
    Path = path;
    Pattern = pattern;

    String readPath = Path;
    while (readPath.GetLength() > 0 && readPath[readPath.GetLength()-1] == '/')
        readPath.Remove(readPath.GetLength()-1);

	int fd;
	if ((fd = sceIoDopen(readPath.ToCStr())) >= 0)
	{
		SceIoDirent dir;
		while (sceIoDread(fd, &dir) > 0)
		{
			String name = dir.d_name;
			if (name.GetExtension() == pattern.GetExtension())
				Filenames.PushBack(name);
		}
	}

	CurFile = 0;
}

Directory::Directory(const String& path, const String& pattern)
{
    pImpl = new DirectoryImpl(path, pattern);
}

Directory::~Directory()
{
    delete pImpl;
}

//------------------------------------------------------------------------
// ***** SystemCursorManager

SystemCursorManager::SystemCursorManager(bool systemCursorAvailable) :
    SystemCursorState(systemCursorAvailable, false),
    pImpl(0)
{
}
SystemCursorManager::~SystemCursorManager()
{
}

void SystemCursorManager::update(bool forceSet)
{
    // System cursors update. Since there are none, do nothing.
}

// ----------------------------------------------------------------

class DeviceImpl : public NewOverrideBase<Stat_Default_Mem>
{
public:
    enum
    {
        FRAME_BUFFERS  = 3,
    };

    DeviceImpl(ThreadCommandQueue *commandQueue);
    ~DeviceImpl();

    Device::Window*         pView;
    Ptr<NGP::HAL>  pHal;
    DeviceStatus            Status;

    uint8_t determineFormat(const ViewConfig& config) const;

    bool adjustViewConfig(ViewConfig* config);

    bool initGraphics(const ViewConfig& config, Device::Window* view, ThreadId renderThreadId);
    void shutdownGraphics();
    void beginFrame();
    void presentFrame();

    SceGxmContext*              GxmCtx;
    NGP::MemoryManager*        pMemManager;

    void*                       DispBuffer[FRAME_BUFFERS];
    SceGxmColorSurface          DispSurface[FRAME_BUFFERS];
    SceGxmSyncObject*           DispSync[FRAME_BUFFERS];
    void*                       DepthBuffer;
    SceGxmDepthStencilSurface   DepthSurface;
    unsigned                    BackBuffer, FrontBuffer;
    SceGxmRenderTarget*         RenderTarget;

    Render::RenderTarget*       pDisplayRT;
    SceGxmMultisampleMode       MultisampleMode;

    SceGxmRenderTargetParams    RTParams;
    SceGxmContextParams         ContextParams;

    SceGxmNotification          Notify;

};

DeviceImpl::DeviceImpl(ThreadCommandQueue *commandQueue)
: pView(0), pHal(0), Status(Device_NeedInit)
{
    pHal = *SF_NEW NGP::HAL(commandQueue);
}

DeviceImpl::~DeviceImpl()
{
    pHal.Clear();
    pView = 0;
}

bool DeviceImpl::adjustViewConfig(ViewConfig* config)
{
    config->ViewSize.Width = DISPLAY_WIDTH;
    config->ViewSize.Height = DISPLAY_HEIGHT;
    config->SetFlag(View_FullScreen, true);
    config->SetFlag(View_Stereo, false);

    return true;
}

static void present(const void *framebuf)
{
    SceDisplayFrameBuf* pframebuf = (SceDisplayFrameBuf*) framebuf;

    sceDisplayWaitSetFrameBufMulti(1);
    sceDisplaySetFrameBuf(pframebuf, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
}

bool DeviceImpl::initGraphics(const ViewConfig& config, Device::Window* view, ThreadId renderThreadId)
{
    if (!pHal || !view)
        return false;

    //sceSysmoduleLoadModule(SCE_SYSMODULE_RAZOR_HUD);
    sceSysmoduleLoadModule(SCE_SYSMODULE_RAZOR_CAPTURE);

    pView = view;

    MultisampleMode = SCE_GXM_MULTISAMPLE_NONE;

    SceGxmInitializeParams gxmParams;
    memset(&gxmParams, 0, sizeof(SceGxmInitializeParams));
    gxmParams.flags							= 0;
    gxmParams.displayQueueMaxPendingCount	= 3;
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
    result = sceDisplaySetFrameBuf(&framebuf, SCE_DISPLAY_UPDATETIMING_NEXTVSYNC);
    result &= sceDisplayWaitSetFrameBuf();
    SF_ASSERT(result == SCE_OK);

    BackBuffer = 0;
    FrontBuffer = 1;

    memset(&RTParams, 0, sizeof(SceGxmRenderTargetParams));
    RTParams.flags				= 0;
    RTParams.width				= DISPLAY_WIDTH;
    RTParams.height				= DISPLAY_HEIGHT;
    RTParams.scenesPerFrame		= 8;
    RTParams.multisampleMode    = MultisampleMode;

    UInt32 gpuMemSize;

#if (SCE_PSP2_SDK_VERSION < 0x00996000)
    sceGxmGetRenderTargetMemSizes(&RTParams, &RTParams.hostMemSize, &gpuMemSize);
    RTParams.hostMem				= SF_ALLOC(RTParams.hostMemSize, Stat_Default_Mem);
#else
    sceGxmGetRenderTargetMemSize(&RTParams, &gpuMemSize);
#endif
    RTParams.driverMemBlock		= sceKernelAllocMemBlock("GFxMainRT", SCE_KERNEL_MEMBLOCK_TYPE_USER_RWDATA_UNCACHE, gpuMemSize, 0);

    result = sceGxmCreateRenderTarget(&RTParams, &RenderTarget);
    SF_ASSERT(result == SCE_OK);

    volatile UInt32* pNotify = sceGxmGetNotificationRegion();
    Notify.address = pNotify;

    if (!pHal->InitHAL(Render::NGP::HALInitParams(GxmCtx, Notify, pMemManager)))
    {
        shutdownGraphics();
        return false;
    }

	// Create the default rendertarget. This is required on NGP.
	pDisplayRT = pHal->CreateRenderTarget(RenderTarget, ImageSize(DISPLAY_WIDTH,DISPLAY_HEIGHT),
        DispSurface[BackBuffer], &DepthSurface, DispSync[BackBuffer], MultisampleMode);

    Status = Device_Ready;
    return true;
}

void DeviceImpl::shutdownGraphics()
{
    if ( Status == Device_NeedInit )
        return;

    sceGxmDestroyRenderTarget(RenderTarget);
    RenderTarget = 0;
    sceGxmDestroyContext(GxmCtx);
    GxmCtx = 0;

#if (SCE_PSP2_SDK_VERSION < 0x00996000)
    SF_FREE(RTParams.hostMem);
    RTParams.hostMem = 0;
#endif
    SF_FREE_ALIGN(ContextParams.hostMem);
    ContextParams.hostMem = 0;

    if (pHal)
    {
        pHal->ShutdownHAL();

        //delete pDisplayRT; TODO: implicit surface deletion.
        pDisplayRT = 0;
    }

    delete pMemManager;
    pMemManager = 0;

    Status = Device_NeedInit;
}

void DeviceImpl::beginFrame()
{
    NGP::HALData::UpdateData(pDisplayRT, 0, ImageSize(DISPLAY_WIDTH, DISPLAY_HEIGHT), RenderTarget, 
                             MultisampleMode, DispSurface[BackBuffer], &DepthSurface, DispSync[BackBuffer]);

    //---------------------------------------------------------------------------------------
    // // sceGxmBeginScene called outside of GFx. This allows GFx content to be rendered into the current scene.
    // // To put GFx content into its own scene, uncomment sceGxmBeginScene call (implement a clear), and pass 
    // // false to SetRenderTarget.
    // sceGxmBeginScene(GxmCtx, 0, RenderTarget, NULL, 0, DispSync[BackBuffer], &DispSurface[BackBuffer], &DepthSurface );

    pHal->SetRenderTarget(pDisplayRT, true);
}

void DeviceImpl::presentFrame()
{
    // If the scene is still active, end it. You must pass the HAL's notification address to sceGxmEndScene; otherwise,
    // fencing will not work correctly. If you need the notifications for your own synchronizing purposes, you must 
    // update the notification address that GFx monitors manually, once it is updated by your SceGxmNotification object.
    if (pHal->IsSceneActive())
    {
        SceGxmErrorCode err = sceGxmEndScene(GxmCtx, 0, &Notify);
        SF_ASSERT(err == SCE_OK);

        //---------------------------------------------------------------------------------------
        // // Example of updating the notifications manually:
        // sceGxmEndScene(GxmCtx, 0, &MyFNotify);
        // ... 
        // sceGxmWaitNotification(&MyFNotify);
        // *Notify.address = Notify.value;
    }

    SceDisplayFrameBuf frame;
    frame.base        = DispBuffer[BackBuffer];
    frame.width       = DISPLAY_WIDTH;
    frame.height      = DISPLAY_HEIGHT;
    frame.pitch       = DISPLAY_PITCH;
    frame.size        = sizeof(SceDisplayFrameBuf);
    frame.pixelformat = SCE_DISPLAY_PIXELFORMAT_A8B8G8R8;

    sceGxmPadHeartbeat(&DispSurface[BackBuffer], DispSync[BackBuffer]);

    int result = sceGxmDisplayQueueAddEntry(DispSync[FrontBuffer], DispSync[BackBuffer], &frame);
    SF_ASSERT(result == SCE_OK);

    FrontBuffer = BackBuffer;
    BackBuffer = (BackBuffer + 1) % FRAME_BUFFERS;
}

//------------------------------------------------------------------------
// *** Device.
Device::Device(ThreadCommandQueue *commandQueue)
{
    pImpl = SF_NEW DeviceImpl(commandQueue);
}
Device::~Device()
{
    delete pImpl;
}

HAL* Device::GetHAL() const
{
    return pImpl->pHal;
}

DeviceStatus Device::GetStatus() const
{
    return pImpl->Status;
}

bool Device::InitGraphics(const ViewConfig& config, Device::Window* view, ThreadId renderThreadId)
{
    return pImpl->initGraphics(config, view, renderThreadId);
}

bool Device::ReconfigureGraphics(const ViewConfig& config)
{
    return true;
}

void Device::ShutdownGraphics()
{
    pImpl->shutdownGraphics();
}

bool Device::GraphicsConfigOnMainThread() const
{
    return true;
}

bool Device::AdjustViewConfig(ViewConfig* config)
{
    return pImpl->adjustViewConfig(config);
}

Size<unsigned> Device::GetDefaultViewSize()
{
    return Size<unsigned>(DISPLAY_WIDTH,DISPLAY_HEIGHT);
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

void Device::Clear(UInt32 color)
{
    Render::Color c (color);
    c.SetAlpha(255);
    pImpl->pHal->BeginDisplay(c, Viewport(DISPLAY_WIDTH,DISPLAY_HEIGHT,0,0,DISPLAY_WIDTH,DISPLAY_HEIGHT));
}

void Device::BeginFrame()
{
    pImpl->beginFrame();
}

void Device::PresentFrame(unsigned)
{
    SF_AMP_SCOPE_RENDER_TIMER_ID("Device::PresentFrame", Amp_Native_Function_Id_Present);

    pImpl->presentFrame();
}

void Device::SetWireframe(bool flag)
{
    sceGxmSetFrontPolygonMode(pImpl->GxmCtx, flag ? SCE_GXM_POLYGON_MODE_TRIANGLE_LINE : SCE_GXM_POLYGON_MODE_TRIANGLE_FILL);
}

bool Device::TakeScreenShot(const String&)
{
    return false;
}

UInt32 Device::GetCaps() const
{
    return DeviceCap_Wireframe;
}

}} // Scaleform::Platform


//------------------------------------------------------------------------
int main(int argc, char** argv)
{
    Scaleform::Platform::AppBase* app = Scaleform::Platform::AppBase::CreateInstance();
    int  result = app->AppMain(argc, argv);
    Scaleform::Platform::AppBase::DestroyInstance(app);
    return result;
}
