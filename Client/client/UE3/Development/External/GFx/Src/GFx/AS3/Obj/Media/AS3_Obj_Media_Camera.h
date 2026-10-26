//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Camera.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_Camera_H
#define INC_AS3_Obj_Media_Camera_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Camera;
}

namespace InstanceTraits
{
    class Camera;
}

namespace Classes
{
    class Camera;
}
    
namespace ClassTraits
{
    class Camera : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Camera"; }
#endif
    public:
        typedef Classes::Camera ClassType;

    public:
        Camera(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Camera : public Class
    {
        friend class ClassTraits::Camera;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Camera"; }
#endif
    public:
        typedef Camera SelfType;
        typedef Camera ClassType;
        
    private:
        Camera(ClassTraits::Traits& t);
       
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

