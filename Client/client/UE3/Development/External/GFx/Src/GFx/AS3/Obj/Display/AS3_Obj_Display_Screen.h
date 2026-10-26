//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Screen.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Screen_H
#define INC_AS3_Obj_Display_Screen_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Rectangle;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Screen;
}

namespace InstanceTraits
{
    class Screen;
}

namespace Classes
{
    class Screen;
}
    
namespace ClassTraits
{
    class Screen : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Screen"; }
#endif
    public:
        typedef Classes::Screen ClassType;

    public:
        Screen(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Screen : public Class
    {
        friend class ClassTraits::Screen;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Screen"; }
#endif
    public:
        typedef Screen SelfType;
        typedef Screen ClassType;
        
    private:
        Screen(ClassTraits::Traits& t);
       
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

