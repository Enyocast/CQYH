//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowInitOptions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindowInitOptions.h"
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

namespace InstanceTraits
{
    const ThunkInfo NativeWindowInitOptions_ti[12] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "maximizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "maximizable", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "minimizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minimizable", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "resizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "resizable", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "systemChrome", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "systemChrome", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "transparent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "transparent", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "type", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "type", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeWindowInitOptions::NativeWindowInitOptions(VM& vm)
    : Traits(vm, NativeWindowInitOptionsCI)
    {
//##protect##"ClassTraits::NativeWindowInitOptions::NativeWindowInitOptions()"
//##protect##"ClassTraits::NativeWindowInitOptions::NativeWindowInitOptions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeWindowInitOptionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindowInitOptions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindowInitOptions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowInitOptionsCI = {
    ClassInfo::CompileTime,
    "NativeWindowInitOptions", "flash.display", &ObjectCI,
    ClassTraits::NativeWindowInitOptions::MakeClassTraits,
    0,
    0,
    12,
    0,
    NULL,
    NULL,
    InstanceTraits::NativeWindowInitOptions_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

