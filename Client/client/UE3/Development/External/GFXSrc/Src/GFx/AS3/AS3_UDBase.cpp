/**************************************************************************

Filename    :   AS3_UDBase.cpp
Content     :   
Created     :   Feb, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_UDBase.h"
#include "AS3_VM.h"
#include "Obj/AS3_Obj_Object.h"

namespace Scaleform { namespace GFx { namespace AS3 
{

namespace InstanceTraits
{
    unsigned UDBase::GetFixedMemSize() const
    {
        const Traits* parent = GetParent();

        if (parent)
            return parent->GetFixedMemSize();

        // We do not have parent in case of interface.
        return sizeof(Instances::Object);
    }

    void UDBase::MakeObject(Value& result, Traits& t)
    {
        // This code is similar to the code in InstanceTraits::UserDefined.

        /* DO NOT delete.
        // This code doesn't compile because of constness.
        Traits* parent = GetParent();
        // UserDefined classes always have a parent. It is at least a class Object.
        SF_ASSERT(parent);
        parent->MakeObject(result, t);
        result.GetObject()->SetTraits(*this);
        */

#if 0
        Class* parent = GetConstructor().GetParentClass();

        if ((parent == NULL) || (parent && parent->GetParentClass() == NULL))
            // Just in case.
            parent = &GetVM().GetClassObject();

        parent->GetInstanceTraits().MakeObject(result, t);
#else
        Traits* parent = const_cast<Traits*>(GetParent());

        if (parent == NULL)
            // Just in case.
            parent = &GetVM().GetITraitsObject();

        parent->MakeObject(result, t);
#endif
//         result.GetObject()->SetTraits(*this);
    }

} // namespace InstanceTraits

namespace Classes
{
    UDBase::UDBase(ClassTraits::Traits& t)
    : Class(t)
    {
        t.ConstructTail(*this);
    }

    UDBase::~UDBase()
    {
        GetTraitsSafe().DestructTail(*this);
    }

    CheckResult UDBase::PreInit(const Value& _this) const
    {
        // Set up slot values.
        return GetClassTraits().GetInstanceTraits().SetupSlotValues(*_this.GetObject());
    }

    void UDBase::InitPrototype(AS3::Object& obj) const
    {
        AddConstructor(obj);
    }

} // namespace Classes

}}} // namespace Scaleform { namespace GFx { namespace AS3 {


