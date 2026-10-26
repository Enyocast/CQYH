/**************************************************************************

Filename    :   FxPlayerAppBase.cpp
Content     :   FxPlayerAppBase and supporting code implementation.

Created     :   November, 2010
Authors     :   Michael Antonov, Dmitry Polenur, Maxim Didenko, 

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "FxPlayerAppBase.h"
#include "GFx/AMP/Amp_Server.h"
//#include "Render/Render_Amp.h"
#include "FxPlayerLog.h"

#ifdef SF_OS_WIN32
    #include "GFx_FontProvider_Win32.h"
    //#include "FileFindWin32.h"

    #ifdef __cplusplus_cli
    #using <mscorlib.dll>
    using namespace System;
    #endif
#endif

#ifdef GFX_ENABLE_XML
    #include "GFx_XML.h"
    #include "GFx/XML/XML_DOM.h"
#endif

#include "GFx/IME/GFx_IMEManager.h"

#if defined(SF_ENABLE_IME) && defined(SF_ENABLE_IME_WIN32)
#include "GFxIME/GFx_IMEManagerWin32.h"
#endif

#ifdef SF_ENABLE_THREADS
#include "GFx/GFx_TaskManager.h"    
#endif

#ifdef GFX_AS2_ENABLE_SHAREDOBJECT
#include "FxSharedObjectManager.h"
#endif  // GFX_AS2_ENABLE_SHAREDOBJECT

#ifdef GFX_ENABLE_SOUND
#include "Sound/Sound_SoundRenderer.h"
#include "Sound/Sound_SoundEvent.h"
#include "Sound/Sound_SoundEventFMOD.h"
#include "Sound/Sound_SoundEventWwise.h"
#include "GFx/GFx_Audio.h"
#include "FxSoundFMOD.h"
#include "FxSoundWwise.h"
#endif

#include "GFx/GFx_ImageCreator.h"

#include "Render/ImageFiles/PNG_ImageFile.h"
#include "Render/ImageFiles/DDS_ImageFile.h"
#if defined (SF_OS_WIIU)
#include "Render/ImageFiles/GTX_ImageFile.h"
#endif
#if defined (SF_OS_NGP)
#include "Render/ImageFiles/GXT_ImageFile.h"
#endif
#include "Render/Render_GlyphCacheConfig.h"

#ifdef GFX_ENABLE_VIDEO
// Core video support
#include "Video/Video_Video.h"
#if   defined(SF_OS_WIN32)
#include "Video/Video_VideoPC.h"
#elif defined(SF_OS_XBOX360)
#include "Video/Video_VideoXbox360.h"
#elif defined(SF_OS_PS3)
#include "Video/Video_VideoPS3.h"
#endif
// Video system sound interfaces
#ifdef GFX_VIDEO_USE_SYSTEM_SOUND
#if   defined(SF_OS_WIN32)
#include "Video/Video_VideoSoundSystemDX8.h"
#elif defined(SF_OS_MAC)
#include "Video/Video_VideoSoundSystemMac.h"
#elif defined(SF_OS_XBOX360)
#include "Video/Video_VideoSoundSystemXA2.h"
#elif defined(SF_OS_PS3)
#include "Video/Video_VideoSoundSystemPS3.h"
#elif defined(SF_OS_WII)
#include "Video/Video_VideoSoundSystemWii.h"
#elif defined(SF_OS_WIIU)
#include "Video/Video_VideoSoundSystemWiiU.h"
#endif
// FMOD and Wwise system sound interfaces
#elif defined(GFX_VIDEO_USE_FMOD)
#include "Video/Video_VideoSoundSystemFMOD.h"
#elif defined(GFX_VIDEO_USE_WWISE)
#include "Video/Video_VideoSoundSystemWwise.h"
#endif
#endif // GFX_ENABLE_VIDEO

//#include "GFx_FontProvider_NGP.h"
//#include "GFx_FontProvider_FT2.h"

//------------------------------------------------------------------------
/** 
A sample sound event callback processor.  This class can be used as a function object
to override _global.gfxProcessSound for sound playback. Overridng the _global.gfxProcessSound
method will, by default, cause most CLIK Components to send sound events to this class. It can
also be used to trigger sound playback from ActionScript using _global.gfxProcessSound().

Note that the implementation of this function is at the discretion of the developer.
*/

#if defined(GFX_ENABLE_SOUND)
class GFxSoundEventCallback : public FunctionHandler
{
public:
    GFxSoundEventCallback (const Movie* pmovie) : pMovie(pmovie)
    {   
        pApp = (FxPlayerAppBase*)pMovie->GetUserData();  

#if defined(GFX_SOUND_FMOD) && !defined(GFX_SOUND_WWISE)
        if (pApp->pSoundFMODSystem)
        {   // FMOD Ex (implementation based on GSoundRender)
            pSoundEvent = *new SoundEventFMOD;    
            pSoundEvent->pUserData = pApp->pSoundFMODSystem->GetSoundRenderer();
            // FMOD Designer
            //pSoundEvent = *new SoundEventFMODDesigner("examples.fev", "examples/FeatureDemonstration");
            //pSoundEvent->pUserData = pApp->pSoundFMODSystem->pSoundRenderer->GetFMODEventSystem();
        }
#elif defined(GFX_SOUND_WWISE)
        // AK Wwise SoundFrame
        pSoundEvent = *new SoundEventWwiseSF; 
#endif
        bCLIKSound = pApp->bCLIKSound; // Is CLIK soundEvent processing enabled ("-cksd" command line parameter)
        pLog = pMovie->GetLog();   // Used for logging debug messages
    }

    /** Called when _global.gfxProcessSound() is called in ActionScript */
    void Call(const Params& params)
    {
        bool bCallProcessed = ProcessSoundEvent(params);
        if (!bCallProcessed && bCLIKSound) 
        {
            if (params.ArgCount >= 1)
            {
                if (params.pArgs[0].IsDisplayObject() && params.ArgCount == 3)
                    ProcessCLIKSoundEvent(params);
            }            
        } 
    }

    /** FMOD-based sample for standard sound processing in FxPlayer. */     
    bool ProcessSoundEvent(const Params& params)
    {
        if (params.pArgs[0].GetType() != Value::VT_String)
            return false;

        const String methodName = params.pArgs[0].GetString();        

        // Usage:   _global.gfxProcessSound(Method:String, Command:String, Filename:String)
        // Example: _global.gfxProcessSound("GFxSound_PostEvent", "Play", "electric.wav");
        if (SFstricmp(methodName, "GFxSound_PostEvent") == 0)
        {
            if (params.ArgCount >= 2 && params.pArgs[1].GetType() == Value::VT_String)
            {
                const String command = params.pArgs[1].GetString();
                String filename;
                if (params.ArgCount >= 3 && params.pArgs[2].GetType() == Value::VT_String)
                    filename = params.pArgs[2].GetString();  

                // This log message can be commented or uncommented at the user's discretion.
                pLog->LogMessage("gfxProcessSound Callback - \n"
                    "\tCommand: %s\n"
                    "\tFilename: %s\n\n", 
                    command.ToCStr(), filename.ToCStr());

                pSoundEvent->PostEvent(command, filename);
                return true;
            } 
        }
        // Usage:   _global.gfxProcessSound(Method:String, Parameter:String, Value:Number, Filename:String)
        // Example: _global.gfxProcessSound("GFxSound_SetParam", "Pan", -1.0, "electric.wav");
        else if (SFstricmp(methodName, "GFxSound_SetParam") == 0)
        {
            if (params.ArgCount >= 2 &&
                params.pArgs[1].GetType() == Value::VT_String &&
                params.pArgs[2].GetType() == Value::VT_Number)
            {
                const String parameter = params.pArgs[1].GetString();
                const Double paramvalue = params.pArgs[2].GetNumber();
                String filename;
                if (params.ArgCount >= 2 && params.pArgs[3].GetType() == Value::VT_String)
                    filename = params.pArgs[3].GetString();  

                // This log message can be commented or uncommented at the user's discretion.
                pLog->LogMessage("gfxProcessSound Callback -\n"
                    "\tParameter: %s\n" 
                    "\tParameter Value: %f\n"
                    "\tFilename: %s\n\n",
                    parameter.ToCStr(), paramvalue, filename.ToCStr());

                pSoundEvent->SetParam(parameter, (float)paramvalue, filename);
                return true;
            }
        }

        // If we're here, the call could not be processed.
        return false;
    }

    /** 
    Sample internal sound processing for CLIK components. CLIK Component events are identified by their
    first parameter, a Value reference to themselves from which extra data can be retrieved. This event is
    fired by all CLIK components who inherit from UIComponent (see UIComponent::dispatchEventAndSound()).

    This method is disabled by default. It can be enabled using the -cksd command line option.

    By default, this method will search for SoundTheme+SoundName.wav (eg. defaultRollOver.wav). It is designed
    to hook into to a more advanced engine sound tool where a theme and name can easily be mapped to a particular
    sound file.

    Usage: _global.gfxProcessSound(CLIK Component:MovieClip, SoundTheme:String, SoundName:String);
    */
    bool ProcessCLIKSoundEvent(const Params& params)
    {
        // Retrieve arguments from the function parameters
        const String componentName = params.pArgs[0].ToString();
        const String soundThemeName = params.pArgs[1].GetString();
        const String soundEventName = params.pArgs[2].GetString(); 
        String soundName = String(soundThemeName.ToCStr(), soundEventName.ToCStr(), ".wav");

        // This log message can be commented or uncommented at the user's discretion.
        if (pLog)
            pLog->LogMessage("gfxProcessSound Callback - \n"
            "\tComponent: %s\n"
            "\tSound Theme: %s\n"
            "\tSoundEvent: %s\n"
            "\tAttempting to play file: %s\n\n",
            componentName.ToCStr(), soundThemeName.ToCStr(), 
            soundEventName.ToCStr(), soundName.ToCStr());     

        if (pSoundEvent)
        {
            // Play the sound with the default parameters.
            pSoundEvent->SetParam("Volume", 0.4f, soundName);                   
            pSoundEvent->SetParam("Pan", 0.f, soundName);
            pSoundEvent->PostEvent("Play", soundName);
        }
        return true;
    }

private:
    const Movie* pMovie;
    FxPlayerAppBase* pApp;
    Ptr<GFx::Log> pLog;

    bool bCLIKSound;
    Ptr<SoundEvent> pSoundEvent;
};
#endif // GFX_ENABLE_SOUND

// FunctionHandler for logging CLIK ADDED_TO_STAGE events (widget initialized callbacks).
class LogLoadHandler : public FunctionHandler
{
public:
	LogLoadHandler (const Movie* pmovie) : pMovie(pmovie)
	{   
		pLog = pMovie->GetLog();   // Used for logging debug messages
	}

	void Call(const Params& params)
	{
		const char* WidgetPathString = params.pArgs[1].GetString();
		pLog->LogMessage("CLIK Load: %s\n", WidgetPathString);
	}

private:
	const Movie* pMovie;
	Ptr<GFx::Log> pLog;
};

// This timer is used when performing automated testing. Without a deterministic timer,
// the tests may not execute exactly everytime, causing false failures.
class AutoTestTimerOverride : public Timer::TimerOverride
{
public:
    AutoTestTimerOverride() : CurrentTicks(1) { };

    virtual UInt32 GetTicksMs()
    {
        return (UInt32)(GetRawTicks() / Timer::MksPerMs);
    }

    virtual UInt64 GetRawTicks()
    {
        // Note: this is incremented each time so that if a .swf is waiting in a loop
        // for a certain time period to pass, it will not freeze in an infinite loop.
        // It will however take quite a long time to complete.
        return CurrentTicks++;
    }

    virtual UInt64 GetRawFrequency()
    {
        return Timer::MksPerSecond;
    }

    void AdvanceTicks(UInt64 ticks)
    {
        CurrentTicks += ticks;
    }
private:
    UInt64 CurrentTicks;

} AutoTimer;



class FxPlayerCommandChangeRes : public FxPlayerCommand
{
    static const unsigned ResList[5][2];
    static Size<unsigned> GetRes(unsigned i) { return Size<unsigned>(ResList[i][0], ResList[i][1]); }
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ResIndex = (app->ResIndex + 1) % 5;
        Size<unsigned> newSize = GetRes(app->ResIndex);
        if (newSize == app->GetViewSize())
        {
            app->ResIndex = (app->ResIndex + 1) % 5;
            newSize = GetRes(app->ResIndex);
        }
        app->OnSize(newSize);
    }
    virtual String GetHelpString() const
    {
        return "Toggle display resolution";
    }
};
const unsigned FxPlayerCommandChangeRes::ResList[5][2] = {{640,480}, {1024, 768}, {1280, 720}, {1280, 1024}, {1920, 1080}};

class FxPlayerCommandScaledDisplay : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ScaleEnable = !app->ScaleEnable;
        app->UpdateViewSize();
    }
    virtual String GetHelpString() const
    {
        return "Toggle scaled display";
    }
};

class FxPlayerCommandWireframe : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->Wireframe = !app->Wireframe;
        app->GetRenderThread()->SetWireframe(app->Wireframe);
        app->GetRenderThread()->DrawFrame();
    }
    virtual String GetHelpString() const
    {
        return "Toggle wire frame";
    }
};

class FxPlayerCommandAntialiasingMode : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ToggleAaMode();
    }
    virtual String GetHelpString() const
    {
        return "Toggle anti-aliasing mode";
    }
};

class FxPlayerCommandFullscreen : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);

        Platform::ViewConfig config;
        app->GetViewConfig(&config);        
        // Use default position for mode switching.
        config.ClearSize();
        config.ClearPos();
        config.SetFlag(Platform::View_FullScreen, !config.HasFlag(Platform::View_FullScreen));
        
        app->ReconfigureGraphics(config);
        app->UpdateViewSize();
        app->SetWindowTitle(app->GetAppTitle());
    }
    virtual String GetHelpString() const
    {
        return "Toggle full-screen";
    }
};

class FxPlayerCommandDynamicTextures : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED3(app, controllerIdx, keyDown);
#if defined(FXPLAYER_RENDER_DIRECT3D) && (SF_D3D_VERSION != 10) && !defined(SF_OS_XBOX360)
        /*
        // MA TBD
        app->VMCFlags = (app->VMCFlags & ~FxPlayerAppBase::rendererHAL_type::VMConfig_UseDynamicTex) |
            ((~(app->VMCFlags & FxPlayerAppBase::rendererHAL_type::VMConfig_UseDynamicTex)) & FxPlayerAppBase::rendererHAL_type::VMConfig_UseDynamicTex);
        app->pRenderer->ResetVideoMode();
        app->SetRendererDependentVideoMode();    
        */
#endif
    }
    virtual String GetHelpString() const
    {
        return "Toggle dynamic textures";
    }
};



class FxPlayerCommandFastMode : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->MeasurePerformance = !app->MeasurePerformance;
        //app->pRenderStats->GetTessStatistics(); // Clear stats
        app->AdjustFrameTime();
        app->LastFPS = 0;
        if (!app->MeasurePerformance)
        {
            app->SetWindowTitle(app->GetAppTitle());
        }
    }
    virtual String GetHelpString() const
    {
        return "Toggle fast mode (FPS)";
    }
};

class FxPlayerCommandFastForward : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->FastForward = !app->FastForward;
        app->AdjustFrameTime();
        app->AmpDirty = true;    
    }
    virtual String GetHelpString() const
    {
        return "Toggle fast forward";
    }
};

class FxPlayerCommandVSync : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
		// MA TBD:

        Platform::ViewConfig config;
        app->GetViewConfig(&config);
        config.SetFlag(Platform::View_VSync, !config.HasFlag(Platform::View_VSync));
        config.ViewFlags &= ~Platform::View_Pos;

        app->ReconfigureGraphics(config);
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Toggle VSync";
    }
};

class FxPlayerCommandPause : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->Paused = !app->Paused;
        // Note that toggling play state through pMovie->SetPlayState would only pause root clip,
        // not children. So instead we just set the global variable above which prevents Advance.
        // However, we may still need to save/restore state in frame.
        app->OnPause(app->Paused);
        app->AdjustFrameTime();
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Toggle pause";
    }
};

class FxPlayerCommandObjectsReport : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        // Note that toggling play state through pMovie->SetPlayState would only pause root clip,
        // not children. So instead we just set the global variable above which prevents Advance.
        // However, we may still need to save/restore state in frame.
        app->OnObjectsReport();
    }
    virtual String GetHelpString() const
    {
        return "Print objects report";
    }
};

class FxPlayerCommandFontConfig : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->CycleFontConfig();
    }
    virtual String GetHelpString() const
    {
        return "Next font config";
    }
};

class FxPlayerCommandRestart : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->Paused = false;
        app->OnPause(app->Paused);        
        app->pMovie->Restart();
        app->AdjustFrameTime();
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Restart the movie";
    }
};

class FxPlayerCommandStageClipping : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ClippingEnable = !app->ClippingEnable;
        app->UpdateViewSize();
    }
    virtual String GetHelpString() const
    {
        return "Toggle stage clipping";
    }
};

class FxPlayerCommandStageCulling : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (app->pMovie)
        {
//@TODO
//             UInt32 rendererFlags = app->pRenderConfig->GetRenderFlags();
//             app->pRenderConfig->SetRenderFlags(rendererFlags ^ RenderConfig::RF_NoViewCull);
        }
    }
    virtual String GetHelpString() const
    {
        return "Toggle stage culling";
    }
};

class FxPlayerCommandResetUserMatrix : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ResetUserMatrix();
    }
    virtual String GetHelpString() const
    {
        return "Reset Zoom";
    }
};

class FxPlayerCommandTriangleOptimization : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (app->pMovie)
        {
            //@TODO

//             UInt32 rendererFlags = app->pRenderConfig->GetRenderFlags();
//             app->pRenderConfig->SetRenderFlags(rendererFlags ^ RenderConfig::RF_OptimizeTriangles);
        }
    }
    virtual String GetHelpString() const
    {
        return "Toggle triangle optimization";
    }
};

class FxPlayerCommandStrokeMode : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->ToggleStrokeType();
    }
    virtual String GetHelpString() const
    {
        return "Switch stroke type";
    }
};

class FxPlayerCommandToggleOverdrawProfile : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->BatchProfile = 0;
        app->OverdrawProfile = !app->OverdrawProfile;
        app->GetRenderThread()->SetProfileMode(app->OverdrawProfile ? FxRenderThread::Profile_Overdraw : FxRenderThread::Profile_None);
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Overdraw Profile";
    }
};

class FxPlayerCommandToggleBatchesProfile : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->OverdrawProfile = 0;
        app->BatchProfile = !app->BatchProfile;
        app->GetRenderThread()->SetProfileMode(app->BatchProfile ? FxRenderThread::Profile_Batch : FxRenderThread::Profile_None);
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Batches Profile";
    }
};

class FxPlayerCommandCycleProfile : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (app->OverdrawProfile)
        {
            app->OverdrawProfile = 0;
            app->BatchProfile = 1;
            app->GetRenderThread()->SetProfileMode(FxRenderThread::Profile_Batch);
        }
        else if (app->BatchProfile)
        {
            app->OverdrawProfile = 0;
            app->BatchProfile = 0;
            app->GetRenderThread()->SetProfileMode(FxRenderThread::Profile_None);
        }
        else
        {
            app->OverdrawProfile = 1;
            app->BatchProfile = 0;
            app->GetRenderThread()->SetProfileMode(FxRenderThread::Profile_Overdraw);
        }
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Cycle Profile Mode";
    }
};

class FxPlayerCommandToggleFilterCaching : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED3(app, controllerIdx, keyDown);
        bool set = app->GetRenderThread()->GetProfileFlag(Render::ProfileViews::ProfileFlag_NoFilterCaching);
        app->GetRenderThread()->SetProfileFlag(Render::ProfileViews::ProfileFlag_NoFilterCaching, !set);
    }
    virtual String GetHelpString() const
    {
        return "Toggles Filter Caching";
    }
};

class FxPlayerCommandMemReport : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED3(app, controllerIdx, keyDown);
        StringBuffer buffer;
        Memory::pGlobalHeap->MemReport(buffer, MemoryHeap::MemReportFull);
        printf("\n%s\n", buffer.ToCStr());
    }
    virtual String GetHelpString() const
    {
        return "Print full memory report to console";
    }
};

class FxPlayerCommandFunctionTiming : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED3(app, controllerIdx, keyDown);
#ifdef SF_AMP_SERVER
        AmpServer::GetInstance().SetProfileLevel(Amp_Profile_Level_High, false);
        AmpServer::GetInstance().ToggleInternalStatRecording();
#endif
    }
    virtual String GetHelpString() const
    {
        return "Toggle function timing";
    }
};

class FxPlayerCommandMute : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->IsMute = !app->IsMute;
#ifdef GFX_ENABLE_SOUND
        Sound::SoundRenderer* psoundRenderer = app->GetSoundRenderer();
        if (psoundRenderer)
        {
            psoundRenderer->Mute(app->IsMute);    
        }
#endif
    }
    virtual String GetHelpString() const
    {
        return "Toggle Mute";
    }
};

class FxPlayerCommandVolumeUp : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
#ifdef GFX_ENABLE_SOUND
        Sound::SoundRenderer* psoundRenderer = app->GetSoundRenderer();
        if (psoundRenderer)
        {
            if (app->IsMute)
            {
                psoundRenderer->Mute(false);
                app->IsMute = false;
            } 
            else
            {
                app->SoundVolume += 10;
                if (app->SoundVolume > 100)
                {
                    app->SoundVolume = 100;
                }
                psoundRenderer->SetMasterVolume(app->SoundVolume);
            }
        }
#else
		SF_UNUSED(app);

#endif
    }
    virtual String GetHelpString() const
    {
        return "Increase Sound Volume";
    }
};

class FxPlayerCommandVolumeDown : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
#ifdef GFX_ENABLE_SOUND
        Sound::SoundRenderer* psoundRenderer = app->GetSoundRenderer();
        if (psoundRenderer)
        {
            if (app->IsMute)
            {
                psoundRenderer->Mute(false);
                app->IsMute = false;
            } 
            else
            {
                app->SoundVolume-=10;
                if (app->SoundVolume < 0)
                {
                    app->SoundVolume = 0;
                }
                psoundRenderer->SetMasterVolume(app->SoundVolume);
            }
        }
#else
		SF_UNUSED(app);
#endif
    }
    virtual String GetHelpString() const
    {
        return "Decrease Sound Volume";
    }
};

class FxPlayerCommandStepForward_1 : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->pMovie->GotoFrame(app->pMovie->GetCurrentFrame() + 1);
        app->OnKeyFinishSeek();
    }
    virtual String GetHelpString() const
    {
        return "Step forward one frame";
    }
};

class FxPlayerCommandStepForward_10 : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->pMovie->GotoFrame(Alg::Min<unsigned>(app->pMovie->GetCurrentFrame() + 10, app->mMovieInfo.FrameCount - 1));
        app->OnKeyFinishSeek();
    }
    virtual String GetHelpString() const
    {
        return "Step forward 10 frames";
    }
};

class FxPlayerCommandStepBack_1 : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->pMovie->GotoFrame(app->pMovie->GetCurrentFrame() - 1);
        app->OnKeyFinishSeek();
    }
    virtual String GetHelpString() const
    {
        return "Step back one frame";
    }
};

class FxPlayerCommandStepBack_10 : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->pMovie->GotoFrame(Alg::Max<unsigned>(0, app->pMovie->GetCurrentFrame()- 10));
        app->OnKeyFinishSeek();
    }
    virtual String GetHelpString() const
    {
        return "Step back 10 frames";
    }
};

class FxPlayerCommandBackground : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (!app->pMovie) return;
        app->Background = !app->Background;
        app->pMovie->SetBackgroundAlpha(app->Background ? 1.0f : 0.0f);
    }
    virtual String GetHelpString() const
    {
        return "Toggle swf background";
    }
};

class FxPlayerCommandBackgroundColor : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        switch(app->BackgroundColor)
        {
        case 0x555555: //Gray 
            app->BackgroundColor = 0x0000FF; 
            break;
        case 0x0000FF: //Blue
            app->BackgroundColor = 0x000000; 
            break;
        case 0x000000: //Black
            app->BackgroundColor = 0xFFFFFF; 
            break;
        case 0xFFFFFF: //White
            app->BackgroundColor = 0x555555; 
            break;
        }    
		app->GetRenderThread()->SetBackgroundColor(app->BackgroundColor);
    }

    virtual String GetHelpString() const
    {
        return "Cycle background color";
    }
};

class FxPlayerCommandCurveToleranceUp : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->CurvePixelError = Alg::Min(10.0f, app->CurvePixelError + 0.5f);
//@TODO
//        app->pRenderConfig->SetMaxCurvePixelError(app->CurvePixelError);
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Curve tolerance up";
    }
};

class FxPlayerCommandCurveToleranceDown : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->CurvePixelError = Alg::Max(0.5f, app->CurvePixelError - 0.5f);
        //@TODO
//        app->pRenderConfig->SetMaxCurvePixelError(app->CurvePixelError);
        app->AmpDirty = true;
    }
    virtual String GetHelpString() const
    {
        return "Curve tolerance down";
    }
};

class FxPlayerCommandLoadPrevFile : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (app->ContentDir.GetNextFile(&app->FileName, true))
        {
            app->LoadMovie(app->FileName);    
        }
    }
    virtual String GetHelpString() const
    {
        return "Load previous file";
    }
};

class FxPlayerCommandLoadNextFile : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        if (app->ContentDir.GetNextFile(&app->FileName, false))
        {
            app->LoadMovie(app->FileName);    
        }
    }
    virtual String GetHelpString() const
    {
        return "Load next file";
    }
};

class FxPlayerCommandQuit : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->Shutdown();

    }
    virtual String GetHelpString() const
    {
        return "Quit";
    }
};

class FxPlayerCommandCtrlKey : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->NoCtrlKey = !app->NoCtrlKey;
    }
    virtual String GetHelpString() const
    {
        return "Toggle Ctrl key handling between Player and movie";
    }
};

class FxPlayerCommandEnter : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {        
        app->OnKeyEvent(controllerIdx, Key::Return, 0, keyDown);  
    }
    virtual String GetHelpString() const
    {
        return "Enter or Mouse button";
    }
    virtual bool HandleKeyUp() const { return true; }
};

class FxPlayerCommandEscape : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED(controllerIdx);
        app->OnKeyEvent(controllerIdx, Key::Escape, 0, keyDown);
    }
    virtual String GetHelpString() const
    {
        return "Escape";
    }
    virtual bool HandleKeyUp() const { return true; }
};

class FxPlayerCommandShowMouseCursor : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        SF_UNUSED2(controllerIdx, keyDown);
        app->EnableCursor(!app->IsCursorEnabled());        
        if (!app->pMovie) return;
        unsigned cursorCount = app->IsCursorEnabled() ? app->GetMouseCount() : 0;
        app->pMovie->SetMouseCursorCount(cursorCount);
    }
    virtual String GetHelpString() const
    {
        return "Enable mouse; Show/Hide cursor";
    }
};

#ifdef GFX_ENABLE_XML
class FxPlayerCommandTakeScreenshot : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown, XML::ElementNode* node) const
    {
        SF_UNUSED2(controllerIdx, keyDown);

        String screenshotFilename;
        
        if ( app->pMovieDef )
        {
            if ( !app->AutomatedTest )
                screenshotFilename = (app->pMovieDef->GetFileURL());
            else
            {
                // If doing an autotest, put the screenshot in the AutoOutputDir, and append the swf filename as a directory.
                String movieURL = app->pMovieDef->GetFileURL();
                screenshotFilename = app->AutoOutputDir + "/" + movieURL.GetFilename() + "/";
            }
        }
        else
            screenshotFilename = "GFxPlayer_Screenshot";

        // 'postfix' attribute is the text to append on the screenshot filename (after the .swf's name).
        // Note: Do not add the image extension on, it will be added automatically, based on the image type.
        // 'prefix' attribute is text to prepend on the filename (may be relative directories).
        if ( node )
        {
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("postfix") == 0 )
                    screenshotFilename.AppendString(attr->Value.ToCStr());
                else if ( attrName.CompareNoCase("prefix") == 0 )
                    screenshotFilename = String(attrName.ToCStr()) + screenshotFilename;
            }        
        }
        if ( !app->TakeScreenShot(screenshotFilename) )
            fprintf(stderr, "Failed to capture screenshot: %s\n", screenshotFilename.ToCStr());
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Takes a screenshot.";
    }
};

class FxPlayerCommandAutoAdvance : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown, XML::ElementNode* node) const
    {
        SF_UNUSED2(controllerIdx, keyDown);

        // 'delta' attribute is the number of seconds to advance (defaults to 0).
        double advanceDelta = 0.0;
        if ( node )
        {
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("delta") == 0 )
                    advanceDelta = SFstrtod(attr->Value.ToCStr(), 0);
            }        
        }
        
        if ( advanceDelta <= 0.0 )
        {
            // Advance is close to zero, still actually advance. This may change the viewport, etc. of the movie.
            app->AdvanceMovie(0);
        }
        else
        {
            // Advance several times, only a little bit at a time.
            double advanceInterval = 0.1;
            for (double advanceTime = 0.0; advanceTime < advanceDelta; advanceTime += advanceInterval)
            {            
                double advance = Alg::Min(advanceInterval, advanceDelta-advanceTime);
                app->AdvanceMovie((float)advance);

                // Update the auto-timer as well.
                AutoTimer.AdvanceTicks((UInt64)( advance * Timer::MksPerSecond));
            }
        }
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Advances the movie a certain number of frames.";
    }
};

class FxPlayerCommandKeyPress : public FxPlayerCommand
{
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown, XML::ElementNode* node) const
    {
        Key::Code code = Key::None;
        UInt8 modifiers = 0;

        if ( node )
        {
            // 'key' attribute is the string representing the keycode to push (see Key::Code).
            // 'modifier' is a *single* modifier attribtue for the keypress (see KeyModifiers).
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("key") == 0 )
                {
                    KeyCode* pc = app->KeyCodeMap.GetCaseInsensitive(attr->Value.ToCStr());
                    if ( !pc )
                        fprintf(stderr, "Keycode not found for '%s'\n", attr->Value.ToCStr());
                    else
                        code = *pc;
                }
                else if ( attrName.CompareNoCase("modifier") == 0)
                {
                    unsigned * pmods = app->KeyModifierMap.GetCaseInsensitive(attr->Value.ToCStr());
                    if ( !pmods )
                        fprintf(stderr, "Key modifier not found for '%s'\n", attr->Value.ToCStr());
                    else
                        modifiers |= pmods ? *pmods : modifiers;
                }
            }
            app->OnKeyEvent(controllerIdx, code, 0, keyDown, KeyModifiers(modifiers) );
        }
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Simulates pressing an arbitrary key";
    }
};

class FxPlayerCommandMouseButton : public FxPlayerCommand
{
public:
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown, XML::ElementNode* node) const
    {
        UInt8 modifiers = 0;
        Point<int> pt;
        int button = 0;

        if ( node )
        {
            // 'key' attribute is the string representing the keycode to push (see Key::Code).
            // 'modifier' is a *single* modifier attribtue for the keypress (see KeyModifiers).
            // 'button' is the index of the button to push
            // 'x' and 'y' are the movie coordinates to move the mouse to.
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("modifier") == 0)
                {
                    unsigned * pmods = app->KeyModifierMap.GetCaseInsensitive(attr->Value.ToCStr());
                    if ( !pmods )
                        fprintf(stderr, "Key modifier not found for '%s'\n", attr->Value.ToCStr());
                    else
                        modifiers |= pmods ? *pmods : modifiers;
                }
                else if (attrName.CompareNoCase("x") == 0 )
                    pt.x = (int)SFatoq(attr->Value.ToCStr());
                else if (attrName.CompareNoCase("y") == 0 )
                    pt.y = (int)SFatoq(attr->Value.ToCStr());
                else if (attrName.CompareNoCase("button") == 0)
                    button = (int)SFatoq(attr->Value.ToCStr());
            }
        }

        pt = app->AdjustMovieDefToViewPort(pt);
        app->OnMouseButton(controllerIdx, button, keyDown, pt, (KeyModifiers)modifiers);
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Simulates clicking the mouse.";
    }
};

class FxPlayerCommandMouseWheel : public FxPlayerCommand
{
public:
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool, XML::ElementNode* node) const
    {
        UInt8 modifiers = 0;
        Point<int> pt;
        float zdelta = 0.0f;

        if ( node )
        {
            // 'key' attribute is the string representing the keycode to push (see Key::Code).
            // 'modifier' is a *single* modifier attribtue for the keypress (see KeyModifiers).
            // 'button' is the index of the button to push
            // 'x' and 'y' are the movie coordinates to move the mouse to.
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("modifier") == 0)
                {
                    unsigned * pmods = app->KeyModifierMap.GetCaseInsensitive(attr->Value.ToCStr());
                    if ( !pmods )
                        fprintf(stderr, "Key modifier not found for '%s'\n", attr->Value.ToCStr());
                    else
                        modifiers |= pmods ? *pmods : modifiers;
                }
                else if (attrName.CompareNoCase("x") == 0 )
                    pt.x = (int)SFatoq(attr->Value.ToCStr());
                else if (attrName.CompareNoCase("y") == 0 )
                    pt.y = (int)SFatoq(attr->Value.ToCStr());
                else if (attrName.CompareNoCase("zdelta") == 0)
                    zdelta = (float)SFatof(attr->Value.ToCStr());
            }
        }

        pt = app->AdjustMovieDefToViewPort(pt);
        app->OnMouseWheel(controllerIdx, zdelta, pt, (KeyModifiers)modifiers);
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Simulates turning the mouse wheel.";
    }
};

class FxPlayerCommandMouseMove : public FxPlayerCommand
{
public:
public:
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool, XML::ElementNode* node) const
    {
        UInt8 modifiers = 0;
        Point<int> pt;

        if ( node ) 
        {
            // 'key' attribute is the string representing the keycode to push (see Key::Code).
            // 'modifier' is a *single* modifier attribtue for the keypress (see KeyModifiers).
            // 'x' and 'y' are the movie coordinates to move the mouse to.
            for (XML::Attribute* attr = node->FirstAttribute; attr != NULL; attr = attr->Next)
            {
                String attrName(attr->Name.ToCStr());
                if ( attrName.CompareNoCase("modifier") == 0)
                {
                    unsigned * pmods = app->KeyModifierMap.GetCaseInsensitive(attr->Value.ToCStr());
                    if ( !pmods )
                    {
                        fprintf(stderr, "Key modifier not found for '%s'\n", attr->Value.ToCStr());
                    }
                    else
                    {
                        modifiers |= pmods ? *pmods : modifiers;
                    }
                }
                else if (attrName.CompareNoCase("x") == 0 )
                    pt.x = (int)SFatoq(attr->Value.ToCStr());
                else if (attrName.CompareNoCase("y") == 0 )
                    pt.y = (int)SFatoq(attr->Value.ToCStr());
            }
        }

        pt = app->AdjustMovieDefToViewPort(pt);
        app->OnMouseMove(controllerIdx, pt, (KeyModifiers)modifiers);
    }
    virtual void Execute(FxPlayerAppBase* app, unsigned controllerIdx, bool keyDown) const
    {
        Execute(app, controllerIdx, keyDown, 0);
    }

    virtual String GetHelpString() const
    {
        return "Simulates moving the mouse.";
    }
};


#endif // GFX_ENABLE_XML

//------------------------------------------------------------------------

void    FxPlayerAppBase::LoadFontConfigs(ConfigParser *parser)
{
    FontConfigs.Parse(parser);
    if (FontConfigs.GetSize() > 0)
    {
        FontConfigIndex = 0;
    }
    else
    {
        FontConfigIndex = -1;
    }
}

int     FxPlayerAppBase::GetFontConfigIndexByName(const char* pname)
{
    for (unsigned i = 0; i < FontConfigs.GetSize(); i++)
    {
        if (SFstricmp(pname, FontConfigs[i]->ConfigName) == 0)
            return i;
    }   
    return -1;
}

FontConfig*  FxPlayerAppBase::GetCurrentFontConfig()
{
    // we are skipping over invalid fontconfigs until one is found.
    // else return NULL.

    if (FontConfigIndex == -1)
        return NULL;

    FontConfig* fc = NULL;
    int  sIdx = FontConfigIndex;
    bool ok = false;

    while (!ok)
    {
        ok = true;
        fc = FontConfigs[FontConfigIndex];
        // check if all fontlib files exist
        for (unsigned i=0; i < fc->FontLibFiles.GetSize(); i++)
        {
            // check if file exists
            SysFile file(fc->FontLibFiles[i]);
            if (!file.IsValid())
            {
                ok = false;
                fprintf(stderr, "Fontlib file '%s' cannot be found. Skipping config '%s'..\n",
                        fc->FontLibFiles[i].ToCStr(), fc->ConfigName.ToCStr());
                break;
            }
        }

        if (!ok)
        {
            FontConfigIndex++;
            FontConfigIndex %= (int)FontConfigs.GetSize();
            if (FontConfigIndex == sIdx)
                return NULL;
        }
    }

    return FontConfigs[FontConfigIndex];
}

bool FxPlayerAppBase::LoadDefaultFontConfigFromPath( const String& path )
{
    if (!GetArgs()["NoFontConfig"]->GetBool())
    {
        // load fontconfig.txt if it exists in the movie's path
        String fontConfigFilePath = GetArgs()["FontConfigFile"]->GetString();

        if (fontConfigFilePath.IsEmpty())
        {
            // [PPS] The absolute check is unneccessary
            // ExtractFilePath will return the correct parent path:
            // C:/folder/filename.ext - C:/folder/
            // folder/filename.ext - folder/
            // filename.ext - empty string
            //if (URLBuilder::IsPathAbsolute(path))
            //{
            fontConfigFilePath.AppendString(path);
            if ( !URLBuilder::ExtractFilePath(&fontConfigFilePath) )
            {
                fontConfigFilePath = "";
            }
            //}
            fontConfigFilePath += "fontconfig.txt";
        }
        
        bool maintainIndex = false;

        // store font config file related info
        if (FontConfigFilePath.GetLength() == 0)   // if no file was previously loaded
        {
            FileStat fileStats;
            if ( SysFile::GetFileStat(&fileStats, fontConfigFilePath.ToCStr()) )
            {
                FontConfigFilePath = fontConfigFilePath;
                FontConfigFileStats = fileStats;
            }
        }
        else // if the file was previously loaded and is modified
        {
            if (fontConfigFilePath == FontConfigFilePath)
            {
                // if modified time is not the same, then reload config file
                FileStat fileStats;
                if ( SysFile::GetFileStat(&fileStats, fontConfigFilePath.ToCStr()) )
                {
                    if ( !(fileStats == FontConfigFileStats) )
                    {
                        FontConfigFileStats = fileStats;
                        maintainIndex = true;
                    }
                }
            }
        }

        // parse the config file
        ConfigParser parser(fontConfigFilePath.ToCStr());
        int          oldIdx = FontConfigIndex;
        LoadFontConfigs(&parser);

        // try to maintain previous font config index
        if ( maintainIndex &&
            (FontConfigIndex == 0) &&
            (oldIdx != -1) )
        {
            FontConfigIndex = oldIdx;
            FontConfigIndex %= (int)FontConfigs.GetSize();
        }

        return true;
    }
    return false;
}




// ***** FxPlayerAppBase Implementation

FxPlayerAppBase::FxPlayerAppBase()
{
    Wireframe       = false;
    AmpDirty        = true;
    // Scale toggle, on by default
    ScaleEnable     = true;
    ClippingEnable  = true;
    Paused          = false;
    PausedState     = GFx::State_Playing;

    ArgResolution.Clear();
    ScaleX = ScaleY     = 1.0f;
    TexLodBias          = -0.5f;
    AAMode              = AAMode_EdgeAA;
    Background          = 1;

    BackgroundColor     = 0x555555;

    MeasurePerformance = IsConsole();

    // No font config used by default.
    FontConfigIndex     = -1;

    AutomatedTest       = false;
#ifdef GFX_ENABLE_XML
    AutoInstructions    = 0;
#endif
    FastForward         = false;
    ExitTimeout         = 0.0f;
    
    // *** Clear timing
    AccumClockTicks = 0;
    PrevTicks       = 0;
    LastFPSUpdatedTicks  = 0;
    LastStatUpdatedTicks = 0;
        
    LastFPS         = 0.0f;
    AccumFPS        = 0.0f;
    FrameCounter    = 0;
    AccumFPSSecondCount = 0;
    LastAdvanceTicks= 0;

    PlayOnce        = false;
    Rendering       = true;
    DoSound         = 0;
    NoControlKeys   = 0;
    NoCtrlKey       = 0;

    SoundVolume     = 1.0f;
    IsMute          = 0;

    bCLIKSound      = false;

    MViewSize.SetSize(0, 0);
    MinSize.SetSize(0, 0);
    MovieCursorType = Platform::Cursor_Arrow;

    Zoom = 1.0;
    Move = PointF(0.0);

    MouseTracking = None;

    SizingEntered = 0;

    CurvePixelError = 1.0f;
    FontLibChanged = false;

#ifdef GFX_ENABLE_SOUND
#ifdef GFX_SOUND_FMOD
    pSoundFMODSystem  = NULL;
#endif
#ifdef GFX_SOUND_WWISE
    pSoundWwiseSystem = NULL;
#endif
#endif

    OverdrawProfile = 0;
    BatchProfile = 0;

    KeyboardIndex = 0;
    ResIndex  = 1;
    SkipLoadMovie = false;

    mMovieInfo.Clear();

#if defined(SF_OS_WIN32) || defined(SF_OS_XBOX360) || defined(FXPLAYER_X11) || defined(SF_OS_MAC)
	UInt32 ctrlMask = (KeyModifiers::Key_CtrlPressed << 16);
    KeyCommandMap.Set(Key::S | ctrlMask, *SF_NEW FxPlayerCommandScaledDisplay());
    KeyCommandMap.Set(Key::W | ctrlMask, *SF_NEW FxPlayerCommandWireframe());
    KeyCommandMap.Set(Key::A | ctrlMask, *SF_NEW FxPlayerCommandAntialiasingMode());
    #if !defined(SF_OS_XBOX360)
        KeyCommandMap.Set(Key::U | ctrlMask, *SF_NEW FxPlayerCommandFullscreen());
    #endif
    #if defined(FXPLAYER_RENDER_DIRECT3D) && (SF_D3D_VERSION != 10) && !defined(SF_OS_XBOX360)
//        KeyCommandMap.Set(Key::V | ctrlMask, *SF_NEW FxPlayerCommandDynamicTextures());
    #endif
    KeyCommandMap.Set(Key::F | ctrlMask, *SF_NEW FxPlayerCommandFastMode());
    KeyCommandMap.Set(Key::G | ctrlMask, *SF_NEW FxPlayerCommandFastForward());
    KeyCommandMap.Set(Key::Y | ctrlMask, *SF_NEW FxPlayerCommandVSync());
    KeyCommandMap.Set(Key::P | ctrlMask, *SF_NEW FxPlayerCommandPause());
    KeyCommandMap.Set(Key::I | ctrlMask, *SF_NEW FxPlayerCommandObjectsReport());
    KeyCommandMap.Set(Key::N | ctrlMask, *SF_NEW FxPlayerCommandFontConfig());
    KeyCommandMap.Set(Key::R | ctrlMask, *SF_NEW FxPlayerCommandRestart());
    KeyCommandMap.Set(Key::D | ctrlMask, *SF_NEW FxPlayerCommandStageClipping());
    KeyCommandMap.Set(Key::C | ctrlMask, *SF_NEW FxPlayerCommandStageCulling());
    KeyCommandMap.Set(Key::Z | ctrlMask, *SF_NEW FxPlayerCommandResetUserMatrix());
    KeyCommandMap.Set(Key::O | ctrlMask, *SF_NEW FxPlayerCommandTriangleOptimization());
    KeyCommandMap.Set(Key::T | ctrlMask, *SF_NEW FxPlayerCommandStrokeMode());
    KeyCommandMap.Set(Key::E | ctrlMask, *SF_NEW FxPlayerCommandToggleOverdrawProfile());
    KeyCommandMap.Set(Key::J | ctrlMask, *SF_NEW FxPlayerCommandToggleBatchesProfile());
    KeyCommandMap.Set(Key::F3 | ctrlMask, *SF_NEW FxPlayerCommandToggleFilterCaching());
    KeyCommandMap.Set(Key::F6 | ctrlMask, *SF_NEW FxPlayerCommandMemReport());
    KeyCommandMap.Set(Key::F7 | ctrlMask, *SF_NEW FxPlayerCommandFunctionTiming());
    #ifdef GFX_ENABLE_SOUND
        KeyCommandMap.Set(Key::M | ctrlMask, *SF_NEW FxPlayerCommandMute());
        KeyCommandMap.Set(Key::Up | ctrlMask, *SF_NEW FxPlayerCommandVolumeUp());
        KeyCommandMap.Set(Key::Down | ctrlMask, *SF_NEW FxPlayerCommandVolumeDown());
    #endif
    KeyCommandMap.Set(Key::Right | ctrlMask, *SF_NEW FxPlayerCommandStepForward_1());
    KeyCommandMap.Set(Key::PageUp | ctrlMask, *SF_NEW FxPlayerCommandStepForward_10());
    KeyCommandMap.Set(Key::Left | ctrlMask, *SF_NEW FxPlayerCommandStepBack_1());
    KeyCommandMap.Set(Key::PageDown | ctrlMask, *SF_NEW FxPlayerCommandStepBack_10());
    KeyCommandMap.Set(Key::B | ctrlMask, *SF_NEW FxPlayerCommandBackground());
    KeyCommandMap.Set(Key::F8 | ctrlMask, *SF_NEW FxPlayerCommandBackgroundColor());
    KeyCommandMap.Set(Key::Equal | ctrlMask, *SF_NEW FxPlayerCommandCurveToleranceUp());
    KeyCommandMap.Set(Key::Minus | ctrlMask, *SF_NEW FxPlayerCommandCurveToleranceDown());
    KeyCommandMap.Set(Key::BracketLeft | ctrlMask, *SF_NEW FxPlayerCommandLoadPrevFile());
    KeyCommandMap.Set(Key::BracketRight | ctrlMask, *SF_NEW FxPlayerCommandLoadNextFile());
    KeyCommandMap.Set(Key::Q | ctrlMask, *SF_NEW FxPlayerCommandQuit());
    KeyCommandMap.Set(Key::F9, *SF_NEW FxPlayerCommandCtrlKey());
    KeyCommandMap.Set(Key::F11, *SF_NEW FxPlayerCommandChangeRes());
#endif

#if defined(SF_OS_XBOX360) || defined(SF_OS_WIN32)
    PadKeyCommandMap.Set(SF::Pad_A, *SF_NEW FxPlayerCommandEnter());
    PadKeyCommandMap.Set(SF::Pad_B, *SF_NEW FxPlayerCommandEscape());
    PadKeyCommandMap.Set(SF::Pad_Y, *SF_NEW FxPlayerCommandRestart());
    PadKeyCommandMap.Set(SF::Pad_Start, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Back, *SF_NEW FxPlayerCommandCycleProfile());
    PadKeyCommandMap.Set(SF::Pad_L1, *SF_NEW FxPlayerCommandAntialiasingMode());
    PadKeyCommandMap.Set(SF::Pad_R1, *SF_NEW FxPlayerCommandWireframe());
    PadKeyCommandMap.Set(SF::Pad_L2, *SF_NEW FxPlayerCommandLoadPrevFile());
    PadKeyCommandMap.Set(SF::Pad_R2, *SF_NEW FxPlayerCommandLoadNextFile());
    PadKeyCommandMap.Set(SF::Pad_LT, *SF_NEW FxPlayerCommandFastForward());
    #if defined(SF_OS_XBOX360) 
        PadKeyCommandMap.Set(SF::Pad_RT, *SF_NEW FxPlayerCommandShowMouseCursor());
    #endif
#elif defined(SF_OS_PS3)
    PadKeyCommandMap.Set(SF::Pad_X, *SF_NEW FxPlayerCommandEnter());
    PadKeyCommandMap.Set(SF::Pad_O, *SF_NEW FxPlayerCommandEscape());
    PadKeyCommandMap.Set(SF::Pad_T, *SF_NEW FxPlayerCommandRestart());
    PadKeyCommandMap.Set(SF::Pad_Start, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Select, *SF_NEW FxPlayerCommandCycleProfile());
    PadKeyCommandMap.Set(SF::Pad_L1, *SF_NEW FxPlayerCommandAntialiasingMode());
    PadKeyCommandMap.Set(SF::Pad_R1, *SF_NEW FxPlayerCommandWireframe());
    PadKeyCommandMap.Set(SF::Pad_L2, *SF_NEW FxPlayerCommandLoadPrevFile());
    PadKeyCommandMap.Set(SF::Pad_R2, *SF_NEW FxPlayerCommandLoadNextFile());
    PadKeyCommandMap.Set(SF::Pad_LT, *SF_NEW FxPlayerCommandFastForward());
    PadKeyCommandMap.Set(SF::Pad_RT, *SF_NEW FxPlayerCommandShowMouseCursor());
#elif defined(SF_OS_WII)
    PadKeyCommandMap.Set(SF::Pad_A, *SF_NEW FxPlayerCommandEnter());
    PadKeyCommandMap.Set(SF::Pad_B, *SF_NEW FxPlayerCommandEscape());
    PadKeyCommandMap.Set(SF::Pad_Home, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Z, *SF_NEW FxPlayerCommandAntialiasingMode());
    PadKeyCommandMap.Set(SF::Pad_C, *SF_NEW FxPlayerCommandFastForward());
	PadKeyCommandMap.Set(SF::Pad_Plus, *SF_NEW FxPlayerCommandLoadNextFile());
	PadKeyCommandMap.Set(SF::Pad_Minus, *SF_NEW FxPlayerCommandLoadPrevFile());
#elif defined(SF_OS_WIIU) //Some functions may be assigned to two buttons for use with Wii controller
    PadKeyCommandMap.Set(SF::Pad_A, *SF_NEW FxPlayerCommandEnter());
    PadKeyCommandMap.Set(SF::Pad_B, *SF_NEW FxPlayerCommandEscape());
    PadKeyCommandMap.Set(SF::Pad_Y, *SF_NEW FxPlayerCommandRestart());
    PadKeyCommandMap.Set(SF::Pad_Plus, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Home, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Minus, *SF_NEW FxPlayerCommandCycleProfile());
    PadKeyCommandMap.Set(SF::Pad_Z, *SF_NEW FxPlayerCommandAntialiasingMode());
    PadKeyCommandMap.Set(SF::Pad_L1, *SF_NEW FxPlayerCommandAntialiasingMode());
    PadKeyCommandMap.Set(SF::Pad_R1, *SF_NEW FxPlayerCommandFastForward());
    PadKeyCommandMap.Set(SF::Pad_L2, *SF_NEW FxPlayerCommandLoadPrevFile());
    PadKeyCommandMap.Set(SF::Pad_R2, *SF_NEW FxPlayerCommandLoadNextFile());
    PadKeyCommandMap.Set(SF::Pad_C, *SF_NEW FxPlayerCommandFastForward());
#else
    PadKeyCommandMap.Set(SF::Pad_X, *SF_NEW FxPlayerCommandEnter());
    PadKeyCommandMap.Set(SF::Pad_O, *SF_NEW FxPlayerCommandEscape());
    PadKeyCommandMap.Set(SF::Pad_T, *SF_NEW FxPlayerCommandRestart());
    PadKeyCommandMap.Set(SF::Pad_Start, *SF_NEW FxPlayerCommandPause());
    PadKeyCommandMap.Set(SF::Pad_Select, *SF_NEW FxPlayerCommandCycleProfile());
    PadKeyCommandMap.Set(SF::Pad_L1, *SF_NEW FxPlayerCommandLoadPrevFile());
    PadKeyCommandMap.Set(SF::Pad_R1, *SF_NEW FxPlayerCommandLoadNextFile());
    PadKeyCommandMap.Set(SF::Pad_LT, *SF_NEW FxPlayerCommandFastForward());
    PadKeyCommandMap.Set(SF::Pad_Y, *SF_NEW FxPlayerCommandFunctionTiming());

#endif

#ifdef GFX_ENABLE_XML
    AutoCommandMap.SetCaseInsensitive("ChangeRes", *SF_NEW FxPlayerCommandChangeRes());
    AutoCommandMap.SetCaseInsensitive("ScaledDisplay", *SF_NEW FxPlayerCommandScaledDisplay());
    AutoCommandMap.SetCaseInsensitive("Wireframe", *SF_NEW FxPlayerCommandWireframe());
    AutoCommandMap.SetCaseInsensitive("AntialiasingMode", *SF_NEW FxPlayerCommandAntialiasingMode());
    AutoCommandMap.SetCaseInsensitive("Fullscreen", *SF_NEW FxPlayerCommandFullscreen());
    AutoCommandMap.SetCaseInsensitive("DynamicTextures", *SF_NEW FxPlayerCommandDynamicTextures());
    AutoCommandMap.SetCaseInsensitive("FastMode", *SF_NEW FxPlayerCommandFastMode());
    AutoCommandMap.SetCaseInsensitive("FastForward", *SF_NEW FxPlayerCommandFastForward());
    AutoCommandMap.SetCaseInsensitive("VSync", *SF_NEW FxPlayerCommandVSync());
    AutoCommandMap.SetCaseInsensitive("Pause", *SF_NEW FxPlayerCommandPause());
    AutoCommandMap.SetCaseInsensitive("FontConfig", *SF_NEW FxPlayerCommandFontConfig());
    AutoCommandMap.SetCaseInsensitive("ObjectsReport", *SF_NEW FxPlayerCommandObjectsReport());
    AutoCommandMap.SetCaseInsensitive("Restart", *SF_NEW FxPlayerCommandRestart());
    AutoCommandMap.SetCaseInsensitive("StageClipping", *SF_NEW FxPlayerCommandStageClipping());
    AutoCommandMap.SetCaseInsensitive("StageCulling", *SF_NEW FxPlayerCommandStageCulling());
    AutoCommandMap.SetCaseInsensitive("ResetUserMatrix", *SF_NEW FxPlayerCommandResetUserMatrix());
    AutoCommandMap.SetCaseInsensitive("TriangleOptimization", *SF_NEW FxPlayerCommandTriangleOptimization());
    AutoCommandMap.SetCaseInsensitive("StrokeMode", *SF_NEW FxPlayerCommandStrokeMode());
    AutoCommandMap.SetCaseInsensitive("ToggleOverdrawProfile", *SF_NEW FxPlayerCommandToggleOverdrawProfile());
    AutoCommandMap.SetCaseInsensitive("ToggleBatchesProfile", *SF_NEW FxPlayerCommandToggleBatchesProfile());
    AutoCommandMap.SetCaseInsensitive("CycleProfile", *SF_NEW FxPlayerCommandCycleProfile());
    AutoCommandMap.SetCaseInsensitive("ToggleFilterCaching", *SF_NEW FxPlayerCommandToggleFilterCaching());
    AutoCommandMap.SetCaseInsensitive("MemReport", *SF_NEW FxPlayerCommandMemReport());
    AutoCommandMap.SetCaseInsensitive("FunctionTiming", *SF_NEW FxPlayerCommandFunctionTiming());
    AutoCommandMap.SetCaseInsensitive("Mute", *SF_NEW FxPlayerCommandMute());
    AutoCommandMap.SetCaseInsensitive("VolumeUp", *SF_NEW FxPlayerCommandVolumeUp());
    AutoCommandMap.SetCaseInsensitive("VolumeDown", *SF_NEW FxPlayerCommandVolumeDown());
    AutoCommandMap.SetCaseInsensitive("StepForward_1", *SF_NEW FxPlayerCommandStepForward_1());
    AutoCommandMap.SetCaseInsensitive("StepForward_10", *SF_NEW FxPlayerCommandStepForward_10());
    AutoCommandMap.SetCaseInsensitive("StepBack_1", *SF_NEW FxPlayerCommandStepBack_1());
    AutoCommandMap.SetCaseInsensitive("StepBack_10", *SF_NEW FxPlayerCommandStepBack_10());
    AutoCommandMap.SetCaseInsensitive("Background", *SF_NEW FxPlayerCommandBackground());
    AutoCommandMap.SetCaseInsensitive("BackgroundColor", *SF_NEW FxPlayerCommandBackgroundColor());
    AutoCommandMap.SetCaseInsensitive("CurveToleranceUp", *SF_NEW FxPlayerCommandCurveToleranceUp());
    AutoCommandMap.SetCaseInsensitive("CurveToleranceDown", *SF_NEW FxPlayerCommandCurveToleranceDown());
    AutoCommandMap.SetCaseInsensitive("LoadPrevFile", *SF_NEW FxPlayerCommandLoadPrevFile());
    AutoCommandMap.SetCaseInsensitive("LoadNextFile", *SF_NEW FxPlayerCommandLoadNextFile());
    AutoCommandMap.SetCaseInsensitive("Quit", *SF_NEW FxPlayerCommandQuit());
    AutoCommandMap.SetCaseInsensitive("CtrlKey", *SF_NEW FxPlayerCommandCtrlKey());
    AutoCommandMap.SetCaseInsensitive("Enter", *SF_NEW FxPlayerCommandEnter());
    AutoCommandMap.SetCaseInsensitive("Escape", *SF_NEW FxPlayerCommandEscape());
    AutoCommandMap.SetCaseInsensitive("ShowMouseCursor", *SF_NEW FxPlayerCommandShowMouseCursor());
    AutoCommandMap.SetCaseInsensitive("TakeScreenshot", *SF_NEW FxPlayerCommandTakeScreenshot());
    AutoCommandMap.SetCaseInsensitive("AutoAdvance", *SF_NEW FxPlayerCommandAutoAdvance());
    AutoCommandMap.SetCaseInsensitive("KeyPress", *SF_NEW FxPlayerCommandKeyPress());
    AutoCommandMap.SetCaseInsensitive("MouseButton", *SF_NEW FxPlayerCommandMouseButton());
    AutoCommandMap.SetCaseInsensitive("MouseWheel", *SF_NEW FxPlayerCommandMouseWheel());
    AutoCommandMap.SetCaseInsensitive("MouseMove", *SF_NEW FxPlayerCommandMouseMove());

    KeyCodeMap.SetCaseInsensitive("A", Key::A);              
    KeyCodeMap.SetCaseInsensitive("B", Key::B );
    KeyCodeMap.SetCaseInsensitive("C", Key::C );
    KeyCodeMap.SetCaseInsensitive("D", Key::D );
    KeyCodeMap.SetCaseInsensitive("E", Key::E );
    KeyCodeMap.SetCaseInsensitive("F", Key::F );
    KeyCodeMap.SetCaseInsensitive("G", Key::G );
    KeyCodeMap.SetCaseInsensitive("H", Key::H );
    KeyCodeMap.SetCaseInsensitive("I", Key::I );
    KeyCodeMap.SetCaseInsensitive("J", Key::J );
    KeyCodeMap.SetCaseInsensitive("K", Key::K );
    KeyCodeMap.SetCaseInsensitive("L", Key::L );
    KeyCodeMap.SetCaseInsensitive("M", Key::M );
    KeyCodeMap.SetCaseInsensitive("N", Key::N );
    KeyCodeMap.SetCaseInsensitive("O", Key::O );
    KeyCodeMap.SetCaseInsensitive("P", Key::P );
    KeyCodeMap.SetCaseInsensitive("Q", Key::Q );
    KeyCodeMap.SetCaseInsensitive("R", Key::R );
    KeyCodeMap.SetCaseInsensitive("S", Key::S );
    KeyCodeMap.SetCaseInsensitive("T", Key::T );
    KeyCodeMap.SetCaseInsensitive("U", Key::U );
    KeyCodeMap.SetCaseInsensitive("V", Key::V );
    KeyCodeMap.SetCaseInsensitive("W", Key::W );
    KeyCodeMap.SetCaseInsensitive("X", Key::X );
    KeyCodeMap.SetCaseInsensitive("Y", Key::Y );
    KeyCodeMap.SetCaseInsensitive("Z", Key::Z );
    KeyCodeMap.SetCaseInsensitive("Num0", Key::Num0);           
    KeyCodeMap.SetCaseInsensitive("Num1", Key::Num1 );
    KeyCodeMap.SetCaseInsensitive("Num2", Key::Num2 );
    KeyCodeMap.SetCaseInsensitive("Num3", Key::Num3 );
    KeyCodeMap.SetCaseInsensitive("Num4", Key::Num4 );
    KeyCodeMap.SetCaseInsensitive("Num5", Key::Num5 );
    KeyCodeMap.SetCaseInsensitive("Num6", Key::Num6 );
    KeyCodeMap.SetCaseInsensitive("Num7", Key::Num7 );
    KeyCodeMap.SetCaseInsensitive("Num8", Key::Num8 );
    KeyCodeMap.SetCaseInsensitive("Num9", Key::Num9 );
    KeyCodeMap.SetCaseInsensitive("KP_0", Key::KP_0);           
    KeyCodeMap.SetCaseInsensitive("KP_1", Key::KP_1 );
    KeyCodeMap.SetCaseInsensitive("KP_2", Key::KP_2 );
    KeyCodeMap.SetCaseInsensitive("KP_3", Key::KP_3 );
    KeyCodeMap.SetCaseInsensitive("KP_4", Key::KP_4 );
    KeyCodeMap.SetCaseInsensitive("KP_5", Key::KP_5 );
    KeyCodeMap.SetCaseInsensitive("KP_6", Key::KP_6 );
    KeyCodeMap.SetCaseInsensitive("KP_7", Key::KP_7 );
    KeyCodeMap.SetCaseInsensitive("KP_8", Key::KP_8 );
    KeyCodeMap.SetCaseInsensitive("KP_9", Key::KP_9 );
    KeyCodeMap.SetCaseInsensitive("KP_Multiply", Key::KP_Multiply );
    KeyCodeMap.SetCaseInsensitive("KP_Add", Key::KP_Add );
    KeyCodeMap.SetCaseInsensitive("KP_Enter", Key::KP_Enter );
    KeyCodeMap.SetCaseInsensitive("KP_Subtract", Key::KP_Subtract );
    KeyCodeMap.SetCaseInsensitive("KP_Decimal", Key::KP_Decimal );
    KeyCodeMap.SetCaseInsensitive("KP_Divide", Key::KP_Divide );
    KeyCodeMap.SetCaseInsensitive("F1", Key::F1);             
    KeyCodeMap.SetCaseInsensitive("F2", Key::F2 );
    KeyCodeMap.SetCaseInsensitive("F3", Key::F3 );
    KeyCodeMap.SetCaseInsensitive("F4", Key::F4 );
    KeyCodeMap.SetCaseInsensitive("F5", Key::F5 );
    KeyCodeMap.SetCaseInsensitive("F6", Key::F6 );
    KeyCodeMap.SetCaseInsensitive("F7", Key::F7 );
    KeyCodeMap.SetCaseInsensitive("F8", Key::F8 );
    KeyCodeMap.SetCaseInsensitive("F9", Key::F9 );
    KeyCodeMap.SetCaseInsensitive("F10", Key::F10 );
    KeyCodeMap.SetCaseInsensitive("F11", Key::F11 );
    KeyCodeMap.SetCaseInsensitive("F12", Key::F12 );
    KeyCodeMap.SetCaseInsensitive("F13", Key::F13 );
    KeyCodeMap.SetCaseInsensitive("F14", Key::F14 );
    KeyCodeMap.SetCaseInsensitive("F15", Key::F15 );
    KeyCodeMap.SetCaseInsensitive("Backspace", Key::Backspace);      
    KeyCodeMap.SetCaseInsensitive("Tab", Key::Tab );
    KeyCodeMap.SetCaseInsensitive("Clear", Key::Clear);          
    KeyCodeMap.SetCaseInsensitive("Return", Key::Return );
    KeyCodeMap.SetCaseInsensitive("Shift", Key::Shift);          
    KeyCodeMap.SetCaseInsensitive("Control", Key::Control );
    KeyCodeMap.SetCaseInsensitive("Alt", Key::Alt );
    KeyCodeMap.SetCaseInsensitive("Pause", Key::Pause );
    KeyCodeMap.SetCaseInsensitive("CapsLock", Key::CapsLock);       
    KeyCodeMap.SetCaseInsensitive("Escape", Key::Escape);         
    KeyCodeMap.SetCaseInsensitive("Space", Key::Space);          
    KeyCodeMap.SetCaseInsensitive("PageUp", Key::PageUp );
    KeyCodeMap.SetCaseInsensitive("PageDown", Key::PageDown );
    KeyCodeMap.SetCaseInsensitive("End", Key::End);            
    KeyCodeMap.SetCaseInsensitive("Home", Key::Home );
    KeyCodeMap.SetCaseInsensitive("Left", Key::Left );
    KeyCodeMap.SetCaseInsensitive("Up", Key::Up );
    KeyCodeMap.SetCaseInsensitive("Right", Key::Right );
    KeyCodeMap.SetCaseInsensitive("Down", Key::Down );
    KeyCodeMap.SetCaseInsensitive("Insert", Key::Insert);         
    KeyCodeMap.SetCaseInsensitive("Delete", Key::Delete );
    KeyCodeMap.SetCaseInsensitive("Help", Key::Help );
    KeyCodeMap.SetCaseInsensitive("NumLock", Key::NumLock);        
    KeyCodeMap.SetCaseInsensitive("ScrollLock", Key::ScrollLock);     

    KeyCodeMap.SetCaseInsensitive("Semicolon", Key::Semicolon);      
    KeyCodeMap.SetCaseInsensitive("Equal", Key::Equal);          
    KeyCodeMap.SetCaseInsensitive("Comma", Key::Comma);          
    KeyCodeMap.SetCaseInsensitive("Minus", Key::Minus);          
    KeyCodeMap.SetCaseInsensitive("Period", Key::Period);         
    KeyCodeMap.SetCaseInsensitive("Slash", Key::Slash);          
    KeyCodeMap.SetCaseInsensitive("Bar", Key::Bar);            
    KeyCodeMap.SetCaseInsensitive("BracketLeft", Key::BracketLeft);    
    KeyCodeMap.SetCaseInsensitive("Backslash", Key::Backslash);      
    KeyCodeMap.SetCaseInsensitive("BracketRight", Key::BracketRight);   
    KeyCodeMap.SetCaseInsensitive("Quote", Key::Quote);          

    KeyCodeMap.SetCaseInsensitive("OEM_AX", Key::OEM_AX);         
    KeyCodeMap.SetCaseInsensitive("OEM_102", Key::OEM_102);        
    KeyCodeMap.SetCaseInsensitive("ICO_HELP", Key::ICO_HELP);       
    KeyCodeMap.SetCaseInsensitive("ICO_00", Key::ICO_00);         

    KeyModifierMap.SetCaseInsensitive("ShiftPressed", KeyModifiers::Key_ShiftPressed); 
    KeyModifierMap.SetCaseInsensitive("CtrlPressed", KeyModifiers::Key_CtrlPressed);  
    KeyModifierMap.SetCaseInsensitive("AltPressed", KeyModifiers::Key_AltPressed);   
    KeyModifierMap.SetCaseInsensitive("CapsToggled", KeyModifiers::Key_CapsToggled);  
    KeyModifierMap.SetCaseInsensitive("NumToggled", KeyModifiers::Key_NumToggled);   
    KeyModifierMap.SetCaseInsensitive("ScrollToggled", KeyModifiers::Key_ScrollToggled);
    KeyModifierMap.SetCaseInsensitive("ExtendedKey", KeyModifiers::Key_ExtendedKey);  
#endif
}

FxPlayerAppBase::~FxPlayerAppBase()      
{
#ifdef GFX_ENABLE_SOUND
    xShutdownSound();
#endif
}

#ifdef GFX_ENABLE_SOUND
void FxPlayerAppBase::InitializeSound()
{
#ifdef GFX_SOUND_FMOD
    if (!pSoundFMODSystem)
        pSoundFMODSystem = new FxSoundFMOD;
    if (!pSoundFMODSystem->IsInitialized())
    {
        bool bIsInitFMOD = pSoundFMODSystem->Initialize(
#ifdef SF_OS_PS3		
            GetSpurs()
#endif
            );
        if (!bIsInitFMOD)
            xShutdownSound();
    }
#endif // GFX_SOUND_FMOD

#ifdef GFX_SOUND_WWISE
    if (!pSoundWwiseSystem)
        pSoundWwiseSystem = new FxSoundWwise;
    if (!pSoundWwiseSystem->IsInitialized())
    {
        bool bIsInitWwise = pSoundWwiseSystem->Initialize(
#ifdef SF_OS_PS3
            GetSpurs()
#endif			
            );
        if (!bIsInitWwise)
            xShutdownSound();
    }
#endif // GFX_SOUND_WWISE
}

void FxPlayerAppBase::xShutdownSound()
{
#ifdef GFX_SOUND_FMOD
    if (pSoundFMODSystem && pSoundFMODSystem->IsInitialized())
        pSoundFMODSystem->Finalize();
    delete pSoundFMODSystem;
    pSoundFMODSystem = NULL;
#endif

#ifdef GFX_SOUND_WWISE
    if (pSoundWwiseSystem && pSoundWwiseSystem->IsInitialized())
        pSoundWwiseSystem->Finalize();
    delete pSoundWwiseSystem;
    pSoundWwiseSystem = NULL;
#endif
}

Sound::SoundRenderer* FxPlayerAppBase::GetSoundRenderer()
{
#ifdef GFX_SOUND_FMOD
    return pSoundFMODSystem && pSoundFMODSystem->IsInitialized() ? pSoundFMODSystem->GetSoundRenderer() : NULL;
#else
    return NULL;
#endif
}
#endif // GFX_ENABLE_SOUND

//  Sample translator implementation that can be used for testing.
/*
class TranslatorImpl : public GFxTranslator
{
public:
// wwMode can be GFxTranslator::WWT_NoHangulWrap (Korean),
// GFxTranslator::WWT_Prohibition (used in Japanese) or
// GFxTranslator::WWT_Asian (Chinese). Also GFxTranslator::WWT_Hyphenation
// might be used for very simple hyphenation. OnWordWrapping virtual 
// method might be overridden to implement custom word-wrapping rules.
TranslatorImpl(unsigned wwMode = GFxTranslator::WWT_Default) :
GFxTranslator(wwMode) {}

virtual unsigned GetCaps() const         
{ 
return Cap_StripTrailingNewLines; 
}
virtual void     Translate(TranslateInfo* ptranslateInfo)
{
// Translated strings start with $$sign
const wchar_t* pkey = ptranslateInfo->GetKey();
if (pkey[0] == '$')
{
WStringBuffer buffer;
size_t l = SFwcslen(pkey);
buffer.Resize(l + 100);
wchar_t* pb = buffer.GetBuffer();

//SFwcscpy(pb, buffer.GetLength(), pkey+1);
//ptranslateInfo->SetResult(buffer.ToWStr());

SFwcscpy(pb, buffer.GetLength(), L"<font color='#00FF33'>*TR[<font color='#FF3300'>");
SFwcscat(pb, buffer.GetLength(), pkey+1);
SFwcscat(pb, buffer.GetLength(), L"</font>]</font>");
ptranslateInfo->SetResultHtml(buffer.ToWStr());
}
// example of using GetInstanceName()
else if (SFstrcmp(ptranslateInfo->GetInstanceName(), "plainText") == 0)
{
ptranslateInfo->SetResult("PLAIN");
}
}
};
*/

#if defined(SF_OS_WIN32)

// Install system-specific clipboard implementation on Win32. If this is not done
// the clipboard will still work in FxPlayer, but it will be impossible to paste
// text to external applications.
class FxPlayerTextClipboard : public TextClipboard
{
public:
    void OnTextStore(const wchar_t* ptext, UPInt len)
    {
        // store the text in a system clipboard.
        if (OpenClipboard(NULL))
        {
            // Empty the Clipboard. This also has the effect
            // of allowing Windows to free the memory associated
            // with any data that is in the Clipboard
            EmptyClipboard();

            HGLOBAL hClipboardData;
            hClipboardData = GlobalAlloc(GMEM_DDESHARE, (len+1)*sizeof(wchar_t));
            SF_ASSERT(sizeof(wchar_t) == 2);

            // Calling GlobalLock returns a pointer to the 
            // data associated with the handle returned from 
            // GlobalAlloc
            wchar_t * pchData;
            pchData = (wchar_t*)GlobalLock(hClipboardData);
            SFwcscpy(pchData, len+1, ptext);

            // Once done, unlock the memory. 
            // don't call GlobalFree because Windows will free the 
            // memory automatically when EmptyClipboard is next 
            // called. 
            GlobalUnlock(hClipboardData);

            // Now, set the Clipboard data by specifying that 
            // Unicode text is being used and passing the handle to
            // the global memory.
            SetClipboardData(CF_UNICODETEXT, hClipboardData);

            // Finally, close the Clipboard which has the effect of 
            // unlocking it so that other  apps can examine or modify its contents.
            CloseClipboard();
        }
    }
};

class FxPlayerMultitouchInterface : public MultitouchInterface
{
public:
    // Should return maximum number of touch points supported by hardware
    virtual unsigned GetMaxTouchPoints() const { return 2; }

    // Should return a bit mask of supported gestures (see MTG_*)
    virtual UInt32   GetSupportedGesturesMask() const { return MTG_Pan | MTG_Zoom | MTG_Rotate; }

    // Sets multitouch input mode. If the input mode is not supported it should
    // return 'false'; otherwise 'true'.
    virtual bool     SetMultitouchInputMode(MultitouchInputMode) { return true; }
};

#endif

void FxPlayerAppBase::InitArgDescriptions(Platform::Args* args)
{
	using namespace Platform;
    BaseClass::InitArgDescriptions(args);

	ArgDesc options []=
    {
        //      {"","--------------spacer example------------------\n","",FxCmdOption::Spacer,""},
        {"",    "FileName",            Args::StringOption | Args::Positional, NULL, //"gfx_cri.swf", 
        "GFX or SWF file to load at startup"},
        {"arg", "Arg",                 Args::StringOption, NULL, //"gfx_cri.swf", 
        "Value for _global.gfxArg variable in ActionScript."},
        {"s",   "ScaleFactor",         Args::FloatOption, "1.0", 
        "<factor> Scale the movie window size by the specified factor."},

        {"vol", "SoundVolume",         Args::IntOption, "80", "Sound Volume. 0-100 (default 80)"},
        {"cksd", "CLIKSound",          Args::Flag, "", "Enable default CLIK sound events."},
        {"mute", "SoundMute",          Args::Flag, "", "Mute sound"},
        {"noclip", "NoClipping",      Args::Flag, "", "Disable stage clipping on startup"},
        {"na",  "noAA",                Args::Flag, "", "Use no anti-aliasing."},
        {"fsa", "FSAA",                Args::Flag, "", "Use use fullscreen HW AA."}, 
        {"nsf", "NoSystemFont",        Args::Flag, "", "No system font - disables FontProviderWin32."},
        {"nfc", "NoFontConfig",        Args::Flag, "", "Disable autoloading of font config file in movie's path."},
        {"fc",  "FontConfigFile",      Args::StringOption, "", "<fname> Load a font config file."},
        {"fl",  "FontLibFile",         Args::StringOption, NULL, 
                                       "<fname>  Specifies a SWF/GFX file to load into FontLib."},
        {"ipk", "UseImagePacker",      Args::Flag, "", "Use ImagePacker (for debug/test only)"},
        {"vp",  "VerboseParse",        Args::Flag, "", "Verbose parse - print SWF parse log."},
        {"vps", "VerboseParseShape",   Args::Flag, "" ,"Verbose parse shape - print SWF shape parse log."},
        {"vpa", "VerboseParseAction",  Args::Flag, "", "Verbose parse action - print SWF actions during parse."},
        {"vfq", "NoLogChildFilnames",  Args::Flag, "", "Do not print SWF filename for ActionScript errors in child movies."},
        {"vfr", "LogRootFilenames",    Args::Flag, "","Print SWF filename for ActionScript errors in root movies."},
        {"vfp", "LogFilePath",         Args::Flag, "", "Print full file path for ActionScript errors."},
        {"va",  "VerboseActions",      Args::Flag, "", "Verbose actions - display ActionScript execution log."},
        {"q",   "Quiet",               Args::Flag, "", "Quiet. Do not display errors or trace statements."},
        {"xmllog",   "XmlLog",         Args::Flag, "", "XML Log. Output errors and trace statement in XML format"},
        {"qae", "SuppressASErrors",    Args::Flag, "", "Quiet. Suppress ActionScript errors."},
        {"ml",  "LodBias",             Args::FloatOption, "-0.5", 
        "<bias>  Specify the texture LOD bias (float, default -0.5)"},
        {"rs",  "RecordStatistics",    Args::StringOption, NULL,
                                       "<filename> Save current performance/memory statistics at exit."},
        {"ff",  "FastForward",         Args::Flag, "", "Fast forward - run one frame per update."},
        {"fps", "LogFPS",              Args::Flag, "", "Log FPS to console every second."},
        {"1",   "PlayOnce",            Args::Flag, "", "Play once; exit when/if movie reaches the last frame."},
        {"nr",  "NoRendering",         Args::Flag, "", "Disable rendering (for batch tests)"},
        {"psh", "PrecompileShaders",   Args::Flag, "", "Compile all shaders on startup"},
        {"ns",  "NoSound",             Args::Flag, "", "Disable sound (for batch tests)"},
        {"nck", "NoControlKeys",       Args::Flag, "", "Disable all player related control keys."},
        {"t",   "ExitTimeout",         Args::FloatOption, "0.0",
        "<msec>    Timeout and exit after the specified number of milliseconds."},
        {"mtl", "ProgressiveLoading", Args::Flag, "", "Enable progressive loading."},
#if defined(FXPLAYER_RENDER_DIRECT3D) && (SF_D3D_VERSION != 10)
        {"dyn", "DynamicTextures" ,    Args::Flag, "", "Use dynamic textures (D3D)."},
#endif
        {"res", "Resolution",          Args::StringOption, "", "Override GFxPlayer resolution with custom values\n"
        "              of width and height using -res W:H."},
#ifdef SF_AMP_SERVER
        {"amp", "AmpPort",             Args::IntOption, "7534", "Port for AMP socket connection. (default 7534)"},
        {"wait","AmpWait",             Args::Flag, "0", "Wait until an AMP connection has been established"},
        {"pl","AmpProfileLevel",       Args::IntOption, "-1", "AMP function profiling level: 0=Low (default), 1=Medium, 2=High."},
        {"mem","AmpMemDetail",         Args::Flag, "0", "AMP detailed memory reports."},
#endif
        {"autotest","AutomatedTest",   Args::Flag, "", "Perform automated testing on the input .swf" },
        {"autodir", "AutoOutput",      Args::StringOption, "AutoOutput", "Destination directory for autotest output." },

        {"","",Args::ArgEnd,"",""},
    };
    args->AddDesriptions(options);
}

String FxPlayerAppBase::GetAppTitle() const
{
    String title("Scaleform GFxPlayer ");

    // Platform
    title += AppBase::GetPlatformName();

    // Version
    title += " v " GFX_VERSION_STRING;

    // Add the word "Debug" to the application
    // title if in debug build mode
#ifdef SF_BUILD_DEBUG
    title += " " SF_BUILD_STRING;
#endif

    return title;
}

String FxPlayerAppBase::GetFilePath() const
{
#if defined(SF_OS_XBOX360)
    return "D:\\Samples\\flash.swf";
#elif defined (SF_OS_PS3)
    return SYS_HOST_ROOT "/usr/local/cell/FxPlayer/flash.swf";
#elif defined (SF_OS_3DS)
    return "rom:/FxPlayer/flash.swf";
#elif defined (SF_OS_WII)
    return "FxPlayer/flash.swf";
#elif defined (SF_OS_NGP) || defined(SF_OS_WIIU)
    return String(GetDefaultFilePath()) + "/flash.swf";
#else
    // return String(GetDefaultFilePath()) + "/flash.swf";
    return "";
#endif
}


#define FXPLAYER_APP_TITLE  "GFx " GFX_VERSION_STRING

void FxPlayerAppBase::UpdateWindowTitle()
{
    String strTitle;
    
    if (pMovie && (MeasurePerformance || FastForward)) 
    {
        // Display frame rate in title
        //Format(strTitle, "{1} (fps:{0:3.1})", LastFPS, GetAppTitle());

        Render::HAL::Stats rstats;
        pRenderThread->GetRenderStats(&rstats);
        UInt64 displayTicks = pRenderThread->GetLastDisplayTicks();
        UInt64 otherTicks   = pRenderThread->GetLastDrawFrameTicks() - displayTicks;

        //@TODO - change sprintf to Format
        char buffer[512]; 
        if (pRenderThread->IsSingleThreaded())
        {
            SF::SFsprintf(buffer, sizeof(buffer),
                FXPLAYER_APP_TITLE " - FPS:%d (M=%d, P=%d, T=%d) A=%.3f, D=%.3f, O=%.3f",
                (int)LastFPS,
                rstats.Meshes, rstats.Primitives, rstats.Triangles,
                double(LastAdvanceTicks)/1000.0,
                double(displayTicks)/1000.0,
                double(otherTicks)/1000.0);
        }
        else
        {
            // TBD: Add Render thread FPS once they are de-synchronized.
            //" - A_FPS:%d, R_FPS:%d  (M=%d, P=%d, T=%d) A=%.3f, D=%.3f, O=%.3f",

            SF::SFsprintf(buffer, sizeof(buffer),
                FXPLAYER_APP_TITLE " MT - FPS:%d (M=%d, P=%d, T=%d) A=%.3f, D=%.3f, O=%.3f",
                (int)LastFPS, // LastDisplayFrames,
                rstats.Meshes, rstats.Primitives,rstats.Triangles,
                double(LastAdvanceTicks)/1000.0,
                double(displayTicks)/1000.0,
                double(otherTicks)/1000.0);
        }
        strTitle = buffer;
    }    

    if (strTitle.IsEmpty())
    {
        strTitle = GetAppTitle();
        if (pRenderThread)
        {
            if (pRenderThread->IsSingleThreaded())
                strTitle += " ST ";
            else
                strTitle +="  MT ";
        }
        else
            strTitle = "  NR ";
    }
    
    if (ViewConfigHasFlag(Platform::View_VSync))
        strTitle += " VSync";

#ifdef SF_AMP_SERVER
    String portString;
    if (AmpServer::GetInstance().IsValidConnection())
    {
        Format(portString, " Connected to AMP ({0})", AmpPort);
    }
    else if (AmpServer::GetInstance().IsEnabled())
    {
        Format(portString, " Listening for AMP ({0})", AmpPort);
    }
    strTitle += portString;
#endif

    SetWindowTitle(strTitle);
}


bool FxPlayerAppBase::OnArgs(const Platform::Args& args, Platform::Args::ParseResult parseResult) 
{
    if (!BaseClass::OnArgs(args, parseResult))
        return false;

    if (args.HasValue("FileName"))
    {
        FileName = args.GetString("FileName");
    }
    String path = FileName.GetPath();
    if (path.GetLength() == 0)
        path = ".";
#if defined(SF_OS_XBOX360) || defined(SF_OS_WIN32)
    ContentDir.Reread(path, "*.swf;*.gfx");
#else
    ContentDir.Reread(path, "*.swf");
#endif

    String customRes = args.GetString("Resolution");
    if (customRes.GetSize() > 0)
    {
        const char* restr = customRes.ToCStr();
        ArgResolution.Width = (unsigned) atoi(restr);
        restr = SFstrchr(restr, ':');
        if (!restr) 
            ArgResolution.Clear();
        else 
            ArgResolution.Height = (unsigned) atoi(restr+1);
    }
    ScaleX = ScaleY = args.GetFloat("ScaleFactor");
    Rendering =       !args.GetBool("NoRendering");
    DoSound =         !args.GetBool("NoSound");
    FastForward =     args.GetBool("FastForward");
    ExitTimeout =     args.GetFloat("ExitTimeout");
    ClippingEnable =  !args.GetBool("NoClipping");

    PlayOnce = args.GetBool("PlayOnce");
    NoControlKeys = args.GetBool("NoControlKeys");
    NoCtrlKey = NoControlKeys;
    SoundVolume = args.GetInt("SoundVolume") / 100.0f;
    if(SoundVolume < 0.0f)
        SoundVolume = 0.0f;
    else if (SoundVolume > 1.0f)
        SoundVolume = 1.0f;

    IsMute     = args.GetBool("SoundMute");
    bCLIKSound = args.GetBool("CLIKSound");

#ifdef SF_AMP_SERVER
    AmpPort = args.GetInt("AmpPort");
#endif

    // Automated tests implies fast forward.
    if (args.GetBool("AutomatedTest"))
    {
        AutoOutputDir = args.GetString("AutoOutput");
        AutomatedTest = true;
        FastForward = true;        

        // Important: Seed the random number generator if doing the autotest.
        // Otherwise, AS that uses the random functions will appear differently
        // in the output, and cause the tests to fail.
        Alg::Random::SeedRandom(13);

        // Also override the default timer, so that timer updates will be deterministic.
        Timer::SetTimerOverride(&AutoTimer);
    }

    return true;
}


bool FxPlayerAppBase::OnInit(Platform::ViewConfig& config)
{
    // Set the verbose flags.
    unsigned verboseFlags = 0;
	const Platform::Args& args = GetArgs();

    if (args.GetBool("VerboseParse"))//Settings.VerboseParse
        verboseFlags |= ParseControl::VerboseParse;
    if (args.GetBool("VerboseParseShape")) //Settings.VerboseParseShape
        verboseFlags |= ParseControl::VerboseParseShape;
    if (args.GetBool("VerboseParseAction")) //Settings.VerboseParseAction
        verboseFlags |= ParseControl::VerboseParseAction;


    // File callback.
    Ptr<FileOpener> pfileOpener = *new FxPlayerFileOpener;	
    mLoader.SetFileOpener(pfileOpener);

    SF::Ptr<GFx::ImageFileHandlerRegistry> pimgReg = *new GFx::ImageFileHandlerRegistry();
#ifdef SF_ENABLE_LIBJPEG
    pimgReg->AddHandler(&SF::Render::JPEG::FileReader::Instance);
#endif
#ifdef SF_ENABLE_LIBPNG
    pimgReg->AddHandler(&SF::Render::PNG::FileReader::Instance);
#endif
    pimgReg->AddHandler(&SF::Render::TGA::FileReader::Instance);
	pimgReg->AddHandler(&SF::Render::DDS::FileReader::Instance);
#if defined (SF_OS_WIIU)
	pimgReg->AddHandler(&SF::Render::GTX::FileReader::Instance);
#endif
#if defined (SF_OS_NGP)
	pimgReg->AddHandler(&SF::Render::GXT::FileReader::Instance);
#endif
    mLoader.SetImageFileHandlerRegistry(pimgReg);


#ifdef GFX_AS2_SUPPORT
    Ptr<ASSupport> pAS2Support = *new AS2Support();
    mLoader.SetAS2Support(pAS2Support);
#endif

#ifdef GFX_AS3_SUPPORT
    Ptr<ASSupport> pAS3Support = *new AS3Support();
    mLoader.SetAS3Support(pAS3Support);
#endif

#ifdef SF_OS_MAC
    /*
    // Keep images for renderer changes
    Ptr<ImageCreator> pImageCreator = *new ImageCreator(1);
    mLoader.SetImageCreator(pImageCreator);
    */
#endif

    //This is for GFxPlayer debug/test only, do not enable in your application.
    if (args.GetBool("UseImagePacker"))
    {
        Ptr<ImagePackParams> ppacker = *new ImagePackParams();
        ImagePackParams::TextureConfig config;
        ppacker->GetTextureConfig(&config);
        config.TextureHeight = config.TextureWidth = 1024;
        config.SizeOptions = ImagePackParamsBase::PackSize_PowerOf2;
        ppacker->SetTextureConfig(config);

        mLoader.SetImagePackParams(ppacker);
    }
    // Task Manager.
#ifdef SF_ENABLE_THREADS
    if (args.GetBool("ProgressiveLoading"))
    {
        pTaskManager = *new ThreadedTaskManager;
        #if defined(SF_OS_XBOX360)
            pTaskManager->AddWorkerThreads(Task::Type_IO, 3, 128 * 1024, 1);
        #endif
        mLoader.SetTaskManager(pTaskManager);
    }
#endif
    //mLoader.SetGradientParams(Ptr<GradientParams>(*new GradientParams(16)));

    // Set log, but only if not quiet
    if (!args.GetBool("Quiet")) //!Settings.Quiet
    {
        if (args.GetBool("XmlLog"))
        {
            mLoader.SetLog(Ptr<GFx::Log>(*new GFxPlayerXmlLog()));
        }
        else
        {
            mLoader.SetLog(Ptr<GFx::Log>(*new GFxPlayerLog()));
        }
    }
#ifdef SF_OS_WIN32    
    mLoader.SetTextClipboard(Ptr<TextClipboard>(*new FxPlayerTextClipboard()));
#endif    
    //mLoader.SetTranslator(Ptr<Translator>(*new TranslatorImpl()));

    // Configuring the glyph packer
    //-----------------------------
    //// Creating the packer
    //mLoader.SetFontPackParams(Ptr<FontPackParams>(*new FontPackParams()));
    //
    //// Optional TextureConfig
    ////-----------------------------
    //FontPackParams::TextureConfig fontPackConfig;
    //fontPackConfig.NominalSize = 32;
    //fontPackConfig.PadPixels   = 2;
    //fontPackConfig.TextureWidth  = 512;
    //fontPackConfig.TextureHeight = 512;
    //mLoader.GetFontPackParams()->SetTextureConfig(fontPackConfig);

    //// Optional restriction: If the font contains more than 1000 glyphs it will not be packed.
    //// Instead, this font will be displayed with the dynamic cache.
    ////-----------------------------
    //mLoader.GetFontPackParams()->SetGlyphCountLimit(1000);


    // Currently doesn't work in 4.0, to be revised and restored.
    // Preprocess parameters (Pre-tessellation)
    //-----------------------------
    //mLoader.SetPreprocessParams(Ptr<PreprocessParams>(*new PreprocessParams()));

    // Image Packer. Enable in Player only for testing; for production use packing in gfxexport.
    //mLoader.SetImagePackParams(Ptr<ImagePackParams>(*new ImagePackParams));

    // Configure Font compactor
    // FontCompactorParams contains the font compactor configuration options 
    // There are two parameters that can be set on the contractor of this class
    // 1. NominalSize - The nominal glyph size that corresponds with the input 
    //    coordinates. Small nominal size results in smaller total data size, 
    //    but less accurate glyphs. For example, NominalSize=256 can typically 
    //    save about 25% of memory, compared with NominalSize=1024, but really 
    //    big glyphs, like 500 pixels may have visual inaccuracy. For typical game 
    //    UI text NominalSize=256 is still good enough. In SWF it is typically 1024.
    // 2. MergeContours - A Boolean flag that tells, whether or not the 
    //    FontCompactor should merge the same contours and glyphs. When merging 
    //    the data can be more compact and save 10-70% of memory, depending on fonts.
    //    But if the font contains too many glyphs, the hash table may consume 
    //    additional memory, 12 (32-bit) or 16 (64-bit) bytes per each unique path, 
    //    plus 12 (32-bit) or 16 (64-bit) bytes per each unique glyph.
    //mLoader.SetFontCompactorParams(Ptr<FontCompactorParams>(*new FontCompactorParams(256, true)));

    SetFontProvider();

    if (FileName.GetLength() == 0)
    {
        FileName = GetFilePath();
        String path = FileName.GetPath();
        if (path.GetLength() == 0)
            path = ".";

        // Directory implementation for X360 and Win32 support multiple extensions. Others do not.
#if defined(SF_OS_XBOX360) || defined(SF_OS_WIN32)
        ContentDir.Reread(path, "*.swf;*.gfx");
#else
        ContentDir.Reread(path, "*.swf");
#endif
    }

    bool loadMovie = strlen(FileName)>0;
    if (loadMovie)
    {
        // if filename is set, then we try to load the font config
        LoadDefaultFontConfigFromPath(FileName);

        // Tell the directory implementation of the current filename.
        ContentDir.SetCurrentFile(FileName);
    }
    // Apply font configuration on a loader
    if (FontConfigIndex != -1) 
    {
        FontConfig* pconfig = GetCurrentFontConfig();
        if (pconfig)
            pconfig->Apply(&mLoader);
    } 
    else 
    {
        // Create and load a file into FontLib if requested.
        if (args.HasValue("FontLibFile")) 
        {
            Ptr<FontLib> fontLib = *new FontLib;
            mLoader.SetFontLib(fontLib);
            Ptr<MovieDef> pmovieDef = *mLoader.CreateMovie(args.GetString("FontLibFile").ToCStr());
            fontLib->AddFontsFrom(pmovieDef);
        }
    }

    // Load movie for the stats display
    // Loader::LoadWaitCompletion should be set from threaded loading for HUD movie. 
    // Otherwise HUD will no be shown because is Advance method gets call only once when the
    // movie is not ready yet
 
    Ptr<ParseControl> pparseControl = *new ParseControl(verboseFlags);
    mLoader.SetParseControl(pparseControl);

#ifdef GFX_ENABLE_SOUND
    if (DoSound)
        // Initialize sound system(s)
        InitializeSound();
#endif

#ifdef GFX_ENABLE_VIDEO
    // Core video support
#if defined(SF_OS_WIN32)
    // The video player state for Windows has four initialization parameters
    // 1. ActionScript VM support: AS2, AS3 or all
    // 2. Priority of video decoding threads
    // 3. Number of video deciding threads (maximum is 3)
    // 4. An array with affinity masks for each decoding thread
    UInt32 affinityMasks[] = {
        DEFAULT_VIDEO_DECODING_AFFINITY_MASK,
        DEFAULT_VIDEO_DECODING_AFFINITY_MASK,
        DEFAULT_VIDEO_DECODING_AFFINITY_MASK
    };
    Ptr<Video::Video> pvideo = *new Video::VideoPC(Video::VideoVMSupportAll(),
        Thread::NormalPriority, MAX_VIDEO_DECODING_THREADS, affinityMasks);
#elif defined(SF_OS_XBOX360)
    // The video player state for Xbox360 has four initialization parameters: 
    // 1. ActionScript VM support: AS2, AS3 or all
    // 2. Mask which specifies which hardware threads will be used for video decoding
    // 3. Priority of video decoding threads
    // 4. Hardware thread which will be used for the video reader
    Ptr<Video::Video> pvideo = *new Video::VideoXbox360(Video::VideoVMSupportAll(),
        Video::Xbox360_Proc3|Video::Xbox360_Proc4|Video::Xbox360_Proc5, Thread::NormalPriority,
        Video::Xbox360_Proc2);
#elif defined(SF_OS_PS3)
    // The video player state for PS3 has six initialization parameters:
    // 1. ActionScript VM support: AS2, AS3 or all
    // 2. CellSpurs structure pointer
    // 3. Number of PPU threads which can be used for video decoding
    // 4. Priority of PPU threads
    // 5. Number of SPUs which can be used for video decoding
    // 6. SPURS task priorities
    UInt8 spursPrios[] = {0, 0, 1, 1, 1, 1, 0, 0};
    Ptr<Video::Video> pvideo = *new Video::VideoPS3(Video::VideoVMSupportAll(),
        GetSpurs(), 1, Thread::NormalPriority, 4, spursPrios);
#else
    // 1. ActionScript VM support: AS2, AS3 or all
    // 2. Priority of the video decoding thread
    Ptr<Video::Video> pvideo = *new Video::Video(Video::VideoVMSupportAll(),
        Thread::NormalPriority);
#endif

    // Video system sound interfaces
#ifdef GFX_VIDEO_USE_SYSTEM_SOUND
#if   defined(SF_OS_WIN32)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemDX8(0)));
#elif defined(SF_OS_MAC)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemMac()));
#elif defined(SF_OS_XBOX360)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemXA2(0,0)));
#elif defined(SF_OS_PS3)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemPS3(true, GetSpurs())));
#elif defined(SF_OS_WII)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemWii(true)));
#elif defined(SF_OS_WIIU)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemWiiU(true)));
#endif
    // FMOD & Wwise system sound interfaces
#elif defined(GFX_VIDEO_USE_FMOD)
    pvideo->SetSoundSystem(Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemFMOD(pSoundFMODSystem->GetFMOD())));
#elif defined(GFX_VIDEO_USE_WWISE)
    pWwise = Ptr<Video::VideoSoundSystem>(*new Video::VideoSoundSystemWwise());
    pvideo->SetSoundSystem(pWwise);
#endif // GFX_VIDEO_USE_SYSTEM_SOUND

    mLoader.SetVideo(pvideo);
#endif // GFX_ENABLE_VIDEO

#ifdef GFX_ENABLE_SOUND
    Sound::SoundRenderer* psoundRenderer = GetSoundRenderer();
    if (psoundRenderer)
    {
        // Sound renderer and parameters for playing SWF streaming sounds are provided to
        // to the loader by GFx::Audio. Those parameters control when and how the synchronization
        // between SWF frames and sound frames should be done.
        Ptr<Audio> paudio = *new Audio(psoundRenderer);
        mLoader.SetAudio(paudio);
        psoundRenderer->SetMasterVolume(SoundVolume);
        psoundRenderer->Mute(IsMute);

#if defined(GFX_ENABLE_VIDEO) && !defined(GFX_VIDEO_USE_SYSTEM_SOUND) && \
                                 !defined(GFX_VIDEO_USE_FMOD) && !defined(GFX_VIDEO_USE_WWISE)
        // if a video has audio tracks and you want to play them through SoundRenderer 
        // object you need to set this object to Video::Video state
        pvideo->SetSoundSystem(psoundRenderer);
#endif
    }
#endif // GFX_ENABLE_SOUND

    // 
    // SharedObject support
    //
#if defined(GFX_AS2_ENABLE_SHAREDOBJECT) && defined(GFX_ENABLE_XML)

    String SOPath;
    SOPath.AppendString(FileName);
    URLBuilder::ExtractFilePath(&SOPath);
    if (SOPath.CompareNoCase(FileName) == 0)
    {
        SOPath = "";
    } 
    // GFx currently does not support creation of directories
    //SOPath.AppendString(".soCache/");
    Ptr<SharedObjectManagerBase> psomgr = *new FxSharedObjectManager(SOPath);
    mLoader.SetSharedObjectManager(psomgr);

#endif  // GFX_AS2_ENABLE_SHAREDOBJECT


#ifdef GFX_ENABLE_XML

    Ptr<XML::Parser> pexpatXmlParser = *new XML::ParserExpat;
    Ptr<XML::SupportBase> pxmlSupport = *new XML::Support(pexpatXmlParser);
    mLoader.SetXMLSupport(pxmlSupport);

    //
    // Using the default parser for document processing from C++
    // ---------------------------------------------------------
    // (Not available in eval/lib distributions)
    //
    //#include "GFx/XML/XML_DOM.h"
    //
    // -- Create a DOM builder that processes whitespace
    //XML::DOMBuilder domBuilder(pxmlSupport);
    // -- Create a DOM builder that ignores whitespace
    //XML::DOMBuilder domBuilder2(pxmlSupport, true);
    //
    // -- Process the xml file and return the root of the DOM tree
    //Ptr<XML::Document> pdoc = domBuilder.ParseFile("inputfile.xml", mLoader.GetFileOpener());
    // -- Process the xml file and return the root of the DOM tree (use provided object manager)
    //Ptr<XML::ObjectManager> pobjMgr = *new XML::ObjectManager();
    //Ptr<XML::Document> pdoc2 = domBuilder.ParseFile("inputfile.xml", mLoader.GetFileOpener(), pobjMgr);
    // 

#endif


    if (loadMovie)
    {
        // Get info about the width & height of the movie.
#ifdef GFX_ENABLE_VIDEO
        if (IsVideoFile(FileName))
        {
            Video::VideoPlayer::VideoInfo vinfo;
            if (Video::VideoPlayer::LoadVideoInfo(FileName, &vinfo, mLoader.GetFileOpener()))
            {
                MViewSize.Width  = (int)(vinfo.Width  * ScaleX);
                MViewSize.Height = (int)(vinfo.Height * ScaleY);
            }
            else 
            {
                if (args.GetBool("Quiet"))
                    fprintf(stderr, "Error: Failed to get USM file info: '%s'\n", FileName.ToCStr());
                loadMovie = 0;
            }
        }
        else
#endif
        {
        if (!mLoader.GetMovieInfo(FileName, &mMovieInfo)) 
        {
            // mLoader.GetMovieInfo will print error message unless we are in quiet mode
            if (args.GetBool("Quiet"))
                fprintf(stderr, "Error: Failed to get info about '%s'\n", FileName.ToCStr());
            loadMovie = 0;
        } 
        else
        {
            MViewSize.Width  = (int)(mMovieInfo.Width  * ScaleX);
            MViewSize.Height = (int)(mMovieInfo.Height * ScaleY);
        }
        }
    }
    if (!loadMovie)
    {
        MViewSize = Platform::Device::GetDefaultViewSize();
    }

    if ( args.GetBool("AutomatedTest"))
    {
        // Enable VSync. It may interfere with screenshots.
        config.SetFlag(Platform::View_VSync, true);

#ifdef GFX_ENABLE_XML
        // Attempt to load the 'instructions'.
        String autoTestFilename = FileName;
        autoTestFilename.AppendString(".autotest");
        XML::DOMBuilder domBuilder(pxmlSupport);
        AutoInstructions = domBuilder.ParseFile(autoTestFilename.ToCStr(), mLoader.GetFileOpener());       

        // Construct a default test, which just takes a screenshot, advances one second, and takes another.
        if ( !AutoInstructions || !AutoInstructions->FirstChild ) 
        {
            fprintf(stderr, "Failed load autotest instructions from '%s'. Using default instructions.\n", autoTestFilename.ToCStr());
            String defaultInstructions = 
                "<AutoTest>\n"
                "    <Instruction name=\"MouseMove\" x=\"0\" y=\"0\"/>\n"
                "    <Instruction name=\"TakeScreenshot\" postfix=\"Time0\"/>\n"
                "    <Instruction name=\"AutoAdvance\" delta=\"1.0\"/>\n"
                "    <Instruction name=\"TakeScreenshot\" postfix=\"Time1\"/>\n"
                "    <Instruction name=\"AutoAdvance\" delta=\"9.0\"/>\n"
                "    <Instruction name=\"TakeScreenshot\" postfix=\"Time10\"/>\n"
                "</AutoTest>";
            AutoInstructions = domBuilder.ParseString(defaultInstructions.ToCStr(), defaultInstructions.GetLength());
            if (!AutoInstructions || !AutoInstructions->FirstChild )
            {
                fprintf(stderr, "Failed to parse default instructions.\n" );
                return false;
            }
        }

        // Iterate directly to the instructions.
        NextAutoInstruction = AutoInstructions->FirstChild;
        while ( NextAutoInstruction && NextAutoInstruction->Type != 1 )
            NextAutoInstruction = NextAutoInstruction->NextSibling;
        if (NextAutoInstruction )
        {
            NextAutoInstruction = ((XML::ElementNode*)NextAutoInstruction.GetPtr())->FirstChild;
            while ( NextAutoInstruction && NextAutoInstruction->Type != 1 )
                NextAutoInstruction = NextAutoInstruction->NextSibling;
        }
        SF_ASSERT(SFstricmp(NextAutoInstruction->Value.ToCStr(), "Instruction" ) == 0 );
#else
        // Can't automated test without XML support.
        fprintf(stderr, "Can't do automated tests without XML support.\n");
        return false;
#endif
    }


    if (Rendering) 
    {
        bool           fsaa = (AAMode == AAMode_FSAA) ? true : false;
        Size<unsigned> defSize = Platform::Device::GetDefaultViewSize();

        /*
        // MA TBD:
#if defined(SF_OS_WIN32) && defined(FXPLAYER_RENDER_DIRECT3D) && (SF_D3D_VERSION != 10)
        if (GetArgs().GetBool("DynamicTextures"))
        {
            VMCFlags |= RENDERER_HAL::VMConfig_UseDynamicTex;
        }
#endif
        */

        if (!ArgResolution.IsNull()) 
            MViewSize = ArgResolution;

        if (IsConsole())
        {
            config.ViewFlags |= Platform::View_FullScreen;
            ScaleX = ((float)defSize.Width)  / MViewSize.Width;
            ScaleY = ((float)defSize.Height) / MViewSize.Height;
			MViewSize = defSize;
        }
        if (fsaa)
            config.ViewFlags |= Platform::View_FSAA;
        // VSync...

        Size<unsigned> appliedSize = MViewSize;
        appliedSize.Height += FXPLAYER_LOGO_BORDER;
        config.ViewSize = appliedSize;
        config.ViewFlags |= Platform::View_WindowResizable|Platform::View_WindowDropFiles;
        
        config.MinSize = MinSize;
        config.SetFlag(Platform::View_PrecompileShaders, args.GetBool("PrecompileShaders"));

        config.ViewFlags |= Platform::View_Stereo;
        

        // Create the window and RenderThread. If doing autotest, run in single threaded mode.
        if (!OnInitHelper(config, GetAppTitle(), AutomatedTest ? Platform::TT_SingleThreaded : Platform::TT_Unspecified ))
            return false;

        // It is important to initialize these sizes, in case OnSizeEnter gets called.
        SizingSize = GetViewSize();
        // Size might be changed by OnInitHelper call above.
        if (GetViewSize() != appliedSize)
            UpdateViewSize();
		GetRenderThread()->SetBackgroundColor(BackgroundColor);

#ifdef GFX_ENABLE_VIDEO
        Render::TextureManager* ptexMan = GetRenderThread()->GetTextureManager();
        if (pvideo && ptexMan)
            pvideo->SetTextureManager(ptexMan);
#endif
    }


	Ptr<GFx::IMEManagerBase> pimemanager = 0;
    if (IsImeEnabled())
    {
#if defined(SF_ENABLE_IME) && defined(SF_ENABLE_IME_WIN32)
        //!Create IMEManager after the application window has been set up since 
        
	//	pimemanager = InitIME();
		pimemanager = *new GFx::IME::GFxIMEManagerWin32((HWND)GetDeviceWindow()->GetHandle());
        if (pimemanager)
        {
            // For error logging. If error logging not desired, just pass null to Init. User must 
            // call Init though!
			/*  Parameters:
			1- Logger used to log IME messages. If not logging is desired, pass NULL
			2- Fileopener necessary to open the ime.xml file that contains the list of supported IME's. If NULL, a default
				list will be used instead
			3- Path for the ime.xml file that contains a list of supported IMEs
			4- Used to set if while loading the candidate list swf, IMEManager should check if the file exists in 
			   current directory (where the parent swf is located) or not. If false, IMEManager will not check
			   if the file exists, and if the file is eventually not found, an error message will be printed.
			   This is useful if you have you own file management system and you want FileOpener::OpenFile to be
			   called regardless. 
			*/	
            pimemanager->Init(NULL /*mLoader.GetLog()*/, pfileOpener, "ime.xml", true);
            pimemanager->SetIMEMoviePath("IME.swf");
            mLoader.SetIMEManager(pimemanager);
            // mLoader keeps the object from this point
        //    pimemanager->Release();
        }
#endif
    }



#ifdef SF_AMP_SERVER
    GFx::AMP::MessageAppControl caps;
    caps.SetCurveToleranceDown(true);
    caps.SetCurveToleranceUp(true);
    caps.SetNextFont(true);
    caps.SetRestartMovie(true);
    caps.SetToggleAaMode(true);
    caps.SetToggleAmpRecording(true);
    caps.SetToggleFastForward(true);
    caps.SetToggleInstructionProfile(true);
    caps.SetToggleOverdraw(true);
    caps.SetToggleBatch(true);
    caps.SetToggleStrokeType(false);
    caps.SetTogglePause(true);
    caps.SetToggleWireframe(true);
    AmpServer::GetInstance().SetAppControlCaps(&caps);
    AmpServer::GetInstance().SetAppControlCallback(this);
    if (args.GetBool("AmpWait"))
    {
        AmpServer::GetInstance().SetConnectionWaitTime(SF_WAIT_INFINITE);
    }
    if (args.GetInt("AmpProfileLevel") >= 0)
    {
        AmpServer::GetInstance().SetProfileLevel(static_cast<AmpProfileLevel>(args.GetInt("AmpProfileLevel")), true);
    }
    if (args.GetBool("AmpMemDetail"))
    {
        AmpServer::GetInstance().SetMemReports(true, true);
    }
    AmpServer::GetInstance().SetListeningPort(AmpPort);
    AmpDirty = true;

    AmpServer::GetInstance().OpenConnection();
#endif

    // Load movie and initialize timing.
    if (!SkipLoadMovie && loadMovie && !LoadMovie(FileName)) 
    {
        //return 1;
    }

    // Animate as fast as possible.
    AdjustFrameTime();    
    AccumClockTicks = 0;
    PrevTicks = Timer::GetTicks();


    if (IsImeEnabled())
    {
#if defined(SF_ENABLE_IME) && defined(SF_ENABLE_IME_WIN32)
        if (pimemanager)
        {
            if(pMovie)
				pMovie->HandleEvent(GFx::Event::SetFocus);
        }
#endif
    }

    return true;
}

void FxPlayerAppBase::OnRenderThreadCreated()
{
    GlyphCacheParams gcParams;
    //gcParams.NumTextures = 0; // Disable dynamic raster cache.
    GetRenderThread()->SetGlyphCacheParams(gcParams);

    ToleranceParams tolParams;
    //tolParams.FillLowerScale = 0.5f; // Set thresholds for tessellation
    //tolParams.FillUpperScale = 2.0f;
    GetRenderThread()->SetToleranceParams(tolParams);
}


void FxPlayerAppBase::OnShutdown()
{
#ifdef SF_AMP_SERVER
    AmpServer::GetInstance().CloseConnection();
#endif

    pMovie = 0;
    pMovieDef = 0;

    // If we started worker threads in the renderer we must end them here;
    // otherwise FinishAllThreads will lock up waiting indefinitely.
#ifdef SF_ENABLE_THREADS
    if (pTaskManager)
    {
        pTaskManager->RequestShutdown();    
    }
#endif
#ifdef GFX_ENABLE_SOUND
    ShutdownSound();
#endif
    BaseClass::OnShutdown();
}

void FxPlayerAppBase::AdjustFrameTime()
{
    bool zeroFrameTime = false;

    if (Rendering)
    {
        if (MeasurePerformance)
            zeroFrameTime = true;
        if (!Paused &&
            (FastForward || ViewConfigHasFlag(Platform::View_VSync)))
            zeroFrameTime = true;
    }
    else
    {
        zeroFrameTime = true;
    }

    if (zeroFrameTime)
        SetFrameTime(0.0f);
    else
        SetFrameTime(1.0f / (pMovie ? mMovieInfo.FPS : 30.0f));    
}


void FxPlayerAppBase::SetMovieVariables(String& argString)
{
    // This should only be true if this is the Player application
    // Make sure to comment this out or set the value to false in your game
    if(pMovie->GetAVMVersion() == 1)
    {
        pMovie->SetVariable("_global.gfxPlayer", Value(true));

#ifdef GFX_ENABLE_SOUND
        Value _global, soundFunc;
        pMovie->GetVariable(&_global, "_global");
        Ptr<GFxSoundEventCallback> soundEventCallback = *new GFxSoundEventCallback(pMovie);
        pMovie->CreateFunction(&soundFunc, soundEventCallback);            
        _global.SetMember("gfxProcessSound", soundFunc);
#endif // GFX_ENABLE_SOUND


        // Pass command line argument to ActionScript if necessary.
        if (GetArgs().HasValue("Arg") && argString.IsEmpty())
            argString = GetArgs()["Arg"]->GetString();
        if (!argString.IsEmpty())
            pMovie->SetVariable("_global.gfxArg", argString.ToCStr());

        const char* language = (FontConfigIndex == -1) ? "Default"
            : FontConfigs[FontConfigIndex]->ConfigName.ToCStr();
        pMovie->SetVariable("_global.gfxLanguage", Value(language));
    }
	else if (pMovie->GetAVMVersion() == 2)
	{
		GFx::Value trueVal(true);
        GFx::Value arg("scaleform.gfx.Extensions");
        GFx::Value extensionsClass;

        pMovie->Invoke("flash.utils.getDefinitionByName", &extensionsClass, &arg, 1);
        SF_ASSERT(extensionsClass.IsObject());

        extensionsClass.SetMember("isGFxPlayer", trueVal);

		// AS3 CLIK_addedToStageCallback Log Messages
		GFx::Value loadFunc;
		Ptr<LogLoadHandler> pLoadHandler = *new LogLoadHandler(pMovie);
		pMovie->CreateFunction(&loadFunc, pLoadHandler, NULL);
		extensionsClass.SetMember("CLIK_addedToStageCallback", loadFunc);
	}
}

void FxPlayerAppBase::OnConfigurationChange(const Platform::ViewConfig& config)
{
    SF_UNUSED1(config);
    pRenderThread->UpdateConfiguration();
}


bool FxPlayerAppBase::ValidateDeviceStatus()
{
    if (!Rendering)
        return true;
    
    // Handle D3D9 lost devices.
    bool                   deviceReady = true;
    Platform::DeviceStatus deviceStatus = pRenderThread->GetDeviceStatus();

    if (deviceStatus != Platform::Device_Ready)
    {
        if (deviceStatus == Platform::Device_NeedReconfigure)
        {
            Platform::ViewConfig config;
            GetViewConfig(&config);
            // ReconfigureGraphics is a synchronizing command, so it'll
            // update the status.
            ReconfigureGraphics(config);
        }
        else
        {   
            if (GetFrameTime() != 0.0f)
                Thread::MSleep(10);
            pRenderThread->UpdateDeviceStatus();
            deviceReady = false;
        }
    }

    return deviceReady;
}


bool FxPlayerAppBase::AdvanceMovie(float deltaT)
{
    // Potential out-of bounds range is not a problem here,
    // because it will be adjusted for inside of the player.
    if (pMovie) 
    {
        UInt64 startAdvanceTicks = Timer::GetProfileTicks();

        Size<unsigned> vsz = GetViewSize();

        // It's important to case size difference to int, as otherwise it will yield
        // large numbers instead of negative ones (which are allowed).
        pMovie->SetViewport((int)vsz.Width, (int)vsz.Height,
                            ((int)vsz.Width-(int)MViewSize.Width)/2, 
                            ((int)vsz.Height-(int)MViewSize.Height)/2,
                            (int)MViewSize.Width, (int)MViewSize.Height);
        pMovie->SetBackgroundAlpha(Background ? 1.0f : 0.0f);
    
        float timeTillNextFrame = pMovie->Advance(deltaT, 0);
        if (GetFrameTime() != 0.0f ) // Fast forward or Measure Performance modes
            SetFrameTime(Alg::Min( 1.0f / mMovieInfo.FPS, timeTillNextFrame));

        LastAdvanceTicks = Timer::GetProfileTicks() - startAdvanceTicks;

        // If we're reached the end of the movie, exit.
        if (pMovie->IsExitRequested() ||
            (PlayOnce && (pMovie->GetCurrentFrame() + 1 == pMovieDef->GetFrameCount())))
            return false;
    }
    else
    {
        LastAdvanceTicks = 0;
    }
    return true;
}


void FxPlayerAppBase::OnUpdateFrame(bool needRepaint)
{
    if ( AutomatedTest )
    {
        OnAutoUpdateFrame();
        return;
    }

    // TBD: Make use of 'needRepaint' once refresh is conditional on change.
    SF_UNUSED(needRepaint);

    HandleAmpAppMessages();
   
    // Update timing.
    UInt64 timer = Timer::GetTicks();
    UInt64 delta = timer - PrevTicks;
    PrevTicks = timer;
    AccumClockTicks += delta;

    if (Paused && Rendering)
        delta = 0;
    else if (FastForward || !Rendering)
        delta = (UInt64)(1000000.0f / mMovieInfo.FPS);

    // Check to see if exit timeout was hit.
    if ((ExitTimeout > 0.0f) && (AccumClockTicks >= (ExitTimeout * 1000.0f)))
    {
        Shutdown();
        return;
    }

    // Update (software) cursors.
    Cursor.UpdateCursor(GetMousePos(), pRenderThread );

#ifdef GFX_VIDEO_USE_WWISE
    pWwise->Update();
#endif

    if (!AdvanceMovie((float)delta / 1000000.f))
    {
        // If movie signaled exit, we are done.
        Shutdown();
        return;
    }

    if ((!ValidateDeviceStatus() || !Rendering ) && pMovie )
    {
        // If the device is in an invalid state we still must ensure NextCapture gets 
        // called on display handles. Otherwise capture change data will build up indefinitely.
        MovieDisplayHandle handle = pMovie->GetDisplayHandle();
        handle.NextCapture(pRenderThread ? pRenderThread->GetRenderer2D()->GetContextNotify() : 0 );

        // Need to 'trick' the context into thinking that a frame has ended, so that NextCapture will
        // process the snapshots correctly. Otherwise, snapshot heaps will build up while the device is lost.
        if ( pRenderThread && pRenderThread->GetRenderer2D()->GetContextNotify())
            pRenderThread->GetRenderer2D()->GetContextNotify()->EndFrameContextNotify();

        // Make sure to tick AMP, otherwise the messages will build up.
        SF_AMP_CODE(AmpServer::GetInstance().AdvanceFrame();)
        return;
    }

    // Capture is done by Advance.
    pRenderThread->WaitForOutstandingDrawFrame();
    pRenderThread->DrawFrame();

    // Update timing
    FrameCounter++;    
    if ((LastFPSUpdatedTicks + 1000000) <= AccumClockTicks)
    {
        LastFPS = 1000000.f * FrameCounter / (float)(AccumClockTicks - LastFPSUpdatedTicks);
        AccumFPS += LastFPS;
        LastFPSUpdatedTicks = AccumClockTicks;
        AccumFPSSecondCount++;
        FrameCounter = 0;
        //if (pRenderThread)
       //     LastDisplayFrames = pRenderThread->GetFrames();
            UpdateFpsDisplay();
    }
    
    // Update stats more frequently; each 1/5 of a second.
    if ((LastStatUpdatedTicks + 1000000/5) <= AccumClockTicks)
    {
        LastStatUpdatedTicks = AccumClockTicks;
        UpdateStatReports();
    }
}

void FxPlayerAppBase::OnAutoUpdateFrame()
{
#ifdef GFX_ENABLE_XML
    // Make sure that the movie has the mouse and keyboard count set, regardless of platform.
    // Because tests can be created on every platform, their 'capabilities' should be equivalent
    // when autotesting, so the output is also equivalent.
    if ( pMovie )
    {
        pMovie->SetMouseCursorCount(1);
        pMovie->SetControllerCount(1);
    }

    while ( NextAutoInstruction )
    {
        if ( NextAutoInstruction->Type != 1)
        {
            NextAutoInstruction = NextAutoInstruction->NextSibling;
            continue;
        }
        XML::ElementNode* element= (XML::ElementNode*)(NextAutoInstruction.GetPtr());

        // Standard FxPlayerCommand::Execute parameters (scan XML for them).
        String commandName("");
        bool keyDown = true;
        int controllerIdx = 0;

        // Interpret the default parameter attributes from the XML
        for (XML::Attribute* attr = element->FirstAttribute; attr != NULL; attr = attr->Next)
        {
            String attrName(attr->Name.ToCStr());
            if ( attrName.CompareNoCase("name") == 0 )
                commandName = attr->Value.ToCStr();
            else if ( attrName.CompareNoCase("controllerIdx") == 0 )
                controllerIdx = (int)SFatoq(attr->Value.ToCStr());
            else if ( attrName.CompareNoCase("keyDown") == 0 )
                keyDown = SFatoq(attr->Value.ToCStr()) != 0;                
        }

        // Find the command and try executing it.
        Ptr<FxPlayerCommand>* command = AutoCommandMap.GetCaseInsensitive(commandName);
        if ( !command )
            fprintf(stderr, "Could not locate autotest command: %s\n", commandName.ToCStr());
        else
            (*command)->Execute(this, controllerIdx, keyDown, element);

        NextAutoInstruction = NextAutoInstruction->NextSibling;
    }
#endif

    // Wait for the last frame. Exiting immediately may interfere with screenshots.
    if (pRenderThread)
        pRenderThread->WaitForOutstandingDrawFrame();

    // Shutdown
    Shutdown();
}

// Called every second
void FxPlayerAppBase::UpdateFpsDisplay()
{
    if (GetArgs().GetBool("LogFPS"))
    {
        float avgFPS = AccumFPS / AccumFPSSecondCount;
        printf("FPS: %6.2f, AVG FPS: %6.2f\n", LastFPS, avgFPS);
    }
}


FxPlayerCommand* FxPlayerAppBase::KeyToCommand(UInt32 key)
{
    Hash< UInt32, Ptr<FxPlayerCommand> >::Iterator it = KeyCommandMap.Find(key);
    if (it != KeyCommandMap.End())
    {
        return it->Second;
    }
    return NULL;
}

FxPlayerCommand* FxPlayerAppBase::PadKeyToCommand(PadKeyCode key)
{
    Hash< UInt32, Ptr<FxPlayerCommand> >::Iterator it = KeyCommandMap.Find(key);
    if (it != KeyCommandMap.End())
    {
        return it->Second;
    }
    return NULL;
}


// An example of ExternalInterface handler implementation
class CustomEIHandler : public ExternalInterface
{
public:
    void Callback(Movie* pmovieView, const char* methodName, const Value* args, unsigned argCount)
    {
        Ptr<GFx::Log> pLog = pmovieView->GetLog();
        pLog->LogMessage("\nCallback! %s, nargs = %d\n", (methodName)?methodName:"(null)", argCount);
        for (unsigned i = 0; i < argCount; ++i)
        {
            pLog->LogMessage("  arg(%d) = ", i);
            switch(args[i].GetType())
            {
            case Value::VT_String:	pLog->LogMessage("%s", args[i].GetString()); break;
            case Value::VT_Number:	pLog->LogMessage("%f", args[i].GetNumber()); break;
			case Value::VT_Int:		pLog->LogMessage("%d", args[i].GetInt()); break;
			case Value::VT_UInt:	pLog->LogMessage("%u", args[i].GetUInt()); break;
            case Value::VT_Boolean: pLog->LogMessage("%s", (args[i].GetBool())?"true":"false"); break;
                // etc...
            default:
                break;
            }
            pLog->LogMessage("\n");
        }
    }

	// oscar@snda
	virtual InteractiveObject*  GetTopMostEntity(const PointF& mousePos, unsigned controllerIdx, 
		bool testAll, const InteractiveObject* ignoreMC = NULL, GFx::DisplayObjectBase** ppRootObj = NULL)
	{
		SF_UNUSED5(mousePos, controllerIdx, testAll, ignoreMC, ppRootObj);
		return 0;
	}

	virtual void MousePosToMovieSpace(PointF& mouseMovieSpace, const PointF& mouseOSSpace)
	{
		SF_UNUSED2(mouseMovieSpace, mouseOSSpace);
		// do nothing
	}
	// oscar@snda
};


// Load a new movie from a file and initialize timing
bool FxPlayerAppBase::LoadMovie( const String& filename)
{
    String filenameStr = filename;
    String argString;

#ifdef GFX_ENABLE_VIDEO
    if (IsVideoFile(filenameStr))
    {
        // Video USM file to SWF file as an argument.
        argString = filenameStr;
        filenameStr = "_internal_video_player";
        ClippingEnable = false;
    }
#endif

    // Try to load the new movie
    Ptr<MovieDef> pnewMovieDef;
    Ptr<Movie> pnewMovie;
    MovieInfo newMovieInfo;

    MovieCursorType = Platform::Cursor_Arrow;
    SetCursor(MovieCursorType);
    ResetUserMatrix();

    // Get info about the width & height of the movie.
    if (!mLoader.GetMovieInfo(filenameStr, &newMovieInfo, 0, Loader::LoadKeepBindData)) 
    {
        fprintf(stderr, "Error: Failed to get info about %s\n", filenameStr.ToCStr());
        return 0;
    }

    unsigned loadConstants = Loader::LoadAll;
	const Platform::Args& args = GetArgs();
    /*
    Ptr<ImageCreator> imageCreator = *new CustomImageCreator;
    mLoader.SetImageCreator(imageCreator);
    */

    // Set ActionScript verbosity / etc.
    Ptr<ActionControl> pactionControl = *new ActionControl();
    pactionControl->SetVerboseAction(args["VerboseActions"]->GetBool());
#ifdef GFC_NO_FXPLAYER_VERBOSE_ACTION
    if (args["VerboseActions"]->GetBool())
        fprintf(stderr, "VerboseAction is disabled by the GFC_NO_FXPLAYER_VERBOSE_ACTION macro in GFxConfig.h\n");
#endif

    pactionControl->SetActionErrorSuppress(args["SuppressASErrors"]->GetBool());
    pactionControl->SetLogRootFilenames(args["LogRootFilenames"]->GetBool());
    pactionControl->SetLogChildFilenames(!args["NoLogChildFilnames"]->GetBool());
    pactionControl->SetLongFilenames(args["LogFilePath"]->GetBool());


    // For D3D, it is good to override image creator to keep image data,
    // so that it can be restored in case of a lost device.
    if (!mLoader.GetImageCreator())
    {
        SF::Ptr<GFx::ImageCreator> pimageCreator = 
            *new GFx::ImageCreator(pRenderThread->GetTextureManager());
        mLoader.SetImageCreator(pimageCreator);
    }

    // Load the actual new movie and create instance.
    // Don't use library: this will ensure that the memory is released.
    pnewMovieDef = *mLoader.CreateMovie(filenameStr, loadConstants
//                                                                |Loader::LoadKeepBindData
                                                                |Loader::LoadWaitFrame1);
    if (!pnewMovieDef) 
    {
        fprintf(stderr, "Error: Failed to create a movie from '%s'\n", filenameStr.ToCStr());
        return 0;
    }

    // Tell the directory implementation of the current filename.
    ContentDir.SetCurrentFile(filenameStr);

    pnewMovie = *pnewMovieDef->CreateInstance(MemoryParams(), false, pactionControl);
    if (!pnewMovie) 
    {
        fprintf(stderr, "Error: Failed to create movie instance\n");
        return 0;
    }

    // If this succeeded, replace the old movie with the new one.
    pMovieDef = pnewMovieDef;
    pMovie = pnewMovie;
    memcpy(&mMovieInfo, &newMovieInfo, sizeof(MovieInfo));

    FileName = filenameStr;

    if (pRenderThread)
    {
        pRenderThread->AddDisplayHandle(pMovie->GetDisplayHandle());
        pRenderThread->ResetRasterizationCount();
    }
    // Release cached memory used by previous file.
//     if (pMovie->GetMeshCacheManager())
//         pMovie->GetMeshCacheManager()->ClearCache();

    // Set a reference to the app
    pMovie->SetUserData(this);

    if (IsCursorEnabled())    
        pMovie->SetMouseCursorCount(GetMouseCount());    
    pMovie->SetControllerCount(GetKeyboardCount());

    SetMovieVariables(argString);

    InstallHandlers();

    //!AB, set active movie..this causes OnMovieFocus to get called on the IMEManager
    pMovie->HandleEvent(GFx::Event::SetFocus);

    // init first frame
    pMovie->Advance(0.0f, 0);

    // Renderer
    if (Rendering) 
    {
        pMovie->SetEdgeAAMode((AAMode == AAMode_EdgeAA) ?
                              Render::EdgeAA_On : Render::EdgeAA_Disable);
    }

    if (DoSound) 
    { 
        // No built-in sound support currently in GFx. Customers
        // can play their own sound through fscommand() callbacks.
    }

    // Disable pause.
    Paused = false;
    AdjustFrameTime();    
    AccumClockTicks = 0;
    LastFPSUpdatedTicks = 0;
    LastStatUpdatedTicks = 0;
    PrevTicks = Timer::GetTicks();

    // Reset FPS counters used for FPS averaging.
    FrameCounter = 0;    
    LastFPS = 0.0f;
    AccumFPS = 0.0f;
    AccumFPSSecondCount = 0;

    // Update the view
    UpdateViewSize();
    AmpDirty = true;

    return 1;
}

// Called when sizing begins and ends.
void FxPlayerAppBase::OnSizeEnter(bool enterSize) 
{
    // When leaving size, adjust to new width/height.
    if (!enterSize) 
    {
        SizingEntered = 0;
        if (SizingSize != GetViewSize())
        {
            Platform::ViewConfig cfg;
            GetViewConfig(&cfg);
            cfg.ViewSize = SizingSize;
            cfg.ViewSize.Height += FXPLAYER_LOGO_BORDER;
            ReconfigureGraphics(cfg);
            UpdateViewSize();
        }
    } 
    else 
    {
        // Set SizingEntered flag so that we can differentiate size-grip
        // resize from instantaneous resize (maximize).
        SizingEntered = 1;        
        SizingSize = GetViewSize();
    }
}

// Sizing; by default, re-initalizes the renderer
void FxPlayerAppBase::OnSize(const Size<unsigned>& newSize) 
{
    SizingSize = newSize;
    if (!SizingEntered) 
    {
        // Commit sizing immediately if it was due to maximize.
        OnSizeEnter(0);
    } 
    else
    {
        if (!ViewConfigHasFlag(Platform::View_FullScreen))
            pRenderThread->PresentOnResize();
    }
}


#ifdef FXPLAYER_LOGO
Size<unsigned>  FxPlayerAppBase::GetViewSize() const
{
    Size<unsigned> winSize = AppBase::GetViewSize();
    winSize.Height -= FXPLAYER_LOGO_BORDER;
    return winSize;
}
#endif

// Updates the view size based on the ScaleEnable flag and window size.
void FxPlayerAppBase::UpdateViewSize() 
{
    if (ScaleEnable) 
    {
        int width = (int)Alg::Max<unsigned>(GetViewSize().Width, 4);
        int height= (int)Alg::Max<unsigned>(GetViewSize().Height, 4);

        if (ClippingEnable) 
        {
            // Determine movie size and location based on the aspect ratio
            float hw;
            if (mMovieInfo.Height != 0 && mMovieInfo.Width != 0)
                hw = (float) mMovieInfo.Height / (float) mMovieInfo.Width;
            else
                hw = (float) height / (float) width;
            if (width * hw > height) 
            {
                // Use height as the basis for aspect ratio
                MViewSize.Width = Alg::IRound((float) height / hw);
                MViewSize.Height = height;
            } 
            else 
            {
                // Use width
                MViewSize.Width = width;
                MViewSize.Height = Alg::IRound(width * hw);
            }
        } 
        else 
        {
            MViewSize.Width = width;
            MViewSize.Height = height;
        }

        // Compute input scale
        if ( mMovieInfo.Width != 0)
            ScaleX = (float) MViewSize.Width / (float) mMovieInfo.Width;
        else
            ScaleX = 1.0f;
        if ( mMovieInfo.Height != 0)
            ScaleY = (float) MViewSize.Height / (float) mMovieInfo.Height;
        else
            ScaleY = 1.0f;
    } 
    else 
    {
        // No scaling, just center the image
        MViewSize.Width = mMovieInfo.Width;
        MViewSize.Height = mMovieInfo.Height;
        ScaleX = ScaleY = 1.0f;
    }

   // MA TBD:
   // if (pRenderThread)
   //     pRenderThread->RecreateRenderer2D();
}



void FxPlayerAppBase::ResetUserMatrix() 
{
    Move = PointF(0.0f);
    Zoom = 1.0f;
    UpdateUserMatrix();
}

void FxPlayerAppBase::UpdateUserMatrix() 
{
    if (!pRenderThread)
        return;
    UserMatrix = Render::Matrix2F::Scaling(Zoom);
    UserMatrix.AppendTranslation(Move.x, Move.y);

    //	Render::Matrix2F m3d;
    //	m3d.AppendScaling(Zoom);
    //	m3d.AppendTranslation(Move.x * 2.f / MViewSize.Width, -Move.y * 2.f / MViewSize.Height);
    pRenderThread->SetUserMatrix(UserMatrix);    
}

//SizeF FxPlayerAppBase::GetMovieScaleSize() 
//{
//    SizeF scale;
//    scale.Width = (pMovie->GetVisibleFrameRect().Width() / ViewWidth);
//    scale.Height = (pMovie->GetVisibleFrameRect().Height() / ViewHeight);
//    return scale;
//}

bool FxPlayerAppBase::HandleAmpRequest(const GFx::AMP::MessageAppControl* message)
{
    Lock::Locker locker(&AmpCallbackLock);
    AmpAppControlMsgs.PushBack(const_cast<GFx::AMP::MessageAppControl*>(message));
    return true;
}


void FxPlayerAppBase::SetRendererProfiling(bool on)
{
	SF_UNUSED(on);
}

bool FxPlayerAppBase::TakeScreenShot( const String& filename )
{
    // This may update the viewport, etc. So do it before taking the screenshot.
    AdvanceMovie(0);
    pRenderThread->WaitForOutstandingDrawFrame();
    pRenderThread->DrawFrame();
    bool screenShot = pRenderThread->TakeScreenShot(filename);
    pRenderThread->DrawFrame();
    return screenShot;
}

void FxPlayerAppBase::ToggleAaMode()
{
    bool renderChange = false, edgeChange = false;
    
    switch(AAMode)
    {
    case AAMode_None:
        AAMode = AAMode_EdgeAA;
        edgeChange = 1;
        break;
    case AAMode_EdgeAA:
        AAMode = AAMode_FSAA;
        edgeChange = renderChange = 1;
        break;
    case AAMode_FSAA:
        AAMode = AAMode_None;
        renderChange = 1;
        break;
    }

    if (renderChange) 
    {
        // FSAA toggle.
        bool fsaa = (AAMode == AAMode_FSAA);
        Platform::ViewConfig config;        
        GetViewConfig(&config);

        if (fsaa != config.HasFlag(Platform::View_FSAA))
        {
            config.SetFlag(Platform::View_FSAA, fsaa);
            ReconfigureGraphics(config);
        }
    }
    if (edgeChange && pMovie)
    {
        pMovie->SetEdgeAAMode((AAMode == AAMode_EdgeAA) ?
                              Render::EdgeAA_On : Render::EdgeAA_Disable);
    }
    AmpDirty = true;

}

void FxPlayerAppBase::ToggleStrokeType()
{
//     UInt32 rf = pRenderConfig->GetRenderFlags();
//     UInt32 stroke = rf & RenderConfig::RF_StrokeMask;
// 
//     switch (stroke) 
//     {
//     case RenderConfig::RF_StrokeHairline:
//         stroke = RenderConfig::RF_StrokeNormal;
//         break;
//     case RenderConfig::RF_StrokeNormal:
//         stroke = RenderConfig::RF_StrokeCorrect;
//         break;
//     case RenderConfig::RF_StrokeCorrect:
//         stroke = RenderConfig::RF_StrokeHairline;
//         break;
//     }
//     pRenderConfig->SetRenderFlags((rf & ~RenderConfig::RF_StrokeMask) | stroke);
//     AmpDirty = true;
}

// Switch international font.
void FxPlayerAppBase::CycleFontConfig()
{
    if ((FontConfigIndex != -1) && (FontConfigs.GetSize() > 1))
    {
        // Apply different settings and reload file.

        FontConfigIndex++;
        FontConfigIndex %= (int)FontConfigs.GetSize();
        FontConfig* pconfig = GetCurrentFontConfig();
        if (pconfig)
        {
            pconfig->Apply(&mLoader);
            const char* language = (FontConfigIndex == -1) ? "Default"
                : pconfig->ConfigName.ToCStr();
            pMovie->Invoke("_root.OnLanguageChanged", "%s", language);
        }
        AmpDirty = true;
    }
}

void FxPlayerAppBase::HandleAmpAppMessages()
{
    AmpCallbackLock.DoLock();
    for (UPInt i = 0; i < AmpAppControlMsgs.GetSize(); ++i)
    {
        AMP::MessageAppControl* msg = AmpAppControlMsgs[i];
        if (msg->IsToggleWireframe())
        {
            Wireframe = !Wireframe;
            pRenderThread->SetWireframe(Wireframe);
        }
        if (msg->IsToggleOverdraw())
        {
            OverdrawProfile = !OverdrawProfile;
            BatchProfile = 0;
            pRenderThread->SetProfileMode(OverdrawProfile ? FxRenderThread::Profile_Overdraw : FxRenderThread::Profile_None);
        }
        if (msg->IsToggleBatch())
        {
            BatchProfile = !BatchProfile;
            OverdrawProfile = 0;
            pRenderThread->SetProfileMode(BatchProfile ? FxRenderThread::Profile_Batch : FxRenderThread::Profile_None);
        }
        if (msg->IsTogglePause())
        {
            Paused = !Paused;
            OnPause(Paused);
        }
        if (msg->IsToggleFastForward())
        {
            FastForward = !FastForward;
        }
        if (msg->IsToggleAaMode())
        {
            ToggleAaMode();
        }
        if (msg->IsToggleStrokeType())
        {
            ToggleStrokeType();
        }
        if (msg->IsRestartMovie())
        {
            Paused = false;
            OnPause(Paused);
            pMovie->Restart();
        }
        if (msg->IsNextFont())
        {
            CycleFontConfig();
        }
//         if (msg->IsCurveToleranceUp())
//         {
//             CurvePixelError = Alg::Min(10.0f, CurvePixelError + 0.5f);
//             pRenderConfig->SetMaxCurvePixelError(CurvePixelError);
//         }
//         if (msg->IsCurveToleranceDown())
//         {
//             CurvePixelError = Alg::Max(0.5f, CurvePixelError - 0.5f);
//             pRenderConfig->SetMaxCurvePixelError(CurvePixelError);
//         }
        if (!msg->GetLoadMovieFile().IsEmpty())
        {
            LoadMovie(msg->GetLoadMovieFile());
        }
        AmpDirty = true;
    }
    AmpAppControlMsgs.Clear();
    AmpCallbackLock.Unlock();

    UpdateAmpState();
}

void FxPlayerAppBase::UpdateAmpState()
{
#ifdef SF_AMP_SERVER
    if (AmpDirty)
    {
        Ptr<GFx::AMP::ServerState> ampState = *SF_NEW GFx::AMP::ServerState();

        ampState->StateFlags = AmpServer::GetInstance().GetCurrentState();
        ampState->ProfileLevel = AmpServer::GetInstance().GetProfileLevel();
        if (OverdrawProfile)
        {
            ampState->StateFlags |= GFx::AMP::Amp_RenderOverdraw;
        }
        else
        {
            ampState->StateFlags &= ~GFx::AMP::Amp_RenderOverdraw;
        }
        if (BatchProfile)
        {
            ampState->StateFlags |= GFx::AMP::Amp_RenderBatch;
        }
        else
        {
            ampState->StateFlags &= ~GFx::AMP::Amp_RenderBatch;
        }
        if (Wireframe)
        {
            ampState->StateFlags |= GFx::AMP::Amp_App_Wireframe;
        }
        else
        {
            ampState->StateFlags &= ~GFx::AMP::Amp_App_Wireframe;
        }
        if (Paused)
        {
            ampState->StateFlags |= GFx::AMP::Amp_App_Paused;
        }
        else
        {
            ampState->StateFlags &= ~GFx::AMP::Amp_App_Paused;
        }
        if (FastForward)
        {
            ampState->StateFlags |= GFx::AMP::Amp_App_FastForward;
        }
        else
        {
            ampState->StateFlags &= ~GFx::AMP::Amp_App_FastForward;
        }

        ampState->ConnectedApp = GetAppTitle();
        ampState->ConnectedFile = FileName;
        ampState->CurveToleranceMin = 0.5f;
        ampState->CurveToleranceMax = 10.0f;
        ampState->CurveToleranceStep = 0.5f;
        for (unsigned i = 0; i < FontConfigs.GetSize(); ++i)
        {
            ampState->Locales.PushBack(FontConfigs[i]->ConfigName);
        }
        switch (AAMode) 
        {
        case AAMode_None:
            ampState->AaMode = "None";
            break;
        case AAMode_EdgeAA:
            // Display a custom message if edge AA is #ifdef-ed out.
#ifndef SF_NO_FXPLAYER_EDGEAA
            ampState->AaMode = "Edge AA";
            //@TODO
//             {
//                 // Report if EdgeAA is not supported by renderer.
//                 Render::Renderer::RenderCaps caps;
//                 caps.CapBits = 0;
//                 if (GetRenderHAL())
//                     GetRenderHAL()->GetRenderCaps(&caps);
//                 if (!(caps.CapBits & Renderer::Cap_FillGouraud))
//                     ampState->AaMode = "Edge AA (Not Supported)";
//                 else if (!(caps.CapBits & Renderer::Cap_FillGouraudTex))
//                     ampState->AaMode = "Edge AA (Limited)";
//             }
#else
            ampState->AaMode = "Edge AA [#disabled]";
#endif
            break;
        case AAMode_FSAA:
            if (ViewConfigHasFlag(Platform::View_FSAA))
                ampState->AaMode = "HW FSAA";
            else
                ampState->AaMode = "HW FSAA (Not Supported)";
            break;
        }

        // Display a custom message if stroke is #ifdef-ed out.
// #ifndef SF_NO_FXPLAYER_STROKER
//         ampState->StrokeType = "Correct";
//         if (stroke == RenderConfig::RF_StrokeNormal)
//             ampState->StrokeType = "Normal";
// #else
//         ampState->StrokeType = "Correct [#disabled]";
//         if (stroke == RenderConfig::RF_StrokeNormal)
//             ampState->StrokeType = "Normal [#disabled]";
// #endif

        ampState->CurrentLocale = (FontConfigIndex == -1) ? "Default"
            : FontConfigs[FontConfigIndex]->ConfigName.ToCStr(); 
        ampState->CurveTolerance = CurvePixelError;

        AmpServer::GetInstance().UpdateState(ampState);
        AmpDirty = false;
    }
#endif
}

// Handle dropped file
void FxPlayerAppBase::OnDropFiles(const String& path)
{
    // unload the translator
    if (FontConfigIndex >= 0)
        mLoader.SetTranslator(NULL);

    if (LoadDefaultFontConfigFromPath(path) ) 
    {
        // set the font config
        FontConfig* pconfig = GetCurrentFontConfig();
        if (pconfig)
            pconfig->Apply(&mLoader);
    }

    // Unload current movie. If new movie fails to load try to re-load previous
    // if re-load fails we will see blank player.
    String prevPath;
    if (pMovieDef)
        prevPath = pMovieDef->GetFileURL();
    pMovie = 0;
    pMovieDef = 0;
    if (!LoadMovie(path) && (!prevPath.IsEmpty()))
        LoadMovie(prevPath);

    //!AB, set active movie
    //   if (pMovie)
    //       pMovie->HandleEvent(Event::SetFocus);

    BringWindowToFront();
}


void FxPlayerAppBase::ProcessCommand(unsigned controllerIdx, const FxPlayerCommand& cmd, bool downFlag)
{
    cmd.Execute(this, controllerIdx, downFlag);
}

void FxPlayerAppBase::OnKeyFinishSeek()
{
    Paused = true;
    pMovie->SetPlayState(GFx::State_Playing);
    // Ensure tag actions are executed. This may change frame state to Stopped.
    pMovie->Advance(0.0f);
    pMovie->SetPause(Paused);
    PausedState = pMovie->GetPlayState();
    AdjustFrameTime();
    AmpDirty = true;
}

void FxPlayerAppBase::ApplyLanguage(const char* name)
{
    if (name != NULL)
    {
        int idx = GetFontConfigIndexByName(name);
        if (idx != -1)
        {
            FontConfigIndex = idx;
            FontConfig* pconfig = FontConfigs[FontConfigIndex];
            pconfig->Apply(&mLoader);
            const char* language = pconfig->ConfigName.ToCStr();
            //pmovie->SetVariable("_global.gfxLanguage", Value(language));
            Value retVal;
            pMovie->Invoke("_root.OnLanguageChanged", &retVal, "%s", language);
        }
        else
        {
            if (pMovie->GetLog())
            {
                pMovie->GetLog()->LogError("\nLanguage support for '%s' not found!\n\n", name);
            }
        }
        FontLibChanged = true;
    }
}

void FxPlayerAppBase::InstallHandlers()
{
    pMovie->SetFSCommandHandler(Ptr<FSCommandHandler>(*new FxPlayerFSCallback(this)));
    pMovie->SetUserEventHandler(Ptr<UserEventHandler>(*new FxPlayerUserEventHandler(this)));

    // setting ExternalInterface handler
    Ptr<CustomEIHandler> pei = *new CustomEIHandler();
    pMovie->SetExternalInterface(pei);

#if defined(SF_OS_WIN32) && defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (GetAppImpl()->IsMultitouchSupported())
        pMovie->SetMultitouchInterface(Ptr<MultitouchInterface>(*new FxPlayerMultitouchInterface()));
#endif
}

void FxPlayerAppBase::SetFontProvider()
{
    // Create a system font provider on Windows. If this is not done,
    // system font characters will be displayed as squares.
    if (!GetArgs().GetBool("NoSystemFont")) 
    {
#ifdef SF_OS_WIN32
        Ptr<GFx::FontProviderWin32> fontProvider = *new GFx::FontProviderWin32(::GetDC(0));
        mLoader.SetFontProvider(fontProvider);
#endif

        //// An example of using FreeType-2 font provider
        //Ptr<GFx::FontProviderFT2> fontProvider = *new GFx::FontProviderFT2;
        ////fontProvider->MapFontToFile("AsiaHS-NC-0502", 0, "C:\\Windows\\Fonts\\AsiaHS_Large.ttf", 0, Font::HintAll, Font::DontHint);

        //fontProvider->MapFontToFile("Times New Roman", 0,                   "C:\\WINDOWS\\Fonts\\times.ttf");
        //fontProvider->MapFontToFile("Times New Roman", Font::FF_Bold,       "C:\\WINDOWS\\Fonts\\timesbd.ttf");
        //fontProvider->MapFontToFile("Times New Roman", Font::FF_Italic,     "C:\\WINDOWS\\Fonts\\timesi.ttf");
        //fontProvider->MapFontToFile("Times New Roman", Font::FF_BoldItalic, "C:\\WINDOWS\\Fonts\\timesbi.ttf");

        //fontProvider->MapFontToFile("Arial",           0,                  "C:\\WINDOWS\\Fonts\\arial.ttf");
        //fontProvider->MapFontToFile("Arial",           Font::FF_Bold,      "C:\\WINDOWS\\Fonts\\arialbd.ttf");
        //fontProvider->MapFontToFile("Arial",           Font::FF_Italic,    "C:\\WINDOWS\\Fonts\\ariali.ttf");
        //fontProvider->MapFontToFile("Arial",           Font::FF_BoldItalic,"C:\\WINDOWS\\Fonts\\arialbi.ttf");

        //fontProvider->MapFontToFile("Verdana",         0,                  "C:\\WINDOWS\\Fonts\\verdana.ttf");
        //fontProvider->MapFontToFile("Verdana",         Font::FF_Bold,      "C:\\WINDOWS\\Fonts\\verdanab.ttf");
        //fontProvider->MapFontToFile("Verdana",         Font::FF_Italic,    "C:\\WINDOWS\\Fonts\\verdanai.ttf");
        //fontProvider->MapFontToFile("Verdana",         Font::FF_BoldItalic,"C:\\WINDOWS\\Fonts\\verdanaz.ttf");
        //fontProvider->MapFontToFile("Georgia",         0,                  "C:\\WINDOWS\\Fonts\\georgia.ttf");
        //mLoader.SetFontProvider(fontProvider);

        // An example of using Vita libpvf font provider
        //String arial = String(GetDefaultFilePath())   + "arial.ttf";
        //String times = String(GetDefaultFilePath())   + "times.ttf";
        //String georgia = String(GetDefaultFilePath()) + "georgia.ttf";
        //Ptr<GFx::FontProviderNGP> fontProvider = *new GFx::FontProviderNGP(8, 0);
        //fontProvider->MapFontToFile("Arial", 0, arial);
        //fontProvider->MapFontToFile("Times New Roman", 0, times);
        //fontProvider->MapFontToFile("Georgia", 0, georgia);
        //mLoader.SetFontProvider(fontProvider);

    }
}

bool FxPlayerAppBase::HandleFsCommand(const char* pcommand, const char* parg)
{
    if (SFstrcmp(pcommand, "GFxApplyLanguage") == 0)
    {
        ApplyLanguage(parg);
    }
    else if (SFstrcmp(pcommand, "wireframe") == 0)
    {
        if (parg != NULL)
        {
            Wireframe = (atoi(parg) != 0);
            pRenderThread->SetWireframe(Wireframe);
            AmpDirty = true;
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool FxPlayerAppBase::HandleEvent(const GFx::Event& event)
{
    bool handled = false;
    const MouseCursorEvent& mcEvent = static_cast<const MouseCursorEvent&>(event);
    
    switch(event.Type)
    {
    case GFx::Event::DoShowMouse:
        if (mcEvent.MouseIndex == 0)
            SetCursor(MovieCursorType);
        handled = true;
        break;
    case GFx::Event::DoHideMouse:
        if (mcEvent.MouseIndex == 0)
            SetCursor(Platform::Cursor_Hidden);
        handled = true;
        break;

    case GFx::Event::DoSetMouseCursor:
        if (mcEvent.MouseIndex == 0)
        {
            switch(mcEvent.GetCursorShape())
            {
            default:
            case MouseCursorEvent::ARROW:
                MovieCursorType = Platform::Cursor_Arrow;
                break;
            case MouseCursorEvent::HAND:
                MovieCursorType = Platform::Cursor_Hand;
                break;
            case MouseCursorEvent::IBEAM:
                MovieCursorType = Platform::Cursor_IBeam;
                break;
            }
            if (GetCursor() != Platform::Cursor_Hidden)
                SetCursor(MovieCursorType);
        }
        handled = true;
        break;
    default:
        break;
    }
    return handled;
}

bool FxPlayerAppBase::IsImeEnabled() const
{
#if defined(SF_ENABLE_IME) && defined(SF_ENABLE_IME_WIN32)
    return true;
#else
    return false;
#endif
}

bool FxPlayerAppBase::OnIMEEvent(unsigned message, UPInt wParam, UPInt lParam, UPInt hWND, bool preprocess)
{
#ifndef SF_NO_IME_SUPPORT

	if (preprocess)
	{
		GFx::IMEWin32Event ev(GFx::IMEEvent::IME_PreProcessKeyboard, hWND, message, wParam, lParam, 0);
		if (pMovie)
		{
			UInt32 handleEvtRetVal = pMovie->HandleEvent(ev);
			return (handleEvtRetVal & Movie::HE_NoDefaultAction) != 0;
		}
		return Movie::HE_NotHandled;
	}
	GFx::IMEWin32Event ev(GFx::IMEEvent::IME_Default, hWND, message, wParam, lParam, true);
	if (pMovie)
	{
		UInt32 handleEvtRetVal = pMovie->HandleEvent(ev);
		return (handleEvtRetVal & Movie::HE_NoDefaultAction) != 0;
	}
	return Movie::HE_NotHandled;
	//	ForwardEventToMovie(event);
	//    return IMEHelper::OnEvent(event, pMovie);
#else
	SF_UNUSED5(message, wParam, lParam, hWND, preprocess);
	return false;
#endif
}

void FxPlayerAppBase::OnPad(unsigned controllerIdx, PadKeyCode keyCode, bool downFlag)
{
    if (!pMovie)
        return;
    switch(keyCode)
    {
    case SF::Pad_Left:
        OnKeyEvent(controllerIdx, Key::Left, 0, downFlag);
        return;
    case SF::Pad_Right:
        OnKeyEvent(controllerIdx, Key::Right, 0, downFlag);
        return;
    case SF::Pad_Up:
        OnKeyEvent(controllerIdx, Key::Up, 0, downFlag);
        return;
    case SF::Pad_Down:
        OnKeyEvent(controllerIdx, Key::Down, 0, downFlag);
        return;
    default:
        break;
    }

    FxPlayerCommand* command = PadKeyToCommand(keyCode);
    if (command != NULL)
    {
        if (downFlag || command->HandleKeyUp())
        {
            ProcessCommand(controllerIdx, *command, downFlag);
        }
    }
}


void FxPlayerAppBase::OnKey(unsigned controllerIndex, KeyCode keyCode,
                            unsigned wcharCode, bool downFlag, KeyModifiers mods) 
{
    if (!pMovie)
    {
        return;
    }

    bool ctrl = false;

	UInt32 keyPlusMods = mods.States & (KeyModifiers::Key_CtrlPressed |
								        KeyModifiers::Key_AltPressed |
								        KeyModifiers::Key_ShiftPressed);
    keyPlusMods <<= 16;
    keyPlusMods |= keyCode;

    if (!NoControlKeys) 
    {
        ctrl = mods.IsCtrlPressed();

        if (keyCode == Key::Control && !NoCtrlKey) 
        {
            return;
        }

        // TODO ???
        //if (keyCode == VK_MENU && downFlag)
        //    ControlKeyDown = false; // to enable Ctrl-Alt-... combinations to work

        if (downFlag && keyCode == Key::Escape)
        {
            // Cancel mouse manipulation
            if (MouseTracking != None) 
            {
                MouseTracking = None;           
                Zoom = ZoomStart;
                Move = MoveStart;
                UpdateUserMatrix();
                return;
            }
        }

        FxPlayerCommand* command = KeyToCommand(keyPlusMods);
        if (command != NULL)
        {
            if (downFlag || command->HandleKeyUp())
            {
                ProcessCommand(controllerIndex, *command, downFlag);
            }
        }
    }

    if (downFlag && (keyCode == Key::None) && wcharCode)
    {
        CharEvent event(wcharCode);
        pMovie->HandleEvent(event);
    }
    
    // Inform the player about keystroke
    if (!ctrl || NoCtrlKey)
    {
        OnKeyEvent(controllerIndex, keyCode, wcharCode, downFlag, mods);
    }
}

// Helper used to convert key codes and route them to GFxPlayer
void FxPlayerAppBase::OnKeyEvent(unsigned controllerIndex, KeyCode keyCode,
                                 unsigned int wcharCode, bool downFlag, KeyModifiers mods)
{
    if (keyCode != Key::None) 
    {
        if (pMovie) 
        {
            KeyEvent event(downFlag ? GFx::Event::KeyDown : KeyEvent::KeyUp,
                           keyCode, 0, wcharCode, mods, (UInt8)controllerIndex);
            pMovie->HandleEvent(event);
        }
    }
}

void FxPlayerAppBase::OnMouseButton(unsigned mouseIndex, unsigned button, bool downFlag, 
                                    const Point<int>& mousePos, KeyModifiers mods)
{
    bool ControlKeyDown = mods.IsCtrlPressed();
    if (!pMovie)
        return;
    MousePrevPos = mousePos;
	Render::PointF p = AdjustToViewPort(mousePos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    // UpdateStatBags mouse state
    if (downFlag) 
    {
        MouseDownPos = mousePos;

        if (button == 0 && ControlKeyDown && !NoCtrlKey)
        {
            MouseTracking = Zooming;
        }
        else if (button == 1 && ControlKeyDown && !NoCtrlKey)
        {
            MouseTracking = Moving;
        }

        if (MouseTracking != None) 
        {
            ZoomStart = Zoom;
            MoveStart = Move;
            return;
        }

        MouseEvent event(GFx::Event::MouseDown, button, p.x, p.y, 0.0f, mouseIndex);
        pMovie->HandleEvent(event);
    } 
    else 
    {
        if (MouseTracking != None)
        {
            MouseTracking = None;
            return;
        } 

        MouseEvent event(GFx::Event::MouseUp, button, p.x, p.y, 0.0f, mouseIndex);
        pMovie->HandleEvent(event);
    }
}


void FxPlayerAppBase::OnMouseWheel(unsigned mouseIndex, float zdelta,
                                   const Point<int>& mousePos, KeyModifiers mods)
{
    bool controlDown = mods.IsCtrlPressed();

	Render::PointF p = AdjustToViewPort(mousePos);

    if (controlDown && !NoCtrlKey)// && MouseTracking == None)
    {
        ZoomStart = Zoom;

        float dZoom = Zoom;
        Zoom += 0.02f * zdelta * Zoom;

        if (Zoom < 0.02f)
            Zoom = dZoom;

        dZoom -= Zoom;

        Render::Matrix m;
        m.AppendScaling(ZoomStart);
        m.AppendTranslation(Move.x, Move.y);
        p = m.TransformByInverse(p);

        Move.x += dZoom * p.x;
        Move.y += dZoom * p.y;

        UpdateUserMatrix();
        return;
    }

    if (!pMovie)
        return;


    Render::Matrix2F m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    MouseEvent event(GFx::Event::MouseWheel, 0, p.x, p.y, zdelta, mouseIndex);

    pMovie->HandleEvent(event);
}


void FxPlayerAppBase::OnMouseMove(unsigned mouseIndex,
                                  const Point<int>& mousePos, KeyModifiers mods)
{
    SF_UNUSED(mods);

    Point<int> delta = MousePrevPos - mousePos;
    MousePrevPos = mousePos;

    // Used by NotifyMouseState in the main loop
    if (!pMovie)
        return;

    if (MouseTracking == Zooming) 
    {
        float dZoom = Zoom; 
        Zoom += 0.01f * delta.y * Zoom;

        if (Zoom < 0.02f)
            Zoom = dZoom;

        dZoom -= Zoom;
        Render::PointF p = AdjustToViewPort(MouseDownPos);
		Render::Matrix2F m;
        m.AppendScaling(ZoomStart);
        m.AppendTranslation(MoveStart.x, MoveStart.y);

        p = m.TransformByInverse(p);

        Move.x += dZoom * p.x;
        Move.y += dZoom * p.y;

        UpdateUserMatrix();
        return;
    }

    if (MouseTracking == Moving) 
    {
        Move.x -= delta.x;
        Move.y -= delta.y;

        UpdateUserMatrix();
        return;
    }

	Render::PointF p = AdjustToViewPort(mousePos);
    Render::Matrix2F m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    //}
    MouseEvent event(GFx::Event::MouseMove, 0, p.x, p.y, 0.0f, mouseIndex);
    pMovie->HandleEvent(event);

    
    // Mouse HitTest debugging logic
    /*
    Double xmouse = pMovie->GetVariableDouble("_root._xmouse");
    Double ymouse = pMovie->GetVariableDouble("_root._ymouse");

    int hitTest = pMovie->HitTest(p.x, p.y, Movie::HitTest_Shapes);
    //int hitTest = pMovie->HitTest(p.x, p.y, Movie::HitTest_ShapesNoInvisible);
    //int hitTest = pMovie->HitTest(p.x, p.y, Movie::HitTest_Bounds);
    //int hitTest = pMovie->HitTest(p.x, p.y, Movie::HitTest_ButtonEvents);

    pMovie->GetLog()->LogMessage("pMovie->HitTest: %d\n", hitTest);

    GFx::Value r;
    if (pMovie->Invoke("_root.hitTest", &r, "%f%f%d", xmouse, ymouse, 1))
        pMovie->GetLog()->LogMessage("_root.hitTest: %s\n", (int)r.ToString().ToCStr());
    */
}

void FxPlayerAppBase::OnTouchBegin(unsigned, unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary) 
{
	SF_UNUSED4(id, pos, contact, primary);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;

    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);

    Render::PointF pp((float)contact.x, (float)contact.y);
    pp = m.TransformByInverse(pp);

    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    TouchEvent event(GFx::Event::TouchBegin, id, p.x, p.y, pp.x, pp.y, primary);
    pMovie->HandleEvent(event);

    if (pGestureManager)
        pGestureManager->ProcessDown(id, pos, p);
#endif
}

void FxPlayerAppBase::OnTouchEnd(unsigned, unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary) 
{
	SF_UNUSED4(id, pos, contact, primary);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;

    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);

    Render::PointF pp((float)contact.x, (float)contact.y);
    pp = m.TransformByInverse(pp);

    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    TouchEvent event(GFx::Event::TouchEnd, id, p.x, p.y, pp.x, pp.y, primary);
    pMovie->HandleEvent(event);

    if (pGestureManager)
        pGestureManager->ProcessUp(id, pos, p);
#endif
}

void FxPlayerAppBase::OnTouchMove(unsigned, unsigned id, const Point<int>& pos, const Point<int>& contact, bool primary) 
{
	SF_UNUSED4(id, pos, contact, primary);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;

    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);

    Render::PointF pp((float)contact.x, (float)contact.y);
    pp = m.TransformByInverse(pp);

    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    TouchEvent event(GFx::Event::TouchMove, id, p.x, p.y, pp.x, pp.y, primary);
    pMovie->HandleEvent(event);

    if (pGestureManager)
        pGestureManager->ProcessMove(id, pos, p);
#endif
}

void FxPlayerAppBase::OnGestureBegin(unsigned, UInt32 gestureMask, const Point<int>& pos, 
                                          const PointF& translationDelta,
                                          const PointF& scaleDelta,
                                          float rotationDelta)
{
	SF_UNUSED5(gestureMask, pos, translationDelta, scaleDelta, rotationDelta);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;

    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);

    Render::PointF pp = m.TransformByInverse(translationDelta);

	m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    GestureEvent event(GFx::Event::GestureBegin, gestureMask, p.x, p.y, pp.x, pp.y, 
        scaleDelta.x, scaleDelta.y, rotationDelta);
    pMovie->HandleEvent(event);
#endif
}

void FxPlayerAppBase::OnGesture(unsigned, UInt32 gestureMask, const Point<int>& pos, 
                                     const PointF& translationDelta,
                                     const PointF& scaleDelta,
                                     float rotationDelta)
{
	SF_UNUSED5(gestureMask, pos, translationDelta, scaleDelta, rotationDelta);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;
	//printf("!!! %d %d    %f %f\n", x,y,translationDeltaX,translationDeltaY);
    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);

	Render::PointF pp = m.TransformByInverse(translationDelta);

	m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);
	//printf("!!! %f %f    %f %f\n", p.x,p.y,pp.x,pp.y);

    GestureEvent event(GFx::Event::Gesture, gestureMask, p.x, p.y, pp.x, pp.y, 
        scaleDelta.x, scaleDelta.y, rotationDelta);
    pMovie->HandleEvent(event);
#endif
}

void FxPlayerAppBase::OnGestureEnd(unsigned, UInt32 gestureMask, const Point<int>& pos)
{
	SF_UNUSED2(gestureMask, pos);
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
    if (!pMovie)
        return;

    Render::PointF p = AdjustToViewPort(pos);

    Render::Matrix2F m;
    m.AppendScaling(Zoom);
    m.AppendTranslation(Move.x, Move.y);
    p = m.TransformByInverse(p);

    GestureEvent event(GFx::Event::GestureEnd, gestureMask, p.x, p.y);
    pMovie->HandleEvent(event);
#endif
}

void FxPlayerAppBase::OnUpdateCliboard(const wchar_t* text) 
{
    Ptr<TextClipboard> pclipBoard = mLoader.GetTextClipboard();
    if (pclipBoard)
        pclipBoard->SetText(text);
}


void FxPlayerAppBase::OnFocus(bool set, KeyModifiers mods)
{
    if (pMovie)
    {
        if (set)
        {
            // need to update toggled keys when focus is being transferred to
            // the movie's windows.
            pMovie->HandleEvent(SetFocusEvent(mods));
        }
        else
        {
            pMovie->HandleEvent(GFx::Event::KillFocus);
        }
    }
}

void FxPlayerAppBase::OnPause(bool paused)
{
    // Note that toggling play state through pMovie->SetPlayState would only pause root clip,
    // not children. So instead we just set the global variable above which prevents Advance.
    // However, we may still need to save/restore state in frame.

    pMovie->ForceCollectGarbage();
    pMovie->SetPause(paused);

    if (paused)
        PausedState = pMovie->GetPlayState();
    else
        pMovie->SetPlayState(PausedState);
}

void FxPlayerAppBase::OnObjectsReport()
{
    pMovie->ForceCollectGarbage();
    pMovie->PrintObjectsReport(Movie::Report_ShortFileNames | 
                               //Movie::Report_SuppressOverallStats | 
                               Movie::Report_AddressesForAnonymObjsOnly |
                               Movie::Report_NoCircularReferences);
}

Render::PointF FxPlayerAppBase::AdjustToViewPort(const Point<int>& pos)
{
    Size<unsigned> szRemainder = GetViewSize() - MViewSize;
	return Render::PointF (static_cast<float>(pos.x - (int)szRemainder.Width/2), 
						   static_cast<float>(pos.y - (int)szRemainder.Height/2));  	
}

// Scales coordinates in MovieDef space into the Movie's viewport space.
Render::Point<int> FxPlayerAppBase::AdjustMovieDefToViewPort(const Point<int>& pos)
{
    if ( !pMovie || !pMovieDef )
        return pos;

    Point<int> pt = pos;
    GFx::Viewport vp;
    pMovie->GetViewport(&vp);
    pt.x = (int)(pt.x * (vp.Width / pMovieDef->GetWidth()));
    pt.y = (int)(pt.y * (vp.Height / pMovieDef->GetHeight()));

    Size<unsigned> szRemainder = GetViewSize() - MViewSize;
    pt.x += szRemainder.Width/2;
    pt.y += szRemainder.Height/2;
    return pt;
}

void FxPlayerFSCallback::Callback(Movie* pmovie, const char* pcommand, const char* parg)
{
    Ptr<GFx::Log> plog = pmovie->GetLog();
    if (plog)
    {
        plog->LogMessage("FsCallback: '");
        plog->LogMessage("%s", pcommand);
        plog->LogMessage("' '");
        plog->LogMessage("%s", parg);
        plog->LogMessage("'\n");
    }

    App->HandleFsCommand(pcommand, parg);
}
