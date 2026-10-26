//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextLineMetrics.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextLineMetrics.h"
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
    TextLineMetrics::TextLineMetrics(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , ascent()
    , descent()
    , height()
    , leading()
    , width()
    , x()
//##protect##"instance::TextLineMetrics::TextLineMetrics()$data"
//##protect##"instance::TextLineMetrics::TextLineMetrics()$data"
    {
//##protect##"instance::TextLineMetrics::TextLineMetrics()$code"
//##protect##"instance::TextLineMetrics::TextLineMetrics()$code"
    }


//##protect##"instance$methods"
    void TextLineMetrics::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0)
        {
            if (argc >= 1) argv[0].Convert2Number(ascent).DoNotCheck();
            if (argc >= 2) argv[1].Convert2Number(descent).DoNotCheck();
            if (argc >= 3) argv[2].Convert2Number(height).DoNotCheck();
            if (argc >= 4) argv[3].Convert2Number(leading).DoNotCheck();
            if (argc >= 5) argv[4].Convert2Number(width).DoNotCheck();
            if (argc >= 6) argv[5].Convert2Number(x).DoNotCheck();
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo TextLineMetrics::mi[TextLineMetrics::MemberInfoNum] = {
        {"ascent", OFFSETOF(Instances::TextLineMetrics, ascent), SlotInfo::BT_Number, 0},
        {"descent", OFFSETOF(Instances::TextLineMetrics, descent), SlotInfo::BT_Number, 0},
        {"height", OFFSETOF(Instances::TextLineMetrics, height), SlotInfo::BT_Number, 0},
        {"leading", OFFSETOF(Instances::TextLineMetrics, leading), SlotInfo::BT_Number, 0},
        {"width", OFFSETOF(Instances::TextLineMetrics, width), SlotInfo::BT_Number, 0},
        {"x", OFFSETOF(Instances::TextLineMetrics, x), SlotInfo::BT_Number, 0},
    };


    TextLineMetrics::TextLineMetrics(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextLineMetrics::TextLineMetrics()"
//##protect##"InstanceTraits::TextLineMetrics::TextLineMetrics()"
        SetMemSize(sizeof(Instances::TextLineMetrics));

    }

    Pickable<Instances::TextLineMetrics> TextLineMetrics::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextLineMetrics>(new(t.Alloc()) Instances::TextLineMetrics(t));
    }

    void TextLineMetrics::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    TextLineMetrics::TextLineMetrics(VM& vm)
    : Traits(vm, TextLineMetricsCI)
    {
//##protect##"ClassTraits::TextLineMetrics::TextLineMetrics()"
//##protect##"ClassTraits::TextLineMetrics::TextLineMetrics()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextLineMetrics(vm, TextLineMetricsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextLineMetrics::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextLineMetrics(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextLineMetricsCI = {
    ClassInfo::CompileTime,
    "TextLineMetrics", "flash.text", &ObjectCI,
    ClassTraits::TextLineMetrics::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::TextLineMetrics::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::TextLineMetrics::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

