//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_PressAndTapGestureEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_PressAndTapGestureEvent_H
#define INC_AS3_Obj_Events_PressAndTapGestureEvent_H

#include "AS3_Obj_Events_GestureEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class PressAndTapGestureEvent;
}

namespace InstanceTraits
{
    class PressAndTapGestureEvent;
}

namespace Classes
{
    class PressAndTapGestureEvent;
}

namespace Instances
{
    class PressAndTapGestureEvent : public Instances::GestureEvent
    {
        friend class InstanceTraits::PressAndTapGestureEvent;
        
    public:
        typedef PressAndTapGestureEvent SelfType;
        typedef Classes::PressAndTapGestureEvent ClassType;
        typedef InstanceTraits::PressAndTapGestureEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::PressAndTapGestureEvent"; }
#endif
    protected:
        PressAndTapGestureEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
        void InitLocalCoords();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_tapLocalXGet, 
            mid_tapLocalXSet, 
            mid_tapLocalYGet, 
            mid_tapLocalYSet, 
            mid_tapStageXGet, 
            mid_tapStageYGet, 
            mid_clone, 
            mid_toString, 
        };
        void tapLocalXGet(Value::Number& result);
        void tapLocalXSet(Value& result, Value::Number value);
        void tapLocalYGet(Value::Number& result);
        void tapLocalYSet(Value& result, Value::Number value);
        void tapStageXGet(Value::Number& result);
        void tapStageYGet(Value::Number& result);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        Value::Number   TapLocalX, TapLocalY;
        Value::Number   TapStageX, TapStageY;
        bool            LocalInitialized;
		bool			TapStageSet;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class PressAndTapGestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::PressAndTapGestureEvent"; }
#endif
    public:
        PressAndTapGestureEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::PressAndTapGestureEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 8 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class PressAndTapGestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::PressAndTapGestureEvent"; }
#endif
    public:
        typedef Classes::PressAndTapGestureEvent ClassType;

    public:
        PressAndTapGestureEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class PressAndTapGestureEvent : public Class
    {
        friend class ClassTraits::PressAndTapGestureEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::PressAndTapGestureEvent"; }
#endif
    public:
        typedef PressAndTapGestureEvent SelfType;
        typedef PressAndTapGestureEvent ClassType;
        
    private:
        PressAndTapGestureEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_GESTURE_PRESS_AND_TAP() const { return GESTURE_PRESS_AND_TAP; }


    protected:
        // AS3 API members.
        const char* GESTURE_PRESS_AND_TAP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

