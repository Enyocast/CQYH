//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_LocalConnection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_LocalConnection.h"
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

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo LocalConnection_ti[8] = {
        {ThunkInfo::EmptyFunc, &ObjectCI, "client", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "client", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "domain", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "allowDomain", NULL, CT_Method, 0, 1023},
        {ThunkInfo::EmptyFunc, NULL, "allowInsecureDomain", NULL, CT_Method, 0, 1023},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "connect", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "send", NULL, CT_Method, 0, 1023},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    LocalConnection::LocalConnection(VM& vm)
    : Traits(vm, LocalConnectionCI)
    {
//##protect##"ClassTraits::LocalConnection::LocalConnection()"
//##protect##"ClassTraits::LocalConnection::LocalConnection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, LocalConnectionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> LocalConnection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) LocalConnection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo LocalConnectionCI = {
    ClassInfo::CompileTime,
    "LocalConnection", "flash.net", &EventDispatcherCI,
    ClassTraits::LocalConnection::MakeClassTraits,
    0,
    0,
    8,
    0,
    NULL,
    NULL,
    InstanceTraits::LocalConnection_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

