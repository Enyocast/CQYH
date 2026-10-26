//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_ISimpleTextSelection.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Accessibility_ISimpleTextSelection_H
#define INC_AS3_Obj_Accessibility_ISimpleTextSelection_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ISimpleTextSelection;
}

namespace InstanceTraits
{
    class ISimpleTextSelection;
}

namespace Classes
{
    class ISimpleTextSelection;
}
    
namespace ClassTraits
{
    class ISimpleTextSelection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ISimpleTextSelection"; }
#endif
    public:
        typedef Classes::ISimpleTextSelection ClassType;

    public:
        ISimpleTextSelection(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

