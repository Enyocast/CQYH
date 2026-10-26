//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_Mouse.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_Mouse_H
#define INC_AS3_Obj_Ui_Mouse_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Mouse;
}

namespace InstanceTraits
{
    class Mouse;
}

namespace Classes
{
    class Mouse;
}
    
namespace ClassTraits
{
    class Mouse : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Mouse"; }
#endif
    public:
        typedef Classes::Mouse ClassType;

    public:
        Mouse(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Mouse : public Class
    {
        friend class ClassTraits::Mouse;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Mouse"; }
#endif
    public:
        typedef Mouse SelfType;
        typedef Mouse ClassType;
        
    private:
        Mouse(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_cursorSet, 
            mid_cursorGet, 
            mid_hide, 
            mid_show, 
        };
        void cursorSet(Value& result, const ASString& value);
        void cursorGet(ASString& result);
        void hide(Value& result);
        void show(Value& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

