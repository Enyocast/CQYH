//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Proxy.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_Proxy.h"
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
    const ThunkInfo Proxy_ti[10] = {
        {ThunkInfo::EmptyFunc, NULL, "callProperty", NS_flash_proxy, CT_Method, 0, 1023},
        {ThunkInfo::EmptyFunc, &BooleanCI, "deleteProperty", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "getDescendants", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "getProperty", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "hasProperty", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "isAttribute", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "nextName", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "nextNameIndex", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "nextValue", NS_flash_proxy, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "setProperty", NS_flash_proxy, CT_Method, 2, 2},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    Proxy::Proxy(VM& vm)
    : Traits(vm, ProxyCI)
    {
//##protect##"ClassTraits::Proxy::Proxy()"
//##protect##"ClassTraits::Proxy::Proxy()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ProxyCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Proxy::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Proxy(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ProxyCI = {
    ClassInfo::CompileTime,
    "Proxy", "flash.utils", &ObjectCI,
    ClassTraits::Proxy::MakeClassTraits,
    0,
    0,
    10,
    0,
    NULL,
    NULL,
    InstanceTraits::Proxy_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

