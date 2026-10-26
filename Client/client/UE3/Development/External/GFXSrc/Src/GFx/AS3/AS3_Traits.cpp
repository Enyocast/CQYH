/**************************************************************************

Filename    :   AS3_Traits.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_VM.h"
#include "AS3_Traits.h"
#include "AS3_VTable.h"
#include "AS3_Marshalling.h"
#include "Obj/AS3_Obj_Namespace.h"
#include "Obj/AS3_Obj_UserDefined.h"

namespace Scaleform { namespace GFx { namespace AS3
{

///////////////////////////////////////////////////////////////////////////
inline
SlotInfo::BindingType GetDataType(TCodeType ct)
{
    SlotInfo::BindingType dt = SlotInfo::BT_Code;
    
    switch (ct)
    {
    case CT_Method:
        dt = SlotInfo::BT_Code;
        break;
    case CT_Get:
        dt = SlotInfo::BT_Get;
        break;
    case CT_Set:
        dt = SlotInfo::BT_Set;
        break;
    }

    return dt;
}

///////////////////////////////////////////////////////////////////////////
#ifdef SF_AS3_ENABLE_SLOTS2

void Slots::SetSlotInfo(AbsoluteIndex ind, const ASString& name, const SlotInfo& v)
{
    SF_ASSERT(ind.IsValid());
    SF_ASSERT(ind.Get() >= FirstOwnSlotNum);

    VArray[ind.Get() - FirstOwnSlotNum].Value = v;
    SetKey(ind, name);
}

#else

void Slots::SetSlotInfo(AbsoluteIndex ind, const ASString& name, const SlotInfo& v)
{
    SF_ASSERT(ind.IsValid());
    
    SlotContainer[ind] = v;
    SlotContainer.SetKey(ind, name);
}

#endif

#ifdef SF_AS3_ENABLE_SLOTS2
void Slots::Inherit(const Slots& parent)
{
    Parent = &parent;
    FirstOwnSlotNum = parent.GetSlotInfoNum();
    Set = parent.Set;
}

void Slots::SetKey(AbsoluteIndex ind, const ASString& k)
{
    SF_ASSERT(ind.Get() >= FirstOwnSlotNum);
    const UPInt index = ind.Get() - FirstOwnSlotNum;

    if (VArray[index].Key == k.GetNode())
        // The same key.
        return;

    // Set new value.
    {
        ASStringNode* node = k.GetNode();
        SF_ASSERT(ASString(VArray[index].Key) == k.GetManager()->CreateEmptyString());
        VArray[index].Key = node;
        SetType::Iterator it = Set.Find(node);

        if (it.IsEnd())
        {
            Set.Add(node, static_cast<UInt32>(index + FirstOwnSlotNum));
            VArray[index].Prev = -1;
        }
        else
        {
            const SPInt cur_ind = it->Second;
            VArray[index].Prev = cur_ind;
            it->Second = static_cast<UInt32>(index + FirstOwnSlotNum);
        }
    }
}

Scaleform::GFx::AS3::AbsoluteIndex Slots::Add(const ASString& k, const ValueType& v)
{
    UPInt result;

    result = VArray.GetSize();
    VArray.PushBack(VArrayType::ValueType(v, k.GetNode()));

    ASStringNode* node = k.GetNode();

    const SPInt index = static_cast<SPInt>(result);
    SetType::Iterator it = Set.Find(node);
    if (it.IsEnd())
    {
        Set.Add(node, static_cast<UInt32>(index + FirstOwnSlotNum));
        VArray[index].Prev = -1;
    }
    else
    {
        const SPInt cur_ind = it->Second;
        VArray[index].Prev = cur_ind;
        it->Second = static_cast<UInt32>(index + FirstOwnSlotNum);
    }

    return AbsoluteIndex(result + FirstOwnSlotNum);
}
#endif

AbsoluteIndex Slots::FindSlotInfoIndex(const ASString& name, const Instances::Namespace& ns) const
{
    // Namespace must match for find to succeed, since an object
    // can have identically named slots from different namespaces.
    const SetType::ValueType *values = FindSlotValues(name);
    if (values)
    {
        for (SPInt ind = *values; ind >= 0; ind = GetPrevSlotIndex(ind))
        {
            const AbsoluteIndex index(ind);
            const SlotInfo& si = GetSlotInfo(index);
            const Instances::Namespace& cur_ns = si.GetNamespace();

            if (cur_ns.GetKind() == ns.GetKind())
            {
                switch (ns.GetKind())
                {
                case Abc::NS_Protected:
                    return index;
                case Abc::NS_Private:
                    if (&ns == &cur_ns)
                        return index;
                    break;
                default:
                    if (cur_ns.GetUri() == ns.GetUri())
                        return index;
                    break;
                }
            }
        }
    }

    return AbsoluteIndex(-1);
}

SlotInfo& Slots::FindAddOwnSlotInfo(const ASString& name, const SlotInfo& v, AbsoluteIndex& ind)
{    
    ind = FindSlotInfoIndex(name, v.GetNamespace());

    if (!ind.IsValid())
        ind = Add(name, v);

    return GetOwnSlotInfo(ind);
}

///////////////////////////////////////////////////////////////////////////
Traits::Traits(VM& _vm, Class& c, const Traits* pt, bool isDynamic)
: GASRefCountBase(&_vm.GetGC())
, FirstOwnSlotInd(0)
, FixedValueSlotNumber(0)
, MemSize(0)
, Flags(0)
, TraitsType(pt ? pt->GetTraitsType() : Traits_Unknown)
, pVM(&_vm)
, pConstructor(&c)
, pParent(pt)
, InitScope(_vm.GetMemoryHeap())
{
    /* DO NOT delete.
    // These are default values any way. 
    SetIsInterface(false);
    SetHasTail(false);
    SetIsAbcObject(false);
    */

    SetArrayLike(pt ? pt->IsArrayLike() : false); // Inherit *ArrayLike* from the parent.
    SetDynamicType(isDynamic);
    SetDeleteLast();
}

Traits::Traits(VM& _vm, const Traits* pt, bool isDynamic)
: GASRefCountBase(&_vm.GetGC())
, FirstOwnSlotInd(0)
, FixedValueSlotNumber(0)
, MemSize(0)
, Flags(0)
, TraitsType(pt ? pt->GetTraitsType() : Traits_Unknown)
, pVM(&_vm)
, pConstructor(NULL)
, pParent(pt)
, InitScope(_vm.GetMemoryHeap())
{
    /* DO NOT delete.
    // These are default values any way. 
    SetIsInterface(false);
    SetHasTail(false);
    SetIsAbcObject(false);
    */

    SetArrayLike(pt ? pt->IsArrayLike() : false); // Inherit *ArrayLike* from the parent.
    SetDynamicType(isDynamic);
    SetDeleteLast();
}

Traits::Traits(VM& _vm)
: GASRefCountBase(&_vm.GetGC())
, FirstOwnSlotInd(0)
, FixedValueSlotNumber(0)
, MemSize(0)
, Flags(0)
, TraitsType(Traits_Unknown)
, pVM(&_vm)
, pConstructor(NULL)
, pParent(NULL)
, InitScope(_vm.GetMemoryHeap())
{
    /* DO NOT delete.
    // This is a default value any way. 
    SetArrayLike(false);
    SetIsInterface(false);
    SetObjectType(SealedObject);
    SetHasTail(false);
    SetAbcObject(false);
    */
    SetDeleteLast();
}

Traits::~Traits()
{
}

bool Traits::IsGlobal() const
{
    return false;
}

CheckResult Traits::SetupSlotValues(Object& /*for_obj*/) const
{
    return true;
}

void* Traits::Alloc() const
{
    unsigned size = GetMemSize();
#if 1
    const AllocInfo ainfo(StatMV_VM_Instance_Mem, __FILE__, __LINE__);
    return Memory::AllocInHeap(GetVM().GetMemoryHeap(), size, ainfo);
#else
    return Memory::AllocInHeap(GetVM().GetMemoryHeap(), size);
#endif
}

struct VarInfo
{
    VarInfo() : _1(0), _4(0), _8(0), _value(0) {}

    unsigned _1;
    unsigned _4;
    unsigned _8;
    unsigned _value;
};

// Return new aligned offset. Align must be power of two.
template <int A>
inline
unsigned AlignMem(unsigned offset)
{
    const unsigned a = A - 1;
    return (offset + a) & ~a;
}

CheckResult Traits::SetupSlotValues(VMAbcFile& file, const Abc::HasTraits& t, Object& for_obj) const
{
    using namespace Abc;

    InitializerGuard __(GetVM());

    // *t* is relative because it is specific to the object and does not include inheritance ...
    //for(RelativeIndex rel_ind(0); rel_ind.Get() < t.GetTraitsCount(); ++rel_ind)
    // *i* is absolute for Abc::HasTraits, but it is relative in current traits.
    for(AbsoluteIndex i(0); i.Get() < t.GetTraitsCount(); ++i)
    {
        const TraitInfo& trait_info = t.GetTraitInfo(file.GetTraits(), i);
        
        switch(trait_info.GetType())
        {
        case TraitInfo::tSlot:
        case TraitInfo::tConst:
        {
            Abc::Multiname mn = trait_info.GetName(file.GetConstPool());
            SlotInfo* si = const_cast<SlotInfo*>(FindSlotInfo(file, mn));

            if (si)
            {
                // If we have a value ...
                if (trait_info.HasDefaultValue())
                {
                    if (!si->SetSlotValue(GetVM(), file.GetDetailValue(trait_info.GetDefaultValue()), &for_obj))
                        return false;
                }
                else
                {
                    Abc::Multiname mn = trait_info.GetTypeName(file.GetAbcFile());

                    if (!si->SetSlotValue(GetVM(), GetVM().GetDefaultValue(file, mn), &for_obj))
                        return false;
                }
            }
            else
                SF_ASSERT(false);
        }
            break;
        case TraitInfo::tMethod:
        case TraitInfo::tGetter:
        case TraitInfo::tSetter:
        {
            // !!!
            // When creating the new function object the scope stack used is the current scope stack when
            // this instruction is executed, and the body is the method_body entry that references the
            // specified method_info entry.
//              const int method_ind = trait_info.AsMethod().GetMethodInd();
//              const Value value = GetVM().ClassMethodClosure->MakeInstance(method_ind, for_obj);
//
//              AddVT(GetVT(), si, value);
        }
            break;
        case TraitInfo::tFunction:
        {
            // !!!
            // When creating the new function object the scope stack used is the current scope stack when
            // this instruction is executed, and the body is the method_body entry that references the
            // specified method_info entry.
//              const int method_ind = trait_info.AsFunction().GetMethodInd();
//              const Value value = GetVM().ClassFunction->MakeInstance(method_ind, for_obj);
//              
//              AddVT(GetVT(), si, value);
        }
            break;
        case TraitInfo::tClass:
            //SF_ASSERT(false);
            // It looks like nothing to initialize.
            break;
        default:
            SF_ASSERT(false);
            break;
        }
    }

    return true;
}

void Traits::AddInterfaceSlots(VMAbcFile& file, const Abc::ClassInfo& class_info)
{
    const Abc::Instance& instance = class_info.GetInstanceInfo();
    const Abc::Instance::Interfaces& interfaces = instance.GetInterfaces();
    VM& vm = GetVM();

    for (UPInt i = 0; i < interfaces.GetSize(); ++i)
    {
        const Multiname interfaceMN(file, interfaces.GetName(file.GetConstPool(), AbsoluteIndex(i)));

        // DO NOT RegisterImplementedInterface() on purpose.
        // We will save some memory by using an overloaded method SupportsInterface()
        //RegisterImplementedInterface(interfaceMN);

        const ClassTraits::Traits* ctraits = vm.GetRegisteredClassTraits(interfaceMN);
        if (!ctraits)
            ctraits = AS3::FindGOTraits(GetVM(), GetVM().GetGlobalObjects(), interfaceMN);

        if (!ctraits || !ctraits->IsValid())
            return GetVM().ThrowVerifyError(VM::Error(VM::eClassNotFoundError, GetVM() 
                SF_DEBUG_ARG(interfaceMN.GetName())
                ));

        const InstanceTraits::Traits& itraits = ctraits->GetInstanceTraits();

        CIterator it = itraits.Begin();
        for (; !it.IsEnd(); ++it)
        {
            ASString        interfaceSlotName(it.GetSlotName());
            const SlotInfo& interfaceSlot = it.GetSlotInfo();

            // For each interface slot, we see if has already been added. If it is, as is the
            // case for 'constructor' and perhaps multiple interface use, no change is necessary.
            // If not, we find the method declared in 'public' namespace of the class and
            // create an alias to it for interface namespace.

            const SlotInfo* thisSlot = FindSlotInfo(interfaceSlotName, interfaceSlot.GetNamespace());
            if (!thisSlot)
            {
                thisSlot = FindSlotInfo(interfaceSlotName, vm.GetPublicNamespace());
                if (thisSlot)
                {
                    // Interface slot was added/overridden in public namespace.
                    // Let us add an alias.
                    // What should we do about protected and private namespaces.

                    // Just thisSlot->setNamespace() below won't work.
                    //thisSlot->setNamespace(interfaceSlot.GetNamespace());

                    SlotInfo newSlot(*thisSlot);
                    newSlot.setNamespace(interfaceSlot.GetNamespace());
                    AddSlotInfo(interfaceSlotName, newSlot);
                }
                else
                {
                    if (instance.IsInterface())
                    {
                        // Add this slot/code.
                        SlotInfo::BindingType binding_type = interfaceSlot.GetBindingType();
                        AbsoluteIndex ind(-1);

                        // This slot is an interface method. Let's mark slot's
                        // namespace as an "IsInterface" namespace.
                        const_cast<Instances::Namespace&>(interfaceSlot.GetNamespace()).SetIsInterface();

                        SlotInfo& si = FindAddOwnSlotInfo(
                            interfaceSlotName, 
                            interfaceSlot,
                            ind
                            );

                        // Initialize a virtual table ...
                        // Add2VT will also bind the slot.
                        // Add2VT(si, vt_value, binding_type);

                        // Code in this block is a part of the Add2VT() method.
                        {
                            switch (binding_type)
                            {
                            case SlotInfo::BT_Code:
                            case SlotInfo::BT_Get:
                                {
                                    const Value& vt_value = itraits.GetVT().GetRaw(interfaceSlot.GetAValueInd());

                                    // Add a new record to the virtual table ...
                                    si.Bind(binding_type, GetVT().AddMethod(vt_value, binding_type SF_DEBUG_ARG(si.GetName())));
                                }
                                break;
                            case SlotInfo::BT_Set:
                                {
                                    const Value& vt_value = itraits.GetVT().GetRaw(interfaceSlot.GetAValueInd() + 1);

                                    // Add a new record to the virtual table ...
                                    si.Bind(binding_type, GetVT().AddMethod(vt_value, binding_type SF_DEBUG_ARG(si.GetName())));
                                }
                                break;
                            case SlotInfo::BT_GetSet:
                                // Add BT_Get part.
                                {
                                    binding_type = SlotInfo::BT_Get;
                                    const Value& vt_value = itraits.GetVT().GetRaw(interfaceSlot.GetAValueInd());

                                    // Add a new record to the virtual table ...
                                    si.Bind(binding_type, GetVT().AddMethod(vt_value, binding_type SF_DEBUG_ARG(si.GetName())));
                                }
                                // Add BT_Set part.
                                {
                                    binding_type = SlotInfo::BT_Set;
                                    const Value& vt_value = itraits.GetVT().GetRaw(interfaceSlot.GetAValueInd() + 1);

                                    // Add a new record to the virtual table ...
                                    si.Bind(binding_type, GetVT().AddMethod(vt_value, binding_type SF_DEBUG_ARG(si.GetName())));
                                }
                                break;
                            default:
                                SF_ASSERT(false);
                            };
                        }
                    }
                    else
                    {
                        // Class instance doesn't implement all traits of the interface!
                        // TBD: message with class, interface, and method name.
                        return GetVM().ThrowVerifyError(VM::Error(VM::eIllegalInterfaceMethodBodyError, GetVM()
                            SF_DEBUG_ARG(interfaceSlotName.ToCStr())
                            ));
                    }
                }
            }
            /* For debugging.
            else
                SF_ASSERT(false);
            */
        }

        // Do the same thing recursively for parent interfaces, if we have any.
        // The loop enough is not enough to propagate all the traits through interface
        // chain, since it only aliases slots that are overridden in the derived interface.
        const InstanceTraits::Traits* parent_tr = itraits.GetParent();
        if (parent_tr && parent_tr->IsAbcObject())
        {
            const Abc::ClassInfo& baseiClassInfo = static_cast<const InstanceTraits::UserDefined&>(*parent_tr).GetClassInfo();

            AddInterfaceSlots(file, baseiClassInfo);
        }
    }
}

void Traits::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
{
    Slots::ForEachChild_GC(prcc, op SF_DEBUG_ARG(*this));
    AS3::ForEachChild_GC<Class, Mem_Stat>(prcc, pConstructor, op SF_DEBUG_ARG(*this));
    AS3::ForEachChild_GC_Const<const Traits, Mem_Stat>(prcc, pParent, op SF_DEBUG_ARG(*this));
    
    if (pVTable)
        pVTable->ForEachChild_GC(prcc, op);

    AS3::ForEachChild_GC(prcc, InitScope, op SF_DEBUG_ARG(*this));
}

void Traits::ForEachChild_GC(Collector* prcc, const Object& obj, RefCountBaseGC<Mem_Stat>::GcOp op) const
{
    AbsoluteIndex count(GetSlotInfoNum());
    
    for(AbsoluteIndex i(0); i < count; ++i)
        GetSlotInfo(i).ForEachChild_GC(prcc, obj, op);
}

SlotInfo::BindingType Traits::GetBindingType(VMAbcFile& file, const Abc::Multiname& mn) const
{
    VM& vm = GetVM();
    SlotInfo::BindingType result;

    if (&mn == &file.GetConstPool().GetAnyType())
    {
        // This is ANY type (Value).
        result = SlotInfo::BT_Value;
    }
    else
    {
        const ClassTraits::Traits* ct = vm.Resolve2ClassTraits(file, mn);

        if (ct)
        {
            const BuiltinTraitsType tt = ct->GetTraitsType();

            switch (tt)
            {
            case Traits_Boolean:
                result = SlotInfo::BT_Boolean;
                break;
            case Traits_SInt:
                result = SlotInfo::BT_Int;
                break;
            case Traits_UInt:
                result = SlotInfo::BT_UInt;
                break;
            case Traits_Number:
                result = SlotInfo::BT_Number;
                break;
            case Traits_String:
                result = SlotInfo::BT_String;
                break;
            case Traits_Function:
                // Function can actually be method closure.
                result = SlotInfo::BT_Value;
                break;
            default:
                if (vm.IsObject(*ct))
                    // Primitive types may be assigned to Object.
                    result = SlotInfo::BT_Value;
                else
                    result = SlotInfo::BT_ObjectAS;
            };
        }
        else
            result = SlotInfo::BT_Value;
    }

    return result;
}

CheckResult Traits::AddSlots(const Abc::HasTraits& traits, VMAbcFile& file, unsigned parent_size)
{
    bool result = true;
    VM& vm = file.GetVM();

    // Slots, which have an ID.
    for(AbsoluteIndex i(0); i.Get() < traits.GetTraitsCount(); ++i)
    {
        const Abc::TraitInfo& trait_info = traits.GetTraitInfo(file.GetTraits(), i);

        // Filter out slots with no ID.
        if (!trait_info.HasSlotID())
            continue;

        const Abc::Multiname& mn = trait_info.GetName(file.GetConstPool());
        // slot_id == 0 means "auto-assign slot" ...
        const SlotIndex slot_id(trait_info.GetSlotID());
        
        // Filter out slots with ID set to 0.
        if (!slot_id.IsValid())
            continue;

#ifdef SF_AS3_CLASS_AS_SLOT
        SlotInfo::BindingType binding_type = SlotInfo::BT_ValueArray;
#else
        SlotInfo::BindingType binding_type = SlotInfo::BT_Unknown;
#endif

        const AbsoluteIndex offset(-1);

        bool _const = false;

        // Get binding_type.
        switch(trait_info.GetType())
        {
        case Abc::TraitInfo::tClass:
        case Abc::TraitInfo::tConst:
            _const = true;
        case Abc::TraitInfo::tSlot:
            binding_type = GetBindingType(file, trait_info.GetTypeName(file.GetAbcFile()));
            break;
        case Abc::TraitInfo::tMethod:
            binding_type = SlotInfo::BT_Code;
            break;
        case Abc::TraitInfo::tGetter:
            binding_type = SlotInfo::BT_Get;
            break;
        case Abc::TraitInfo::tSetter:
            binding_type = SlotInfo::BT_Set;
            break;
        case Abc::TraitInfo::tFunction:
            // Theoretically, functions should be stored as regular members
            // and should go into virtual table.
            binding_type = SlotInfo::BT_Code;
            break;
        default:
            SF_ASSERT(false);
            break;
        }

        /* DO NOT delete this code.
        // Try to resolve type in place.
        // This doesn't work because of dependencies.
        const ClassTraits::Traits* tr = NULL;
        if (trait_info.IsData())
        {
            const Abc::Multiname& tmn = trait_info.GetTypeName(file.GetAbcFile());
            tr = GetVM().Resolve2ClassTraits(file, tmn);
            SF_ASSERT(tr);
        }
        */

        const ASString mn_name = file.GetInternedString(mn.GetNameInd());
        RelativeIndex ind(slot_id);

        // We do not use ClassTraits::Traits here because we want to postpone name resolution.
        // Otherwise we will get problems with dependencies.
        // We use AddSetSlot() here because indices can be out of order.
        SlotInfo& si = AddSetSlot(
            ind, 
            mn_name,
            Pickable<Instances::Namespace>(&file.GetInternedNamespace(mn), PickValue),
            file,
            trait_info,
            _const
            );

        if (trait_info.HasMethodInd())
        {
            if (SlotInfo::IsValidCodeBT(si.GetBindingType()))
            {
                // Initialize a virtual table ...
                // Add2VT will also bind the slot.
                Add2VT(si, Value(trait_info.GetMethodInd()), binding_type);
            }
            else
                result = false;
        }
        else
        {
            if (si.GetBindingType() == SlotInfo::BT_Unknown)
                si.Bind(binding_type, offset);
            else
                result = false;
        }

        if (!result)
        {
            vm.ThrowVerifyError(VM::Error(VM::eIllegalOverrideError, vm
                SF_DEBUG_ARG(mn_name.ToCStr())
                SF_DEBUG_ARG(GetName().ToCStr())
                ));

            break;
        }
    }

    if (!result)
        return result;

    // Slots, which do not have an ID.
    for(AbsoluteIndex i(0); i.Get() < traits.GetTraitsCount(); ++i)
    {
        const Abc::TraitInfo& trait_info = traits.GetTraitInfo(file.GetTraits(), i);

        // Filter out slots with ID.
        if (trait_info.HasSlotID())
        {
            // slot_id == 0 means "auto-assign slot" ...
            const SlotIndex slot_id(trait_info.GetSlotID());

            if (slot_id.IsValid())
                // This case should be already handled.
                continue;
        }

#ifdef SF_AS3_CLASS_AS_SLOT
        SlotInfo::BindingType binding_type = SlotInfo::BT_ValueArray;
#else
        SlotInfo::BindingType binding_type = SlotInfo::BT_Unknown;
#endif
        const Abc::Multiname& mn = trait_info.GetName(file.GetConstPool());
        const AbsoluteIndex offset(trait_info.HasMethodInd() ? -1 : static_cast<SPInt>(FixedValueSlotNumber++));
        bool _const = false;

        // Get binding_type.
        switch(trait_info.GetType())
        {
        case Abc::TraitInfo::tClass:
        case Abc::TraitInfo::tConst:
            _const = true;
        case Abc::TraitInfo::tSlot:
            binding_type = GetBindingType(file, trait_info.GetTypeName(file.GetAbcFile()));
            break;
        case Abc::TraitInfo::tMethod:
            binding_type = SlotInfo::BT_Code;
            break;
        case Abc::TraitInfo::tGetter:
            binding_type = SlotInfo::BT_Get;
            break;
        case Abc::TraitInfo::tSetter:
            binding_type = SlotInfo::BT_Set;
            break;
        case Abc::TraitInfo::tFunction:
            // Theoretically, functions should be stored as regular members
            // and should go into virtual table.
            binding_type = SlotInfo::BT_Code;
            break;
        default:
            SF_ASSERT(false);
            break;
        }

        // Auto-assign a slot number ...

        /* DO NOT delete this code.
        // Try to resolve type in place.
        // This doesn't work because of dependencies.
        const ClassTraits::Traits* tr = NULL;
        if (trait_info.IsData())
        {
            const Abc::Multiname& tmn = trait_info.GetTypeName(file.GetAbcFile());
            tr = GetVM().Resolve2ClassTraits(file, tmn);
            SF_ASSERT(tr);
        }
        */

        const ASString mn_name = file.GetInternedString(mn.GetNameInd());
        Instances::Namespace& mn_ns = file.GetInternedNamespace(mn);
        AbsoluteIndex ind(-1);

#if 1

#if 1
        SlotInfo nsi(
            Pickable<Instances::Namespace>(&mn_ns, PickValue),
            file,
            trait_info,
            (_const ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum)
            SF_DEBUG_ARG((GetQualifiedName() + "/" + mn_name).GetNode())
            );

        // This can be either method or member.
        if (trait_info.HasMethodInd())
            result = RegisterWithVT(mn_name, nsi, Value(trait_info.GetMethodInd()), binding_type);
        else
        {
            ind = Add(mn_name, nsi);
            SlotInfo& si = GetOwnSlotInfo(ind);

            if (si.GetBindingType() == SlotInfo::BT_Unknown)
                si.Bind(binding_type, offset);
            else
                result = false;
        }

#else

        ind = FindSlotInfoIndex(mn_name, mn_ns);
        if (ind.IsValid())
        {
            const SlotInfo& si = GetSlotInfo(ind);

            // This is an overridden method.
            if (trait_info.HasMethodInd())
            {
                if (SlotInfo::IsValidCodeBT(si.GetBindingType()))
                {
                    // Initialize virtual table.
                    const Value v(trait_info.GetMethodInd());

                    // Interface methods may have two records in a VT.
                    // One has public namespace, another has namespace marked as "IsInterface".
                    if (&mn_ns == &vm.GetPublicNamespace())
                    {
                        // This method can be an interface method.
                        const SetType::ValueType *values = FindSlotValues(mn_name);
                        SF_ASSERT(values);
                        for (SPInt ind = *values; ind >= 0; ind = GetPrevSlotIndex(ind))
                        {
                            const AbsoluteIndex index(ind);
                            const SlotInfo& si = GetSlotInfo(index);
                            const Instances::Namespace& ns = si.GetNamespace();

                            if (ns.GetIsInterface())
                            {
                                // Add2VT will also bind the slot.
                                UpdateVT(si, v, binding_type);
                                break;
                            }
                        }
                    }

                    // Add2VT will also bind the slot.
                    UpdateVT(si, v, binding_type);
                }
                else
                    result = false;
            }
            else
                result = false;
        }
        else
        {
            ind = Add(
                mn_name, 
                SlotInfo(
                    Pickable<Instances::Namespace>(&mn_ns, PickValue),
                    file,
                    trait_info,
                    (_const ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum)
                    SF_DEBUG_ARG((GetQualifiedName() + "/" + mn_name).GetNode())
                    )
                );

            SlotInfo& si = GetOwnSlotInfo(ind);

            // This can be either method or member.
            if (trait_info.HasMethodInd())
            {
                if (SlotInfo::IsValidCodeBT(si.GetBindingType()))
                {
                    // Initialize virtual table.
                    const Value v(trait_info.GetMethodInd());

                    // Interface methods may have two records in a VT.
                    // One has public namespace, another has namespace marked as "IsInterface".
                    if (&mn_ns == &vm.GetPublicNamespace())
                    {
                        // This method can be an interface method.
                        const SetType::ValueType *values = FindSlotValues(mn_name);
                        SF_ASSERT(values);
                        for (SPInt ind = *values; ind >= 0; ind = GetPrevSlotIndex(ind))
                        {
                            const AbsoluteIndex index(ind);
                            const SlotInfo& si = GetSlotInfo(index);
                            const Instances::Namespace& ns = si.GetNamespace();

                            if (ns.GetIsInterface())
                            {
                                // Add2VT will also bind the slot.
                                UpdateVT(si, v, binding_type);
                                break;
                            }
                        }
                    }

                    // Add2VT will also bind the slot.
                    Add2VT(si, v, binding_type);
                }
                else
                    result = false;
            }
            else
            {
                if (si.GetBindingType() == SlotInfo::BT_Unknown)
                    si.Bind(binding_type, offset);
                else
                    result = false;
            }
        }
#endif
#else
        // We do not use ClassTraits::Traits here because we want to postpone name resolution.
        // Otherwise we will get problems with dependencies.
        SlotInfo& si = FindAddOwnSlotInfo(
            mn_name,
            SlotInfo(
                Pickable<Instances::Namespace>(&mn_ns, PickValue),
                file,
                trait_info,
                (_const ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum)
                SF_DEBUG_ARG((GetQualifiedName() + "/" + mn_name).GetNode())
                ),
            ind
            );

        if (trait_info.HasMethodInd())
        {
            if (SlotInfo::IsValidCodeBT(si.GetBindingType()))
            {
                // Initialize virtual table.
                const Value v(trait_info.GetMethodInd());

                // Interface methods may have two records in a VT.
                // One has public namespace, another has namespace marked as "IsInterface".
                if (&mn_ns == &vm.GetPublicNamespace())
                {
                    // This method can be an interface method.
                    const SetType::ValueType *values = FindSlotValues(mn_name);
                    SF_ASSERT(values);
                    for (SPInt ind = *values; ind >= 0; ind = GetPrevSlotIndex(ind))
                    {
                        const AbsoluteIndex index(ind);
                        SlotInfo& si = GetOwnSlotInfo(index);
                        const Instances::Namespace& ns = si.GetNamespace();
     
                        if (ns.GetIsInterface())
                        {
                            // Add2VT will also bind the slot.
                            Add2VT(si, v, binding_type);
                            break;
                        }
                    }
                }

                // Add2VT will also bind the slot.
                Add2VT(si, v, binding_type);
            }
            else
                result = false;
        }
        else
        {
            if (si.GetBindingType() == SlotInfo::BT_Unknown)
                si.Bind(binding_type, offset);
            else
                result = false;
        }
#endif

        if (!result)
        {
            vm.ThrowVerifyError(VM::Error(VM::eIllegalOverrideError, vm
                SF_DEBUG_ARG(mn_name.ToCStr())
                SF_DEBUG_ARG(GetName().ToCStr())
                ));

            break;
        }
    }

    if (result)
        CalculateMemSize(parent_size);

    return result;
}

SlotInfo::BindingType Traits::GetNewBT(SlotInfo::BindingType bt, SlotInfo::BindingType new_bt)
{
    if ((bt == SlotInfo::BT_Get && new_bt == SlotInfo::BT_Set) || (bt == SlotInfo::BT_Set && new_bt == SlotInfo::BT_Get))
        bt = SlotInfo::BT_GetSet;

    return bt;
}

// new_bt - new binding type.
void Traits::Add2VT(SlotInfo& si, const Value& v, SlotInfo::BindingType new_bt)
{
    SF_ASSERT(new_bt == SlotInfo::BT_Code || new_bt == SlotInfo::BT_Get || new_bt == SlotInfo::BT_Set);
    VTable& vt = GetVT();
    AbsoluteIndex method_ind = si.GetAValueInd();

    // This is not always CPP binging, but this will let us not visit code 
    // when we visit data in Traits.
    si.CppBinding = true;
    
    if (method_ind.IsValid())
    {
        // bt - binding type.
        const SlotInfo::BindingType bt = si.GetBindingType();
        
        // Check for possible problems.
        if (bt == SlotInfo::BT_Code && new_bt != bt)
        {
            // We do not want to assign a Getter/Setter value on top of regular code.
            SF_ASSERT(false);
            return;
        } else if ((bt == SlotInfo::BT_GetSet || bt == SlotInfo::BT_Get || bt == SlotInfo::BT_Set) && new_bt == SlotInfo::BT_Code)
        {
            // Code instead of a Getter/Setter.

            // This happens in
            // Test\AS3\WebSWF\Flint\4.0.1\examples\examples3D\BrownianMotion\Flare3d\BrownianMotion.swf
            // Test\AS3\WebSWF\Flint\4.0.1\examples\examples3D\Planets\Flare3d\Planets.swf

            // There should be no problems because Code requires only one record in VT 
            // and Getter/Setter reserve two.

            // SF_ASSERT(false);
            // return;
        }
        
        // Set the value.
        vt.SetMethod(method_ind, v, new_bt SF_DEBUG_ARG(si.GetName()));
        
        // Rebind if necessary.
        new_bt = GetNewBT(bt, new_bt);
        if (new_bt != bt)
            si.Bind(new_bt, method_ind);
    } else
    {
        // Add a new record to the virtual table ...
        si.Bind(new_bt, vt.AddMethod(v, new_bt SF_DEBUG_ARG(si.GetName())));
    }
}

// new_bt - new binding type.
void Traits::UpdateVT(const SlotInfo& si, const Value& v, SlotInfo::BindingType new_bt)
{
    SF_ASSERT(new_bt == SlotInfo::BT_Code || new_bt == SlotInfo::BT_Get || new_bt == SlotInfo::BT_Set);
    VTable& vt = GetVT();
    AbsoluteIndex method_ind = si.GetAValueInd();

    SF_ASSERT(method_ind.IsValid());

    // bt - binding type.
    const SlotInfo::BindingType bt = si.GetBindingType();

    // Check for possible problems.
    if (bt == SlotInfo::BT_Code && new_bt != bt)
    {
        // We do not want to assign a Getter/Setter value on top of regular code.
        SF_ASSERT(false);
        return;
    } else if ((bt == SlotInfo::BT_GetSet || bt == SlotInfo::BT_Get || bt == SlotInfo::BT_Set) && new_bt == SlotInfo::BT_Code)
    {
        // Code instead of a Getter/Setter.

        // This happens in
        // Test\AS3\WebSWF\Flint\4.0.1\examples\examples3D\BrownianMotion\Flare3d\BrownianMotion.swf
        // Test\AS3\WebSWF\Flint\4.0.1\examples\examples3D\Planets\Flare3d\Planets.swf

        // There should be no problems because Code requires only one record in VT 
        // and Getter/Setter reserve two.

        // SF_ASSERT(false);
        // return;
    }

    // Set the value.
    vt.SetMethod(method_ind, v, new_bt SF_DEBUG_ARG(si.GetName()));
}

Instances::Namespace& Traits::GetPublicNamespace() const
{
    return GetVM().GetPublicNamespace();
}

void Traits::CalculateMemSize(unsigned parent_size)
{
    MemSize = parent_size;

    VM& vm = GetVM();
    ArrayDH_POD<AbsoluteIndex> siv(vm.GetMemoryHeap());
    const UPInt size = GetSlotInfoNum();

    // Calculate number of values having different size.
    VarInfo var_num;
    for (UPInt i = FirstOwnSlotInd.Get(); i < size; ++i)
    {
        const SlotInfo& si = GetSlotInfo(AbsoluteIndex(i));

        if (si.IsCppBinding())
            // Skip CPP bindings.
            continue;

        SlotInfo::BindingType bt = si.GetBindingType();
        switch (bt)
        {
        case SlotInfo::BT_Value:
            ++var_num._value;
            break;
        case SlotInfo::BT_ObjectAS:
        case SlotInfo::BT_String:
#ifdef SF_64BIT_POINTERS
            ++var_num._8;
#else
            ++var_num._4;
#endif
            break;
        case SlotInfo::BT_Boolean:
            ++var_num._1;
            break;
        case SlotInfo::BT_Int:
            ++var_num._4;
            break;
        case SlotInfo::BT_UInt:
            ++var_num._4;
            break;
        case SlotInfo::BT_Number:
            ++var_num._8;
            break;
        case SlotInfo::BT_Code:
        case SlotInfo::BT_Get:
        case SlotInfo::BT_Set:
        case SlotInfo::BT_GetSet:
            // Ignore code.
            break;
        default:
            // BT_Unknown, BT_ValueArray
            // This shouldn't happen.
            SF_ASSERT(false);
            break;
        }
    }

    if (var_num._1 + var_num._4 + var_num._8 + var_num._value == 0)
        // There is nothing else to do.
        return;

    // Calculate offset of each pool.
    VarInfo offset;

    // We do not need to align it.
    offset._1 = parent_size;

    // Not aligned.
    offset._4 = offset._1 + var_num._1 * 1;
    if (var_num._4 > 0)
        // Aligned.
        offset._4 = AlignMem<4>(offset._4);

    // Not aligned.
    offset._8 = offset._4 + var_num._4 * 4;
    if (var_num._8 > 0) 
        // Aligned.
        offset._8 = AlignMem<8>(offset._8);

    // Not aligned.
    offset._value = offset._8 + var_num._8 * 8;
#ifdef SF_64BIT_POINTERS
    if (var_num._value > 0) 
        // Aligned.
        offset._value = AlignMem<32>(offset._value);

    MemSize = offset._value + var_num._value * 32;
#else
    if (var_num._value > 0) 
        // Aligned.
        offset._value = AlignMem<16>(offset._value);

    MemSize = offset._value + var_num._value * 16;
#endif


    // Replace index in a pool with offset.
    VarInfo var_ind;
    for (UPInt i = FirstOwnSlotInd.Get(); i < size; ++i)
    {
        SlotInfo& si = GetOwnSlotInfo(AbsoluteIndex(i));

        if (si.IsCppBinding())
            // Skip CPP bindings.
            continue;

        switch (si.GetBindingType())
        {
        case SlotInfo::BT_Boolean:
            si.ValueInd = offset._1 + var_ind._1++ * 1;

            break;
        case SlotInfo::BT_Int:
        case SlotInfo::BT_UInt:
            si.ValueInd = offset._4 + var_ind._4++ * 4;

            break;
        case SlotInfo::BT_Number:
            si.ValueInd = offset._8 + var_ind._8++ * 8;

            break;
        case SlotInfo::BT_String:
        case SlotInfo::BT_ObjectAS:
#ifdef SF_64BIT_POINTERS
            si.ValueInd = offset._8 + var_ind._8++ * 8;
#else
            si.ValueInd = offset._4 + var_ind._4++ * 4;
#endif

            break;
        case SlotInfo::BT_Value:
#ifdef SF_64BIT_POINTERS
            si.ValueInd = offset._value + var_ind._value++ * 32;
#else
            si.ValueInd = offset._value + var_ind._value++ * 16;
#endif

            break;
        default:
            SF_ASSERT(false);
            break;
        }
    }
}

unsigned Traits::GetFixedMemSize() const
{
    return GetMemSize();
}

void Traits::InitOnDemand() const
{
    ; // Do nothing.
}

const ClassTraits::Traits* Traits::RetrieveParentClassTraits(VM& vm, const ClassInfo& ci)
{
    const ClassTraits::Traits* ct = NULL;

    if (ci.Parent)
    {
        SPtr<Instances::Namespace> parentNs = 
            vm.MakeInternedNamespace(Abc::NS_Public, ci.Parent->PkgName);

        ct = vm.Resolve2ClassTraits(
            vm.GetStringManager().CreateConstString(ci.Parent->Name),
            *parentNs
            );
    }

    return ct;
}

void Traits::Add2StoredScopeStack(const Value& o)
{
    InitScope.PushBack(o);
}

void Traits::StoreScopeStack(const UPInt baseSSInd, const ScopeStackType& ss)
{
    const UPInt size = ss.GetSize();

    InitScope.Reserve(InitScope.GetSize() + size);
    for (UPInt i = baseSSInd; i < size; ++i)
        InitScope.PushBack(ss[i]);
}

SlotInfo& 
Traits::AddSetSlot(RelativeIndex ind, const ASString& name, Pickable<const Instances::Namespace> ns,
                   VMAbcFile& file, const Abc::TraitInfo& ti, bool _const)
{
    AbsoluteIndex index(ind, *this);

    while (index.Get() > GetSlotInfoNum())
    {
        // Use empty string as a key for dummy records ...
        AddSlotInfo(GetStringManager().CreateEmptyString(), SlotInfo());
    }

    if (index.Get() == GetSlotInfoNum())
        // Add data ...
        index = AddSlot(name, ns, file, ti, _const);
    else
        // Set data ...
        SetSlot(index, name, ns, file, ti, _const);

    return GetOwnSlotInfo(index);
}

void Traits::AddSlot(const ASString& name, Pickable<const Instances::Namespace> ns, const ClassTraits::Traits* tr, SlotInfo::BindingType dt, AbsoluteIndex offset, bool _const)
{
    int attr = _const ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum;

    const AbsoluteIndex ind = AddSlotInfo(
        name, 
        SlotInfo(
            ns, 
            tr,
            attr
            SF_DEBUG_ARG(name.GetNode())
            )
        );

    SlotInfo& si = GetOwnSlotInfo(ind);
    si.Bind(dt, offset);
}

void Traits::AddSlot(const ASString& name, Pickable<const Instances::Namespace> ns, SlotInfo::BindingType dt, AbsoluteIndex offset, bool const_)
{
    int attr = const_ ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum;

    const AbsoluteIndex ind = AddSlotInfo(
        name, 
        SlotInfo(
            ns, 
            NULL,
            attr
            SF_DEBUG_ARG(name.GetNode())
            )
        );

    SlotInfo& si = GetOwnSlotInfo(ind);
    si.Bind(dt, offset);
}

AbsoluteIndex Traits::AddSlot(const ASString& name, Pickable<const Instances::Namespace> ns, VMAbcFile& file, const Abc::TraitInfo& ti, bool const_)
{
    int attr = const_ ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum;

    return AddSlotInfo(
        name, 
        SlotInfo(
            ns, 
            file,
            ti,
            attr
            SF_DEBUG_ARG(name.GetNode())
            )
        );
}

void Traits::AddSlotCPP(const ASString& name, Pickable<const Instances::Namespace> ns, const ClassTraits::Traits* tr, SlotInfo::BindingType dt, AbsoluteIndex offset, bool const_)
{
    int attr = const_ ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum;
    attr |= SlotInfo::aCppBinding;

    const AbsoluteIndex ind = AddSlotInfo(
        name, 
        SlotInfo(
            ns, 
            tr,
            attr
            SF_DEBUG_ARG(name.GetNode())
            )
        );

    SlotInfo& si = GetOwnSlotInfo(ind);
    si.Bind(dt, offset);
}

void Traits::AddSlot(const MemberInfo& mi)
{
    int attr = (mi.Const != 0) ? (SlotInfo::aDontEnum | SlotInfo::aReadOnly) : SlotInfo::aDontEnum;
    attr |= SlotInfo::aCppBinding;

    VM& vm = GetVM();
    SF_ASSERT(mi.Name && *mi.Name != 0);
    ASString name = vm.GetStringManager().CreateConstString(mi.Name);

    const AbsoluteIndex ind = AddSlotInfo(
        name, 
        SlotInfo(
            Pickable<const Instances::Namespace>(&vm.GetPublicNamespace(), PickValue),
            NULL,
            attr
            SF_DEBUG_ARG(name.GetNode())
            )
        );

    SlotInfo& si = GetOwnSlotInfo(ind);
    si.Bind(mi.BT, AbsoluteIndex(mi.Offset));
}

void Traits::Add2VT(const ClassInfo& ci, const ThunkInfo& func)
{
    ASString method_name = GetStringManager().CreateConstString(func.Name);
    Pickable<Instances::Namespace> ns;
    const bool empty_ns_name = func.NamespaceName == NULL || *func.NamespaceName == 0;

    if (!empty_ns_name)
    {
        if (func.NamespaceName == NS_AS3 || strcmp(func.NamespaceName, NS_AS3) == 0)
            ns = Pickable<Instances::Namespace>(&GetVM().GetAS3Namespace(), PickValue);
        else
            ns = GetVM().MakeInternedNamespace(Abc::NS_Public, func.NamespaceName);
    }
    else
    {
        const bool empty_class_name = ci.Name == NULL || *ci.Name == 0;

        if (empty_class_name)
        {
            const bool empty_pkg_name = ci.PkgName == NULL || *ci.PkgName == 0;
            if (empty_pkg_name)
                ns = GetVM().MakePublicNamespace();
            else
                ns = GetVM().MakeInternedNamespace(Abc::NS_Public, ci.PkgName);
        }
        else
            ns = GetVM().MakePublicNamespace();

        /* DO NOT delete this code.
        if (!func.PackageName || *func.PackageName == 0)
            ns = &GetVM().GetPublicNamespace();
        else
            ns = &GetVM().MakeInternedNamespace(func.NsKind, func.PackageName);
        */

        /* DO NOT delete this code.
        if (!func.PackageName && !func.ClassName)
            ns = &GetVM().GetPublicNamespace();
        else
        {
            ASString ns_name = GetVM().GetStringManager().CreateEmptyString();
            if (func.PackageName)
                ns_name += func.PackageName;

            if (func.ClassName)
            {
                if (func.PackageName)
                    ns_name += ".";

                ns_name += func.ClassName;
            }

            ns = &GetVM().MakeInternedNamespace(func.NsKind, ns_name);
        }
        */
    }

#if 0
    AbsoluteIndex ind(-1);
    SlotInfo& si = FindAddOwnSlotInfo(
        method_name,
        SlotInfo(
            ns, 
            NULL,
            SlotInfo::aDontEnum
            SF_DEBUG_ARG(method_name.GetNode())
        ),
        ind
    );

    Add2VT(si, func, GetDataType(func.GetCodeType()));
#else
    if (!RegisterWithVT(
        method_name, 
        SlotInfo(
            ns, 
            NULL, // !!! Result type is missing.
            SlotInfo::aDontEnum
            SF_DEBUG_ARG(method_name.GetNode())
            ),
        func,
        GetDataType(func.GetCodeType())
        ))
    {
        VM& vm = GetVM();

        vm.ThrowVerifyError(VM::Error(VM::eIllegalOverrideError, vm
            SF_DEBUG_ARG(method_name.ToCStr())
            SF_DEBUG_ARG(GetName().ToCStr())
            ));
    }
#endif
}

void Traits::UpdateVT4IM(const ASString& mn_name, const Instances::Namespace& mn_ns, const Value& v, SlotInfo::BindingType bt)
{
    VM& vm = GetVM();

    // Interface methods may have two records in a VT.
    // One has public namespace, another has namespace marked as "IsInterface".
    if (&mn_ns == &vm.GetPublicNamespace())
    {
        // This method can be an interface method.
        const SetType::ValueType *values = FindSlotValues(mn_name);
        SF_ASSERT(values);
        for (SPInt ind = *values; ind >= 0; ind = GetPrevSlotIndex(ind))
        {
            const AbsoluteIndex index(ind);
            const SlotInfo& si = GetSlotInfo(index);
            const Instances::Namespace& ns = si.GetNamespace();

            if (ns.GetIsInterface())
            {
                UpdateVT(si, v, bt);
                break;
            }
        }
    }
}

void Traits::Add2VT(const ASString& mn_name, const Instances::Namespace& mn_ns, const SlotInfo& nsi, const Value& v, SlotInfo::BindingType bt)
{
    // In case we need to add new slot.
    const AbsoluteIndex ind = Add(mn_name, nsi);
    SlotInfo& si = GetOwnSlotInfo(ind);

    UpdateVT4IM(mn_name, mn_ns, v, bt);

    // Add2VT will also bind the slot.
    Add2VT(si, v, bt);
}

CheckResult Traits::RegisterWithVT(const ASString& mn_name, const SlotInfo& nsi, const Value& v, SlotInfo::BindingType bt)
{
    bool result = false;
    const Instances::Namespace& mn_ns = nsi.GetNamespace();
    AbsoluteIndex ind = FindSlotInfoIndex(mn_name, mn_ns);

    if (ind.IsValid())
    {
        // This is an overridden method.

        const SlotInfo& si = GetSlotInfo(ind);
        const SlotInfo::BindingType cur_bt = si.GetBindingType();

        // Slot is supposed to be bound at this point.
        if (SlotInfo::IsValidCodeBT(cur_bt))
        {
            const SlotInfo::BindingType new_bt = GetNewBT(cur_bt, bt);

#ifdef SF_AS3_ENABLE_SLOTS2
            // We are allowed to update VT only in case when binding types match.
            // Otherwise we will need to add a new slot with fixed binding.
            if (new_bt != bt)
                // Duplicate SlotInfo.
                Add2VT(mn_name, mn_ns, si, v, bt);
            else
#endif
            {
                UpdateVT4IM(mn_name, mn_ns, v, bt);

                UpdateVT(si, v, bt);

#ifndef SF_AS3_ENABLE_SLOTS2
                if (new_bt != bt)
                    const_cast<SlotInfo&>(si).Bind(new_bt, si.GetAValueInd());
#endif
            }

            result = true;
        }
    }
    else
    {
        Add2VT(mn_name, mn_ns, nsi, v, bt);
        result = true;
    }

    return result;
}

VMAbcFile* Traits::GetFilePtr() const
{
    return NULL;
}

bool Traits::IsParentOf(const Traits& other) const
{
    const Traits* ot = &other;

    while (ot->GetParent())
    {
        ot = ot->GetParent();

        if (ot == this)
            return true;
    }

    return false;
}

const Class& Traits::GetConstructor() const
{
    if (!pConstructor.GetPtr())
    {
        InitOnDemand();
        SF_ASSERT(pConstructor.GetPtr());
    }

    return *pConstructor;
}

Class& Traits::GetConstructor()
{
    if (!pConstructor.GetPtr())
    {
        InitOnDemand();
        SF_ASSERT(pConstructor.GetPtr());
    }

    return *pConstructor;
}

void Traits::DestructTail(Object& obj) const
{
    const UPInt size = GetSlotInfoNum();
    const UPInt first_own_ind = 0;
         
    // Destroy in order opposite to creation.
    for (UPInt i = size; i > first_own_ind; --i)
    {
        const SlotInfo& si = GetSlotInfo(AbsoluteIndex(i - 1));

        if (!si.IsCppBinding())
            si.DestroyPrimitiveMember(obj);
    }
}

void Traits::ConstructTail(Object& obj) const
{
    const UPInt size = GetSlotInfoNum();

    for (UPInt i = 0; i < size; ++i)
    {
        const SlotInfo& si = GetSlotInfo(AbsoluteIndex(i));

        if (!si.IsCppBinding())
            si.ConstructPrimitiveMember(obj);
    }
}

void Traits::ForEachChild_GC_Slot(Collector* prcc, const Object& obj, RefCountBaseGC<Mem_Stat>::GcOp op) const
{
    const UPInt size = GetSlotInfoNum();

    // Is it correct to use FirstOwnSlotInd here ???
    //for (UPInt i = FirstOwnSlotInd.Get(); i < size; ++i)
    for (UPInt i = 0; i < size; ++i)
    {
        const SlotInfo& si = GetSlotInfo(AbsoluteIndex(i));

        // We want to visit all slots, not just AS3 ones.
        // This way we avoid creating of ForEachChild_GC() for each
        // C++ class, which has garbage-collectable members.
        si.ForEachChild_GC(prcc, obj, op);
    }
}

GlobalSlotIndex Traits::GetNextPropertyIndex(GlobalSlotIndex ind)
{
    while (ind.Get() < GetSlotInfoNum())
    {
        ++ind;

        if (GetSlotInfo(AbsoluteIndex(ind)).IsDontEnum())
            continue;

        return ind;
    }

    return GlobalSlotIndex(0);
}

VTable& Traits::GetVT() const
{
    if (!pVTable)
    {
        // Initialize vtable ...
        if (pParent.GetPtr())
            // pVTable is AutoPtr.
            pVTable = SF_HEAP_NEW(pVM->GetMemoryHeap()) VTable(*const_cast<Traits*>(this), pParent->GetVT());
        else
            // pVTable is AutoPtr.
            pVTable = SF_HEAP_NEW(pVM->GetMemoryHeap()) VTable(*const_cast<Traits*>(this));
    }

    return *pVTable;
}

typedef ThunkFunc0<Class, __LINE__, Value> TFunc_prototypeGet;
typedef ThunkFunc0<Class, __LINE__, SInt32> TFunc_lengthGet;
typedef ThunkFunc0<Class, __LINE__, ASString> TFunc_toString;

template <> const TFunc_prototypeGet::TMethod TFunc_prototypeGet::Method = &Class::prototypeGet;
template <> const TFunc_lengthGet::TMethod TFunc_lengthGet::Method = &Class::lengthGet;
template <> const TFunc_toString::TMethod TFunc_toString::Method = &Class::toString;

namespace ClassTraits
{
    static const ThunkInfo ti[] = {
        {&Instances::Object::AS3isPrototypeOf, &BooleanCI, "isPrototypeOf", NS_AS3, CT_Method, 1, 1},
        {&Instances::Object::AS3hasOwnProperty, &BooleanCI, "hasOwnProperty", NS_AS3, CT_Method, 1, 1},
        {&Instances::Object::AS3propertyIsEnumerable, &BooleanCI, "propertyIsEnumerable", NS_AS3, CT_Method, 1, 1},
    };
    static const ThunkInfo f[3] = {
        {TFunc_prototypeGet::Func, &ObjectCI, "prototype", NULL, CT_Get, 0, 0},
        {TFunc_lengthGet::Func, &int_CI, "length", NULL, CT_Get, 0, 0},
        {TFunc_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    Traits::Traits(VM& vm, const ClassInfo& ci)
    : AS3::Traits(vm, vm.GetClassClass(), RetrieveParentClassTraits(vm, ci), true) // Classes are Dynamic Objects.
    {
        SetIsClassTraits();
        RegisterSlots();

        for (UInt8 i = 0; i < ci.ClassMethodNum; ++i)
            Add2VT(ci, ci.ClassMethod[i]);

        for (UInt8 i = 0; i < ci.ClassMemberNum; ++i)
            AddSlot(ci.ClassMember[i]);
    }

    Traits::Traits(VM& vm, const ClassTraits::Traits* pt)
    : AS3::Traits(vm, vm.GetClassClass(), pt, true) // Classes are Dynamic Objects.
    {
        SetIsClassTraits();
        RegisterSlots();
    }

    Traits::Traits(VM& vm)
        : AS3::Traits(vm)
    {
        SetIsClassTraits();
//         RegisterSlots();
//         SF_ASSERT(SlotsAreBound2Values());
    }

    void Traits::SetInstanceTraits(Pickable<InstanceTraits::Traits> itr)
    {
        SetIsInterface(itr->IsInterface());
        ITraits = itr;
        /* This will introduce memory leaks.
        if (!IsAbcObject() && GetVM().IsInitialized())
            GetVT().MakeScopeStackCPP(*this);
        */
    }

    void Traits::InitOnDemand() const
    {
        InstanceTraits::Traits& itr = GetInstanceTraits();

        if (!itr.HasConstructorSetup())
            // Lazy initialization.
            itr.InitOnDemand();
    }

    void Traits::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        AS3::Traits::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<InstanceTraits::Traits, Mem_Stat>(prcc, ITraits, op SF_DEBUG_ARG(*this));
    }

    void Traits::RegisterSlots()
    {
        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            Add2VT(ObjectCI, ti[i]);

        ClassInfo None;
        None.Name = "";
        None.PkgName = "";

        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            Add2VT(None, f[i]);

        // FirstOwnSlotInd += own_slot_number;
        FirstOwnSlotInd += 3 + 3;
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
            const InstanceTraits::Traits& itr = tr->GetInstanceTraits();
            if (itr.SupportsInterface(GetInstanceTraits()))
                return true;

            tr = tr->GetParent();
            if (tr == this)
                return true;
        }

        return false;
    }

    bool Traits::Coerce(const Value& value, Value& result) const
    {
        return CoerceValue(value, result);
    }

    bool Traits::CoerceValue(const Value& value, Value& result) const
    {
        // Primitives can be coerced to their own return types and Object,
        // as well as Number/unsigned when appropriate.

        VM& vm = GetVM();
        const BuiltinTraitsType tt = GetTraitsType();

        switch (value.GetKind())
        {
        case Value::kUndefined:
            result.SetNull();
            break;
        case Value::kInt:
#if 0
            // Not converting to Number doesn't work at the moment.
            if (!vm.IsObject(*this) && tt != Traits_SInt)
                return false;
            result.SetSInt32(value.AsInt());
#else
            if (!vm.IsObject(*this) && tt != Traits_Number && tt != Traits_SInt)
                return false;
            result.SetNumber(value.AsInt());
#endif
            break;
        case Value::kUInt:
#if 0
            // Not converting to Number doesn't work at the moment.
            if (!vm.IsObject(*this) && tt != Traits_UInt)
                return false;
            result.SetUInt32(value.AsUInt());
#else
            if (!vm.IsObject(*this) && tt != Traits_Number && tt != Traits_UInt)
                return false;
            result.SetNumber(value.AsUInt());
#endif
            break;
        case Value::kThunk:
        case Value::kVTableInd:
            if (!vm.IsObject(*this) && tt != Traits_Function)
                return false;
            result = value;
            break;

        case Value::kBoolean:
            if (!vm.IsObject(*this) && tt != Traits_Boolean)
                return false;
            result = value;
            break;

        case Value::kNumber:
            if (!vm.IsObject(*this) && tt != Traits_Number)
                return false;
            result = value;
            break;

        case Value::kString:
            if (!vm.IsObject(*this) && tt != Traits_String)
                return false;
            result = value;
            break;
        case Value::kNamespace:
            if (!vm.IsObject(*this) && tt != Traits_Namespace)
                return false;
            result = value;
            break;
        case Value::kFunction:
        case Value::kObject:
        case Value::kThunkFunction:
            // We do not need to get classes of primitive objects because they all are final.
            if (value.GetObject())
            {
                const Traits& other = vm.GetClassTraits(value);

                if (IsParentTypeOf(other))
                    result = value;
                else
                    return false;
            }
            else
                // null
                result = value;

            break;
        case Value::kThunkClosure:
        case Value::kVTableIndClosure:
            result = value;
            break;
        case Value::kClass:
            // We do not need to get classes of primitive objects because they all are final.
            if (IsParentTypeOf(value.AsClass().GetClassTraits()))
                result = value;
            else
                return false;

            break;
        default:
            SF_ASSERT(false);
            break;
        }

        return true;
    }

    ASString Traits::GetName() const
    {
        return GetInstanceTraits().GetName();
    }

    ASString Traits::GetQualifiedName(QNameFormat f) const
    {
        return GetInstanceTraits().GetQualifiedName(f);
    }
} // namespace ClassTraits

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

