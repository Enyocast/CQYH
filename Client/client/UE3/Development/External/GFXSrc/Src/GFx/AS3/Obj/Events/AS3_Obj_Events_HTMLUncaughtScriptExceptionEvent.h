//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_HTMLUncaughtScriptExceptionEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_HTMLUncaughtScriptExceptionEvent_H
#define INC_AS3_Obj_Events_HTMLUncaughtScriptExceptionEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class HTMLUncaughtScriptExceptionEvent;
}

namespace InstanceTraits
{
    class HTMLUncaughtScriptExceptionEvent;
}

namespace Classes
{
    class HTMLUncaughtScriptExceptionEvent;
}

namespace Instances
{
    class HTMLUncaughtScriptExceptionEvent : public Instances::Event
    {
        friend class InstanceTraits::HTMLUncaughtScriptExceptionEvent;
        
    public:
        typedef HTMLUncaughtScriptExceptionEvent SelfType;
        typedef Classes::HTMLUncaughtScriptExceptionEvent ClassType;
        typedef InstanceTraits::HTMLUncaughtScriptExceptionEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::HTMLUncaughtScriptExceptionEvent"; }
#endif
    protected:
        HTMLUncaughtScriptExceptionEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const Value& get_exceptionValue() const { return exceptionValue; }
        Instances::Array* get_stackTrace() const { return stackTrace; }


    protected:
        // AS3 API members.
        Value exceptionValue;
        SPtr<Instances::Array> stackTrace;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class HTMLUncaughtScriptExceptionEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::HTMLUncaughtScriptExceptionEvent"; }
#endif
    public:
        HTMLUncaughtScriptExceptionEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::HTMLUncaughtScriptExceptionEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class HTMLUncaughtScriptExceptionEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::HTMLUncaughtScriptExceptionEvent"; }
#endif
    public:
        typedef Classes::HTMLUncaughtScriptExceptionEvent ClassType;

    public:
        HTMLUncaughtScriptExceptionEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class HTMLUncaughtScriptExceptionEvent : public Class
    {
        friend class ClassTraits::HTMLUncaughtScriptExceptionEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::HTMLUncaughtScriptExceptionEvent"; }
#endif
    public:
        typedef HTMLUncaughtScriptExceptionEvent SelfType;
        typedef HTMLUncaughtScriptExceptionEvent ClassType;
        
    private:
        HTMLUncaughtScriptExceptionEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const Value& get_UNCAUGHT_SCRIPT_EXCEPTION() const { return UNCAUGHT_SCRIPT_EXCEPTION; }


    protected:
        // AS3 API members.
        Value UNCAUGHT_SCRIPT_EXCEPTION;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

