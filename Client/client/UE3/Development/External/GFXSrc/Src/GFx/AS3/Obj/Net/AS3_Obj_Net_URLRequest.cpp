//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequest.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLRequest.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "AS3_Obj_Net_URLVariables.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_authenticateGet, bool> TFunc_Instances_URLRequest_authenticateGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_authenticateSet, Value, bool> TFunc_Instances_URLRequest_authenticateSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_cacheResponseGet, bool> TFunc_Instances_URLRequest_cacheResponseGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_cacheResponseSet, Value, bool> TFunc_Instances_URLRequest_cacheResponseSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_contentTypeGet, ASString> TFunc_Instances_URLRequest_contentTypeGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_contentTypeSet, Value, const ASString&> TFunc_Instances_URLRequest_contentTypeSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_dataGet, Value> TFunc_Instances_URLRequest_dataGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_dataSet, Value, const Value&> TFunc_Instances_URLRequest_dataSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_digestGet, ASString> TFunc_Instances_URLRequest_digestGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_digestSet, Value, const ASString&> TFunc_Instances_URLRequest_digestSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_followRedirectsGet, bool> TFunc_Instances_URLRequest_followRedirectsGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_followRedirectsSet, Value, bool> TFunc_Instances_URLRequest_followRedirectsSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_manageCookiesGet, bool> TFunc_Instances_URLRequest_manageCookiesGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_manageCookiesSet, Value, bool> TFunc_Instances_URLRequest_manageCookiesSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_methodGet, ASString> TFunc_Instances_URLRequest_methodGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_methodSet, Value, const ASString&> TFunc_Instances_URLRequest_methodSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_requestHeadersGet, Value> TFunc_Instances_URLRequest_requestHeadersGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_requestHeadersSet, Value, Instances::Array*> TFunc_Instances_URLRequest_requestHeadersSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_urlGet, ASString> TFunc_Instances_URLRequest_urlGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_urlSet, Value, const ASString&> TFunc_Instances_URLRequest_urlSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_useCacheGet, bool> TFunc_Instances_URLRequest_useCacheGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_useCacheSet, Value, bool> TFunc_Instances_URLRequest_useCacheSet;
typedef ThunkFunc0<Instances::URLRequest, Instances::URLRequest::mid_userAgentGet, ASString> TFunc_Instances_URLRequest_userAgentGet;
typedef ThunkFunc1<Instances::URLRequest, Instances::URLRequest::mid_userAgentSet, Value, const ASString&> TFunc_Instances_URLRequest_userAgentSet;

template <> const TFunc_Instances_URLRequest_authenticateGet::TMethod TFunc_Instances_URLRequest_authenticateGet::Method = &Instances::URLRequest::authenticateGet;
template <> const TFunc_Instances_URLRequest_authenticateSet::TMethod TFunc_Instances_URLRequest_authenticateSet::Method = &Instances::URLRequest::authenticateSet;
template <> const TFunc_Instances_URLRequest_cacheResponseGet::TMethod TFunc_Instances_URLRequest_cacheResponseGet::Method = &Instances::URLRequest::cacheResponseGet;
template <> const TFunc_Instances_URLRequest_cacheResponseSet::TMethod TFunc_Instances_URLRequest_cacheResponseSet::Method = &Instances::URLRequest::cacheResponseSet;
template <> const TFunc_Instances_URLRequest_contentTypeGet::TMethod TFunc_Instances_URLRequest_contentTypeGet::Method = &Instances::URLRequest::contentTypeGet;
template <> const TFunc_Instances_URLRequest_contentTypeSet::TMethod TFunc_Instances_URLRequest_contentTypeSet::Method = &Instances::URLRequest::contentTypeSet;
template <> const TFunc_Instances_URLRequest_dataGet::TMethod TFunc_Instances_URLRequest_dataGet::Method = &Instances::URLRequest::dataGet;
template <> const TFunc_Instances_URLRequest_dataSet::TMethod TFunc_Instances_URLRequest_dataSet::Method = &Instances::URLRequest::dataSet;
template <> const TFunc_Instances_URLRequest_digestGet::TMethod TFunc_Instances_URLRequest_digestGet::Method = &Instances::URLRequest::digestGet;
template <> const TFunc_Instances_URLRequest_digestSet::TMethod TFunc_Instances_URLRequest_digestSet::Method = &Instances::URLRequest::digestSet;
template <> const TFunc_Instances_URLRequest_followRedirectsGet::TMethod TFunc_Instances_URLRequest_followRedirectsGet::Method = &Instances::URLRequest::followRedirectsGet;
template <> const TFunc_Instances_URLRequest_followRedirectsSet::TMethod TFunc_Instances_URLRequest_followRedirectsSet::Method = &Instances::URLRequest::followRedirectsSet;
template <> const TFunc_Instances_URLRequest_manageCookiesGet::TMethod TFunc_Instances_URLRequest_manageCookiesGet::Method = &Instances::URLRequest::manageCookiesGet;
template <> const TFunc_Instances_URLRequest_manageCookiesSet::TMethod TFunc_Instances_URLRequest_manageCookiesSet::Method = &Instances::URLRequest::manageCookiesSet;
template <> const TFunc_Instances_URLRequest_methodGet::TMethod TFunc_Instances_URLRequest_methodGet::Method = &Instances::URLRequest::methodGet;
template <> const TFunc_Instances_URLRequest_methodSet::TMethod TFunc_Instances_URLRequest_methodSet::Method = &Instances::URLRequest::methodSet;
template <> const TFunc_Instances_URLRequest_requestHeadersGet::TMethod TFunc_Instances_URLRequest_requestHeadersGet::Method = &Instances::URLRequest::requestHeadersGet;
template <> const TFunc_Instances_URLRequest_requestHeadersSet::TMethod TFunc_Instances_URLRequest_requestHeadersSet::Method = &Instances::URLRequest::requestHeadersSet;
template <> const TFunc_Instances_URLRequest_urlGet::TMethod TFunc_Instances_URLRequest_urlGet::Method = &Instances::URLRequest::urlGet;
template <> const TFunc_Instances_URLRequest_urlSet::TMethod TFunc_Instances_URLRequest_urlSet::Method = &Instances::URLRequest::urlSet;
template <> const TFunc_Instances_URLRequest_useCacheGet::TMethod TFunc_Instances_URLRequest_useCacheGet::Method = &Instances::URLRequest::useCacheGet;
template <> const TFunc_Instances_URLRequest_useCacheSet::TMethod TFunc_Instances_URLRequest_useCacheSet::Method = &Instances::URLRequest::useCacheSet;
template <> const TFunc_Instances_URLRequest_userAgentGet::TMethod TFunc_Instances_URLRequest_userAgentGet::Method = &Instances::URLRequest::userAgentGet;
template <> const TFunc_Instances_URLRequest_userAgentSet::TMethod TFunc_Instances_URLRequest_userAgentSet::Method = &Instances::URLRequest::userAgentSet;

namespace Instances
{
    URLRequest::URLRequest(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::URLRequest::URLRequest()$data"
    , Url(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::URLRequest::URLRequest()$data"
    {
//##protect##"instance::URLRequest::URLRequest()$code"
//##protect##"instance::URLRequest::URLRequest()$code"
    }

    void URLRequest::authenticateGet(bool& result)
    {
//##protect##"instance::URLRequest::authenticateGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::authenticateGet()");
//##protect##"instance::URLRequest::authenticateGet()"
    }
    void URLRequest::authenticateSet(Value& result, bool value)
    {
//##protect##"instance::URLRequest::authenticateSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::authenticateSet()");
//##protect##"instance::URLRequest::authenticateSet()"
    }
    void URLRequest::cacheResponseGet(bool& result)
    {
//##protect##"instance::URLRequest::cacheResponseGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::cacheResponseGet()");
//##protect##"instance::URLRequest::cacheResponseGet()"
    }
    void URLRequest::cacheResponseSet(Value& result, bool value)
    {
//##protect##"instance::URLRequest::cacheResponseSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::cacheResponseSet()");
//##protect##"instance::URLRequest::cacheResponseSet()"
    }
    void URLRequest::contentTypeGet(ASString& result)
    {
//##protect##"instance::URLRequest::contentTypeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::contentTypeGet()");
//##protect##"instance::URLRequest::contentTypeGet()"
    }
    void URLRequest::contentTypeSet(Value& result, const ASString& value)
    {
//##protect##"instance::URLRequest::contentTypeSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::contentTypeSet()");
//##protect##"instance::URLRequest::contentTypeSet()"
    }
    void URLRequest::dataGet(Value& result)
    {
//##protect##"instance::URLRequest::dataGet()"
        SF_UNUSED1(result);
        result = DataObj;
//##protect##"instance::URLRequest::dataGet()"
    }
    void URLRequest::dataSet(Value& result, const Value& value)
    {
//##protect##"instance::URLRequest::dataSet()"
        SF_UNUSED2(result, value);
        if (value.IsObject())
            DataObj = value.GetObject();
//##protect##"instance::URLRequest::dataSet()"
    }
    void URLRequest::digestGet(ASString& result)
    {
//##protect##"instance::URLRequest::digestGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::digestGet()");
//##protect##"instance::URLRequest::digestGet()"
    }
    void URLRequest::digestSet(Value& result, const ASString& value)
    {
//##protect##"instance::URLRequest::digestSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::digestSet()");
//##protect##"instance::URLRequest::digestSet()"
    }
    void URLRequest::followRedirectsGet(bool& result)
    {
//##protect##"instance::URLRequest::followRedirectsGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::followRedirectsGet()");
//##protect##"instance::URLRequest::followRedirectsGet()"
    }
    void URLRequest::followRedirectsSet(Value& result, bool value)
    {
//##protect##"instance::URLRequest::followRedirectsSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::followRedirectsSet()");
//##protect##"instance::URLRequest::followRedirectsSet()"
    }
    void URLRequest::manageCookiesGet(bool& result)
    {
//##protect##"instance::URLRequest::manageCookiesGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::manageCookiesGet()");
//##protect##"instance::URLRequest::manageCookiesGet()"
    }
    void URLRequest::manageCookiesSet(Value& result, bool value)
    {
//##protect##"instance::URLRequest::manageCookiesSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::manageCookiesSet()");
//##protect##"instance::URLRequest::manageCookiesSet()"
    }
    void URLRequest::methodGet(ASString& result)
    {
//##protect##"instance::URLRequest::methodGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::methodGet()");
//##protect##"instance::URLRequest::methodGet()"
    }
    void URLRequest::methodSet(Value& result, const ASString& value)
    {
//##protect##"instance::URLRequest::methodSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::methodSet()");
//##protect##"instance::URLRequest::methodSet()"
    }
    void URLRequest::requestHeadersGet(Value& result)
    {
//##protect##"instance::URLRequest::requestHeadersGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::requestHeadersGet()");
//##protect##"instance::URLRequest::requestHeadersGet()"
    }
    void URLRequest::requestHeadersSet(Value& result, Instances::Array* value)
    {
//##protect##"instance::URLRequest::requestHeadersSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::requestHeadersSet()");
//##protect##"instance::URLRequest::requestHeadersSet()"
    }
    void URLRequest::urlGet(ASString& result)
    {
//##protect##"instance::URLRequest::urlGet()"
        SF_UNUSED1(result);
        result = Url;
//##protect##"instance::URLRequest::urlGet()"
    }
    void URLRequest::urlSet(Value& result, const ASString& value)
    {
//##protect##"instance::URLRequest::urlSet()"
        SF_UNUSED2(result, value);
        Url = value;
//##protect##"instance::URLRequest::urlSet()"
    }
    void URLRequest::useCacheGet(bool& result)
    {
//##protect##"instance::URLRequest::useCacheGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::useCacheGet()");
//##protect##"instance::URLRequest::useCacheGet()"
    }
    void URLRequest::useCacheSet(Value& result, bool value)
    {
//##protect##"instance::URLRequest::useCacheSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::useCacheSet()");
//##protect##"instance::URLRequest::useCacheSet()"
    }
    void URLRequest::userAgentGet(ASString& result)
    {
//##protect##"instance::URLRequest::userAgentGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("URLRequest::userAgentGet()");
//##protect##"instance::URLRequest::userAgentGet()"
    }
    void URLRequest::userAgentSet(Value& result, const ASString& value)
    {
//##protect##"instance::URLRequest::userAgentSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("URLRequest::userAgentSet()");
//##protect##"instance::URLRequest::userAgentSet()"
    }

//##protect##"instance$methods"
    void URLRequest::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Object::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<AS3::Object, Mem_Stat>(prcc, DataObj, op SF_DEBUG_ARG(*this));
    }

    void URLRequest::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1)
        {
            const Value& v = argv[0];

            // There is nothing to check. It it is a last statement.
            v.Convert2String(Url).DoNotCheck();
        }
    }

    const ASString& URLRequest::GetUrl() const
    {
        return Url;
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo URLRequest::ti[URLRequest::ThunkInfoNum] = {
        {TFunc_Instances_URLRequest_authenticateGet::Func, &BooleanCI, "authenticate", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_authenticateSet::Func, NULL, "authenticate", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_cacheResponseGet::Func, &BooleanCI, "cacheResponse", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_cacheResponseSet::Func, NULL, "cacheResponse", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_contentTypeGet::Func, &StringCI, "contentType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_contentTypeSet::Func, NULL, "contentType", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_dataGet::Func, &ObjectCI, "data", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_dataSet::Func, NULL, "data", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_digestGet::Func, &StringCI, "digest", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_digestSet::Func, NULL, "digest", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_followRedirectsGet::Func, &BooleanCI, "followRedirects", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_followRedirectsSet::Func, NULL, "followRedirects", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_manageCookiesGet::Func, &BooleanCI, "manageCookies", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_manageCookiesSet::Func, NULL, "manageCookies", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_methodGet::Func, &StringCI, "method", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_methodSet::Func, NULL, "method", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_requestHeadersGet::Func, &ArrayCI, "requestHeaders", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_requestHeadersSet::Func, NULL, "requestHeaders", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_urlGet::Func, &StringCI, "url", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_urlSet::Func, NULL, "url", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_useCacheGet::Func, &BooleanCI, "useCache", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_useCacheSet::Func, NULL, "useCache", NULL, CT_Set, 1, 1},
        {TFunc_Instances_URLRequest_userAgentGet::Func, &StringCI, "userAgent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_URLRequest_userAgentSet::Func, NULL, "userAgent", NULL, CT_Set, 1, 1},
    };

    URLRequest::URLRequest(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::URLRequest::URLRequest()"
//##protect##"InstanceTraits::URLRequest::URLRequest()"
        SetMemSize(sizeof(Instances::URLRequest));

    }

    Pickable<Instances::URLRequest> URLRequest::MakeInstance(Traits& t)
    {
        return Pickable<Instances::URLRequest>(new(t.Alloc()) Instances::URLRequest(t));
    }

    void URLRequest::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    URLRequest::URLRequest(VM& vm)
    : Traits(vm, URLRequestCI)
    {
//##protect##"ClassTraits::URLRequest::URLRequest()"
//##protect##"ClassTraits::URLRequest::URLRequest()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::URLRequest(vm, URLRequestCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLRequest::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLRequest(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLRequestCI = {
    ClassInfo::CompileTime,
    "URLRequest", "flash.net", &ObjectCI,
    ClassTraits::URLRequest::MakeClassTraits,
    0,
    0,
    InstanceTraits::URLRequest::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::URLRequest::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

