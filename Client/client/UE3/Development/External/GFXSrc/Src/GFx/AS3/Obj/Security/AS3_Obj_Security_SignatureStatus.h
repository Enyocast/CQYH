//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_SignatureStatus.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Security_SignatureStatus_H
#define INC_AS3_Obj_Security_SignatureStatus_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SignatureStatus;
}

namespace InstanceTraits
{
    class SignatureStatus;
}

namespace Classes
{
    class SignatureStatus;
}
    
namespace ClassTraits
{
    class SignatureStatus : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SignatureStatus"; }
#endif
    public:
        typedef Classes::SignatureStatus ClassType;

    public:
        SignatureStatus(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SignatureStatus : public Class
    {
        friend class ClassTraits::SignatureStatus;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SignatureStatus"; }
#endif
    public:
        typedef SignatureStatus SelfType;
        typedef SignatureStatus ClassType;
        
    private:
        SignatureStatus(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_INVALID() const { return INVALID; }
        const char* get_UNKNOWN() const { return UNKNOWN; }
        const char* get_VALID() const { return VALID; }


    protected:
        // AS3 API members.
        const char* INVALID;
        const char* UNKNOWN;
        const char* VALID;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

