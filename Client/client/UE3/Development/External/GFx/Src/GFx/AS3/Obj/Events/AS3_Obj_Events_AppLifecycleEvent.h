//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_AppLifecycleEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_AppLifecycleEvent_H
#define INC_AS3_Obj_Events_AppLifecycleEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AppLifecycleEvent;
}

namespace InstanceTraits
{
    class AppLifecycleEvent;
}

namespace Classes
{
    class AppLifecycleEvent;
}

namespace Instances
{
    class AppLifecycleEvent : public Instances::Event
    {
        friend class InstanceTraits::AppLifecycleEvent;
        
    public:
        typedef AppLifecycleEvent SelfType;
        typedef Classes::AppLifecycleEvent ClassType;
        typedef InstanceTraits::AppLifecycleEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::AppLifecycleEvent"; }
#endif
    protected:
        AppLifecycleEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_statusGet, 
            mid_clone, 
            mid_toString, 
        };
        void statusGet(Value& result);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        Value Status;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class AppLifecycleEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::AppLifecycleEvent"; }
#endif
    public:
        AppLifecycleEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::AppLifecycleEvent> MakeInstance(Traits& t);

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
    class AppLifecycleEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AppLifecycleEvent"; }
#endif
    public:
        typedef Classes::AppLifecycleEvent ClassType;

    public:
        AppLifecycleEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class AppLifecycleEvent : public Class
    {
        friend class ClassTraits::AppLifecycleEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::AppLifecycleEvent"; }
#endif
    public:
        typedef AppLifecycleEvent SelfType;
        typedef AppLifecycleEvent ClassType;
        
    private:
        AppLifecycleEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ONPAUSE() const { return ONPAUSE; }
        const char* get_ONRESUME() const { return ONRESUME; }


    protected:
        // AS3 API members.
        const char* ONPAUSE;
        const char* ONRESUME;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

