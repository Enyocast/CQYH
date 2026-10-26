//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_CSMSettings.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_CSMSettings.h"
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
    CSMSettings::CSMSettings(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , fontSize()
    , insideCutoff()
    , outsideCutoff()
//##protect##"instance::CSMSettings::CSMSettings()$data"
//##protect##"instance::CSMSettings::CSMSettings()$data"
    {
//##protect##"instance::CSMSettings::CSMSettings()$code"
//##protect##"instance::CSMSettings::CSMSettings()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo CSMSettings::mi[CSMSettings::MemberInfoNum] = {
        {"fontSize", OFFSETOF(Instances::CSMSettings, fontSize), SlotInfo::BT_Number, 0},
        {"insideCutoff", OFFSETOF(Instances::CSMSettings, insideCutoff), SlotInfo::BT_Number, 0},
        {"outsideCutoff", OFFSETOF(Instances::CSMSettings, outsideCutoff), SlotInfo::BT_Number, 0},
    };


    CSMSettings::CSMSettings(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::CSMSettings::CSMSettings()"
//##protect##"InstanceTraits::CSMSettings::CSMSettings()"
        SetMemSize(sizeof(Instances::CSMSettings));

    }

    Pickable<Instances::CSMSettings> CSMSettings::MakeInstance(Traits& t)
    {
        return Pickable<Instances::CSMSettings>(new(t.Alloc()) Instances::CSMSettings(t));
    }

    void CSMSettings::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    CSMSettings::CSMSettings(VM& vm)
    : Traits(vm, CSMSettingsCI)
    {
//##protect##"ClassTraits::CSMSettings::CSMSettings()"
//##protect##"ClassTraits::CSMSettings::CSMSettings()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::CSMSettings(vm, CSMSettingsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> CSMSettings::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) CSMSettings(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo CSMSettingsCI = {
    ClassInfo::CompileTime,
    "CSMSettings", "flash.text", &ObjectCI,
    ClassTraits::CSMSettings::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::CSMSettings::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::CSMSettings::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

