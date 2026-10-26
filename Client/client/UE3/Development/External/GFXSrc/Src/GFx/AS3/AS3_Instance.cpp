/**************************************************************************

Filename    :   AS3_Instance.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_Instance.h"
#include "AS3_VM.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

///////////////////////////////////////////////////////////////////////////
const char* NS_AS3 = "http://adobe.com/AS3/2006/builtin";
const char* NS_flash_proxy = "http://www.adobe.com/flash/proxy";
const char* NS_Vector = "__AS3__.vec";

///////////////////////////////////////////////////////////////////////////
namespace InstanceTraits
{
    Traits::Traits(VM& vm, const ClassInfo& ci)
    : AS3::Traits(vm, GetParentInstanceTraits(vm, ci), ci.IsDynamicObject())
    , Name(GetName(vm, ci))
    , Ns(vm.MakeInternedNamespace(Abc::NS_Public, ci.PkgName))
    {
        Init();

        for (UInt8 i = 0; i < ci.InstanceMemberNum; ++i)
            AddSlot(ci.InstanceMember[i]);

        for (UInt8 i = 0; i < ci.InstanceMethodNum; ++i)
            Add2VT(ci, ci.InstanceMethod[i]);
    }

    Traits::Traits(VM& vm, const ASString& n, Pickable<Instances::Namespace> ns, const Traits* pt, bool isDynamic)
    : AS3::Traits(vm, pt, isDynamic)
    , Name(n)
    , Ns(ns)
    {
        Init();
    }
    
    Traits::Traits(VM& vm, const ASString& n, Pickable<Instances::Namespace> ns, Class& c, bool isDynamic)
    : AS3::Traits(vm, c, (c.GetParentClass() ? &c.GetParentClass()->GetInstanceTraits() : NULL), isDynamic)
    , Name(n)
    , Ns(ns)
    {
        Init();
    }

    Traits::~Traits()
    {
    }

    void Traits::Init()
    {
        // Parent traits are also InstanceTraits.
        // Copy parent's traits.
        if (GetParent())
        {
            Inherit(*GetParent());

            FirstOwnSlotInd = AbsoluteIndex(GetSlotInfoNum());
#ifdef SF_AS3_CLASS_AS_SLOT
            FixedValueSlotNumber = GetParent()->GetFixedValueSlotNumber();
#endif
        }
    }

    ASString Traits::GetName(VM& vm, const ClassInfo& ci)
    {
        return ci.IsCompileTime() ? vm.GetStringManager().CreateConstString(ci.Name) : vm.GetStringManager().CreateString(ci.Name);
    }

    void Traits::MakeObject(Value& result, Traits& t)
    {
        result = Pickable<Instances::Object>(new(t.Alloc()) Instances::Object(t));
    }

    void Traits::AS3Constructor(const AS3::Traits& /*ot*/, const Value& _this, unsigned argc, const Value* argv) const
    {
        SF_ASSERT(!_this.IsNull());
        _this.GetObject()->AS3Constructor(argc, argv);
    }

    ASString Traits::GetName() const
    {
        return Name;
    }

    void Traits::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        AS3::Traits::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<Instances::Namespace, Mem_Stat>(prcc, Ns, op SF_DEBUG_ARG(*this));
#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
        AS3::ForEachChild_GC<Instances::Namespace, Mem_Stat>(prcc, ProtectedNamespace, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC<Instances::Namespace, Mem_Stat>(prcc, PrivateNamespace, op SF_DEBUG_ARG(*this));
#endif
    }

#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
    void Traits::SetProtectedNamespace(Pickable<Instances::Namespace> ns)
    {
        ProtectedNamespace = ns;
        ProtectedNamespace->SetOwner(*this);
    }

    const Instances::Namespace& Traits::GetPrivateNamespace()
    {
        if (!PrivateNamespace)
        {
            PrivateNamespace = GetVM().MakeNamespace(Abc::NS_Private);
            PrivateNamespace->SetOwner(*this);
        }

        return *PrivateNamespace;
    }
#endif

    bool Traits::SupportsInterface(const Traits& itraits) const
    {
        VM& vm = GetVM();
        const ArrayLH<Multiname>& interfaces = GetImplementedInterfaces();

        for (UPInt i = 0; i < interfaces.GetSize(); ++i)
        {
            const ClassTraits::Traits* ctr = vm.GetRegisteredClassTraits(interfaces[i]);

			if (ctr)
			{
				InstanceTraits::Traits& itr = ctr->GetInstanceTraits();

				if (&itr == &itraits)
					return true;

				// Recursive handling of nested interfaces.
				if (itr.SupportsInterface(itraits))
					return true;
			}
        }

        return false;
    }

    ASString Traits::GetQualifiedName(QNameFormat f) const
    {
        const ASString& nsUri = GetNamespace().GetUri();
        if (nsUri.IsEmpty())
            return Name;

        if (f == qnfWithColons)
            return nsUri + "::" + Name;

        return nsUri + "." + Name;
    }

	bool Traits::IsParentTypeOf(const Traits& other) const
	{
		// let valueType refer to *this* type. If valueType is the same as otherType, result
		// is true. If otherType is a base type of valueType, or an implemented interface of valueType,
		// then result is true. Otherwise result is set to false.

		if (this == &other)
			return true;

		const Traits* tr = &other;

		while (tr)
		{
			// Check implemented interfaces.
			if (tr->SupportsInterface(*this))
				return true;

			tr = tr->GetParent();
			if (tr == this)
				return true;
		}

		return false;
	}

    const Traits* Traits::GetParentInstanceTraits(VM& vm, const ClassInfo& ci)
    {
        const ClassTraits::Traits* ctr = RetrieveParentClassTraits(vm, ci);
        const Traits* itr = NULL;

        if (ctr)
            itr = &ctr->GetInstanceTraits();

        return itr;
    }

    ///////////////////////////////////////////////////////////////////////
    void Prototype::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t);
        SF_ASSERT(false);
    }

    Prototype::Prototype(VM& vm, const ClassInfo& ci) : Traits(vm, ci)
    {
        SetConstructor(Pickable<Class>(&vm.GetClassObject(), PickValue));
    }

    Prototype::Prototype(VM& vm, const ASString& n, Class& c) 
    : Traits(vm, n, Pickable<Instances::Namespace>(&vm.GetPublicNamespace(), PickValue), c, true) // No VMAbcFile because it is supposed to be used with C++ classes only.
    {
    }

    ///////////////////////////////////////////////////////////////////////
    const ClassInfo Anonimous::Info = {ClassInfo::CompileTime, "", "", &ObjectCI, NULL};

    ///////////////////////////////////////////////////////////////////////
    const ClassInfo Void::Info = {ClassInfo::CompileTime, "void", "", &ObjectCI, NULL};

} // namespace InstanceTraits

///////////////////////////////////////////////////////////////////////////////
Instance::Instance(InstanceTraits::Traits& t) 
: AS3::Object(t)
{
    t.ConstructTail(*this);
}

Instance::~Instance()
{
    GetTraitsSafe().DestructTail(*this);
}

void Instance::Construct(Value& /*result*/, unsigned /*argc*/, const Value* /*argv*/, bool /*extCall*/)
{
    return GetVM().ThrowTypeError(VM::Error(VM::eNotConstructorError, GetVM()));
}

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

