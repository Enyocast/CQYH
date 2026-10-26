/**************************************************************************

Filename    :   AS3_Tracer.cpp
Content     :   
Created     :   Sep, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_Tracer.h"
#include "AS3_AsString.h"
#include "AS3_VTable.h"
#include "Obj/AS3_Obj_Array.h"
#include "Obj/AS3_Obj_UserDefined.h"
#include "Obj/AS3_Obj_Global.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_object.h"
#include "Obj/AS3_Obj_int.h"
#include "Obj/AS3_Obj_uint.h"
#include "Obj/AS3_Obj_Number.h"
#include "Obj/AS3_Obj_Boolean.h"
#include "Obj/AS3_Obj_String.h"

#include "Obj/Vec/AS3_Obj_Vec_Vector.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_int.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_uint.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_double.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_String.h"
#include "Obj/Vec/AS3_Obj_Vec_Vector_object.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

///////////////////////////////////////////////////////////////////////////////
static
const ClassTraits::Traits* FindScopeTraits(VM& vm, const UPInt baseSSInd, const ScopeStackType& scope_stack, const Multiname& mn)
{
    const ClassTraits::Traits* result = NULL;

    for (UPInt i = scope_stack.GetSize(); i > baseSSInd ; --i)
    {
        const Value& v = scope_stack[i - 1];
        const Traits& tr = vm.GetValueTraits(v);

        result = FindFixedTraits(vm, tr, mn);
        
        if (result)
            // For RVO sake ...
            break;
    }

    return result;
}

static
const ClassTraits::Traits* FindClassTraits(VM& vm, const Multiname& mn)
{
    const ClassTraits::Traits* ctr = NULL;

    if (mn.IsQName())
        ctr = vm.Resolve2ClassTraits(mn);
    else
    {
        NamespaceSet& nss = mn.GetNamespaceSet();
        const NamespaceSet::TContainer& n = nss.GetNamespaces();
        const UPInt size = n.GetSize();

        for (UPInt i = 0; i < size; ++i)
        {
            ctr = vm.Resolve2ClassTraits(mn.GetName(), *n[i]);
            if (ctr)
                break;
        }
    }

    return ctr;
}


namespace TR 
{

    ///////////////////////////////////////////////////////////////////////////
    void StackReader::CheckObject(const Value& v) const
    {
        SF_UNUSED1(v);

        /* Disable checks temporarily till we implement all operations with stack.
        if (v.IsNull())
        {
            // A TypeError is thrown if obj is null or undefined.
            GetVM().ThrowVerifyError(VM::eConvertNullToObjectError);
        }
        else if (v.IsUndefined())
        {
            GetVM().ThrowVerifyError(VM::eConvertUndefinedToObjectError);
        }
        */
    }

    int StackReader::Read(Multiname& obj) const
    {
        switch (obj.GetKind())
        {
        case Abc::MN_QName:
        case Abc::MN_QNameA:
            // QName is not read from stack; both name and namespase known at compile-time.
            break;
        case Abc::MN_RTQName:
        case Abc::MN_RTQNameA:
            // Name is known at compile time, Namespace is resolved at runtime.

            /*
            // For maniacs.
            CheckObject(GetState().BackOpValue());
            if (GetVM().IsException())
                break;
            */

            // !!! We should get a Namespace here.
            // It is up to verifier to check that.
            // In our case we will just get "any namespace".
            GetState().PopOpValue();
            return 1;
        case Abc::MN_RTQNameL:
        case Abc::MN_RTQNameLA:
            // Both name and namespace are resolved at runtime.
            // We will get "any name" here.
            GetState().PopOpValue();

            /*
            // For maniacs.
            CheckObject(GetState().BackOpValue());
            if (GetVM().IsException())
                break;
            */

            // !!! We should get a Namespace here.
            // It is up to verifier to check that.
            // In our case we will just get "any namespace".
            //GetState().PopOpValue();
            obj.SetRTName(GetState().PopOpValue());
            return 2;
        case Abc::MN_Multiname:
        case Abc::MN_MultinameA:
            // MInfo is not supposed to be read from stack.
            break;
        case Abc::MN_MultinameL:
        case Abc::MN_MultinameLA:
            // Namespace set is known at compile time, Name is resolved at runtime.        
            // name_ind is a string, and we will get an int or an uint as an index instead;
            // We will get "any name" here.
            //GetState().PopOpValue();
            obj.SetRTName(GetState().PopOpValue());
            return 1;
        case Abc::MN_Typename:
            // Recursive!!!?
            GetVM().GetUI().Output(FlashUI::Output_Warning, "Reading chained multiname in itself.");
            return Read(obj);
        default:
            SF_ASSERT(false);
            break;
        }

        return 0;
    }

    ///////////////////////////////////////////////////////////////////////////
    ReadArgs::ReadArgs(VM& vm, State& s, UInt32 arg_count )
        : StackReader(vm, s)
        , ArgNum(arg_count)
        , CallArgs(GetVM().GetMemoryHeap())
    {
        if (arg_count)
        {
            const UPInt size = GetOpStack().GetSize();

            if (arg_count <= eFixedArrSize)
            {
                unsigned j = 0;
                for (UPInt i = size - arg_count; i < size; ++i, ++j)
                {
                    FixedArr[j] = GetState().GetOpValue(i);
                }
            }
            else
            {
                for (UPInt i = size - arg_count; i < size; ++i)
                {
                    CallArgs.PushBack(GetState().GetOpValue(i));
                }
            }

            GetOpStack().Resize(size - arg_count);
        }

        HaveRead(arg_count);
    }

    ///////////////////////////////////////////////////////////////////////////////
    void State::exec_construct(UInt32 arg_count)
    {
        PushCode(arg_count);

        TR::ReadArgsObject args(GetVM(), *this, arg_count);

        // Retrieve InstanceTraits if possible.
        switch (args.ArgObject.GetKind())
        {
        case Value::kInstanceTraits:
            PushOp(Value(args.ArgObject.GetInstanceTraits()));
            return;
        case Value::kClassTraits:
            PushOp(Value(args.ArgObject.GetClassTraits().GetInstanceTraits()));
            return;
        case Value::kClass:
            PushOp(Value(args.ArgObject.AsClass().GetClassTraits().GetInstanceTraits()));
            return;
        default:
            break;
        }

        // Theoretically, we shouldn't be able to reach this point.
        SF_ASSERT(false);
        PushOp(args.ArgObject);
    }

    void State::exec_constructsuper(UInt32 arg_count)
    {
        PushCode(arg_count);

        TR::ReadArgsObject args(GetVM(), *this, arg_count);
    }

    void State::exec_constructprop(UInt32 mn_index, UInt32 arg_count)
    {
        PushCode(mn_index);
        PushCode(arg_count);

        TR::ReadArgsMnObject args(GetFile(), *this, arg_count, mn_index);

        if (args.ArgObject.GetKind() == Value::kInstanceTraits)
        {
            PushOp(Value(args.ArgObject.GetInstanceTraits()));
            return;
        }

        if (!args.ArgMN.IsRunTime())
        {
            // Ignore run-time multinames for the time being.
            VM& vm = GetVM();

            // Find a property.
            const ClassTraits::Traits* tr = FindScopeTraits(vm, 0, GetScopeStack(), args.ArgMN);

            // Look in Saved Scope.
            /* No Saved Scope at this time.
            if (!tr)
            {
                const ScopeStackType* ss = CallStack.Back().GetSavedScope();

                if (ss)
                    tr = FindScopeTraits(vm, *ss, args.ArgMN);
            }
            */

            // Look in Global Objects.
            // !!! WARNING:
            // !!! We are not supposed to search in Global Objects with this opcode.
            if (!tr)
                tr = FindGOTraits(vm, vm.GetGlobalObjects(), args.ArgMN);

            if (tr)
            {
                // Push found object ...
                PushOp(Value(tr->GetInstanceTraits()));
                return;
            }
        }

        PushOp(Value(GetObjectType()));
    }

    InstanceTraits::Traits& State::GetFunctType(const Value& value) const
    {
        switch (value.GetKind())
        {
        case Value::kThunk:
            return GetVM().GetClassTraitsFunction().GetThunkTraits();
        case Value::kThunkClosure:
            return GetVM().GetClassTraitsFunction().GetThunkFunctionTraits();
        case Value::kVTableInd: // So far kVTableInd is used with MethodInd only.
        case Value::kVTableIndClosure:
            return GetVM().GetClassTraitsFunction().GetVTableTraits();
        default:
            break;
        }

        return GetVM().GetClassTraitsFunction().GetInstanceTraits();
    }

    InstanceTraits::Traits& State::GetFunctReturnType(const ThunkInfo& thunk) const
    {
        const ClassInfo* rt = thunk.ResultType;

        if (rt)
        {
            VM& vm = GetVM();
            StringManager& sm = vm.GetStringManager();
            const ASString name = sm.CreateConstString(rt->Name);
            const Instances::Namespace& ns = vm.GetInternedNamespace(Abc::NS_Public, rt->PkgName);

            const ClassTraits::Traits* ctr = vm.Resolve2ClassTraits(name, ns);

            if (ctr)
                return ctr->GetInstanceTraits();
        }

        return GetObjectType();
    }

    InstanceTraits::Traits& State::GetFunctReturnType(const Value& value) const
    {
        const Value::KindType kind = value.GetKind();

        switch (kind)
        {
        case Value::kFunction:
            {
                const Instances::Function& f = value.AsFunction();
                const ClassTraits::Traits* ctr = GetVM().Resolve2ClassTraits(f.GetFile(), f.GetReturnType());

                if (ctr)
                    return ctr->GetInstanceTraits();
            }
            break;
        case Value::kVTableInd:
        case Value::kVTableIndClosure:
            {
                const VTable& vt = value.GetTraits().GetVT();
                const SInt32 ind = value.GetVTableInd();
                const Value& real_func = vt.GetRaw(AbsoluteIndex(ind));

                // VTable stores MethodInd or Thunk.
                if (real_func.GetKind() == Value::kMethodInd)
                {
                    // MethodInd.

                    const SInt32 method_ind = real_func.GetMethodInd();
                    const Traits& real_tr = real_func.GetTraits();
                    SF_ASSERT(real_tr.GetFilePtr());
                    VMAbcFile& file = *real_tr.GetFilePtr();
                    //const Abc::MethodBodyInfo& mbi = file.GetMethodBodyInfo(method_ind);
                    const Abc::MethodInfo& mi = file.GetMethodInfo(method_ind);
                    const Abc::Multiname& rt = mi.GetReturnType(file.GetConstPool());
                    const ClassTraits::Traits* ctr = GetVM().Resolve2ClassTraits(file, rt);

                    if (ctr)
                        return ctr->GetInstanceTraits();
                }
                else
                {
                    // Thunk.
                    switch (kind)
                    {
                    case Value::kVTableInd:
                        return GetFunctReturnType(real_func.AsThunk());
                        break;
                    case Value::kVTableIndClosure:
                        return GetFunctReturnType(real_func.GetThunkFunct());
                        break;
                    default:
                        break;
                    }
                }
            }
            break;
        case Value::kMethodInd:
            {
                // MethodInd.

                const SInt32 method_ind = value.GetMethodInd();
                const Traits& real_tr = value.GetTraits();
                SF_ASSERT(real_tr.GetFilePtr());
                VMAbcFile& file = *real_tr.GetFilePtr();
                //const Abc::MethodBodyInfo& mbi = file.GetMethodBodyInfo(method_ind);
                const Abc::MethodInfo& mi = file.GetMethodInfo(method_ind);
                const Abc::Multiname& rt = mi.GetReturnType(file.GetConstPool());
                const ClassTraits::Traits* ctr = GetVM().Resolve2ClassTraits(file, rt);

                if (ctr)
                    return ctr->GetInstanceTraits();
            }
            break;
        case Value::kThunk:
            return GetFunctReturnType(value.AsThunk());
        case Value::kThunkFunction:
            return GetFunctReturnType(value.AsThunkFunction().GetThunk());
        case Value::kThunkClosure:
            return GetFunctReturnType(value.GetThunkFunct());
        default:
            break;
        }

        return GetObjectType();
    }

    CheckResult State::GetPropertyType(const Traits& obj_traits, const SlotInfo& si, Value& type) const
    {
        if (si.IsCode() && si.GetAValueInd().IsValid())
        {
            if (si.GetBindingType() == SlotInfo::BT_Code)
                // Retrieve function type.
                type = GetFunctType(obj_traits.GetVT().GetValue(si.GetAValueInd()));
            else
                // Retrieve function return type.
                type = GetFunctReturnType(obj_traits.GetVT().GetRaw(si.GetAValueInd()));

            return true;
        }

        VM& vm = GetVM();
        const ClassTraits::Traits* ctr = const_cast<SlotInfo&>(si).GetDataType(vm);

        if (ctr == NULL)
        {
            vm.ThrowVerifyError(VM::Error(VM::eClassNotFoundError, vm
                SF_DEBUG_ARG(si.GetDataTypeName(vm))
                ));
            return false;
        }

        if (si.IsClass())
            type = const_cast<ClassTraits::Traits&>(*ctr);
        else
            type = ctr->GetInstanceTraits();

        return true;
    }

    void State::exec_call(UInt32 arg_count)
    {
        PushCode(arg_count);

        TR::ReadArgsObjectValue args(GetVM(), *this, arg_count);

        PushOp(Value(GetFunctReturnType(args.value)));
    }

    void State::exec_callmethod(UInt32 method_index, UInt32 arg_count)
    {
        PushCode(method_index);
        PushCode(arg_count);

        TR::ReadArgsObject args(GetVM(), *this, arg_count);

        // We can do better than this.
        //PushOp(Value());
        PushOp(Value(GetObjectType()));
    }

    void State::exec_callstatic(UInt32 method_index, UInt32 arg_count)
    {
        PushCode(method_index);
        PushCode(arg_count);

        TR::ReadArgsObject args(GetVM(), *this, arg_count);

        // We can do better than this.
        //PushOp(Value());
        PushOp(Value(GetObjectType()));
    }

    void State::exec_applytype(UInt32 arg_count)
    {
#if 0
        // For maniacs.
        if (arg_count == 0)
        {
            return GetVM().ThrowVerifyError(VM::Error(VM::eClassNotFoundError, GetVM()
                DEBUG_ARG(args.ArgMN.GetName(GetFile().GetConstPool()).ToCStr())
                ));
        }
#endif

        PushCode(arg_count);

        VM& vm = GetVM();
        TR::ReadArgsObject args(vm, *this, arg_count);

        const Value& arg0 = args.GetCallArgs()[0];

        const ClassTraits::Traits* ctr = NULL;

        switch (arg0.GetKind())
        {
        case Value::kUndefined:
            ctr = &vm.GetClassTraitsObject();
            break;
        case Value::kClass:
            ctr = &arg0.AsClass().GetClassTraits();
            break;
        case Value::kObject:
            if (arg0.IsNull())
                ctr = &vm.GetClassTraitsObject();
            break;
        case Value::kClassTraits:
            ctr = &arg0.GetClassTraits();
            break;
        default:
            break;
        }

        const ClassTraits::Traits* v_ctr = &vm.GetClassTraitsObject();

        if (ctr)
        {
            if (ctr == &vm.GetClassTraitsInt())
                v_ctr = &vm.GetClassTraitsVectorSInt();
            else if (ctr == &vm.GetClassTraitsUInt())
                v_ctr = &vm.GetClassTraitsVectorUInt();
            else if (ctr == &vm.GetClassTraitsNumber())
                v_ctr = &vm.GetClassTraitsVectorNumber();
            else if (ctr == &vm.GetClassTraitsString())
                v_ctr = &vm.GetClassTraitsVectorString();
            else
                v_ctr = &vm.GetClassVector().Resolve2Vector(*ctr);
        }

        // Result is a type.
        PushOp(Value(const_cast<ClassTraits::Traits&>(*v_ctr)));
    }

    void State::exec_newobject(UInt32 arg_count)
    {
        PushCode(arg_count);

        for (UInt32 i = 0; i < arg_count; ++i)
        {
            PopOp(); // value
            PopOp(); // name
        }

        // This is always an object. There is nothing else to do.
        PushOp(Value(GetObjectType()));
    }

    void State::exec_newarray(UInt32 arr_size)
    {
        PushCode(arr_size);

        for (UInt32 i = 0; i < arr_size; ++i)
        {
            PopOp(); // value
        }

        PushOp(Value(GetArrayType()));
    }

    void State::exec_getdescendants(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMnObject args(GetFile(), *this, mn_index);

        // !!! This is a wrong result !!!
        PushOp(Value(GetObjectType(), true));
    }

    void State::exec_newcatch(UInt32 v)
    {
        PushCode(v);

        // There is no need for precise type of the catch object because
        // abc pCode will address data using slot numbers.
        PushOp(Value(GetObjectType()));
    }

    void State::FindProp(PropRef& result, const Multiname& mn, ScopeType& stype, UPInt& scope_index)
    {
        // Ignore run-time multinames for the time being.
        if (mn.IsRunTime() || mn.IsNameLate())
            return;

        VM& vm = GetVM();
        UPInt slot_index = 0;

        // 1) Check scope stack.
        {
            for (UPInt i = GetScopeStack().GetSize(); i > 0; --i)
            {
                scope_index = i - 1;
                const Value& v = GetScopeStack()[scope_index];
                const Traits* tr = GetValueTraits(v);

                if (v.GetWith())
                    return;

                // Skip global object.
                if (tr && !tr->IsGlobal())
                {
                    const SlotInfo* si = FindFixedSlot(vm, *tr, mn, slot_index, NULL);
                    if (si)
                    {
                        stype = stScopeStack;
                        result = PropRef(v, si, slot_index);
                        return;
                    }
                }
            }
        }

        // 2) Look in Saved Scope.
        // Saved Scope has classes, Activation objects, regular object, and a global object.
        // No primitive types so far.
        if (GetSavedScope())
        {
            const ValueArrayDH& ss = *GetSavedScope();
            for (UPInt i = ss.GetSize(); i > 0 ; --i)
            {
                scope_index = i - 1;
                const Value& v = ss[scope_index];
                const Traits& tr = vm.GetValueTraits(v);

                if (v.GetWith())
                    return;

                /* Search in global objects has the same pCode.
                if (tr.IsGlobal())
                    // We will deal with global objects later.
                    continue;
                */

                const SlotInfo* si = FindFixedSlot(vm, tr, mn, slot_index, NULL);

                if (si)
                {
                    // We found it

                    stype = stStoredScope;
                    result = PropRef(v, si, slot_index);
                    return;
                }
            }
        }

        // Check global objects.

        // We are looking for classes.
        // We know about all registered class objects.
//             {
//                 const ClassTraits::Traits* ctr = vm.GetRegisteredClassTraits(mn);
//                 if (ctr && ctr->IsValid() && ctr->GetInstanceTraits().HasConstructorSetup())
//                 {
//                     // Not correct. This should be a global object.
//                     // This is just a class.
//                     value = Value(&ctr->GetInstanceTraits().GetClass());
// 
//                     return stGlobalObject;
//                 }
//             }

        if (!mn.GetName().IsTraits())
        {
            // FindClassTraits() won't work here.
            //const ClassTraits::Traits* ctr = vm.FindClassTraits(mn)
            const ClassTraits::Traits* ctr = vm.GetRegisteredClassTraits(mn);

#if 1 // Experimental
            // This shouldn't cause any problem.
            if (ctr)
            {
                if (ctr->IsValid())
                {
                    // This is just a class.

                    InstanceTraits::Traits& itr = ctr->GetInstanceTraits();
                    AS3::Object* obj = NULL;

                    if (itr.IsAbcObject())
                    {
                        // Class will be created later. Just get a slot.
                        InstanceTraits::UserDefined& ud = static_cast<InstanceTraits::UserDefined&>(itr);
                        obj = &ud.GetScript();
                    }
                    else
                        obj = &vm.GetGlobalObjectCPP();

                    SF_ASSERT(obj);
                    UPInt slot_index = 0;
                    const SlotInfo* si = AS3::FindFixedSlot(vm, obj->GetTraits(), mn, slot_index, obj);

                    if (si)
                    {
                        result = PropRef(obj, si, slot_index);
                        stype = stGlobalObject;
                        return;
                    }
                    else
#ifdef SF_AS3_CLASS_AS_SLOT
                        SF_ASSERT(false);
#else
                        // There is no slot for Class any more.
                        return;
#endif
                }
                else
                    SF_ASSERT(false);
            }
#endif

            FindGOProperty(result, vm, vm.GetGlobalObjects(), mn, ctr);
            if (result)
            {
                stype = stGlobalObject;
                return;
            }
        }
    }

    void State::exec_findpropstrict(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMn args(GetFile(), *this, mn_index);

        UPInt scope_index;
        ScopeType stype;
        PropRef prop;

        FindProp(prop, args.ArgMN, stype, scope_index);

        if (prop)
        {
            PushOp(prop.GetThis());
            return;
        }

        PushOp(Value(GetObjectType()));
    }

    void State::exec_findproperty(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMn args(GetFile(), *this, mn_index);

        UPInt scope_index;
        ScopeType stype;
        PropRef prop;

        FindProp(prop, args.ArgMN, stype, scope_index);

        if (prop)
        {
            PushOp(prop.GetThis());
            return;
        }

        // Can be null.
        PushOp(Value(GetObjectType(), true));
    }

    void State::exec_getlex(UInt32 mn_index)
    {
        PushCode(mn_index);

        //TR::ReadMnCt args(GetFile(), *this, mn_index); // ReadMnCt() doesn't change stack state.

        // We can do better than this.
        PushOp(Value(GetObjectType()));
    }

    void State::exec_getabsobject(InstanceTraits::Traits& tr)
    {
        // It is a replacement opcode, so, we do not have to store mn_index.
        //TR::ReadMnCt args(GetFile(), *this, mn_index); // ReadMnCt() doesn't change stack state.

        PushOp(Value(tr));
    }

    void State::exec_newactivation()
    {
        InstanceTraits::Activation& it = GetFile().GetActivationInstanceTraits(GetTracer().GetMethodBodyInfo() SF_DEBUG_ARG(GetTracer().GetName()));

        PushOp(Value(it));
    }

    void State::exec_kill(UInt32 index)
    {
        PushCode(index);

        SetRegister(AbsoluteIndex(index), Value::GetUndefined());
        // Kill the register.
        RegistersAlive.Clear(index);
    }

    void State::exec_pushbyte(SInt32 v)
    {
        PushCode(v);

        // The value is promoted to an int.
        PushOp(Value(SInt32(SInt8(v))));
    }

    void State::exec_pushshort(SInt32 v)
    {
        PushCode(v);

        PushOp(Value(v));
    }

    void State::exec_pushstring(SInt32 v)
    {
        PushCode(v);

        StringDataPtr str = GetFile().GetConstPool().GetString(AbsoluteIndex(v));
        PushOp(
            Value(GetVM().GetStringManager().CreateString(
            str.ToCStr(), str.GetSize()
            ))
            );
    }

    void State::exec_pushint(SInt32 v)
    {
        PushCode(v);

        PushOp(Value(GetFile().GetConstPool().GetInt(v)));
    }

    void State::exec_pushuint(SInt32 v)
    {
        PushCode(v);

        PushOp(Value(GetFile().GetConstPool().GetUInt(v)));
    }

    void State::exec_pushdouble(SInt32 v)
    {
        PushCode(v);

        PushOp(Value(MakeValueNumber(GetFile().GetConstPool().GetDouble(v))));
    }

    void State::exec_hasnext2(UInt32 object_reg, UInt32 index_reg)
    {
        PushCode(object_reg);
        PushCode(index_reg);

        AbsoluteIndex reg_ind(index_reg); // Value must be of type int.
        //AbsoluteIndex obj_ind(object_reg); // Can be set to null.

        // A kind of verification.
        // reg_ind can be undefined.
        SF_ASSERT(GetRegister(reg_ind).IsUndefined() || GetValueTraits(GetRegister(reg_ind)) == &GetSIntType());

        PushOp(Value(GetBooleanType()));
    }

    void State::exec_nextname()
    {
        PopOp(); // index: int
        Value obj = PopOpValue();
        const Traits* tr = GetValueTraits(obj);

        // In general case name can be of any type.

        // In case of a Dictionary name can be of any type.
        if (tr->GetTraitsType() == Traits_Dictionary && tr->IsInstanceTraits())
        {
            // General case.
            PushOp(Value(GetObjectType())); // name
            return;
        }

        // In case of Array or Vector name is either UInt or String.
        // String is mostly a theoretical case.
        if (tr->IsArrayLike())
        {
            PushOp(Value(GetUIntType())); // name
            return;
        }

        // In case of an Object name will be a String.
        PushOp(Value(GetStringType())); // name
    }

    void State::exec_hasnext()
    {
        PopOp(); // cur_index: int
        PopOp(); // obj

        PushOp(GetSIntType()); // next_index
    }

    void State::exec_nextvalue()
    {
        PopOp(); // index: int
        PopOp(); // obj: Value

        PushOp(Value(GetObjectType())); // next_value: Value, not null.
    }

    void State::exec_astypelate()
    {
        // Top of the stack is a class. Below it is a value.
        const Value class_ = PopOpValue(); // class
        const Value::KindType kind = class_.GetKind();
        InstanceTraits::Traits* itr = NULL;

        switch (kind)
        {
        case Value::kInstanceTraits:
            itr = &class_.GetInstanceTraits();
            break;
        case Value::kClassTraits:
            {
                const ClassTraits::Traits& ctr = class_.GetClassTraits();
                itr = &ctr.GetInstanceTraits();
            }
            break;
        case Value::kClass:
            {
                const Class& cl = class_.AsClass();
                const ClassTraits::Traits& ctr = cl.GetClassTraits();
                itr = &ctr.GetInstanceTraits();
            }
            break;
        default:
            // Do nothing.
            break;
        }

        if (itr)
        {
            // We, probably, should also check for null/undefined here.
            if (GetTracer().IsPrimitiveType(itr))
                // Primitive types cannot be null (well, except of String).
                // But we have to put null on stack. So, we have to use
                // a generic type.
                itr = &GetObjectType();

            ConvertOpTo(*itr);
        }
    }

    void State::exec_1OpSInt()
    {
        ConvertOpTo(GetSIntType());
    }

    void State::exec_1OpNumber()
    {
        ConvertOpTo(GetNumberType());
    }

    void State::exec_1OpString()
    {
        ConvertOpTo(GetStringType());
    }

    void State::exec_2OpNumber()
    {
        PopOp(); // value2
        ConvertOpTo(GetNumberType());
    }

    void State::exec_2OpSInt()
    {
        PopOp(); // value2
        ConvertOpTo(GetSIntType());
    }

    void State::exec_2OpUInt()
    {
        PopOp(); // value2
        ConvertOpTo(GetUIntType());
    }

    void State::exec_2OpBoolean()
    {
        PopOp();
        ConvertOpTo(GetBooleanType());
    }

    void State::exec_istype(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMnCt args(GetFile(), *this, mn_index);

        ConvertOpTo(GetBooleanType());
    }

    void State::exec_pushscope()
    {
        // A TypeError is thrown if value is null or undefined.

        // It is safe to use BackOpValue() this way because op stack won't be midified.
        PushScope(BackOpValue());
        PopOp();
    }

    void State::exec_initproperty(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadValueMnObject args(GetFile(), *this, mn_index);
    }

    void State::exec_deleteproperty(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMnObject args(GetFile(), *this, mn_index);

        PushOp(Value(GetBooleanType()));
    }

    void State::exec_getslot(UInt32 slot_index)
    {
        PushCode(slot_index);

        TR::ReadObject args(GetVM(), *this);

        Tracer& tracer = GetTracer();
        const Traits* vtr = tracer.GetValueTraits(args.ArgObject);

        if (vtr)
        {
            /*
            // Original pCode
            // Slot's indices begin from ONE.
            if (slot_index <= vtr->GetSlots().GetSize())
            {
                const ClassTraits::Traits& ctr = tracer.GetSlotCTraits(*vtr, SlotIndex(slot_index));

                PushOp(Value(ctr.GetInstanceTraits()));
            }
            else
            {
                // !!! Check that vtr is a dynamic type.
                PushOp(Value(GetObjectType()));
            }

            return;
            */

            // Slot's indices begin from ONE.
//             if (slot_index <= vtr->GetSlots().GetSize())
//             {
//                 const SlotInfo& si = vtr->GetSlotInfo(AbsoluteIndex(SlotIndex(slot_index), *vtr));
// 
//                 /* 
//                 // Attempt 1.
//                 // Class is not initialized yet because script wasn't executed yet.
//                 if (si.IsClassOrConst() && args.ArgObject.IsObject())
//                 {
//                     // In case this is a class or a const we can get a real value.
//                     // It is already initialized.
// 
//                     Value value;
// 
//                     if (si.GetSlotValueUnsafe(GetVM(), value, args.ArgObject.GetObject()))
//                     {
//                         PushOp(value);
//                         return;
//                     }
//                 }
//                 */
// 
//                 /*
//                 // Attempt 2.
//                 // Class is not initialized yet because script wasn't executed yet.
//                 if (si.IsClass())
//                 {
//                     const ClassTraits::Traits& ctr = tracer.GetSlotCTraits(*vtr, SlotIndex(slot_index));
// 
//                     PushOp(Value(&ctr.GetInstanceTraits().GetClass()));
//                     return;
//                 }
//                 else
//                 {
//                     // Use InstanceTraits.
// 
//                     const ClassTraits::Traits& ctr = tracer.GetSlotCTraits(*vtr, SlotIndex(slot_index));
// 
//                     PushOp(Value(ctr.GetInstanceTraits()));
//                     return;
//                 }
//                 */
//             }
// 
//             // !!! Check that vtr is a dynamic type.
//             PushOp(Value(GetObjectType()));
// 
//             return;

            // Slot's indices begin from ONE.
            if (slot_index <= vtr->GetSlotInfoNum())
            {
                const SlotInfo& si = vtr->GetSlotInfo(AbsoluteIndex(SlotIndex(slot_index), *vtr));
                const ClassTraits::Traits* ctr = tracer.GetSlotCTraits(*vtr, SlotIndex(slot_index));

                if (ctr == NULL)
                {
                    return GetVM().ThrowVerifyError(VM::Error(VM::eClassNotFoundError, GetVM()
                        SF_DEBUG_ARG(si.GetDataTypeName(GetVM()))
                        ));
                }

                if (si.IsClass())
                    PushOp(Value(const_cast<ClassTraits::Traits&>(*ctr)));
                else
                    PushOp(Value(ctr->GetInstanceTraits()));
            }
            else
            {
                // !!! Check that vtr is a dynamic type.
                PushOp(Value(GetObjectType()));
            }

            return;
        }

        PushOp(Value());
    }

    void State::exec_setslot(UInt32 slot_index)
    {
        PushCode(slot_index);

        TR::ReadValueObject args(GetVM(), *this);
    }

    void State::exec_astype(UInt32 mn_index)
    {
        PushCode(mn_index);

        TR::ReadMnCtValue args(GetFile(), *this, mn_index);
    }

    void State::exec_newclass(UInt32 v)
    {
        PushCode(v);

        PopOp(); // Base Class: Object or null

        VMAbcFile& file = GetFile();

        const Abc::ClassInfo& class_info = file.GetClasses().Get(v);

        // check for *scaleform extension* packages.
        const Abc::Multiname& name = class_info.GetName(file.GetConstPool());
        Instances::Namespace& ns = file.GetInternedNamespace(name.GetNamespaceInd());
        ClassTraits::Traits* ctr = NULL;

        if (IsScaleformGFx(ns))
            // Hack on constness.
            ctr = const_cast<ClassTraits::Traits*>(GetVM().Resolve2ClassTraits(file, name));
        else
            ctr = &GetVM().GetUserDefinedTraits(file, class_info);

        if (ctr == NULL)
            ctr = &GetVM().GetClassTraitsObject();

        PushOp(Value(*ctr));
    }

    State::State(Tracer& tr, Abc::TCodeOffset cp) : pTracer(&tr)
        , BCP(cp)
        , Registers(tr.GetHeap())
        , OpStack(tr.GetHeap())
        , ScopeStack(tr.GetHeap())
        , RegistersAlive(tr.GetHeap(), tr.GetMethodBodyInfo().GetMaxLocalRegisterIndex())
    {
    }

    ValueArrayDH& State::GetValueArray(MergeSet ms)
    {
        ValueArrayDH* result = NULL;;

        switch (ms)
        {
        case msOpStack:
            result = &OpStack;
            break;
        case msScopeStack:
            result = &ScopeStack;
            break;
        case msRegisterFile:
            result = &Registers;
            break;
        }

        return *result;
    }

    const ValueArrayDH& State::GetValueArray(MergeSet ms) const
    {
        const ValueArrayDH* result = NULL;;

        switch (ms)
        {
        case msOpStack:
            result = &OpStack;
            break;
        case msScopeStack:
            result = &ScopeStack;
            break;
        case msRegisterFile:
            result = &Registers;
            break;
        }

        return *result;
    }

    void State::RefineOpCodeStack1(InstanceTraits::Traits& type, Abc::Code::OpCode op)
    {
        if (GetValueTraits(BackOpValue()) == &type)
            // Value already has a correct type.
            GetTracer().SetNewOpCode(op);
        else
            ConvertOpTo(type);
    }

    void State::RefineOpCodeStack2(InstanceTraits::Traits& type, Abc::Code::OpCode op)
    {
        const Value _2 = PopOpValue(); // value2

        if (GetValueTraits(BackOpValue()) == &type && GetValueTraits(_2) == &type)
            // Values already have correct types.
            GetTracer().SetNewOpCode(op);
        else
            ConvertOpTo(type);
    }

    void State::RefineOpCodeReg1(InstanceTraits::Traits& type, Abc::Code::OpCode op, int reg_num)
    {
        const Value& r = GetRegister(AbsoluteIndex(reg_num));

        if (GetValueTraits(r) == &type)
            // Value already has a correct type.
            GetTracer().SetNewOpCode(op);
        else
            ConvertRegisterTo(AbsoluteIndex(reg_num), type);

        PushCode(reg_num);
    }

    void State::exec_pop()
    {
        using namespace Abc;

        if (GetTracer().IsNotRefCountedType(GetValueTraits(BackOpValue())))
            // Value has not ref-counted type.
            GetTracer().SetNewOpCode(Code::op_pop_nrc);

        PopOp();
    }

    void State::exec_dup()
    {
        using namespace Abc;

        if (GetTracer().IsNotRefCountedType(GetValueTraits(BackOpValue())))
            // Value has not ref-counted type.
            GetTracer().SetNewOpCode(Code::op_dup_nrc);

        // This sequence of calls is necessary to prevent problems related
        // to Array reallocation.
        PushOp(Value::GetUndefined());
        const Value& v = GetOpValue(GetOpStack().GetSize() - 2);
        SetBackOpValueUnsafe(v);
    }

    void State::exec_convert_u()
    {
        Value& value = BackOpValue(); // value

        if (value.IsPrimitive())
            // Try to preserve real value on stack.
            value.ToUInt32Value().DoNotCheck();
        else
            ConvertOpTo(GetUIntType());
    }

    void State::exec_convert_i()
    {
        Value& value = BackOpValue(); // value

        if (value.IsPrimitive())
            // Try to preserve real value on stack.
            value.ToInt32Value().DoNotCheck();
        else
            ConvertOpTo(GetSIntType());
    }

    void State::exec_convert_d()
    {
        Value& value = BackOpValue(); // value

        if (value.IsPrimitive())
            // Try to preserve real value on stack.
            value.ToNumberValue().DoNotCheck();
        else
            ConvertOpTo(GetNumberType());
    }

    void State::exec_convert_b()
    {
        Value& value = BackOpValue(); // value

        if (value.IsPrimitive())
            // Try to preserve real value on stack.
            value.ToBooleanValue();
        else
            ConvertOpTo(GetBooleanType());
    }

    void State::SwapOp()
    {
        // Optimized version ...
        SPInt num      = OpStack.GetSize();
        const Value _2 = OpStack[--num];

        OpStack[num] = OpStack[num - 1];
        OpStack[--num] = _2;
    }

} // namespace TR

///////////////////////////////////////////////////////////////////////////////
Tracer::Tracer(
    MemoryHeap* heap,
    const CallFrame& cf,
    Abc::TOpCode& wc,
    Abc::MethodBodyInfo::Exception& we
    )
    : Done(false)
    , Heap(heap)
    , CF(cf)
    , WCode(wc)
    , WException(we)
    , CurrOffset(0)
    , BCode(cf.GetMethodBodyInfo().GetCode().GetCode())
    , pCode(reinterpret_cast<const UInt8*>(BCode.ToCStr()))
    , CodeEnd(BCode.GetSize())
    , OrigOpcodePos(heap)
    , NewOpcodePos(heap)
    , PosToRecalculate(heap)
    , Orig2newPosMap(heap)
    , States(heap)
    , PrintOffset(0)
    , CurrBlock(NULL)
{
    VM& vm = GetVM();

    // Switch on State tracing
    {
        SetNeedToCheckOpCode(vm.GetUI().NeedToCheckOpCode());
        SetState(FlashUI::sStep);
        PrintOffset = vm.GetCallStack().GetSize();

        if (PrintOffset)
            --PrintOffset;
    }

    WCode.Clear();
    WCode.Reserve(BCode.GetSize());
    Orig2newPosMap.Resize(BCode.GetSize());

    States.PushBack(TR::State(*this, 0));
    TR::State& st = States.Back();
    ValueArrayDH& reg_file = st.Registers;
    FixedBitSetDH<StatMV_VM_Tracer_Mem>& reg_alive = st.RegistersAlive;
    unsigned reg = 0;

    // Initialize registers ...
    {
        // Initialize *this*

#if 0
        // Version 1.
        // Doesn't work in case of custom this.
        {
            Value& _this = CF.GetRegister(0);

            if (_this.IsObject() && _this.GetObject()->GetName() == "global")
                reg_file.PushBack(_this);
            else if (_this.IsClass())
                reg_file.PushBack(_this.AsClass().GetClassTraits());
            else
                reg_file.PushBack(vm.GetInstanceTraits(_this));
        }
#endif

#if 0
        // Version 2.
        // It works.
        {
            Traits* ot = const_cast<Traits*>(CF.GetOriginationTraits());

            // We MAY NOT use real object for *this* because this may be passed
            // at run time and can be of different type
            if (ot)
            {
                if (ot->IsClassTraits())
                    reg_file.PushBack(static_cast<ClassTraits::Traits&>(*ot));
                else
                    reg_file.PushBack(static_cast<InstanceTraits::Traits&>(*ot));
            }
            else
                reg_file.PushBack(GetObjectType());

            // "this" is always alive.
            reg_alive.Set(reg++);
        }
#endif

#if 0
        // It doesn't work.
        // We MAY NOT use real object for *this* because this may be passed
        // at run time and can be of different type

        // Version 3.
        {
            Traits* ot = const_cast<Traits*>(CF.GetOriginationTraits());

            if (ot)
            {
                if (ot->IsGlobal())
                    reg_file.PushBack(CF.GetRegister(0));
                else if (ot->IsClassTraits())
                    reg_file.PushBack(static_cast<ClassTraits::Traits&>(*ot));
                else
                    reg_file.PushBack(static_cast<InstanceTraits::Traits&>(*ot));
            }
            else
                reg_file.PushBack(GetObjectType());
        }
#endif

#if 1
        // Version 4.
        // It works.
        {
            Traits* ot = const_cast<Traits*>(CF.GetOriginationTraits());

            // We MAY NOT use real object for *this* because this may be passed
            // at run time and can be of different type
            if (ot)
            {
                if (ot->IsClassTraits())
                    reg_file.PushBack(static_cast<ClassTraits::Traits&>(*ot));
                else
                {
                    const Value& invoker = CF.GetInvoker();

                    if (invoker.GetKind() == Value::kFunction)
                        // Correct object type for constructor function.
                        reg_file.PushBack(GetObjectType());
                    else
                        reg_file.PushBack(static_cast<InstanceTraits::Traits&>(*ot));
                }
            }
            else
                reg_file.PushBack(GetObjectType());


            // "this" is always alive.
            reg_alive.Set(reg++);
        }
#endif

        ///////////
        // Set up the rest of the registers.
        ///////////

        const Abc::MethodBodyInfo& mbi = GetMethodBodyInfo();

        const Abc::MethodInfo& mi = GetMethodBodyInfo().GetMethodInfo(GetAbcFile().GetMethods());
        const SInt32 maxInd = mbi.GetMaxLocalRegisterIndex();

        for(SInt32 i = 1; i < maxInd; ++i)
            reg_file.PushBack(Value::GetUndefined());

        // Get register's types.
        const UPInt param_count = mi.GetParamCount();

        // Registers 1 through method_info.param_count holds parameter values coerced to the declared types
        // of the parameters. If fewer than method_body_info.local_count values are supplied to the call then
        // the remaining values are either the values provided by default value declarations (optional arguments)
        // or the value undefined.

        for(UPInt i = 0; i < param_count; ++i)
        {
            const Abc::Multiname& amn = mi.GetParamType(GetAbcFile().GetConstPool(), i);
            const ClassTraits::Traits* tr = vm.Resolve2ClassTraits(GetFile(), amn);

            if (tr)
            {
                reg_file[reg] = tr->GetInstanceTraits();
                reg_alive.Set(reg++);
            }
            else
            {
                // Class wasn't found. It happens.
                vm.ThrowVerifyError(VM::Error(VM::eClassNotFoundError, vm
                    SF_DEBUG_ARG(GetFile().GetInternedString(amn.GetNameInd()))
                    ));

                return;
            }
        }

        if (mi.NeedRest())
        {
            // If NEED_REST is set in method_info.flags, the method_info.param_count+1 register is set up to
            // reference an array that holds the superfluous arguments.

            reg_file[reg] = vm.GetClassTraitsArray().GetInstanceTraits();
            reg_alive.Set(reg++);
        } else if (mi.NeedArguments())
        {
            // If NEED_ARGUMENTS is set in method_info.flags, the method_info.param_count+1 register is set up
            // to reference an "arguments" object that holds all the actual arguments: see ECMA-262 for more
            // information. (The AVM2 is not strictly compatible with ECMA-262; it creates an Array object for
            // the "arguments" object, whereas ECMA-262 requires a plain Object.)

            // "arguments" is a regular Array. There is no an explicit "arguments" class.
            reg_file[reg] = vm.GetClassTraitsArray().GetInstanceTraits();
            reg_alive.Set(reg++);
        }
    }

    // Create initial state/block.
    {
#if 0
        // Everything seems to be fine without this pCode.
        if (CF.IsNewObjectCreated())
            st.GetOpStack().PushBack(reg_file[0]);
#endif
        Blocks.PushBack(SF_HEAP_NEW(GetHeap()) TR::Block(0, 0));
    }
}

Tracer::~Tracer()
{
    // Free list elements.
    {
        TR::Block* block = Blocks.GetFirst();
        while(!Blocks.IsNull(block))
        {
            TR::Block* next = Blocks.GetNext(block);
            SF_FREE(block);
            block = next;
        }
        Blocks.Clear();
    }
}

void Tracer::EmitCode()
{
    using namespace Abc;

    // Sometimes compiler generates dummy pCode, which produces
    // absolute address outside of a pCode block. Such opcodes should
    // be dropped from a newly generated pCode. TBD.

    if (Done)
        return;

#ifdef GFX_AS3_TRACE
    FlashUI& ui = GetUI();

    if (ui.NeedToCheckOpCode())
    {
        MakeOffset(ui, GetPrintOffset());

        ui.Output(FlashUI::Output_Action, "=== Start optimization ");
        SF_DEBUG_CODE(ui.Output(FlashUI::Output_Action, GetName().ToCStr());)
        ui.Output(FlashUI::Output_Action, " ===\n");
    }
#endif

    VM& vm = GetVM();
    const MethodBodyInfo::Exception& e = GetMethodBodyInfo().exception;

    // Create blocks for exceptions if any.
    {
        const TR::State* pState = &GetState(GetFirstBlock());

        for (UPInt i = 0; i < e.GetSize(); ++i)
        {
            const MethodBodyInfo::ExceptionInfo& ei = e.Get(i);

            // A "from" block is uninitialized, but AddBlock() will mark it as initialized.
            // We will need to reset this flag.
            TR::Block* try_block = AddBlock(*pState, ei.GetFrom(), false, false);

            // pState can be invalidated in AddBlock().
            pState = &GetState(GetFirstBlock());

            if (try_block)
            {
                // Reset the "initialized" flag.
                try_block->SetInitialized(false);
                try_block->SetTryBlock();
            }

            // ei.GetTo() is inclusive.
//             if (ei.GetTo() != ei.GetTargetPos())
//                 AddBlock(ei.GetTo());

            // !!! ei.GetTargetPos() can be a dead block, if there is no throw.
            // If there is no explicit throw opcode we need to simulate it,
            // otherwise stack will be broken.
            // We can specify only the beginning of the block.
            // catch_block is already initialized.
            // A "target" block is initialized.
            TR::Block* catch_block = AddBlock(*pState, ei.GetTargetPos(), false, false);

            // pState can be invalidated in AddBlock().
            pState = &GetState(GetFirstBlock());

            if (catch_block)
            {
                catch_block->SetCatchBlock();

                TR::State& state = GetState(*catch_block);
                const SInt32 et_ind = ei.GetExceptionTypeInd();

                if (et_ind == 0)
                {
                    // This handler can handle any type of exceptions ...
                    state.PushOp(Value(GetObjectType()));
                }
                else
                {
                    const Abc::Multiname& amn = GetFile().GetConstPool().GetMultiname(et_ind);
                    const ClassTraits::Traits* etr = vm.Resolve2ClassTraits(GetFile(), amn);

                    if (etr)
                    {
                        state.PushOp(Value(etr->GetInstanceTraits()));
                    }
                    else
                    {
                        // Class wasn't found. It happens.
                        return vm.ThrowVerifyError(VM::Error(VM::eClassNotFoundError, vm
                            SF_DEBUG_ARG(GetFile().GetInternedString(amn.GetNameInd()))
                            ));
                    }
                }
            }
        }
    }

    TraceBlock(0, GetFirstBlock());

    if (vm.IsException())
    {
        // Clear pCode to prevent execution of not completely generated pCode.
        WCode.Clear();
        return;
    }

#ifdef GFX_AS3_TRACE
    if (ui.NeedToCheckOpCode())
    {
        MakeOffset(ui, GetPrintOffset());

        ui.Output(FlashUI::Output_Action, "=== Finish optimization ");
        SF_DEBUG_CODE(ui.Output(FlashUI::Output_Action, GetName().ToCStr());)
        ui.Output(FlashUI::Output_Action, " ===\n");
    }
#endif

    // Recalculate positions.
    for(UPInt i = 0; i < PosToRecalculate.GetSize(); ++i)
    {
        // Get position in WCode where an absolute address is stored.
        const Recalculate& r = PosToRecalculate[i];
        const Abc::TCodeOffset pos = r.pos;
        const TOpCode::ValueType absolute_address = WCode[pos];

        // Fix relative offset.
        // Convert it back from absolute to relative.
        TOpCode::ValueType new_address = 0;

        // It is possible that compiler generates dummy pCode, which addresses
        // pCode outside of a pCode segment. Let's set address to ZERO in such
        // case.
        if (absolute_address < Orig2newPosMap.GetSize())
        {
            // long version for debugging.
            new_address = static_cast<TOpCode::ValueType>(Orig2newPosMap[absolute_address]);
            new_address -= static_cast<TOpCode::ValueType>(pos);
            new_address += r.base;
        }

        SF_ASSERT(new_address < WCode.GetSize());
        WCode[pos] = new_address;
    }

    // Create exception info for word pCode.
    {
        const MethodBodyInfo::Exception& e = GetMethodBodyInfo().exception;
        for (UPInt i = 0; i < e.GetSize(); ++i)
        {
            const MethodBodyInfo::ExceptionInfo& ei = e.Get(i);

            WException.info.PushBack(MethodBodyInfo::ExceptionInfo(
                static_cast<SInd>(Orig2newPosMap[ei.GetFrom()]),
                static_cast<SInd>(Orig2newPosMap[ei.GetTo()]),
                static_cast<SInd>(Orig2newPosMap[ei.GetTargetPos()]),
                ei.GetExceptionTypeInd(),
                ei.GetVariableNameInd()
                ));
        }
    }

    // Clear original pCode.
    // A hack with constness.
    const_cast<Abc::MethodBodyInfo&>(CF.GetMethodBodyInfo()).ClearCode();

    Done = true;
}

void Tracer::TraceBlock(Abc::TCodeOffset bcp, const TR::Block& initBlock)
{
    using namespace Abc;

    TR::Block*& pBlock = CurrBlock;
    pBlock = GetBlock(bcp);
    SF_ASSERT(pBlock);

    if (pBlock->IsInitializedBlock())
    {
        // Block is already initialized. We just need to merge states
        // and, probably, retrace it.
        if (!MergeBlock(*pBlock, initBlock))
            // Oops. Exception.
            return;
    }
    else
    {
        // Block is not yet initialized and traced.
        InitializeBlock(*pBlock, initBlock);
    }

    TR::State* pState = &GetState(*pBlock);

    /* Do not handle this for the time being.
    UPInt tryInd = 0;
    UPInt tryBegin = SF_MAX_UPINT;
    UPInt tryEnd = SF_MAX_UPINT;

    // Try block related stuff.
    {
        const MethodBodyInfo::Exception& e = GetMethodBodyInfo().exception;
        if (tryInd < e.GetSize())
        {
            const MethodBodyInfo::ExceptionInfo& ei = e.Get(tryInd++);
            tryBegin = ei.GetFrom();
            tryEnd = ei.GetTo();
        }
    }
    */

#ifdef GFX_AS3_TRACE
    FlashUI& ui = GetUI();
#endif

    while (bcp < CodeEnd)
    {
        // Check for next block
        {
            const TR::Block& prevBlock = *pBlock;
            TR::Block* nextBlock = GetBlock(bcp);

            if (nextBlock && nextBlock->GetFrom() == bcp)
            {
                // We entered a new block.
#ifdef GFX_AS3_TRACE
                if (ui.NeedToCheckOpCode())
                {
                    MakeOffset(ui, GetPrintOffset());
                    ui.Output(FlashUI::Output_Action, "// Basic Block.\n");
                }
#endif
                pBlock = nextBlock;
                pState = &GetState(*pBlock);

                if (pBlock->IsInitializedBlock())
                {
                    if (pBlock->IsCatchBlock())
                    {
#ifdef GFX_AS3_TRACE
                        if (ui.NeedToCheckOpCode())
                        {
                            MakeOffset(ui, GetPrintOffset());
                            ui.Output(FlashUI::Output_Action, "// Catch Block.\n");
                        }
#endif
                    }

                    if (!MergeBlock(*pBlock, prevBlock))
                        // Oops. Exception.
                        return;
                }
                else
                    InitializeBlock(*pBlock, prevBlock);
            }
        }


        // Handle dead blocks
        {
            SF_ASSERT(pBlock);
            while (pBlock->IsDeadBlock() && bcp < CodeEnd)
            {
                // This call is mandatory to maintain Orig2newPosMap consistency.
                RegisterOrigOpCode(bcp);

                const UInt8 byte_code = static_cast<UInt8>(Read8(pCode, bcp));
                const Code::OpCode dopcode = static_cast<Code::OpCode>(byte_code);

#ifdef GFX_AS3_TRACE
                if (ui.NeedToCheckOpCode())
                {
                    MakeOffset(ui, GetPrintOffset());
                    ui.Output(FlashUI::Output_Action, "// Skip opcode below.\n");
                    ui.OnOpCode(CurrOffset);
                }
#endif
                switch (dopcode)
                {
                case Code::op_ifnlt:
                case Code::op_ifnle:
                case Code::op_ifngt:
                case Code::op_ifnge:
                case Code::op_ifeq:
                case Code::op_ifge:
                case Code::op_ifgt:
                case Code::op_ifle:
                case Code::op_iflt:
                case Code::op_ifne:
                case Code::op_ifstricteq:
                case Code::op_ifstrictne:
                case Code::op_iftrue:
                case Code::op_iffalse:
                case Code::op_jump:
                    ReadS24(pCode, bcp);
                    break;
                case Code::op_lookupswitch:
                    {
                        ReadS24(pCode, bcp);
                        int case_count = ReadU30(pCode, bcp);

                        for(int i = 0; i <= case_count; ++i)
                            ReadS24(pCode, bcp);
                    }
                    break;
                case Code::op_pushbyte:
                    Read8(pCode, bcp);
                    break;
                case Code::op_debug:
                    Read8(pCode, bcp);
                    ReadU30(pCode, bcp);
                    Read8(pCode, bcp);
                    ReadU30(pCode, bcp);
                    break;
                default:
                    switch (Code::GetOpCodeInfo(dopcode).operandCount)
                    {
                    case 2:
                        ReadU30(pCode, bcp);
                        // No break on purpose.
                    case 1:
                        ReadU30(pCode, bcp);
                        break;
                    default:
                        break;
                    }
                }

                // Check for next block
                {
                    const TR::Block& prevBlock = *pBlock;
                    TR::Block* nextBlock = GetBlock(bcp);

                    if (nextBlock && nextBlock->GetFrom() == bcp)
                    {
                        // We entered a new block.
#ifdef GFX_AS3_TRACE
                        if (ui.NeedToCheckOpCode())
                        {
                            MakeOffset(ui, GetPrintOffset());
                            ui.Output(FlashUI::Output_Action, "// Basic Block.\n");
                        }
#endif
                        pBlock = nextBlock;
                        pState = &GetState(*pBlock);

                        if (pBlock->IsInitializedBlock())
                        {
                            if (pBlock->IsCatchBlock())
                            {
#ifdef GFX_AS3_TRACE
                                if (ui.NeedToCheckOpCode())
                                {
                                    MakeOffset(ui, GetPrintOffset());
                                    ui.Output(FlashUI::Output_Action, "// Catch Block.\n");
                                }
#endif
                            }

                            if (!MergeBlock(*pBlock, prevBlock))
                                // Oops. Exception.
                                return;
                        }
                        else
                            InitializeBlock(*pBlock, prevBlock);
                    }
                }
            }

            if (bcp >= CodeEnd)
                break;
        } // Handle dead blocks

        // Try block related stuff.
        // Should be evaluated before an opcode.
        /* Do not handle this for the time being.
        if (tryBegin != SF_MAX_UPINT && bcp > tryEnd)
        {
            const MethodBodyInfo::Exception& e = GetMethodBodyInfo().exception;
            if (tryInd < e.GetSize())
            {
                // Get a new try block.

                const MethodBodyInfo::ExceptionInfo& ei = e.Get(tryInd++);
                tryBegin = ei.GetFrom();
                tryEnd = ei.GetTo();
            }
            else
            {
                // No more try blocks.
                tryBegin = SF_MAX_UPINT;
                tryEnd = SF_MAX_UPINT;
            }
        }

        const bool insideOfTry = (bcp >= tryBegin && bcp <= tryEnd);
        */

        // This call is mandatory to maintain Orig2newPosMap consistency.
        RegisterOrigOpCode(bcp);

        const UInt8 byte_code = static_cast<UInt8>(Read8(pCode, bcp));
        const Code::OpCode opcode = static_cast<Code::OpCode>(byte_code);

#ifdef GFX_AS3_TRACE
        if (ui.NeedToCheckOpCode() && ui.OnOpCode(CurrOffset))
        {
            // That should never happen.
            SF_ASSERT(false);
        }
#endif

        // Try to substitute with a strictly typed opcode.
        // Opcode can be replaced.
        if (SubstituteOpCode(bcp, *pState, byte_code))
            continue;

        // SubstituteOpCode() can throw exceptions.
        if (GetVM().IsException())
            return;

        PushNewOpCode(opcode);

        // Fix offsets and remove useless opcodes.
        {
            // We do not need to handle new WCode here ...
            switch (opcode)
            {
            case Code::op_throw:
                /* DO NOT delete this pCode.
                // It looks like it is not enough to put logic below only in op_throw.
                {
                    Code::OpCode noc = GetNextOpCode();
                    bool deadBlock = (noc != Code::op_label && noc != Code::op_jump);

                    AddBlock(bcp, deadBlock); // Block after throw. Possible dead block.
                }
                */

                pState->exec_throw();

                // Block after throw. It should NOT be marked as a dead block as previously.
                AddBlock(*pState, bcp);
                // pState can be invalidated in AddBlock().
                pState = &GetState(*pBlock);
                break;
            case Code::op_getsuper:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_setsuper:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_dxns:
                pState->exec_dxns(ReadU30(pCode, bcp));
                break;
            case Code::op_dxnslate:
                pState->exec_dxnslate();
                break;
            case Code::op_kill:
                pState->exec_kill(ReadU30(pCode, bcp));
                break;
            case Code::op_label:
                AddBlock(*pState, CurrOffset); // Block starts from label.

                // pState can be invalidated in AddBlock().
                pState = &GetState(*pBlock);

                pState->exec_label();

                // Get rid of op_label.
                PopNewOpCode();

                break;
            case Code::op_ifnlt:
            case Code::op_ifnle:
            case Code::op_ifngt:
            case Code::op_ifnge:
            case Code::op_ifeq:
            case Code::op_ifge:
            case Code::op_ifgt:
            case Code::op_ifle:
            case Code::op_iflt:
            case Code::op_ifne:
            case Code::op_ifstricteq:
            case Code::op_ifstrictne:
                {
                    if (IsSIntType(pState->BackOpValue()) && IsSIntType(pState->BackOp2ndValue()))
                    {
                        Code::OpCode new_opcode = opcode;
                        switch (opcode)
                        {
                        case Code::op_ifnlt:
                            new_opcode = Code::op_ifnlt_ti;
                            break;
                        case Code::op_ifnle:
                            new_opcode = Code::op_ifnle_ti;
                            break;
                        case Code::op_ifngt:
                            new_opcode = Code::op_ifngt_ti;
                            break;
                        case Code::op_ifnge:
                            new_opcode = Code::op_ifnge_ti;
                            break;
                        case Code::op_ifeq:
                            new_opcode = Code::op_ifeq_ti;
                            break;
                        case Code::op_ifge:
                            new_opcode = Code::op_ifge_ti;
                            break;
                        case Code::op_ifgt:
                            new_opcode = Code::op_ifgt_ti;
                            break;
                        case Code::op_ifle:
                            new_opcode = Code::op_ifle_ti;
                            break;
                        case Code::op_iflt:
                            new_opcode = Code::op_iflt_ti;
                            break;
                        case Code::op_ifne:
                            new_opcode = Code::op_ifne_ti;
                            break;
                        case Code::op_ifstricteq:
                            new_opcode = Code::op_ifeq_ti;
                            break;
                        case Code::op_ifstrictne:
                            new_opcode = Code::op_ifne_ti;
                            break;
                        default:
                            break;
                        }

                        SetNewOpCode(new_opcode);
                    } else if (IsNumberType(pState->BackOpValue()) && IsNumberType(pState->BackOp2ndValue()))
                    {
                        Code::OpCode new_opcode = opcode;
                        switch (opcode)
                        {
                        case Code::op_ifnlt:
                            new_opcode = Code::op_ifnlt_td;
                            break;
                        case Code::op_ifnle:
                            new_opcode = Code::op_ifnle_td;
                            break;
                        case Code::op_ifngt:
                            new_opcode = Code::op_ifngt_td;
                            break;
                        case Code::op_ifnge:
                            new_opcode = Code::op_ifnge_td;
                            break;
                        case Code::op_ifeq:
                            new_opcode = Code::op_ifeq_td;
                            break;
                        case Code::op_ifge:
                            new_opcode = Code::op_ifge_td;
                            break;
                        case Code::op_ifgt:
                            new_opcode = Code::op_ifgt_td;
                            break;
                        case Code::op_ifle:
                            new_opcode = Code::op_ifle_td;
                            break;
                        case Code::op_iflt:
                            new_opcode = Code::op_iflt_td;
                            break;
                        case Code::op_ifne:
                            new_opcode = Code::op_ifne_td;
                            break;
                        case Code::op_ifstricteq:
                            new_opcode = Code::op_ifeq_td;
                            break;
                        case Code::op_ifstrictne:
                            new_opcode = Code::op_ifne_td;
                            break;
                        default:
                            break;
                        }

                        SetNewOpCode(new_opcode);
                    }

                    // Relative
                    const int offset = ReadS24(pCode, bcp);

                    pState->PopOp();
                    pState->PopOp();
                    // Relative
                    StoreOffset(bcp, *pState, offset);

                    // pState can be invalidated in StoreOffset().
                    pState = &GetState(*pBlock);
                }
                break;
            case Code::op_iftrue:
            case Code::op_iffalse:
                {
                    if (IsBooleanType(pState->BackOpValue()))
                        SetNewOpCode(opcode == Code::op_iftrue ? Code::op_iftrue_tb : Code::op_iffalse_tb);

                    // Relative
                    const int offset = ReadS24(pCode, bcp);

                    pState->PopOp();
                    StoreOffset(bcp, *pState, offset);

                    // pState can be invalidated in StoreOffset().
                    pState = &GetState(*pBlock);
                }
                break;
            case Code::op_jump:
                {
                    const int offset = ReadS24(pCode, bcp);

                    // No manipulation with stack.
                    StoreOffset(bcp, *pState, offset);

                    // pState can be invalidated in StoreOffset().
                    pState = &GetState(*pBlock);

                    AddBlock(*pState, bcp, true); // Code immediately following the jump. Possible dead block.

                    // pState can be invalidated in AddBlock().
                    pState = &GetState(*pBlock);

                    //bcp += offset;
                }
                break;
            case Code::op_lookupswitch:
                {
                    pState->exec_lookupswitch();

                    Abc::TCodeOffset base_location = CurrOffset;
                    int default_offset = ReadS24(pCode, bcp);
                    StoreOffset(bcp, *pState, static_cast<SInt32>(base_location + default_offset - bcp), 1);

                    // pState can be invalidated in StoreOffset().
                    pState = &GetState(*pBlock);

                    int case_count = ReadU30(pCode, bcp);
                    PushNewOpCodeArg(case_count);

                    for(int i = 0; i <= case_count; ++i)
                    {
                        const int offset = ReadS24(pCode, bcp);

                        StoreOffset(bcp, *pState, static_cast<SInt32>(base_location + offset - bcp), i + 3);

                        // pState can be invalidated in StoreOffset().
                        pState = &GetState(*pBlock);
                    }
                }
                AddBlock(*pState, bcp, true); // Code immediately following the lookupswitch. Possible dead block.

                // pState can be invalidated in AddBlock().
                pState = &GetState(*pBlock);

                break;
            case Code::op_pushwith:
                pState->exec_pushwith();
                break;
            case Code::op_popscope:
                pState->exec_popscope();
                break;
            case Code::op_nextname:
                pState->exec_nextname();
                break;
            case Code::op_hasnext:
                pState->exec_hasnext();
                break;
            case Code::op_pushnull:
                // Tamarin style.
                //pState->PushOp(Value(GetNullType(), true));
                pState->PushOp(Value::GetNull());
                break;
            case Code::op_pushundefined:
                // Tamarin style.
                //pState->PushOp(Value(GetVoidType()));
                pState->PushOp(Value::GetUndefined());
                break;
            case Code::op_nextvalue:
                pState->exec_nextvalue();
                break;
            case Code::op_pushbyte:
                pState->exec_pushbyte(Read8(pCode, bcp));
                break;
            case Code::op_pushshort:
                pState->exec_pushshort(ReadU30(pCode, bcp));
                break;
            case Code::op_pushtrue:
                pState->PushOp(Value(true));
                break;
            case Code::op_pushfalse:
                pState->PushOp(Value(false));
                break;
            case Code::op_pushnan:
                pState->PushOp(Value(GetNumberType()));
                break;
            case Code::op_pop:
                pState->exec_pop();
                break;
            case Code::op_dup:
                pState->exec_dup();
                break;
            case Code::op_swap:
                pState->SwapOp();
                break;
            case Code::op_pushstring:
                pState->exec_pushstring(ReadU30(pCode, bcp));
                break;
            case Code::op_pushint:
                pState->exec_pushint(ReadU30(pCode, bcp));
                break;
            case Code::op_pushuint:
                pState->exec_pushuint(ReadU30(pCode, bcp));
                break;
            case Code::op_pushdouble:
                pState->exec_pushdouble(ReadU30(pCode, bcp));
                break;
            case Code::op_pushscope:
                pState->exec_pushscope();
                break;
            case Code::op_pushnamespace:
                pState->exec_pushnamespace(ReadU30(pCode, bcp));
                // ??? Exceptions ?
                break;
            case Code::op_hasnext2:
                {
                    UInt32 object_reg = ReadU30(pCode, bcp);
                    UInt32 index_reg = ReadU30(pCode, bcp);
                    pState->exec_hasnext2(object_reg, index_reg);
                }
                break;
            case Code::op_increment_tu:
                pState->exec_li8();
                break;
            case Code::op_decrement_tu:
                pState->exec_li16();
                break;
            case Code::op_inclocal_tu:
                pState->exec_li32();
                break;
            case Code::op_declocal_tu:
                pState->exec_lf32();
                break;
            case Code::op_lf64:
                pState->exec_lf64();
                break;
            case Code::op_si8:
                pState->exec_si8();
                break;
            case Code::op_si16:
                pState->exec_si16();
                break;
            case Code::op_si32:
                pState->exec_si32();
                break;
            case Code::op_sf32:
                pState->exec_sf32();
                break;
            case Code::op_sf64:
                pState->exec_sf64();
                break;
            case Code::op_newfunction:
                pState->exec_newfunction(ReadU30(pCode, bcp));
                break;
            case Code::op_call:
                pState->exec_call(ReadU30(pCode, bcp));
                break;
            case Code::op_construct:
                pState->exec_construct(ReadU30(pCode, bcp));
                break;
            case Code::op_callmethod:
                {
                    UInt32 _1 = ReadU30(pCode, bcp);
                    UInt32 _2 = ReadU30(pCode, bcp);
                    pState->exec_callmethod(_1, _2);
                }
                break;
            case Code::op_callstatic:
                {
                    UInt32 _1 = ReadU30(pCode, bcp);
                    UInt32 _2 = ReadU30(pCode, bcp);
                    pState->exec_callstatic(_1, _2);
                }
                break;
            case Code::op_callsuper:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_callproperty:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_returnvoid:
            case Code::op_returnvalue:
                // Possible dead block.
                AddBlock(*pState, bcp, true);

                // pState can be invalidated in AddBlock().
                pState = &GetState(*pBlock);

                // Exceptions are possible, but we can ignore them here.

                // Stop tracing.
                //goto call_stack_label;
                break;
            case Code::op_constructsuper:
                pState->exec_constructsuper(ReadU30(pCode, bcp));
                break;
            case Code::op_constructprop:
                {
                    UInt32 _1 = ReadU30(pCode, bcp);
                    UInt32 _2 = ReadU30(pCode, bcp);
                    pState->exec_constructprop(_1, _2);
                }
                break;
            case Code::op_callproplex:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_callsupervoid:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_callpropvoid:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_sxi1:
                pState->exec_sxi1();
                break;
            case Code::op_sxi8:
                pState->exec_sxi8();
                break;
            case Code::op_sxi16:
                pState->exec_sxi16();
                break;
            case Code::op_applytype:
                pState->exec_applytype(ReadU30(pCode, bcp));
                break;
            case Code::op_newobject:
                pState->exec_newobject(ReadU30(pCode, bcp));
                break;
            case Code::op_newarray:
                pState->exec_newarray(ReadU30(pCode, bcp));
                break;
            case Code::op_newactivation:
                pState->exec_newactivation();
                break;
            case Code::op_newclass:
                pState->exec_newclass(ReadU30(pCode, bcp));
                break;
            case Code::op_getdescendants:
                pState->exec_getdescendants(ReadU30(pCode, bcp));
                break;
            case Code::op_newcatch:
                pState->exec_newcatch(ReadU30(pCode, bcp));
                break;
            case Code::op_findpropstrict:
                pState->exec_findpropstrict(ReadU30(pCode, bcp));
                break;
            case Code::op_findproperty:
                pState->exec_findproperty(ReadU30(pCode, bcp));
                break;
            case Code::op_getlex:
                pState->exec_getlex(ReadU30(pCode, bcp));
                break;
            case Code::op_setproperty:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_setlocal:
                pState->exec_setlocal(ReadU30(pCode, bcp));
                break;
            case Code::op_getglobalscope:
                pState->exec_getglobalscope();
                break;
            case Code::op_getscopeobject:
                pState->exec_getscopeobject(ReadU30(pCode, bcp));
                break;
            case Code::op_getproperty:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_initproperty:
                pState->exec_initproperty(ReadU30(pCode, bcp));
                break;
            case Code::op_deleteproperty:
                pState->exec_deleteproperty(ReadU30(pCode, bcp));
                break;
            case Code::op_getslot:
                pState->exec_getslot(ReadU30(pCode, bcp));
                break;
            case Code::op_setslot:
                pState->exec_setslot(ReadU30(pCode, bcp));
                break;
            case Code::op_getglobalslot:
                pState->exec_getglobalslot(ReadU30(pCode, bcp));
                break;
            case Code::op_setglobalslot:
                pState->exec_setglobalslot(ReadU30(pCode, bcp));
                break;
            case Code::op_convert_s:
                pState->exec_1OpString();
                break;
            case Code::op_esc_xelem:
                pState->exec_esc_xelem();
                break;
            case Code::op_esc_xattr:
                pState->exec_esc_xattr();
                break;
            case Code::op_convert_i:
                pState->exec_convert_i();
                break;
            case Code::op_convert_u:
                pState->exec_convert_u();
                break;
            case Code::op_convert_d:
                pState->exec_convert_d();
                break;
            case Code::op_convert_b:
                pState->exec_convert_b();
                break;
            case Code::op_convert_o:
                pState->exec_convert_o();
                break;
            case Code::op_checkfilter:
                pState->exec_checkfilter();
                break;
            case Code::op_coerce:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_coerce_a:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_coerce_s:
                pState->exec_1OpString();
                break;
            case Code::op_astype:
                pState->exec_astype(ReadU30(pCode, bcp));
                break;
            case Code::op_astypelate:
                pState->exec_astypelate();
                break;
            case Code::op_negate:
                pState->exec_negate();
                break;
            case Code::op_increment:
                pState->exec_1OpNumber();
                break;
            case Code::op_inclocal:
                pState->exec_inclocal(ReadU30(pCode, bcp));
                break;
            case Code::op_decrement:
                pState->exec_1OpNumber();
                break;
            case Code::op_declocal:
                pState->exec_declocal(ReadU30(pCode, bcp));
                break;
            case Code::op_typeof:
                pState->exec_1OpString();
                break;
            case Code::op_not:
                pState->exec_not();
                break;
            case Code::op_bitnot:
                pState->exec_1OpSInt();
                break;
            case Code::op_add_d:
                pState->exec_add_d();
                break;
            case Code::op_add:
                // Should be handled by SubstituteOpCode().
                SF_ASSERT(false);
                break;
            case Code::op_subtract:
                pState->exec_subtract();
                break;
            case Code::op_multiply:
                pState->exec_multiply();
                break;
            case Code::op_divide:
                pState->exec_divide();
                break;
            case Code::op_modulo:
                pState->exec_2OpNumber();
                break;
            case Code::op_lshift:
                pState->exec_2OpSInt();
                break;
            case Code::op_rshift:
                pState->exec_2OpSInt();
                break;
            case Code::op_urshift:
                pState->exec_2OpUInt();
                break;
            case Code::op_bitand:
                pState->exec_2OpSInt();
                break;
            case Code::op_bitor:
                pState->exec_2OpSInt();
                break;
            case Code::op_bitxor:
                pState->exec_2OpSInt();
                break;
            case Code::op_equals:
            case Code::op_strictequals:
            case Code::op_lessthan:
            case Code::op_lessequals:
            case Code::op_greaterthan:
            case Code::op_greaterequals:
            case Code::op_istypelate:
                pState->PopOp(); // value2
                pState->ConvertOpTo(GetBooleanType());
                break;
            case Code::op_instanceof:
                pState->exec_2OpBoolean();
                break;
            case Code::op_istype:
                pState->exec_istype(ReadU30(pCode, bcp));
                break;
            case Code::op_in:
                pState->exec_2OpBoolean();
                break;
            case Code::op_increment_i:
                pState->exec_increment_i();
                break;
            case Code::op_decrement_i:
                pState->exec_decrement_i();
                break;
            case Code::op_negate_i:
                pState->exec_negate_i();
                break;
            case Code::op_add_i:
                pState->exec_add_i();
                break;
            case Code::op_subtract_i:
                pState->exec_subtract_i();
                break;
            case Code::op_multiply_i:
                pState->exec_multiply_i();
                break;
            case Code::op_inclocal_i:
                pState->exec_inclocal_i(ReadU30(pCode, bcp));
                break;
            case Code::op_declocal_i:
                pState->exec_declocal_i(ReadU30(pCode, bcp));
                break;
            case Code::op_getlocal:
                pState->exec_getlocal(ReadU30(pCode, bcp));
                break;
            case Code::op_getlocal0:
                pState->exec_getlocal0();
                break;
            case Code::op_getlocal1:
                pState->exec_getlocal1();
                break;
            case Code::op_getlocal2:
                pState->exec_getlocal2();
                break;
            case Code::op_getlocal3:
                pState->exec_getlocal3();
                break;
            case Code::op_setlocal0:
                pState->exec_setlocal0();
                break;
            case Code::op_setlocal1:
                pState->exec_setlocal1();
                break;
            case Code::op_setlocal2:
                pState->exec_setlocal2();
                break;
            case Code::op_setlocal3:
                pState->exec_setlocal3();
                break;
            case Code::op_debug:
                PushNewOpCodeArg(Read8(pCode, bcp));
                PushNewOpCodeArg(ReadU30(pCode, bcp));
                PushNewOpCodeArg(Read8(pCode, bcp));
                PushNewOpCodeArg(ReadU30(pCode, bcp));
                break;
            case Code::op_debugline:
            case Code::op_debugfile:
                PushNewOpCodeArg(ReadU30(pCode, bcp));
                break;
            case Code::op_0xF2:
                ReadU30(pCode, bcp);
                // ???
                break;
            default:
                // This part should be gone eventually.
                switch (Code::GetOpCodeInfo(opcode).operandCount)
                {
                case 1:
                    PushNewOpCodeArg(ReadU30(pCode, bcp));
                    break;
                case 2:
                    PushNewOpCodeArg(ReadU30(pCode, bcp));
                    PushNewOpCodeArg(ReadU30(pCode, bcp));
                    break;
                case 0:
                    break;
                default:
                    GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG(Code::GetOpCodeInfo(opcode).name)));
                    break;
                }
            }
        }

        // Exception related.
        /* Let's skip it for the time being.
        if (oi.canThrow && insideOfTry)
        {
            AddBlock(bcp);

            // pState can be invalidated in AddBlock().
            pState = &GetState(*pBlock);
        }
        */

        if (GetVM().IsException())
            return;
    }
}

TR::Block* Tracer::GetBlock(Abc::TCodeOffset offset)
{
    TR::Block* block = Blocks.GetLast();

    // Skip blocks with bigger offset.
    while (block != NULL && offset < block->GetFrom())
    {
        block = Blocks.GetPrev(block);
    }

    return block;
}

void Tracer::StoreOffset(Abc::TCodeOffset bcp, const TR::State& st, SInt32 offset, int base)
{
    using namespace Abc;

    if (offset < 0)
    {
        /* DO NOT delete this pCode.
        // This check proves that each back reference is marked with the Code::op_label.
        {
            TCodeOffset ccp = cp;
            const Code::OpCode offset_opcode = static_cast<Code::OpCode>(Read8(pCode + offset, ccp));
            SF_UNUSED(offset_opcode);
            SF_ASSERT(offset_opcode == Code::op_label);
        }
        */

        // We already know a new address. We just need to get it and store it.
        TCodeOffset new_offset = Orig2newPosMap[bcp + offset] - WCode.GetSize() + base;
        //SF_ASSERT((WCode.GetSize() + new_offset) >= 0);
        PushNewOpCodeArg(static_cast<Abc::TOpCode::ValueType>(new_offset));
    } else
    {
        AddBlock(st, bcp + offset);

        // A new address is not known at this time because it is in front of current pCode pointer.
        // Translate offset to an absolute address and store it instead of a relative address.
        PushNewOpCodeArg(static_cast<Abc::TOpCode::ValueType>(bcp + offset));
        // Store a position in WCode where we stored this absolute address, which we will need 
        // to recalculate later.
        PosToRecalculate.PushBack(Recalculate(WCode.GetSize() - 1, base));
    }
}

Abc::Code::OpCode Tracer::GetNewTopOpCode(UPInt num) const
{
    using namespace Abc;

    if (NewOpcodePos.GetSize() > num)
    {
        TCodeOffset ccp = NewOpcodePos[NewOpcodePos.GetSize() - 1 - num];
        const Code::OpCode prev_opcode = static_cast<Code::OpCode>(WCode[ccp]);

        return prev_opcode;
    }

    return Code::op_nop;
}

void Tracer::SkipOrigOpCode(Abc::TCodeOffset& opcode_cp, Abc::TCodeOffset new_cp)
{
    // Store pos in case it is referenced.
    OrigOpcodePos.PushBack(opcode_cp);
    Orig2newPosMap[opcode_cp] = WCode.GetSize();

    // This assert triggers in several tests.
    //SF_ASSERT(Orig2newPosMap[opcode_cp] < 100000);

    // Change CP.
    opcode_cp = new_cp;
}

void Tracer::RegisterOrigOpCode(Abc::TCodeOffset opcode_cp)
{
    CurrOffset = opcode_cp;

    OrigOpcodePos.PushBack(opcode_cp);
    Orig2newPosMap[opcode_cp] = WCode.GetSize();

    // This assert triggers in several tests.
    //SF_ASSERT(Orig2newPosMap[opcode_cp] < 100000);
}

Abc::Code::OpCode Tracer::GetOrigPrevOpCode(UPInt opcode_num_diff) const
{
    using namespace Abc;

    if (OrigOpcodePos.GetSize() > opcode_num_diff)
    {
        TCodeOffset ccp = OrigOpcodePos[OrigOpcodePos.GetSize() - opcode_num_diff - 1];
        const Code::OpCode prev_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));

        return prev_opcode;
    }

    return Code::op_nop;
}

Abc::Code::OpCode Tracer::GetOrigPrevOpCode2(Abc::TCodeOffset offset) const
{
    using namespace Abc;

    UPInt i = Alg::LowerBound(OrigOpcodePos, offset);
    TCodeOffset ccp = OrigOpcodePos[i - 1];
    const Code::OpCode prev_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));

    return prev_opcode;
}

Abc::Code::OpCode Tracer::GetOrigValueConsumer(Abc::TCodeOffset bcp) const
{
    using namespace Abc;

    Code::OpCode opcode = Code::op_nop;
    int st_size = 1;

    while (true)
    {
        opcode = static_cast<Code::OpCode>(Read8(pCode, bcp));

        if (opcode == Code::op_jump)
        {
            int offset = ReadS24(pCode, bcp);
            bcp += offset;
            continue;
        }

        // Adjust stack size.
        {
            const Code::OpCodeInfo& oi = Code::GetOpCodeInfo(opcode);

            st_size -= oi.pop;

            if (oi.pop_mn)
            {
                const int mn_index = ReadU30(pCode, bcp);
                const Abc::Multiname& mn = GetAbcFile().GetConstPool().GetMultiname(mn_index);

                switch (mn.GetKind())
                {
                case Abc::MN_QName:
                case Abc::MN_QNameA:
                    // QName is not read from stack; both name and namespase known at compile-time.
                    break;
                case Abc::MN_RTQName:
                case Abc::MN_RTQNameA:
                    // Name is known at compile time, Namespace is resolved at runtime.
                    --st_size;
                    break;
                case Abc::MN_RTQNameL:
                case Abc::MN_RTQNameLA:
                    // Both name and namespace are resolved at runtime.
                    st_size -= 2;
                    break;
                case Abc::MN_Multiname:
                case Abc::MN_MultinameA:
                    // MInfo is not supposed to be read from stack.
                    break;
                case Abc::MN_MultinameL:
                case Abc::MN_MultinameLA:
                    // Namespace set is known at compile time, Name is resolved at runtime.        
                    --st_size;
                    break;
                case Abc::MN_Typename:
                    // Recursive!!!?
                    SF_ASSERT(false);
                    break;
                default:
                    SF_ASSERT(false);
                    break;
                }
            }

            if (oi.pop_args)
            {
                const int arg_count = ReadU30(pCode, bcp);

                if (opcode == Code::op_newobject)
                    st_size -= arg_count * 2;
                else
                    st_size -= arg_count;
            }

            if (st_size > 0)
                st_size += Code::GetOpCodeInfo(opcode).push;
            else
                break;

            if (oi.pop_args | oi.pop_mn)
                // We have already read all operands.
                continue;
        }

        // Read operands.
        switch (opcode)
        {
        case Code::op_ifnlt:
        case Code::op_ifnle:
        case Code::op_ifngt:
        case Code::op_ifnge:
        case Code::op_ifeq:
        case Code::op_ifge:
        case Code::op_ifgt:
        case Code::op_ifle:
        case Code::op_iflt:
        case Code::op_ifne:
        case Code::op_ifstricteq:
        case Code::op_ifstrictne:
        case Code::op_iftrue:
        case Code::op_iffalse:
        case Code::op_jump:
            ReadS24(pCode, bcp);
            break;
        case Code::op_lookupswitch:
            {
                ReadS24(pCode, bcp);
                int case_count = ReadU30(pCode, bcp);

                for(int i = 0; i <= case_count; ++i)
                    ReadS24(pCode, bcp);

            }
            break;
        case Code::op_pushbyte:
            Read8(pCode, bcp);
            break;
        case Code::op_debug:
            Read8(pCode, bcp);
            ReadU30(pCode, bcp);
            Read8(pCode, bcp);
            ReadU30(pCode, bcp);
            break;
        default:
            switch (Code::GetOpCodeInfo(opcode).operandCount)
            {
            case 2:
                ReadU30(pCode, bcp);
                // No break on purpose.
            case 1:
                ReadU30(pCode, bcp);
                break;
            default:
                break;
            }
        }
    }

    return opcode;
}

void Tracer::ThrowMergeTypeError(const Traits& to_tr, const Traits& from_tr) const
{
    SF_UNUSED2(to_tr, from_tr);

    VM& vm = GetVM();
    vm.ThrowVerifyError(VM::Error(VM::eCannotMergeTypesError, vm
        SF_DEBUG_ARG(to_tr.GetName())
        SF_DEBUG_ARG(from_tr.GetName())
        ));
}

CheckResult Tracer::MergeValues(UPInt ind, TR::State& to, const TR::State& from, TR::MergeSet ms) const
{
    ValueArrayDH& to_va = to.GetValueArray(ms);
    const ValueArrayDH& from_va = from.GetValueArray(ms);

    Value& to_v = to_va[ind];
    const Value& from_v = from_va[ind];

    const Traits* to_tr = GetValueTraits(to_v);
    const Traits* from_tr = GetValueTraits(from_v);

    bool result = false;

    if (ms == TR::msScopeStack)
	{
		if (to_v.GetWith() != from_v.GetWith())
            goto error;
	}

	// Same types.
	if (to_tr == from_tr)
        goto success;

    if (ms == TR::msRegisterFile)
    {
        const unsigned i = static_cast<unsigned>(ind);
        if (!from.RegistersAlive.IsSet(i))
            // "from" register is not set.
            // It doesn't contain any meaningful value.
            goto success;

        if (!to.RegistersAlive.IsSet(i))
        {
            // We do not need to merge types if "to" is not alive.
            to_v = from_v;
            goto success;
        }
    }

    // Undefined.
	if (to_v.IsUndefined())
	{
		to_v = from_v;
        goto success;
	}

    // Any type
    if (IsAnyType(to_tr))
        goto success;

    if (IsAnyType(from_tr))
    {
        // Make "to" of "any" type.
        to_v = Value(GetObjectType());
        goto success;
    }

    // Numeric types.
#ifdef SF_AS3_TR_UINT_AS_SINT
    if (IsNumericType(to_tr) && IsNumericType(from_tr))
    {
        // If one of the types is Number then result is Number.
        if (IsNumberType(to_tr) || IsNumberType(from_tr))
            to_v = Value(GetNumberType());

        goto success;
    }
#else
    if (IsNumericType(to_tr) && IsNumericType(from_tr))
    {
        // Promote type to Number because types are not equal and SInt is
        // not the same as UInt.
        to_v = Value(GetNumberType());
        goto success;
    }
#endif

    // Null.
    if (to_v.IsNull() || IsNullType(to_tr))
    {
        if (from_v.IsNull() || IsNullType(from_tr))
            goto success;
        else if (IsStringType(from_tr) || !IsNumericType(from_tr))
        {
            // We can store Null in Strings and non-numeric types.
            to_v = from_v;
            goto success;
        }
        else
            goto error;
    }

    if (from_v.IsNull() || IsNullType(from_tr))
    {
        if (IsStringType(to_tr) || !IsNumericType(to_tr))
            // We can store Null in Strings and non-numeric types.
            // "to" already has a right type.
            goto success;
        else
            goto error;
    }

    // Try to find a common base.
    {
        // Set tmp bit.
        const Traits* tr = to_tr;
        while (tr)
        {
            tr->SetTmpBit();
            tr = tr->GetParent();
        }

        // Check tmp bit.
        tr = from_tr;
        while (tr)
        {
            if (tr->IsTmpBit())
            {
                // We found a common base.
                break;
            }

            tr = tr->GetParent();
        }

        if (tr)
        {
            result = true;

            // "tr" can be either ClassTraits or InstanceTraits.
            Traits* tr1 = const_cast<Traits*>(tr);
            if (tr->IsClassTraits())
                to_v = Value(*static_cast<ClassTraits::Traits*>(tr1));
            else
                to_v = Value(*static_cast<InstanceTraits::Traits*>(tr1));
        }

        // Clear tmp bit. It should always be false.
        tr = to_tr;
        while (tr)
        {
            tr->SetTmpBit(false);
            tr = tr->GetParent();
        }
    }

    // For debugging.
    if (result)
        goto success;
    else
        goto error;

    success:
        if (ms == TR::msRegisterFile)
        {
            // Mark register as alive if at least one of them is alive.
            const unsigned i = static_cast<unsigned>(ind);
            const bool isAlive = from.RegistersAlive.IsSet(i) || to.RegistersAlive.IsSet(i);
            to.RegistersAlive.Set(i, isAlive);
        }
        return true;

    error:
        ThrowMergeTypeError(*to_tr, *from_tr);
        return false;
}

CheckResult Tracer::MergeLists(TR::State& to, const TR::State& from, bool check_size, TR::MergeSet ms) const
{
    // Skip merging if lists, which are of different size.
    // Is this a correct approach?
    // There are three tests, which will break if we remove this check.
    // 1) as3/Definitions\Classes\ClassDef\Bug118272Package.abc
    // 2) as3/Statements\Exceptions\TryCatchBlockUserWithBuiltInExceptions.abc
    // 3) ecma3/Statements\etry_006.abc

    ValueArrayDH& to_va = to.GetValueArray(ms);
    const ValueArrayDH& from_va = from.GetValueArray(ms);

    if (check_size && to_va.GetSize() != from_va.GetSize())
        return false;

    for (UPInt i = 0; i < from_va.GetSize(); ++i)
    {
        if (i >= to_va.GetSize())
            to_va.PushBack(from_va[i]);
        else if (!MergeValues(i, to, from, ms))
            return false;
    }

    return true;
}

void Tracer::InitializeBlock(TR::Block& to, const TR::Block& from)
{
    SF_ASSERT(!to.IsInitializedBlock());

    const TR::State& from_st = GetState(from);
    TR::State& to_st = GetState(to);

    MergeLists(to_st, from_st, false, TR::msOpStack).DoNotCheck();
    MergeLists(to_st, from_st, false, TR::msScopeStack).DoNotCheck();
    MergeLists(to_st, from_st, true,  TR::msRegisterFile).DoNotCheck();

    to.SetInitialized();
}

CheckResult Tracer::MergeBlock(TR::Block& to, const TR::Block& from)
{
    SF_ASSERT(to.IsInitializedBlock());

    const TR::State& from_st = GetState(from);
    TR::State& to_st = GetState(to);

    if (!to.IsCatchBlock())
    {
        if (!MergeLists(to_st, from_st, true, TR::msOpStack))
        {
#if 0
            // Too much trouble so far.
            VM& vm = GetVM();
            vm.ThrowVerifyError(VM::Error(VM::eStackDepthUnbalancedError, vm
                SF_DEBUG_ARG(to_st.GetOpStack().GetSize())
                SF_DEBUG_ARG(from_st.GetOpStack().GetSize())
                ));

            return false;
#endif
        }

        if (!MergeLists(to_st, from_st, true, TR::msScopeStack))
        {
#if 0
            // Enabling this exception breaks five tests. Otherwise it seems to be fine.
            // This seems to work fine.
            VM& vm = GetVM();
            vm.ThrowVerifyError(VM::Error(VM::eScopeDepthUnbalancedError, vm
                SF_DEBUG_ARG(to_st.GetScopeStack().GetSize())
                SF_DEBUG_ARG(from_st.GetScopeStack().GetSize())
                ));

            return false;
#endif
        }
    }

    return MergeLists(to_st, from_st, true, TR::msRegisterFile);
}

int Tracer::GetNextU30(UPInt opcode_offset) const
{
    using namespace Abc;

    TCodeOffset ccp = OrigOpcodePos[OrigOpcodePos.GetSize() - opcode_offset - 1];

    return ReadU30(pCode, ++ccp);
}

bool Tracer::SubstituteOpCode(Abc::TCodeOffset& bcp, TR::State& st, UInt8 byte_code)
{
    using namespace Abc;

    const Code::OpCode opcode = static_cast<Code::OpCode>(byte_code);

#ifdef GFX_AS3_TRACE
    FlashUI& ui = GetUI();;
#endif

    // Try to substitute with a strictly typed opcode ...

    // Opcodes op_coerce_a, op_label, and op_kill are always skipped and 
    // will not be presented in a running VM.
    // op_label is handled in TraceBlock() because it creates new block.

    switch(opcode)
    {
    case Code::op_kill:
        {
            const int index = ReadU30(pCode, bcp);

            st.SetRegister(AbsoluteIndex(index), Value::GetUndefined());
            // Kill the register.
            st.RegistersAlive.Clear(index);
        }

        // Skip this opcode.
        SkipOrigOpCode(bcp, bcp);
        return true;
    case Code::op_coerce_a:
        {
            Value& v = st.BackOpValue();

#if 1
            // Let's be not very conservative and convert integer into Number.
            if (IsSIntType(v) || IsUIntType(v))
            {
                PushNewOpCode(Code::op_convert_d);

                // Try to preserve real value on stack.
                if (v.IsInt())
                    // We do not expect any errors here.
                    v.ToNumberValue().DoNotCheck();
                else
                    st.ConvertOpTo(GetNumberType());
            }
            else
                // Just skip this opcode.
                SkipOrigOpCode(bcp, bcp);
#else
            // This simple logic doesn't work at this time.
            // Just skip this opcode.
            SkipOrigOpCode(bcp, bcp);
#endif
        }
        return true;
    case Code::op_coerce_s:
        {
            const Value& v = st.BackOpValue();

            // Can be null.
            if (v.IsNull() || IsStringType(v))
            {
                st.ConvertOpTo(GetStringType(), true);

                // Skip this opcode.
                SkipOrigOpCode(bcp, bcp);
                return true;
            }
        }
        break;
    case Code::op_coerce:
        {
            TCodeOffset ccp = bcp;
            const int mn_index = ReadU30(pCode, ccp);
            const Abc::Multiname& mn = GetFile().GetConstPool().GetMultiname(mn_index);
            // ATTN: We do not remove value from the stack.
            const Value& value = st.BackOpValue();

            const ClassTraits::Traits* ctr = GetVM().Resolve2ClassTraits(GetFile(), mn);
            if (ctr == NULL)
            {
                GetVM().ThrowVerifyError(VM::Error(VM::eClassNotFoundError, GetVM()
                    SF_DEBUG_ARG(mn.GetName(GetFile().GetConstPool()).ToCStr())
                    ));

                return true;
            }

            InstanceTraits::Traits& itr = ctr->GetInstanceTraits();

            // Check for "undefined" plus ObjectType
            if (value.IsUndefined() && &itr != &GetClassType() && !IsNotObjectType(&itr))
            {
                // If previous opcode was op_pushundefined we can replace it with op_pushnull.
                if (GetNewTopOpCode() == Code::op_pushundefined)
                {
                    SetNewOpCode(Code::op_pushnull);

                    // Do not push "null". Preserve type.
                    st.ConvertOpTo(itr, true);

                    // Skip prev combination ...
                    SkipOrigOpCode(bcp, ccp);

                    return true;
                }
            }

            // Null value can be of any Object type.
            if (value.IsNull() || ValueIsOfType(value, *ctr))
            {
                // We can eliminate this "coerce".

                // TBD: It, probably, should be st.ConvertOpTo(*GetValueTraits(value));
                // It will be a more precise type.
                // Value wasn't popped from stack.
                st.ConvertOpTo(itr, true);

                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                return true;
            }

            // Skip prev combination ...
            SkipOrigOpCode(bcp, ccp);

            PushNewOpCode(Code::op_coerce, mn_index);
            st.ConvertOpTo(itr);
        }
        return true;
    case Code::op_getglobalscope:
        {
            TCodeOffset ccp = bcp;
#ifdef GFX_AS3_TRACE
            TCodeOffset next_offset = ccp;
#endif
            const Code::OpCode next_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));
            int drop_num = 0;

            if (next_opcode == Code::op_getslot)
            {
                // Simulate prev opcode.
                st.exec_getglobalscope();
#ifdef GFX_AS3_TRACE
                if (ui.NeedToCheckOpCode()) { ui.OnOpCode(next_offset); }
#endif
                PushNewOpCode(Code::op_getglobalslot);
                // Simulate prev opcode.
                st.exec_getslot(ReadU30(pCode, ccp));

                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                return true;
            } else if (next_opcode == Code::op_swap)
            {
                OrigOpcodePos.PushBack(ccp);
                ++drop_num;

#ifdef GFX_AS3_TRACE
                TCodeOffset next_offset2 = ccp;
#endif
                const Code::OpCode next_opcode2 = static_cast<Code::OpCode>(Read8(pCode, ccp));

                if (next_opcode2 == Code::op_setslot)
                {
                    PushNewOpCode(Code::op_setglobalslot);

                    // Simulate a set of opcodes below.
                    st.exec_getglobalscope();
#ifdef GFX_AS3_TRACE
                    if (ui.NeedToCheckOpCode()) { ui.OnOpCode(next_offset); }
#endif
                    st.exec_swap();
#ifdef GFX_AS3_TRACE
                    if (ui.NeedToCheckOpCode()) { ui.OnOpCode(next_offset2); }
#endif
                    st.exec_setslot(ReadU30(pCode, ccp));


                    // Instead of simulating a simple one below.
                    //exec_setglobalslot(ReadU30(pCode, ccp));

                    // Skip prev combination ...
                    SkipOrigOpCode(bcp, ccp);

                    return true;
                } else
                {
                    OrigOpcodePos.PopBack(drop_num);
                }
            }
        }
        break;
    case Code::op_getlocal:
        {
            TCodeOffset ccp = bcp;
            const int reg_num = ReadU30(pCode, ccp);

            return SubstituteGetlocal(bcp, ccp, st, reg_num);
        }
        break;
    case Code::op_getlocal0:
        return SubstituteGetlocal(bcp, bcp, st, 0);
    case Code::op_getlocal1:
        return SubstituteGetlocal(bcp, bcp, st, 1);
    case Code::op_getlocal2:
        return SubstituteGetlocal(bcp, bcp, st, 2);
    case Code::op_getlocal3:
        return SubstituteGetlocal(bcp, bcp, st, 3);
    case Code::op_initproperty:
        // It looks like it is not possible to optimize out initproperty for classes because
        // compiler can generate *getslot* for this property in the same function and we do
        // not have absolute object for this class at optimization time.
    case Code::op_setproperty:
    case Code::op_setsuper:
        {
            using namespace Abc;

            TCodeOffset ccp = bcp;
            const int mn_index = ReadU30(pCode, ccp);

            TR::ReadValueMnObject args(GetFile(), st, mn_index);

            const bool super_tr = (opcode == Code::op_setsuper);
            const Traits* obj_tr = GetValueTraits(args.ArgObject, super_tr);
            const Traits* val_tr = GetValueTraits(args.ArgValue);

            // EmitSetProperty() always returns true.
            if (EmitSetProperty(opcode, obj_tr, val_tr, args.ArgMN, mn_index))
            {
                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);
                return true;
            }
        }
        break;
    case Code::op_getproperty:
    case Code::op_getsuper:
        {
            using namespace Abc;

            TCodeOffset ccp = bcp;
            const int mn_index = ReadU30(pCode, ccp);

            TR::ReadMnObject args(GetFile(), st, mn_index);

            const bool super_tr = (opcode == Code::op_getsuper);
            const Traits* tr = GetValueTraits(args.ArgObject, super_tr);

            if (EmitGetProperty(opcode, st, tr, args.ArgMN, mn_index))
            {
                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                return true;
            }
        }
        break;
    case Code::op_findpropstrict:
        {
            // Try to eliminate (findpropstrict + getproperty) or (findpropstrict + constructprop)
            TCodeOffset ccp0 = bcp;
            const int mn_index = ReadU30(pCode, ccp0);
            TCodeOffset ccp = ccp0;
            const Code::OpCode next_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));
#ifdef SF_BUILD_DEBUG
//             const UPInt origOpStackSize = st.GetOpStack().GetSize();
#endif

            const Code::OpCode consumer = GetOrigValueConsumer(ccp0);

            if (next_opcode == Code::op_getproperty)
            {
                const int get_mn_index = ReadU30(pCode, ccp);
                
#if 1
                SF_UNUSED2(mn_index, get_mn_index);
#else
                // Compiler can generate different namespace sets for op_findpropstrict and
                // op_getproperty in case of Vector.<>.
                if (mn_index == get_mn_index)
#endif
                {
                    // This is the same as getlex.
                    if (EmitFindProperty(st, mn_index, true, consumer SF_DEBUG_ARG(true)))
                    {
                        // Skip prev combination ...
                        SkipOrigOpCode(bcp, ccp);

                        // This combination should add one element to the stack.
                        //SF_ASSERT(st.GetOpStack().GetSize() == origOpStackSize + 1);

                        return true;
                    }
                }
            }
            else
            {
                //  && !IsOrigCall(consumer)
                //const bool get_prop = !IsOrigPropSetter(consumer) && !IsOrigConstruct(consumer) || IsOrigCall(consumer);
                // 
                if (EmitFindProperty(st, mn_index, false, consumer SF_DEBUG_ARG(true)))
                {
                    // Skip prev combination ...
                    SkipOrigOpCode(bcp, ccp0);

                    // This combination should add one element to the stack.
                    //SF_ASSERT(st.GetOpStack().GetSize() == origOpStackSize + 1);

                    return true;
                }
            }
        }
        // No break on purpose.
        // op_findpropstrict has same logic as op_findproperty.
    case Code::op_findproperty:
        {
            TCodeOffset ccp = bcp;
            const int mn_index = ReadU30(pCode, ccp);

            if (EmitFindProperty(st, mn_index))
            {
                // Skip prev combination.
                SkipOrigOpCode(bcp, ccp);
                return true;
            }
        }
        break;
    case Code::op_getlex:
        {
            TCodeOffset ccp = bcp;
            const int mn_index = ReadU30(pCode, ccp);
#ifdef SF_BUILD_DEBUG
            const UPInt origOpStackSize = st.GetOpStack().GetSize();
#endif

#if 0 // For debugging.
            const Abc::Multiname& mn = GetAbcFile().GetConstPool().GetMultiname(mn_index);
            AS3::Multiname as3_mn(GetFile(), mn);
            if (as3_mn.GetName().AsString() == "InputDetails")
            {
                int i = 0;
                ++i;
            }
#endif

            if (EmitFindProperty(st, mn_index, true))
            {
                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                // op_getlex should add one element to the stack.
                SF_ASSERT(st.GetOpStack().GetSize() == origOpStackSize + 1);

                return true;
            }
        }
        break;
    case Code::op_callproplex:
    case Code::op_callpropvoid:
    case Code::op_callproperty:
    case Code::op_callsuper:
    case Code::op_callsupervoid:
        {
            // Call a property.

            TCodeOffset ccp = bcp;

            UInt32 mn_index = ReadU30(pCode, ccp);
            UInt32 arg_count = ReadU30(pCode, ccp);

            // Read arguments ...
            TR::ReadArgsMnObject args(GetFile(), st, arg_count, mn_index);

            /*
            if (IsException())
                return false;
            */

            const bool super_tr = (opcode == Code::op_callsuper || opcode == Code::op_callsupervoid);
            const Traits* tr = GetValueTraits(args.ArgObject, super_tr);

            // EmitCall() always returns true.
            if (EmitCall(opcode, st, tr, args.ArgMN, mn_index, arg_count))
            {
                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);
                return true;
            }

        }
        break;
    case Code::op_constructprop:
        {
            TCodeOffset ccp = bcp;
            UInt32 mn_index = ReadU30(pCode, ccp);
            UInt32 arg_count = ReadU30(pCode, ccp);

            // Read arguments ...
            TR::ReadArgsMnObject args(GetFile(), st, arg_count, mn_index);

            if (args.ArgMN.IsRunTime())
            {
                // Restore back old opcode.
                PushNewOpCode(Code::op_constructprop, mn_index, arg_count);
                st.PushOp(GetObjectType());
            }
            else
            {
                switch (args.ArgObject.GetKind())
                {
                case Value::kClassTraits:
                    // Emit *construct*.
                    PushNewOpCode(Code::op_construct, arg_count);
                    st.PushOp(Value(args.ArgObject.GetClassTraits().GetInstanceTraits()));
                    break;
                case Value::kClass:
                    // Emit *construct*.
                    PushNewOpCode(Code::op_construct, arg_count);
                    st.PushOp(Value(args.ArgObject.AsClass().GetClassTraits().GetInstanceTraits()));
                    break;
                default:
                    // Function object
                    PushNewOpCode(Code::op_constructprop, mn_index, arg_count);
                    st.PushOp(GetObjectType());
                    break;
                }
            }

            // Skip prev combination ...
            SkipOrigOpCode(bcp, ccp);

            return true;
        }
        break;
    case Code::op_astypelate:
        {
            // Top of the stack is a class. Below it is a value.
            const Value class_ = st.PopOpValue(); // class
            const ClassTraits::Traits* ctr = NULL;
            const Value::KindType kind = class_.GetKind();

            switch (kind)
            {
            case Value::kClassTraits:
                ctr = &class_.GetClassTraits();
                break;
            case Value::kClass:
                ctr = &class_.AsClass().GetClassTraits();
                break;
            default:
                break;
            }

            if (ctr)
            {
                const Value& value = st.BackOpValue(); // value

                if (value.IsNull() || ValueIsOfType(value, *ctr))
                {
                    // We can get rid of this "astypelate".

                    // Get rid of an argument.
                    EmitPopPrevResult();

                    SkipOrigOpCode(bcp, bcp);

                    // There is no reason to convert to a type unless value is null. 
                    // We already have a right type.
                    if (value.IsNull())
                        st.ConvertOpTo(ctr->GetInstanceTraits());

                    return true;
                }
            }

            // Restore class back.
            st.PushOp(class_);
        }
        break;
    case Code::op_convert_i:
        {
            const Value& value = st.BackOpValue(); // value

            if (IsSIntType(value))
            {
                SkipOrigOpCode(bcp, bcp);

                return true;
            }
        }
        break;
    case Code::op_convert_u:
        {
            const Value& value = st.BackOpValue(); // value

            if (IsUIntType(value))
            {
                SkipOrigOpCode(bcp, bcp);

                return true;
            }
        }
        break;
    case Code::op_convert_d:
        {
            const Value& value = st.BackOpValue(); // value

            if (IsNumberType(value))
            {
                SkipOrigOpCode(bcp, bcp);

                return true;
            }
        }
        break;
    case Code::op_convert_b:
        {
            const Value& value = st.BackOpValue(); // value

            if (IsBooleanType(value))
            {
                SkipOrigOpCode(bcp, bcp);

                return true;
            }
        }
        break;
    case Code::op_convert_s:
        {
            const Value& value = st.BackOpValue(); // value

            if (value.IsNull() || IsStringType(value))
            {
                st.ConvertOpTo(GetStringType());
                SkipOrigOpCode(bcp, bcp);

                return true;
            }
        }
        break;
    case Code::op_add:
        {
            const Value _2 = st.PopOpValue(); // value2
            const Value _1 = st.PopOpValue(); // value1

            const Traits* _1tr = GetValueTraits(_1);
            const Traits* _2tr = GetValueTraits(_2);

            // Strings.
            if (_1tr == &GetStringType() || _2tr == &GetStringType())
            {
                PushNewOpCode(Code::op_add);
                st.PushOp(GetStringType());
            }
            else if (IsNumberType(_1) && IsNumberType(_2))
            {
                // Values are already of Number type.
                PushNewOpCode(Code::op_add_td);
                st.PushOp(GetNumberType());
            }
            else if (GetNextOrigOpCode(bcp) == Code::op_convert_d)
            {
                // Result is Number any way.
                PushNewOpCode(Code::op_add_d);

                // Skip next opcode.
                // Size op_convert_d/op_coerce_d is one.
                SkipOrigOpCode(bcp, bcp + 1);

                st.PushOp(GetNumberType());
            }
#if 0
            else if (GetNextOrigOpCode(bcp) == Code::op_convert_i && IsSIntType(_1) && IsSIntType(_2))
            {
                // This is addition of integers.
                PushNewOpCode(Code::op_add_ti);

                // Skip next opcode.
                // Size of Code::op_convert_i is one.
                SkipOrigOpCode(bcp, bcp + 1);

                st.PushOp(GetSIntType());
            }
#else
            // Theoretically, this can lead to problems because "add" is supposed to return Number.
            else if (IsSIntType(_1) && IsSIntType(_2))
            {
                // This is addition of integers.
                PushNewOpCode(Code::op_add_ti);

                st.PushOp(GetSIntType());
            }
#endif
            else
            {
                PushNewOpCode(Code::op_add);

                // Operands are primitives but strings.
                if (IsPrimitiveType(_1tr) && IsPrimitiveType(_2tr))
                    st.PushOp(GetNumberType());
                else
                    // Result should be either String or Number, so, let us make it of Object type.
                    st.PushOp(GetObjectType());
            }

            return true;
        }
        break;
    default:
        break;
    }

    return false;
}

bool Tracer::SubstituteGetlocal(Abc::TCodeOffset& bcp, Abc::TCodeOffset ccp, TR::State& st, int src_reg_num)
{
    using namespace Abc;

    const Value& reg = st.GetRegister(AbsoluteIndex(src_reg_num));

#ifdef GFX_AS3_TRACE
    TCodeOffset next_offset = ccp;
#endif
    const Code::OpCode next_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));
    bool check_setlocal = false;
    int drop_num = 0;

    switch(next_opcode)
    {
    case Code::op_increment:
    case Code::op_decrement:
    case Code::op_increment_i:
    case Code::op_decrement_i:
        check_setlocal = true;
        break;
    default:
        break;
    }

    if (check_setlocal)
    {
#ifdef GFX_AS3_TRACE
        FlashUI& ui = GetUI();;
        if (ui.NeedToCheckOpCode()) { ui.OnOpCode(next_offset); }
#endif

        OrigOpcodePos.PushBack(ccp);
        ++drop_num;

#ifdef GFX_AS3_TRACE
        TCodeOffset current_offset = ccp;
#endif
        Code::OpCode current_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));
        // We want to reuse enum values from BuiltinTraitsType here.
        BuiltinTraitsType result_dt = Traits_Unknown;

        switch (current_opcode)
        {
        case Code::op_convert_i:
            result_dt = Traits_SInt;
            break;
        case Code::op_convert_u:
            result_dt = Traits_UInt;
            break;
        case Code::op_convert_d:
            result_dt = Traits_Number;
            break;
        default:
            break;
        }

        if (result_dt == Traits_Unknown)
        {
            // No conversion operator was found.
            // Get type info from the opcode itself.
            switch (next_opcode)
            {
            case Code::op_increment_i:
            case Code::op_decrement_i:
                result_dt = Traits_SInt;
                break;
            default:
                result_dt = Traits_Number;
                break;
            }
        }
        else
        {
            OrigOpcodePos.PushBack(ccp);
            ++drop_num;
#ifdef GFX_AS3_TRACE
            if (ui.NeedToCheckOpCode()) { ui.OnOpCode(CurrOffset); }
            current_offset = ccp;
#endif
            current_opcode = static_cast<Code::OpCode>(Read8(pCode, ccp));
        }

        int dest_reg_num = 0;
        bool is_setlocal = true;

        switch (current_opcode)
        {
        case Code::op_setlocal:
            dest_reg_num = ReadU30(pCode, ccp);
            break;
        case Code::op_setlocal0:
            dest_reg_num = 0;
            break;
        case Code::op_setlocal1:
            dest_reg_num = 1;
            break;
        case Code::op_setlocal2:
            dest_reg_num = 2;
            break;
        case Code::op_setlocal3:
            dest_reg_num = 3;
            break;
        default:
            is_setlocal = false;
            break;
        }

        if (is_setlocal && dest_reg_num == src_reg_num)
        {
            // We want to reuse enum values from BuiltinTraitsType here.
            BuiltinTraitsType reg_dt = Traits_Number;
            const Traits* reg_tr = GetValueTraits(reg);

            if (reg_tr && reg_tr->IsInstanceTraits())
                reg_dt = reg_tr->GetTraitsType();

            switch(next_opcode)
            {
            case Code::op_increment:
            case Code::op_increment_i:
#ifdef GFX_AS3_TRACE
                if (ui.NeedToCheckOpCode()) { ui.OnOpCode(CurrOffset); }
#endif

                if (reg_dt == result_dt)
                {
                    switch (reg_dt)
                    {
                    case Traits_SInt:
                        PushNewOpCode(Code::op_inclocal_ti, src_reg_num);
                        st.exec_convert_reg_i(src_reg_num);
                        break;
                    case Traits_UInt:
                        PushNewOpCode(Code::op_inclocal_tu, src_reg_num);
                        st.exec_convert_reg_u(src_reg_num);
                        break;
                    case Traits_Number:
                        PushNewOpCode(Code::op_inclocal, src_reg_num);
                        st.exec_convert_reg_d(src_reg_num);
                        break;
                    default:
                        break;
                    }
                }
                else if (result_dt == Traits_SInt)
                {
                    PushNewOpCode(Code::op_inclocal_i, src_reg_num);
                    st.exec_convert_reg_i(src_reg_num);
                }
                else
                {
                    PushNewOpCode(Code::op_inclocal, src_reg_num);
                    st.exec_convert_reg_d(src_reg_num);
                }

                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                return true;
            case Code::op_decrement:
            case Code::op_decrement_i:
#ifdef GFX_AS3_TRACE
                if (ui.NeedToCheckOpCode()) { ui.OnOpCode(CurrOffset); }
#endif

                if (reg_dt == result_dt)
                {
                    switch (reg_dt)
                    {
                    case Traits_SInt:
                        PushNewOpCode(Code::op_declocal_ti, src_reg_num);
                        st.exec_convert_reg_i(src_reg_num);
                        break;
                    case Traits_UInt:
                        PushNewOpCode(Code::op_declocal_tu, src_reg_num);
                        st.exec_convert_reg_u(src_reg_num);
                        break;
                    case Traits_Number:
                        PushNewOpCode(Code::op_declocal, src_reg_num);
                        st.exec_convert_reg_d(src_reg_num);
                        break;
                    default:
                        break;
                    }
                }
                else if (result_dt == Traits_SInt)
                {
                    PushNewOpCode(Code::op_declocal_i, src_reg_num);
                    st.exec_convert_reg_i(src_reg_num);
                }
                else
                {
                    PushNewOpCode(Code::op_declocal, src_reg_num);
                    st.exec_convert_reg_d(src_reg_num);
                }

                // Skip prev combination ...
                SkipOrigOpCode(bcp, ccp);

                return true;
            default:
                break;
            }
        } else
        {
            OrigOpcodePos.PopBack(drop_num);
        }
    }

    return false;
}

void Tracer::EmitPopPrevResult()
{
    using namespace Abc;

    // Get rid of previous result in two different ways.
    // 1) If result was retrieved via "getabsobject" command,
    //    then get rid of this command.
    // 2) If it is something else, then just do "pop" instead.
    const Code::OpCode prev_opcode = GetNewTopOpCode();

    switch (prev_opcode)
    {
    /*
    // DO NOT delete.
    // Opcodes below retrieve result, but they also read arguments from stack.
    case Code::op_getsuper:
    case Code::op_getproperty:
    case Code::op_getslot:
    case Code::op_getabsslot:
    */

    // Opcodes below do not read arguments from stack.
    // So, it is safe to get rid of them.
    case Code::op_pushnull:
    case Code::op_pushundefined:
    case Code::op_pushbyte:
    case Code::op_pushshort:
    case Code::op_pushtrue:
    case Code::op_pushfalse:
    case Code::op_pushnan:
    case Code::op_dup:
    case Code::op_pushstring:
    case Code::op_pushint:
    case Code::op_pushuint:
    case Code::op_pushdouble:
    case Code::op_pushnamespace:
    case Code::op_getlex:
    case Code::op_getlocal:
    case Code::op_getglobalscope:
    case Code::op_getscopeobject:
    case Code::op_getouterscope:
    case Code::op_getglobalslot:
    case Code::op_getabsobject:
    case Code::op_getlocal0:
    case Code::op_getlocal1:
    case Code::op_getlocal2:
    case Code::op_getlocal3:
        PopNewOpCode();
        break;
    default:
        PushNewOpCode(Code::op_pop);
        break;
    }
}

bool Tracer::EmitGetClassTraits(TR::State& st, AS3::Multiname as3_mn, bool objOnStack)
{
    using namespace Abc;

#if 0
    // This should be checked outside of this method.
    if (as3_mn.IsRunTime())
        return false;
#endif

    VM& vm = GetVM();

    // FindClassTraits() can handle Multiname (multiple namespaces).
    const ClassTraits::Traits* ctr = FindClassTraits(vm, as3_mn);
    if (ctr == NULL)
        return false;

    if (ctr->IsValid())
    {
        // This is just a class.

        InstanceTraits::Traits& itr = ctr->GetInstanceTraits();
        if (itr.HasConstructorSetup())
        {
            // Class already created.
            // Emit getabsobject.

            Value value(&ctr->GetInstanceTraits().GetClass());
            if (EmitGetAbsObject(value, objOnStack))
            {
                st.PushOp(value);

                return true;
            }
        }
        else if (itr.IsAbcObject())
        {
            // Class will be created later. Just get a slot.
            InstanceTraits::UserDefined& ud = static_cast<InstanceTraits::UserDefined&>(itr);
            AS3::Object& obj = ud.GetScript();

            UPInt slot_index = 0;
            const SlotInfo* si = AS3::FindFixedSlot(GetVM(), obj.GetTraits(), as3_mn, slot_index, &obj);

            if (si)
            {
                st.PushOp(const_cast<ClassTraits::Traits&>(*ctr));

                EmitGetAbsObject(Value(&obj));
                EmitGetAbsSlot(slot_index);

                return true;
            }
            else
                SF_ASSERT(false);
        }
        else
            SF_ASSERT(false);
    }
    else
        SF_ASSERT(false);

    return false;
}

bool Tracer::EmitFindProperty(TR::State& st, const int mn_index, bool get_prop, const Abc::Code::OpCode consumer SF_DEBUG_ARG(bool show_getprop))
{
    using namespace Abc;
    using namespace TR;

    SF_DEBUG_CODE(show_getprop = show_getprop;)
    SF_UNUSED1(consumer);

    const Abc::Multiname& mn = GetAbcFile().GetConstPool().GetMultiname(mn_index);
    AS3::Multiname as3_mn(GetFile(), mn);
    UPInt scope_ind = 0;
    State::ScopeType stype;
#ifdef GFX_AS3_TRACE
    FlashUI& ui = GetUI();;
#endif

    // Theoretically, we can get us into trouble if somebody decides to declare a property
    // having same name as a Class and will use object having this property with the "with"
    // statement.
    if (as3_mn.IsRunTime() || as3_mn.IsNameLate())
        return false;

#if 0
    // DO NOT delete this code, so, I do not make this mistake again.
    // We may not do that because property can have the same name as class.
    // Handle Classes.
    if (!IsOrigPropSetter(consumer) && EmitGetClassTraits(st, as3_mn))
        return true;
#endif

    PropRef prop;
    st.FindProp(prop, as3_mn, stype, scope_ind);

    if (prop)
    {
        if (prop.IsAsValue())
            // It is a dynamic property. Skip binding.
            // Fixed properties have SlotInfo.
            return false;

        SF_ASSERT(prop.GetAsSlotInfo());
        const UPInt slot_ind = prop.GetSlotIndex();
        const SlotInfo* si = prop.GetAsSlotInfo();
        const Traits* tr = GetValueTraits(prop.GetThis());
        SF_ASSERT(tr);

        switch (stype)
        {
        case State::stScopeStack:
        case State::stStoredScope:
            // Altered behavior. Always get Class.
            if (!IsOrigPropSetter(consumer) && si->IsClass() && EmitGetClassTraits(st, as3_mn))
                return true;

            // We may not use tr->IsClassTraits() here because class itself
            // can be not created yet.

            if (EmitGetAbsObject(prop.GetThis()))
            {
                // Well, this is an absolute object.
            } else if (stype == State::stScopeStack)
            {
                // Let's replace it with op_getscopeobject.
                PushNewOpCode(Code::op_getscopeobject, scope_ind);
            } else if (!EmitGetAbsObject(prop.GetThis()))
            {
                // Activation object is always different.
                // It would be a bad idea to store address to it.
                // Regular object can be garbage collected by the time we refer to it.
                // Let's replace it with op_getouterscope.
                EmitGetOuterScope(scope_ind);
            }

            if (get_prop)
            {
                // !!! ATTN: We MAY NOT skip BT_Set here.
                if (si->IsCode())
                {
                    if (si->GetAValueInd().IsValid() && !tr->IsInterface())
                    {
                        if (si->GetBindingType() == SlotInfo::BT_Code)
                        {
                            EmitGetAbsSlot(slot_ind);

                            // Retrieve function type.
                            st.PushOp(st.GetFunctType(tr->GetVT().GetValue(si->GetAValueInd())));
                        }
                        else
                        {
                            // Emit op_callmethod.
                            PushNewOpCode(Code::op_callmethod, si->GetValueInd(), 0);

                            // Retrieve function return type. In case of SlotInfo::BT_Code we need to retrieve function type.
                            st.PushOp(Value(st.GetFunctReturnType(tr->GetVT().GetValue(si->GetAValueInd()))));
                        }

                        // We are done. Result type is on stack.
                        return true;
                    }
                }

                EmitGetAbsSlot(slot_ind);
            }

            // Push value type.
            if (get_prop)
            {
                {
                    Value type;

                    if (!st.GetPropertyType(*tr, *si, type))
                        return false;

                    st.PushOp(type);
                }

#ifdef GFX_AS3_TRACE
                if (show_getprop && ui.NeedToCheckOpCode())
                {
                    Abc::TCodeOffset ccp = CurrOffset;

                    Read8(pCode, ccp);
                    ReadU30(pCode, ccp);
                    ui.OnOpCode(ccp);
                }
#endif
            }
            else
                // Push object, which has this slot.
                st.PushOp(prop.GetThis());

            return true;
        case State::stGlobalObject:
            // Check global objects. We are looking for classes.
            // We know about all registered class objects.

            // Altered behavior. Always get Class.
            if (!IsOrigPropSetter(consumer) && si->IsClass() && EmitGetClassTraits(st, as3_mn))
                return true;

            if (get_prop)
            {
                // It looks like there is no need to handle getters in global objects.
                if (!si->IsCode())
                {
                    // It is possible that we are trying to retrieve "undefined" or "NaN".
                    const Value& _this = prop.GetThis();
                    if (_this.IsObject() && _this.GetObject() == &GetVM().GetGlobalObjectCPP())
                    {
                        // We found a property of the GlobalObjectCPP
                        const ASString name = tr->GetSlotName(AbsoluteIndex(slot_ind));

                        enum en{nothing, undef, nan};
                        en e = nothing;
                        if (name == "undefined")
                            e = undef;
                        else if (name == "NaN")
                            e = nan;

                        if (e != nothing)
                        {
                            // Emit op_pushundefined or op_pushnan.
                            PushNewOpCode(e == undef ? Code::op_pushundefined : Code::op_pushnan);
                            st.PushOp(undef ? Value::GetUndefined() : Value(NumberUtil::NaN()));

#ifdef GFX_AS3_TRACE
                            if (show_getprop && ui.NeedToCheckOpCode())
                            {
                                Abc::TCodeOffset ccp = CurrOffset;

                                Read8(pCode, ccp);
                                ReadU30(pCode, ccp);
                                ui.OnOpCode(ccp);
                            }
#endif

                            return true;
                        }
                    }

                    // Emit getabsobject.
                    if (EmitGetAbsObject(prop.GetThis()))
                    {
                        // Get type.
                        {
                            Value type;

                            if (!st.GetPropertyType(*tr, *si, type))
                                return false;

                            st.PushOp(type);
                        }

                        // Get absolute slot on a global object.
                        EmitGetAbsSlot(slot_ind);

#ifdef GFX_AS3_TRACE
                        if (show_getprop && ui.NeedToCheckOpCode())
                        {
                            Abc::TCodeOffset ccp = CurrOffset;

                            Read8(pCode, ccp);
                            ReadU30(pCode, ccp);
                            ui.OnOpCode(ccp);
                        }
#endif

                        return true;
                    }
                }
            }
            else
            {
                const Value& value = prop.GetThis();

                const bool rc = EmitGetSlot(value, slot_ind);
                if (rc)
                {
                    st.PushOp(value);
#ifdef GFX_AS3_TRACE
                    if (show_getprop && ui.NeedToCheckOpCode())
                    {
                        Abc::TCodeOffset ccp = CurrOffset;

                        Read8(pCode, ccp);
                        ReadU30(pCode, ccp);
                        ui.OnOpCode(ccp);
                    }
#endif
                }

                return rc;
            }

            break;
        }
    }
    else if (get_prop)
    {
        if (EmitGetClassTraits(st, as3_mn))
            return true;
    }

    return false;
}

void Tracer::EmitGetAbsSlot(const UPInt index)
{
    using namespace Abc;

    const GlobalSlotIndex gsind = GlobalSlotIndex(AbsoluteIndex(index));
    SF_ASSERT(gsind.IsValid());
    PushNewOpCode(Code::op_getabsslot, gsind.Get());
}

void Tracer::EmitSetAbsSlot(const SlotInfo& si, const Traits* val_tr, const UPInt index)
{
    using namespace Abc;

#ifdef ENABLE_STRICT_SETSLOT
    const UPInt offset = si.GetValueInd().Get();
    VM& vm = GetVM();

    if (!si.IsConst())
    {
        switch (si.GetBindingType())
        {
        case SlotInfo::BT_Value:
            // We do not care about type of value.
            return PushNewOpCode(Code::op_setslot_value, offset);
        case SlotInfo::BT_ObjectAS:
            if (!IsNotObjectType(val_tr))
                return PushNewOpCode(Code::op_setslot_obj_as, offset);
            break;
        case SlotInfo::BT_ObjectCpp:
            if (!IsNotObjectType(val_tr))
                return PushNewOpCode(Code::op_setslot_obj_cpp, offset);
            break;
        case SlotInfo::BT_Boolean:
            if (val_tr == &vm.GetITraitsBoolean())
                return PushNewOpCode(Code::op_setslot_bool, offset);
            break;
        case SlotInfo::BT_Int:
            if (val_tr == &vm.GetITraitsSInt())
                return PushNewOpCode(Code::op_setslot_sint, offset);
            break;
        case SlotInfo::BT_UInt:
            if (val_tr == &vm.GetITraitsUInt())
                return PushNewOpCode(Code::op_setslot_uint, offset);
            break;
        case SlotInfo::BT_Number:
            if (val_tr == &vm.GetITraitsNumber())
                return PushNewOpCode(Code::op_setslot_num, offset);
            break;
        case SlotInfo::BT_String:
            if (val_tr == &vm.GetITraitsString())
                return PushNewOpCode(Code::op_setslot_str, offset);
            break;
        default:
            break;
        }
    }
#else
    SF_UNUSED2(si, val_tr);
#endif

    const GlobalSlotIndex gsind = GlobalSlotIndex(AbsoluteIndex(index));
    SF_ASSERT(gsind.IsValid());
    PushNewOpCode(Code::op_setabsslot, gsind.Get());
}

void Tracer::EmitInitAbsSlot(const UPInt index)
{
    using namespace Abc;

    const GlobalSlotIndex gsind = GlobalSlotIndex(AbsoluteIndex(index));
    SF_ASSERT(gsind.IsValid());
    PushNewOpCode(Code::op_initabsslot, gsind.Get());
}

bool Tracer::EmitGetSlot(const Value& value, const UPInt index, bool objOnStack)
{
    using namespace Abc;

    if (value.IsTraits())
    {
        EmitGetAbsSlot(index);

        return true;
    }
    else
    {
        switch (value.GetKind())
        {
        case Value::kUndefined:
            if (objOnStack)
                EmitPopPrevResult();
            PushNewOpCode(Code::op_pushundefined);
            return true;
        case Value::kBoolean:
            if (objOnStack)
                EmitPopPrevResult();
            PushNewOpCode(value.AsBool() ? Code::op_pushtrue : Code::op_pushfalse);
            return true;
            /* TBD: pushint/pushuint
        case Value::kInt:
        case Value::kUInt:
            */
        case Value::kNumber:
            if (value.IsNaN())
            {
                if (objOnStack)
                    EmitPopPrevResult();
                PushNewOpCode(Code::op_pushnan);
                return true;
            }
            break;
            /* TBD: We can introduce an ObjectTag for strings.
        case Value::kString:
            break;
            */
        /*
        // Life time of objects and namespaces is not known.
        // TBD: We can keep a list of used objects in a function metainfo.
        case Value::kObject:
        case Value::kFunction:
        case Value::kNamespace:
        */
#if 1 // SS Dev.
        // This code had issues with unloading. See ComponentBrowser.swf
        case Value::kObject:
            // Duplicate code for debugging purposes.
            return EmitGetAbsObject(value, objOnStack);
#endif
        case Value::kClass:
            return EmitGetAbsObject(value, objOnStack);
        default:
            break;
        }
    }

    return false;
}

bool Tracer::EmitGetProperty(const Abc::Code::OpCode opcode, TR::State& st, const Traits* tr, const Multiname& mn, const int mn_index)
{
    using namespace Abc;

    // Ignore run-time multinames for the time being.
    if (!mn.IsRunTime())
    {
        if (tr)
        {
            VM& vm = GetVM();
            UPInt slot_ind = 0;

            if (mn.GetName().IsTraits())
            {
#if 0
                // Disabled because it probably causes problems.
                if (tr->IsArrayLike() && IsNumericType(mn.GetName()))
                {
                    const AS3::Multiname mn_getValue(vm.GetPublicNamespace(), vm.GetStringManager().CreateConstString("getValue"));
                    const SlotInfo* si = FindFixedSlot(vm, *tr, mn_getValue, slot_ind, NULL);
                    if (si && si->GetValueInd().IsValid())
                    {
                        // It looks like there is no reason to try to call callsupermethod here.

                        // Emit op_callmethod.
                        PushCode(Code::op_callmethod);
                        PushCode(static_cast<UInt32>(si->GetValueInd().Get()));
                        PushCode(1);

                        // Retrieve type of elements.
                        InstanceTraits::Traits* elem_tr = NULL;
                        if (tr == &GetVectorSIntType())
                            elem_tr = &st.GetSIntType();
                        else if (tr == &GetVectorUIntType())
                            elem_tr = &st.GetUIntType();
                        else if (tr == &GetVectorNumberType())
                            elem_tr = &st.GetNumberType();
                        else if (tr == &GetVectorStringType())
                            elem_tr = &st.GetStringType();
                        else if (tr->GetTraitsType() == Traits_Vector_object && tr->IsInstanceTraits())
                        {
                            const InstanceTraits::Traits* itr = static_cast<const InstanceTraits::Traits*>(tr);

                            if (itr && itr->HasConstructorSetup())
                                elem_tr = &static_cast<const ClassTraits::Vector_object&>(itr->GetClass().GetClassTraits()).GetEnclosedClassTraits().GetInstanceTraits();
                            else
                                elem_tr = &st.GetObjectType();
                        }
                        else
                            elem_tr = &st.GetObjectType();

                        st.PushOp(*elem_tr);

                        return true;
                    }
                }
#endif

                // Fall back.
                {
                    st.PushOp(Value(GetObjectType()));
                    // Restore back old opcode.
                    PushNewOpCode(opcode, mn_index);
                    return true;
                }
            }

            if (!tr->IsInterface() && !IsPrimitiveType(tr))
            {
                // Object is on stack. This is the difference from EmitFindProperty().
                if (tr->IsGlobal() && EmitGetClassTraits(st, mn, true))
                    return true;

                const SlotInfo* si = FindFixedSlot(vm, *tr, mn, slot_ind, NULL);

                if (si)
                {
                    // !!! ATTN: We MAY NOT skip BT_Set here.
                    if (si->IsCode())
                    {
                        if (si->GetAValueInd().IsValid())
                        {
                            // Call the code.
                            if (si->IsMethod())
                            {
                                // op_getsuper cannot be handled correctly by op_getabsslot.
                                if (opcode == Code::op_getproperty)
                                {
                                    EmitGetAbsSlot(slot_ind);

                                    // Retrieve function type.
                                    // We do not call GetFunctReturnType() here because found code is not
                                    // supposed to be called. It can be just assigned to a variable.
                                    st.PushOp(st.GetFunctType(tr->GetVT().GetValue(si->GetAValueInd())));

                                    return true;
                                }
                            }
                            else
                            {
                                if (mn.IsNameLate())
                                    // Get rid of runtime multiname on stack.
                                    PushNewOpCode(Code::op_pop);

                                PushNewOpCode(opcode == Code::op_getsuper ? Code::op_callsupermethod : Code::op_callmethod, si->GetValueInd(), 0); // Num of arguments.

                                // Retrieve function return type. In case of SlotInfo::BT_Code we need to retrieve function type.
                                st.PushOp(st.GetFunctReturnType(tr->GetVT().GetValue(si->GetAValueInd())));

                                return true;
                            }
                        }
                    }
                    else
                    {
                        // Get type.
                        {
                            Value type;

                            if (!st.GetPropertyType(*tr, *si, type))
                                return false;

                            st.PushOp(type);
                        }

                        if (mn.IsNameLate())
                            // Get rid of runtime multiname on stack.
                            PushNewOpCode(Code::op_pop);

                        EmitGetAbsSlot(slot_ind);

                        return true;
                    }
                }
            }


            // Default implementation.
            {
                // The property with the name specified by the multiname will be resolved in object, and the
                // value of that property will be pushed onto the stack. If the property is unresolved,
                // undefined is pushed onto the stack.

                UPInt slot_ind = 0;
                const SlotInfo* si = FindFixedSlot(GetVM(), *tr, mn, slot_ind, NULL);
                if (si)
                {
                    // Get type.
                    {
                        Value type;

                        if (!st.GetPropertyType(*tr, *si, type))
                            return false;

                        st.PushOp(type);
                    }

                    // Restore back old opcode.
                    PushNewOpCode(opcode, mn_index);

                    return true;
                }

                // Check for predefined Vector<> types.
                {
                    InstanceTraits::Traits* vitr = NULL;
                    if (tr == &vm.GetITraitsVectorSInt())
                        vitr = &vm.GetITraitsSInt();
                    else if (tr == &vm.GetITraitsVectorUInt())
                        vitr = &vm.GetITraitsUInt();
                    else if (tr == &vm.GetITraitsVectorNumber())
                        vitr = &vm.GetITraitsNumber();
                    else if (tr == &vm.GetITraitsVectorString())
                        vitr = &vm.GetITraitsString();
                    else if (tr->GetTraitsType() == Traits_Vector_object && tr->IsInstanceTraits())
                    {
                        const ClassTraits::Vector_object& ctr = static_cast<const ClassTraits::Vector_object&>(tr->GetClass().GetClassTraits());
                        const ClassTraits::Traits& elem_ctr = ctr.GetEnclosedClassTraits();

                        vitr = &elem_ctr.GetInstanceTraits();
                    }

                    if (vitr)
                    {
                        st.PushOp(Value(*vitr));

                        // Restore back old opcode.
                        PushNewOpCode(opcode, mn_index);

                        return true;
                    }
                }

            }
        }

    }

    st.PushOp(Value(GetObjectType()));

    // Restore back old opcode.
    PushNewOpCode(opcode, mn_index);

    return true;
}

bool Tracer::EmitSetProperty(const Abc::Code::OpCode opcode, const Traits* obj_tr, const Traits* val_tr, const Multiname& mn, const int mn_index)
{
    using namespace Abc;

    // Ignore run-time multinames for the time being.
    if (!mn.IsRunTime())
    {
        if (obj_tr)
        {
            VM& vm = GetVM();
            UPInt slot_ind = 0;
            const SlotInfo* si = FindFixedSlot(vm, *obj_tr, mn, slot_ind, NULL);

            if (si)
            {
                if (si->IsCode())
                {
                    if (si->GetAValueInd().IsValid() && !obj_tr->IsInterface())
                    {
                        const SlotInfo::BindingType dt = si->GetBindingType();

                        if (dt == SlotInfo::BT_Set || dt == SlotInfo::BT_GetSet)
                        {
                            // Get rid of Multiname on stack.
                            if (mn.IsNameLate())
                            {
                                PushNewOpCode(Code::op_swap);
                                PushNewOpCode(Code::op_pop);
                            }

                            PushNewOpCode(
                                opcode == Code::op_setsuper ? Code::op_callsupermethod : Code::op_callmethod, 
                                si->GetValueInd() + 1, 
                                1
                                );
                            PushNewOpCode(Code::op_pop);

                            return true;
                        }
                    }
                }
                else
                {
                    // Get rid of Multiname on stack.
                    if (mn.IsNameLate())
                    {
                        PushNewOpCode(Code::op_swap);
                        PushNewOpCode(Code::op_pop);
                    }

                    if (opcode == Code::op_initproperty)
                        EmitInitAbsSlot(slot_ind);
                    else
                        EmitSetAbsSlot(*si, val_tr, slot_ind);

                    return true;
                }
            }
        }
    }

    // Restore back old opcode.
    PushNewOpCode(opcode, mn_index);

    return true;
}

bool Tracer::EmitCall(const Abc::Code::OpCode opcode, TR::State& st, const Traits* tr, const Multiname& mn, const UInt32 mn_index, const UInt32 argc)
{
    using namespace Abc;

    // Ignore run-time multinames for the time being.
    if (!mn.IsRunTime())
    {
        UPInt slot_index = 0;
        VM& vm = GetVM();

        if (tr && !tr->IsInterface())
        {
            const SlotInfo* si = FindFixedSlot(GetVM(), *tr, mn, slot_index, NULL);

            // In case of a method or a getter ...
            if (si && si->GetAValueInd().IsValid() && (si->IsMethod() || si->IsGetter()))
            {
#ifdef SF_AS3_ENABLE_ARGNUM_VALIDATION_IN_TRACER
                // Validate number of arguments.
                {
                    const VTable& vt = tr->GetVT();
                    const Value& real_func = vt.GetRaw(AbsoluteIndex(si->GetValueInd()));

                    // VTable stores MethodInd or Thunk.
                    if (real_func.GetKind() == Value::kMethodInd)
                    {
                        // MethodInd.
                        const SInt32 method_ind = real_func.GetMethodInd();
                        const Traits& real_tr = real_func.GetTraits();
                        SF_ASSERT(real_tr.GetFilePtr());
                        VMAbcFile& file = *real_tr.GetFilePtr();
                        const Abc::MethodInfo& mi = file.GetMethodInfo(method_ind);
                        const UPInt max_param_num = mi.GetParamCount();
                        const UPInt opt_param_num = mi.GetOptionalParamCount();
                        const UPInt min_param_num = max_param_num - opt_param_num;
                        const bool need_rest = mi.NeedRest();

                        if (argc < min_param_num || (!need_rest && argc > max_param_num))
                        {
                            vm.ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, vm 
                                SF_DEBUG_ARG(si->GetNameNode()->pData) 
                                SF_DEBUG_ARG(min_param_num) 
                                SF_DEBUG_ARG(max_param_num)
                                SF_DEBUG_ARG(argc) 
                                ));
                            return false;
                        }
                    }
                    else
                    {
                        // Thunk.
                        const ThunkInfo& thunk = real_func.AsThunk();

                        // Check number of arguments.
                        if (argc > thunk.GetMaxArgNum() || argc < thunk.GetMinArgNum())
                        {
                            vm.ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, vm 
                                SF_DEBUG_ARG(thunk.Name) 
                                SF_DEBUG_ARG(thunk.GetMinArgNum()) 
                                SF_DEBUG_ARG(thunk.GetMaxArgNum())
                                SF_DEBUG_ARG(argc) 
                                ));
                            return false;
                        }
                    }
                }
#endif

                // Call the code.
                if (si->IsMethod())
                {
                    Code::OpCode new_opcode;

                    switch (opcode)
                    {
                    case Code::op_callsuper:
                    case Code::op_callsupervoid:
                        // Emit op_callsupermethod.
                        new_opcode = Code::op_callsupermethod;
                        break;
                    default:
                        // Emit op_callmethod.
                        new_opcode = Code::op_callmethod;
                        break;
                    }

                    PushNewOpCode(new_opcode, si->GetValueInd(), argc);

                    if (opcode == Code::op_callpropvoid || opcode == Code::op_callsupervoid)
                        PushNewOpCode(Code::op_pop);
                    else
                        // Retrieve a function type.
                        st.PushOp(Value(st.GetFunctReturnType(tr->GetVT().GetValue(si->GetAValueInd()))));

                    return true;
                }
                else if (si->IsGetter())
                {
#ifdef SF_AS3_ENABLE_ARGNUM_VALIDATION_IN_TRACER
                    // Validate number of arguments.
                    if (argc != 0)
                    {
                        vm.ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, vm 
                            SF_DEBUG_ARG(si->GetNameNode()->pData) 
                            SF_DEBUG_ARG(0) 
                            SF_DEBUG_ARG(0)
                            SF_DEBUG_ARG(argc) 
                            ));
                        return false;
                    }
#endif

                    Code::OpCode new_opcode = opcode;
                    switch (opcode)
                    {
                    case Code::op_callsuper:
                        // Emit op_callsupergetter.
                        new_opcode = Code::op_callsupergetter;
                        break;
                    case Code::op_callproperty:
                        // Emit op_callgetter.
                        new_opcode = Code::op_callgetter;
                        break;
                    default:
                        SF_ASSERT(false);
                        break;
                    }

                    PushNewOpCode(new_opcode, si->GetValueInd(), argc);

                    // Retrieve a function type.
                    st.PushOp(Value(st.GetFunctReturnType(tr->GetVT().GetValue(si->GetAValueInd()))));

                    return true;
                }
            }
        }

        {
            // It might happen that we "call" a type name.
            const ClassTraits::Traits* ctr = FindClassTraits(vm, mn);
            if (ctr)
            {
                // If we are here we have a valid type.
                // At least we know a result type.

                // It can happen that Class wasn't put on stack. This can happen in case of "with" statement.
                if (tr->IsClassTraits())
                {
                    PushNewOpCode(Code::op_callobject, argc);
                    st.PushOp(ctr->GetInstanceTraits());

                    return true;
                }

                // Emit original op_callproperty and set precise type, which, by the way, is not null.
                // It looks like there is no need to validate argc here because all
                // constructors take variable number of arguments.
                {
                    PushNewOpCode(opcode, mn_index, argc);

                    if (opcode != Code::op_callpropvoid || opcode != Code::op_callsupervoid)
                        st.PushOp(Value(ctr->GetInstanceTraits()));
                }

                return true;
            }
        }

    }

    // There is nothing we can do. Emit original op_callproperty.
    // We cannot validate argc here because name wasn't resolved.
    // Theoretically, this can be a problem.
    {
        PushNewOpCode(opcode, mn_index, argc);

        if (opcode != Code::op_callpropvoid || opcode != Code::op_callsupervoid)
            // It looks like we cannot do any better at this point.
            st.PushOp(Value(GetObjectType()));
    }

    return true;
}

bool Tracer::EmitGetAbsObject(const Value& value, bool objOnStack)
{
    using namespace Abc;

    bool result = false;

#ifdef SF_AS3_ENABLE_GETABSOBJECT
    const Traits& tr = GetVM().GetValueTraits(value);

    if (value.IsClass() || tr.IsGlobal())
    {
        Value::ObjectTag tag = value.GetObjectTag();

        if (objOnStack)
            EmitPopPrevResult();

        PushNewOpCode(
            Code::op_getabsobject,
            reinterpret_cast<UPInt>(value.GetObject()) + tag
            );

        // Putting GetGlobalObjectCPP in AbsObjects list will cause memory leaks.
        if (value.GetObject() != (Object*)&GetVM().GetGlobalObjectCPP())
            GetFile().AbsObjects.Set(value.GetObject());

        result = true;
    }
#else
    SF_UNUSED2(value, objOnStack);
#endif

    return result;
}

void Tracer::EmitGetOuterScope(const UPInt index)
{
    using namespace Abc;

    PushNewOpCode(Code::op_getouterscope, index);
}

void Tracer::Output(OutputMessageType type, const char* msg)
{
    GetFile().GetVM().GetUI().Output(type, msg);
}

bool Tracer::OnOpCode(Abc::TCodeOffset offset) 
{ 
    SF_UNUSED1(offset);
#ifdef GFX_AS3_TRACE
    // Trace trace state and opcode.
    AS3::TraceVM(*this, "\t");
    // We trace original byte code.
    AS3::TraceOpCode(*this, BCode, offset);
#endif

    return false;
}

TR::Block* Tracer::AddBlock(const TR::State& st, Abc::TCodeOffset from, bool dead, bool checkOpCode)
{
    using namespace Abc;

    if (from >= CodeEnd)
        // No blocks after CodeEnd.
        return NULL;

    TR::Block* block = GetBlock(from);
    SF_ASSERT(block);

    if (block && from == block->GetFrom())
    {
        // A block already exists.
        // The "dead" flag will be ignored here.

        return block;
    }

    // We need to create a new block.

    //
    //const bool not_initialized = dead;

    // Check current opcode.
    if (checkOpCode)
    {
        // !!! We can store prev_opcode and pass as an argument. That would save time.
        const Code::OpCode curr_opcode = GetCurrOrigOpCode(from);

        switch (curr_opcode)
        {
        case Code::op_label:
        case Code::op_debug:
        case Code::op_debugline:
        case Code::op_debugfile:
            // If there is a label, then this block is not dead.
            dead = false;
            break;
        case Code::op_jump:
            {
                const Code::OpCode prev_opcode = GetOrigPrevOpCode2(from);

                if (prev_opcode == Code::op_throw)
                    dead = false;
            }
            break;
        default:
            break;
        }
    }

    const UPInt si = States.GetSize();
    TR::State new_st(st);
    States.PushBack(new_st);
    // st can be invalidated at this point.
    TR::Block* newNode = SF_HEAP_NEW(GetHeap()) TR::Block(static_cast<UInt32>(si), from, dead);
    block->InsertNodeAfter(newNode);

    //if (not_initialized)
    if (dead)
    {
        // So far we do not check opcode only in exception blocks.
        newNode->SetInitialized(!dead);
    }

    return newNode;
}

const Traits* Tracer::GetValueTraits(const Value& v, const bool super_tr) const
{
    const Traits* result = NULL;

    if (super_tr)
        result = GetOriginationTraits();

    if (result == NULL)
    {
        switch (v.GetKind())
        {
        case Value::kUndefined:
			result = &GetVoidType();
            break;
        case Value::kInstanceTraits:
            result = &v.GetInstanceTraits();
            break;
        case Value::kClassTraits:
            result = &v.GetClassTraits();
            break;
        default:
            result = &GetVM().GetValueTraits(v);
        }

        // A hack.
        if (result && result == &GetVM().GetClassTraitsClassClass())
            result = &GetVM().GetClassTraitsObject();
    }

    if (super_tr && result)
        result = result->GetParent();

    return result;
}

const InstanceTraits::Traits& Tracer::GetInstanceTraits(const Value& v) const
{
    const InstanceTraits::Traits* result = NULL;

	if (v.IsNull())
		result = &GetNullType();
	else
	{
		switch (v.GetKind())
		{
		case Value::kUndefined:
			result = &GetClassType();
			break;
		case Value::kInstanceTraits:
			result = &v.GetInstanceTraits();
			break;
		case Value::kClassTraits:
			result = &v.GetClassTraits().GetInstanceTraits();
			break;
		default:
			result = &GetVM().GetInstanceTraits(v);
		}
	}

#if 0
    // ClassType (any type) is not the same as ObjectType.
    // ClassType can be "undefined". ObjectType can be only "null".
    // A hack.
    if (result && result == &GetClassType())
        result = &GetObjectType();
#endif

    return *result;
}

Scaleform::GFx::AS3::Value Tracer::GetGlobalObject(const TR::State& st) const
{
    const ScopeStackType* sss = GetSavedScope();

    if (sss && !sss->IsEmpty())
        return sss->At(0);

    return st.GetRegister(AbsoluteIndex(0));
}

const ClassTraits::Traits* Tracer::GetSlotCTraits(const Traits& tr, SlotIndex ind)
{
    const SlotInfo& si = tr.GetSlotInfo(AbsoluteIndex(ind, tr));
    return const_cast<SlotInfo&>(si).GetDataType(tr.GetVM());
}

bool Tracer::IsAnyType(const Traits* tr) const
{
#if 0
    // Not checking for ObjectType breaks code (VerifyError)
    // Example: 3DGenerator_AS3.swf
    // AnyType allows undefined, Object type doesn't.
    return  tr == &GetClassType();
#else
    return  tr == &GetObjectType() || tr == &GetClassType();
#endif
}

bool Tracer::IsPrimitiveType(const Traits* tr) const
{
    return  IsNotRefCountedType(tr) ||
            tr == &GetStringType();
}

bool Tracer::IsNotRefCountedType(const Traits* tr) const
{
    // ??? kUndefined = 0, // = 0
    return  tr == &GetBooleanType() ||
            tr == &GetVoidType() ||
            tr == &GetNullType() ||
            IsNumericType(tr);
}

bool Tracer::IsNumericType(const Traits* tr) const
{
    return  tr == &GetSIntType() ||
            tr == &GetUIntType() ||
            tr == &GetNumberType();
}

bool Tracer::IsNotObjectType(const Traits* tr) const
{
    return  IsNumericType(tr) ||
            tr == &GetBooleanType() ||
            tr == &GetVoidType() ||
            tr == &GetStringType();
}

bool Tracer::ValueIsOfType(const Value& value, const ClassTraits::Traits& type) const
{
    // There is no Tracer::GetClassTraits() function at this time.
    bool result = false;
    const Value::KindType kind = value.GetKind();

    switch (kind)
    {
    case Value::kClassTraits:
        {
            const ClassTraits::Traits& ctr = value.GetClassTraits();
            result = ctr.IsOfType(type);
        }
        break;
    case Value::kClass:
        {
            const Class& cl = value.AsClass();
            const ClassTraits::Traits& ctr = cl.GetClassTraits();
            result = ctr.IsOfType(type);
        }
        break;
    default:
        {
            const InstanceTraits::Traits& itr = GetInstanceTraits(value);

            result = itr.IsOfType(type.GetInstanceTraits());
        }
        break;
    }

    return result;
}

void Tracer::PushNewOpCode(Abc::Code::OpCode opcode)
{
    NewOpcodePos.PushBack(WCode.GetSize());
    WCode.PushBack(opcode);
}

void Tracer::PushNewOpCode(Abc::Code::OpCode opcode, UPInt arg1)
{
    NewOpcodePos.PushBack(WCode.GetSize());
    WCode.PushBack(opcode);
    WCode.PushBack(arg1);
}

void Tracer::PushNewOpCode(Abc::Code::OpCode opcode, UPInt arg1, UPInt arg2)
{
    NewOpcodePos.PushBack(WCode.GetSize());
    WCode.PushBack(opcode);
    WCode.PushBack(arg1);
    WCode.PushBack(arg2);
}

void Tracer::PushNewOpCodeArg(Abc::TOpCode::ValueType code)
{
    WCode.PushBack(code);
}

void Tracer::PopNewOpCode()
{
    SF_ASSERT(!NewOpcodePos.IsEmpty());
    Abc::TCodeOffset offset = NewOpcodePos.Back();

    NewOpcodePos.Pop();
    SF_ASSERT(WCode.GetSize() > offset);
    WCode.Resize(offset);
}

bool Tracer::IsOrigCall(Abc::Code::OpCode opcode)
{
    using namespace Abc;

    bool result = false;
    switch (opcode)
    {
    case Code::op_call:
    case Code::op_callmethod:
    case Code::op_callstatic:
    case Code::op_callsuper:
    case Code::op_callproperty:
    case Code::op_callproplex:
    case Code::op_callsupervoid:
    case Code::op_callpropvoid:
        result = true;
        break;
    default:
        break;
    }

    return result;
}

bool Tracer::IsOrigConstruct(Abc::Code::OpCode opcode)
{
    using namespace Abc;

    bool result = false;
    switch (opcode)
    {
    case Code::op_construct:
    case Code::op_constructsuper:
    case Code::op_constructprop:
        result = true;
        break;
    default:
        break;
    }

    return result;
}

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

