//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_SecurityDomain.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_SecurityDomain.h"
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

namespace Instances
{
    SecurityDomain::SecurityDomain(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::SecurityDomain::SecurityDomain()$data"
//##protect##"instance::SecurityDomain::SecurityDomain()$data"
    {
//##protect##"instance::SecurityDomain::SecurityDomain()$code"
//##protect##"instance::SecurityDomain::SecurityDomain()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{

    SecurityDomain::SecurityDomain(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SecurityDomain::SecurityDomain()"
//##protect##"InstanceTraits::SecurityDomain::SecurityDomain()"
        SetMemSize(sizeof(Instances::SecurityDomain));

    }

    Pickable<Instances::SecurityDomain> SecurityDomain::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SecurityDomain>(new(t.Alloc()) Instances::SecurityDomain(t));
    }

    void SecurityDomain::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    SecurityDomain::SecurityDomain(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::SecurityDomain::SecurityDomain()"
//##protect##"class_::SecurityDomain::SecurityDomain()"
    }
    void SecurityDomain::currentDomainGet(Value& result)
    {
//##protect##"class_::SecurityDomain::currentDomainGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::SecurityDomain::currentDomainGet()");
//##protect##"class_::SecurityDomain::currentDomainGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::SecurityDomain, Classes::SecurityDomain::mid_currentDomainGet, Value> TFunc_Classes_SecurityDomain_currentDomainGet;

template <> const TFunc_Classes_SecurityDomain_currentDomainGet::TMethod TFunc_Classes_SecurityDomain_currentDomainGet::Method = &Classes::SecurityDomain::currentDomainGet;

namespace ClassTraits
{
    const ThunkInfo SecurityDomain::ti[SecurityDomain::ThunkInfoNum] = {
        {TFunc_Classes_SecurityDomain_currentDomainGet::Func, &SecurityDomainCI, "currentDomain", NULL, CT_Get, 0, 0},
    };
    SecurityDomain::SecurityDomain(VM& vm)
    : Traits(vm, SecurityDomainCI)
    {
//##protect##"ClassTraits::SecurityDomain::SecurityDomain()"
//##protect##"ClassTraits::SecurityDomain::SecurityDomain()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SecurityDomain(vm, SecurityDomainCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SecurityDomain(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SecurityDomain::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SecurityDomain(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SecurityDomainCI = {
    ClassInfo::CompileTime,
    "SecurityDomain", "flash.system", &ObjectCI,
    ClassTraits::SecurityDomain::MakeClassTraits,
    ClassTraits::SecurityDomain::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::SecurityDomain::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

