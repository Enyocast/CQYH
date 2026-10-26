//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_SecurityPanel.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_SecurityPanel.h"
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
    SecurityPanel::SecurityPanel(ClassTraits::Traits& t)
    : Class(t)
    , CAMERA("camera")
    , DEFAULT("default")
    , DISPLAY("display")
    , LOCAL_STORAGE("localStorage")
    , MICROPHONE("microphone")
    , PRIVACY("privacy")
    , SETTINGS_MANAGER("settingsManager")
    {
//##protect##"class_::SecurityPanel::SecurityPanel()"
//##protect##"class_::SecurityPanel::SecurityPanel()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SecurityPanel::mi[SecurityPanel::MemberInfoNum] = {
        {"CAMERA", OFFSETOF(Classes::SecurityPanel, CAMERA), SlotInfo::BT_ConstChar, 1},
        {"DEFAULT", OFFSETOF(Classes::SecurityPanel, DEFAULT), SlotInfo::BT_ConstChar, 1},
        {"DISPLAY", OFFSETOF(Classes::SecurityPanel, DISPLAY), SlotInfo::BT_ConstChar, 1},
        {"LOCAL_STORAGE", OFFSETOF(Classes::SecurityPanel, LOCAL_STORAGE), SlotInfo::BT_ConstChar, 1},
        {"MICROPHONE", OFFSETOF(Classes::SecurityPanel, MICROPHONE), SlotInfo::BT_ConstChar, 1},
        {"PRIVACY", OFFSETOF(Classes::SecurityPanel, PRIVACY), SlotInfo::BT_ConstChar, 1},
        {"SETTINGS_MANAGER", OFFSETOF(Classes::SecurityPanel, SETTINGS_MANAGER), SlotInfo::BT_ConstChar, 1},
    };

    SecurityPanel::SecurityPanel(VM& vm)
    : Traits(vm, SecurityPanelCI)
    {
//##protect##"ClassTraits::SecurityPanel::SecurityPanel()"
//##protect##"ClassTraits::SecurityPanel::SecurityPanel()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SecurityPanelCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SecurityPanel(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SecurityPanel::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SecurityPanel(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SecurityPanelCI = {
    ClassInfo::CompileTime,
    "SecurityPanel", "flash.system", &ObjectCI,
    ClassTraits::SecurityPanel::MakeClassTraits,
    0,
    ClassTraits::SecurityPanel::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::SecurityPanel::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

