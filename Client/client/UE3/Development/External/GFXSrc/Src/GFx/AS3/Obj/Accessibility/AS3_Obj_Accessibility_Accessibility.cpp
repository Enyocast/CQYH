//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_Accessibility.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Accessibility_Accessibility.h"
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
    Accessibility::Accessibility(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Accessibility::Accessibility()"
//##protect##"class_::Accessibility::Accessibility()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo Accessibility_ti[2] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "active", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "updateProperties", NULL, CT_Method, 0, 0},
    };
    Accessibility::Accessibility(VM& vm)
    : Traits(vm, AccessibilityCI)
    {
//##protect##"ClassTraits::Accessibility::Accessibility()"
//##protect##"ClassTraits::Accessibility::Accessibility()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, AccessibilityCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Accessibility(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Accessibility::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Accessibility(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo AccessibilityCI = {
    ClassInfo::CompileTime,
    "Accessibility", "flash.accessibility", &ObjectCI,
    ClassTraits::Accessibility::MakeClassTraits,
    2,
    0,
    0,
    0,
    ClassTraits::Accessibility_ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

