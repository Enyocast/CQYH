//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_int.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_int.h"
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
    const ThunkInfo int_::ti[int_::ThunkInfoNum] = {
        {&InstanceTraits::int_::AS3toExponential, &StringCI, "toExponential", NS_AS3, CT_Method, 0, 1},
        {&InstanceTraits::int_::AS3toFixed, &StringCI, "toFixed", NS_AS3, CT_Method, 0, 1},
        {&InstanceTraits::int_::AS3toPrecision, &StringCI, "toPrecision", NS_AS3, CT_Method, 0, 1},
        {&InstanceTraits::int_::AS3toString, &StringCI, "toString", NS_AS3, CT_Method, 0, 1},
        {&InstanceTraits::int_::AS3valueOf, &int_CI, "valueOf", NS_AS3, CT_Method, 0, 0},
    };

    int_::int_(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::int_::int_()"
        SetTraitsType(Traits_SInt);
//##protect##"InstanceTraits::int_::int_()"

    }

    void int_::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t); SF_ASSERT(false);
    }

    void int_::AS3toExponential(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toExponential()"
        SF_UNUSED1(ti);

        UInt32 fractionDigits = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(fractionDigits))
                // Exception
                return;

        if (fractionDigits > 20)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsInt()));
        f.SetType(DoubleFormatter::FmtScientific).SetPrecision(fractionDigits).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toExponential()"
    }
    void int_::AS3toFixed(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toFixed()"
        SF_UNUSED1(ti);

        UInt32 fractionDigits = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(fractionDigits))
                // Exception
                return;

        if (fractionDigits > 20)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsInt()));
        f.SetType(DoubleFormatter::FmtDecimal).SetPrecision(fractionDigits).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toFixed()"
    }
    void int_::AS3toPrecision(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toPrecision()"
        SF_UNUSED1(ti);

        UInt32 precision = 0;

        if (argc > 0)
            if (!argv[0].Convert2UInt32(precision))
                // Exception
                return;

        if (precision == 0 || precision > 21)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidPrecisionError, vm));

        DoubleFormatter f(static_cast<Double>(_this.AsInt()));
        f.SetType(DoubleFormatter::FmtSignificant).SetPrecision(precision).Convert();
        result = vm.GetStringManager().CreateString(f.GetResult().ToCStr(), f.GetSize());
//##protect##"InstanceTraits::AS3toPrecision()"
    }
    void int_::AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toString()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsInt())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        // If radix is the number 10 or undefined ...
        // Save undefined.
        UInt32 radix = 10;
        if (argc > 0 && !argv[0].IsUndefined())
            if (!argv[0].Convert2UInt32(radix))
                // Exception
                return;

        if (radix < 2 || radix > 16)
            return vm.ThrowRangeError(VM::Error(VM::eInvalidRadixError, vm SF_DEBUG_ARG(radix)));

        LongFormatter f(_this.AsInt());
        f.SetBase(radix).SetBigLetters(false).Convert();
        StringDataPtr r = f.GetResult();

        result = vm.GetStringManager().CreateString(r.ToCStr(), r.GetSize());
//##protect##"InstanceTraits::AS3toString()"
    }
    void int_::AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3valueOf()"
        SF_UNUSED4(ti, vm, argc, argv);

        // This method is not generic.
        if (!_this.IsInt())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result.SetSInt32(_this.AsInt());
//##protect##"InstanceTraits::AS3valueOf()"
    }
    void int_::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toStringProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassInt().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_zero);
        else
            AS3toString(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::toStringProto()"
    }
    void int_::toLocaleStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toLocaleStringProto()"
        toStringProto(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::toLocaleStringProto()"
    }
    void int_::valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::valueOfProto()"
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassInt().GetPrototype())
            // This method is called on a prototype object.
            result.SetSInt32(0);
        else
            AS3valueOf(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::valueOfProto()"
    }
    void int_::toExponentialProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toExponentialProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsInt().GetName().ToCStr())
                ));
        }

        AS3toExponential(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toExponentialProto()"
    }
    void int_::toFixedProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toFixedProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsInt().GetName().ToCStr())
                ));
        }

        AS3toFixed(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toFixedProto()"
    }
    void int_::toPrecisionProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toPrecisionProto()"
        Value coerced_this;

        if (!vm.GetClassTraitsInt().CoerceValue(_this, coerced_this))
        {
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm
                SF_DEBUG_ARG(vm.GetValueTraits(_this).GetName().ToCStr())
                SF_DEBUG_ARG(vm.GetClassTraitsInt().GetName().ToCStr())
                ));
        }

        AS3toPrecision(ti, vm, coerced_this, result, argc, argv);
//##protect##"InstanceTraits::toPrecisionProto()"
    }
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    const ThunkInfo int_::ti[int_::ThunkInfoNum] = {
        {&InstanceTraits::int_::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 1},
        {&InstanceTraits::int_::toLocaleStringProto, &StringCI, "toLocaleString", NULL, CT_Method, 0, 1},
        {&InstanceTraits::int_::valueOfProto, &int_CI, "valueOf", NULL, CT_Method, 0, 0},
        {&InstanceTraits::int_::toExponentialProto, &StringCI, "toExponential", NULL, CT_Method, 0, 1},
        {&InstanceTraits::int_::toFixedProto, &StringCI, "toFixed", NULL, CT_Method, 0, 1},
        {&InstanceTraits::int_::toPrecisionProto, &StringCI, "toPrecision", NULL, CT_Method, 0, 1},
    };

    int_::int_(ClassTraits::Traits& t)
    : Class(t)
    , MIN_VALUE(SF_MIN_SINT32)
    , MAX_VALUE(SF_MAX_SINT32)
    {
//##protect##"class_::int_::int_()"
//##protect##"class_::int_::int_()"
    }

    void int_::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void int_::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    void int_::Construct(Value& result, unsigned argc, const Value* argv, bool /*extCall*/)
    {
        if (argc > 0)
        {
            SInt32 v;
            if (argv[0].Convert2Int32(v))
                result.SetSInt32(v);
        }
        else
            result.SetSInt32(0);
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo int_::mi[int_::MemberInfoNum] = {
        {"MIN_VALUE", OFFSETOF(Classes::int_, MIN_VALUE), SlotInfo::BT_Int, 1},
        {"MAX_VALUE", OFFSETOF(Classes::int_, MAX_VALUE), SlotInfo::BT_Int, 1},
    };

    int_::int_(VM& vm)
    : Traits(vm, int_CI)
    {
//##protect##"ClassTraits::int_::int_()"
        SetTraitsType(Traits_SInt);
//##protect##"ClassTraits::int_::int_()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::int_(vm, int_CI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::int_(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> int_::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) int_(vm));
    }
//##protect##"ClassTraits$methods"
    bool int_::Coerce(const Value& value, Value& result) const
    {
        return CoerceValue(value, result);
    }
    bool int_::CoerceValue(const Value& value, Value& result) const
    {
        SInt32 r;

        if (value.Convert2Int32(r))
        {
            result.SetSInt32(r);
            return true;
        }

        return false;
    }
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo int_CI = {
    ClassInfo::CompileTime,
    "int", "", &ObjectCI,
    ClassTraits::int_::MakeClassTraits,
    0,
    ClassTraits::int_::MemberInfoNum,
    InstanceTraits::int_::ThunkInfoNum,
    0,
    NULL,
    ClassTraits::int_::mi,
    InstanceTraits::int_::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

