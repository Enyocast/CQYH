//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_ReferencesValidationSetting.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Security_ReferencesValidationSetting_H
#define INC_AS3_Obj_Security_ReferencesValidationSetting_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ReferencesValidationSetting;
}

namespace InstanceTraits
{
    class ReferencesValidationSetting;
}

namespace Classes
{
    class ReferencesValidationSetting;
}
    
namespace ClassTraits
{
    class ReferencesValidationSetting : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ReferencesValidationSetting"; }
#endif
    public:
        typedef Classes::ReferencesValidationSetting ClassType;

    public:
        ReferencesValidationSetting(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ReferencesValidationSetting : public Class
    {
        friend class ClassTraits::ReferencesValidationSetting;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ReferencesValidationSetting"; }
#endif
    public:
        typedef ReferencesValidationSetting SelfType;
        typedef ReferencesValidationSetting ClassType;
        
    private:
        ReferencesValidationSetting(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_NEVER() const { return NEVER; }
        const char* get_VALID_IDENTITY() const { return VALID_IDENTITY; }
        const char* get_VALID_OR_UNKNOWN_IDENTITY() const { return VALID_OR_UNKNOWN_IDENTITY; }


    protected:
        // AS3 API members.
        const char* NEVER;
        const char* VALID_IDENTITY;
        const char* VALID_OR_UNKNOWN_IDENTITY;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

