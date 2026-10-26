//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragManager.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeDragManager.h"
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
    const ThunkInfo NativeDragManager_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "dropAction", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    NativeDragManager::NativeDragManager(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::NativeDragManager::NativeDragManager()"
//##protect##"class_::NativeDragManager::NativeDragManager()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo NativeDragManager_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "acceptDragDrop", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "doDrag", NULL, CT_Method, 2, 5},
    };
    NativeDragManager::NativeDragManager(VM& vm)
    : Traits(vm, NativeDragManagerCI)
    {
//##protect##"ClassTraits::NativeDragManager::NativeDragManager()"
//##protect##"ClassTraits::NativeDragManager::NativeDragManager()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, NativeDragManagerCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::NativeDragManager(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeDragManager::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeDragManager(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeDragManagerCI = {
    ClassInfo::CompileTime,
    "NativeDragManager", "flash.desktop", &ObjectCI,
    ClassTraits::NativeDragManager::MakeClassTraits,
    2,
    0,
    1,
    0,
    ClassTraits::NativeDragManager_ti,
    NULL,
    InstanceTraits::NativeDragManager_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

