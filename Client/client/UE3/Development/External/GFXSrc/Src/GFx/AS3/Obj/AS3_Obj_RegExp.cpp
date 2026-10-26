//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_RegExp.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_RegExp.h"
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
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_sourceGet, ASString> TFunc_Instances_RegExp_sourceGet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_globalGet, bool> TFunc_Instances_RegExp_globalGet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_ignoreCaseGet, bool> TFunc_Instances_RegExp_ignoreCaseGet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_multilineGet, bool> TFunc_Instances_RegExp_multilineGet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_lastIndexGet, SInt32> TFunc_Instances_RegExp_lastIndexGet;
typedef ThunkFunc1<Instances::RegExp, Instances::RegExp::mid_lastIndexSet, Value, SInt32> TFunc_Instances_RegExp_lastIndexSet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_dotallGet, bool> TFunc_Instances_RegExp_dotallGet;
typedef ThunkFunc0<Instances::RegExp, Instances::RegExp::mid_extendedGet, bool> TFunc_Instances_RegExp_extendedGet;
typedef ThunkFunc1<Instances::RegExp, Instances::RegExp::mid_AS3exec, Value, const ASString&> TFunc_Instances_RegExp_AS3exec;
typedef ThunkFunc1<Instances::RegExp, Instances::RegExp::mid_AS3test, bool, const ASString&> TFunc_Instances_RegExp_AS3test;

template <> const TFunc_Instances_RegExp_sourceGet::TMethod TFunc_Instances_RegExp_sourceGet::Method = &Instances::RegExp::sourceGet;
template <> const TFunc_Instances_RegExp_globalGet::TMethod TFunc_Instances_RegExp_globalGet::Method = &Instances::RegExp::globalGet;
template <> const TFunc_Instances_RegExp_ignoreCaseGet::TMethod TFunc_Instances_RegExp_ignoreCaseGet::Method = &Instances::RegExp::ignoreCaseGet;
template <> const TFunc_Instances_RegExp_multilineGet::TMethod TFunc_Instances_RegExp_multilineGet::Method = &Instances::RegExp::multilineGet;
template <> const TFunc_Instances_RegExp_lastIndexGet::TMethod TFunc_Instances_RegExp_lastIndexGet::Method = &Instances::RegExp::lastIndexGet;
template <> const TFunc_Instances_RegExp_lastIndexSet::TMethod TFunc_Instances_RegExp_lastIndexSet::Method = &Instances::RegExp::lastIndexSet;
template <> const TFunc_Instances_RegExp_dotallGet::TMethod TFunc_Instances_RegExp_dotallGet::Method = &Instances::RegExp::dotallGet;
template <> const TFunc_Instances_RegExp_extendedGet::TMethod TFunc_Instances_RegExp_extendedGet::Method = &Instances::RegExp::extendedGet;
template <> const TFunc_Instances_RegExp_AS3exec::TMethod TFunc_Instances_RegExp_AS3exec::Method = &Instances::RegExp::AS3exec;
template <> const TFunc_Instances_RegExp_AS3test::TMethod TFunc_Instances_RegExp_AS3test::Method = &Instances::RegExp::AS3test;

namespace Instances
{
    RegExp::RegExp(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::RegExp::RegExp()$data"
//##protect##"instance::RegExp::RegExp()$data"
    {
//##protect##"instance::RegExp::RegExp()$code"
//##protect##"instance::RegExp::RegExp()$code"
    }

    void RegExp::sourceGet(ASString& result)
    {
//##protect##"instance::RegExp::sourceGet()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("RegExp::sourceGet()");
//##protect##"instance::RegExp::sourceGet()"
    }
    void RegExp::globalGet(bool& result)
    {
//##protect##"instance::RegExp::globalGet()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::globalGet()"
    }
    void RegExp::ignoreCaseGet(bool& result)
    {
//##protect##"instance::RegExp::ignoreCaseGet()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::ignoreCaseGet()"
    }
    void RegExp::multilineGet(bool& result)
    {
//##protect##"instance::RegExp::multilineGet()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::multilineGet()"
    }
    void RegExp::lastIndexGet(SInt32& result)
    {
//##protect##"instance::RegExp::lastIndexGet()"
        result = AS3::DefaultValue<int>(GetStringManager());
//##protect##"instance::RegExp::lastIndexGet()"
    }
    void RegExp::lastIndexSet(Value& result, SInt32 i)
    {
//##protect##"instance::RegExp::lastIndexSet()"
        SF_UNUSED2(result, i);
        NOT_IMPLEMENTED("RegExp::lastIndexSet()");
//##protect##"instance::RegExp::lastIndexSet()"
    }
    void RegExp::dotallGet(bool& result)
    {
//##protect##"instance::RegExp::dotallGet()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::dotallGet()"
    }
    void RegExp::extendedGet(bool& result)
    {
//##protect##"instance::RegExp::extendedGet()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::extendedGet()"
    }
    void RegExp::AS3exec(Value& result, const ASString& s)
    {
//##protect##"instance::RegExp::AS3exec()"
        SF_UNUSED1(s);
        result = AS3::DefaultValue<Instances::Object*>(GetStringManager());
//##protect##"instance::RegExp::AS3exec()"
    }
    void RegExp::AS3test(bool& result, const ASString& s)
    {
//##protect##"instance::RegExp::AS3test()"
        SF_UNUSED1(s);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::RegExp::AS3test()"
    }

//##protect##"instance$methods"
    void RegExp::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
        SF_UNUSED4(ti, _this, argc, argv);
        result = vm.GetStringManager().CreateConstString("/(?:)/");
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo RegExp::ti[RegExp::ThunkInfoNum] = {
        {TFunc_Instances_RegExp_sourceGet::Func, &StringCI, "source", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_globalGet::Func, &BooleanCI, "global", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_ignoreCaseGet::Func, &BooleanCI, "ignoreCase", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_multilineGet::Func, &BooleanCI, "multiline", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_lastIndexGet::Func, &int_CI, "lastIndex", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_lastIndexSet::Func, NULL, "lastIndex", NULL, CT_Set, 1, 1},
        {TFunc_Instances_RegExp_dotallGet::Func, &BooleanCI, "dotall", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_extendedGet::Func, &BooleanCI, "extended", NULL, CT_Get, 0, 0},
        {TFunc_Instances_RegExp_AS3exec::Func, &ObjectCI, "exec", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_RegExp_AS3test::Func, &BooleanCI, "test", NS_AS3, CT_Method, 1, 1},
    };

    RegExp::RegExp(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::RegExp::RegExp()"
//##protect##"InstanceTraits::RegExp::RegExp()"
        SetMemSize(sizeof(Instances::RegExp));

    }

    Pickable<Instances::RegExp> RegExp::MakeInstance(Traits& t)
    {
        return Pickable<Instances::RegExp>(new(t.Alloc()) Instances::RegExp(t));
    }

    void RegExp::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    RegExp::RegExp(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::RegExp::RegExp()"
//##protect##"class_::RegExp::RegExp()"
    }
//##protect##"class_$methods"
    void RegExp::Call(const Value& _this, Value& result, unsigned argc, const Value* const argv)
    {
        SF_UNUSED(_this);

        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    Pickable<AS3::Object> RegExp::MakePrototype() const
    {
        InstanceTraits::RegExp& itr = static_cast<InstanceTraits::RegExp&>(GetClassTraits().GetInstanceTraits());
        return itr.MakeInstance(itr);
    }

    void RegExp::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        InitPrototypeFromVTableCheckType(obj);

        // Created manually.
        static ThunkInfo f[] = {
            {&Instances::RegExp::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
        };
        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    RegExp::RegExp(VM& vm)
    : Traits(vm, RegExpCI)
    {
//##protect##"ClassTraits::RegExp::RegExp()"
//##protect##"ClassTraits::RegExp::RegExp()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::RegExp(vm, RegExpCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::RegExp(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> RegExp::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) RegExp(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo RegExpCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "RegExp", "", &ObjectCI,
    ClassTraits::RegExp::MakeClassTraits,
    0,
    0,
    InstanceTraits::RegExp::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::RegExp::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

