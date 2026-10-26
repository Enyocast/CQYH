//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Scene.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Scene.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "AS3_Obj_Display_FrameLabel.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Scene, Instances::Scene::mid_labelsGet, Value> TFunc_Instances_Scene_labelsGet;
typedef ThunkFunc0<Instances::Scene, Instances::Scene::mid_nameGet, ASString> TFunc_Instances_Scene_nameGet;
typedef ThunkFunc0<Instances::Scene, Instances::Scene::mid_numFramesGet, SInt32> TFunc_Instances_Scene_numFramesGet;

template <> const TFunc_Instances_Scene_labelsGet::TMethod TFunc_Instances_Scene_labelsGet::Method = &Instances::Scene::labelsGet;
template <> const TFunc_Instances_Scene_nameGet::TMethod TFunc_Instances_Scene_nameGet::Method = &Instances::Scene::nameGet;
template <> const TFunc_Instances_Scene_numFramesGet::TMethod TFunc_Instances_Scene_numFramesGet::Method = &Instances::Scene::numFramesGet;

namespace Instances
{
    Scene::Scene(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Scene::Scene()$data"
    , SceneInfo(NULL)
//##protect##"instance::Scene::Scene()$data"
    {
//##protect##"instance::Scene::Scene()$code"
//##protect##"instance::Scene::Scene()$code"
    }

    void Scene::labelsGet(Value& result)
    {
//##protect##"instance::Scene::labelsGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        // Create an array
        SPtr<Instances::Array> labelsArray(GetVM().MakeArray());

        Class* frameLabelClassVal = GetVM().GetClass("flash.display.FrameLabel");

        if (SceneInfo)
        {
            UPInt cnt = SceneInfo->Labels.GetSize();
            for (UPInt i = 0; i < cnt; ++i)
            {
                // create a FrameLabel object

                SPtr<Instances::FrameLabel> frameLabel;
                asvm.ConstructInstance(frameLabel, frameLabelClassVal, 0);

                // populate frameLabel
                frameLabel->Set(SceneInfo->Offset, &SceneInfo->Labels[i]);

                labelsArray->PushBack(Value(frameLabel));
            }
        }
        else
        {
            SF_ASSERT(SpriteObj);
            unsigned cnt = SpriteObj->GetFrameCount();
            Scaleform::Array<String> labels;
            for (unsigned i = 0; i < cnt; ++i)
            {
                // not very efficient way of getting labels from the sprite;
                // however, hopefully, it is not critical.
                if (SpriteObj->GetDef()->GetFrameLabels(i, &labels))
                {
                    for (UPInt j = 0, nj = labels.GetSize(); j < nj; ++j)
                    {
                        // create a FrameLabel object
                        SPtr<Instances::FrameLabel> frameLabel;
                        asvm.ConstructInstance(frameLabel, frameLabelClassVal, 0);

                        // populate frameLabel
                        frameLabel->Set(i + 1, asvm.GetStringManager().CreateString(labels[j].ToCStr()));

                        labelsArray->PushBack(Value(frameLabel));
                    }
                    labels.Clear();
                }
            }
        }
        result = Value(labelsArray);
//##protect##"instance::Scene::labelsGet()"
    }
    void Scene::nameGet(ASString& result)
    {
//##protect##"instance::Scene::nameGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (SceneInfo)
            result = SceneInfo->Name;
        else
            result = asvm.GetStringManager().CreateEmptyString();
//##protect##"instance::Scene::nameGet()"
    }
    void Scene::numFramesGet(SInt32& result)
    {
//##protect##"instance::Scene::numFramesGet()"
        SF_UNUSED1(result);
        if (SceneInfo)
            result = (SInt32)SceneInfo->NumFrames;
        else
        {
            SF_ASSERT(SpriteObj);
            result = SpriteObj->GetFrameCount();
        }
//##protect##"instance::Scene::numFramesGet()"
    }

//##protect##"instance$methods"
    void Scene::Set(const MovieDataDef::SceneInfo* sceneInfo)
    {
        SceneInfo = sceneInfo;
    }
    void Scene::Set(GFx::Sprite* spr)
    {
        SpriteObj = spr;
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Scene::ti[Scene::ThunkInfoNum] = {
        {TFunc_Instances_Scene_labelsGet::Func, &ArrayCI, "labels", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Scene_nameGet::Func, &StringCI, "name", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Scene_numFramesGet::Func, &int_CI, "numFrames", NULL, CT_Get, 0, 0},
    };

    Scene::Scene(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Scene::Scene()"
//##protect##"InstanceTraits::Scene::Scene()"
        SetMemSize(sizeof(Instances::Scene));

    }

    Pickable<Instances::Scene> Scene::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Scene>(new(t.Alloc()) Instances::Scene(t));
    }

    void Scene::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Scene::Scene(VM& vm)
    : Traits(vm, SceneCI)
    {
//##protect##"ClassTraits::Scene::Scene()"
//##protect##"ClassTraits::Scene::Scene()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Scene(vm, SceneCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Scene::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Scene(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SceneCI = {
    ClassInfo::CompileTime,
    "Scene", "flash.display", &ObjectCI,
    ClassTraits::Scene::MakeClassTraits,
    0,
    0,
    InstanceTraits::Scene::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Scene::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

