//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJobOptions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Printing_PrintJobOptions.h"
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
    PrintJobOptions::PrintJobOptions(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , printAsBitmap(false)
//##protect##"instance::PrintJobOptions::PrintJobOptions()$data"
//##protect##"instance::PrintJobOptions::PrintJobOptions()$data"
    {
//##protect##"instance::PrintJobOptions::PrintJobOptions()$code"
//##protect##"instance::PrintJobOptions::PrintJobOptions()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo PrintJobOptions::mi[PrintJobOptions::MemberInfoNum] = {
        {"printAsBitmap", OFFSETOF(Instances::PrintJobOptions, printAsBitmap), SlotInfo::BT_Boolean, 0},
    };


    PrintJobOptions::PrintJobOptions(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::PrintJobOptions::PrintJobOptions()"
//##protect##"InstanceTraits::PrintJobOptions::PrintJobOptions()"
        SetMemSize(sizeof(Instances::PrintJobOptions));

    }

    Pickable<Instances::PrintJobOptions> PrintJobOptions::MakeInstance(Traits& t)
    {
        return Pickable<Instances::PrintJobOptions>(new(t.Alloc()) Instances::PrintJobOptions(t));
    }

    void PrintJobOptions::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    PrintJobOptions::PrintJobOptions(VM& vm)
    : Traits(vm, PrintJobOptionsCI)
    {
//##protect##"ClassTraits::PrintJobOptions::PrintJobOptions()"
//##protect##"ClassTraits::PrintJobOptions::PrintJobOptions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::PrintJobOptions(vm, PrintJobOptionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PrintJobOptions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PrintJobOptions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PrintJobOptionsCI = {
    ClassInfo::CompileTime,
    "PrintJobOptions", "flash.printing", &ObjectCI,
    ClassTraits::PrintJobOptions::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::PrintJobOptions::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::PrintJobOptions::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

