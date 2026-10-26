//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_InterpolationMethod.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_InterpolationMethod_H
#define INC_AS3_Obj_Display_InterpolationMethod_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef RGB
#undef RGB
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class InterpolationMethod;
}

namespace InstanceTraits
{
    class InterpolationMethod;
}

namespace Classes
{
    class InterpolationMethod;
}
    
namespace ClassTraits
{
    class InterpolationMethod : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::InterpolationMethod"; }
#endif
    public:
        typedef Classes::InterpolationMethod ClassType;

    public:
        InterpolationMethod(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class InterpolationMethod : public Class
    {
        friend class ClassTraits::InterpolationMethod;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::InterpolationMethod"; }
#endif
    public:
        typedef InterpolationMethod SelfType;
        typedef InterpolationMethod ClassType;
        
    private:
        InterpolationMethod(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_LINEAR_RGB() const { return LINEAR_RGB; }
        const char* get_RGB() const { return RGB; }


    protected:
        // AS3 API members.
        const char* LINEAR_RGB;
        const char* RGB;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

