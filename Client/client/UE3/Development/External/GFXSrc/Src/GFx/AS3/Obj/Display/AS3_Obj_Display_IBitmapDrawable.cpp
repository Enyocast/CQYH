//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_IBitmapDrawable.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_IBitmapDrawable.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"


namespace ClassTraits
{
    IBitmapDrawable::IBitmapDrawable(VM& vm)
    : Traits(vm, IBitmapDrawableCI)
    {
//##protect##"ClassTraits::IBitmapDrawable::IBitmapDrawable()"
//##protect##"ClassTraits::IBitmapDrawable::IBitmapDrawable()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, IBitmapDrawableCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IBitmapDrawable::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IBitmapDrawable(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IBitmapDrawableCI = {
    ClassInfo::CompileTime,
    "IBitmapDrawable", "flash.display", NULL,
    ClassTraits::IBitmapDrawable::MakeClassTraits,
    0,
    0,
    0,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

