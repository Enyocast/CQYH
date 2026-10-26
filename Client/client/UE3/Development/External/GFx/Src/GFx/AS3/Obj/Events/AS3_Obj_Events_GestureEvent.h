//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_GestureEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_GestureEvent_H
#define INC_AS3_Obj_Events_GestureEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class GestureEvent;
}

namespace InstanceTraits
{
    class GestureEvent;
}

namespace Classes
{
    class GestureEvent;
}

namespace Instances
{
    class GestureEvent : public Instances::Event
    {
        friend class InstanceTraits::GestureEvent;
        
    public:
        typedef GestureEvent SelfType;
        typedef Classes::GestureEvent ClassType;
        typedef InstanceTraits::GestureEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GestureEvent"; }
#endif
    protected:
        GestureEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        enum PhaseType
        {
            Phase_Null,
            Phase_All,
            Phase_Begin,
            Phase_End,
            Phase_Update,

            Phase_Count
        };

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
            mid_localXGet, 
            mid_localXSet, 
            mid_localYGet, 
            mid_localYSet, 
            mid_phaseGet, 
            mid_phaseSet, 
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
        void commandKeyGet(bool& result);
        void commandKeySet(Value& result, bool value);
        void controlKeyGet(bool& result);
        void controlKeySet(Value& result, bool value);
        void ctrlKeyGet(bool& result);
        void ctrlKeySet(Value& result, bool value);
        void localXGet(Value::Number& result);
        void localXSet(Value& result, Value::Number value);
        void localYGet(Value::Number& result);
        void localYSet(Value& result, Value::Number value);
        void phaseGet(Value& result);
        void phaseSet(Value& result, const Value& value);
        void shiftKeyGet(bool& result);
        void shiftKeySet(Value& result, bool value);
        void stageXGet(Value::Number& result);
        void stageYGet(Value::Number& result);
        void clone(Value& result);
        void toString(ASString& result);
        void updateAfterEvent(Value& result);

//##protect##"instance$data"
        bool            AltKey, CtrlKey, ShiftKey, CommandKey, ControlKey;
        Value::Number   LocalX, LocalY;
        Value::Number   StageX, StageY;
        PhaseType       Phase;           
        bool            LocalInitialized;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class GestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::GestureEvent"; }
#endif
    public:
        GestureEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::GestureEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 21 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class GestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GestureEvent"; }
#endif
    public:
        typedef Classes::GestureEvent ClassType;

    public:
        GestureEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class GestureEvent : public Class
    {
        friend class ClassTraits::GestureEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::GestureEvent"; }
#endif
    public:
        typedef GestureEvent SelfType;
        typedef GestureEvent ClassType;
        
    private:
        GestureEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_GESTURE_TWO_FINGER_TAP() const { return GESTURE_TWO_FINGER_TAP; }


    protected:
        // AS3 API members.
        const char* GESTURE_TWO_FINGER_TAP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

