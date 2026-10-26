//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundChannel.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_SoundChannel.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Media_SoundTransform.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::SoundChannel, Instances::SoundChannel::mid_leftPeakGet, Value::Number> TFunc_Instances_SoundChannel_leftPeakGet;
typedef ThunkFunc0<Instances::SoundChannel, Instances::SoundChannel::mid_positionGet, Value::Number> TFunc_Instances_SoundChannel_positionGet;
typedef ThunkFunc0<Instances::SoundChannel, Instances::SoundChannel::mid_rightPeakGet, Value::Number> TFunc_Instances_SoundChannel_rightPeakGet;
typedef ThunkFunc0<Instances::SoundChannel, Instances::SoundChannel::mid_soundTransformGet, Value> TFunc_Instances_SoundChannel_soundTransformGet;
typedef ThunkFunc1<Instances::SoundChannel, Instances::SoundChannel::mid_soundTransformSet, Value, Instances::SoundTransform*> TFunc_Instances_SoundChannel_soundTransformSet;
typedef ThunkFunc0<Instances::SoundChannel, Instances::SoundChannel::mid_stop, Value> TFunc_Instances_SoundChannel_stop;

template <> const TFunc_Instances_SoundChannel_leftPeakGet::TMethod TFunc_Instances_SoundChannel_leftPeakGet::Method = &Instances::SoundChannel::leftPeakGet;
template <> const TFunc_Instances_SoundChannel_positionGet::TMethod TFunc_Instances_SoundChannel_positionGet::Method = &Instances::SoundChannel::positionGet;
template <> const TFunc_Instances_SoundChannel_rightPeakGet::TMethod TFunc_Instances_SoundChannel_rightPeakGet::Method = &Instances::SoundChannel::rightPeakGet;
template <> const TFunc_Instances_SoundChannel_soundTransformGet::TMethod TFunc_Instances_SoundChannel_soundTransformGet::Method = &Instances::SoundChannel::soundTransformGet;
template <> const TFunc_Instances_SoundChannel_soundTransformSet::TMethod TFunc_Instances_SoundChannel_soundTransformSet::Method = &Instances::SoundChannel::soundTransformSet;
template <> const TFunc_Instances_SoundChannel_stop::TMethod TFunc_Instances_SoundChannel_stop::Method = &Instances::SoundChannel::stop;

namespace Instances
{
    SoundChannel::SoundChannel(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::SoundChannel::SoundChannel()$data"
//##protect##"instance::SoundChannel::SoundChannel()$data"
    {
//##protect##"instance::SoundChannel::SoundChannel()$code"
//##protect##"instance::SoundChannel::SoundChannel()$code"
    }

    void SoundChannel::leftPeakGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::leftPeakGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::leftPeakGet()");
//##protect##"instance::SoundChannel::leftPeakGet()"
    }
    void SoundChannel::positionGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::positionGet()"
#ifdef GFX_ENABLE_SOUND
        float position = 0.0f;
        if (pSoundObject)
            position = pSoundObject->GetPosition();
        result = position;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::positionGet()");
#endif
//##protect##"instance::SoundChannel::positionGet()"
    }
    void SoundChannel::rightPeakGet(Value::Number& result)
    {
//##protect##"instance::SoundChannel::rightPeakGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::rightPeakGet()");
//##protect##"instance::SoundChannel::rightPeakGet()"
    }
    void SoundChannel::soundTransformGet(Value& result)
    {
//##protect##"instance::SoundChannel::soundTransformGet()"
#ifdef GFX_ENABLE_SOUND
        Value v;
        GetVM().Construct("flash.media.SoundTransform", v);
        SPtr<Instances::SoundTransform> trans = static_cast<Instances::SoundTransform*>(v.GetObject());
        if (pSoundObject)
        {
            Value r;
            trans->volumeSet(r, pSoundObject->GetVolume() / 100);
            trans->panSet(r, pSoundObject->GetPan() / 100);
        }
        result = trans;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::soundTransformGet()");
#endif
//##protect##"instance::SoundChannel::soundTransformGet()"
    }
    void SoundChannel::soundTransformSet(Value& result, Instances::SoundTransform* value)
    {
//##protect##"instance::SoundChannel::soundTransformSet()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
        {
            int volume = (SInt32)(value->Volume * 100);
            pSoundObject->SetVolume(volume);
            int pan = (SInt32)(value->Pan * 100);
            pSoundObject->SetPan(pan);
        }
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundChannel::soundTransformSet()");
#endif
//##protect##"instance::SoundChannel::soundTransformSet()"
    }
    void SoundChannel::stop(Value& result)
    {
//##protect##"instance::SoundChannel::stop()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        if (pSoundObject)
            pSoundObject->Stop();
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundChannel::stop()");
#endif
//##protect##"instance::SoundChannel::stop()"
    }

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    void SoundChannel::DispatchEventSoundComplete()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString eventType = asvm.GetStringManager().CreateConstString("soundComplete");
        SPtr<Event> eventObj = CreateEventObject(eventType);
        eventObj->Target = this;
        DispatchSingleEvent(eventObj, false);
    }
#endif
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo SoundChannel::ti[SoundChannel::ThunkInfoNum] = {
        {TFunc_Instances_SoundChannel_leftPeakGet::Func, &NumberCI, "leftPeak", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_positionGet::Func, &NumberCI, "position", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_rightPeakGet::Func, &NumberCI, "rightPeak", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_soundTransformGet::Func, &SoundTransformCI, "soundTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundChannel_soundTransformSet::Func, NULL, "soundTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundChannel_stop::Func, NULL, "stop", NULL, CT_Method, 0, 0},
    };

    SoundChannel::SoundChannel(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SoundChannel::SoundChannel()"
//##protect##"InstanceTraits::SoundChannel::SoundChannel()"
        SetMemSize(sizeof(Instances::SoundChannel));

    }

    Pickable<Instances::SoundChannel> SoundChannel::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SoundChannel>(new(t.Alloc()) Instances::SoundChannel(t));
    }

    void SoundChannel::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    SoundChannel::SoundChannel(VM& vm)
    : Traits(vm, SoundChannelCI)
    {
//##protect##"ClassTraits::SoundChannel::SoundChannel()"
//##protect##"ClassTraits::SoundChannel::SoundChannel()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SoundChannel(vm, SoundChannelCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SoundChannel::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SoundChannel(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SoundChannelCI = {
    ClassInfo::CompileTime,
    "SoundChannel", "flash.media", &EventDispatcherCI,
    ClassTraits::SoundChannel::MakeClassTraits,
    0,
    0,
    InstanceTraits::SoundChannel::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::SoundChannel::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

