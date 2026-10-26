//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeMenu.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeMenu.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenuItem;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo NativeMenu_ti[14] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "items", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "numItems", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "addItem", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "addItemAt", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "addSubmenu", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "addSubmenuAt", NULL, CT_Method, 3, 3},
        {ThunkInfo::EmptyFunc, &BooleanCI, "containsItem", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "display", NULL, CT_Method, 3, 3},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "getItemAt", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "getItemByName", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "getItemIndex", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "removeItem", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &NativeMenuItemCI, "removeItemAt", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setItemIndex", NULL, CT_Method, 2, 2},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeMenu::NativeMenu(VM& vm)
    : Traits(vm, NativeMenuCI)
    {
//##protect##"ClassTraits::NativeMenu::NativeMenu()"
//##protect##"ClassTraits::NativeMenu::NativeMenu()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, NativeMenuCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeMenu::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeMenu(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeMenuCI = {
    ClassInfo::CompileTime,
    "NativeMenu", "flash.display", &EventDispatcherCI,
    ClassTraits::NativeMenu::MakeClassTraits,
    0,
    0,
    14,
    0,
    NULL,
    NULL,
    InstanceTraits::NativeMenu_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

