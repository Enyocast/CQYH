//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeMenuItem.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeMenuItem.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo NativeMenuItem_ti[20] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "checked", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "checked", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ObjectCI, "data", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "data", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "enabled", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "enabled", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isSeparator", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "keyEquivalent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "keyEquivalent", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "keyEquivalentModifiers", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "keyEquivalentModifiers", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "label", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "label", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "mnemonicIndex", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mnemonicIndex", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "name", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "name", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "submenu", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeMenuItem::NativeMenuItem(VM& vm)
    : Traits(vm, NativeMenuItemCI)
    {
//##protect##"ClassTraits::NativeMenuItem::NativeMenuItem()"
//##protect##"ClassTraits::NativeMenuItem::NativeMenuItem()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, NativeMenuItemCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeMenuItem::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeMenuItem(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeMenuItemCI = {
    ClassInfo::CompileTime,
    "NativeMenuItem", "flash.display", &EventDispatcherCI,
    ClassTraits::NativeMenuItem::MakeClassTraits,
    0,
    0,
    20,
    0,
    NULL,
    NULL,
    InstanceTraits::NativeMenuItem_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

