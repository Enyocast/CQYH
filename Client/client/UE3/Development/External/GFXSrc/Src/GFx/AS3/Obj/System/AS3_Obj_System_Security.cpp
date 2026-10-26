//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_Security.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_Security.h"
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

namespace InstanceTraits
{
    const ThunkInfo Security_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "exactSettings", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    Security::Security(ClassTraits::Traits& t)
    : Class(t)
    , APPLICATION("application")
    , LOCAL_TRUSTED("localTrusted")
    , LOCAL_WITH_FILE("localWithFile")
    , LOCAL_WITH_NETWORK("localWithNetwork")
    , REMOTE("remote")
    {
//##protect##"class_::Security::Security()"
//##protect##"class_::Security::Security()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo Security::mi[Security::MemberInfoNum] = {
        {"APPLICATION", OFFSETOF(Classes::Security, APPLICATION), SlotInfo::BT_ConstChar, 1},
        {"LOCAL_TRUSTED", OFFSETOF(Classes::Security, LOCAL_TRUSTED), SlotInfo::BT_ConstChar, 1},
        {"LOCAL_WITH_FILE", OFFSETOF(Classes::Security, LOCAL_WITH_FILE), SlotInfo::BT_ConstChar, 1},
        {"LOCAL_WITH_NETWORK", OFFSETOF(Classes::Security, LOCAL_WITH_NETWORK), SlotInfo::BT_ConstChar, 1},
        {"REMOTE", OFFSETOF(Classes::Security, REMOTE), SlotInfo::BT_ConstChar, 1},
    };

    const ThunkInfo Security::ti[Security::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, NULL, "allowDomain", NULL, CT_Method, 0, 1023},
        {ThunkInfo::EmptyFunc, NULL, "allowInsecureDomain", NULL, CT_Method, 0, 1023},
        {ThunkInfo::EmptyFunc, NULL, "loadPolicyFile", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "showSettings", NULL, CT_Method, 0, 1},
    };
    Security::Security(VM& vm)
    : Traits(vm, SecurityCI)
    {
//##protect##"ClassTraits::Security::Security()"
//##protect##"ClassTraits::Security::Security()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SecurityCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Security(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Security::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Security(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SecurityCI = {
    ClassInfo::CompileTime,
    "Security", "flash.system", &ObjectCI,
    ClassTraits::Security::MakeClassTraits,
    ClassTraits::Security::ThunkInfoNum,
    ClassTraits::Security::MemberInfoNum,
    1,
    0,
    ClassTraits::Security::ti,
    ClassTraits::Security::mi,
    InstanceTraits::Security_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

