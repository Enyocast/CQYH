//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_MouseEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_MouseEvent_H
#define INC_AS3_Obj_Events_MouseEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class InteractiveObject;
}
#ifdef DOUBLE_CLICK
#undef DOUBLE_CLICK
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MouseEvent;
}

namespace InstanceTraits
{
    class MouseEvent;
}

namespace Classes
{
    class MouseEvent;
}

namespace Instances
{
    class MouseEvent : public Instances::Event
    {
        friend class InstanceTraits::MouseEvent;
        
    public:
        typedef MouseEvent SelfType;
        typedef Classes::MouseEvent ClassType;
        typedef InstanceTraits::MouseEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::MouseEvent"; }
#endif
    protected:
        MouseEvent(InstanceTraits::Traits& t);

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
            mid_buttonDownGet, 
            mid_buttonDownSet, 
            mid_clickCountGet, 
            mid_commandKeyGet, 
            mid_commandKeySet, 
            mid_controlKeyGet, 
            mid_controlKeySet, 
            mid_ctrlKeyGet, 
            mid_ctrlKeySet, 
            mid_deltaGet, 
            mid_deltaSet, 
            mid_localXGet, 
            mid_localXSet, 
            mid_localYGet, 
            mid_localYSet, 
            mid_relatedObjectGet, 
            mid_relatedObjectSet, 
            mid_shiftKeyGet, 
            mid_shiftKeySet, 
            mid_stageXGet, 
            mid_stageYGet, 
            mid_clone, 
            mid_toString, 
            mid_updateAfterEvent, 
        };
        void altKeyGet(bool& result);
        void altKeySet(Value& result, bool value);
        void buttonDownGet(bool& result);
        void buttonDownSet(Value& result, bool value);
        void clickCountGet(SInt32& result);
        void commandKeyGet(bool& result);
        void commandKeySet(Value& result, bool value);
        void controlKeyGet(bool& result);
        void controlKeySet(Value& result, bool value);
        void ctrlKeyGet(bool& result);
        void ctrlKeySet(Value& result, bool value);
        void deltaGet(SInt32& result);
        void deltaSet(Value& result, SInt32 value);
        void localXGet(Value::Number& result);
        void localXSet(Value& result, Value::Number value);
        void localYGet(Value::Number& result);
        void localYSet(Value& result, Value::Number value);
        void relatedObjectGet(Value& result);
        void relatedObjectSet(Value& result, Instances::InteractiveObject* value);
        void shiftKeyGet(bool& result);
        void shiftKeySet(Value& result, bool value);
        void stageXGet(Value::Number& result);
        void stageYGet(Value::Number& result);
        void clone(Value& result);
        void toString(ASString& result);
        void updateAfterEvent(Value& result);

//##protect##"instance$data"
    public:
        bool            AltKey, CtrlKey, ShiftKey;
        int             Delta;
        SPtr<Instances::InteractiveObject> RelatedObj;
        Value::Number   LocalX, LocalY;
        Value::Number   StageX, StageY;
        enum
        {
            Button_Left     = 0x1,
            Button_Right    = 0x2,
            Button_Middle   = 0x4
        };
        unsigned        ButtonsMask; // bit 0 - left, bit 1 - right, bit 2 - middle, etc
        bool            LocalInitialized;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class MouseEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::MouseEvent"; }
#endif
    public:
        MouseEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::MouseEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 26 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class MouseEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MouseEvent"; }
#endif
    public:
        typedef Classes::MouseEvent ClassType;

    public:
        MouseEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 17 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class MouseEvent : public Class
    {
        friend class ClassTraits::MouseEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::MouseEvent"; }
#endif
    public:
        typedef MouseEvent SelfType;
        typedef MouseEvent ClassType;
        
    private:
        MouseEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CLICK() const { return CLICK; }
        const char* get_CONTEXT_MENU() const { return CONTEXT_MENU; }
        const char* get_DOUBLE_CLICK() const { return DOUBLE_CLICK; }
        const char* get_MIDDLE_CLICK() const { return MIDDLE_CLICK; }
        const char* get_MIDDLE_MOUSE_DOWN() const { return MIDDLE_MOUSE_DOWN; }
        const char* get_MIDDLE_MOUSE_UP() const { return MIDDLE_MOUSE_UP; }
        const char* get_MOUSE_DOWN() const { return MOUSE_DOWN; }
        const char* get_MOUSE_MOVE() const { return MOUSE_MOVE; }
        const char* get_MOUSE_OUT() const { return MOUSE_OUT; }
        const char* get_MOUSE_OVER() const { return MOUSE_OVER; }
        const char* get_MOUSE_UP() const { return MOUSE_UP; }
        const char* get_MOUSE_WHEEL() const { return MOUSE_WHEEL; }
        const char* get_RIGHT_CLICK() const { return RIGHT_CLICK; }
        const char* get_RIGHT_MOUSE_DOWN() const { return RIGHT_MOUSE_DOWN; }
        const char* get_RIGHT_MOUSE_UP() const { return RIGHT_MOUSE_UP; }
        const char* get_ROLL_OUT() const { return ROLL_OUT; }
        const char* get_ROLL_OVER() const { return ROLL_OVER; }


    protected:
        // AS3 API members.
        const char* CLICK;
        const char* CONTEXT_MENU;
        const char* DOUBLE_CLICK;
        const char* MIDDLE_CLICK;
        const char* MIDDLE_MOUSE_DOWN;
        const char* MIDDLE_MOUSE_UP;
        const char* MOUSE_DOWN;
        const char* MOUSE_MOVE;
        const char* MOUSE_OUT;
        const char* MOUSE_OVER;
        const char* MOUSE_UP;
        const char* MOUSE_WHEEL;
        const char* RIGHT_CLICK;
        const char* RIGHT_MOUSE_DOWN;
        const char* RIGHT_MOUSE_UP;
        const char* ROLL_OUT;
        const char* ROLL_OVER;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

