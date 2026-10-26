//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BitmapDataChannel.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_BitmapDataChannel.h"
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
    BitmapDataChannel::BitmapDataChannel(ClassTraits::Traits& t)
    : Class(t)
    , ALPHA(8)
    , BLUE(4)
    , GREEN(2)
    , RED(1)
    {
//##protect##"class_::BitmapDataChannel::BitmapDataChannel()"
//##protect##"class_::BitmapDataChannel::BitmapDataChannel()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo BitmapDataChannel::mi[BitmapDataChannel::MemberInfoNum] = {
        {"ALPHA", OFFSETOF(Classes::BitmapDataChannel, ALPHA), SlotInfo::BT_UInt, 1},
        {"BLUE", OFFSETOF(Classes::BitmapDataChannel, BLUE), SlotInfo::BT_UInt, 1},
        {"GREEN", OFFSETOF(Classes::BitmapDataChannel, GREEN), SlotInfo::BT_UInt, 1},
        {"RED", OFFSETOF(Classes::BitmapDataChannel, RED), SlotInfo::BT_UInt, 1},
    };

    BitmapDataChannel::BitmapDataChannel(VM& vm)
    : Traits(vm, BitmapDataChannelCI)
    {
//##protect##"ClassTraits::BitmapDataChannel::BitmapDataChannel()"
//##protect##"ClassTraits::BitmapDataChannel::BitmapDataChannel()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, BitmapDataChannelCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::BitmapDataChannel(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BitmapDataChannel::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapDataChannel(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapDataChannelCI = {
    ClassInfo::CompileTime,
    "BitmapDataChannel", "flash.display", &ObjectCI,
    ClassTraits::BitmapDataChannel::MakeClassTraits,
    0,
    ClassTraits::BitmapDataChannel::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::BitmapDataChannel::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

