//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Vec_Vector_object.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Vec_Vector_object_H
#define INC_AS3_Obj_Vec_Vector_object_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "AS3_Obj_Vec_VectorBase.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Vector_object;
}

namespace InstanceTraits
{
    class Vector_object;
}

namespace Classes
{
    class Vector_object;
}

namespace Instances
{
    class Vector_object : public Instances::Object
    {
        friend class InstanceTraits::Vector_object;
        
    public:
        typedef Vector_object SelfType;
        typedef Classes::Vector_object ClassType;
        typedef InstanceTraits::Vector_object TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Vector_object"; }
#endif
    protected:
        Vector_object(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
#if 0
        typedef SPtr<AS3::Object> ValueType;
#else
        typedef Value ValueType;
#endif

        void Append(const SelfType& other) { V.Append(other.V); }
        void Append(unsigned argc, const Value* const argv) { V.Append(argc, argv, GetEnclosedClassTraits()); }
        void Append(const Instances::Array& arr) { V.Append(arr, GetEnclosedClassTraits()); }
        void Append(const ArrayDH<ValueType>& arr) { V.Append(arr); }

        void AppendCoerce(const Instances::Array& arr) { V.AppendCoerce(arr, GetEnclosedClassTraits()); }
        bool AppendCoerce(const Value& v) { return V.AppendCoerce(v, GetEnclosedClassTraits()); }

#if 0
        void PushBack(Object* v) { V.PushBack(SPtr<AS3::Object>(v)); }
        void PushBack(const Value& v) { V.PushBack(SPtr<AS3::Object>(v.GetObject())); }
#else
        void PushBack(const ValueType& v) { V.PushBack(v); }
#endif

        const ClassTraits::Traits& GetEnclosedClassTraits() const;
        const ArrayBase& GetArrayBase() const { return V; }

    public:
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

    public:
        AbsoluteIndex GetNextArrayIndex(AbsoluteIndex ind) const { return V.GetNextArrayIndex(ind); }
        void GetNextValue(Value& value, GlobalSlotIndex ind) const { V.GetNextValue(value, ind); }

        CheckResult Set(UInt32 ind, const Value& v, const ClassTraits::Traits& tr) { return V.Set(ind, v, tr); }
        void Get(UInt32 ind, Value& v) const { V.Get(ind, v); }
        CheckResult RemoveAt(UInt32 ind) { return V.RemoveAt(ind); }

    public:
        virtual void GetNextPropertyName(Value& name, GlobalSlotIndex ind) const;
        virtual GlobalSlotIndex GetNextDynPropIndex(GlobalSlotIndex ind) const;

        virtual CheckResult SetProperty(const Multiname& prop_name, const Value& value);
        virtual CheckResult GetProperty(const Multiname& prop_name, Value& value);
        virtual void GetDynamicProperty(AbsoluteIndex ind, Value& value);
        virtual CheckResult DeleteProperty(const Multiname& prop_name);

//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_lengthGet, 
            mid_lengthSet, 
            mid_fixedSet, 
            mid_fixedGet, 
            mid_AS3toString, 
            mid_AS3toLocaleString, 
            mid_AS3join, 
            mid_AS3every, 
            mid_AS3forEach, 
            mid_AS3map, 
            mid_AS3push, 
            mid_AS3some, 
            mid_AS3unshift, 
            mid_AS3concat, 
            mid_AS3filter, 
            mid_AS3pop, 
            mid_AS3reverse, 
            mid_AS3shift, 
            mid_AS3slice, 
            mid_AS3sort, 
            mid_AS3splice, 
            mid_AS3indexOf, 
            mid_AS3lastIndexOf, 
        };
        void lengthGet(UInt32& result);
        void lengthSet(Value& result, UInt32 value);
        void fixedSet(Value& result, bool f);
        void fixedGet(bool& result);
        void AS3toString(ASString& result);
        void AS3toLocaleString(ASString& result);
        void AS3join(ASString& result, const ASString& separator);
        void AS3every(bool& result, const Value& checker, const Value& thisObj);
        void AS3forEach(Value& result, const Value& eacher, const Value& thisObj);
        void AS3map(Value& result, const Value& mapper, const Value& thisObj);
        void AS3push(Value& result, unsigned argc, const Value* const argv);
        void AS3some(bool& result, const Value& checker, const Value& thisObj);
        void AS3unshift(Value& result, unsigned argc, const Value* const argv);
        void AS3concat(Value& result, unsigned argc, const Value* const argv);
        void AS3filter(Value& result, const Value& checker, const Value& thisObj);
        void AS3pop(Value& result);
        void AS3reverse(Value& result);
        void AS3shift(Value& result);
        void AS3slice(Value& result, unsigned argc, const Value* const argv);
        void AS3sort(Value& result, unsigned argc, const Value* const argv);
        void AS3splice(Value& result, unsigned argc, const Value* const argv);
        void AS3indexOf(SInt32& result, const Value& value, SInt32 from);
        void AS3lastIndexOf(SInt32& result, const Value& value, SInt32 from);

//##protect##"instance$data"
    private:
        VectorBase<ValueType> V;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Vector_object : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Vector_object"; }
#endif
    public:
        Vector_object(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Vector_object> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 23 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Vector_object : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Vector_object"; }
#endif
    public:
        typedef Classes::Vector_object ClassType;

    public:
        Vector_object(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
        Vector_object(VM& vm, const ClassInfo& ci, const ClassTraits::Traits& ect);
        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;

    public:
        const ClassTraits::Traits& GetEnclosedClassTraits() const
        {
            SF_ASSERT(EnclosedClassTraits.GetPtr());
            return *EnclosedClassTraits;
        }

    private:
        SPtr<const ClassTraits::Traits> EnclosedClassTraits;
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Vector_object : public Class
    {
        friend class ClassTraits::Vector_object;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Vector_object"; }
#endif
    public:
        typedef Vector_object SelfType;
        typedef Vector_object ClassType;
        
    private:
        Vector_object(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
//##protect##"class_$methods"

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"

namespace Instances
{
    inline
    const ClassTraits::Traits& Vector_object::GetEnclosedClassTraits() const
    {
        return static_cast<const ClassTraits::Vector_object&>(GetClass().GetClassTraits()).GetEnclosedClassTraits();
    }
} // namespace Instances

//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

