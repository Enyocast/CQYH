//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_MouseEventEx.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_MouseEventEx_H
#define INC_AS3_Obj_Gfx_MouseEventEx_H

#include "../Events/AS3_Obj_Events_MouseEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MouseEventEx;
}

namespace InstanceTraits
{
    class MouseEventEx;
}

namespace Classes
{
    class MouseEventEx;
}

namespace Instances
{
    class MouseEventEx : public Instances::MouseEvent
    {
        friend class InstanceTraits::MouseEventEx;
        
    public:
        typedef MouseEventEx SelfType;
        typedef Classes::MouseEventEx ClassType;
        typedef InstanceTraits::MouseEventEx TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::MouseEventEx"; }
#endif
    protected:
        MouseEventEx(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        UInt32 get_mouseIdx() const { return mouseIdx; }
        UInt32 get_buttonIdx() const { return buttonIdx; }
        UInt32 get_nestingIdx() const { return nestingIdx; }


    protected:
        // AS3 API members.
        UInt32 mouseIdx;
        UInt32 buttonIdx;
        UInt32 nestingIdx;

//##protect##"instance$data"
    public:
        void    SetMouseIdx(unsigned idx) { mouseIdx = idx; }
        void    SetButtonIdx(unsigned idx) { buttonIdx = idx; }
        void    SetNestingIdx(unsigned idx) { nestingIdx = idx; }
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class MouseEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::MouseEventEx"; }
#endif
    public:
        MouseEventEx(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::MouseEventEx> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class MouseEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MouseEventEx"; }
#endif
    public:
        typedef Classes::MouseEventEx ClassType;

    public:
        MouseEventEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class MouseEventEx : public Class
    {
        friend class ClassTraits::MouseEventEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::MouseEventEx"; }
#endif
    public:
        typedef MouseEventEx SelfType;
        typedef MouseEventEx ClassType;
        
    private:
        MouseEventEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_LEFT_BUTTON() const { return LEFT_BUTTON; }
        UInt32 get_RIGHT_BUTTON() const { return RIGHT_BUTTON; }
        UInt32 get_MIDDLE_BUTTON() const { return MIDDLE_BUTTON; }


    protected:
        // AS3 API members.
        const UInt32 LEFT_BUTTON;
        const UInt32 RIGHT_BUTTON;
        const UInt32 MIDDLE_BUTTON;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

