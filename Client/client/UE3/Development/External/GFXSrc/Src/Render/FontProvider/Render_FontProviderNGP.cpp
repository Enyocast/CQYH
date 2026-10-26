/**************************************************************************

Filename    :   Render_FontProviderNGP.cpp
Content     :   
Created     :   2011
Authors     :   Maxim Shemanarev

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "Render_FontProviderNGP.h"
#include "Kernel/SF_Std.h"

#include "Kernel/SF_HeapNew.h"
#include "Kernel/SF_Debug.h"

namespace Scaleform { namespace Render {

static const float NGP_ReferenceFontSize = 16.0f;

//------------------------------------------------------------------------
ExternalFontNGP::ExternalFontNGP(FontProviderNGP* provider, ScePvf_t_fontId library, const FontInfoNGP& fontInfo) :
    Font(fontInfo.FontFlags),
    pFontProvider(provider),
    Name(fontInfo.FontName),
    Valid(false),
    LastFontHeight(0),
    MetricsScale(fontInfo.MetricsScale),
    AdvanceScale(fontInfo.AdvanceScale)
{
    ScePvf_t_error errorCode;
    ScePvfDataAccessMode fontStream = (fontInfo.FontStream == NGP_FontStream_File) ? 
                                       SCE_PVF_FILEBASEDSTREAM : SCE_PVF_MEMORYBASEDSTREAM;

    if (fontInfo.FontData && fontInfo.FontDataSize)
    {
        FontId = scePvfOpenUserMemory(library, (char*)fontInfo.FontData, fontInfo.FontDataSize, &errorCode);
        if (errorCode)
            return;
    }
    else
    if (!fontInfo.FileName.IsEmpty())
    {
        char* name = (char*)fontInfo.FileName.ToCStr();
        FontId = scePvfOpenUserFile(library, name, fontStream, &errorCode);
        if (errorCode)
            return;
    }
    else
    {
        FontId = scePvfOpen(library, fontInfo.FontType, fontStream, &errorCode );
        if (errorCode)
            return;
    }

    ScePvf_t_fontInfo scefontInfo;
    errorCode = scePvfGetFontInfo(FontId, &scefontInfo);
    if (errorCode)
    {
        scePvfClose(FontId);
        return;
    }

    float ascent  =  float(scefontInfo.maxIGlyphMetrics.ascender64) * MetricsScale;
    float descent = -float(scefontInfo.maxIGlyphMetrics.descender64) * MetricsScale;
    float height  =  float(scefontInfo.maxIGlyphMetrics.height64) * MetricsScale;

    SetFontMetrics(height - ascent + descent, ascent, descent);

    Valid = true;
}

//------------------------------------------------------------------------
ExternalFontNGP::~ExternalFontNGP()
{
    if (!IsValid())
        return;

    scePvfClose(FontId);
}




//------------------------------------------------------------------------
int ExternalFontNGP::GetGlyphIndex(UInt16 code)
{
    if (!IsValid() ) 
        return -1;

    ScePvf_t_error error_code;
    ScePvf_t_charInfo charInfo;
    ScePvf_t_irect rect;

    const unsigned* indexPtr = CodeTable.Get(code);
    if( indexPtr )
        return *indexPtr;

    if(LastFontHeight != NGP_ReferenceFontSize)
    {
        //scePvfSetCharSize is expensive. Avoid calling it often.
        error_code = scePvfSetCharSize(FontId, NGP_ReferenceFontSize*2, NGP_ReferenceFontSize*2);
        LastFontHeight = NGP_ReferenceFontSize;
    }

    error_code = scePvfGetCharInfo(FontId, code, &charInfo);

    GlyphType glyph;
    glyph.Code      =  code;
    glyph.Advance   =  float(charInfo.glyphMetrics.horizontalAdvance64) * AdvanceScale;
    glyph.Bounds.x1 =  charInfo.glyphMetrics.horizontalBearingX64 * AdvanceScale;
    glyph.Bounds.y1 = -charInfo.glyphMetrics.horizontalBearingY64 * AdvanceScale;
    glyph.Bounds.x2 =  glyph.Bounds.x1 + charInfo.glyphMetrics.width64 * AdvanceScale;
    glyph.Bounds.y2 =  glyph.Bounds.y1 + charInfo.glyphMetrics.height64 * AdvanceScale;

    Glyphs.PushBackAlt(glyph);
    CodeTable.Add(code, (unsigned)Glyphs.GetSize()-1);

    return (unsigned)Glyphs.GetSize()-1;
}

//------------------------------------------------------------------------
bool ExternalFontNGP::IsHintedVectorGlyph(unsigned glyphIndex, unsigned glyphSize) const
{
    SF_UNUSED2(glyphIndex, glyphSize);
    return false;
}

//------------------------------------------------------------------------
bool ExternalFontNGP::IsHintedRasterGlyph(unsigned glyphIndex, unsigned glyphSize) const
{
    SF_UNUSED2(glyphIndex, glyphSize);
    return true;
}


bool ExternalFontNGP::GetTemporaryGlyphShape(unsigned glyphIndex, unsigned hintedSize, GlyphShape* shape)
{
    SF_UNUSED3(glyphIndex, hintedSize, shape);
    return false;
}

//------------------------------------------------------------------------
bool ExternalFontNGP::GetGlyphRaster(unsigned glyphIndex, unsigned glyphSize, GlyphRaster* raster)
{
    if( !IsValid() )
        return NULL;

    ScePvf_t_error errorCode;
    GlyphType& glyph = Glyphs[glyphIndex];

    if(LastFontHeight != float(glyphSize))
    {
        errorCode = scePvfSetCharSize ( FontId, float(glyphSize), float(glyphSize));
        LastFontHeight = float(glyphSize);
    }

    int pad=0;
    ScePvf_t_charInfo charInfo;
    errorCode = scePvfGetCharInfo(FontId, glyph.Code, &charInfo);
    UInt32 w = (charInfo.glyphMetrics.width64 + 63) / 64 + pad*2;
    UInt32 h = (charInfo.glyphMetrics.height64 + 63) / 64 + pad*2;

    raster->Width   = w;
    raster->Height  = h;
    raster->OriginX = -charInfo.glyphMetrics.horizontalBearingX64 / 64 + pad;
    raster->OriginY =  charInfo.glyphMetrics.ascender64 / 64 + pad;
    raster->Raster.Resize(raster->Width * raster->Height);
    memset(&raster->Raster[0], 0, raster->Width * raster->Height);

    ScePvf_t_userImageBufferRec glyphImage;

    glyphImage.pixelFormat  = SCE_PVF_USERIMAGE_DIRECT8;
    glyphImage.rect.width   = w;
    glyphImage.rect.height  = h;
    glyphImage.bytesPerLine = w;
    glyphImage.reserved     = 0;
    glyphImage.buffer       = &raster->Raster[pad*w+pad];
    glyphImage.xPos64       = -charInfo.glyphMetrics.horizontalBearingX64;
    glyphImage.yPos64       =  charInfo.glyphMetrics.ascender64 + pad*64 + 64;

    errorCode = scePvfGetCharGlyphImage(FontId, glyph.Code, &glyphImage);
    return raster;
}

//------------------------------------------------------------------------
float ExternalFontNGP::GetAdvance(unsigned glyphIndex) const
{
    if(IsMissingGlyph(glyphIndex))
        return GetNominalGlyphWidth();

    return Glyphs[glyphIndex].Advance;
}

//------------------------------------------------------------------------
float ExternalFontNGP::GetKerningAdjustment(unsigned lastCode, unsigned thisCode) const
{
    SF_UNUSED2(lastCode, thisCode);
    return 0.0f;
}

//------------------------------------------------------------------------
float ExternalFontNGP::GetGlyphWidth(unsigned glyphIndex) const
{
    if(IsMissingGlyph(glyphIndex))
        return GetNominalGlyphWidth();

    const RectF& r = Glyphs[glyphIndex].Bounds;

    return r.Width();
}

//------------------------------------------------------------------------
float ExternalFontNGP::GetGlyphHeight(unsigned glyphIndex) const
{
    if(IsMissingGlyph(glyphIndex))
        return GetNominalGlyphHeight();

    const RectF& r = Glyphs[glyphIndex].Bounds;
    return r.Height();
}

//------------------------------------------------------------------------
RectF& ExternalFontNGP::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
{
    if(IsMissingGlyph(glyphIndex))
        prect->SetRect( GetNominalGlyphWidth(), GetNominalGlyphHeight() );
    else
        *prect = Glyphs[glyphIndex].Bounds;
    return *prect;
}




















//========================================================================
// FontProviderNGP
//========================================================================


// static callbacks
//------------------------------------------------------------------------
static ScePvf_t_pointer FontProviderNGP_malloc( ScePvf_t_pointer pData, ScePvf_t_u32 size )
{
    SF_UNUSED( pData );
    return SF_ALLOC( size, Stat_Default_Mem );
}

//------------------------------------------------------------------------
static ScePvf_t_pointer FontProviderNGP_realloc( ScePvf_t_pointer pData, ScePvf_t_pointer pOldData, ScePvf_t_u32 size )
{
    SF_UNUSED( pData );
    return SF_REALLOC( pOldData, size, Stat_Default_Mem );
}

//------------------------------------------------------------------------
static void FontProviderNGP_free( ScePvf_t_pointer pData, ScePvf_t_pointer pObj )
{
    SF_UNUSED( pData );
    SF_FREE( pObj );
}


//------------------------------------------------------------------------
FontProviderNGP::FontProviderNGP(unsigned numUserFontEntries, int firstId) :
    Valid(false),
    LibId(0),
    NextFontId(firstId)
{
    ScePvf_t_error errorCode;

    // setup params
    FontParams.userData    = NULL;
    FontParams.maxNumFonts = numUserFontEntries;
    FontParams.cache       = NULL;
    FontParams.reserved    = 0;
    FontParams.allocFunc   = FontProviderNGP_malloc;
    FontParams.reallocFunc = FontProviderNGP_realloc;
    FontParams.freeFunc    = FontProviderNGP_free;

    // Init libpvf instance
    LibId = scePvfNewLib( &FontParams, &errorCode );
    Valid = true;

    float res = 72.0f;

    // set em square value
    errorCode = scePvfSetEM( LibId, 72.0f / (10.125f * res) );

    // set resolution
    errorCode = scePvfSetResolution(LibId, res, res);
}

//------------------------------------------------------------------------
FontProviderNGP::~FontProviderNGP()
{
    if( !IsValid() ) 
        return;

    ScePvf_t_error errorCode;

    // Destroy font library instance
    errorCode = scePvfDoneLib(LibId);
}

//------------------------------------------------------------------------
void FontProviderNGP::MapSystemFont(const char* fontName, unsigned fontFlags, unsigned fontType, 
                                    NGP_FontStreamType fontStream,
                                    float metricsScale, float advanceScale)
{
    // Mask flags to be safe.
    fontFlags &= Font::FF_CreateFont_Mask;
    fontFlags |= Font::FF_DeviceFont | Font::FF_NativeHinting;

    FontInfoNGP font;
    font.FontName     = fontName;
    font.FontFlags    = fontFlags;
    font.FontData     = 0;
    font.FontDataSize = 0;
    font.UniqueId     = 0;
    font.FontType     = fontType;
    font.FontStream   = fontStream;
    font.MetricsScale = metricsScale;
    font.AdvanceScale = advanceScale;
    Fonts.PushBackAlt(font);
}

//------------------------------------------------------------------------
void FontProviderNGP::MapFontToFile(const char* fontName, unsigned fontFlags, const char* fileName, 
                                    NGP_FontStreamType fontStream,
                                    float metricsScale, float advanceScale)
{
    // Mask flags to be safe.
    fontFlags &= Font::FF_CreateFont_Mask;
    fontFlags |= Font::FF_DeviceFont | Font::FF_NativeHinting;

    FontInfoNGP font;
    font.FontName     = fontName;
    font.FontFlags    = fontFlags;
    font.FileName     = fileName;
    font.FontData     = 0;
    font.FontDataSize = 0;
    font.UniqueId     = NextFontId++;
    font.FontType     = ~0U;
    font.FontStream   = fontStream;
    font.MetricsScale = metricsScale;
    font.AdvanceScale = advanceScale;
    Fonts.PushBackAlt(font);
}

//------------------------------------------------------------------------
void FontProviderNGP::MapFontToMemory(const char* fontName, unsigned fontFlags, 
                                      const char* fontData, unsigned dataSize, 
                                      float metricsScale, float advanceScale)
{
    // Mask flags to be safe.
    fontFlags &= Font::FF_CreateFont_Mask;
    fontFlags |= Font::FF_DeviceFont | Font::FF_NativeHinting;

    FontInfoNGP font;
    font.FontName     = fontName;
    font.FontFlags    = fontFlags;
    font.FontData     = fontData;
    font.FontDataSize = dataSize;
    font.UniqueId     = NextFontId++;
    font.FontType     = ~0U;
    font.FontStream   = NGP_FontStream_Memory;
    font.MetricsScale = metricsScale;
    font.AdvanceScale = advanceScale;
    Fonts.PushBackAlt(font);
}

//------------------------------------------------------------------------
Font* FontProviderNGP::CreateFont(const char* name, unsigned fontFlags)
{
    if( !IsValid() )
        return NULL;

    // Mask flags to be safe.
    fontFlags &= Font::FF_CreateFont_Mask;
    fontFlags |= Font::FF_DeviceFont;

    unsigned i;
    for (i = 0; i < Fonts.GetSize(); ++i)
    {
        FontInfoNGP& font = Fonts[i];
        if( ( font.FontName.CompareNoCase(name) == 0 ) && 
            ( ( font.FontFlags & Font::FF_Style_Mask) == (fontFlags & Font::FF_Style_Mask) ) )
        {
            ExternalFontNGP* newFont = new ExternalFontNGP(this, LibId, font);
            if( newFont && !newFont->IsValid() )
            {
                newFont->Release();
                return NULL;
            }

            return newFont;
        }
    }
    return NULL;
}

void FontProviderNGP::LoadFontNames(StringHash<String>& fontnames)
{
    SF_UNUSED(fontnames);
    //SF_ASSERT(0);
}



}} // Scaleform::Render

