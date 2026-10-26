//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLHistoryItem.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLHistoryItem.h"
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
    const ThunkInfo HTMLHistoryItem_ti[4] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "isPost", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "originalUrl", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "title", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "url", NULL, CT_Get, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    HTMLHistoryItem::HTMLHistoryItem(VM& vm)
    : Traits(vm, HTMLHistoryItemCI)
    {
//##protect##"ClassTraits::HTMLHistoryItem::HTMLHistoryItem()"
//##protect##"ClassTraits::HTMLHistoryItem::HTMLHistoryItem()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, HTMLHistoryItemCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLHistoryItem::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLHistoryItem(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLHistoryItemCI = {
    ClassInfo::CompileTime,
    "HTMLHistoryItem", "flash.html", &ObjectCI,
    ClassTraits::HTMLHistoryItem::MakeClassTraits,
    0,
    0,
    4,
    0,
    NULL,
    NULL,
    InstanceTraits::HTMLHistoryItem_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

