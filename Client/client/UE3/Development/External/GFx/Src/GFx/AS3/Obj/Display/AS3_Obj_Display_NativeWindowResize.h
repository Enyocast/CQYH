//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowResize.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_NativeWindowResize_H
#define INC_AS3_Obj_Display_NativeWindowResize_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeWindowResize;
}

namespace InstanceTraits
{
    class NativeWindowResize;
}

namespace Classes
{
    class NativeWindowResize;
}
    
namespace ClassTraits
{
    class NativeWindowResize : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeWindowResize"; }
#endif
    public:
        typedef Classes::NativeWindowResize ClassType;

    public:
        NativeWindowResize(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 9 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NativeWindowResize : public Class
    {
        friend class ClassTraits::NativeWindowResize;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NativeWindowResize"; }
#endif
    public:
        typedef NativeWindowResize SelfType;
        typedef NativeWindowResize ClassType;
        
    private:
        NativeWindowResize(ClassTraits::Traits& t);
       
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
        const char* get_BOTTOM_LEFT() const { return BOTTOM_LEFT; }
        const char* get_BOTTOM_RIGHT() const { return BOTTOM_RIGHT; }
        const char* get_LEFT() const { return LEFT; }
        const char* get_NONE() const { return NONE; }
        const char* get_RIGHT() const { return RIGHT; }
        const char* get_TOP() const { return TOP; }
        const char* get_TOP_LEFT() const { return TOP_LEFT; }
        const char* get_TOP_RIGHT() const { return TOP_RIGHT; }


    protected:
        // AS3 API members.
        const char* BOTTOM;
        const char* BOTTOM_LEFT;
        const char* BOTTOM_RIGHT;
        const char* LEFT;
        const char* NONE;
        const char* RIGHT;
        const char* TOP;
        const char* TOP_LEFT;
        const char* TOP_RIGHT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

