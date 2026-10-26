/**************************************************************************

PublicHeader:   GFx_FontProviderNGP.h
Filename    :   GFx_FontProviderNGP.h
Content     :
Created     :   2011
Authors     :   Maxim Shemanarev

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_GFX_FontProviderNGP_H
#define INC_SF_GFX_FontProviderNGP_H

#include "Render/FontProvider/Render_FontProviderNGP.h"
#include "GFx/GFx_Loader.h"

namespace Scaleform { namespace GFx {

typedef Render::ExternalFontNGP ExternalFontNGP;

//------------------------------------------------------------------------
// External font provider that supports libpvf. This provider has a number 
// of restriction due to the fact that there is no access to vector glyph shapes.
// 
// So that, the maximal glyph height cannot exceed GlyphCacheParams.MaxSlotHeight. 
// 
// The libpvf uses strange units, probably to be compatible with the older libpgf, 
// which makes it difficult to conform with the Flash font units with its traditional 
// 1024x1024 EM square. 
// 
// The only reasonable way is to tune 2 scaling coefficients when mapping the font:
// metricsScale = 1.5f, advanceScale = 0.5f
// These coefficients correspond well with the TrueType fonts opened by scePvfOpenUserFile, 
// but may need to be adjusted when using system fonts.
// The greater metricsScale is the lower the text will be positioned.
// The greater advanceScale is the bigger letter spacing will appear.
// 
// An example of mapping the TrueType fonts:
//
// String arial = String(GetDefaultFilePath())   + "arial.ttf";
// String times = String(GetDefaultFilePath())   + "times.ttf";
// String georgia = String(GetDefaultFilePath()) + "georgia.ttf";
// Ptr<GFx::FontProviderNGP> fontProvider = *new GFx::FontProviderNGP(8, 0);
//
// fontProvider->MapFontToFile("Arial", 0, arial);
// fontProvider->MapFontToFile("Times New Roman", 0, times);
// fontProvider->MapFontToFile("Georgia", 0, georgia);
//
// mLoader.SetFontProvider(fontProvider);
//
// The ld requires -lScePvf_stub
//------------------------------------------------------------------------

class FontProviderNGP : public FontProvider
{
    typedef Render::Font Font;
    Render::FontProviderNGP* getFontProvider();

public:
    FontProviderNGP(unsigned numUserFontEntries=8, int firstId=0);
    FontProviderNGP(MemoryHeap* heap, unsigned numUserFontEntries=8, int firstId=0);

    void MapSystemFont(const char* fontName, unsigned fontFlags, unsigned fontType, 
                       Render::NGP_FontStreamType fontStream = Render::NGP_FontStream_File,
                       float metricsScale = 1.5f, float advanceScale = 0.5f);

    void MapFontToFile(const char* fontName, unsigned fontFlags, const char* fileName, 
                       Render::NGP_FontStreamType fontStream = Render::NGP_FontStream_File,
                       float metricsScale = 1.5f, float advanceScale = 0.5f);

    void MapFontToMemory(const char* fontName, unsigned fontFlags, 
                         const char* fontData, unsigned dataSize, 
                         float metricsScale = 1.5f, float advanceScale = 0.5f);

    virtual void     LoadFontNames(StringHash<String>& fontnames);
};

}} // namespace Scaleform { namespace GFx {

#endif
