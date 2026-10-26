//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextColorType.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextColorType_H
#define INC_AS3_Obj_Text_TextColorType_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextColorType;
}

namespace InstanceTraits
{
    class TextColorType;
}

namespace Classes
{
    class TextColorType;
}
    
namespace ClassTraits
{
    class TextColorType : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextColorType"; }
#endif
    public:
        typedef Classes::TextColorType ClassType;

    public:
        TextColorType(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextColorType : public Class
    {
        friend class ClassTraits::TextColorType;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextColorType"; }
#endif
    public:
        typedef TextColorType SelfType;
        typedef TextColorType ClassType;
        
    private:
        TextColorType(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DARK_COLOR() const { return DARK_COLOR; }
        const char* get_LIGHT_COLOR() const { return LIGHT_COLOR; }


    protected:
        // AS3 API members.
        const char* DARK_COLOR;
        const char* LIGHT_COLOR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

