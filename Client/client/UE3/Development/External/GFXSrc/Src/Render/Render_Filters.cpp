/**************************************************************************

Filename    :   Render_Filters.cpp
Content     :   Filter and FilterSet implementations.
Created     :   May 18, 2011
Authors     :   Michael Antonov

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_Filters.h"
#include "Kernel/SF_HeapNew.h"

namespace Scaleform { namespace Render {

//--------------------------------------------------------------------
// ***** BlurFilter
Filter* BlurFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) BlurFilter(Params);
}

bool BlurFilter::IsContributing() const
{
    return (Params.BlurX > 20 || Params.BlurY > 20);
}

//--------------------------------------------------------------------
// ***** ShadowFilter
Filter* ShadowFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) ShadowFilter(Params, Angle, TwipsToPixels(Distance));
}

bool ShadowFilter::IsContributing() const
{
    return Params.Colors[0].GetAlpha() > 0;
}

//--------------------------------------------------------------------
// ***** GlowFilter
Filter* GlowFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) GlowFilter(Params);
}

bool GlowFilter::IsContributing() const
{
    return Params.Colors[0].GetAlpha() > 0;
}

//--------------------------------------------------------------------
// ***** BevelFilter
Filter* BevelFilter::Clone(MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);
    return SF_HEAP_NEW(heap) BevelFilter(Params, Angle, TwipsToPixels(Distance));
}

bool BevelFilter::IsContributing() const
{
    return Params.Colors[0].GetAlpha() > 0 || 
           Params.Colors[1].GetAlpha() > 0;
}

//--------------------------------------------------------------------
// ***** ColorMatrixFilter

static float ColorMatrix_Identity[20] =
{
    1.0f, 0.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 0.0f
};

ColorMatrixFilter::ColorMatrixFilter() : Filter(Filter_ColorMatrix)
{
    memcpy(MatrixData, ColorMatrix_Identity, sizeof(MatrixData));
}
ColorMatrixFilter::~ColorMatrixFilter()
{
}

bool ColorMatrixFilter::IsContributing() const
{
    return memcmp( MatrixData, ColorMatrix_Identity, sizeof(ColorMatrix_Identity)) != 0;
}

Filter* ColorMatrixFilter::Clone(MemoryHeap* heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);

    ColorMatrixFilter* newFilter = SF_HEAP_NEW(heap) ColorMatrixFilter();
    if (newFilter)
    {
        memcpy(newFilter->MatrixData, MatrixData, sizeof(MatrixData));
    }
    return newFilter;
}


//--------------------------------------------------------------------
// ***** FilterSet

FilterSet::FilterSet(Filter* filter)
    : Frozen(false)
{
    if (filter)
        AddFilter(filter);
}
FilterSet::~FilterSet()
{
}

void FilterSet::Freeze()
{
    if (!Frozen)
    {
        for (UPInt i=0; i<Filters.GetSize(); i++)
            Filters[i]->Freeze();
        Frozen = true;
    }
}

void FilterSet::RemoveFilter(Filter* filter)
{
    SF_ASSERT(!IsFrozen());
    for (UPInt i=0; i<Filters.GetSize(); i++)
    {
        if (Filters[i] == filter)
        {
            Filters.RemoveAt(i);
            i--;
        }
    }
}

FilterSet* FilterSet::Clone(bool deepCopy, MemoryHeap *heap) const
{
    if (!heap)
        heap = Memory::GetHeapByAddress(this);

    FilterSet* newSet = SF_HEAP_NEW(heap) FilterSet;
    if (!newSet)
        return 0;

    for (UPInt i=0; i< Filters.GetSize(); i++)
    {
        if (deepCopy)
        {
            Ptr<Filter> newFilter = *Filters[i]->Clone(heap);
            newSet->AddFilter(newFilter);
        }
        else
        {
            newSet->AddFilter(Filters[i]);
        }
    }

    return newSet;
}

bool FilterSet::IsContributing() const
{
    unsigned f;
    for (f = 0; f < Filters.GetSize(); ++f )
    {
        const Filter* filter = Filters[f];
        if ( filter && filter->IsContributing() )
            return true;
    }
    return false;
}

}} // Scaleform::Render
