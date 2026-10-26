//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFieldType.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextFieldType_H
#define INC_AS3_Obj_Text_TextFieldType_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextFieldType;
}

namespace InstanceTraits
{
    class TextFieldType;
}

namespace Classes
{
    class TextFieldType;
}
    
namespace ClassTraits
{
    class TextFieldType : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextFieldType"; }
#endif
    public:
        typedef Classes::TextFieldType ClassType;

    public:
        TextFieldType(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextFieldType : public Class
    {
        friend class ClassTraits::TextFieldType;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextFieldType"; }
#endif
    public:
        typedef TextFieldType SelfType;
        typedef TextFieldType ClassType;
        
    private:
        TextFieldType(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DYNAMIC() const { return DYNAMIC; }
        const char* get_INPUT() const { return INPUT; }


    protected:
        // AS3 API members.
        const char* DYNAMIC;
        const char* INPUT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

