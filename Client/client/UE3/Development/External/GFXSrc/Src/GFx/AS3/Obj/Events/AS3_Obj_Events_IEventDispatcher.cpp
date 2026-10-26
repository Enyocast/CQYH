//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IEventDispatcher.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Events_IEventDispatcher.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Events_Event.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo IEventDispatcher_ti[5] = {
        {ThunkInfo::EmptyFunc, NULL, "addEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 5},
        {ThunkInfo::EmptyFunc, &BooleanCI, "dispatchEvent", "flash.events:IEventDispatcher", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "hasEventListener", "flash.events:IEventDispatcher", CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "removeEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 3},
        {ThunkInfo::EmptyFunc, &BooleanCI, "willTrigger", "flash.events:IEventDispatcher", CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    IEventDispatcher::IEventDispatcher(VM& vm)
    : Traits(vm, IEventDispatcherCI)
    {
//##protect##"ClassTraits::IEventDispatcher::IEventDispatcher()"
//##protect##"ClassTraits::IEventDispatcher::IEventDispatcher()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Interface(vm, IEventDispatcherCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IEventDispatcher::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IEventDispatcher(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IEventDispatcherCI = {
    ClassInfo::CompileTime,
    "IEventDispatcher", "flash.events", NULL,
    ClassTraits::IEventDispatcher::MakeClassTraits,
    0,
    0,
    5,
    0,
    NULL,
    NULL,
    InstanceTraits::IEventDispatcher_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

