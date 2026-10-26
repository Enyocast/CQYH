//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_EventPhase.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_EventPhase_H
#define INC_AS3_Obj_Events_EventPhase_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class EventPhase;
}

namespace InstanceTraits
{
    class EventPhase;
}

namespace Classes
{
    class EventPhase;
}
    
namespace ClassTraits
{
    class EventPhase : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::EventPhase"; }
#endif
    public:
        typedef Classes::EventPhase ClassType;

    public:
        EventPhase(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class EventPhase : public Class
    {
        friend class ClassTraits::EventPhase;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::EventPhase"; }
#endif
    public:
        typedef EventPhase SelfType;
        typedef EventPhase ClassType;
        
    private:
        EventPhase(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_AT_TARGET() const { return AT_TARGET; }
        UInt32 get_BUBBLING_PHASE() const { return BUBBLING_PHASE; }
        UInt32 get_CAPTURING_PHASE() const { return CAPTURING_PHASE; }


    protected:
        // AS3 API members.
        const UInt32 AT_TARGET;
        const UInt32 BUBBLING_PHASE;
        const UInt32 CAPTURING_PHASE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

