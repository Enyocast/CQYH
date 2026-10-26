//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_AsyncErrorEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_AsyncErrorEvent_H
#define INC_AS3_Obj_Events_AsyncErrorEvent_H

#include "AS3_Obj_Events_ErrorEvent.h"
//##protect##"includes"
#include "../AS3_Obj_Error.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AsyncErrorEvent;
}

namespace InstanceTraits
{
    class AsyncErrorEvent;
}

namespace Classes
{
    class AsyncErrorEvent;
}

namespace Instances
{
    class AsyncErrorEvent : public Instances::ErrorEvent
    {
        friend class InstanceTraits::AsyncErrorEvent;
        
    public:
        typedef AsyncErrorEvent SelfType;
        typedef Classes::AsyncErrorEvent ClassType;
        typedef InstanceTraits::AsyncErrorEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::AsyncErrorEvent"; }
#endif
    protected:
        AsyncErrorEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        ~AsyncErrorEvent();

    private:
        AsyncErrorEvent(const AsyncErrorEvent&);
        AsyncErrorEvent& operator =(const AsyncErrorEvent&);
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::Error* get_error() const { return error; }


    protected:
        // AS3 API members.
        SPtr<Instances::Error> error;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class AsyncErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::AsyncErrorEvent"; }
#endif
    public:
        AsyncErrorEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::AsyncErrorEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class AsyncErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AsyncErrorEvent"; }
#endif
    public:
        typedef Classes::AsyncErrorEvent ClassType;

    public:
        AsyncErrorEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class AsyncErrorEvent : public Class
    {
        friend class ClassTraits::AsyncErrorEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::AsyncErrorEvent"; }
#endif
    public:
        typedef AsyncErrorEvent SelfType;
        typedef AsyncErrorEvent ClassType;
        
    private:
        AsyncErrorEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ASYNC_ERROR() const { return ASYNC_ERROR; }


    protected:
        // AS3 API members.
        const char* ASYNC_ERROR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

