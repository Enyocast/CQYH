//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_FocusEventEx.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_FocusEventEx_H
#define INC_AS3_Obj_Gfx_FocusEventEx_H

#include "../Events/AS3_Obj_Events_FocusEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FocusEventEx;
}

namespace InstanceTraits
{
    class FocusEventEx;
}

namespace Classes
{
    class FocusEventEx;
}

namespace Instances
{
    class FocusEventEx : public Instances::FocusEvent
    {
        friend class InstanceTraits::FocusEventEx;
        
    public:
        typedef FocusEventEx SelfType;
        typedef Classes::FocusEventEx ClassType;
        typedef InstanceTraits::FocusEventEx TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::FocusEventEx"; }
#endif
    protected:
        FocusEventEx(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        UInt32 get_controllerIdx() const { return controllerIdx; }


    protected:
        // AS3 API members.
        UInt32 controllerIdx;

//##protect##"instance$data"
    public:
        void    SetControllerIdx(unsigned idx)  { controllerIdx = idx; }
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class FocusEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::FocusEventEx"; }
#endif
    public:
        FocusEventEx(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::FocusEventEx> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class FocusEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FocusEventEx"; }
#endif
    public:
        typedef Classes::FocusEventEx ClassType;

    public:
        FocusEventEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

