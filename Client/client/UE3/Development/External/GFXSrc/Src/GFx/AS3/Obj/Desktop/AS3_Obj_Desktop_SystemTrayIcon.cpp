//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_SystemTrayIcon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_SystemTrayIcon.h"
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
    const ThunkInfo SystemTrayIcon_ti[7] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "bitmaps", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "height", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "tooltip", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "tooltip", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "width", NULL, CT_Get, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    SystemTrayIcon::SystemTrayIcon(ClassTraits::Traits& t)
    : Class(t)
    , MAX_TIP_LENGTH(63)
    {
//##protect##"class_::SystemTrayIcon::SystemTrayIcon()"
//##protect##"class_::SystemTrayIcon::SystemTrayIcon()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SystemTrayIcon::mi[SystemTrayIcon::MemberInfoNum] = {
        {"MAX_TIP_LENGTH", OFFSETOF(Classes::SystemTrayIcon, MAX_TIP_LENGTH), SlotInfo::BT_Number, 1},
    };

    SystemTrayIcon::SystemTrayIcon(VM& vm)
    : Traits(vm, SystemTrayIconCI)
    {
//##protect##"ClassTraits::SystemTrayIcon::SystemTrayIcon()"
//##protect##"ClassTraits::SystemTrayIcon::SystemTrayIcon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, SystemTrayIconCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SystemTrayIcon(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SystemTrayIcon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SystemTrayIcon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SystemTrayIconCI = {
    ClassInfo::CompileTime,
    "SystemTrayIcon", "flash.desktop", &InteractiveIconCI,
    ClassTraits::SystemTrayIcon::MakeClassTraits,
    0,
    ClassTraits::SystemTrayIcon::MemberInfoNum,
    7,
    0,
    NULL,
    ClassTraits::SystemTrayIcon::mi,
    InstanceTraits::SystemTrayIcon_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

