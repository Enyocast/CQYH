//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenu.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_ContextMenu.h"
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
typedef ThunkFunc0<Instances::ContextMenu, Instances::ContextMenu::mid_builtInItemsGet, Value> TFunc_Instances_ContextMenu_builtInItemsGet;
typedef ThunkFunc1<Instances::ContextMenu, Instances::ContextMenu::mid_builtInItemsSet, Value, Instances::ContextMenuBuiltInItems*> TFunc_Instances_ContextMenu_builtInItemsSet;
typedef ThunkFunc0<Instances::ContextMenu, Instances::ContextMenu::mid_customItemsGet, Value> TFunc_Instances_ContextMenu_customItemsGet;
typedef ThunkFunc1<Instances::ContextMenu, Instances::ContextMenu::mid_customItemsSet, Value, Instances::Array*> TFunc_Instances_ContextMenu_customItemsSet;
typedef ThunkFunc0<Instances::ContextMenu, Instances::ContextMenu::mid_clone, Value> TFunc_Instances_ContextMenu_clone;
typedef ThunkFunc0<Instances::ContextMenu, Instances::ContextMenu::mid_hideBuiltInItems, Value> TFunc_Instances_ContextMenu_hideBuiltInItems;

template <> const TFunc_Instances_ContextMenu_builtInItemsGet::TMethod TFunc_Instances_ContextMenu_builtInItemsGet::Method = &Instances::ContextMenu::builtInItemsGet;
template <> const TFunc_Instances_ContextMenu_builtInItemsSet::TMethod TFunc_Instances_ContextMenu_builtInItemsSet::Method = &Instances::ContextMenu::builtInItemsSet;
template <> const TFunc_Instances_ContextMenu_customItemsGet::TMethod TFunc_Instances_ContextMenu_customItemsGet::Method = &Instances::ContextMenu::customItemsGet;
template <> const TFunc_Instances_ContextMenu_customItemsSet::TMethod TFunc_Instances_ContextMenu_customItemsSet::Method = &Instances::ContextMenu::customItemsSet;
template <> const TFunc_Instances_ContextMenu_clone::TMethod TFunc_Instances_ContextMenu_clone::Method = &Instances::ContextMenu::clone;
template <> const TFunc_Instances_ContextMenu_hideBuiltInItems::TMethod TFunc_Instances_ContextMenu_hideBuiltInItems::Method = &Instances::ContextMenu::hideBuiltInItems;

namespace Instances
{
    ContextMenu::ContextMenu(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::ContextMenu::ContextMenu()$data"
//##protect##"instance::ContextMenu::ContextMenu()$data"
    {
//##protect##"instance::ContextMenu::ContextMenu()$code"
//##protect##"instance::ContextMenu::ContextMenu()$code"
    }

    void ContextMenu::builtInItemsGet(Value& result)
    {
//##protect##"instance::ContextMenu::builtInItemsGet()"
        SF_UNUSED1(result);
        result.SetNull();
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::builtInItemsGet()");
//##protect##"instance::ContextMenu::builtInItemsGet()"
    }
    void ContextMenu::builtInItemsSet(Value& result, Instances::ContextMenuBuiltInItems* value)
    {
//##protect##"instance::ContextMenu::builtInItemsSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::builtInItemsSet()");
//##protect##"instance::ContextMenu::builtInItemsSet()"
    }
    void ContextMenu::customItemsGet(Value& result)
    {
//##protect##"instance::ContextMenu::customItemsGet()"
        //@TODO
        result = GetVM().MakeArray();
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::customItemsGet()");
//##protect##"instance::ContextMenu::customItemsGet()"
    }
    void ContextMenu::customItemsSet(Value& result, Instances::Array* value)
    {
//##protect##"instance::ContextMenu::customItemsSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::customItemsSet()");
//##protect##"instance::ContextMenu::customItemsSet()"
    }
    void ContextMenu::clone(Value& result)
    {
//##protect##"instance::ContextMenu::clone()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::clone()");
//##protect##"instance::ContextMenu::clone()"
    }
    void ContextMenu::hideBuiltInItems(Value& result)
    {
//##protect##"instance::ContextMenu::hideBuiltInItems()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::ContextMenu::hideBuiltInItems()");
//##protect##"instance::ContextMenu::hideBuiltInItems()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ContextMenu::ti[ContextMenu::ThunkInfoNum] = {
        {TFunc_Instances_ContextMenu_builtInItemsGet::Func, &ContextMenuBuiltInItemsCI, "builtInItems", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ContextMenu_builtInItemsSet::Func, NULL, "builtInItems", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ContextMenu_customItemsGet::Func, &ArrayCI, "customItems", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ContextMenu_customItemsSet::Func, NULL, "customItems", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ContextMenu_hideBuiltInItems::Func, NULL, "hideBuiltInItems", NULL, CT_Method, 0, 0},
    };

    ContextMenu::ContextMenu(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ContextMenu::ContextMenu()"
//##protect##"InstanceTraits::ContextMenu::ContextMenu()"
        SetMemSize(sizeof(Instances::ContextMenu));

    }

    Pickable<Instances::ContextMenu> ContextMenu::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ContextMenu>(new(t.Alloc()) Instances::ContextMenu(t));
    }

    void ContextMenu::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ContextMenu::ContextMenu(VM& vm)
    : Traits(vm, ContextMenuCI)
    {
//##protect##"ClassTraits::ContextMenu::ContextMenu()"
//##protect##"ClassTraits::ContextMenu::ContextMenu()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ContextMenu(vm, ContextMenuCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ContextMenu::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ContextMenu(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ContextMenuCI = {
    ClassInfo::CompileTime,
    "ContextMenu", "flash.ui", &EventDispatcherCI,
    ClassTraits::ContextMenu::MakeClassTraits,
    0,
    0,
    InstanceTraits::ContextMenu::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::ContextMenu::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

