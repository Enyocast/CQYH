//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SimpleButton.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_SimpleButton.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Media/AS3_Obj_Media_SoundTransform.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/GFx_CharacterDef.h"
#include "GFx/GFx_Resource.h"
#include "GFx/AS3/AS3_AvmButton.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_downStateGet, Value> TFunc_Instances_SimpleButton_downStateGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_downStateSet, Value, Instances::DisplayObject*> TFunc_Instances_SimpleButton_downStateSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_enabledGet, bool> TFunc_Instances_SimpleButton_enabledGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_enabledSet, Value, bool> TFunc_Instances_SimpleButton_enabledSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_hitTestStateGet, Value> TFunc_Instances_SimpleButton_hitTestStateGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_hitTestStateSet, Value, Instances::DisplayObject*> TFunc_Instances_SimpleButton_hitTestStateSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_overStateGet, Value> TFunc_Instances_SimpleButton_overStateGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_overStateSet, Value, Instances::DisplayObject*> TFunc_Instances_SimpleButton_overStateSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_soundTransformGet, Value> TFunc_Instances_SimpleButton_soundTransformGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_soundTransformSet, Value, Instances::SoundTransform*> TFunc_Instances_SimpleButton_soundTransformSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_trackAsMenuGet, bool> TFunc_Instances_SimpleButton_trackAsMenuGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_trackAsMenuSet, Value, bool> TFunc_Instances_SimpleButton_trackAsMenuSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_upStateGet, Value> TFunc_Instances_SimpleButton_upStateGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_upStateSet, Value, Instances::DisplayObject*> TFunc_Instances_SimpleButton_upStateSet;
typedef ThunkFunc0<Instances::SimpleButton, Instances::SimpleButton::mid_useHandCursorGet, bool> TFunc_Instances_SimpleButton_useHandCursorGet;
typedef ThunkFunc1<Instances::SimpleButton, Instances::SimpleButton::mid_useHandCursorSet, Value, bool> TFunc_Instances_SimpleButton_useHandCursorSet;

template <> const TFunc_Instances_SimpleButton_downStateGet::TMethod TFunc_Instances_SimpleButton_downStateGet::Method = &Instances::SimpleButton::downStateGet;
template <> const TFunc_Instances_SimpleButton_downStateSet::TMethod TFunc_Instances_SimpleButton_downStateSet::Method = &Instances::SimpleButton::downStateSet;
template <> const TFunc_Instances_SimpleButton_enabledGet::TMethod TFunc_Instances_SimpleButton_enabledGet::Method = &Instances::SimpleButton::enabledGet;
template <> const TFunc_Instances_SimpleButton_enabledSet::TMethod TFunc_Instances_SimpleButton_enabledSet::Method = &Instances::SimpleButton::enabledSet;
template <> const TFunc_Instances_SimpleButton_hitTestStateGet::TMethod TFunc_Instances_SimpleButton_hitTestStateGet::Method = &Instances::SimpleButton::hitTestStateGet;
template <> const TFunc_Instances_SimpleButton_hitTestStateSet::TMethod TFunc_Instances_SimpleButton_hitTestStateSet::Method = &Instances::SimpleButton::hitTestStateSet;
template <> const TFunc_Instances_SimpleButton_overStateGet::TMethod TFunc_Instances_SimpleButton_overStateGet::Method = &Instances::SimpleButton::overStateGet;
template <> const TFunc_Instances_SimpleButton_overStateSet::TMethod TFunc_Instances_SimpleButton_overStateSet::Method = &Instances::SimpleButton::overStateSet;
template <> const TFunc_Instances_SimpleButton_soundTransformGet::TMethod TFunc_Instances_SimpleButton_soundTransformGet::Method = &Instances::SimpleButton::soundTransformGet;
template <> const TFunc_Instances_SimpleButton_soundTransformSet::TMethod TFunc_Instances_SimpleButton_soundTransformSet::Method = &Instances::SimpleButton::soundTransformSet;
template <> const TFunc_Instances_SimpleButton_trackAsMenuGet::TMethod TFunc_Instances_SimpleButton_trackAsMenuGet::Method = &Instances::SimpleButton::trackAsMenuGet;
template <> const TFunc_Instances_SimpleButton_trackAsMenuSet::TMethod TFunc_Instances_SimpleButton_trackAsMenuSet::Method = &Instances::SimpleButton::trackAsMenuSet;
template <> const TFunc_Instances_SimpleButton_upStateGet::TMethod TFunc_Instances_SimpleButton_upStateGet::Method = &Instances::SimpleButton::upStateGet;
template <> const TFunc_Instances_SimpleButton_upStateSet::TMethod TFunc_Instances_SimpleButton_upStateSet::Method = &Instances::SimpleButton::upStateSet;
template <> const TFunc_Instances_SimpleButton_useHandCursorGet::TMethod TFunc_Instances_SimpleButton_useHandCursorGet::Method = &Instances::SimpleButton::useHandCursorGet;
template <> const TFunc_Instances_SimpleButton_useHandCursorSet::TMethod TFunc_Instances_SimpleButton_useHandCursorSet::Method = &Instances::SimpleButton::useHandCursorSet;

namespace Instances
{
    SimpleButton::SimpleButton(InstanceTraits::Traits& t)
    : Instances::InteractiveObject(t)
//##protect##"instance::SimpleButton::SimpleButton()$data"
//##protect##"instance::SimpleButton::SimpleButton()$data"
    {
//##protect##"instance::SimpleButton::SimpleButton()$code"
//##protect##"instance::SimpleButton::SimpleButton()$code"
    }

    void SimpleButton::downStateGet(Value& result)
    {
//##protect##"instance::SimpleButton::downStateGet()"
        SF_UNUSED1(result);
        GFx::DisplayObject* state = GetAvmButton()->GetDownStateObject();
        if (state)
        {
            result = Value(ToAvmDisplayObj(state)->GetAS3Obj());
        }
        else
            result.SetUndefined();
//##protect##"instance::SimpleButton::downStateGet()"
    }
    void SimpleButton::downStateSet(Value& result, Instances::DisplayObject* value)
    {
//##protect##"instance::SimpleButton::downStateSet()"
        SF_UNUSED2(result, value);
        GetAvmButton()->SetDownStateObject(value->pDispObj);
//##protect##"instance::SimpleButton::downStateSet()"
    }
    void SimpleButton::enabledGet(bool& result)
    {
//##protect##"instance::SimpleButton::enabledGet()"
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        result = pDispObj->CharToInteractiveObject_Unsafe()->IsEnabledFlagSet();
//##protect##"instance::SimpleButton::enabledGet()"
    }
    void SimpleButton::enabledSet(Value& result, bool value)
    {
//##protect##"instance::SimpleButton::enabledSet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());

        pDispObj->CharToInteractiveObject_Unsafe()->SetEnabledFlag(value);
//##protect##"instance::SimpleButton::enabledSet()"
    }
    void SimpleButton::hitTestStateGet(Value& result)
    {
//##protect##"instance::SimpleButton::hitTestStateGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        GFx::DisplayObject* state = GetAvmButton()->GetHitStateObject();
        if (state)
        {
            result = Value(ToAvmDisplayObj(state)->GetAS3Obj());
        }
        else
            result.SetUndefined();
//##protect##"instance::SimpleButton::hitTestStateGet()"
    }
    void SimpleButton::hitTestStateSet(Value& result, Instances::DisplayObject* value)
    {
//##protect##"instance::SimpleButton::hitTestStateSet()"
        SF_UNUSED2(result, value);
        GetAvmButton()->SetHitStateObject(value->pDispObj);
//##protect##"instance::SimpleButton::hitTestStateSet()"
    }
    void SimpleButton::overStateGet(Value& result)
    {
//##protect##"instance::SimpleButton::overStateGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        GFx::DisplayObject* state = GetAvmButton()->GetOverStateObject();
        if (state)
        {
            result = Value(ToAvmDisplayObj(state)->GetAS3Obj());
        }
        else
            result.SetUndefined();
//##protect##"instance::SimpleButton::overStateGet()"
    }
    void SimpleButton::overStateSet(Value& result, Instances::DisplayObject* value)
    {
//##protect##"instance::SimpleButton::overStateSet()"
        SF_UNUSED2(result, value);
        GetAvmButton()->SetOverStateObject(value->pDispObj);
//##protect##"instance::SimpleButton::overStateSet()"
    }
    void SimpleButton::soundTransformGet(Value& result)
    {
//##protect##"instance::SimpleButton::soundTransformGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("SimpleButton::soundTransformGet()");
//##protect##"instance::SimpleButton::soundTransformGet()"
    }
    void SimpleButton::soundTransformSet(Value& result, Instances::SoundTransform* value)
    {
//##protect##"instance::SimpleButton::soundTransformSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("SimpleButton::soundTransformSet()");
//##protect##"instance::SimpleButton::soundTransformSet()"
    }
    void SimpleButton::trackAsMenuGet(bool& result)
    {
//##protect##"instance::SimpleButton::trackAsMenuGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        GFx::InteractiveObject* spr = pDispObj->CharToInteractiveObject_Unsafe();
        SF_ASSERT(spr);
        result = spr->GetTrackAsMenu();
//##protect##"instance::SimpleButton::trackAsMenuGet()"
    }
    void SimpleButton::trackAsMenuSet(Value& result, bool value)
    {
//##protect##"instance::SimpleButton::trackAsMenuSet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        GFx::InteractiveObject* spr = pDispObj->CharToInteractiveObject_Unsafe();
        SF_ASSERT(spr);
        spr->SetTrackAsMenuFlag(value);
//##protect##"instance::SimpleButton::trackAsMenuSet()"
    }
    void SimpleButton::upStateGet(Value& result)
    {
//##protect##"instance::SimpleButton::upStateGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        GFx::DisplayObject* state = GetAvmButton()->GetUpStateObject();
        if (state)
        {
            result = Value(ToAvmDisplayObj(state)->GetAS3Obj());
        }
        else
            result.SetUndefined();
//##protect##"instance::SimpleButton::upStateGet()"
    }
    void SimpleButton::upStateSet(Value& result, Instances::DisplayObject* value)
    {
//##protect##"instance::SimpleButton::upStateSet()"
        SF_UNUSED2(result, value);
        GetAvmButton()->SetUpStateObject(value->pDispObj);
//##protect##"instance::SimpleButton::upStateSet()"
    }
    void SimpleButton::useHandCursorGet(bool& result)
    {
//##protect##"instance::SimpleButton::useHandCursorGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        result = pDispObj->CharToInteractiveObject_Unsafe()->IsUseHandCursorFlagTrue();
//##protect##"instance::SimpleButton::useHandCursorGet()"
    }
    void SimpleButton::useHandCursorSet(Value& result, bool value)
    {
//##protect##"instance::SimpleButton::useHandCursorSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj && pDispObj->IsInteractiveObject());
        pDispObj->CharToInteractiveObject_Unsafe()->SetUseHandCursorFlag(value);
//##protect##"instance::SimpleButton::useHandCursorSet()"
    }

//##protect##"instance$methods"
    AvmButton* SimpleButton::GetAvmButton() const
    {
        SF_ASSERT(pDispObj);
        return static_cast<AvmButton*>(ToAvmDisplayObj(pDispObj));
    }

    void SimpleButton::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1)
        {
            if (GetVM().IsOfType(argv[0], "flash.display.DisplayObject"))
            {
                DisplayObject* value = static_cast<DisplayObject*>(argv[0].GetObject());
                GetAvmButton()->SetUpStateObject(value->pDispObj);
            }
        }
        if (argc >= 2)
        {
            if (GetVM().IsOfType(argv[1], "flash.display.DisplayObject"))
            {
                DisplayObject* value = static_cast<DisplayObject*>(argv[1].GetObject());
                GetAvmButton()->SetOverStateObject(value->pDispObj);
            }
        }
        if (argc >= 3)
        {
            if (GetVM().IsOfType(argv[2], "flash.display.DisplayObject"))
            {
                DisplayObject* value = static_cast<DisplayObject*>(argv[2].GetObject());
                GetAvmButton()->SetDownStateObject(value->pDispObj);
            }
        }
        if (argc >= 4)
        {
            if (GetVM().IsOfType(argv[3], "flash.display.DisplayObject"))
            {
                DisplayObject* value = static_cast<DisplayObject*>(argv[3].GetObject());
                GetAvmButton()->SetHitStateObject(value->pDispObj);
            }
        }
    }

    void SimpleButton::InitInstance(bool extCall)
    {
        if (!extCall)
            SimpleButton::CreateStageObject();
    }

    GFx::DisplayObject* SimpleButton::CreateStageObject()
    {
        if (!pDispObj)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();
            MovieDefImpl* pdefImpl = asvm.GetResourceMovieDef(this);

            if (pdefImpl)
            {
                // it is possible that there is no corresponding stage object
                // for the class; use empty button then.
                CharacterCreateInfo ccinfo;
                ccinfo.pCharDef     = NULL;

                FindLibarySymbol(&ccinfo, pdefImpl);

                if (!ccinfo.pCharDef)
                {
                    ccinfo = pdefImpl->GetCharacterCreateInfo(ResourceId(CharacterDef::CharId_EmptyButton));
                    // figure out MovieDefImpl from current call frame.
                    const VMAbcFile& abcFile = GetVM().GetCurrCallFrame().GetFile();
                    ccinfo.pBindDefImpl = static_cast<const ASVM::AbcFileWithMovieDef&>(abcFile.GetAbcFile()).pDefImpl;
                }

                SF_ASSERT(ccinfo.pCharDef);
                pDispObj = *static_cast<GFx::DisplayObject*>(proot->GetASSupport()->CreateCharacterInstance(
                    proot->GetMovieImpl(), ccinfo, NULL, 
                    ResourceId(), CharacterDef::Button));
                ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);
                static_cast<Button*>(pDispObj.GetPtr())->CreateCharacters();
            }
        }
        return pDispObj;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo SimpleButton::ti[SimpleButton::ThunkInfoNum] = {
        {TFunc_Instances_SimpleButton_downStateGet::Func, &DisplayObjectCI, "downState", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_downStateSet::Func, NULL, "downState", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_enabledGet::Func, &BooleanCI, "enabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_enabledSet::Func, NULL, "enabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_hitTestStateGet::Func, &DisplayObjectCI, "hitTestState", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_hitTestStateSet::Func, NULL, "hitTestState", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_overStateGet::Func, &DisplayObjectCI, "overState", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_overStateSet::Func, NULL, "overState", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_soundTransformGet::Func, &SoundTransformCI, "soundTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_soundTransformSet::Func, NULL, "soundTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_trackAsMenuGet::Func, &BooleanCI, "trackAsMenu", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_trackAsMenuSet::Func, NULL, "trackAsMenu", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_upStateGet::Func, &DisplayObjectCI, "upState", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_upStateSet::Func, NULL, "upState", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SimpleButton_useHandCursorGet::Func, &BooleanCI, "useHandCursor", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SimpleButton_useHandCursorSet::Func, NULL, "useHandCursor", NULL, CT_Set, 1, 1},
    };

    SimpleButton::SimpleButton(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SimpleButton::SimpleButton()"
        SetTraitsType(Traits_SimpleButton);
//##protect##"InstanceTraits::SimpleButton::SimpleButton()"
        SetMemSize(sizeof(Instances::SimpleButton));

    }

    Pickable<Instances::SimpleButton> SimpleButton::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SimpleButton>(new(t.Alloc()) Instances::SimpleButton(t));
    }

    void SimpleButton::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    SimpleButton::SimpleButton(VM& vm)
    : Traits(vm, SimpleButtonCI)
    {
//##protect##"ClassTraits::SimpleButton::SimpleButton()"
        SetTraitsType(Traits_SimpleButton);
//##protect##"ClassTraits::SimpleButton::SimpleButton()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SimpleButton(vm, SimpleButtonCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SimpleButton::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SimpleButton(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SimpleButtonCI = {
    ClassInfo::CompileTime,
    "SimpleButton", "flash.display", &InteractiveObjectCI,
    ClassTraits::SimpleButton::MakeClassTraits,
    0,
    0,
    InstanceTraits::SimpleButton::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::SimpleButton::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

