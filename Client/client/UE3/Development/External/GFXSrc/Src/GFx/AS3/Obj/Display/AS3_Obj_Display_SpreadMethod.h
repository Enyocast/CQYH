//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SpreadMethod.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_SpreadMethod_H
#define INC_AS3_Obj_Display_SpreadMethod_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SpreadMethod;
}

namespace InstanceTraits
{
    class SpreadMethod;
}

namespace Classes
{
    class SpreadMethod;
}
    
namespace ClassTraits
{
    class SpreadMethod : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SpreadMethod"; }
#endif
    public:
        typedef Classes::SpreadMethod ClassType;

    public:
        SpreadMethod(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SpreadMethod : public Class
    {
        friend class ClassTraits::SpreadMethod;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SpreadMethod"; }
#endif
    public:
        typedef SpreadMethod SelfType;
        typedef SpreadMethod ClassType;
        
    private:
        SpreadMethod(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_PAD() const { return PAD; }
        const char* get_REFLECT() const { return REFLECT; }
        const char* get_REPEAT() const { return REPEAT; }


    protected:
        // AS3 API members.
        const char* PAD;
        const char* REFLECT;
        const char* REPEAT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

