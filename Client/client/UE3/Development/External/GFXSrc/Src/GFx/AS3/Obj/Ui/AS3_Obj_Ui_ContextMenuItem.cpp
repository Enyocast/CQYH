//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuItem.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_ContextMenuItem.h"
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
    const ThunkInfo ContextMenuItem_ti[7] = {
        {ThunkInfo::EmptyFunc, &StringCI, "caption", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "caption", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "separatorBefore", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "separatorBefore", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "visible", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "visible", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ContextMenuItemCI, "clone", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    ContextMenuItem::ContextMenuItem(VM& vm)
    : Traits(vm, ContextMenuItemCI)
    {
//##protect##"ClassTraits::ContextMenuItem::ContextMenuItem()"
//##protect##"ClassTraits::ContextMenuItem::ContextMenuItem()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, ContextMenuItemCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ContextMenuItem::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenuItem(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ContextMenuItemCI = {
    ClassInfo::CompileTime,
    "ContextMenuItem", "flash.ui", &EventDispatcherCI,
    ClassTraits::ContextMenuItem::MakeClassTraits,
    0,
    0,
    7,
    0,
    NULL,
    NULL,
    InstanceTraits::ContextMenuItem_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

