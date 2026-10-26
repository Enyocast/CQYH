//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_FileReference.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_FileReference.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_URLRequest.h"
#include "../AS3_Obj_Date.h"
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
    const ThunkInfo FileReference_ti[12] = {
        {ThunkInfo::EmptyFunc, &DateCI, "creationDate", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "creator", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "extension", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &DateCI, "modificationDate", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "name", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "size", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "type", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "browse", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "cancel", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "download", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "upload", NULL, CT_Method, 1, 3},
        {ThunkInfo::EmptyFunc, NULL, "uploadUnencoded", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    FileReference::FileReference(VM& vm)
    : Traits(vm, FileReferenceCI)
    {
//##protect##"ClassTraits::FileReference::FileReference()"
//##protect##"ClassTraits::FileReference::FileReference()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, FileReferenceCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FileReference::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileReference(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileReferenceCI = {
    ClassInfo::CompileTime,
    "FileReference", "flash.net", &EventDispatcherCI,
    ClassTraits::FileReference::MakeClassTraits,
    0,
    0,
    12,
    0,
    NULL,
    NULL,
    InstanceTraits::FileReference_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

