//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ErrorEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_ErrorEvent_H
#define INC_AS3_Obj_Events_ErrorEvent_H

#include "AS3_Obj_Events_TextEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef ERROR
#undef ERROR
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ErrorEvent;
}

namespace InstanceTraits
{
    class ErrorEvent;
}

namespace Classes
{
    class ErrorEvent;
}

namespace Instances
{
    class ErrorEvent : public Instances::TextEvent
    {
        friend class InstanceTraits::ErrorEvent;
        
    public:
        typedef ErrorEvent SelfType;
        typedef Classes::ErrorEvent ClassType;
        typedef InstanceTraits::ErrorEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ErrorEvent"; }
#endif
    protected:
        ErrorEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_errorIDGet, 
            mid_clone, 
            mid_toString, 
        };
        void errorIDGet(SInt32& result);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ErrorEvent"; }
#endif
    public:
        ErrorEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ErrorEvent> MakeInstance(Traits& t);

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
    class ErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ErrorEvent"; }
#endif
    public:
        typedef Classes::ErrorEvent ClassType;

    public:
        ErrorEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ErrorEvent : public Class
    {
        friend class ClassTraits::ErrorEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ErrorEvent"; }
#endif
    public:
        typedef ErrorEvent SelfType;
        typedef ErrorEvent ClassType;
        
    private:
        ErrorEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ERROR() const { return ERROR; }


    protected:
        // AS3 API members.
        const char* ERROR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

