//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMStatusEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_DRMStatusEvent_H
#define INC_AS3_Obj_Events_DRMStatusEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DRMStatusEvent;
}

namespace InstanceTraits
{
    class DRMStatusEvent;
}

namespace Classes
{
    class DRMStatusEvent;
}
    
namespace ClassTraits
{
    class DRMStatusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DRMStatusEvent"; }
#endif
    public:
        typedef Classes::DRMStatusEvent ClassType;

    public:
        DRMStatusEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class DRMStatusEvent : public Class
    {
        friend class ClassTraits::DRMStatusEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::DRMStatusEvent"; }
#endif
    public:
        typedef DRMStatusEvent SelfType;
        typedef DRMStatusEvent ClassType;
        
    private:
        DRMStatusEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DRM_STATUS() const { return DRM_STATUS; }


    protected:
        // AS3 API members.
        const char* DRM_STATUS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

