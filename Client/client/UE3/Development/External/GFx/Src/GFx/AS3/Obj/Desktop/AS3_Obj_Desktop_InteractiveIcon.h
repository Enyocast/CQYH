//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_InteractiveIcon.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_InteractiveIcon_H
#define INC_AS3_Obj_Desktop_InteractiveIcon_H

#include "AS3_Obj_Desktop_Icon.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class InteractiveIcon;
}

namespace InstanceTraits
{
    class InteractiveIcon;
}

namespace Classes
{
    class InteractiveIcon;
}
    
namespace ClassTraits
{
    class InteractiveIcon : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::InteractiveIcon"; }
#endif
    public:
        typedef Classes::InteractiveIcon ClassType;

    public:
        InteractiveIcon(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

