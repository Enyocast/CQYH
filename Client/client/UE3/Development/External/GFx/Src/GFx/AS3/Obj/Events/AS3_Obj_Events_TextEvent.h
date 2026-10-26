//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_TextEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_TextEvent_H
#define INC_AS3_Obj_Events_TextEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextEvent;
}

namespace InstanceTraits
{
    class TextEvent;
}

namespace Classes
{
    class TextEvent;
}

namespace Instances
{
    class TextEvent : public Instances::Event
    {
        friend class InstanceTraits::TextEvent;
        
    public:
        typedef TextEvent SelfType;
        typedef Classes::TextEvent ClassType;
        typedef InstanceTraits::TextEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextEvent"; }
#endif
    protected:
        TextEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
    public:
        void SetText(const ASString& t) { Text = t; }
        void SetText(wchar_t ch);
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
    class TextEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextEvent"; }
#endif
    public:
        TextEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextEvent> MakeInstance(Traits& t);

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
    class TextEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextEvent"; }
#endif
    public:
        typedef Classes::TextEvent ClassType;

    public:
        TextEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextEvent : public Class
    {
        friend class ClassTraits::TextEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextEvent"; }
#endif
    public:
        typedef TextEvent SelfType;
        typedef TextEvent ClassType;
        
    private:
        TextEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_LINK() const { return LINK; }
        const char* get_TEXT_INPUT() const { return TEXT_INPUT; }


    protected:
        // AS3 API members.
        const char* LINK;
        const char* TEXT_INPUT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

