//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_LoaderInfo.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_LoaderInfo_H
#define INC_AS3_Obj_Display_LoaderInfo_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "AS3_Obj_Display_Loader.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class ApplicationDomain;
    class ByteArray;
    class Loader;
    class DisplayObject;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class LoaderInfo;
}

namespace InstanceTraits
{
    class LoaderInfo;
}

namespace Classes
{
    class LoaderInfo;
}

namespace Instances
{
    class LoaderInfo : public Instances::EventDispatcher
    {
        friend class InstanceTraits::LoaderInfo;
        
    public:
        typedef LoaderInfo SelfType;
        typedef Classes::LoaderInfo ClassType;
        typedef InstanceTraits::LoaderInfo TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::LoaderInfo"; }
#endif
    protected:
        LoaderInfo(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        void ForEachChild_GC(Collector* prcc, GcOp op) const;

    public:
        void ExecuteProgressEvent(UPInt bytesLoaded, UPInt totalBytes);
        void ExecuteCompleteEvent();
        void ExecuteErrorEvent(const char* errorStr);
        void ExecuteOpenEvent();
        void ExecuteInitEvent(GFx::DisplayObject* obj);
        void SetLoader(Loader* ploader) { pLoader = ploader; }
        void ResetContent() { Content = NULL; }
        
        GFx::DisplayObject* GetContentDispObj() const { return (Content) ? Content->pDispObj : 0; }
        void SetContent(DisplayObject* c) { Content = c; }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_actionScriptVersionGet, 
            mid_applicationDomainGet, 
            mid_bytesGet, 
            mid_bytesLoadedGet, 
            mid_bytesTotalGet, 
            mid_childAllowsParentGet, 
            mid_childSandboxBridgeGet, 
            mid_childSandboxBridgeSet, 
            mid_contentGet, 
            mid_contentTypeGet, 
            mid_frameRateGet, 
            mid_heightGet, 
            mid_loaderGet, 
            mid_loaderURLGet, 
            mid_parametersGet, 
            mid_parentAllowsChildGet, 
            mid_parentSandboxBridgeGet, 
            mid_parentSandboxBridgeSet, 
            mid_sameDomainGet, 
            mid_sharedEventsGet, 
            mid_swfVersionGet, 
            mid_urlGet, 
            mid_widthGet, 
        };
        void actionScriptVersionGet(UInt32& result);
        void applicationDomainGet(Value& result);
        void bytesGet(Value& result);
        void bytesLoadedGet(UInt32& result);
        void bytesTotalGet(UInt32& result);
        void childAllowsParentGet(bool& result);
        void childSandboxBridgeGet(Value& result);
        void childSandboxBridgeSet(Value& result, const Value& value);
        void contentGet(Value& result);
        void contentTypeGet(ASString& result);
        void frameRateGet(Value::Number& result);
        void heightGet(SInt32& result);
        void loaderGet(Value& result);
        void loaderURLGet(ASString& result);
        void parametersGet(Value& result);
        void parentAllowsChildGet(bool& result);
        void parentSandboxBridgeGet(Value& result);
        void parentSandboxBridgeSet(Value& result, const Value& value);
        void sameDomainGet(bool& result);
        void sharedEventsGet(Value& result);
        void swfVersionGet(UInt32& result);
        void urlGet(ASString& result);
        void widthGet(SInt32& result);

//##protect##"instance$data"
    protected:
        UInt32 BytesLoaded;
        UInt32 BytesTotal;
        SPtr<DisplayObject> Content;
        SPtr<Loader> pLoader;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class LoaderInfo : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::LoaderInfo"; }
#endif
    public:
        LoaderInfo(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::LoaderInfo> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 23 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class LoaderInfo : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::LoaderInfo"; }
#endif
    public:
        typedef Classes::LoaderInfo ClassType;

    public:
        LoaderInfo(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class LoaderInfo : public Class
    {
        friend class ClassTraits::LoaderInfo;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::LoaderInfo"; }
#endif
    public:
        typedef LoaderInfo SelfType;
        typedef LoaderInfo ClassType;
        
    private:
        LoaderInfo(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_getLoaderInfoByDefinition, 
        };
        void getLoaderInfoByDefinition(Value& result, const Value& object);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

