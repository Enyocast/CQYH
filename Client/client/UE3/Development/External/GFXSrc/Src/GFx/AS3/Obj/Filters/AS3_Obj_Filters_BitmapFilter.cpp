//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BitmapFilter.h"
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
typedef ThunkFunc0<Instances::BitmapFilter, Instances::BitmapFilter::mid_clone, Value> TFunc_Instances_BitmapFilter_clone;

template <> const TFunc_Instances_BitmapFilter_clone::TMethod TFunc_Instances_BitmapFilter_clone::Method = &Instances::BitmapFilter::clone;

namespace Instances
{
    BitmapFilter::BitmapFilter(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::BitmapFilter::BitmapFilter()$data"
      , FilterData(0)
//##protect##"instance::BitmapFilter::BitmapFilter()$data"
    {
//##protect##"instance::BitmapFilter::BitmapFilter()$code"
//##protect##"instance::BitmapFilter::BitmapFilter()$code"
    }

    void BitmapFilter::clone(Value& result)
    {
//##protect##"instance::BitmapFilter::clone()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::BitmapFilter::clone()");
//##protect##"instance::BitmapFilter::clone()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo BitmapFilter::ti[BitmapFilter::ThunkInfoNum] = {
        {TFunc_Instances_BitmapFilter_clone::Func, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

    BitmapFilter::BitmapFilter(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::BitmapFilter::BitmapFilter()"
//##protect##"InstanceTraits::BitmapFilter::BitmapFilter()"
        SetMemSize(sizeof(Instances::BitmapFilter));

    }

    Pickable<Instances::BitmapFilter> BitmapFilter::MakeInstance(Traits& t)
    {
        return Pickable<Instances::BitmapFilter>(new(t.Alloc()) Instances::BitmapFilter(t));
    }

    void BitmapFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    BitmapFilter::BitmapFilter(VM& vm)
    : Traits(vm, BitmapFilterCI)
    {
//##protect##"ClassTraits::BitmapFilter::BitmapFilter()"
//##protect##"ClassTraits::BitmapFilter::BitmapFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapFilter(vm, BitmapFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BitmapFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapFilterCI = {
    ClassInfo::CompileTime,
    "BitmapFilter", "flash.filters", &ObjectCI,
    ClassTraits::BitmapFilter::MakeClassTraits,
    0,
    0,
    InstanceTraits::BitmapFilter::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::BitmapFilter::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

