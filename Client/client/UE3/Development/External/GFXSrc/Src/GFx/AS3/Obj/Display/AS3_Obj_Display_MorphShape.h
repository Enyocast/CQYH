//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_MorphShape.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_MorphShape_H
#define INC_AS3_Obj_Display_MorphShape_H

#include "AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MorphShape;
}

namespace InstanceTraits
{
    class MorphShape;
}

namespace Classes
{
    class MorphShape;
}

namespace Instances
{
    class MorphShape : public Instances::DisplayObject
    {
        friend class InstanceTraits::MorphShape;
        
    public:
        typedef MorphShape SelfType;
        typedef Classes::MorphShape ClassType;
        typedef InstanceTraits::MorphShape TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::MorphShape"; }
#endif
    protected:
        MorphShape(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class MorphShape : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::MorphShape"; }
#endif
    public:
        MorphShape(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::MorphShape> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class MorphShape : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MorphShape"; }
#endif
    public:
        typedef Classes::MorphShape ClassType;

    public:
        MorphShape(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

