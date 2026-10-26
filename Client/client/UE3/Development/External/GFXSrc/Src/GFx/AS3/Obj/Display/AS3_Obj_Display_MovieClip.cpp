//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_MovieClip.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_MovieClip.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../Obj/AS3_Obj_Array.h"
#include "AS3_Obj_Display_Scene.h"
#include "GFx/AS3/AS3_AvmSprite.h"
#include "Kernel/SF_Array.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/GFx_CharacterDef.h"
#include "GFx/GFx_Resource.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::MovieClip, Instances::MovieClip::mid_gotoAndPlay, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::MovieClip, Instances::MovieClip::mid_gotoAndStop, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

} // namespace Impl
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_currentFrameGet, SInt32> TFunc_Instances_MovieClip_currentFrameGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_currentFrameLabelGet, Value> TFunc_Instances_MovieClip_currentFrameLabelGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_currentLabelGet, Value> TFunc_Instances_MovieClip_currentLabelGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_currentLabelsGet, Value> TFunc_Instances_MovieClip_currentLabelsGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_currentSceneGet, Value> TFunc_Instances_MovieClip_currentSceneGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_enabledGet, bool> TFunc_Instances_MovieClip_enabledGet;
typedef ThunkFunc1<Instances::MovieClip, Instances::MovieClip::mid_enabledSet, Value, bool> TFunc_Instances_MovieClip_enabledSet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_framesLoadedGet, SInt32> TFunc_Instances_MovieClip_framesLoadedGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_scenesGet, Value> TFunc_Instances_MovieClip_scenesGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_totalFramesGet, SInt32> TFunc_Instances_MovieClip_totalFramesGet;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_trackAsMenuGet, bool> TFunc_Instances_MovieClip_trackAsMenuGet;
typedef ThunkFunc1<Instances::MovieClip, Instances::MovieClip::mid_trackAsMenuSet, Value, bool> TFunc_Instances_MovieClip_trackAsMenuSet;
typedef ThunkFunc2<Instances::MovieClip, Instances::MovieClip::mid_addFrameScript, Value, unsigned, const Value*> TFunc_Instances_MovieClip_addFrameScript;
typedef ThunkFunc2<Instances::MovieClip, Instances::MovieClip::mid_gotoAndPlay, Value, const Value&, const Value&> TFunc_Instances_MovieClip_gotoAndPlay;
typedef ThunkFunc2<Instances::MovieClip, Instances::MovieClip::mid_gotoAndStop, Value, const Value&, const Value&> TFunc_Instances_MovieClip_gotoAndStop;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_nextFrame, Value> TFunc_Instances_MovieClip_nextFrame;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_nextScene, Value> TFunc_Instances_MovieClip_nextScene;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_play, Value> TFunc_Instances_MovieClip_play;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_prevFrame, Value> TFunc_Instances_MovieClip_prevFrame;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_prevScene, Value> TFunc_Instances_MovieClip_prevScene;
typedef ThunkFunc0<Instances::MovieClip, Instances::MovieClip::mid_stop, Value> TFunc_Instances_MovieClip_stop;

template <> const TFunc_Instances_MovieClip_currentFrameGet::TMethod TFunc_Instances_MovieClip_currentFrameGet::Method = &Instances::MovieClip::currentFrameGet;
template <> const TFunc_Instances_MovieClip_currentFrameLabelGet::TMethod TFunc_Instances_MovieClip_currentFrameLabelGet::Method = &Instances::MovieClip::currentFrameLabelGet;
template <> const TFunc_Instances_MovieClip_currentLabelGet::TMethod TFunc_Instances_MovieClip_currentLabelGet::Method = &Instances::MovieClip::currentLabelGet;
template <> const TFunc_Instances_MovieClip_currentLabelsGet::TMethod TFunc_Instances_MovieClip_currentLabelsGet::Method = &Instances::MovieClip::currentLabelsGet;
template <> const TFunc_Instances_MovieClip_currentSceneGet::TMethod TFunc_Instances_MovieClip_currentSceneGet::Method = &Instances::MovieClip::currentSceneGet;
template <> const TFunc_Instances_MovieClip_enabledGet::TMethod TFunc_Instances_MovieClip_enabledGet::Method = &Instances::MovieClip::enabledGet;
template <> const TFunc_Instances_MovieClip_enabledSet::TMethod TFunc_Instances_MovieClip_enabledSet::Method = &Instances::MovieClip::enabledSet;
template <> const TFunc_Instances_MovieClip_framesLoadedGet::TMethod TFunc_Instances_MovieClip_framesLoadedGet::Method = &Instances::MovieClip::framesLoadedGet;
template <> const TFunc_Instances_MovieClip_scenesGet::TMethod TFunc_Instances_MovieClip_scenesGet::Method = &Instances::MovieClip::scenesGet;
template <> const TFunc_Instances_MovieClip_totalFramesGet::TMethod TFunc_Instances_MovieClip_totalFramesGet::Method = &Instances::MovieClip::totalFramesGet;
template <> const TFunc_Instances_MovieClip_trackAsMenuGet::TMethod TFunc_Instances_MovieClip_trackAsMenuGet::Method = &Instances::MovieClip::trackAsMenuGet;
template <> const TFunc_Instances_MovieClip_trackAsMenuSet::TMethod TFunc_Instances_MovieClip_trackAsMenuSet::Method = &Instances::MovieClip::trackAsMenuSet;
template <> const TFunc_Instances_MovieClip_addFrameScript::TMethod TFunc_Instances_MovieClip_addFrameScript::Method = &Instances::MovieClip::addFrameScript;
template <> const TFunc_Instances_MovieClip_gotoAndPlay::TMethod TFunc_Instances_MovieClip_gotoAndPlay::Method = &Instances::MovieClip::gotoAndPlay;
template <> const TFunc_Instances_MovieClip_gotoAndStop::TMethod TFunc_Instances_MovieClip_gotoAndStop::Method = &Instances::MovieClip::gotoAndStop;
template <> const TFunc_Instances_MovieClip_nextFrame::TMethod TFunc_Instances_MovieClip_nextFrame::Method = &Instances::MovieClip::nextFrame;
template <> const TFunc_Instances_MovieClip_nextScene::TMethod TFunc_Instances_MovieClip_nextScene::Method = &Instances::MovieClip::nextScene;
template <> const TFunc_Instances_MovieClip_play::TMethod TFunc_Instances_MovieClip_play::Method = &Instances::MovieClip::play;
template <> const TFunc_Instances_MovieClip_prevFrame::TMethod TFunc_Instances_MovieClip_prevFrame::Method = &Instances::MovieClip::prevFrame;
template <> const TFunc_Instances_MovieClip_prevScene::TMethod TFunc_Instances_MovieClip_prevScene::Method = &Instances::MovieClip::prevScene;
template <> const TFunc_Instances_MovieClip_stop::TMethod TFunc_Instances_MovieClip_stop::Method = &Instances::MovieClip::stop;

namespace Instances
{
    MovieClip::MovieClip(InstanceTraits::Traits& t)
    : Instances::Sprite(t)
//##protect##"instance::MovieClip::MovieClip()$data"
//    , pDisplaySprite(NULL)
//##protect##"instance::MovieClip::MovieClip()$data"
    {
//##protect##"instance::MovieClip::MovieClip()$code"
//##protect##"instance::MovieClip::MovieClip()$code"
    }

    void MovieClip::currentFrameGet(SInt32& result)
    {
//##protect##"instance::MovieClip::currentFrameGet()"
        if (!pDispObj)
        {
            result = 0;
            return;
        }
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        result = spr->GetCurrentFrame() + 1;
//##protect##"instance::MovieClip::currentFrameGet()"
    }
    void MovieClip::currentFrameLabelGet(Value& result)
    {
//##protect##"instance::MovieClip::currentFrameLabelGet()"
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        unsigned fr = spr->GetCurrentFrame(), exactFr;

        const String* label = spr->GetDef()->GetFrameLabel(fr, &exactFr);
        if (label && fr == exactFr)
            result = Value(asvm.GetStringManager().CreateString(label->ToCStr()));
        else
            result.SetNull();
//##protect##"instance::MovieClip::currentFrameLabelGet()"
    }
    void MovieClip::currentLabelGet(Value& result)
    {
//##protect##"instance::MovieClip::currentLabelGet()"
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        unsigned fr = spr->GetCurrentFrame();

        const String* label = spr->GetDef()->GetFrameLabel(fr, &fr);
        if (label)
            result = Value(asvm.GetStringManager().CreateString(label->ToCStr()));
        else
            result.SetNull();
//##protect##"instance::MovieClip::currentLabelGet()"
    }
    void MovieClip::currentLabelsGet(Value& result)
    {
//##protect##"instance::MovieClip::currentLabelsGet()"

        Value sceneVal;
        currentSceneGet(sceneVal);
        SPtr<Instances::Scene> scene = static_cast<Scene*>(sceneVal.GetObject());
        scene->labelsGet(result);
//##protect##"instance::MovieClip::currentLabelsGet()"
    }
    void MovieClip::currentSceneGet(Value& result)
    {
//##protect##"instance::MovieClip::currentSceneGet()"
        result.SetNull();

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            // main time line
            unsigned fr = spr->GetCurrentFrame();
            UPInt cnt = 0;
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);

            for (UPInt i = 0; i < cnt; ++i)
            {
                if (fr >= scenes[i].Offset && fr < scenes[i].Offset + scenes[i].NumFrames)
                {
                    // create a Scene object
                    Class* sceneClassVal = GetVM().GetClass("flash.display.Scene");

                    SPtr<Instances::Scene> scene;
                    asvm.ConstructInstance(scene, sceneClassVal, 0);

                    // populate scene
                    scene->Set(&scenes[i]);
                    result = Value(scene);
                    break;
                }
            }
        }
        else
        {
            SPtr<Instances::Scene> scene = CreateFakeScene();
            result = Value(scene);
        }
     
//##protect##"instance::MovieClip::currentSceneGet()"
    }
    void MovieClip::enabledGet(bool& result)
    {
//##protect##"instance::MovieClip::enabledGet()"
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        result = pDispObj->CharToInteractiveObject_Unsafe()->IsEnabledFlagSet();
//##protect##"instance::MovieClip::enabledGet()"
    }
    void MovieClip::enabledSet(Value& result, bool value)
    {
//##protect##"instance::MovieClip::enabledSet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        
        pDispObj->CharToInteractiveObject_Unsafe()->SetEnabledFlag(value);

//##protect##"instance::MovieClip::enabledSet()"
    }
    void MovieClip::framesLoadedGet(SInt32& result)
    {
//##protect##"instance::MovieClip::framesLoadedGet()"
        if (!pDispObj)
        {
            result = 1;
            return;
        }
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        result = spr->GetLoadingFrame();
//##protect##"instance::MovieClip::framesLoadedGet()"
    }
    void MovieClip::scenesGet(Value& result)
    {
//##protect##"instance::MovieClip::scenesGet()"
        SF_UNUSED1(result);
        // create an array of scenes
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        // Create an array
        SPtr<Instances::Array> scenesArray(GetVM().MakeArray());

        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            UPInt cnt = 0;
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);

            Class* sceneClassVal = GetVM().GetClass("flash.display.Scene");

            for (UPInt i = 0; i < cnt; ++i)
            {
                // create a Scene object

                SPtr<Instances::Scene> scene;
                asvm.ConstructInstance(scene, sceneClassVal, 0);

                // populate scene
                scene->Set(&scenes[i]);

                scenesArray->PushBack(Value(scene));
            }
        }
        else
        {
            SPtr<Instances::Scene> scene = CreateFakeScene();
            scenesArray->PushBack(Value(scene));
        }
        result = Value(scenesArray);
//##protect##"instance::MovieClip::scenesGet()"
    }
    void MovieClip::totalFramesGet(SInt32& result)
    {
//##protect##"instance::MovieClip::totalFramesGet()"
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        result = spr->GetDef()->GetFrameCount();
//##protect##"instance::MovieClip::totalFramesGet()"
    }
    void MovieClip::trackAsMenuGet(bool& result)
    {
//##protect##"instance::MovieClip::trackAsMenuGet()"
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        result = spr->GetTrackAsMenu();
//##protect##"instance::MovieClip::trackAsMenuGet()"
    }
    void MovieClip::trackAsMenuSet(Value& result, bool value)
    {
//##protect##"instance::MovieClip::trackAsMenuSet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        spr->SetTrackAsMenuFlag(value);
//##protect##"instance::MovieClip::trackAsMenuSet()"
    }
    void MovieClip::addFrameScript(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::MovieClip::addFrameScript()"
        SF_UNUSED3(result, argc, argv);

        if (!pDispObj) CreateStageObject();
        SF_ASSERT(pDispObj);

        GFx::Sprite* pspr = pDispObj->CharToSprite();
        if (pspr)
        {
            AvmSprite* avmSpr = ToAvmSprite(pspr);
            int n = argc/2;
            Scaleform::ArrayCPP<FrameScript::Descr> frames;
            //frames.Reserve(n);
            for (int i = 0, k = 0; i < n; ++i)
            {
                SInt32 frameNum;
                if (!argv[k++].Convert2Int32(frameNum))
                    continue; // wrong number, skip? or break?
                // frames for addFrameScript are zero-based;
                // however, our frames are 1-based (0 frame is used
                // for initialization logic, rigistering classes, etc).
                FrameScript::Descr fr(frameNum, argv[k++]);
                frames.PushBack(fr);
            }
            mFrameScript.Set(avmSpr->GetHeap(), pspr->GetFrameCount(), n, &frames[0]);

            // each call to addFrameScript adds current frame to queue, regardless to
            // parameters
            const FrameScript::Descr* pd = mFrameScript.Get(pspr->GetCurrentFrame());
            if (pd)
            {
                avmSpr->SetNeedExecuteFrameFlag();
            }
        }
//##protect##"instance::MovieClip::addFrameScript()"
    }
    void MovieClip::gotoAndPlay(Value& result, const Value& frame, const Value& scene)
    {
//##protect##"instance::MovieClip::gotoAndPlay()"
        SF_UNUSED3(result, frame, scene);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        unsigned targetFrame;
        if (frame.IsString())
        {
            if (!GetLabeledFrame(spr, frame, scene, &targetFrame))
                return;
        }
        else
        {
            UInt32 r;
            if (!frame.Convert2UInt32(r))
                return;
            targetFrame = r - 1;
        }
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (targetFrame != spr->GetCurrentFrame())
        {
            // This seems to be necessary to avoid extra execution of already queued up
            // frames: gotoAnd... in AS3 overrides it (unlike in AS2).
            vm.GetMovieRoot()->RemoveActionQueueEntriesFor(MovieRoot::AL_Frame, pDispObj);

            spr->GotoFrame(targetFrame);
        }
        spr->SetPlayState(State_Playing);

        // execute all events right here
        vm.GetMovieRoot()->QueueFrameActions();
        // execute all actions starting from highest level down to frame (including).
        // Do not execute lower levels (render events and such)
        for (unsigned i = MovieRoot::AL_Highest; i <= MovieRoot::AL_Frame; ++i)
        {
            vm.GetMovieRoot()->ExecuteActionQueue((MovieRoot::ActionLevel)i);
        }

//##protect##"instance::MovieClip::gotoAndPlay()"
    }
    void MovieClip::gotoAndStop(Value& result, const Value& frame, const Value& scene)
    {
//##protect##"instance::MovieClip::gotoAndStop()"
        SF_UNUSED3(result, frame, scene);

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        unsigned targetFrame;
        if (frame.IsString())
        {
            if (!GetLabeledFrame(spr, frame, scene, &targetFrame))
                return;
        }
        else
        {
            UInt32 r;
            if (!frame.Convert2UInt32(r))
                return;
            targetFrame = r - 1;
        }
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (targetFrame != spr->GetCurrentFrame())
        {
            // This seems to be necessary to avoid extra execution of already queued up
            // frames: gotoAnd... in AS3 overrides it (unlike in AS2).
            vm.GetMovieRoot()->RemoveActionQueueEntriesFor(MovieRoot::AL_Frame, pDispObj);

            spr->GotoFrame(targetFrame);
        }
        spr->SetPlayState(State_Stopped);

        // execute all events right here
        vm.GetMovieRoot()->QueueFrameActions();
        // execute all actions starting from highest level down to frame (including).
        // Do not execute lower levels (render events and such)
        for (unsigned i = MovieRoot::AL_Highest; i <= MovieRoot::AL_Frame; ++i)
        {
            vm.GetMovieRoot()->ExecuteActionQueue((MovieRoot::ActionLevel)i);
        }

//##protect##"instance::MovieClip::gotoAndStop()"
    }
    void MovieClip::nextFrame(Value& result)
    {
//##protect##"instance::MovieClip::nextFrame()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        int availableFrameCount = spr->GetLoadingFrame();
        int currentFrame = spr->GetCurrentFrame();
        if (currentFrame < availableFrameCount)
            spr->GotoFrame(currentFrame + 1);      
        spr->SetPlayState(State_Stopped);
//##protect##"instance::MovieClip::nextFrame()"
    }
    void MovieClip::nextScene(Value& result)
    {
//##protect##"instance::MovieClip::nextScene()"
        SF_UNUSED1(result);
        
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        // Determine the current scene first
        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            UPInt cnt = 0;
            //ASVM& asvm = static_cast<ASVM&>(GetVM());
            //MovieRoot* proot = asvm.GetMovieRoot();
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);
            unsigned frameNumber = spr->GetCurrentFrame();

            for (UPInt i = 0; i < cnt; ++i)
            {
                if (frameNumber >= scenes[i].Offset && frameNumber < scenes[i].Offset + scenes[i].NumFrames)
                {
                    // get the next one, if exists
                    if (i + 1 < cnt)
                    {
                        // goto frame
                        unsigned availableFrameCount = spr->GetLoadingFrame();
                        if (scenes[i + 1].Offset < availableFrameCount)
                        {
                            spr->GotoFrame(scenes[i + 1].Offset);      
                            spr->SetPlayState(State_Playing);
                        }
                    }
                }
            }
        }
//##protect##"instance::MovieClip::nextScene()"
    }
    void MovieClip::play(Value& result)
    {
//##protect##"instance::MovieClip::play()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        spr->SetPlayState(State_Playing);
//##protect##"instance::MovieClip::play()"
    }
    void MovieClip::prevFrame(Value& result)
    {
//##protect##"instance::MovieClip::prevFrame()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        int currentFrame = spr->GetCurrentFrame();
        if (currentFrame > 0)
            spr->GotoFrame(currentFrame - 1);
        spr->SetPlayState(State_Stopped);
//##protect##"instance::MovieClip::prevFrame()"
    }
    void MovieClip::prevScene(Value& result)
    {
//##protect##"instance::MovieClip::prevScene()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        // Determine the current scene first
        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            UPInt cnt = 0;
            //ASVM& asvm = static_cast<ASVM&>(GetVM());
            //MovieRoot* proot = asvm.GetMovieRoot();
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);
            unsigned frameNumber = spr->GetCurrentFrame();

            for (UPInt i = 0; i < cnt; ++i)
            {
                if (frameNumber >= scenes[i].Offset && frameNumber < scenes[i].Offset + scenes[i].NumFrames)
                {
                    // get the prev one, if exists
                    if (i > 0)
                    {
                        // goto frame
                        spr->GotoFrame(scenes[i - 1].Offset);      
                        spr->SetPlayState(State_Playing);
                    }
                }
            }
        }
//##protect##"instance::MovieClip::prevScene()"
    }
    void MovieClip::stop(Value& result)
    {
//##protect##"instance::MovieClip::stop()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        
        spr->SetPlayState(State_Stopped);
//##protect##"instance::MovieClip::stop()"
    }

//##protect##"instance$methods"
    SPtr<Instances::Scene> MovieClip::CreateFakeScene()
    {
        // There is only one Scene in the sprite
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        Class* sceneClassVal = GetVM().GetClass("flash.display.Scene");

        SPtr<Instances::Scene> scene;
        asvm.ConstructInstance(scene, sceneClassVal, 0);

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);
        scene->Set(spr);
        return scene;
    }

    const MovieDataDef::SceneInfo* MovieClip::GetSceneInfo(unsigned frameNumber) const
    {
        //ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            UPInt cnt = 0;
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);

            for (UPInt i = 0; i < cnt; ++i)
            {
                if (frameNumber >= scenes[i].Offset && frameNumber < scenes[i].Offset + scenes[i].NumFrames)
                {
                    return &scenes[i];
                }
            }
        }
        return NULL;
    }

    const MovieDataDef::SceneInfo* MovieClip::GetSceneInfoByName(const ASString& name) const
    {
        //ASVM& asvm = static_cast<ASVM&>(GetVM());
        //MovieRoot* proot = asvm.GetMovieRoot();

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        if (spr->GetDef()->GetType() == CharacterDef::MovieData)
        {
            UPInt cnt = 0;
            const MovieDataDef::SceneInfo* scenes = spr->GetResourceMovieDef()->GetDataDef()->GetScenes(&cnt);

            for (UPInt i = 0; i < cnt; ++i)
            {
                if (name == scenes[i].Name)
                {
                    return &scenes[i];
                }
            }
        }
        return NULL;
    }

    bool MovieClip::GetLabeledFrame(GFx::Sprite* spr, const Value& frame, const Value& scene, unsigned* targetFrame)
    {
        SF_ASSERT(targetFrame);
        spr->GetLabeledFrame(frame.AsString().ToCStr(), targetFrame);
        if (!scene.IsNull() && !scene.IsUndefined())
        {
            ASString sceneName = GetVM().GetStringManager().CreateEmptyString();
            scene.Convert2String(sceneName).DoNotCheck();

            // scene is specified.
            // check if the targetFrame is within the specified scene.
            const MovieDataDef::SceneInfo* sceneInfo = GetSceneInfoByName(sceneName);
            if (!sceneInfo)
            {
                GetVM().ThrowArgumentError(VM::Error(VM::eSceneNotFound, GetVM() SF_DEBUG_ARG(sceneName.ToCStr())));
                return false;
            }
            const MovieDataDef::SceneInfo* targetSceneInfo = GetSceneInfo(*targetFrame);
            if (sceneInfo != targetSceneInfo)
            {
                GetVM().ThrowArgumentError(VM::Error(VM::eFrameLabelNotFoundInScene, GetVM()
                    SF_DEBUG_ARG(frame) 
                    SF_DEBUG_ARG(sceneName.ToCStr())
                    ));
                return false;
            }
        }
        else
        {
            // scene is not specified.
            // just check if the targetFrame is within the curSceneInfo
            const MovieDataDef::SceneInfo* curSceneInfo = GetSceneInfo(spr->GetCurrentFrame());
            if (curSceneInfo)
            {
                const MovieDataDef::SceneInfo* targetSceneInfo = GetSceneInfo(*targetFrame);
                if (curSceneInfo != targetSceneInfo)
                {
                    GetVM().ThrowArgumentError(VM::Error(VM::eFrameLabelNotFoundInScene, GetVM()
                        SF_DEBUG_ARG(frame) 
                        SF_DEBUG_ARG(curSceneInfo->Name.ToCStr())
                        ));
                    return false;
                }
            }
        }
        return true;
    }

    //////////////////////////////////////////////////////////////////////////
    MovieClip::FrameScript::~FrameScript() 
    { 
        Clear();
    }

    void MovieClip::FrameScript::Set(
        MemoryHeap* pheap, unsigned totalFrames, unsigned cnt, const Descr* pdescriptors)
    {
        unsigned actualDescrCnt = 0;
        if (pData)
        {
            // if pData already exists we need to update records for existing frames
            // and add new ones. No duplicates are allowed.
            SF_ASSERT(totalFrames == FrameCnt);

            actualDescrCnt = DescrCnt;
            unsigned delta = 0;
            // check if we need to expand storage...
            for (int i = (int)cnt - 1; i >= 0; --i)
            {
                unsigned fr = pdescriptors[i].Frame;
                if (fr < FrameCnt)
                {
                    if (!(pData[fr >> 3] & (1 << (fr & 7))))
                        ++delta;
                    else
                    {
                        // update the existing entry

                        Descr* pdescr = GetDescs();
                        // bit indicates the descriptor exists: do search in sorted array
                        UPInt k = Alg::LowerBoundSized(pdescr, DescrCnt, Descr(fr, Value::GetUndefined()));
                        SF_ASSERT(pdescr[k].Frame == fr);
                        pdescr[k] = pdescriptors[i];
                    }
                }
            }
            unsigned newDescrCnt = DescrCnt + delta;
            if (delta > 0)
            {
                // expand pData for delta elements
                pData = reinterpret_cast<UByte*>(
                    SF_REALLOC(pData, GetDescSize(newDescrCnt), StatMV_ActionScript_Mem_FrameScript));

                Descr* pdest = GetDescs();
                for (int i = (int)newDescrCnt-1, j = (int)cnt-1; i >= DescrCnt && j >= 0; --j)
                {
                    unsigned fr = pdescriptors[j].Frame;
                    if (fr < FrameCnt)
                    {
                        if (!(pData[fr >> 3] & (1 << (fr & 7))))
                        {
                            new (&pdest[i--]) Descr(pdescriptors[j]);
                            // set corresponding bits to 1
                            pData[fr >> 3] |= (1 << (fr & 7));
                            ++actualDescrCnt;
                        }
                    }
                }

                if (newDescrCnt != actualDescrCnt)
                {
                    SF_ASSERT(actualDescrCnt < newDescrCnt);
                    memcpy(pdest + DescrCnt, pdest + actualDescrCnt, 
                        (newDescrCnt - actualDescrCnt) * sizeof(Descr));
                }
                DescrCnt = (UInt16)newDescrCnt;
            }
        }
        else if (cnt > 0)
        {
            // pData is NULL, create from scratch

            DescrCnt = (UInt16)Alg::Min(cnt, totalFrames);
            FrameCnt = (UInt16)totalFrames;
            // allocate data for each frame + space for a bitset that indicates presence of
            // action in the corresponding frame.
            pData = reinterpret_cast<UByte*>(
                SF_HEAP_ALLOC(pheap, GetDescSize(DescrCnt), StatMV_ActionScript_Mem_FrameScript));
            if (!pData)
                return; //?

            // The bitset is at the beginning of the data; an offset to Descrs is
            // (FrameCnt + 7)/8
            memset(pData, 0, (FrameCnt + 7)/8); // set all bits to 0

            // copy descriptors
            Descr* pdest = GetDescs();
            for (int i = (int)DescrCnt - 1, j = i; i >= 0; --i)
            {
                unsigned f = pdescriptors[i].Frame;
                if (f < FrameCnt)
                {
                    if (!(pData[f >> 3] & (1 << (f & 7))))
                    {
                        new (&pdest[j--]) Descr(pdescriptors[i]);
                        // set corresponding bits to 1
                        pData[f >> 3] |= (1 << (f & 7));
                        ++actualDescrCnt;
                    }
                }
            }
            if (DescrCnt != actualDescrCnt)
            {
                SF_ASSERT(actualDescrCnt < DescrCnt);
                memcpy(pdest, pdest + (DescrCnt - actualDescrCnt), actualDescrCnt * sizeof(Descr));
            }
        }
        // sort
        Descr* pdest = GetDescs();

        if (DescrCnt != actualDescrCnt)
        {
            DescrCnt = (UInt16)actualDescrCnt;
            // compact memory if we can; usually happens when the same frame is specified twice 
            // (very rarely).
            pData = reinterpret_cast<UByte*>(
                SF_REALLOC(pData, GetDescSize(DescrCnt), StatMV_ActionScript_Mem_FrameScript));
        }

        Alg::QuickSortSliced(pdest, 0, DescrCnt, Alg::OperatorLess<Descr>::Compare);
    }

    const MovieClip::FrameScript::Descr* MovieClip::FrameScript::Get(unsigned frameNum)
    {
        // check if frameNum exceeds max frame number
        // checks if there is a descriptor for this frame
        if (frameNum < FrameCnt && pData[frameNum >> 3] & (1 << (frameNum & 7)))
        {
            const Descr* pdescr = GetDescs();
            // bit indicates the descriptor exists: do search in sorted array
            UPInt i = Alg::LowerBoundSized(pdescr, DescrCnt, Descr(frameNum, Value::GetUndefined()));
            if (pdescr[i].Frame == frameNum)
                return &pdescr[i];
        }
        return NULL;
    }

    void MovieClip::FrameScript::Clear()
    {
        if (pData)
        {
            const Descr* pdescr = GetDescs();
            for (unsigned i = 0; i < DescrCnt; ++i)
            {
                pdescr[i].~Descr();
            }

            SF_FREE(pData); 
            pData = NULL;
        }
    }

    void MovieClip::FrameScript::ForEachChild_GC(Collector* prcc, GcOp op
                                                SF_DEBUG_ARG(const MovieClip& owner)) const
    {
        if (pData)
        {
            const Descr* pdescr = GetDescs();
            for (unsigned i = 0; i < DescrCnt; ++i)
            {
                AS3::ForEachChild_GC(prcc, pdescr[i].Method, op SF_DEBUG_ARG(owner));
            }
        }
    }

    void MovieClip::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Sprite::ForEachChild_GC(prcc, op);

        mFrameScript.ForEachChild_GC(prcc, op SF_DEBUG_ARG(*this));
    }

    bool    MovieClip::HasFrameScript() const
    {
        return !mFrameScript.IsEmpty();
    }

    bool    MovieClip::GetFrameScript(unsigned frame, Value* pmethod)
    {
        // check, if we need to execute ("queue up") AS execution for the frame
        const FrameScript::Descr* pdescr = mFrameScript.Get(frame);
        if (pdescr)
        {
            SF_ASSERT(pmethod);
            if (pdescr->Method.IsCallable() && !pdescr->Method.IsNull())
            {
                *pmethod = pdescr->Method;
                return true;
            }
        }
        return false;
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo MovieClip::ti[MovieClip::ThunkInfoNum] = {
        {TFunc_Instances_MovieClip_currentFrameGet::Func, &int_CI, "currentFrame", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_currentFrameLabelGet::Func, &ObjectCI, "currentFrameLabel", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_currentLabelGet::Func, &ObjectCI, "currentLabel", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_currentLabelsGet::Func, &ArrayCI, "currentLabels", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_currentSceneGet::Func, &SceneCI, "currentScene", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_enabledGet::Func, &BooleanCI, "enabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_enabledSet::Func, NULL, "enabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MovieClip_framesLoadedGet::Func, &int_CI, "framesLoaded", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_scenesGet::Func, &ArrayCI, "scenes", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_totalFramesGet::Func, &int_CI, "totalFrames", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_trackAsMenuGet::Func, &BooleanCI, "trackAsMenu", NULL, CT_Get, 0, 0},
        {TFunc_Instances_MovieClip_trackAsMenuSet::Func, NULL, "trackAsMenu", NULL, CT_Set, 1, 1},
        {TFunc_Instances_MovieClip_addFrameScript::Func, NULL, "addFrameScript", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_MovieClip_gotoAndPlay::Func, NULL, "gotoAndPlay", NULL, CT_Method, 1, 2},
        {TFunc_Instances_MovieClip_gotoAndStop::Func, NULL, "gotoAndStop", NULL, CT_Method, 1, 2},
        {TFunc_Instances_MovieClip_nextFrame::Func, NULL, "nextFrame", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MovieClip_nextScene::Func, NULL, "nextScene", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MovieClip_play::Func, NULL, "play", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MovieClip_prevFrame::Func, NULL, "prevFrame", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MovieClip_prevScene::Func, NULL, "prevScene", NULL, CT_Method, 0, 0},
        {TFunc_Instances_MovieClip_stop::Func, NULL, "stop", NULL, CT_Method, 0, 0},
    };

    MovieClip::MovieClip(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::MovieClip::MovieClip()"
        SetTraitsType(Traits_MovieClip);
//##protect##"InstanceTraits::MovieClip::MovieClip()"
        SetMemSize(sizeof(Instances::MovieClip));

    }

    Pickable<Instances::MovieClip> MovieClip::MakeInstance(Traits& t)
    {
        return Pickable<Instances::MovieClip>(new(t.Alloc()) Instances::MovieClip(t));
    }

    void MovieClip::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    MovieClip::MovieClip(VM& vm)
    : Traits(vm, MovieClipCI)
    {
//##protect##"ClassTraits::MovieClip::MovieClip()"
        SetTraitsType(Traits_MovieClip);
//##protect##"ClassTraits::MovieClip::MovieClip()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::MovieClip(vm, MovieClipCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> MovieClip::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) MovieClip(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MovieClipCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "MovieClip", "flash.display", &SpriteCI,
    ClassTraits::MovieClip::MakeClassTraits,
    0,
    0,
    InstanceTraits::MovieClip::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::MovieClip::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

