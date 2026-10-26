//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_IExternalizable.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_IExternalizable.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Utils_IDataOutput.h"
#include "AS3_Obj_Utils_IDataInput.h"
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
    const ThunkInfo IExternalizable_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "readExternal", "flash.utils:IExternalizable", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "writeExternal", "flash.utils:IExternalizable", CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    IExternalizable::IExternalizable(VM& vm)
    : Traits(vm, IExternalizableCI)
    {
//##protect##"ClassTraits::IExternalizable::IExternalizable()"
//##protect##"ClassTraits::IExternalizable::IExternalizable()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, IExternalizableCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IExternalizable::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IExternalizable(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IExternalizableCI = {
    ClassInfo::CompileTime,
    "IExternalizable", "flash.utils", NULL,
    ClassTraits::IExternalizable::MakeClassTraits,
    0,
    0,
    2,
    0,
    NULL,
    NULL,
    InstanceTraits::IExternalizable_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

