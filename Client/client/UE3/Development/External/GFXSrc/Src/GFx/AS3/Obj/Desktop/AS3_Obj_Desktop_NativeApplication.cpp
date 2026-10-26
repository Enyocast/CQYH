//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeApplication.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_NativeApplication.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeWindow;
    class InteractiveIcon;
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo NativeApplication_ti[32] = {
        {ThunkInfo::EmptyFunc, &XMLCI, "applicationDescriptor", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "applicationID", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "autoExit", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "autoExit", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &InteractiveIconCI, "icon", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "idleThreshold", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "idleThreshold", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "openedWindows", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "publisherID", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &uintCI, "runtimePatchLevel", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "runtimeVersion", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "startAtLogin", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "startAtLogin", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "timeSinceLastUserInput", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "activate", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "addEventListener", NULL, CT_Method, 2, 5},
        {ThunkInfo::EmptyFunc, &BooleanCI, "clear", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "copy", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "cut", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "dispatchEvent", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "exit", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "getDefaultApplication", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isSetAsDefaultApplication", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "paste", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "removeAsDefaultApplication", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "removeEventListener", NULL, CT_Method, 2, 3},
        {ThunkInfo::EmptyFunc, &BooleanCI, "selectAll", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setAsDefaultApplication", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "addEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 5},
        {ThunkInfo::EmptyFunc, &BooleanCI, "dispatchEvent", "flash.events:IEventDispatcher", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "removeEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 3},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeApplication::NativeApplication(VM& vm)
    : Traits(vm, NativeApplicationCI)
    {
//##protect##"ClassTraits::NativeApplication::NativeApplication()"
//##protect##"ClassTraits::NativeApplication::NativeApplication()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, NativeApplicationCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeApplication::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeApplication(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeApplicationCI = {
    ClassInfo::CompileTime,
    "NativeApplication", "flash.desktop", &EventDispatcherCI,
    ClassTraits::NativeApplication::MakeClassTraits,
    0,
    0,
    32,
    0,
    NULL,
    NULL,
    InstanceTraits::NativeApplication_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

