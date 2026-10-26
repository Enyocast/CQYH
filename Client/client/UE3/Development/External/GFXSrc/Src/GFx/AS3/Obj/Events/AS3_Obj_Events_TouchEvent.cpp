//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TouchEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_TouchEvent.h"
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
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_altKeyGet, bool> TFunc_Instances_TouchEvent_altKeyGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_altKeySet, Value, bool> TFunc_Instances_TouchEvent_altKeySet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_commandKeyGet, bool> TFunc_Instances_TouchEvent_commandKeyGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_commandKeySet, Value, bool> TFunc_Instances_TouchEvent_commandKeySet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_controlKeyGet, bool> TFunc_Instances_TouchEvent_controlKeyGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_controlKeySet, Value, bool> TFunc_Instances_TouchEvent_controlKeySet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_ctrlKeyGet, bool> TFunc_Instances_TouchEvent_ctrlKeyGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_ctrlKeySet, Value, bool> TFunc_Instances_TouchEvent_ctrlKeySet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_isPrimaryTouchPointGet, bool> TFunc_Instances_TouchEvent_isPrimaryTouchPointGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_isPrimaryTouchPointSet, Value, bool> TFunc_Instances_TouchEvent_isPrimaryTouchPointSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_isRelatedObjectInaccessibleGet, bool> TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_isRelatedObjectInaccessibleSet, Value, bool> TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_localXGet, Value::Number> TFunc_Instances_TouchEvent_localXGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_localXSet, Value, Value::Number> TFunc_Instances_TouchEvent_localXSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_localYGet, Value::Number> TFunc_Instances_TouchEvent_localYGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_localYSet, Value, Value::Number> TFunc_Instances_TouchEvent_localYSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_pressureGet, Value::Number> TFunc_Instances_TouchEvent_pressureGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_pressureSet, Value, Value::Number> TFunc_Instances_TouchEvent_pressureSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_relatedObjectGet, Value> TFunc_Instances_TouchEvent_relatedObjectGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_relatedObjectSet, Value, Instances::InteractiveObject*> TFunc_Instances_TouchEvent_relatedObjectSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_shiftKeyGet, bool> TFunc_Instances_TouchEvent_shiftKeyGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_shiftKeySet, Value, bool> TFunc_Instances_TouchEvent_shiftKeySet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_sizeXGet, Value::Number> TFunc_Instances_TouchEvent_sizeXGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_sizeXSet, Value, Value::Number> TFunc_Instances_TouchEvent_sizeXSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_sizeYGet, Value::Number> TFunc_Instances_TouchEvent_sizeYGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_sizeYSet, Value, Value::Number> TFunc_Instances_TouchEvent_sizeYSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_stageXGet, Value::Number> TFunc_Instances_TouchEvent_stageXGet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_stageYGet, Value::Number> TFunc_Instances_TouchEvent_stageYGet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_touchPointIDGet, SInt32> TFunc_Instances_TouchEvent_touchPointIDGet;
typedef ThunkFunc1<Instances::TouchEvent, Instances::TouchEvent::mid_touchPointIDSet, Value, SInt32> TFunc_Instances_TouchEvent_touchPointIDSet;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_clone, Value> TFunc_Instances_TouchEvent_clone;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_toString, ASString> TFunc_Instances_TouchEvent_toString;
typedef ThunkFunc0<Instances::TouchEvent, Instances::TouchEvent::mid_updateAfterEvent, Value> TFunc_Instances_TouchEvent_updateAfterEvent;

template <> const TFunc_Instances_TouchEvent_altKeyGet::TMethod TFunc_Instances_TouchEvent_altKeyGet::Method = &Instances::TouchEvent::altKeyGet;
template <> const TFunc_Instances_TouchEvent_altKeySet::TMethod TFunc_Instances_TouchEvent_altKeySet::Method = &Instances::TouchEvent::altKeySet;
template <> const TFunc_Instances_TouchEvent_commandKeyGet::TMethod TFunc_Instances_TouchEvent_commandKeyGet::Method = &Instances::TouchEvent::commandKeyGet;
template <> const TFunc_Instances_TouchEvent_commandKeySet::TMethod TFunc_Instances_TouchEvent_commandKeySet::Method = &Instances::TouchEvent::commandKeySet;
template <> const TFunc_Instances_TouchEvent_controlKeyGet::TMethod TFunc_Instances_TouchEvent_controlKeyGet::Method = &Instances::TouchEvent::controlKeyGet;
template <> const TFunc_Instances_TouchEvent_controlKeySet::TMethod TFunc_Instances_TouchEvent_controlKeySet::Method = &Instances::TouchEvent::controlKeySet;
template <> const TFunc_Instances_TouchEvent_ctrlKeyGet::TMethod TFunc_Instances_TouchEvent_ctrlKeyGet::Method = &Instances::TouchEvent::ctrlKeyGet;
template <> const TFunc_Instances_TouchEvent_ctrlKeySet::TMethod TFunc_Instances_TouchEvent_ctrlKeySet::Method = &Instances::TouchEvent::ctrlKeySet;
template <> const TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::TMethod TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::Method = &Instances::TouchEvent::isPrimaryTouchPointGet;
template <> const TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::TMethod TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::Method = &Instances::TouchEvent::isPrimaryTouchPointSet;
template <> const TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::TMethod TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::Method = &Instances::TouchEvent::isRelatedObjectInaccessibleGet;
template <> const TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::TMethod TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::Method = &Instances::TouchEvent::isRelatedObjectInaccessibleSet;
template <> const TFunc_Instances_TouchEvent_localXGet::TMethod TFunc_Instances_TouchEvent_localXGet::Method = &Instances::TouchEvent::localXGet;
template <> const TFunc_Instances_TouchEvent_localXSet::TMethod TFunc_Instances_TouchEvent_localXSet::Method = &Instances::TouchEvent::localXSet;
template <> const TFunc_Instances_TouchEvent_localYGet::TMethod TFunc_Instances_TouchEvent_localYGet::Method = &Instances::TouchEvent::localYGet;
template <> const TFunc_Instances_TouchEvent_localYSet::TMethod TFunc_Instances_TouchEvent_localYSet::Method = &Instances::TouchEvent::localYSet;
template <> const TFunc_Instances_TouchEvent_pressureGet::TMethod TFunc_Instances_TouchEvent_pressureGet::Method = &Instances::TouchEvent::pressureGet;
template <> const TFunc_Instances_TouchEvent_pressureSet::TMethod TFunc_Instances_TouchEvent_pressureSet::Method = &Instances::TouchEvent::pressureSet;
template <> const TFunc_Instances_TouchEvent_relatedObjectGet::TMethod TFunc_Instances_TouchEvent_relatedObjectGet::Method = &Instances::TouchEvent::relatedObjectGet;
template <> const TFunc_Instances_TouchEvent_relatedObjectSet::TMethod TFunc_Instances_TouchEvent_relatedObjectSet::Method = &Instances::TouchEvent::relatedObjectSet;
template <> const TFunc_Instances_TouchEvent_shiftKeyGet::TMethod TFunc_Instances_TouchEvent_shiftKeyGet::Method = &Instances::TouchEvent::shiftKeyGet;
template <> const TFunc_Instances_TouchEvent_shiftKeySet::TMethod TFunc_Instances_TouchEvent_shiftKeySet::Method = &Instances::TouchEvent::shiftKeySet;
template <> const TFunc_Instances_TouchEvent_sizeXGet::TMethod TFunc_Instances_TouchEvent_sizeXGet::Method = &Instances::TouchEvent::sizeXGet;
template <> const TFunc_Instances_TouchEvent_sizeXSet::TMethod TFunc_Instances_TouchEvent_sizeXSet::Method = &Instances::TouchEvent::sizeXSet;
template <> const TFunc_Instances_TouchEvent_sizeYGet::TMethod TFunc_Instances_TouchEvent_sizeYGet::Method = &Instances::TouchEvent::sizeYGet;
template <> const TFunc_Instances_TouchEvent_sizeYSet::TMethod TFunc_Instances_TouchEvent_sizeYSet::Method = &Instances::TouchEvent::sizeYSet;
template <> const TFunc_Instances_TouchEvent_stageXGet::TMethod TFunc_Instances_TouchEvent_stageXGet::Method = &Instances::TouchEvent::stageXGet;
template <> const TFunc_Instances_TouchEvent_stageYGet::TMethod TFunc_Instances_TouchEvent_stageYGet::Method = &Instances::TouchEvent::stageYGet;
template <> const TFunc_Instances_TouchEvent_touchPointIDGet::TMethod TFunc_Instances_TouchEvent_touchPointIDGet::Method = &Instances::TouchEvent::touchPointIDGet;
template <> const TFunc_Instances_TouchEvent_touchPointIDSet::TMethod TFunc_Instances_TouchEvent_touchPointIDSet::Method = &Instances::TouchEvent::touchPointIDSet;
template <> const TFunc_Instances_TouchEvent_clone::TMethod TFunc_Instances_TouchEvent_clone::Method = &Instances::TouchEvent::clone;
template <> const TFunc_Instances_TouchEvent_toString::TMethod TFunc_Instances_TouchEvent_toString::Method = &Instances::TouchEvent::toString;
template <> const TFunc_Instances_TouchEvent_updateAfterEvent::TMethod TFunc_Instances_TouchEvent_updateAfterEvent::Method = &Instances::TouchEvent::updateAfterEvent;

namespace Instances
{
    TouchEvent::TouchEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
//##protect##"instance::TouchEvent::TouchEvent()$data"
//##protect##"instance::TouchEvent::TouchEvent()$data"
    {
//##protect##"instance::TouchEvent::TouchEvent()$code"
        AltKey = CtrlKey    = ShiftKey = CommandKey = ControlKey = false;
        SizeX = SizeY       = 0;
        LocalX = LocalY     = 0;
        StageX = StageY     = 0;
        Pressure            = 1.0;
        TouchPointID        = 0;
        PrimaryPoint        = false;
        LocalInitialized    = false;
//##protect##"instance::TouchEvent::TouchEvent()$code"
    }

    void TouchEvent::altKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::altKeyGet()"
        SF_UNUSED1(result);
        result = AltKey;
//##protect##"instance::TouchEvent::altKeyGet()"
    }
    void TouchEvent::altKeySet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::altKeySet()"
        SF_UNUSED2(result, value);
        AltKey = value;
//##protect##"instance::TouchEvent::altKeySet()"
    }
    void TouchEvent::commandKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::commandKeyGet()"
        SF_UNUSED1(result);
        result = CommandKey;
//##protect##"instance::TouchEvent::commandKeyGet()"
    }
    void TouchEvent::commandKeySet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::commandKeySet()"
        SF_UNUSED2(result, value);
        CommandKey = value;
//##protect##"instance::TouchEvent::commandKeySet()"
    }
    void TouchEvent::controlKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::controlKeyGet()"
        SF_UNUSED1(result);
        result = ControlKey;
//##protect##"instance::TouchEvent::controlKeyGet()"
    }
    void TouchEvent::controlKeySet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::controlKeySet()"
        SF_UNUSED2(result, value);
        ControlKey = value;
//##protect##"instance::TouchEvent::controlKeySet()"
    }
    void TouchEvent::ctrlKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::ctrlKeyGet()"
        SF_UNUSED1(result);
        result = CtrlKey;
//##protect##"instance::TouchEvent::ctrlKeyGet()"
    }
    void TouchEvent::ctrlKeySet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::ctrlKeySet()"
        SF_UNUSED2(result, value);
        CtrlKey = value;
//##protect##"instance::TouchEvent::ctrlKeySet()"
    }
    void TouchEvent::isPrimaryTouchPointGet(bool& result)
    {
//##protect##"instance::TouchEvent::isPrimaryTouchPointGet()"
        SF_UNUSED1(result);
        result = PrimaryPoint;
//##protect##"instance::TouchEvent::isPrimaryTouchPointGet()"
    }
    void TouchEvent::isPrimaryTouchPointSet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::isPrimaryTouchPointSet()"
        SF_UNUSED2(result, value);
        PrimaryPoint = value;
//##protect##"instance::TouchEvent::isPrimaryTouchPointSet()"
    }
    void TouchEvent::isRelatedObjectInaccessibleGet(bool& result)
    {
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleGet()"
        SF_UNUSED1(result);
        result = false;
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleGet()"
    }
    void TouchEvent::isRelatedObjectInaccessibleSet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleSet()"
        SF_UNUSED2(result, value);
        //WARN_NOT_IMPLEMENTED("instance::TouchEvent::isRelatedObjectInaccessibleSet()");
//##protect##"instance::TouchEvent::isRelatedObjectInaccessibleSet()"
    }
    void TouchEvent::localXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::localXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalX);
//##protect##"instance::TouchEvent::localXGet()"
    }
    void TouchEvent::localXSet(Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::localXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalX = PixelsToTwips(value);
//##protect##"instance::TouchEvent::localXSet()"
    }
    void TouchEvent::localYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::localYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(LocalY);
//##protect##"instance::TouchEvent::localYGet()"
    }
    void TouchEvent::localYSet(Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::localYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        LocalY = PixelsToTwips(value);
//##protect##"instance::TouchEvent::localYSet()"
    }
    void TouchEvent::pressureGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::pressureGet()"
        SF_UNUSED1(result);
        result = Pressure;
//##protect##"instance::TouchEvent::pressureGet()"
    }
    void TouchEvent::pressureSet(Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::pressureSet()"
        SF_UNUSED2(result, value);
        Pressure = value;
//##protect##"instance::TouchEvent::pressureSet()"
    }
    void TouchEvent::relatedObjectGet(Value& result)
    {
//##protect##"instance::TouchEvent::relatedObjectGet()"
        SF_UNUSED1(result);
        result = Value(RelatedObj);
//##protect##"instance::TouchEvent::relatedObjectGet()"
    }
    void TouchEvent::relatedObjectSet(Value& result, Instances::InteractiveObject* value)
    {
//##protect##"instance::TouchEvent::relatedObjectSet()"
        SF_UNUSED2(result, value);
        RelatedObj = value;
//##protect##"instance::TouchEvent::relatedObjectSet()"
    }
    void TouchEvent::shiftKeyGet(bool& result)
    {
//##protect##"instance::TouchEvent::shiftKeyGet()"
        SF_UNUSED1(result);
        result = ShiftKey;
//##protect##"instance::TouchEvent::shiftKeyGet()"
    }
    void TouchEvent::shiftKeySet(Value& result, bool value)
    {
//##protect##"instance::TouchEvent::shiftKeySet()"
        SF_UNUSED2(result, value);
        ShiftKey = value;
//##protect##"instance::TouchEvent::shiftKeySet()"
    }
    void TouchEvent::sizeXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::sizeXGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(SizeX);
//##protect##"instance::TouchEvent::sizeXGet()"
    }
    void TouchEvent::sizeXSet(Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::sizeXSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        SizeX = PixelsToTwips(value);
//##protect##"instance::TouchEvent::sizeXSet()"
    }
    void TouchEvent::sizeYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::sizeYGet()"
        SF_UNUSED1(result);
        InitLocalCoords();
        result = TwipsToPixels(SizeY);
//##protect##"instance::TouchEvent::sizeYGet()"
    }
    void TouchEvent::sizeYSet(Value& result, Value::Number value)
    {
//##protect##"instance::TouchEvent::sizeYSet()"
        SF_UNUSED2(result, value);
        InitLocalCoords();
        SizeY = PixelsToTwips(value);
//##protect##"instance::TouchEvent::sizeYSet()"
    }
    void TouchEvent::stageXGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::stageXGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageX);
//##protect##"instance::TouchEvent::stageXGet()"
    }
    void TouchEvent::stageYGet(Value::Number& result)
    {
//##protect##"instance::TouchEvent::stageYGet()"
        SF_UNUSED1(result);
        result = TwipsToPixels(StageY);
//##protect##"instance::TouchEvent::stageYGet()"
    }
    void TouchEvent::touchPointIDGet(SInt32& result)
    {
//##protect##"instance::TouchEvent::touchPointIDGet()"
        SF_UNUSED1(result);
        result = TouchPointID;
//##protect##"instance::TouchEvent::touchPointIDGet()"
    }
    void TouchEvent::touchPointIDSet(Value& result, SInt32 value)
    {
//##protect##"instance::TouchEvent::touchPointIDSet()"
        SF_UNUSED2(result, value);
        TouchPointID = value;
//##protect##"instance::TouchEvent::touchPointIDSet()"
    }
    void TouchEvent::clone(Value& result)
    {
//##protect##"instance::TouchEvent::clone()"
        SF_UNUSED1(result);
        result = Clone().GetPtr();
//##protect##"instance::TouchEvent::clone()"
    }
    void TouchEvent::toString(ASString& result)
    {
//##protect##"instance::TouchEvent::toString()"
        SF_UNUSED1(result);
        //example: [TouchEvent type="touchTap" bubbles=true cancelable=false eventPhase=2 touchPointID=2 isPrimaryTouchPoint=true 
        // localX=149.25 localY=188.85 stageX=157.25 stageY=198.85 sizeX=1.4600000381469727 sizeY=0.8199999928474426 pressure=1 
        // relatedObject=null ctrlKey=false altKey=false shiftKey=false commandKey=false controlKey=false]
        Value res;
        ASVM& vm = static_cast<ASVM&>(GetVM());
        Value params[] = {
            vm.GetStringManager().CreateConstString("TouchEvent"),
            vm.GetStringManager().CreateConstString("type"),
            vm.GetStringManager().CreateConstString("bubbles"),
            vm.GetStringManager().CreateConstString("cancelable"),
            vm.GetStringManager().CreateConstString("eventPhase"),
            vm.GetStringManager().CreateConstString("touchPointID"),
            vm.GetStringManager().CreateConstString("isPrimaryTouchPoint"),
            vm.GetStringManager().CreateConstString("localX"),
            vm.GetStringManager().CreateConstString("localY"),
            vm.GetStringManager().CreateConstString("stageX"),
            vm.GetStringManager().CreateConstString("stageY"),
            vm.GetStringManager().CreateConstString("sizeX"),
            vm.GetStringManager().CreateConstString("sizeY"),
            vm.GetStringManager().CreateConstString("relatedObject"),
            vm.GetStringManager().CreateConstString("ctrlKey"),
            vm.GetStringManager().CreateConstString("altKey"),
            vm.GetStringManager().CreateConstString("shiftKey"),
            vm.GetStringManager().CreateConstString("commandKey"),
            vm.GetStringManager().CreateConstString("controlKey")
        };
        formatToString(res, sizeof(params)/sizeof(params[0]), params);
        res.Convert2String(result).DoNotCheck();
//##protect##"instance::TouchEvent::toString()"
    }
    void TouchEvent::updateAfterEvent(Value& result)
    {
//##protect##"instance::TouchEvent::updateAfterEvent()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::TouchEvent::updateAfterEvent()");
//##protect##"instance::TouchEvent::updateAfterEvent()"
    }

//##protect##"instance$methods"
    void TouchEvent::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<InteractiveObject, Mem_Stat>(prcc, RelatedObj, op SF_DEBUG_ARG(*this));
    }
    void TouchEvent::AS3Constructor(unsigned argc, const Value* argv)
    {
        Event::AS3Constructor(argc, argv);
        if (argc >= 4)
        {
            argv[3].Convert2Int32(TouchPointID).DoNotCheck();
        }
        if (argc >= 5)
        {
            PrimaryPoint = argv[4].Convert2Boolean();
        }
        if (argc >= 6)
        {
            Value::Number v;
            argv[5].Convert2Number(v).DoNotCheck();
            LocalX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 7)
        {
            Value::Number v;
            argv[6].Convert2Number(v).DoNotCheck();
            LocalY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 8)
        {
            Value::Number v;
            argv[7].Convert2Number(v).DoNotCheck();
            SizeX = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 9)
        {
            Value::Number v;
            argv[8].Convert2Number(v).DoNotCheck();
            SizeY = PixelsToTwips(v);
            LocalInitialized = true;
        }
        if (argc >= 10)
        {
            argv[9].Convert2Number(Pressure).DoNotCheck();
        }
        if (argc >= 11)
        {
            RelatedObj = NULL;
            AS3::Object* ptr = argv[5].GetObject();
            if (ptr)
            {
                if (GetVM().IsOfType(argv[10], "flash.display.InteractiveObject"))
                {
                    RelatedObj = static_cast<InteractiveObject*>(ptr);
                }
            }
        }
        if (argc >= 12)
        {
            CtrlKey = argv[11].Convert2Boolean();
        }
        if (argc >= 13)
        {
            AltKey = argv[12].Convert2Boolean();
        }
        if (argc >= 14)
        {
            ShiftKey = argv[13].Convert2Boolean();
        }
        if (argc >= 15)
        {
            CommandKey = argv[14].Convert2Boolean();
        }
        if (argc >= 16)
        {
            ControlKey = argv[15].Convert2Boolean();
        }
    }
    AS3::Object* TouchEvent::GetEventClass() const 
    { 
#if defined(GFX_MULTITOUCH_SUPPORT_ENABLE)
		return static_cast<ASVM&>(GetVM()).TouchEventClass; 
#else
		return NULL;
#endif
    }

    SPtr<Instances::Event> TouchEvent::Clone() const
    {
        SPtr<Instances::Event> p = Event::Clone();
        TouchEvent* pe = static_cast<TouchEvent*>(p.GetPtr());
        pe->AltKey          = AltKey;
        pe->CtrlKey         = CtrlKey;
        pe->ShiftKey        = ShiftKey;
        pe->CommandKey      = CommandKey;
        pe->ControlKey      = ControlKey;
        pe->Pressure        = Pressure;
        pe->RelatedObj      = RelatedObj;
        pe->LocalX          = LocalX;
        pe->LocalY          = LocalY;
        pe->StageX          = StageX;
        pe->StageY          = StageY;
        pe->SizeX           = SizeX;
        pe->SizeY           = SizeY;
        pe->TouchPointID    = TouchPointID;
        pe->PrimaryPoint    = PrimaryPoint;
        pe->LocalInitialized= LocalInitialized;
        return p;
    }

    void TouchEvent::InitLocalCoords()
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

                PointF p1((float)SizeX, (float)SizeY);
                p1 = m.TransformByInverse(p1);
                SizeX = p1.x;
                SizeY = p1.y;
            }
            else
            {
                LocalX = LocalY = SizeX = SizeY = 0;
            }
            LocalInitialized = true;
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TouchEvent::ti[TouchEvent::ThunkInfoNum] = {
        {TFunc_Instances_TouchEvent_altKeyGet::Func, &BooleanCI, "altKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_altKeySet::Func, NULL, "altKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_commandKeyGet::Func, &BooleanCI, "commandKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_commandKeySet::Func, NULL, "commandKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_controlKeyGet::Func, &BooleanCI, "controlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_controlKeySet::Func, NULL, "controlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_ctrlKeyGet::Func, &BooleanCI, "ctrlKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_ctrlKeySet::Func, NULL, "ctrlKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_isPrimaryTouchPointGet::Func, &BooleanCI, "isPrimaryTouchPoint", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_isPrimaryTouchPointSet::Func, NULL, "isPrimaryTouchPoint", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleGet::Func, &BooleanCI, "isRelatedObjectInaccessible", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_isRelatedObjectInaccessibleSet::Func, NULL, "isRelatedObjectInaccessible", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_localXGet::Func, &NumberCI, "localX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_localXSet::Func, NULL, "localX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_localYGet::Func, &NumberCI, "localY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_localYSet::Func, NULL, "localY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_pressureGet::Func, &NumberCI, "pressure", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_pressureSet::Func, NULL, "pressure", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_relatedObjectGet::Func, &InteractiveObjectCI, "relatedObject", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_relatedObjectSet::Func, NULL, "relatedObject", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_shiftKeyGet::Func, &BooleanCI, "shiftKey", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_shiftKeySet::Func, NULL, "shiftKey", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_sizeXGet::Func, &NumberCI, "sizeX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_sizeXSet::Func, NULL, "sizeX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_sizeYGet::Func, &NumberCI, "sizeY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_sizeYSet::Func, NULL, "sizeY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_stageXGet::Func, &NumberCI, "stageX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_stageYGet::Func, &NumberCI, "stageY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_touchPointIDGet::Func, &int_CI, "touchPointID", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TouchEvent_touchPointIDSet::Func, NULL, "touchPointID", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TouchEvent_clone::Func, &EventCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_TouchEvent_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_TouchEvent_updateAfterEvent::Func, NULL, "updateAfterEvent", NULL, CT_Method, 0, 0},
    };

    TouchEvent::TouchEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TouchEvent::TouchEvent()"
//##protect##"InstanceTraits::TouchEvent::TouchEvent()"
        SetMemSize(sizeof(Instances::TouchEvent));

    }

    Pickable<Instances::TouchEvent> TouchEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TouchEvent>(new(t.Alloc()) Instances::TouchEvent(t));
    }

    void TouchEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    TouchEvent::TouchEvent(ClassTraits::Traits& t)
    : Class(t)
    , TOUCH_BEGIN("touchBegin")
    , TOUCH_END("touchEnd")
    , TOUCH_MOVE("touchMove")
    , TOUCH_OUT("touchOut")
    , TOUCH_OVER("touchOver")
    , TOUCH_ROLL_OUT("touchRollOut")
    , TOUCH_ROLL_OVER("touchRollOver")
    , TOUCH_TAP("touchTap")
    {
//##protect##"class_::TouchEvent::TouchEvent()"
//##protect##"class_::TouchEvent::TouchEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo TouchEvent::mi[TouchEvent::MemberInfoNum] = {
        {"TOUCH_BEGIN", OFFSETOF(Classes::TouchEvent, TOUCH_BEGIN), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_END", OFFSETOF(Classes::TouchEvent, TOUCH_END), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_MOVE", OFFSETOF(Classes::TouchEvent, TOUCH_MOVE), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_OUT", OFFSETOF(Classes::TouchEvent, TOUCH_OUT), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_OVER", OFFSETOF(Classes::TouchEvent, TOUCH_OVER), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_ROLL_OUT", OFFSETOF(Classes::TouchEvent, TOUCH_ROLL_OUT), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_ROLL_OVER", OFFSETOF(Classes::TouchEvent, TOUCH_ROLL_OVER), SlotInfo::BT_ConstChar, 1},
        {"TOUCH_TAP", OFFSETOF(Classes::TouchEvent, TOUCH_TAP), SlotInfo::BT_ConstChar, 1},
    };

    TouchEvent::TouchEvent(VM& vm)
    : Traits(vm, TouchEventCI)
    {
//##protect##"ClassTraits::TouchEvent::TouchEvent()"
//##protect##"ClassTraits::TouchEvent::TouchEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TouchEvent(vm, TouchEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TouchEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TouchEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TouchEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TouchEventCI = {
    ClassInfo::CompileTime,
    "TouchEvent", "flash.events", &EventCI,
    ClassTraits::TouchEvent::MakeClassTraits,
    0,
    ClassTraits::TouchEvent::MemberInfoNum,
    InstanceTraits::TouchEvent::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::TouchEvent::mi,
    InstanceTraits::TouchEvent::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

