//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_LoaderInfo.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_LoaderInfo.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Display_Loader.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/AS3/AS3_AvmLoader.h"
#include "../Events/AS3_Obj_Events_ProgressEvent.h"
#include "../Events/AS3_Obj_Events_IOErrorEvent.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class ApplicationDomain;
    class ByteArray;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_actionScriptVersionGet, UInt32> TFunc_Instances_LoaderInfo_actionScriptVersionGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_applicationDomainGet, Value> TFunc_Instances_LoaderInfo_applicationDomainGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_bytesGet, Value> TFunc_Instances_LoaderInfo_bytesGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_bytesLoadedGet, UInt32> TFunc_Instances_LoaderInfo_bytesLoadedGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_bytesTotalGet, UInt32> TFunc_Instances_LoaderInfo_bytesTotalGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_childAllowsParentGet, bool> TFunc_Instances_LoaderInfo_childAllowsParentGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_childSandboxBridgeGet, Value> TFunc_Instances_LoaderInfo_childSandboxBridgeGet;
typedef ThunkFunc1<Instances::LoaderInfo, Instances::LoaderInfo::mid_childSandboxBridgeSet, Value, const Value&> TFunc_Instances_LoaderInfo_childSandboxBridgeSet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_contentGet, Value> TFunc_Instances_LoaderInfo_contentGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_contentTypeGet, ASString> TFunc_Instances_LoaderInfo_contentTypeGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_frameRateGet, Value::Number> TFunc_Instances_LoaderInfo_frameRateGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_heightGet, SInt32> TFunc_Instances_LoaderInfo_heightGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_loaderGet, Value> TFunc_Instances_LoaderInfo_loaderGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_loaderURLGet, ASString> TFunc_Instances_LoaderInfo_loaderURLGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_parametersGet, Value> TFunc_Instances_LoaderInfo_parametersGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_parentAllowsChildGet, bool> TFunc_Instances_LoaderInfo_parentAllowsChildGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_parentSandboxBridgeGet, Value> TFunc_Instances_LoaderInfo_parentSandboxBridgeGet;
typedef ThunkFunc1<Instances::LoaderInfo, Instances::LoaderInfo::mid_parentSandboxBridgeSet, Value, const Value&> TFunc_Instances_LoaderInfo_parentSandboxBridgeSet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_sameDomainGet, bool> TFunc_Instances_LoaderInfo_sameDomainGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_sharedEventsGet, Value> TFunc_Instances_LoaderInfo_sharedEventsGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_swfVersionGet, UInt32> TFunc_Instances_LoaderInfo_swfVersionGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_urlGet, ASString> TFunc_Instances_LoaderInfo_urlGet;
typedef ThunkFunc0<Instances::LoaderInfo, Instances::LoaderInfo::mid_widthGet, SInt32> TFunc_Instances_LoaderInfo_widthGet;

template <> const TFunc_Instances_LoaderInfo_actionScriptVersionGet::TMethod TFunc_Instances_LoaderInfo_actionScriptVersionGet::Method = &Instances::LoaderInfo::actionScriptVersionGet;
template <> const TFunc_Instances_LoaderInfo_applicationDomainGet::TMethod TFunc_Instances_LoaderInfo_applicationDomainGet::Method = &Instances::LoaderInfo::applicationDomainGet;
template <> const TFunc_Instances_LoaderInfo_bytesGet::TMethod TFunc_Instances_LoaderInfo_bytesGet::Method = &Instances::LoaderInfo::bytesGet;
template <> const TFunc_Instances_LoaderInfo_bytesLoadedGet::TMethod TFunc_Instances_LoaderInfo_bytesLoadedGet::Method = &Instances::LoaderInfo::bytesLoadedGet;
template <> const TFunc_Instances_LoaderInfo_bytesTotalGet::TMethod TFunc_Instances_LoaderInfo_bytesTotalGet::Method = &Instances::LoaderInfo::bytesTotalGet;
template <> const TFunc_Instances_LoaderInfo_childAllowsParentGet::TMethod TFunc_Instances_LoaderInfo_childAllowsParentGet::Method = &Instances::LoaderInfo::childAllowsParentGet;
template <> const TFunc_Instances_LoaderInfo_childSandboxBridgeGet::TMethod TFunc_Instances_LoaderInfo_childSandboxBridgeGet::Method = &Instances::LoaderInfo::childSandboxBridgeGet;
template <> const TFunc_Instances_LoaderInfo_childSandboxBridgeSet::TMethod TFunc_Instances_LoaderInfo_childSandboxBridgeSet::Method = &Instances::LoaderInfo::childSandboxBridgeSet;
template <> const TFunc_Instances_LoaderInfo_contentGet::TMethod TFunc_Instances_LoaderInfo_contentGet::Method = &Instances::LoaderInfo::contentGet;
template <> const TFunc_Instances_LoaderInfo_contentTypeGet::TMethod TFunc_Instances_LoaderInfo_contentTypeGet::Method = &Instances::LoaderInfo::contentTypeGet;
template <> const TFunc_Instances_LoaderInfo_frameRateGet::TMethod TFunc_Instances_LoaderInfo_frameRateGet::Method = &Instances::LoaderInfo::frameRateGet;
template <> const TFunc_Instances_LoaderInfo_heightGet::TMethod TFunc_Instances_LoaderInfo_heightGet::Method = &Instances::LoaderInfo::heightGet;
template <> const TFunc_Instances_LoaderInfo_loaderGet::TMethod TFunc_Instances_LoaderInfo_loaderGet::Method = &Instances::LoaderInfo::loaderGet;
template <> const TFunc_Instances_LoaderInfo_loaderURLGet::TMethod TFunc_Instances_LoaderInfo_loaderURLGet::Method = &Instances::LoaderInfo::loaderURLGet;
template <> const TFunc_Instances_LoaderInfo_parametersGet::TMethod TFunc_Instances_LoaderInfo_parametersGet::Method = &Instances::LoaderInfo::parametersGet;
template <> const TFunc_Instances_LoaderInfo_parentAllowsChildGet::TMethod TFunc_Instances_LoaderInfo_parentAllowsChildGet::Method = &Instances::LoaderInfo::parentAllowsChildGet;
template <> const TFunc_Instances_LoaderInfo_parentSandboxBridgeGet::TMethod TFunc_Instances_LoaderInfo_parentSandboxBridgeGet::Method = &Instances::LoaderInfo::parentSandboxBridgeGet;
template <> const TFunc_Instances_LoaderInfo_parentSandboxBridgeSet::TMethod TFunc_Instances_LoaderInfo_parentSandboxBridgeSet::Method = &Instances::LoaderInfo::parentSandboxBridgeSet;
template <> const TFunc_Instances_LoaderInfo_sameDomainGet::TMethod TFunc_Instances_LoaderInfo_sameDomainGet::Method = &Instances::LoaderInfo::sameDomainGet;
template <> const TFunc_Instances_LoaderInfo_sharedEventsGet::TMethod TFunc_Instances_LoaderInfo_sharedEventsGet::Method = &Instances::LoaderInfo::sharedEventsGet;
template <> const TFunc_Instances_LoaderInfo_swfVersionGet::TMethod TFunc_Instances_LoaderInfo_swfVersionGet::Method = &Instances::LoaderInfo::swfVersionGet;
template <> const TFunc_Instances_LoaderInfo_urlGet::TMethod TFunc_Instances_LoaderInfo_urlGet::Method = &Instances::LoaderInfo::urlGet;
template <> const TFunc_Instances_LoaderInfo_widthGet::TMethod TFunc_Instances_LoaderInfo_widthGet::Method = &Instances::LoaderInfo::widthGet;

namespace Instances
{
    LoaderInfo::LoaderInfo(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::LoaderInfo::LoaderInfo()$data"
//##protect##"instance::LoaderInfo::LoaderInfo()$data"
    {
//##protect##"instance::LoaderInfo::LoaderInfo()$code"
        BytesLoaded = BytesTotal = 0;
//##protect##"instance::LoaderInfo::LoaderInfo()$code"
    }

    void LoaderInfo::actionScriptVersionGet(UInt32& result)
    {
//##protect##"instance::LoaderInfo::actionScriptVersionGet()"
        SF_UNUSED1(result);
        result = 3; // only as3 is supported for now.
//##protect##"instance::LoaderInfo::actionScriptVersionGet()"
    }
    void LoaderInfo::applicationDomainGet(Value& result)
    {
//##protect##"instance::LoaderInfo::applicationDomainGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.GetLog())
            asvm.GetLog()->LogWarning("LoaderInfo::applicationDomainGet() is not supported.");
        result.SetNull();
//##protect##"instance::LoaderInfo::applicationDomainGet()"
    }
    void LoaderInfo::bytesGet(Value& result)
    {
//##protect##"instance::LoaderInfo::bytesGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::bytesGet()");
//##protect##"instance::LoaderInfo::bytesGet()"
    }
    void LoaderInfo::bytesLoadedGet(UInt32& result)
    {
//##protect##"instance::LoaderInfo::bytesLoadedGet()"
        SF_UNUSED1(result);
        if (GetContentDispObj())
            result = GetContentDispObj()->GetResourceMovieDef()->GetBytesLoaded();
        else
            result = (UInt32) BytesLoaded;
//##protect##"instance::LoaderInfo::bytesLoadedGet()"
    }
    void LoaderInfo::bytesTotalGet(UInt32& result)
    {
//##protect##"instance::LoaderInfo::bytesTotalGet()"
        SF_UNUSED1(result);
        if (GetContentDispObj())
            result = GetContentDispObj()->GetResourceMovieDef()->GetFileBytes();
        else
            result = (UInt32) BytesTotal;
//##protect##"instance::LoaderInfo::bytesTotalGet()"
    }
    void LoaderInfo::childAllowsParentGet(bool& result)
    {
//##protect##"instance::LoaderInfo::childAllowsParentGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::childAllowsParentGet()");
//##protect##"instance::LoaderInfo::childAllowsParentGet()"
    }
    void LoaderInfo::childSandboxBridgeGet(Value& result)
    {
//##protect##"instance::LoaderInfo::childSandboxBridgeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::childSandboxBridgeGet()");
//##protect##"instance::LoaderInfo::childSandboxBridgeGet()"
    }
    void LoaderInfo::childSandboxBridgeSet(Value& result, const Value& value)
    {
//##protect##"instance::LoaderInfo::childSandboxBridgeSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("LoaderInfo::childSandboxBridgeSet()");
//##protect##"instance::LoaderInfo::childSandboxBridgeSet()"
    }
    void LoaderInfo::contentGet(Value& result)
    {
//##protect##"instance::LoaderInfo::contentGet()"
        result = Content;
//##protect##"instance::LoaderInfo::contentGet()"
    }
    void LoaderInfo::contentTypeGet(ASString& result)
    {
//##protect##"instance::LoaderInfo::contentTypeGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            MovieDefImpl* def = GetContentDispObj()->GetResourceMovieDef();
            if (def->GetDataDef()->MovieType == MovieDataDef::MT_Flash)
                result = "application/x-shockwave-flash";
            else if (def->GetDataDef()->MovieType == MovieDataDef::MT_Image)
                result = "image";
            else
                result = "unknown";
        }
        else
            result = "unknown"; //?
//##protect##"instance::LoaderInfo::contentTypeGet()"
    }
    void LoaderInfo::frameRateGet(Value::Number& result)
    {
//##protect##"instance::LoaderInfo::frameRateGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            result = (Value::Number)GetContentDispObj()->GetResourceMovieDef()->GetFrameRate();
        }
        else
            result = 0;
//##protect##"instance::LoaderInfo::frameRateGet()"
    }
    void LoaderInfo::heightGet(SInt32& result)
    {
//##protect##"instance::LoaderInfo::heightGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            result = (SInt32)GetContentDispObj()->GetResourceMovieDef()->GetHeight();
        }
        else
            result = 0;
//##protect##"instance::LoaderInfo::heightGet()"
    }
    void LoaderInfo::loaderGet(Value& result)
    {
//##protect##"instance::LoaderInfo::loaderGet()"
        result = pLoader;
//##protect##"instance::LoaderInfo::loaderGet()"
    }
    void LoaderInfo::loaderURLGet(ASString& result)
    {
//##protect##"instance::LoaderInfo::loaderURLGet()"
        SF_UNUSED1(result);
        if (pLoader)
        {
            result = GetVM().GetStringManager().CreateString(pLoader->GetAvmLoader()->GetResourceMovieDef()->GetFileURL());
        }
        else
            result = GetVM().GetStringManager().CreateEmptyString();
//##protect##"instance::LoaderInfo::loaderURLGet()"
    }
    void LoaderInfo::parametersGet(Value& result)
    {
//##protect##"instance::LoaderInfo::parametersGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::parametersGet()");
//##protect##"instance::LoaderInfo::parametersGet()"
    }
    void LoaderInfo::parentAllowsChildGet(bool& result)
    {
//##protect##"instance::LoaderInfo::parentAllowsChildGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::parentAllowsChildGet()");
//##protect##"instance::LoaderInfo::parentAllowsChildGet()"
    }
    void LoaderInfo::parentSandboxBridgeGet(Value& result)
    {
//##protect##"instance::LoaderInfo::parentSandboxBridgeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::parentSandboxBridgeGet()");
//##protect##"instance::LoaderInfo::parentSandboxBridgeGet()"
    }
    void LoaderInfo::parentSandboxBridgeSet(Value& result, const Value& value)
    {
//##protect##"instance::LoaderInfo::parentSandboxBridgeSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("LoaderInfo::parentSandboxBridgeSet()");
//##protect##"instance::LoaderInfo::parentSandboxBridgeSet()"
    }
    void LoaderInfo::sameDomainGet(bool& result)
    {
//##protect##"instance::LoaderInfo::sameDomainGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::sameDomainGet()");
//##protect##"instance::LoaderInfo::sameDomainGet()"
    }
    void LoaderInfo::sharedEventsGet(Value& result)
    {
//##protect##"instance::LoaderInfo::sharedEventsGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("LoaderInfo::sharedEventsGet()");
//##protect##"instance::LoaderInfo::sharedEventsGet()"
    }
    void LoaderInfo::swfVersionGet(UInt32& result)
    {
//##protect##"instance::LoaderInfo::swfVersionGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            result = (UInt32)GetContentDispObj()->GetResourceMovieDef()->GetVersion();
        }
        else
            result = 0;
//##protect##"instance::LoaderInfo::swfVersionGet()"
    }
    void LoaderInfo::urlGet(ASString& result)
    {
//##protect##"instance::LoaderInfo::urlGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            result = GetVM().GetStringManager().CreateString(
                GetContentDispObj()->GetResourceMovieDef()->GetFileURL());
        }
        else
            result = GetVM().GetStringManager().CreateEmptyString();
//##protect##"instance::LoaderInfo::urlGet()"
    }
    void LoaderInfo::widthGet(SInt32& result)
    {
//##protect##"instance::LoaderInfo::widthGet()"
        SF_UNUSED1(result);
        if (Content)
        {
            result = (SInt32)GetContentDispObj()->GetResourceMovieDef()->GetWidth();
        }
        else
            result = 0;
//##protect##"instance::LoaderInfo::widthGet()"
    }

//##protect##"instance$methods"
    void LoaderInfo::ExecuteProgressEvent(UPInt bytesLoaded, UPInt totalBytes)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString evtName(asvm.GetBuiltin(AS3Builtin_progress));
        if (HasEventHandler(evtName, false))
        {
            SPtr<ProgressEvent> efe = CreateProgressEventObject(evtName);
            efe->Target  = this;
            BytesLoaded = static_cast<UInt32>(bytesLoaded);
            BytesTotal  = static_cast<UInt32>(totalBytes);
            efe->SetBytesLoaded(bytesLoaded);
            efe->SetBytesTotal(totalBytes);
            DispatchSingleEvent(efe, false);
        }
    }

    void LoaderInfo::ExecuteCompleteEvent()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString evtName(asvm.GetBuiltin(AS3Builtin_complete));
        if (HasEventHandler(evtName, false))
        {
            SPtr<Event> efe = CreateEventObject(evtName);
            efe->Target  = this;
            DispatchSingleEvent(efe, false);
        }
    }

    void LoaderInfo::ExecuteErrorEvent(const char* errorStr)
    {
        SPtr<IOErrorEvent> efe = CreateIOErrorEventObject(errorStr);
        efe->Target  = this;
        DispatchSingleEvent(efe, false);
    }

    void LoaderInfo::ExecuteOpenEvent()
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString evtName(asvm.GetBuiltin(AS3Builtin_open));
        if (HasEventHandler(evtName, false))
        {
            SPtr<Event> efe = CreateEventObject(evtName);
            efe->Target  = this;
            DispatchSingleEvent(efe, false);
        }
    }

    void LoaderInfo::ExecuteInitEvent(GFx::DisplayObject* obj)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString evtName(asvm.GetBuiltin(AS3Builtin_init));
        if (obj)
        {
            ToAvmDisplayObj(obj)->CreateASInstance(true); 
            Content = ToAvmDisplayObj(obj)->GetAS3Obj();
        }
        if (HasEventHandler(evtName, false))
        {
            SPtr<Event> efe = CreateEventObject(evtName);
            efe->Target  = this;
            DispatchSingleEvent(efe, false);
        }
    }

    void LoaderInfo::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::EventDispatcher::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<DisplayObject, Mem_Stat>(prcc, Content, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC<Loader, Mem_Stat>(prcc, pLoader, op SF_DEBUG_ARG(*this));
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo LoaderInfo::ti[LoaderInfo::ThunkInfoNum] = {
        {TFunc_Instances_LoaderInfo_actionScriptVersionGet::Func, &uintCI, "actionScriptVersion", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_applicationDomainGet::Func, &ApplicationDomainCI, "applicationDomain", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_bytesGet::Func, &ByteArrayCI, "bytes", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_bytesLoadedGet::Func, &uintCI, "bytesLoaded", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_bytesTotalGet::Func, &uintCI, "bytesTotal", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_childAllowsParentGet::Func, &BooleanCI, "childAllowsParent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_childSandboxBridgeGet::Func, &ObjectCI, "childSandboxBridge", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_childSandboxBridgeSet::Func, NULL, "childSandboxBridge", NULL, CT_Set, 1, 1},
        {TFunc_Instances_LoaderInfo_contentGet::Func, &DisplayObjectCI, "content", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_contentTypeGet::Func, &StringCI, "contentType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_frameRateGet::Func, &NumberCI, "frameRate", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_heightGet::Func, &int_CI, "height", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_loaderGet::Func, &LoaderCI, "loader", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_loaderURLGet::Func, &StringCI, "loaderURL", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_parametersGet::Func, &ObjectCI, "parameters", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_parentAllowsChildGet::Func, &BooleanCI, "parentAllowsChild", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_parentSandboxBridgeGet::Func, &ObjectCI, "parentSandboxBridge", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_parentSandboxBridgeSet::Func, NULL, "parentSandboxBridge", NULL, CT_Set, 1, 1},
        {TFunc_Instances_LoaderInfo_sameDomainGet::Func, &BooleanCI, "sameDomain", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_sharedEventsGet::Func, &EventDispatcherCI, "sharedEvents", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_swfVersionGet::Func, &uintCI, "swfVersion", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_urlGet::Func, &StringCI, "url", NULL, CT_Get, 0, 0},
        {TFunc_Instances_LoaderInfo_widthGet::Func, &int_CI, "width", NULL, CT_Get, 0, 0},
    };

    LoaderInfo::LoaderInfo(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::LoaderInfo::LoaderInfo()"
//##protect##"InstanceTraits::LoaderInfo::LoaderInfo()"
        SetMemSize(sizeof(Instances::LoaderInfo));

    }

    Pickable<Instances::LoaderInfo> LoaderInfo::MakeInstance(Traits& t)
    {
        return Pickable<Instances::LoaderInfo>(new(t.Alloc()) Instances::LoaderInfo(t));
    }

    void LoaderInfo::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    LoaderInfo::LoaderInfo(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::LoaderInfo::LoaderInfo()"
//##protect##"class_::LoaderInfo::LoaderInfo()"
    }
    void LoaderInfo::getLoaderInfoByDefinition(Value& result, const Value& object)
    {
//##protect##"class_::LoaderInfo::getLoaderInfoByDefinition()"
        SF_UNUSED2(result, object);
        WARN_NOT_IMPLEMENTED("class_::LoaderInfo::getLoaderInfoByDefinition()");
//##protect##"class_::LoaderInfo::getLoaderInfoByDefinition()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::LoaderInfo, Classes::LoaderInfo::mid_getLoaderInfoByDefinition, Value, const Value&> TFunc_Classes_LoaderInfo_getLoaderInfoByDefinition;

template <> const TFunc_Classes_LoaderInfo_getLoaderInfoByDefinition::TMethod TFunc_Classes_LoaderInfo_getLoaderInfoByDefinition::Method = &Classes::LoaderInfo::getLoaderInfoByDefinition;

namespace ClassTraits
{
    const ThunkInfo LoaderInfo::ti[LoaderInfo::ThunkInfoNum] = {
        {TFunc_Classes_LoaderInfo_getLoaderInfoByDefinition::Func, &LoaderInfoCI, "getLoaderInfoByDefinition", NULL, CT_Method, 1, 1},
    };
    LoaderInfo::LoaderInfo(VM& vm)
    : Traits(vm, LoaderInfoCI)
    {
//##protect##"ClassTraits::LoaderInfo::LoaderInfo()"
//##protect##"ClassTraits::LoaderInfo::LoaderInfo()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::LoaderInfo(vm, LoaderInfoCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::LoaderInfo(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> LoaderInfo::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) LoaderInfo(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo LoaderInfoCI = {
    ClassInfo::CompileTime,
    "LoaderInfo", "flash.display", &EventDispatcherCI,
    ClassTraits::LoaderInfo::MakeClassTraits,
    ClassTraits::LoaderInfo::ThunkInfoNum,
    0,
    InstanceTraits::LoaderInfo::ThunkInfoNum,
    0,
    ClassTraits::LoaderInfo::ti,
    NULL,
    InstanceTraits::LoaderInfo::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

