//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Bitmap.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Bitmap_H
#define INC_AS3_Obj_Display_Bitmap_H

#include "AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
#include "GFx/AS3/AS3_AvmBitmap.h"
#include "AS3_Obj_Display_BitmapData.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class BitmapData;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Bitmap;
}

namespace InstanceTraits
{
    class Bitmap;
}

namespace Classes
{
    class Bitmap;
}

namespace Instances
{
    class Bitmap : public Instances::DisplayObject
    {
        friend class InstanceTraits::Bitmap;
        
    public:
        typedef Bitmap SelfType;
        typedef Classes::Bitmap ClassType;
        typedef InstanceTraits::Bitmap TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Bitmap"; }
#endif
    protected:
        Bitmap(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        enum PixelSnappingType
        {
            Never,
            Always,
            Auto
        };

        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void InitInstance(bool extCall);
        virtual GFx::DisplayObject* CreateStageObject();

        PixelSnappingType String2PixelSnapping(const char* str);
    public:
        BitmapData*         GetBitmapData() const { return pBitmapData; }
        void                SetBitmapData(BitmapData* b)
        {
            Value r;
            bitmapDataSet(r, b);
        }
        void                NotifyBitmapDataChanged();
        GFx::ImageResource* GetImageResource() const;
        bool                IsSmoothed() const { return Smoothing; }
        AvmBitmap*          GetAvmBitmap() const { return static_cast<AvmBitmap*>(pDispObj.GetPtr()); }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bitmapDataGet, 
            mid_bitmapDataSet, 
            mid_pixelSnappingGet, 
            mid_pixelSnappingSet, 
            mid_smoothingGet, 
            mid_smoothingSet, 
        };
        void bitmapDataGet(Value& result);
        void bitmapDataSet(Value& result, Instances::BitmapData* value);
        void pixelSnappingGet(ASString& result);
        void pixelSnappingSet(Value& result, const ASString& value);
        void smoothingGet(bool& result);
        void smoothingSet(Value& result, bool value);

//##protect##"instance$data"
        SPtr<BitmapData>    pBitmapData;
        PixelSnappingType   PixelSnapping;
        bool                Smoothing;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Bitmap : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Bitmap"; }
#endif
    public:
        Bitmap(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Bitmap> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Bitmap : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Bitmap"; }
#endif
    public:
        typedef Classes::Bitmap ClassType;

    public:
        Bitmap(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

