//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_KeyboardEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_KeyboardEvent_H
#define INC_AS3_Obj_Events_KeyboardEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
#include "GFx/GFx_Input.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class KeyboardEvent;
}

namespace InstanceTraits
{
    class KeyboardEvent;
}

namespace Classes
{
    class KeyboardEvent;
}

namespace Instances
{
    class KeyboardEvent : public Instances::Event
    {
        friend class InstanceTraits::KeyboardEvent;
        
    public:
        typedef KeyboardEvent SelfType;
        typedef Classes::KeyboardEvent ClassType;
        typedef InstanceTraits::KeyboardEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::KeyboardEvent"; }
#endif
    protected:
        KeyboardEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
    public:
        void SetEventId(const EventId& eid);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_altKeyGet, 
            mid_altKeySet, 
            mid_charCodeGet, 
            mid_charCodeSet, 
            mid_commandKeyGet, 
            mid_commandKeySet, 
            mid_controlKeyGet, 
            mid_controlKeySet, 
            mid_ctrlKeyGet, 
            mid_ctrlKeySet, 
            mid_keyCodeGet, 
            mid_keyCodeSet, 
            mid_keyLocationGet, 
            mid_keyLocationSet, 
            mid_shiftKeyGet, 
            mid_shiftKeySet, 
            mid_clone, 
            mid_toString, 
            mid_updateAfterEvent, 
        };
        void altKeyGet(bool& result);
        void altKeySet(Value& result, bool value);
        void charCodeGet(UInt32& result);
        void charCodeSet(Value& result, UInt32 value);
        void commandKeyGet(bool& result);
        void commandKeySet(Value& result, bool value);
        void controlKeyGet(bool& result);
        void controlKeySet(Value& result, bool value);
        void ctrlKeyGet(bool& result);
        void ctrlKeySet(Value& result, bool value);
        void keyCodeGet(UInt32& result);
        void keyCodeSet(Value& result, UInt32 value);
        void keyLocationGet(UInt32& result);
        void keyLocationSet(Value& result, UInt32 value);
        void shiftKeyGet(bool& result);
        void shiftKeySet(Value& result, bool value);
        void clone(Value& result);
        void toString(ASString& result);
        void updateAfterEvent(Value& result);

//##protect##"instance$data"
        EventId     EvtId;
        int         KeyLocation;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class KeyboardEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::KeyboardEvent"; }
#endif
    public:
        KeyboardEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::KeyboardEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 19 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class KeyboardEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::KeyboardEvent"; }
#endif
    public:
        typedef Classes::KeyboardEvent ClassType;

    public:
        KeyboardEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class KeyboardEvent : public Class
    {
        friend class ClassTraits::KeyboardEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::KeyboardEvent"; }
#endif
    public:
        typedef KeyboardEvent SelfType;
        typedef KeyboardEvent ClassType;
        
    private:
        KeyboardEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_KEY_DOWN() const { return KEY_DOWN; }
        const char* get_KEY_UP() const { return KEY_UP; }


    protected:
        // AS3 API members.
        const char* KEY_DOWN;
        const char* KEY_UP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

