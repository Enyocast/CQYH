//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Loader.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Loader_H
#define INC_AS3_Obj_Display_Loader_H

#include "AS3_Obj_Display_DisplayObjectContainer.h"
//##protect##"includes"
#include "AS3_Obj_Display_DisplayObjectContainer.h"
#include "../Net/AS3_Obj_Net_URLRequest.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
class AvmLoader;

namespace Instances
{
    class URLRequest;
    class ByteArray;
    class LoaderContext;
}

class NotifyLoadInitC;

//##protect##"forward_declaration"

namespace ClassTraits
{
    class Loader;
}

namespace InstanceTraits
{
    class Loader;
}

namespace Classes
{
    class Loader;
}

namespace Instances
{
    class Loader : public Instances::DisplayObjectContainer
    {
        friend class InstanceTraits::Loader;
        
    public:
        typedef Loader SelfType;
        typedef Classes::Loader ClassType;
        typedef InstanceTraits::Loader TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Loader"; }
#endif
    protected:
        Loader(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
	public:
        virtual void InitInstance(bool extCall);
        virtual GFx::DisplayObject* CreateStageObject();

        AvmLoader* GetAvmLoader() const;

        LoaderInfo* GetContentLoaderInfo() const;
    public:
        void ExecuteProgressEvent(UPInt bytesLoaded, UPInt totalBytes);
        void ExecuteCompleteEvent();
        void QueueCompleteEvent();
        void QueueInitEvent(GFx::DisplayObject* obj, Ptr<NotifyLoadInitC> ptr);
        void ExecuteErrorEvent(const char* url);
        void ExecuteOpenEvent();
        void ExecuteInitEvent(GFx::DisplayObject* obj);
        void ResetContent();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_contentGet, 
            mid_contentLoaderInfoGet, 
            mid_close, 
            mid_load, 
            mid_loadBytes, 
            mid_unload, 
            mid_unloadAndStop, 
        };
        void contentGet(Value& result);
        void contentLoaderInfoGet(Value& result);
        void close(Value& result);
        void load(Value& result, Instances::URLRequest* request, Instances::LoaderContext* context);
        void loadBytes(Value& result, Instances::ByteArray* bytes, Instances::LoaderContext* context);
        void unload(Value& result);
        void unloadAndStop(Value& result, bool gc);

//##protect##"instance$data"
    protected:
        SPtr<LoaderInfo> pContentLoaderInfo;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Loader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Loader"; }
#endif
    public:
        Loader(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Loader> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 7 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Loader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Loader"; }
#endif
    public:
        typedef Classes::Loader ClassType;

    public:
        Loader(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

