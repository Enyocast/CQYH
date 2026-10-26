//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Namespace.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Namespace.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_QName.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"

Value::Value(Instances::Namespace* v)
: Flags(kNamespace)
, value(v)
{
    if (v)
        v->AddRef();
}

void Value::Assign(Instances::Namespace* v)
{
    Release();

    SetKind(kNamespace);
    value = v;
    if (v)
        v->AddRef();
}

void Value::AssignUnsafe(Instances::Namespace* v)
{
    SF_ASSERT(!IsRefCounted());
    SetKind(kNamespace);
    value = v;
    if (v)
        v->AddRef();
}

void Value::Pick(Instances::Namespace* v)
{
    Release();

    SetKind(kNamespace);
    value = v;
    // No AddRef() is necessary.
}

void Value::PickUnsafe(Instances::Namespace* v)
{
    SF_ASSERT(!IsRefCounted());
    SetKind(kNamespace);
    value = v;
    // No AddRef() is necessary.
}


// ***** NamespaceInstanceFactory implementation

// Alternative non-instance hash lookup key used for Instances::Namespace hash.
struct NamespaceKey
{      
    Abc::NamespaceKind Kind;
    ASString           URI;
    NamespaceKey(const NamespaceKey &src) : Kind(src.Kind), URI(src.URI) { }
    NamespaceKey(Abc::NamespaceKind kind, const ASString& uri) : Kind(kind), URI(uri) { }
};

bool operator == (Instances::Namespace* ns, const NamespaceKey &key)
{
    return (ns->GetKind() == key.Kind) && (ns->GetUri() == key.URI);
}

// NamespaceInstanceFactory is responsible for creating interned Instances::Namespace objects.
// Factory maintains a hash-table of weak references, which are removed when Namespace objects
// are garbage collected (i.e. their destructor is called).
// NamespaceInstanceFactory uses non-GCs reference counting on purpose, to avoid being
// a part of collection cycle.

// By SS:
// There is one problem with the NamespaceInstanceFactory class. If a namespace is created by calling
// to MakeNamespace() and not stored anywhere (and as a result not visited by a garbage collector)
// it will prevent garbage collector from cleaning up of namespace object and cause memory
// leaks.
class NamespaceInstanceFactory : public RefCountBase<NamespaceInstanceFactory, StatMV_VM_ITraits_Mem>
{
    friend class InstanceTraits::Namespace;

public:
    NamespaceInstanceFactory(InstanceTraits::Namespace * nsInstanceTraits)
        : pNamespaceInstanceTraits(nsInstanceTraits)
    { }    
    ~NamespaceInstanceFactory()
    {
    }

    Pickable<Instances::Namespace> MakeNamespace(Abc::NamespaceKind kind, const ASString& uri,
        const Value& prefix)
    {
        NamespaceKey key(kind, uri);
        Instances::Namespace*   ns = 0;

        if (!NamespaceSet.GetAlt(key, &ns))
        {
            // MakeNamespace call not allowed after Traits are destroyed.
            SF_ASSERT(pNamespaceInstanceTraits); 

            Pickable<Instances::Namespace> result = pNamespaceInstanceTraits->MakeInstance(kind, uri, prefix);
            NamespaceSet.Add(result.GetPtr());
            return result;
        }

        return Pickable<Instances::Namespace>(ns, PickValue);
    }

    Instances::Namespace& GetNamespace(Abc::NamespaceKind kind, const ASString& uri,
        const Value& prefix)
    {
        SF_UNUSED(prefix);
        NamespaceKey key(kind, uri);
        Instances::Namespace*   ns = 0;

        if (!NamespaceSet.GetAlt(key, &ns))
        {
            SF_ASSERT(false);
            if (pNamespaceInstanceTraits)
                return pNamespaceInstanceTraits->GetVM().GetPublicNamespace();
        }

        return *ns;
    }

    void AddNamespace(Instances::Namespace& ns)
    {
        NamespaceSet.Add(&ns);
    }
    void RemoveNamespace(Instances::Namespace& ns)
    {
        NamespaceSet.Remove(&ns);
    }

private:
    // Debugging-only.
    void onNamespaceTraitsDestroy() { pNamespaceInstanceTraits = 0; }

private:
    class NamespaceHashFunc
    {
    public:        
        // Hash code is stored right in the node
        UPInt  operator() (const Instances::Namespace*const& ns) const { return ns->GetHash(); }
        UPInt  operator() (const NamespaceKey &str) const
        {
            return Instances::Namespace::CalcHash(str.Kind, str.URI);
        }
        // Hash update - unused.
        static UPInt    GetCachedHash(const Instances::Namespace*& ns)            { return ns->GetHash(); }
        static void     SetCachedHash(Instances::Namespace*& ns, UPInt hashValue) { SF_UNUSED2(ns, hashValue); }
        static Instances::Namespace*&       GetValue(Instances::Namespace*& ns)              { return ns; }
        static const Instances::Namespace*& GetValue(const Instances::Namespace*& ns)        { return ns; }
    };

    typedef HashSetUncachedLH<Instances::Namespace*, NamespaceHashFunc, 
        NamespaceHashFunc, Stat_Default_Mem>  NamespacePtrHashType;

    NamespacePtrHashType       NamespaceSet;
    InstanceTraits::Namespace *pNamespaceInstanceTraits;
};

///////////////////////////////////////////////////////////////////////////////
namespace Instances
{
    Namespace::Namespace(VM& vm, Abc::NamespaceKind kind, const char* uri)
    : GASRefCountBase(&vm.GetGC())
    , Kind(kind)
    , IsInterface(false)
    , VMRef(vm)
    , Uri(vm.GetStringManager().CreateConstString(uri))
    {
    }

    Namespace::Namespace(
        VM& vm,
        NamespaceInstanceFactory* factory,
        Abc::NamespaceKind kind,
        const ASString& uri,
        const Value& prefix
        )
    : GASRefCountBase(&vm.GetGC())
    , Kind(kind)
    , IsInterface(false)
    , VMRef(vm)
    , Uri(uri)
    , pFactory(factory)
    , Prefix(prefix)
    {
    }

    Namespace::~Namespace()
    {
        // Remove weak reference to us from factory, if we were added there.
        if (pFactory)
            pFactory->RemoveNamespace(*this);
    }

    void Namespace::SetUri(const Value& value)
    {
        VM& vm = GetVM();

        const Traits& tr = vm.GetValueTraits(value);
        if (tr.GetTraitsType() == Traits_QName && tr.IsInstanceTraits())
        {
            // If the value is a QName object, the uri property is set to the uri property of the QName object.
            if (value.GetObject())
            {
                Instances::QName& qname = static_cast<Instances::QName&>(*value.GetObject());

                SetUri(qname.GetUri());
            }
        } else
        {
            // Otherwise, the uriValue parameter is converted to a string and assigned to the uri property.
            value.Convert2String(Uri).DoNotCheck();
        }
    }

    void Namespace::AS3Constructor(unsigned argc, const Value* argv)
    {
        VM& vm = GetVM();

        // If no value is passed, the prefix and uri properties are set to an empty string.
        switch(argc)
        {
        case 0:
            SetPrefix(vm.GetStringManager().CreateEmptyString());
            break;
        case 1:
            {
                SetPrefix(vm.GetStringManager().CreateEmptyString());
                const Value& v = argv[0];
                if (v.IsNamespace())
                    // If the value is a Namespace object, a copy of the object is created.
                    *this = v.AsNamespace();
                else if (v.IsObject() && v.GetObject() &&
                    v.GetObject()->GetTraits().GetTraitsType() == Traits_QName &&
                    v.GetObject()->GetTraits().IsInstanceTraits()
                    )
                {
                    const Instances::QName* inst = static_cast<const Instances::QName*>(v.GetObject());
                    SetUri(inst->GetUri());
                }
                else
                    SetUri(v);
            }
            break;
        default:
            // Two and more arguments ...
            {
                const Value& vp = argv[0];
                const Value& vu = argv[1];
                StringManager& sm = vm.GetStringManager();
                ASString p = sm.CreateEmptyString();
                ASString u = sm.CreateEmptyString();

                vp.Convert2String(p).DoNotCheck();
                vu.Convert2String(u).DoNotCheck();

                if (!p.IsEmpty() && u.IsEmpty())
                    return vm.ThrowTypeError(VM::Error(VM::eXMLNamespaceWithPrefixAndNoURI, vm SF_DEBUG_ARG(p)));

#if 0
                // First argument prefixValue ...
                if (argv[0].IsUndefined())
                {
                    // If undefined is passed, prefix is set to undefined.
                    SetPrefix(argv[0]);
                } else
                {
                    //SF_ASSERT(false); // Not implemented yet ...

                    // If the value is a valid XML name, as determined by the isXMLName() function, it is converted to a string and assigned to the prefix property.

                    // If the value is not a valid XML name, the prefix property is set to undefined.

                    // Set Prefix to undefined for the time being.
                    SetPrefix(Value::GetUndefined());
                }
#else
                // First argument prefixValue ...
                SetPrefix(vp);
#endif

                // Second argument uriValue ...
                SetUri(vu);
            }
            break;
        }
    }

    Namespace& Namespace::operator =(const Namespace& other)
    {
        if (this != &other)
        {
            Prefix = other.Prefix;
            Uri = other.Uri;
            Kind = other.Kind;
            pFactory = other.pFactory;
        }

        return *this;
    }

    void Namespace::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        AS3::ForEachChild_GC(prcc, Prefix, op SF_DEBUG_ARG(*this));
#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
        AS3::ForEachChild_GC<AS3::Traits, Mem_Stat>(prcc, pOwner, op SF_DEBUG_ARG(*this));
#endif
    }

}

//##protect##"methods"

namespace InstanceTraits
{
    const ThunkInfo Namespace::ti[Namespace::ThunkInfoNum] = {
        {&InstanceTraits::Namespace::prefixGet, NULL, "prefix", NULL, CT_Get, 0, 0},
        {&InstanceTraits::Namespace::uriGet, &StringCI, "uri", NULL, CT_Get, 0, 0},
        {&InstanceTraits::Namespace::AS3valueOf, &StringCI, "valueOf", NS_AS3, CT_Method, 0, 0},
        {&InstanceTraits::Namespace::AS3toString, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
    };

    Namespace::Namespace(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Namespace::Namespace()"
        SetTraitsType(Traits_Namespace);
        pNamespaceFactory = *SF_HEAP_NEW(vm.GetMemoryHeap()) NamespaceInstanceFactory(this);        
//##protect##"InstanceTraits::Namespace::Namespace()"

    }

    void Namespace::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t); SF_ASSERT(false);
    }

    void Namespace::prefixGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::prefixGet()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsNamespace())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = _this.AsNamespace().GetPrefix();
//##protect##"InstanceTraits::prefixGet()"
    }
    void Namespace::uriGet(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::uriGet()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsNamespace())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = _this.AsNamespace().GetUri();
//##protect##"InstanceTraits::uriGet()"
    }
    void Namespace::AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3valueOf()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsNamespace())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = _this.AsNamespace().GetUri();
//##protect##"InstanceTraits::AS3valueOf()"
    }
    void Namespace::AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::AS3toString()"
        SF_UNUSED3(ti, argc, argv);

        // This method is not generic.
        if (!_this.IsNamespace())
            return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

        result = _this.AsNamespace().GetUri();
//##protect##"InstanceTraits::AS3toString()"
    }
    void Namespace::valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::valueOfProto()"
        toStringProto(ti, vm, _this, result, argc, argv);
//##protect##"InstanceTraits::valueOfProto()"
    }
    void Namespace::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"InstanceTraits::toStringProto()"
        SF_UNUSED3(ti, argc, argv);

        if (_this.IsObject() && _this.GetObject())
        {
            const AS3::Object& o = *_this.GetObject();
            if (&o == &vm.GetClassNamespace().GetPrototype())
            {
                // This method is called on a prototype object.
                result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
                return;
            }
        }
        else if (_this.IsNamespace())
        {
            result = _this.AsNamespace().GetUri();
            return;
        }

        vm.ThrowTypeError(VM::Error(VM::eUndefinedVarError, vm));
//##protect##"InstanceTraits::toStringProto()"
    }
//##protect##"instance_traits$methods"

    Namespace::~Namespace()
    {
        // Notify factory of our destruction for debug error checking.
        pNamespaceFactory->onNamespaceTraitsDestroy();
    }

    Pickable<Instances::Namespace> Namespace::MakeInternedInstance(Abc::NamespaceKind kind, const ASString& uri,
                                                         const Value& prefix)
    {
        return pNamespaceFactory->MakeNamespace(kind, uri, prefix);
    }

    Instances::Namespace& Namespace::GetInternedInstance(Abc::NamespaceKind kind, const ASString& uri,
        const Value& prefix)
    {
        return pNamespaceFactory->GetNamespace(kind, uri, prefix);
    }

//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    const ThunkInfo Namespace::ti[Namespace::ThunkInfoNum] = {
        {&InstanceTraits::Namespace::valueOfProto, &StringCI, "valueOf", NULL, CT_Method, 0, 0},
        {&InstanceTraits::Namespace::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    Namespace::Namespace(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Namespace::Namespace()"
//##protect##"class_::Namespace::Namespace()"
    }

    void Namespace::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void Namespace::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    void Namespace::Construct(Value& result, unsigned argc, const Value* argv, bool /*extCall*/)
    {
#if 0
        InstanceTraits::Namespace& itr = static_cast<InstanceTraits::Namespace&>(GetClassTraits().GetInstanceTraits());
        Pickable<Instances::Namespace> inst = itr.MakeInternedInstance(Abc::NS_Public, GetStringManager().CreateEmptyString());
        inst->AS3Constructor(argc, argv);
        result = inst;
#else
        InstanceTraits::Namespace& itr = static_cast<InstanceTraits::Namespace&>(GetClassTraits().GetInstanceTraits());
        Pickable<Instances::Namespace> inst = itr.MakeInstance(Abc::NS_Public, GetStringManager().CreateEmptyString(), Value::GetUndefined());
        inst->AS3Constructor(argc, argv);
        itr.pNamespaceFactory->AddNamespace(*inst);
        result = inst;
#endif
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    Namespace::Namespace(VM& vm)
    : Traits(vm, NamespaceCI)
    {
//##protect##"ClassTraits::Namespace::Namespace()"
        SetTraitsType(Traits_Namespace);
//##protect##"ClassTraits::Namespace::Namespace()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Namespace(vm, NamespaceCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Namespace(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Namespace::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Namespace(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NamespaceCI = {
    ClassInfo::CompileTime,
    "Namespace", "", &ObjectCI,
    ClassTraits::Namespace::MakeClassTraits,
    0,
    0,
    InstanceTraits::Namespace::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Namespace::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

