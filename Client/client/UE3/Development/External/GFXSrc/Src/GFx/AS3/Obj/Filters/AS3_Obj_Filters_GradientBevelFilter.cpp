//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GradientBevelFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_GradientBevelFilter.h"
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
    const ThunkInfo GradientBevelFilter_ti[23] = {
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
    GradientBevelFilter::GradientBevelFilter(VM& vm)
    : Traits(vm, GradientBevelFilterCI)
    {
//##protect##"ClassTraits::GradientBevelFilter::GradientBevelFilter()"
//##protect##"ClassTraits::GradientBevelFilter::GradientBevelFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapFilter(vm, GradientBevelFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GradientBevelFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GradientBevelFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GradientBevelFilterCI = {
    ClassInfo::CompileTime,
    "GradientBevelFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::GradientBevelFilter::MakeClassTraits,
    0,
    0,
    23,
    0,
    NULL,
    NULL,
    InstanceTraits::GradientBevelFilter_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

