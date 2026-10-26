//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TouchEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_TouchEvent_H
#define INC_AS3_Obj_Events_TouchEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TouchEvent;
}

namespace InstanceTraits
{
    class TouchEvent;
}

namespace Classes
{
    class TouchEvent;
}

namespace Instances
{
    class TouchEvent : public Instances::Event
    {
        friend class InstanceTraits::TouchEvent;
        
    public:
        typedef TouchEvent SelfType;
        typedef Classes::TouchEvent ClassType;
        typedef InstanceTraits::TouchEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TouchEvent"; }
#endif
    protected:
        TouchEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
        void InitLocalCoords();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_altKeyGet, 
            mid_altKeySet, 
            mid_commandKeyGet, 
            mid_commandKeySet, 
            mid_controlKeyGet, 
            mid_controlKeySet, 
            mid_ctrlKeyGet, 
            mid_ctrlKeySet, 
            mid_isPrimaryTouchPointGet, 
            mid_isPrimaryTouchPointSet, 
            mid_isRelatedObjectInaccessibleGet, 
            mid_isRelatedObjectInaccessibleSet, 
            mid_localXGet, 
            mid_localXSet, 
            mid_localYGet, 
            mid_localYSet, 
            mid_pressureGet, 
            mid_pressureSet, 
            mid_relatedObjectGet, 
            mid_relatedObjectSet, 
            mid_shiftKeyGet, 
            mid_shiftKeySet, 
            mid_sizeXGet, 
            mid_sizeXSet, 
            mid_sizeYGet, 
            mid_sizeYSet, 
            mid_stageXGet, 
            mid_stageYGet, 
            mid_touchPointIDGet, 
            mid_touchPointIDSet, 
            mid_clone, 
            mid_toString, 
            mid_updateAfterEvent, 
        };
        void altKeyGet(bool& result);
        void altKeySet(Value& result, bool value);
        void commandKeyGet(bool& result);
        void commandKeySet(Value& result, bool value);
        void controlKeyGet(bool& result);
        void controlKeySet(Value& result, bool value);
        void ctrlKeyGet(bool& result);
        void ctrlKeySet(Value& result, bool value);
        void isPrimaryTouchPointGet(bool& result);
        void isPrimaryTouchPointSet(Value& result, bool value);
        void isRelatedObjectInaccessibleGet(bool& result);
        void isRelatedObjectInaccessibleSet(Value& result, bool value);
        void localXGet(Value::Number& result);
        void localXSet(Value& result, Value::Number value);
        void localYGet(Value::Number& result);
        void localYSet(Value& result, Value::Number value);
        void pressureGet(Value::Number& result);
        void pressureSet(Value& result, Value::Number value);
        void relatedObjectGet(Value& result);
        void relatedObjectSet(Value& result, Instances::InteractiveObject* value);
        void shiftKeyGet(bool& result);
        void shiftKeySet(Value& result, bool value);
        void sizeXGet(Value::Number& result);
        void sizeXSet(Value& result, Value::Number value);
        void sizeYGet(Value::Number& result);
        void sizeYSet(Value& result, Value::Number value);
        void stageXGet(Value::Number& result);
        void stageYGet(Value::Number& result);
        void touchPointIDGet(SInt32& result);
        void touchPointIDSet(Value& result, SInt32 value);
        void clone(Value& result);
        void toString(ASString& result);
        void updateAfterEvent(Value& result);

//##protect##"instance$data"
    public:
        bool            AltKey, CtrlKey, ShiftKey, CommandKey, ControlKey;
        SPtr<Instances::InteractiveObject> RelatedObj;
        Value::Number   LocalX, LocalY;
        Value::Number   SizeX, SizeY;
        Value::Number   StageX, StageY;
        Value::Number   Pressure;
        SInt32          TouchPointID;
        bool            PrimaryPoint;
        bool            LocalInitialized;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TouchEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TouchEvent"; }
#endif
    public:
        TouchEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TouchEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 33 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TouchEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TouchEvent"; }
#endif
    public:
        typedef Classes::TouchEvent ClassType;

    public:
        TouchEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TouchEvent : public Class
    {
        friend class ClassTraits::TouchEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TouchEvent"; }
#endif
    public:
        typedef TouchEvent SelfType;
        typedef TouchEvent ClassType;
        
    private:
        TouchEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_TOUCH_BEGIN() const { return TOUCH_BEGIN; }
        const char* get_TOUCH_END() const { return TOUCH_END; }
        const char* get_TOUCH_MOVE() const { return TOUCH_MOVE; }
        const char* get_TOUCH_OUT() const { return TOUCH_OUT; }
        const char* get_TOUCH_OVER() const { return TOUCH_OVER; }
        const char* get_TOUCH_ROLL_OUT() const { return TOUCH_ROLL_OUT; }
        const char* get_TOUCH_ROLL_OVER() const { return TOUCH_ROLL_OVER; }
        const char* get_TOUCH_TAP() const { return TOUCH_TAP; }


    protected:
        // AS3 API members.
        const char* TOUCH_BEGIN;
        const char* TOUCH_END;
        const char* TOUCH_MOVE;
        const char* TOUCH_OUT;
        const char* TOUCH_OVER;
        const char* TOUCH_ROLL_OUT;
        const char* TOUCH_ROLL_OVER;
        const char* TOUCH_TAP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

