//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_MorphShape.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_MorphShape.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace Instances
{
    MorphShape::MorphShape(InstanceTraits::Traits& t)
    : Instances::DisplayObject(t)
//##protect##"instance::MorphShape::MorphShape()$data"
//##protect##"instance::MorphShape::MorphShape()$data"
    {
//##protect##"instance::MorphShape::MorphShape()$code"
//##protect##"instance::MorphShape::MorphShape()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{

    MorphShape::MorphShape(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::MorphShape::MorphShape()"
        SetTraitsType(Traits_MorphShape);
//##protect##"InstanceTraits::MorphShape::MorphShape()"
        SetMemSize(sizeof(Instances::MorphShape));

    }

    Pickable<Instances::MorphShape> MorphShape::MakeInstance(Traits& t)
    {
        return Pickable<Instances::MorphShape>(new(t.Alloc()) Instances::MorphShape(t));
    }

    void MorphShape::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    MorphShape::MorphShape(VM& vm)
    : Traits(vm, MorphShapeCI)
    {
//##protect##"ClassTraits::MorphShape::MorphShape()"
        SetTraitsType(Traits_MorphShape);
//##protect##"ClassTraits::MorphShape::MorphShape()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::MorphShape(vm, MorphShapeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MorphShape::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MorphShape(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MorphShapeCI = {
    ClassInfo::CompileTime,
    "MorphShape", "flash.display", &DisplayObjectCI,
    ClassTraits::MorphShape::MakeClassTraits,
    0,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

