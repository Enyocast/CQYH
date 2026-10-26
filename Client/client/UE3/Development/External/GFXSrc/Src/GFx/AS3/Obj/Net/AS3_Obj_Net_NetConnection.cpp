//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_NetConnection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_NetConnection.h"
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
    Value GetMethodDefArg<Instances::NetConnection, Instances::NetConnection::mid_addHeader, 2, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

} // namespace Impl
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_clientGet, Value> TFunc_Instances_NetConnection_clientGet;
typedef ThunkFunc1<Instances::NetConnection, Instances::NetConnection::mid_clientSet, Value, const Value&> TFunc_Instances_NetConnection_clientSet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_connectedGet, bool> TFunc_Instances_NetConnection_connectedGet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_connectedProxyTypeGet, ASString> TFunc_Instances_NetConnection_connectedProxyTypeGet;
typedef ThunkFunc1<Instances::NetConnection, Instances::NetConnection::mid_defaultObjectEncodingSet, Value, UInt32> TFunc_Instances_NetConnection_defaultObjectEncodingSet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_objectEncodingGet, UInt32> TFunc_Instances_NetConnection_objectEncodingGet;
typedef ThunkFunc1<Instances::NetConnection, Instances::NetConnection::mid_objectEncodingSet, Value, UInt32> TFunc_Instances_NetConnection_objectEncodingSet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_proxyTypeGet, ASString> TFunc_Instances_NetConnection_proxyTypeGet;
typedef ThunkFunc1<Instances::NetConnection, Instances::NetConnection::mid_proxyTypeSet, Value, const ASString&> TFunc_Instances_NetConnection_proxyTypeSet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_uriGet, ASString> TFunc_Instances_NetConnection_uriGet;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_usingTLSGet, bool> TFunc_Instances_NetConnection_usingTLSGet;
typedef ThunkFunc3<Instances::NetConnection, Instances::NetConnection::mid_addHeader, Value, const ASString&, bool, const Value&> TFunc_Instances_NetConnection_addHeader;
typedef ThunkFunc2<Instances::NetConnection, Instances::NetConnection::mid_call, Value, unsigned, const Value*> TFunc_Instances_NetConnection_call;
typedef ThunkFunc0<Instances::NetConnection, Instances::NetConnection::mid_close, Value> TFunc_Instances_NetConnection_close;
typedef ThunkFunc2<Instances::NetConnection, Instances::NetConnection::mid_connect, Value, unsigned, const Value*> TFunc_Instances_NetConnection_connect;

template <> const TFunc_Instances_NetConnection_clientGet::TMethod TFunc_Instances_NetConnection_clientGet::Method = &Instances::NetConnection::clientGet;
template <> const TFunc_Instances_NetConnection_clientSet::TMethod TFunc_Instances_NetConnection_clientSet::Method = &Instances::NetConnection::clientSet;
template <> const TFunc_Instances_NetConnection_connectedGet::TMethod TFunc_Instances_NetConnection_connectedGet::Method = &Instances::NetConnection::connectedGet;
template <> const TFunc_Instances_NetConnection_connectedProxyTypeGet::TMethod TFunc_Instances_NetConnection_connectedProxyTypeGet::Method = &Instances::NetConnection::connectedProxyTypeGet;
template <> const TFunc_Instances_NetConnection_defaultObjectEncodingSet::TMethod TFunc_Instances_NetConnection_defaultObjectEncodingSet::Method = &Instances::NetConnection::defaultObjectEncodingSet;
template <> const TFunc_Instances_NetConnection_objectEncodingGet::TMethod TFunc_Instances_NetConnection_objectEncodingGet::Method = &Instances::NetConnection::objectEncodingGet;
template <> const TFunc_Instances_NetConnection_objectEncodingSet::TMethod TFunc_Instances_NetConnection_objectEncodingSet::Method = &Instances::NetConnection::objectEncodingSet;
template <> const TFunc_Instances_NetConnection_proxyTypeGet::TMethod TFunc_Instances_NetConnection_proxyTypeGet::Method = &Instances::NetConnection::proxyTypeGet;
template <> const TFunc_Instances_NetConnection_proxyTypeSet::TMethod TFunc_Instances_NetConnection_proxyTypeSet::Method = &Instances::NetConnection::proxyTypeSet;
template <> const TFunc_Instances_NetConnection_uriGet::TMethod TFunc_Instances_NetConnection_uriGet::Method = &Instances::NetConnection::uriGet;
template <> const TFunc_Instances_NetConnection_usingTLSGet::TMethod TFunc_Instances_NetConnection_usingTLSGet::Method = &Instances::NetConnection::usingTLSGet;
template <> const TFunc_Instances_NetConnection_addHeader::TMethod TFunc_Instances_NetConnection_addHeader::Method = &Instances::NetConnection::addHeader;
template <> const TFunc_Instances_NetConnection_call::TMethod TFunc_Instances_NetConnection_call::Method = &Instances::NetConnection::call;
template <> const TFunc_Instances_NetConnection_close::TMethod TFunc_Instances_NetConnection_close::Method = &Instances::NetConnection::close;
template <> const TFunc_Instances_NetConnection_connect::TMethod TFunc_Instances_NetConnection_connect::Method = &Instances::NetConnection::connect;

namespace Instances
{
    NetConnection::NetConnection(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::NetConnection::NetConnection()$data"
//##protect##"instance::NetConnection::NetConnection()$data"
    {
//##protect##"instance::NetConnection::NetConnection()$code"
//##protect##"instance::NetConnection::NetConnection()$code"
    }

    void NetConnection::clientGet(Value& result)
    {
//##protect##"instance::NetConnection::clientGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::clientGet()");
//##protect##"instance::NetConnection::clientGet()"
    }
    void NetConnection::clientSet(Value& result, const Value& value)
    {
//##protect##"instance::NetConnection::clientSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::clientSet()");
//##protect##"instance::NetConnection::clientSet()"
    }
    void NetConnection::connectedGet(bool& result)
    {
//##protect##"instance::NetConnection::connectedGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::connectedGet()");
//##protect##"instance::NetConnection::connectedGet()"
    }
    void NetConnection::connectedProxyTypeGet(ASString& result)
    {
//##protect##"instance::NetConnection::connectedProxyTypeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::connectedProxyTypeGet()");
//##protect##"instance::NetConnection::connectedProxyTypeGet()"
    }
    void NetConnection::defaultObjectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"instance::NetConnection::defaultObjectEncodingSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::defaultObjectEncodingSet()");
//##protect##"instance::NetConnection::defaultObjectEncodingSet()"
    }
    void NetConnection::objectEncodingGet(UInt32& result)
    {
//##protect##"instance::NetConnection::objectEncodingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::objectEncodingGet()");
//##protect##"instance::NetConnection::objectEncodingGet()"
    }
    void NetConnection::objectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"instance::NetConnection::objectEncodingSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::objectEncodingSet()");
//##protect##"instance::NetConnection::objectEncodingSet()"
    }
    void NetConnection::proxyTypeGet(ASString& result)
    {
//##protect##"instance::NetConnection::proxyTypeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::proxyTypeGet()");
//##protect##"instance::NetConnection::proxyTypeGet()"
    }
    void NetConnection::proxyTypeSet(Value& result, const ASString& value)
    {
//##protect##"instance::NetConnection::proxyTypeSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::proxyTypeSet()");
//##protect##"instance::NetConnection::proxyTypeSet()"
    }
    void NetConnection::uriGet(ASString& result)
    {
//##protect##"instance::NetConnection::uriGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::uriGet()");
//##protect##"instance::NetConnection::uriGet()"
    }
    void NetConnection::usingTLSGet(bool& result)
    {
//##protect##"instance::NetConnection::usingTLSGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::usingTLSGet()");
//##protect##"instance::NetConnection::usingTLSGet()"
    }
    void NetConnection::addHeader(Value& result, const ASString& operation, bool mustUnderstand, const Value& param)
    {
//##protect##"instance::NetConnection::addHeader()"
        SF_UNUSED4(result, operation, mustUnderstand, param);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::addHeader()");
//##protect##"instance::NetConnection::addHeader()"
    }
    void NetConnection::call(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::NetConnection::call()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::call()");
//##protect##"instance::NetConnection::call()"
    }
    void NetConnection::close(Value& result)
    {
//##protect##"instance::NetConnection::close()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::NetConnection::close()");
//##protect##"instance::NetConnection::close()"
    }
    void NetConnection::connect(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::NetConnection::connect()"
        SF_UNUSED3(result, argc, argv);
#ifndef GFX_ENABLE_VIDEO
        WARN_NOT_IMPLEMENTED("instance::NetConnection::connect()");
#endif
//##protect##"instance::NetConnection::connect()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo NetConnection::ti[NetConnection::ThunkInfoNum] = {
        {TFunc_Instances_NetConnection_clientGet::Func, &ObjectCI, "client", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_clientSet::Func, NULL, "client", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetConnection_connectedGet::Func, &BooleanCI, "connected", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_connectedProxyTypeGet::Func, &StringCI, "connectedProxyType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_defaultObjectEncodingSet::Func, NULL, "defaultObjectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetConnection_objectEncodingGet::Func, &uintCI, "objectEncoding", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_objectEncodingSet::Func, NULL, "objectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetConnection_proxyTypeGet::Func, &StringCI, "proxyType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_proxyTypeSet::Func, NULL, "proxyType", NULL, CT_Set, 1, 1},
        {TFunc_Instances_NetConnection_uriGet::Func, &StringCI, "uri", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_usingTLSGet::Func, &BooleanCI, "usingTLS", NULL, CT_Get, 0, 0},
        {TFunc_Instances_NetConnection_addHeader::Func, NULL, "addHeader", NULL, CT_Method, 1, 3},
        {TFunc_Instances_NetConnection_call::Func, NULL, "call", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_NetConnection_close::Func, NULL, "close", NULL, CT_Method, 0, 0},
        {TFunc_Instances_NetConnection_connect::Func, NULL, "connect", NULL, CT_Method, 0, 1023},
    };

    NetConnection::NetConnection(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::NetConnection::NetConnection()"
//##protect##"InstanceTraits::NetConnection::NetConnection()"
        SetMemSize(sizeof(Instances::NetConnection));

    }

    Pickable<Instances::NetConnection> NetConnection::MakeInstance(Traits& t)
    {
        return Pickable<Instances::NetConnection>(new(t.Alloc()) Instances::NetConnection(t));
    }

    void NetConnection::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    NetConnection::NetConnection(VM& vm)
    : Traits(vm, NetConnectionCI)
    {
//##protect##"ClassTraits::NetConnection::NetConnection()"
//##protect##"ClassTraits::NetConnection::NetConnection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::NetConnection(vm, NetConnectionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NetConnection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NetConnection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NetConnectionCI = {
    ClassInfo::CompileTime,
    "NetConnection", "flash.net", &EventDispatcherCI,
    ClassTraits::NetConnection::MakeClassTraits,
    0,
    0,
    InstanceTraits::NetConnection::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::NetConnection::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

