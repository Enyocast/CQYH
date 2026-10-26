//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextField.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextField_H
#define INC_AS3_Obj_Text_TextField_H

#include "../Display/AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"
#include "GFx/GFx_TextField.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class TextFormat;
    class StyleSheet;
    class TextLineMetrics;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextField;
}

namespace InstanceTraits
{
    class TextField;
}

namespace Classes
{
    class TextField;
}

namespace Instances
{
    class TextField : public Instances::InteractiveObject
    {
        friend class InstanceTraits::TextField;
        
    public:
        typedef TextField SelfType;
        typedef Classes::TextField ClassType;
        typedef InstanceTraits::TextField TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextField"; }
#endif
    protected:
        TextField(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void                InitInstance(bool extCall = false);
        virtual GFx::DisplayObject* CreateStageObject();
        void                        UpdateAutosizeSettings();
	public:
        GFx::TextField* GetTextField() const 
        { 
            SF_ASSERT(pDispObj && pDispObj->GetType() == CharacterDef::TextField);
            return static_cast<GFx::TextField*>(pDispObj.GetPtr()); 
        }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_alwaysShowSelectionGet, 
            mid_alwaysShowSelectionSet, 
            mid_antiAliasTypeGet, 
            mid_antiAliasTypeSet, 
            mid_autoSizeGet, 
            mid_autoSizeSet, 
            mid_backgroundGet, 
            mid_backgroundSet, 
            mid_backgroundColorGet, 
            mid_backgroundColorSet, 
            mid_borderGet, 
            mid_borderSet, 
            mid_borderColorGet, 
            mid_borderColorSet, 
            mid_bottomScrollVGet, 
            mid_caretIndexGet, 
            mid_condenseWhiteGet, 
            mid_condenseWhiteSet, 
            mid_contextMenuGet, 
            mid_defaultTextFormatGet, 
            mid_defaultTextFormatSet, 
            mid_displayAsPasswordGet, 
            mid_displayAsPasswordSet, 
            mid_embedFontsGet, 
            mid_embedFontsSet, 
            mid_gridFitTypeGet, 
            mid_gridFitTypeSet, 
            mid_htmlTextGet, 
            mid_htmlTextSet, 
            mid_lengthGet, 
            mid_maxCharsGet, 
            mid_maxCharsSet, 
            mid_maxScrollHGet, 
            mid_maxScrollVGet, 
            mid_mouseWheelEnabledGet, 
            mid_mouseWheelEnabledSet, 
            mid_multilineGet, 
            mid_multilineSet, 
            mid_numLinesGet, 
            mid_restrictGet, 
            mid_restrictSet, 
            mid_scrollHGet, 
            mid_scrollHSet, 
            mid_scrollVGet, 
            mid_scrollVSet, 
            mid_selectableGet, 
            mid_selectableSet, 
            mid_selectionBeginIndexGet, 
            mid_selectionEndIndexGet, 
            mid_sharpnessGet, 
            mid_sharpnessSet, 
            mid_styleSheetGet, 
            mid_styleSheetSet, 
            mid_textGet, 
            mid_textSet, 
            mid_textColorGet, 
            mid_textColorSet, 
            mid_textHeightGet, 
            mid_textWidthGet, 
            mid_thicknessGet, 
            mid_thicknessSet, 
            mid_typeGet, 
            mid_typeSet, 
            mid_useRichTextClipboardGet, 
            mid_useRichTextClipboardSet, 
            mid_wordWrapGet, 
            mid_wordWrapSet, 
            mid_appendText, 
            mid_getCharBoundaries, 
            mid_getCharIndexAtPoint, 
            mid_getFirstCharInParagraph, 
            mid_getImageReference, 
            mid_getLineIndexAtPoint, 
            mid_getLineIndexOfChar, 
            mid_getLineLength, 
            mid_getLineMetrics, 
            mid_getLineOffset, 
            mid_getLineText, 
            mid_getParagraphLength, 
            mid_getTextFormat, 
            mid_replaceSelectedText, 
            mid_replaceText, 
            mid_setSelection, 
            mid_setTextFormat, 
        };
        void alwaysShowSelectionGet(bool& result);
        void alwaysShowSelectionSet(Value& result, bool value);
        void antiAliasTypeGet(ASString& result);
        void antiAliasTypeSet(Value& result, const ASString& value);
        void autoSizeGet(ASString& result);
        void autoSizeSet(Value& result, const ASString& value);
        void backgroundGet(bool& result);
        void backgroundSet(Value& result, bool value);
        void backgroundColorGet(UInt32& result);
        void backgroundColorSet(Value& result, UInt32 value);
        void borderGet(bool& result);
        void borderSet(Value& result, bool value);
        void borderColorGet(UInt32& result);
        void borderColorSet(Value& result, UInt32 value);
        void bottomScrollVGet(SInt32& result);
        void caretIndexGet(SInt32& result);
        void condenseWhiteGet(bool& result);
        void condenseWhiteSet(Value& result, bool value);
        void contextMenuGet(Value& result);
        void defaultTextFormatGet(Value& result);
        void defaultTextFormatSet(Value& result, Instances::TextFormat* value);
        void displayAsPasswordGet(bool& result);
        void displayAsPasswordSet(Value& result, bool value);
        void embedFontsGet(bool& result);
        void embedFontsSet(Value& result, bool value);
        void gridFitTypeGet(ASString& result);
        void gridFitTypeSet(Value& result, const ASString& value);
        void htmlTextGet(ASString& result);
        void htmlTextSet(Value& result, const ASString& value);
        void lengthGet(SInt32& result);
        void maxCharsGet(SInt32& result);
        void maxCharsSet(Value& result, SInt32 value);
        void maxScrollHGet(SInt32& result);
        void maxScrollVGet(SInt32& result);
        void mouseWheelEnabledGet(bool& result);
        void mouseWheelEnabledSet(Value& result, bool value);
        void multilineGet(bool& result);
        void multilineSet(Value& result, bool value);
        void numLinesGet(SInt32& result);
        void restrictGet(Value& result);
        void restrictSet(Value& result, const Value& value);
        void scrollHGet(SInt32& result);
        void scrollHSet(Value& result, SInt32 value);
        void scrollVGet(SInt32& result);
        void scrollVSet(Value& result, SInt32 value);
        void selectableGet(bool& result);
        void selectableSet(Value& result, bool value);
        void selectionBeginIndexGet(SInt32& result);
        void selectionEndIndexGet(SInt32& result);
        void sharpnessGet(Value::Number& result);
        void sharpnessSet(Value& result, Value::Number value);
        void styleSheetGet(Value& result);
        void styleSheetSet(Value& result, Instances::StyleSheet* value);
        void textGet(ASString& result);
        void textSet(Value& result, const ASString& value);
        void textColorGet(UInt32& result);
        void textColorSet(Value& result, UInt32 value);
        void textHeightGet(Value::Number& result);
        void textWidthGet(Value::Number& result);
        void thicknessGet(Value::Number& result);
        void thicknessSet(Value& result, Value::Number value);
        void typeGet(ASString& result);
        void typeSet(Value& result, const ASString& value);
        void useRichTextClipboardGet(bool& result);
        void useRichTextClipboardSet(Value& result, bool value);
        void wordWrapGet(bool& result);
        void wordWrapSet(Value& result, bool value);
        void appendText(Value& result, const ASString& newText);
        void getCharBoundaries(Value& result, SInt32 charIndex);
        void getCharIndexAtPoint(SInt32& result, Value::Number x, Value::Number y);
        void getFirstCharInParagraph(SInt32& result, SInt32 charIndex);
        void getImageReference(Value& result, const ASString& id);
        void getLineIndexAtPoint(SInt32& result, Value::Number x, Value::Number y);
        void getLineIndexOfChar(SInt32& result, SInt32 charIndex);
        void getLineLength(SInt32& result, SInt32 lineIndex);
        void getLineMetrics(Value& result, SInt32 lineIndex);
        void getLineOffset(SInt32& result, SInt32 lineIndex);
        void getLineText(ASString& result, SInt32 lineIndex);
        void getParagraphLength(SInt32& result, SInt32 charIndex);
        void getTextFormat(Value& result, SInt32 beginIndex, SInt32 endIndex);
        void replaceSelectedText(Value& result, const ASString& value);
        void replaceText(Value& result, SInt32 beginIndex, SInt32 endIndex, const ASString& newText);
        void setSelection(Value& result, SInt32 beginIndex, SInt32 endIndex);
        void setTextFormat(Value& result, Instances::TextFormat* format, SInt32 beginIndex, SInt32 endIndex);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TextField : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextField"; }
#endif
    public:
        TextField(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextField> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 83 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TextField : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextField"; }
#endif
    public:
        typedef Classes::TextField ClassType;

    public:
        TextField(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

