//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_IMEEventEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_IMEEventEx.h"
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
    IMEEventEx::IMEEventEx(InstanceTraits::Traits& t)
    : Instances::Event(t)
    , message(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::IMEEventEx::IMEEventEx()$data"
//##protect##"instance::IMEEventEx::IMEEventEx()$data"
    {
//##protect##"instance::IMEEventEx::IMEEventEx()$code"
//##protect##"instance::IMEEventEx::IMEEventEx()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo IMEEventEx::mi[IMEEventEx::MemberInfoNum] = {
        {"message", OFFSETOF(Instances::IMEEventEx, message), SlotInfo::BT_String, 0},
    };


    IMEEventEx::IMEEventEx(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::IMEEventEx::IMEEventEx()"
//##protect##"InstanceTraits::IMEEventEx::IMEEventEx()"
        SetMemSize(sizeof(Instances::IMEEventEx));

    }

    Pickable<Instances::IMEEventEx> IMEEventEx::MakeInstance(Traits& t)
    {
        return Pickable<Instances::IMEEventEx>(new(t.Alloc()) Instances::IMEEventEx(t));
    }

    void IMEEventEx::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    IMEEventEx::IMEEventEx(ClassTraits::Traits& t)
    : Class(t)
    , SET_CURRENT_INPUT_LANGUAGE("SetCurrentInputLanguage")
    , SET_SUPPORTED_LANGUAGES("SetSupportedLanguages")
    , SET_SUPPORTED_IMENAMES("SetSupportedIMENames")
    , SET_IMENAME("SetIMEName")
    , SET_CURRENT_LANGUAGE("SetCurrentLanguage")
    , REMOVE_STATUS_WINDOW("RemoveStatusWindow")
    , DISPLAY_STATUS_WINDOW("DisplayStatusWindow")
    , SET_CONVERSION_STATUS("SetConversionStatus")
    {
//##protect##"class_::IMEEventEx::IMEEventEx()"
//##protect##"class_::IMEEventEx::IMEEventEx()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo IMEEventEx::mi[IMEEventEx::MemberInfoNum] = {
        {"SET_CURRENT_INPUT_LANGUAGE", OFFSETOF(Classes::IMEEventEx, SET_CURRENT_INPUT_LANGUAGE), SlotInfo::BT_ConstChar, 1},
        {"SET_SUPPORTED_LANGUAGES", OFFSETOF(Classes::IMEEventEx, SET_SUPPORTED_LANGUAGES), SlotInfo::BT_ConstChar, 1},
        {"SET_SUPPORTED_IMENAMES", OFFSETOF(Classes::IMEEventEx, SET_SUPPORTED_IMENAMES), SlotInfo::BT_ConstChar, 1},
        {"SET_IMENAME", OFFSETOF(Classes::IMEEventEx, SET_IMENAME), SlotInfo::BT_ConstChar, 1},
        {"SET_CURRENT_LANGUAGE", OFFSETOF(Classes::IMEEventEx, SET_CURRENT_LANGUAGE), SlotInfo::BT_ConstChar, 1},
        {"REMOVE_STATUS_WINDOW", OFFSETOF(Classes::IMEEventEx, REMOVE_STATUS_WINDOW), SlotInfo::BT_ConstChar, 1},
        {"DISPLAY_STATUS_WINDOW", OFFSETOF(Classes::IMEEventEx, DISPLAY_STATUS_WINDOW), SlotInfo::BT_ConstChar, 1},
        {"SET_CONVERSION_STATUS", OFFSETOF(Classes::IMEEventEx, SET_CONVERSION_STATUS), SlotInfo::BT_ConstChar, 1},
    };

    IMEEventEx::IMEEventEx(VM& vm)
    : Traits(vm, IMEEventExCI)
    {
//##protect##"ClassTraits::IMEEventEx::IMEEventEx()"
//##protect##"ClassTraits::IMEEventEx::IMEEventEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::IMEEventEx(vm, IMEEventExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IMEEventEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IMEEventEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMEEventEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMEEventExCI = {
    ClassInfo::CompileTime,
    "IMEEventEx", "scaleform.gfx", &EventCI,
    ClassTraits::IMEEventEx::MakeClassTraits,
    0,
    ClassTraits::IMEEventEx::MemberInfoNum,
    0,
    InstanceTraits::IMEEventEx::MemberInfoNum,
    NULL,
    ClassTraits::IMEEventEx::mi,
    NULL,
    InstanceTraits::IMEEventEx::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

