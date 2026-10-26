//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_IMECandidateListStyle.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_IMECandidateListStyle.h"
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
    IMECandidateListStyle::IMECandidateListStyle(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , textColor(-1)
    , selectedTextColor(-1)
    , fontSize(-1)
    , backgroundColor(-1)
    , selectedBackgroundColor(-1)
    , indexBackgroundColor(-1)
    , selectedIndexBackgroundColor(-1)
    , readingWindowTextColor(-1)
    , readingWindowBackgroundColor(-1)
    , readingWindowFontSize(-1)
//##protect##"instance::IMECandidateListStyle::IMECandidateListStyle()$data"
//##protect##"instance::IMECandidateListStyle::IMECandidateListStyle()$data"
    {
//##protect##"instance::IMECandidateListStyle::IMECandidateListStyle()$code"
//##protect##"instance::IMECandidateListStyle::IMECandidateListStyle()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo IMECandidateListStyle::mi[IMECandidateListStyle::MemberInfoNum] = {
        {"textColor", OFFSETOF(Instances::IMECandidateListStyle, textColor), SlotInfo::BT_Int, 0},
        {"selectedTextColor", OFFSETOF(Instances::IMECandidateListStyle, selectedTextColor), SlotInfo::BT_Int, 0},
        {"fontSize", OFFSETOF(Instances::IMECandidateListStyle, fontSize), SlotInfo::BT_Int, 0},
        {"backgroundColor", OFFSETOF(Instances::IMECandidateListStyle, backgroundColor), SlotInfo::BT_Int, 0},
        {"selectedBackgroundColor", OFFSETOF(Instances::IMECandidateListStyle, selectedBackgroundColor), SlotInfo::BT_Int, 0},
        {"indexBackgroundColor", OFFSETOF(Instances::IMECandidateListStyle, indexBackgroundColor), SlotInfo::BT_Int, 0},
        {"selectedIndexBackgroundColor", OFFSETOF(Instances::IMECandidateListStyle, selectedIndexBackgroundColor), SlotInfo::BT_Int, 0},
        {"readingWindowTextColor", OFFSETOF(Instances::IMECandidateListStyle, readingWindowTextColor), SlotInfo::BT_Int, 0},
        {"readingWindowBackgroundColor", OFFSETOF(Instances::IMECandidateListStyle, readingWindowBackgroundColor), SlotInfo::BT_Int, 0},
        {"readingWindowFontSize", OFFSETOF(Instances::IMECandidateListStyle, readingWindowFontSize), SlotInfo::BT_Int, 0},
    };


    IMECandidateListStyle::IMECandidateListStyle(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::IMECandidateListStyle::IMECandidateListStyle()"
//##protect##"InstanceTraits::IMECandidateListStyle::IMECandidateListStyle()"
        SetMemSize(sizeof(Instances::IMECandidateListStyle));

    }

    Pickable<Instances::IMECandidateListStyle> IMECandidateListStyle::MakeInstance(Traits& t)
    {
        return Pickable<Instances::IMECandidateListStyle>(new(t.Alloc()) Instances::IMECandidateListStyle(t));
    }

    void IMECandidateListStyle::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    IMECandidateListStyle::IMECandidateListStyle(VM& vm)
    : Traits(vm, IMECandidateListStyleCI)
    {
//##protect##"ClassTraits::IMECandidateListStyle::IMECandidateListStyle()"
//##protect##"ClassTraits::IMECandidateListStyle::IMECandidateListStyle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::IMECandidateListStyle(vm, IMECandidateListStyleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IMECandidateListStyle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMECandidateListStyle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMECandidateListStyleCI = {
    ClassInfo::CompileTime,
    "IMECandidateListStyle", "scaleform.gfx", &ObjectCI,
    ClassTraits::IMECandidateListStyle::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::IMECandidateListStyle::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::IMECandidateListStyle::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

