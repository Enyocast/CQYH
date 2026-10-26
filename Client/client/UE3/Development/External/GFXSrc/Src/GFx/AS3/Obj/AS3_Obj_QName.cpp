//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_QName.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_QName.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::QName, Instances::QName::mid_localNameGet, ASString> TFunc_Instances_QName_localNameGet;
typedef ThunkFunc0<Instances::QName, Instances::QName::mid_uriGet, Value> TFunc_Instances_QName_uriGet;
typedef ThunkFunc0<Instances::QName, Instances::QName::mid_AS3valueOf, Value> TFunc_Instances_QName_AS3valueOf;
typedef ThunkFunc0<Instances::QName, Instances::QName::mid_AS3toString, ASString> TFunc_Instances_QName_AS3toString;

template <> const TFunc_Instances_QName_localNameGet::TMethod TFunc_Instances_QName_localNameGet::Method = &Instances::QName::localNameGet;
template <> const TFunc_Instances_QName_uriGet::TMethod TFunc_Instances_QName_uriGet::Method = &Instances::QName::uriGet;
template <> const TFunc_Instances_QName_AS3valueOf::TMethod TFunc_Instances_QName_AS3valueOf::Method = &Instances::QName::AS3valueOf;
template <> const TFunc_Instances_QName_AS3toString::TMethod TFunc_Instances_QName_AS3toString::Method = &Instances::QName::AS3toString;


namespace Instances
{
    QName::QName(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::QName::QName()$data"
    , LocalName(GetStringManager().CreateEmptyString())
//##protect##"instance::QName::QName()$data"
    {
//##protect##"instance::QName::QName()$code"
        Uri = GetStringManager().CreateEmptyString();
//##protect##"instance::QName::QName()$code"
    }

    void QName::localNameGet(ASString& result)
    {
//##protect##"instance::QName::localNameGet()"
        result = LocalName;
//##protect##"instance::QName::localNameGet()"
    }
    void QName::uriGet(Value& result)
    {
//##protect##"instance::QName::uriGet()"
        result = Uri;
//##protect##"instance::QName::uriGet()"
    }
    void QName::AS3valueOf(Value& result)
    {
//##protect##"instance::QName::AS3valueOf()"
        result = this;
//##protect##"instance::QName::AS3valueOf()"
    }
    void QName::AS3toString(ASString& result)
    {
//##protect##"instance::QName::AS3toString()"
        if (Uri.IsUndefined() || Uri.IsString() && Uri.AsString().GetSize() == 0)
            result = LocalName;
        else if (Uri.IsNull())
            result = "*::" + LocalName;
        else
        {
            // Check for exceptions.
            if (Uri.Convert2String(result))
            {
                result += "::";
                result += LocalName;
            }
        }
//##protect##"instance::QName::AS3toString()"
    }
    void QName::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
//##protect##"instance::QName::toStringProto()"

#ifdef SF_ENABLE_XML
        SF_UNUSED3(ti, argc, argv);
        if (_this.IsObject() && _this.GetObject() == &vm.GetClassQName().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else 
        {
            const Traits& tr = vm.GetValueTraits(_this);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (tt != Traits_QName || tr.IsClassTraits())
                return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

            Instances::QName* obj = static_cast<Instances::QName*>(_this.GetObject());
            ASString str = vm.GetStringManager().CreateEmptyString();

            obj->AS3toString(str);
            if (vm.IsException())
                return;

            result = str;
        }
#else
        SF_UNUSED5(ti, _this, result, argc, argv);
        WARN_NOT_IMPLEMENTED_STATIC("QName::toStringProto()");
#endif
//##protect##"instance::QName::toStringProto()"
    }

//##protect##"instance$methods"
    void QName::AS3Constructor(unsigned argc, const Value* argv)
    {
        VM& vm = GetVM();
        StringManager& sm = vm.GetStringManager();

        // If the parameter is undefined or unspecified, a new QName object 
        // is created with the localName property set to the empty string.
        // 
        if (argc == 0)
            LocalName = sm.CreateEmptyString();
        else if (argc == 1)
        {
            // If the parameter is not a QName object, the parameter is 
            // converted to a string and assigned to the localName property 
            // of the new QName instance.
            // Situation when parameter is not a QName object is handled by Construct().
            if (argv[0].IsNullOrUndefined())
                LocalName = sm.CreateEmptyString();
            else
                argv[0].Convert2String(LocalName).DoNotCheck();
        }
        else
        {
            // Set Uri up.
            Uri = argv[0];
            // Namespace is a final class.
            if (!Uri.IsNull() && &vm.GetValueTraits(argv[0]) != &vm.GetITraitsNamespace())
                Uri.ToStringValue(sm).DoNotCheck();

            // Set LocalName up.
            // If argv[1] is QName.
            if (&GetTraits() == &vm.GetValueTraits(argv[1]))
            {
                QName* other = static_cast<QName*>(argv[1].GetObject());
                LocalName = other->LocalName;
            }
            else
                argv[1].Convert2String(LocalName).DoNotCheck();
        }
    }

    void QName::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC(prcc, Uri, op SF_DEBUG_ARG(*this));
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo QName::ti[QName::ThunkInfoNum] = {
        {TFunc_Instances_QName_localNameGet::Func, &StringCI, "localName", NULL, CT_Get, 0, 0},
        {TFunc_Instances_QName_uriGet::Func, NULL, "uri", NULL, CT_Get, 0, 0},
        {TFunc_Instances_QName_AS3valueOf::Func, &QNameCI, "valueOf", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_QName_AS3toString::Func, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
    };

    QName::QName(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::QName::QName()"
        SetTraitsType(Traits_QName);
//##protect##"InstanceTraits::QName::QName()"
        SetMemSize(sizeof(Instances::QName));

    }

    Pickable<Instances::QName> QName::MakeInstance(Traits& t)
    {
        return Pickable<Instances::QName>(new(t.Alloc()) Instances::QName(t));
    }

    void QName::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    const ThunkInfo QName::ti[QName::ThunkInfoNum] = {
        {&Instances::QName::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    QName::QName(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::QName::QName()"
//##protect##"class_::QName::QName()"
    }

    void QName::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void QName::Construct(Value& _this, unsigned argc, const Value* argv, bool extCall)
    {
        if (argc == 1)
        {
            const Traits& tr = GetVM().GetValueTraits(argv[0]);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (tt == Traits_QName && tr.IsInstanceTraits())
            {
                // We shouldn't create new object in this case.
                _this = argv[0];
                return;
            }
        }

        Class::Construct(_this, argc, argv, extCall);
    }

    void QName::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    QName::QName(VM& vm)
    : Traits(vm, QNameCI)
    {
//##protect##"ClassTraits::QName::QName()"
        SetTraitsType(Traits_QName);
//##protect##"ClassTraits::QName::QName()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::QName(vm, QNameCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::QName(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> QName::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) QName(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo QNameCI = {
    ClassInfo::CompileTime,
    "QName", "", &ObjectCI,
    ClassTraits::QName::MakeClassTraits,
    0,
    0,
    InstanceTraits::QName::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::QName::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

