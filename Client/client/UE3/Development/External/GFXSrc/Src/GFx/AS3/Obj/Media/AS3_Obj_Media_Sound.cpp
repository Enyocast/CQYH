//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Sound.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Sound.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Media_ID3Info.h"
#include "AS3_Obj_Media_SoundChannel.h"
#include "AS3_Obj_Media_SoundLoaderContext.h"
#include "AS3_Obj_Media_SoundTransform.h"
#include "../Net/AS3_Obj_Net_URLRequest.h"
#include "../Events/AS3_Obj_Events_IOErrorEvent.h"
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
    Value::Number GetMethodDefArg<Instances::Sound, Instances::Sound::mid_play, 0, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_bytesLoadedGet, UInt32> TFunc_Instances_Sound_bytesLoadedGet;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_bytesTotalGet, SInt32> TFunc_Instances_Sound_bytesTotalGet;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_id3Get, Value> TFunc_Instances_Sound_id3Get;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_isBufferingGet, bool> TFunc_Instances_Sound_isBufferingGet;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_lengthGet, Value::Number> TFunc_Instances_Sound_lengthGet;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_urlGet, ASString> TFunc_Instances_Sound_urlGet;
typedef ThunkFunc0<Instances::Sound, Instances::Sound::mid_close, Value> TFunc_Instances_Sound_close;
typedef ThunkFunc2<Instances::Sound, Instances::Sound::mid_load, Value, Instances::URLRequest*, Instances::SoundLoaderContext*> TFunc_Instances_Sound_load;
typedef ThunkFunc3<Instances::Sound, Instances::Sound::mid_play, Value, Value::Number, SInt32, Instances::SoundTransform*> TFunc_Instances_Sound_play;

template <> const TFunc_Instances_Sound_bytesLoadedGet::TMethod TFunc_Instances_Sound_bytesLoadedGet::Method = &Instances::Sound::bytesLoadedGet;
template <> const TFunc_Instances_Sound_bytesTotalGet::TMethod TFunc_Instances_Sound_bytesTotalGet::Method = &Instances::Sound::bytesTotalGet;
template <> const TFunc_Instances_Sound_id3Get::TMethod TFunc_Instances_Sound_id3Get::Method = &Instances::Sound::id3Get;
template <> const TFunc_Instances_Sound_isBufferingGet::TMethod TFunc_Instances_Sound_isBufferingGet::Method = &Instances::Sound::isBufferingGet;
template <> const TFunc_Instances_Sound_lengthGet::TMethod TFunc_Instances_Sound_lengthGet::Method = &Instances::Sound::lengthGet;
template <> const TFunc_Instances_Sound_urlGet::TMethod TFunc_Instances_Sound_urlGet::Method = &Instances::Sound::urlGet;
template <> const TFunc_Instances_Sound_close::TMethod TFunc_Instances_Sound_close::Method = &Instances::Sound::close;
template <> const TFunc_Instances_Sound_load::TMethod TFunc_Instances_Sound_load::Method = &Instances::Sound::load;
template <> const TFunc_Instances_Sound_play::TMethod TFunc_Instances_Sound_play::Method = &Instances::Sound::play;

namespace Instances
{
    Sound::Sound(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::Sound::Sound()$data"
//##protect##"instance::Sound::Sound()$data"
    {
//##protect##"instance::Sound::Sound()$code"
#ifdef GFX_ENABLE_SOUND
        Streaming = false;
#endif
//##protect##"instance::Sound::Sound()$code"
    }

    void Sound::bytesLoadedGet(UInt32& result)
    {
//##protect##"instance::Sound::bytesLoadedGet()"
#ifdef GFX_ENABLE_SOUND
        result = 0;
        if (pSoundObject)
            result = pSoundObject->GetBytesLoaded();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::bytesLoadedGet()");
#endif
//##protect##"instance::Sound::bytesLoadedGet()"
    }
    void Sound::bytesTotalGet(SInt32& result)
    {
//##protect##"instance::Sound::bytesTotalGet()"
#ifdef GFX_ENABLE_SOUND
        result = 0;
        if (pSoundObject)
            result = pSoundObject->GetBytesTotal();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::bytesTotalGet()");
#endif
//##protect##"instance::Sound::bytesTotalGet()"
    }
    void Sound::id3Get(Value& result)
    {
//##protect##"instance::Sound::id3Get()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::id3Get()");
//##protect##"instance::Sound::id3Get()"
    }
    void Sound::isBufferingGet(bool& result)
    {
//##protect##"instance::Sound::isBufferingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::isBufferingGet()");
//##protect##"instance::Sound::isBufferingGet()"
    }
    void Sound::lengthGet(Value::Number& result)
    {
//##protect##"instance::Sound::lengthGet()"
#ifdef GFX_ENABLE_SOUND
        float length = 0.0f;
        if (pSoundObject)
            length = pSoundObject->GetDuration();
        result = length;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::lengthGet()");
#endif
//##protect##"instance::Sound::lengthGet()"
    }
    void Sound::urlGet(ASString& result)
    {
//##protect##"instance::Sound::urlGet()"
#ifdef GFX_ENABLE_SOUND
        result = SoundURL;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::urlGet()");
#endif
//##protect##"instance::Sound::urlGet()"
    }
    void Sound::close(Value& result)
    {
//##protect##"instance::Sound::close()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            pSoundObject->Stop();
            pSoundObject = NULL;
        }
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sound::close()");
#endif
//##protect##"instance::Sound::close()"
    }
    void Sound::load(Value& result, Instances::URLRequest* stream, Instances::SoundLoaderContext* context)
    {
//##protect##"instance::Sound::load()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            if (stream)
                SoundURL = stream->GetUrl().ToCStr();
            if (context)
                Streaming = context->get_bufferTime() > 0 ? true : false;
            pSoundObject->LoadFile(SoundURL, Streaming);
        }
#else
        SF_UNUSED3(result, stream, context);
        WARN_NOT_IMPLEMENTED("Sound::load()");
#endif
//##protect##"instance::Sound::load()"
    }
    void Sound::play(Value& result, Value::Number startTime, SInt32 loops, Instances::SoundTransform* sndTransform)
    {
//##protect##"instance::Sound::play()"
#ifdef GFX_ENABLE_SOUND
        Value v, r;
        GetVM().Construct("flash.media.SoundChannel", v);
        SPtr<Instances::SoundChannel> pchan = static_cast<Instances::SoundChannel*>(v.GetObject());
        pchan->pSoundObject = pSoundObject;
        if (sndTransform)
            pchan->soundTransformSet(r, sndTransform);
        pChannel = pchan;

        if (pSoundObject)
            pSoundObject->Play((SInt32)startTime, loops);

        result = pchan;
#else
        SF_UNUSED4(result, startTime, loops, sndTransform);
        WARN_NOT_IMPLEMENTED("Sound::play()");
#endif
//##protect##"instance::Sound::play()"
    }

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    void Sound::AS3Constructor(unsigned argc, const Value* argv)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        pSoundObject = *SF_HEAP_NEW(asvm.GetMovieImpl()->GetHeap()) SoundObject(asvm, this);
        SF_ASSERT(pSoundObject);

        if (pSoundResource)
            pSoundObject->AttachResource(pSoundResource);

        if (argc >= 1 && asvm.IsOfType(argv[0], "flash.net.URLRequest"))
        {
            Instances::URLRequest* req = static_cast<Instances::URLRequest*>(argv[0].GetObject());
            Instances::SoundLoaderContext* cntx = NULL;
            if (argc >= 2 && asvm.IsOfType(argv[1], "flash.media.SoundLoaderContext"))
                cntx = static_cast<Instances::SoundLoaderContext*>(argv[0].GetObject());
            Value r;
            load(r, req, cntx);
        }
    }

    void Sound::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        EventDispatcher::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<Instances::SoundChannel, Mem_Stat>(prcc, pChannel, op SF_DEBUG_ARG(*this));
    }

    void Sound::InitInstance(bool extCall)
    {
        if (!extCall)
            CreateLibraryObject();
    }

    bool Sound::CreateLibraryObject()
    {
        if (!pSoundResource)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            MovieDefImpl* pdefImpl = asvm.GetResourceMovieDef(this);

            if (pdefImpl && GetTraits().IsUserDefined())
            {
                ASString className = GetInstanceTraits().GetQualifiedName(Traits::qnfWithDot);
                ResourceBindData resBindData;
                if (!asvm.GetMovieImpl()->FindExportedResource(pdefImpl, &resBindData, className.ToCStr()))
                    return false;

                if (resBindData.pResource)
                {
                    if (resBindData.pResource->GetResourceType() & Resource::RT_SoundSample)
                        pSoundResource = static_cast<SoundResource*>(resBindData.pResource.GetPtr());
                }
                return true;
            }
        }
        return false;
    }

    void Sound::DispatchEventOpen()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Event> eventObj = CreateEventObject(asvm.GetBuiltin(AS3Builtin_open));
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
    void Sound::DispatchEventComplete()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Event> eventObj = CreateEventObject(asvm.GetBuiltin(AS3Builtin_complete));
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
    void Sound::DispatchEventSoundComplete()
    {
        if (pChannel)
            pChannel->DispatchEventSoundComplete();
    }
    void Sound::DispatchEventIOError()
    {
        SPtr<IOErrorEvent> eventObj = CreateIOErrorEventObject("soundIOError");
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
#endif
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Sound::ti[Sound::ThunkInfoNum] = {
        {TFunc_Instances_Sound_bytesLoadedGet::Func, &uintCI, "bytesLoaded", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_bytesTotalGet::Func, &int_CI, "bytesTotal", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_id3Get::Func, &ID3InfoCI, "id3", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_isBufferingGet::Func, &BooleanCI, "isBuffering", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_lengthGet::Func, &NumberCI, "length", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_urlGet::Func, &StringCI, "url", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sound_close::Func, NULL, "close", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Sound_load::Func, NULL, "load", NULL, CT_Method, 1, 2},
        {TFunc_Instances_Sound_play::Func, NULL, "play", NULL, CT_Method, 0, 3},
    };

    Sound::Sound(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Sound::Sound()"
//##protect##"InstanceTraits::Sound::Sound()"
        SetMemSize(sizeof(Instances::Sound));

    }

    Pickable<Instances::Sound> Sound::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Sound>(new(t.Alloc()) Instances::Sound(t));
    }

    void Sound::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Sound::Sound(VM& vm)
    : Traits(vm, SoundCI)
    {
//##protect##"ClassTraits::Sound::Sound()"
//##protect##"ClassTraits::Sound::Sound()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Sound(vm, SoundCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Sound::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Sound(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SoundCI = {
    ClassInfo::CompileTime,
    "Sound", "flash.media", &EventDispatcherCI,
    ClassTraits::Sound::MakeClassTraits,
    0,
    0,
    InstanceTraits::Sound::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Sound::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

