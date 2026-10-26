//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Display_Shader.cpp
Content     :   
Created     :   Sep, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Shader.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class ShaderData;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo Shader_ti[5] = {
        {ThunkInfo::EmptyFunc, NULL, "byteCode", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ShaderDataCI, "data", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "data", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "precisionHint", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "precisionHint", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    Shader::Shader(VM& vm)
    : Traits(vm, ShaderCI)
    {
//##protect##"ClassTraits::Shader::Shader()"
//##protect##"ClassTraits::Shader::Shader()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ShaderCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Shader::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Shader(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ShaderCI = {
    ClassInfo::CompileTime,
    "Shader", "flash.display", &ObjectCI,
    ClassTraits::Shader::MakeClassTraits,
    0,
    0,
    5,
    0,
    NULL,
    NULL,
    InstanceTraits::Shader_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

