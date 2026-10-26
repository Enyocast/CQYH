//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_FontStyle.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_FontStyle_H
#define INC_AS3_Obj_Text_FontStyle_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FontStyle;
}

namespace InstanceTraits
{
    class FontStyle;
}

namespace Classes
{
    class FontStyle;
}
    
namespace ClassTraits
{
    class FontStyle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FontStyle"; }
#endif
    public:
        typedef Classes::FontStyle ClassType;

    public:
        FontStyle(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FontStyle : public Class
    {
        friend class ClassTraits::FontStyle;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FontStyle"; }
#endif
    public:
        typedef FontStyle SelfType;
        typedef FontStyle ClassType;
        
    private:
        FontStyle(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BOLD() const { return BOLD; }
        const char* get_BOLD_ITALIC() const { return BOLD_ITALIC; }
        const char* get_ITALIC() const { return ITALIC; }
        const char* get_REGULAR() const { return REGULAR; }


    protected:
        // AS3 API members.
        const char* BOLD;
        const char* BOLD_ITALIC;
        const char* ITALIC;
        const char* REGULAR;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

