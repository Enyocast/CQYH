//##protect##"disclaimer"
/**********************************************************************

Filename    :   .cpp
Content     :   
Created     :   Jul, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_GamePad.h"
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
    GamePad::GamePad(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::GamePad::GamePad()"
        PAD_NONE.SetUInt32(Pad_None);
        PAD_BACK.SetUInt32(Pad_Back);
        PAD_A.SetUInt32(Pad_A);
        PAD_B.SetUInt32(Pad_B);
        PAD_X.SetUInt32(Pad_X);
        PAD_Y.SetUInt32(Pad_Y);
        PAD_R1.SetUInt32(Pad_R1);
        PAD_L1.SetUInt32(Pad_L1);
        PAD_R2.SetUInt32(Pad_R2);
        PAD_L2.SetUInt32(Pad_L2);
        PAD_UP.SetUInt32(Pad_Up);
        PAD_DOWN.SetUInt32(Pad_Down);
        PAD_RIGHT.SetUInt32(Pad_Right);
        PAD_LEFT.SetUInt32(Pad_Left);
        PAD_PLUS.SetUInt32(Pad_Plus);
        PAD_MINUS.SetUInt32(Pad_Minus);
        PAD_1.SetUInt32(Pad_1);
        PAD_2.SetUInt32(Pad_2);
        PAD_H.SetUInt32(Pad_H);
        PAD_C.SetUInt32(Pad_C);
        PAD_Z.SetUInt32(Pad_Z);
        PAD_O.SetUInt32(Pad_O);
        PAD_T.SetUInt32(Pad_T);
        PAD_S.SetUInt32(Pad_S);
        PAD_SELECT.SetUInt32(Pad_Select);
        PAD_HOME.SetUInt32(Pad_Home);
        PAD_RT.SetUInt32(Pad_RT);
        PAD_LT.SetUInt32(Pad_LT);
//##protect##"class_::GamePad::GamePad()"
    }
    void GamePad::supportsAnalogEvents(bool& result)
    {
//##protect##"class_::GamePad::supportsAnalogEvents()"
        
#ifdef GFX_ENABLE_ANALOG_GAMEPAD
        result = true;
#else
        result = false;
#endif

//##protect##"class_::GamePad::supportsAnalogEvents()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::GamePad, Classes::GamePad::mid_supportsAnalogEvents, bool> TFunc_Classes_GamePad_supportsAnalogEvents;

template <> const TFunc_Classes_GamePad_supportsAnalogEvents::TMethod TFunc_Classes_GamePad_supportsAnalogEvents::Method = &Classes::GamePad::supportsAnalogEvents;

namespace ClassTraits
{
    const MemberInfo GamePad::mi[GamePad::MemberInfoNum] = {
        {"PAD_NONE", OFFSETOF(Classes::GamePad, PAD_NONE), SlotInfo::BT_Value, 1},
        {"PAD_BACK", OFFSETOF(Classes::GamePad, PAD_BACK), SlotInfo::BT_Value, 1},
        {"PAD_START", OFFSETOF(Classes::GamePad, PAD_START), SlotInfo::BT_Value, 1},
        {"PAD_A", OFFSETOF(Classes::GamePad, PAD_A), SlotInfo::BT_Value, 1},
        {"PAD_B", OFFSETOF(Classes::GamePad, PAD_B), SlotInfo::BT_Value, 1},
        {"PAD_X", OFFSETOF(Classes::GamePad, PAD_X), SlotInfo::BT_Value, 1},
        {"PAD_Y", OFFSETOF(Classes::GamePad, PAD_Y), SlotInfo::BT_Value, 1},
        {"PAD_R1", OFFSETOF(Classes::GamePad, PAD_R1), SlotInfo::BT_Value, 1},
        {"PAD_L1", OFFSETOF(Classes::GamePad, PAD_L1), SlotInfo::BT_Value, 1},
        {"PAD_R2", OFFSETOF(Classes::GamePad, PAD_R2), SlotInfo::BT_Value, 1},
        {"PAD_L2", OFFSETOF(Classes::GamePad, PAD_L2), SlotInfo::BT_Value, 1},
        {"PAD_UP", OFFSETOF(Classes::GamePad, PAD_UP), SlotInfo::BT_Value, 1},
        {"PAD_DOWN", OFFSETOF(Classes::GamePad, PAD_DOWN), SlotInfo::BT_Value, 1},
        {"PAD_RIGHT", OFFSETOF(Classes::GamePad, PAD_RIGHT), SlotInfo::BT_Value, 1},
        {"PAD_LEFT", OFFSETOF(Classes::GamePad, PAD_LEFT), SlotInfo::BT_Value, 1},
        {"PAD_PLUS", OFFSETOF(Classes::GamePad, PAD_PLUS), SlotInfo::BT_Value, 1},
        {"PAD_MINUS", OFFSETOF(Classes::GamePad, PAD_MINUS), SlotInfo::BT_Value, 1},
        {"PAD_1", OFFSETOF(Classes::GamePad, PAD_1), SlotInfo::BT_Value, 1},
        {"PAD_2", OFFSETOF(Classes::GamePad, PAD_2), SlotInfo::BT_Value, 1},
        {"PAD_H", OFFSETOF(Classes::GamePad, PAD_H), SlotInfo::BT_Value, 1},
        {"PAD_C", OFFSETOF(Classes::GamePad, PAD_C), SlotInfo::BT_Value, 1},
        {"PAD_Z", OFFSETOF(Classes::GamePad, PAD_Z), SlotInfo::BT_Value, 1},
        {"PAD_O", OFFSETOF(Classes::GamePad, PAD_O), SlotInfo::BT_Value, 1},
        {"PAD_T", OFFSETOF(Classes::GamePad, PAD_T), SlotInfo::BT_Value, 1},
        {"PAD_S", OFFSETOF(Classes::GamePad, PAD_S), SlotInfo::BT_Value, 1},
        {"PAD_SELECT", OFFSETOF(Classes::GamePad, PAD_SELECT), SlotInfo::BT_Value, 1},
        {"PAD_HOME", OFFSETOF(Classes::GamePad, PAD_HOME), SlotInfo::BT_Value, 1},
        {"PAD_RT", OFFSETOF(Classes::GamePad, PAD_RT), SlotInfo::BT_Value, 1},
        {"PAD_LT", OFFSETOF(Classes::GamePad, PAD_LT), SlotInfo::BT_Value, 1},
    };

    const ThunkInfo GamePad::ti[GamePad::ThunkInfoNum] = {
        {TFunc_Classes_GamePad_supportsAnalogEvents::Func, &BooleanCI, "supportsAnalogEvents", NULL, CT_Method, 0, 0},
    };
    GamePad::GamePad(VM& vm)
    : Traits(vm, GamePadCI)
    {
//##protect##"ClassTraits::GamePad::GamePad()"
//##protect##"ClassTraits::GamePad::GamePad()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, GamePadCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::GamePad(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> GamePad::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) GamePad(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo GamePadCI = {
    ClassInfo::CompileTime,
    "GamePad", "scaleform.gfx", &ObjectCI,
    ClassTraits::GamePad::MakeClassTraits,
    ClassTraits::GamePad::ThunkInfoNum,
    ClassTraits::GamePad::MemberInfoNum,
    0,
    0,
    ClassTraits::GamePad::ti,
    ClassTraits::GamePad::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

