//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NetStatusEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_NetStatusEvent_H
#define INC_AS3_Obj_Events_NetStatusEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NetStatusEvent;
}

namespace InstanceTraits
{
    class NetStatusEvent;
}

namespace Classes
{
    class NetStatusEvent;
}

namespace Instances
{
    class NetStatusEvent : public Instances::Event
    {
        friend class InstanceTraits::NetStatusEvent;
        
    public:
        typedef NetStatusEvent SelfType;
        typedef Classes::NetStatusEvent ClassType;
        typedef InstanceTraits::NetStatusEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NetStatusEvent"; }
#endif
    protected:
        NetStatusEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);

        virtual SPtr<Instances::Event> Clone() const;
        virtual const char* GetEventName() const;
        virtual AS3::Object* GetEventClass() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_infoGet, 
            mid_infoSet, 
            mid_clone, 
            mid_toString, 
        };
        void infoGet(Value& result);
        void infoSet(Value& result, const Value& value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        ASString Code;
        ASString Level;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NetStatusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NetStatusEvent"; }
#endif
    public:
        NetStatusEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NetStatusEvent> MakeInstance(Traits& t);

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
    class NetStatusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NetStatusEvent"; }
#endif
    public:
        typedef Classes::NetStatusEvent ClassType;

    public:
        NetStatusEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NetStatusEvent : public Class
    {
        friend class ClassTraits::NetStatusEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NetStatusEvent"; }
#endif
    public:
        typedef NetStatusEvent SelfType;
        typedef NetStatusEvent ClassType;
        
    private:
        NetStatusEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_NET_STATUS() const { return NET_STATUS; }


    protected:
        // AS3 API members.
        const char* NET_STATUS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

