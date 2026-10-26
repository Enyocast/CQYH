//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_RevocationCheckSettings.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Security_RevocationCheckSettings_H
#define INC_AS3_Obj_Security_RevocationCheckSettings_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class RevocationCheckSettings;
}

namespace InstanceTraits
{
    class RevocationCheckSettings;
}

namespace Classes
{
    class RevocationCheckSettings;
}
    
namespace ClassTraits
{
    class RevocationCheckSettings : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::RevocationCheckSettings"; }
#endif
    public:
        typedef Classes::RevocationCheckSettings ClassType;

    public:
        RevocationCheckSettings(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class RevocationCheckSettings : public Class
    {
        friend class ClassTraits::RevocationCheckSettings;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::RevocationCheckSettings"; }
#endif
    public:
        typedef RevocationCheckSettings SelfType;
        typedef RevocationCheckSettings ClassType;
        
    private:
        RevocationCheckSettings(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const Value& get_ALWAYS_REQUIRED() const { return ALWAYS_REQUIRED; }
        const Value& get_BEST_EFFORT() const { return BEST_EFFORT; }
        const Value& get_NEVER() const { return NEVER; }
        const Value& get_REQUIRED_IF_AVAILABLE() const { return REQUIRED_IF_AVAILABLE; }


    protected:
        // AS3 API members.
        Value ALWAYS_REQUIRED;
        Value BEST_EFFORT;
        Value NEVER;
        Value REQUIRED_IF_AVAILABLE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

