//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DisplacementMapFilterMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_DisplacementMapFilterMode_H
#define INC_AS3_Obj_Filters_DisplacementMapFilterMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef IGNORE
#undef IGNORE
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DisplacementMapFilterMode;
}

namespace InstanceTraits
{
    class DisplacementMapFilterMode;
}

namespace Classes
{
    class DisplacementMapFilterMode;
}
    
namespace ClassTraits
{
    class DisplacementMapFilterMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DisplacementMapFilterMode"; }
#endif
    public:
        typedef Classes::DisplacementMapFilterMode ClassType;

    public:
        DisplacementMapFilterMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class DisplacementMapFilterMode : public Class
    {
        friend class ClassTraits::DisplacementMapFilterMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::DisplacementMapFilterMode"; }
#endif
    public:
        typedef DisplacementMapFilterMode SelfType;
        typedef DisplacementMapFilterMode ClassType;
        
    private:
        DisplacementMapFilterMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CLAMP() const { return CLAMP; }
        const char* get_COLOR() const { return COLOR; }
        const char* get_IGNORE() const { return IGNORE; }
        const char* get_WRAP() const { return WRAP; }


    protected:
        // AS3 API members.
        const char* CLAMP;
        const char* COLOR;
        const char* IGNORE;
        const char* WRAP;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

