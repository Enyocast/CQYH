//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BlurFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_BlurFilter.h"
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
typedef ThunkFunc0<Instances::BlurFilter, Instances::BlurFilter::mid_blurXGet, Value::Number> TFunc_Instances_BlurFilter_blurXGet;
typedef ThunkFunc1<Instances::BlurFilter, Instances::BlurFilter::mid_blurXSet, Value, Value::Number> TFunc_Instances_BlurFilter_blurXSet;
typedef ThunkFunc0<Instances::BlurFilter, Instances::BlurFilter::mid_blurYGet, Value::Number> TFunc_Instances_BlurFilter_blurYGet;
typedef ThunkFunc1<Instances::BlurFilter, Instances::BlurFilter::mid_blurYSet, Value, Value::Number> TFunc_Instances_BlurFilter_blurYSet;
typedef ThunkFunc0<Instances::BlurFilter, Instances::BlurFilter::mid_qualityGet, SInt32> TFunc_Instances_BlurFilter_qualityGet;
typedef ThunkFunc1<Instances::BlurFilter, Instances::BlurFilter::mid_qualitySet, Value, SInt32> TFunc_Instances_BlurFilter_qualitySet;
typedef ThunkFunc0<Instances::BlurFilter, Instances::BlurFilter::mid_clone, Value> TFunc_Instances_BlurFilter_clone;

template <> const TFunc_Instances_BlurFilter_blurXGet::TMethod TFunc_Instances_BlurFilter_blurXGet::Method = &Instances::BlurFilter::blurXGet;
template <> const TFunc_Instances_BlurFilter_blurXSet::TMethod TFunc_Instances_BlurFilter_blurXSet::Method = &Instances::BlurFilter::blurXSet;
template <> const TFunc_Instances_BlurFilter_blurYGet::TMethod TFunc_Instances_BlurFilter_blurYGet::Method = &Instances::BlurFilter::blurYGet;
template <> const TFunc_Instances_BlurFilter_blurYSet::TMethod TFunc_Instances_BlurFilter_blurYSet::Method = &Instances::BlurFilter::blurYSet;
template <> const TFunc_Instances_BlurFilter_qualityGet::TMethod TFunc_Instances_BlurFilter_qualityGet::Method = &Instances::BlurFilter::qualityGet;
template <> const TFunc_Instances_BlurFilter_qualitySet::TMethod TFunc_Instances_BlurFilter_qualitySet::Method = &Instances::BlurFilter::qualitySet;
template <> const TFunc_Instances_BlurFilter_clone::TMethod TFunc_Instances_BlurFilter_clone::Method = &Instances::BlurFilter::clone;

namespace Instances
{
    BlurFilter::BlurFilter(InstanceTraits::Traits& t)
    : Instances::BitmapFilter(t)
//##protect##"instance::BlurFilter::BlurFilter()$data"
//##protect##"instance::BlurFilter::BlurFilter()$data"
    {
//##protect##"instance::BlurFilter::BlurFilter()$code"
        FilterData = *SF_NEW Render::BlurFilter();
//##protect##"instance::BlurFilter::BlurFilter()$code"
    }

    void BlurFilter::blurXGet(Value::Number& result)
    {
//##protect##"instance::BlurFilter::blurXGet()"
        result = TwipsToPixels(GetBlurFilterData()->GetParams().BlurX);
//##protect##"instance::BlurFilter::blurXGet()"
    }
    void BlurFilter::blurXSet(Value& result, Value::Number value)
    {
//##protect##"instance::BlurFilter::blurXSet()"
        SF_UNUSED(result);
        GetBlurFilterData()->GetParams().BlurX = PixelsToTwips((float)value);
//##protect##"instance::BlurFilter::blurXSet()"
    }
    void BlurFilter::blurYGet(Value::Number& result)
    {
//##protect##"instance::BlurFilter::blurYGet()"
        result = TwipsToPixels(GetBlurFilterData()->GetParams().BlurY);
//##protect##"instance::BlurFilter::blurYGet()"
    }
    void BlurFilter::blurYSet(Value& result, Value::Number value)
    {
//##protect##"instance::BlurFilter::blurYSet()"
        SF_UNUSED(result);
        GetBlurFilterData()->GetParams().BlurY = PixelsToTwips((float)value);
//##protect##"instance::BlurFilter::blurYSet()"
    }
    void BlurFilter::qualityGet(SInt32& result)
    {
//##protect##"instance::BlurFilter::qualityGet()"
        result = (GetBlurFilterData()->GetParams().Passes);
//##protect##"instance::BlurFilter::qualityGet()"
    }
    void BlurFilter::qualitySet(Value& result, SInt32 value)
    {
//##protect##"instance::BlurFilter::qualitySet()"
        SF_UNUSED(result);
        GetBlurFilterData()->GetParams().Passes = value;
//##protect##"instance::BlurFilter::qualitySet()"
    }
    void BlurFilter::clone(Value& result)
    {
//##protect##"instance::BlurFilter::clone()"
        InstanceTraits::BlurFilter& itr = static_cast<InstanceTraits::BlurFilter&>(GetTraits());
        Pickable<BlurFilter> r = itr.MakeInstance(itr);

        Value::Number blurX, blurY;
        SInt32 qual;
        blurXGet(blurX);
        blurYGet(blurY);
        qualityGet(qual);

        Value tempResult;
        r->blurXSet(tempResult, blurX);
        r->blurYSet(tempResult, blurY);
        r->qualitySet(tempResult, qual);
        result = r;
//##protect##"instance::BlurFilter::clone()"
    }

//##protect##"instance$methods"
    void BlurFilter::AS3Constructor(unsigned argc, const Value* argv)
    {
        Value result;
        Value::Number bx(4), by(4);
        SInt32 qual(1);
        if ( argc >= 1 && !argv[0].Convert2Number(bx)) return;
        if ( argc >= 2 && !argv[1].Convert2Number(by)) return;
        if ( argc >= 3 && !argv[2].Convert2Int32(qual)) return;

        blurXSet(result, bx);
        blurYSet(result, by);
        qualitySet(result, (SInt16)qual);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo BlurFilter::ti[BlurFilter::ThunkInfoNum] = {
        {TFunc_Instances_BlurFilter_blurXGet::Func, &NumberCI, "blurX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BlurFilter_blurXSet::Func, NULL, "blurX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_BlurFilter_blurYGet::Func, &NumberCI, "blurY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BlurFilter_blurYSet::Func, NULL, "blurY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_BlurFilter_qualityGet::Func, &int_CI, "quality", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BlurFilter_qualitySet::Func, NULL, "quality", NULL, CT_Set, 1, 1},
        {TFunc_Instances_BlurFilter_clone::Func, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

    BlurFilter::BlurFilter(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::BlurFilter::BlurFilter()"
//##protect##"InstanceTraits::BlurFilter::BlurFilter()"
        SetMemSize(sizeof(Instances::BlurFilter));

    }

    Pickable<Instances::BlurFilter> BlurFilter::MakeInstance(Traits& t)
    {
        return Pickable<Instances::BlurFilter>(new(t.Alloc()) Instances::BlurFilter(t));
    }

    void BlurFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    BlurFilter::BlurFilter(VM& vm)
    : Traits(vm, BlurFilterCI)
    {
//##protect##"ClassTraits::BlurFilter::BlurFilter()"
//##protect##"ClassTraits::BlurFilter::BlurFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BlurFilter(vm, BlurFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BlurFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BlurFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BlurFilterCI = {
    ClassInfo::CompileTime,
    "BlurFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::BlurFilter::MakeClassTraits,
    0,
    0,
    InstanceTraits::BlurFilter::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::BlurFilter::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

