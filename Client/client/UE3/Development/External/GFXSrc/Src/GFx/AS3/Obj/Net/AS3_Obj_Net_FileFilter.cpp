//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_FileFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_FileFilter.h"
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
    const ThunkInfo FileFilter_ti[6] = {
        {ThunkInfo::EmptyFunc, &StringCI, "description", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "description", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "extension", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "extension", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "macType", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "macType", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    FileFilter::FileFilter(VM& vm)
    : Traits(vm, FileFilterCI)
    {
//##protect##"ClassTraits::FileFilter::FileFilter()"
//##protect##"ClassTraits::FileFilter::FileFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FileFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FileFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FileFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FileFilterCI = {
    ClassInfo::CompileTime,
    "FileFilter", "flash.net", &ObjectCI,
    ClassTraits::FileFilter::MakeClassTraits,
    0,
    0,
    6,
    0,
    NULL,
    NULL,
    InstanceTraits::FileFilter_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

