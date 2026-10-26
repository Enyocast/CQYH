//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_NetStream.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_NetStream.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Media/AS3_Obj_Media_SoundTransform.h"
#include "../Media/AS3_Obj_Media_Microphone.h"
#include "../Media/AS3_Obj_Media_Camera.h"
#include "../Net/AS3_Obj_Net_URLRequest.h"
#include "../Events/AS3_Obj_Events_NetStatusEvent.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::NetStream, Instances::NetStream::mid_attachCamera, 1, SInt32>(AS3::StringManager&)
    {
        return -1;
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::NetStream, Instances::NetStream::mid_publish, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::NetStream, Instances::NetStream::mid_publish, 1, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

} // namespace Impl
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_bufferLengthGet, Value::Number> TFunc_Instances_NetStream_bufferLengthGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_bufferTimeGet, Value::Number> TFunc_Instances_NetStream_bufferTimeGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_bufferTimeSet, Value, Value::Number> TFunc_Instances_NetStream_bufferTimeSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_bytesLoadedGet, UInt32> TFunc_Instances_NetStream_bytesLoadedGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_bytesTotalGet, UInt32> TFunc_Instances_NetStream_bytesTotalGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_checkPolicyFileGet, bool> TFunc_Instances_NetStream_checkPolicyFileGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_checkPolicyFileSet, Value, bool> TFunc_Instances_NetStream_checkPolicyFileSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_clientGet, Value> TFunc_Instances_NetStream_clientGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_clientSet, Value, const Value&> TFunc_Instances_NetStream_clientSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_currentFPSGet, Value::Number> TFunc_Instances_NetStream_currentFPSGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_liveDelayGet, Value::Number> TFunc_Instances_NetStream_liveDelayGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_objectEncodingGet, UInt32> TFunc_Instances_NetStream_objectEncodingGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_soundTransformGet, Value> TFunc_Instances_NetStream_soundTransformGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_soundTransformSet, Value, Instances::SoundTransform*> TFunc_Instances_NetStream_soundTransformSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_timeGet, Value::Number> TFunc_Instances_NetStream_timeGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_attachAudio, Value, Instances::Microphone*> TFunc_Instances_NetStream_attachAudio;
typedef ThunkFunc2<Instances::NetStream, Instances::NetStream::mid_attachCamera, Value, Instances::Camera*, SInt32> TFunc_Instances_NetStream_attachCamera;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_close, Value, bool> TFunc_Instances_NetStream_close;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_pause, Value> TFunc_Instances_NetStream_pause;
typedef ThunkFunc2<Instances::NetStream, Instances::NetStream::mid_play, Value, unsigned, const Value*> TFunc_Instances_NetStream_play;
typedef ThunkFunc2<Instances::NetStream, Instances::NetStream::mid_publish, Value, const ASString&, const ASString&> TFunc_Instances_NetStream_publish;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_receiveAudio, Value, bool> TFunc_Instances_NetStream_receiveAudio;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_receiveVideo, Value, bool> TFunc_Instances_NetStream_receiveVideo;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_receiveVideoFPS, Value, Value::Number> TFunc_Instances_NetStream_receiveVideoFPS;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_resume, Value> TFunc_Instances_NetStream_resume;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_seek, Value, Value::Number> TFunc_Instances_NetStream_seek;
typedef ThunkFunc2<Instances::NetStream, Instances::NetStream::mid_send, Value, unsigned, const Value*> TFunc_Instances_NetStream_send;
typedef ThunkFunc3<Instances::NetStream, Instances::NetStream::mid_setDRMAuthenticationCredentials, Value, const ASString&, const ASString&, const ASString&> TFunc_Instances_NetStream_setDRMAuthenticationCredentials;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_togglePause, Value> TFunc_Instances_NetStream_togglePause;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_loopGet, bool> TFunc_Instances_NetStream_loopGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_loopSet, Value, bool> TFunc_Instances_NetStream_loopSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_currentFrameGet, Value::Number> TFunc_Instances_NetStream_currentFrameGet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_audioTrackGet, Value::Number> TFunc_Instances_NetStream_audioTrackGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_audioTrackSet, Value, Value::Number> TFunc_Instances_NetStream_audioTrackSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_subAudioTrackGet, Value::Number> TFunc_Instances_NetStream_subAudioTrackGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_subAudioTrackSet, Value, Value::Number> TFunc_Instances_NetStream_subAudioTrackSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_voiceTrackGet, Value::Number> TFunc_Instances_NetStream_voiceTrackGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_voiceTrackSet, Value, Value::Number> TFunc_Instances_NetStream_voiceTrackSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_subtitleTrackGet, Value::Number> TFunc_Instances_NetStream_subtitleTrackGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_subtitleTrackSet, Value, Value::Number> TFunc_Instances_NetStream_subtitleTrackSet;
typedef ThunkFunc0<Instances::NetStream, Instances::NetStream::mid_subSoundTransformGet, Value> TFunc_Instances_NetStream_subSoundTransformGet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_subSoundTransformSet, Value, Instances::SoundTransform*> TFunc_Instances_NetStream_subSoundTransformSet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_reloadThresholdTimeSet, Value, Value::Number> TFunc_Instances_NetStream_reloadThresholdTimeSet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_numberOfFramePoolsSet, Value, Value::Number> TFunc_Instances_NetStream_numberOfFramePoolsSet;
typedef ThunkFunc1<Instances::NetStream, Instances::NetStream::mid_openTimeoutSet, Value, Value::Number> TFunc_Instances_NetStream_openTimeoutSet;

template <> const TFunc_Instances_NetStream_bufferLengthGet::TMethod TFunc_Instances_NetStream_bufferLengthGet::Method = &Instances::NetStream::bufferLengthGet;
template <> const TFunc_Instances_NetStream_bufferTimeGet::TMethod TFunc_Instances_NetStream_bufferTimeGet::Method = &Instances::NetStream::bufferTimeGet;
template <> const TFunc_Instances_NetStream_bufferTimeSet::TMethod TFunc_Instances_NetStream_bufferTimeSet::Method = &Instances::NetStream::bufferTimeSet;
template <> const TFunc_Instances_NetStream_bytesLoadedGet::TMethod TFunc_Instances_NetStream_bytesLoadedGet::Method = &Instances::NetStream::bytesLoadedGet;
template <> const TFunc_Instances_NetStream_bytesTotalGet::TMethod TFunc_Instances_NetStream_bytesTotalGet::Method = &Instances::NetStream::bytesTotalGet;
template <> const TFunc_Instances_NetStream_checkPolicyFileGet::TMethod TFunc_Instances_NetStream_checkPolicyFileGet::Method = &Instances::NetStream::checkPolicyFileGet;
template <> const TFunc_Instances_NetStream_checkPolicyFileSet::TMethod TFunc_Instances_NetStream_checkPolicyFileSet::Method = &Instances::NetStream::checkPolicyFileSet;
template <> const TFunc_Instances_NetStream_clientGet::TMethod TFunc_Instances_NetStream_clientGet::Method = &Instances::NetStream::clientGet;
template <> const TFunc_Instances_NetStream_clientSet::TMethod TFunc_Instances_NetStream_clientSet::Method = &Instances::NetStream::clientSet;
template <> const TFunc_Instances_NetStream_currentFPSGet::TMethod TFunc_Instances_NetStream_currentFPSGet::Method = &Instances::NetStream::currentFPSGet;
template <> const TFunc_Instances_NetStream_liveDelayGet::TMethod TFunc_Instances_NetStream_liveDelayGet::Method = &Instances::NetStream::liveDelayGet;
template <> const TFunc_Instances_NetStream_objectEncodingGet::TMethod TFunc_Instances_NetStream_objectEncodingGet::Method = &Instances::NetStream::objectEncodingGet;
template <> const TFunc_Instances_NetStream_soundTransformGet::TMethod TFunc_Instances_NetStream_soundTransformGet::Method = &Instances::NetStream::soundTransformGet;
template <> const TFunc_Instances_NetStream_soundTransformSet::TMethod TFunc_Instances_NetStream_soundTransformSet::Method = &Instances::NetStream::soundTransformSet;
template <> const TFunc_Instances_NetStream_timeGet::TMethod TFunc_Instances_NetStream_timeGet::Method = &Instances::NetStream::timeGet;
template <> const TFunc_Instances_NetStream_attachAudio::TMethod TFunc_Instances_NetStream_attachAudio::Method = &Instances::NetStream::attachAudio;
template <> const TFunc_Instances_NetStream_attachCamera::TMethod TFunc_Instances_NetStream_attachCamera::Method = &Instances::NetStream::attachCamera;
template <> const TFunc_Instances_NetStream_close::TMethod TFunc_Instances_NetStream_close::Method = &Instances::NetStream::close;
template <> const TFunc_Instances_NetStream_pause::TMethod TFunc_Instances_NetStream_pause::Method = &Instances::NetStream::pause;
template <> const TFunc_Instances_NetStream_play::TMethod TFunc_Instances_NetStream_play::Method = &Instances::NetStream::play;
template <> const TFunc_Instances_NetStream_publish::TMethod TFunc_Instances_NetStream_publish::Method = &Instances::NetStream::publish;
template <> const TFunc_Instances_NetStream_receiveAudio::TMethod TFunc_Instances_NetStream_receiveAudio::Method = &Instances::NetStream::receiveAudio;
template <> const TFunc_Instances_NetStream_receiveVideo::TMethod TFunc_Instances_NetStream_receiveVideo::Method = &Instances::NetStream::receiveVideo;
template <> const TFunc_Instances_NetStream_receiveVideoFPS::TMethod TFunc_Instances_NetStream_receiveVideoFPS::Method = &Instances::NetStream::receiveVideoFPS;
template <> const TFunc_Instances_NetStream_resume::TMethod TFunc_Instances_NetStream_resume::Method = &Instances::NetStream::resume;
template <> const TFunc_Instances_NetStream_seek::TMethod TFunc_Instances_NetStream_seek::Method = &Instances::NetStream::seek;
template <> const TFunc_Instances_NetStream_send::TMethod TFunc_Instances_NetStream_send::Method = &Instances::NetStream::send;
template <> const TFunc_Instances_NetStream_setDRMAuthenticationCredentials::TMethod TFunc_Instances_NetStream_setDRMAuthenticationCredentials::Method = &Instances::NetStream::setDRMAuthenticationCredentials;
template <> const TFunc_Instances_NetStream_togglePause::TMethod TFunc_Instances_NetStream_togglePause::Method = &Instances::NetStream::togglePause;
template <> const TFunc_Instances_NetStream_loopGet::TMethod TFunc_Instances_NetStream_loopGet::Method = &Instances::NetStream::loopGet;
template <> const TFunc_Instances_NetStream_loopSet::TMethod TFunc_Instances_NetStream_loopSet::Method = &Instances::NetStream::loopSet;
template <> const TFunc_Instances_NetStream_currentFrameGet::TMethod TFunc_Instances_NetStream_currentFrameGet::Method = &Instances::NetStream::currentFrameGet;
template <> const TFunc_Instances_NetStream_audioTrackGet::TMethod TFunc_Instances_NetStream_audioTrackGet::Method = &Instances::NetStream::audioTrackGet;
template <> const TFunc_Instances_NetStream_audioTrackSet::TMethod TFunc_Instances_NetStream_audioTrackSet::Method = &Instances::NetStream::audioTrackSet;
template <> const TFunc_Instances_NetStream_subAudioTrackGet::TMethod TFunc_Instances_NetStream_subAudioTrackGet::Method = &Instances::NetStream::subAudioTrackGet;
template <> const TFunc_Instances_NetStream_subAudioTrackSet::TMethod TFunc_Instances_NetStream_subAudioTrackSet::Method = &Instances::NetStream::subAudioTrackSet;
template <> const TFunc_Instances_NetStream_voiceTrackGet::TMethod TFunc_Instances_NetStream_voiceTrackGet::Method = &Instances::NetStream::voiceTrackGet;
template <> const TFunc_Instances_NetStream_voiceTrackSet::TMethod TFunc_Instances_NetStream_voiceTrackSet::Method = &Instances::NetStream::voiceTrackSet;
template <> const TFunc_Instances_NetStream_subtitleTrackGet::TMethod TFunc_Instances_NetStream_subtitleTrackGet::Method = &Instances::NetStream::subtitleTrackGet;
template <> const TFunc_Instances_NetStream_subtitleTrackSet::TMethod TFunc_Instances_NetStream_subtitleTrackSet::Method = &Instances::NetStream::subtitleTrackSet;
template <> const TFunc_Instances_NetStream_subSoundTransformGet::TMethod TFunc_Instances_NetStream_subSoundTransformGet::Method = &Instances::NetStream::subSoundTransformGet;
template <> const TFunc_Instances_NetStream_subSoundTransformSet::TMethod TFunc_Instances_NetStream_subSoundTransformSet::Method = &Instances::NetStream::subSoundTransformSet;
template <> const TFunc_Instances_NetStream_reloadThresholdTimeSet::TMethod TFunc_Instances_NetStream_reloadThresholdTimeSet::Method = &Instances::NetStream::reloadThresholdTimeSet;
template <> const TFunc_Instances_NetStream_numberOfFramePoolsSet::TMethod TFunc_Instances_NetStream_numberOfFramePoolsSet::Method = &Instances::NetStream::numberOfFramePoolsSet;
template <> const TFunc_Instances_NetStream_openTimeoutSet::TMethod TFunc_Instances_NetStream_openTimeoutSet::Method = &Instances::NetStream::openTimeoutSet;

namespace Instances
{
    NetStream::NetStream(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::NetStream::NetStream()$data"
//##protect##"instance::NetStream::NetStream()$data"
    {
//##protect##"instance::NetStream::NetStream()$code"
#ifdef GFX_ENABLE_VIDEO
        Paused = false;

        LoopFlag = false;
        BufferTime = 0.1f;              // Flash AS3 default
        ReloadThresholdTime = 0.08f;    // 80% of the default buffering time
        NumberOfFramePools = 2;
        OpenTimeout = 5.0f;

        AudioTrack = 0;
        SubAudioTrack = 0;
        VoiceTrack = 0;
        SubtitleTrack = 0;

        SoundVolume = 1.0f;
        SubSoundVolume = 0.0f;
#endif
//##protect##"instance::NetStream::NetStream()$code"
    }

    void NetStream::bufferLengthGet(Value::Number& result)
    {
//##protect##"instance::NetStream::bufferLengthGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::bufferLengthGet()");
//##protect##"instance::NetStream::bufferLengthGet()"
    }
    void NetStream::bufferTimeGet(Value::Number& result)
    {
//##protect##"instance::NetStream::bufferTimeGet()"
#ifdef GFX_ENABLE_VIDEO
        result = BufferTime;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::bufferTimeGet()");
#endif
//##protect##"instance::NetStream::bufferTimeGet()"
    }
    void NetStream::bufferTimeSet(Value& result, Value::Number value)
    {
//##protect##"instance::NetStream::bufferTimeSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        BufferTime = (float)value;
        pVideoProvider->SetBufferTime(BufferTime);
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("NetStream::bufferTimeSet()");
#endif
//##protect##"instance::NetStream::bufferTimeSet()"
    }
    void NetStream::bytesLoadedGet(UInt32& result)
    {
//##protect##"instance::NetStream::bytesLoadedGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::bytesLoadedGet()");
//##protect##"instance::NetStream::bytesLoadedGet()"
    }
    void NetStream::bytesTotalGet(UInt32& result)
    {
//##protect##"instance::NetStream::bytesTotalGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::bytesTotalGet()");
//##protect##"instance::NetStream::bytesTotalGet()"
    }
    void NetStream::checkPolicyFileGet(bool& result)
    {
//##protect##"instance::NetStream::checkPolicyFileGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::checkPolicyFileGet()");
//##protect##"instance::NetStream::checkPolicyFileGet()"
    }
    void NetStream::checkPolicyFileSet(Value& result, bool value)
    {
//##protect##"instance::NetStream::checkPolicyFileSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("NetStream::checkPolicyFileSet()");
//##protect##"instance::NetStream::checkPolicyFileSet()"
    }
    void NetStream::clientGet(Value& result)
    {
//##protect##"instance::NetStream::clientGet()"
#ifdef GFX_ENABLE_VIDEO
        SPtr<Instances::Object> pobj = GetVM().MakeObject();
        StringManager& sm = GetVM().GetStringManager();
        pobj->AddDynamicSlotValuePair(sm.CreateString("onMetaData"), OnMetaDataFunc);
        pobj->AddDynamicSlotValuePair(sm.CreateString("onCuePoint"), OnCuePointFunc);
        pobj->AddDynamicSlotValuePair(sm.CreateString("onSubtitle"), OnSubtitleFunc);
        result = pobj;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::clientGet()");
#endif
//##protect##"instance::NetStream::clientGet()"
    }
    void NetStream::clientSet(Value& result, const Value& value)
    {
//##protect##"instance::NetStream::clientSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        Instances::Object* pobj = static_cast<Instances::Object*>(value.GetObject());
        StringManager& sm = GetVM().GetStringManager();

        Value prop;
        Multiname mnOnMetaData(GetVM().GetPublicNamespace(), sm.CreateString("onMetaData"));
        Multiname mnOnCuePoint(GetVM().GetPublicNamespace(), sm.CreateString("onCuePoint"));
        Multiname mnOnSubtitle(GetVM().GetPublicNamespace(), sm.CreateString("onSubtitle"));
        if (pobj->GetProperty(mnOnMetaData, prop))
            OnMetaDataFunc = prop;
        if (pobj->GetProperty(mnOnCuePoint, prop))
            OnCuePointFunc = prop;
        if (pobj->GetProperty(mnOnSubtitle, prop))
            OnSubtitleFunc = prop;
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("NetStream::clientSet()");
#endif
//##protect##"instance::NetStream::clientSet()"
    }
    void NetStream::currentFPSGet(Value::Number& result)
    {
//##protect##"instance::NetStream::currentFPSGet()"
#ifdef GFX_ENABLE_VIDEO
        const GFx::Video::VideoPlayer::VideoInfo& info = pVideoProvider->GetVideoInfo();
        float fps = 1.0f * info.FrameRate / 1000.f;
        result = fps;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::currentFPSGet()");
#endif
//##protect##"instance::NetStream::currentFPSGet()"
    }
    void NetStream::liveDelayGet(Value::Number& result)
    {
//##protect##"instance::NetStream::liveDelayGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::liveDelayGet()");
//##protect##"instance::NetStream::liveDelayGet()"
    }
    void NetStream::objectEncodingGet(UInt32& result)
    {
//##protect##"instance::NetStream::objectEncodingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::objectEncodingGet()");
//##protect##"instance::NetStream::objectEncodingGet()"
    }
    void NetStream::soundTransformGet(Value& result)
    {
//##protect##"instance::NetStream::soundTransformGet()"
#if defined(GFX_ENABLE_VIDEO) && defined(GFX_ENABLE_SOUND)
        Value v, r;
        GetVM().Construct("flash.media.SoundTransform", v);
        SPtr<Instances::SoundTransform> trans = static_cast<Instances::SoundTransform*>(v.GetObject());
        trans->volumeSet(r, SoundVolume);
        result = trans;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::soundTransformGet()");
#endif
//##protect##"instance::NetStream::soundTransformGet()"
    }
    void NetStream::soundTransformSet(Value& result, Instances::SoundTransform* value)
    {
//##protect##"instance::NetStream::soundTransformSet()"
#if defined(GFX_ENABLE_VIDEO) && defined(GFX_ENABLE_SOUND)
        SF_UNUSED(result);
        if (value)
        {
            value->volumeGet(SoundVolume);
            pVideoProvider->SetSoundVolume((SInt32)(SoundVolume * 100), (SInt32)(SubSoundVolume * 100));
        }
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("NetStream::soundTransformSet()");
#endif
//##protect##"instance::NetStream::soundTransformSet()"
    }
    void NetStream::timeGet(Value::Number& result)
    {
//##protect##"instance::NetStream::timeGet()"
#ifdef GFX_ENABLE_VIDEO
        float currentTime = 0.0f;
        UInt32 currentFrame = pVideoProvider->GetPosition();
        const GFx::Video::VideoPlayer::VideoInfo& info = pVideoProvider->GetVideoInfo();
        if (info.FrameRate > 0)
            currentTime = (1.0f * currentFrame) / (info.FrameRate / 1000.0f);
        result = currentTime;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::timeGet()");
#endif
//##protect##"instance::NetStream::timeGet()"
    }
    void NetStream::attachAudio(Value& result, Instances::Microphone* microphone)
    {
//##protect##"instance::NetStream::attachAudio()"
        SF_UNUSED2(result, microphone);
        WARN_NOT_IMPLEMENTED("NetStream::attachAudio()");
//##protect##"instance::NetStream::attachAudio()"
    }
    void NetStream::attachCamera(Value& result, Instances::Camera* theCamera, SInt32 snapshotMilliseconds)
    {
//##protect##"instance::NetStream::attachCamera()"
        SF_UNUSED3(result, theCamera, snapshotMilliseconds);
        WARN_NOT_IMPLEMENTED("NetStream::attachCamera()");
//##protect##"instance::NetStream::attachCamera()"
    }
    void NetStream::close(Value& result, bool flag)
    {
//##protect##"instance::NetStream::close()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        pVideoProvider->Stop();
        if (flag) // Force to release resources immediately after stop
            pVideoProvider->Close();
#else
        SF_UNUSED2(result, flag);
        WARN_NOT_IMPLEMENTED("NetStream::close()");
#endif
//##protect##"instance::NetStream::close()"
    }
    void NetStream::pause(Value& result)
    {
//##protect##"instance::NetStream::pause()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        Paused = true;
        pVideoProvider->Pause(Paused);
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::pause()");
#endif
//##protect##"instance::NetStream::pause()"
    }
    void NetStream::play(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::NetStream::play()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        if (argc >= 1)
        {
            Value v(argv[0]);
            v.ToStringValue(GetVM().GetStringManager()).DoNotCheck();
            const char* url = v.AsString().ToCStr();
            ASVM& asvm = static_cast<ASVM&>(GetVM());

            Paused = false;
            pVideoProvider->OpenUrl(url, asvm);
#ifdef GFX_ENABLE_SOUND
            pVideoProvider->SetSoundVolume((SInt32)(SoundVolume * 100), (SInt32)(SubSoundVolume * 100));
#endif
        }
#else
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("NetStream::play()");
#endif
//##protect##"instance::NetStream::play()"
    }
    void NetStream::publish(Value& result, const ASString& name, const ASString& type)
    {
//##protect##"instance::NetStream::publish()"
        SF_UNUSED3(result, name, type);
        WARN_NOT_IMPLEMENTED("NetStream::publish()");
//##protect##"instance::NetStream::publish()"
    }
    void NetStream::receiveAudio(Value& result, bool flag)
    {
//##protect##"instance::NetStream::receiveAudio()"
        SF_UNUSED2(result, flag);
        WARN_NOT_IMPLEMENTED("NetStream::receiveAudio()");
//##protect##"instance::NetStream::receiveAudio()"
    }
    void NetStream::receiveVideo(Value& result, bool flag)
    {
//##protect##"instance::NetStream::receiveVideo()"
        SF_UNUSED2(result, flag);
        WARN_NOT_IMPLEMENTED("NetStream::receiveVideo()");
//##protect##"instance::NetStream::receiveVideo()"
    }
    void NetStream::receiveVideoFPS(Value& result, Value::Number FPS)
    {
//##protect##"instance::NetStream::receiveVideoFPS()"
        SF_UNUSED2(result, FPS);
        WARN_NOT_IMPLEMENTED("NetStream::receiveVideoFPS()");
//##protect##"instance::NetStream::receiveVideoFPS()"
    }
    void NetStream::resume(Value& result)
    {
//##protect##"instance::NetStream::resume()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        Paused = false;
        pVideoProvider->Pause(Paused);
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::resume()");
#endif
//##protect##"instance::NetStream::resume()"
    }
    void NetStream::seek(Value& result, Value::Number offset)
    {
//##protect##"instance::NetStream::seek()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        GFx::MovieImpl* proot = asvm.GetMovieImpl();
        pVideoProvider->Seek((float)offset, proot);
#else
        SF_UNUSED2(result, offset);
        WARN_NOT_IMPLEMENTED("NetStream::seek()");
#endif
//##protect##"instance::NetStream::seek()"
    }
    void NetStream::send(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::NetStream::send()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("NetStream::send()");
//##protect##"instance::NetStream::send()"
    }
    void NetStream::setDRMAuthenticationCredentials(Value& result, const ASString& userName, const ASString& password, const ASString& type)
    {
//##protect##"instance::NetStream::setDRMAuthenticationCredentials()"
        SF_UNUSED4(result, userName, password, type);
        WARN_NOT_IMPLEMENTED("NetStream::setDRMAuthenticationCredentials()");
//##protect##"instance::NetStream::setDRMAuthenticationCredentials()"
    }
    void NetStream::togglePause(Value& result)
    {
//##protect##"instance::NetStream::togglePause()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        Paused = !Paused;
        pVideoProvider->Pause(Paused);
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::togglePause()");
#endif
//##protect##"instance::NetStream::togglePause()"
    }
    void NetStream::loopGet(bool& result)
    {
//##protect##"instance::NetStream::loopGet()"
#ifdef GFX_ENABLE_VIDEO
        result = LoopFlag;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::loopGet()");
#endif
//##protect##"instance::NetStream::loopGet()"
    }
    void NetStream::loopSet(Value& result, bool flag)
    {
//##protect##"instance::NetStream::loopSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        LoopFlag = flag;
        pVideoProvider->SetLoopFlag(LoopFlag);
#else
        SF_UNUSED2(result, flag);
        WARN_NOT_IMPLEMENTED("instance::NetStream::loopSet()");
#endif
//##protect##"instance::NetStream::loopSet()"
    }
    void NetStream::currentFrameGet(Value::Number& result)
    {
//##protect##"instance::NetStream::currentFrameGet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        UInt32 currentFrame = pVideoProvider->GetPosition();
        result = 1.0f * (currentFrame + 1);
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::currentFrameGet()");
#endif
//##protect##"instance::NetStream::currentFrameGet()"
    }
    void NetStream::audioTrackGet(Value::Number& result)
    {
//##protect##"instance::NetStream::audioTrackGet()"
#ifdef GFX_ENABLE_VIDEO
        result = AudioTrack;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::audioTrackGet()");
#endif
//##protect##"instance::NetStream::audioTrackGet()"
    }
    void NetStream::audioTrackSet(Value& result, Value::Number track)
    {
//##protect##"instance::NetStream::audioTrackSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        AudioTrack = (SInt32)track;
        pVideoProvider->SetAudioTrack(AudioTrack);
#else
        SF_UNUSED2(result, track);
        WARN_NOT_IMPLEMENTED("instance::NetStream::audioTrackSet()");
#endif
//##protect##"instance::NetStream::audioTrackSet()"
    }
    void NetStream::subAudioTrackGet(Value::Number& result)
    {
//##protect##"instance::NetStream::subAudioTrackGet()"
#ifdef GFX_ENABLE_VIDEO
        result = SubAudioTrack;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::subAudioTrackGet()");
#endif
//##protect##"instance::NetStream::subAudioTrackGet()"
    }
    void NetStream::subAudioTrackSet(Value& result, Value::Number track)
    {
//##protect##"instance::NetStream::subAudioTrackSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        SubAudioTrack = (SInt32)track;
        pVideoProvider->SetSubAudioTrack(SubAudioTrack);
#else
        SF_UNUSED2(result, track);
        WARN_NOT_IMPLEMENTED("instance::NetStream::subAudioTrackSet()");
#endif
//##protect##"instance::NetStream::subAudioTrackSet()"
    }
    void NetStream::voiceTrackGet(Value::Number& result)
    {
//##protect##"instance::NetStream::voiceTrackGet()"
#ifdef GFX_ENABLE_VIDEO
        result = VoiceTrack;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::voiceTrackGet()");
#endif
//##protect##"instance::NetStream::voiceTrackGet()"
    }
    void NetStream::voiceTrackSet(Value& result, Value::Number track)
    {
//##protect##"instance::NetStream::voiceTrackSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        VoiceTrack = (SInt32)track;
        pVideoProvider->ReplaceCenterVoice((int)VoiceTrack);
#else
        SF_UNUSED2(result, track);
        WARN_NOT_IMPLEMENTED("instance::NetStream::voiceTrackSet()");
#endif
//##protect##"instance::NetStream::voiceTrackSet()"
    }
    void NetStream::subtitleTrackGet(Value::Number& result)
    {
//##protect##"instance::NetStream::subtitleTrackGet()"
#ifdef GFX_ENABLE_VIDEO
        result = SubtitleTrack;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetStream::subtitleTrackGet()");
#endif
//##protect##"instance::NetStream::subtitleTrackGet()"
    }
    void NetStream::subtitleTrackSet(Value& result, Value::Number track)
    {
//##protect##"instance::NetStream::subtitleTrackSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        SubtitleTrack = (SInt32)track;
        SubtitleTrack--;
        if (!OnSubtitleFunc.IsNullOrUndefined())
            pVideoProvider->SetSubtitleChannel(SubtitleTrack);
#else
        SF_UNUSED2(result, track);
        WARN_NOT_IMPLEMENTED("instance::NetStream::subtitleTrackSet()");
#endif
//##protect##"instance::NetStream::subtitleTrackSet()"
    }
    void NetStream::subSoundTransformGet(Value& result)
    {
//##protect##"instance::NetStream::subSoundTransformGet()"
#if defined(GFX_ENABLE_VIDEO) && defined(GFX_ENABLE_SOUND)
        Value v, r;
        GetVM().Construct("flash.media.SoundTransform", v);
        SPtr<Instances::SoundTransform> trans = static_cast<Instances::SoundTransform*>(v.GetObject());
        trans->volumeSet(r, SubSoundVolume);
        result = trans;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("NetStream::soundTransformGet()");
#endif
//##protect##"instance::NetStream::subSoundTransformGet()"
    }
    void NetStream::subSoundTransformSet(Value& result, Instances::SoundTransform* value)
    {
//##protect##"instance::NetStream::subSoundTransformSet()"
#if defined(GFX_ENABLE_VIDEO) && defined(GFX_ENABLE_SOUND)
        SF_UNUSED(result);
        if (value)
        {
            value->volumeGet(SubSoundVolume);
            pVideoProvider->SetSoundVolume((SInt32)(SoundVolume * 100), (SInt32)(SubSoundVolume * 100));
        }
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("NetStream::soundTransformSet()");
#endif
//##protect##"instance::NetStream::subSoundTransformSet()"
    }
    void NetStream::reloadThresholdTimeSet(Value& result, Value::Number time)
    {
//##protect##"instance::NetStream::reloadThresholdTimeSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        ReloadThresholdTime = (float)time;
        pVideoProvider->SetReloadThresholdTime(ReloadThresholdTime);
#else
        SF_UNUSED2(result, time);
        WARN_NOT_IMPLEMENTED("instance::NetStream::reloadThresholdTimeSet()");
#endif
//##protect##"instance::NetStream::reloadThresholdTimeSet()"
    }
    void NetStream::numberOfFramePoolsSet(Value& result, Value::Number pools)
    {
//##protect##"instance::NetStream::numberOfFramePoolsSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        NumberOfFramePools = (SInt32)pools;
        pVideoProvider->SetNumberOfFramePools(NumberOfFramePools);
#else
        SF_UNUSED2(result, pools);
        WARN_NOT_IMPLEMENTED("instance::NetStream::numberOfFramePoolsSet()");
#endif
//##protect##"instance::NetStream::numberOfFramePoolsSet()"
    }
    void NetStream::openTimeoutSet(Value& result, Value::Number time)
    {
//##protect##"instance::NetStream::openTimeoutSet()"
#ifdef GFX_ENABLE_VIDEO
        SF_UNUSED(result);
        OpenTimeout = (float)time;
        pVideoProvider->SetOpenURLTimeout(OpenTimeout);
#else
        SF_UNUSED2(result, time);
        WARN_NOT_IMPLEMENTED("instance::NetStream::openTimeoutSet()");
#endif
//##protect##"instance::NetStream::openTimeoutSet()"
    }

//##protect##"instance$methods"
#ifdef GFX_ENABLE_VIDEO
    void NetStream::AS3Constructor(unsigned argc, const Value* argv)
    {
        SF_UNUSED2(argc, argv);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        pEventHandlers = *SF_HEAP_NEW(asvm.GetMovieImpl()->GetHeap()) EventHandlers(this);
        pVideoProvider = *SF_HEAP_NEW(asvm.GetMovieImpl()->GetHeap()) VideoProviderNetStream(pEventHandlers);
        SF_ASSERT(pVideoProvider);
    }

    void NetStream::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        EventDispatcher::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC(prcc, OnMetaDataFunc, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, OnCuePointFunc, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, OnSubtitleFunc, op SF_DEBUG_ARG(*this));
    }

    NetStream::~NetStream()
    {
        pVideoProvider->NotifyNetStreamRemoved();
        pVideoProvider->Stop();
    }

    void NetStream::EventHandlers::DispatchNetStatus(const String& code, const String& level)
    {
        StringManager& sm = pNetStream->GetVM().GetStringManager();
        SPtr<NetStatusEvent> eventObj = pNetStream->CreateNetStatusEvent(sm.CreateString(code), sm.CreateString(level));
        eventObj->Target = pNetStream;
        pNetStream->DispatchSingleEvent(eventObj, false);
    }

    void NetStream::EventHandlers::ExecuteOnMataData(GFx::Video::VideoPlayer::VideoInfo* pinfo)
    {
        SF_ASSERT(pinfo);
        if (pNetStream->OnMetaDataFunc.IsNullOrUndefined())
            return;

        StringManager& sm = pNetStream->GetVM().GetStringManager();

        SPtr<Instances::Object> pobj = pNetStream->GetVM().MakeObject();
        pobj->AddDynamicSlotValuePair(sm.CreateString("duration"), Value(pinfo->TotalFrames * 1000.f / pinfo->FrameRate));
        pobj->AddDynamicSlotValuePair(sm.CreateString("width"),    Value(SInt32(pinfo->Width)));
        pobj->AddDynamicSlotValuePair(sm.CreateString("height"),   Value(SInt32(pinfo->Height)));
        pobj->AddDynamicSlotValuePair(sm.CreateString("totalFrames"), Value(pinfo->TotalFrames));
        pobj->AddDynamicSlotValuePair(sm.CreateString("frameRate"),   Value(pinfo->FrameRate/1000.f));
        pobj->AddDynamicSlotValuePair(sm.CreateString("subtitleTracksCount"), Value(SInt32(pinfo->SubtitleChannelsNumber)));
        pobj->AddDynamicSlotValuePair(sm.CreateString("audioTracksCount"),    Value(pinfo->AudioTracks.GetSize()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("cuePointsCount"),      Value(pinfo->CuePoints.GetSize()));
        // TODO: Also we can send arrays of "audioTracks" and "cuePoints" from here
        //       to ActionScript, if it would be necessary.

        Value result;
        Value argv[1] = { Value(pobj) };
        pNetStream->GetVM().ExecuteUnsafe(pNetStream->OnMetaDataFunc, Value::GetUndefined(), result, 1, argv);
        if (pNetStream->GetVM().IsException())
            pNetStream->GetVM().OutputAndIgnoreException();
    }

    void NetStream::EventHandlers::ExecuteOnCuePoint(GFx::Video::VideoPlayer::CuePoint* pcuepoint)
    {
        SF_ASSERT(pcuepoint);
        if (pNetStream->OnCuePointFunc.IsNullOrUndefined())
            return;

        StringManager& sm = pNetStream->GetVM().GetStringManager();

        SPtr<Instances::Object> pobj = pNetStream->GetVM().MakeObject();
        pobj->AddDynamicSlotValuePair(sm.CreateString("name"), Value(sm.CreateString(pcuepoint->Name)));
        pobj->AddDynamicSlotValuePair(sm.CreateString("time"), Value(pcuepoint->Time * 1.0f / 1000.0f));
        pobj->AddDynamicSlotValuePair(sm.CreateString("type"), Value(pcuepoint->Type ==
            GFx::Video::VideoPlayer::NavigationCuePoint ? sm.CreateString("navigation") :
                                                          sm.CreateString("event")));
        pobj->AddDynamicSlotValuePair(sm.CreateString("parameters"), Value(sm.CreateEmptyString()));

        if (pcuepoint->Params.GetSize() > 0)
        {
            SPtr<Instances::Object> pparamObj = pNetStream->GetVM().MakeObject();
            for(UPInt p = 0; p < pcuepoint->Params.GetSize(); p++)
            {
                pparamObj->AddDynamicSlotValuePair(sm.CreateString(pcuepoint->Params[p].Name),
                                             Value(sm.CreateString(pcuepoint->Params[p].Value)));
            }
            pobj->AddDynamicSlotValuePair(sm.CreateString("parameters"), Value(pparamObj));
        }

        Value result;
        Value argv[1] = { Value(pobj) };
        pNetStream->GetVM().ExecuteUnsafe(pNetStream->OnCuePointFunc, Value::GetUndefined(), result, 1, argv);
        if (pNetStream->GetVM().IsException())
            pNetStream->GetVM().OutputAndIgnoreException();
    }

    void NetStream::EventHandlers::ExecuteOnSubtitle(const String& subtitle)
    {
        if (pNetStream->OnSubtitleFunc.IsNullOrUndefined())
            return;

        Value result;
        StringManager& sm = pNetStream->GetVM().GetStringManager();
        Value argv[1] = { Value(sm.CreateString(subtitle)) };
        pNetStream->GetVM().ExecuteUnsafe(pNetStream->OnSubtitleFunc, Value::GetUndefined(), result, 1, argv);
        if (pNetStream->GetVM().IsException())
            pNetStream->GetVM().OutputAndIgnoreException();
    }
#endif
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NetStream::ti[NetStream::ThunkInfoNum] = {
        {TFunc_Instances_NetStream_bufferLengthGet::Func, &NumberCI, "bufferLength", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_bufferTimeGet::Func, &NumberCI, "bufferTime", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_bufferTimeSet::Func, NULL, "bufferTime", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_bytesLoadedGet::Func, &uintCI, "bytesLoaded", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_bytesTotalGet::Func, &uintCI, "bytesTotal", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_checkPolicyFileGet::Func, &BooleanCI, "checkPolicyFile", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_checkPolicyFileSet::Func, NULL, "checkPolicyFile", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_clientGet::Func, &ObjectCI, "client", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_clientSet::Func, NULL, "client", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_currentFPSGet::Func, &NumberCI, "currentFPS", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_liveDelayGet::Func, &NumberCI, "liveDelay", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_objectEncodingGet::Func, &uintCI, "objectEncoding", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_soundTransformGet::Func, &SoundTransformCI, "soundTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_soundTransformSet::Func, NULL, "soundTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_timeGet::Func, &NumberCI, "time", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_attachAudio::Func, NULL, "attachAudio", NULL, CT_Method, 1, 1},
        {TFunc_Instances_NetStream_attachCamera::Func, NULL, "attachCamera", NULL, CT_Method, 1, 2},
        {TFunc_Instances_NetStream_close::Func, NULL, "close", NULL, CT_Method, 0, 1},
        {TFunc_Instances_NetStream_pause::Func, NULL, "pause", NULL, CT_Method, 0, 0},
        {TFunc_Instances_NetStream_play::Func, NULL, "play", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_NetStream_publish::Func, NULL, "publish", NULL, CT_Method, 0, 2},
        {TFunc_Instances_NetStream_receiveAudio::Func, NULL, "receiveAudio", NULL, CT_Method, 1, 1},
        {TFunc_Instances_NetStream_receiveVideo::Func, NULL, "receiveVideo", NULL, CT_Method, 1, 1},
        {TFunc_Instances_NetStream_receiveVideoFPS::Func, NULL, "receiveVideoFPS", NULL, CT_Method, 1, 1},
        {TFunc_Instances_NetStream_resume::Func, NULL, "resume", NULL, CT_Method, 0, 0},
        {TFunc_Instances_NetStream_seek::Func, NULL, "seek", NULL, CT_Method, 1, 1},
        {TFunc_Instances_NetStream_send::Func, NULL, "send", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_NetStream_setDRMAuthenticationCredentials::Func, NULL, "setDRMAuthenticationCredentials", NULL, CT_Method, 3, 3},
        {TFunc_Instances_NetStream_togglePause::Func, NULL, "togglePause", NULL, CT_Method, 0, 0},
        {TFunc_Instances_NetStream_loopGet::Func, &BooleanCI, "loop", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_loopSet::Func, NULL, "loop", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_currentFrameGet::Func, &NumberCI, "currentFrame", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_audioTrackGet::Func, &NumberCI, "audioTrack", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_audioTrackSet::Func, NULL, "audioTrack", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_subAudioTrackGet::Func, &NumberCI, "subAudioTrack", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_subAudioTrackSet::Func, NULL, "subAudioTrack", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_voiceTrackGet::Func, &NumberCI, "voiceTrack", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_voiceTrackSet::Func, NULL, "voiceTrack", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_subtitleTrackGet::Func, &NumberCI, "subtitleTrack", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_subtitleTrackSet::Func, NULL, "subtitleTrack", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_subSoundTransformGet::Func, &SoundTransformCI, "subSoundTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetStream_subSoundTransformSet::Func, NULL, "subSoundTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_reloadThresholdTimeSet::Func, NULL, "reloadThresholdTime", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_numberOfFramePoolsSet::Func, NULL, "numberOfFramePools", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetStream_openTimeoutSet::Func, NULL, "openTimeout", NULL, CT_Set, 1, 1},
    };

    NetStream::NetStream(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NetStream::NetStream()"
//##protect##"InstanceTraits::NetStream::NetStream()"
        SetMemSize(sizeof(Instances::NetStream));

    }

    Pickable<Instances::NetStream> NetStream::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NetStream>(new(t.Alloc()) Instances::NetStream(t));
    }

    void NetStream::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    NetStream::NetStream(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::NetStream::NetStream()"
//##protect##"class_::NetStream::NetStream()"
    }
    void NetStream::resetDRMVouchers(Value& result)
    {
//##protect##"class_::NetStream::resetDRMVouchers()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::NetStream::resetDRMVouchers()");
//##protect##"class_::NetStream::resetDRMVouchers()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::NetStream, Classes::NetStream::mid_resetDRMVouchers, Value> TFunc_Classes_NetStream_resetDRMVouchers;

template <> const TFunc_Classes_NetStream_resetDRMVouchers::TMethod TFunc_Classes_NetStream_resetDRMVouchers::Method = &Classes::NetStream::resetDRMVouchers;

namespace ClassTraits
{
    const ThunkInfo NetStream::ti[NetStream::ThunkInfoNum] = {
        {TFunc_Classes_NetStream_resetDRMVouchers::Func, NULL, "resetDRMVouchers", NULL, CT_Method, 0, 0},
    };
    NetStream::NetStream(VM& vm)
    : Traits(vm, NetStreamCI)
    {
//##protect##"ClassTraits::NetStream::NetStream()"
//##protect##"ClassTraits::NetStream::NetStream()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NetStream(vm, NetStreamCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NetStream(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NetStream::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NetStream(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NetStreamCI = {
    ClassInfo::CompileTime,
    "NetStream", "flash.net", &EventDispatcherCI,
    ClassTraits::NetStream::MakeClassTraits,
    ClassTraits::NetStream::ThunkInfoNum,
    0,
    InstanceTraits::NetStream::ThunkInfoNum,
    0,
    ClassTraits::NetStream::ti,
    NULL,
    InstanceTraits::NetStream::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

