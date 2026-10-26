/**************************************************************************

Filename    :   AS3_Obj_Function.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#ifndef INC_AS3_Obj_Function_H
#define INC_AS3_Obj_Function_H

#include "../AS3_Object.h"
#include "AS3_Obj_Object.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

// Forward declaration.
class VMAbcFile;    
class VTable;

namespace InstanceTraits
{
    class Function;
    class ThunkFunction;
}

namespace Classes
{
    class Function;
} // namespace Classes

namespace Instances
{
    //////////////////////////////////////////////////////////////////////////
    class FunctionBase : public Instances::Object
    //class FunctionBase : public Class
    {
        friend class InstanceTraits::Function; // Because of *Prototype* ...

    public:
        typedef FunctionBase SelfType;
        typedef Classes::Function ClassType;
        
    protected:
        FunctionBase(InstanceTraits::Traits& t);
        virtual ~FunctionBase();

    public:
//         void toStringProto(ASString& result);
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

        // *argv* does not include *this* ...
        // These Execute() methods should be const. It is reasonable.
        // Function call doesn't change function itself.
        virtual void ExecuteUnsafe(const Value& _this, Value& result, unsigned argc, const Value* argv) const;
        virtual void Execute(const Value& _this, unsigned argc, const Value* argv, bool discard_result = false) const;

        // Apply is similar to Call(), except arguments are passed as an Array object.
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual void Construct(Value& result, unsigned argc, const Value* argv, bool extCall = false);

#if 0 // We do not need this method because Prototype is registered with Traits and will be visited automatically.
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
#endif

        virtual UInt32 GetMaxParamNum() const;

    public:
        // AS3 methods.
        void lengthGet(UInt32& result);
        static void call(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void apply(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

    protected:
        void PushResult(Value& value) const;
        void PickPushResult(Value& value) const;
        void RetrieveResult(Value& result) const;
        void RetrieveResultUnsafe(Value& result) const;

    protected:
        SPtr<AS3::Object> Prototype; // Function behaves similar to Class. Because of that it has a prototype ...
    };
    
    //////////////////////////////////////////////////////////////////////////
    // If function is included in a Virtual Table it stores Origination Traits
    // (Traits to which this Virtual Table belongs)
    class Function : public FunctionBase
    {
        friend class Classes::Function; // Because of constructor.
        friend class AS3::VTable; // Because of StoreScopeStack();

        typedef Function SelfType;
        typedef FunctionBase ParentType;
        
    private:
        Function(
            VMAbcFile& file,
            const UInt32 mi_ind,
            const ScopeStackType& scope,
            const Value& _this,
            const Traits* ot
            SF_DEBUG_ARG(const ASString& name)
            );
            
    public:
        ~Function();
        
    public:
        virtual const ScopeStackType* GetStoredScope() const;
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        
    public:
        // *argv* does not include *this* ...
        virtual void Execute(const Value& _this, unsigned argc, const Value* argv, bool discard_result = false) const;
        // *argv* does not include *this* ...
        void Execute(unsigned argc, const Value* argv, bool discard_result = false)
        {
            Execute(Value(this), argc, argv, discard_result);
        }
        // *argv* does not include *this* ...
        virtual void ExecuteUnsafe(const Value& _this, Value& result, unsigned argc, const Value* argv) const;
        virtual UInt32 GetMaxParamNum() const;

        const Abc::Multiname& GetReturnType() const;
        const ScopeStackType& GetInitScope() const
        {
            return InitScope;
        }
        VMAbcFile& GetFile() const
        {
            return *File;
        }

        const Abc::MethodBodyInfo& GetMBI() const;

        SelfType& GetSelf()
        {
            return *this;
        }
        UInt32 GetMethodInfoInd() const
        {
            return MethodInfoInd;
        }
        const Traits& GetOriginationTraits() const
        {
            return *OriginationTraits;
        }

        SF_DEBUG_CODE(const ASString& GetFunctionName() const { return Name; })

    private:
        void StoreScopeStack(const UPInt baseSSInd, const ScopeStackType& ss)
        {
            InitScope.Clear();

            for (UPInt i = baseSSInd; i < ss.GetSize(); ++i)
                InitScope.PushBack(ss[i]);
        }
        void Add2StoredScopeStack(const Value& o)
        {
            InitScope.PushBack(o);
        }

    private:
        SPtr<VMAbcFile> File;
        const UInt32 MethodInfoInd; // MethodInd is required to build a proper object's name.
        // We keep a copy of the scope stack ...
        ScopeStackType InitScope;
        const Value This;
        // OriginationTraits is where this function came from.
        const SPtr<const Traits> OriginationTraits;
        SF_DEBUG_CODE(const ASString Name;)
    };

    //////////////////////////////////////////////////////////////////////////
    class ThunkFunction : public FunctionBase
    {
        friend class Classes::Function;

    protected:
        ThunkFunction(
            InstanceTraits::Traits& t,
            const ThunkInfo& thunk
            SF_DEBUG_ARG(const Traits& ot)
            )
            : FunctionBase(t)
            , Thunk(thunk)
            SF_DEBUG_ARG(OriginationTraits(&ot))
        {
        }

    public:
        virtual void ExecuteUnsafe(const Value& _this, Value& result, unsigned argc, const Value* argv) const;
        virtual void Execute(const Value& _this, unsigned argc, const Value* argv, bool discard_result = false) const;

        const ThunkInfo& GetThunk() const { return Thunk; }

        SF_DEBUG_CODE(virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;)
        SF_DEBUG_CODE(const Traits& GetOriginationTraits() const  { return *OriginationTraits; })

    public:
        // AS3 methods.
        void length(Value& result, unsigned argc, const Value* argv);

    private:
        // Function itself.
        const ThunkInfo& Thunk;
        // OriginationTraits is where this function came from.
        // OriginationTraits is optional here. We need it just to be able
        // to trace where it came from if it was assigned to an object
        // as a dynamic property. Main case is prototype.
        SF_DEBUG_CODE(const SPtr<const Traits> OriginationTraits;)
    };
    
    //////////////////////////////////////////////////////////////////////////
    // It is a function delegate, which will check type of *this* before a call.
    class CheckTypeTF : public ThunkFunction
    {
        friend class Classes::Function;

    public:
        typedef CheckTypeTF     SelfType;
        typedef ThunkFunction   ParentType;

    protected:
        CheckTypeTF(
            InstanceTraits::ThunkFunction& t,
            const ThunkInfo& thunk,
            const Class& data_type
            SF_DEBUG_ARG(const Traits& ot)
            );

    public:
        virtual void ExecuteUnsafe(const Value& _this, Value& result, unsigned argc, const Value* argv) const;
        virtual void Execute(const Value& _this, unsigned argc, const Value* argv, bool discard_result = false) const;

    private:
        const Class& DataTypeClass;
    };

} // namespace Instances

namespace InstanceTraits
{
    // All InstanceTraits related to Function have same Virtual Table.
    // ( apply(), call(), lengthGet() )

    ///////////////////////////////////////////////////////////////////////////
    // It is a SealedObject, what is not absolutely correct,
    // but we cannot do anything about this.
    class Thunk : public Traits
    {
    public:
        Thunk(VM& vm);

    public:
        virtual void MakeObject(Value& result, Traits& t);
        ASString GetThunkName(const Value& _this) const;

    public:
        // AS3 methods.
        // toString() belongs to a prototype.
        static void lengthGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

    private:
        static const ThunkInfo f[3];
    };

    ///////////////////////////////////////////////////////////////////////////
    // It is a SealedObject, what is not absolutely correct,
    // but we cannot do anything about this.
    class MethodInd : public Traits
    {
    public:
        MethodInd(VM& vm);

    public:
        virtual void MakeObject(Value& result, Traits& t);
        ASString GetMethodIndName(const Value& _this) const;

    public:
        // AS3 methods.
        // toString() belongs to a prototype.
        static void lengthGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

    private:
        static const ThunkInfo f[3];
    };

    ///////////////////////////////////////////////////////////////////////////
    // It is a SealedObject, what is not absolutely correct,
    // but we cannot do anything about this.
    class VTableInd : public Traits
    {
    public:
        VTableInd(VM& vm);

    public:
        virtual void MakeObject(Value& result, Traits& t);
        // Not implemented yet.
        //ASString GetName(const Value& _this) const;

    public:
        // AS3 methods.
        // toString() belongs to a prototype.
        static void lengthGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

    private:
        static const ThunkInfo f[3];
    };

    ///////////////////////////////////////////////////////////////////////////
    // ThunkFunction is Traits for a dynamic object, which will delegate 
    // all calls to Thunk methods. ThunkFunction is supposed to be used as a proxy
    // to check types and do type conversions.
    class ThunkFunction : public Traits
    {
    public:
        ThunkFunction(VM& vm);

    public:
        virtual void MakeObject(Value& result, Traits& t);
        ASString GetThunkName(const Value& _this) const;

    private:
        static const ThunkInfo f[1];
    };

    ///////////////////////////////////////////////////////////////////////////
    class Function : public Traits
    {
        friend class Classes::Function; // Because of Function(VM& vm, Class& c).
        friend class ClassTraits::Function; // Because of Function(VM& vm, Class& c).
        friend class AS3::VM; // Because of Function(VM& vm, Class& c).

    public:
        Function(VMAbcFile* file, VM& vm, const ClassInfo& ci, const Abc::MethodBodyInfo& mbi);

    public:
        Pickable<Instances::FunctionBase> MakeInstance(Traits& t)
        {
            // Placement new.
            return Pickable<Instances::FunctionBase>(new(t.Alloc()) Instances::FunctionBase(*this));
        }
        virtual void MakeObject(Value& result, Traits& t);
        virtual unsigned GetFixedMemSize() const;

        ASString GetFunctionName(const Value& _this) const;

        static const ThunkInfo& GetApplyThunkInfo() { return GetThunkInfo(0); }
        static const ThunkInfo& GetCallThunkInfo() { return GetThunkInfo(1); }

    protected:
        Function(VM& vm, const ClassInfo& ci);

    private:
        void RegisterSlots();
        static const ThunkInfo& GetThunkInfo(UPInt ind)
        {
            return f[ind];
        }

    private:
        static const ThunkInfo f[3];
    };

} // namespace InstanceTraits

namespace ClassTraits
{
    // ClassTraits::Function shouldn't be related to any VMAbcFile,
    // because it can be created when VMAbcFile is not available yet.
    class Function : public Traits
    {
    public:
        Function(VM& vm, const ClassInfo& ci);

    public:
        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;

    public:
        InstanceTraits::Thunk& GetThunkTraits() const
        {
            return *ThunkTraits;
        }

        InstanceTraits::ThunkFunction& GetThunkFunctionTraits() const
        {
            return *ThunkFunctionTraits;
        }

        InstanceTraits::MethodInd& GetMethodIndTraits() const
        {
            return *MethodIndTraits;
        }

        InstanceTraits::VTableInd& GetVTableTraits() const
        {
            return *VTableTraits;
        }

    public:
        // Coerce *value* to this type (value of this class) ...
        virtual bool Coerce(const Value& value, Value& result) const;
        bool CoerceValue(const Value& value, Value& result) const;

    private:
        SPtr<InstanceTraits::Thunk>         ThunkTraits;
        SPtr<InstanceTraits::ThunkFunction> ThunkFunctionTraits;
        SPtr<InstanceTraits::MethodInd>     MethodIndTraits;
        SPtr<InstanceTraits::VTableInd>     VTableTraits;
    };

} // namespace ClassTraits

namespace Classes
{
    // Class for the Function ...
    class Function : public Class
    {
        friend class ClassTraits::Function;
        
    public:
        typedef Function SelfType;
        
    protected:
        SF_INLINE
        Function(ClassTraits::Traits& t)
        : Class(t)
        {
        }
        
    public:
        virtual Pickable<AS3::Object> MakePrototype() const;
        virtual void InitPrototype(AS3::Object& obj) const;
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual void Construct(Value& _this, unsigned argc, const Value* argv, bool extCall = false);

    public:
        const ClassTraits::Function& GetClassTraits() const
        {
            return static_cast<const ClassTraits::Function&>(Class::GetClassTraits());
        }

        // !!! In this method we miss an object ...
        // So, it is a function by default.
        Pickable<Instances::Function> MakeInstance(VMAbcFile& file, const UInt32 method_ind, const ScopeStackType& ss, const Traits& ot) const;
        // This method is supposed to be used in a Construct() method ...
//          Instances::Function* MakeInstance(const int method_ind, AS3::Object& _this);

        // It can be an instance of a function or a method closure.
        // MakeInstance2 is used with virtual table only.
        Pickable<Instances::Function> MakeInstance2(VMAbcFile& file, const UInt32 method_ind, const Value& _this, const ScopeStackType& ss, const Traits& ot SF_DEBUG_ARG(const ASString& name)) const;

        // Create a MethodClosure from a Function.
        Pickable<Instances::Function> MakeInstance2(const Instances::Function& f, const Value& _this) const;

//         // This one is for for TThunkFunc ...
//         Instances::ThunkClosure* MakeInstance(InstanceTraits::Traits& t, AS3::Object& _this, Value::TThunkFunc func) const;

        Pickable<Instances::ThunkFunction> MakeThunkFunction(const ThunkInfo& thunk SF_DEBUG_ARG(const Traits& ot)) const;
        Pickable<Instances::CheckTypeTF> MakeCheckTypeInstance(const Class& data_type, const ThunkInfo& thunk SF_DEBUG_ARG(const Traits& ot)) const;

    protected:
        ClassTraits::Function& GetClassTraits()
        {
            return static_cast<ClassTraits::Function&>(Class::GetClassTraits());
        }

    private:
        SelfType& GetSelf()
        {
            return *this;
        }

    private:
        static const ThunkInfo f[4];
    };
    
} // namespace Classes

namespace Instances
{
    inline
    CheckTypeTF::CheckTypeTF(
        InstanceTraits::ThunkFunction& t,
        const ThunkInfo& thunk,
        const Class& data_type
        SF_DEBUG_ARG(const Traits& ot)
        )
        : ThunkFunction(t, thunk SF_DEBUG_ARG(ot))
        , DataTypeClass(data_type)
    {
    }
} // namespace Instances

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif // INC_AS3_Obj_Function_H
