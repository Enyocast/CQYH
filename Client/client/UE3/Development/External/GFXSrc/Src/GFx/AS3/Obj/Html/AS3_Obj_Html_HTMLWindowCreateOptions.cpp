//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLWindowCreateOptions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLWindowCreateOptions.h"
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
    HTMLWindowCreateOptions::HTMLWindowCreateOptions(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , fullscreen(false)
    , height(NumberUtil::NaN())
    , locationBarVisible(false)
    , menuBarVisible(false)
    , resizable(false)
    , scrollBarsVisible(true)
    , statusBarVisible(false)
    , toolBarVisible(false)
    , width(NumberUtil::NaN())
    , x(NumberUtil::NaN())
    , y(NumberUtil::NaN())
//##protect##"instance::HTMLWindowCreateOptions::HTMLWindowCreateOptions()$data"
//##protect##"instance::HTMLWindowCreateOptions::HTMLWindowCreateOptions()$data"
    {
//##protect##"instance::HTMLWindowCreateOptions::HTMLWindowCreateOptions()$code"
//##protect##"instance::HTMLWindowCreateOptions::HTMLWindowCreateOptions()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo HTMLWindowCreateOptions::mi[HTMLWindowCreateOptions::MemberInfoNum] = {
        {"fullscreen", OFFSETOF(Instances::HTMLWindowCreateOptions, fullscreen), SlotInfo::BT_Boolean, 0},
        {"height", OFFSETOF(Instances::HTMLWindowCreateOptions, height), SlotInfo::BT_Number, 0},
        {"locationBarVisible", OFFSETOF(Instances::HTMLWindowCreateOptions, locationBarVisible), SlotInfo::BT_Boolean, 0},
        {"menuBarVisible", OFFSETOF(Instances::HTMLWindowCreateOptions, menuBarVisible), SlotInfo::BT_Boolean, 0},
        {"resizable", OFFSETOF(Instances::HTMLWindowCreateOptions, resizable), SlotInfo::BT_Boolean, 0},
        {"scrollBarsVisible", OFFSETOF(Instances::HTMLWindowCreateOptions, scrollBarsVisible), SlotInfo::BT_Boolean, 0},
        {"statusBarVisible", OFFSETOF(Instances::HTMLWindowCreateOptions, statusBarVisible), SlotInfo::BT_Boolean, 0},
        {"toolBarVisible", OFFSETOF(Instances::HTMLWindowCreateOptions, toolBarVisible), SlotInfo::BT_Boolean, 0},
        {"width", OFFSETOF(Instances::HTMLWindowCreateOptions, width), SlotInfo::BT_Number, 0},
        {"x", OFFSETOF(Instances::HTMLWindowCreateOptions, x), SlotInfo::BT_Number, 0},
        {"y", OFFSETOF(Instances::HTMLWindowCreateOptions, y), SlotInfo::BT_Number, 0},
    };


    HTMLWindowCreateOptions::HTMLWindowCreateOptions(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::HTMLWindowCreateOptions::HTMLWindowCreateOptions()"
//##protect##"InstanceTraits::HTMLWindowCreateOptions::HTMLWindowCreateOptions()"
        SetMemSize(sizeof(Instances::HTMLWindowCreateOptions));

    }

    Pickable<Instances::HTMLWindowCreateOptions> HTMLWindowCreateOptions::MakeInstance(Traits& t)
    {
        return Pickable<Instances::HTMLWindowCreateOptions>(new(t.Alloc()) Instances::HTMLWindowCreateOptions(t));
    }

    void HTMLWindowCreateOptions::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    HTMLWindowCreateOptions::HTMLWindowCreateOptions(VM& vm)
    : Traits(vm, HTMLWindowCreateOptionsCI)
    {
//##protect##"ClassTraits::HTMLWindowCreateOptions::HTMLWindowCreateOptions()"
//##protect##"ClassTraits::HTMLWindowCreateOptions::HTMLWindowCreateOptions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::HTMLWindowCreateOptions(vm, HTMLWindowCreateOptionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLWindowCreateOptions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLWindowCreateOptions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLWindowCreateOptionsCI = {
    ClassInfo::CompileTime,
    "HTMLWindowCreateOptions", "flash.html", &ObjectCI,
    ClassTraits::HTMLWindowCreateOptions::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::HTMLWindowCreateOptions::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::HTMLWindowCreateOptions::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

