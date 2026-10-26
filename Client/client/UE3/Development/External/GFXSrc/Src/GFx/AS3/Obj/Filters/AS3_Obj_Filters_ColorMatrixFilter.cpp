//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_ColorMatrixFilter.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Filters_ColorMatrixFilter.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::ColorMatrixFilter, Instances::ColorMatrixFilter::mid_matrixGet, Value> TFunc_Instances_ColorMatrixFilter_matrixGet;
typedef ThunkFunc1<Instances::ColorMatrixFilter, Instances::ColorMatrixFilter::mid_matrixSet, Value, Instances::Array*> TFunc_Instances_ColorMatrixFilter_matrixSet;
typedef ThunkFunc0<Instances::ColorMatrixFilter, Instances::ColorMatrixFilter::mid_clone, Value> TFunc_Instances_ColorMatrixFilter_clone;

template <> const TFunc_Instances_ColorMatrixFilter_matrixGet::TMethod TFunc_Instances_ColorMatrixFilter_matrixGet::Method = &Instances::ColorMatrixFilter::matrixGet;
template <> const TFunc_Instances_ColorMatrixFilter_matrixSet::TMethod TFunc_Instances_ColorMatrixFilter_matrixSet::Method = &Instances::ColorMatrixFilter::matrixSet;
template <> const TFunc_Instances_ColorMatrixFilter_clone::TMethod TFunc_Instances_ColorMatrixFilter_clone::Method = &Instances::ColorMatrixFilter::clone;

namespace Instances
{
    ColorMatrixFilter::ColorMatrixFilter(InstanceTraits::Traits& t)
    : Instances::BitmapFilter(t)
//##protect##"instance::ColorMatrixFilter::ColorMatrixFilter()$data"
//##protect##"instance::ColorMatrixFilter::ColorMatrixFilter()$data"
    {
//##protect##"instance::ColorMatrixFilter::ColorMatrixFilter()$code"
        FilterData = *SF_NEW Render::ColorMatrixFilter();
//##protect##"instance::ColorMatrixFilter::ColorMatrixFilter()$code"
    }

    void ColorMatrixFilter::matrixGet(Value& result)
    {
//##protect##"instance::ColorMatrixFilter::matrixGet()"
        SPtr<Instances::Array> asArray = GetVM().MakeArray();
        asArray->Resize(20);
        const Render::ColorMatrixFilter* filterData = GetColorMatrixFilterData();
        for ( unsigned i = 0; i < 20; i++ )
        {
            Value v;

            // Require a conversion, because the render stores the matrix internally with
            // the multiply matrix first, and then the addition row.
            if ( i%5 == 0 && i != 0 )
                v.SetNumber((Value::Number)(*filterData)[16+i/5]);
            else
                v.SetNumber((Value::Number)(*filterData)[i/5*4+i%5]);
            asArray->Set(i, v);
        }
        result = asArray;
//##protect##"instance::ColorMatrixFilter::matrixGet()"
    }
    void ColorMatrixFilter::matrixSet(Value& result, Instances::Array* value)
    {
//##protect##"instance::ColorMatrixFilter::matrixSet()"
        if ( value == 0 )
            return;
        SF_UNUSED(result);
        Render::ColorMatrixFilter* filterData = GetColorMatrixFilterData();
        for ( unsigned i = 0; i < value->GetSize(); ++i)
        {
            Value::Number n;
            if ( !value->At(i).Convert2Number(n) )
                return;

            if ( i >= 20 )
                continue;

            // Require a conversion, because the render stores the matrix internally with
            // the multiply matrix first, and then the addition row.
            if ( i%5 == 4 )
                (*filterData)[16+i/5] = (float)n;
            else
                (*filterData)[i/5*4+i%5] = (float)n;
        }
//##protect##"instance::ColorMatrixFilter::matrixSet()"
    }
    void ColorMatrixFilter::clone(Value& result)
    {
//##protect##"instance::ColorMatrixFilter::clone()"

        InstanceTraits::ColorMatrixFilter & itr = static_cast<InstanceTraits::ColorMatrixFilter&>(GetTraits());
        Pickable<ColorMatrixFilter> r = itr.MakeInstance(itr);

        // Not performance efficient way of cloning a matrix.
        Value matrix, tempResult;
        matrixGet(matrix);
        // matrix IS an ARRAY here.
        r->matrixSet(tempResult, static_cast<Instances::Array*>(matrix.GetObject()));
        
        result = r;
//##protect##"instance::ColorMatrixFilter::clone()"
    }

//##protect##"instance$methods"
    void ColorMatrixFilter::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0 && IsValidArrayObject(argv[0]))
        {
            Value result;
            matrixSet(result, static_cast<Instances::Array*>(argv[0].GetObject()));
        }
    }

    bool ColorMatrixFilter::IsValidArrayObject(const Value& v) const
    {
        bool result = false;

        if (v.IsObject() && v.GetObject())
        {
            Traits& tr = v.GetObject()->GetTraits();

            if (tr.GetTraitsType() == Traits_Array && tr.IsInstanceTraits())
                result = true;
        }

        return result;
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ColorMatrixFilter::ti[ColorMatrixFilter::ThunkInfoNum] = {
        {TFunc_Instances_ColorMatrixFilter_matrixGet::Func, &ArrayCI, "matrix", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ColorMatrixFilter_matrixSet::Func, NULL, "matrix", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ColorMatrixFilter_clone::Func, &BitmapFilterCI, "clone", NULL, CT_Method, 0, 0},
    };

    ColorMatrixFilter::ColorMatrixFilter(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ColorMatrixFilter::ColorMatrixFilter()"
//##protect##"InstanceTraits::ColorMatrixFilter::ColorMatrixFilter()"
        SetMemSize(sizeof(Instances::ColorMatrixFilter));

    }

    Pickable<Instances::ColorMatrixFilter> ColorMatrixFilter::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ColorMatrixFilter>(new(t.Alloc()) Instances::ColorMatrixFilter(t));
    }

    void ColorMatrixFilter::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    ColorMatrixFilter::ColorMatrixFilter(VM& vm)
    : Traits(vm, ColorMatrixFilterCI)
    {
//##protect##"ClassTraits::ColorMatrixFilter::ColorMatrixFilter()"
//##protect##"ClassTraits::ColorMatrixFilter::ColorMatrixFilter()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ColorMatrixFilter(vm, ColorMatrixFilterCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ColorMatrixFilter::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ColorMatrixFilter(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ColorMatrixFilterCI = {
    ClassInfo::CompileTime,
    "ColorMatrixFilter", "flash.filters", &BitmapFilterCI,
    ClassTraits::ColorMatrixFilter::MakeClassTraits,
    0,
    0,
    InstanceTraits::ColorMatrixFilter::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::ColorMatrixFilter::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

