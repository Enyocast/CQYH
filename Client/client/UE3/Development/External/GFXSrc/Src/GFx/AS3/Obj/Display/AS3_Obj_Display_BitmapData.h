//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BitmapData.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_BitmapData_H
#define INC_AS3_Obj_Display_BitmapData_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//#include "Render/Render_ImageInfo.h"
#include "GFx/GFx_ImageResource.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Rectangle;
    class Matrix;
    class Point;

    class BitmapFilter;
    class ByteArray;
    class ColorTransform;
    class IBitmapDrawable;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BitmapData;
}

namespace InstanceTraits
{
    class BitmapData;
}

namespace Classes
{
    class BitmapData;
}

namespace Instances
{
    class BitmapData : public Instances::Object
    {
        friend class InstanceTraits::BitmapData;
        
    public:
        typedef BitmapData SelfType;
        typedef Classes::BitmapData ClassType;
        typedef InstanceTraits::BitmapData TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::BitmapData"; }
#endif
    protected:
        BitmapData(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void InitInstance(bool extCall);
        virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        bool            IsDirty() { return (Dirty) ? Dirty = false, true : false; }
        ImageResource*  GetImageResource() const;
        bool            CreateLibraryObject(ImageResource* imgRes);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_heightGet, 
            mid_rectGet, 
            mid_transparentGet, 
            mid_widthGet, 
            mid_applyFilter, 
            mid_clone, 
            mid_colorTransform, 
            mid_compare, 
            mid_copyChannel, 
            mid_copyPixels, 
            mid_dispose, 
            mid_draw, 
            mid_fillRect, 
            mid_floodFill, 
            mid_generateFilterRect, 
            mid_getColorBoundsRect, 
            mid_getPixel, 
            mid_getPixel32, 
            mid_getPixels, 
            mid_hitTest, 
            mid_lock, 
            mid_merge, 
            mid_noise, 
            mid_paletteMap, 
            mid_perlinNoise, 
            mid_pixelDissolve, 
            mid_scroll, 
            mid_setPixel, 
            mid_setPixel32, 
            mid_setPixels, 
            mid_threshold, 
            mid_unlock, 
        };
        void heightGet(SInt32& result);
        void rectGet(Value& result);
        void transparentGet(bool& result);
        void widthGet(SInt32& result);
        void applyFilter(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, Instances::BitmapFilter* filter);
        void clone(Value& result);
        void colorTransform(Value& result, Instances::Rectangle* rect, Instances::ColorTransform* colorTransform);
        void compare(Value& result, Instances::BitmapData* otherBitmapData);
        void copyChannel(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, UInt32 sourceChannel, UInt32 destChannel);
        void copyPixels(Value& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, Instances::BitmapData* alphaBitmapData, Instances::Point* alphaPoint, bool mergeAlpha);
        void dispose(Value& result);
        void draw(Value& result, Instances::IBitmapDrawable* source, Instances::Matrix* matrix, Instances::ColorTransform* colorTransform, const ASString& blendMode, Instances::Rectangle* clipRect, bool smoothing);
        void fillRect(Value& result, Instances::Rectangle* rect, UInt32 color);
        void floodFill(Value& result, SInt32 x, SInt32 y, UInt32 color);
        void generateFilterRect(Value& result, Instances::Rectangle* sourceRect, Instances::BitmapFilter* filter);
        void getColorBoundsRect(Value& result, UInt32 mask, UInt32 color, bool findColor);
        void getPixel(UInt32& result, SInt32 x, SInt32 y);
        void getPixel32(UInt32& result, SInt32 x, SInt32 y);
        void getPixels(Value& result, Instances::Rectangle* rect);
        void hitTest(bool& result, Instances::Point* firstPoint, UInt32 firstAlphaThreshold, const Value& secondObject, Instances::Point* secondBitmapDataPoint, UInt32 secondAlphaThreshold);
        void lock(Value& result);
        void merge(Value& result, unsigned argc, const Value* const argv);
        void noise(Value& result, SInt32 randomSeed, UInt32 low, UInt32 high, UInt32 channelOptions, bool grayScale);
        void paletteMap(Value& result, unsigned argc, const Value* const argv);
        void perlinNoise(Value& result, unsigned argc, const Value* const argv);
        void pixelDissolve(SInt32& result, Instances::BitmapData* sourceBitmapData, Instances::Rectangle* sourceRect, Instances::Point* destPoint, SInt32 randomSeed, SInt32 numPixels, UInt32 fillColor);
        void scroll(Value& result, SInt32 x, SInt32 y);
        void setPixel(Value& result, SInt32 x, SInt32 y, UInt32 color);
        void setPixel32(Value& result, SInt32 x, SInt32 y, UInt32 color);
        void setPixels(Value& result, Instances::Rectangle* rect, Instances::ByteArray* inputByteArray);
        void threshold(Value& result, unsigned argc, const Value* const argv);
        void unlock(Value& result, Instances::Rectangle* changeRect);

//##protect##"instance$data"
        Ptr<ImageResource>      pImageResource;
        Ptr<Render::ImageBase>  pImage;
        unsigned                Width, Height;
        bool                    Dirty;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class BitmapData : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::BitmapData"; }
#endif
    public:
        BitmapData(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::BitmapData> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 32 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class BitmapData : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BitmapData"; }
#endif
    public:
        typedef Classes::BitmapData ClassType;

    public:
        BitmapData(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

