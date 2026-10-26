//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_MouseCursor.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_MouseCursor_H
#define INC_AS3_Obj_Ui_MouseCursor_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MouseCursor;
}

namespace InstanceTraits
{
    class MouseCursor;
}

namespace Classes
{
    class MouseCursor;
}
    
namespace ClassTraits
{
    class MouseCursor : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MouseCursor"; }
#endif
    public:
        typedef Classes::MouseCursor ClassType;

    public:
        MouseCursor(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 5 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class MouseCursor : public Class
    {
        friend class ClassTraits::MouseCursor;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::MouseCursor"; }
#endif
    public:
        typedef MouseCursor SelfType;
        typedef MouseCursor ClassType;
        
    private:
        MouseCursor(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ARROW() const { return ARROW; }
        const char* get_AUTO() const { return AUTO; }
        const char* get_BUTTON() const { return BUTTON; }
        const char* get_HAND() const { return HAND; }
        const char* get_IBEAM() const { return IBEAM; }


    protected:
        // AS3 API members.
        const char* ARROW;
        const char* AUTO;
        const char* BUTTON;
        const char* HAND;
        const char* IBEAM;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

