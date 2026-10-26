//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TimerEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_TimerEvent_H
#define INC_AS3_Obj_Events_TimerEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TimerEvent;
}

namespace InstanceTraits
{
    class TimerEvent;
}

namespace Classes
{
    class TimerEvent;
}

namespace Instances
{
    class TimerEvent : public Instances::Event
    {
        friend class InstanceTraits::TimerEvent;
        
    public:
        typedef TimerEvent SelfType;
        typedef Classes::TimerEvent ClassType;
        typedef InstanceTraits::TimerEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TimerEvent"; }
#endif
    protected:
        TimerEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual const char*     GetEventName() const { return "TimerEvent"; }
        virtual AS3::Object*    GetEventClass() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_clone, 
            mid_toString, 
            mid_updateAfterEvent, 
        };
        void clone(Value& result);
        void toString(ASString& result);
        void updateAfterEvent(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TimerEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TimerEvent"; }
#endif
    public:
        TimerEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TimerEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TimerEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TimerEvent"; }
#endif
    public:
        typedef Classes::TimerEvent ClassType;

    public:
        TimerEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TimerEvent : public Class
    {
        friend class ClassTraits::TimerEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TimerEvent"; }
#endif
    public:
        typedef TimerEvent SelfType;
        typedef TimerEvent ClassType;
        
    private:
        TimerEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_TIMER() const { return TIMER; }
        const char* get_TIMER_COMPLETE() const { return TIMER_COMPLETE; }


    protected:
        // AS3 API members.
        const char* TIMER;
        const char* TIMER_COMPLETE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

