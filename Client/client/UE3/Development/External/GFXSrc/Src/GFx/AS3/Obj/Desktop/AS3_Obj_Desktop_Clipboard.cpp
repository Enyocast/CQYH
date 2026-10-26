//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Clipboard.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_Clipboard.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    bool GetMethodDefArg<Instances::Clipboard, Instances::Clipboard::mid_setData, 2, bool>(AS3::StringManager&)
    {
        return true;
    }

    template <>
    SF_INLINE
    bool GetMethodDefArg<Instances::Clipboard, Instances::Clipboard::mid_setDataHandler, 2, bool>(AS3::StringManager&)
    {
        return true;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::Clipboard, Instances::Clipboard::mid_formatsGet, Value> TFunc_Instances_Clipboard_formatsGet;
typedef ThunkFunc0<Instances::Clipboard, Instances::Clipboard::mid_clear, Value> TFunc_Instances_Clipboard_clear;
typedef ThunkFunc1<Instances::Clipboard, Instances::Clipboard::mid_clearData, Value, const ASString&> TFunc_Instances_Clipboard_clearData;
typedef ThunkFunc2<Instances::Clipboard, Instances::Clipboard::mid_getData, Value, const ASString&, const ASString&> TFunc_Instances_Clipboard_getData;
typedef ThunkFunc1<Instances::Clipboard, Instances::Clipboard::mid_hasFormat, bool, const ASString&> TFunc_Instances_Clipboard_hasFormat;
typedef ThunkFunc3<Instances::Clipboard, Instances::Clipboard::mid_setData, bool, const ASString&, const Value&, bool> TFunc_Instances_Clipboard_setData;
typedef ThunkFunc3<Instances::Clipboard, Instances::Clipboard::mid_setDataHandler, bool, const ASString&, const Value&, bool> TFunc_Instances_Clipboard_setDataHandler;

template <> const TFunc_Instances_Clipboard_formatsGet::TMethod TFunc_Instances_Clipboard_formatsGet::Method = &Instances::Clipboard::formatsGet;
template <> const TFunc_Instances_Clipboard_clear::TMethod TFunc_Instances_Clipboard_clear::Method = &Instances::Clipboard::clear;
template <> const TFunc_Instances_Clipboard_clearData::TMethod TFunc_Instances_Clipboard_clearData::Method = &Instances::Clipboard::clearData;
template <> const TFunc_Instances_Clipboard_getData::TMethod TFunc_Instances_Clipboard_getData::Method = &Instances::Clipboard::getData;
template <> const TFunc_Instances_Clipboard_hasFormat::TMethod TFunc_Instances_Clipboard_hasFormat::Method = &Instances::Clipboard::hasFormat;
template <> const TFunc_Instances_Clipboard_setData::TMethod TFunc_Instances_Clipboard_setData::Method = &Instances::Clipboard::setData;
template <> const TFunc_Instances_Clipboard_setDataHandler::TMethod TFunc_Instances_Clipboard_setDataHandler::Method = &Instances::Clipboard::setDataHandler;

namespace Instances
{
    Clipboard::Clipboard(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Clipboard::Clipboard()$data"
//##protect##"instance::Clipboard::Clipboard()$data"
    {
//##protect##"instance::Clipboard::Clipboard()$code"
//##protect##"instance::Clipboard::Clipboard()$code"
    }

    void Clipboard::formatsGet(Value& result)
    {
//##protect##"instance::Clipboard::formatsGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::formatsGet()");
//##protect##"instance::Clipboard::formatsGet()"
    }
    void Clipboard::clear(Value& result)
    {
//##protect##"instance::Clipboard::clear()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::clear()");
//##protect##"instance::Clipboard::clear()"
    }
    void Clipboard::clearData(Value& result, const ASString& format)
    {
//##protect##"instance::Clipboard::clearData()"
        SF_UNUSED2(result, format);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::clearData()");
//##protect##"instance::Clipboard::clearData()"
    }
    void Clipboard::getData(Value& result, const ASString& format, const ASString& transferMode)
    {
//##protect##"instance::Clipboard::getData()"
        SF_UNUSED3(result, format, transferMode);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::getData()");
//##protect##"instance::Clipboard::getData()"
    }
    void Clipboard::hasFormat(bool& result, const ASString& format)
    {
//##protect##"instance::Clipboard::hasFormat()"
        SF_UNUSED2(result, format);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::hasFormat()");
//##protect##"instance::Clipboard::hasFormat()"
    }
    void Clipboard::setData(bool& result, const ASString& format, const Value& data, bool serializable)
    {
//##protect##"instance::Clipboard::setData()"
        SF_UNUSED4(result, format, data, serializable);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::setData()");
//##protect##"instance::Clipboard::setData()"
    }
    void Clipboard::setDataHandler(bool& result, const ASString& format, const Value& handler, bool serializable)
    {
//##protect##"instance::Clipboard::setDataHandler()"
        SF_UNUSED4(result, format, handler, serializable);
        WARN_NOT_IMPLEMENTED("instance::Clipboard::setDataHandler()");
//##protect##"instance::Clipboard::setDataHandler()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Clipboard::ti[Clipboard::ThunkInfoNum] = {
        {TFunc_Instances_Clipboard_formatsGet::Func, &ArrayCI, "formats", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Clipboard_clear::Func, NULL, "clear", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Clipboard_clearData::Func, NULL, "clearData", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Clipboard_getData::Func, &ObjectCI, "getData", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Clipboard_hasFormat::Func, &BooleanCI, "hasFormat", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Clipboard_setData::Func, &BooleanCI, "setData", NULL, CT_Method, 2, 3},
        {TFunc_Instances_Clipboard_setDataHandler::Func, &BooleanCI, "setDataHandler", NULL, CT_Method, 2, 3},
    };

    Clipboard::Clipboard(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Clipboard::Clipboard()"
//##protect##"InstanceTraits::Clipboard::Clipboard()"
        SetMemSize(sizeof(Instances::Clipboard));

    }

    Pickable<Instances::Clipboard> Clipboard::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Clipboard>(new(t.Alloc()) Instances::Clipboard(t));
    }

    void Clipboard::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Clipboard::Clipboard(VM& vm)
    : Traits(vm, ClipboardCI)
    {
//##protect##"ClassTraits::Clipboard::Clipboard()"
//##protect##"ClassTraits::Clipboard::Clipboard()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Clipboard(vm, ClipboardCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Clipboard::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Clipboard(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ClipboardCI = {
    ClassInfo::CompileTime,
    "Clipboard", "flash.desktop", &ObjectCI,
    ClassTraits::Clipboard::MakeClassTraits,
    0,
    0,
    InstanceTraits::Clipboard::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Clipboard::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

