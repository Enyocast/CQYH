//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextFormat.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextFormat_H
#define INC_AS3_Obj_Text_TextFormat_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "Render/Text/Text_Core.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextFormat;
}

namespace InstanceTraits
{
    class TextFormat;
}

namespace Classes
{
    class TextFormat;
}

namespace Instances
{
    class TextFormat : public Instances::Object
    {
        friend class InstanceTraits::TextFormat;
        
    public:
        typedef TextFormat SelfType;
        typedef Classes::TextFormat ClassType;
        typedef InstanceTraits::TextFormat TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextFormat"; }
#endif
    protected:
        TextFormat(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        void SetTextFormat(const Render::Text::ParagraphFormat& parafmt, const Render::Text::TextFormat&);
        void GetTextFormat(Render::Text::ParagraphFormat* parafmt, Render::Text::TextFormat* fmt);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_alignGet, 
            mid_alignSet, 
            mid_blockIndentGet, 
            mid_blockIndentSet, 
            mid_boldGet, 
            mid_boldSet, 
            mid_bulletGet, 
            mid_bulletSet, 
            mid_colorGet, 
            mid_colorSet, 
            mid_fontGet, 
            mid_fontSet, 
            mid_indentGet, 
            mid_indentSet, 
            mid_italicGet, 
            mid_italicSet, 
            mid_kerningGet, 
            mid_kerningSet, 
            mid_leadingGet, 
            mid_leadingSet, 
            mid_leftMarginGet, 
            mid_leftMarginSet, 
            mid_letterSpacingGet, 
            mid_letterSpacingSet, 
            mid_rightMarginGet, 
            mid_rightMarginSet, 
            mid_sizeGet, 
            mid_sizeSet, 
            mid_tabStopsGet, 
            mid_tabStopsSet, 
            mid_targetGet, 
            mid_targetSet, 
            mid_underlineGet, 
            mid_underlineSet, 
            mid_urlGet, 
            mid_urlSet, 
        };
        void alignGet(Value& result);
        void alignSet(Value& result, const Value& value);
        void blockIndentGet(Value& result);
        void blockIndentSet(Value& result, const Value& value);
        void boldGet(Value& result);
        void boldSet(Value& result, const Value& value);
        void bulletGet(Value& result);
        void bulletSet(Value& result, const Value& value);
        void colorGet(Value& result);
        void colorSet(Value& result, const Value& value);
        void fontGet(Value& result);
        void fontSet(Value& result, const Value& value);
        void indentGet(Value& result);
        void indentSet(Value& result, const Value& value);
        void italicGet(Value& result);
        void italicSet(Value& result, const Value& value);
        void kerningGet(Value& result);
        void kerningSet(Value& result, const Value& value);
        void leadingGet(Value& result);
        void leadingSet(Value& result, const Value& value);
        void leftMarginGet(Value& result);
        void leftMarginSet(Value& result, const Value& value);
        void letterSpacingGet(Value& result);
        void letterSpacingSet(Value& result, const Value& value);
        void rightMarginGet(Value& result);
        void rightMarginSet(Value& result, const Value& value);
        void sizeGet(Value& result);
        void sizeSet(Value& result, const Value& value);
        void tabStopsGet(Value& result);
        void tabStopsSet(Value& result, const Value& value);
        void targetGet(Value& result);
        void targetSet(Value& result, const Value& value);
        void underlineGet(Value& result);
        void underlineSet(Value& result, const Value& value);
        void urlGet(Value& result);
        void urlSet(Value& result, const Value& value);

//##protect##"instance$data"
        // original values
        Value                   mAlign;
        Value                   mBlockIndent;
        Value                   mBullet;
        Value                   mBold;
        Value                   mColor;
        Value                   mFont;
        Value                   mItalic;
        Value                   mIndent;
        Value                   mKerning;
        Value                   mLeading;
        Value                   mLeftMargin;
        Value                   mRightMargin;
        Value                   mLetterSpacing;
        Value                   mSize;
        Value                   mTabStops;
        Value                   mTarget;
        Value                   mUnderline;
        Value                   mUrl;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TextFormat : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextFormat"; }
#endif
    public:
        TextFormat(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextFormat> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 36 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TextFormat : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextFormat"; }
#endif
    public:
        typedef Classes::TextFormat ClassType;

    public:
        TextFormat(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

