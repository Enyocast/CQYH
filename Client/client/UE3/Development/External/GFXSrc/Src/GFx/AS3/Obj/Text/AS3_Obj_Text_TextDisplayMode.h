//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextDisplayMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextDisplayMode_H
#define INC_AS3_Obj_Text_TextDisplayMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextDisplayMode;
}

namespace InstanceTraits
{
    class TextDisplayMode;
}

namespace Classes
{
    class TextDisplayMode;
}
    
namespace ClassTraits
{
    class TextDisplayMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextDisplayMode"; }
#endif
    public:
        typedef Classes::TextDisplayMode ClassType;

    public:
        TextDisplayMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextDisplayMode : public Class
    {
        friend class ClassTraits::TextDisplayMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextDisplayMode"; }
#endif
    public:
        typedef TextDisplayMode SelfType;
        typedef TextDisplayMode ClassType;
        
    private:
        TextDisplayMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CRT() const { return CRT; }
        const char* get_DEFAULT() const { return DEFAULT; }
        const char* get_LCD() const { return LCD; }


    protected:
        // AS3 API members.
        const char* CRT;
        const char* DEFAULT;
        const char* LCD;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

