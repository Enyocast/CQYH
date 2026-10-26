//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Updater.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_Updater.h"
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
    const ThunkInfo Updater_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "update", NULL, CT_Method, 2, 2},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    Updater::Updater(VM& vm)
    : Traits(vm, UpdaterCI)
    {
//##protect##"ClassTraits::Updater::Updater()"
//##protect##"ClassTraits::Updater::Updater()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, UpdaterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Updater::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Updater(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo UpdaterCI = {
    ClassInfo::CompileTime,
    "Updater", "flash.desktop", &ObjectCI,
    ClassTraits::Updater::MakeClassTraits,
    0,
    0,
    1,
    0,
    NULL,
    NULL,
    InstanceTraits::Updater_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

