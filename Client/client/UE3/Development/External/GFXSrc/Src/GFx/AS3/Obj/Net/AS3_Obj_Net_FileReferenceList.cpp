//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_FileReferenceList.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_FileReferenceList.h"
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

namespace InstanceTraits
{
    const ThunkInfo FileReferenceList_ti[2] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "fileList", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "browse", NULL, CT_Method, 0, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    FileReferenceList::FileReferenceList(VM& vm)
    : Traits(vm, FileReferenceListCI)
    {
//##protect##"ClassTraits::FileReferenceList::FileReferenceList()"
//##protect##"ClassTraits::FileReferenceList::FileReferenceList()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, FileReferenceListCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FileReferenceList::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileReferenceList(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileReferenceListCI = {
    ClassInfo::CompileTime,
    "FileReferenceList", "flash.net", &EventDispatcherCI,
    ClassTraits::FileReferenceList::MakeClassTraits,
    0,
    0,
    2,
    0,
    NULL,
    NULL,
    InstanceTraits::FileReferenceList_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

