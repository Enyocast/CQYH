//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_ActionScriptVersion.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_ActionScriptVersion.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    ActionScriptVersion::ActionScriptVersion(ClassTraits::Traits& t)
    : Class(t)
    , ACTIONSCRIPT2(2)
    , ACTIONSCRIPT3(3)
    {
//##protect##"class_::ActionScriptVersion::ActionScriptVersion()"
//##protect##"class_::ActionScriptVersion::ActionScriptVersion()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo ActionScriptVersion::mi[ActionScriptVersion::MemberInfoNum] = {
        {"ACTIONSCRIPT2", OFFSETOF(Classes::ActionScriptVersion, ACTIONSCRIPT2), SlotInfo::BT_UInt, 1},
        {"ACTIONSCRIPT3", OFFSETOF(Classes::ActionScriptVersion, ACTIONSCRIPT3), SlotInfo::BT_UInt, 1},
    };

    ActionScriptVersion::ActionScriptVersion(VM& vm)
    : Traits(vm, ActionScriptVersionCI)
    {
//##protect##"ClassTraits::ActionScriptVersion::ActionScriptVersion()"
//##protect##"ClassTraits::ActionScriptVersion::ActionScriptVersion()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ActionScriptVersionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ActionScriptVersion(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ActionScriptVersion::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ActionScriptVersion(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ActionScriptVersionCI = {
    ClassInfo::CompileTime,
    "ActionScriptVersion", "flash.display", &ObjectCI,
    ClassTraits::ActionScriptVersion::MakeClassTraits,
    0,
    ClassTraits::ActionScriptVersion::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::ActionScriptVersion::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

