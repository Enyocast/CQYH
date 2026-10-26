//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_FocusManager.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy, Prasad Silva

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_FocusManager.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    FocusManager::FocusManager(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::FocusManager::FocusManager()"
//##protect##"class_::FocusManager::FocusManager()"
    }
    void FocusManager::alwaysEnableArrowKeysSet(Value& result, bool enable)
    {
//##protect##"class_::FocusManager::alwaysEnableArrowKeysSet()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
            asvm.GetMovieImpl()->SetAlwaysEnableFocusArrowKeys(enable);

//##protect##"class_::FocusManager::alwaysEnableArrowKeysSet()"
    }
    void FocusManager::alwaysEnableArrowKeysGet(bool& result)
    {
//##protect##"class_::FocusManager::alwaysEnableArrowKeysGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (!asvm.ExtensionsEnabled) return;
        MovieImpl* proot = asvm.GetMovieImpl();
        if (proot->IsAlwaysEnableFocusArrowKeysSet())
            result = proot->IsAlwaysEnableFocusArrowKeys();
        else
            result = false;

//##protect##"class_::FocusManager::alwaysEnableArrowKeysGet()"
    }
    void FocusManager::disableFocusKeysSet(Value& result, bool disable)
    {
//##protect##"class_::FocusManager::disableFocusKeysSet()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
            asvm.GetMovieImpl()->SetDisableFocusKeys(disable);

//##protect##"class_::FocusManager::disableFocusKeysSet()"
    }
    void FocusManager::disableFocusKeysGet(bool& result)
    {
//##protect##"class_::FocusManager::disableFocusKeysGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (!asvm.ExtensionsEnabled) return;
        MovieImpl* proot = asvm.GetMovieImpl();
        if (proot->IsDisableFocusKeysSet())
            result = proot->IsDisableFocusKeys();
        else
            result = false;

//##protect##"class_::FocusManager::disableFocusKeysGet()"
    }
    void FocusManager::moveFocus(Value& result, const ASString& keyToSimulate, Instances::InteractiveObject* startFromMovie, bool includeFocusEnabledChars, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::moveFocus()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            result.SetUndefined();            

            MovieImpl* proot = asvm.GetMovieImpl();
            Ptr<GFx::InteractiveObject> startChar;
            if (startFromMovie)
            {
                startChar = startFromMovie->GetIntObj();
            }
            else
                startChar = proot->GetFocusedCharacter(controllerIdx).GetPtr();

            short keycode;
            KeyModifiers kmods;
            if (keyToSimulate == "up")
                keycode = Key::Up;
            else if (keyToSimulate == "down")
                keycode = Key::Down;
            else if (keyToSimulate == "left")
                keycode = Key::Left;
            else if (keyToSimulate == "right")
                keycode = Key::Right;
            else if (keyToSimulate == "tab")
                keycode = Key::Tab;
            else if (keyToSimulate == "shifttab")
            {
                keycode = Key::Tab;
                kmods.SetShiftPressed(true);
            }
            else
            {                
                if (asvm.GetLog())
                    asvm.GetLog()->LogWarning("moveFocus - invalid string id for key: '%s'",
                    keyToSimulate.ToCStr());
                return;
            }
            ProcessFocusKeyInfo focusInfo;
            InputEventsQueue::QueueEntry::KeyEntry ke;
            ke.KeyboardIndex            = (UInt8)controllerIdx;
            ke.Code                     = keycode;
            ke.KeysState                = kmods.States;
            proot->InitFocusKeyInfo(&focusInfo, ke, includeFocusEnabledChars);
            focusInfo.CurFocused        = startChar;
            focusInfo.ManualFocus       = true;
            proot->ProcessFocusKey(GFx::Event::KeyDown, ke, &focusInfo);
            proot->FinalizeProcessFocusKey(&focusInfo);

            result = ToAvmInteractiveObj(focusInfo.CurFocused)->GetAS3IntObj();
        }

//##protect##"class_::FocusManager::moveFocus()"
    }
    void FocusManager::findFocus(Value& result, const ASString& keyToSimulate, Instances::DisplayObjectContainer* parentMovie, bool loop, Instances::InteractiveObject* startFromMovie, bool includeFocusEnabledChars, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::findFocus()"

    ASVM& asvm = static_cast<ASVM&>(GetVM());
    if (asvm.ExtensionsEnabled)
    {
        result.SetUndefined();

        MovieImpl* proot = asvm.GetMovieImpl();
        Ptr<GFx::InteractiveObject> startChar;
        if (startFromMovie)
        {
            startChar = startFromMovie->GetIntObj();
        }
        else
            startChar = proot->GetFocusedCharacter(controllerIdx).GetPtr();

        short keycode;
        KeyModifiers kmods;
        if (keyToSimulate == "up")
            keycode = Key::Up;
        else if (keyToSimulate == "down")
            keycode = Key::Down;
        else if (keyToSimulate == "left")
            keycode = Key::Left;
        else if (keyToSimulate == "right")
            keycode = Key::Right;
        else if (keyToSimulate == "tab")
            keycode = Key::Tab;
        else if (keyToSimulate == "shifttab")
        {
            keycode = Key::Tab;
            kmods.SetShiftPressed(true);
        }
        else
        {
            /* // PPS: Warning causes unnecessary spew in log with CLIK. CLIK's FocusHandler
               // passes all unhandled key events to findFocus.
            if (fn.Env->GetLog())
                fn.Env->GetLog()->LogWarning("findFocus - invalid string id for key: '%s'",
                directionStr.ToCStr());
            */
            return;
        }

        Ptr<GFx::InteractiveObject> panelChar;
        if (parentMovie)
        {
            panelChar = parentMovie->GetIntObj();
        }
        else
        {
            // take a modal clip as panelChar, if the parameter is "null"
            panelChar = proot->GetModalClip(controllerIdx);
        }

        ProcessFocusKeyInfo focusInfo;
        InputEventsQueue::QueueEntry::KeyEntry ke;
        ke.KeyboardIndex            = (UInt8)controllerIdx;
        ke.Code                     = keycode;
        ke.KeysState                = kmods.States;
        FocusGroupDescr focusGroup(asvm.GetHeap());
        focusGroup.ModalClip        = (panelChar) ? panelChar->GetCharacterHandle() : NULL;
        focusGroup.LastFocused      = startChar;
        proot->InitFocusKeyInfo(&focusInfo, ke, includeFocusEnabledChars, &focusGroup);
        focusInfo.ManualFocus       = true;
        proot->ProcessFocusKey(GFx::Event::KeyDown, ke, &focusInfo);
        if (focusInfo.CurFocused && focusInfo.CurFocused != startChar)
        {
            result = ToAvmInteractiveObj(focusInfo.CurFocused)->GetAS3IntObj();
        }
        else
        {
            if (!loop || focusGroup.TabableArray.GetSize() == 0)
            {
                result.SetNull();
            }
            else
            {
                if (keycode == Key::Tab)
                {
                    if (!kmods.IsShiftPressed())
                    {
                        result = ToAvmInteractiveObj(focusGroup.TabableArray[0])->GetAS3IntObj();
                    }
                    else
                    {
                        result = ToAvmInteractiveObj(focusGroup.TabableArray[focusGroup.TabableArray.GetSize()-1])->GetAS3IntObj();
                    }
                }
                else
                {
                    float lastV = SF_MIN_FLOAT;
                    UPInt index = 0;
                    for (UPInt i = 0, n = focusGroup.TabableArray.GetSize(); i < n; ++i)
                    {
                        Ptr<GFx::InteractiveObject> b = focusGroup.TabableArray[i];
                        if ((!focusInfo.InclFocusEnabled && !b->IsTabable()) ||
                            !b->IsFocusAllowed(proot, focusInfo.KeyboardIndex))
                        {
                            // If this is not for manual focus and not tabable - ignore.
                            continue;
                        }
                        GFx::DisplayObject::Matrix mb = b->GetLevelMatrix();
                        RectF bRect  = mb.EncloseTransform(b->GetFocusRect());
                        switch (keycode)
                        {
                        case Key::Down: 
                            // find top
                            if (lastV == SF_MIN_FLOAT || bRect.y1 < lastV)
                            {
                                lastV = bRect.y1;
                                index = i;
                            }
                            break; //
                        case Key::Up: 
                            // find bottom
                            if (lastV == SF_MIN_FLOAT || bRect.y2 > lastV)
                            {
                                lastV = bRect.y2;
                                index = i;
                            }
                            break; //
                        case Key::Left: 
                            // find most right
                            if (lastV == SF_MIN_FLOAT || bRect.x2 > lastV)
                            {
                                lastV = bRect.x2;
                                index = i;
                            }
                            break; //
                        case Key::Right: 
                            // find most left
                            if (lastV == SF_MIN_FLOAT || bRect.x1 < lastV)
                            {
                                lastV = bRect.x1;
                                index = i;
                            }
                            break; //
                        default: SF_ASSERT(0);
                        }
                    }
                    result = ToAvmInteractiveObj(focusGroup.TabableArray[index])->GetAS3IntObj();
                }
            }
        }
    }

//##protect##"class_::FocusManager::findFocus()"
    }
    void FocusManager::setFocus(Value& result, Instances::InteractiveObject* obj, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::setFocus()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        Ptr<GFx::InteractiveObject> newFocus;
        if (obj)
            newFocus = obj->GetIntObj();
        Ptr<GFx::InteractiveObject> focused = asvm.GetMovieImpl()->GetFocusedCharacter(controllerIdx);
        if (focused != newFocus)
            asvm.GetMovieImpl()->SetKeyboardFocusTo(newFocus, controllerIdx, GFx_FocusMovedByAS); 

//##protect##"class_::FocusManager::setFocus()"
    }
    void FocusManager::getFocus(Value& result, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::getFocus()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        Ptr<GFx::InteractiveObject> focused = asvm.GetMovieImpl()->GetFocusedCharacter(controllerIdx);
        if (!focused)
            result.SetNull();
        else
            result = Value(ToAvmInteractiveObj(focused)->GetAS3Obj());

//##protect##"class_::FocusManager::getFocus()"
    }
    void FocusManager::numFocusGroupsGet(UInt32& result)
    {
//##protect##"class_::FocusManager::numFocusGroupsGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        MovieImpl* proot = asvm.GetMovieImpl();
        result = proot->GetFocusGroupCount();

//##protect##"class_::FocusManager::numFocusGroupsGet()"
    }
    void FocusManager::setFocusGroupMask(Value& result, Instances::InteractiveObject* obj, UInt32 mask)
    {
//##protect##"class_::FocusManager::setFocusGroupMask()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            if (obj) 
                obj->GetIntObj()->PropagateFocusGroupMask(mask);
        }

//##protect##"class_::FocusManager::setFocusGroupMask()"
    }
    void FocusManager::getFocusGroupMask(UInt32& result, Instances::InteractiveObject* obj)
    {
//##protect##"class_::FocusManager::getFocusGroupMask()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            result = obj->GetIntObj()->GetFocusGroupMask();
        }

//##protect##"class_::FocusManager::getFocusGroupMask()"
    }
    void FocusManager::setControllerFocusGroup(bool& result, UInt32 controllerIdx, UInt32 focusGroupIdx)
    {
//##protect##"class_::FocusManager::setControllerFocusGroup()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            result = proot->SetControllerFocusGroup(controllerIdx, focusGroupIdx);
        }
        else 
            result = false;

//##protect##"class_::FocusManager::setControllerFocusGroup()"
    }
    void FocusManager::getControllerFocusGroup(UInt32& result, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::getControllerFocusGroup()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            result = proot->GetControllerFocusGroup(controllerIdx);
        }
        else
            result = 0;

//##protect##"class_::FocusManager::getControllerFocusGroup()"
    }
    void FocusManager::getControllerMaskByFocusGroup(UInt32& result, UInt32 focusGroupIdx)
    {
//##protect##"class_::FocusManager::getControllerMaskByFocusGroup()"
		
		ASVM& asvm = static_cast<ASVM&>(GetVM());		
		if (asvm.ExtensionsEnabled)
		{
			MovieImpl* proot = asvm.GetMovieImpl();
			result = proot->GetControllerMaskByFocusGroup(focusGroupIdx);
		}
		else 
		{
			result = 0;
		}
//##protect##"class_::FocusManager::getControllerMaskByFocusGroup()"
    }
    void FocusManager::getModalClip(Value& result, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::getModalClip()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            GFx::Sprite* pmodalClip = proot->GetModalClip(controllerIdx);
            if (pmodalClip)
                result = ToAvmSprite(pmodalClip)->GetAS3Obj();
        }

//##protect##"class_::FocusManager::getModalClip()"
    }
    void FocusManager::setModalClip(Value& result, Instances::Sprite* mc, UInt32 controllerIdx)
    {
//##protect##"class_::FocusManager::setModalClip()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            if (mc)
            {
                proot->SetModalClip(static_cast<GFx::Sprite*>(mc->pDispObj.GetPtr()), controllerIdx);
            }
            else
                proot->SetModalClip(NULL, controllerIdx);
        }

//##protect##"class_::FocusManager::setModalClip()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_alwaysEnableArrowKeysSet, Value, bool> TFunc_Classes_FocusManager_alwaysEnableArrowKeysSet;
typedef ThunkFunc0<Classes::FocusManager, Classes::FocusManager::mid_alwaysEnableArrowKeysGet, bool> TFunc_Classes_FocusManager_alwaysEnableArrowKeysGet;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_disableFocusKeysSet, Value, bool> TFunc_Classes_FocusManager_disableFocusKeysSet;
typedef ThunkFunc0<Classes::FocusManager, Classes::FocusManager::mid_disableFocusKeysGet, bool> TFunc_Classes_FocusManager_disableFocusKeysGet;
typedef ThunkFunc4<Classes::FocusManager, Classes::FocusManager::mid_moveFocus, Value, const ASString&, Instances::InteractiveObject*, bool, UInt32> TFunc_Classes_FocusManager_moveFocus;
typedef ThunkFunc6<Classes::FocusManager, Classes::FocusManager::mid_findFocus, Value, const ASString&, Instances::DisplayObjectContainer*, bool, Instances::InteractiveObject*, bool, UInt32> TFunc_Classes_FocusManager_findFocus;
typedef ThunkFunc2<Classes::FocusManager, Classes::FocusManager::mid_setFocus, Value, Instances::InteractiveObject*, UInt32> TFunc_Classes_FocusManager_setFocus;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_getFocus, Value, UInt32> TFunc_Classes_FocusManager_getFocus;
typedef ThunkFunc0<Classes::FocusManager, Classes::FocusManager::mid_numFocusGroupsGet, UInt32> TFunc_Classes_FocusManager_numFocusGroupsGet;
typedef ThunkFunc2<Classes::FocusManager, Classes::FocusManager::mid_setFocusGroupMask, Value, Instances::InteractiveObject*, UInt32> TFunc_Classes_FocusManager_setFocusGroupMask;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_getFocusGroupMask, UInt32, Instances::InteractiveObject*> TFunc_Classes_FocusManager_getFocusGroupMask;
typedef ThunkFunc2<Classes::FocusManager, Classes::FocusManager::mid_setControllerFocusGroup, bool, UInt32, UInt32> TFunc_Classes_FocusManager_setControllerFocusGroup;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_getControllerFocusGroup, UInt32, UInt32> TFunc_Classes_FocusManager_getControllerFocusGroup;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_getControllerMaskByFocusGroup, UInt32, UInt32> TFunc_Classes_FocusManager_getControllerMaskByFocusGroup;
typedef ThunkFunc1<Classes::FocusManager, Classes::FocusManager::mid_getModalClip, Value, UInt32> TFunc_Classes_FocusManager_getModalClip;
typedef ThunkFunc2<Classes::FocusManager, Classes::FocusManager::mid_setModalClip, Value, Instances::Sprite*, UInt32> TFunc_Classes_FocusManager_setModalClip;

template <> const TFunc_Classes_FocusManager_alwaysEnableArrowKeysSet::TMethod TFunc_Classes_FocusManager_alwaysEnableArrowKeysSet::Method = &Classes::FocusManager::alwaysEnableArrowKeysSet;
template <> const TFunc_Classes_FocusManager_alwaysEnableArrowKeysGet::TMethod TFunc_Classes_FocusManager_alwaysEnableArrowKeysGet::Method = &Classes::FocusManager::alwaysEnableArrowKeysGet;
template <> const TFunc_Classes_FocusManager_disableFocusKeysSet::TMethod TFunc_Classes_FocusManager_disableFocusKeysSet::Method = &Classes::FocusManager::disableFocusKeysSet;
template <> const TFunc_Classes_FocusManager_disableFocusKeysGet::TMethod TFunc_Classes_FocusManager_disableFocusKeysGet::Method = &Classes::FocusManager::disableFocusKeysGet;
template <> const TFunc_Classes_FocusManager_moveFocus::TMethod TFunc_Classes_FocusManager_moveFocus::Method = &Classes::FocusManager::moveFocus;
template <> const TFunc_Classes_FocusManager_findFocus::TMethod TFunc_Classes_FocusManager_findFocus::Method = &Classes::FocusManager::findFocus;
template <> const TFunc_Classes_FocusManager_setFocus::TMethod TFunc_Classes_FocusManager_setFocus::Method = &Classes::FocusManager::setFocus;
template <> const TFunc_Classes_FocusManager_getFocus::TMethod TFunc_Classes_FocusManager_getFocus::Method = &Classes::FocusManager::getFocus;
template <> const TFunc_Classes_FocusManager_numFocusGroupsGet::TMethod TFunc_Classes_FocusManager_numFocusGroupsGet::Method = &Classes::FocusManager::numFocusGroupsGet;
template <> const TFunc_Classes_FocusManager_setFocusGroupMask::TMethod TFunc_Classes_FocusManager_setFocusGroupMask::Method = &Classes::FocusManager::setFocusGroupMask;
template <> const TFunc_Classes_FocusManager_getFocusGroupMask::TMethod TFunc_Classes_FocusManager_getFocusGroupMask::Method = &Classes::FocusManager::getFocusGroupMask;
template <> const TFunc_Classes_FocusManager_setControllerFocusGroup::TMethod TFunc_Classes_FocusManager_setControllerFocusGroup::Method = &Classes::FocusManager::setControllerFocusGroup;
template <> const TFunc_Classes_FocusManager_getControllerFocusGroup::TMethod TFunc_Classes_FocusManager_getControllerFocusGroup::Method = &Classes::FocusManager::getControllerFocusGroup;
template <> const TFunc_Classes_FocusManager_getControllerMaskByFocusGroup::TMethod TFunc_Classes_FocusManager_getControllerMaskByFocusGroup::Method = &Classes::FocusManager::getControllerMaskByFocusGroup;
template <> const TFunc_Classes_FocusManager_getModalClip::TMethod TFunc_Classes_FocusManager_getModalClip::Method = &Classes::FocusManager::getModalClip;
template <> const TFunc_Classes_FocusManager_setModalClip::TMethod TFunc_Classes_FocusManager_setModalClip::Method = &Classes::FocusManager::setModalClip;

namespace ClassTraits
{
    const ThunkInfo FocusManager::ti[FocusManager::ThunkInfoNum] = {
        {TFunc_Classes_FocusManager_alwaysEnableArrowKeysSet::Func, NULL, "alwaysEnableArrowKeys", NULL, CT_Set, 1, 1},
        {TFunc_Classes_FocusManager_alwaysEnableArrowKeysGet::Func, &BooleanCI, "alwaysEnableArrowKeys", NULL, CT_Get, 0, 0},
        {TFunc_Classes_FocusManager_disableFocusKeysSet::Func, NULL, "disableFocusKeys", NULL, CT_Set, 1, 1},
        {TFunc_Classes_FocusManager_disableFocusKeysGet::Func, &BooleanCI, "disableFocusKeys", NULL, CT_Get, 0, 0},
        {TFunc_Classes_FocusManager_moveFocus::Func, &InteractiveObjectCI, "moveFocus", NULL, CT_Method, 1, 4},
        {TFunc_Classes_FocusManager_findFocus::Func, &InteractiveObjectCI, "findFocus", NULL, CT_Method, 1, 6},
        {TFunc_Classes_FocusManager_setFocus::Func, NULL, "setFocus", NULL, CT_Method, 1, 2},
        {TFunc_Classes_FocusManager_getFocus::Func, &InteractiveObjectCI, "getFocus", NULL, CT_Method, 0, 1},
        {TFunc_Classes_FocusManager_numFocusGroupsGet::Func, &uintCI, "numFocusGroups", NULL, CT_Get, 0, 0},
        {TFunc_Classes_FocusManager_setFocusGroupMask::Func, NULL, "setFocusGroupMask", NULL, CT_Method, 2, 2},
        {TFunc_Classes_FocusManager_getFocusGroupMask::Func, &uintCI, "getFocusGroupMask", NULL, CT_Method, 1, 1},
        {TFunc_Classes_FocusManager_setControllerFocusGroup::Func, &BooleanCI, "setControllerFocusGroup", NULL, CT_Method, 2, 2},
        {TFunc_Classes_FocusManager_getControllerFocusGroup::Func, &uintCI, "getControllerFocusGroup", NULL, CT_Method, 1, 1},
        {TFunc_Classes_FocusManager_getControllerMaskByFocusGroup::Func, &uintCI, "getControllerMaskByFocusGroup", NULL, CT_Method, 1, 1},
        {TFunc_Classes_FocusManager_getModalClip::Func, &SpriteCI, "getModalClip", NULL, CT_Method, 0, 1},
        {TFunc_Classes_FocusManager_setModalClip::Func, NULL, "setModalClip", NULL, CT_Method, 1, 2},
    };
    FocusManager::FocusManager(VM& vm)
    : Traits(vm, FocusManagerCI)
    {
//##protect##"ClassTraits::FocusManager::FocusManager()"
//##protect##"ClassTraits::FocusManager::FocusManager()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, FocusManagerCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::FocusManager(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> FocusManager::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) FocusManager(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo FocusManagerCI = {
    ClassInfo::CompileTime,
    "FocusManager", "scaleform.gfx", &ObjectCI,
    ClassTraits::FocusManager::MakeClassTraits,
    ClassTraits::FocusManager::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::FocusManager::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

