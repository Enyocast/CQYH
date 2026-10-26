//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Bitmap.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Bitmap.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Display_BitmapData.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Bitmap, Instances::Bitmap::mid_bitmapDataGet, Value> TFunc_Instances_Bitmap_bitmapDataGet;
typedef ThunkFunc1<Instances::Bitmap, Instances::Bitmap::mid_bitmapDataSet, Value, Instances::BitmapData*> TFunc_Instances_Bitmap_bitmapDataSet;
typedef ThunkFunc0<Instances::Bitmap, Instances::Bitmap::mid_pixelSnappingGet, ASString> TFunc_Instances_Bitmap_pixelSnappingGet;
typedef ThunkFunc1<Instances::Bitmap, Instances::Bitmap::mid_pixelSnappingSet, Value, const ASString&> TFunc_Instances_Bitmap_pixelSnappingSet;
typedef ThunkFunc0<Instances::Bitmap, Instances::Bitmap::mid_smoothingGet, bool> TFunc_Instances_Bitmap_smoothingGet;
typedef ThunkFunc1<Instances::Bitmap, Instances::Bitmap::mid_smoothingSet, Value, bool> TFunc_Instances_Bitmap_smoothingSet;

template <> const TFunc_Instances_Bitmap_bitmapDataGet::TMethod TFunc_Instances_Bitmap_bitmapDataGet::Method = &Instances::Bitmap::bitmapDataGet;
template <> const TFunc_Instances_Bitmap_bitmapDataSet::TMethod TFunc_Instances_Bitmap_bitmapDataSet::Method = &Instances::Bitmap::bitmapDataSet;
template <> const TFunc_Instances_Bitmap_pixelSnappingGet::TMethod TFunc_Instances_Bitmap_pixelSnappingGet::Method = &Instances::Bitmap::pixelSnappingGet;
template <> const TFunc_Instances_Bitmap_pixelSnappingSet::TMethod TFunc_Instances_Bitmap_pixelSnappingSet::Method = &Instances::Bitmap::pixelSnappingSet;
template <> const TFunc_Instances_Bitmap_smoothingGet::TMethod TFunc_Instances_Bitmap_smoothingGet::Method = &Instances::Bitmap::smoothingGet;
template <> const TFunc_Instances_Bitmap_smoothingSet::TMethod TFunc_Instances_Bitmap_smoothingSet::Method = &Instances::Bitmap::smoothingSet;

namespace Instances
{
    Bitmap::Bitmap(InstanceTraits::Traits& t)
    : Instances::DisplayObject(t)
//##protect##"instance::Bitmap::Bitmap()$data"
    , PixelSnapping(Never)
    , Smoothing(GFX_AS3_SMOOTH_BMP_BY_DEFAULT)
//##protect##"instance::Bitmap::Bitmap()$data"
    {
//##protect##"instance::Bitmap::Bitmap()$code"
//##protect##"instance::Bitmap::Bitmap()$code"
    }

    void Bitmap::bitmapDataGet(Value& result)
    {
//##protect##"instance::Bitmap::bitmapDataGet()"
        SF_UNUSED1(result);
        result = Value(pBitmapData);
//##protect##"instance::Bitmap::bitmapDataGet()"
    }
    void Bitmap::bitmapDataSet(Value& result, Instances::BitmapData* value)
    {
//##protect##"instance::Bitmap::bitmapDataSet()"
        SF_UNUSED2(result, value);
        pBitmapData = value;
        NotifyBitmapDataChanged();
//##protect##"instance::Bitmap::bitmapDataSet()"
    }
    void Bitmap::pixelSnappingGet(ASString& result)
    {
//##protect##"instance::Bitmap::pixelSnappingGet()"
        SF_UNUSED1(result);
        switch (PixelSnapping)
        {
        case Never:     result = "never"; break;
        case Always:    result = "always"; break;
        case Auto:      result = "auto"; break;
        default: SF_ASSERT(0);
        }
//##protect##"instance::Bitmap::pixelSnappingGet()"
    }
    void Bitmap::pixelSnappingSet(Value& result, const ASString& value)
    {
//##protect##"instance::Bitmap::pixelSnappingSet()"
        SF_UNUSED2(result, value);
        PixelSnapping = String2PixelSnapping(value.ToCStr());
        NotifyBitmapDataChanged();
//##protect##"instance::Bitmap::pixelSnappingSet()"
    }
    void Bitmap::smoothingGet(bool& result)
    {
//##protect##"instance::Bitmap::smoothingGet()"
        SF_UNUSED1(result);
        result = Smoothing;
//##protect##"instance::Bitmap::smoothingGet()"
    }
    void Bitmap::smoothingSet(Value& result, bool value)
    {
//##protect##"instance::Bitmap::smoothingSet()"
        SF_UNUSED2(result, value);
        Smoothing = value;
        NotifyBitmapDataChanged();
//##protect##"instance::Bitmap::smoothingSet()"
    }

//##protect##"instance$methods"
    void Bitmap::NotifyBitmapDataChanged()
    {
        if (pDispObj)
        {
            GetAvmBitmap()->RecreateRenderNode();
        }
    }

    GFx::ImageResource* Bitmap::GetImageResource() const
    {
        if (pBitmapData)
            return pBitmapData->GetImageResource();
        return NULL;
    }

    void Bitmap::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        DisplayObject::ForEachChild_GC(prcc, op);
        AS3::ForEachChild_GC<BitmapData, Mem_Stat>(prcc, pBitmapData, op SF_DEBUG_ARG(*this));
    }

    void Bitmap::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1)
        {
            if (GetVM().IsOfType(argv[0], "flash.display.BitmapData"))
            {
                pBitmapData = static_cast<BitmapData*>(argv[0].GetObject());
            }
            if (argc >= 2)
            {
                const Value& v = argv[1];
                ASString str = GetVM().GetStringManager().CreateEmptyString();

                if (!v.Convert2String(str))
                    return;

                PixelSnapping = String2PixelSnapping(str.ToCStr());

                if (argc >= 3)
                {
                    Smoothing = argv[2].Convert2Boolean();
                }
            }
            NotifyBitmapDataChanged();
        }
    }

    void Bitmap::InitInstance(bool extCall)
    {
        if (!extCall)
        {
            // create stage display object if the movieclip was created by
            // "new".
            Bitmap::CreateStageObject();
            SF_ASSERT(pDispObj);
        }
    }
    GFx::DisplayObject* Bitmap::CreateStageObject()
    {
        // CreateStageObject is called when the object is instantiated by
        // ActionScript 'new' operator. There are several different scenarios possible:
        //  1) There are no library symbols linked to the bitmap (new Bitmap):
        //      no BitmapData is created.
        //  2) The bitmap was put into a library and linked with a class:
        //      in this case the class is linked to a BitmapData, not to a bitmap itself; therefore
        //      Bitmap will be created as 'new Bitmap(new MyBitmapData())' (see 1st item)
        //  3) The bitmap was embedded via [Embed] directive with assigned class. In this case
        //      the class is linked to the actual Bitmap, so we need to create a proper ActionScript
        //      class and a proper BitmapData.
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

                if (!FindLibarySymbol(&ccinfo, pdefImpl))
                {
                    // not found... Let check if there are symbols linked to the same class in other
                    // moviedefs. Seems like Flash does it.
                    if (!proot->FindLibrarySymbolInAllABCs(this, &ccinfo))
                    {
                        ccinfo.pCharDef = NULL;
                        ccinfo.pResource = NULL;
                    }
                }

                pDispObj = *static_cast<GFx::DisplayObject*>(proot->GetASSupport()->CreateCharacterInstance(
                    proot->GetMovieImpl(), ccinfo, NULL, 
                    ResourceId(), CharacterDef::Bitmap));
                ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);

                if (ccinfo.pResource && ccinfo.pResource->GetResourceType() == Resource::RT_Image)
                {
                    // create a BitmapData right here if Resource was found.

                    Value params[] = { Value(0.f), Value(0.f) };
                    SPtr<Instances::BitmapData> bmpData;
                    asvm.ConstructBuiltinObject(bmpData, "flash.display.BitmapData", 2, params);

                    bmpData->CreateLibraryObject(static_cast<ImageResource*>(ccinfo.pResource));
                    SetBitmapData(bmpData);
                }
            }
        }
        return pDispObj;
    }

    Bitmap::PixelSnappingType Bitmap::String2PixelSnapping(const char* str)
    {
        if (SFstrcmp(str, "never") == 0)
            return Never;
        else if (SFstrcmp(str, "always") == 0)
            return Always;
        else if (SFstrcmp(str, "auto") == 0)
            return Auto;
        else
        {
            GetVM().ThrowArgumentError(VM::Error(VM::eInvalidEnumError, GetVM() SF_DEBUG_ARG("pixelSnapping")));
        }
        return Never;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Bitmap::ti[Bitmap::ThunkInfoNum] = {
        {TFunc_Instances_Bitmap_bitmapDataGet::Func, &BitmapDataCI, "bitmapData", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Bitmap_bitmapDataSet::Func, NULL, "bitmapData", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Bitmap_pixelSnappingGet::Func, &StringCI, "pixelSnapping", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Bitmap_pixelSnappingSet::Func, NULL, "pixelSnapping", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Bitmap_smoothingGet::Func, &BooleanCI, "smoothing", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Bitmap_smoothingSet::Func, NULL, "smoothing", NULL, CT_Set, 1, 1},
    };

    Bitmap::Bitmap(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Bitmap::Bitmap()"
        SetTraitsType(Traits_Bitmap);
//##protect##"InstanceTraits::Bitmap::Bitmap()"
        SetMemSize(sizeof(Instances::Bitmap));

    }

    Pickable<Instances::Bitmap> Bitmap::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Bitmap>(new(t.Alloc()) Instances::Bitmap(t));
    }

    void Bitmap::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Bitmap::Bitmap(VM& vm)
    : Traits(vm, BitmapCI)
    {
//##protect##"ClassTraits::Bitmap::Bitmap()"
        SetTraitsType(Traits_Bitmap);
//##protect##"ClassTraits::Bitmap::Bitmap()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Bitmap(vm, BitmapCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Bitmap::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Bitmap(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo BitmapCI = {
    ClassInfo::CompileTime,
    "Bitmap", "flash.display", &DisplayObjectCI,
    ClassTraits::Bitmap::MakeClassTraits,
    0,
    0,
    InstanceTraits::Bitmap::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Bitmap::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

