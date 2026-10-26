//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLHost.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Html_HTMLHost.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "AS3_Obj_Html_HTMLWindowCreateOptions.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class HTMLLoader;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo HTMLHost_ti[10] = {
        {ThunkInfo::EmptyFunc, &HTMLLoaderCI, "htmlLoader", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &RectangleCI, "windowRect", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "windowRect", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &HTMLLoaderCI, "createWindow", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "updateLocation", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "updateStatus", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "updateTitle", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "windowBlur", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "windowClose", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "windowFocus", NULL, CT_Method, 0, 0},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    HTMLHost::HTMLHost(VM& vm)
    : Traits(vm, HTMLHostCI)
    {
//##protect##"ClassTraits::HTMLHost::HTMLHost()"
//##protect##"ClassTraits::HTMLHost::HTMLHost()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, HTMLHostCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> HTMLHost::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) HTMLHost(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo HTMLHostCI = {
    ClassInfo::CompileTime,
    "HTMLHost", "flash.html", &ObjectCI,
    ClassTraits::HTMLHost::MakeClassTraits,
    0,
    0,
    10,
    0,
    NULL,
    NULL,
    InstanceTraits::HTMLHost_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

