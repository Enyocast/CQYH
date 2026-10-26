/**************************************************************************

Filename    :   AS3_Instance.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_Instance_H
#define INC_AS3_Instance_H


#include "AS3_Traits.h"

#ifdef GetClassInfo
// There is a define GetClassInfo in winuser.h
#undef GetClassInfo
#endif

// #define SF_AS3_ENABLE_INSTANCE_NAMESPACES

namespace Scaleform { namespace GFx { namespace AS3 
{

///////////////////////////////////////////////////////////////////////////
extern const char* NS_AS3;
extern const char* NS_flash_proxy;
extern const char* NS_Vector;

///////////////////////////////////////////////////////////////////////////
namespace InstanceTraits
{
    class Traits : public AS3::Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Traits"; }
#endif
    public:
        Traits(VM& vm, const ClassInfo& ci);
        Traits(VM& vm, const ASString& n, Pickable<Instances::Namespace> ns, Class& c, bool isDynamic);
        ~Traits();

    protected:
        Traits(VM& vm, const ASString& n, Pickable<Instances::Namespace> ns, const Traits* pt, bool isDynamic);

    public:
        // This method is not const because it is supposed to pass non-const "this"
        // into a newly created object ...
        // This method returns Value instead of Object* because primitive types 
        // have more compact representations.
        // Object initialization should be done by the AS3Constructor() method.
        // This is a default implementation.
        virtual void MakeObject(Value& result, Traits& t);

        virtual void AS3Constructor(const AS3::Traits& /*ot*/, const Value& _this, unsigned argc, const Value* argv) const;

        // Determines whether these traits implement the specified
        // interface class; implemented in InstanceTraits::UserDefined
        // This implementation is very similar to UserDefined::SupportsInterface()
        virtual bool SupportsInterface(const Traits&) const;

        const ASString& GetNameRef() const { return Name; }
        virtual ASString GetName() const;
        virtual ASString GetQualifiedName(QNameFormat f = qnfWithColons) const;

        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;

        const ArrayLH<Multiname>& GetImplementedInterfaces() const
        {
            return ImplementsInterfaces;
        }
        const Instances::Namespace& GetNamespace() const 
        { 
            return *Ns; 
        }
        const Traits* GetParent() const
        {
            return static_cast<const Traits*>(AS3::Traits::GetParent());
        }

#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
        // May be NULL.
        const Instances::Namespace* GetProtectedNamespace() const { return ProtectedNamespace; }
        void SetProtectedNamespace(Pickable<Instances::Namespace> ns);

        // Should never be NULL.
        const Instances::Namespace& GetPrivateNamespace();
#endif

	public:
		// From documentation to the *istype* opcode:
		// let valueType refer to *this* type. If valueType is the same as otherType, result
		// is true. If otherType is a base type of valueType, or an implemented interface of valueType,
		// then result is true. Otherwise result is set to false.
		bool IsParentTypeOf(const Traits& other) const;
		bool IsOfType(const Traits& other) const
		{
			return other.IsParentTypeOf(*this);
		}

    protected:
        void RegisterImplementedInterface(const Multiname& mn)
        {
            return ImplementsInterfaces.PushBack(mn);
        }

    private:
        void Init();
        static const Traits* GetParentInstanceTraits(VM& vm, const ClassInfo& ci);
        static ASString GetName(VM& vm, const ClassInfo& ci);

    private:
        ASString Name;
        SPtr<Instances::Namespace> Ns;

#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
        SPtr<Instances::Namespace> ProtectedNamespace;
        SPtr<Instances::Namespace> PrivateNamespace;
#endif

        // This member is used only by C++ Traits. AS3 Traits use Abc::Instance
        // to get info about implemented interfaces.
        ArrayLH<Multiname> ImplementsInterfaces;
    };

    // This is Traits, which cannot create objects.
    // Such paradigm is used at several places.
    class Prototype : public Traits
    {
    public:
        Prototype(VM& vm, const ClassInfo& ci);
        // This constructor is used by the Date class only.
        Prototype(VM& vm, const ASString& n, Class& c);

    public:
        virtual void MakeObject(Value& result, Traits& t);
    };

    // Doesn't belong to any class.
    // It is more like the ClassTraits::Traits.
    class Anonimous : public Prototype
    {
    public:
        Anonimous(VM& vm) : Prototype(vm, Info) {}
        static const ClassInfo Info;
    };

    class Void : public Prototype
    {
    public:
        Void(VM& vm) : Prototype(vm, Info) {}
        static const ClassInfo Info;
    };

} // namespace InstanceTraits

///////////////////////////////////////////////////////////////////////////
// Instance of a Class ...

class Instance : public AS3::Object
{
    friend class Instances::Object; // Because of Instance(VM& vm).
    
#ifdef GFX_AS3_VERBOSE
private:
    virtual const char* GetAS3ObjectType() const { return "Instance"; }
#endif
public:
    Instance(InstanceTraits::Traits& t);
    virtual ~Instance();

    // Placement new/delete.
    SF_MEMORY_DEFINE_PLACEMENT_NEW
    void  operator delete (void* ptr) { SF_FREE(ptr); }
    
private:
    Instance(VM& vm)
    : AS3::Object(vm)
    {
    }
    
public:
    virtual void Construct(Value& result, unsigned argc, const Value* argv, bool extCall = false);
    
    InstanceTraits::Traits& GetInstanceTraits()
    {
        return static_cast<InstanceTraits::Traits&>(GetTraits());
    }
    const InstanceTraits::Traits& GetInstanceTraits() const
    {
        return static_cast<const InstanceTraits::Traits&>(GetTraits());
    }
};

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_Instance_H

