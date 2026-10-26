/**************************************************************************

Filename    :   Platform_Android_GL.cpp
Content     :   Platform::App implementation for Android GL.
Created     :   Jan 10, 2008
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

// GFx Includes
#include "Platform.h"
#include "Platform_Android.h"
#include "Platform_AppThread.h"
#include "GFx/GFx_Loader.h"
#include "Kernel/SF_System.h"
#include "Kernel/SF_WString.h"
#include "Kernel/SF_HeapNew.h"

#include "Render/GL/GL_HAL.h"

//------------------------------------------------------------------------

namespace Scaleform {


extern File *FileFILEOpen(FILE *file, const char* path, int closeFd);


namespace Platform {


// ***** AppImpl

AppImpl::AppImpl(AppBase* app) : 
    AppImplBase(app),
    RTInitialized(false),
    NeedPaint(true),
    BlockOnSize(false)
{
    Created = false;
    CursorEnabled = true;
    Modifiers = 0;
    pAppThread = new AppThread(app);
}

bool AppImpl::setupWindow(const String& title, const ViewConfig& config)
{
    Title  = title;
    Config = config;

    // This is called after the render thread object is created in OnInitHelper, so let the RT proceed now.
    RTInitialized = 1;
    RTInitializedEvent.PulseEvent();
    pRenderThread = pApp->GetAppRenderThread();
 
    glLineWidth(1.0f);

    return 1;
}

void AppImpl::SetupFiles()
{
    JNIEnv* jenv;
    if (pJVM->GetEnv((void**)&jenv, JNI_VERSION_1_6) < 0)
    {
        SF_DEBUG_ERROR(1, "Cannot get jni env");
        abort();
    }

    ActivityClass = jenv->GetObjectClass(MainActivity);
    jmethodID getAssets = jenv->GetMethodID(ActivityClass, "getAssets", "()Landroid/content/res/AssetManager;");

    AssetManager = jenv->CallObjectMethod(MainActivity, getAssets);
    AssetManagerClass = jenv->GetObjectClass(AssetManager);

    jmethodID getFilesDir = jenv->GetMethodID(ActivityClass, "getFilesDir", "()Ljava/io/File;");
    jobject filesDirH = jenv->CallObjectMethod(MainActivity, getFilesDir);
    jclass FileClass = jenv->GetObjectClass(filesDirH);
    jmethodID getAbsPath = jenv->GetMethodID(FileClass, "getAbsolutePath", "()Ljava/lang/String;");
    jstring filesDir = (jstring) jenv->CallObjectMethod(filesDirH, getAbsPath);

    jboolean copy;
    const char* fs = jenv->GetStringUTFChars(filesDir, &copy);

    // Does not exist by default.
    mkdir(fs, 0700);

    FilesDir = fs;
    FilesDir += "/";
    jenv->ReleaseStringUTFChars(filesDir, fs);

    SF_DEBUG_MESSAGE1(1, "Files dir: %s", fs);
}

File* AppImpl::OpenAssetFile(const char* name, int flags)
{
    JNIEnv* jenv;
    bool didAttach = false;
    if (pJVM->GetEnv((void**)&jenv, JNI_VERSION_1_6) < 0)
    {
        if (pJVM->AttachCurrentThread(&jenv, 0) < 0)
        {
            SF_DEBUG_ERROR(1, "OpenAssetFile: Cannot get jni env");
            return 0;
        }

        didAttach = true;
    }

    jmethodID openFd = jenv->GetMethodID(AssetManagerClass, "openFd", "(Ljava/lang/String;)Landroid/content/res/AssetFileDescriptor;");
    jobject jfd = jenv->CallObjectMethod(AssetManager, openFd, jenv->NewStringUTF(name));

    if (!jfd)
    {
        SF_DEBUG_WARNING1(1, "OpenAssetFile: %s not found\n", name);

        if (didAttach)
            pJVM->DetachCurrentThread();
        return 0;
    }

    jclass AssetFdClass = jenv->GetObjectClass(jfd);
    jmethodID getParcelFd = jenv->GetMethodID(AssetFdClass, "getParcelFileDescriptor", "()Landroid/os/ParcelFileDescriptor;");
    jmethodID getStartOffset = jenv->GetMethodID(AssetFdClass, "getStartOffset", "()J");
    jmethodID getLength = jenv->GetMethodID(AssetFdClass, "getLength", "()J");
    jlong start = jenv->CallLongMethod(jfd, getStartOffset);
    jlong length = jenv->CallLongMethod(jfd, getLength);

    SF_DEBUG_MESSAGE3(1, "Loading asset %s: start %lld size %lld\n", name, start, length);
    jfd = jenv->CallObjectMethod(jfd, getParcelFd);

    jclass ParcelFdClass = jenv->GetObjectClass(jfd);

    // This can be used instead on Android 3
#if 0 
    jmethodID getFd = jenv->GetMethodID(ParcelFdClass, "getFd", "()I");
    int fd = jenv->CallIntMethod(jfd, getFd);

#else
    jmethodID getFd = jenv->GetMethodID(ParcelFdClass, "getFileDescriptor", "()Ljava/io/FileDescriptor;");
    jfd = jenv->CallObjectMethod(jfd, getFd);
    jclass FdClass = jenv->GetObjectClass(jfd);

    jfieldID descriptor = jenv->GetFieldID(FdClass, "descriptor", "I");
    int fd = jenv->GetIntField(jfd, descriptor);
#endif
    SF_DEBUG_WARNING2(fd < 0, "Asset %s: bad fd: %d", name, fd);

    if (didAttach)
        pJVM->DetachCurrentThread();

    if (fd >= 0)
    {
        FILE* pfile = fdopen(fd, "rb");
        fseek(pfile, start, SEEK_SET);
        return SF_NEW FileRange(FileFILEOpen(pfile, name, 1), start, length);
    }
    else
        return 0;
}

void AppImpl::failSetupWindow(const char* cause)
{
}

void AppImpl::killWindow()
{
    if (!Created)
        return;

    Created = 0;
}

void AppImpl::ConfigureWindow(ViewConfig& config)
{
}

void AppImpl::OnSize(const Size<unsigned>& newSize)
{
    Config.ViewSize = newSize;
    pApp->OnSize(Config.ViewSize);
}

void AppImpl::WaitForInit()
{
    pAppThread->WaitForInit();
}

ThreadingType AppImpl::GetArgsThreadingType() const
{
    // Android must be multithreaded.
    return TT_MultiThreaded;
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

    SF_DEBUG_MESSAGE(1, "Device initGraphics ");

    // Configure renderer in "Dependent mode", honoring externally
    // configured device settings.
    if (!pHal->InitHAL(Render::GL::HALInitParams()))
    {
        shutdownGraphics();
        pWindow = 0;
        return false;
    }

    SF_DEBUG_MESSAGE(1, "Device initGraphics finished");

    Status = Device_Ready;
    return true;
}

bool DeviceImpl::reconfigureGraphics(const ViewConfig& config)
{
    return true;
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

    return true;
}
void Device::ShutdownGraphics()
{
    pImpl->shutdownGraphics();
}

Size<unsigned> Device::GetDefaultViewSize()
{
    return Size<unsigned>(800, 480);
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
    SF_AMP_SCOPE_RENDER_TIMER_ID("Device::PresentFrame", Amp_Native_Function_Id_Present);
}

void Device::BeginFrame()
{
}

void Device::SetWireframe(bool wireframeEnable)
{
}

bool Device::TakeScreenShot(const String&)
{
    return false;
}

UInt32 Device::GetCaps() const
{
    return 0;
}


//------------------------------------------------------------------------
// ***** AppBase

AppBase::AppBase()
 : Cursor(false), ShuttingDown(false)
{
    pImplBase = pImpl = SF_NEW AppImpl(this);
    pDevice = 0;
}
AppBase::~AppBase()
{
    delete pImpl;
}

void AppImpl::ApplyViewConfigArgs(ViewConfig* config, const Args& args)
{
    // No options modify view config arguments/flags.
}

//------------------------------------------------------------------------

// This call cleans up the application and kills the window.
void AppBase::Shutdown()
{
    pImpl->killWindow();
    ShuttingDown = true;
}

bool AppBase::IsPadConnected(unsigned)
{
    return false;
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
    return SF_ANDROID_CONTENT_DIR;
}

static const GFx::Event::EventType MouseEvents[] = {GFx::Event::MouseDown, GFx::Event::MouseUp, GFx::Event::MouseMove, GFx::Event::Unknown, GFx::Event::Unknown,
GFx::Event::MouseDown, GFx::Event::MouseUp, GFx::Event::MouseMove};

void AppImpl::OnTouchMouse1(int action, float x, float y)
{
    if (MouseEvents[action & 0xff] != GFx::Event::Unknown)
    {
        GFx::MouseEvent event (MouseEvents[action & 0xff], 0, x, y);
        pAppThread->OnEvent(event);
    }
}

static const GFx::Event::EventType TouchEvents[] = {GFx::Event::TouchBegin, GFx::Event::TouchEnd, GFx::Event::TouchMove, GFx::Event::Unknown, GFx::Event::Unknown,
GFx::Event::TouchBegin, GFx::Event::TouchEnd, GFx::Event::TouchMove};

void AppImpl::OnTouch1(int pointerId, int action, float x, float y)
{
    if (TouchEvents[action] != GFx::Event::Unknown)
    {
        GFx::TouchEvent event(TouchEvents[action], pointerId, x, y, 0, 0, pointerId == 0);
        pAppThread->OnEvent(event);
    }
}

static const GFx::Event::EventType GestureEvents[] = {GFx::Event::GestureEnd, GFx::Event::GestureBegin, GFx::Event::Gesture, GFx::Event::GestureSimple};
static const unsigned GestureTypes[] = {0, GFx::GestureEvent::GestureBit_Pan, GFx::GestureEvent::GestureBit_Zoom, GFx::GestureEvent::GestureBit_Swipe};

void AppImpl::OnGesture1(int action, int mode, float x, float y, float panx, float pany, float scale)
{
    GFx::GestureEvent event(GestureEvents[action], GestureTypes[mode], x, y, panx, pany, scale, scale, 0);
    pAppThread->OnEvent(event);
}

void AppImpl::OnOrientation1(int orient, bool flip)
{
    if (orient == 1)
    {
        if (flip)
            pAppThread->OnOrientation(Render::Viewport::View_Orientation_R90, false);
        else
            pApp->OnOrientation(Render::Viewport::View_Orientation_L90, false);
    }
    else
    {
        pApp->OnOrientation(Render::Viewport::View_Orientation_Normal, false);
    }
}

void AppImpl::OnKeyboard1(int kbId, int key, int down, int mods)
{
    GFx::KeyEvent event(down ? GFx::Event::KeyDown : GFx::Event::KeyUp, (Key::Code)key, 0, 0, mods, kbId);
    pAppThread->OnEvent(event);
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

    return 0;
}

String AppBase::GetContentDirectory()
{
    return SF_ANDROID_CONTENT_DIR;
}

int AppBase::GetKeyboardCount()
{
    return 1;
}

int AppBase::GetMouseCount()
{
    return 1;
}

void AppBase::SetOrientationMode(bool)
{
}

UInt32 AppBase::GetCaps() const
{
    return 0;
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


String AppBase::GetSaveDataDirectory()
{
    return pImpl->FilesDir;
}


}} // Scaleform::Platform
