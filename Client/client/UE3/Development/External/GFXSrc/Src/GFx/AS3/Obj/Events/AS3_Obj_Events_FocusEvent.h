//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FocusEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_FocusEvent_H
#define INC_AS3_Obj_Events_FocusEvent_H

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
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FocusEvent;
}

namespace InstanceTraits
{
    class FocusEvent;
}

namespace Classes
{
    class FocusEvent;
}

namespace Instances
{
    class FocusEvent : public Instances::Event
    {
        friend class InstanceTraits::FocusEvent;
        
    public:
        typedef FocusEvent SelfType;
        typedef Classes::FocusEvent ClassType;
        typedef InstanceTraits::FocusEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::FocusEvent"; }
#endif
    protected:
        FocusEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);

        Instances::InteractiveObject* GetRelatedObj() const
        {
            return RelatedObj;
        }
        void SetRelatedObj(Instances::InteractiveObject* obj)
        {
            RelatedObj = obj;
        }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_directionGet, 
            mid_directionSet, 
            mid_keyCodeGet, 
            mid_keyCodeSet, 
            mid_relatedObjectGet, 
            mid_relatedObjectSet, 
            mid_shiftKeyGet, 
            mid_shiftKeySet, 
            mid_clone, 
            mid_toString, 
        };
        void directionGet(ASString& result);
        void directionSet(Value& result, const ASString& value);
        void keyCodeGet(UInt32& result);
        void keyCodeSet(Value& result, UInt32 value);
        void relatedObjectGet(Value& result);
        void relatedObjectSet(Value& result, Instances::InteractiveObject* value);
        void shiftKeyGet(bool& result);
        void shiftKeySet(Value& result, bool value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        bool                                ShiftKey;
        UInt32                              KeyCode;

    protected:
        SPtr<Instances::InteractiveObject>  RelatedObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class FocusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::FocusEvent"; }
#endif
    public:
        FocusEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::FocusEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 10 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class FocusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FocusEvent"; }
#endif
    public:
        typedef Classes::FocusEvent ClassType;

    public:
        FocusEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FocusEvent : public Class
    {
        friend class ClassTraits::FocusEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FocusEvent"; }
#endif
    public:
        typedef FocusEvent SelfType;
        typedef FocusEvent ClassType;
        
    private:
        FocusEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_FOCUS_IN() const { return FOCUS_IN; }
        const char* get_FOCUS_OUT() const { return FOCUS_OUT; }
        const char* get_KEY_FOCUS_CHANGE() const { return KEY_FOCUS_CHANGE; }
        const char* get_MOUSE_FOCUS_CHANGE() const { return MOUSE_FOCUS_CHANGE; }


    protected:
        // AS3 API members.
        const char* FOCUS_IN;
        const char* FOCUS_OUT;
        const char* KEY_FOCUS_CHANGE;
        const char* MOUSE_FOCUS_CHANGE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

