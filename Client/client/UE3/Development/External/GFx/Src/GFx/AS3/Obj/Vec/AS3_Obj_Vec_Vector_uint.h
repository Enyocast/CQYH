//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Vec_Vector_uint.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Vec_Vector_uint_H
#define INC_AS3_Obj_Vec_Vector_uint_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../AS3_Obj_uint.h"
#include "AS3_Obj_Vec_VectorBase.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Vector_uint;
}

namespace InstanceTraits
{
    class Vector_uint;
}

namespace Classes
{
    class Vector_uint;
}

namespace Instances
{
    class Vector_uint : public Instances::Object
    {
        friend class InstanceTraits::Vector_uint;
        
    public:
        typedef Vector_uint SelfType;
        typedef Classes::Vector_uint ClassType;
        typedef InstanceTraits::Vector_uint TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Vector_uint"; }
#endif
    protected:
        Vector_uint(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void Append(const SelfType& other) { V.Append(other.V); }
        void Append(unsigned argc, const Value* const argv) { V.Append(argc, argv, GetEnclosedClassTraits()); }
        void Append(const Instances::Array& arr) { V.Append(arr, GetEnclosedClassTraits()); }
        void Append(const ArrayDH<UInt32>& arr) { V.Append(arr); }

        void AppendCoerce(const Instances::Array& arr) { V.AppendCoerce(arr, GetEnclosedClassTraits()); }
        bool AppendCoerce(const Value& v) { return V.AppendCoerce(v, GetEnclosedClassTraits()); }

        void PushBack(UInt32 v) { V.PushBack(v); }

        const ClassTraits::Traits& GetEnclosedClassTraits() const { return GetVM().GetClassTraitsUInt(); }
        const ArrayBase& GetArrayBase() const { return V; }

    public:
        virtual void AS3Constructor(unsigned argc, const Value* argv);

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
        void AS3pop(UInt32& result);
        void AS3reverse(Value& result);
        void AS3shift(UInt32& result);
        void AS3slice(Value& result, unsigned argc, const Value* const argv);
        void AS3sort(Value& result, unsigned argc, const Value* const argv);
        void AS3splice(Value& result, unsigned argc, const Value* const argv);
        void AS3indexOf(SInt32& result, UInt32 value, SInt32 from);
        void AS3lastIndexOf(SInt32& result, UInt32 value, SInt32 from);

//##protect##"instance$data"
    private:
        VectorBase<UInt32> V;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Vector_uint : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Vector_uint"; }
#endif
    public:
        Vector_uint(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Vector_uint> MakeInstance(Traits& t);

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
    class Vector_uint : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Vector_uint"; }
#endif
    public:
        typedef Classes::Vector_uint ClassType;

    public:
        Vector_uint(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
        Pickable<Instances::Vector_uint> MakeInstance() const
        {
            InstanceTraits::Vector_uint& itr = static_cast<InstanceTraits::Vector_uint&>(GetInstanceTraits());
            return itr.MakeInstance(itr);
        }
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Vector_uint : public Class
    {
        friend class ClassTraits::Vector_uint;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Vector_uint"; }
#endif
    public:
        typedef Vector_uint SelfType;
        typedef Vector_uint ClassType;
        
    private:
        Vector_uint(ClassTraits::Traits& t);
       
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
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

