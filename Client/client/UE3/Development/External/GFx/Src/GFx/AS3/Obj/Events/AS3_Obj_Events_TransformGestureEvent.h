//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TransformGestureEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_TransformGestureEvent_H
#define INC_AS3_Obj_Events_TransformGestureEvent_H

#include "AS3_Obj_Events_GestureEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TransformGestureEvent;
}

namespace InstanceTraits
{
    class TransformGestureEvent;
}

namespace Classes
{
    class TransformGestureEvent;
}

namespace Instances
{
    class TransformGestureEvent : public Instances::GestureEvent
    {
        friend class InstanceTraits::TransformGestureEvent;
        
    public:
        typedef TransformGestureEvent SelfType;
        typedef Classes::TransformGestureEvent ClassType;
        typedef InstanceTraits::TransformGestureEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TransformGestureEvent"; }
#endif
    protected:
        TransformGestureEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
		void InitLocalCoords();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_offsetXGet, 
            mid_offsetXSet, 
            mid_offsetYGet, 
            mid_offsetYSet, 
            mid_rotationGet, 
            mid_rotationSet, 
            mid_scaleXGet, 
            mid_scaleXSet, 
            mid_scaleYGet, 
            mid_scaleYSet, 
            mid_clone, 
            mid_toString, 
        };
        void offsetXGet(Value::Number& result);
        void offsetXSet(Value& result, Value::Number value);
        void offsetYGet(Value::Number& result);
        void offsetYSet(Value& result, Value::Number value);
        void rotationGet(Value::Number& result);
        void rotationSet(Value& result, Value::Number value);
        void scaleXGet(Value::Number& result);
        void scaleXSet(Value& result, Value::Number value);
        void scaleYGet(Value::Number& result);
        void scaleYSet(Value& result, Value::Number value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        Value::Number	OffsetX, OffsetY;
		Value::Number	LocalOffsetX, LocalOffsetY;
        Value::Number	ScaleX, ScaleY;
        Value::Number	Rotation;
		bool			LocalInitialized;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TransformGestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TransformGestureEvent"; }
#endif
    public:
        TransformGestureEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TransformGestureEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 12 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TransformGestureEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TransformGestureEvent"; }
#endif
    public:
        typedef Classes::TransformGestureEvent ClassType;

    public:
        TransformGestureEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TransformGestureEvent : public Class
    {
        friend class ClassTraits::TransformGestureEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TransformGestureEvent"; }
#endif
    public:
        typedef TransformGestureEvent SelfType;
        typedef TransformGestureEvent ClassType;
        
    private:
        TransformGestureEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_GESTURE_PAN() const { return GESTURE_PAN; }
        const char* get_GESTURE_ROTATE() const { return GESTURE_ROTATE; }
        const char* get_GESTURE_SWIPE() const { return GESTURE_SWIPE; }
        const char* get_GESTURE_ZOOM() const { return GESTURE_ZOOM; }


    protected:
        // AS3 API members.
        const char* GESTURE_PAN;
        const char* GESTURE_ROTATE;
        const char* GESTURE_SWIPE;
        const char* GESTURE_ZOOM;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

