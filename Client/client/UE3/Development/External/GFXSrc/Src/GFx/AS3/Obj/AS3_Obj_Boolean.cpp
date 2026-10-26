//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Boolean.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Boolean.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "Kernel/SF_MsgFormat.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace InstanceTraits
{
    const ThunkInfo Boolean::ti[Boolean::ThunkInfoNum] = {
        {&InstanceTraits::Boolean::AS3toString, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
        {&InstanceTraits::Boolean::AS3valueOf, &BooleanCI, "valueOf", NS_AS3, CT_Method, 0, 0},
    };

    Boolean::Boolean(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Boolean::Boolean()"
        SetTraitsType(Traits_Boolean);
//##protect##"InstanceTraits::Boolean::Boolean()"

    }

    void Boolean::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t); SF_ASSERT(false);
    }

    void Boolean::AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toString()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsBool())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = vm.GetStringManager().GetBuiltin(_this.AsBool() ? AS3Builtin_true : AS3Builtin_false);
//##protect##"InstanceTraits::AS3toString()"
    }
    void Boolean::AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3valueOf()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsBool())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = _this;
//##protect##"InstanceTraits::AS3valueOf()"
    }
    void Boolean::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toStringProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassBoolean().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_false);
        else
            AS3toString(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::toStringProto()"
    }
    void Boolean::valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::valueOfProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassBoolean().GetPrototype())
            // This method is called on a prototype object.
            result.SetBool(false);
        else
            AS3valueOf(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::valueOfProto()"
    }
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    const ThunkInfo Boolean::ti[Boolean::ThunkInfoNum] = {
        {&InstanceTraits::Boolean::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {&InstanceTraits::Boolean::valueOfProto, &BooleanCI, "valueOf", NULL, CT_Method, 0, 0},
    };

    Boolean::Boolean(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Boolean::Boolean()"
//##protect##"class_::Boolean::Boolean()"
    }

    void Boolean::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void Boolean::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    void Boolean::Construct(Value& result, unsigned argc, const Value* argv, bool /*extCall*/)
    {
        if (argc > 0)
            result.SetBool(argv[0].Convert2Boolean());
        else
            result.SetBool(false);
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    Boolean::Boolean(VM& vm)
    : Traits(vm, BooleanCI)
    {
//##protect##"ClassTraits::Boolean::Boolean()"
        SetTraitsType(Traits_Boolean);
//##protect##"ClassTraits::Boolean::Boolean()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Boolean(vm, BooleanCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Boolean(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Boolean::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Boolean(vm));
    }
//##protect##"ClassTraits$methods"
    bool Boolean::Coerce(const Value& value, Value& result) const
    {
        return CoerceValue(value, result);
    }
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BooleanCI = {
    ClassInfo::CompileTime,
    "Boolean", "", &ObjectCI,
    ClassTraits::Boolean::MakeClassTraits,
    0,
    0,
    InstanceTraits::Boolean::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Boolean::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

