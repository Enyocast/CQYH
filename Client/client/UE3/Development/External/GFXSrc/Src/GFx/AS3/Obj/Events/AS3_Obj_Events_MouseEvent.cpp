//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_MouseEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_MouseEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_altKeyGet, bool> TFunc_Instances_MouseEvent_altKeyGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_altKeySet, Value, bool> TFunc_Instances_MouseEvent_altKeySet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_buttonDownGet, bool> TFunc_Instances_MouseEvent_buttonDownGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_buttonDownSet, Value, bool> TFunc_Instances_MouseEvent_buttonDownSet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_clickCountGet, SInt32> TFunc_Instances_MouseEvent_clickCountGet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_commandKeyGet, bool> TFunc_Instances_MouseEvent_commandKeyGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_commandKeySet, Value, bool> TFunc_Instances_MouseEvent_commandKeySet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_controlKeyGet, bool> TFunc_Instances_MouseEvent_controlKeyGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_controlKeySet, Value, bool> TFunc_Instances_MouseEvent_controlKeySet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_ctrlKeyGet, bool> TFunc_Instances_MouseEvent_ctrlKeyGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_ctrlKeySet, Value, bool> TFunc_Instances_MouseEvent_ctrlKeySet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_deltaGet, SInt32> TFunc_Instances_MouseEvent_deltaGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_deltaSet, Value, SInt32> TFunc_Instances_MouseEvent_deltaSet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_localXGet, Value::Number> TFunc_Instances_MouseEvent_localXGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_localXSet, Value, Value::Number> TFunc_Instances_MouseEvent_localXSet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_localYGet, Value::Number> TFunc_Instances_MouseEvent_localYGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_localYSet, Value, Value::Number> TFunc_Instances_MouseEvent_localYSet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_relatedObjectGet, Value> TFunc_Instances_MouseEvent_relatedObjectGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_relatedObjectSet, Value, Instances::InteractiveObject*> TFunc_Instances_MouseEvent_relatedObjectSet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_shiftKeyGet, bool> TFunc_Instances_MouseEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::MouseEvent, Instances::MouseEvent::mid_shiftKeySet, Value, bool> TFunc_Instances_MouseEvent_shiftKeySet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_stageXGet, Value::Number> TFunc_Instances_MouseEvent_stageXGet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_stageYGet, Value::Number> TFunc_Instances_MouseEvent_stageYGet;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_clone, Value> TFunc_Instances_MouseEvent_clone;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_toString, ASString> TFunc_Instances_MouseEvent_toString;
typedef ThunkFunc0<Instances::MouseEvent, Instances::MouseEvent::mid_updateAfterEvent, Value> TFunc_Instances_MouseEvent_updateAfterEvent;

template <> const TFunc_Instances_MouseEvent_altKeyGet::TMethod TFunc_Instances_MouseEvent_altKeyGet::Method = &Instances::MouseEvent::altKeyGet;
template <> const TFunc_Instances_MouseEvent_altKeySet::TMethod TFunc_Instances_MouseEvent_altKeySet::Method = &Instances::MouseEvent::altKeySet;
template <> const TFunc_Instances_MouseEvent_buttonDownGet::TMethod TFunc_Instances_MouseEvent_buttonDownGet::Method = &Instances::MouseEvent::buttonDownGet;
template <> const TFunc_Instances_MouseEvent_buttonDownSet::TMethod TFunc_Instances_MouseEvent_buttonDownSet::Method = &Instances::MouseEvent::buttonDownSet;
template <> const TFunc_Instances_MouseEvent_clickCountGet::TMethod TFunc_Instances_MouseEvent_clickCountGet::Method = &Instances::MouseEvent::clickCountGet;
template <> const TFunc_Instances_MouseEvent_commandKeyGet::TMethod TFunc_Instances_MouseEvent_commandKeyGet::Method = &Instances::MouseEvent::commandKeyGet;
template <> const TFunc_Instances_MouseEvent_commandKeySet::TMethod TFunc_Instances_MouseEvent_commandKeySet::Method = &Instances::MouseEvent::commandKeySet;
template <> const TFunc_Instances_MouseEvent_controlKeyGet::TMethod TFunc_Instances_MouseEvent_controlKeyGet::Method = &Instances::MouseEvent::controlKeyGet;
template <> const TFunc_Instances_MouseEvent_controlKeySet::TMethod TFunc_Instances_MouseEvent_controlKeySet::Method = &Instances::MouseEvent::controlKeySet;
template <> const TFunc_Instances_MouseEvent_ctrlKeyGet::TMethod TFunc_Instances_MouseEvent_ctrlKeyGet::Method = &Instances::MouseEvent::ctrlKeyGet;
template <> const TFunc_Instances_MouseEvent_ctrlKeySet::TMethod TFunc_Instances_MouseEvent_ctrlKeySet::Method = &Instances::MouseEvent::ctrlKeySet;
template <> const TFunc_Instances_MouseEvent_deltaGet::TMethod TFunc_Instances_MouseEvent_deltaGet::Method = &Instances::MouseEvent::deltaGet;
template <> const TFunc_Instances_MouseEvent_deltaSet::TMethod TFunc_Instances_MouseEvent_deltaSet::Method = &Instances::MouseEvent::deltaSet;
template <> const TFunc_Instances_MouseEvent_localXGet::TMethod TFunc_Instances_MouseEvent_localXGet::Method = &Instances::MouseEvent::localXGet;
template <> const TFunc_Instances_MouseEvent_localXSet::TMethod TFunc_Instances_MouseEvent_localXSet::Method = &Instances::MouseEvent::localXSet;
template <> const TFunc_Instances_MouseEvent_localYGet::TMethod TFunc_Instances_MouseEvent_localYGet::Method = &Instances::MouseEvent::localYGet;
template <> const TFunc_Instances_MouseEvent_localYSet::TMethod TFunc_Instances_MouseEvent_localYSet::Method = &Instances::MouseEvent::localYSet;
template <> const TFunc_Instances_MouseEvent_relatedObjectGet::TMethod TFunc_Instances_MouseEvent_relatedObjectGet::Method = &Instances::MouseEvent::relatedObjectGet;
template <> const TFunc_Instances_MouseEvent_relatedObjectSet::TMethod TFunc_Instances_MouseEvent_relatedObjectSet::Method = &Instances::MouseEvent::relatedObjectSet;
template <> const TFunc_Instances_MouseEvent_shiftKeyGet::TMethod TFunc_Instances_MouseEvent_shiftKeyGet::Method = &Instances::MouseEvent::shiftKeyGet;
template <> const TFunc_Instances_MouseEvent_shiftKeySet::TMethod TFunc_Instances_MouseEvent_shiftKeySet::Method = &Instances::MouseEvent::shiftKeySet;
template <> const TFunc_Instances_MouseEvent_stageXGet::TMethod TFunc_Instances_MouseEvent_stageXGet::Method = &Instances::MouseEvent::stageXGet;
template <> const TFunc_Instances_MouseEvent_stageYGet::TMethod TFunc_Instances_MouseEvent_stageYGet::Method = &Instances::MouseEvent::stageYGet;
template <> const TFunc_Instances_MouseEvent_clone::TMethod TFunc_Instances_MouseEvent_clone::Method = &Instances::MouseEvent::clone;
template <> const TFunc_Instances_MouseEvent_toString::TMethod TFunc_Instances_MouseEvent_toString::Method = &Instances::MouseEvent::toString;
template <> const TFunc_Instances_MouseEvent_updateAfterEvent::TMethod TFunc_Instances_MouseEvent_updateAfterEvent::Method = &Instances::MouseEvent::updateAfterEvent;

namespace Instances
{
    MouseEvent::MouseEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::MouseEvent::MouseEvent()$data"
//##protect##"instance::MouseEvent::MouseEvent()$data"
    {
//##protect##"instance::MouseEvent::MouseEvent()$code"
        AltKey = CtrlKey    = ShiftKey = false;
        Delta               = 0;
        LocalX = LocalY     = 0;
        StageX = StageY     = 0;
        LocalInitialized    = false;
        ButtonsMask         = 0;
//##protect##"instance::MouseEvent::MouseEvent()$code"
    }

    void MouseEvent::altKeyGet(bool& result)
    {
//##protect##"instance::MouseEvent::altKeyGet()"
        SF_UNUSED1(result);
        result = AltKey;
//##protect##"instance::MouseEvent::altKeyGet()"
    }
    void MouseEvent::altKeySet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::altKeySet()"
        SF_UNUSED2(result, value);
        AltKey = value;
//##protect##"instance::MouseEvent::altKeySet()"
    }
    void MouseEvent::buttonDownGet(bool& result)
    {
//##protect##"instance::MouseEvent::buttonDownGet()"
        SF_UNUSED1(result);
        result = (ButtonsMask & Button_Left) != 0;
//##protect##"instance::MouseEvent::buttonDownGet()"
    }
    void MouseEvent::buttonDownSet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::buttonDownSet()"
        SF_UNUSED2(result, value);
        if (value)
            ButtonsMask |= Button_Left;
        else
            ButtonsMask &= ~Button_Left;
//##protect##"instance::MouseEvent::buttonDownSet()"
    }
    void MouseEvent::clickCountGet(SInt32& result)
    {
//##protect##"instance::MouseEvent::clickCountGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("MouseEvent::clickCountGet()");
//##protect##"instance::MouseEvent::clickCountGet()"
    }
    void MouseEvent::commandKeyGet(bool& result)
    {
//##protect##"instance::MouseEvent::commandKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::MouseEvent::commandKeyGet()"
    }
    void MouseEvent::commandKeySet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::commandKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::MouseEvent::commandKeySet()"
    }
    void MouseEvent::controlKeyGet(bool& result)
    {
//##protect##"instance::MouseEvent::controlKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::MouseEvent::controlKeyGet()"
    }
    void MouseEvent::controlKeySet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::controlKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::MouseEvent::controlKeySet()"
    }
    void MouseEvent::ctrlKeyGet(bool& result)
    {
//##protect##"instance::MouseEvent::ctrlKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::MouseEvent::ctrlKeyGet()"
    }
    void MouseEvent::ctrlKeySet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::ctrlKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::MouseEvent::ctrlKeySet()"
    }
    void MouseEvent::deltaGet(SInt32& result)
    {
//##protect##"instance::MouseEvent::deltaGet()"
        SF_UNUSED1(result);
        result = Delta;
//##protect##"instance::MouseEvent::deltaGet()"
    }
    void MouseEvent::deltaSet(Value& result, SInt32 value)
    {
//##protect##"instance::MouseEvent::deltaSet()"
        SF_UNUSED2(result, value);
        Delta = value;
//##protect##"instance::MouseEvent::deltaSet()"
    }
    void MouseEvent::localXGet(Value::Number& result)
    {
//##protect##"instance::MouseEvent::localXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalX);
//##protect##"instance::MouseEvent::localXGet()"
    }
    void MouseEvent::localXSet(Value& result, Value::Number value)
    {
//##protect##"instance::MouseEvent::localXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalX = PixelsToTwips(value);
//##protect##"instance::MouseEvent::localXSet()"
    }
    void MouseEvent::localYGet(Value::Number& result)
    {
//##protect##"instance::MouseEvent::localYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalY);
//##protect##"instance::MouseEvent::localYGet()"
    }
    void MouseEvent::localYSet(Value& result, Value::Number value)
    {
//##protect##"instance::MouseEvent::localYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalY = PixelsToTwips(value);
//##protect##"instance::MouseEvent::localYSet()"
    }
    void MouseEvent::relatedObjectGet(Value& result)
    {
//##protect##"instance::MouseEvent::relatedObjectGet()"
        SF_UNUSED1(result);
        result = Value(RelatedObj);
//##protect##"instance::MouseEvent::relatedObjectGet()"
    }
    void MouseEvent::relatedObjectSet(Value& result, Instances::InteractiveObject* value)
    {
//##protect##"instance::MouseEvent::relatedObjectSet()"
        SF_UNUSED2(result, value);
        RelatedObj = value;
//##protect##"instance::MouseEvent::relatedObjectSet()"
    }
    void MouseEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::MouseEvent::shiftKeyGet()"
        SF_UNUSED1(result);
        result = ShiftKey;
//##protect##"instance::MouseEvent::shiftKeyGet()"
    }
    void MouseEvent::shiftKeySet(Value& result, bool value)
    {
//##protect##"instance::MouseEvent::shiftKeySet()"
        SF_UNUSED2(result, value);
        ShiftKey = value;
//##protect##"instance::MouseEvent::shiftKeySet()"
    }
    void MouseEvent::stageXGet(Value::Number& result)
    {
//##protect##"instance::MouseEvent::stageXGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageX);
//##protect##"instance::MouseEvent::stageXGet()"
    }
    void MouseEvent::stageYGet(Value::Number& result)
    {
//##protect##"instance::MouseEvent::stageYGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageY);
//##protect##"instance::MouseEvent::stageYGet()"
    }
    void MouseEvent::clone(Value& result)
    {
//##protect##"instance::MouseEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::MouseEvent::clone()"
    }
    void MouseEvent::toString(ASString& result)
    {
//##protect##"instance::MouseEvent::toString()"
        SF_UNUSED1(result);
        //example: [MouseEvent type="rollOver" bubbles=false cancelable=false eventPhase=2 localX=248 localY=47 
        // stageX=369 stageY=152 relatedObject=null ctrlKey=false altKey=false shiftKey=false delta=0]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("MouseEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("localX"),
            vm.GetStringManager().CreateConstString("localY"),
            vm.GetStringManager().CreateConstString("stageX"),
            vm.GetStringManager().CreateConstString("stageY"),
            vm.GetStringManager().CreateConstString("relatedObject"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("delta")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::MouseEvent::toString()"
    }
    void MouseEvent::updateAfterEvent(Value& result)
    {
//##protect##"instance::MouseEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("MouseEvent::updateAfterEvent()");
//##protect##"instance::MouseEvent::updateAfterEvent()"
    }

//##protect##"instance$methods"
    // AS3 ctor of Event class
    void MouseEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<InteractiveObject, Mem_Stat>(prcc, RelatedObj, op SF_DEBUG_ARG(*this));
    }
    void MouseEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            Value::Number v;
            argv[3].Convert2Number(v).DoNotCheck();
            LocalX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 5)
        {
            Value::Number v;
            argv[4].Convert2Number(v).DoNotCheck();
            LocalY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 6)
        {
            RelatedObj = NULL;
            AS3::Object* ptr = argv[5].GetObject();
            if (ptr)
            {
                if (GetVM().IsOfType(argv[5], "flash.display.InteractiveObject"))
                {
                    RelatedObj = static_cast<InteractiveObject*>(ptr);
                }
            }
        }
        if (argc >= 7)
        {
            CtrlKey = argv[6].Convert2Boolean();
        }
        if (argc >= 8)
        {
            AltKey = argv[7].Convert2Boolean();
        }
        if (argc >= 9)
        {
            ShiftKey = argv[8].Convert2Boolean();
        }
        if (argc >= 10)
        {
            if (argv[9].Convert2Boolean())
                ButtonsMask |= Button_Left;
            else
                ButtonsMask &= ~Button_Left;
        }
        if (argc >= 11)
        {
            SInt32 v;
            argv[10].Convert2Int32(v).DoNotCheck();
            Delta = v;
        }
    }
    AS3::Object* MouseEvent::GetEventClass() const 
    { 
        return static_cast<ASVM&>(GetVM()).MouseEventClass; 
    }

    SPtr<Instances::Event> MouseEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        MouseEvent* pe = static_cast<MouseEvent*>(p.GetPtr());
        pe->AltKey          = AltKey;
        pe->CtrlKey         = CtrlKey;
        pe->ShiftKey        = ShiftKey;
        pe->Delta           = Delta;
        pe->RelatedObj      = RelatedObj;
        pe->LocalX          = LocalX;
        pe->LocalY          = LocalY;
        pe->StageX          = StageX;
        pe->StageY          = StageY;
        pe->ButtonsMask     = ButtonsMask;
        pe->LocalInitialized= LocalInitialized;
        return p;
    }

    void MouseEvent::InitLocalCoords()
    {
        if (!LocalInitialized)
        {
            if (Target && GetVM().IsOfType(Value(Target), "flash.display.DisplayObject"))
            {
                Instances::DisplayObject* dobj = static_cast<Instances::DisplayObject*>(Target.GetPtr());
                SF_ASSERT(dobj->pDispObj);
                Matrix2F m = dobj->pDispObj->GetWorldMatrix();
         
                PointF p((float)StageX, (float)StageY);
                p = m.TransformByInverse(p);
                LocalX = p.x;
                LocalY = p.y;
            }
            else
            {
                LocalX = LocalY = 0;
            }
            LocalInitialized = true;
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo MouseEvent::ti[MouseEvent::ThunkInfoNum] = {
        {TFunc_Instances_MouseEvent_altKeyGet::Func, &BooleanCI, "altKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_altKeySet::Func, NULL, "altKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_buttonDownGet::Func, &BooleanCI, "buttonDown", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_buttonDownSet::Func, NULL, "buttonDown", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_clickCountGet::Func, &int_CI, "clickCount", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_commandKeyGet::Func, &BooleanCI, "commandKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_commandKeySet::Func, NULL, "commandKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_controlKeyGet::Func, &BooleanCI, "controlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_controlKeySet::Func, NULL, "controlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_ctrlKeyGet::Func, &BooleanCI, "ctrlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_ctrlKeySet::Func, NULL, "ctrlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_deltaGet::Func, &int_CI, "delta", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_deltaSet::Func, NULL, "delta", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_localXGet::Func, &NumberCI, "localX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_localXSet::Func, NULL, "localX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_localYGet::Func, &NumberCI, "localY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_localYSet::Func, NULL, "localY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_relatedObjectGet::Func, &InteractiveObjectCI, "relatedObject", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_relatedObjectSet::Func, NULL, "relatedObject", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_shiftKeyGet::Func, &BooleanCI, "shiftKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MouseEvent_stageXGet::Func, &NumberCI, "stageX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_stageYGet::Func, &NumberCI, "stageY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MouseEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MouseEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MouseEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, CT_Method, 0, 0},
    };

    MouseEvent::MouseEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::MouseEvent::MouseEvent()"
//##protect##"InstanceTraits::MouseEvent::MouseEvent()"
        SetMemSize(sizeof(Instances::MouseEvent));

    }

    Pickable<Instances::MouseEvent> MouseEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::MouseEvent>(new(t.Alloc()) Instances::MouseEvent(t));
    }

    void MouseEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    MouseEvent::MouseEvent(ClassTraits::Traits& t)
    : Class(t)
    , CLICK("click")
    , CONTEXT_MENU("contextMenu")
    , DOUBLE_CLICK("doubleClick")
    , MIDDLE_CLICK("middleClick")
    , MIDDLE_MOUSE_DOWN("middleMouseDown")
    , MIDDLE_MOUSE_UP("middleMouseUp")
    , MOUSE_DOWN("mouseDown")
    , MOUSE_MOVE("mouseMove")
    , MOUSE_OUT("mouseOut")
    , MOUSE_OVER("mouseOver")
    , MOUSE_UP("mouseUp")
    , MOUSE_WHEEL("mouseWheel")
    , RIGHT_CLICK("rightClick")
    , RIGHT_MOUSE_DOWN("rightMouseDown")
    , RIGHT_MOUSE_UP("rightMouseUp")
    , ROLL_OUT("rollOut")
    , ROLL_OVER("rollOver")
    {
//##protect##"class_::MouseEvent::MouseEvent()"
//##protect##"class_::MouseEvent::MouseEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo MouseEvent::mi[MouseEvent::MemberInfoNum] = {
        {"CLICK", OFFSETOF(Classes::MouseEvent, CLICK), SlotInfo::BT_ConstChar, 1},
        {"CONTEXT_MENU", OFFSETOF(Classes::MouseEvent, CONTEXT_MENU), SlotInfo::BT_ConstChar, 1},
        {"DOUBLE_CLICK", OFFSETOF(Classes::MouseEvent, DOUBLE_CLICK), SlotInfo::BT_ConstChar, 1},
        {"MIDDLE_CLICK", OFFSETOF(Classes::MouseEvent, MIDDLE_CLICK), SlotInfo::BT_ConstChar, 1},
        {"MIDDLE_MOUSE_DOWN", OFFSETOF(Classes::MouseEvent, MIDDLE_MOUSE_DOWN), SlotInfo::BT_ConstChar, 1},
        {"MIDDLE_MOUSE_UP", OFFSETOF(Classes::MouseEvent, MIDDLE_MOUSE_UP), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_DOWN", OFFSETOF(Classes::MouseEvent, MOUSE_DOWN), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_MOVE", OFFSETOF(Classes::MouseEvent, MOUSE_MOVE), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_OUT", OFFSETOF(Classes::MouseEvent, MOUSE_OUT), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_OVER", OFFSETOF(Classes::MouseEvent, MOUSE_OVER), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_UP", OFFSETOF(Classes::MouseEvent, MOUSE_UP), SlotInfo::BT_ConstChar, 1},
        {"MOUSE_WHEEL", OFFSETOF(Classes::MouseEvent, MOUSE_WHEEL), SlotInfo::BT_ConstChar, 1},
        {"RIGHT_CLICK", OFFSETOF(Classes::MouseEvent, RIGHT_CLICK), SlotInfo::BT_ConstChar, 1},
        {"RIGHT_MOUSE_DOWN", OFFSETOF(Classes::MouseEvent, RIGHT_MOUSE_DOWN), SlotInfo::BT_ConstChar, 1},
        {"RIGHT_MOUSE_UP", OFFSETOF(Classes::MouseEvent, RIGHT_MOUSE_UP), SlotInfo::BT_ConstChar, 1},
        {"ROLL_OUT", OFFSETOF(Classes::MouseEvent, ROLL_OUT), SlotInfo::BT_ConstChar, 1},
        {"ROLL_OVER", OFFSETOF(Classes::MouseEvent, ROLL_OVER), SlotInfo::BT_ConstChar, 1},
    };

    MouseEvent::MouseEvent(VM& vm)
    : Traits(vm, MouseEventCI)
    {
//##protect##"ClassTraits::MouseEvent::MouseEvent()"
//##protect##"ClassTraits::MouseEvent::MouseEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::MouseEvent(vm, MouseEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::MouseEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MouseEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MouseEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MouseEventCI = {
    ClassInfo::CompileTime,
    "MouseEvent", "flash.events", &EventCI,
    ClassTraits::MouseEvent::MakeClassTraits,
    0,
    ClassTraits::MouseEvent::MemberInfoNum,
    InstanceTraits::MouseEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::MouseEvent::mi,
    InstanceTraits::MouseEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

