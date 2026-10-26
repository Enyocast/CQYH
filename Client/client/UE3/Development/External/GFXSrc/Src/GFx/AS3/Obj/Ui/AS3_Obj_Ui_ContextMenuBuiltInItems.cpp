//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuBuiltInItems.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_ContextMenuBuiltInItems.h"
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
    ContextMenuBuiltInItems::ContextMenuBuiltInItems(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , forwardAndBack(true)
    , loop(true)
    , play(true)
    , print(true)
    , quality(true)
    , rewind(true)
    , save(true)
    , zoom(true)
//##protect##"instance::ContextMenuBuiltInItems::ContextMenuBuiltInItems()$data"
//##protect##"instance::ContextMenuBuiltInItems::ContextMenuBuiltInItems()$data"
    {
//##protect##"instance::ContextMenuBuiltInItems::ContextMenuBuiltInItems()$code"
//##protect##"instance::ContextMenuBuiltInItems::ContextMenuBuiltInItems()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo ContextMenuBuiltInItems::mi[ContextMenuBuiltInItems::MemberInfoNum] = {
        {"forwardAndBack", OFFSETOF(Instances::ContextMenuBuiltInItems, forwardAndBack), SlotInfo::BT_Boolean, 0},
        {"loop", OFFSETOF(Instances::ContextMenuBuiltInItems, loop), SlotInfo::BT_Boolean, 0},
        {"play", OFFSETOF(Instances::ContextMenuBuiltInItems, play), SlotInfo::BT_Boolean, 0},
        {"print", OFFSETOF(Instances::ContextMenuBuiltInItems, print), SlotInfo::BT_Boolean, 0},
        {"quality", OFFSETOF(Instances::ContextMenuBuiltInItems, quality), SlotInfo::BT_Boolean, 0},
        {"rewind", OFFSETOF(Instances::ContextMenuBuiltInItems, rewind), SlotInfo::BT_Boolean, 0},
        {"save", OFFSETOF(Instances::ContextMenuBuiltInItems, save), SlotInfo::BT_Boolean, 0},
        {"zoom", OFFSETOF(Instances::ContextMenuBuiltInItems, zoom), SlotInfo::BT_Boolean, 0},
    };


    ContextMenuBuiltInItems::ContextMenuBuiltInItems(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ContextMenuBuiltInItems::ContextMenuBuiltInItems()"
//##protect##"InstanceTraits::ContextMenuBuiltInItems::ContextMenuBuiltInItems()"
        SetMemSize(sizeof(Instances::ContextMenuBuiltInItems));

    }

    Pickable<Instances::ContextMenuBuiltInItems> ContextMenuBuiltInItems::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ContextMenuBuiltInItems>(new(t.Alloc()) Instances::ContextMenuBuiltInItems(t));
    }

    void ContextMenuBuiltInItems::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ContextMenuBuiltInItems::ContextMenuBuiltInItems(VM& vm)
    : Traits(vm, ContextMenuBuiltInItemsCI)
    {
//##protect##"ClassTraits::ContextMenuBuiltInItems::ContextMenuBuiltInItems()"
//##protect##"ClassTraits::ContextMenuBuiltInItems::ContextMenuBuiltInItems()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ContextMenuBuiltInItems(vm, ContextMenuBuiltInItemsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ContextMenuBuiltInItems::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenuBuiltInItems(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ContextMenuBuiltInItemsCI = {
    ClassInfo::CompileTime,
    "ContextMenuBuiltInItems", "flash.ui", &ObjectCI,
    ClassTraits::ContextMenuBuiltInItems::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::ContextMenuBuiltInItems::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::ContextMenuBuiltInItems::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

