//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GradientGlowFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_GradientGlowFilter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo GradientGlowFilter_ti[23] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "alphas", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alphas", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "angle", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "angle", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "blurX", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "blurX", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "blurY", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "blurY", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "colors", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "colors", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "distance", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "distance", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "knockout", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "knockout", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "quality", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "quality", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "ratios", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "ratios", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "strength", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "strength", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "type", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "type", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    GradientGlowFilter::GradientGlowFilter(VM& vm)
    : Traits(vm, GradientGlowFilterCI)
    {
//##protect##"ClassTraits::GradientGlowFilter::GradientGlowFilter()"
//##protect##"ClassTraits::GradientGlowFilter::GradientGlowFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapFilter(vm, GradientGlowFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GradientGlowFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GradientGlowFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GradientGlowFilterCI = {
    ClassInfo::CompileTime,
    "GradientGlowFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::GradientGlowFilter::MakeClassTraits,
    0,
    0,
    23,
    0,
    NULL,
    NULL,
    InstanceTraits::GradientGlowFilter_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

