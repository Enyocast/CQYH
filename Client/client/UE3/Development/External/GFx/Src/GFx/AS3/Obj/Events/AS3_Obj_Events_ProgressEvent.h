//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ProgressEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_ProgressEvent_H
#define INC_AS3_Obj_Events_ProgressEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ProgressEvent;
}

namespace InstanceTraits
{
    class ProgressEvent;
}

namespace Classes
{
    class ProgressEvent;
}

namespace Instances
{
    class ProgressEvent : public Instances::Event
    {
        friend class InstanceTraits::ProgressEvent;
        
    public:
        typedef ProgressEvent SelfType;
        typedef Classes::ProgressEvent ClassType;
        typedef InstanceTraits::ProgressEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ProgressEvent"; }
#endif
    protected:
        ProgressEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void SetBytesTotal(UPInt t)  { BytesTotal = t; }
        void SetBytesLoaded(UPInt t) { BytesLoaded = t; }

        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bytesLoadedGet, 
            mid_bytesLoadedSet, 
            mid_bytesTotalGet, 
            mid_bytesTotalSet, 
            mid_clone, 
            mid_toString, 
        };
        void bytesLoadedGet(Value::Number& result);
        void bytesLoadedSet(Value& result, Value::Number value);
        void bytesTotalGet(Value::Number& result);
        void bytesTotalSet(Value& result, Value::Number value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
    protected:
        UPInt BytesLoaded;
        UPInt BytesTotal;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ProgressEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ProgressEvent"; }
#endif
    public:
        ProgressEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ProgressEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ProgressEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ProgressEvent"; }
#endif
    public:
        typedef Classes::ProgressEvent ClassType;

    public:
        ProgressEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ProgressEvent : public Class
    {
        friend class ClassTraits::ProgressEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ProgressEvent"; }
#endif
    public:
        typedef ProgressEvent SelfType;
        typedef ProgressEvent ClassType;
        
    private:
        ProgressEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_PROGRESS() const { return PROGRESS; }
        const char* get_SOCKET_DATA() const { return SOCKET_DATA; }


    protected:
        // AS3 API members.
        const char* PROGRESS;
        const char* SOCKET_DATA;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

