//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_ISearchableText.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_ISearchableText.h"
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
    const ThunkInfo ISearchableText_ti[1] = {
        {ThunkInfo::EmptyFunc, &StringCI, "searchText", "flash.accessibility:ISearchableText", CT_Get, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    ISearchableText::ISearchableText(VM& vm)
    : Traits(vm, ISearchableTextCI)
    {
//##protect##"ClassTraits::ISearchableText::ISearchableText()"
//##protect##"ClassTraits::ISearchableText::ISearchableText()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, ISearchableTextCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ISearchableText::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ISearchableText(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ISearchableTextCI = {
    ClassInfo::CompileTime,
    "ISearchableText", "flash.accessibility", NULL,
    ClassTraits::ISearchableText::MakeClassTraits,
    0,
    0,
    1,
    0,
    NULL,
    NULL,
    InstanceTraits::ISearchableText_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

