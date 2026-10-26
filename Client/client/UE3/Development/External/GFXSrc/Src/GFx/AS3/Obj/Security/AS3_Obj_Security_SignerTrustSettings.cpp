//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_SignerTrustSettings.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_SignerTrustSettings.h"
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
    SignerTrustSettings::SignerTrustSettings(ClassTraits::Traits& t)
    : Class(t)
    , CODE_SIGNING("codeSigning")
    , PLAYLIST_SIGNING("playlistSigning")
    , SIGNING("signing")
    {
//##protect##"class_::SignerTrustSettings::SignerTrustSettings()"
//##protect##"class_::SignerTrustSettings::SignerTrustSettings()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo SignerTrustSettings::mi[SignerTrustSettings::MemberInfoNum] = {
        {"CODE_SIGNING", OFFSETOF(Classes::SignerTrustSettings, CODE_SIGNING), SlotInfo::BT_ConstChar, 1},
        {"PLAYLIST_SIGNING", OFFSETOF(Classes::SignerTrustSettings, PLAYLIST_SIGNING), SlotInfo::BT_ConstChar, 1},
        {"SIGNING", OFFSETOF(Classes::SignerTrustSettings, SIGNING), SlotInfo::BT_ConstChar, 1},
    };

    SignerTrustSettings::SignerTrustSettings(VM& vm)
    : Traits(vm, SignerTrustSettingsCI)
    {
//##protect##"ClassTraits::SignerTrustSettings::SignerTrustSettings()"
//##protect##"ClassTraits::SignerTrustSettings::SignerTrustSettings()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SignerTrustSettingsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SignerTrustSettings(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SignerTrustSettings::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SignerTrustSettings(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SignerTrustSettingsCI = {
    ClassInfo::CompileTime,
    "SignerTrustSettings", "flash.security", &ObjectCI,
    ClassTraits::SignerTrustSettings::MakeClassTraits,
    0,
    ClassTraits::SignerTrustSettings::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::SignerTrustSettings::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

