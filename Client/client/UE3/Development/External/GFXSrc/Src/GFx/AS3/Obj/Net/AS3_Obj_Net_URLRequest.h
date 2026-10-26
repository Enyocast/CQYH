//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequest.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLRequest_H
#define INC_AS3_Obj_Net_URLRequest_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLRequest;
}

namespace InstanceTraits
{
    class URLRequest;
}

namespace Classes
{
    class URLRequest;
}

namespace Instances
{
    class URLRequest : public Instances::Object
    {
        friend class InstanceTraits::URLRequest;
        
    public:
        typedef URLRequest SelfType;
        typedef Classes::URLRequest ClassType;
        typedef InstanceTraits::URLRequest TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::URLRequest"; }
#endif
    protected:
        URLRequest(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void    ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void    AS3Constructor(unsigned argc, const Value* argv);
    public:
        const ASString& GetUrl() const;

//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_authenticateGet, 
            mid_authenticateSet, 
            mid_cacheResponseGet, 
            mid_cacheResponseSet, 
            mid_contentTypeGet, 
            mid_contentTypeSet, 
            mid_dataGet, 
            mid_dataSet, 
            mid_digestGet, 
            mid_digestSet, 
            mid_followRedirectsGet, 
            mid_followRedirectsSet, 
            mid_manageCookiesGet, 
            mid_manageCookiesSet, 
            mid_methodGet, 
            mid_methodSet, 
            mid_requestHeadersGet, 
            mid_requestHeadersSet, 
            mid_urlGet, 
            mid_urlSet, 
            mid_useCacheGet, 
            mid_useCacheSet, 
            mid_userAgentGet, 
            mid_userAgentSet, 
        };
        void authenticateGet(bool& result);
        void authenticateSet(Value& result, bool value);
        void cacheResponseGet(bool& result);
        void cacheResponseSet(Value& result, bool value);
        void contentTypeGet(ASString& result);
        void contentTypeSet(Value& result, const ASString& value);
        void dataGet(Value& result);
        void dataSet(Value& result, const Value& value);
        void digestGet(ASString& result);
        void digestSet(Value& result, const ASString& value);
        void followRedirectsGet(bool& result);
        void followRedirectsSet(Value& result, bool value);
        void manageCookiesGet(bool& result);
        void manageCookiesSet(Value& result, bool value);
        void methodGet(ASString& result);
        void methodSet(Value& result, const ASString& value);
        void requestHeadersGet(Value& result);
        void requestHeadersSet(Value& result, Instances::Array* value);
        void urlGet(ASString& result);
        void urlSet(Value& result, const ASString& value);
        void useCacheGet(bool& result);
        void useCacheSet(Value& result, bool value);
        void userAgentGet(ASString& result);
        void userAgentSet(Value& result, const ASString& value);

//##protect##"instance$data"
    protected:
        ASString            Url;
        SPtr<AS3::Object>   DataObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class URLRequest : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::URLRequest"; }
#endif
    public:
        URLRequest(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::URLRequest> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 24 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class URLRequest : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLRequest"; }
#endif
    public:
        typedef Classes::URLRequest ClassType;

    public:
        URLRequest(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

