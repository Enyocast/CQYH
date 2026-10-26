//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GlowFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_GlowFilter.h"
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
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_alphaGet, Value::Number> TFunc_Instances_GlowFilter_alphaGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_alphaSet, Value, Value::Number> TFunc_Instances_GlowFilter_alphaSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_blurXGet, Value::Number> TFunc_Instances_GlowFilter_blurXGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_blurXSet, Value, Value::Number> TFunc_Instances_GlowFilter_blurXSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_blurYGet, Value::Number> TFunc_Instances_GlowFilter_blurYGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_blurYSet, Value, Value::Number> TFunc_Instances_GlowFilter_blurYSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_colorGet, UInt32> TFunc_Instances_GlowFilter_colorGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_colorSet, Value, UInt32> TFunc_Instances_GlowFilter_colorSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_innerGet, bool> TFunc_Instances_GlowFilter_innerGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_innerSet, Value, bool> TFunc_Instances_GlowFilter_innerSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_knockoutGet, bool> TFunc_Instances_GlowFilter_knockoutGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_knockoutSet, Value, bool> TFunc_Instances_GlowFilter_knockoutSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_qualityGet, SInt32> TFunc_Instances_GlowFilter_qualityGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_qualitySet, Value, SInt32> TFunc_Instances_GlowFilter_qualitySet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_strengthGet, Value::Number> TFunc_Instances_GlowFilter_strengthGet;
typedef ThunkFunc1<Instances::GlowFilter, Instances::GlowFilter::mid_strengthSet, Value, Value::Number> TFunc_Instances_GlowFilter_strengthSet;
typedef ThunkFunc0<Instances::GlowFilter, Instances::GlowFilter::mid_clone, Value> TFunc_Instances_GlowFilter_clone;

template <> const TFunc_Instances_GlowFilter_alphaGet::TMethod TFunc_Instances_GlowFilter_alphaGet::Method = &Instances::GlowFilter::alphaGet;
template <> const TFunc_Instances_GlowFilter_alphaSet::TMethod TFunc_Instances_GlowFilter_alphaSet::Method = &Instances::GlowFilter::alphaSet;
template <> const TFunc_Instances_GlowFilter_blurXGet::TMethod TFunc_Instances_GlowFilter_blurXGet::Method = &Instances::GlowFilter::blurXGet;
template <> const TFunc_Instances_GlowFilter_blurXSet::TMethod TFunc_Instances_GlowFilter_blurXSet::Method = &Instances::GlowFilter::blurXSet;
template <> const TFunc_Instances_GlowFilter_blurYGet::TMethod TFunc_Instances_GlowFilter_blurYGet::Method = &Instances::GlowFilter::blurYGet;
template <> const TFunc_Instances_GlowFilter_blurYSet::TMethod TFunc_Instances_GlowFilter_blurYSet::Method = &Instances::GlowFilter::blurYSet;
template <> const TFunc_Instances_GlowFilter_colorGet::TMethod TFunc_Instances_GlowFilter_colorGet::Method = &Instances::GlowFilter::colorGet;
template <> const TFunc_Instances_GlowFilter_colorSet::TMethod TFunc_Instances_GlowFilter_colorSet::Method = &Instances::GlowFilter::colorSet;
template <> const TFunc_Instances_GlowFilter_innerGet::TMethod TFunc_Instances_GlowFilter_innerGet::Method = &Instances::GlowFilter::innerGet;
template <> const TFunc_Instances_GlowFilter_innerSet::TMethod TFunc_Instances_GlowFilter_innerSet::Method = &Instances::GlowFilter::innerSet;
template <> const TFunc_Instances_GlowFilter_knockoutGet::TMethod TFunc_Instances_GlowFilter_knockoutGet::Method = &Instances::GlowFilter::knockoutGet;
template <> const TFunc_Instances_GlowFilter_knockoutSet::TMethod TFunc_Instances_GlowFilter_knockoutSet::Method = &Instances::GlowFilter::knockoutSet;
template <> const TFunc_Instances_GlowFilter_qualityGet::TMethod TFunc_Instances_GlowFilter_qualityGet::Method = &Instances::GlowFilter::qualityGet;
template <> const TFunc_Instances_GlowFilter_qualitySet::TMethod TFunc_Instances_GlowFilter_qualitySet::Method = &Instances::GlowFilter::qualitySet;
template <> const TFunc_Instances_GlowFilter_strengthGet::TMethod TFunc_Instances_GlowFilter_strengthGet::Method = &Instances::GlowFilter::strengthGet;
template <> const TFunc_Instances_GlowFilter_strengthSet::TMethod TFunc_Instances_GlowFilter_strengthSet::Method = &Instances::GlowFilter::strengthSet;
template <> const TFunc_Instances_GlowFilter_clone::TMethod TFunc_Instances_GlowFilter_clone::Method = &Instances::GlowFilter::clone;

namespace Instances
{
    GlowFilter::GlowFilter(InstanceTraits::Traits& t)
    : Instances::BitmapFilter(t)
//##protect##"instance::GlowFilter::GlowFilter()$data"
//##protect##"instance::GlowFilter::GlowFilter()$data"
    {
//##protect##"instance::GlowFilter::GlowFilter()$code"
        FilterData = *SF_NEW Render::GlowFilter();
//##protect##"instance::GlowFilter::GlowFilter()$code"
    }

    void GlowFilter::alphaGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::alphaGet()"
        result = GetGlowFilterData()->GetParams().Colors[0].GetAlpha() / 255.0;
//##protect##"instance::GlowFilter::alphaGet()"
    }
    void GlowFilter::alphaSet(Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::alphaSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Colors[0].SetAlpha((UByte)(value * 255));
//##protect##"instance::GlowFilter::alphaSet()"
    }
    void GlowFilter::blurXGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::blurXGet()"
        result = TwipsToPixels(GetGlowFilterData()->GetParams().BlurX);
//##protect##"instance::GlowFilter::blurXGet()"
    }
    void GlowFilter::blurXSet(Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::blurXSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().BlurX = PixelsToTwips((float)value);
//##protect##"instance::GlowFilter::blurXSet()"
    }
    void GlowFilter::blurYGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::blurYGet()"
        result = TwipsToPixels(GetGlowFilterData()->GetParams().BlurY);
//##protect##"instance::GlowFilter::blurYGet()"
    }
    void GlowFilter::blurYSet(Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::blurYSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().BlurY = PixelsToTwips((float)value);
//##protect##"instance::GlowFilter::blurYSet()"
    }
    void GlowFilter::colorGet(UInt32& result)
    {
//##protect##"instance::GlowFilter::colorGet()"
        Render::Color& c = GetGlowFilterData()->GetParams().Colors[0];
        result = c.GetColorRGB().Raw;
//##protect##"instance::GlowFilter::colorGet()"
    }
    void GlowFilter::colorSet(Value& result, UInt32 value)
    {
//##protect##"instance::GlowFilter::colorSet()"
        SF_UNUSED(result);
        Render::Color& c = GetGlowFilterData()->GetParams().Colors[0];
        c.SetColor(value, c.GetAlpha());
//##protect##"instance::GlowFilter::colorSet()"
    }
    void GlowFilter::innerGet(bool& result)
    {
//##protect##"instance::GlowFilter::innerGet()"
        result = (GetGlowFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Inner) != 0;
//##protect##"instance::GlowFilter::innerGet()"
    }
    void GlowFilter::innerSet(Value& result, bool value)
    {
//##protect##"instance::GlowFilter::innerSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Mode |= (value ? Render::BlurFilterParams::Mode_Inner : 0);
//##protect##"instance::GlowFilter::innerSet()"
    }
    void GlowFilter::knockoutGet(bool& result)
    {
//##protect##"instance::GlowFilter::knockoutGet()"
        result = (GetGlowFilterData()->GetParams().Mode & Render::BlurFilterParams::Mode_Knockout) != 0;
//##protect##"instance::GlowFilter::knockoutGet()"
    }
    void GlowFilter::knockoutSet(Value& result, bool value)
    {
//##protect##"instance::GlowFilter::knockoutSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Mode |= (value ? Render::BlurFilterParams::Mode_Knockout : 0);
//##protect##"instance::GlowFilter::knockoutSet()"
    }
    void GlowFilter::qualityGet(SInt32& result)
    {
//##protect##"instance::GlowFilter::qualityGet()"
        result = (GetGlowFilterData()->GetParams().Passes);
//##protect##"instance::GlowFilter::qualityGet()"
    }
    void GlowFilter::qualitySet(Value& result, SInt32 value)
    {
//##protect##"instance::GlowFilter::qualitySet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Passes = value;
//##protect##"instance::GlowFilter::qualitySet()"
    }
    void GlowFilter::strengthGet(Value::Number& result)
    {
//##protect##"instance::GlowFilter::strengthGet()"
        result = GetGlowFilterData()->GetParams().Strength;
//##protect##"instance::GlowFilter::strengthGet()"
    }
    void GlowFilter::strengthSet(Value& result, Value::Number value)
    {
//##protect##"instance::GlowFilter::strengthSet()"
        SF_UNUSED(result);
        GetGlowFilterData()->GetParams().Strength = (float)value;
//##protect##"instance::GlowFilter::strengthSet()"
    }
    void GlowFilter::clone(Value& result)
    {
//##protect##"instance::GlowFilter::clone()"
        InstanceTraits::GlowFilter& itr = static_cast<InstanceTraits::GlowFilter&>(GetTraits());
        Pickable<GlowFilter> r = itr.MakeInstance(itr);

        UInt32 color;
        Value::Number alpha, blurX, blurY, stren;
        SInt32 qual;
        bool inner, knock;
        colorGet(color);
        alphaGet(alpha);
        blurXGet(blurX);
        blurYGet(blurY);
        strengthGet(stren);
        qualityGet(qual);
        innerGet(inner);
        knockoutGet(knock);

        Value tempResult;
        r->colorSet(tempResult, color);
        r->alphaSet(tempResult, alpha);
        r->blurXSet(tempResult, blurX);
        r->blurYSet(tempResult, blurY);
        r->strengthSet(tempResult, stren);
        r->qualitySet(tempResult, qual);
        r->innerSet(tempResult, inner);
        r->knockoutSet(tempResult, knock);
        result = r;
//##protect##"instance::GlowFilter::clone()"
    }

//##protect##"instance$methods"
    void GlowFilter::AS3Constructor(unsigned argc, const Value* argv)
    {
        UInt32 color(0xFF0000);
        Value::Number alpha(1), blurX(6), blurY(6), stren(2);
        SInt32 qual(1);
        bool inner(false), knock(false);

        if ( argc >= 1 && !argv[0].Convert2UInt32(color)) return;
        if ( argc >= 2 && !argv[1].Convert2Number(alpha)) return;
        if ( argc >= 3 && !argv[2].Convert2Number(blurX)) return;
        if ( argc >= 4 && !argv[3].Convert2Number(blurY)) return;
        if ( argc >= 5 && !argv[4].Convert2Number(stren)) return;
        if ( argc >= 6 && !argv[5].Convert2Int32(qual)) return;
        if ( argc >= 7 ) inner = argv[6].Convert2Boolean();
        if ( argc >= 8 ) knock = argv[7].Convert2Boolean();

        Value result;
        colorSet(result, color);
        alphaSet(result, alpha);
        blurXSet(result, blurX);
        blurYSet(result, blurY);
        strengthSet(result, stren);
        qualitySet(result, qual);
        innerSet(result, inner);
        knockoutSet(result, knock);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo GlowFilter::ti[GlowFilter::ThunkInfoNum] = {
        {TFunc_Instances_GlowFilter_alphaGet::Func, &NumberCI, "alpha", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_alphaSet::Func, NULL, "alpha", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_blurXGet::Func, &NumberCI, "blurX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_blurXSet::Func, NULL, "blurX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_blurYGet::Func, &NumberCI, "blurY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_blurYSet::Func, NULL, "blurY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_colorGet::Func, &uintCI, "color", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_colorSet::Func, NULL, "color", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_innerGet::Func, &BooleanCI, "inner", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_innerSet::Func, NULL, "inner", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_knockoutGet::Func, &BooleanCI, "knockout", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_knockoutSet::Func, NULL, "knockout", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_qualityGet::Func, &int_CI, "quality", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_qualitySet::Func, NULL, "quality", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_strengthGet::Func, &NumberCI, "strength", NULL, CT_Get, 0, 0},
        {TFunc_Instances_GlowFilter_strengthSet::Func, NULL, "strength", NULL, CT_Set, 1, 1},
        {TFunc_Instances_GlowFilter_clone::Func, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

    GlowFilter::GlowFilter(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::GlowFilter::GlowFilter()"
//##protect##"InstanceTraits::GlowFilter::GlowFilter()"
        SetMemSize(sizeof(Instances::GlowFilter));

    }

    Pickable<Instances::GlowFilter> GlowFilter::MakeInstance(Traits& t)
    {
        return Pickable<Instances::GlowFilter>(new(t.Alloc()) Instances::GlowFilter(t));
    }

    void GlowFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    GlowFilter::GlowFilter(VM& vm)
    : Traits(vm, GlowFilterCI)
    {
//##protect##"ClassTraits::GlowFilter::GlowFilter()"
//##protect##"ClassTraits::GlowFilter::GlowFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::GlowFilter(vm, GlowFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GlowFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GlowFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GlowFilterCI = {
    ClassInfo::CompileTime,
    "GlowFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::GlowFilter::MakeClassTraits,
    0,
    0,
    InstanceTraits::GlowFilter::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::GlowFilter::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

