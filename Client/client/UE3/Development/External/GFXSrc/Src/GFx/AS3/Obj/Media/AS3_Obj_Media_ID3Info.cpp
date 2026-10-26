//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_ID3Info.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_ID3Info.h"
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
    ID3Info::ID3Info(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , album(AS3::DefaultValue<ASString>(GetStringManager()))
    , artist(AS3::DefaultValue<ASString>(GetStringManager()))
    , comment(AS3::DefaultValue<ASString>(GetStringManager()))
    , genre(AS3::DefaultValue<ASString>(GetStringManager()))
    , songName(AS3::DefaultValue<ASString>(GetStringManager()))
    , track(AS3::DefaultValue<ASString>(GetStringManager()))
    , year(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::ID3Info::ID3Info()$data"
//##protect##"instance::ID3Info::ID3Info()$data"
    {
//##protect##"instance::ID3Info::ID3Info()$code"
//##protect##"instance::ID3Info::ID3Info()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo ID3Info::mi[ID3Info::MemberInfoNum] = {
        {"album", OFFSETOF(Instances::ID3Info, album), SlotInfo::BT_String, 0},
        {"artist", OFFSETOF(Instances::ID3Info, artist), SlotInfo::BT_String, 0},
        {"comment", OFFSETOF(Instances::ID3Info, comment), SlotInfo::BT_String, 0},
        {"genre", OFFSETOF(Instances::ID3Info, genre), SlotInfo::BT_String, 0},
        {"songName", OFFSETOF(Instances::ID3Info, songName), SlotInfo::BT_String, 0},
        {"track", OFFSETOF(Instances::ID3Info, track), SlotInfo::BT_String, 0},
        {"year", OFFSETOF(Instances::ID3Info, year), SlotInfo::BT_String, 0},
    };


    ID3Info::ID3Info(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ID3Info::ID3Info()"
//##protect##"InstanceTraits::ID3Info::ID3Info()"
        SetMemSize(sizeof(Instances::ID3Info));

    }

    Pickable<Instances::ID3Info> ID3Info::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ID3Info>(new(t.Alloc()) Instances::ID3Info(t));
    }

    void ID3Info::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ID3Info::ID3Info(VM& vm)
    : Traits(vm, ID3InfoCI)
    {
//##protect##"ClassTraits::ID3Info::ID3Info()"
//##protect##"ClassTraits::ID3Info::ID3Info()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ID3Info(vm, ID3InfoCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ID3Info::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ID3Info(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ID3InfoCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "ID3Info", "flash.media", &ObjectCI,
    ClassTraits::ID3Info::MakeClassTraits,
    0,
    0,
    0,
    InstanceTraits::ID3Info::MemberInfoNum,
    NULL,
    NULL,
    NULL,
    InstanceTraits::ID3Info::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

