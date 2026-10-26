//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Loader.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Loader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
#include "AS3_Obj_Display_LoaderInfo.h"
#include "../System/AS3_Obj_System_LoaderContext.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/AS3/AS3_AvmLoader.h"
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
    bool GetMethodDefArg<Instances::Loader, Instances::Loader::mid_unloadAndStop, 0, bool>(AS3::StringManager&)
    {
        return true;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::Loader, Instances::Loader::mid_contentGet, Value> TFunc_Instances_Loader_contentGet;
typedef ThunkFunc0<Instances::Loader, Instances::Loader::mid_contentLoaderInfoGet, Value> TFunc_Instances_Loader_contentLoaderInfoGet;
typedef ThunkFunc0<Instances::Loader, Instances::Loader::mid_close, Value> TFunc_Instances_Loader_close;
typedef ThunkFunc2<Instances::Loader, Instances::Loader::mid_load, Value, Instances::URLRequest*, Instances::LoaderContext*> TFunc_Instances_Loader_load;
typedef ThunkFunc2<Instances::Loader, Instances::Loader::mid_loadBytes, Value, Instances::ByteArray*, Instances::LoaderContext*> TFunc_Instances_Loader_loadBytes;
typedef ThunkFunc0<Instances::Loader, Instances::Loader::mid_unload, Value> TFunc_Instances_Loader_unload;
typedef ThunkFunc1<Instances::Loader, Instances::Loader::mid_unloadAndStop, Value, bool> TFunc_Instances_Loader_unloadAndStop;

template <> const TFunc_Instances_Loader_contentGet::TMethod TFunc_Instances_Loader_contentGet::Method = &Instances::Loader::contentGet;
template <> const TFunc_Instances_Loader_contentLoaderInfoGet::TMethod TFunc_Instances_Loader_contentLoaderInfoGet::Method = &Instances::Loader::contentLoaderInfoGet;
template <> const TFunc_Instances_Loader_close::TMethod TFunc_Instances_Loader_close::Method = &Instances::Loader::close;
template <> const TFunc_Instances_Loader_load::TMethod TFunc_Instances_Loader_load::Method = &Instances::Loader::load;
template <> const TFunc_Instances_Loader_loadBytes::TMethod TFunc_Instances_Loader_loadBytes::Method = &Instances::Loader::loadBytes;
template <> const TFunc_Instances_Loader_unload::TMethod TFunc_Instances_Loader_unload::Method = &Instances::Loader::unload;
template <> const TFunc_Instances_Loader_unloadAndStop::TMethod TFunc_Instances_Loader_unloadAndStop::Method = &Instances::Loader::unloadAndStop;

namespace Instances
{
    Loader::Loader(InstanceTraits::Traits& t)
    : Instances::DisplayObjectContainer(t)
//##protect##"instance::Loader::Loader()$data"
//##protect##"instance::Loader::Loader()$data"
    {
//##protect##"instance::Loader::Loader()$code"
//##protect##"instance::Loader::Loader()$code"
    }

    void Loader::contentGet(Value& result)
    {
//##protect##"instance::Loader::contentGet()"
        SF_UNUSED1(result);
        if (GetDisplayObjContainer()->GetNumChildren() > 0)
            getChildAt(result, 0); //?
        else
            result.SetNull();
//##protect##"instance::Loader::contentGet()"
    }
    void Loader::contentLoaderInfoGet(Value& result)
    {
//##protect##"instance::Loader::contentLoaderInfoGet()"
        SF_UNUSED1(result);
        result = pContentLoaderInfo;
//##protect##"instance::Loader::contentLoaderInfoGet()"
    }
    void Loader::close(Value& result)
    {
//##protect##"instance::Loader::close()"
        SF_UNUSED1(result);

        //?
        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();
        root->UnloadMovie(this);
//##protect##"instance::Loader::close()"
    }
    void Loader::load(Value& result, Instances::URLRequest* request, Instances::LoaderContext* context)
    {
//##protect##"instance::Loader::load()"
        SF_UNUSED3(result, request, context);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();

        // check if we need to unload already loaded movie first.
        if (pContentLoaderInfo && pContentLoaderInfo->GetContentDispObj())
            root->UnloadMovie(this);

        root->AddNewLoadQueueEntry(request, this);
//##protect##"instance::Loader::load()"
    }
    void Loader::loadBytes(Value& result, Instances::ByteArray* bytes, Instances::LoaderContext* context)
    {
//##protect##"instance::Loader::loadBytes()"
        SF_UNUSED3(result, bytes, context);

        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();

        // check if we need to unload already loaded movie first.
        if (pContentLoaderInfo && pContentLoaderInfo->GetContentDispObj())
            root->UnloadMovie(this);

        root->AddNewLoadQueueEntry(bytes, this);
//##protect##"instance::Loader::loadBytes()"
    }
    void Loader::unload(Value& result)
    {
//##protect##"instance::Loader::unload()"
        SF_UNUSED1(result);

        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();
        root->UnloadMovie(this);
//##protect##"instance::Loader::unload()"
    }
    void Loader::unloadAndStop(Value& result, bool gc)
    {
//##protect##"instance::Loader::unloadAndStop()"
        SF_UNUSED2(result, gc);

        // Tries to unload a child SWF and stops the execution from loaded SWFs. 
        // Tries to remove references to EventDispatcher, NetConnection, Timer, Sound, 
        // or Video objects of the child SWF file. The following occurs for the child SWF 
        // file and the child SWF file's display list:
        //    Sounds are stopped.
        //    Stage event listeners are removed.
        //    Event listeners for enterFrame, frameConstructed, exitFrame, activate and deactivate are removed.
        //    Timers are stopped.
        //    Camera and Microphone instances are detached (n/a)
        //    Movie clips are stopped.
        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* root = vm.GetMovieRoot();
        root->UnloadMovie(this, true, gc);
//##protect##"instance::Loader::unloadAndStop()"
    }

//##protect##"instance$methods"
    void Loader::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        DisplayObjectContainer::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<LoaderInfo, Mem_Stat>(prcc, pContentLoaderInfo, op SF_DEBUG_ARG(*this));
    }

    void Loader::InitInstance(bool extCall)
    {
        ASVM& vm        = static_cast<ASVM&>(GetVM());

        if (!extCall)
        {
            // create stage display object if the movieclip was created by
            // "new".
            // create a LoaderInfo object
            SPtr<AS3::Object> _class = vm.GetClass("flash.display.LoaderInfo");
            if (_class.GetPtr() == NULL)  
                SF_ASSERT(0);

            if (vm.ConstructInstance(pContentLoaderInfo, _class))
            {
            }
            else
                SF_ASSERT(0); //@TODO error handling

            pContentLoaderInfo->SetLoader(this);

            Loader::CreateStageObject();
            SF_ASSERT(pDispObj);
        }
        else
        {
            if (pDispObj)
            {
                Instances::DisplayObject* as3dobj = ToAvmDisplayObj(pDispObj)->GetAS3Obj();
                if (as3dobj && as3dobj->pLoaderInfo)
                    as3dobj->pLoaderInfo->SetLoader(this);
            }
        }
    }
    GFx::DisplayObject* Loader::CreateStageObject()
    {
        if (!pDispObj)
        {
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();

            pDispObj = *SF_HEAP_NEW(proot->GetMovieHeap()) 
                AS3::AvmLoader(proot, proot->GetMovieImpl()->GetMovieDefImpl(), NULL, ResourceId());

            ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);
            proot->AddScriptableMovieClip(GetDisplayObjContainer()); 
        }
        return pDispObj;
    }

    void Loader::ResetContent() { pContentLoaderInfo->ResetContent(); }

    void Loader::ExecuteProgressEvent(UPInt bytesLoaded, UPInt totalBytes)
    {
        if (pContentLoaderInfo)
            pContentLoaderInfo->ExecuteProgressEvent(bytesLoaded, totalBytes);
    }

    void Loader::ExecuteCompleteEvent()
    {
        if (pContentLoaderInfo)
            pContentLoaderInfo->ExecuteCompleteEvent();
    }
    static void ExecuteCompleteEventCFunc(const MovieRoot::ActionEntry& ae)
    {
        SF_ASSERT(ae.pAS3Obj);
        Loader* loader = static_cast<Loader*>(ae.pAS3Obj.GetPtr());
        loader->ExecuteCompleteEvent();
    }

    void Loader::QueueCompleteEvent()
    {
        if (pContentLoaderInfo)
        {
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();
            MovieRoot::ActionEntry* ae = proot->InsertEmptyAction(MovieRoot::AL_Manual);
            if (ae)
            {
                ae->SetAction(pDispObj, this, ExecuteCompleteEventCFunc);
            }
        }
    }

    static void ExecuteInitEventCFunc(const MovieRoot::ActionEntry& ae)
    {
        SF_ASSERT(ae.pAS3Obj);
        Loader* loader = static_cast<Loader*>(ae.pAS3Obj.GetPtr());
        loader->ExecuteInitEvent(ae.pCharacter);
		if (ae.pNLoadInitCL)
			ae.pNLoadInitCL->InitEventCallback();
    }
    void Loader::QueueInitEvent(GFx::DisplayObject* obj, Ptr<NotifyLoadInitC> pnLoadInitCL )
    {
        if (pContentLoaderInfo)
        {
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();
            MovieRoot::ActionEntry* ae = proot->InsertEmptyAction(MovieRoot::AL_Manual);
            if (ae)
            {
                ae->SetAction(pDispObj, this, ExecuteInitEventCFunc);
                ae->pCharacter		= obj;
				ae->pNLoadInitCL	= pnLoadInitCL;
            }
        }
    }
    void Loader::ExecuteInitEvent(GFx::DisplayObject* obj)
    {
        if (pContentLoaderInfo)
            pContentLoaderInfo->ExecuteInitEvent(obj);
    }
    void Loader::ExecuteErrorEvent(const char* url)
    {
        if (pContentLoaderInfo)
        {
            char buf[1024];
            SFsprintf(buf, sizeof(buf), "Error reading %s", url);
            pContentLoaderInfo->ExecuteErrorEvent(buf);
        }
    }

    void Loader::ExecuteOpenEvent()
    {
        if (pContentLoaderInfo)
            pContentLoaderInfo->ExecuteOpenEvent();
    }


    LoaderInfo* Loader::GetContentLoaderInfo() const
    {
        return pContentLoaderInfo;
    }
    AvmLoader* Loader::GetAvmLoader() const { return static_cast<AvmLoader*>(pDispObj.GetPtr()); }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Loader::ti[Loader::ThunkInfoNum] = {
        {TFunc_Instances_Loader_contentGet::Func, &DisplayObjectCI, "content", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Loader_contentLoaderInfoGet::Func, &LoaderInfoCI, "contentLoaderInfo", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Loader_close::Func, NULL, "close", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Loader_load::Func, NULL, "load", NULL, CT_Method, 1, 2},
        {TFunc_Instances_Loader_loadBytes::Func, NULL, "loadBytes", NULL, CT_Method, 1, 2},
        {TFunc_Instances_Loader_unload::Func, NULL, "unload", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Loader_unloadAndStop::Func, NULL, "unloadAndStop", NULL, CT_Method, 0, 1},
    };

    Loader::Loader(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Loader::Loader()"
        SetTraitsType(Traits_Loader);
//##protect##"InstanceTraits::Loader::Loader()"
        SetMemSize(sizeof(Instances::Loader));

    }

    Pickable<Instances::Loader> Loader::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Loader>(new(t.Alloc()) Instances::Loader(t));
    }

    void Loader::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Loader::Loader(VM& vm)
    : Traits(vm, LoaderCI)
    {
//##protect##"ClassTraits::Loader::Loader()"
        SetTraitsType(Traits_Loader);
//##protect##"ClassTraits::Loader::Loader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Loader(vm, LoaderCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Loader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Loader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo LoaderCI = {
    ClassInfo::CompileTime,
    "Loader", "flash.display", &DisplayObjectContainerCI,
    ClassTraits::Loader::MakeClassTraits,
    0,
    0,
    InstanceTraits::Loader::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Loader::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

