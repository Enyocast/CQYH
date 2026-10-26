//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GradientGlowFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_GradientGlowFilter_H
#define INC_AS3_Obj_Filters_GradientGlowFilter_H

#include "AS3_Obj_Filters_BitmapFilter.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class GradientGlowFilter;
}

namespace InstanceTraits
{
    class GradientGlowFilter;
}

namespace Classes
{
    class GradientGlowFilter;
}
    
namespace ClassTraits
{
    class GradientGlowFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GradientGlowFilter"; }
#endif
    public:
        typedef Classes::GradientGlowFilter ClassType;

    public:
        GradientGlowFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

