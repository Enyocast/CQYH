//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ContextMenuEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_ContextMenuEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
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
    const ThunkInfo ContextMenuEvent_ti[6] = {
        {ThunkInfo::EmptyFunc, &InteractiveObjectCI, "contextMenuOwner", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "contextMenuOwner", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &InteractiveObjectCI, "mouseTarget", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "mouseTarget", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    ContextMenuEvent::ContextMenuEvent(ClassTraits::Traits& t)
    : Class(t)
    , MENU_ITEM_SELECT("menuItemSelect")
    , MENU_SELECT("menuSelect")
    {
//##protect##"class_::ContextMenuEvent::ContextMenuEvent()"
//##protect##"class_::ContextMenuEvent::ContextMenuEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ContextMenuEvent::mi[ContextMenuEvent::MemberInfoNum] = {
        {"MENU_ITEM_SELECT", OFFSETOF(Classes::ContextMenuEvent, MENU_ITEM_SELECT), SlotInfo::BT_ConstChar, 1},
        {"MENU_SELECT", OFFSETOF(Classes::ContextMenuEvent, MENU_SELECT), SlotInfo::BT_ConstChar, 1},
    };

    ContextMenuEvent::ContextMenuEvent(VM& vm)
    : Traits(vm, ContextMenuEventCI)
    {
//##protect##"ClassTraits::ContextMenuEvent::ContextMenuEvent()"
//##protect##"ClassTraits::ContextMenuEvent::ContextMenuEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Event(vm, ContextMenuEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ContextMenuEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ContextMenuEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenuEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ContextMenuEventCI = {
    ClassInfo::CompileTime,
    "ContextMenuEvent", "flash.events", &EventCI,
    ClassTraits::ContextMenuEvent::MakeClassTraits,
    0,
    ClassTraits::ContextMenuEvent::MemberInfoNum,
    6,
    0,
    NULL,
    ClassTraits::ContextMenuEvent::mi,
    InstanceTraits::ContextMenuEvent_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

