//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuClipboardItems.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_ContextMenuClipboardItems.h"
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

namespace Instances
{
    ContextMenuClipboardItems::ContextMenuClipboardItems(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , clear(false)
    , copy(false)
    , cut(false)
    , paste(false)
    , selectAll(true)
//##protect##"instance::ContextMenuClipboardItems::ContextMenuClipboardItems()$data"
//##protect##"instance::ContextMenuClipboardItems::ContextMenuClipboardItems()$data"
    {
//##protect##"instance::ContextMenuClipboardItems::ContextMenuClipboardItems()$code"
//##protect##"instance::ContextMenuClipboardItems::ContextMenuClipboardItems()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo ContextMenuClipboardItems::mi[ContextMenuClipboardItems::MemberInfoNum] = {
        {"clear", OFFSETOF(Instances::ContextMenuClipboardItems, clear), SlotInfo::BT_Boolean, 0},
        {"copy", OFFSETOF(Instances::ContextMenuClipboardItems, copy), SlotInfo::BT_Boolean, 0},
        {"cut", OFFSETOF(Instances::ContextMenuClipboardItems, cut), SlotInfo::BT_Boolean, 0},
        {"paste", OFFSETOF(Instances::ContextMenuClipboardItems, paste), SlotInfo::BT_Boolean, 0},
        {"selectAll", OFFSETOF(Instances::ContextMenuClipboardItems, selectAll), SlotInfo::BT_Boolean, 0},
    };


    ContextMenuClipboardItems::ContextMenuClipboardItems(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ContextMenuClipboardItems::ContextMenuClipboardItems()"
//##protect##"InstanceTraits::ContextMenuClipboardItems::ContextMenuClipboardItems()"
        SetMemSize(sizeof(Instances::ContextMenuClipboardItems));

    }

    Pickable<Instances::ContextMenuClipboardItems> ContextMenuClipboardItems::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ContextMenuClipboardItems>(new(t.Alloc()) Instances::ContextMenuClipboardItems(t));
    }

    void ContextMenuClipboardItems::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ContextMenuClipboardItems::ContextMenuClipboardItems(VM& vm)
    : Traits(vm, ContextMenuClipboardItemsCI)
    {
//##protect##"ClassTraits::ContextMenuClipboardItems::ContextMenuClipboardItems()"
//##protect##"ClassTraits::ContextMenuClipboardItems::ContextMenuClipboardItems()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ContextMenuClipboardItems(vm, ContextMenuClipboardItemsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ContextMenuClipboardItems::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenuClipboardItems(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ContextMenuClipboardItemsCI = {
    ClassInfo::CompileTime,
    "ContextMenuClipboardItems", "flash.ui", &ObjectCI,
    ClassTraits::ContextMenuClipboardItems::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::ContextMenuClipboardItems::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::ContextMenuClipboardItems::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

