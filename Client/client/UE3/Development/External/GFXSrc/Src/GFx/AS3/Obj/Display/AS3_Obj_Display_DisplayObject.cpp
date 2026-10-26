//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_DisplayObject.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_DisplayObject.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "AS3_Obj_Display_Loader.h"
#include "AS3_Obj_Display_DisplayObjectContainer.h"
#include "AS3_Obj_Display_Stage.h"
#include "AS3_Obj_Display_LoaderInfo.h"
#include "../Geom/AS3_Obj_Geom_Point.h"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "../Geom/AS3_Obj_Geom_Transform.h"
#include "../Geom/AS3_Obj_Geom_ColorTransform.h"
#include "../Geom/AS3_Obj_Geom_Vector3D.h"
#include "../Accessibility/AS3_Obj_Accessibility_AccessibilityProperties.h"
#include "GFx/AS3/AS3_AvmDisplayObjContainer.h"
#include "GFx/AS3/AS3_AvmStage.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "../Filters/AS3_Obj_Filters_BevelFilter.h"
#include "../Filters/AS3_Obj_Filters_BlurFilter.h"
#include "../Filters/AS3_Obj_Filters_ColorMatrixFilter.h"
#include "../Filters/AS3_Obj_Filters_DropShadowFilter.h"
#include "../Filters/AS3_Obj_Filters_GlowFilter.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_accessibilityPropertiesGet, Value> TFunc_Instances_DisplayObject_accessibilityPropertiesGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_accessibilityPropertiesSet, Value, Instances::AccessibilityProperties*> TFunc_Instances_DisplayObject_accessibilityPropertiesSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_alphaGet, Value::Number> TFunc_Instances_DisplayObject_alphaGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_alphaSet, Value, Value::Number> TFunc_Instances_DisplayObject_alphaSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_blendModeGet, ASString> TFunc_Instances_DisplayObject_blendModeGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_blendModeSet, Value, const ASString&> TFunc_Instances_DisplayObject_blendModeSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_cacheAsBitmapGet, bool> TFunc_Instances_DisplayObject_cacheAsBitmapGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_cacheAsBitmapSet, Value, bool> TFunc_Instances_DisplayObject_cacheAsBitmapSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_filtersGet, Value> TFunc_Instances_DisplayObject_filtersGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_filtersSet, Value, Instances::Array*> TFunc_Instances_DisplayObject_filtersSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_heightGet, Value::Number> TFunc_Instances_DisplayObject_heightGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_heightSet, Value, Value::Number> TFunc_Instances_DisplayObject_heightSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_loaderInfoGet, Value> TFunc_Instances_DisplayObject_loaderInfoGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_maskGet, Value> TFunc_Instances_DisplayObject_maskGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_maskSet, Value, Instances::DisplayObject*> TFunc_Instances_DisplayObject_maskSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_mouseXGet, Value::Number> TFunc_Instances_DisplayObject_mouseXGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_mouseYGet, Value::Number> TFunc_Instances_DisplayObject_mouseYGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_nameGet, Value> TFunc_Instances_DisplayObject_nameGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_nameSet, Value, const Value&> TFunc_Instances_DisplayObject_nameSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_opaqueBackgroundGet, Value> TFunc_Instances_DisplayObject_opaqueBackgroundGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_opaqueBackgroundSet, Value, const Value&> TFunc_Instances_DisplayObject_opaqueBackgroundSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_parentGet, Value> TFunc_Instances_DisplayObject_parentGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_rootGet, Value> TFunc_Instances_DisplayObject_rootGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_rotationGet, Value::Number> TFunc_Instances_DisplayObject_rotationGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_rotationSet, Value, Value::Number> TFunc_Instances_DisplayObject_rotationSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_rotationXGet, Value::Number> TFunc_Instances_DisplayObject_rotationXGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_rotationXSet, Value, Value::Number> TFunc_Instances_DisplayObject_rotationXSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_rotationYGet, Value::Number> TFunc_Instances_DisplayObject_rotationYGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_rotationYSet, Value, Value::Number> TFunc_Instances_DisplayObject_rotationYSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_rotationZGet, Value::Number> TFunc_Instances_DisplayObject_rotationZGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_rotationZSet, Value, Value::Number> TFunc_Instances_DisplayObject_rotationZSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_scale9GridGet, Value> TFunc_Instances_DisplayObject_scale9GridGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_scale9GridSet, Value, Instances::Rectangle*> TFunc_Instances_DisplayObject_scale9GridSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_scaleXGet, Value::Number> TFunc_Instances_DisplayObject_scaleXGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_scaleXSet, Value, Value::Number> TFunc_Instances_DisplayObject_scaleXSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_scaleYGet, Value::Number> TFunc_Instances_DisplayObject_scaleYGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_scaleYSet, Value, Value::Number> TFunc_Instances_DisplayObject_scaleYSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_scaleZGet, Value::Number> TFunc_Instances_DisplayObject_scaleZGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_scaleZSet, Value, Value::Number> TFunc_Instances_DisplayObject_scaleZSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_scrollRectGet, Value> TFunc_Instances_DisplayObject_scrollRectGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_scrollRectSet, Value, Instances::Rectangle*> TFunc_Instances_DisplayObject_scrollRectSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_stageGet, Value> TFunc_Instances_DisplayObject_stageGet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_transformGet, Value> TFunc_Instances_DisplayObject_transformGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_transformSet, Value, Instances::Transform*> TFunc_Instances_DisplayObject_transformSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_visibleGet, bool> TFunc_Instances_DisplayObject_visibleGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_visibleSet, Value, bool> TFunc_Instances_DisplayObject_visibleSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_widthGet, Value::Number> TFunc_Instances_DisplayObject_widthGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_widthSet, Value, Value::Number> TFunc_Instances_DisplayObject_widthSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_xGet, Value::Number> TFunc_Instances_DisplayObject_xGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_xSet, Value, Value::Number> TFunc_Instances_DisplayObject_xSet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_yGet, Value::Number> TFunc_Instances_DisplayObject_yGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_ySet, Value, Value::Number> TFunc_Instances_DisplayObject_ySet;
typedef ThunkFunc0<Instances::DisplayObject, Instances::DisplayObject::mid_zGet, Value::Number> TFunc_Instances_DisplayObject_zGet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_zSet, Value, Value::Number> TFunc_Instances_DisplayObject_zSet;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_getBounds, Value, Instances::DisplayObject*> TFunc_Instances_DisplayObject_getBounds;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_getRect, Value, Instances::DisplayObject*> TFunc_Instances_DisplayObject_getRect;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_globalToLocal, Value, Instances::Point*> TFunc_Instances_DisplayObject_globalToLocal;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_globalToLocal3D, Value, Instances::Point*> TFunc_Instances_DisplayObject_globalToLocal3D;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_hitTestObject, bool, Instances::DisplayObject*> TFunc_Instances_DisplayObject_hitTestObject;
typedef ThunkFunc3<Instances::DisplayObject, Instances::DisplayObject::mid_hitTestPoint, bool, Value::Number, Value::Number, bool> TFunc_Instances_DisplayObject_hitTestPoint;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_localToGlobal, Value, Instances::Point*> TFunc_Instances_DisplayObject_localToGlobal;
typedef ThunkFunc1<Instances::DisplayObject, Instances::DisplayObject::mid_local3DToGlobal, Value, Instances::Vector3D*> TFunc_Instances_DisplayObject_local3DToGlobal;

template <> const TFunc_Instances_DisplayObject_accessibilityPropertiesGet::TMethod TFunc_Instances_DisplayObject_accessibilityPropertiesGet::Method = &Instances::DisplayObject::accessibilityPropertiesGet;
template <> const TFunc_Instances_DisplayObject_accessibilityPropertiesSet::TMethod TFunc_Instances_DisplayObject_accessibilityPropertiesSet::Method = &Instances::DisplayObject::accessibilityPropertiesSet;
template <> const TFunc_Instances_DisplayObject_alphaGet::TMethod TFunc_Instances_DisplayObject_alphaGet::Method = &Instances::DisplayObject::alphaGet;
template <> const TFunc_Instances_DisplayObject_alphaSet::TMethod TFunc_Instances_DisplayObject_alphaSet::Method = &Instances::DisplayObject::alphaSet;
template <> const TFunc_Instances_DisplayObject_blendModeGet::TMethod TFunc_Instances_DisplayObject_blendModeGet::Method = &Instances::DisplayObject::blendModeGet;
template <> const TFunc_Instances_DisplayObject_blendModeSet::TMethod TFunc_Instances_DisplayObject_blendModeSet::Method = &Instances::DisplayObject::blendModeSet;
template <> const TFunc_Instances_DisplayObject_cacheAsBitmapGet::TMethod TFunc_Instances_DisplayObject_cacheAsBitmapGet::Method = &Instances::DisplayObject::cacheAsBitmapGet;
template <> const TFunc_Instances_DisplayObject_cacheAsBitmapSet::TMethod TFunc_Instances_DisplayObject_cacheAsBitmapSet::Method = &Instances::DisplayObject::cacheAsBitmapSet;
template <> const TFunc_Instances_DisplayObject_filtersGet::TMethod TFunc_Instances_DisplayObject_filtersGet::Method = &Instances::DisplayObject::filtersGet;
template <> const TFunc_Instances_DisplayObject_filtersSet::TMethod TFunc_Instances_DisplayObject_filtersSet::Method = &Instances::DisplayObject::filtersSet;
template <> const TFunc_Instances_DisplayObject_heightGet::TMethod TFunc_Instances_DisplayObject_heightGet::Method = &Instances::DisplayObject::heightGet;
template <> const TFunc_Instances_DisplayObject_heightSet::TMethod TFunc_Instances_DisplayObject_heightSet::Method = &Instances::DisplayObject::heightSet;
template <> const TFunc_Instances_DisplayObject_loaderInfoGet::TMethod TFunc_Instances_DisplayObject_loaderInfoGet::Method = &Instances::DisplayObject::loaderInfoGet;
template <> const TFunc_Instances_DisplayObject_maskGet::TMethod TFunc_Instances_DisplayObject_maskGet::Method = &Instances::DisplayObject::maskGet;
template <> const TFunc_Instances_DisplayObject_maskSet::TMethod TFunc_Instances_DisplayObject_maskSet::Method = &Instances::DisplayObject::maskSet;
template <> const TFunc_Instances_DisplayObject_mouseXGet::TMethod TFunc_Instances_DisplayObject_mouseXGet::Method = &Instances::DisplayObject::mouseXGet;
template <> const TFunc_Instances_DisplayObject_mouseYGet::TMethod TFunc_Instances_DisplayObject_mouseYGet::Method = &Instances::DisplayObject::mouseYGet;
template <> const TFunc_Instances_DisplayObject_nameGet::TMethod TFunc_Instances_DisplayObject_nameGet::Method = &Instances::DisplayObject::nameGet;
template <> const TFunc_Instances_DisplayObject_nameSet::TMethod TFunc_Instances_DisplayObject_nameSet::Method = &Instances::DisplayObject::nameSet;
template <> const TFunc_Instances_DisplayObject_opaqueBackgroundGet::TMethod TFunc_Instances_DisplayObject_opaqueBackgroundGet::Method = &Instances::DisplayObject::opaqueBackgroundGet;
template <> const TFunc_Instances_DisplayObject_opaqueBackgroundSet::TMethod TFunc_Instances_DisplayObject_opaqueBackgroundSet::Method = &Instances::DisplayObject::opaqueBackgroundSet;
template <> const TFunc_Instances_DisplayObject_parentGet::TMethod TFunc_Instances_DisplayObject_parentGet::Method = &Instances::DisplayObject::parentGet;
template <> const TFunc_Instances_DisplayObject_rootGet::TMethod TFunc_Instances_DisplayObject_rootGet::Method = &Instances::DisplayObject::rootGet;
template <> const TFunc_Instances_DisplayObject_rotationGet::TMethod TFunc_Instances_DisplayObject_rotationGet::Method = &Instances::DisplayObject::rotationGet;
template <> const TFunc_Instances_DisplayObject_rotationSet::TMethod TFunc_Instances_DisplayObject_rotationSet::Method = &Instances::DisplayObject::rotationSet;
template <> const TFunc_Instances_DisplayObject_rotationXGet::TMethod TFunc_Instances_DisplayObject_rotationXGet::Method = &Instances::DisplayObject::rotationXGet;
template <> const TFunc_Instances_DisplayObject_rotationXSet::TMethod TFunc_Instances_DisplayObject_rotationXSet::Method = &Instances::DisplayObject::rotationXSet;
template <> const TFunc_Instances_DisplayObject_rotationYGet::TMethod TFunc_Instances_DisplayObject_rotationYGet::Method = &Instances::DisplayObject::rotationYGet;
template <> const TFunc_Instances_DisplayObject_rotationYSet::TMethod TFunc_Instances_DisplayObject_rotationYSet::Method = &Instances::DisplayObject::rotationYSet;
template <> const TFunc_Instances_DisplayObject_rotationZGet::TMethod TFunc_Instances_DisplayObject_rotationZGet::Method = &Instances::DisplayObject::rotationZGet;
template <> const TFunc_Instances_DisplayObject_rotationZSet::TMethod TFunc_Instances_DisplayObject_rotationZSet::Method = &Instances::DisplayObject::rotationZSet;
template <> const TFunc_Instances_DisplayObject_scale9GridGet::TMethod TFunc_Instances_DisplayObject_scale9GridGet::Method = &Instances::DisplayObject::scale9GridGet;
template <> const TFunc_Instances_DisplayObject_scale9GridSet::TMethod TFunc_Instances_DisplayObject_scale9GridSet::Method = &Instances::DisplayObject::scale9GridSet;
template <> const TFunc_Instances_DisplayObject_scaleXGet::TMethod TFunc_Instances_DisplayObject_scaleXGet::Method = &Instances::DisplayObject::scaleXGet;
template <> const TFunc_Instances_DisplayObject_scaleXSet::TMethod TFunc_Instances_DisplayObject_scaleXSet::Method = &Instances::DisplayObject::scaleXSet;
template <> const TFunc_Instances_DisplayObject_scaleYGet::TMethod TFunc_Instances_DisplayObject_scaleYGet::Method = &Instances::DisplayObject::scaleYGet;
template <> const TFunc_Instances_DisplayObject_scaleYSet::TMethod TFunc_Instances_DisplayObject_scaleYSet::Method = &Instances::DisplayObject::scaleYSet;
template <> const TFunc_Instances_DisplayObject_scaleZGet::TMethod TFunc_Instances_DisplayObject_scaleZGet::Method = &Instances::DisplayObject::scaleZGet;
template <> const TFunc_Instances_DisplayObject_scaleZSet::TMethod TFunc_Instances_DisplayObject_scaleZSet::Method = &Instances::DisplayObject::scaleZSet;
template <> const TFunc_Instances_DisplayObject_scrollRectGet::TMethod TFunc_Instances_DisplayObject_scrollRectGet::Method = &Instances::DisplayObject::scrollRectGet;
template <> const TFunc_Instances_DisplayObject_scrollRectSet::TMethod TFunc_Instances_DisplayObject_scrollRectSet::Method = &Instances::DisplayObject::scrollRectSet;
template <> const TFunc_Instances_DisplayObject_stageGet::TMethod TFunc_Instances_DisplayObject_stageGet::Method = &Instances::DisplayObject::stageGet;
template <> const TFunc_Instances_DisplayObject_transformGet::TMethod TFunc_Instances_DisplayObject_transformGet::Method = &Instances::DisplayObject::transformGet;
template <> const TFunc_Instances_DisplayObject_transformSet::TMethod TFunc_Instances_DisplayObject_transformSet::Method = &Instances::DisplayObject::transformSet;
template <> const TFunc_Instances_DisplayObject_visibleGet::TMethod TFunc_Instances_DisplayObject_visibleGet::Method = &Instances::DisplayObject::visibleGet;
template <> const TFunc_Instances_DisplayObject_visibleSet::TMethod TFunc_Instances_DisplayObject_visibleSet::Method = &Instances::DisplayObject::visibleSet;
template <> const TFunc_Instances_DisplayObject_widthGet::TMethod TFunc_Instances_DisplayObject_widthGet::Method = &Instances::DisplayObject::widthGet;
template <> const TFunc_Instances_DisplayObject_widthSet::TMethod TFunc_Instances_DisplayObject_widthSet::Method = &Instances::DisplayObject::widthSet;
template <> const TFunc_Instances_DisplayObject_xGet::TMethod TFunc_Instances_DisplayObject_xGet::Method = &Instances::DisplayObject::xGet;
template <> const TFunc_Instances_DisplayObject_xSet::TMethod TFunc_Instances_DisplayObject_xSet::Method = &Instances::DisplayObject::xSet;
template <> const TFunc_Instances_DisplayObject_yGet::TMethod TFunc_Instances_DisplayObject_yGet::Method = &Instances::DisplayObject::yGet;
template <> const TFunc_Instances_DisplayObject_ySet::TMethod TFunc_Instances_DisplayObject_ySet::Method = &Instances::DisplayObject::ySet;
template <> const TFunc_Instances_DisplayObject_zGet::TMethod TFunc_Instances_DisplayObject_zGet::Method = &Instances::DisplayObject::zGet;
template <> const TFunc_Instances_DisplayObject_zSet::TMethod TFunc_Instances_DisplayObject_zSet::Method = &Instances::DisplayObject::zSet;
template <> const TFunc_Instances_DisplayObject_getBounds::TMethod TFunc_Instances_DisplayObject_getBounds::Method = &Instances::DisplayObject::getBounds;
template <> const TFunc_Instances_DisplayObject_getRect::TMethod TFunc_Instances_DisplayObject_getRect::Method = &Instances::DisplayObject::getRect;
template <> const TFunc_Instances_DisplayObject_globalToLocal::TMethod TFunc_Instances_DisplayObject_globalToLocal::Method = &Instances::DisplayObject::globalToLocal;
template <> const TFunc_Instances_DisplayObject_globalToLocal3D::TMethod TFunc_Instances_DisplayObject_globalToLocal3D::Method = &Instances::DisplayObject::globalToLocal3D;
template <> const TFunc_Instances_DisplayObject_hitTestObject::TMethod TFunc_Instances_DisplayObject_hitTestObject::Method = &Instances::DisplayObject::hitTestObject;
template <> const TFunc_Instances_DisplayObject_hitTestPoint::TMethod TFunc_Instances_DisplayObject_hitTestPoint::Method = &Instances::DisplayObject::hitTestPoint;
template <> const TFunc_Instances_DisplayObject_localToGlobal::TMethod TFunc_Instances_DisplayObject_localToGlobal::Method = &Instances::DisplayObject::localToGlobal;
template <> const TFunc_Instances_DisplayObject_local3DToGlobal::TMethod TFunc_Instances_DisplayObject_local3DToGlobal::Method = &Instances::DisplayObject::local3DToGlobal;

namespace Instances
{
    DisplayObject::DisplayObject(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::DisplayObject::DisplayObject()$data"
    , pDispObj(NULL)
//##protect##"instance::DisplayObject::DisplayObject()$data"
    {
//##protect##"instance::DisplayObject::DisplayObject()$code"
        pReleaseProxy = *SF_HEAP_AUTO_NEW(this) ReleaseProxy();
//##protect##"instance::DisplayObject::DisplayObject()$code"
    }

    void DisplayObject::accessibilityPropertiesGet(Value& result)
    {
//##protect##"instance::DisplayObject::accessibilityPropertiesGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::DisplayObject::accessibilityPropertiesGet()");
//##protect##"instance::DisplayObject::accessibilityPropertiesGet()"
    }
    void DisplayObject::accessibilityPropertiesSet(Value& result, Instances::AccessibilityProperties* value)
    {
//##protect##"instance::DisplayObject::accessibilityPropertiesSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::DisplayObject::accessibilityPropertiesSet()");
//##protect##"instance::DisplayObject::accessibilityPropertiesSet()"
    }
    void DisplayObject::alphaGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::alphaGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetAlpha()/100;
//##protect##"instance::DisplayObject::alphaGet()"
    }
    void DisplayObject::alphaSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::alphaSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        pDispObj->SetAlpha(value * 100);        
//##protect##"instance::DisplayObject::alphaSet()"
    }
    void DisplayObject::blendModeGet(ASString& result)
    {
//##protect##"instance::DisplayObject::blendModeGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        GFx::DisplayObjectBase::BlendType bm = pDispObj->GetBlendMode();
        switch (bm)
        {
        case Render::Blend_None:
        case Render::Blend_Normal:
            result = GetVM().GetStringManager().CreateConstString("normal");
            break;
        case Render::Blend_Layer:         
            result = GetVM().GetStringManager().CreateConstString("layer");
            break;
        case Render::Blend_Multiply:
            result = GetVM().GetStringManager().CreateConstString("multiply");
            break;
        case Render::Blend_Screen:        
            result = GetVM().GetStringManager().CreateConstString("screen");
            break;
        case Render::Blend_Lighten:       
            result = GetVM().GetStringManager().CreateConstString("lighten");
            break;
        case Render::Blend_Darken:        
            result = GetVM().GetStringManager().CreateConstString("darken");
            break;
        case Render::Blend_Difference:    
            result = GetVM().GetStringManager().CreateConstString("difference");
            break;
        case Render::Blend_Add:           
            result = GetVM().GetStringManager().CreateConstString("add");
            break;
        case Render::Blend_Subtract:      
            result = GetVM().GetStringManager().CreateConstString("subtract");
            break;
        case Render::Blend_Invert:        
            result = GetVM().GetStringManager().CreateConstString("invert");
            break;
        case Render::Blend_Alpha:         
            result = GetVM().GetStringManager().CreateConstString("alpha");
            break;
        case Render::Blend_Erase:         
            result = GetVM().GetStringManager().CreateConstString("erase");
            break;
        case Render::Blend_Overlay:       
            result = GetVM().GetStringManager().CreateConstString("overlay");
            break;
        case Render::Blend_HardLight:
            result = GetVM().GetStringManager().CreateConstString("hardlight");
            break;
        default: SF_ASSERT(0); // unknown
        }
//##protect##"instance::DisplayObject::blendModeGet()"
    }
    void DisplayObject::blendModeSet(Value& result, const ASString& value)
    {
//##protect##"instance::DisplayObject::blendModeSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);

        Render::BlendMode blend = Render::Blend_None;
        if (value == "normal")
            blend = Render::Blend_Normal;
        else if (value == "add")
            blend = Render::Blend_Add;
        else if (value == "alpha")
            blend = Render::Blend_Alpha;
        else if (value == "multiply")
            blend = Render::Blend_Multiply;
        else if (value == "subtract")
            blend = Render::Blend_Subtract;
        else if (value == "layer")
            blend = Render::Blend_Layer;
        else if (value == "screen")
            blend = Render::Blend_Screen;
        else if (value == "lighten")
            blend = Render::Blend_Lighten;
        else if (value == "darken")
            blend = Render::Blend_Darken;
        else if (value == "difference")
            blend = Render::Blend_Difference;
        else if (value == "invert")
            blend = Render::Blend_Invert;
        else if (value == "erase")
            blend = Render::Blend_Erase;
        else if (value == "overlay")
            blend = Render::Blend_Overlay;
        else if (value == "hardlight")
            blend = Render::Blend_HardLight;
        pDispObj->SetBlendMode(blend);
//##protect##"instance::DisplayObject::blendModeSet()"
    }
    void DisplayObject::cacheAsBitmapGet(bool& result)
    {
//##protect##"instance::DisplayObject::cacheAsBitmapGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("DisplayObject::cacheAsBitmapGet()");
//##protect##"instance::DisplayObject::cacheAsBitmapGet()"
    }
    void DisplayObject::cacheAsBitmapSet(Value& result, bool value)
    {
//##protect##"instance::DisplayObject::cacheAsBitmapSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("DisplayObject::cacheAsBitmapSet()");
//##protect##"instance::DisplayObject::cacheAsBitmapSet()"
    }
    void DisplayObject::filtersGet(Value& result)
    {
//##protect##"instance::DisplayObject::filtersGet()"
        Pickable<Instances::Array> array = GetVM().MakeArray();
        const FilterSet* filters = pDispObj->GetFilters();
        if ( !filters || filters->GetFilterCount() == 0 )
        {
            result = array;
            return;
        }
        for (unsigned i = 0; i < filters->GetFilterCount(); ++i )
        {
            const Filter* filter = filters->GetFilter(i);
            SPtr<BitmapFilter> as3filter;
            const char* className = 0;
            switch( filter->GetFilterType() )
            {
                case Render::Filter_Blur:           className = "flash.filters.BlurFilter"; break;
                case Render::Filter_Shadow:         className = "flash.filters.DropShadowFilter"; break;
                case Render::Filter_Glow:           className = "flash.filters.GlowFilter"; break;
                case Render::Filter_Bevel:          className = "flash.filters.BevelFilter"; break;
                case Render::Filter_ColorMatrix:    className = "flash.filters.ColorMatrixFilter"; break;
                default:
                    array->PushBack(0);
                    continue;
            }
            if (GetVM().ConstructBuiltinObject(as3filter, className ))
            {
                as3filter->SetFilterData(filter->Clone());
                array->PushBack(Value(as3filter));
            }
        }
        result = array;
//##protect##"instance::DisplayObject::filtersGet()"
    }
    void DisplayObject::filtersSet(Value& result, Instances::Array* value)
    {
//##protect##"instance::DisplayObject::filtersSet()"
        SF_UNUSED2(result, value);
        Ptr<FilterSet> filters = *SF_NEW FilterSet();

        if (value)
        {
            for ( UPInt i =0; i < value->GetSize(); i++ )
            {
                const Value& fv = value->At(i);
                ASString className = fv.GetObject()->GetTraits().GetName();
                if ( className == "GlowFilter")
                {
                    Instances::GlowFilter* filter = (Instances::GlowFilter*)fv.GetObject();
                    Ptr<Render::GlowFilter> data = *(Render::GlowFilter*)filter->GetFilterData()->Clone(GetVM().GetMemoryHeap());
                    filters->AddFilter(data);
                }
                else if ( className == "BevelFilter")
                {
                    Instances::BevelFilter* filter = (Instances::BevelFilter*)fv.GetObject();
                    Ptr<Render::BevelFilter> data = *(Render::BevelFilter*)filter->GetFilterData()->Clone(GetVM().GetMemoryHeap());
                    filters->AddFilter(data);
                }
                else if ( className == "DropShadowFilter")
                {
                    Instances::DropShadowFilter* filter = (Instances::DropShadowFilter*)fv.GetObject();
                    Ptr<Render::ShadowFilter> data = *(Render::ShadowFilter*)filter->GetFilterData()->Clone(GetVM().GetMemoryHeap());
                    filters->AddFilter(data);
                }
                else if ( className == "BlurFilter")
                {
                    Instances::BlurFilter* filter = (Instances::BlurFilter*)fv.GetObject();
                    Ptr<Render::BlurFilter> data = *(Render::BlurFilter*)filter->GetFilterData()->Clone(GetVM().GetMemoryHeap());
                    filters->AddFilter(data);
                }
                else if ( className == "ColorMatrixFilter")
                {
                    Instances::ColorMatrixFilter* filter = (Instances::ColorMatrixFilter*)fv.GetObject();
                    Ptr<Render::ColorMatrixFilter> data = *(Render::ColorMatrixFilter*)filter->GetFilterData()->Clone(GetVM().GetMemoryHeap());
                    filters->AddFilter(data);
                }
            }
        }

        pDispObj->SetFilters(filters);
//##protect##"instance::DisplayObject::filtersSet()"
    }
    void DisplayObject::heightGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::heightGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetHeight();
//##protect##"instance::DisplayObject::heightGet()"
    }
    void DisplayObject::heightSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::heightSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        pDispObj->SetHeight(value);
//##protect##"instance::DisplayObject::heightSet()"
    }
    void DisplayObject::loaderInfoGet(Value& result)
    {
//##protect##"instance::DisplayObject::loaderInfoGet()"
        SF_UNUSED1(result);
        if (pDispObj->IsTimelineObjectFlagSet())
        {
            AvmDisplayObj* prootContainer = ToAvmDisplayObj(ToAvmDisplayObj(pDispObj)->GetRoot());
            SF_ASSERT(prootContainer && prootContainer->GetAS3Obj());
            result = prootContainer->GetAS3Obj()->pLoaderInfo;
        }
        else
            result = pLoaderInfo;
//##protect##"instance::DisplayObject::loaderInfoGet()"
    }
    void DisplayObject::maskGet(Value& result)
    {
//##protect##"instance::DisplayObject::maskGet()"
        SF_UNUSED1(result);
        result.SetNull();
        if (pDispObj)
        {
            if (pDispObj->GetMask())
            {
                result = ToAvmDisplayObj(pDispObj->GetMask())->GetAS3Obj();
                SF_ASSERT(!result.IsNull()); // AS3 obj is not created? Should be!
            }
        }
//##protect##"instance::DisplayObject::maskGet()"
    }
    void DisplayObject::maskSet(Value& result, Instances::DisplayObject* value)
    {
//##protect##"instance::DisplayObject::maskSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        if (!value)
        {
            // remove mask
            pDispObj->SetMask(NULL);
        }
        else
        {
            if (!value->pDispObj) value->CreateStageObject();
            SF_ASSERT(value->pDispObj);
            pDispObj->SetMask(value->pDispObj);
        }
//##protect##"instance::DisplayObject::maskSet()"
    }
    void DisplayObject::mouseXGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::mouseXGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetMouseX();
//##protect##"instance::DisplayObject::mouseXGet()"
    }
    void DisplayObject::mouseYGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::mouseYGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetMouseY();
//##protect##"instance::DisplayObject::mouseYGet()"
    }
    void DisplayObject::nameGet(Value& result)
    {
//##protect##"instance::DisplayObject::nameGet()"
        SF_ASSERT(pDispObj);
        const ASString& n = pDispObj->GetName();
        if (n.IsEmpty() && pDispObj->IsInstanceBasedNameFlagSet())
            result.SetNull();
        else
            result = n;
//##protect##"instance::DisplayObject::nameGet()"
    }
    void DisplayObject::nameSet(Value& result, const Value& value)
    {
//##protect##"instance::DisplayObject::nameSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        if (pDispObj->IsTimelineObjectFlagSet())
            GetVM().ThrowTypeError(VM::Error(VM::eConstWriteError, GetVM()
                SF_DEBUG_ARG("name")
                SF_DEBUG_ARG("Timeline")
                ));
        else
        {
            ASString n(GetVM().GetStringManager().CreateEmptyString());
            value.Convert2String(n).DoNotCheck();
            pDispObj->SetName(n);
            pDispObj->ClearInstanceBasedNameFlag();
        }
//##protect##"instance::DisplayObject::nameSet()"
    }
    void DisplayObject::opaqueBackgroundGet(Value& result)
    {
//##protect##"instance::DisplayObject::opaqueBackgroundGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("DisplayObject::opaqueBackgroundGet()");
//##protect##"instance::DisplayObject::opaqueBackgroundGet()"
    }
    void DisplayObject::opaqueBackgroundSet(Value& result, const Value& value)
    {
//##protect##"instance::DisplayObject::opaqueBackgroundSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("DisplayObject::opaqueBackgroundSet()");
//##protect##"instance::DisplayObject::opaqueBackgroundSet()"
    }
    void DisplayObject::parentGet(Value& result)
    {
//##protect##"instance::DisplayObject::parentGet()"
        SF_ASSERT(pDispObj);
        GFx::InteractiveObject* pparent = pDispObj->GetParent();
        if (pparent)
        {
            AvmInteractiveObj* pcontObj = ToAvmInteractiveObj(pparent);

            // We can't create AS instance here since this may break the order of ctors' 
            // execution. Is 'null' result acceptable? (AB)
            //pcontObj->CreateASInstance(true);
            //SF_ASSERT(pcontObj->GetAS3Obj());

            result = pcontObj->GetAS3Obj();
        }
        else
            result.SetNull();
//##protect##"instance::DisplayObject::parentGet()"
    }
    void DisplayObject::rootGet(Value& result)
    {
//##protect##"instance::DisplayObject::rootGet()"
        SF_ASSERT(pDispObj);
        AvmDisplayObj* pcontObj = ToAvmDisplayObj(ToAvmDisplayObj(pDispObj)->GetRoot());

        pcontObj->CreateASInstance(true);
        result = pcontObj->GetAS3Obj();
//##protect##"instance::DisplayObject::rootGet()"
    }
    void DisplayObject::rotationGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::rotationGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetRotation();
//##protect##"instance::DisplayObject::rotationGet()"
    }
    void DisplayObject::rotationSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::rotationSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetRotation(value);
//##protect##"instance::DisplayObject::rotationSet()"
    }
    void DisplayObject::rotationXGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::rotationXGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetXRotation();
//##protect##"instance::DisplayObject::rotationXGet()"
    }
    void DisplayObject::rotationXSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::rotationXSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetXRotation(value);
//##protect##"instance::DisplayObject::rotationXSet()"
    }
    void DisplayObject::rotationYGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::rotationYGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetYRotation();
//##protect##"instance::DisplayObject::rotationYGet()"
    }
    void DisplayObject::rotationYSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::rotationYSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetYRotation(value);
//##protect##"instance::DisplayObject::rotationYSet()"
    }
    void DisplayObject::rotationZGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::rotationZGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetRotation();
//##protect##"instance::DisplayObject::rotationZGet()"
    }
    void DisplayObject::rotationZSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::rotationZSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetRotation(value);
//##protect##"instance::DisplayObject::rotationZSet()"
    }
    void DisplayObject::scale9GridGet(Value& result)
    {
//##protect##"instance::DisplayObject::scale9GridGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        
        if (pDispObj->HasScale9Grid())
        {
            RectF s9g = pDispObj->GetScale9Grid();
            // create Rectangle object
            Value params[] = { Value(TwipsToPixels(s9g.x1)), 
                               Value(TwipsToPixels(s9g.y1)), 
                               Value(TwipsToPixels(s9g.Width())), 
                               Value(TwipsToPixels(s9g.Height())) 
            };
            static_cast<ASVM&>(GetVM()).RectangleClass->Construct(result, 4, params, true);
        }
        else
        {
            result.SetNull();
        }
//##protect##"instance::DisplayObject::scale9GridGet()"
    }
    void DisplayObject::scale9GridSet(Value& result, Instances::Rectangle* value)
    {
//##protect##"instance::DisplayObject::scale9GridSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);

        if (value)
        {
            RectF sg;
            sg.x1 = PixelsToTwips(float(value->GetX()));
            sg.y1 = PixelsToTwips(float(value->GetY()));
            sg.SetWidth(PixelsToTwips(float(value->GetWidth())));
            sg.SetHeight(PixelsToTwips(float(value->GetHeight())));
            pDispObj->SetScale9Grid(sg);
        }
        else
            pDispObj->SetScale9Grid(RectF(0));

//##protect##"instance::DisplayObject::scale9GridSet()"
    }
    void DisplayObject::scaleXGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::scaleXGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetXScale()/100;
//##protect##"instance::DisplayObject::scaleXGet()"
    }
    void DisplayObject::scaleXSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::scaleXSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetXScale(value*100);
//##protect##"instance::DisplayObject::scaleXSet()"
    }
    void DisplayObject::scaleYGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::scaleYGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetYScale()/100;
//##protect##"instance::DisplayObject::scaleYGet()"
    }
    void DisplayObject::scaleYSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::scaleYSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetYScale(value*100);
//##protect##"instance::DisplayObject::scaleYSet()"
    }
    void DisplayObject::scaleZGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::scaleZGet()"
        SF_ASSERT(pDispObj);
        result = (Value::Number)pDispObj->GetZScale()/100;
//##protect##"instance::DisplayObject::scaleZGet()"
    }
    void DisplayObject::scaleZSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::scaleZSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetZScale(value*100);
//##protect##"instance::DisplayObject::scaleZSet()"
    }
    void DisplayObject::scrollRectGet(Value& result)
    {
//##protect##"instance::DisplayObject::scrollRectGet()"
        SF_UNUSED1(result);
        SF_ASSERT(pDispObj);
        const Render::RectD* r = pDispObj->GetScrollRect();
        if (r)
        {
            Value argv[4];
            argv[0].SetNumber(Alg::IRound(TwipsToPixels(r->x1)));
            argv[1].SetNumber(Alg::IRound(TwipsToPixels(r->y1)));
            argv[2].SetNumber(Alg::IRound(TwipsToPixels(r->Width())));
            argv[3].SetNumber(Alg::IRound(TwipsToPixels(r->Height())));

            ASVM& asvm = static_cast<ASVM&>(GetVM());
            SPtr<Rectangle> rect;
            asvm.ConstructInstance(rect, asvm.RectangleClass, 4, argv);
            SF_ASSERT(rect);

            result = Value(rect);
        }
        else
            result.SetNull();
//##protect##"instance::DisplayObject::scrollRectGet()"
    }
    void DisplayObject::scrollRectSet(Value& result, Instances::Rectangle* value)
    {
//##protect##"instance::DisplayObject::scrollRectSet()"
        SF_UNUSED2(result, value);
        SF_ASSERT(pDispObj);
        if (value)
        {
            Render::RectD r(PixelsToTwips(value->GetX()),
                            PixelsToTwips(value->GetY()),
                            Render::SizeD(PixelsToTwips(value->GetWidth()),
                                          PixelsToTwips(value->GetHeight())));
            pDispObj->SetScrollRect(&r);
        }
        else
            pDispObj->SetScrollRect(NULL);
//##protect##"instance::DisplayObject::scrollRectSet()"
    }
    void DisplayObject::stageGet(Value& result)
    {
//##protect##"instance::DisplayObject::stageGet()"
        SF_ASSERT(pDispObj);
        if (ToAvmDisplayObj(pDispObj)->IsStageAccessible())
        {
            AvmDisplayObjContainer* pcontObj = ToAvmDisplayObjContainer(ToAvmDisplayObj(pDispObj)->GetStage());

            pcontObj->CreateASInstance(true);
            result = static_cast<Stage*>(pcontObj->GetAS3Obj());
            SF_ASSERT(GetVM().IsOfType(Value(result), "flash.display.Stage"));
        }
        else
            result.SetNull();
//##protect##"instance::DisplayObject::stageGet()"
    }
    void DisplayObject::transformGet(Value& result)
    {
//##protect##"instance::DisplayObject::transformGet()"
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		SPtr<Transform> ptransform;
		if (asvm.ConstructInstance(ptransform, asvm.TransformClass))
		{
			ptransform->pDispObj = pDispObj;
		}
		result = ptransform;
//##protect##"instance::DisplayObject::transformGet()"
    }
    void DisplayObject::transformSet(Value& result, Instances::Transform* value)
    {
//##protect##"instance::DisplayObject::transformSet()"
		// Obtain the values of the members of the transform class and set it on 
		// the underlying display object.
		pDispObj->SetCxform(value->pDispObj->GetCxform());
        if (pDispObj->Is3D())
            pDispObj->SetMatrix3D(value->pDispObj->GetMatrix3D());
        else
            pDispObj->SetMatrix(value->pDispObj->GetMatrix());
        
        Matrix3F view;
        if (value->pDispObj->GetViewMatrix3D(&view))
            pDispObj->SetViewMatrix3D(view);

        Matrix4F proj;
        if (value->pDispObj->GetProjectionMatrix3D(&proj))
            pDispObj->SetProjectionMatrix3D(proj);

		result.SetUndefined();
//##protect##"instance::DisplayObject::transformSet()"
    }
    void DisplayObject::visibleGet(bool& result)
    {
//##protect##"instance::DisplayObject::visibleGet()"
        SF_ASSERT(pDispObj);

        result = pDispObj->GetVisible();
//##protect##"instance::DisplayObject::visibleGet()"
    }
    void DisplayObject::visibleSet(Value& result, bool value)
    {
//##protect##"instance::DisplayObject::visibleSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetVisible(value);
//##protect##"instance::DisplayObject::visibleSet()"
    }
    void DisplayObject::widthGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::widthGet()"
        SF_ASSERT(pDispObj);

        result = pDispObj->GetWidth();
//##protect##"instance::DisplayObject::widthGet()"
    }
    void DisplayObject::widthSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::widthSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetWidth(value);
//##protect##"instance::DisplayObject::widthSet()"
    }
    void DisplayObject::xGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::xGet()"
        SF_ASSERT(pDispObj);

        result = pDispObj->GetX();
//##protect##"instance::DisplayObject::xGet()"
    }
    void DisplayObject::xSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::xSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetX(value);
//##protect##"instance::DisplayObject::xSet()"
    }
    void DisplayObject::yGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::yGet()"
        SF_ASSERT(pDispObj);

        result = pDispObj->GetY();
//##protect##"instance::DisplayObject::yGet()"
    }
    void DisplayObject::ySet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::ySet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetY(value);
//##protect##"instance::DisplayObject::ySet()"
    }
    void DisplayObject::zGet(Value::Number& result)
    {
//##protect##"instance::DisplayObject::zGet()"
        SF_ASSERT(pDispObj);

        result = TwipsToPixels(pDispObj->GetZ());
//##protect##"instance::DisplayObject::zGet()"
    }
    void DisplayObject::zSet(Value& result, Value::Number value)
    {
//##protect##"instance::DisplayObject::zSet()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj);

        pDispObj->SetZ(PixelsToTwips(value));
//##protect##"instance::DisplayObject::zSet()"
    }
    void DisplayObject::getBounds(Value& result, Instances::DisplayObject* targetCoordinateSpace)
    {
//##protect##"instance::DisplayObject::getBounds()"
        SF_UNUSED2(result, targetCoordinateSpace);

        RectF      b(0);
        Matrix2F   matrix;

        // Transform first by sprite's matrix, then by inverse of target.
        if (targetCoordinateSpace && targetCoordinateSpace != this) // Optimize identity case.
        {
            matrix.SetInverse(targetCoordinateSpace->pDispObj->GetWorldMatrix());
            matrix *= pDispObj->GetWorldMatrix();
        }

        // A "perfect" implementation would be { b = psprite->GetBounds(matrix); },
        // however, Flash always gets the local bounding box before a transform,
        // as follows.
        matrix.EncloseTransform(&b, pDispObj->GetBounds(Matrix2F()));
        
        // to pixels
        b = TwipsToPixels(b);

        // create Rectangle object
        Value params[] = { Value(b.x1), Value(b.y1), Value(b.Width()), Value(b.Height()) };
        static_cast<ASVM&>(GetVM()).RectangleClass->Construct(result, 4, params, true);
//##protect##"instance::DisplayObject::getBounds()"
    }
    void DisplayObject::getRect(Value& result, Instances::DisplayObject* targetCoordinateSpace)
    {
//##protect##"instance::DisplayObject::getRect()"
        SF_UNUSED2(result, targetCoordinateSpace);
        RectF      b(0);
        Matrix2F   matrix;

        // Transform first by sprite's matrix, then by inverse of target.
        if (targetCoordinateSpace && targetCoordinateSpace != this) // Optimize identity case.
        {
            matrix.SetInverse(targetCoordinateSpace->pDispObj->GetWorldMatrix());
            matrix *= pDispObj->GetWorldMatrix();
        }

        // A "perfect" implementation would be { b = psprite->GetBounds(matrix); },
        // however, Flash always gets the local bounding box before a transform,
        // as follows.
        matrix.EncloseTransform(&b, pDispObj->GetRectBounds(Matrix2F()));

        // to pixels
        b = TwipsToPixels(b);

        // create Rectangle object
        Value params[] = { Value(b.x1), Value(b.y1), Value(b.Width()), Value(b.Height()) };
        static_cast<ASVM&>(GetVM()).RectangleClass->Construct(result, 4, params, true);
//##protect##"instance::DisplayObject::getRect()"
    }
    void DisplayObject::globalToLocal(Value& result, Instances::Point* point)
    {
//##protect##"instance::DisplayObject::globalToLocal()"
        // Compute transformation and create a point.
        Render::PointF ptIn((float)PixelsToTwips(point->GetX()), (float)PixelsToTwips(point->GetY()));
		Render::PointF ptOut;
		ptOut = pDispObj->GlobalToLocal(ptIn);
        Value params[] = { Value(TwipsToPixels(ptOut.x)), Value(TwipsToPixels(ptOut.y)) };
        static_cast<ASVM&>(GetVM()).PointClass->Construct(result, 2, params, true);
//##protect##"instance::DisplayObject::globalToLocal()"
    }
    void DisplayObject::globalToLocal3D(Value& result, Instances::Point* point)
    {
//##protect##"instance::DisplayObject::globalToLocal3D()"
        // Compute transformation and create a point.
		Render::PointF ptIn((float)PixelsToTwips(point->GetX()), (float)PixelsToTwips(point->GetY()));
		Render::Point3F ptOut;
		ptOut = pDispObj->GlobalToLocal3D(ptIn);
		Value params[] = { Value(TwipsToPixels(ptOut.x)), Value(TwipsToPixels(ptOut.y)), Value(TwipsToPixels(ptOut.z)) };
		static_cast<ASVM&>(GetVM()).Vector3DClass->Construct(result, 3, params, true);
//##protect##"instance::DisplayObject::globalToLocal3D()"
    }
    void DisplayObject::hitTestObject(bool& result, Instances::DisplayObject* obj)
    {
//##protect##"instance::DisplayObject::hitTestObject()"
        SF_ASSERT(pDispObj);

        result = false;
        RectF spriteLocalBounds = pDispObj->GetBounds(Matrix2F());
        if (spriteLocalBounds.IsNull())
            return;
        if (!obj)
            return;
        SF_ASSERT(obj->pDispObj);

        RectF targetLocalRect  = obj->pDispObj->GetBounds(Matrix2F());
        if (targetLocalRect.IsNull())
            return;
        // Rect rectangles in same coordinate space & check intersection.
		// TODO - need to handle if object are 3D
        RectF spriteWorldRect  = pDispObj->GetWorldMatrix().EncloseTransform(spriteLocalBounds);
        RectF targetWorldRect  = obj->pDispObj->GetWorldMatrix().EncloseTransform(targetLocalRect);
        result = spriteWorldRect.Intersects(targetWorldRect);
//##protect##"instance::DisplayObject::hitTestObject()"
    }
    void DisplayObject::hitTestPoint(bool& result, Value::Number x, Value::Number y, bool shapeFlag)
    {
//##protect##"instance::DisplayObject::hitTestPoint()"
        SF_ASSERT(pDispObj);

        result = false;
        RectF spriteLocalBounds = pDispObj->GetBounds(Matrix2F());
        if (spriteLocalBounds.IsNull())
            return;

        UInt8 hitTestMask = 0;
        // x, y, shapeFlag version of hitTest.
        Render::PointF pt(
            (float)SF_PIXELS_TO_TWIPS(x),
            (float)SF_PIXELS_TO_TWIPS(y));
        if (shapeFlag) // optional parameter shapeFlag
            hitTestMask |= GFx::DisplayObject::HitTest_TestShape;

        MovieImpl * proot = pDispObj->GetMovieImpl();
        if ( proot && pDispObj->Is3D(true) )
        {   // 3D case
            proot->SetNormalizedScreenCoords(pt);

            Matrix3F view;
            Matrix4F proj; 

            Render::ScreenToWorld & stw = proot->ScreenToWorld;
            if (pDispObj->GetProjectionMatrix3D(&proj))
                stw.SetProjection(proj);

            if (pDispObj->GetViewMatrix3D(&view))
                stw.SetView(view);

            stw.SetWorld(pDispObj->GetWorldMatrix3D());
            Render::PointF pp;
            stw.GetWorldPoint(&pp);

            result = pDispObj->PointTestLocal (pp, hitTestMask);
        }
        else
        {   // 2D case            
            Render::PointF ptSpr = pDispObj->GetLevelMatrix().TransformByInverse(pt);
            // pt is already in root's coordinates!

            if (pDispObj->DoesScale9GridExist())
            {
                result = pDispObj->PointTestLocal (ptSpr, hitTestMask);
            }
            else
            {
                if (spriteLocalBounds.Contains(ptSpr))
                {
                    if (!(hitTestMask & GFx::DisplayObject::HitTest_TestShape))
                        result = true;
                    else
                        result = pDispObj->PointTestLocal (ptSpr, hitTestMask);
                }
            }
        }
//##protect##"instance::DisplayObject::hitTestPoint()"
    }
    void DisplayObject::localToGlobal(Value& result, Instances::Point* point)
    {
//##protect##"instance::DisplayObject::localToGlobal()"
        SF_UNUSED(result);
        // Compute transformation and create a point.
        Render::PointF pt((float)PixelsToTwips(point->GetX()), (float)PixelsToTwips(point->GetY()));
        pt = pDispObj->LocalToGlobal(pt);
        Value params[] = { Value(TwipsToPixels(pt.x)), Value(TwipsToPixels(pt.y)) };
        static_cast<ASVM&>(GetVM()).PointClass->Construct(result, 2, params, true);
//##protect##"instance::DisplayObject::localToGlobal()"
    }
    void DisplayObject::local3DToGlobal(Value& result, Instances::Vector3D* point)
    {
//##protect##"instance::DisplayObject::local3DToGlobal()"
        SF_UNUSED(result);
        // Compute transformation and create a point.
        Render::Point3F ptIn((float)PixelsToTwips(point->GetX()), (float)PixelsToTwips(point->GetY()), (float)PixelsToTwips(point->GetZ()));
        Render::PointF ptOut = pDispObj->Local3DToGlobal(ptIn);
        Value params[] = { Value(TwipsToPixels(ptOut.x)), Value(TwipsToPixels(ptOut.y)) };
        static_cast<ASVM&>(GetVM()).PointClass->Construct(result, 2, params, true);
//##protect##"instance::DisplayObject::local3DToGlobal()"
    }

//##protect##"instance$methods"
    DisplayObject::~DisplayObject()
    {
        if (pDispObj)
        {
            ToAvmDisplayObj(pDispObj)->ReleaseAS3Obj();
            if (GetVMSafe().GetGC().IsInCollect())
            {
                pReleaseProxy->Data = pDispObj;
                GetVMSafe().GetGC().AddDelayedReleaseProxy(pReleaseProxy);
            }
        }
    }

    GFx::DisplayObject* DisplayObject::CreateStageObject()
    {
        SF_ASSERT(0); // should be overridden!
        return pDispObj;
    }

    // sets pLoaderInfo = Loader.contentLoaderInfo.
    void DisplayObject::SetLoaderInfo(const Loader& loader)
    {
        pLoaderInfo = loader.GetContentLoaderInfo();
    }
    void DisplayObject::SetLoaderInfo(LoaderInfo* loaderInfo)
    {
        // need to hold this since assignment to pLoaderInfo may cause
        // 'this' release...
        SPtr<DisplayObject> t = this; 
        pLoaderInfo = loaderInfo;
    }

    // returns true if pLoaderInfo is set for the instance
    bool DisplayObject::HasLoaderInfo() const
    {
        return pLoaderInfo.GetPtr() != NULL;
    }

    void DisplayObject::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        EventDispatcher::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<LoaderInfo, Mem_Stat>(prcc, pLoaderInfo, op SF_DEBUG_ARG(*this));
    }

    bool DisplayObject::FindLibarySymbol(CharacterCreateInfo* pccinfo, MovieDefImpl* pdefImpl) const
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        pccinfo->pCharDef     = NULL;
        pccinfo->pResource    = NULL;
        pccinfo->pBindDefImpl = pdefImpl;
        const Traits* curTraits = &GetTraits();

        // We need to interate through all base classes in order to find a library symbol.
        // The library symbol may be linked to one of the base class and it still should be
        // picked up (see mc_linkage_to_base_class.swf)
        while (curTraits && curTraits->IsUserDefined() && 
               !pccinfo->pCharDef && !pccinfo->pResource)
        {
            // here we should get fully qualified name of class, with package, 
            // for example: example_fla.Symbol1. 
            //                    ASString className = GetInstanceTraits().GetQualifiedName(Traits::qnfWithDot);
            ASString className = curTraits->GetQualifiedName(Traits::qnfWithDot);

            ResourceBindData resBindData;
            if (asvm.GetMovieImpl()->FindExportedResource(pdefImpl, &resBindData, className.ToCStr()))
            {
                if (resBindData.pResource->GetResourceType() & Resource::RT_CharacterDef_Bit)
                    pccinfo->pCharDef = static_cast<CharacterDef*>(resBindData.pResource.GetPtr());
                else
                    pccinfo->pResource = resBindData.pResource.GetPtr();
                pccinfo->pBindDefImpl = resBindData.pBinding->GetOwnerDefImpl();
            }
            else
                curTraits = curTraits->GetParent();
        }
        return (pccinfo->pCharDef != NULL || pccinfo->pResource != NULL);
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo DisplayObject::ti[DisplayObject::ThunkInfoNum] = {
        {TFunc_Instances_DisplayObject_accessibilityPropertiesGet::Func, &AccessibilityPropertiesCI, "accessibilityProperties", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_accessibilityPropertiesSet::Func, NULL, "accessibilityProperties", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_alphaGet::Func, &NumberCI, "alpha", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_alphaSet::Func, NULL, "alpha", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_blendModeGet::Func, &StringCI, "blendMode", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_blendModeSet::Func, NULL, "blendMode", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_cacheAsBitmapGet::Func, &BooleanCI, "cacheAsBitmap", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_cacheAsBitmapSet::Func, NULL, "cacheAsBitmap", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_filtersGet::Func, &ArrayCI, "filters", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_filtersSet::Func, NULL, "filters", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_heightGet::Func, &NumberCI, "height", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_heightSet::Func, NULL, "height", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_loaderInfoGet::Func, &LoaderInfoCI, "loaderInfo", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_maskGet::Func, &DisplayObjectCI, "mask", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_maskSet::Func, NULL, "mask", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_mouseXGet::Func, &NumberCI, "mouseX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_mouseYGet::Func, &NumberCI, "mouseY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_nameGet::Func, &ObjectCI, "name", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_nameSet::Func, NULL, "name", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_opaqueBackgroundGet::Func, &ObjectCI, "opaqueBackground", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_opaqueBackgroundSet::Func, NULL, "opaqueBackground", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_parentGet::Func, &DisplayObjectContainerCI, "parent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rootGet::Func, &DisplayObjectCI, "root", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rotationGet::Func, &NumberCI, "rotation", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rotationSet::Func, NULL, "rotation", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_rotationXGet::Func, &NumberCI, "rotationX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rotationXSet::Func, NULL, "rotationX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_rotationYGet::Func, &NumberCI, "rotationY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rotationYSet::Func, NULL, "rotationY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_rotationZGet::Func, &NumberCI, "rotationZ", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_rotationZSet::Func, NULL, "rotationZ", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_scale9GridGet::Func, &RectangleCI, "scale9Grid", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_scale9GridSet::Func, NULL, "scale9Grid", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_scaleXGet::Func, &NumberCI, "scaleX", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_scaleXSet::Func, NULL, "scaleX", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_scaleYGet::Func, &NumberCI, "scaleY", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_scaleYSet::Func, NULL, "scaleY", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_scaleZGet::Func, &NumberCI, "scaleZ", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_scaleZSet::Func, NULL, "scaleZ", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_scrollRectGet::Func, &RectangleCI, "scrollRect", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_scrollRectSet::Func, NULL, "scrollRect", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_stageGet::Func, &StageCI, "stage", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_transformGet::Func, &TransformCI, "transform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_transformSet::Func, NULL, "transform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_visibleGet::Func, &BooleanCI, "visible", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_visibleSet::Func, NULL, "visible", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_widthGet::Func, &NumberCI, "width", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_widthSet::Func, NULL, "width", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_xGet::Func, &NumberCI, "x", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_xSet::Func, NULL, "x", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_yGet::Func, &NumberCI, "y", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_ySet::Func, NULL, "y", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_zGet::Func, &NumberCI, "z", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObject_zSet::Func, NULL, "z", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObject_getBounds::Func, &RectangleCI, "getBounds", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_getRect::Func, &RectangleCI, "getRect", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_globalToLocal::Func, &PointCI, "globalToLocal", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_globalToLocal3D::Func, &Vector3DCI, "globalToLocal3D", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_hitTestObject::Func, &BooleanCI, "hitTestObject", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_hitTestPoint::Func, &BooleanCI, "hitTestPoint", NULL, CT_Method, 2, 3},
        {TFunc_Instances_DisplayObject_localToGlobal::Func, &PointCI, "localToGlobal", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObject_local3DToGlobal::Func, &PointCI, "local3DToGlobal", NULL, CT_Method, 1, 1},
    };

    DisplayObject::DisplayObject(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::DisplayObject::DisplayObject()"
        SetTraitsType(Traits_DisplayObject);
//##protect##"InstanceTraits::DisplayObject::DisplayObject()"
        SetMemSize(sizeof(Instances::DisplayObject));
        RegisterImplementedInterface(Multiname(GetVM(), "flash.display.IBitmapDrawable"));

    }

    Pickable<Instances::DisplayObject> DisplayObject::MakeInstance(Traits& t)
    {
        return Pickable<Instances::DisplayObject>(new(t.Alloc()) Instances::DisplayObject(t));
    }

    void DisplayObject::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    DisplayObject::DisplayObject(VM& vm)
    : Traits(vm, DisplayObjectCI)
    {
//##protect##"ClassTraits::DisplayObject::DisplayObject()"
        SetTraitsType(Traits_DisplayObject);
//##protect##"ClassTraits::DisplayObject::DisplayObject()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::DisplayObject(vm, DisplayObjectCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DisplayObject::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DisplayObject(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DisplayObjectCI = {
    ClassInfo::CompileTime,
    "DisplayObject", "flash.display", &EventDispatcherCI,
    ClassTraits::DisplayObject::MakeClassTraits,
    0,
    0,
    InstanceTraits::DisplayObject::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::DisplayObject::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

