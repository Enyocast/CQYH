//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestDefaults.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLRequestDefaults.h"
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
    const ThunkInfo URLRequestDefaults_ti[6] = {
        {ThunkInfo::EmptyFunc, NULL, "authenticate", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "cacheResponse", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "followRedirects", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "manageCookies", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "useCache", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "userAgent", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    URLRequestDefaults::URLRequestDefaults(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::URLRequestDefaults::URLRequestDefaults()"
//##protect##"class_::URLRequestDefaults::URLRequestDefaults()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo URLRequestDefaults_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "setLoginCredentialsForHost", NULL, CT_Method, 3, 3},
    };
    URLRequestDefaults::URLRequestDefaults(VM& vm)
    : Traits(vm, URLRequestDefaultsCI)
    {
//##protect##"ClassTraits::URLRequestDefaults::URLRequestDefaults()"
//##protect##"ClassTraits::URLRequestDefaults::URLRequestDefaults()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, URLRequestDefaultsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::URLRequestDefaults(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLRequestDefaults::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLRequestDefaults(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLRequestDefaultsCI = {
    ClassInfo::CompileTime,
    "URLRequestDefaults", "flash.net", &ObjectCI,
    ClassTraits::URLRequestDefaults::MakeClassTraits,
    1,
    0,
    6,
    0,
    ClassTraits::URLRequestDefaults_ti,
    NULL,
    InstanceTraits::URLRequestDefaults_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

