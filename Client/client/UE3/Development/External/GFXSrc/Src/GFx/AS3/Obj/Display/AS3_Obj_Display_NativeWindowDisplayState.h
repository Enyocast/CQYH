//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindowDisplayState.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_NativeWindowDisplayState_H
#define INC_AS3_Obj_Display_NativeWindowDisplayState_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeWindowDisplayState;
}

namespace InstanceTraits
{
    class NativeWindowDisplayState;
}

namespace Classes
{
    class NativeWindowDisplayState;
}
    
namespace ClassTraits
{
    class NativeWindowDisplayState : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeWindowDisplayState"; }
#endif
    public:
        typedef Classes::NativeWindowDisplayState ClassType;

    public:
        NativeWindowDisplayState(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NativeWindowDisplayState : public Class
    {
        friend class ClassTraits::NativeWindowDisplayState;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NativeWindowDisplayState"; }
#endif
    public:
        typedef NativeWindowDisplayState SelfType;
        typedef NativeWindowDisplayState ClassType;
        
    private:
        NativeWindowDisplayState(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_MAXIMIZED() const { return MAXIMIZED; }
        const char* get_MINIMIZED() const { return MINIMIZED; }
        const char* get_NORMAL() const { return NORMAL; }


    protected:
        // AS3 API members.
        const char* MAXIMIZED;
        const char* MINIMIZED;
        const char* NORMAL;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

