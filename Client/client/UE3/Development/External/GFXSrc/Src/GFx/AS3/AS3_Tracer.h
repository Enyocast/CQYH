/**************************************************************************

Filename    :   AS3_Tracer.h
Content     :   
Created     :   Sep, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_TRACER_H
#define INC_AS3_TRACER_H

#include "Kernel/SF_List.h"
#include "Kernel/SF_BitSet.h"

#include "AS3_VM.h"
#include "AS3_FlashUI.h"

// Not finished yet.
// #define SF_AS3_TR_UINT_AS_SINT

namespace Scaleform { namespace GFx { namespace AS3
{

///////////////////////////////////////////////////////////////////////////
class Tracer;

namespace TR
{
    enum MergeSet {msOpStack, msScopeStack, msRegisterFile};

    ///////////////////////////////////////////////////////////////////////////
    // Moveable.
    class Block : public NewOverrideBase<StatMV_VM_Tracer_Mem>, public ListNode<Block>
    {
        friend class AS3::Tracer;

    public:
        Block(UInt32 si, Abc::TCodeOffset f, bool dead = false) 
            : IsCatch(false)
            , IsTry(false)
            , IsDead(dead)
            , IsInitialized(true)
            , StateInd(si)
            , From(f)
        {
        }

    public:
        //
        bool IsInitializedBlock() const
        {
            return IsInitialized;
        }

        //
        bool IsCatchBlock() const
        {
            return IsCatch;
        }
        void SetCatchBlock(bool flag = true)
        {
            IsCatch = flag;
        }

        //
        bool IsTryBlock() const
        {
            return IsTry;
        }
        void SetTryBlock(bool flag = true)
        {
            IsTry = flag;
        }

        //
        bool IsDeadBlock() const
        {
            return IsDead;
        }
        void SetDeadBlock(bool flag = true)
        {
            IsDead = flag;
        }

        //
        Abc::TCodeOffset GetFrom() const
        {
            return From;
        }

        //
        UInt32 GetStateInd() const
        {
            return StateInd;
        }

    private:
        void SetInitialized(bool flag = true)
        {
            IsInitialized = flag;
        }

    private:
        UInt32              IsCatch:1;
        UInt32              IsTry:1;
        UInt32              IsDead:1;
        UInt32              IsInitialized:1;
        UInt32              StateInd;
        Abc::TCodeOffset    From; // Inclusive
    }; // class Block

    ///////////////////////////////////////////////////////////////////////////

    class StackReader;

    class State
    {
        friend class AS3::Tracer;
        friend class StackReader;

    public:
        State(Tracer& tr, Abc::TCodeOffset cp);

    public:
        enum ScopeType {stScopeStack, stStoredScope, stGlobalObject};

    public:
        const ValueArrayDH& GetRegisters() const
        {
            return Registers;
        }
        const ValueArrayDH& GetOpStack() const
        {
            return OpStack;
        }
        const ValueArrayDH& GetScopeStack() const
        {
            return ScopeStack;
        }

        ValueArrayDH& GetValueArray(MergeSet ms);
        const ValueArrayDH& GetValueArray(MergeSet ms) const;

    public:
        ///
        const Value& GetOpValue(UPInt ind) const
        {
            SF_ASSERT(ind < OpStack.GetSize());
            return OpStack[ind];
        }

        ///
        const Value& BackOpValue() const
        {
            return OpStack.Back();
        }
        Value& BackOpValue()
        {
            return OpStack.Back();
        }
        void SetBackOpValue(const Value& v)
        {
            OpStack.Back().Assign(v);
        }
        void SetBackOpValueUnsafe(const Value& v)
        {
            OpStack.Back().AssignUnsafe(v);
        }

        ///
        const Value& BackOp2ndValue() const
        {
            return OpStack[OpStack.GetSize() - 2];
        }

        ///
        Value PopOpValue()
        {
            return OpStack.Pop();
        }
        void PopOp(UPInt count = 1)
        {
            OpStack.PopBack(count);
        }
        void PushOp(const Value& v)
        {
            OpStack.PushBack(v);
        }
        void PushOp(InstanceTraits::Traits& tr, bool isNull = false)
        {
            OpStack.PushBack(Value(tr, isNull));
        }
        void PushOp(ClassTraits::Traits& tr, bool isNull = false)
        {
            OpStack.PushBack(Value(tr, isNull));
        }
        void ConvertOpTo(InstanceTraits::Traits& tr, bool isNull = false)
        {
            OpStack.Back() = Value(tr, isNull);
        }
        void SwapOp();

        ///
        const Value& GetScopeValue(UPInt ind)
        {
            SF_ASSERT(ind < ScopeStack.GetSize());
            return ScopeStack[ind];
        }
        void PopScope(UPInt count = 1)
        {
            ScopeStack.PopBack(count);
        }
        void PushScope(const Value& v)
        {
            ScopeStack.PushBack(v);
        }

        ///
        void SetRegister(AbsoluteIndex index, const Value& v)
        {
            Registers[index.Get()] = v;
            RegistersAlive.Set(index.Get());
        }
        const Value& GetRegister(AbsoluteIndex index) const
        {
            SF_ASSERT(RegistersAlive.IsSet(index.Get()));
            return Registers[index.Get()];
        }
        void ConvertRegisterTo(AbsoluteIndex index, InstanceTraits::Traits& tr, bool isNull = false)
        {
            SF_ASSERT(RegistersAlive.IsSet(index.Get()));
            Registers[index.Get()] = Value(tr, isNull);
        }

    public:
        const Tracer& GetTracer() const
        {
            return *pTracer;
        }
        Abc::TCodeOffset GetCP() const
        {
            return BCP;
        }

        ValueArrayDH& GetRegisters()
        {
            return Registers;
        }
        ValueArrayDH& GetOpStack()
        {
            return OpStack;
        }
        ValueArrayDH& GetScopeStack()
        {
            return ScopeStack;
        }

    public:

        void exec_throw() 
        { 
            // Get exception object from the stack ...
            PopOp(); // Index
        }

        void exec_dxns(UInt32 index) 
        {
            PushCode(index);

            // Sets the default XML namespace.

            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_dxns")));

            // index is a u30 that must be an index into the string constant pool. The string at index is used
            // as the uri for the default XML namespace for this method.

            // A VerifyError is thrown if dxns is used in a method that does not have the SETS_DXNS flag set.
        }
        void exec_dxnslate()
        {
            // Sets the default XML namespace with a value determined at runtime.

            PopOp();

            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_dxnslate")));

            // The top value on the stack is popped, converted to a string, and that string is used as the uri
            // for the default XML namespace for this method.

            // A VerifyError is thrown if dxnslate is used in a method that does not have the SETS_DXNS flag set.
        }
        void exec_kill(UInt32 index);
        void exec_label() 
        { 
            // Do nothing 
        }

        void exec_lookupswitch() 
        {
            // Value on the stack must be of type integer ...
            PopOp(); // Index
        }

        void exec_pushwith()
        {
            // A TypeError is thrown if scope_obj is null or undefined.

            PushScope(PopOpValue());
            // Set up the *scope* flag.
            GetScopeStack().Back().SetWith();
        }
        void exec_popscope()
        {
            PopScope();
        }
        void exec_nextname();
        void exec_hasnext();
        void exec_pushundefined()
        {
            PushOp(Value(GetVoidType()));
        }
        void exec_nextvalue();

        void exec_pushbyte(SInt32 v);
        void exec_pushshort(SInt32 v);
        void exec_pop();
        void exec_dup();
        void exec_swap() 
        {
            SwapOp();
        }
        void exec_pushstring(SInt32 v);
        void exec_pushint(SInt32 v);
        void exec_pushuint(SInt32 v);
        void exec_pushdouble(SInt32 v);
        void exec_pushscope();
        void exec_pushnamespace(UInt32 v) 
        {
            PushCode(v);
            PushOp(GetNamespaceType());
        }
        void exec_hasnext2(UInt32 object_reg, UInt32 index_reg);
        void exec_li8() 
        {
            // Load data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_li8")));
        }
        void exec_li16() 
        {
            // Load data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_li16")));
        }
        void exec_li32() 
        {
            // Load data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_li32")));
        }
        void exec_lf32() 
        {
            // Load data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_lf32")));
        }
        void exec_lf64() 
        {
            // Load data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_lf64")));
        }
        void exec_si8() 
        {
            // Store data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_si8")));
        }
        void exec_si16() 
        {
            // Store data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_si16")));
        }
        void exec_si32() 
        {
            // Store data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_si32")));
        }
        void exec_sf32() 
        {
            // Store data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_sf32")));
        }
        void exec_sf64() 
        {
            // Store data ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_sf64")));
        }
        void exec_newfunction(UInt32 method_ind)
        {
            PushCode(method_ind);

            PushOp(GetFunctionType());
        }
        void exec_call(UInt32 arg_count);
        void exec_construct(UInt32 arg_count);
        void exec_callmethod(UInt32 method_index, UInt32 arg_count);
        void exec_callstatic(UInt32 method_index, UInt32 arg_count);
        void exec_constructsuper(UInt32 arg_count);
        void exec_constructprop(UInt32 mn_index, UInt32 arg_count);
        void exec_sxi1() 
        {
            // Sign extend ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_sxi1")));
        }
        void exec_sxi8() 
        {
            // Sign extend ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_sxi8")));
        }
        void exec_sxi16() 
        {
            // Sign extend ... FP10 ...
            // Not documented ...
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_sxi16")));
        }
        void exec_applytype(UInt32 arg_count);
        void exec_newobject(UInt32 arg_count);
        void exec_newarray(UInt32 arr_size);
        void exec_newactivation();
        void exec_newclass(UInt32 v);
        void exec_getdescendants(UInt32 index);
        void exec_newcatch(UInt32 v);
        void exec_findpropstrict(UInt32 mn_index);
        void exec_findproperty(UInt32 mn_index);
        void exec_getlex(UInt32 mn_index);
        void exec_getabsobject(InstanceTraits::Traits& tr);
        void exec_getlocal(UInt32 reg_num) 
        {
            PushCode(reg_num);
            const Value& reg_value = GetRegister(AbsoluteIndex(reg_num));

            PushOp(reg_value);
        }
        void exec_setlocal(UInt32 v) 
        {
            PushCode(v);

            SetRegister(AbsoluteIndex(v), PopOpValue());
        }
        void exec_getglobalscope();
        void exec_getscopeobject(UInt32 scope_index) 
        {
            PushCode(scope_index);

            PushOp(GetScopeValue(scope_index));
            // Clean up the *with* flag.
            GetOpStack().Back().SetWith(false);
        }
        void exec_initproperty(UInt32 mn_index);
        void exec_deleteproperty(UInt32 mn_index);
        void exec_getslot(UInt32 slot_index);
        void exec_setslot(UInt32 slot_index);
        void exec_getglobalslot(UInt32 slot_index) 
        {
            PushCode(slot_index);

            // We can do better than this.
            PushOp(Value());
        }
        void exec_setglobalslot(UInt32 slot_index) 
        {
            PushCode(slot_index);

            // We can do better than this.
            PopOp();
        }
        void exec_esc_xelem() 
        {
            ConvertOpTo(GetStringType());

            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_esc_xelem")));
        }
        void exec_esc_xattr() 
        {
            ConvertOpTo(GetStringType());

            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_esc_xattr")));
        }
        void exec_convert_i();
        // Artificial command.
        void exec_convert_reg_i(UInt32 reg_num) 
        {
            // reg_num should be stored in WCode outside of this method.
            ConvertRegisterTo(AbsoluteIndex(reg_num), GetSIntType());
        }
        void exec_convert_u();
        // Artificial command.
        void exec_convert_reg_u(UInt32 reg_num) 
        {
            // reg_num should be stored in WCode outside of this method.
            ConvertRegisterTo(AbsoluteIndex(reg_num), GetUIntType());
        }
        void exec_convert_d();
        // Artificial command.
        void exec_convert_reg_d(UInt32 reg_num) 
        {
            // reg_num should be stored in WCode outside of this method.
            ConvertRegisterTo(AbsoluteIndex(reg_num), GetNumberType());
        }
        void exec_convert_b();
        void exec_convert_o() 
        {
            // Error if value.IsNullOrUndefined() || !value.IsObjectStrict()
        }
        void exec_checkfilter() 
        {
            // Not implemented yet ...
            GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("exec_checkfilter")));
        }
        void exec_astype(UInt32 mn_index);
        void exec_astypelate();
        void exec_inclocal(UInt32 v)
        {
            ConvertRegisterTo(AbsoluteIndex(v), GetNumberType());
        }
        void exec_declocal(UInt32 v)
        {
            ConvertRegisterTo(AbsoluteIndex(v), GetNumberType());
        }
        SF_INLINE
        void exec_not()
        {
            RefineOpCodeStack1(GetBooleanType(), Abc::Code::op_not_tb);
        }
        SF_INLINE
        void exec_negate()
        {
            // Result type of "negate" should always be number.
            RefineOpCodeStack1(GetNumberType(), Abc::Code::op_negate_td);
        }
        SF_INLINE
        void exec_increment_i()
        {
            RefineOpCodeStack1(GetSIntType(), Abc::Code::op_increment_ti);
        }
        SF_INLINE
        void exec_decrement_i()
        {
            RefineOpCodeStack1(GetSIntType(), Abc::Code::op_decrement_ti);
        }
        SF_INLINE
        void exec_negate_i()
        {
            RefineOpCodeStack1(GetSIntType(), Abc::Code::op_negate_ti);
        }

        SF_INLINE
        void exec_add_d()
        {
            RefineOpCodeStack2(GetNumberType(), Abc::Code::op_add_td);
        }
        SF_INLINE
        void exec_add_i()
        {
            RefineOpCodeStack2(GetSIntType(), Abc::Code::op_add_ti);
        }
        void exec_subtract()
        {
            RefineOpCodeStack2(GetNumberType(), Abc::Code::op_subtract_td);
        }
        SF_INLINE
        void exec_subtract_i()
        {
            RefineOpCodeStack2(GetSIntType(), Abc::Code::op_subtract_ti);
        }
        void exec_multiply()
        {
            RefineOpCodeStack2(GetNumberType(), Abc::Code::op_multiply_td);
        }
        SF_INLINE
        void exec_multiply_i()
        {
            RefineOpCodeStack2(GetSIntType(), Abc::Code::op_multiply_ti);
        }
        void exec_divide()
        {
            RefineOpCodeStack2(GetNumberType(), Abc::Code::op_divide_td);
        }

        void exec_1OpSInt();
        void exec_1OpNumber();
        void exec_1OpString();

        void exec_2OpNumber();
        void exec_2OpSInt();
        void exec_2OpUInt();
        void exec_2OpBoolean();

        void exec_istype(UInt32 mn_index);
        void exec_inclocal_i(UInt32 v)
        {
            RefineOpCodeReg1(GetSIntType(), Abc::Code::op_inclocal_ti, v);
        }
        void exec_declocal_i(UInt32 v) 
        {
            RefineOpCodeReg1(GetSIntType(), Abc::Code::op_declocal_ti, v);
        }
        void exec_getlocal0() 
        {
            const Value& reg_value = GetRegister(AbsoluteIndex(0));

            PushOp(reg_value);
        }
        void exec_getlocal1()
        {
            const Value& reg_value = GetRegister(AbsoluteIndex(1));

            PushOp(reg_value);
        }   
        void exec_getlocal2()
        {
            const Value& reg_value = GetRegister(AbsoluteIndex(2));

            PushOp(reg_value);
        }
        void exec_getlocal3()
        {
            const Value& reg_value = GetRegister(AbsoluteIndex(3));

            PushOp(reg_value);
        }
        void exec_setlocal0()
        {
            SetRegister(AbsoluteIndex(0), PopOpValue());
        }
        void exec_setlocal1()
        {
            SetRegister(AbsoluteIndex(1), PopOpValue());
        }
        void exec_setlocal2() 
        {
            SetRegister(AbsoluteIndex(2), PopOpValue());
        }
        void exec_setlocal3()
        {
            SetRegister(AbsoluteIndex(3), PopOpValue());
        }

    private:
        InstanceTraits::Traits& GetObjectType() const;
        InstanceTraits::Traits& GetClassType() const;
        InstanceTraits::Traits& GetFunctionType() const;
        InstanceTraits::Traits& GetArrayType() const;
        InstanceTraits::Traits& GetStringType() const;
        InstanceTraits::Traits& GetNumberType() const;
        InstanceTraits::Traits& GetSIntType() const;
        InstanceTraits::Traits& GetUIntType() const;
        InstanceTraits::Traits& GetBooleanType() const;
        InstanceTraits::Traits& GetNamespaceType() const;
        InstanceTraits::Traits& GetVectorSIntType() const;
        InstanceTraits::Traits& GetVectorUIntType() const;
        InstanceTraits::Traits& GetVectorNumberType() const;
        InstanceTraits::Traits& GetVectorStringType() const;
        InstanceTraits::Traits& GetNullType() const;
        InstanceTraits::Traits& GetVoidType() const;

        InstanceTraits::Traits& GetFunctType(const Value& value) const;

        InstanceTraits::Traits& GetFunctReturnType(const Value& value) const;
        InstanceTraits::Traits& GetFunctReturnType(const ThunkInfo& thunk) const;

        // This method will throw VerifyError if type is not found.
        CheckResult GetPropertyType(const Traits& obj_traits, const SlotInfo& si, Value& type) const;

    private:
        VMAbcFile& GetFile() const;
        VM& GetVM() const;
        Tracer& GetTracer()
        {
            return *pTracer;
        }

    private:
        void PushCode(UInt32 code) const;
        const Traits* GetValueTraits(const Value& v);
        const ScopeStackType* GetSavedScope() const;
        void FindProp(PropRef& result, const Multiname& mn, ScopeType& stype, UPInt& scope_index);

        // Refine opcode having one argument on stack.
        void RefineOpCodeStack1(InstanceTraits::Traits& type, Abc::Code::OpCode op);
        // Refine opcode having two arguments on stack.
        void RefineOpCodeStack2(InstanceTraits::Traits& type, Abc::Code::OpCode op);

        // Refine opcode having one argument in register.
        void RefineOpCodeReg1(InstanceTraits::Traits& type, Abc::Code::OpCode op, int reg_num);

    private:
        State& operator =(const State& other);

    private:
        Tracer*                             pTracer;
        Abc::TCodeOffset                    BCP;
        ValueArrayDH                        Registers;
        ValueArrayDH                        OpStack;
        ValueArrayDH                        ScopeStack;
        FixedBitSetDH<StatMV_VM_Tracer_Mem> RegistersAlive;
    }; // class State

    ///////////////////////////////////////////////////////////////////////////
    // This class is very similar to one, which reads real values.
    class StackReader
    {
    public:
        typedef StackReader SelfType;

        SF_INLINE
        StackReader(VM& vm, State& s)
            : VMRef(vm)
            , StateRef(s)
            , Num(0)
        {
        }

    protected:
        // How many extra records we have read ...
        void HaveRead(int _n)
        {
            Num += _n;
        }
        int GetRead() const
        {
            return Num;
        }

    protected:
        VM& GetVM() const
        {
            return VMRef;
        }
        State& GetState() const
        {
            return StateRef;
        }

        ValueArrayDH& GetOpStack() const
        {
            return GetState().OpStack;
        }
        Value PopOpValue()
        {
            return GetState().PopOpValue();
        }

        void CheckObject(const Value& v) const;

        int Read(Multiname& obj) const;

    private:
        SelfType& operator =(const SelfType&);

    private:
        VM&     VMRef;
        State&  StateRef;
        int     Num;
    };

    class MnReader
    {
    public:
        SF_INLINE
        MnReader(VMAbcFile& file)
            : File(file)
        {
        }

    public:
        VMAbcFile& GetFile() const
        {
            return File;
        }
        const Abc::Multiname& GetMultiname(UPInt ind) const
        {
            return GetFile().GetConstPool().GetMultiname(ind);
        }

    private:
        MnReader& operator =(const MnReader&);

    private:
        VMAbcFile& File;
    };

    // ReadArgs classes are used to read arguments from stack in various call opcodes,
    // including callproperty, callmethod, callsuper, construct, etc.

    struct ReadArgs : public StackReader
    {
        typedef ReadArgs SelfType;

        ReadArgs(VM& vm, State& s, UInt32 arg_count);

        const Value* GetCallArgs() const
        {
            if (ArgNum > CallArgs.GetSize())
                return FixedArr;
            else
                return CallArgs.GetDataPtr();
        }
        unsigned GetCallArgsNum() const
        {
            return ArgNum;
        }

    private:
        SelfType& operator =(const SelfType&);

    private:
        enum {eFixedArrSize = 8};

        const unsigned  ArgNum;
        Value      FixedArr[eFixedArrSize];
        ValueArrayDH    CallArgs;
    };

    struct ReadArgsObject : public ReadArgs
    {
        typedef ReadArgsObject SelfType;

        SF_INLINE
        ReadArgsObject(VM& vm, State& s, UInt32 arg_count)
            : ReadArgs(vm, s, arg_count)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadArgsObjectValue : public ReadArgsObject
    {
        typedef ReadArgsObjectValue SelfType;

        SF_INLINE
        ReadArgsObjectValue(VM& vm, State& s, UInt32 arg_count)
            : ReadArgsObject(vm, s, arg_count)
            , value(s.PopOpValue())
        {
            HaveRead(1);
        }

        const Value value;
    };

    struct ReadArgsMn : public ReadArgs, public MnReader
    {
        typedef ReadArgsMn SelfType;

        SF_INLINE
        ReadArgsMn(VMAbcFile& file, State& s, UInt32 arg_count, UInt32 mn_index)
            : ReadArgs(file.GetVM(), s, arg_count)
            , MnReader(file)
            , ArgMN(file, GetMultiname(mn_index))
        {
            HaveRead(Read(ArgMN));
        }

        Multiname ArgMN;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadArgsMnObject : public ReadArgsMn
    {
        typedef ReadArgsMnObject SelfType;

        SF_INLINE
        ReadArgsMnObject(VMAbcFile& file, State& s, UInt32 arg_count, UInt32 mn_index)
            : ReadArgsMn(file, s, arg_count, mn_index)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        const Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadMn : public StackReader, public MnReader
    {
        typedef ReadMn SelfType;

        SF_INLINE
        ReadMn(VMAbcFile& file, State& s, UInt32 mn_index)
            : StackReader(file.GetVM(), s)
            , MnReader(file)
            , ArgMN(file, GetMultiname(mn_index))
        {
            HaveRead(Read(ArgMN));
        }

        Multiname ArgMN;

    private:
        SelfType& operator =(const SelfType&);
    };

    // Read compile-time multiname ...
    struct ReadMnCt : public StackReader, public MnReader
    {
        typedef ReadMnCt SelfType;

        SF_INLINE
        ReadMnCt(VMAbcFile& file, State& s, UInt32 mn_index)
            : StackReader(file.GetVM(), s)
            , MnReader(file)
            , ArgMN(GetMultiname(mn_index))
        {
            if (!ArgMN.IsCompileTime())
            {
                // The multiname at index must not be a runtime multiname.
                SF_ASSERT(false);
            }
        }

        const Abc::Multiname& ArgMN;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadValue : public StackReader
    {
        typedef ReadValue SelfType;

        SF_INLINE
        ReadValue(VM& vm, State& s)
            : StackReader(vm, s)
            , ArgValue(s.PopOpValue())
        {
            HaveRead(1);
        }

        const Value ArgValue;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadObject : public StackReader
    {
        typedef ReadObject SelfType;

        SF_INLINE
        ReadObject(VM& vm, State& s)
            : StackReader(vm, s)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        const Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadMnCtValue : public ReadMnCt
    {
        typedef ReadMnCtValue SelfType;

        SF_INLINE
        ReadMnCtValue(VMAbcFile& file, State& s, UInt32 mn_index)
            : ReadMnCt(file, s, mn_index)
            , value(s.PopOpValue())
        {
            HaveRead(1);
        }

        const Value value;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadValueObject : public ReadValue
    {
        typedef ReadValueObject SelfType;

        SF_INLINE
        ReadValueObject(VM& vm, State& s)
            : ReadValue(vm, s)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        const Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadValueMn : public ReadValue, public MnReader
    {
        typedef ReadValueMn SelfType;

        SF_INLINE
        ReadValueMn(VMAbcFile& file, State& s, UInt32 mn_index)
            : ReadValue(file.GetVM(), s)
            , MnReader(file)
            , ArgMN(file, GetMultiname(mn_index))
        {
            HaveRead(Read(ArgMN));
        }

        Multiname ArgMN;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadValueMnObject : public ReadValueMn
    {
        typedef ReadValueMnObject SelfType;

        SF_INLINE
        ReadValueMnObject(VMAbcFile& file, State& s, UInt32 mn_index)
            : ReadValueMn(file, s, mn_index)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        const Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

    struct ReadMnObject : public ReadMn
    {
        typedef ReadMnObject SelfType;

        SF_INLINE
        ReadMnObject(VMAbcFile& file, State& s, UInt32 mn_index)
            : ReadMn(file, s, mn_index)
            , ArgObject(s.PopOpValue())
        {
            HaveRead(1);

            CheckObject(ArgObject);
        }

        const Value ArgObject;

    private:
        SelfType& operator =(const SelfType&);
    };

} // namespace TR

// Tracer is similar to the VM in the way that it tries to "execute" opcode.
// The main difference is that it doesn't care about real values. It does 
// care only about value's types.
// As a side effect it generates optimized byte pCode (it is actually word pCode).

class Tracer : FlashUI
{
    friend class TR::State;

public:
    Tracer(MemoryHeap* heap, const CallFrame& cf, Abc::TOpCode& wc, Abc::MethodBodyInfo::Exception& we);
    ~Tracer();

public:
    // Can throw exceptions.
    void EmitCode();

public:
    //
    MemoryHeap* GetHeap() const
    {
        return Heap;
    }

    //
    const TR::Block& GetFirstBlock() const
    {
        SF_ASSERT(!Blocks.IsEmpty());
        return *Blocks.GetFirst();
    }
    const TR::Block& GetCurrBlock() const
    {
        SF_ASSERT(CurrBlock);
        return *CurrBlock;
    }

    //
    VMAbcFile& GetFile() const
    {
        return CF.GetFile();
    }

    //
    const Abc::MethodBodyInfo& GetMethodBodyInfo() const
    {
        return CF.GetMethodBodyInfo();
    }

    const ScopeStackType* GetSavedScope() const
    {
        return CF.GetSavedScope();
    }
    const Traits* GetOriginationTraits() const
    {
        return CF.GetOriginationTraits();
    }

    const Abc::File& GetAbcFile() const
    {
        return GetFile().GetAbcFile();
    }

    VM& GetVM() const
    {
        return GetFile().GetVM();
    }

    const Traits* GetValueTraits(const Value& v, const bool super_tr = false) const;
    const InstanceTraits::Traits& GetInstanceTraits(const Value& v) const;
    // This doesn't seem to be possible to implement.
    //const ClassTraits::Traits* GetClassTraits(const Value& v) const;

    UPInt GetPrintOffset() const
    {
        return PrintOffset;
    }

    const TR::State& GetState(const TR::Block& b) const
    {
        return States[b.GetStateInd()];
    }

    SF_DEBUG_CODE(ASString GetName() const { return ASString(CF.GetName());} )

public:
    void InitializeBlock(TR::Block& to, const TR::Block& from);
    // Return false in case of an exception.
    CheckResult MergeBlock(TR::Block& to, const TR::Block& from);

private:
    // Methods in this section deal with ORIGINAL Abc byte code.
    // They MAY NOT be used with newly generated byte code.

    int GetNextU30(UPInt opcode_offset = 0) const;

    void SkipOrigOpCode(Abc::TCodeOffset& opcode_cp, Abc::TCodeOffset new_cp);
    void RegisterOrigOpCode(Abc::TCodeOffset opcode_cp);

    Abc::Code::OpCode GetCurrOrigOpCode(Abc::TCodeOffset opcode_offset) const
    {
        using namespace Abc;
        TCodeOffset ccp = opcode_offset;
        return static_cast<Code::OpCode>(Read8(pCode, ccp));

    }
    Abc::Code::OpCode GetNextOrigOpCode(Abc::TCodeOffset bcp) const
    {
        using namespace Abc;
        TCodeOffset ccp = bcp;
        return static_cast<Code::OpCode>(Read8(pCode, ccp));
    }
    Abc::Code::OpCode GetOrigPrevOpCode(UPInt opcode_num_diff = 1) const;
    // offset - absolute byte offset.
    Abc::Code::OpCode GetOrigPrevOpCode2(Abc::TCodeOffset offset) const;

    Abc::Code::OpCode GetOrigValueConsumer(Abc::TCodeOffset bcp) const;
    static bool IsOrigPropGetter(Abc::Code::OpCode opcode) 
    {
        using namespace Abc;
        return opcode == Code::op_getproperty;
    }
    static bool IsOrigPropSetter(Abc::Code::OpCode opcode) 
    {
        using namespace Abc;
        return opcode == Code::op_setproperty || opcode == Code::op_initproperty;
    }
    static bool IsOrigCall(Abc::Code::OpCode opcode);
    static bool IsOrigConstruct(Abc::Code::OpCode opcode);

private:
    // It will create a block if necessary.
    void StoreOffset(Abc::TCodeOffset bcp, const TR::State& st, SInt32 offset, int base = -1);

    Abc::Code::OpCode GetNewTopOpCode(UPInt num = 0) const;

    // Return true if no further processing is needed.
    // Can throw exceptions.
    bool SubstituteOpCode(Abc::TCodeOffset& bcp, TR::State& st, UInt8 byte_code);
    // Substitute op_getlocalXXX.
    bool SubstituteGetlocal(Abc::TCodeOffset& bcp, Abc::TCodeOffset ccp, TR::State& st, int src_reg_num);
    bool EmitFindProperty(TR::State& st, const int mn_index, bool get_prop = false, const Abc::Code::OpCode consumer = Abc::Code::op_nop SF_DEBUG_ARG(bool show_getprop = false));

    bool EmitGetClassTraits(TR::State& st, AS3::Multiname as3_mn, bool objOnStack = false);

    void EmitGetAbsSlot(const UPInt index);
    void EmitSetAbsSlot(const SlotInfo& si, const Traits* val_tr, const UPInt index);
    void EmitInitAbsSlot(const UPInt index);
    bool EmitGetAbsObject(const Value& value, bool objOnStack = false);

    bool EmitGetSlot(const Value& value, const UPInt index, bool objOnStack = false);

    void EmitGetOuterScope(const UPInt index);

    // EmitGetProperty() always returns true.
    bool EmitGetProperty(const Abc::Code::OpCode opcode, TR::State& st, const Traits* tr, const Multiname& mn, const int mn_index);
    bool EmitSetProperty(const Abc::Code::OpCode opcode, const Traits* obj_tr, const Traits* val_tr, const Multiname& mn, const int mn_index);
    bool EmitCall(const Abc::Code::OpCode opcode, TR::State& st, const Traits* tr, const Multiname& mn, const UInt32 mn_index, const UInt32 argc);

    // Emit code, which should pop result of previous opcode.
    void EmitPopPrevResult();

    // Translate offset into a block.
    TR::Block* GetBlock(Abc::TCodeOffset offset);
    // Can throw exceptions.
    void TraceBlock(Abc::TCodeOffset bcp, const TR::Block& initBlock);

private:
    InstanceTraits::Traits& GetObjectType() const
    {
        return GetVM().GetClassTraitsObject().GetInstanceTraits();
    }
    InstanceTraits::Traits& GetClassType() const
    {
        return GetVM().GetClassTraitsClassClass().GetInstanceTraits();
    }
    InstanceTraits::Traits& GetFunctionType() const
    {
        return GetVM().GetClassTraitsFunction().GetInstanceTraits();
    }
    InstanceTraits::Traits& GetArrayType() const
    {
        return GetVM().GetITraitsArray();
    }
    InstanceTraits::Traits& GetStringType() const
    {
        return GetVM().GetITraitsString();
    }
    InstanceTraits::Traits& GetNumberType() const
    {
        return GetVM().GetITraitsNumber();
    }
    InstanceTraits::Traits& GetSIntType() const
    {
        return GetVM().GetITraitsSInt();
    }
    InstanceTraits::Traits& GetUIntType() const
    {
        return GetVM().GetITraitsUInt();
    }
    InstanceTraits::Traits& GetBooleanType() const
    {
        return GetVM().GetITraitsBoolean();
    }
    InstanceTraits::Traits& GetNamespaceType() const
    {
        return GetVM().GetITraitsNamespace();
    }
    InstanceTraits::Traits& GetVectorSIntType() const
    {
        return GetVM().GetITraitsVectorSInt();
    }
    InstanceTraits::Traits& GetVectorUIntType() const
    {
        return GetVM().GetITraitsVectorUInt();
    }
    InstanceTraits::Traits& GetVectorNumberType() const
    {
        return GetVM().GetITraitsVectorNumber();
    }
    InstanceTraits::Traits& GetVectorStringType() const
    {
        return GetVM().GetITraitsVectorString();
    }
//     InstanceTraits::Traits& GetVectorObjectType() const
//     {
//         GetVM().GetClassTraitsVectorObject().GetInstanceTraits();
//     }

    InstanceTraits::Traits& GetNullType() const
    {
        return GetVM().GetITraitsNull();
    }
    InstanceTraits::Traits& GetVoidType() const
    {
        return GetVM().GetITraitsVoid();
    }

public:
    // Theoretically, we should pass InstanceTraits::Traits here.
    // But just Traits work fine. 
    bool IsAnyType(const Traits* tr) const;
    bool IsPrimitiveType(const Traits* tr) const;
    bool IsNumericType(const Traits* tr) const;
    bool IsNotRefCountedType(const Traits* tr) const;
    bool IsNotObjectType(const Traits* tr) const;

    // Null is of Object type.
    bool IsStringType(const Traits* tr) const
    {
        return tr == &GetStringType();
    }
    bool IsStringType(const Value& v) const
    {
        return  IsStringType(GetValueTraits(v));
    }

    //
    bool IsBooleanType(const Traits* tr) const
    {
        return tr == &GetBooleanType();
    }
    bool IsBooleanType(const Value& v) const
    {
        return  IsBooleanType(GetValueTraits(v));
    }

    //
#ifdef SF_AS3_TR_UINT_AS_SINT
    bool IsSIntType(const Traits* tr) const
    {
        return tr == &GetSIntType() || tr == &GetUIntType();
    }
#else
    bool IsSIntType(const Traits* tr) const
    {
        return tr == &GetSIntType();
    }
#endif
    bool IsSIntType(const Value& v) const
    {
        return  IsSIntType(GetValueTraits(v));
    }

    //
#ifdef SF_AS3_TR_UINT_AS_SINT
    bool IsUIntType(const Traits* tr) const
    {
        return tr == &GetUIntType() || tr == &GetSIntType();
    }
#else
    bool IsUIntType(const Traits* tr) const
    {
        return tr == &GetUIntType();
    }
#endif
    bool IsUIntType(const Value& v) const
    {
        return IsUIntType(GetValueTraits(v));
    }

    //
    bool IsNumberType(const Traits* tr) const
    {
        return tr == &GetNumberType();
    }
    bool IsNumberType(const Value& v) const
    {
        return IsNumberType(GetValueTraits(v));
    }

    bool IsNullType(const Traits* tr) const
    {
        return tr == &GetNullType();
    }

    bool ValueIsOfType(const Value& value, const ClassTraits::Traits& type) const;
    bool ValueIsOfType(const Value& value, const InstanceTraits::Traits& type) const
    {
        const InstanceTraits::Traits& itr = GetInstanceTraits(value);
        return itr.IsOfType(type);
    }


private:
    CheckResult MergeValues(UPInt ind, TR::State& to, const TR::State& from, TR::MergeSet ms) const;
	CheckResult MergeLists(TR::State& to, const TR::State& from, bool check_size, TR::MergeSet ms) const;
    void ThrowMergeTypeError(const Traits& to_tr, const Traits& from_tr) const;

private:
    Tracer& operator =(const Tracer&);

private:
    struct Recalculate
    {
        Recalculate(Abc::TCodeOffset p, int b = -1)
            : pos(p)
            , base(b)
        {
            SF_ASSERT(pos > 0);
            //SF_ASSERT(base <= 0);
        }
        Abc::TCodeOffset pos;
        // offset of a command base relative to "pos".
        // "base" uses target coordinates.
        int base;
    };

    TR::State& GetState(const TR::Block& b)
    {
        return States[b.GetStateInd()];
    }

private:
    void PushNewOpCode(Abc::Code::OpCode opcode);
    void PushNewOpCode(Abc::Code::OpCode opcode, UPInt arg1);
    void PushNewOpCode(Abc::Code::OpCode opcode, UPInt arg1, UPInt arg2);

    void PushNewOpCodeArg(Abc::TOpCode::ValueType code);

    // PopNewOpCode will pop opcode itself and its arguments.
    void PopNewOpCode();

    void SetNewOpCode(UInt32 code)
    {
        WCode.Back() = code;
    }

private:
    bool IsException() const
    {
        return GetVM().IsException();
    }

    Value GetGlobalObject(const TR::State& st) const;
    static const ClassTraits::Traits* GetSlotCTraits(const Traits& tr, SlotIndex ind);

    // Return NULL if a valid block cannot be created.
    TR::Block* AddBlock(const TR::State& st, Abc::TCodeOffset from, bool dead = false, bool checkOpCode = true);

public:
    // UI related stuff.

    FlashUI& GetUI() { return *this; }

private:
    virtual void Output(OutputMessageType type, const char* msg);  
    virtual bool OnOpCode(Abc::TCodeOffset offset);

private:
    bool                            Done;
    MemoryHeap*                     Heap;
    const CallFrame&                CF;
    Abc::TOpCode&                   WCode;
    Abc::MethodBodyInfo::Exception& WException;
    Abc::TCodeOffset                CurrOffset;
    const StringDataPtr             BCode;
    const UInt8*                    pCode;
    const Abc::TCodeOffset          CodeEnd;
    // Original opcode positions
    ArrayDH_POD<Abc::TCodeOffset, Mem_Stat> OrigOpcodePos;
    // New opcode positions
    ArrayDH_POD<Abc::TCodeOffset, Mem_Stat> NewOpcodePos;
    // Positions, which require postponed recalculation.
    ArrayDH_POD<Recalculate, Mem_Stat>      PosToRecalculate;
    // Map of original position to new (long) position.
    ArrayDH_POD<Abc::TCodeOffset, Mem_Stat> Orig2newPosMap;

    ArrayDH<TR::State>  States;
    List<TR::Block>     Blocks;
    UPInt               PrintOffset;
    //UPInt BlockInd;
    TR::Block*          CurrBlock;
}; // class Tracer

namespace TR
{
    inline
    InstanceTraits::Traits& State::GetObjectType() const
    {
        return GetTracer().GetObjectType();
    }

    inline
    InstanceTraits::Traits& State::GetClassType() const
    {
        return GetTracer().GetClassType();
    }

    inline
    InstanceTraits::Traits& State::GetFunctionType() const
    {
        return GetTracer().GetFunctionType();
    }

    inline
    InstanceTraits::Traits& State::GetArrayType() const
    {
        return GetTracer().GetArrayType();
    }

    inline
    InstanceTraits::Traits& State::GetStringType() const
    {
        return GetTracer().GetStringType();
    }

    inline
    InstanceTraits::Traits& State::GetNumberType() const
    {
        return GetTracer().GetNumberType();
    }

    inline
    InstanceTraits::Traits& State::GetSIntType() const
    {
        return GetTracer().GetSIntType();
    }

    inline
    InstanceTraits::Traits& State::GetUIntType() const
    {
        return GetTracer().GetUIntType();
    }

    inline
    InstanceTraits::Traits& State::GetBooleanType() const
    {
        return GetTracer().GetBooleanType();
    }

    inline
    InstanceTraits::Traits& State::GetNamespaceType() const
    {
        return GetTracer().GetNamespaceType();
    }

    inline
    InstanceTraits::Traits& State::GetVectorSIntType() const
    {
        return GetTracer().GetVectorSIntType();
    }

    inline
    InstanceTraits::Traits& State::GetVectorUIntType() const
    {
        return GetTracer().GetVectorUIntType();
    }

    inline
    InstanceTraits::Traits& State::GetVectorNumberType() const
    {
        return GetTracer().GetVectorNumberType();
    }

    inline
    InstanceTraits::Traits& State::GetVectorStringType() const
    {
        return GetTracer().GetVectorStringType();
    }

    inline
    InstanceTraits::Traits& State::GetNullType() const
    {
        return GetTracer().GetNullType();
    }

    inline
    InstanceTraits::Traits& State::GetVoidType() const
    {
        return GetTracer().GetVoidType();
    }

    inline
    void State::exec_getglobalscope() 
    {
        PushOp(GetTracer().GetGlobalObject(*this));
    }

    inline
    void State::PushCode(UInt32 code) const
    {
        pTracer->WCode.PushBack(code);
    }

    inline
    const Traits* State::GetValueTraits(const Value& v)
    {
        return GetTracer().GetValueTraits(v);
    }

    inline
    const ScopeStackType* State::GetSavedScope() const
    {
        return GetTracer().GetSavedScope();
    }

    inline
    VMAbcFile& State::GetFile() const
    {
        return GetTracer().GetFile();
    }

    inline
    VM& State::GetVM() const
    {
        return GetTracer().GetVM();
    }

} // namespace TR

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_TRACER_H

