//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLLoader.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLLoader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Html_HTMLHost.h"
#include "../Net/AS3_Obj_Net_URLRequest.h"
#include "../System/AS3_Obj_System_ApplicationDomain.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class HTMLHistoryItem;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo HTMLLoader_ti[49] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "authenticate", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "authenticate", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "cacheResponse", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "cacheResponse", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "contentHeight", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "contentWidth", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "hasFocusableContent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "height", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "height", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &uintCI, "historyLength", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "historyPosition", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "historyPosition", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &HTMLHostCI, "htmlHost", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "htmlHost", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "loaded", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "location", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "manageCookies", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "manageCookies", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "navigateInSystemBrowser", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "navigateInSystemBrowser", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "paintsDefaultBackground", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "paintsDefaultBackground", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "placeLoadStringContentInApplicationSandbox", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "placeLoadStringContentInApplicationSandbox", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ApplicationDomainCI, "runtimeApplicationDomain", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "runtimeApplicationDomain", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "scrollH", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scrollH", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "scrollV", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "scrollV", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "textEncodingFallback", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "textEncodingFallback", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "textEncodingOverride", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "textEncodingOverride", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "useCache", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "useCache", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "userAgent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "userAgent", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "width", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "width", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ObjectCI, "window", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "cancelLoad", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &HTMLHistoryItemCI, "getHistoryAt", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "historyBack", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "historyForward", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "historyGo", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "load", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "loadString", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "reload", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    HTMLLoader::HTMLLoader(VM& vm)
    : Traits(vm, HTMLLoaderCI)
    {
//##protect##"ClassTraits::HTMLLoader::HTMLLoader()"
//##protect##"ClassTraits::HTMLLoader::HTMLLoader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Sprite(vm, HTMLLoaderCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLLoader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLLoader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLLoaderCI = {
    ClassInfo::CompileTime,
    "HTMLLoader", "flash.html", &SpriteCI,
    ClassTraits::HTMLLoader::MakeClassTraits,
    0,
    0,
    49,
    0,
    NULL,
    NULL,
    InstanceTraits::HTMLLoader_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

