//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FileListEvent.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_FileListEvent.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
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
    FileListEvent::FileListEvent(InstanceTraits::Traits& t)
    : Instances::Event(t)
    , files()
//##protect##"instance::FileListEvent::FileListEvent()$data"
//##protect##"instance::FileListEvent::FileListEvent()$data"
    {
//##protect##"instance::FileListEvent::FileListEvent()$code"
//##protect##"instance::FileListEvent::FileListEvent()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const MemberInfo FileListEvent::mi[FileListEvent::MemberInfoNum] = {
        {"files", OFFSETOF(Instances::FileListEvent, files), SlotInfo::BT_ObjectCpp, 0},
    };


    FileListEvent::FileListEvent(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::FileListEvent::FileListEvent()"
//##protect##"InstanceTraits::FileListEvent::FileListEvent()"
        SetMemSize(sizeof(Instances::FileListEvent));

    }

    Pickable<Instances::FileListEvent> FileListEvent::MakeInstance(Traits& t)
    {
        return Pickable<Instances::FileListEvent>(new(t.Alloc()) Instances::FileListEvent(t));
    }

    void FileListEvent::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    FileListEvent::FileListEvent(ClassTraits::Traits& t)
    : Class(t)
    , DIRECTORY_LISTING("directoryListing")
    , SELECT_MULTIPLE("selectMultiple")
    {
//##protect##"class_::FileListEvent::FileListEvent()"
//##protect##"class_::FileListEvent::FileListEvent()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo FileListEvent::mi[FileListEvent::MemberInfoNum] = {
        {"DIRECTORY_LISTING", OFFSETOF(Classes::FileListEvent, DIRECTORY_LISTING), SlotInfo::BT_ConstChar, 1},
        {"SELECT_MULTIPLE", OFFSETOF(Classes::FileListEvent, SELECT_MULTIPLE), SlotInfo::BT_ConstChar, 1},
    };

    FileListEvent::FileListEvent(VM& vm)
    : Traits(vm, FileListEventCI)
    {
//##protect##"ClassTraits::FileListEvent::FileListEvent()"
//##protect##"ClassTraits::FileListEvent::FileListEvent()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::FileListEvent(vm, FileListEventCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FileListEvent(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FileListEvent::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileListEvent(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileListEventCI = {
    ClassInfo::CompileTime,
    "FileListEvent", "flash.events", &EventCI,
    ClassTraits::FileListEvent::MakeClassTraits,
    0,
    ClassTraits::FileListEvent::MemberInfoNum,
    0,
    InstanceTraits::FileListEvent::MemberInfoNum,
    NULL,
    ClassTraits::FileListEvent::mi,
    NULL,
    InstanceTraits::FileListEvent::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

