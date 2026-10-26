//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_CapsStyle.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_CapsStyle_H
#define INC_AS3_Obj_Display_CapsStyle_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class CapsStyle;
}

namespace InstanceTraits
{
    class CapsStyle;
}

namespace Classes
{
    class CapsStyle;
}
    
namespace ClassTraits
{
    class CapsStyle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::CapsStyle"; }
#endif
    public:
        typedef Classes::CapsStyle ClassType;

    public:
        CapsStyle(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class CapsStyle : public Class
    {
        friend class ClassTraits::CapsStyle;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::CapsStyle"; }
#endif
    public:
        typedef CapsStyle SelfType;
        typedef CapsStyle ClassType;
        
    private:
        CapsStyle(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_NONE() const { return NONE; }
        const char* get_ROUND() const { return ROUND; }
        const char* get_SQUARE() const { return SQUARE; }


    protected:
        // AS3 API members.
        const char* NONE;
        const char* ROUND;
        const char* SQUARE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

