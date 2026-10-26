//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Dictionary.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Utils_Dictionary_H
#define INC_AS3_Obj_Utils_Dictionary_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"

///////////////////////////////////////////////////////////////////////////
typedef HashLH<Value, Value, Value::HashFunctor> ValueContainerType;
void ForEachChild_GC(RefCountCollector<Mem_Stat>* prcc, bool WeakKeys, ValueContainerType& v, RefCountBaseGC<Mem_Stat>::GcOp op
                     SF_DEBUG_ARG(const RefCountBaseGC<Mem_Stat>& owner));

//##protect##"forward_declaration"

namespace ClassTraits
{
    class Dictionary;
}

namespace InstanceTraits
{
    class Dictionary;
}

namespace Classes
{
    class Dictionary;
}

namespace Instances
{
    class Dictionary : public Instances::Object
    {
        friend class InstanceTraits::Dictionary;
        
    public:
        typedef Dictionary SelfType;
        typedef Classes::Dictionary ClassType;
        typedef InstanceTraits::Dictionary TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Dictionary"; }
#endif
    protected:
        Dictionary(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        virtual ~Dictionary();

        virtual CheckResult SetProperty(const Multiname& prop_name, const Value& value);
        virtual CheckResult GetProperty(const Multiname& prop_name, Value& value);
        virtual void GetDynamicProperty(AbsoluteIndex ind, Value& value);
        virtual CheckResult DeleteProperty(const Multiname& prop_name);
        virtual void AddDynamicSlotValuePair(const Value& prop_name, const Value& value,
            SlotInfo::Attribute a = SlotInfo::aNone);
        virtual PropRef FindDynamicSlot(const Multiname& prop_name);

        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

    public:
        virtual void GetNextPropertyName(Value& name, GlobalSlotIndex ind) const;
        // This method will enumerate only dynamic properties.
        // Initial index should be invalid (for example -1)
        virtual GlobalSlotIndex GetNextDynPropIndex(GlobalSlotIndex ind) const;

    protected:
        virtual void AS3Constructor(unsigned argc, const Value* argv);

        ValueContainerType::Iterator FindKey(const Multiname& prop_name) const;

//##protect##"instance$methods"

//##protect##"instance$data"
    private:
        bool WeakKeys;
        mutable ValueContainerType ValueH;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Dictionary : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Dictionary"; }
#endif
    public:
        Dictionary(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Dictionary> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Dictionary : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Dictionary"; }
#endif
    public:
        typedef Classes::Dictionary ClassType;

    public:
        Dictionary(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

