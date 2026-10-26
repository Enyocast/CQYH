//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_InteractiveObject.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_InteractiveObject.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_AvmInteractiveObj.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_contextMenuGet, Value> TFunc_Instances_InteractiveObject_contextMenuGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_contextMenuSet, Value, const Value&> TFunc_Instances_InteractiveObject_contextMenuSet;
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_doubleClickEnabledGet, bool> TFunc_Instances_InteractiveObject_doubleClickEnabledGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_doubleClickEnabledSet, Value, bool> TFunc_Instances_InteractiveObject_doubleClickEnabledSet;
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_focusRectGet, Value> TFunc_Instances_InteractiveObject_focusRectGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_focusRectSet, Value, const Value&> TFunc_Instances_InteractiveObject_focusRectSet;
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_mouseEnabledGet, bool> TFunc_Instances_InteractiveObject_mouseEnabledGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_mouseEnabledSet, Value, bool> TFunc_Instances_InteractiveObject_mouseEnabledSet;
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_tabEnabledGet, bool> TFunc_Instances_InteractiveObject_tabEnabledGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_tabEnabledSet, Value, bool> TFunc_Instances_InteractiveObject_tabEnabledSet;
typedef ThunkFunc0<Instances::InteractiveObject, Instances::InteractiveObject::mid_tabIndexGet, SInt32> TFunc_Instances_InteractiveObject_tabIndexGet;
typedef ThunkFunc1<Instances::InteractiveObject, Instances::InteractiveObject::mid_tabIndexSet, Value, SInt32> TFunc_Instances_InteractiveObject_tabIndexSet;

template <> const TFunc_Instances_InteractiveObject_contextMenuGet::TMethod TFunc_Instances_InteractiveObject_contextMenuGet::Method = &Instances::InteractiveObject::contextMenuGet;
template <> const TFunc_Instances_InteractiveObject_contextMenuSet::TMethod TFunc_Instances_InteractiveObject_contextMenuSet::Method = &Instances::InteractiveObject::contextMenuSet;
template <> const TFunc_Instances_InteractiveObject_doubleClickEnabledGet::TMethod TFunc_Instances_InteractiveObject_doubleClickEnabledGet::Method = &Instances::InteractiveObject::doubleClickEnabledGet;
template <> const TFunc_Instances_InteractiveObject_doubleClickEnabledSet::TMethod TFunc_Instances_InteractiveObject_doubleClickEnabledSet::Method = &Instances::InteractiveObject::doubleClickEnabledSet;
template <> const TFunc_Instances_InteractiveObject_focusRectGet::TMethod TFunc_Instances_InteractiveObject_focusRectGet::Method = &Instances::InteractiveObject::focusRectGet;
template <> const TFunc_Instances_InteractiveObject_focusRectSet::TMethod TFunc_Instances_InteractiveObject_focusRectSet::Method = &Instances::InteractiveObject::focusRectSet;
template <> const TFunc_Instances_InteractiveObject_mouseEnabledGet::TMethod TFunc_Instances_InteractiveObject_mouseEnabledGet::Method = &Instances::InteractiveObject::mouseEnabledGet;
template <> const TFunc_Instances_InteractiveObject_mouseEnabledSet::TMethod TFunc_Instances_InteractiveObject_mouseEnabledSet::Method = &Instances::InteractiveObject::mouseEnabledSet;
template <> const TFunc_Instances_InteractiveObject_tabEnabledGet::TMethod TFunc_Instances_InteractiveObject_tabEnabledGet::Method = &Instances::InteractiveObject::tabEnabledGet;
template <> const TFunc_Instances_InteractiveObject_tabEnabledSet::TMethod TFunc_Instances_InteractiveObject_tabEnabledSet::Method = &Instances::InteractiveObject::tabEnabledSet;
template <> const TFunc_Instances_InteractiveObject_tabIndexGet::TMethod TFunc_Instances_InteractiveObject_tabIndexGet::Method = &Instances::InteractiveObject::tabIndexGet;
template <> const TFunc_Instances_InteractiveObject_tabIndexSet::TMethod TFunc_Instances_InteractiveObject_tabIndexSet::Method = &Instances::InteractiveObject::tabIndexSet;

namespace Instances
{
    InteractiveObject::InteractiveObject(InstanceTraits::Traits& t)
    : Instances::DisplayObject(t)
//##protect##"instance::InteractiveObject::InteractiveObject()$data"
//##protect##"instance::InteractiveObject::InteractiveObject()$data"
    {
//##protect##"instance::InteractiveObject::InteractiveObject()$code"
//##protect##"instance::InteractiveObject::InteractiveObject()$code"
    }

    void InteractiveObject::contextMenuGet(Value& result)
    {
//##protect##"instance::InteractiveObject::contextMenuGet()"
        SF_UNUSED1(result);
        result = pContextMenu;
//##protect##"instance::InteractiveObject::contextMenuGet()"
    }
    void InteractiveObject::contextMenuSet(Value& result, const Value& value)
    {
//##protect##"instance::InteractiveObject::contextMenuSet()"
        SF_UNUSED2(result, value);
        if (value.IsObject())
            pContextMenu = value.GetObject();
        else
        {
            return GetVM().ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, GetVM()
                SF_DEBUG_ARG(GetVM().GetValueTraits(value).GetName().ToCStr())
                SF_DEBUG_ARG("flash.ui.ContextMenu")
                ));
        }
//##protect##"instance::InteractiveObject::contextMenuSet()"
    }
    void InteractiveObject::doubleClickEnabledGet(bool& result)
    {
//##protect##"instance::InteractiveObject::doubleClickEnabledGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        result = ToAvmInteractiveObj(pDispObj->CharToInteractiveObject())->IsDoubleClickEnabled();
//##protect##"instance::InteractiveObject::doubleClickEnabledGet()"
    }
    void InteractiveObject::doubleClickEnabledSet(Value& result, bool value)
    {
//##protect##"instance::InteractiveObject::doubleClickEnabledSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        ToAvmInteractiveObj(pDispObj->CharToInteractiveObject())->SetDoubleClickEnabled(value);
//##protect##"instance::InteractiveObject::doubleClickEnabledSet()"
    }
    void InteractiveObject::focusRectGet(Value& result)
    {
//##protect##"instance::InteractiveObject::focusRectGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        if (GetIntObj()->IsTabEnabledFlagDefined())
            result.SetBool(GetIntObj()->IsTabEnabledFlagTrue());
        else
            result.SetNull();
//##protect##"instance::InteractiveObject::focusRectGet()"
    }
    void InteractiveObject::focusRectSet(Value& result, const Value& value)
    {
//##protect##"instance::InteractiveObject::focusRectSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());

        if (!value.IsUndefined())
        {
            GetIntObj()->SetFocusRectFlag(value.Convert2Boolean());
        }
        else
            GetIntObj()->UndefineTabEnabledFlag();
//##protect##"instance::InteractiveObject::focusRectSet()"
    }
    void InteractiveObject::mouseEnabledGet(bool& result)
    {
//##protect##"instance::InteractiveObject::mouseEnabledGet()"
        result = !pDispObj->CharToInteractiveObject()->IsMouseDisabledFlagSet();
//##protect##"instance::InteractiveObject::mouseEnabledGet()"
    }
    void InteractiveObject::mouseEnabledSet(Value& result, bool value)
    {
//##protect##"instance::InteractiveObject::mouseEnabledSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);

        pDispObj->CharToInteractiveObject()->SetMouseDisabledFlag(!value);
//##protect##"instance::InteractiveObject::mouseEnabledSet()"
    }
    void InteractiveObject::tabEnabledGet(bool& result)
    {
//##protect##"instance::InteractiveObject::tabEnabledGet()"
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        SF_UNUSED1(result);
        result = GetIntObj()->IsTabEnabledFlagTrue();
//##protect##"instance::InteractiveObject::tabEnabledGet()"
    }
    void InteractiveObject::tabEnabledSet(Value& result, bool value)
    {
//##protect##"instance::InteractiveObject::tabEnabledSet()"
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        SF_UNUSED2(result, value);
        GetIntObj()->SetTabEnabledFlag(value);

        // fire tabChildrenChange event
        SPtr<Event> e = 
            CreateEventObject(GetVM().GetStringManager().CreateConstString("tabEnabledChange"), true, false);
        Dispatch(e, pDispObj);

//##protect##"instance::InteractiveObject::tabEnabledSet()"
    }
    void InteractiveObject::tabIndexGet(SInt32& result)
    {
//##protect##"instance::InteractiveObject::tabIndexGet()"
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        SF_UNUSED1(result);
        result = GetIntObj()->GetTabIndex();
//##protect##"instance::InteractiveObject::tabIndexGet()"
    }
    void InteractiveObject::tabIndexSet(Value& result, SInt32 value)
    {
//##protect##"instance::InteractiveObject::tabIndexSet()"
        SF_UNUSED2(result, value);
        GetIntObj()->SetTabIndex(value);

        // fire tabChildrenChange event
        SPtr<Event> e = 
            CreateEventObject(GetVM().GetStringManager().CreateConstString("tabIndexChange"), true, false);
        Dispatch(e, pDispObj);

//##protect##"instance::InteractiveObject::tabIndexSet()"
    }

//##protect##"instance$methods"
    void InteractiveObject::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        DisplayObject::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<AS3::Object, Mem_Stat>(prcc, pContextMenu, op SF_DEBUG_ARG(*this));
    }

    InteractiveObject::~InteractiveObject()
    {
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo InteractiveObject::ti[InteractiveObject::ThunkInfoNum] = {
        {TFunc_Instances_InteractiveObject_contextMenuGet::Func, &ObjectCI, "contextMenu", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_contextMenuSet::Func, NULL, "contextMenu", NULL, CT_Set, 1, 1},
        {TFunc_Instances_InteractiveObject_doubleClickEnabledGet::Func, &BooleanCI, "doubleClickEnabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_doubleClickEnabledSet::Func, NULL, "doubleClickEnabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_InteractiveObject_focusRectGet::Func, &ObjectCI, "focusRect", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_focusRectSet::Func, NULL, "focusRect", NULL, CT_Set, 1, 1},
        {TFunc_Instances_InteractiveObject_mouseEnabledGet::Func, &BooleanCI, "mouseEnabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_mouseEnabledSet::Func, NULL, "mouseEnabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_InteractiveObject_tabEnabledGet::Func, &BooleanCI, "tabEnabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_tabEnabledSet::Func, NULL, "tabEnabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_InteractiveObject_tabIndexGet::Func, &int_CI, "tabIndex", NULL, CT_Get, 0, 0},
        {TFunc_Instances_InteractiveObject_tabIndexSet::Func, NULL, "tabIndex", NULL, CT_Set, 1, 1},
    };

    InteractiveObject::InteractiveObject(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::InteractiveObject::InteractiveObject()"
        SetTraitsType(Traits_InteractiveObject);
//##protect##"InstanceTraits::InteractiveObject::InteractiveObject()"
        SetMemSize(sizeof(Instances::InteractiveObject));

    }

    Pickable<Instances::InteractiveObject> InteractiveObject::MakeInstance(Traits& t)
    {
        return Pickable<Instances::InteractiveObject>(new(t.Alloc()) Instances::InteractiveObject(t));
    }

    void InteractiveObject::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    InteractiveObject::InteractiveObject(VM& vm)
    : Traits(vm, InteractiveObjectCI)
    {
//##protect##"ClassTraits::InteractiveObject::InteractiveObject()"
        SetTraitsType(Traits_InteractiveObject);
//##protect##"ClassTraits::InteractiveObject::InteractiveObject()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::InteractiveObject(vm, InteractiveObjectCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> InteractiveObject::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InteractiveObject(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo InteractiveObjectCI = {
    ClassInfo::CompileTime,
    "InteractiveObject", "flash.display", &DisplayObjectCI,
    ClassTraits::InteractiveObject::MakeClassTraits,
    0,
    0,
    InstanceTraits::InteractiveObject::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::InteractiveObject::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

