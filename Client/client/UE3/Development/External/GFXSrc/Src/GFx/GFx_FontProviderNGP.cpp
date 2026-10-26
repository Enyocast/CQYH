/**************************************************************************

Filename    :   GFx_FontProviderNGP.cpp
Content     :
Created     :   2011
Authors     :   Maxim Shemanarev

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

----------------------------------------------------------------------
----The code of these classes was taken from the Anti-Grain Geometry
Project and modified for the use by Scaleform. 
Permission to use without restrictions is hereby granted to 
Scaleform Corporation by the author of Anti-Grain Geometry Project.
See http://antigtain.com for details.
**************************************************************************/

#include "GFx/GFx_FontProviderNGP.h"
#include "Render/Render_Font.h"
#include "Kernel/SF_HeapNew.h"

namespace Scaleform { namespace GFx {


FontProviderNGP::FontProviderNGP(unsigned numUserFontEntries, int firstId)
: FontProvider(Ptr<Render::FontProviderNGP>(*SF_NEW Render::FontProviderNGP(numUserFontEntries, firstId)).GetPtr())
{
}

FontProviderNGP::FontProviderNGP(MemoryHeap* heap, unsigned numUserFontEntries, int firstId)
: FontProvider(Ptr<Render::FontProviderNGP>(*SF_HEAP_NEW(heap) Render::FontProviderNGP(numUserFontEntries, firstId)).GetPtr())
{
}

Render::FontProviderNGP* FontProviderNGP::getFontProvider()
{
    return static_cast<Render::FontProviderNGP*>(pFontProvider.GetPtr());
}

void FontProviderNGP::MapSystemFont(const char* fontName, unsigned fontFlags, unsigned fontType, 
                                    Render::NGP_FontStreamType fontStream,
                                    float metricsScale, float advanceScale)
{
    getFontProvider()->MapSystemFont(fontName, fontFlags, fontType, fontStream,
                                     metricsScale, advanceScale);
}

void FontProviderNGP::MapFontToFile(const char* fontName, unsigned fontFlags, const char* fileName, 
                                    Render::NGP_FontStreamType fontStream,
                                    float metricsScale, float advanceScale)
{
    getFontProvider()->MapFontToFile(fontName, fontFlags, fileName, fontStream,
                                     metricsScale, advanceScale);
}

void FontProviderNGP::MapFontToMemory(const char* fontName, unsigned fontFlags, 
                                      const char* fontData, unsigned dataSize, 
                                      float metricsScale, float advanceScale)
{
    getFontProvider()->MapFontToMemory(fontName, fontFlags, fontData, dataSize, 
                                       metricsScale, advanceScale);
}

void FontProviderNGP::LoadFontNames(StringHash<String>& fontnames)
{
    getFontProvider()->LoadFontNames(fontnames);
}

}} //namespace Scaleform { namespace GFx {
