//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_TextEventEx.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_TextEventEx_H
#define INC_AS3_Obj_Gfx_TextEventEx_H

#include "../Events/AS3_Obj_Events_TextEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextEventEx;
}

namespace InstanceTraits
{
    class TextEventEx;
}

namespace Classes
{
    class TextEventEx;
}

namespace Instances
{
    class TextEventEx : public Instances::TextEvent
    {
        friend class InstanceTraits::TextEventEx;
        
    public:
        typedef TextEventEx SelfType;
        typedef Classes::TextEventEx ClassType;
        typedef InstanceTraits::TextEventEx TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextEventEx"; }
#endif
    protected:
        TextEventEx(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        UInt32 get_controllerIdx() const { return controllerIdx; }
        UInt32 get_buttonIdx() const { return buttonIdx; }


    protected:
        // AS3 API members.
        UInt32 controllerIdx;
        UInt32 buttonIdx;

//##protect##"instance$data"
    public:
        void    SetControllerIdx(unsigned idx)  { controllerIdx = idx; }
        void    SetButtonIdx(unsigned idx) { buttonIdx = idx; }
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TextEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextEventEx"; }
#endif
    public:
        TextEventEx(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextEventEx> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TextEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextEventEx"; }
#endif
    public:
        typedef Classes::TextEventEx ClassType;

    public:
        TextEventEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextEventEx : public Class
    {
        friend class ClassTraits::TextEventEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextEventEx"; }
#endif
    public:
        typedef TextEventEx SelfType;
        typedef TextEventEx ClassType;
        
    private:
        TextEventEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_LINK_MOUSE_OVER() const { return LINK_MOUSE_OVER; }
        const char* get_LINK_MOUSE_OUT() const { return LINK_MOUSE_OUT; }


    protected:
        // AS3 API members.
        const char* LINK_MOUSE_OVER;
        const char* LINK_MOUSE_OUT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

