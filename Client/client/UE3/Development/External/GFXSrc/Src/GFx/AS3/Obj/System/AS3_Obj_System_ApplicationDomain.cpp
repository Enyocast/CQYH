//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_ApplicationDomain.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_ApplicationDomain.h"
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
typedef ThunkFunc0<Instances::ApplicationDomain, Instances::ApplicationDomain::mid_parentDomainGet, Value> TFunc_Instances_ApplicationDomain_parentDomainGet;
typedef ThunkFunc1<Instances::ApplicationDomain, Instances::ApplicationDomain::mid_getDefinition, Value, const ASString&> TFunc_Instances_ApplicationDomain_getDefinition;
typedef ThunkFunc1<Instances::ApplicationDomain, Instances::ApplicationDomain::mid_hasDefinition, bool, const ASString&> TFunc_Instances_ApplicationDomain_hasDefinition;

template <> const TFunc_Instances_ApplicationDomain_parentDomainGet::TMethod TFunc_Instances_ApplicationDomain_parentDomainGet::Method = &Instances::ApplicationDomain::parentDomainGet;
template <> const TFunc_Instances_ApplicationDomain_getDefinition::TMethod TFunc_Instances_ApplicationDomain_getDefinition::Method = &Instances::ApplicationDomain::getDefinition;
template <> const TFunc_Instances_ApplicationDomain_hasDefinition::TMethod TFunc_Instances_ApplicationDomain_hasDefinition::Method = &Instances::ApplicationDomain::hasDefinition;

namespace Instances
{
    ApplicationDomain::ApplicationDomain(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::ApplicationDomain::ApplicationDomain()$data"
//##protect##"instance::ApplicationDomain::ApplicationDomain()$data"
    {
//##protect##"instance::ApplicationDomain::ApplicationDomain()$code"
//##protect##"instance::ApplicationDomain::ApplicationDomain()$code"
    }

    void ApplicationDomain::parentDomainGet(Value& result)
    {
//##protect##"instance::ApplicationDomain::parentDomainGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("ApplicationDomain::parentDomainGet()");
//##protect##"instance::ApplicationDomain::parentDomainGet()"
    }
    void ApplicationDomain::getDefinition(Value& result, const ASString& name)
    {
//##protect##"instance::ApplicationDomain::getDefinition()"
        SF_UNUSED2(result, name);
        WARN_NOT_IMPLEMENTED("ApplicationDomain::getDefinition()");
//##protect##"instance::ApplicationDomain::getDefinition()"
    }
    void ApplicationDomain::hasDefinition(bool& result, const ASString& name)
    {
//##protect##"instance::ApplicationDomain::hasDefinition()"
        SF_UNUSED2(result, name);
        WARN_NOT_IMPLEMENTED("ApplicationDomain::hasDefinition()");
//##protect##"instance::ApplicationDomain::hasDefinition()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ApplicationDomain::ti[ApplicationDomain::ThunkInfoNum] = {
        {TFunc_Instances_ApplicationDomain_parentDomainGet::Func, &ApplicationDomainCI, "parentDomain", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ApplicationDomain_getDefinition::Func, &ObjectCI, "getDefinition", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ApplicationDomain_hasDefinition::Func, &BooleanCI, "hasDefinition", NULL, CT_Method, 1, 1},
    };

    ApplicationDomain::ApplicationDomain(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ApplicationDomain::ApplicationDomain()"
//##protect##"InstanceTraits::ApplicationDomain::ApplicationDomain()"
        SetMemSize(sizeof(Instances::ApplicationDomain));

    }

    Pickable<Instances::ApplicationDomain> ApplicationDomain::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ApplicationDomain>(new(t.Alloc()) Instances::ApplicationDomain(t));
    }

    void ApplicationDomain::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ApplicationDomain::ApplicationDomain(VM& vm)
    : Traits(vm, ApplicationDomainCI)
    {
//##protect##"ClassTraits::ApplicationDomain::ApplicationDomain()"
//##protect##"ClassTraits::ApplicationDomain::ApplicationDomain()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ApplicationDomain(vm, ApplicationDomainCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ApplicationDomain::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ApplicationDomain(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ApplicationDomainCI = {
    ClassInfo::CompileTime,
    "ApplicationDomain", "flash.system", &ObjectCI,
    ClassTraits::ApplicationDomain::MakeClassTraits,
    0,
    0,
    InstanceTraits::ApplicationDomain::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::ApplicationDomain::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

