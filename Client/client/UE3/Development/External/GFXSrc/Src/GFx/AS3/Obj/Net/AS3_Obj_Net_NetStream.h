//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_NetStream.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_NetStream_H
#define INC_AS3_Obj_Net_NetStream_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#ifdef GFX_ENABLE_VIDEO
#include "GFx/AS3/AS3_MovieRoot.h"
#include "Video/AS3/AS3_VideoProviderNetStream.h"
#endif
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class SoundTransform;
    class Microphone;
    class Camera;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NetStream;
}

namespace InstanceTraits
{
    class NetStream;
}

namespace Classes
{
    class NetStream;
}

namespace Instances
{
    class NetStream : public Instances::EventDispatcher
    {
        friend class InstanceTraits::NetStream;
        
    public:
        typedef NetStream SelfType;
        typedef Classes::NetStream ClassType;
        typedef InstanceTraits::NetStream TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NetStream"; }
#endif
    protected:
        NetStream(InstanceTraits::Traits& t);

//##protect##"instance$methods"
#ifdef GFX_ENABLE_VIDEO
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
    public:
        ~NetStream();
        VideoProviderNetStream* GetVideoProvider() { return pVideoProvider; }

        class EventHandlers: public NetStreamInterface
        {
            Instances::NetStream* pNetStream;
        public:
            EventHandlers(Instances::NetStream* p) : pNetStream(p) { SF_ASSERT(pNetStream); }
            virtual void DispatchNetStatus(const String& code, const String& level);
            virtual void ExecuteOnMataData(GFx::Video::VideoPlayer::VideoInfo* pinfo);
            virtual void ExecuteOnCuePoint(GFx::Video::VideoPlayer::CuePoint* pcuepoint);
            virtual void ExecuteOnSubtitle(const String& subtitle);
        };
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bufferLengthGet, 
            mid_bufferTimeGet, 
            mid_bufferTimeSet, 
            mid_bytesLoadedGet, 
            mid_bytesTotalGet, 
            mid_checkPolicyFileGet, 
            mid_checkPolicyFileSet, 
            mid_clientGet, 
            mid_clientSet, 
            mid_currentFPSGet, 
            mid_liveDelayGet, 
            mid_objectEncodingGet, 
            mid_soundTransformGet, 
            mid_soundTransformSet, 
            mid_timeGet, 
            mid_attachAudio, 
            mid_attachCamera, 
            mid_close, 
            mid_pause, 
            mid_play, 
            mid_publish, 
            mid_receiveAudio, 
            mid_receiveVideo, 
            mid_receiveVideoFPS, 
            mid_resume, 
            mid_seek, 
            mid_send, 
            mid_setDRMAuthenticationCredentials, 
            mid_togglePause, 
            mid_loopGet, 
            mid_loopSet, 
            mid_currentFrameGet, 
            mid_audioTrackGet, 
            mid_audioTrackSet, 
            mid_subAudioTrackGet, 
            mid_subAudioTrackSet, 
            mid_voiceTrackGet, 
            mid_voiceTrackSet, 
            mid_subtitleTrackGet, 
            mid_subtitleTrackSet, 
            mid_subSoundTransformGet, 
            mid_subSoundTransformSet, 
            mid_reloadThresholdTimeSet, 
            mid_numberOfFramePoolsSet, 
            mid_openTimeoutSet, 
        };
        void bufferLengthGet(Value::Number& result);
        void bufferTimeGet(Value::Number& result);
        void bufferTimeSet(Value& result, Value::Number value);
        void bytesLoadedGet(UInt32& result);
        void bytesTotalGet(UInt32& result);
        void checkPolicyFileGet(bool& result);
        void checkPolicyFileSet(Value& result, bool value);
        void clientGet(Value& result);
        void clientSet(Value& result, const Value& value);
        void currentFPSGet(Value::Number& result);
        void liveDelayGet(Value::Number& result);
        void objectEncodingGet(UInt32& result);
        void soundTransformGet(Value& result);
        void soundTransformSet(Value& result, Instances::SoundTransform* value);
        void timeGet(Value::Number& result);
        void attachAudio(Value& result, Instances::Microphone* microphone);
        void attachCamera(Value& result, Instances::Camera* theCamera, SInt32 snapshotMilliseconds);
        void close(Value& result, bool flag);
        void pause(Value& result);
        void play(Value& result, unsigned argc, const Value* const argv);
        void publish(Value& result, const ASString& name, const ASString& type);
        void receiveAudio(Value& result, bool flag);
        void receiveVideo(Value& result, bool flag);
        void receiveVideoFPS(Value& result, Value::Number FPS);
        void resume(Value& result);
        void seek(Value& result, Value::Number offset);
        void send(Value& result, unsigned argc, const Value* const argv);
        void setDRMAuthenticationCredentials(Value& result, const ASString& userName, const ASString& password, const ASString& type);
        void togglePause(Value& result);
        void loopGet(bool& result);
        void loopSet(Value& result, bool flag);
        void currentFrameGet(Value::Number& result);
        void audioTrackGet(Value::Number& result);
        void audioTrackSet(Value& result, Value::Number track);
        void subAudioTrackGet(Value::Number& result);
        void subAudioTrackSet(Value& result, Value::Number track);
        void voiceTrackGet(Value::Number& result);
        void voiceTrackSet(Value& result, Value::Number track);
        void subtitleTrackGet(Value::Number& result);
        void subtitleTrackSet(Value& result, Value::Number track);
        void subSoundTransformGet(Value& result);
        void subSoundTransformSet(Value& result, Instances::SoundTransform* value);
        void reloadThresholdTimeSet(Value& result, Value::Number time);
        void numberOfFramePoolsSet(Value& result, Value::Number pools);
        void openTimeoutSet(Value& result, Value::Number time);

//##protect##"instance$data"
#ifdef GFX_ENABLE_VIDEO
        Ptr<VideoProviderNetStream>  pVideoProvider;
        Ptr<NetStreamInterface>      pEventHandlers;
        bool Paused;

        float    BufferTime;
        float    ReloadThresholdTime;
        unsigned NumberOfFramePools;
        float    OpenTimeout;

        bool     LoopFlag;
        int      AudioTrack;
        int      SubAudioTrack;
        int      VoiceTrack;
        int      SubtitleTrack;

        Value::Number SoundVolume;
        Value::Number SubSoundVolume;

        Value    OnMetaDataFunc;
        Value    OnCuePointFunc;
        Value    OnSubtitleFunc;
#endif
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NetStream : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NetStream"; }
#endif
    public:
        NetStream(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NetStream> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 45 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class NetStream : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NetStream"; }
#endif
    public:
        typedef Classes::NetStream ClassType;

    public:
        NetStream(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NetStream : public Class
    {
        friend class ClassTraits::NetStream;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NetStream"; }
#endif
    public:
        typedef NetStream SelfType;
        typedef NetStream ClassType;
        
    private:
        NetStream(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_resetDRMVouchers, 
        };
        void resetDRMVouchers(Value& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

