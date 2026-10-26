//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityImplementation.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_AccessibilityImplementation.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
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
    AccessibilityImplementation::AccessibilityImplementation(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , errno()
    , stub()
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$data"
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$data"
    {
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$code"
//##protect##"instance::AccessibilityImplementation::AccessibilityImplementation()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo AccessibilityImplementation::ti[AccessibilityImplementation::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, NULL, "accDoDefaultAction", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "accLocation", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "accSelect", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, &StringCI, "get_accDefaultAction", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "get_accFocus", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "get_accName", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "get_accRole", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "get_accSelection", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "get_accState", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "get_accValue", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "getChildIDArray", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isLabeledBy", NULL, CT_Method, 1, 1},
    };
    const MemberInfo AccessibilityImplementation::mi[AccessibilityImplementation::MemberInfoNum] = {
        {"errno", OFFSETOF(Instances::AccessibilityImplementation, errno), SlotInfo::BT_UInt, 0},
        {"stub", OFFSETOF(Instances::AccessibilityImplementation, stub), SlotInfo::BT_Boolean, 0},
    };


    AccessibilityImplementation::AccessibilityImplementation(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::AccessibilityImplementation::AccessibilityImplementation()"
//##protect##"InstanceTraits::AccessibilityImplementation::AccessibilityImplementation()"
        SetMemSize(sizeof(Instances::AccessibilityImplementation));

    }

    Pickable<Instances::AccessibilityImplementation> AccessibilityImplementation::MakeInstance(Traits& t)
    {
        return Pickable<Instances::AccessibilityImplementation>(new(t.Alloc()) Instances::AccessibilityImplementation(t));
    }

    void AccessibilityImplementation::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    AccessibilityImplementation::AccessibilityImplementation(VM& vm)
    : Traits(vm, AccessibilityImplementationCI)
    {
//##protect##"ClassTraits::AccessibilityImplementation::AccessibilityImplementation()"
//##protect##"ClassTraits::AccessibilityImplementation::AccessibilityImplementation()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::AccessibilityImplementation(vm, AccessibilityImplementationCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> AccessibilityImplementation::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AccessibilityImplementation(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo AccessibilityImplementationCI = {
    ClassInfo::CompileTime,
    "AccessibilityImplementation", "flash.accessibility", &ObjectCI,
    ClassTraits::AccessibilityImplementation::MakeClassTraits,
    0,
    0,
    InstanceTraits::AccessibilityImplementation::ThunkInfoNum,
    InstanceTraits::AccessibilityImplementation::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::AccessibilityImplementation::ti,
    InstanceTraits::AccessibilityImplementation::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

