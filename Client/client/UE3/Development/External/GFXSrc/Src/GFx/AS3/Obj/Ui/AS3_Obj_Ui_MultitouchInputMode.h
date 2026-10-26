//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_MultitouchInputMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_MultitouchInputMode_H
#define INC_AS3_Obj_Ui_MultitouchInputMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MultitouchInputMode;
}

namespace InstanceTraits
{
    class MultitouchInputMode;
}

namespace Classes
{
    class MultitouchInputMode;
}
    
namespace ClassTraits
{
    class MultitouchInputMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MultitouchInputMode"; }
#endif
    public:
        typedef Classes::MultitouchInputMode ClassType;

    public:
        MultitouchInputMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class MultitouchInputMode : public Class
    {
        friend class ClassTraits::MultitouchInputMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::MultitouchInputMode"; }
#endif
    public:
        typedef MultitouchInputMode SelfType;
        typedef MultitouchInputMode ClassType;
        
    private:
        MultitouchInputMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_GESTURE() const { return GESTURE; }
        const char* get_NONE() const { return NONE; }
        const char* get_TOUCH_POINT() const { return TOUCH_POINT; }


    protected:
        // AS3 API members.
        const char* GESTURE;
        const char* NONE;
        const char* TOUCH_POINT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

