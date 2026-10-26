//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Stage.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Stage.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "../Text/AS3_Obj_Text_TextSnapshot.h"
#include "../Events/AS3_Obj_Events_Event.h"
#include "GFx/AS3/AS3_AvmInteractiveObj.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeWindow;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_alignGet, ASString> TFunc_Instances_Stage_alignGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_alignSet, Value, const ASString&> TFunc_Instances_Stage_alignSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_autoOrientsGet, bool> TFunc_Instances_Stage_autoOrientsGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_deviceOrientationGet, ASString> TFunc_Instances_Stage_deviceOrientationGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_displayStateGet, ASString> TFunc_Instances_Stage_displayStateGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_displayStateSet, Value, const ASString&> TFunc_Instances_Stage_displayStateSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_focusGet, Value> TFunc_Instances_Stage_focusGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_focusSet, Value, Instances::InteractiveObject*> TFunc_Instances_Stage_focusSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_frameRateGet, Value::Number> TFunc_Instances_Stage_frameRateGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_frameRateSet, Value, Value::Number> TFunc_Instances_Stage_frameRateSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_fullScreenHeightGet, UInt32> TFunc_Instances_Stage_fullScreenHeightGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_fullScreenSourceRectGet, Value> TFunc_Instances_Stage_fullScreenSourceRectGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_fullScreenSourceRectSet, Value, Instances::Rectangle*> TFunc_Instances_Stage_fullScreenSourceRectSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_fullScreenWidthGet, UInt32> TFunc_Instances_Stage_fullScreenWidthGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_heightGet, Value::Number> TFunc_Instances_Stage_heightGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_heightSet, Value, Value::Number> TFunc_Instances_Stage_heightSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_mouseChildrenGet, bool> TFunc_Instances_Stage_mouseChildrenGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_mouseChildrenSet, Value, bool> TFunc_Instances_Stage_mouseChildrenSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_nativeWindowGet, Value> TFunc_Instances_Stage_nativeWindowGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_numChildrenGet, SInt32> TFunc_Instances_Stage_numChildrenGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_orientationGet, ASString> TFunc_Instances_Stage_orientationGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_qualityGet, ASString> TFunc_Instances_Stage_qualityGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_qualitySet, Value, const ASString&> TFunc_Instances_Stage_qualitySet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_scaleModeGet, ASString> TFunc_Instances_Stage_scaleModeGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_scaleModeSet, Value, const ASString&> TFunc_Instances_Stage_scaleModeSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_showDefaultContextMenuGet, bool> TFunc_Instances_Stage_showDefaultContextMenuGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_showDefaultContextMenuSet, Value, bool> TFunc_Instances_Stage_showDefaultContextMenuSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_stageFocusRectGet, bool> TFunc_Instances_Stage_stageFocusRectGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_stageFocusRectSet, Value, bool> TFunc_Instances_Stage_stageFocusRectSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_stageHeightGet, SInt32> TFunc_Instances_Stage_stageHeightGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_stageHeightSet, Value, SInt32> TFunc_Instances_Stage_stageHeightSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_stageWidthGet, SInt32> TFunc_Instances_Stage_stageWidthGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_stageWidthSet, Value, SInt32> TFunc_Instances_Stage_stageWidthSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_tabChildrenGet, bool> TFunc_Instances_Stage_tabChildrenGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_tabChildrenSet, Value, bool> TFunc_Instances_Stage_tabChildrenSet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_textSnapshotGet, Value> TFunc_Instances_Stage_textSnapshotGet;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_widthGet, Value::Number> TFunc_Instances_Stage_widthGet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_widthSet, Value, Value::Number> TFunc_Instances_Stage_widthSet;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_addChild, Value, Instances::DisplayObject*> TFunc_Instances_Stage_addChild;
typedef ThunkFunc2<Instances::Stage, Instances::Stage::mid_addChildAt, Value, Instances::DisplayObject*, SInt32> TFunc_Instances_Stage_addChildAt;
typedef ThunkFunc5<Instances::Stage, Instances::Stage::mid_addEventListener, Value, const ASString&, const Value&, bool, SInt32, bool> TFunc_Instances_Stage_addEventListener;
typedef ThunkFunc2<Instances::Stage, Instances::Stage::mid_assignFocus, Value, Instances::InteractiveObject*, const ASString&> TFunc_Instances_Stage_assignFocus;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_dispatchEvent, bool, Instances::Event*> TFunc_Instances_Stage_dispatchEvent;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_hasEventListener, bool, const ASString&> TFunc_Instances_Stage_hasEventListener;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_invalidate, Value> TFunc_Instances_Stage_invalidate;
typedef ThunkFunc0<Instances::Stage, Instances::Stage::mid_isFocusInaccessible, bool> TFunc_Instances_Stage_isFocusInaccessible;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_removeChildAt, Value, SInt32> TFunc_Instances_Stage_removeChildAt;
typedef ThunkFunc3<Instances::Stage, Instances::Stage::mid_removeEventListener, Value, const ASString&, const Value&, bool> TFunc_Instances_Stage_removeEventListener;
typedef ThunkFunc2<Instances::Stage, Instances::Stage::mid_setChildIndex, Value, Instances::DisplayObject*, SInt32> TFunc_Instances_Stage_setChildIndex;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_setOrientation, Value, const ASString&> TFunc_Instances_Stage_setOrientation;
typedef ThunkFunc2<Instances::Stage, Instances::Stage::mid_swapChildrenAt, Value, SInt32, SInt32> TFunc_Instances_Stage_swapChildrenAt;
typedef ThunkFunc1<Instances::Stage, Instances::Stage::mid_willTrigger, bool, const ASString&> TFunc_Instances_Stage_willTrigger;

template <> const TFunc_Instances_Stage_alignGet::TMethod TFunc_Instances_Stage_alignGet::Method = &Instances::Stage::alignGet;
template <> const TFunc_Instances_Stage_alignSet::TMethod TFunc_Instances_Stage_alignSet::Method = &Instances::Stage::alignSet;
template <> const TFunc_Instances_Stage_autoOrientsGet::TMethod TFunc_Instances_Stage_autoOrientsGet::Method = &Instances::Stage::autoOrientsGet;
template <> const TFunc_Instances_Stage_deviceOrientationGet::TMethod TFunc_Instances_Stage_deviceOrientationGet::Method = &Instances::Stage::deviceOrientationGet;
template <> const TFunc_Instances_Stage_displayStateGet::TMethod TFunc_Instances_Stage_displayStateGet::Method = &Instances::Stage::displayStateGet;
template <> const TFunc_Instances_Stage_displayStateSet::TMethod TFunc_Instances_Stage_displayStateSet::Method = &Instances::Stage::displayStateSet;
template <> const TFunc_Instances_Stage_focusGet::TMethod TFunc_Instances_Stage_focusGet::Method = &Instances::Stage::focusGet;
template <> const TFunc_Instances_Stage_focusSet::TMethod TFunc_Instances_Stage_focusSet::Method = &Instances::Stage::focusSet;
template <> const TFunc_Instances_Stage_frameRateGet::TMethod TFunc_Instances_Stage_frameRateGet::Method = &Instances::Stage::frameRateGet;
template <> const TFunc_Instances_Stage_frameRateSet::TMethod TFunc_Instances_Stage_frameRateSet::Method = &Instances::Stage::frameRateSet;
template <> const TFunc_Instances_Stage_fullScreenHeightGet::TMethod TFunc_Instances_Stage_fullScreenHeightGet::Method = &Instances::Stage::fullScreenHeightGet;
template <> const TFunc_Instances_Stage_fullScreenSourceRectGet::TMethod TFunc_Instances_Stage_fullScreenSourceRectGet::Method = &Instances::Stage::fullScreenSourceRectGet;
template <> const TFunc_Instances_Stage_fullScreenSourceRectSet::TMethod TFunc_Instances_Stage_fullScreenSourceRectSet::Method = &Instances::Stage::fullScreenSourceRectSet;
template <> const TFunc_Instances_Stage_fullScreenWidthGet::TMethod TFunc_Instances_Stage_fullScreenWidthGet::Method = &Instances::Stage::fullScreenWidthGet;
template <> const TFunc_Instances_Stage_heightGet::TMethod TFunc_Instances_Stage_heightGet::Method = &Instances::Stage::heightGet;
template <> const TFunc_Instances_Stage_heightSet::TMethod TFunc_Instances_Stage_heightSet::Method = &Instances::Stage::heightSet;
template <> const TFunc_Instances_Stage_mouseChildrenGet::TMethod TFunc_Instances_Stage_mouseChildrenGet::Method = &Instances::Stage::mouseChildrenGet;
template <> const TFunc_Instances_Stage_mouseChildrenSet::TMethod TFunc_Instances_Stage_mouseChildrenSet::Method = &Instances::Stage::mouseChildrenSet;
template <> const TFunc_Instances_Stage_nativeWindowGet::TMethod TFunc_Instances_Stage_nativeWindowGet::Method = &Instances::Stage::nativeWindowGet;
template <> const TFunc_Instances_Stage_numChildrenGet::TMethod TFunc_Instances_Stage_numChildrenGet::Method = &Instances::Stage::numChildrenGet;
template <> const TFunc_Instances_Stage_orientationGet::TMethod TFunc_Instances_Stage_orientationGet::Method = &Instances::Stage::orientationGet;
template <> const TFunc_Instances_Stage_qualityGet::TMethod TFunc_Instances_Stage_qualityGet::Method = &Instances::Stage::qualityGet;
template <> const TFunc_Instances_Stage_qualitySet::TMethod TFunc_Instances_Stage_qualitySet::Method = &Instances::Stage::qualitySet;
template <> const TFunc_Instances_Stage_scaleModeGet::TMethod TFunc_Instances_Stage_scaleModeGet::Method = &Instances::Stage::scaleModeGet;
template <> const TFunc_Instances_Stage_scaleModeSet::TMethod TFunc_Instances_Stage_scaleModeSet::Method = &Instances::Stage::scaleModeSet;
template <> const TFunc_Instances_Stage_showDefaultContextMenuGet::TMethod TFunc_Instances_Stage_showDefaultContextMenuGet::Method = &Instances::Stage::showDefaultContextMenuGet;
template <> const TFunc_Instances_Stage_showDefaultContextMenuSet::TMethod TFunc_Instances_Stage_showDefaultContextMenuSet::Method = &Instances::Stage::showDefaultContextMenuSet;
template <> const TFunc_Instances_Stage_stageFocusRectGet::TMethod TFunc_Instances_Stage_stageFocusRectGet::Method = &Instances::Stage::stageFocusRectGet;
template <> const TFunc_Instances_Stage_stageFocusRectSet::TMethod TFunc_Instances_Stage_stageFocusRectSet::Method = &Instances::Stage::stageFocusRectSet;
template <> const TFunc_Instances_Stage_stageHeightGet::TMethod TFunc_Instances_Stage_stageHeightGet::Method = &Instances::Stage::stageHeightGet;
template <> const TFunc_Instances_Stage_stageHeightSet::TMethod TFunc_Instances_Stage_stageHeightSet::Method = &Instances::Stage::stageHeightSet;
template <> const TFunc_Instances_Stage_stageWidthGet::TMethod TFunc_Instances_Stage_stageWidthGet::Method = &Instances::Stage::stageWidthGet;
template <> const TFunc_Instances_Stage_stageWidthSet::TMethod TFunc_Instances_Stage_stageWidthSet::Method = &Instances::Stage::stageWidthSet;
template <> const TFunc_Instances_Stage_tabChildrenGet::TMethod TFunc_Instances_Stage_tabChildrenGet::Method = &Instances::Stage::tabChildrenGet;
template <> const TFunc_Instances_Stage_tabChildrenSet::TMethod TFunc_Instances_Stage_tabChildrenSet::Method = &Instances::Stage::tabChildrenSet;
template <> const TFunc_Instances_Stage_textSnapshotGet::TMethod TFunc_Instances_Stage_textSnapshotGet::Method = &Instances::Stage::textSnapshotGet;
template <> const TFunc_Instances_Stage_widthGet::TMethod TFunc_Instances_Stage_widthGet::Method = &Instances::Stage::widthGet;
template <> const TFunc_Instances_Stage_widthSet::TMethod TFunc_Instances_Stage_widthSet::Method = &Instances::Stage::widthSet;
template <> const TFunc_Instances_Stage_addChild::TMethod TFunc_Instances_Stage_addChild::Method = &Instances::Stage::addChild;
template <> const TFunc_Instances_Stage_addChildAt::TMethod TFunc_Instances_Stage_addChildAt::Method = &Instances::Stage::addChildAt;
template <> const TFunc_Instances_Stage_addEventListener::TMethod TFunc_Instances_Stage_addEventListener::Method = &Instances::Stage::addEventListener;
template <> const TFunc_Instances_Stage_assignFocus::TMethod TFunc_Instances_Stage_assignFocus::Method = &Instances::Stage::assignFocus;
template <> const TFunc_Instances_Stage_dispatchEvent::TMethod TFunc_Instances_Stage_dispatchEvent::Method = &Instances::Stage::dispatchEvent;
template <> const TFunc_Instances_Stage_hasEventListener::TMethod TFunc_Instances_Stage_hasEventListener::Method = &Instances::Stage::hasEventListener;
template <> const TFunc_Instances_Stage_invalidate::TMethod TFunc_Instances_Stage_invalidate::Method = &Instances::Stage::invalidate;
template <> const TFunc_Instances_Stage_isFocusInaccessible::TMethod TFunc_Instances_Stage_isFocusInaccessible::Method = &Instances::Stage::isFocusInaccessible;
template <> const TFunc_Instances_Stage_removeChildAt::TMethod TFunc_Instances_Stage_removeChildAt::Method = &Instances::Stage::removeChildAt;
template <> const TFunc_Instances_Stage_removeEventListener::TMethod TFunc_Instances_Stage_removeEventListener::Method = &Instances::Stage::removeEventListener;
template <> const TFunc_Instances_Stage_setChildIndex::TMethod TFunc_Instances_Stage_setChildIndex::Method = &Instances::Stage::setChildIndex;
template <> const TFunc_Instances_Stage_setOrientation::TMethod TFunc_Instances_Stage_setOrientation::Method = &Instances::Stage::setOrientation;
template <> const TFunc_Instances_Stage_swapChildrenAt::TMethod TFunc_Instances_Stage_swapChildrenAt::Method = &Instances::Stage::swapChildrenAt;
template <> const TFunc_Instances_Stage_willTrigger::TMethod TFunc_Instances_Stage_willTrigger::Method = &Instances::Stage::willTrigger;

namespace Instances
{
    Stage::Stage(InstanceTraits::Traits& t)
    : Instances::DisplayObjectContainer(t)
//##protect##"instance::Stage::Stage()$data"
//##protect##"instance::Stage::Stage()$data"
    {
//##protect##"instance::Stage::Stage()$code"
//##protect##"instance::Stage::Stage()$code"
    }

    void Stage::alignGet(ASString& result)
    {
//##protect##"instance::Stage::alignGet()"
		const char* align; 
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		switch(asvm.GetMovieImpl()->GetViewAlignment())
		{
			case MovieImpl::Align_TopCenter:     align = "T"; break;
			case MovieImpl::Align_BottomCenter:  align = "B"; break;
			case MovieImpl::Align_CenterLeft:    align = "L"; break;
			case MovieImpl::Align_CenterRight:   align = "R"; break;
			case MovieImpl::Align_TopLeft:       align = "LT"; break; // documented as TL, but returns LT
			case MovieImpl::Align_TopRight:      align = "TR"; break;
			case MovieImpl::Align_BottomLeft:    align = "LB"; break; // documented as BL, but returns LB
			case MovieImpl::Align_BottomRight:   align = "RB"; break; // documented as BR, but returns RB
			default: align = "";
		}
		result += GetStringManager().CreateConstString(align); 
	
//##protect##"instance::Stage::alignGet()"
    }
    void Stage::alignSet(Value& result, const ASString& value)
    {
//##protect##"instance::Stage::alignSet()"
		ASString alignStr = value.ToUpper();
		MovieImpl::AlignType align;
		UInt32 char1 = 0, char2 = 0;
		int len = alignStr.GetLength();
		if (len >= 1)
		{
			char1 = alignStr.GetCharAt(0);
			if (len >= 2)
				char2 = alignStr.GetCharAt(1);
		}
		if ((char1 == 'T' && char2 == 'L') || (char1 == 'L' && char2 == 'T')) // TL or LT
			align = MovieImpl::Align_TopLeft;
		else if ((char1 == 'T' && char2 == 'R') || (char1 == 'R' && char2 == 'T')) // TR or RT
			align = MovieImpl::Align_TopRight;
		else if ((char1 == 'B' && char2 == 'L') || (char1 == 'L' && char2 == 'B')) // BL or LB
			align = MovieImpl::Align_BottomLeft;
		else if ((char1 == 'B' && char2 == 'R') || (char1 == 'R' && char2 == 'B')) // BR or RB
			align = MovieImpl::Align_BottomRight;
		else if (char1 == 'T')
			align = MovieImpl::Align_TopCenter;
		else if (char1 == 'B')
			align = MovieImpl::Align_BottomCenter;
		else if (char1 == 'L')
			align = MovieImpl::Align_CenterLeft;
		else if (char1 == 'R')
			align = MovieImpl::Align_CenterRight;
		else 
			align = MovieImpl::Align_Center;
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		asvm.GetMovieImpl()->SetViewAlignment(align);
        result.SetBool(true);
//##protect##"instance::Stage::alignSet()"
    }
    void Stage::autoOrientsGet(bool& result)
    {
//##protect##"instance::Stage::autoOrientsGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        result = asvm.GetMovieImpl()->DoesStageAutoOrients();
//##protect##"instance::Stage::autoOrientsGet()"
    }
    void Stage::deviceOrientationGet(ASString& result)
    {
//##protect##"instance::Stage::deviceOrientationGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        const char* no;
        switch(asvm.GetMovieImpl()->GetDeviceOrientation())
        {
        case OrientationEvent::Default:         no = "default"; break;
        case OrientationEvent::RotatedLeft:     no = "rotatedLeft"; break;
        case OrientationEvent::RotatedRight:    no = "rotatedRight"; break;
        case OrientationEvent::UpsideDown:      no = "upsideDown"; break;
        default: no = "unknown";
        }
        result = asvm.GetStringManager().CreateConstString(no);
//##protect##"instance::Stage::deviceOrientationGet()"
    }
    void Stage::displayStateGet(ASString& result)
    {
//##protect##"instance::Stage::displayStateGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::displayStateGet()");
//##protect##"instance::Stage::displayStateGet()"
    }
    void Stage::displayStateSet(Value& result, const ASString& value)
    {
//##protect##"instance::Stage::displayStateSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::displayStateSet()");
//##protect##"instance::Stage::displayStateSet()"
    }
    void Stage::focusGet(Value& result)
    {
//##protect##"instance::Stage::focusGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        // only controller 0 is supported for now @TODO
        Ptr<GFx::InteractiveObject> focused = asvm.GetMovieImpl()->GetFocusedCharacter(0);
        if (!focused)
            result.SetNull();
        else
            result = Value(ToAvmInteractiveObj(focused)->GetAS3Obj());
//##protect##"instance::Stage::focusGet()"
    }
    void Stage::focusSet(Value& result, Instances::InteractiveObject* value)
    {
//##protect##"instance::Stage::focusSet()"
        SF_UNUSED2(result, value);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        Ptr<GFx::InteractiveObject> newFocus;
        if (value)
            newFocus = value->GetIntObj();
        // only controller 0 is supported for now @TODO
        Ptr<GFx::InteractiveObject> focused = asvm.GetMovieImpl()->GetFocusedCharacter(0);
        if (focused != newFocus)
            asvm.GetMovieImpl()->SetKeyboardFocusTo(newFocus, 0, GFx_FocusMovedByAS);        
//##protect##"instance::Stage::focusSet()"
    }
    void Stage::frameRateGet(Value::Number& result)
    {
//##protect##"instance::Stage::frameRateGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        result = asvm.GetMovieImpl()->GetMovieDef()->GetFrameRate();

//##protect##"instance::Stage::frameRateGet()"
    }
    void Stage::frameRateSet(Value& result, Value::Number value)
    {
//##protect##"instance::Stage::frameRateSet()"

        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::frameRateSet()");
//##protect##"instance::Stage::frameRateSet()"
    }
    void Stage::fullScreenHeightGet(UInt32& result)
    {
//##protect##"instance::Stage::fullScreenHeightGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::fullScreenHeightGet()");
//##protect##"instance::Stage::fullScreenHeightGet()"
    }
    void Stage::fullScreenSourceRectGet(Value& result)
    {
//##protect##"instance::Stage::fullScreenSourceRectGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::fullScreenSourceRectGet()");
//##protect##"instance::Stage::fullScreenSourceRectGet()"
    }
    void Stage::fullScreenSourceRectSet(Value& result, Instances::Rectangle* value)
    {
//##protect##"instance::Stage::fullScreenSourceRectSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::fullScreenSourceRectSet()");
//##protect##"instance::Stage::fullScreenSourceRectSet()"
    }
    void Stage::fullScreenWidthGet(UInt32& result)
    {
//##protect##"instance::Stage::fullScreenWidthGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::fullScreenWidthGet()");
//##protect##"instance::Stage::fullScreenWidthGet()"
    }
    void Stage::heightGet(Value::Number& result)
    {
//##protect##"instance::Stage::heightGet()"
		AS3::Stage* as3stage = GetStageObj();
		RectF rect = as3stage->GetBounds(as3stage->GetMatrix());
		result = TwipsToPixels((Double)rect.Height());
//##protect##"instance::Stage::heightGet()"
    }
    void Stage::heightSet(Value& result, Value::Number value)
    {
//##protect##"instance::Stage::heightSet()"
		SF_UNUSED2(result, value);
		WARN_NOT_IMPLEMENTED("Stage::heightSet()");
//##protect##"instance::Stage::heightSet()"
    }
    void Stage::mouseChildrenGet(bool& result)
    {
//##protect##"instance::Stage::mouseChildrenGet()"
		DisplayObjectContainer::mouseChildrenGet(result);
//##protect##"instance::Stage::mouseChildrenGet()"
    }
    void Stage::mouseChildrenSet(Value& result, bool value)
    {
//##protect##"instance::Stage::mouseChildrenSet()"
		DisplayObjectContainer::mouseChildrenSet(result, value);
//##protect##"instance::Stage::mouseChildrenSet()"
    }
    void Stage::nativeWindowGet(Value& result)
    {
//##protect##"instance::Stage::nativeWindowGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::Stage::nativeWindowGet()");
//##protect##"instance::Stage::nativeWindowGet()"
    }
    void Stage::numChildrenGet(SInt32& result)
    {
//##protect##"instance::Stage::numChildrenGet()"
        DisplayObjectContainer::numChildrenGet(result);
//##protect##"instance::Stage::numChildrenGet()"
    }
    void Stage::orientationGet(ASString& result)
    {
//##protect##"instance::Stage::orientationGet()"
        SF_UNUSED1(result);
        AS3::Stage* as3stage = GetStageObj();
        result = as3stage->GetCurrentStageOrientation();
//##protect##"instance::Stage::orientationGet()"
    }
    void Stage::qualityGet(ASString& result)
    {
//##protect##"instance::Stage::qualityGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::qualityGet()");
//##protect##"instance::Stage::qualityGet()"
    }
    void Stage::qualitySet(Value& result, const ASString& value)
    {
//##protect##"instance::Stage::qualitySet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::qualitySet()");
//##protect##"instance::Stage::qualitySet()"
    }
    void Stage::scaleModeGet(ASString& result)
    {
//##protect##"instance::Stage::scaleModeGet()"
		const char* scaleMode; 
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		switch(asvm.GetMovieImpl()->GetViewScaleMode())
		{
		case MovieImpl::SM_NoScale:  scaleMode = "noScale"; break;
		case MovieImpl::SM_ExactFit: scaleMode = "exactFit"; break;
		case MovieImpl::SM_NoBorder: scaleMode = "noBorder"; break;
		default: scaleMode = "showAll";
		}
		result += GetStringManager().CreateConstString(scaleMode); 
	
//##protect##"instance::Stage::scaleModeGet()"
    }
    void Stage::scaleModeSet(Value& result, const ASString& value)
    {
//##protect##"instance::Stage::scaleModeSet()"
		ASString scaleModeStr = value;
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();

		MovieImpl::ScaleModeType scaleMode;
		
		if (!String::CompareNoCase(scaleModeStr.ToCStr(), "noScale"))
			scaleMode = MovieImpl::SM_NoScale;
		else if (!String::CompareNoCase(scaleModeStr.ToCStr(), "exactFit"))
			scaleMode = MovieImpl::SM_ExactFit;
		else if (!String::CompareNoCase(scaleModeStr.ToCStr(), "noBorder"))
			scaleMode = MovieImpl::SM_NoBorder;
		else
			scaleMode = MovieImpl::SM_ShowAll;
		if (pmovieImpl)
			pmovieImpl->SetViewScaleMode(scaleMode);
		result.SetUndefined();
	
//##protect##"instance::Stage::scaleModeSet()"
    }
    void Stage::showDefaultContextMenuGet(bool& result)
    {
//##protect##"instance::Stage::showDefaultContextMenuGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::showDefaultContextMenuGet()");
//##protect##"instance::Stage::showDefaultContextMenuGet()"
    }
    void Stage::showDefaultContextMenuSet(Value& result, bool value)
    {
//##protect##"instance::Stage::showDefaultContextMenuSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::showDefaultContextMenuSet()");
//##protect##"instance::Stage::showDefaultContextMenuSet()"
    }
    void Stage::stageFocusRectGet(bool& result)
    {
//##protect##"instance::Stage::stageFocusRectGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        result = GetStageObj()->IsFocusRectEnabled();
//##protect##"instance::Stage::stageFocusRectGet()"
    }
    void Stage::stageFocusRectSet(Value& result, bool value)
    {
//##protect##"instance::Stage::stageFocusRectSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        GetStageObj()->SetFocusRectFlag(value);
//##protect##"instance::Stage::stageFocusRectSet()"
    }
    void Stage::stageHeightGet(SInt32& result)
    {
//##protect##"instance::Stage::stageHeightGet()"
        ASVM& vm = static_cast<ASVM&>(GetVM());
        result = SInt32(vm.GetMovieImpl()->GetVisibleFrameRect().Height());
//##protect##"instance::Stage::stageHeightGet()"
    }
    void Stage::stageHeightSet(Value& result, SInt32 value)
    {
//##protect##"instance::Stage::stageHeightSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::stageHeightSet()");
//##protect##"instance::Stage::stageHeightSet()"
    }
    void Stage::stageWidthGet(SInt32& result)
    {
//##protect##"instance::Stage::stageWidthGet()"
        ASVM& vm = static_cast<ASVM&>(GetVM());
        result = SInt32(vm.GetMovieImpl()->GetVisibleFrameRect().Width());
//##protect##"instance::Stage::stageWidthGet()"
    }
    void Stage::stageWidthSet(Value& result, SInt32 value)
    {
//##protect##"instance::Stage::stageWidthSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::stageWidthSet()");
//##protect##"instance::Stage::stageWidthSet()"
    }
    void Stage::tabChildrenGet(bool& result)
    {
//##protect##"instance::Stage::tabChildrenGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::tabChildrenGet()");
//##protect##"instance::Stage::tabChildrenGet()"
    }
    void Stage::tabChildrenSet(Value& result, bool value)
    {
//##protect##"instance::Stage::tabChildrenSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("Stage::tabChildrenSet()");
//##protect##"instance::Stage::tabChildrenSet()"
    }
    void Stage::textSnapshotGet(Value& result)
    {
//##protect##"instance::Stage::textSnapshotGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::textSnapshotGet()");
//##protect##"instance::Stage::textSnapshotGet()"
    }
    void Stage::widthGet(Value::Number& result)
    {
//##protect##"instance::Stage::widthGet()"
		AS3::Stage* as3stage = GetStageObj();
		RectF rect = as3stage->GetBounds(as3stage->GetMatrix());
		result = TwipsToPixels((Double)rect.Width());
//##protect##"instance::Stage::widthGet()"
    }
    void Stage::widthSet(Value& result, Value::Number value)
    {
//##protect##"instance::Stage::widthSet()"
		SF_UNUSED2(result, value);
		WARN_NOT_IMPLEMENTED("Stage::widthSet()");
//##protect##"instance::Stage::widthSet()"
    }
    void Stage::addChild(Value& result, Instances::DisplayObject* child)
    {
//##protect##"instance::Stage::addChild()"
        DisplayObjectContainer::addChild(result, child);
//##protect##"instance::Stage::addChild()"
    }
    void Stage::addChildAt(Value& result, Instances::DisplayObject* child, SInt32 index)
    {
//##protect##"instance::Stage::addChildAt()"
        DisplayObjectContainer::addChildAt(result, child, index);
//##protect##"instance::Stage::addChildAt()"
    }
    void Stage::addEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture, SInt32 priority, bool useWeakReference)
    {
//##protect##"instance::Stage::addEventListener()"
        DisplayObjectContainer::addEventListener(result, type, listener, useCapture, priority, useWeakReference);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (type == vm.GetBuiltin(AS3Builtin_mouseCursorChange))
        {
            GetStageObj()->SetHasMouseCursorEventFlag();
        }
//##protect##"instance::Stage::addEventListener()"
    }
    void Stage::assignFocus(Value& result, Instances::InteractiveObject* objectToFocus, const ASString& direction)
    {
//##protect##"instance::Stage::assignFocus()"
        SF_UNUSED3(result, objectToFocus, direction);
        WARN_NOT_IMPLEMENTED("Stage::assignFocus()");
//##protect##"instance::Stage::assignFocus()"
    }
    void Stage::dispatchEvent(bool& result, Instances::Event* event)
    {
//##protect##"instance::Stage::dispatchEvent()"
        DisplayObjectContainer::dispatchEvent(result, event);
//##protect##"instance::Stage::dispatchEvent()"
    }
    void Stage::hasEventListener(bool& result, const ASString& type)
    {
//##protect##"instance::Stage::hasEventListener()"
        DisplayObjectContainer::hasEventListener(result, type);
//##protect##"instance::Stage::hasEventListener()"
    }
    void Stage::invalidate(Value& result)
    {
//##protect##"instance::Stage::invalidate()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.GetMovieRoot()->InvalidateStage();
//##protect##"instance::Stage::invalidate()"
    }
    void Stage::isFocusInaccessible(bool& result)
    {
//##protect##"instance::Stage::isFocusInaccessible()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("Stage::isFocusInaccessible()");
//##protect##"instance::Stage::isFocusInaccessible()"
    }
    void Stage::removeChildAt(Value& result, SInt32 index)
    {
//##protect##"instance::Stage::removeChildAt()"
        DisplayObjectContainer::removeChildAt(result, index);
//##protect##"instance::Stage::removeChildAt()"
    }
    void Stage::removeEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture)
    {
//##protect##"instance::Stage::removeEventListener()"
        SF_UNUSED4(result, type, listener, useCapture);
        DisplayObjectContainer::removeEventListener(result, type, listener, useCapture);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        if (type == vm.GetBuiltin(AS3Builtin_mouseCursorChange))
        {
            GetStageObj()->ClearHasMouseCursorEventFlag();
        }
//##protect##"instance::Stage::removeEventListener()"
    }
    void Stage::setChildIndex(Value& result, Instances::DisplayObject* child, SInt32 index)
    {
//##protect##"instance::Stage::setChildIndex()"
		DisplayObjectContainer::setChildIndex(result, child, index);
//##protect##"instance::Stage::setChildIndex()"
    }
    void Stage::setOrientation(Value& result, const ASString& newOrientation)
    {
//##protect##"instance::Stage::setOrientation()"
        SF_UNUSED2(result, newOrientation);
        AS3::Stage* as3stage = GetStageObj();
        as3stage->SetOrientation(newOrientation);
//##protect##"instance::Stage::setOrientation()"
    }
    void Stage::swapChildrenAt(Value& result, SInt32 index1, SInt32 index2)
    {
//##protect##"instance::Stage::swapChildrenAt()"
        DisplayObjectContainer::swapChildrenAt(result, index1, index2);
//##protect##"instance::Stage::swapChildrenAt()"
    }
    void Stage::willTrigger(bool& result, const ASString& type)
    {
//##protect##"instance::Stage::willTrigger()"
        DisplayObjectContainer::willTrigger(result, type);
//##protect##"instance::Stage::willTrigger()"
    }

//##protect##"instance$methods"
Stage::~Stage()
{

}

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Stage::ti[Stage::ThunkInfoNum] = {
        {TFunc_Instances_Stage_alignGet::Func, &StringCI, "align", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_alignSet::Func, NULL, "align", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_autoOrientsGet::Func, &BooleanCI, "autoOrients", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_deviceOrientationGet::Func, &StringCI, "deviceOrientation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_displayStateGet::Func, &StringCI, "displayState", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_displayStateSet::Func, NULL, "displayState", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_focusGet::Func, &InteractiveObjectCI, "focus", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_focusSet::Func, NULL, "focus", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_frameRateGet::Func, &NumberCI, "frameRate", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_frameRateSet::Func, NULL, "frameRate", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_fullScreenHeightGet::Func, &uintCI, "fullScreenHeight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_fullScreenSourceRectGet::Func, &RectangleCI, "fullScreenSourceRect", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_fullScreenSourceRectSet::Func, NULL, "fullScreenSourceRect", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_fullScreenWidthGet::Func, &uintCI, "fullScreenWidth", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_heightGet::Func, &NumberCI, "height", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_heightSet::Func, NULL, "height", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_mouseChildrenGet::Func, &BooleanCI, "mouseChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_mouseChildrenSet::Func, NULL, "mouseChildren", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_numChildrenGet::Func, &int_CI, "numChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_orientationGet::Func, &StringCI, "orientation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_qualityGet::Func, &StringCI, "quality", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_qualitySet::Func, NULL, "quality", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_scaleModeGet::Func, &StringCI, "scaleMode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_scaleModeSet::Func, NULL, "scaleMode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_showDefaultContextMenuGet::Func, &BooleanCI, "showDefaultContextMenu", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_showDefaultContextMenuSet::Func, NULL, "showDefaultContextMenu", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_stageFocusRectGet::Func, &BooleanCI, "stageFocusRect", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_stageFocusRectSet::Func, NULL, "stageFocusRect", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_stageHeightGet::Func, &int_CI, "stageHeight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_stageHeightSet::Func, NULL, "stageHeight", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_stageWidthGet::Func, &int_CI, "stageWidth", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_stageWidthSet::Func, NULL, "stageWidth", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_tabChildrenGet::Func, &BooleanCI, "tabChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_tabChildrenSet::Func, NULL, "tabChildren", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_textSnapshotGet::Func, &TextSnapshotCI, "textSnapshot", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_widthGet::Func, &NumberCI, "width", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Stage_widthSet::Func, NULL, "width", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Stage_addChild::Func, &DisplayObjectCI, "addChild", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_addChildAt::Func, &DisplayObjectCI, "addChildAt", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Stage_addEventListener::Func, NULL, "addEventListener", NULL, CT_Method, 2, 5},
        {TFunc_Instances_Stage_assignFocus::Func, NULL, "assignFocus", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Stage_dispatchEvent::Func, &BooleanCI, "dispatchEvent", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_hasEventListener::Func, &BooleanCI, "hasEventListener", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_invalidate::Func, NULL, "invalidate", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Stage_isFocusInaccessible::Func, &BooleanCI, "isFocusInaccessible", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Stage_removeChildAt::Func, &DisplayObjectCI, "removeChildAt", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_removeEventListener::Func, NULL, "removeEventListener", NULL, CT_Method, 2, 3},
        {TFunc_Instances_Stage_setChildIndex::Func, NULL, "setChildIndex", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Stage_setOrientation::Func, NULL, "setOrientation", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_swapChildrenAt::Func, NULL, "swapChildrenAt", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Stage_willTrigger::Func, &BooleanCI, "willTrigger", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Stage_addEventListener::Func, NULL, "addEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 5},
        {TFunc_Instances_Stage_dispatchEvent::Func, &BooleanCI, "dispatchEvent", "flash.events:IEventDispatcher", CT_Method, 1, 1},
        {TFunc_Instances_Stage_hasEventListener::Func, &BooleanCI, "hasEventListener", "flash.events:IEventDispatcher", CT_Method, 1, 1},
        {TFunc_Instances_Stage_removeEventListener::Func, NULL, "removeEventListener", "flash.events:IEventDispatcher", CT_Method, 2, 3},
        {TFunc_Instances_Stage_willTrigger::Func, &BooleanCI, "willTrigger", "flash.events:IEventDispatcher", CT_Method, 1, 1},
    };

    Stage::Stage(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Stage::Stage()"
        SetTraitsType(Traits_Stage);
//##protect##"InstanceTraits::Stage::Stage()"
        SetMemSize(sizeof(Instances::Stage));

    }

    Pickable<Instances::Stage> Stage::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Stage>(new(t.Alloc()) Instances::Stage(t));
    }

    void Stage::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    Stage::Stage(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Stage::Stage()"
//##protect##"class_::Stage::Stage()"
    }
    void Stage::supportsOrientationChangeGet(bool& result)
    {
//##protect##"class_::Stage::supportsOrientationChangeGet()"
        SF_UNUSED1(result);
        //ASVM& asvm = static_cast<ASVM&>(GetVM());
#if defined(SF_OS_ANDROID) || defined(SF_OS_IPHONE)
        result = true;
#else
        result = false;
#endif
//##protect##"class_::Stage::supportsOrientationChangeGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::Stage, Classes::Stage::mid_supportsOrientationChangeGet, bool> TFunc_Classes_Stage_supportsOrientationChangeGet;

template <> const TFunc_Classes_Stage_supportsOrientationChangeGet::TMethod TFunc_Classes_Stage_supportsOrientationChangeGet::Method = &Classes::Stage::supportsOrientationChangeGet;

namespace ClassTraits
{
    const ThunkInfo Stage::ti[Stage::ThunkInfoNum] = {
        {TFunc_Classes_Stage_supportsOrientationChangeGet::Func, &BooleanCI, "supportsOrientationChange", NULL, CT_Get, 0, 0},
    };
    Stage::Stage(VM& vm)
    : Traits(vm, StageCI)
    {
//##protect##"ClassTraits::Stage::Stage()"
        SetTraitsType(Traits_Stage);
//##protect##"ClassTraits::Stage::Stage()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Stage(vm, StageCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Stage(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Stage::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Stage(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StageCI = {
    ClassInfo::CompileTime,
    "Stage", "flash.display", &DisplayObjectContainerCI,
    ClassTraits::Stage::MakeClassTraits,
    ClassTraits::Stage::ThunkInfoNum,
    0,
    InstanceTraits::Stage::ThunkInfoNum,
    0,
    ClassTraits::Stage::ti,
    NULL,
    InstanceTraits::Stage::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

