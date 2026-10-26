/**************************************************************************

Filename    :   GFx_FontResource.cpp
Content     :   Representation of SWF/GFX font data and resources.
Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "GFx/GFx_FontResource.h"
#include "GFx/GFx_Stream.h"
#include "GFx/GFx_Log.h"
#include "Kernel/SF_Debug.h"
#include "GFx/GFx_ShapeSwf.h"
#include "Render/Render_Math2D.h"
#include "Render/Render_GlyphParam.h"
#include "Kernel/SF_Std.h"
#include "Kernel/SF_File.h"
#include "Kernel/SF_Alg.h"

#include "GFx/GFx_LoadProcess.h"
#include "Kernel/SF_MsgFormat.h"

namespace Scaleform { namespace GFx {

// ***** TextureGlyphData
TextureGlyphData::TextureGlyphData(const TextureGlyphData& orig) 
: PackTextureConfig(orig.PackTextureConfig), FileCreation(orig.FileCreation)
{
    TextureGlyphs.Resize(orig.TextureGlyphs.GetSize());
    for (UPInt i = 0, n = orig.TextureGlyphs.GetSize(); i < n; ++i)
    {
        TextureGlyphs[i] = orig.TextureGlyphs[i];
    }
    ImageResourceHash::ConstIterator iter = orig.GlyphsTextures.Begin();
    for (; iter != orig.GlyphsTextures.End(); ++iter)
    {
        GlyphsTextures.Set(iter->First, iter->Second);
    }
}


// Return a pointer to a TextureGlyph struct Corresponding to
// the given GlyphIndex, if we have one.  Otherwise return NULL.
const TextureGlyph&  TextureGlyphData::GetTextureGlyph(unsigned glyphIndex) const
{
   if (glyphIndex >= TextureGlyphs.GetSize())
   {
       static const TextureGlyph dummyTextureGlyph;
       return dummyTextureGlyph;
   }
   return TextureGlyphs[glyphIndex];
}


// Register some texture info for the glyph at the specified
// index.  The TextureGlyph can be used later to render the glyph.
void    TextureGlyphData::AddTextureGlyph(unsigned glyphIndex, const TextureGlyph& glyph)
{
//    SF_ASSERT(!IsMissingGlyph(glyphIndex));

   // Resize texture glyphs so that the index will fit.
   if (TextureGlyphs.GetSize() <= glyphIndex)
   {
       TextureGlyphs.Resize(glyphIndex+1);
       if (TextureGlyphs.GetSize() <= glyphIndex)
           return;
   }
   
   //SF_ASSERT(glyph.HasImageResource());
   //SF_ASSERT(TextureGlyphs[glyphIndex].HasImageResource() == false);
   TextureGlyphs[glyphIndex] = glyph;
}


// Delete all our texture glyph info.
void    TextureGlyphData::WipeTextureGlyphs()
{
   //SF_ASSERT(TextureGlyphs.GetSize() == Glyphs.GetSize());

   // Replace with default (empty) glyph info.
   TextureGlyph defaultTg;
   for (UPInt i = 0, n = TextureGlyphs.GetSize(); i < n; i++)
       TextureGlyphs[i] = defaultTg;
}


void TextureGlyphData::VisitTextureGlyphs(TextureGlyphVisitor* pvisitor)
{
   SF_ASSERT(pvisitor);

   for(UPInt i = 0, n = TextureGlyphs.GetSize(); i < n; ++i)    
       pvisitor->Visit((unsigned)i, &TextureGlyphs[i]);    
}

float TextureGlyphData::GetTextureGlyphScale() const
{
   return FontPackParams::GlyphBoundBox / PackTextureConfig.NominalSize;
}

void TextureGlyphData::AddTexture(ResourceId textureId, ImageResource* pimageRes)
{
   ResourcePtr<ImageResource> pres = pimageRes;
   GlyphsTextures.Set(textureId, pres);
}
void TextureGlyphData::AddTexture(ResourceId textureId, const ResourceHandle &rh)
{
   ResourcePtr<ImageResource> pres;
   pres.SetFromHandle(rh);
   GlyphsTextures.Set(textureId, pres);
}


void TextureGlyphData::VisitTextures(TexturesVisitor* pvisitor, ResourceBinding* pbinding)
{
   SF_ASSERT(pvisitor);

   ImageResourceHash::ConstIterator iter = GlyphsTextures.Begin();
   for (; iter != GlyphsTextures.End(); ++iter)
   {
       Resource* pres = (*pbinding) [iter->Second];
       SF_ASSERT(pres->GetResourceType() == Resource::RT_Image);        
       pvisitor->Visit(iter->First, (ImageResource*) pres);
   }
}


// ***** FontData


// DBG
//======================== Remove
//static Ptr<RawImage> SharedImg;
//Render::TextureGlyph SharedGlyph;
//const Render::TextureGlyph* FontData::GetTextureGlyph(unsigned) const
//{
//    if (SharedImg.GetPtr() == 0)
//    {
//        enum { w=1024, h=128, x1=395, y1=0, x2=417, y2=30 };
//        float ox = 396.53125f;
//        float oy = 25.65625;
//
//
//        ImageSize size(w, h);
//        unsigned use = ImageUse_Update;
//        ImageData d;
//        SharedImg = *RawImage::Create(Image_A8, 1, size, use, Memory::GetGlobalHeap());
//        SharedImg->GetImageData(&d);
//        ImagePlane& pl = d.pPlanes[0];
//
//        unsigned i;
//        for (i = 0; i < size.Height; i += 2)
//        {
//            UByte* p1 = pl.GetScanline(i);
//            UByte* p2 = pl.GetScanline(i+1);
//            memset(p1, 0, size.Width);
//            memset(p2, 255, size.Width);
//        }
//        float u1 = float(x1) / w;
//        float v1 = float(y1) / h;
//        float u2 = float(x2) / w;
//        float v2 = float(y2) / h;
//        float uo = ox / w;
//        float vo = oy / h;
//        SharedGlyph.UvBounds = RectF(u1, v1, u2, v2);
//        SharedGlyph.UvOrigin = PointF(uo, vo);
//        SharedGlyph.pImage = SharedImg;
//    }
//    return &SharedGlyph;
//}
//
//float FontData::GetTextureGlyphHeight() const
//{
//    return 48.0 * 1024.0 / 1536.0;
//}
//======================== Remove


const Render::TextureGlyph* FontData::GetTextureGlyph(unsigned glyphIndex) const
{
    if (pTGData && glyphIndex < pTGData->GetTextureGlyphCount())
        return &pTGData->GetTextureGlyph(glyphIndex);
    return NULL;
}

float FontData::GetTextureGlyphHeight() const
{
    return (pTGData) ? float(pTGData->GetNominalSize() * 1024.0 / 1536.0) : 0;
}


FontData::FontData()   
   : Font(), Name(NULL)
{
}

FontData::FontData(const char* name, unsigned fontFlags)
    : Font(fontFlags), Name(NULL)
{
    Name = (char*)SF_ALLOC(SFstrlen(name) + 1, StatMD_Fonts_Mem);
    if (Name)
        SFstrcpy(Name, SFstrlen(name) + 1, name);

    SetHasLayout(1);
}


FontData::~FontData()
{
    Glyphs.Resize(0);

    // Delete the name string.
    if (Name)
    {
        SF_FREE(Name);
        Name = NULL;
    }
}


void    FontData::Read(LoadProcess* p, const TagInfo& tagInfo)
{
    SF_ASSERT(tagInfo.TagType == Tag_DefineFont ||
            tagInfo.TagType == Tag_DefineFont2 ||
            tagInfo.TagType == Tag_DefineFont3);

    Stream *    pin = p->GetStream();
    bool        isLoadingFontShapes = p->IsLoadingFontShapes();
    MemoryHeap* pheap = p->GetLoadHeap();

    // No AddRef() here, to avoid cycle.
    // OwningMovie is our owner, so it has a ref to us.
    //OwningMovie = p->GetDataDef();    

    if (tagInfo.TagType == Tag_DefineFont)
    {
        pin->LogParse("reading DefineFont\n");

        int tableBase = pin->Tell();

        // Read the glyph offsets.  Offsets
        // are measured from the start of the
        // offset table.
        Array<int>    offsets;
        offsets.PushBack(pin->ReadU16());
        pin->LogParse("offset[0] = %d\n", offsets[0]);
        int count = offsets[0] >> 1;
        for (int i = 1; i < count; i++)
        {
            UInt16 off = pin->ReadU16();
            if (off == 0)
            {
                // special case for tag with stripped font shapes
                isLoadingFontShapes = false;
                break;
            }
            offsets.PushBack(off);
            pin->LogParse("offset[%d] = %d\n", i, offsets[i]);
        }

        Glyphs.Resize(count);
      //  TextureGlyphs.Resize(Glyphs.GetSize());

        if (isLoadingFontShapes)
        {
            // Read the glyph shapes.
            for (int i = 0; i < count; i++)
            {
                // Seek to the start of the shape data.
                int newPos = tableBase + offsets[i];
                pin->SetPosition(newPos);
                
                SPInt shapeDataLen;
                if (i + 1 < count)
                    shapeDataLen = offsets[i + 1] - offsets[i];
                else
                    shapeDataLen = tagInfo.TagDataOffset + tagInfo.TagLength - newPos;

                // Create & read the shape.
                Ptr<ConstShapeNoStyles> s = *SF_HEAP_NEW_ID(pheap, StatMD_ShapeData_Mem) ConstShapeNoStyles;
                s->Read(p, Tag_DefineShape, (unsigned)shapeDataLen, false);

                Glyphs[i] = s;
            }
        }
        else
            SetGlyphShapesStripped();
    }
    else if ((tagInfo.TagType == Tag_DefineFont2) || (tagInfo.TagType == Tag_DefineFont3))
    {
        if (tagInfo.TagType == Tag_DefineFont2)
            pin->LogParse("reading DefineFont2: ");
        else
            pin->LogParse("reading DefineFont3: ");

        bool    hasLayout = (pin->ReadUInt(1) != 0);
        SetHasLayout(hasLayout);

        bool shiftJisFlag        = (pin->ReadUInt(1) != 0);
        bool pixelAlignedChars   = (pin->ReadUInt(1) != 0);
        bool ansiFlag            = (pin->ReadUInt(1) != 0);

        if (shiftJisFlag)  SetCodePage(FF_CodePage_ShiftJis);
        else if (ansiFlag) SetCodePage(FF_CodePage_Ansi);
        else               SetCodePage(FF_CodePage_Unicode);
        
        SetPixelAligned(pixelAlignedChars);
        
        bool    wideOffsets = (pin->ReadUInt(1) != 0);
        SetWideCodes(pin->ReadUInt(1) != 0);
        SetItalic(pin->ReadUInt(1) != 0);
        SetBold(pin->ReadUInt(1) != 0);
        UByte   langCode = pin->ReadU8(); // Language code

        // Inhibit warning.
        langCode = langCode;

        Name = pin->ReadStringWithLength(p->GetLoadHeap());

        int glyphCount = pin->ReadU16();

        if (pin->IsVerboseParse())
        {
            pin->LogParse("  Name = %s, %d glyphs\n", Name ? Name : "(none)", glyphCount);

            const char* pcodePage = "Unicode";
            if (GetCodePage() == FF_CodePage_ShiftJis)
                pcodePage = "ShiftJIS";
            else if (GetCodePage() == FF_CodePage_Ansi)
                pcodePage = "ANSI";

            pin->LogParse("  HasLayout = %d, CodePage = %s, Italic = %d, Bold = %d\n", 
                (int)hasLayout, pcodePage, IsItalic(), IsBold());
            pin->LogParse("  LangCode = %d\n", langCode);
        }

        
        int tableBase = pin->Tell();

        // Read the glyph offsets.  Offsets
        // are measured from the start of the
        // offset table.
        Array<int>    offsets;
        int fontCodeOffset;

        int offsetsCount = glyphCount;
        if (glyphCount > 0)
        {
            // check for the first offset. If it is 0 then shapes
            // were stripped from the tag.
            unsigned off0 = (wideOffsets) ? (unsigned)pin->ReadU32() : (unsigned)pin->ReadU16();
            if (off0 == 0)
            {
                // special case for tags with stripped font shapes
                isLoadingFontShapes = false;
                offsetsCount = 0;
            }
            else
            {
                offsets.PushBack(off0);
                //pin->LogParse("offset[0] = %d\n", offsets[0]);
            }
        }
        if (wideOffsets)
        {
            // 32-bit offsets.
            for (int i = 1; i < offsetsCount; i++)
            {
                offsets.PushBack(pin->ReadU32());
                //pin->LogParse("offset[%d] = %d\n", i, offsets[i]);
            }
            fontCodeOffset = pin->ReadU32();
        }
        else
        {
            // 16-bit offsets.
            for (int i = 1; i < offsetsCount; i++)
            {
                offsets.PushBack(pin->ReadU16());
                //pin->LogParse("offset[%d] = %d\n", i, offsets[i]);
            }
            fontCodeOffset = pin->ReadU16();
        }

        Glyphs.Resize(glyphCount);
    //    TextureGlyphs.Resize(Glyphs.GetSize());

        if (isLoadingFontShapes)
        {
            TagType fontGlyphShapeTag = (tagInfo.TagType == Tag_DefineFont2) ?
                                           Tag_DefineShape2 : tagInfo.TagType;

            if (hasLayout)
            {
                AdvanceTable.Resize(glyphCount);
            }

            // Read the glyph shapes.
            for (int i = 0; i < glyphCount; i++)
            {
                // Seek to the start of the shape data.
                int newPos = tableBase + offsets[i];
                // if we're seeking backwards, then that looks like a bug.
                SF_ASSERT(newPos >= pin->Tell());
                pin->SetPosition(newPos);

                SPInt shapeDataLen;
                if (i + 1 < glyphCount)
                    shapeDataLen = offsets[i + 1] - offsets[i];
                else
                    shapeDataLen = fontCodeOffset - offsets[i];
                SF_ASSERT(shapeDataLen >= 0);

                // Create & read the shape.
                Ptr<ConstShapeNoStyles> s = *SF_HEAP_NEW_ID(pheap, StatMD_Fonts_Mem) ConstShapeNoStyles;
                if (!s->Read(p, fontGlyphShapeTag, (unsigned)shapeDataLen, false))
                {
                    // error occurred; correct number of glyphs and break
                    glyphCount = i;
                    AdvanceTable.Resize(i);
                    Glyphs.Resize(i);
                    return;
                }

                Glyphs[i] = s;

                if (hasLayout)
                {
                    RectF bounds;
                    s->ComputeBound(&bounds);
                    AdvanceEntry& ge = AdvanceTable[i];
                    if (bounds.IsNormal())
                    {
                        float left = bounds.x1;
                        float top  = bounds.y1;
                        float w = bounds.Width();
                        float h = bounds.Height();
                        /*
                        SF_ASSERT(left >= -32768./20 && left < 32767./20 && 
                            top  >= -32768./20 && top < 32767./20 && 
                            w < 65535./20 && h < 65535./20);
                            */
                        ge.Left    = (SInt16)(left * 20.f);
                        ge.Top     = (SInt16)(top * 20.f);
                        ge.Width   = (UInt16)(w * 20.f);
                        ge.Height  = (UInt16)(h * 20.f);
                    }
                    else
                    {
                        ge.Left  = ge.Top = 0;
                        ge.Width = ge.Height = 0;
                    }
                }
                //@DBG
                //RectF bounds;
                //s->ComputeBound(&bounds);
                //if (bounds.IsNormal())
                //{
                //    pin->LogParse("  chidx = %d, bounds = (%f, %f, {%f, %f}\n", 
                //        (int)i, bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
                //}
            }

            int currentPosition = pin->Tell();
            if (fontCodeOffset + tableBase != currentPosition)
            {
                // Bad offset!  Don't try to read any more.
                return;
            }
        }
        else
        {
            // Skip the shape data.
            int newPos = tableBase + fontCodeOffset;
            if (newPos >= pin->GetTagEndPosition())
            {
                // No layout data!
                return;
            }

            pin->SetPosition(newPos);
            SetGlyphShapesStripped();
        }

        ReadCodeTable(pin);

        // Read layout info for the glyphs.
        if (hasLayout)
        {
            // Multiplier used for scaling.
            // In SWF 8, font shape constant resolution (tag 75) was increased by 20.
            float sfactor = (tagInfo.TagType == Tag_DefineFont3)  ? 1.0f / 20.0f : 1.0f;

            Ascent = (float) pin->ReadS16() * sfactor;
            Descent = (float) pin->ReadS16() * sfactor;
            Leading = (float) pin->ReadS16() * sfactor;
            
            if (pin->IsVerboseParse())
            {
                pin->LogParse("  Ascent = %d, Descent = %d, Leading = %d\n", 
                    (int)Ascent, (int)Descent, (int)Leading);
            }

            // Advance table; i.E. how wide each character is.
            if (AdvanceTable.GetSize() != Glyphs.GetSize())
                AdvanceTable.Resize(Glyphs.GetSize());
            for (UPInt i = 0, n = AdvanceTable.GetSize(); i < n; i++)
            {
                AdvanceEntry& ge = AdvanceTable[i];
                ge.Advance = (float) pin->ReadU16() * sfactor;
            }

            // Bounds table.
            //BoundsTable.Resize(Glyphs.GetSize());    // kill
            RectF  dummyRect;
            {for (UPInt i = 0, n = Glyphs.GetSize(); i < n; i++)
            {
                //BoundsTable[i].Read(pin);  // kill
                pin->ReadRect(&dummyRect);                   
            }}

            // Kerning pairs.
            int kerningCount = pin->ReadU16();
            if (pin->IsVerboseParse())
            {
                pin->LogParse("  KerningCount = %d\n", (int)kerningCount);
            }
            for (int i = 0; i < kerningCount; i++)
            {
                int off = pin->Tell();
                if (off >= tagInfo.TagDataOffset + tagInfo.TagLength)
                {
                    pin->LogError("Corrupted file %s, kerning table of the font '%s' is longer than tagLength.",
                                  pin->GetFileName().ToCStr(), (Name) ? Name : "<noname>");
                    break;
                }

                UInt16  char0, char1;
                if (AreWideCodes())
                {
                    char0 = pin->ReadU16();
                    char1 = pin->ReadU16();
                }
                else
                {
                    char0 = pin->ReadU8();
                    char1 = pin->ReadU8();
                }
                float   adjustment = (float) pin->ReadS16() * sfactor;

                KerningPair k;
                k.Char0 = char0;
                k.Char1 = char1;

                if (pin->IsVerboseParse())
                    pin->LogParse("     Pair: %d - %d,\tadj = %d\n", (int)char0, (int)char1, (int)adjustment);

                // Remember this adjustment; we can look it up quickly
                // later using the character pair as the key.
                KerningPairs.Add(k, adjustment);
            }
        }
        if (!isLoadingFontShapes && AdvanceTable.GetSize() > 0)
        {
            // reset glyphRects if no FontShapes loaded
            for (UPInt i = 0, n = AdvanceTable.GetSize(); i < n; i++)
            {
                AdvanceEntry& ge = AdvanceTable[i];
                ge.Left = ge.Top = ge.Height = ge.Width = 0;
            }
        }
    }
}


// Read additional information about this FontData, from a
// DefineFontInfo tag.  The caller has already read the tag
// type and FontData id.
void    FontData::ReadFontInfo(Stream* in, TagType tagType)
{
    if (Name)
    {
        SF_FREE(Name);
        Name = NULL;
    }

    Name = in->ReadStringWithLength(in->GetHeap());

    UByte flags = in->ReadU8();

    UByte langCode = 0;
    if (tagType == Tag_DefineFontInfo2)
    {
        langCode = in->ReadU8(); // Language code
        langCode = langCode; // suppress warning
    }

    bool pixelAlignedChars  =  ((flags & 0x20) != 0);
    bool shiftJisFlag        = ((flags & 0x10) != 0);
    bool ansiFlag            = ((flags & 0x08) != 0);

    if (shiftJisFlag)  SetCodePage(FF_CodePage_ShiftJis);
    else if (ansiFlag) SetCodePage(FF_CodePage_Ansi);
    else               SetCodePage(FF_CodePage_Unicode);
    SF_UNUSED(pixelAlignedChars);
    
    SetItalic       ((flags & 0x04) != 0);
    SetBold         ((flags & 0x02) != 0);
    SetWideCodes    ((flags & 0x01) != 0);

    if (in->IsVerboseParse())
    {
        if (tagType == Tag_DefineFontInfo)        
            in->LogParse("reading DefineFontInfo\n");
        else
            in->LogParse("reading DefineFontInfo2\n");
        in->LogParse("  Name = %s\n", Name ? Name : "(none)");

        const char* pcodePage = "Unicode";
        if (GetCodePage() == FF_CodePage_ShiftJis)
            pcodePage = "ShiftJIS";
        else if (GetCodePage() == FF_CodePage_Ansi)
            pcodePage = "ANSI";

        in->LogParse("  CodePage = %s, Italic = %d, Bold = %d\n", 
            pcodePage, IsItalic(), IsBold());
        if (tagType == Tag_DefineFontInfo2)
            in->LogParse("  LangCode = %d\n", langCode);
    }

    ReadCodeTable(in);
}


// Read the table that maps from glyph indices to character codes.
void    FontData::ReadCodeTable(Stream* in)
{
    in->LogParse("reading code table at offset %d\n", in->Tell());

    SF_ASSERT(CodeTable.IsEmpty() && Glyphs.GetSize() == AdvanceTable.GetSize() /*zhaojun@snda*/);

    CodeTable.SetCapacity(Glyphs.GetSize());
    if (AreWideCodes())
    {
        // Code table is made of UInt16's.
        for (UPInt i = 0, n = Glyphs.GetSize(); i < n; i++) 
        {
			UINT16 code = in->ReadU16();
			AdvanceTable[i].Code = code;
			CodeTable.Add(code, (UInt16)i);
		}
    }
    else
    {
		// Code table is made of bytes.
		for (UPInt i = 0, n = Glyphs.GetSize(); i < n; i++) 
		{
			UINT8 code = in->ReadU8();
			AdvanceTable[i].Code = code;
			CodeTable.Add(code, (UInt16)i);
		}
    }
}

int FontData::GetGlyphIndex(UInt16 code)
{
    UInt16 glyphIndex;
    if (CodeTable.Get(code, &glyphIndex))
    {
        return glyphIndex;
    }
    return -1;
}

int     FontData::GetCharValue(unsigned glyphIndex) const
{
	// modified by zhaojun@snda
	if (glyphIndex < AdvanceTable.GetSize())
	{
		return AdvanceTable[glyphIndex].Code;
	}
    //for (CodeTableType::ConstIterator iter = CodeTable.Begin();
    //    iter != CodeTable.End(); ++iter)
    //{
    //    if (iter->Second == glyphIndex)
    //        return iter->First;
    //}
    return -1;
}

const Render::ShapeDataInterface* FontData::GetPermanentGlyphShape(unsigned glyphIndex) const
{
    if (glyphIndex < Glyphs.GetSize())
        return Glyphs[glyphIndex].GetPtr();
    else
        return NULL;
}

float   FontData::GetAdvance(unsigned glyphIndex) const
{
    // how could this be if GlyphIndex is unsigned?
    if (IsMissingGlyph(glyphIndex))
        return GetNominalGlyphWidth();

    if (AdvanceTable.GetSize() == 0)
    {
        // No layout info for this FontData!!!
        static bool Logged = false;
        if (Logged == false)
        {
            Logged = true;
            SF_DEBUG_ERROR1(1, "Empty advance table in font %s", GetName());
        }
        
        // MA: It is better to return default advance, make char substitution show up better
        return GetNominalGlyphWidth();        
    }

    if (glyphIndex < AdvanceTable.GetSize())
    {
        return AdvanceTable[glyphIndex].Advance;
    }
    else
    {
        SF_ASSERT(0);
    }
    return 0;
}

float   FontData::GetGlyphWidth(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex))
        return GetNominalGlyphWidth();
    
    if (glyphIndex < AdvanceTable.GetSize())
    {
        SF_ASSERT(!IsMissingGlyph(glyphIndex));
        float w = float(AdvanceTable[glyphIndex].Width)/20.f;
        if (w != 0)
            return w;
    }
    return GetAdvance(glyphIndex); 
}

float   FontData::GetGlyphHeight(unsigned glyphIndex) const
{
    // How could this be if GlyphIndex is unsigned?
    if (IsMissingGlyph(glyphIndex) || AdvanceTable.GetSize() == 0)    
        return GetNominalGlyphHeight();

    if (glyphIndex < AdvanceTable.GetSize())
    {
        SF_ASSERT(!IsMissingGlyph(glyphIndex));
        return float(AdvanceTable[glyphIndex].Height)/20.f;
    }
    else
    {
        // Bad glyph index.  Due to bad data file?
        // This is possible, if font doesn't have layout (for static text).
        // But AdvanceTable should be empty in this case.
        SF_ASSERT(AdvanceTable.GetSize() == 0);
        return 0;
    }
}

RectF& FontData::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
{
    if (IsMissingGlyph(glyphIndex))
    {
        prect->x1 = prect->y1 = 0;
        prect->SetWidth(GetGlyphWidth(glyphIndex));
        prect->SetHeight(GetGlyphHeight(glyphIndex));
    }
    else if (glyphIndex < AdvanceTable.GetSize())
    {
        SF_ASSERT(!IsMissingGlyph(glyphIndex));
        const AdvanceEntry& e = AdvanceTable[glyphIndex];
        float w = float(e.Width)/20.f;
        if (w == 0)
            w = e.Advance;
        float h = float(e.Height)/20.f;
        prect->x1 = float(e.Left)/20.f;
        prect->y1  = float(e.Top)/20.f;
        prect->SetWidth(w);
        prect->SetHeight(h);
    }
    else
    {
        // Bad glyph index.  Due to bad data file?
        // This is possible, if font doesn't have layout (for static text).
        // But AdvanceTable should be empty in this case.
        //SF_ASSERT(AdvanceTable.GetSize() == 0);
        SF_DEBUG_ERROR3((AdvanceTable.GetSize() != 0), 
            "Glyph index %d exceeds advance table (size = %d), font = %s", 
            glyphIndex, (int)AdvanceTable.GetSize(), GetName());

        prect->x1 = prect->y1 = 0;
        prect->SetWidth(0);
        prect->SetHeight(0);

        // so try to calculate the bounds
        if (glyphIndex < Glyphs.GetSize())
        {
            ShapeDataBase* s = Glyphs[glyphIndex];
            if (s)
            {
                RectF bounds;
                s->ComputeBound(&bounds);
                if (bounds.IsNormal())
                {
                    float left = bounds.x1;
                    float top  = bounds.y1;
                    float w = bounds.Width();
                    float h = bounds.Height();
                    prect->x1    = left;
                    prect->y1     = top;
                    prect->SetWidth(w);
                    prect->SetHeight(h);
                }
            }
        }
    }
    return *prect;
}

// Return the adjustment in advance between the given two
// characters.  Normally this will be 0; i.E. the 
float   FontData::GetKerningAdjustment(unsigned LastCode, unsigned code) const
{
    float   adjustment;
    KerningPair k;
    k.Char0 = (UInt16)LastCode;
    k.Char1 = (UInt16)code;
    if (KerningPairs.Get(k, &adjustment))
    {
        return adjustment;
    }
    return 0;
}


// =======================begin zhaojun@snda=======================

//int FontData4AOD::GetGlyphIndex(UInt16 code)
//{
//	if (MasterFont)
//	{
//		Lock::Locker locker(pFontLock);
//		const unsigned* indexPtr = CodeTable.Get(code);
//		if (indexPtr)
//			return *indexPtr;
//
//		GFxGdiSelectObjectGuard g1(pSysData->WinHDC, MasterFont);
//		GLYPHMETRICS gm;
//		MAT2 im = { {0,1}, {0,0}, {0,0}, {0,1} };
//		int ret = ::GetGlyphOutlineW(pSysData->WinHDC,
//			code,
//			GGO_METRICS,
//			&gm,
//			0, 0,
//			&im);
//
//		if (ret == GDI_ERROR)
//			return -1;
//
//		GlyphType glyph;
//		glyph.Code      =  code;
//		glyph.Advance   =  float(gm.gmCellIncX) * Scale1024;
//		glyph.Bounds.x1 =  float(gm.gmptGlyphOrigin.x) * Scale1024;
//		glyph.Bounds.y1 = -float(gm.gmptGlyphOrigin.y) * Scale1024;
//		glyph.Bounds.x2 =  glyph.Bounds.x1 + float(gm.gmBlackBoxX) * Scale1024;
//		glyph.Bounds.y2 =  glyph.Bounds.y1 + float(gm.gmBlackBoxY) * Scale1024;
//
//		Glyphs.PushBack(glyph);
//		CodeTable.Add(code, (unsigned)Glyphs.GetSize()-1);
//		return (unsigned)Glyphs.GetSize()-1;
//	}
//	return -1;
//}
//
//float FontData4AOD::GetAdvance(unsigned glyphIndex) const
//{
//	if (IsMissingGlyph(glyphIndex))
//		return GetNominalGlyphWidth();
//
//	Lock::Locker locker(pFontLock);
//	return Glyphs[glyphIndex].Advance;
//}
//
////------------------------------------------------------------------------
//float FontData4AOD::GetKerningAdjustment(unsigned lastCode, unsigned thisCode) const
//{
//	float adjustment;
//	KerningPairType k;
//	k.Char0 = (UInt16)lastCode;
//	k.Char1 = (UInt16)thisCode;
//	if (KerningPairs.Get(k, &adjustment))
//	{
//		return adjustment;
//	}
//	return 0;
//}
//
////------------------------------------------------------------------------
//float FontData4AOD::GetGlyphWidth(unsigned glyphIndex) const
//{
//	if (IsMissingGlyph(glyphIndex))
//		return GetNominalGlyphWidth();
//
//	Lock::Locker locker(pFontLock);
//	const RectF& r = Glyphs[glyphIndex].Bounds;
//	return r.Width();
//}
//
////------------------------------------------------------------------------
//float FontData4AOD::GetGlyphHeight(unsigned glyphIndex) const
//{
//	if (IsMissingGlyph(glyphIndex))
//		return GetNominalGlyphHeight();
//
//	Lock::Locker locker(pFontLock);
//	const RectF& r = Glyphs[glyphIndex].Bounds;
//	return r.Height();
//}
//
////------------------------------------------------------------------------
//RectF& FontData4AOD::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
//{
//	if (IsMissingGlyph(glyphIndex))
//		prect->SetRect(GetNominalGlyphWidth(), GetNominalGlyphHeight());
//	else
//	{
//		Lock::Locker locker(pFontLock);
//		*prect = Glyphs[glyphIndex].Bounds;
//	}
//	return *prect;
//}

RectF& FontData4AOD::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
{
	return __super::GetGlyphBounds(glyphIndex, prect);
}


//RectF& FontData4AOD::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
//{
//	if (IsMissingGlyph(glyphIndex))
//	{
//		prect->x1 = prect->y1 = 0;
//		prect->SetWidth(GetGlyphWidth(glyphIndex));
//		prect->SetHeight(GetGlyphHeight(glyphIndex));
//	}
//	else if (glyphIndex < AdvanceTable.GetSize())
//	{
//		SF_ASSERT(!IsMissingGlyph(glyphIndex));
//		const AdvanceEntry& e = AdvanceTable[glyphIndex];
//		float w = float(e.Width)/20.f;
//		if (w == 0)
//			w = e.Advance;
//		float h = float(e.Height)/20.f;
//		prect->x1 = float(e.Left)/20.f;
//		prect->y1  = float(e.Top)/20.f;
//		prect->SetWidth(w);
//		prect->SetHeight(h);
//	}
//	else
//	{
//		// Bad glyph index.  Due to bad data file?
//		// This is possible, if font doesn't have layout (for static text).
//		// But AdvanceTable should be empty in this case.
//		//SF_ASSERT(AdvanceTable.GetSize() == 0);
//		SF_DEBUG_ERROR3((AdvanceTable.GetSize() != 0), 
//			"Glyph index %d exceeds advance table (size = %d), font = %s", 
//			glyphIndex, (int)AdvanceTable.GetSize(), GetName());
//
//		prect->x1 = prect->y1 = 0;
//		prect->SetWidth(0);
//		prect->SetHeight(0);
//
//		// so try to calculate the bounds
//		if (glyphIndex < Glyphs.GetSize())
//		{
//			ShapeDataBase* s = Glyphs[glyphIndex];
//			if (s)
//			{
//				RectF bounds;
//				s->ComputeBound(&bounds);
//				if (bounds.IsNormal())
//				{
//					float left = bounds.x1;
//					float top  = bounds.y1;
//					float w = bounds.Width();
//					float h = bounds.Height();
//					prect->x1    = left;
//					prect->y1     = top;
//					prect->SetWidth(w);
//					prect->SetHeight(h);
//				}
//			}
//		}
//	}
//	return *prect;
//}

struct GFxGdiSelectObjectGuard
{
	HDC     WinDC;
	HGDIOBJ WinObj;
	GFxGdiSelectObjectGuard(HDC dc, HGDIOBJ obj) : WinDC(dc), WinObj(::SelectObject(dc, obj)) {}
	~GFxGdiSelectObjectGuard() { ::SelectObject(WinDC, WinObj); }
};

void FontData4AOD::Read( LoadProcess* p, const TagInfo& tagInfo )
{
	// not threadsafe, but AOD is not multi-thread

	__super::Read(p, tagInfo);

	Glyphs.ClearAndRelease();	// clear the glyph shape cache, 但只是清除了本身,对于内部的glyph shape数据却没有清理,析构时也没清理
	
	p->GetPathAllocator()->Clear();	// free the shape cache allocator, 这里清除其上分配的glyph shape, 非常暴力,
									// 这句会导致gfxplayer的一个断言错误
									// GFXSrc\Src\GFx\GFx_ShapeSwf.cpp
									//	SwfShapeDecoder::SwfShapeDecoder 中//	 SF_ASSERT(sig == Signature);// zhaojun@snda

	///////////Generate Advance, add and commented by zhaojun@snda////////////
	//RectF r;
	//GLYPHMETRICS gm;
	//MAT2 im = { {0,1}, {0,0}, {0,0}, {0,1} };

	//const float Scale1024 = (1024.0f / float(GGO_FontHeight));

	//HFONT MasterFont = ::CreateFontA(-GGO_FontHeight,             // height of font
	//	0,                          // average character width
	//	0,                          // angle of escapement
	//	0,                          // base-line orientation angle
	//	IsBold() ? FW_BOLD : FW_NORMAL, // font weight
	//	IsItalic(),                 // italic attribute option
	//	0,                          // underline attribute option
	//	0,                          // strikeout attribute option
	//	DEFAULT_CHARSET,            // character set identifier
	//	OUT_DEFAULT_PRECIS,         // output precision
	//	CLIP_DEFAULT_PRECIS,        // clipping precision
	//	ANTIALIASED_QUALITY,        // output quality
	//	DEFAULT_PITCH,              // pitch and family
	//	Name);                 // typeface name

	//if(MasterFont)
	//{
	//	TEXTMETRICW tm;
	//	GFxGdiSelectObjectGuard g1(WinDC, MasterFont);

	//	if (::GetTextMetricsW(WinDC, &tm))
	//	{
	//		SetFontMetrics(float(tm.tmInternalLeading) * Scale1024, 
	//			float(tm.tmAscent) * Scale1024, 
	//			float(tm.tmDescent) * Scale1024);
	//		
	//	}
	//	else
	//	{
	//		// GetTextMetrics may return FALSE sometimes; not sure what the best
	//		// strategy is in this case, just print an error in debug output.
	//		//SF_ASSERT(0);
	//		SF_DEBUG_WARNING1(1, "ExternalFontWinAPI: GetTextMetricsW for '%s' returned FALSE, text rendering may be affected.",
	//			Name);
	//	}

	//	AdvanceEntry* ae = NULL;
	//	RectF r;

	//	for (UInt32 index = 0; index < AdvanceTable.GetSize(); ++index)
	//	{
	//		ae = &(AdvanceTable[index]);

	//		UInt16 code = ae->Code;

	//		ShapeDataBase* pShape = Glyphs[index];

	//		pShape->ComputeBound(&r);

	//		float l = r.x1 * 20;
	//		float t = r.y1 * 20;
	//		float w = r.Width() * 20;
	//		float h = r.Height() * 20;

	//		::GetGlyphOutline(WinDC, code, GGO_METRICS, &gm, 0, NULL, &im);

	//		float Advance   =  float(gm.gmCellIncX) * Scale1024;
	//		float Left =  float(gm.gmptGlyphOrigin.x) * Scale1024 * 20.0f;
	//		float Top = -float(gm.gmptGlyphOrigin.y) * Scale1024 * 20.0f;
	//		float Width =  float(gm.gmBlackBoxX) * Scale1024 * 20.0f;
	//		float Height =  float(gm.gmBlackBoxY) * Scale1024 * 20.0f;


	//		//ae->Advance = Advance;//.5;//* Advance;//float(gm.gmCellIncX) * Scale1024;
	//		//ae->Left = Left;//float(gm.gmptGlyphOrigin.x) * Scale1024 * 20.0f;
	//		//ae->Top = Top;//-float(gm.gmptGlyphOrigin.y) * Scale1024 * 20.0f;
	//		//ae->Width = Width;//float(gm.gmBlackBoxX) * Scale1024 * 20.0f;
	//		//ae->Height = Height;//float(gm.gmBlackBoxY) * Scale1024 * 20.0f;

	//	}

	//	//CloseHandle(MasterFont);
	//}

}

bool FontData4AOD::IsHintedRasterGlyph( unsigned glyphIndex, unsigned hintedSize ) const
{
	// need lock?
	glyphIndex;
	hintedSize;
	return true;
}

UByte AverageColor(UByte c, UByte lt, UByte t, UByte rt, UByte l, UByte r, UByte lb, UByte b, UByte rb)
{
	UINT colorSum = c + lt + t + rt + l + r + lb + b + rb;
	return (UByte)(colorSum / 9);
}

UByte DarkBoarder(UByte c, UByte lt, UByte t, UByte rt, UByte l, UByte r, UByte lb, UByte b, UByte rb)
{
	c; lt; t; rt; l;  r;  lb;  b;  rb;

	if (t * b == 0 && t + b != 0)
	{
		return 255;
	}
	else
	{
		return c;
	}
	//UINT colorProduct = lt * t * rt * l * r * lb * b * rb;
	//UINT colorSum = lt + t + rt + l + r + lb + b + rb;
	//
	//if (colorProduct == 0 && colorSum != 0)
	//{
	//	return 255;
	//}
	//else
	//{
	//	return c;
	//}
}

UByte* FontData4AOD::GetGlyphBitmap(UByte* pBuff, unsigned nBuffSize, unsigned glyphCode, unsigned hintedSize, unsigned fuFormat, GLYPHMETRICS& gm)
{
	static const char* specialCharacterFont = "Microsoft YaHei";
	bool	  isChineseCharacter  = ( glyphCode >= 0x4e00 && glyphCode <= 0x9fa5 ) || ( glyphCode >= 0x2e80 && glyphCode <= 0xa4cf )
		|| ( glyphCode >= 0xf900 && glyphCode <= 0xfaff ) || ( glyphCode >= 0xfe30 && glyphCode <= 0xfe4f )
		|| ( glyphCode <= 127 );
	if ( isChineseCharacter && ( LastIsChineseCharacter != isChineseCharacter || hintedSize != LastHintedFontSize && isChineseCharacter ) )
	{
		if (HintedFont)
			::DeleteObject(HintedFont);

		HintedFont = ::CreateFontA(-int(hintedSize),             // height of font
			0,                          // average character width
			0,                          // angle of escapement
			0,                          // base-line orientation angle
			IsBold() ? FW_BOLD : FW_NORMAL, // font weight
			IsItalic(),                 // italic attribute option
			0,                          // underline attribute option
			0,                          // strikeout attribute option
			DEFAULT_CHARSET,            // character set identifier
			OUT_DEFAULT_PRECIS,         // output precision
			CLIP_DEFAULT_PRECIS,        // clipping precision
			ANTIALIASED_QUALITY,		// output quality
			DEFAULT_PITCH,              // pitch and family
			Name);						// typeface name
		LastHintedFontSize = hintedSize;
		LastIsChineseCharacter = isChineseCharacter;
	}
	else if ( !isChineseCharacter && ( LastIsChineseCharacter != isChineseCharacter || hintedSize != LastHintedFontSize && isChineseCharacter ) )
	{
		if (HintedFont)
			::DeleteObject(HintedFont);

		HintedFont = ::CreateFontA(-int(hintedSize),             // height of font
			0,                          // average character width
			0,                          // angle of escapement
			0,                          // base-line orientation angle
			IsBold() ? FW_BOLD : FW_NORMAL, // font weight
			IsItalic(),                 // italic attribute option
			0,                          // underline attribute option
			0,                          // strikeout attribute option
			DEFAULT_CHARSET,            // character set identifier
			OUT_DEFAULT_PRECIS,         // output precision
			CLIP_DEFAULT_PRECIS,        // clipping precision
			ANTIALIASED_QUALITY,		// output quality
			DEFAULT_PITCH,              // pitch and family
			specialCharacterFont);						// typeface name
		LastHintedFontSize = hintedSize;
		LastIsChineseCharacter = isChineseCharacter;
	}

	GFxGdiSelectObjectGuard g1(WinDC, HintedFont);

	int totalSize = 0;
	MAT2 im = { {0,1}, {0,0}, {0,0}, {0,1} };
	totalSize = ::GetGlyphOutlineW(WinDC,
		glyphCode,
		fuFormat,
		&gm,
		nBuffSize,
		pBuff,
		&im);

	if (totalSize == GDI_ERROR || totalSize >= (int)nBuffSize)
	{
		// An error has occurred. Most probably it's because
		// of not enough room in the buffer. So, request the buffer size,
		// reallocate, and try again. The second call may fail for
		// some other reason (no glyph); in this case there's nothing 
		// else to do, just return NULL. 
		// The buffer is reallocated with adding BufSizeInc in order
		// to reduce the number of reallocations.
		//----------------------------------
		int totalSizeReq = ::GetGlyphOutlineW(WinDC,
			glyphCode,
			fuFormat,
			&gm, 0, 0, &im);

		if(totalSizeReq == GDI_ERROR) 
			return NULL;

		pBuff = new UByte[totalSizeReq];

		totalSize = ::GetGlyphOutlineW(WinDC,
			glyphCode,
			fuFormat,
			&gm,
			totalSizeReq,
			pBuff,
			&im);

		if (totalSize == GDI_ERROR || totalSize > totalSizeReq)
		{
			delete [] pBuff;
			return NULL;
		}
	}

	return pBuff;
}

UByte GrayPixelBlend_Src0_Dest_With_Weight(UByte src, UByte dest)
{
	src;
	return dest / 8;
}

UByte GrayPixelBlend_Src0_Dest1(UByte src, UByte dest)
{
	src;
	return (dest > 0 ? (dest/* / 2 + 128*/) : 0/*128*/);
}

UByte GrayPixelBlend_With_Weight(UByte src, UByte dest)
{
	return (src + dest / 8);
	//	if (src > 0 || dest > 0)
	//	{
	//	return 255;
	//}
	//else
	//{
	//	return 0;
	//}
}

UByte GrayPixelBlend_Src_Dest_Bigger(UByte src, UByte dest)
{
	return (src > dest ? src : dest);
}

UByte GrayPixelBlend_Dest_Bigger_Than_128_Src_Less_Than_128(UByte src, UByte dest)
{
	if (dest > 0)
	{
		return dest / 2 + 128;
	}
	else
	{
		return src / 2;
	}
}

bool FontData4AOD::GetGlyphRaster( unsigned glyphIndex, unsigned hintedSize, Scaleform::Render::GlyphRaster* raster )
{
	//const AdvanceEntry& ae = (AdvanceTable[glyphIndex]);

	//hintedSize = ae.Advance * GGO_FontHeight / (20.0f * 1024);

	if (IsMissingGlyph(glyphIndex))
		return false;

	if (!IsHintedRasterGlyph(glyphIndex, hintedSize))
		return 0;

	//Lock::Locker locker(pFontLock);
	//GlyphType& glyph = Glyphs[glyphIndex];

	//LockRasterGlyph.DoLock();

	unsigned glyphCode = GetCharValue(glyphIndex);//CodeTable.Find();

	if (glyphCode == -1)
		return false;

	UByte buff[4096];
	GLYPHMETRICS gm;

	bool bContour = false;

	UByte* pSrc = NULL;

	if (bContour)
	{

		//pSrc = GetGlyphBitmap(buff, sizeof(buff), glyphCode, hintedSize, GGO_GRAY8_BITMAP, gm);
		//raster->Width  = gm.gmBlackBoxX;
		//raster->Height = gm.gmBlackBoxY;
		//raster->OriginX = gm.gmptGlyphOrigin.x;	// no matter bOutline is true or false, the origin is the same
		//raster->OriginY = gm.gmptGlyphOrigin.y;
		//raster->Raster.Resize(raster->Width * raster->Height);

		//UByte* pDest = &raster->Raster[0];
		//
		//decomposeGlyphBitmap<8, GrayPixelBlend_Src0_Dest1, DarkBoarder>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 0, 0);

		
		//////////////////////////////////////////////////////////////////////////

		const int offset = -1;
		const int doubleOffset = offset * (-2);
		pSrc = GetGlyphBitmap(buff, sizeof(buff), glyphCode, hintedSize/* - doubleOffset*/, GGO_GRAY8_BITMAP, gm);
		
		if (pSrc)
		{

			raster->Width  = gm.gmBlackBoxX + doubleOffset;
			raster->Height = gm.gmBlackBoxY + doubleOffset;
			raster->OriginX = gm.gmptGlyphOrigin.x;	// no matter bOutline is true or false, the origin is the same
			raster->OriginY = gm.gmptGlyphOrigin.y;//gm.gmptGlyphOrigin.y;
			raster->Raster.Resize(raster->Width * raster->Height);

			UByte* pDest = &raster->Raster[0];

			decomposeGlyphBitmap<8, GrayPixelBlend_Src0_Dest_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 0 + offset, -1 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, -1 + offset, 0 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 1 + offset, 0 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 0 + offset, 1 + offset);

			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, -1 + offset, -1 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 1 + offset, -1 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, -1 + offset, 1 + offset);
			decomposeGlyphBitmap<8, GrayPixelBlend_With_Weight, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 1 + offset, 1 + offset);
			
			decomposeGlyphBitmap<8, GrayPixelBlend_Dest_Bigger_Than_128_Src_Less_Than_128, NULL>(pSrc, pDest, gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 0 + offset, 0 + offset);
		}
	}
	else
	{
		pSrc = GetGlyphBitmap(buff, sizeof(buff), glyphCode, hintedSize, GGO_GRAY4_BITMAP, gm);

		if (pSrc)
		{
			raster->Width  = gm.gmBlackBoxX;
			raster->Height = gm.gmBlackBoxY;
			raster->OriginX = gm.gmptGlyphOrigin.x;	// no matter bOutline is true or false, the origin is the same
			raster->OriginY = gm.gmptGlyphOrigin.y;

			
			raster->Raster.Resize(raster->Width * raster->Height);
			UByte* pDest = &raster->Raster[0];

			decomposeGlyphBitmap<4, GrayPixelBlend_Src0_Dest1, NULL>(pSrc, pDest, 
				gm.gmBlackBoxX, gm.gmBlackBoxY, raster->Width, raster->Height, 0, 0);
		}
	}

	if (pSrc == NULL)
	{
		raster->Width  = 1;
		raster->Height = 1;
		raster->Raster.Resize(1);
		raster->Raster[0] = 0;
	}
	else if (pSrc != buff)
	{
		delete [] pSrc;
	}

	return true;
}

// =======================end zhaojun@snda=======================



namespace {
    struct Range { UInt16 start,end; };
    struct RangeLess  { bool operator()(const Range& r1, const Range& r2) const { return r1.start < r2.start; } };
}

static String BuildStringFromRanges(const Array<Range>& ranges)
{
    String ret;
    char buff[512];
    int countPrinted = 0;
    bool lastPrinted = true;
    UInt16 start = 0;
    UPInt i = 0;
    for(; i < ranges.GetSize(); ++i)
    {
        if (i == 0)
        {
            start = ranges[i].start;
            lastPrinted = false;
        }
        else
        {
            if (ranges[i].start > ranges[i-1].end + 1)
            {
                if (start == ranges[i-1].end)
                    Format(StringDataPtr(buff, sizeof(buff)), "0x{0:x}", start);
                else
                    Format(StringDataPtr(buff, sizeof(buff)), "0x{0:x}-0x{1:x}", start, ranges[i-1].end);
                lastPrinted = true;
                if (countPrinted)
                    ret += ", ";
                ret += buff;
                countPrinted++;
                if (countPrinted > 4)
                    break;
                start = ranges[i].start;
                lastPrinted = false;
            }
        }
    }
    if (!lastPrinted)
    {
        Format(StringDataPtr(buff, sizeof(buff)), "0x{0:x}-0x{1:x}", start, ranges[ranges.GetSize()-1].end);
        if (countPrinted)
            ret += ", ";
        ret += buff;
    }
    if ( i < ranges.GetSize() )
        ret += " (truncated)";
    return ret;
}
String FontData::GetCharRanges() const
{
    Array<Range> ranges;
    CodeTableType::ConstIterator it = CodeTable.Begin();
    UInt16 rangeStart = 0, prevValue = 0;
    bool rangeStarted = false;
    while( it != CodeTable.End() )
    {
        if (!rangeStarted)
        {
            rangeStart = it->First;
            rangeStarted = true;
        }
        else
        {
            if (prevValue != it->First-1)
            {
                Range range;
                range.start = rangeStart;
                range.end = prevValue;
                ranges.PushBack(range);
                rangeStarted = false;
                continue;
            }
        }
        prevValue = it->First;
        ++it;
    }
    if (rangeStarted)
    {
        Range range;
        range.start = rangeStart;
        range.end = prevValue;
        ranges.PushBack(range);
    }
    Alg::QuickSort(ranges, RangeLess());
    return BuildStringFromRanges(ranges);
}

//
struct Normalizer
{
    enum { FontHeight = 1024, ShapePageSize = 256-2 - 8-4 };

    Normalizer(unsigned nominalSize) : NominalSize(nominalSize) {}

    template<typename T>
    inline T norm(T v) const { return v * FontHeight / T(NominalSize); }
    template<typename T>
    inline T denorm(T v) const { return v * T(NominalSize) / FontHeight; }

    unsigned          NominalSize;
};

#if defined(GFX_ENABLE_COMPACTED_FONTS) || defined(GFX_ENABLE_FONT_COMPACTOR)
template<class FontType>
static inline ShapeDataBase* GetGlyphShape(const FontType& font, unsigned glyphIndex)
{
    typedef typename FontType::ContainerType ContainerType;
    typedef typename FontType::CompactedFontType CompactedFontType;

    if (glyphIndex >= font.GetCompactedFont().GetNumGlyphs())
        return NULL;

    typename CompactedFontType::GlyphPathIteratorType glyph(font.GetContainer());
    font.GetCompactedFont().GetGlyphShape(glyphIndex, &glyph);
    Normalizer n(font.GetCompactedFont().GetNominalSize());

    ShapeNoStyles* pshape = SF_HEAP_AUTO_NEW(&font) ShapeNoStyles(Normalizer::ShapePageSize);

    PathPacker path;
    bool shapeValid = false;

    while(!glyph.IsFinished())
    {
        path.Reset();
        path.SetFill0(1);
        path.SetFill1(0);
        path.SetMoveTo(n.norm(glyph.GetMoveX()), n.norm(glyph.GetMoveY()));

        int edge[5];
        while(!glyph.IsPathFinished())
        {
            glyph.ReadEdge(edge);
            if (edge[0] == CompactedFontType::PathDataDecoderType::Edge_Line)
                path.LineToAbs(n.norm(edge[1]), n.norm(edge[2]));
            else
                path.CurveToAbs(n.norm(edge[1]), n.norm(edge[2]), n.norm(edge[3]), n.norm(edge[4]));
        }

        if(!path.IsEmpty())
        {
            path.ClosePath();
            pshape->AddPath(&path);
            shapeValid = true;
        }
        glyph.AdvancePath();
    }
    if (!shapeValid)
    {
        delete pshape;
        pshape = NULL;
    }
    return pshape;
}

template <class FontType>
static inline RectF& GetGlyphBounds(const FontType& font, unsigned glyphIndex, RectF* prect)
{
    if (IsMissingGlyph(glyphIndex))
    {
        prect->x1 = prect->y1 = 0;
        prect->SetRect(Font::GetDefaultGlyphWidth(), Font::GetDefaultGlyphHeight());
    }
    else if (glyphIndex < font.GetCompactedFont().GetNumGlyphs())
    {
        font.GetCompactedFont().GetGlyphBounds(glyphIndex,prect);
    }
    else
    {
        prect->x1 = prect->y1 = 0;
        prect->SetRect(Font::GetDefaultGlyphWidth(), Font::GetDefaultGlyphHeight());
        //return *prect;
        //SF_ASSERT(0);
    }
    Normalizer n(font.GetCompactedFont().GetNominalSize());
    prect->x1   = n.norm(prect->x1);
    prect->y1    = n.norm(prect->y1);
    prect->x2  = n.norm(prect->x2);
    prect->y2 = n.norm(prect->y2);
    return *prect;
}

template<class FontType>
static String GetCharRanges(const FontType& font)
{
    Array<Range> ranges;
    UInt16 rangeStart = 0, prevValue = 0;
    bool rangeStarted = false;
    for(unsigned i = 0; i < font.GetGlyphShapeCount();)
    {
        if (!rangeStarted)
        {
            rangeStart = (UInt16)font.GetCompactedFont().GetGlyphCode(i);
            rangeStarted = true;
        }
        else
        {
            if (prevValue != (UInt16)font.GetCompactedFont().GetGlyphCode(i)-1)
            {
                Range range;
                range.start = rangeStart;
                range.end = prevValue;
                ranges.PushBack(range);
                rangeStarted = false;
                continue;
            }
        }
        prevValue = (UInt16)font.GetCompactedFont().GetGlyphCode(i);
        ++i;
    }
    if (rangeStarted)
    {
        Range range;
        range.start = rangeStart;
        range.end = prevValue;
        ranges.PushBack(range);
    }
    Alg::QuickSort(ranges, RangeLess());
    return BuildStringFromRanges(ranges);
}
#endif

#ifdef GFX_ENABLE_FONT_COMPACTOR
// ***** FontDataCompactedSwf

FontDataCompactedSwf::FontDataCompactedSwf() 
    : Container(),CompactedFontValue(Container),NumGlyphs(0)
{
}
FontDataCompactedSwf::~FontDataCompactedSwf()
{

}
// *** GFX/SWF Loading methods.
void FontDataCompactedSwf::Read(LoadProcess* p, const TagInfo& tagInfo)
{
    SF_ASSERT(tagInfo.TagType == Tag_DefineFont2 ||
            tagInfo.TagType == Tag_DefineFont3);

    Stream * pin = p->GetStream();
    bool        isLoadingFontShapes = p->IsLoadingFontShapes();

    // No AddRef() here, to avoid cycle.
    // OwningMovie is our owner, so it has a ref to us.
    //OwningMovie = p->GetDataDef();    

    if ((tagInfo.TagType == Tag_DefineFont2) || (tagInfo.TagType == Tag_DefineFont3))
    {
        SF_ASSERT(p->GetLoadStates()->GetFontCompactorParams());
        unsigned nominalSize = p->GetLoadStates()->GetFontCompactorParams()->GetNominalSize();
        bool mergeContours = p->GetLoadStates()->GetFontCompactorParams()->NeedMergeContours();
        FontCompactor compactor(Container);

        if (tagInfo.TagType == Tag_DefineFont2)
            pin->LogParse("reading DefineFont2: ");
        else
            pin->LogParse("reading DefineFont3: ");

        bool    hasLayout = (pin->ReadUInt(1) != 0);
        SetHasLayout(hasLayout);

        bool shiftJisFlag        = (pin->ReadUInt(1) != 0);
        bool pixelAlignedChars   = (pin->ReadUInt(1) != 0);
        bool ansiFlag            = (pin->ReadUInt(1) != 0);

        if (shiftJisFlag)  SetCodePage(FF_CodePage_ShiftJis);
        else if (ansiFlag) SetCodePage(FF_CodePage_Ansi);
        else               SetCodePage(FF_CodePage_Unicode);

        SF_UNUSED(pixelAlignedChars);       

        bool    wideOffsets = (pin->ReadUInt(1) != 0);
        SetWideCodes(pin->ReadUInt(1) != 0);
        SetItalic(pin->ReadUInt(1) != 0);
        SetBold(pin->ReadUInt(1) != 0);
        UByte   langCode = pin->ReadU8(); // Language code

        // Inhibit warning.
        langCode = langCode;

        String name;
        pin->ReadStringWithLength(&name);        

        NumGlyphs = pin->ReadU16();

        if (pin->IsVerboseParse())
        {
            pin->LogParse("  Name = %s, %d glyphs\n", name.ToCStr() ? name.ToCStr() : "(none)", NumGlyphs);

            const char* pcodePage = "Unicode";
            if (GetCodePage() == FF_CodePage_ShiftJis)
                pcodePage = "ShiftJIS";
            else if (GetCodePage() == FF_CodePage_Ansi)
                pcodePage = "ANSI";

            pin->LogParse("  HasLayout = %d, CodePage = %s, Italic = %d, Bold = %d\n", 
                (int)hasLayout, pcodePage, IsItalic(), IsBold());
            pin->LogParse("  LangCode = %d\n", langCode);
        }

        int tableBase = pin->Tell();

        // Read the glyph offsets.  Offsets
        // are measured from the start of the
        // offset table.
        Array<int>    offsets;
        int fontCodeOffset;

        int offsetsCount = NumGlyphs;
        if (NumGlyphs > 0)
        {
            // check for the first offset. If it is 0 then shapes
            // were stripped from the tag.
            unsigned off0 = (wideOffsets) ? (unsigned)pin->ReadU32() : (unsigned)pin->ReadU16();
            if (off0 == 0)
            {
                // special case for tags with stripped font shapes
                isLoadingFontShapes = false;
                offsetsCount = 0;
            }
            else
                offsets.PushBack(off0);
        }
        if (wideOffsets)
        {
            // 32-bit offsets.
            for (int i = 1; i < offsetsCount; i++)
            {
                offsets.PushBack(pin->ReadU32());
            }
            fontCodeOffset = pin->ReadU32();
        }
        else
        {
            // 16-bit offsets.
            for (int i = 1; i < offsetsCount; i++)
            {
                offsets.PushBack(pin->ReadU16());
            }
            fontCodeOffset = pin->ReadU16();
        }

        compactor.StartFont(name.ToCStr(),Flags,nominalSize,0,0,0);
        Normalizer n(nominalSize);
        
        //    TextureGlyphs.Resize(Glyphs.GetSize());
        //Glyphs.Resize(glyphCount);
        //pPath = new PathAllocator;
        if (isLoadingFontShapes)
        {
            TagType fontGlyphShapeTag = (tagInfo.TagType == Tag_DefineFont2) ?
                                            Tag_DefineShape2 : tagInfo.TagType;

            // Allocate PathAllocator so that it properly uses 'this' heap.
            PathAllocator* ppathAllocator = SF_HEAP_AUTO_NEW(this) PathAllocator;

            // Read the glyph shapes.
            for (unsigned i = 0; i < NumGlyphs; i++)
            {
                // Seek to the start of the shape data.
                int newPos = tableBase + offsets[i];
                // if we're seeking backwards, then that looks like a bug.
                SF_ASSERT(newPos >= pin->Tell());
                pin->SetPosition(newPos);

                SPInt shapeDataLen;
                if (i + 1 < NumGlyphs)
                    shapeDataLen = offsets[i + 1] - offsets[i];
                else
                    shapeDataLen = fontCodeOffset - offsets[i];
                SF_ASSERT(shapeDataLen >= 0);

                // Create & read the shape.
                compactor.StartGlyph();                
                ConstShapeNoStyles s;
                s.Read(p, fontGlyphShapeTag, (unsigned)shapeDataLen, false, ppathAllocator);

                //Ptr<ConstShapeNoStyles> s = *new ConstShapeNoStyles;
                //s->Read(p, fontGlyphShapeTag, (unsigned)shapeDataLen, false, pPath);
                //Glyphs[i] = s;

                SwfPathData::PathsIterator pit = s.GetNativePathsIterator();
                while(!pit.IsFinished())
                {
                    if (pit.IsNewShape())
                    {
                        pit.Skip();
                        continue;
                    }
                    SwfPathData::EdgesIterator eit = pit.GetEdgesIterator();
                    float mx[2];
                    eit.GetMoveXY(&mx[0], &mx[1]);
                    compactor.MoveTo((SInt16)n.denorm(mx[0]),(SInt16)n.denorm(mx[1]));
                    while (!eit.IsFinished())
                    {
                        SwfPathData::EdgesIterator::Edge edge;
                        eit.GetEdge(&edge);
                        if (edge.Curve)
                            compactor.QuadTo((SInt16)n.denorm(edge.Cx),(SInt16)n.denorm(edge.Cy),
                                             (SInt16)n.denorm(edge.Ax),(SInt16)n.denorm(edge.Ay));
                        else
                            compactor.LineTo((SInt16)n.denorm(edge.Ax),(SInt16)n.denorm(edge.Ay));
                    }
                    pit.AdvanceBy(eit);
                }

                compactor.EndGlyph(mergeContours);

                ppathAllocator->Clear();
            }

            delete ppathAllocator;

            int currentPosition = pin->Tell();
            if (fontCodeOffset + tableBase != currentPosition)
            {
                // Bad offset!  Don't try to read any more.
                return;
            }
        }
        else
        {
            // Skip the shape data.
            int newPos = tableBase + fontCodeOffset;
            if (newPos >= pin->GetTagEndPosition())
            {
                // No layout data!
                return;
            }

            pin->SetPosition(newPos);
            SetGlyphShapesStripped();
        }

        pin->LogParse("reading code table at offset %d\n", pin->Tell());

        if (AreWideCodes())
        {
            // Code table is made of UInt16's.
            for (UPInt i = 0, n = NumGlyphs; i < n; i++)
                compactor.AssignGlyphCode((unsigned)i, pin->ReadU16());
        }
        else
        {
            // Code table is made of bytes.
            for (UPInt i = 0, n = NumGlyphs; i < n; i++)
                compactor.AssignGlyphCode((unsigned)i, pin->ReadU8());
        }

        // Read layout info for the glyphs.
        if (hasLayout)
        {
            // Multiplier used for scaling.
            // In SWF 8, font shape constant resolution (tag 75) was increased by 20.
            float sfactor = (tagInfo.TagType == Tag_DefineFont3) ? 1.0f / 20.0f : 1.0f;

            Ascent = (float) pin->ReadS16() * sfactor;
            Descent = (float) pin->ReadS16() * sfactor;
            Leading = (float) pin->ReadS16() * sfactor;

            compactor.UpdateMetrics(n.denorm((int)Ascent),n.denorm((int)Descent),n.denorm((int)Leading));

            if (pin->IsVerboseParse())
            {
                pin->LogParse("  Ascent = %d, Descent = %d, Leading = %d\n", 
                    (int)Ascent, (int)Descent, (int)Leading);
            }

            for (UPInt i = 0, k = NumGlyphs; i < k; i++)
                compactor.AssignGlyphAdvance((unsigned)i,n.denorm((int)(pin->ReadU16() * sfactor)));

            // Bounds table.
            //BoundsTable.Resize(Glyphs.GetSize());    // kill
            RectF  dummyRect;
            {for (UPInt i = 0, k = NumGlyphs; i < k; i++)
            {
                //BoundsTable[i].Read(pin);  // kill
                pin->ReadRect(&dummyRect);                   
            }}

            // Kerning pairs.
            int kerningCount = pin->ReadU16();
            if (pin->IsVerboseParse())
            {
                pin->LogParse("  KerningCount = %d\n", (int)kerningCount);
            }
            {for (int i = 0; i < kerningCount; i++)
            {
                UInt16  char0, char1;
                if (AreWideCodes())
                {
                    char0 = pin->ReadU16();
                    char1 = pin->ReadU16();
                }
                else
                {
                    char0 = pin->ReadU8();
                    char1 = pin->ReadU8();
                }
                float   adjustment = (float) pin->ReadS16() * sfactor;

                if (pin->IsVerboseParse())
                    pin->LogParse("     Pair: %d - %d,\tadj = %d\n", (int)char0, (int)char1, (int)adjustment);

                compactor.AddKerningPair(char0, char1, n.denorm((int)adjustment));
            }}
        }
        compactor.EndFont();
        CompactedFontValue.AcquireFont(0);
    }
}

int FontDataCompactedSwf::GetGlyphIndex(UInt16 code) const
{
    return CompactedFontValue.GetGlyphIndex(code);
}

int FontDataCompactedSwf::GetCharValue(unsigned glyphIndex) const
{
    if (glyphIndex < CompactedFontValue.GetNumGlyphs())
        return CompactedFontValue.GetGlyphCode(glyphIndex);    
    return -1;
}

ShapeDataBase* FontDataCompactedSwf::GetGlyphShape(unsigned glyphIndex, unsigned)
{
    return GFx::GetGlyphShape(*this, glyphIndex);
}

float FontDataCompactedSwf::GetAdvance(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex) || glyphIndex >= CompactedFontValue.GetNumGlyphs())
        return GetDefaultGlyphWidth();

    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetAdvance(glyphIndex));
}
float FontDataCompactedSwf::GetKerningAdjustment(unsigned lastCode, unsigned thisCode) const
{
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetKerningAdjustment(lastCode,thisCode));
}

unsigned FontDataCompactedSwf::GetGlyphShapeCount() const
{
    return NumGlyphs;//CompactedFontValue.GetNumGlyphs();
}

float FontDataCompactedSwf::GetGlyphWidth(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex) || glyphIndex >= CompactedFontValue.GetNumGlyphs())
        return GetDefaultGlyphWidth();
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetGlyphWidth(glyphIndex));
}

float FontDataCompactedSwf::GetGlyphHeight(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex) || glyphIndex >= CompactedFontValue.GetNumGlyphs())
        return GetDefaultGlyphHeight();
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetGlyphHeight(glyphIndex));
}

RectF& FontDataCompactedSwf::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
{
    return GFx::GetGlyphBounds(*this, glyphIndex, prect);
}

// Slyph/State access.
const char* FontDataCompactedSwf::GetName() const
{
    return CompactedFontValue.GetName();
}

String FontDataCompactedSwf::GetCharRanges() const
{
    return GFx::GetCharRanges(*this);
}
bool FontDataCompactedSwf::HasVectorOrRasterGlyphs() const
{
    return NumGlyphs != 0; //CompactedFontValue.GetNumGlyphs() != 0;
}
#endif //#ifdef GFX_ENABLE_FONT_COMPACTOR


#ifdef GFX_ENABLE_COMPACTED_FONTS
// *** FontDataCompactedGfx implementation
//
FontDataCompactedGfx::FontDataCompactedGfx() 
: CompactedFontValue(Container)
{
}
FontDataCompactedGfx::~FontDataCompactedGfx()
{
}
// *** GFX/SWF Loading methods.
void FontDataCompactedGfx::Read(LoadProcess* p, const TagInfo& tagInfo)
{
    SF_ASSERT(tagInfo.TagType == Tag_DefineCompactedFont);

    Stream * pin = p->GetStream();
    //bool        isLoadingFontShapes = p->IsLoadingFontShapes();
    //UInt16 fontId = pin->ReadU16();

    pin->LogParse("reading DefineCompactedFont:\n");

    int csize = tagInfo.TagLength - 2;
    ArrayUnsafePOD<UByte> buf;
    buf.Resize(4096);
    Container.Reserve(csize);
    int bytes = 0;
    do
    {
        int bytesToRead = Alg::Min(4096, csize - bytes);
        int bytesRead = pin->ReadToBuffer(&buf[0], bytesToRead);
        bytes += bytesRead;
        if (bytesRead > 0)
        {
            for(int i = 0; i < bytesRead; ++i)
                Container.PushBack(buf[i]);
        }
        if (bytesRead != bytesToRead)
        {
            //SF_DEBUG_ERROR1(1, "Empty advance table in font %s", GetName());
            pin->LogError("Could not read tag DefineCompactedFont. Broken gfx file.");
            break;
        }
    }
    while(bytes < csize);

    CompactedFontValue.AcquireFont(0);
    if (CompactedFontValue.GetNominalSize() <= 0)
    {
        pin->LogError("Invalid nominal size for DefineCompactedFont, font %s. Broken gfx file.", GetName());
        SetFontMetrics(0, 960, 1024-960);
    }
    else
    {
        const float scale = 1024.f/CompactedFontValue.GetNominalSize();
        SetFontMetrics(CompactedFontValue.GetLeading()*scale, CompactedFontValue.GetAscent()*scale, CompactedFontValue.GetDescent()*scale);
        pin->LogParse(   "read font \"%s\"\n", GetName());
        Flags = CompactedFontValue.GetFontFlags();
    }
}

int FontDataCompactedGfx::GetGlyphIndex(UInt16 code) const
{
    return CompactedFontValue.GetGlyphIndex(code);
}

int     FontDataCompactedGfx::GetCharValue(unsigned glyphIndex) const
{
    if (glyphIndex < CompactedFontValue.GetNumGlyphs())
        return CompactedFontValue.GetGlyphCode(glyphIndex);    
    return -1;
}

ShapeDataBase* FontDataCompactedGfx::GetGlyphShape(unsigned glyphIndex, unsigned)
{
    return GFx::GetGlyphShape(*this, glyphIndex);
}

float FontDataCompactedGfx::GetAdvance(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex))
        return GetDefaultGlyphWidth();
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetAdvance(glyphIndex));
}

float FontDataCompactedGfx::GetKerningAdjustment(unsigned lastCode, unsigned thisCode) const
{
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetKerningAdjustment(lastCode,thisCode));
}

unsigned FontDataCompactedGfx::GetGlyphShapeCount() const
{
    return CompactedFontValue.GetNumGlyphs();
}

float FontDataCompactedGfx::GetGlyphWidth(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex))
        return GetDefaultGlyphWidth();
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetGlyphWidth(glyphIndex));
}
float FontDataCompactedGfx::GetGlyphHeight(unsigned glyphIndex) const
{
    if (IsMissingGlyph(glyphIndex))
        return GetDefaultGlyphHeight();
    Normalizer n(CompactedFontValue.GetNominalSize());
    return n.norm(CompactedFontValue.GetGlyphHeight(glyphIndex));
}
RectF& FontDataCompactedGfx::GetGlyphBounds(unsigned glyphIndex, RectF* prect) const
{
    return GFx::GetGlyphBounds(*this, glyphIndex, prect);
}

// Glyph/State access.
const char* FontDataCompactedGfx::GetName() const
{
    return CompactedFontValue.GetName();
}

String FontDataCompactedGfx::GetCharRanges() const
{
    return GFx::GetCharRanges(*this);
}
bool FontDataCompactedGfx::HasVectorOrRasterGlyphs() const
{
    return CompactedFontValue.GetNumGlyphs() != 0;
}
#endif //#ifdef GFX_ENABLE_COMPACTED_FONTS

// ***** FontDataBound
struct TextureGlyphBinder : public TextureGlyphData::TextureGlyphVisitor
{
    ResourceBinding* ResBinding;

    TextureGlyphBinder(ResourceBinding* resBnd) : ResBinding(resBnd) {}
    virtual void Visit(unsigned /*index*/, TextureGlyph* ptextureGlyph)
    {
        if (!ptextureGlyph->pImage && ptextureGlyph->BindIndex != ~0u)
        {
            ResourceBindData rdata;
            ResBinding->GetResourceData(&rdata, ptextureGlyph->BindIndex);
            if (rdata.pResource.GetPtr() && rdata.pResource->GetResourceType() == Resource::RT_Image)
            {
                ImageResource* imgRes       = static_cast<ImageResource*>(rdata.pResource.GetPtr());
                ptextureGlyph->pImage = static_cast<Image*>(imgRes->GetImage());
                ptextureGlyph->BindIndex = ~0u;
            }
            else // - type of resource is wrong, warning?
            {
                //SF_ASSERT(0); //?
            }
        }
    }
};

FontDataBound::FontDataBound(Font* pfont, ResourceBinding* pbinding) 
    : Font(*pfont), pFont(pfont)
{
    // make a copy of TextureGlyphData and resolve image resources in it.
    SF_ASSERT(pfont->HasTextureGlyphs() && pbinding);

    const TextureGlyphData* srcTGData = static_cast<const TextureGlyphData*>(pfont->GetTextureGlyphData());
    pTGData = *SF_HEAP_AUTO_NEW(this) TextureGlyphData(*srcTGData);

    TextureGlyphBinder binder(pbinding);
    pTGData->VisitTextureGlyphs(&binder);
}

const TextureGlyph* FontDataBound::GetTextureGlyph(unsigned glyphIndex) const
{
    if (pTGData && glyphIndex < pTGData->GetTextureGlyphCount())
        return &pTGData->GetTextureGlyph(glyphIndex);
    return NULL;
}

// ***** FontResource

FontResource::FontResource(Font *pfont, ResourceBinding* pbinding)
    : pBinding(pbinding)
{    
    pFont           = pfont;
    LowerCaseTop    = 0;
    UpperCaseTop    = 0;
}

FontResource::FontResource(Font *pfont, const ResourceKey& key)
    : pBinding(0)
{    
    pFont           = pfont;
    FontKey         = key;
    LowerCaseTop    = 0;
    UpperCaseTop    = 0;
}


UInt16 FontResource::calcTopBound(UInt16 code)
{
    RectF bounds;

    int idx = pFont->GetGlyphIndex(code);
    if (idx != -1)
    {
        /*
        Ptr<ShapeDataBase> shape = *GetGlyphShape(idx, 0);
        if (shape)
        {
            shape->ComputeBound(&bounds);
            return UInt16(-bounds.y1);
        }
        */
        pFont->GetGlyphBounds(idx,&bounds);
        return UInt16(-bounds.y1);
    }
    return 0;
}


void FontResource::calcLowerUpperTop(Log* log)
{
    SInt16 lowerCaseTop = 0;
    SInt16 upperCaseTop = 0;
    if (pFont && LowerCaseTop == 0 && UpperCaseTop == 0)
    {
        const UByte upperCaseCandidates[] = "HEFTUVWXZ";
        const UByte lowerCaseCandidates[] = "zxvwy";
        
        const UByte* p;
        for (p = upperCaseCandidates; *p; ++p)
        {
            upperCaseTop = calcTopBound(*p);
            if (upperCaseTop)
                break;
        }

        if (upperCaseTop)
        {
            for (p = lowerCaseCandidates; *p; ++p)
            {
                lowerCaseTop = calcTopBound(*p);
                if (lowerCaseTop)
                    break;
            }
        }
    }
    if (lowerCaseTop && upperCaseTop)
    {
        LowerCaseTop = lowerCaseTop;
        UpperCaseTop = upperCaseTop;
    }
    else
    {
        if (log)
            log->LogWarning("Font '%s%s%s' has no hinting chars "
                            "(any of 'HEFTUVWXZ' and 'zxvwy'). Auto-Hinting disabled.", 
                            GetName(), 
                            pFont->IsBold() ? " Bold" : "", 
                            pFont->IsItalic() ? " Italic" : "");
        LowerCaseTop = -1;
        UpperCaseTop = -1;
    }
}


FontResource::~FontResource()
{
//     if (HandlerArrayFlag)
//     {
//         for (unsigned i=0; i<pHandlerArray->GetSize(); i++)
//             (*pHandlerArray)[i]->OnDispose(this);
//     }
//     else if (pHandler)
//     {
//         pHandler->OnDispose(this);
//     }
}

// *** System FontProvider resource key

// We store system fonts obtained from FontProvider is ResourceLib so
// that they are re-used it requested several times.

class GFxSystemFontResourceKey : public RefCountBase<GFxSystemFontResourceKey, StatMD_Fonts_Mem>
{
    // Image States.  
    Ptr<FontProvider>   pFontProvider;
    String               FontName;
    unsigned                CreateFontFlags;
public:

    GFxSystemFontResourceKey(const char* pname, unsigned fontFlags,
                             FontProvider* pfontProvider)
    {        
        FontName        = String(pname).ToLower(); // Font names are case-insensitive.   
        CreateFontFlags = fontFlags & FontData::FF_Style_Mask;
        pFontProvider   = pfontProvider;
    }

    bool operator == (GFxSystemFontResourceKey& other) const
    {
        return (FontName == other.FontName &&
                pFontProvider == other.pFontProvider &&
                CreateFontFlags == other.CreateFontFlags);
    }

    UPInt  GetHashCode() const
    {
        UPInt hashCode = String::BernsteinHashFunctionCIS(
                            FontName.ToCStr(), FontName.GetSize());
        return CreateFontFlags ^ hashCode ^            
            ((UPInt)pFontProvider.GetPtr()) ^ (((UPInt)pFontProvider.GetPtr()) >> 7);
    }
};

class GFxSystemFontResourceKeyInterface : public ResourceKey::KeyInterface
{
public:
    typedef ResourceKey::KeyHandle KeyHandle;    

    // ResourceKey::KeyInterface implementation.    
    virtual void                AddRef(KeyHandle hdata)     { ((GFxSystemFontResourceKey*) hdata)->AddRef(); }
    virtual void                Release(KeyHandle hdata)    { ((GFxSystemFontResourceKey*) hdata)->Release(); }
    
    virtual ResourceKey::KeyType GetKeyType(KeyHandle hdata) const
    {
        SF_UNUSED(hdata);
        return ResourceKey::Key_None;
    }
    virtual UPInt               GetHashCode(KeyHandle hdata) const
    {
        return ((GFxSystemFontResourceKey*) hdata)->GetHashCode();
    }

    virtual bool                KeyEquals(KeyHandle hdata, const ResourceKey& other);
};

static GFxSystemFontResourceKeyInterface GFxSystemFontResourceKeyInterface_Instance;

bool    GFxSystemFontResourceKeyInterface::KeyEquals(KeyHandle hdata, const ResourceKey& other)
{
    if (this != other.GetKeyInterface())
        return 0;

    GFxSystemFontResourceKey* pthisData = (GFxSystemFontResourceKey*) hdata;
    GFxSystemFontResourceKey* potherData = (GFxSystemFontResourceKey*) other.GetKeyData();
    SF_ASSERT(pthisData && potherData);    
    return (*pthisData == *potherData);
}


ResourceKey FontResource::CreateFontResourceKey(const char* pname, unsigned fontFlags,
                                                      FontProvider* pfontProvider)
{
    Ptr<GFxSystemFontResourceKey> pdata =
        *new GFxSystemFontResourceKey(pname, fontFlags, pfontProvider);

    return ResourceKey(&GFxSystemFontResourceKeyInterface_Instance,
                          (ResourceKey::KeyHandle)pdata.GetPtr() );
}



// Static helper function used to lookup and/or create a font resource from provider.
FontResource* FontResource::CreateFontResource(const char* pname, unsigned fontFlags,
                                                     FontProvider* pprovider,
                                                     ResourceWeakLib *plib)
{
    SF_ASSERT(pname && pprovider && plib);

    // Create a search key.
    ResourceKey              fontKey = CreateFontResourceKey(pname, fontFlags, pprovider);
    ResourceLib::BindHandle  bh;
    FontResource*            pfontRes = 0;

    if (plib->BindResourceKey(&bh, fontKey) == ResourceLib::RS_NeedsResolve)
    {
        // If hot found, create the font object.
        Ptr<Render::Font> pexternalFont = *pprovider->CreateFont(pname, fontFlags);
        if (pexternalFont)        
            pfontRes = SF_NEW FontResource(pexternalFont, fontKey);
        
        if (pfontRes)
        {
            bh.ResolveResource(pfontRes);
        }
        else
        {   // No error messages are logged for failed system font creation.
            bh.CancelResolve("");
        }
    }
    else
    {
        // If Available, wait for resource to become available.
        pfontRes = (FontResource*)bh.WaitForResolve();
        SF_ASSERT(pfontRes->GetResourceType() == RT_Font);        
    }

    return pfontRes;
}

// Resolves TextureGlyphData (images), if any. Called from BindNextFrame.
void FontResource::ResolveTextureGlyphs()
{
    if (pFont->HasTextureGlyphs())
        pFont       = *SF_HEAP_AUTO_NEW(this) FontDataBound(pFont, pBinding);
}

}} // Scaleform::GFx
