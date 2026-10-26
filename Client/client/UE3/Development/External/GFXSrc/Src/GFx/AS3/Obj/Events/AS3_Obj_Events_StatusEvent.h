//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StatusEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_StatusEvent_H
#define INC_AS3_Obj_Events_StatusEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StatusEvent;
}

namespace InstanceTraits
{
    class StatusEvent;
}

namespace Classes
{
    class StatusEvent;
}
    
namespace ClassTraits
{
    class StatusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StatusEvent"; }
#endif
    public:
        typedef Classes::StatusEvent ClassType;

    public:
        StatusEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StatusEvent : public Class
    {
        friend class ClassTraits::StatusEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StatusEvent"; }
#endif
    public:
        typedef StatusEvent SelfType;
        typedef StatusEvent ClassType;
        
    private:
        StatusEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_STATUS() const { return STATUS; }


    protected:
        // AS3 API members.
        const char* STATUS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

