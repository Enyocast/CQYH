//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BitmapData.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_BitmapData.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Display_IBitmapDrawable.h"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
#include "../Geom/AS3_Obj_Geom_Rectangle.h"
#include "../Geom/AS3_Obj_Geom_Point.h"
#include "../Geom/AS3_Obj_Geom_ColorTransform.h"
#include "../Geom/AS3_Obj_Geom_Matrix.h"
#include "../Filters/AS3_Obj_Filters_BitmapFilter.h"
#include "GFx/GFx_FontResource.h"
#include "GFx/AS3/AS3_MovieRoot.h"
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
    ASString GetMethodDefArg<Instances::BitmapData, Instances::BitmapData::mid_draw, 3, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

    template <>
    SF_INLINE
    bool GetMethodDefArg<Instances::BitmapData, Instances::BitmapData::mid_getColorBoundsRect, 2, bool>(AS3::StringManager&)
    {
        return true;
    }

    template <>
    SF_INLINE
    UInt32 GetMethodDefArg<Instances::BitmapData, Instances::BitmapData::mid_hitTest, 4, UInt32>(AS3::StringManager&)
    {
        return 1;
    }

    template <>
    SF_INLINE
    UInt32 GetMethodDefArg<Instances::BitmapData, Instances::BitmapData::mid_noise, 2, UInt32>(AS3::StringManager&)
    {
        return 255;
    }

    template <>
    SF_INLINE
    UInt32 GetMethodDefArg<Instances::BitmapData, Instances::BitmapData::mid_noise, 3, UInt32>(AS3::StringManager&)
    {
        return 7;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_heightGet, SInt32> TFunc_Instances_BitmapData_heightGet;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_rectGet, Value> TFunc_Instances_BitmapData_rectGet;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_transparentGet, bool> TFunc_Instances_BitmapData_transparentGet;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_widthGet, SInt32> TFunc_Instances_BitmapData_widthGet;
typedef ThunkFunc4<Instances::BitmapData, Instances::BitmapData::mid_applyFilter, Value, Instances::BitmapData*, Instances::Rectangle*, Instances::Point*, Instances::BitmapFilter*> TFunc_Instances_BitmapData_applyFilter;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_clone, Value> TFunc_Instances_BitmapData_clone;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_colorTransform, Value, Instances::Rectangle*, Instances::ColorTransform*> TFunc_Instances_BitmapData_colorTransform;
typedef ThunkFunc1<Instances::BitmapData, Instances::BitmapData::mid_compare, Value, Instances::BitmapData*> TFunc_Instances_BitmapData_compare;
typedef ThunkFunc5<Instances::BitmapData, Instances::BitmapData::mid_copyChannel, Value, Instances::BitmapData*, Instances::Rectangle*, Instances::Point*, UInt32, UInt32> TFunc_Instances_BitmapData_copyChannel;
typedef ThunkFunc6<Instances::BitmapData, Instances::BitmapData::mid_copyPixels, Value, Instances::BitmapData*, Instances::Rectangle*, Instances::Point*, Instances::BitmapData*, Instances::Point*, bool> TFunc_Instances_BitmapData_copyPixels;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_dispose, Value> TFunc_Instances_BitmapData_dispose;
typedef ThunkFunc6<Instances::BitmapData, Instances::BitmapData::mid_draw, Value, Instances::IBitmapDrawable*, Instances::Matrix*, Instances::ColorTransform*, const ASString&, Instances::Rectangle*, bool> TFunc_Instances_BitmapData_draw;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_fillRect, Value, Instances::Rectangle*, UInt32> TFunc_Instances_BitmapData_fillRect;
typedef ThunkFunc3<Instances::BitmapData, Instances::BitmapData::mid_floodFill, Value, SInt32, SInt32, UInt32> TFunc_Instances_BitmapData_floodFill;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_generateFilterRect, Value, Instances::Rectangle*, Instances::BitmapFilter*> TFunc_Instances_BitmapData_generateFilterRect;
typedef ThunkFunc3<Instances::BitmapData, Instances::BitmapData::mid_getColorBoundsRect, Value, UInt32, UInt32, bool> TFunc_Instances_BitmapData_getColorBoundsRect;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_getPixel, UInt32, SInt32, SInt32> TFunc_Instances_BitmapData_getPixel;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_getPixel32, UInt32, SInt32, SInt32> TFunc_Instances_BitmapData_getPixel32;
typedef ThunkFunc1<Instances::BitmapData, Instances::BitmapData::mid_getPixels, Value, Instances::Rectangle*> TFunc_Instances_BitmapData_getPixels;
typedef ThunkFunc5<Instances::BitmapData, Instances::BitmapData::mid_hitTest, bool, Instances::Point*, UInt32, const Value&, Instances::Point*, UInt32> TFunc_Instances_BitmapData_hitTest;
typedef ThunkFunc0<Instances::BitmapData, Instances::BitmapData::mid_lock, Value> TFunc_Instances_BitmapData_lock;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_merge, Value, unsigned, const Value*> TFunc_Instances_BitmapData_merge;
typedef ThunkFunc5<Instances::BitmapData, Instances::BitmapData::mid_noise, Value, SInt32, UInt32, UInt32, UInt32, bool> TFunc_Instances_BitmapData_noise;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_paletteMap, Value, unsigned, const Value*> TFunc_Instances_BitmapData_paletteMap;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_perlinNoise, Value, unsigned, const Value*> TFunc_Instances_BitmapData_perlinNoise;
typedef ThunkFunc6<Instances::BitmapData, Instances::BitmapData::mid_pixelDissolve, SInt32, Instances::BitmapData*, Instances::Rectangle*, Instances::Point*, SInt32, SInt32, UInt32> TFunc_Instances_BitmapData_pixelDissolve;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_scroll, Value, SInt32, SInt32> TFunc_Instances_BitmapData_scroll;
typedef ThunkFunc3<Instances::BitmapData, Instances::BitmapData::mid_setPixel, Value, SInt32, SInt32, UInt32> TFunc_Instances_BitmapData_setPixel;
typedef ThunkFunc3<Instances::BitmapData, Instances::BitmapData::mid_setPixel32, Value, SInt32, SInt32, UInt32> TFunc_Instances_BitmapData_setPixel32;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_setPixels, Value, Instances::Rectangle*, Instances::ByteArray*> TFunc_Instances_BitmapData_setPixels;
typedef ThunkFunc2<Instances::BitmapData, Instances::BitmapData::mid_threshold, Value, unsigned, const Value*> TFunc_Instances_BitmapData_threshold;
typedef ThunkFunc1<Instances::BitmapData, Instances::BitmapData::mid_unlock, Value, Instances::Rectangle*> TFunc_Instances_BitmapData_unlock;

template <> const TFunc_Instances_BitmapData_heightGet::TMethod TFunc_Instances_BitmapData_heightGet::Method = &Instances::BitmapData::heightGet;
template <> const TFunc_Instances_BitmapData_rectGet::TMethod TFunc_Instances_BitmapData_rectGet::Method = &Instances::BitmapData::rectGet;
template <> const TFunc_Instances_BitmapData_transparentGet::TMethod TFunc_Instances_BitmapData_transparentGet::Method = &Instances::BitmapData::transparentGet;
template <> const TFunc_Instances_BitmapData_widthGet::TMethod TFunc_Instances_BitmapData_widthGet::Method = &Instances::BitmapData::widthGet;
template <> const TFunc_Instances_BitmapData_applyFilter::TMethod TFunc_Instances_BitmapData_applyFilter::Method = &Instances::BitmapData::applyFilter;
template <> const TFunc_Instances_BitmapData_clone::TMethod TFunc_Instances_BitmapData_clone::Method = &Instances::BitmapData::clone;
template <> const TFunc_Instances_BitmapData_colorTransform::TMethod TFunc_Instances_BitmapData_colorTransform::Method = &Instances::BitmapData::colorTransform;
template <> const TFunc_Instances_BitmapData_compare::TMethod TFunc_Instances_BitmapData_compare::Method = &Instances::BitmapData::compare;
template <> const TFunc_Instances_BitmapData_copyChannel::TMethod TFunc_Instances_BitmapData_copyChannel::Method = &Instances::BitmapData::copyChannel;
template <> const TFunc_Instances_BitmapData_copyPixels::TMethod TFunc_Instances_BitmapData_copyPixels::Method = &Instances::BitmapData::copyPixels;
template <> const TFunc_Instances_BitmapData_dispose::TMethod TFunc_Instances_BitmapData_dispose::Method = &Instances::BitmapData::dispose;
template <> const TFunc_Instances_BitmapData_draw::TMethod TFunc_Instances_BitmapData_draw::Method = &Instances::BitmapData::draw;
template <> const TFunc_Instances_BitmapData_fillRect::TMethod TFunc_Instances_BitmapData_fillRect::Method = &Instances::BitmapData::fillRect;
template <> const TFunc_Instances_BitmapData_floodFill::TMethod TFunc_Instances_BitmapData_floodFill::Method = &Instances::BitmapData::floodFill;
template <> const TFunc_Instances_BitmapData_generateFilterRect::TMethod TFunc_Instances_BitmapData_generateFilterRect::Method = &Instances::BitmapData::generateFilterRect;
template <> const TFunc_Instances_BitmapData_getColorBoundsRect::TMethod TFunc_Instances_BitmapData_getColorBoundsRect::Method = &Instances::BitmapData::getColorBoundsRect;
template <> const TFunc_Instances_BitmapData_getPixel::TMethod TFunc_Instances_BitmapData_getPixel::Method = &Instances::BitmapData::getPixel;
template <> const TFunc_Instances_BitmapData_getPixel32::TMethod TFunc_Instances_BitmapData_getPixel32::Method = &Instances::BitmapData::getPixel32;
template <> const TFunc_Instances_BitmapData_getPixels::TMethod TFunc_Instances_BitmapData_getPixels::Method = &Instances::BitmapData::getPixels;
template <> const TFunc_Instances_BitmapData_hitTest::TMethod TFunc_Instances_BitmapData_hitTest::Method = &Instances::BitmapData::hitTest;
template <> const TFunc_Instances_BitmapData_lock::TMethod TFunc_Instances_BitmapData_lock::Method = &Instances::BitmapData::lock;
template <> const TFunc_Instances_BitmapData_merge::TMethod TFunc_Instances_BitmapData_merge::Method = &Instances::BitmapData::merge;
template <> const TFunc_Instances_BitmapData_noise::TMethod TFunc_Instances_BitmapData_noise::Method = &Instances::BitmapData::noise;
template <> const TFunc_Instances_BitmapData_paletteMap::TMethod TFunc_Instances_BitmapData_paletteMap::Method = &Instances::BitmapData::paletteMap;
template <> const TFunc_Instances_BitmapData_perlinNoise::TMethod TFunc_Instances_BitmapData_perlinNoise::Method = &Instances::BitmapData::perlinNoise;
template <> const TFunc_Instances_BitmapData_pixelDissolve::TMethod TFunc_Instances_BitmapData_pixelDissolve::Method = &Instances::BitmapData::pixelDissolve;
template <> const TFunc_Instances_BitmapData_scroll::TMethod TFunc_Instances_BitmapData_scroll::Method = &Instances::BitmapData::scroll;
template <> const TFunc_Instances_BitmapData_setPixel::TMethod TFunc_Instances_BitmapData_setPixel::Method = &Instances::BitmapData::setPixel;
template <> const TFunc_Instances_BitmapData_setPixel32::TMethod TFunc_Instances_BitmapData_setPixel32::Method = &Instances::BitmapData::setPixel32;
template <> const TFunc_Instances_BitmapData_setPixels::TMethod TFunc_Instances_BitmapData_setPixels::Method = &Instances::BitmapData::setPixels;
template <> const TFunc_Instances_BitmapData_threshold::TMethod TFunc_Instances_BitmapData_threshold::Method = &Instances::BitmapData::threshold;
template <> const TFunc_Instances_BitmapData_unlock::TMethod TFunc_Instances_BitmapData_unlock::Method = &Instances::BitmapData::unlock;

namespace Instances
{
    BitmapData::BitmapData(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::BitmapData::BitmapData()$data"
    , Width(0), Height(0), Dirty(false)
//##protect##"instance::BitmapData::BitmapData()$data"
    {
//##protect##"instance::BitmapData::BitmapData()$code"
//##protect##"instance::BitmapData::BitmapData()$code"
    }

    void BitmapData::heightGet(SInt32& result)
    {
//##protect##"instance::BitmapData::heightGet()"
        SF_UNUSED1(result);
        if (pImage)
            result = pImage->GetRect().Height();
        else
            result = (SInt32)Height;
//##protect##"instance::BitmapData::heightGet()"
    }
    void BitmapData::rectGet(Value& result)
    {
//##protect##"instance::BitmapData::rectGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("BitmapData::rectGet()");
//##protect##"instance::BitmapData::rectGet()"
    }
    void BitmapData::transparentGet(bool& result)
    {
//##protect##"instance::BitmapData::transparentGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("BitmapData::transparentGet()");
//##protect##"instance::BitmapData::transparentGet()"
    }
    void BitmapData::widthGet(SInt32& result)
    {
//##protect##"instance::BitmapData::widthGet()"
        SF_UNUSED1(result);
        if (pImage)
            result = pImage->GetRect().Width();
        else
            result = (SInt32)Width;
//##protect##"instance::BitmapData::widthGet()"
    }
    void BitmapData::applyFilter(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, Instances::BitmapFilter* filter)
    {
//##protect##"instance::BitmapData::applyFilter()"
        SF_UNUSED5(result, sourceBitmapData, sourceRect, destPoint, filter);
        WARN_NOT_IMPLEMENTED("BitmapData::applyFilter()");
//##protect##"instance::BitmapData::applyFilter()"
    }
    void BitmapData::clone(Value& result)
    {
//##protect##"instance::BitmapData::clone()"
        WARN_NOT_IMPLEMENTED("BitmapData::clone()");
        InstanceTraits::BitmapData& itr = static_cast<InstanceTraits::BitmapData&>(GetInstanceTraits());
        result = itr.MakeInstance(itr);
//##protect##"instance::BitmapData::clone()"
    }
    void BitmapData::colorTransform(Value& result, Instances::Rectangle* rect, Instances::ColorTransform* colorTransform)
    {
//##protect##"instance::BitmapData::colorTransform()"
        SF_UNUSED3(result, rect, colorTransform);
        WARN_NOT_IMPLEMENTED("BitmapData::colorTransform()");
//##protect##"instance::BitmapData::colorTransform()"
    }
    void BitmapData::compare(Value& result, Instances::BitmapData* otherBitmapData)
    {
//##protect##"instance::BitmapData::compare()"
        SF_UNUSED2(result, otherBitmapData);
        WARN_NOT_IMPLEMENTED("BitmapData::compare()");
//##protect##"instance::BitmapData::compare()"
    }
    void BitmapData::copyChannel(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, UInt32 sourceChannel, UInt32 destChannel)
    {
//##protect##"instance::BitmapData::copyChannel()"
        SF_UNUSED6(result, sourceBitmapData, sourceRect, destPoint, sourceChannel, destChannel);
        WARN_NOT_IMPLEMENTED("BitmapData::copyChannel()");
//##protect##"instance::BitmapData::copyChannel()"
    }
    void BitmapData::copyPixels(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, Instances::BitmapData* alphaBitmapData, Instances::Point* alphaPoint, bool mergeAlpha)
    {
//##protect##"instance::BitmapData::copyPixels()"
        SF_UNUSED7(result, sourceBitmapData, sourceRect, destPoint, alphaBitmapData, alphaPoint, mergeAlpha);
        WARN_NOT_IMPLEMENTED("BitmapData::copyPixels()");
//##protect##"instance::BitmapData::copyPixels()"
    }
    void BitmapData::dispose(Value& result)
    {
//##protect##"instance::BitmapData::dispose()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("BitmapData::dispose()");
//##protect##"instance::BitmapData::dispose()"
    }
    void BitmapData::draw(Value& result, Instances::IBitmapDrawable* source, Instances::Matrix* matrix, Instances::ColorTransform* colorTransform, const ASString& blendMode, Instances::Rectangle* clipRect, bool smoothing)
    {
//##protect##"instance::BitmapData::draw()"
        SF_UNUSED7(result, source, matrix, colorTransform, blendMode, clipRect, smoothing);
        WARN_NOT_IMPLEMENTED("BitmapData::draw()");
//##protect##"instance::BitmapData::draw()"
    }
    void BitmapData::fillRect(Value& result, Instances::Rectangle* rect, UInt32 color)
    {
//##protect##"instance::BitmapData::fillRect()"
        SF_UNUSED3(result, rect, color);
        WARN_NOT_IMPLEMENTED("BitmapData::fillRect()");
//##protect##"instance::BitmapData::fillRect()"
    }
    void BitmapData::floodFill(Value& result, SInt32 x, SInt32 y, UInt32 color)
    {
//##protect##"instance::BitmapData::floodFill()"
        SF_UNUSED4(result, x, y, color);
        WARN_NOT_IMPLEMENTED("BitmapData::floodFill()");
//##protect##"instance::BitmapData::floodFill()"
    }
    void BitmapData::generateFilterRect(Value& result, Instances::Rectangle* sourceRect, Instances::BitmapFilter* filter)
    {
//##protect##"instance::BitmapData::generateFilterRect()"
        SF_UNUSED3(result, sourceRect, filter);
        WARN_NOT_IMPLEMENTED("BitmapData::generateFilterRect()");
//##protect##"instance::BitmapData::generateFilterRect()"
    }
    void BitmapData::getColorBoundsRect(Value& result, UInt32 mask, UInt32 color, bool findColor)
    {
//##protect##"instance::BitmapData::getColorBoundsRect()"
        SF_UNUSED4(result, mask, color, findColor);
        WARN_NOT_IMPLEMENTED("BitmapData::getColorBoundsRect()");
//##protect##"instance::BitmapData::getColorBoundsRect()"
    }
    void BitmapData::getPixel(UInt32& result, SInt32 x, SInt32 y)
    {
//##protect##"instance::BitmapData::getPixel()"
        SF_UNUSED3(result, x, y);
        WARN_NOT_IMPLEMENTED("BitmapData::getPixel()");
//##protect##"instance::BitmapData::getPixel()"
    }
    void BitmapData::getPixel32(UInt32& result, SInt32 x, SInt32 y)
    {
//##protect##"instance::BitmapData::getPixel32()"
        SF_UNUSED3(result, x, y);
        WARN_NOT_IMPLEMENTED("BitmapData::getPixel32()");
//##protect##"instance::BitmapData::getPixel32()"
    }
    void BitmapData::getPixels(Value& result, Instances::Rectangle* rect)
    {
//##protect##"instance::BitmapData::getPixels()"
        SF_UNUSED2(result, rect);
        WARN_NOT_IMPLEMENTED("BitmapData::getPixels()");
//##protect##"instance::BitmapData::getPixels()"
    }
    void BitmapData::hitTest(bool& result, Instances::Point* firstPoint, UInt32 firstAlphaThreshold, const Value& secondObject, Instances::Point* secondBitmapDataPoint, UInt32 secondAlphaThreshold)
    {
//##protect##"instance::BitmapData::hitTest()"
        SF_UNUSED6(result, firstPoint, firstAlphaThreshold, secondObject, secondBitmapDataPoint, secondAlphaThreshold);
        WARN_NOT_IMPLEMENTED("BitmapData::hitTest()");
//##protect##"instance::BitmapData::hitTest()"
    }
    void BitmapData::lock(Value& result)
    {
//##protect##"instance::BitmapData::lock()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("BitmapData::lock()");
//##protect##"instance::BitmapData::lock()"
    }
    void BitmapData::merge(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::BitmapData::merge()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("BitmapData::merge()");
//##protect##"instance::BitmapData::merge()"
    }
    void BitmapData::noise(Value& result, SInt32 randomSeed, UInt32 low, UInt32 high, UInt32 channelOptions, bool grayScale)
    {
//##protect##"instance::BitmapData::noise()"
        SF_UNUSED6(result, randomSeed, low, high, channelOptions, grayScale);
        WARN_NOT_IMPLEMENTED("BitmapData::noise()");
//##protect##"instance::BitmapData::noise()"
    }
    void BitmapData::paletteMap(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::BitmapData::paletteMap()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("BitmapData::paletteMap()");
//##protect##"instance::BitmapData::paletteMap()"
    }
    void BitmapData::perlinNoise(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::BitmapData::perlinNoise()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("BitmapData::perlinNoise()");
//##protect##"instance::BitmapData::perlinNoise()"
    }
    void BitmapData::pixelDissolve(SInt32& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, SInt32 randomSeed, SInt32 numPixels, UInt32 fillColor)
    {
//##protect##"instance::BitmapData::pixelDissolve()"
        SF_UNUSED7(result, sourceBitmapData, sourceRect, destPoint, randomSeed, numPixels, fillColor);
        WARN_NOT_IMPLEMENTED("BitmapData::pixelDissolve()");
//##protect##"instance::BitmapData::pixelDissolve()"
    }
    void BitmapData::scroll(Value& result, SInt32 x, SInt32 y)
    {
//##protect##"instance::BitmapData::scroll()"
        SF_UNUSED3(result, x, y);
        WARN_NOT_IMPLEMENTED("BitmapData::scroll()");
//##protect##"instance::BitmapData::scroll()"
    }
    void BitmapData::setPixel(Value& result, SInt32 x, SInt32 y, UInt32 color)
    {
//##protect##"instance::BitmapData::setPixel()"
        SF_UNUSED4(result, x, y, color);
        WARN_NOT_IMPLEMENTED("BitmapData::setPixel()");
//##protect##"instance::BitmapData::setPixel()"
    }
    void BitmapData::setPixel32(Value& result, SInt32 x, SInt32 y, UInt32 color)
    {
//##protect##"instance::BitmapData::setPixel32()"
        SF_UNUSED4(result, x, y, color);
        WARN_NOT_IMPLEMENTED("BitmapData::setPixel32()");
//##protect##"instance::BitmapData::setPixel32()"
    }
    void BitmapData::setPixels(Value& result, Instances::Rectangle* rect, Instances::ByteArray* inputByteArray)
    {
//##protect##"instance::BitmapData::setPixels()"
        SF_UNUSED3(result, rect, inputByteArray);
        WARN_NOT_IMPLEMENTED("BitmapData::setPixels()");
//##protect##"instance::BitmapData::setPixels()"
    }
    void BitmapData::threshold(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::BitmapData::threshold()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("BitmapData::threshold()");
//##protect##"instance::BitmapData::threshold()"
    }
    void BitmapData::unlock(Value& result, Instances::Rectangle* changeRect)
    {
//##protect##"instance::BitmapData::unlock()"
        SF_UNUSED2(result, changeRect);
        WARN_NOT_IMPLEMENTED("BitmapData::unlock()");
//##protect##"instance::BitmapData::unlock()"
    }

//##protect##"instance$methods"
    void BitmapData::InitInstance(bool extCall)
    {
        if (!extCall)
        {
            // create stage display object if the movieclip was created by
            // "new".
            BitmapData::CreateLibraryObject(NULL);
        }
    }

    bool BitmapData::CreateLibraryObject(ImageResource* imgRes)
    {
        if (!pImage)
        {
            if (imgRes)
            {
                pImageResource = imgRes;
                pImage = pImageResource->GetImage();
            }
            else
            {
                ASVM& asvm = static_cast<ASVM&>(GetVM());
                MovieDefImpl* pdefImpl = asvm.GetResourceMovieDef(this);

                if (pdefImpl && GetTraits().IsUserDefined())
                {
                    // here we should get fully qualified name of class, with package, 
                    // for example: example_fla.Symbol1. 
                    ASString className = GetInstanceTraits().GetQualifiedName(Traits::qnfWithDot);

                    ResourceBindData    resBindData;
                    if (!asvm.GetMovieImpl()->FindExportedResource(pdefImpl, &resBindData, className.ToCStr()))
                    {
                        MovieRoot* proot = asvm.GetMovieRoot();
                        if (proot->GetLog())
                            proot->GetLog()->LogWarning("Attaching a bitmap with class '%s' failed",
                            className.ToCStr());
                        return false;
                    }
                    
                    if (resBindData.pResource)
                    {
                        if (resBindData.pResource->GetResourceType() == Resource::RT_Image)
                        {
                            pImageResource = static_cast<ImageResource*>(resBindData.pResource.GetPtr());
                            pImage = pImageResource->GetImage();
                        }
                    }
                }
            }
        }
        return false;
    }

    ImageResource* BitmapData::GetImageResource() const
    {
        if (pImageResource)
            return pImageResource;
        if (pImage)
        {
            return SF_HEAP_AUTO_NEW(pImage) ImageResource(pImage, Resource::Use_Bitmap);
        }
        return false;
    }

    void BitmapData::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc < 2)
            return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("BitmapData::AS3Constructor") SF_DEBUG_ARG(2) SF_DEBUG_ARG(2) SF_DEBUG_ARG(argc)));

        SInt32 v;
        argv[0].Convert2Int32(v).DoNotCheck();
        Width = (unsigned)v;

        argv[1].Convert2Int32(v).DoNotCheck();
        Height = (unsigned)v;
        
        //argv[2].Convert2Int32(v).DoNotCheck(); // fillcolor
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo BitmapData::ti[BitmapData::ThunkInfoNum] = {
        {TFunc_Instances_BitmapData_heightGet::Func, &int_CI, "height", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BitmapData_rectGet::Func, &RectangleCI, "rect", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BitmapData_transparentGet::Func, &BooleanCI, "transparent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BitmapData_widthGet::Func, &int_CI, "width", NULL, CT_Get, 0, 0},
        {TFunc_Instances_BitmapData_applyFilter::Func, NULL, "applyFilter", NULL, CT_Method, 4, 4},
        {TFunc_Instances_BitmapData_clone::Func, &BitmapDataCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_BitmapData_colorTransform::Func, NULL, "colorTransform", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_compare::Func, &ObjectCI, "compare", NULL, CT_Method, 1, 1},
        {TFunc_Instances_BitmapData_copyChannel::Func, NULL, "copyChannel", NULL, CT_Method, 5, 5},
        {TFunc_Instances_BitmapData_copyPixels::Func, NULL, "copyPixels", NULL, CT_Method, 3, 6},
        {TFunc_Instances_BitmapData_dispose::Func, NULL, "dispose", NULL, CT_Method, 0, 0},
        {TFunc_Instances_BitmapData_draw::Func, NULL, "draw", NULL, CT_Method, 1, 6},
        {TFunc_Instances_BitmapData_fillRect::Func, NULL, "fillRect", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_floodFill::Func, NULL, "floodFill", NULL, CT_Method, 3, 3},
        {TFunc_Instances_BitmapData_generateFilterRect::Func, &RectangleCI, "generateFilterRect", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_getColorBoundsRect::Func, &RectangleCI, "getColorBoundsRect", NULL, CT_Method, 2, 3},
        {TFunc_Instances_BitmapData_getPixel::Func, &uintCI, "getPixel", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_getPixel32::Func, &uintCI, "getPixel32", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_getPixels::Func, &ByteArrayCI, "getPixels", NULL, CT_Method, 1, 1},
        {TFunc_Instances_BitmapData_hitTest::Func, &BooleanCI, "hitTest", NULL, CT_Method, 3, 5},
        {TFunc_Instances_BitmapData_lock::Func, NULL, "lock", NULL, CT_Method, 0, 0},
        {TFunc_Instances_BitmapData_merge::Func, NULL, "merge", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_BitmapData_noise::Func, NULL, "noise", NULL, CT_Method, 1, 5},
        {TFunc_Instances_BitmapData_paletteMap::Func, NULL, "paletteMap", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_BitmapData_perlinNoise::Func, NULL, "perlinNoise", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_BitmapData_pixelDissolve::Func, &int_CI, "pixelDissolve", NULL, CT_Method, 3, 6},
        {TFunc_Instances_BitmapData_scroll::Func, NULL, "scroll", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_setPixel::Func, NULL, "setPixel", NULL, CT_Method, 3, 3},
        {TFunc_Instances_BitmapData_setPixel32::Func, NULL, "setPixel32", NULL, CT_Method, 3, 3},
        {TFunc_Instances_BitmapData_setPixels::Func, NULL, "setPixels", NULL, CT_Method, 2, 2},
        {TFunc_Instances_BitmapData_threshold::Func, &uintCI, "threshold", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_BitmapData_unlock::Func, NULL, "unlock", NULL, CT_Method, 0, 1},
    };

    BitmapData::BitmapData(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::BitmapData::BitmapData()"
//##protect##"InstanceTraits::BitmapData::BitmapData()"
        SetMemSize(sizeof(Instances::BitmapData));
        RegisterImplementedInterface(Multiname(GetVM(), "flash.display.IBitmapDrawable"));

    }

    Pickable<Instances::BitmapData> BitmapData::MakeInstance(Traits& t)
    {
        return Pickable<Instances::BitmapData>(new(t.Alloc()) Instances::BitmapData(t));
    }

    void BitmapData::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    BitmapData::BitmapData(VM& vm)
    : Traits(vm, BitmapDataCI)
    {
//##protect##"ClassTraits::BitmapData::BitmapData()"
//##protect##"ClassTraits::BitmapData::BitmapData()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::BitmapData(vm, BitmapDataCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> BitmapData::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) BitmapData(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapDataCI = {
    ClassInfo::CompileTime,
    "BitmapData", "flash.display", &ObjectCI,
    ClassTraits::BitmapData::MakeClassTraits,
    0,
    0,
    InstanceTraits::BitmapData::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::BitmapData::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

