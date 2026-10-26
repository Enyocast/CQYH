/**************************************************************************

Filename    :   Platform_Android.h
Content     :   
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#ifndef INC_Platform_Android_H
#define INC_Platform_Android_H

#include "GFx_Kernel.h"
#include "GFx_Renderer_GL.h"
#include "Platform.h"

#include <jni.h>

namespace Scaleform { namespace Platform {

class AppThread;

#if 0
class AndroidAssetFile : public File
{
    String Path;
    int    Errno;
    
    static jmethodID AssetManager_open, InputStream_read, InputStream_seek

 public:
    AndroidAssetFile(jobject 
    virtual const char* GetFilePath()  { return Path.ToCStr(); }
                                                                                        

    virtual bool        IsValid() { return 1; }
    virtual bool        IsWritable() { return 0; }
                                                                                        
    // Return position
    virtual int         Tell ();
    virtual SInt64      LTell () { return Tell(); }
    
    // File size                                                                        
    virtual int         GetLength ();
    virtual SInt64      LGetLength () { return GetLength(); }
                                                                                        
    virtual int         GetErrorCode() { return Errno; }

    virtual int         Write(const UByte *pbuffer, int numBytes) { return -1; }
    virtual int         Read(UByte *pbuffer, int numBytes);
    virtual int         SkipBytes(int numBytes) { return Skip(numBytes); }
    virtual int         BytesAvailable() { return GetLength()-Tell(); }

    virtual bool        Flush() { return 1; }
                                                                                            
    virtual int         Seek(int offset, int origin=Seek_Set);
    virtual SInt64      LSeek(SInt64 offset, int origin=Seek_Set) { return Seek(offset, origin); }

    virtual bool        ChangeSize(int newSize) { return 0; }
    virtual int         CopyFromStream(File *pstream, int byteSize) { return -1; }

    virtual bool        Close();
};
#endif

class AppImpl : public Device::Window, public AppImplBase
{
public:
    AppImpl(AppBase* app);

    // Window Interface
    virtual void* GetHandle() { return this; }
    virtual void  GetViewConfig(ViewConfig *config) const { *config = Config; }
    virtual void  ConfigureWindow(ViewConfig& newConfig);    

    virtual void  OnSize(const Size<unsigned>& newSize);

    bool          setupWindow(const String& title, const ViewConfig& config);
    void          failSetupWindow(const char* cause);

    void          WaitForInit();

    File* OpenAssetFile(const char* name, int flags);

    void SetupFiles();
    void OnOrientation1(int orient, bool flip);
    void OnTouchMouse1(int action, float x, float y);
    void OnTouch1(int pointerId, int action, float x, float y);
    void OnGesture1(int action, int mode, float x, float y, float panx, float pany, float scale);
    void OnKeyboard1(int kbId, int key, int down, int mods);

    //bool          AdvanceAndDisplay();

    // AppImplBase
    virtual ThreadingType   GetArgsThreadingType() const;
    virtual void            ApplyViewConfigArgs(ViewConfig* config, const Args& args);
    virtual void            killWindow();


    AppThread*      pAppThread;
    RenderHALThread* pRenderThread;
    bool            RTInitialized;
    Event           RTInitializedEvent;
    bool            Created;
    unsigned int    Modifiers;
    // Window location saved when going full-screen.
    ViewConfig      OldConfig;

    bool            NeedPaint, BlockOnSize, CursorEnabled;

    JavaVM*         pJVM;
    jobject         MainActivity;
    jclass          ActivityClass;
    jobject         AssetManager;
    jclass          AssetManagerClass;
    String          FilesDir;
};


class FileRange : public DelegatedFile
{
    SInt64 Start, Size;
public:
    // Constructors
    FileRange(File *pfile, SInt64 start, SInt64 size) : DelegatedFile(pfile), Start(start), Size(size) {}

    virtual int         Tell()                                                  { return (int)(pFile->Tell()-Start); }
    virtual SInt64      LTell()                                                 { return pFile->LTell()-Start; }
    
    virtual int         GetLength()                                             { return Size; }
    virtual SInt64      LGetLength()                                            { return Size; }
    
    //virtual int         Write(const UByte *pbuffer, int numBytes)              { return pFile->Write(pbuffer,numBytes); }  
    virtual int         Read(UByte *pbuffer, int numBytes)
    {
        SInt64 pos = LTell();
        if (pos + numBytes >= Size)
            numBytes = Size - pos;
        return pFile->Read(pbuffer,numBytes);
    }
    
    //virtual int         SkipBytes(int numBytes)                                { return pFile->SkipBytes(numBytes); }      
    virtual int         BytesAvailable()
    {
        return Size-Tell();
    }

    virtual int         Seek(int offset, int origin=Seek_Set)                 { return (int)LSeek(offset,origin); }
    virtual SInt64      LSeek(SInt64 offset, int origin=Seek_Set)
    {
        if (origin == Seek_Set)
            offset += Start;
        else if (origin == Seek_End)
        {
            offset = Start + Size - offset;
            origin = Seek_Set;
        }
        return pFile->LSeek(offset,origin);
    }
};

}}

#define SF_ANDROID_JNI(SystemClass,AppClass,Package,Activity,args)      \
using namespace Scaleform;                                              \
using namespace Render;                                                 \
using namespace Platform;                                               \
static unsigned char SystemStorage[sizeof(SystemClass)];                \
static AppClass*     pApp;                                              \
static AppImpl*      pImpl;                                             \
static JavaVM   *pJVM = 0;                                              \
                                                                        \
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) \
{                                                                       \
    pJVM = jvm;                                                         \
    JNIEnv* env = NULL;                                                 \
    if (jvm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK)           \
    {                                                                   \
        SF_DEBUG_MESSAGE(1, "JNI_OnLoad: Could not get environment..\n"); \
        return -1;                                                      \
    }                                                                   \
                                                                        \
    SF_DEBUG_MESSAGE(1, "JNI_OnLoad: Done\n");                          \
    return JNI_VERSION_1_6;                                             \
}                                                                       \
                                                                        \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeAppInit(JNIEnv * env, jobject obj) \
{                                                                       \
    new (SystemStorage) SystemClass();                                  \
    pApp = new AppClass args;                                           \
    pImpl = (AppImpl*)pApp->GetAppImpl();                               \
    pImpl->pJVM = pJVM;                                                 \
    SF_DEBUG_MESSAGE(1, #Activity " AppInit");                          \
    pImpl->pAppThread->Start(Thread::Running);                          \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnCreate(JNIEnv * env, jobject obj) \
{                                                                       \
    pImpl->MainActivity = obj;                                          \
    pImpl->SetupFiles();                                                \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnResume(JNIEnv * env, jobject obj) \
{                                                                       \
    SF_DEBUG_MESSAGE(1, #Activity " resume");                           \
    pImpl->NextUpdateTicks = Timer::GetTicks()/1000;                    \
    pImpl->pAppThread->OnLifecycleEvent(GFx::AppLifecycleEvent::OnResume);      \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnPause(JNIEnv * env, jobject obj) \
{                                                                       \
    pImpl->pAppThread->OnLifecycleEvent(GFx::AppLifecycleEvent::OnPause);       \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnOpenFile(JNIEnv * env, jobject obj, jstring path) \
{                                                                       \
    int len = env->GetStringLength(path);                               \
    const jchar *jchars = env->GetStringChars(path, NULL);              \
    String fileName;                                                    \
    for (int i = 0; i < len; i++)                                       \
        fileName.AppendChar(jchars[i]);                                 \
    env->ReleaseStringChars(path,jchars);                               \
                                                                        \
    if (pImpl->pRenderThread)                                           \
        pImpl->pAppThread->OnDropFiles(fileName);                       \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_GLView_NativeReset(JNIEnv * env, jobject obj) \
{                                                                       \
    if (!pImpl->RTInitialized)                                          \
        pImpl->RTInitializedEvent.Wait();                               \
    if (pImpl->Created)                                                 \
    {                                                                   \
        SF_DEBUG_MESSAGE(1, "Resetting gl context");                    \
        ((Render::GL::HAL*)pApp->GetDevice()->GetHAL())->ResetContext();\
        return;                                                         \
    }                                                                   \
    SF_DEBUG_MESSAGE1(1, #Activity " RT init graphics %d", pImpl->RTInitialized);\
    if (!pImpl->pRenderThread->InitGraphics_RenderThread())             \
        SF_DEBUG_MESSAGE(1, "InitGraphics failed");                     \
    pImpl->Created = 1;                                                 \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_GLView_NativeResize(JNIEnv * env, jobject obj,  jint width, jint height) \
{                                                                       \
    pImpl->pRenderThread->AbortFrame();                                 \
    pImpl->pAppThread->OnSize(width,height);                            \
    pImpl->pRenderThread->OnSize_RenderThread(width, height);           \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_GLView_NativeDraw(JNIEnv * env, jobject obj) \
{                                                                       \
    pImpl->pRenderThread->DrawFrame_RenderThread();                     \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnOrientation(JNIEnv * env, jobject obj,  jint orient, jboolean flip) \
{                                                                       \
    pImpl->OnOrientation1(orient, flip);                                \
}                                                                       \
                                                                        \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnKey(JNIEnv * env, jobject obj, jboolean down, jint key) \
{                                                                               \
    pImpl->OnKeyboard1(0, key, down, 0);                                        \
}                                                                               \
                                                                                \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnTouch(JNIEnv * env, jobject obj, jint pointerId, jint event, jfloat x, jfloat y) \
{                                                                               \
    pImpl->OnTouch1(pointerId, event, x, y);                                    \
}                                                                               \
                                                                                \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnGesture(JNIEnv * env, jobject obj, jint event, jint mode, jfloat x, jfloat y, jfloat panx, jfloat pany, jfloat scale) \
{                                                                               \
    pImpl->OnGesture1(event, mode, x, y, panx, pany, scale);                    \
}                                                                               \
                                                                                \
extern "C" JNIEXPORT void JNICALL Java_##Package##_##Activity##_NativeOnTouchMouse(JNIEnv * env, jobject obj, jint event, jfloat x, jfloat y) \
{                                                                               \
    pImpl->OnTouchMouse1(event, x, y);                                          \
}

#include "Platform_AppThread.h"

#endif //INC_Platform_Android_H
