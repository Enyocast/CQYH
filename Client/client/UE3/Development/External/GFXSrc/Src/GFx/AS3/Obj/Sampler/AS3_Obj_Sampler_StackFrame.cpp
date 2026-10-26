//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_StackFrame.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Sampler_StackFrame.h"
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
    StackFrame::StackFrame(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , file(AS3::DefaultValue<char*>(GetStringManager()))
    , line()
    , name(AS3::DefaultValue<char*>(GetStringManager()))
//##protect##"instance::StackFrame::StackFrame()$data"
//##protect##"instance::StackFrame::StackFrame()$data"
    {
//##protect##"instance::StackFrame::StackFrame()$code"
//##protect##"instance::StackFrame::StackFrame()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo StackFrame::ti[StackFrame::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo StackFrame::mi[StackFrame::MemberInfoNum] = {
        {"file", OFFSETOF(Instances::StackFrame, file), SlotInfo::BT_ConstChar, 1},
        {"line", OFFSETOF(Instances::StackFrame, line), SlotInfo::BT_UInt, 1},
        {"name", OFFSETOF(Instances::StackFrame, name), SlotInfo::BT_ConstChar, 1},
    };


    StackFrame::StackFrame(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::StackFrame::StackFrame()"
//##protect##"InstanceTraits::StackFrame::StackFrame()"
        SetMemSize(sizeof(Instances::StackFrame));

    }

    Pickable<Instances::StackFrame> StackFrame::MakeInstance(Traits& t)
    {
        return Pickable<Instances::StackFrame>(new(t.Alloc()) Instances::StackFrame(t));
    }

    void StackFrame::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    StackFrame::StackFrame(VM& vm)
    : Traits(vm, StackFrameCI)
    {
//##protect##"ClassTraits::StackFrame::StackFrame()"
//##protect##"ClassTraits::StackFrame::StackFrame()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::StackFrame(vm, StackFrameCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StackFrame::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StackFrame(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StackFrameCI = {
    ClassInfo::CompileTime,
    "StackFrame", "flash.sampler", &ObjectCI,
    ClassTraits::StackFrame::MakeClassTraits,
    0,
    0,
    InstanceTraits::StackFrame::ThunkInfoNum,
    InstanceTraits::StackFrame::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::StackFrame::ti,
    InstanceTraits::StackFrame::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

