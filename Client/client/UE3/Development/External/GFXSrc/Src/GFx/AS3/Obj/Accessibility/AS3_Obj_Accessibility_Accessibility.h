//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_Accessibility.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Accessibility_Accessibility_H
#define INC_AS3_Obj_Accessibility_Accessibility_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Accessibility;
}

namespace InstanceTraits
{
    class Accessibility;
}

namespace Classes
{
    class Accessibility;
}
    
namespace ClassTraits
{
    class Accessibility : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Accessibility"; }
#endif
    public:
        typedef Classes::Accessibility ClassType;

    public:
        Accessibility(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Accessibility : public Class
    {
        friend class ClassTraits::Accessibility;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Accessibility"; }
#endif
    public:
        typedef Accessibility SelfType;
        typedef Accessibility ClassType;
        
    private:
        Accessibility(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

