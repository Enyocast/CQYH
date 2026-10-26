//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityProperties.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_AccessibilityProperties.h"
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
    AccessibilityProperties::AccessibilityProperties(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , description(AS3::DefaultValue<ASString>(GetStringManager()))
    , forceSimple()
    , name(AS3::DefaultValue<ASString>(GetStringManager()))
    , noAutoLabeling()
    , shortcut(AS3::DefaultValue<ASString>(GetStringManager()))
    , silent()
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$data"
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$data"
    {
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$code"
//##protect##"instance::AccessibilityProperties::AccessibilityProperties()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo AccessibilityProperties::mi[AccessibilityProperties::MemberInfoNum] = {
        {"description", OFFSETOF(Instances::AccessibilityProperties, description), SlotInfo::BT_String, 0},
        {"forceSimple", OFFSETOF(Instances::AccessibilityProperties, forceSimple), SlotInfo::BT_Boolean, 0},
        {"name", OFFSETOF(Instances::AccessibilityProperties, name), SlotInfo::BT_String, 0},
        {"noAutoLabeling", OFFSETOF(Instances::AccessibilityProperties, noAutoLabeling), SlotInfo::BT_Boolean, 0},
        {"shortcut", OFFSETOF(Instances::AccessibilityProperties, shortcut), SlotInfo::BT_String, 0},
        {"silent", OFFSETOF(Instances::AccessibilityProperties, silent), SlotInfo::BT_Boolean, 0},
    };


    AccessibilityProperties::AccessibilityProperties(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::AccessibilityProperties::AccessibilityProperties()"
//##protect##"InstanceTraits::AccessibilityProperties::AccessibilityProperties()"
        SetMemSize(sizeof(Instances::AccessibilityProperties));

    }

    Pickable<Instances::AccessibilityProperties> AccessibilityProperties::MakeInstance(Traits& t)
    {
        return Pickable<Instances::AccessibilityProperties>(new(t.Alloc()) Instances::AccessibilityProperties(t));
    }

    void AccessibilityProperties::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    AccessibilityProperties::AccessibilityProperties(VM& vm)
    : Traits(vm, AccessibilityPropertiesCI)
    {
//##protect##"ClassTraits::AccessibilityProperties::AccessibilityProperties()"
//##protect##"ClassTraits::AccessibilityProperties::AccessibilityProperties()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::AccessibilityProperties(vm, AccessibilityPropertiesCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> AccessibilityProperties::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) AccessibilityProperties(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo AccessibilityPropertiesCI = {
    ClassInfo::CompileTime,
    "AccessibilityProperties", "flash.accessibility", &ObjectCI,
    ClassTraits::AccessibilityProperties::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::AccessibilityProperties::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::AccessibilityProperties::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

