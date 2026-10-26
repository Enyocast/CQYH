//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextRenderer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextRenderer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
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
    const ThunkInfo TextRenderer_ti[2] = {
        {ThunkInfo::EmptyFunc, NULL, "displayMode", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "maxLevel", NULL, CT_Set, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    TextRenderer::TextRenderer(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::TextRenderer::TextRenderer()"
//##protect##"class_::TextRenderer::TextRenderer()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo TextRenderer_ti[1] = {
        {ThunkInfo::EmptyFunc, NULL, "setAdvancedAntiAliasingTable", NULL, CT_Method, 4, 4},
    };
    TextRenderer::TextRenderer(VM& vm)
    : Traits(vm, TextRendererCI)
    {
//##protect##"ClassTraits::TextRenderer::TextRenderer()"
//##protect##"ClassTraits::TextRenderer::TextRenderer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextRendererCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextRenderer(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextRenderer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextRenderer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextRendererCI = {
    ClassInfo::CompileTime,
    "TextRenderer", "flash.text", &ObjectCI,
    ClassTraits::TextRenderer::MakeClassTraits,
    1,
    0,
    2,
    0,
    ClassTraits::TextRenderer_ti,
    NULL,
    InstanceTraits::TextRenderer_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

