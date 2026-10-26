//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFormat.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextFormat.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
using namespace Render;
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_alignGet, Value> TFunc_Instances_TextFormat_alignGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_alignSet, Value, const Value&> TFunc_Instances_TextFormat_alignSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_blockIndentGet, Value> TFunc_Instances_TextFormat_blockIndentGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_blockIndentSet, Value, const Value&> TFunc_Instances_TextFormat_blockIndentSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_boldGet, Value> TFunc_Instances_TextFormat_boldGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_boldSet, Value, const Value&> TFunc_Instances_TextFormat_boldSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_bulletGet, Value> TFunc_Instances_TextFormat_bulletGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_bulletSet, Value, const Value&> TFunc_Instances_TextFormat_bulletSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_colorGet, Value> TFunc_Instances_TextFormat_colorGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_colorSet, Value, const Value&> TFunc_Instances_TextFormat_colorSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_fontGet, Value> TFunc_Instances_TextFormat_fontGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_fontSet, Value, const Value&> TFunc_Instances_TextFormat_fontSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_indentGet, Value> TFunc_Instances_TextFormat_indentGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_indentSet, Value, const Value&> TFunc_Instances_TextFormat_indentSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_italicGet, Value> TFunc_Instances_TextFormat_italicGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_italicSet, Value, const Value&> TFunc_Instances_TextFormat_italicSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_kerningGet, Value> TFunc_Instances_TextFormat_kerningGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_kerningSet, Value, const Value&> TFunc_Instances_TextFormat_kerningSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_leadingGet, Value> TFunc_Instances_TextFormat_leadingGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_leadingSet, Value, const Value&> TFunc_Instances_TextFormat_leadingSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_leftMarginGet, Value> TFunc_Instances_TextFormat_leftMarginGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_leftMarginSet, Value, const Value&> TFunc_Instances_TextFormat_leftMarginSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_letterSpacingGet, Value> TFunc_Instances_TextFormat_letterSpacingGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_letterSpacingSet, Value, const Value&> TFunc_Instances_TextFormat_letterSpacingSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_rightMarginGet, Value> TFunc_Instances_TextFormat_rightMarginGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_rightMarginSet, Value, const Value&> TFunc_Instances_TextFormat_rightMarginSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_sizeGet, Value> TFunc_Instances_TextFormat_sizeGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_sizeSet, Value, const Value&> TFunc_Instances_TextFormat_sizeSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_tabStopsGet, Value> TFunc_Instances_TextFormat_tabStopsGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_tabStopsSet, Value, const Value&> TFunc_Instances_TextFormat_tabStopsSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_targetGet, Value> TFunc_Instances_TextFormat_targetGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_targetSet, Value, const Value&> TFunc_Instances_TextFormat_targetSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_underlineGet, Value> TFunc_Instances_TextFormat_underlineGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_underlineSet, Value, const Value&> TFunc_Instances_TextFormat_underlineSet;
typedef ThunkFunc0<Instances::TextFormat, Instances::TextFormat::mid_urlGet, Value> TFunc_Instances_TextFormat_urlGet;
typedef ThunkFunc1<Instances::TextFormat, Instances::TextFormat::mid_urlSet, Value, const Value&> TFunc_Instances_TextFormat_urlSet;

template <> const TFunc_Instances_TextFormat_alignGet::TMethod TFunc_Instances_TextFormat_alignGet::Method = &Instances::TextFormat::alignGet;
template <> const TFunc_Instances_TextFormat_alignSet::TMethod TFunc_Instances_TextFormat_alignSet::Method = &Instances::TextFormat::alignSet;
template <> const TFunc_Instances_TextFormat_blockIndentGet::TMethod TFunc_Instances_TextFormat_blockIndentGet::Method = &Instances::TextFormat::blockIndentGet;
template <> const TFunc_Instances_TextFormat_blockIndentSet::TMethod TFunc_Instances_TextFormat_blockIndentSet::Method = &Instances::TextFormat::blockIndentSet;
template <> const TFunc_Instances_TextFormat_boldGet::TMethod TFunc_Instances_TextFormat_boldGet::Method = &Instances::TextFormat::boldGet;
template <> const TFunc_Instances_TextFormat_boldSet::TMethod TFunc_Instances_TextFormat_boldSet::Method = &Instances::TextFormat::boldSet;
template <> const TFunc_Instances_TextFormat_bulletGet::TMethod TFunc_Instances_TextFormat_bulletGet::Method = &Instances::TextFormat::bulletGet;
template <> const TFunc_Instances_TextFormat_bulletSet::TMethod TFunc_Instances_TextFormat_bulletSet::Method = &Instances::TextFormat::bulletSet;
template <> const TFunc_Instances_TextFormat_colorGet::TMethod TFunc_Instances_TextFormat_colorGet::Method = &Instances::TextFormat::colorGet;
template <> const TFunc_Instances_TextFormat_colorSet::TMethod TFunc_Instances_TextFormat_colorSet::Method = &Instances::TextFormat::colorSet;
template <> const TFunc_Instances_TextFormat_fontGet::TMethod TFunc_Instances_TextFormat_fontGet::Method = &Instances::TextFormat::fontGet;
template <> const TFunc_Instances_TextFormat_fontSet::TMethod TFunc_Instances_TextFormat_fontSet::Method = &Instances::TextFormat::fontSet;
template <> const TFunc_Instances_TextFormat_indentGet::TMethod TFunc_Instances_TextFormat_indentGet::Method = &Instances::TextFormat::indentGet;
template <> const TFunc_Instances_TextFormat_indentSet::TMethod TFunc_Instances_TextFormat_indentSet::Method = &Instances::TextFormat::indentSet;
template <> const TFunc_Instances_TextFormat_italicGet::TMethod TFunc_Instances_TextFormat_italicGet::Method = &Instances::TextFormat::italicGet;
template <> const TFunc_Instances_TextFormat_italicSet::TMethod TFunc_Instances_TextFormat_italicSet::Method = &Instances::TextFormat::italicSet;
template <> const TFunc_Instances_TextFormat_kerningGet::TMethod TFunc_Instances_TextFormat_kerningGet::Method = &Instances::TextFormat::kerningGet;
template <> const TFunc_Instances_TextFormat_kerningSet::TMethod TFunc_Instances_TextFormat_kerningSet::Method = &Instances::TextFormat::kerningSet;
template <> const TFunc_Instances_TextFormat_leadingGet::TMethod TFunc_Instances_TextFormat_leadingGet::Method = &Instances::TextFormat::leadingGet;
template <> const TFunc_Instances_TextFormat_leadingSet::TMethod TFunc_Instances_TextFormat_leadingSet::Method = &Instances::TextFormat::leadingSet;
template <> const TFunc_Instances_TextFormat_leftMarginGet::TMethod TFunc_Instances_TextFormat_leftMarginGet::Method = &Instances::TextFormat::leftMarginGet;
template <> const TFunc_Instances_TextFormat_leftMarginSet::TMethod TFunc_Instances_TextFormat_leftMarginSet::Method = &Instances::TextFormat::leftMarginSet;
template <> const TFunc_Instances_TextFormat_letterSpacingGet::TMethod TFunc_Instances_TextFormat_letterSpacingGet::Method = &Instances::TextFormat::letterSpacingGet;
template <> const TFunc_Instances_TextFormat_letterSpacingSet::TMethod TFunc_Instances_TextFormat_letterSpacingSet::Method = &Instances::TextFormat::letterSpacingSet;
template <> const TFunc_Instances_TextFormat_rightMarginGet::TMethod TFunc_Instances_TextFormat_rightMarginGet::Method = &Instances::TextFormat::rightMarginGet;
template <> const TFunc_Instances_TextFormat_rightMarginSet::TMethod TFunc_Instances_TextFormat_rightMarginSet::Method = &Instances::TextFormat::rightMarginSet;
template <> const TFunc_Instances_TextFormat_sizeGet::TMethod TFunc_Instances_TextFormat_sizeGet::Method = &Instances::TextFormat::sizeGet;
template <> const TFunc_Instances_TextFormat_sizeSet::TMethod TFunc_Instances_TextFormat_sizeSet::Method = &Instances::TextFormat::sizeSet;
template <> const TFunc_Instances_TextFormat_tabStopsGet::TMethod TFunc_Instances_TextFormat_tabStopsGet::Method = &Instances::TextFormat::tabStopsGet;
template <> const TFunc_Instances_TextFormat_tabStopsSet::TMethod TFunc_Instances_TextFormat_tabStopsSet::Method = &Instances::TextFormat::tabStopsSet;
template <> const TFunc_Instances_TextFormat_targetGet::TMethod TFunc_Instances_TextFormat_targetGet::Method = &Instances::TextFormat::targetGet;
template <> const TFunc_Instances_TextFormat_targetSet::TMethod TFunc_Instances_TextFormat_targetSet::Method = &Instances::TextFormat::targetSet;
template <> const TFunc_Instances_TextFormat_underlineGet::TMethod TFunc_Instances_TextFormat_underlineGet::Method = &Instances::TextFormat::underlineGet;
template <> const TFunc_Instances_TextFormat_underlineSet::TMethod TFunc_Instances_TextFormat_underlineSet::Method = &Instances::TextFormat::underlineSet;
template <> const TFunc_Instances_TextFormat_urlGet::TMethod TFunc_Instances_TextFormat_urlGet::Method = &Instances::TextFormat::urlGet;
template <> const TFunc_Instances_TextFormat_urlSet::TMethod TFunc_Instances_TextFormat_urlSet::Method = &Instances::TextFormat::urlSet;

namespace Instances
{
    TextFormat::TextFormat(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::TextFormat::TextFormat()$data"
//##protect##"instance::TextFormat::TextFormat()$data"
    {
//##protect##"instance::TextFormat::TextFormat()$code"
        Value r, n;
        n.SetNull();

        alignSet(r, n);
        blockIndentSet(r, n);
        boldSet(r, n);
        bulletSet(r, n);
        colorSet(r, n);
        fontSet(r, n);
        indentSet(r, n);
        italicSet(r, n);
        kerningSet(r, n);
        leadingSet(r, n);
        leftMarginSet(r, n);
        letterSpacingSet(r, n);
        rightMarginSet(r, n);
        sizeSet(r, n);
        tabStopsSet(r, n);
        targetSet(r, n);
        underlineSet(r, n);
        urlSet(r, n);
//##protect##"instance::TextFormat::TextFormat()$code"
    }

    void TextFormat::alignGet(Value& result)
    {
//##protect##"instance::TextFormat::alignGet()"
        SF_UNUSED1(result);
        result = mAlign;
//##protect##"instance::TextFormat::alignGet()"
    }
    void TextFormat::alignSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::alignSet()"
        SF_UNUSED2(result, value);
        mAlign = value;
//##protect##"instance::TextFormat::alignSet()"
    }
    void TextFormat::blockIndentGet(Value& result)
    {
//##protect##"instance::TextFormat::blockIndentGet()"
        SF_UNUSED1(result);
        result = mBlockIndent;
//##protect##"instance::TextFormat::blockIndentGet()"
    }
    void TextFormat::blockIndentSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::blockIndentSet()"
        SF_UNUSED2(result, value);
        mBlockIndent = value;
//##protect##"instance::TextFormat::blockIndentSet()"
    }
    void TextFormat::boldGet(Value& result)
    {
//##protect##"instance::TextFormat::boldGet()"
        SF_UNUSED1(result);
        result = mBold;
//##protect##"instance::TextFormat::boldGet()"
    }
    void TextFormat::boldSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::boldSet()"
        SF_UNUSED2(result, value);
        mBold = value;
//##protect##"instance::TextFormat::boldSet()"
    }
    void TextFormat::bulletGet(Value& result)
    {
//##protect##"instance::TextFormat::bulletGet()"
        SF_UNUSED1(result);
        result = mBullet;
//##protect##"instance::TextFormat::bulletGet()"
    }
    void TextFormat::bulletSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::bulletSet()"
        SF_UNUSED2(result, value);
        mBullet = value;
//##protect##"instance::TextFormat::bulletSet()"
    }
    void TextFormat::colorGet(Value& result)
    {
//##protect##"instance::TextFormat::colorGet()"
        SF_UNUSED1(result);
        result = mColor;
//##protect##"instance::TextFormat::colorGet()"
    }
    void TextFormat::colorSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::colorSet()"
        SF_UNUSED2(result, value);
        mColor = value;
//##protect##"instance::TextFormat::colorSet()"
    }
    void TextFormat::fontGet(Value& result)
    {
//##protect##"instance::TextFormat::fontGet()"
        SF_UNUSED1(result);
        result = mFont;
//##protect##"instance::TextFormat::fontGet()"
    }
    void TextFormat::fontSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::fontSet()"
        SF_UNUSED2(result, value);
        mFont = value;
//##protect##"instance::TextFormat::fontSet()"
    }
    void TextFormat::indentGet(Value& result)
    {
//##protect##"instance::TextFormat::indentGet()"
        SF_UNUSED1(result);
        result = mIndent;
//##protect##"instance::TextFormat::indentGet()"
    }
    void TextFormat::indentSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::indentSet()"
        SF_UNUSED2(result, value);
        mIndent = value;
//##protect##"instance::TextFormat::indentSet()"
    }
    void TextFormat::italicGet(Value& result)
    {
//##protect##"instance::TextFormat::italicGet()"
        SF_UNUSED1(result);
        result = mItalic;
//##protect##"instance::TextFormat::italicGet()"
    }
    void TextFormat::italicSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::italicSet()"
        SF_UNUSED2(result, value);
        mItalic = value;
//##protect##"instance::TextFormat::italicSet()"
    }
    void TextFormat::kerningGet(Value& result)
    {
//##protect##"instance::TextFormat::kerningGet()"
        SF_UNUSED1(result);
        result = mKerning;
//##protect##"instance::TextFormat::kerningGet()"
    }
    void TextFormat::kerningSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::kerningSet()"
        SF_UNUSED2(result, value);
        mKerning = value;
//##protect##"instance::TextFormat::kerningSet()"
    }
    void TextFormat::leadingGet(Value& result)
    {
//##protect##"instance::TextFormat::leadingGet()"
        SF_UNUSED1(result);
        result = mLeading;
//##protect##"instance::TextFormat::leadingGet()"
    }
    void TextFormat::leadingSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::leadingSet()"
        SF_UNUSED2(result, value);
        mLeading = value;
//##protect##"instance::TextFormat::leadingSet()"
    }
    void TextFormat::leftMarginGet(Value& result)
    {
//##protect##"instance::TextFormat::leftMarginGet()"
        SF_UNUSED1(result);
        result = mLeftMargin;
//##protect##"instance::TextFormat::leftMarginGet()"
    }
    void TextFormat::leftMarginSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::leftMarginSet()"
        SF_UNUSED2(result, value);
        mLeftMargin = value;
//##protect##"instance::TextFormat::leftMarginSet()"
    }
    void TextFormat::letterSpacingGet(Value& result)
    {
//##protect##"instance::TextFormat::letterSpacingGet()"
        SF_UNUSED1(result);
        result = mLetterSpacing;
//##protect##"instance::TextFormat::letterSpacingGet()"
    }
    void TextFormat::letterSpacingSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::letterSpacingSet()"
        SF_UNUSED2(result, value);
        mLetterSpacing = value;
//##protect##"instance::TextFormat::letterSpacingSet()"
    }
    void TextFormat::rightMarginGet(Value& result)
    {
//##protect##"instance::TextFormat::rightMarginGet()"
        SF_UNUSED1(result);
        result = mRightMargin;
//##protect##"instance::TextFormat::rightMarginGet()"
    }
    void TextFormat::rightMarginSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::rightMarginSet()"
        SF_UNUSED2(result, value);
        mRightMargin = value;
//##protect##"instance::TextFormat::rightMarginSet()"
    }
    void TextFormat::sizeGet(Value& result)
    {
//##protect##"instance::TextFormat::sizeGet()"
        SF_UNUSED1(result);
        result = mSize;
//##protect##"instance::TextFormat::sizeGet()"
    }
    void TextFormat::sizeSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::sizeSet()"
        SF_UNUSED2(result, value);
        mSize = value;
//##protect##"instance::TextFormat::sizeSet()"
    }
    void TextFormat::tabStopsGet(Value& result)
    {
//##protect##"instance::TextFormat::tabStopsGet()"
        SF_UNUSED1(result);
        result = mTabStops;
//##protect##"instance::TextFormat::tabStopsGet()"
    }
    void TextFormat::tabStopsSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::tabStopsSet()"
        SF_UNUSED2(result, value);
        mTabStops = value;
//##protect##"instance::TextFormat::tabStopsSet()"
    }
    void TextFormat::targetGet(Value& result)
    {
//##protect##"instance::TextFormat::targetGet()"
        SF_UNUSED1(result);
        result = mTarget;
//##protect##"instance::TextFormat::targetGet()"
    }
    void TextFormat::targetSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::targetSet()"
        SF_UNUSED2(result, value);
        mTarget = value;
//##protect##"instance::TextFormat::targetSet()"
    }
    void TextFormat::underlineGet(Value& result)
    {
//##protect##"instance::TextFormat::underlineGet()"
        SF_UNUSED1(result);
        result = mUnderline;
//##protect##"instance::TextFormat::underlineGet()"
    }
    void TextFormat::underlineSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::underlineSet()"
        SF_UNUSED2(result, value);
        mUnderline = value;
//##protect##"instance::TextFormat::underlineSet()"
    }
    void TextFormat::urlGet(Value& result)
    {
//##protect##"instance::TextFormat::urlGet()"
        SF_UNUSED1(result);
        result = mUrl;
//##protect##"instance::TextFormat::urlGet()"
    }
    void TextFormat::urlSet(Value& result, const Value& value)
    {
//##protect##"instance::TextFormat::urlSet()"
        SF_UNUSED2(result, value);
        mUrl = value;
//##protect##"instance::TextFormat::urlSet()"
    }

//##protect##"instance$methods"
    void TextFormat::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Object::ForEachChild_GC(prcc, op);
        
        AS3::ForEachChild_GC(prcc, mAlign, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mBlockIndent, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mBullet, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mBold, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mColor, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mFont, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mItalic, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mIndent, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mKerning, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mLeading, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mLeftMargin, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mRightMargin, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mLetterSpacing, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mSize, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mTabStops, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mTarget, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mUnderline, op SF_DEBUG_ARG(*this));
        AS3::ForEachChild_GC(prcc, mUrl, op SF_DEBUG_ARG(*this));
    }

    void TextFormat::SetTextFormat(const Text::ParagraphFormat& parafmt, const Text::TextFormat& fmt)
    {
        Value r, n;
        n.SetNull();

        if (parafmt.IsAlignmentSet())
        {
            const char* newAlign = "left";
            switch(parafmt.GetAlignment())
            {
            case Text::ParagraphFormat::Align_Center:  newAlign = "center"; break;
            case Text::ParagraphFormat::Align_Right:   newAlign = "right"; break;
            case Text::ParagraphFormat::Align_Justify: newAlign = "justify"; break;
            default: break;
            }
            alignSet(r, Value(GetVM().GetStringManager().CreateString(newAlign)));
        }
        else
            alignSet(r, n);
        blockIndentSet(r, (parafmt.IsBlockIndentSet()) ? Value((UPInt)parafmt.GetBlockIndent()) : n);
        boldSet(r, (fmt.IsBoldSet()) ? Value(fmt.IsBold()) : n);
        italicSet(r, (fmt.IsItalicSet()) ? Value(fmt.IsItalic()) : n);
        underlineSet(r, (fmt.IsUnderlineSet()) ? Value(fmt.IsUnderline()) : n);

        bulletSet(r, (parafmt.IsBulletSet()) ? Value(parafmt.IsBullet()) : n);
        colorSet(r, (fmt.IsColorSet()) ? Value(Value::Number(fmt.GetColor32() & 0xFFFFFFu)) : n);
        fontSet(r, (fmt.IsFontListSet()) ? 
            Value(GetVM().GetStringManager().CreateString(fmt.GetFontList())) : n);
        indentSet(r, (parafmt.IsIndentSet()) ? Value(Value::Number(parafmt.GetIndent())) : n);
        kerningSet(r, (fmt.IsKerningSet()) ? Value(fmt.IsKerning()) : n);
        leadingSet(r, (parafmt.IsLeadingSet()) ? Value(Value::Number(parafmt.GetLeading())) : n);
        leftMarginSet(r, (parafmt.IsLeftMarginSet()) ? Value(Value::Number(parafmt.GetLeftMargin())) : n);
        letterSpacingSet(r, (fmt.IsLetterSpacingSet()) ? Value(Value::Number(fmt.GetLetterSpacing())) : n);
        rightMarginSet(r, (parafmt.IsRightMarginSet()) ? Value(Value::Number(parafmt.GetRightMargin())) : n);
        sizeSet(r, (fmt.IsFontSizeSet()) ? Value(Value::Number(fmt.GetFontSize())) : n);
        targetSet(r, n);
        urlSet(r, (fmt.IsUrlSet()) ? Value(GetVM().GetStringManager().CreateString(fmt.GetUrl())) : n);
        if (parafmt.IsTabStopsSet())
        {
            unsigned num = 0;
            const unsigned* ptabStops = parafmt.GetTabStops(&num);
            SF_ASSERT(num > 0 && ptabStops);
            
            // Create an array
            SPtr<Instances::Array> parr(GetVM().MakeArray());

            parr->Resize((int)num);
            for (unsigned i = 0; i < num; i++)
                parr->Set(i, Value((Value::Number)ptabStops[i]));
            tabStopsSet(r, Value(parr));
        }
        else 
            tabStopsSet(r, n);
    }

    void TextFormat::GetTextFormat(Text::ParagraphFormat* parafmt, Text::TextFormat* fmt)
    {
        if (!mAlign.IsNullOrUndefined())
        {
            ASString strval = GetVM().GetStringManager().CreateEmptyString();
            mAlign.Convert2String(strval).DoNotCheck();
            if (strval == "left")
            {
                parafmt->SetAlignment(Text::ParagraphFormat::Align_Left);
            }
            else if (strval == "right")
            {
                parafmt->SetAlignment(Text::ParagraphFormat::Align_Right);
            }
            else if (strval == "center")
            {
                parafmt->SetAlignment(Text::ParagraphFormat::Align_Center);
            }
            else if (strval == "justify")
            {
                parafmt->SetAlignment(Text::ParagraphFormat::Align_Justify);
            }
            else
            {
                parafmt->ClearAlignment();
            }
        }

        if (!mBlockIndent.IsNullOrUndefined())
        {
            SInt32 v;
            mBlockIndent.Convert2Int32(v).DoNotCheck();
            if (v < 0) v = 0;
            else if (v > 720) v = 720;
            parafmt->SetBlockIndent((unsigned)v);
        }
        else
            parafmt->ClearBlockIndent();

        if (!mBold.IsNullOrUndefined())
        {
            fmt->SetBold(mBold.Convert2Boolean());
        }
        else
            fmt->ClearBold();

        if (!mItalic.IsNullOrUndefined())
        {
            fmt->SetItalic(mItalic.Convert2Boolean());
        }
        else
            fmt->ClearItalic();

        if (!mUnderline.IsNullOrUndefined())
        {
            fmt->SetUnderline(mUnderline.Convert2Boolean());
        }
        else
            fmt->ClearUnderline();

        if (!mBullet.IsNullOrUndefined())
        {
            parafmt->SetBullet(mBullet.Convert2Boolean());
        }
        else
            parafmt->ClearBullet();

        if (!mColor.IsNullOrUndefined())
        {
            UInt32 c;
            mColor.Convert2UInt32(c).DoNotCheck();
            fmt->SetColor32(c);
        }
        else
            fmt->ClearColor();

        if (!mFont.IsNullOrUndefined())
        {
            ASString v = GetVM().GetStringManager().CreateEmptyString();
            mFont.Convert2String(v).DoNotCheck();
            fmt->SetFontList(v.ToCStr());
        }
        else
            fmt->ClearFontList();

        if (!mIndent.IsNullOrUndefined())
        {   
            SInt32 v;
            mIndent.Convert2Int32(v).DoNotCheck();
            if (v < -720) v = -720;
            else if (v > 720) v = 720;
            parafmt->SetIndent((int)v);
        }
        else
            parafmt->ClearIndent();

        if (!mLeading.IsNullOrUndefined())
        {
            SInt32 v;
            mLeading.Convert2Int32(v).DoNotCheck();
            if (v < -720) v = -720;
            else if (v > 720) v = 720;
            parafmt->SetLeading((int)v);
        }
        else
            parafmt->ClearLeading();

        if (!mLeftMargin.IsNullOrUndefined())
        {
            SInt32 v;
            mLeftMargin.Convert2Int32(v).DoNotCheck();
            if (v < 0) v = 0;
            else if (v > 720) v = 720;
            parafmt->SetLeftMargin((unsigned)v);
        }
        else
            parafmt->ClearLeftMargin();

        if (!mRightMargin.IsNullOrUndefined())
        {
            SInt32 v;
            mRightMargin.Convert2Int32(v).DoNotCheck();
            if (v < 0) v = 0;
            else if (v > 720) v = 720;
            parafmt->SetRightMargin((unsigned)v);
        }
        else
            parafmt->ClearRightMargin();

        if (!mSize.IsNullOrUndefined())
        {
            SInt32 v;
            mSize.Convert2Int32(v).DoNotCheck();
            if (v >= 0)
            {
                if (v < 128)
                   fmt->SetFontSize((float)(unsigned)v);
                else
                    fmt->SetFontSize(127);
            }
        }
        else
            fmt->ClearFontSize();

        if (!mUrl.IsNullOrUndefined())
        {
            ASString v = GetVM().GetStringManager().CreateEmptyString();
            mUrl.Convert2String(v).DoNotCheck();
            fmt->SetUrl(v.ToCStr());
        }
        else
            fmt->ClearUrl();

        if (!mLetterSpacing.IsNullOrUndefined())
        {
            Value::Number v;
            mLetterSpacing.Convert2Number(v).DoNotCheck();
            if (v < -720) v = -720;
            else if (v > 720) v = 720;
            fmt->SetLetterSpacing((float)v);
        }
        else
            fmt->ClearLetterSpacing();
            
        if (!mKerning.IsNullOrUndefined())
        {
            fmt->SetKerning(mKerning.Convert2Boolean());
        }
        else
            fmt->ClearKerning();

        if (!mTabStops.IsNullOrUndefined())
        {
            if (mTabStops.IsObject() && mTabStops.GetObject() && 
                mTabStops.GetObject()->GetTraitsType() == Traits_Array && 
                mTabStops.GetObject()->GetTraits().IsInstanceTraits())
            {
                Array* parr = static_cast<Array*>(mTabStops.GetObject());
                parafmt->SetTabStopsNum((unsigned)parr->GetSize());
                for(UPInt i = 0, n = parr->GetSize(); i < n; ++i)
                {
                    Value::Number v;
                    parr->At(i).Convert2Number(v);
                    parafmt->SetTabStopsElement((unsigned)i, (unsigned)v);
                }
            }
        }
        else
            parafmt->ClearTabStops();

    }

    // TextFormat(font:String = null, size:Object = null, color:Object = null, bold:Object = null, 
    // italic:Object = null, underline:Object = null, url:String = null, target:String = null, 
    // align:String = null, leftMargin:Object = null, rightMargin:Object = null, indent:Object = null, 
    // leading:Object = null)
    void TextFormat::AS3Constructor(unsigned argc, const Value* argv)
    {
        Object::AS3Constructor(argc, argv);

        if (argc >= 1)
            mFont = argv[0];
        if (argc >= 2)
            mSize = argv[1];
        if (argc >= 3)
            mColor = argv[2];
        if (argc >= 4)
            mBold = argv[3];
        if (argc >= 5)
            mItalic = argv[4];
        if (argc >= 6)
            mUnderline = argv[5];
        if (argc >= 7)
            mUrl = argv[6];
        if (argc >= 8)
            mTarget = argv[7];
        if (argc >= 9)
            mAlign = argv[8];
        if (argc >= 10)
            mLeftMargin = argv[9];
        if (argc >= 11)
            mRightMargin = argv[10];
        if (argc >= 12)
            mIndent = argv[11];
        if (argc >= 13)
            mLeading = argv[12];
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TextFormat::ti[TextFormat::ThunkInfoNum] = {
        {TFunc_Instances_TextFormat_alignGet::Func, &ObjectCI, "align", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_alignSet::Func, NULL, "align", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_blockIndentGet::Func, &ObjectCI, "blockIndent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_blockIndentSet::Func, NULL, "blockIndent", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_boldGet::Func, &ObjectCI, "bold", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_boldSet::Func, NULL, "bold", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_bulletGet::Func, &ObjectCI, "bullet", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_bulletSet::Func, NULL, "bullet", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_colorGet::Func, &ObjectCI, "color", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_colorSet::Func, NULL, "color", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_fontGet::Func, &ObjectCI, "font", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_fontSet::Func, NULL, "font", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_indentGet::Func, &ObjectCI, "indent", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_indentSet::Func, NULL, "indent", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_italicGet::Func, &ObjectCI, "italic", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_italicSet::Func, NULL, "italic", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_kerningGet::Func, &ObjectCI, "kerning", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_kerningSet::Func, NULL, "kerning", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_leadingGet::Func, &ObjectCI, "leading", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_leadingSet::Func, NULL, "leading", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_leftMarginGet::Func, &ObjectCI, "leftMargin", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_leftMarginSet::Func, NULL, "leftMargin", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_letterSpacingGet::Func, &ObjectCI, "letterSpacing", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_letterSpacingSet::Func, NULL, "letterSpacing", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_rightMarginGet::Func, &ObjectCI, "rightMargin", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_rightMarginSet::Func, NULL, "rightMargin", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_sizeGet::Func, &ObjectCI, "size", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_sizeSet::Func, NULL, "size", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_tabStopsGet::Func, &ObjectCI, "tabStops", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_tabStopsSet::Func, NULL, "tabStops", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_targetGet::Func, &ObjectCI, "target", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_targetSet::Func, NULL, "target", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_underlineGet::Func, &ObjectCI, "underline", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_underlineSet::Func, NULL, "underline", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextFormat_urlGet::Func, &ObjectCI, "url", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextFormat_urlSet::Func, NULL, "url", NULL, CT_Set, 1, 1},
    };

    TextFormat::TextFormat(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextFormat::TextFormat()"
//##protect##"InstanceTraits::TextFormat::TextFormat()"
        SetMemSize(sizeof(Instances::TextFormat));

    }

    Pickable<Instances::TextFormat> TextFormat::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextFormat>(new(t.Alloc()) Instances::TextFormat(t));
    }

    void TextFormat::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    TextFormat::TextFormat(VM& vm)
    : Traits(vm, TextFormatCI)
    {
//##protect##"ClassTraits::TextFormat::TextFormat()"
//##protect##"ClassTraits::TextFormat::TextFormat()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextFormat(vm, TextFormatCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextFormat::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFormat(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFormatCI = {
    ClassInfo::CompileTime,
    "TextFormat", "flash.text", &ObjectCI,
    ClassTraits::TextFormat::MakeClassTraits,
    0,
    0,
    InstanceTraits::TextFormat::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::TextFormat::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

