/**************************************************************************

PublicHeader:   Render
Filename    :   Render_FontProviderNGP.h
Content     :   
Created     :   2011
Authors     :   Maxim Shemanarev

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_SF_Render_FontProviderNGP_H
#define INC_SF_Render_FontProviderNGP_H

#include <font/libpvf.h>

#include "Kernel/SF_Hash.h"
#include "Render/Render_Font.h"

namespace Scaleform { namespace Render {

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

class FontProviderNGP;

enum NGP_FontStreamType
{
    NGP_FontStream_File,
    NGP_FontStream_Memory
};

struct FontInfoNGP
{
    String              FontName;
    unsigned            FontFlags;
    String              FileName;
    const char*         FontData;
    unsigned            FontDataSize;
    int                 UniqueId;
    unsigned            FontType;
    NGP_FontStreamType  FontStream;
    float               MetricsScale;
    float               AdvanceScale;
};


class ExternalFontNGP : public Font
{
    enum { ShapePageSize = 256-2 - 8-4 };
public:
    ExternalFontNGP(FontProviderNGP* pprovider, ScePvf_t_libId library, const FontInfoNGP& fontInfo);

    virtual ~ExternalFontNGP();

    bool    IsValid() const { return Valid; }

    void    SetHinting(const Font::NativeHintingType& pnh);

	virtual const char* GetName() const { return &Name[0]; }

    virtual int     GetGlyphIndex(UInt16 code);
    virtual float   GetAdvance(unsigned glyphIndex) const;
    virtual float   GetKerningAdjustment(unsigned lastCode, unsigned thisCode) const;
    virtual float   GetGlyphWidth(unsigned glyphIndex) const;
    virtual float   GetGlyphHeight(unsigned glyphIndex) const;
    virtual RectF&  GetGlyphBounds(unsigned glyphIndex, RectF* prect) const;
    virtual bool    IsHintedVectorGlyph(unsigned glyphIndex, unsigned hintedSize) const;
    virtual bool    IsHintedRasterGlyph(unsigned glyphIndex, unsigned hintedSize) const;
    virtual const ShapeDataInterface* GetPermanentGlyphShape(unsigned glyphIndex) const { SF_UNUSED(glyphIndex); return 0; }
    virtual bool    GetTemporaryGlyphShape(unsigned glyphIndex, unsigned hintedSize, GlyphShape* shape);
    virtual bool    GetGlyphRaster(unsigned glyphIndex, unsigned hintedSize, GlyphRaster* raster);

private:
    struct GlyphType
    {
        unsigned    Code;
        float       Advance;
        RectF       Bounds;
    };

    struct KerningPairType
    {           
        UInt16  Char0, Char1;
        bool    operator==(const KerningPairType& k) const { return Char0 == k.Char0 && Char1 == k.Char1; }
    };

    // AddRef for font provider since it contains our cache.
    Ptr<FontProviderNGP>                pFontProvider;    
    String                              Name;
    
    bool                                Valid;
    
    ScePvf_t_fontId                     FontId;
    
    Array<GlyphType>                    Glyphs;
    HashIdentity<UInt16, unsigned>      CodeTable;
    Hash<KerningPairType, float>        KerningPairs;
    float                               LastFontHeight;
    float                               MetricsScale;
    float                               AdvanceScale;
};



//------------------------------------------------------------------------
class FontProviderNGP : public FontProvider
{
public:
    FontProviderNGP(unsigned numUserFontEntries=8, int firstId=0);
    virtual ~FontProviderNGP();


    void MapSystemFont(const char* fontName, unsigned fontFlags, unsigned fontType, 
                       NGP_FontStreamType fontStream = NGP_FontStream_File,
                       float metricsScale = 1.5f, float advanceScale = 0.5f);

    void MapFontToFile(const char* fontName, unsigned fontFlags, const char* fileName, 
                       NGP_FontStreamType fontStream = NGP_FontStream_File,
                       float metricsScale = 1.5f, float advanceScale = 0.5f);

    void MapFontToMemory(const char* fontName, unsigned fontFlags, 
                         const char* fontData, unsigned dataSize, 
                         float metricsScale = 1.5f, float advanceScale = 0.5f);


    virtual Font* CreateFont( const char* name, unsigned fontFlags );

    virtual void     LoadFontNames( StringHash<String>& fontnames );

    bool    IsValid() const { return Valid; }

    ScePvf_t_libId GetLibId() { return LibId; }

private:
    ExternalFontNGP* createFont(const FontInfoNGP& font);

    bool                Valid;
    
    ScePvf_t_initRec    FontParams;
    ScePvf_t_libId      LibId;

    int                 NextFontId;

    Array<FontInfoNGP>  Fonts;
};

}} // Scaleform::Render


#endif


