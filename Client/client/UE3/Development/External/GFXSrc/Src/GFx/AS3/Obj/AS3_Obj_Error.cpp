//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Error.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Error.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "Kernel/SF_MsgFormat.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Error, Instances::Error::mid_errorIDGet, SInt32> TFunc_Instances_Error_errorIDGet;
typedef ThunkFunc0<Instances::Error, Instances::Error::mid_getStackTrace, ASString> TFunc_Instances_Error_getStackTrace;

template <> const TFunc_Instances_Error_errorIDGet::TMethod TFunc_Instances_Error_errorIDGet::Method = &Instances::Error::errorIDGet;
template <> const TFunc_Instances_Error_getStackTrace::TMethod TFunc_Instances_Error_getStackTrace::Method = &Instances::Error::getStackTrace;

typedef ThunkFunc0<Instances::Error, Instances::Error::mid_toStringProto, ASString> TFunc_Instances_Error_toStringProto;

template <> const TFunc_Instances_Error_toStringProto::TMethod TFunc_Instances_Error_toStringProto::Method = &Instances::Error::toStringProto;

namespace Instances
{
    Error::Error(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , message(AS3::DefaultValue<ASString>(GetStringManager()))
    , name(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::Error::Error()$data"
    , ID()
#ifdef GFX_AS3_VERBOSE
    , StackTrace(GetVM().GetStringManager().CreateEmptyString())
#endif
//##protect##"instance::Error::Error()$data"
    {
//##protect##"instance::Error::Error()$code"
        // Code below doesn't work because this class is reused with different error types.
        //name = GetStringManager().CreateConstString("Error");
        name = t.GetName();

#ifdef GFX_AS3_VERBOSE
        GetVM().GetStackTraceASString(StackTrace);
#endif
//##protect##"instance::Error::Error()$code"
    }

    void Error::errorIDGet(SInt32& result)
    {
//##protect##"instance::Error::errorIDGet()"
        result = ID;
//##protect##"instance::Error::errorIDGet()"
    }
    void Error::getStackTrace(ASString& result)
    {
//##protect##"instance::Error::getStackTrace()"
#ifdef GFX_AS3_VERBOSE
        toStringProto(result);
        result += "\n" + StackTrace;
#else
        result = GetStringManager().GetBuiltin(AS3Builtin_null);
#endif
//##protect##"instance::Error::getStackTrace()"
    }
    void Error::toStringProto(ASString& result)
    {
//##protect##"instance::Error::toStringProto()"
        // !!! I'm using GetName() instead of the "name" property.
        result = GetName();
        if (!message.IsEmpty())
        {
            // "Error #1223: " prefix is actually a part of the message,
            //  so we don't generate it here.
            result += ": " + message;
        }
//##protect##"instance::Error::toStringProto()"
    }

//##protect##"instance$methods"
    Error::Error(InstanceTraits::Traits& t, int id SF_DEBUG_ARG(const ASString& msg))
    : Instances::Object(t)
#ifdef GFX_AS3_VERBOSE
    , message(msg.GetNode())
#else
    , message(GetStringManager().CreateEmptyString())
#endif
    , name(GetStringManager().CreateConstString("Error"))
    , ID(id)
#ifdef GFX_AS3_VERBOSE
    , StackTrace(GetStringManager().CreateEmptyString())
#endif
    {
#ifdef GFX_AS3_VERBOSE
        GetVM().GetStackTraceASString(StackTrace);
#endif
    }

    void Error::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0)
            AS3::Convert(message, argv[0]);

        if (argc > 1)
            AS3::Convert(ID, argv[1]);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Error::ti[Error::ThunkInfoNum] = {
        {TFunc_Instances_Error_errorIDGet::Func, &int_CI, "errorID", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Error_getStackTrace::Func, &StringCI, "getStackTrace", NULL, CT_Method, 0, 0},
    };
    const MemberInfo Error::mi[Error::MemberInfoNum] = {
        {"message", OFFSETOF(Instances::Error, message), SlotInfo::BT_String, 0},
        {"name", OFFSETOF(Instances::Error, name), SlotInfo::BT_String, 0},
    };


    Error::Error(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Error::Error()"
//##protect##"InstanceTraits::Error::Error()"
        SetMemSize(sizeof(Instances::Error));

    }

    Pickable<Instances::Error> Error::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Error>(new(t.Alloc()) Instances::Error(t));
    }

    void Error::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    const ThunkInfo Error::ti[Error::ThunkInfoNum] = {
        {TFunc_Instances_Error_toStringProto::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    Error::Error(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Error::Error()"
//##protect##"class_::Error::Error()"
    }
    void Error::getErrorMessage(ASString& result, SInt32 index)
    {
//##protect##"class_::Error::getErrorMessage()"
        SF_UNUSED2(result, index);
        NOT_IMPLEMENTED("class_::Error::getErrorMessage()");
//##protect##"class_::Error::getErrorMessage()"
    }
    void Error::throwError(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"class_::Error::throwError()"
        SF_UNUSED3(result, argc, argv);
        NOT_IMPLEMENTED("class_::Error::throwError()");
//##protect##"class_::Error::throwError()"
    }

    void Error::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        for (unsigned i = 0; i < NUMBEROF(ti); ++i)
            AddDynamicFunc(obj, ti[i]);
        AddConstructor(obj);
    }
//##protect##"class_$methods"
    void Error::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    Pickable<AS3::Object> Error::MakePrototype() const
    {
        InstanceTraits::Error& itr = static_cast<InstanceTraits::Error&>(GetClassTraits().GetInstanceTraits());
        return itr.MakeInstance(itr);
    }
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::Error, Classes::Error::mid_getErrorMessage, ASString, SInt32> TFunc_Classes_Error_getErrorMessage;
typedef ThunkFunc2<Classes::Error, Classes::Error::mid_throwError, Value, unsigned, const Value*> TFunc_Classes_Error_throwError;

template <> const TFunc_Classes_Error_getErrorMessage::TMethod TFunc_Classes_Error_getErrorMessage::Method = &Classes::Error::getErrorMessage;
template <> const TFunc_Classes_Error_throwError::TMethod TFunc_Classes_Error_throwError::Method = &Classes::Error::throwError;

namespace ClassTraits
{
    const ThunkInfo Error::ti[Error::ThunkInfoNum] = {
        {TFunc_Classes_Error_getErrorMessage::Func, &StringCI, "getErrorMessage", NULL, CT_Method, 1, 1},
        {TFunc_Classes_Error_throwError::Func, NULL, "throwError", NULL, CT_Method, 0, 1023},
    };
    Error::Error(VM& vm)
    : Traits(vm, ErrorCI)
    {
//##protect##"ClassTraits::Error::Error()"
//##protect##"ClassTraits::Error::Error()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Error(vm, ErrorCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Error(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Error::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Error(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ErrorCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "Error", "", &ObjectCI,
    ClassTraits::Error::MakeClassTraits,
    ClassTraits::Error::ThunkInfoNum,
    0,
    InstanceTraits::Error::ThunkInfoNum,
    InstanceTraits::Error::MemberInfoNum,
    ClassTraits::Error::ti,
    NULL,
    InstanceTraits::Error::ti,
    InstanceTraits::Error::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

