/**************************************************************************

Filename    :   AS3_Obj_UserDefined.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "../AS3_VM.h"
#include "../AS3_VTable.h"
#include "AS3_Obj_UserDefined.h"
#include "AS3_Obj_Namespace.h"
#include "AS3_Obj_Global.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

namespace Classes
{
    ///////////////////////////////////////////////////////////////////////
    UserDefined::UserDefined(ClassTraits::UserDefined& t)
    : UDBase(t)
    {
        // MA: Interfaces have null parent class.
        //SF_ASSERT(GetParentClass() != NULL);
        
        // Set up slot values ...
        if (t.SetupSlotValues(*this))
        {
            // Alter Traits to store scope stack.
            GetTraits().StoreScopeStack(GetVM().GetScopeStackBaseInd(), const_cast<const VM&>(GetVM()).GetScopeStack());
        }
    }

    UserDefined::~UserDefined()
    {
    }

    void UserDefined::CallStaticConstructor()
    {
        // Run initialization code ...
        const int method_ind = GetClassInfo().GetStaticInfo().GetMethodInfoInd();
        const SInt32 mbi_ind = GetFile().GetMethodBodyInfoInd(method_ind);

        // Class constructors do not have arguments, only instance constructors do.
        // For some reason it is not always zero.
        //SF_ASSERT(mi.GetParamCount() == 0);

        GetVM().AddFrame(
            Value(this), // It is not really necessary to track life time of classes (at least it seems so)
            GetFile(),
            mbi_ind,
            Value(this),
            0, // No arguments ...
            NULL,
            true, // discard_result
            // GetTraits() will return class traits. That is correct.
            &GetTraits().GetStoredScopeStack(),
            &GetTraits() // ??? Is this correct?
            SF_DEBUG_ARG(GetName() + " class constructor")
            ); 
    }

    void UserDefined::PostInit(const Value& _this, unsigned argc, const Value* argv) const
    {
        // Run initialization (constructor) code ...
        const int method_ind = GetClassInfo().GetInstanceInfo().GetMethodInfoInd();
        const SInt32 mbi_ind = GetFile().GetMethodBodyInfoInd(method_ind);
        InstanceTraits::Traits& itr = GetClassTraits().GetInstanceTraits();

        GetVM().AddFrame(
#if 0
            Value(const_cast<UserDefined*>(this)), // It is not really necessary to track life time of classes (at least it seems so)
#else
            _this,
#endif
            GetFile(),
            mbi_ind,
            _this,
            argc,
            argv,
            true, // discard_result because this is a constructor.
            // We need Instance Traits here.
            &itr.GetStoredScopeStack(),
            &itr // ??? Is this correct?
            SF_DEBUG_ARG(GetName() + " instance constructor")
            ); 
    }

} // namespace Classes

namespace ClassTraits
{
    ///////////////////////////////////////////////////////////////////////
    UserDefined::UserDefined(VMAbcFile& file, VM& vm, const Abc::ClassInfo& info)
    : Traits(vm, NULL) // Parent traits are not set on purpose (to prevent recursive dependencies).
    , File(&file)
    , class_info(info)
    {
        // This is ABC related class.
        SetIsAbcObject(true);

        // We MAY NOT register slots nor create InstanceTraits in the constructor because of possible recursion.
    }
    
    UserDefined::~UserDefined()
    {
    }

    CheckResult UserDefined::RegisterSlots()
    {
        // There is no need to check for parent's size because we have only one level
        // of inheritance.
        if(!AddSlots(class_info.GetStaticInfo(), GetFile(), GetFixedMemSize()))
            return false;

        // AddInterfaceSlots() call HAS TO go after AddSlots().
        if (class_info.GetInstanceInfo().IsInterface())
            AddInterfaceSlots(GetFile(), class_info);

        return true;
    }

    unsigned UserDefined::GetFixedMemSize() const
    {
        return sizeof(Classes::UserDefined);
    }

    const Traits* UserDefined::GetSuperClassTraits(VMAbcFile& file, const Abc::ClassInfo& info)
    {
        const Traits* result = NULL;
        const Abc::Instance& inst = info.GetInstanceInfo();

        if (inst.HasSuperClass())
        {
            const Abc::Multiname& mn = inst.GetSuperClassName(file.GetConstPool());
            result = file.GetVM().Resolve2ClassTraits(file, mn);

            if (!result)
            {
                // Parent class is not defined.
                SF_DEBUG_CODE(const StringDataPtr& s = mn.GetName(file.GetConstPool()));
                SF_DEBUG_CODE(const Scaleform::String name(s.ToCStr(), s.GetSize()));
                file.GetVM().ThrowVerifyError(VM::Error(VM::eNotImplementedError, file.GetVM() SF_DEBUG_ARG(name)));
            }
        }

        return result;
    }

    CheckResult UserDefined::Initialize()
    {
        const ClassTraits::Traits* parent_tr = GetSuperClassTraits(GetFile(), class_info);

        // GetSuperClassTraits() can throw exceptions.
        if (GetVM().IsException())
            return false;

        if (GetParent() == NULL)
            // Set parent traits.
            SetParentTraits(parent_tr);
        else
        {
            SF_ASSERT(GetParent() == parent_tr);
        }

        if (IsValid())
            return true;


        // Set instance traits.
        {
            InstanceTraits::Traits* ipt = NULL;

            if (parent_tr)
            {
                if (!parent_tr->IsValid())
                {
                    static_cast<ClassTraits::UserDefined*>(const_cast<ClassTraits::Traits*>(parent_tr))->Initialize();

                    // InstanceTraits::UserDefined() can throw exceptions.
                    if (GetVM().IsException())
                        return false;
                }

                SF_ASSERT(parent_tr->IsValid());
                ipt = &parent_tr->GetInstanceTraits();
            }
            /* DO NOT delete this code.
            // Parent class seems to not exist for interfaces.
            else
                SF_ASSERT(false);
            */

            Pickable<InstanceTraits::UserDefined> it(SF_HEAP_NEW_ID(GetVM().GetMemoryHeap(), StatMV_VM_ITraits_Mem) InstanceTraits::UserDefined(GetFile(), ipt, class_info));
            // We HAVE TO call SetInstanceTraits() even in case of an exception
            // because otherwise we will get a memory leak.
            SetInstanceTraits(it);

            // InstanceTraits::UserDefined() can throw exceptions.
            if (GetVM().IsException())
                return false;
        }

        return RegisterSlots();
    }

    CheckResult UserDefined::SetupSlotValues(AS3::Object& for_obj) const
    {
//              if (HasParent())
//                  GetParent().SetupSlotValues(for_obj);

        return Traits::SetupSlotValues(GetFile(), class_info.GetStaticInfo(), for_obj);
    }

    Pickable<Classes::UserDefined> UserDefined::MakeClass()
    {
        // Theoretically, all this logic can be moved into UserDefined::UserDefined().

        // Placement new.
        Pickable<Classes::UserDefined> cl(new(Alloc()) Classes::UserDefined(*this));
        InstanceTraits::Traits& it = GetInstanceTraits();

        // Make an extra AddRef by creating an extra Pickable.
        it.SetConstructor(Pickable<Classes::UserDefined>(cl.GetPtr(), PickValue));

        // Fix InstanceTraits stored scope stack.
        {
            // Alter Traits to store scope stack.
            it.StoreScopeStack(GetVM().GetScopeStackBaseInd(), const_cast<const VM&>(GetVM()).GetScopeStack());
            // Magic logic.
            // Should be called only for instance traits.
            it.Add2StoredScopeStack(Value(cl.GetPtr()));
        }

        // A line below is different from all other similar cases.
        cl->CallStaticConstructor();

        return cl;
    }
    
    VMAbcFile* UserDefined::GetFilePtr() const
    {
        return File;
    }

    void UserDefined::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        Traits::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<VMAbcFile, Mem_Stat>(prcc, File, op SF_DEBUG_ARG(*this));
    }
} // namespace ClassTraits

namespace InstanceTraits
{
    UserDefined::UserDefined(VMAbcFile& file, const Traits* pt, const Abc::ClassInfo& info)
        : UDBase(
            file.GetVM(), 
            file.GetInternedString(info.GetInstanceInfo().GetName(file.GetConstPool()).GetNameInd()),
            Pickable<Instances::Namespace>(&file.GetInternedNamespace(
                info.GetInstanceInfo().GetName(file.GetConstPool()).GetNamespaceInd()
                ), PickValue),
            pt, 
            !info.GetInstanceInfo().IsSealed()
            )
        , class_info(info)
    {
        // Instance size will be set by AddSlots().

        // This is ABC related class.
        SetIsAbcObject(true);

        const Abc::Instance& ii = info.GetInstanceInfo();

#ifdef SF_AS3_ENABLE_INSTANCE_NAMESPACES
        // Set up protected namespace.
        if (ii.HasProtectedNamespace())
        {
            const Abc::NamespaceInfo& ni = ii.GetProtectedNamespace(file.GetConstPool());
            
            SetProtectedNamespace(file.GetVM().MakeInternedNamespace(ni.GetKind(), ni.GetNameURI()));
        }
#endif
        
        SetIsInterface(ii.IsInterface());
        
        // Add new object traits ...
        // Everything is at least an Object.
        if (!AddSlots(ii, file, pt ? pt->GetMemSize() : GetFixedMemSize()))
            return;

        // AddInterfaceSlots() call HAS TO go after AddSlots().
        AddInterfaceSlots(file, info);
    }

    void UserDefined::AS3Constructor(const AS3::Traits& ot, const Value& _this, unsigned argc, const Value* argv) const
    {
        // This method is used in implementation of the exec_constructsuper opcode.
        // class_info is specific to the InstanceTraits (and to a class).

        // Run initialization (constructor) code ...
        {
            const int method_ind = class_info.GetInstanceInfo().GetMethodInfoInd();
            // We always have file in UserDefined InstanceTraits.
            const SInt32 mbi_ind = GetFile().GetMethodBodyInfoInd(method_ind);

            GetVM().AddFrame(
                Value::GetUndefined(), // It is a constructor. We do not need to track Object's life time here.
                GetFile(),
                mbi_ind,
                _this,
                argc,
                argv,
                true, // discard_result because this is a constructor.
                // We will get VT of Instance Traits here. That is correct.
                &this->GetStoredScopeStack(),
                ot.GetParent() // Origination Traits. 
                SF_DEBUG_ARG(GetName() + " instance constructor")
                ); 
            SF_ASSERT(GetName() != "MenuManager");
        }
    }

    bool UserDefined::SupportsInterface(const Traits& itraits) const
    {
        const Abc::Instance::Interfaces& interfaces = class_info.GetInstanceInfo().GetInterfaces();
        VM& vm = GetVM();

        for (UPInt i = 0; i < interfaces.GetSize(); i++)
        {
            const Multiname interfaceMN(GetFile(), interfaces.GetName(GetFile().GetConstPool(), AbsoluteIndex(i)));

            const ClassTraits::Traits* ctr = vm.GetRegisteredClassTraits(interfaceMN);

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

    VMAbcFile* UserDefined::GetFilePtr() const
    {
        return &GetFile();
    }

    CheckResult UserDefined::SetupSlotValues(AS3::Object& for_obj) const
    {
        if (GetParent())
        {
            if (!GetParent()->SetupSlotValues(for_obj))
                return false;
        }

        return Traits::SetupSlotValues(GetFile(), class_info.GetInstanceInfo(), for_obj);
    }

    CheckResult UserDefined::PreInit(const Value& _this) const
    {
        // Set up slot values ...
        return SetupSlotValues(*_this.GetObject());
    }

    void UserDefined::PostInit(const Value& _this, unsigned argc, const Value* argv) const
    {
        // Run initialization (constructor) code ...
        const int method_ind = class_info.GetInstanceInfo().GetMethodInfoInd();
        const SInt32 mbi_ind = GetFile().GetMethodBodyInfoInd(method_ind);

        GetVM().AddFrame(
            Value::GetNull(),
            GetFile(),
            mbi_ind,
            _this,
            argc,
            argv,
            true, // discard_result because this is a constructor.
            // We need Instance Traits here.
            &this->GetStoredScopeStack(),
            this // ??? Is this correct?
            SF_DEBUG_ARG(GetName() + " instance constructor")
            ); 
    }

    void UserDefined::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        Traits::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<Instances::GlobalObjectScript, Mem_Stat>(prcc, Script, op SF_DEBUG_ARG(*this));
    }

    void UserDefined::InitOnDemand() const
    {
        GetScript().InitOnDemand();
    }

    VMAbcFile& UserDefined::GetFile() const
    {
        return GetScript().GetFile();
    }

    void UserDefined::SetScript(Instances::GlobalObjectScript& script)
    {
        SF_ASSERT(!HasScriptSetUp());
        Script.SetPtr(&script);
    }
} // namespace InstanceTraits

}}} // namespace Scaleform { namespace GFx { namespace AS3
