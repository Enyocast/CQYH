//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_XMLSocket.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_XMLSocket.h"
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
    const ThunkInfo XMLSocket_ti[4] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "connected", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "connect", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "send", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    XMLSocket::XMLSocket(VM& vm)
    : Traits(vm, XMLSocketCI)
    {
//##protect##"ClassTraits::XMLSocket::XMLSocket()"
//##protect##"ClassTraits::XMLSocket::XMLSocket()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, XMLSocketCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLSocket::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLSocket(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLSocketCI = {
    ClassInfo::CompileTime,
    "XMLSocket", "flash.net", &EventDispatcherCI,
    ClassTraits::XMLSocket::MakeClassTraits,
    0,
    0,
    4,
    0,
    NULL,
    NULL,
    InstanceTraits::XMLSocket_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

