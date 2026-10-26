//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowType.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_NativeWindowType_H
#define INC_AS3_Obj_Display_NativeWindowType_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeWindowType;
}

namespace InstanceTraits
{
    class NativeWindowType;
}

namespace Classes
{
    class NativeWindowType;
}
    
namespace ClassTraits
{
    class NativeWindowType : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeWindowType"; }
#endif
    public:
        typedef Classes::NativeWindowType ClassType;

    public:
        NativeWindowType(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NativeWindowType : public Class
    {
        friend class ClassTraits::NativeWindowType;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NativeWindowType"; }
#endif
    public:
        typedef NativeWindowType SelfType;
        typedef NativeWindowType ClassType;
        
    private:
        NativeWindowType(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_LIGHTWEIGHT() const { return LIGHTWEIGHT; }
        const char* get_NORMAL() const { return NORMAL; }
        const char* get_UTILITY() const { return UTILITY; }


    protected:
        // AS3 API members.
        const char* LIGHTWEIGHT;
        const char* NORMAL;
        const char* UTILITY;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

