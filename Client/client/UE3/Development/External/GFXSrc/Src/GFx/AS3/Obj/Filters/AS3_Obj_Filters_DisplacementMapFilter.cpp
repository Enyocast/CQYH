//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DisplacementMapFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_DisplacementMapFilter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_BitmapData.h"
#include "../Geom/AS3_Obj_Geom_Point.h"
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
    const ThunkInfo DisplacementMapFilter_ti[19] = {
        {ThunkInfo::EmptyFunc, &NumberCI, "alpha", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alpha", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "color", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "color", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "componentX", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "componentX", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "componentY", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "componentY", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BitmapDataCI, "mapBitmap", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mapBitmap", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &PointCI, "mapPoint", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mapPoint", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "mode", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mode", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "scaleX", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scaleX", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "scaleY", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scaleY", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    DisplacementMapFilter::DisplacementMapFilter(VM& vm)
    : Traits(vm, DisplacementMapFilterCI)
    {
//##protect##"ClassTraits::DisplacementMapFilter::DisplacementMapFilter()"
//##protect##"ClassTraits::DisplacementMapFilter::DisplacementMapFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapFilter(vm, DisplacementMapFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DisplacementMapFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DisplacementMapFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DisplacementMapFilterCI = {
    ClassInfo::CompileTime,
    "DisplacementMapFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::DisplacementMapFilter::MakeClassTraits,
    0,
    0,
    19,
    0,
    NULL,
    NULL,
    InstanceTraits::DisplacementMapFilter_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

