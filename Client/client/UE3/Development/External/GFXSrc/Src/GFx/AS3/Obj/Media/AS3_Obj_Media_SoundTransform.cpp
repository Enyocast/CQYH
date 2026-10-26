//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundTransform.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_SoundTransform.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_leftToLeftGet, Value::Number> TFunc_Instances_SoundTransform_leftToLeftGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_leftToLeftSet, Value, Value::Number> TFunc_Instances_SoundTransform_leftToLeftSet;
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_leftToRightGet, Value::Number> TFunc_Instances_SoundTransform_leftToRightGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_leftToRightSet, Value, Value::Number> TFunc_Instances_SoundTransform_leftToRightSet;
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_panGet, Value::Number> TFunc_Instances_SoundTransform_panGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_panSet, Value, Value::Number> TFunc_Instances_SoundTransform_panSet;
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_rightToLeftGet, Value::Number> TFunc_Instances_SoundTransform_rightToLeftGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_rightToLeftSet, Value, Value::Number> TFunc_Instances_SoundTransform_rightToLeftSet;
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_rightToRightGet, Value::Number> TFunc_Instances_SoundTransform_rightToRightGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_rightToRightSet, Value, Value::Number> TFunc_Instances_SoundTransform_rightToRightSet;
typedef ThunkFunc0<Instances::SoundTransform, Instances::SoundTransform::mid_volumeGet, Value::Number> TFunc_Instances_SoundTransform_volumeGet;
typedef ThunkFunc1<Instances::SoundTransform, Instances::SoundTransform::mid_volumeSet, Value, Value::Number> TFunc_Instances_SoundTransform_volumeSet;

template <> const TFunc_Instances_SoundTransform_leftToLeftGet::TMethod TFunc_Instances_SoundTransform_leftToLeftGet::Method = &Instances::SoundTransform::leftToLeftGet;
template <> const TFunc_Instances_SoundTransform_leftToLeftSet::TMethod TFunc_Instances_SoundTransform_leftToLeftSet::Method = &Instances::SoundTransform::leftToLeftSet;
template <> const TFunc_Instances_SoundTransform_leftToRightGet::TMethod TFunc_Instances_SoundTransform_leftToRightGet::Method = &Instances::SoundTransform::leftToRightGet;
template <> const TFunc_Instances_SoundTransform_leftToRightSet::TMethod TFunc_Instances_SoundTransform_leftToRightSet::Method = &Instances::SoundTransform::leftToRightSet;
template <> const TFunc_Instances_SoundTransform_panGet::TMethod TFunc_Instances_SoundTransform_panGet::Method = &Instances::SoundTransform::panGet;
template <> const TFunc_Instances_SoundTransform_panSet::TMethod TFunc_Instances_SoundTransform_panSet::Method = &Instances::SoundTransform::panSet;
template <> const TFunc_Instances_SoundTransform_rightToLeftGet::TMethod TFunc_Instances_SoundTransform_rightToLeftGet::Method = &Instances::SoundTransform::rightToLeftGet;
template <> const TFunc_Instances_SoundTransform_rightToLeftSet::TMethod TFunc_Instances_SoundTransform_rightToLeftSet::Method = &Instances::SoundTransform::rightToLeftSet;
template <> const TFunc_Instances_SoundTransform_rightToRightGet::TMethod TFunc_Instances_SoundTransform_rightToRightGet::Method = &Instances::SoundTransform::rightToRightGet;
template <> const TFunc_Instances_SoundTransform_rightToRightSet::TMethod TFunc_Instances_SoundTransform_rightToRightSet::Method = &Instances::SoundTransform::rightToRightSet;
template <> const TFunc_Instances_SoundTransform_volumeGet::TMethod TFunc_Instances_SoundTransform_volumeGet::Method = &Instances::SoundTransform::volumeGet;
template <> const TFunc_Instances_SoundTransform_volumeSet::TMethod TFunc_Instances_SoundTransform_volumeSet::Method = &Instances::SoundTransform::volumeSet;

namespace Instances
{
    SoundTransform::SoundTransform(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::SoundTransform::SoundTransform()$data"
//##protect##"instance::SoundTransform::SoundTransform()$data"
    {
//##protect##"instance::SoundTransform::SoundTransform()$code"
#ifdef GFX_ENABLE_SOUND
        Volume = 1;
        Pan = 0;
#endif
//##protect##"instance::SoundTransform::SoundTransform()$code"
    }

    void SoundTransform::leftToLeftGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::leftToLeftGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::leftToLeftGet()");
//##protect##"instance::SoundTransform::leftToLeftGet()"
    }
    void SoundTransform::leftToLeftSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::leftToLeftSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::leftToLeftSet()");
//##protect##"instance::SoundTransform::leftToLeftSet()"
    }
    void SoundTransform::leftToRightGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::leftToRightGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::leftToRightGet()");
//##protect##"instance::SoundTransform::leftToRightGet()"
    }
    void SoundTransform::leftToRightSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::leftToRightSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::leftToRightSet()");
//##protect##"instance::SoundTransform::leftToRightSet()"
    }
    void SoundTransform::panGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::panGet()"
#ifdef GFX_ENABLE_SOUND
        result = Pan;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::panGet()");
#endif
//##protect##"instance::SoundTransform::panGet()"
    }
    void SoundTransform::panSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::panSet()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        Pan = value;
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::panSet()");
#endif
//##protect##"instance::SoundTransform::panSet()"
    }
    void SoundTransform::rightToLeftGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::rightToLeftGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::rightToLeftGet()");
//##protect##"instance::SoundTransform::rightToLeftGet()"
    }
    void SoundTransform::rightToLeftSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::rightToLeftSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::rightToLeftSet()");
//##protect##"instance::SoundTransform::rightToLeftSet()"
    }
    void SoundTransform::rightToRightGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::rightToRightGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::rightToRightGet()");
//##protect##"instance::SoundTransform::rightToRightGet()"
    }
    void SoundTransform::rightToRightSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::rightToRightSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::rightToRightSet()");
//##protect##"instance::SoundTransform::rightToRightSet()"
    }
    void SoundTransform::volumeGet(Value::Number& result)
    {
//##protect##"instance::SoundTransform::volumeGet()"
#ifdef GFX_ENABLE_SOUND
        result = Volume;
#else
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SoundTransform::volumeGet()");
#endif
//##protect##"instance::SoundTransform::volumeGet()"
    }
    void SoundTransform::volumeSet(Value& result, Value::Number value)
    {
//##protect##"instance::SoundTransform::volumeSet()"
#ifdef GFX_ENABLE_SOUND
        SF_UNUSED(result);
        Volume = value;
#else
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SoundTransform::volumeSet()");
#endif
//##protect##"instance::SoundTransform::volumeSet()"
    }

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    void SoundTransform::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1)
        {
            argv[0].Convert2Number(Volume).DoNotCheck();
            if (argc >= 2)
                argv[1].Convert2Number(Pan).DoNotCheck();
        }
    }
#endif
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo SoundTransform::ti[SoundTransform::ThunkInfoNum] = {
        {TFunc_Instances_SoundTransform_leftToLeftGet::Func, &NumberCI, "leftToLeft", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_leftToLeftSet::Func, NULL, "leftToLeft", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundTransform_leftToRightGet::Func, &NumberCI, "leftToRight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_leftToRightSet::Func, NULL, "leftToRight", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundTransform_panGet::Func, &NumberCI, "pan", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_panSet::Func, NULL, "pan", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundTransform_rightToLeftGet::Func, &NumberCI, "rightToLeft", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_rightToLeftSet::Func, NULL, "rightToLeft", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundTransform_rightToRightGet::Func, &NumberCI, "rightToRight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_rightToRightSet::Func, NULL, "rightToRight", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SoundTransform_volumeGet::Func, &NumberCI, "volume", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SoundTransform_volumeSet::Func, NULL, "volume", NULL, CT_Set, 1, 1},
    };

    SoundTransform::SoundTransform(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SoundTransform::SoundTransform()"
//##protect##"InstanceTraits::SoundTransform::SoundTransform()"
        SetMemSize(sizeof(Instances::SoundTransform));

    }

    Pickable<Instances::SoundTransform> SoundTransform::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SoundTransform>(new(t.Alloc()) Instances::SoundTransform(t));
    }

    void SoundTransform::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    SoundTransform::SoundTransform(VM& vm)
    : Traits(vm, SoundTransformCI)
    {
//##protect##"ClassTraits::SoundTransform::SoundTransform()"
//##protect##"ClassTraits::SoundTransform::SoundTransform()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SoundTransform(vm, SoundTransformCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SoundTransform::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SoundTransform(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SoundTransformCI = {
    ClassInfo::CompileTime,
    "SoundTransform", "flash.media", &ObjectCI,
    ClassTraits::SoundTransform::MakeClassTraits,
    0,
    0,
    InstanceTraits::SoundTransform::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::SoundTransform::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

