//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJob.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Printing_PrintJob.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "../Display/AS3_Obj_Display_Sprite.h"
#include "AS3_Obj_Printing_PrintJobOptions.h"
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
    const ThunkInfo PrintJob_ti[8] = {
        {ThunkInfo::EmptyFunc, &StringCI, "orientation", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "pageHeight", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "pageWidth", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "paperHeight", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "paperWidth", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "addPage", NULL, CT_Method, 1, 4},
        {ThunkInfo::EmptyFunc, NULL, "send", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "start", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    PrintJob::PrintJob(VM& vm)
    : Traits(vm, PrintJobCI)
    {
//##protect##"ClassTraits::PrintJob::PrintJob()"
//##protect##"ClassTraits::PrintJob::PrintJob()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, PrintJobCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PrintJob::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PrintJob(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PrintJobCI = {
    ClassInfo::CompileTime,
    "PrintJob", "flash.printing", &EventDispatcherCI,
    ClassTraits::PrintJob::MakeClassTraits,
    0,
    0,
    8,
    0,
    NULL,
    NULL,
    InstanceTraits::PrintJob_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

