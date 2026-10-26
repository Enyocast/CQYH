//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_FocusDirection.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_FocusDirection_H
#define INC_AS3_Obj_Display_FocusDirection_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FocusDirection;
}

namespace InstanceTraits
{
    class FocusDirection;
}

namespace Classes
{
    class FocusDirection;
}
    
namespace ClassTraits
{
    class FocusDirection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FocusDirection"; }
#endif
    public:
        typedef Classes::FocusDirection ClassType;

    public:
        FocusDirection(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FocusDirection : public Class
    {
        friend class ClassTraits::FocusDirection;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FocusDirection"; }
#endif
    public:
        typedef FocusDirection SelfType;
        typedef FocusDirection ClassType;
        
    private:
        FocusDirection(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BOTTOM() const { return BOTTOM; }
        const char* get_NONE() const { return NONE; }
        const char* get_TOP() const { return TOP; }


    protected:
        // AS3 API members.
        const char* BOTTOM;
        const char* NONE;
        const char* TOP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

