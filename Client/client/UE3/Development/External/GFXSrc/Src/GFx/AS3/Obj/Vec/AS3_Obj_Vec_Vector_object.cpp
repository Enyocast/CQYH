//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Vec_Vector_object.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Vec_Vector_object.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Vec_Vector.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3join, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString(",");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3every, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3forEach, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3map, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3some, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3filter, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::Vector_object, Instances::Vector_object::mid_AS3lastIndexOf, 1, SInt32>(AS3::StringManager&)
    {
        return 0x7fffffff;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_lengthGet, UInt32> TFunc_Instances_Vector_object_lengthGet;
typedef ThunkFunc1<Instances::Vector_object, Instances::Vector_object::mid_lengthSet, Value, UInt32> TFunc_Instances_Vector_object_lengthSet;
typedef ThunkFunc1<Instances::Vector_object, Instances::Vector_object::mid_fixedSet, Value, bool> TFunc_Instances_Vector_object_fixedSet;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_fixedGet, bool> TFunc_Instances_Vector_object_fixedGet;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_AS3toString, ASString> TFunc_Instances_Vector_object_AS3toString;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_AS3toLocaleString, ASString> TFunc_Instances_Vector_object_AS3toLocaleString;
typedef ThunkFunc1<Instances::Vector_object, Instances::Vector_object::mid_AS3join, ASString, const ASString&> TFunc_Instances_Vector_object_AS3join;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3every, bool, const Value&, const Value&> TFunc_Instances_Vector_object_AS3every;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3forEach, Value, const Value&, const Value&> TFunc_Instances_Vector_object_AS3forEach;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3map, Value, const Value&, const Value&> TFunc_Instances_Vector_object_AS3map;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3push, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3push;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3some, bool, const Value&, const Value&> TFunc_Instances_Vector_object_AS3some;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3unshift, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3unshift;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3concat, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3concat;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3filter, Value, const Value&, const Value&> TFunc_Instances_Vector_object_AS3filter;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_AS3pop, Value> TFunc_Instances_Vector_object_AS3pop;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_AS3reverse, Value> TFunc_Instances_Vector_object_AS3reverse;
typedef ThunkFunc0<Instances::Vector_object, Instances::Vector_object::mid_AS3shift, Value> TFunc_Instances_Vector_object_AS3shift;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3slice, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3slice;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3sort, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3sort;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3splice, Value, unsigned, const Value*> TFunc_Instances_Vector_object_AS3splice;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3indexOf, SInt32, const Value&, SInt32> TFunc_Instances_Vector_object_AS3indexOf;
typedef ThunkFunc2<Instances::Vector_object, Instances::Vector_object::mid_AS3lastIndexOf, SInt32, const Value&, SInt32> TFunc_Instances_Vector_object_AS3lastIndexOf;

template <> const TFunc_Instances_Vector_object_lengthGet::TMethod TFunc_Instances_Vector_object_lengthGet::Method = &Instances::Vector_object::lengthGet;
template <> const TFunc_Instances_Vector_object_lengthSet::TMethod TFunc_Instances_Vector_object_lengthSet::Method = &Instances::Vector_object::lengthSet;
template <> const TFunc_Instances_Vector_object_fixedSet::TMethod TFunc_Instances_Vector_object_fixedSet::Method = &Instances::Vector_object::fixedSet;
template <> const TFunc_Instances_Vector_object_fixedGet::TMethod TFunc_Instances_Vector_object_fixedGet::Method = &Instances::Vector_object::fixedGet;
template <> const TFunc_Instances_Vector_object_AS3toString::TMethod TFunc_Instances_Vector_object_AS3toString::Method = &Instances::Vector_object::AS3toString;
template <> const TFunc_Instances_Vector_object_AS3toLocaleString::TMethod TFunc_Instances_Vector_object_AS3toLocaleString::Method = &Instances::Vector_object::AS3toLocaleString;
template <> const TFunc_Instances_Vector_object_AS3join::TMethod TFunc_Instances_Vector_object_AS3join::Method = &Instances::Vector_object::AS3join;
template <> const TFunc_Instances_Vector_object_AS3every::TMethod TFunc_Instances_Vector_object_AS3every::Method = &Instances::Vector_object::AS3every;
template <> const TFunc_Instances_Vector_object_AS3forEach::TMethod TFunc_Instances_Vector_object_AS3forEach::Method = &Instances::Vector_object::AS3forEach;
template <> const TFunc_Instances_Vector_object_AS3map::TMethod TFunc_Instances_Vector_object_AS3map::Method = &Instances::Vector_object::AS3map;
template <> const TFunc_Instances_Vector_object_AS3push::TMethod TFunc_Instances_Vector_object_AS3push::Method = &Instances::Vector_object::AS3push;
template <> const TFunc_Instances_Vector_object_AS3some::TMethod TFunc_Instances_Vector_object_AS3some::Method = &Instances::Vector_object::AS3some;
template <> const TFunc_Instances_Vector_object_AS3unshift::TMethod TFunc_Instances_Vector_object_AS3unshift::Method = &Instances::Vector_object::AS3unshift;
template <> const TFunc_Instances_Vector_object_AS3concat::TMethod TFunc_Instances_Vector_object_AS3concat::Method = &Instances::Vector_object::AS3concat;
template <> const TFunc_Instances_Vector_object_AS3filter::TMethod TFunc_Instances_Vector_object_AS3filter::Method = &Instances::Vector_object::AS3filter;
template <> const TFunc_Instances_Vector_object_AS3pop::TMethod TFunc_Instances_Vector_object_AS3pop::Method = &Instances::Vector_object::AS3pop;
template <> const TFunc_Instances_Vector_object_AS3reverse::TMethod TFunc_Instances_Vector_object_AS3reverse::Method = &Instances::Vector_object::AS3reverse;
template <> const TFunc_Instances_Vector_object_AS3shift::TMethod TFunc_Instances_Vector_object_AS3shift::Method = &Instances::Vector_object::AS3shift;
template <> const TFunc_Instances_Vector_object_AS3slice::TMethod TFunc_Instances_Vector_object_AS3slice::Method = &Instances::Vector_object::AS3slice;
template <> const TFunc_Instances_Vector_object_AS3sort::TMethod TFunc_Instances_Vector_object_AS3sort::Method = &Instances::Vector_object::AS3sort;
template <> const TFunc_Instances_Vector_object_AS3splice::TMethod TFunc_Instances_Vector_object_AS3splice::Method = &Instances::Vector_object::AS3splice;
template <> const TFunc_Instances_Vector_object_AS3indexOf::TMethod TFunc_Instances_Vector_object_AS3indexOf::Method = &Instances::Vector_object::AS3indexOf;
template <> const TFunc_Instances_Vector_object_AS3lastIndexOf::TMethod TFunc_Instances_Vector_object_AS3lastIndexOf::Method = &Instances::Vector_object::AS3lastIndexOf;

namespace Instances
{
    Vector_object::Vector_object(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Vector_object::Vector_object()$data"
    , V(t.GetVM().GetMemoryHeap(), t.GetVM())
//##protect##"instance::Vector_object::Vector_object()$data"
    {
//##protect##"instance::Vector_object::Vector_object()$code"
//##protect##"instance::Vector_object::Vector_object()$code"
    }

    void Vector_object::lengthGet(UInt32& result)
    {
//##protect##"instance::Vector_object::lengthGet()"
        result = static_cast<UInt32>(V.GetSize());
//##protect##"instance::Vector_object::lengthGet()"
    }
    void Vector_object::lengthSet(Value& result, UInt32 value)
    {
//##protect##"instance::Vector_object::lengthSet()"
        SF_UNUSED1(result);
        V.Resize(value).DoNotCheck();
//##protect##"instance::Vector_object::lengthSet()"
    }
    void Vector_object::fixedSet(Value& result, bool f)
    {
//##protect##"instance::Vector_object::fixedSet()"
        SF_UNUSED1(result);
        V.SetFixed(f);
//##protect##"instance::Vector_object::fixedSet()"
    }
    void Vector_object::fixedGet(bool& result)
    {
//##protect##"instance::Vector_object::fixedGet()"
        result = V.GetFixed();
//##protect##"instance::Vector_object::fixedGet()"
    }
    void Vector_object::AS3toString(ASString& result)
    {
//##protect##"instance::Vector_object::AS3toString()"
        result = V.ToString(GetVM().GetStringManager().GetBuiltin(AS3Builtin_comma));
//##protect##"instance::Vector_object::AS3toString()"
    }
    void Vector_object::AS3toLocaleString(ASString& result)
    {
//##protect##"instance::Vector_object::AS3toLocaleString()"
        AS3toString(result);
//##protect##"instance::Vector_object::AS3toLocaleString()"
    }
    void Vector_object::AS3join(ASString& result, const ASString& separator)
    {
//##protect##"instance::Vector_object::AS3join()"
        result = V.ToString(separator);
//##protect##"instance::Vector_object::AS3join()"
    }
    void Vector_object::AS3every(bool& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_object::AS3every()"
        result = V.Every(checker, thisObj, *this);
//##protect##"instance::Vector_object::AS3every()"
    }
    void Vector_object::AS3forEach(Value& result, const Value& eacher, const Value& thisObj)
    {
//##protect##"instance::Vector_object::AS3forEach()"
        SF_UNUSED1(result);
        V.ForEach(eacher, thisObj, *this);
//##protect##"instance::Vector_object::AS3forEach()"
    }
    void Vector_object::AS3map(Value& result, const Value& mapper, const Value& thisObj)
    {
//##protect##"instance::Vector_object::AS3map()"
        V.Map(result, mapper, thisObj, this);
//##protect##"instance::Vector_object::AS3map()"
    }
    void Vector_object::AS3push(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3push()"
        V.PushBack(argc, argv, GetEnclosedClassTraits());
        result.SetUInt32(static_cast<UInt32>(V.GetSize()));
//##protect##"instance::Vector_object::AS3push()"
    }
    void Vector_object::AS3some(bool& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_object::AS3some()"
        result = V.Some(checker, thisObj, *this);
//##protect##"instance::Vector_object::AS3some()"
    }
    void Vector_object::AS3unshift(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3unshift()"
        V.Unshift(argc, argv, GetEnclosedClassTraits());
        result.SetUInt32(static_cast<UInt32>(V.GetSize()));
//##protect##"instance::Vector_object::AS3unshift()"
    }
    void Vector_object::AS3concat(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3concat()"
        V.Concat(result, argc, argv, *this);
//##protect##"instance::Vector_object::AS3concat()"
    }
    void Vector_object::AS3filter(Value& result, const Value& checker, const Value& thisObj)
    {
//##protect##"instance::Vector_object::AS3filter()"
        V.Filter(result, checker, thisObj, *this);
//##protect##"instance::Vector_object::AS3filter()"
    }
    void Vector_object::AS3pop(Value& result)
    {
//##protect##"instance::Vector_object::AS3pop()"
        V.Pop(result);
//##protect##"instance::Vector_object::AS3pop()"
    }
    void Vector_object::AS3reverse(Value& result)
    {
//##protect##"instance::Vector_object::AS3reverse()"
        V.Reverse();
        result = this;
//##protect##"instance::Vector_object::AS3reverse()"
    }
    void Vector_object::AS3shift(Value& result)
    {
//##protect##"instance::Vector_object::AS3shift()"
        V.Shift(result);
//##protect##"instance::Vector_object::AS3shift()"
    }
    void Vector_object::AS3slice(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3slice()"
        V.Slice(result, argc, argv, *this);
//##protect##"instance::Vector_object::AS3slice()"
    }
    void Vector_object::AS3sort(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3sort()"
        if (argc < 1 || argv[0].IsNullOrUndefined() || !argv[0].IsCallable())
        {
            VM& vm = GetVM();
            return vm.ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, vm 
                SF_DEBUG_ARG((argc > 0) ? vm.GetValueTraits(argv[0]).GetName().ToCStr() : "undefined")
                SF_DEBUG_ARG(this->GetEnclosedClassTraits().GetName().ToCStr())
                ));
        }

        V.Sort(result, argc, argv, *this);
//##protect##"instance::Vector_object::AS3sort()"
    }
    void Vector_object::AS3splice(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::Vector_object::AS3splice()"
        V.Splice(result, argc, argv, *this);
//##protect##"instance::Vector_object::AS3splice()"
    }
    void Vector_object::AS3indexOf(SInt32& result, const Value& value, SInt32 from)
    {
//##protect##"instance::Vector_object::AS3indexOf()"
        V.IndexOf(result, value, from);
//##protect##"instance::Vector_object::AS3indexOf()"
    }
    void Vector_object::AS3lastIndexOf(SInt32& result, const Value& value, SInt32 from)
    {
//##protect##"instance::Vector_object::AS3lastIndexOf()"
        V.LastIndexOf(result, value, from);
//##protect##"instance::Vector_object::AS3lastIndexOf()"
    }

//##protect##"instance$methods"
    void Vector_object::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0)
        {
            UInt32 length;
            if (!argv[0].Convert2UInt32(length))
                return;

            if (!V.Resize(length))
                return;
        }

        if (argc > 1)
        {
            V.SetFixed(argv[1].Convert2Boolean());
        }
    }

    void Vector_object::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);

        V.ForEachChild_GC(prcc, op SF_DEBUG_ARG(*this));
    }

    void Vector_object::GetNextPropertyName(Value& name, GlobalSlotIndex ind) const
    {
        if (!ind.IsValid())
            return name.SetUndefined();

        name.SetUInt32(static_cast<UInt32>(AbsoluteIndex(ind).Get()));
    }

    GlobalSlotIndex Vector_object::GetNextDynPropIndex(GlobalSlotIndex ind) const
    {
        GlobalSlotIndex gind(0);
        const AbsoluteIndex aind = GetNextArrayIndex(AbsoluteIndex(ind));

        if (aind.IsValid())
            gind = GlobalSlotIndex(aind);

        return gind;
    }

    CheckResult Vector_object::SetProperty(const Multiname& prop_name, const Value& value)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
            return Set(ind, value, GetEnclosedClassTraits());

        // Not an Array index. Let us treat it as a regular object.
        return Instances::Object::SetProperty(prop_name, value);

        // !!! This was needed for something.
//         GetVM().ThrowReferenceError(VM::eWriteSealedError);
//         return false;
    }

    CheckResult Vector_object::GetProperty(const Multiname& prop_name, Value& value)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
        {
            if (ind < V.GetSize())
            {
                Get(ind, value);
                return true;
            }

            return false;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::Object::GetProperty(prop_name, value);
    }

    void Vector_object::GetDynamicProperty(AbsoluteIndex ind, Value& value)
    {
        V.GetValue(ind.Get(), value);
    }

    CheckResult Vector_object::DeleteProperty(const Multiname& prop_name)
    {
        UInt32 ind;
        if (GetVectorInd(prop_name, ind))
            return RemoveAt(ind);

        // Not an Array index. Let us treat it as a regular object.
        return Instances::Object::DeleteProperty(prop_name);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Vector_object::ti[Vector_object::ThunkInfoNum] = {
        {TFunc_Instances_Vector_object_lengthGet::Func, &uintCI, "length", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Vector_object_lengthSet::Func, NULL, "length", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Vector_object_fixedSet::Func, NULL, "fixed", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Vector_object_fixedGet::Func, &BooleanCI, "fixed", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Vector_object_AS3toString::Func, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_Vector_object_AS3toLocaleString::Func, &StringCI, "toLocaleString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_Vector_object_AS3join::Func, &StringCI, "join", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_Vector_object_AS3every::Func, &BooleanCI, "every", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3forEach::Func, NULL, "forEach", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3map::Func, NULL, "map", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3push::Func, &uintCI, "push", NS_AS3, CT_Method, 0, 1023},
        {TFunc_Instances_Vector_object_AS3some::Func, &BooleanCI, "some", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3unshift::Func, &uintCI, "unshift", NS_AS3, CT_Method, 0, 1023},
        {TFunc_Instances_Vector_object_AS3concat::Func, NULL, "concat", NS_AS3, CT_Method, 0, 1023},
        {TFunc_Instances_Vector_object_AS3filter::Func, NULL, "filter", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3pop::Func, NULL, "pop", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_Vector_object_AS3reverse::Func, NULL, "reverse", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_Vector_object_AS3shift::Func, NULL, "shift", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_Vector_object_AS3slice::Func, NULL, "slice", NS_AS3, CT_Method, 0, 2},
        {TFunc_Instances_Vector_object_AS3sort::Func, NULL, "sort", NS_AS3, CT_Method, 0, 1023},
        {TFunc_Instances_Vector_object_AS3splice::Func, NULL, "splice", NS_AS3, CT_Method, 0, 1023},
        {TFunc_Instances_Vector_object_AS3indexOf::Func, &int_CI, "indexOf", NS_AS3, CT_Method, 1, 2},
        {TFunc_Instances_Vector_object_AS3lastIndexOf::Func, &int_CI, "lastIndexOf", NS_AS3, CT_Method, 1, 2},
    };

    Vector_object::Vector_object(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Vector_object::Vector_object()"
        SetArrayLike();
        SetTraitsType(Traits_Vector_object);
//##protect##"InstanceTraits::Vector_object::Vector_object()"
        SetMemSize(sizeof(Instances::Vector_object));

    }

    Pickable<Instances::Vector_object> Vector_object::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Vector_object>(new(t.Alloc()) Instances::Vector_object(t));
    }

    void Vector_object::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    Vector_object::Vector_object(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Vector_object::Vector_object()"
//##protect##"class_::Vector_object::Vector_object()"
    }
//##protect##"class_$methods"
    void Vector_object::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        if (argc == 1)
        {
            const Value& value = argv[0];

            if (value.IsNullOrUndefined())
            {
                result = value;
                return;
            }

            InstanceTraits::Vector_object& itr = static_cast<InstanceTraits::Vector_object&>(GetClassTraits().GetInstanceTraits());
            const Traits& value_tr = GetVM().GetValueTraits(value);

            // Class Vector.<X> is final. 
            if (&value_tr == &itr)
            {
                result = value;
                return;
            }

            SPtr<Instances::Vector_object> vstr(itr.MakeInstance(itr));

            if (vstr->AppendCoerce(value))
                result = vstr;
            else
                GetVM().ThrowTypeError(VM::Error(VM::eCheckTypeFailedError, GetVM()
                    SF_DEBUG_ARG(value)
                    SF_DEBUG_ARG(itr.GetName().ToCStr())
                    ));
        }
        else
            return GetVM().ThrowRangeError(VM::Error(VM::eCoerceArgumentCountError, GetVM() SF_DEBUG_ARG(argc)));
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    Vector_object::Vector_object(VM& vm)
    : Traits(vm, Vector_objectCI)
    {
//##protect##"ClassTraits::Vector_object::Vector_object()"
        // SetArrayLike();
        SetTraitsType(Traits_Vector_object);
//##protect##"ClassTraits::Vector_object::Vector_object()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Vector_object(vm, Vector_objectCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Vector_object(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Vector_object::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Vector_object(vm));
    }
//##protect##"ClassTraits$methods"
    Vector_object::Vector_object(VM& vm, const ClassInfo& ci, const ClassTraits::Traits& ect)
        : Traits(vm, ci)
        , EnclosedClassTraits(&ect)
    {
        // SetArrayLike();
        SetTraitsType(Traits_Vector_object);

        Pickable<InstanceTraits::Vector_object> it(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::Vector_object(GetVM(), ci));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_Class_Mem) Classes::Vector_object(*this));
        it->SetConstructor(cl);
    }

    void Vector_object::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        Traits::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC_Const<const ClassTraits::Traits, Mem_Stat>(prcc, EnclosedClassTraits, op SF_DEBUG_ARG(*this));
    }
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo Vector_objectCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "Vector$object", "__AS3__.vec", &ObjectCI,
    ClassTraits::Vector_object::MakeClassTraits,
    0,
    0,
    InstanceTraits::Vector_object::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Vector_object::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

