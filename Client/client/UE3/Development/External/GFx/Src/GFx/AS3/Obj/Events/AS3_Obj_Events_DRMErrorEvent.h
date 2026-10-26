//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMErrorEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_DRMErrorEvent_H
#define INC_AS3_Obj_Events_DRMErrorEvent_H

#include "AS3_Obj_Events_ErrorEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DRMErrorEvent;
}

namespace InstanceTraits
{
    class DRMErrorEvent;
}

namespace Classes
{
    class DRMErrorEvent;
}
    
namespace ClassTraits
{
    class DRMErrorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DRMErrorEvent"; }
#endif
    public:
        typedef Classes::DRMErrorEvent ClassType;

    public:
        DRMErrorEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class DRMErrorEvent : public Class
    {
        friend class ClassTraits::DRMErrorEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::DRMErrorEvent"; }
#endif
    public:
        typedef DRMErrorEvent SelfType;
        typedef DRMErrorEvent ClassType;
        
    private:
        DRMErrorEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DRM_ERROR() const { return DRM_ERROR; }


    protected:
        // AS3 API members.
        const char* DRM_ERROR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

