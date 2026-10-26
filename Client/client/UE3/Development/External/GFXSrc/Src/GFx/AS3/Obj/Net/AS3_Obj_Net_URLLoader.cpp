//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLLoader.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLLoader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_URLRequest.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "AS3_Obj_Net_URLVariables.h"
#include "../Events/AS3_Obj_Events_ProgressEvent.h"
#include "../Events/AS3_Obj_Events_IOErrorEvent.h"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc5<Instances::URLLoader, Instances::URLLoader::mid_addEventListener, Value, const ASString&, const Value&, bool, SInt32, bool> TFunc_Instances_URLLoader_addEventListener;
typedef ThunkFunc0<Instances::URLLoader, Instances::URLLoader::mid_close, Value> TFunc_Instances_URLLoader_close;
typedef ThunkFunc1<Instances::URLLoader, Instances::URLLoader::mid_load, Value, Instances::URLRequest*> TFunc_Instances_URLLoader_load;

template <> const TFunc_Instances_URLLoader_addEventListener::TMethod TFunc_Instances_URLLoader_addEventListener::Method = &Instances::URLLoader::addEventListener;
template <> const TFunc_Instances_URLLoader_close::TMethod TFunc_Instances_URLLoader_close::Method = &Instances::URLLoader::close;
template <> const TFunc_Instances_URLLoader_load::TMethod TFunc_Instances_URLLoader_load::Method = &Instances::URLLoader::load;

namespace Instances
{
    URLLoader::URLLoader(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
    , bytesLoaded(0)
    , bytesTotal(0)
    , data()
    , dataFormat(AS3::DefaultValue<ASString>(GetStringManager()))
//##protect##"instance::URLLoader::URLLoader()$data"
//##protect##"instance::URLLoader::URLLoader()$data"
    {
//##protect##"instance::URLLoader::URLLoader()$code"
        dataFormat = "text";
//##protect##"instance::URLLoader::URLLoader()$code"
    }

    void URLLoader::addEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture, SInt32 priority, bool useWeakReference)
    {
//##protect##"instance::URLLoader::addEventListener()"
        SF_UNUSED6(result, type, listener, useCapture, priority, useWeakReference);
        EventDispatcher::addEventListener(result, type, listener, useCapture, priority, useWeakReference);
//##protect##"instance::URLLoader::addEventListener()"
    }
    void URLLoader::close(Value& result)
    {
//##protect##"instance::URLLoader::close()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLLoader::close()");
//##protect##"instance::URLLoader::close()"
    }
    void URLLoader::load(Value& result, Instances::URLRequest* request)
    {
//##protect##"instance::URLLoader::load()"
        SF_UNUSED2(result, request);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();

        root->AddNewLoadQueueEntry(request, this);
//##protect##"instance::URLLoader::load()"
    }

//##protect##"instance$methods"
    bool URLLoader::IsLoadingVariables() const
    {
        return (dataFormat == "variables");
    }

    bool URLLoader::IsLoadingText() const
    {
        return (dataFormat == "text");
    }

    bool URLLoader::IsLoadingBinary() const
    {
        return (dataFormat == "binary");
    }

    void URLLoader::ExecuteProgressEvent(UInt32 bytesLoaded, UInt32 totalBytes)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        ASString evtName(asvm.GetBuiltin(AS3Builtin_progress));
        if (HasEventHandler(evtName, false))
        {
            this->bytesLoaded = bytesLoaded;
            this->bytesTotal  = totalBytes;
            SPtr<ProgressEvent> efe = CreateProgressEventObject(evtName);
            efe->Target  = this;
            efe->SetBytesLoaded(bytesLoaded);
            efe->SetBytesTotal(totalBytes);
            DispatchSingleEvent(efe, false);
        }
    }

    void URLLoader::ExecuteOpenEvent()
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

    void URLLoader::ExecuteCompleteEvent()
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

    void URLLoader::ExecuteErrorEvent(const char* errorStr)
    {
        SPtr<IOErrorEvent> efe = CreateIOErrorEventObject(errorStr);
        efe->Target  = this;
        DispatchSingleEvent(efe, false);
    }

    void URLLoader::SetVariablesDataString(const char* pdata)
    {
        // create URLVariables object    
        ASVM& vm        = static_cast<ASVM&>(GetVM());

        // create a LoaderInfo object
        SPtr<AS3::Object> _class = vm.GetClass("flash.net.URLVariables");
        if (_class.GetPtr() == NULL)  
            SF_ASSERT(0);

        ASString dataStr(GetVM().GetStringManager().CreateString(pdata));
        Value dataParams(dataStr);
        SPtr<URLVariables> varObj;
        if (vm.ConstructInstance(varObj, _class, 1, &dataParams))
        {
            data = varObj.GetPtr();
        }
        else
            SF_ASSERT(0);
    }

    void URLLoader::SetTextString(const char* pdata)
    {
        ASString dataStr(GetVM().GetStringManager().CreateString(pdata));
        data = Value(dataStr);
    }

    void URLLoader::SetBinaryData(const ArrayPOD<UByte>& binaryData)
    {
        // create URLVariables object    
        ASVM& vm        = static_cast<ASVM&>(GetVM());

        // create a LoaderInfo object
        SPtr<AS3::Object> _class = vm.GetClass("flash.utils.ByteArray");
        if (_class.GetPtr() == NULL)  
            SF_ASSERT(0);
        
        SPtr<ByteArray> arrObj;
        if (vm.ConstructInstance(arrObj, _class))
        {
            arrObj->Set(binaryData.GetDataPtr(), binaryData.GetSize());
            data = arrObj.GetPtr();
        }
        else
            SF_ASSERT(0);
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo URLLoader::ti[URLLoader::ThunkInfoNum] = {
        {TFunc_Instances_URLLoader_addEventListener::Func, NULL, "addEventListener", NULL, CT_Method, 2, 5},
        {TFunc_Instances_URLLoader_close::Func, NULL, "close", NULL, CT_Method, 0, 0},
        {TFunc_Instances_URLLoader_load::Func, NULL, "load", NULL, CT_Method, 1, 1},
        {TFunc_Instances_URLLoader_addEventListener::Func, NULL, "addEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 5},
    };
    const MemberInfo URLLoader::mi[URLLoader::MemberInfoNum] = {
        {"bytesLoaded", OFFSETOF(Instances::URLLoader, bytesLoaded), SlotInfo::BT_UInt, 0},
        {"bytesTotal", OFFSETOF(Instances::URLLoader, bytesTotal), SlotInfo::BT_UInt, 0},
        {"data", OFFSETOF(Instances::URLLoader, data), SlotInfo::BT_Value, 0},
        {"dataFormat", OFFSETOF(Instances::URLLoader, dataFormat), SlotInfo::BT_String, 0},
    };


    URLLoader::URLLoader(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::URLLoader::URLLoader()"
//##protect##"InstanceTraits::URLLoader::URLLoader()"
        SetMemSize(sizeof(Instances::URLLoader));

    }

    Pickable<Instances::URLLoader> URLLoader::MakeInstance(Traits& t)
    {
        return Pickable<Instances::URLLoader>(new(t.Alloc()) Instances::URLLoader(t));
    }

    void URLLoader::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    URLLoader::URLLoader(VM& vm)
    : Traits(vm, URLLoaderCI)
    {
//##protect##"ClassTraits::URLLoader::URLLoader()"
//##protect##"ClassTraits::URLLoader::URLLoader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::URLLoader(vm, URLLoaderCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLLoader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLLoader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLLoaderCI = {
    ClassInfo::CompileTime,
    "URLLoader", "flash.net", &EventDispatcherCI,
    ClassTraits::URLLoader::MakeClassTraits,
    0,
    0,
    InstanceTraits::URLLoader::ThunkInfoNum,
    InstanceTraits::URLLoader::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::URLLoader::ti,
    InstanceTraits::URLLoader::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

