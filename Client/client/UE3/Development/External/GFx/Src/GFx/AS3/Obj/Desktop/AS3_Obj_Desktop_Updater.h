//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Updater.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_Updater_H
#define INC_AS3_Obj_Desktop_Updater_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class File;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Updater;
}

namespace InstanceTraits
{
    class Updater;
}

namespace Classes
{
    class Updater;
}
    
namespace ClassTraits
{
    class Updater : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Updater"; }
#endif
    public:
        typedef Classes::Updater ClassType;

    public:
        Updater(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

