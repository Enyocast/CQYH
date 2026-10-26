//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Sprite.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Sprite.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Display_Graphics.h"
#include "../Media/AS3_Obj_Media_SoundTransform.h"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"

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

} // namespace Impl
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_buttonModeGet, bool> TFunc_Instances_Sprite_buttonModeGet;
typedef ThunkFunc1<Instances::Sprite, Instances::Sprite::mid_buttonModeSet, Value, bool> TFunc_Instances_Sprite_buttonModeSet;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_dropTargetGet, Value> TFunc_Instances_Sprite_dropTargetGet;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_graphicsGet, Value> TFunc_Instances_Sprite_graphicsGet;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_hitAreaGet, Value> TFunc_Instances_Sprite_hitAreaGet;
typedef ThunkFunc1<Instances::Sprite, Instances::Sprite::mid_hitAreaSet, Value, Instances::Sprite*> TFunc_Instances_Sprite_hitAreaSet;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_soundTransformGet, Value> TFunc_Instances_Sprite_soundTransformGet;
typedef ThunkFunc1<Instances::Sprite, Instances::Sprite::mid_soundTransformSet, Value, Instances::SoundTransform*> TFunc_Instances_Sprite_soundTransformSet;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_useHandCursorGet, bool> TFunc_Instances_Sprite_useHandCursorGet;
typedef ThunkFunc1<Instances::Sprite, Instances::Sprite::mid_useHandCursorSet, Value, bool> TFunc_Instances_Sprite_useHandCursorSet;
typedef ThunkFunc2<Instances::Sprite, Instances::Sprite::mid_startDrag, Value, bool, Instances::Rectangle*> TFunc_Instances_Sprite_startDrag;
typedef ThunkFunc0<Instances::Sprite, Instances::Sprite::mid_stopDrag, Value> TFunc_Instances_Sprite_stopDrag;

template <> const TFunc_Instances_Sprite_buttonModeGet::TMethod TFunc_Instances_Sprite_buttonModeGet::Method = &Instances::Sprite::buttonModeGet;
template <> const TFunc_Instances_Sprite_buttonModeSet::TMethod TFunc_Instances_Sprite_buttonModeSet::Method = &Instances::Sprite::buttonModeSet;
template <> const TFunc_Instances_Sprite_dropTargetGet::TMethod TFunc_Instances_Sprite_dropTargetGet::Method = &Instances::Sprite::dropTargetGet;
template <> const TFunc_Instances_Sprite_graphicsGet::TMethod TFunc_Instances_Sprite_graphicsGet::Method = &Instances::Sprite::graphicsGet;
template <> const TFunc_Instances_Sprite_hitAreaGet::TMethod TFunc_Instances_Sprite_hitAreaGet::Method = &Instances::Sprite::hitAreaGet;
template <> const TFunc_Instances_Sprite_hitAreaSet::TMethod TFunc_Instances_Sprite_hitAreaSet::Method = &Instances::Sprite::hitAreaSet;
template <> const TFunc_Instances_Sprite_soundTransformGet::TMethod TFunc_Instances_Sprite_soundTransformGet::Method = &Instances::Sprite::soundTransformGet;
template <> const TFunc_Instances_Sprite_soundTransformSet::TMethod TFunc_Instances_Sprite_soundTransformSet::Method = &Instances::Sprite::soundTransformSet;
template <> const TFunc_Instances_Sprite_useHandCursorGet::TMethod TFunc_Instances_Sprite_useHandCursorGet::Method = &Instances::Sprite::useHandCursorGet;
template <> const TFunc_Instances_Sprite_useHandCursorSet::TMethod TFunc_Instances_Sprite_useHandCursorSet::Method = &Instances::Sprite::useHandCursorSet;
template <> const TFunc_Instances_Sprite_startDrag::TMethod TFunc_Instances_Sprite_startDrag::Method = &Instances::Sprite::startDrag;
template <> const TFunc_Instances_Sprite_stopDrag::TMethod TFunc_Instances_Sprite_stopDrag::Method = &Instances::Sprite::stopDrag;

namespace Instances
{
    Sprite::Sprite(InstanceTraits::Traits& t)
    : Instances::DisplayObjectContainer(t)
//##protect##"instance::Sprite::Sprite()$data"
//##protect##"instance::Sprite::Sprite()$data"
    {
//##protect##"instance::Sprite::Sprite()$code"
//##protect##"instance::Sprite::Sprite()$code"
    }

    void Sprite::buttonModeGet(bool& result)
    {
//##protect##"instance::Sprite::buttonModeGet()"
        SF_UNUSED1(result);
        if (!pDispObj)
            result = false;
        else
            result = static_cast<AvmSprite*>(ToAvmDisplayObj(pDispObj))->IsButtonMode();
//##protect##"instance::Sprite::buttonModeGet()"
    }
    void Sprite::buttonModeSet(Value& result, bool value)
    {
//##protect##"instance::Sprite::buttonModeSet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        static_cast<AvmSprite*>(ToAvmDisplayObj(pDispObj))->SetButtonMode(value);
//##protect##"instance::Sprite::buttonModeSet()"
    }
    void Sprite::dropTargetGet(Value& result)
    {
//##protect##"instance::Sprite::dropTargetGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);

        MovieImpl* proot = pDispObj->GetMovieImpl();
        Render::PointF mousePos = proot->GetMouseState(0)->GetLastPosition();
        // only mouseIndex 0 is supported.
        GFx::InteractiveObject* ptopCh = proot->GetTopMostEntity(mousePos, 0, true, pDispObj->CharToInteractiveObject_Unsafe());
        
        if (ptopCh)
        {
            ToAvmInteractiveObj(ptopCh)->CreateASInstance(true);
            result = ToAvmInteractiveObj(ptopCh)->GetAS3Obj();
        }
        else
        {
            //@TODO
            //GetVM().ThrowError();
            result.SetNull();
        }
//##protect##"instance::Sprite::dropTargetGet()"
    }
    void Sprite::graphicsGet(Value& result)
    {
//##protect##"instance::Sprite::graphicsGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
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
//##protect##"instance::Sprite::graphicsGet()"
    }
    void Sprite::hitAreaGet(Value& result)
    {
//##protect##"instance::Sprite::hitAreaGet()"
        SF_UNUSED1(result);
        if (!pDispObj)
            result.SetNull();
        else
        {
            GFx::Sprite* hitAreaSprite = pDispObj->CharToSprite_Unsafe()->GetHitArea();
            if (hitAreaSprite)
            {
                // sprite should have create AS instance already (AB). 
                //ToAvmSprite(hitAreaSprite)->CreateASInstance(true);
                result = static_cast<Instances::Sprite*>(
                    ToAvmSprite(hitAreaSprite)->GetAS3Obj());
            }
            else
                result.SetNull();
        }
//##protect##"instance::Sprite::hitAreaGet()"
    }
    void Sprite::hitAreaSet(Value& result, Instances::Sprite* value)
    {
//##protect##"instance::Sprite::hitAreaSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);

        if (value)
        {
            if (!value->pDispObj) value->CreateStageObject();
            SF_ASSERT(value->pDispObj);
            pDispObj->CharToSprite_Unsafe()->SetHitArea(value->pDispObj->CharToSprite_Unsafe());
        }
        else 
        {
            pDispObj->CharToSprite_Unsafe()->SetHitArea(NULL);
        }
//##protect##"instance::Sprite::hitAreaSet()"
    }
    void Sprite::soundTransformGet(Value& result)
    {
//##protect##"instance::Sprite::soundTransformGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Sprite::soundTransformGet()");
//##protect##"instance::Sprite::soundTransformGet()"
    }
    void Sprite::soundTransformSet(Value& result, Instances::SoundTransform* value)
    {
//##protect##"instance::Sprite::soundTransformSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Sprite::soundTransformSet()");
//##protect##"instance::Sprite::soundTransformSet()"
    }
    void Sprite::useHandCursorGet(bool& result)
    {
//##protect##"instance::Sprite::useHandCursorGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        result = pDispObj->CharToInteractiveObject_Unsafe()->IsUseHandCursorFlagTrue();
//##protect##"instance::Sprite::useHandCursorGet()"
    }
    void Sprite::useHandCursorSet(Value& result, bool value)
    {
//##protect##"instance::Sprite::useHandCursorSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        pDispObj->CharToInteractiveObject_Unsafe()->SetUseHandCursorFlag(value);
//##protect##"instance::Sprite::useHandCursorSet()"
    }
    void Sprite::startDrag(Value& result, bool lockCenter, Instances::Rectangle* bounds)
    {
//##protect##"instance::Sprite::startDrag()"
        SF_UNUSED3(result, lockCenter, bounds);
        
        SF_ASSERT(pDispObj);
        MovieImpl::DragState st;

        // If there are arguments, init appropriate values.
        if (bounds)
        {
            st.Bound = true;
            st.BoundLT.x = SF_PIXELS_TO_TWIPS((float) bounds->GetX());
            st.BoundLT.y = SF_PIXELS_TO_TWIPS((float) bounds->GetY());
            st.BoundRB.x = SF_PIXELS_TO_TWIPS((float) bounds->GetX() + bounds->GetWidth());
            st.BoundRB.y = SF_PIXELS_TO_TWIPS((float) bounds->GetY() + bounds->GetHeight());
        }

        SF_ASSERT(pDispObj->IsInteractiveObject());
        st.pCharacter = pDispObj->CharToInteractiveObject_Unsafe();
        // Init mouse offsets based on LockCenter flag.
        st.InitCenterDelta(lockCenter);

        // Begin dragging.
        MovieImpl* proot = pDispObj->GetMovieImpl();
        proot->SetDragState(st);  
        pDispObj->CharToInteractiveObject_Unsafe()->ModifyOptimizedPlayList();
//##protect##"instance::Sprite::startDrag()"
    }
    void Sprite::stopDrag(Value& result)
    {
//##protect##"instance::Sprite::stopDrag()"
        SF_UNUSED1(result);

        SF_ASSERT(pDispObj);

        MovieImpl* proot = pDispObj->GetMovieImpl();
        proot->StopDrag();    
        SF_ASSERT(pDispObj->IsInteractiveObject());
        pDispObj->CharToInteractiveObject_Unsafe()->ModifyOptimizedPlayList();
//##protect##"instance::Sprite::stopDrag()"
    }

//##protect##"instance$methods"
    Sprite::~Sprite()
    {

    }

    void Sprite::AS3Constructor(unsigned argc, const Value* argv)
    {
        SF_UNUSED2(argc, argv);
        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        GFx::Sprite* spr = pDispObj->CharToSprite_Unsafe();
        SF_ASSERT(spr);

        ToAvmSprite(spr)->CreateChildren();
    }

    void Sprite::InitInstance(bool extCall)
    {
        if (!extCall)
        {
            // create stage display object if the movieclip was created by
            // "new".
            Sprite::CreateStageObject();
            SF_ASSERT(pDispObj && pDispObj->IsSprite());
            GFx::Sprite* pspr = pDispObj->CharToSprite_Unsafe();
            AvmSprite* avmSpr = ToAvmSprite(pspr);
            // add in playlist
            MovieRoot* as3root = avmSpr->GetAS3Root();
            
            as3root->AddScriptableMovieClip(pspr);
        }
        SF_ASSERT(pDispObj);
        if (IsMovieClip())
        {
            // check if this is a Sprite or a MovieClip.
            // If this is a movieclip, set the appropriate flag and add
            // to the list of scriptable clips.
            pDispObj->SetMovieClipFlag();
        }
    }

    void Sprite::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        DisplayObjectContainer::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<Graphics, Mem_Stat>(prcc, pGraphics, op SF_DEBUG_ARG(*this));
    }

    GFx::DisplayObject* Sprite::CreateStageObject()
    {
        if (!pDispObj)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            MovieRoot* proot = asvm.GetMovieRoot();

            MovieDefImpl* pdefImpl = asvm.GetResourceMovieDef(this);

            if (pdefImpl)
            {
                // it is possible that there is no corresponding stage object
                // for the class; use empty movie clip then.
                CharacterCreateInfo ccinfo;
                ccinfo.pCharDef = NULL;

                FindLibarySymbol(&ccinfo, pdefImpl);
                
                if (!ccinfo.pCharDef)
                {
                    // not found... Let check if there are symbols linked to the same class in other
                    // moviedefs. Seems like Flash does it.
                    if (!proot->FindLibrarySymbolInAllABCs(this, &ccinfo))
                    {
                        ccinfo = pdefImpl->GetCharacterCreateInfo(ResourceId(CharacterDef::CharId_EmptyMovieClip));
                        if (GetVM().GetCallStack().GetSize() > 0)
                        {
                            // figure out MovieDefImpl from current call frame.
                            const VMAbcFile& abcFile = GetVM().GetCurrCallFrame().GetFile();
                            ccinfo.pBindDefImpl = static_cast<const ASVM::AbcFileWithMovieDef&>(abcFile.GetAbcFile()).pDefImpl;
                        }
                        else
                            ccinfo.pBindDefImpl = pdefImpl;
                    }
                }

                SF_ASSERT(ccinfo.pCharDef);
                pDispObj = *static_cast<GFx::DisplayObject*>(proot->GetASSupport()->CreateCharacterInstance(
                    proot->GetMovieImpl(), ccinfo, NULL, 
                    ResourceId(), CharacterDef::Sprite));
                ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);

                SF_ASSERT(pDispObj->IsSprite());
            }
        }
        return pDispObj;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Sprite::ti[Sprite::ThunkInfoNum] = {
        {TFunc_Instances_Sprite_buttonModeGet::Func, &BooleanCI, "buttonMode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_buttonModeSet::Func, NULL, "buttonMode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Sprite_dropTargetGet::Func, &DisplayObjectCI, "dropTarget", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_graphicsGet::Func, &GraphicsCI, "graphics", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_hitAreaGet::Func, &SpriteCI, "hitArea", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_hitAreaSet::Func, NULL, "hitArea", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Sprite_soundTransformGet::Func, &SoundTransformCI, "soundTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_soundTransformSet::Func, NULL, "soundTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Sprite_useHandCursorGet::Func, &BooleanCI, "useHandCursor", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Sprite_useHandCursorSet::Func, NULL, "useHandCursor", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Sprite_startDrag::Func, NULL, "startDrag", NULL, CT_Method, 0, 2},
        {TFunc_Instances_Sprite_stopDrag::Func, NULL, "stopDrag", NULL, CT_Method, 0, 0},
    };

    Sprite::Sprite(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Sprite::Sprite()"
        SetTraitsType(Traits_Sprite);
//##protect##"InstanceTraits::Sprite::Sprite()"
        SetMemSize(sizeof(Instances::Sprite));

    }

    Pickable<Instances::Sprite> Sprite::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Sprite>(new(t.Alloc()) Instances::Sprite(t));
    }

    void Sprite::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Sprite::Sprite(VM& vm)
    : Traits(vm, SpriteCI)
    {
//##protect##"ClassTraits::Sprite::Sprite()"
        SetTraitsType(Traits_Sprite);
//##protect##"ClassTraits::Sprite::Sprite()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Sprite(vm, SpriteCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Sprite::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Sprite(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SpriteCI = {
    ClassInfo::CompileTime,
    "Sprite", "flash.display", &DisplayObjectContainerCI,
    ClassTraits::Sprite::MakeClassTraits,
    0,
    0,
    InstanceTraits::Sprite::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Sprite::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

