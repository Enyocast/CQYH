//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_AntiAliasType.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_AntiAliasType_H
#define INC_AS3_Obj_Text_AntiAliasType_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AntiAliasType;
}

namespace InstanceTraits
{
    class AntiAliasType;
}

namespace Classes
{
    class AntiAliasType;
}
    
namespace ClassTraits
{
    class AntiAliasType : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AntiAliasType"; }
#endif
    public:
        typedef Classes::AntiAliasType ClassType;

    public:
        AntiAliasType(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class AntiAliasType : public Class
    {
        friend class ClassTraits::AntiAliasType;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::AntiAliasType"; }
#endif
    public:
        typedef AntiAliasType SelfType;
        typedef AntiAliasType ClassType;
        
    private:
        AntiAliasType(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ADVANCED() const { return ADVANCED; }
        const char* get_NORMAL() const { return NORMAL; }


    protected:
        // AS3 API members.
        const char* ADVANCED;
        const char* NORMAL;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

