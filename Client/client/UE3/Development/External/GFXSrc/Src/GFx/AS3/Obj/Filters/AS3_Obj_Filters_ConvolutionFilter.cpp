//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_ConvolutionFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_ConvolutionFilter.h"
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
    const ThunkInfo ConvolutionFilter_ti[19] = {
        {ThunkInfo::EmptyFunc, &NumberCI, "alpha", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alpha", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "bias", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bias", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "clamp", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "clamp", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "color", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "color", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "divisor", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "divisor", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "matrix", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrix", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "matrixX", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrixX", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "matrixY", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "matrixY", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "preserveAlpha", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "preserveAlpha", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    ConvolutionFilter::ConvolutionFilter(VM& vm)
    : Traits(vm, ConvolutionFilterCI)
    {
//##protect##"ClassTraits::ConvolutionFilter::ConvolutionFilter()"
//##protect##"ClassTraits::ConvolutionFilter::ConvolutionFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapFilter(vm, ConvolutionFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ConvolutionFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ConvolutionFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ConvolutionFilterCI = {
    ClassInfo::CompileTime,
    "ConvolutionFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::ConvolutionFilter::MakeClassTraits,
    0,
    0,
    19,
    0,
    NULL,
    NULL,
    InstanceTraits::ConvolutionFilter_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

