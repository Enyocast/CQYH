//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IOErrorEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_IOErrorEvent_H
#define INC_AS3_Obj_Events_IOErrorEvent_H

#include "AS3_Obj_Events_ErrorEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IOErrorEvent;
}

namespace InstanceTraits
{
    class IOErrorEvent;
}

namespace Classes
{
    class IOErrorEvent;
}

namespace Instances
{
    class IOErrorEvent : public Instances::ErrorEvent
    {
        friend class InstanceTraits::IOErrorEvent;
        
    public:
        typedef IOErrorEvent SelfType;
        typedef Classes::IOErrorEvent ClassType;
        typedef InstanceTraits::IOErrorEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::IOErrorEvent"; }
#endif
    protected:
        IOErrorEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_textGet, 
            mid_textSet, 
            mid_clone, 
            mid_toString, 
        };
        void textGet(ASString& result);
        void textSet(Value& result, const ASString& value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        ASString Text;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class IOErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::IOErrorEvent"; }
#endif
    public:
        IOErrorEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::IOErrorEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class IOErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IOErrorEvent"; }
#endif
    public:
        typedef Classes::IOErrorEvent ClassType;

    public:
        IOErrorEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IOErrorEvent : public Class
    {
        friend class ClassTraits::IOErrorEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IOErrorEvent"; }
#endif
    public:
        typedef IOErrorEvent SelfType;
        typedef IOErrorEvent ClassType;
        
    private:
        IOErrorEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_IO_ERROR() const { return IO_ERROR; }


    protected:
        // AS3 API members.
        const char* IO_ERROR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

