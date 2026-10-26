/**************************************************************************

Filename    :   AS3_VMRead.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_VMRead_H
#define INC_AS3_VMRead_H

#include "AS3_VM.h"


namespace Scaleform { namespace GFx { namespace AS3 
{

///////////////////////////////////////////////////////////////////////////
class StackReader
{
public:
    typedef StackReader SelfType;

    StackReader(VM& vm)
    : VMRef(vm)
    , OpStack(vm.OpStack)
    {
    }
    
public:
    void CheckObject(const Value& v) const
    {
        if (v.IsNullOrUndefined())
            GetVM().ThrowTypeError(VM::Error(
                v.IsNull() ? VM::eConvertNullToObjectError : VM::eConvertUndefinedToObjectError,
                GetVM()
            ));
    }

protected:
    VM& GetVM() const
    {
        return VMRef;
    }

    //
    VM::OpStackType& GetOpStack()
    {
        return OpStack;
    }
    const VM::OpStackType& GetOpStack() const
    {
        return OpStack;
    }

    //
    SF_INLINE
    void PopBack()
    {
        GetOpStack().PopBack();
    }
    SF_INLINE
    void PopBack2()
    {
        GetOpStack().PopBack2();
    }
    SF_INLINE
    void PopBack3()
    {
        GetOpStack().PopBack3();
    }
    SF_INLINE
    void PopBack(UPInt n)
    {
        GetOpStack().PopBack(static_cast<unsigned>(n));
    }

    //
    SF_INLINE
    Value& Back()
    {
        return GetOpStack().Top0();
    }
    SF_INLINE
    const Value& Back() const
    {
        return GetOpStack().Top0();
    }

protected:
    void Read(Multiname& obj);

private:
    SelfType& operator =(const SelfType&);

private:
    VM& VMRef;
    VM::OpStackType& OpStack;
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
    SF_INLINE
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

    ReadArgs(VM& vm, UInt32 arg_count);
    
    SF_INLINE
    const Value* GetCallArgs() const
    {
        if (ArgNum <= eFixedArrSize)
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

    const unsigned ArgNum;
    Value FixedArr[eFixedArrSize];
    ValueArrayDH CallArgs;
};

struct ReadArgsObject : public ReadArgs
{
    typedef ReadArgsObject SelfType;

    SF_INLINE
    ReadArgsObject(VM& vm, UInt32 arg_count)
    : ReadArgs(vm, arg_count)
    , ArgObject(GetOpStack())
    {
        CheckObject(ArgObject);
    }
    
    Value ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadArgsObjectRef : public ReadArgs
{
    typedef ReadArgsObjectRef SelfType;

    SF_INLINE
    ReadArgsObjectRef(VM& vm, UInt32 arg_count)
        : ReadArgs(vm, arg_count)
        , ArgObject(Back())
    {
        CheckObject(ArgObject);
    }

    Value& ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadArgsObjectValue : public ReadArgsObject
{
    typedef ReadArgsObjectValue SelfType;

    SF_INLINE
    ReadArgsObjectValue(VM& vm, UInt32 arg_count)
    : ReadArgsObject(vm, arg_count)
    , value(GetOpStack())
    {
    }
    
    const Value value;
};

struct ReadArgsMn : public ReadArgs, public MnReader
{
    typedef ReadArgsMn SelfType;

    SF_INLINE
    ReadArgsMn(VMAbcFile& file, UInt32 arg_count, UInt32 mn_index)
    : ReadArgs(file.GetVM(), arg_count)
    , MnReader(file)
    , ArgMN(file, GetMultiname(mn_index))
    {
        Read(ArgMN);
    }
    
    Multiname ArgMN;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadArgsMnObject : public ReadArgsMn
{
    typedef ReadArgsMnObject SelfType;

    SF_INLINE
    ReadArgsMnObject(VMAbcFile& file, UInt32 arg_count, UInt32 mn_index)
    : ReadArgsMn(file, arg_count, mn_index)
    , ArgObject(GetOpStack())
    {
        CheckObject(ArgObject);
    }
    
    const Value ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadArgsMnObjectRef : public ReadArgsMn
{
    typedef ReadArgsMnObjectRef SelfType;

    SF_INLINE
    ReadArgsMnObjectRef(VMAbcFile& file, UInt32 arg_count, UInt32 mn_index)
        : ReadArgsMn(file, arg_count, mn_index)
        , ArgObject(Back())
    {
        CheckObject(ArgObject);
    }

    Value& ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadMn : public StackReader, public MnReader
{
    typedef ReadMn SelfType;

    SF_INLINE
    ReadMn(VMAbcFile& file, UInt32 mn_index)
    : StackReader(file.GetVM())
    , MnReader(file)
    , ArgMN(file, GetMultiname(mn_index))
    {
        Read(ArgMN);
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
    ReadMnCt(VMAbcFile& file, UInt32 mn_index)
    : StackReader(file.GetVM())
    , MnReader(file)
    , ArgMN(GetMultiname(mn_index))
    {
        if (!ArgMN.IsCompileTime())
        {
            // The multiname at index must not be a runtime multiname.
            SF_DEBUG_CODE(const StringDataPtr& s = ArgMN.GetName(file.GetConstPool());)
            SF_DEBUG_CODE(const String name(s.ToCStr(), s.GetSize());)
            GetVM().ThrowTypeError(VM::Error(VM::eIllegalOpMultinameError, GetVM() SF_DEBUG_ARG(name) SF_DEBUG_ARG("compile time")));
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
    ReadValue(VM& vm)
    : StackReader(vm)
    , ArgValue(GetOpStack())
    {
    }
    
    Value ArgValue;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadObject : public StackReader
{
    typedef ReadObject SelfType;

    SF_INLINE
    ReadObject(VM& vm)
    : StackReader(vm)
    , ArgObject(GetOpStack())
    {
        CheckObject(ArgObject);
    }

    Value ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadObjectRef : public StackReader
{
    typedef ReadObjectRef SelfType;

    SF_INLINE
    ReadObjectRef(VM& vm)
        : StackReader(vm)
        , ArgObject(Back())
    {
        CheckObject(ArgObject);
    }

    Value& ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadMnCtValue : public ReadMnCt
{
    typedef ReadMnCtValue SelfType;

    SF_INLINE
    ReadMnCtValue(VMAbcFile& file, UInt32 mn_index)
    : ReadMnCt(file, mn_index)
    , value(GetOpStack())
    {
    }
    
    const Value value;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadMnCtValueRef : public ReadMnCt
{
    typedef ReadMnCtValueRef SelfType;

    SF_INLINE
    ReadMnCtValueRef(VMAbcFile& file, UInt32 mn_index)
        : ReadMnCt(file, mn_index)
        , value(Back())
    {
    }

    Value& value;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadValueObject : public ReadValue
{
    typedef ReadValueObject SelfType;

    SF_INLINE
    ReadValueObject(VM& vm)
    : ReadValue(vm)
    , ArgObject(GetOpStack())
    {
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
    ReadValueMn(VMAbcFile& file, UInt32 mn_index)
    : ReadValue(file.GetVM())
    , MnReader(file)
    , ArgMN(file, GetMultiname(mn_index))
    {
        Read(ArgMN);
    }
    
    Multiname ArgMN;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadValueMnObject : public ReadValueMn
{
    typedef ReadValueMnObject SelfType;

    SF_INLINE
    ReadValueMnObject(VMAbcFile& file, UInt32 mn_index)
    : ReadValueMn(file, mn_index)
    , ArgObject(GetOpStack())
    {
        CheckObject(ArgObject);
    }
    
    const Value ArgObject;

private:
    SelfType& operator =(const SelfType&);
};

struct ReadMnObjectRef : public ReadMn
{
    typedef ReadMnObjectRef SelfType;

    SF_INLINE
    ReadMnObjectRef(VMAbcFile& file, UInt32 mn_index)
    : ReadMn(file, mn_index)
    , ArgObject(Back())
    {
        CheckObject(ArgObject);
    }
    
    Value& ArgObject;

private:
    SelfType& operator =(const SelfType&);
};
    
}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_VMRead_H
