//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IMEEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_IMEEvent_H
#define INC_AS3_Obj_Events_IMEEvent_H

#include "AS3_Obj_Events_TextEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IMEEvent;
}

namespace InstanceTraits
{
    class IMEEvent;
}

namespace Classes
{
    class IMEEvent;
}

namespace Instances
{
    class IMEEvent : public Instances::TextEvent
    {
        friend class InstanceTraits::IMEEvent;
        
    public:
        typedef IMEEvent SelfType;
        typedef Classes::IMEEvent ClassType;
        typedef InstanceTraits::IMEEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::IMEEvent"; }
#endif
    protected:
        IMEEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_clone, 
            mid_toString, 
        };
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class IMEEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::IMEEvent"; }
#endif
    public:
        IMEEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::IMEEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

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
    class IMEEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IMEEvent"; }
#endif
    public:
        typedef Classes::IMEEvent ClassType;

    public:
        IMEEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IMEEvent : public Class
    {
        friend class ClassTraits::IMEEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IMEEvent"; }
#endif
    public:
        typedef IMEEvent SelfType;
        typedef IMEEvent ClassType;
        
    private:
        IMEEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_IME_COMPOSITION() const { return IME_COMPOSITION; }


    protected:
        // AS3 API members.
        const char* IME_COMPOSITION;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

