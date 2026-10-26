//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Catch.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Catch.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
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

namespace Instances
{
    Catch::Catch(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Catch::Catch()$data"
//##protect##"instance::Catch::Catch()$data"
    {
//##protect##"instance::Catch::Catch()$code"
//##protect##"instance::Catch::Catch()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{

    Catch::Catch(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Catch::Catch()"
//##protect##"InstanceTraits::Catch::Catch()"
        SetMemSize(sizeof(Instances::Catch));

    }

    Pickable<Instances::Catch> Catch::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Catch>(new(t.Alloc()) Instances::Catch(t));
    }

    void Catch::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
    Catch::Catch(VMAbcFile& file, VM& vm, const Abc::MethodBodyInfo::ExceptionInfo& e)
    : Traits(vm, CatchCI)
    {
        // Adobe is doing weird stuff with exception  variable name.
        UInt32 ind = e.GetVariableNameInd();
        if (ind)
            ind = static_cast<UInt32>(file.GetConstPool().GetStringCount() - ind);

        const ASString name = file.GetInternedString(ind);
        const SInt32 et_ind = e.GetExceptionTypeInd();
        SlotInfo::BindingType bt = SlotInfo::BT_Value;

        if (et_ind != 0)
        {
            const Abc::Multiname& amn = file.GetConstPool().GetMultiname(et_ind);

            bt = GetBindingType(file, amn);
        }

        AddSlot(name, GetVM().MakePublicNamespace(), bt, AbsoluteIndex(0));
        CalculateMemSize(sizeof(Instances::Catch));
    }
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    Catch::Catch(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Catch::Catch()"
//##protect##"class_::Catch::Catch()"
    }
//##protect##"class_$methods"
    Pickable<Instances::Catch> Catch::MakeInstance(VMAbcFile& file, const Abc::MethodBodyInfo::ExceptionInfo& e)
    {
        SPtr<InstanceTraits::Catch> tr = MakePickable(SF_HEAP_AUTO_NEW(this) InstanceTraits::Catch(file, GetVM(), e));
        return tr->MakeInstance(*tr);
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    Catch::Catch(VM& vm)
    : Traits(vm, CatchCI)
    {
//##protect##"ClassTraits::Catch::Catch()"
//##protect##"ClassTraits::Catch::Catch()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Catch(vm, CatchCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Catch(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Catch::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Catch(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo CatchCI = {
    ClassInfo::CompileTime,
    "Catch", "", &ObjectCI,
    ClassTraits::Catch::MakeClassTraits,
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

