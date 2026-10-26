//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFieldAutoSize.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextFieldAutoSize_H
#define INC_AS3_Obj_Text_TextFieldAutoSize_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextFieldAutoSize;
}

namespace InstanceTraits
{
    class TextFieldAutoSize;
}

namespace Classes
{
    class TextFieldAutoSize;
}
    
namespace ClassTraits
{
    class TextFieldAutoSize : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextFieldAutoSize"; }
#endif
    public:
        typedef Classes::TextFieldAutoSize ClassType;

    public:
        TextFieldAutoSize(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextFieldAutoSize : public Class
    {
        friend class ClassTraits::TextFieldAutoSize;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextFieldAutoSize"; }
#endif
    public:
        typedef TextFieldAutoSize SelfType;
        typedef TextFieldAutoSize ClassType;
        
    private:
        TextFieldAutoSize(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CENTER() const { return CENTER; }
        const char* get_LEFT() const { return LEFT; }
        const char* get_NONE() const { return NONE; }
        const char* get_RIGHT() const { return RIGHT; }


    protected:
        // AS3 API members.
        const char* CENTER;
        const char* LEFT;
        const char* NONE;
        const char* RIGHT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

