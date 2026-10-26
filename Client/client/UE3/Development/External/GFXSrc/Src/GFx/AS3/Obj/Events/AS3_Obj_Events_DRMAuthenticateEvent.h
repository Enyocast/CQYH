//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DRMAuthenticateEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_DRMAuthenticateEvent_H
#define INC_AS3_Obj_Events_DRMAuthenticateEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DRMAuthenticateEvent;
}

namespace InstanceTraits
{
    class DRMAuthenticateEvent;
}

namespace Classes
{
    class DRMAuthenticateEvent;
}
    
namespace ClassTraits
{
    class DRMAuthenticateEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DRMAuthenticateEvent"; }
#endif
    public:
        typedef Classes::DRMAuthenticateEvent ClassType;

    public:
        DRMAuthenticateEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class DRMAuthenticateEvent : public Class
    {
        friend class ClassTraits::DRMAuthenticateEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::DRMAuthenticateEvent"; }
#endif
    public:
        typedef DRMAuthenticateEvent SelfType;
        typedef DRMAuthenticateEvent ClassType;
        
    private:
        DRMAuthenticateEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_AUTHENTICATION_TYPE_DRM() const { return AUTHENTICATION_TYPE_DRM; }
        const char* get_AUTHENTICATION_TYPE_PROXY() const { return AUTHENTICATION_TYPE_PROXY; }
        const char* get_DRM_AUTHENTICATE() const { return DRM_AUTHENTICATE; }


    protected:
        // AS3 API members.
        const char* AUTHENTICATION_TYPE_DRM;
        const char* AUTHENTICATION_TYPE_PROXY;
        const char* DRM_AUTHENTICATE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

