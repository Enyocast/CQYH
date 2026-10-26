//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Shape.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Shape.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/GFx_CharacterDef.h"
#include "GFx/GFx_Resource.h"
#include "AS3_Obj_Display_Graphics.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Shape, Instances::Shape::mid_graphicsGet, Value> TFunc_Instances_Shape_graphicsGet;

template <> const TFunc_Instances_Shape_graphicsGet::TMethod TFunc_Instances_Shape_graphicsGet::Method = &Instances::Shape::graphicsGet;

namespace Instances
{
    Shape::Shape(InstanceTraits::Traits& t)
    : Instances::DisplayObject(t)
//##protect##"instance::Shape::Shape()$data"
//##protect##"instance::Shape::Shape()$data"
    {
//##protect##"instance::Shape::Shape()$code"
//##protect##"instance::Shape::Shape()$code"
    }

    void Shape::graphicsGet(Value& result)
    {
//##protect##"instance::Shape::graphicsGet()"
        SF_UNUSED1(result);
        if (!pDispObj) CreateStageObject();
        if (!pGraphics)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            if (asvm.ConstructInstance(pGraphics, asvm.GraphicsClass))
            {
                pGraphics->pDrawing = pDispObj->GetDrawingContext();
                pGraphics->pDispObj = pDispObj;
            }
        }
        result = pGraphics;
//##protect##"instance::Shape::graphicsGet()"
    }

//##protect##"instance$methods"
    Shape::~Shape()
    {
        //pGraphics = NULL;
    }

    void Shape::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        DisplayObject::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<Graphics, Mem_Stat>(prcc, pGraphics, op SF_DEBUG_ARG(*this));
    }

    void Shape::InitInstance(bool extCall)
    {
        if (!extCall)
        {
            // create stage display object if the movieclip was created by
            // "new".
            Shape::CreateStageObject();
            SF_ASSERT(pDispObj);
        }
    }

    GFx::DisplayObject* Shape::CreateStageObject()
    {
        if (!pDispObj)
        {
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();

            CharacterCreateInfo ccinfo = 
                proot->GetMovieDefImpl()->GetCharacterCreateInfo(ResourceId(CharacterDef::CharId_EmptyShape));
            SF_ASSERT(ccinfo.pCharDef);
            pDispObj = *static_cast<GFx::DisplayObject*>(proot->GetASSupport()->CreateCharacterInstance(
                proot->GetMovieImpl(), ccinfo, NULL, 
                ResourceId(CharacterDef::CharId_EmptyMovieClip), CharacterDef::Shape));
            ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);
        }
        return pDispObj;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Shape::ti[Shape::ThunkInfoNum] = {
        {TFunc_Instances_Shape_graphicsGet::Func, &GraphicsCI, "graphics", NULL, CT_Get, 0, 0},
    };

    Shape::Shape(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Shape::Shape()"
//##protect##"InstanceTraits::Shape::Shape()"
        SetMemSize(sizeof(Instances::Shape));

    }

    Pickable<Instances::Shape> Shape::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Shape>(new(t.Alloc()) Instances::Shape(t));
    }

    void Shape::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Shape::Shape(VM& vm)
    : Traits(vm, ShapeCI)
    {
//##protect##"ClassTraits::Shape::Shape()"
//##protect##"ClassTraits::Shape::Shape()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Shape(vm, ShapeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Shape::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Shape(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ShapeCI = {
    ClassInfo::CompileTime,
    "Shape", "flash.display", &DisplayObjectCI,
    ClassTraits::Shape::MakeClassTraits,
    0,
    0,
    InstanceTraits::Shape::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Shape::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

