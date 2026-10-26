//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextField.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextField.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Text_TextFormat.h"
#include "AS3_Obj_Text_StyleSheet.h"
#include "AS3_Obj_Text_TextLineMetrics.h"
#include "GFx/GFx_TextField.h"
#include "GFx/AS3/AS3_AvmTextField.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/AS3/Obj/Geom/AS3_Obj_Geom_Rectangle.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::TextField, Instances::TextField::mid_getTextFormat, 0, SInt32>(AS3::StringManager&)
    {
        return -1;
    }

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::TextField, Instances::TextField::mid_getTextFormat, 1, SInt32>(AS3::StringManager&)
    {
        return -1;
    }

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::TextField, Instances::TextField::mid_setTextFormat, 1, SInt32>(AS3::StringManager&)
    {
        return -1;
    }

    template <>
    SF_INLINE
    SInt32 GetMethodDefArg<Instances::TextField, Instances::TextField::mid_setTextFormat, 2, SInt32>(AS3::StringManager&)
    {
        return -1;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_alwaysShowSelectionGet, bool> TFunc_Instances_TextField_alwaysShowSelectionGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_alwaysShowSelectionSet, Value, bool> TFunc_Instances_TextField_alwaysShowSelectionSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_antiAliasTypeGet, ASString> TFunc_Instances_TextField_antiAliasTypeGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_antiAliasTypeSet, Value, const ASString&> TFunc_Instances_TextField_antiAliasTypeSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_autoSizeGet, ASString> TFunc_Instances_TextField_autoSizeGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_autoSizeSet, Value, const ASString&> TFunc_Instances_TextField_autoSizeSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_backgroundGet, bool> TFunc_Instances_TextField_backgroundGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_backgroundSet, Value, bool> TFunc_Instances_TextField_backgroundSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_backgroundColorGet, UInt32> TFunc_Instances_TextField_backgroundColorGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_backgroundColorSet, Value, UInt32> TFunc_Instances_TextField_backgroundColorSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_borderGet, bool> TFunc_Instances_TextField_borderGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_borderSet, Value, bool> TFunc_Instances_TextField_borderSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_borderColorGet, UInt32> TFunc_Instances_TextField_borderColorGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_borderColorSet, Value, UInt32> TFunc_Instances_TextField_borderColorSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_bottomScrollVGet, SInt32> TFunc_Instances_TextField_bottomScrollVGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_caretIndexGet, SInt32> TFunc_Instances_TextField_caretIndexGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_condenseWhiteGet, bool> TFunc_Instances_TextField_condenseWhiteGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_condenseWhiteSet, Value, bool> TFunc_Instances_TextField_condenseWhiteSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_contextMenuGet, Value> TFunc_Instances_TextField_contextMenuGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_defaultTextFormatGet, Value> TFunc_Instances_TextField_defaultTextFormatGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_defaultTextFormatSet, Value, Instances::TextFormat*> TFunc_Instances_TextField_defaultTextFormatSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_displayAsPasswordGet, bool> TFunc_Instances_TextField_displayAsPasswordGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_displayAsPasswordSet, Value, bool> TFunc_Instances_TextField_displayAsPasswordSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_embedFontsGet, bool> TFunc_Instances_TextField_embedFontsGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_embedFontsSet, Value, bool> TFunc_Instances_TextField_embedFontsSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_gridFitTypeGet, ASString> TFunc_Instances_TextField_gridFitTypeGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_gridFitTypeSet, Value, const ASString&> TFunc_Instances_TextField_gridFitTypeSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_htmlTextGet, ASString> TFunc_Instances_TextField_htmlTextGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_htmlTextSet, Value, const ASString&> TFunc_Instances_TextField_htmlTextSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_lengthGet, SInt32> TFunc_Instances_TextField_lengthGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_maxCharsGet, SInt32> TFunc_Instances_TextField_maxCharsGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_maxCharsSet, Value, SInt32> TFunc_Instances_TextField_maxCharsSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_maxScrollHGet, SInt32> TFunc_Instances_TextField_maxScrollHGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_maxScrollVGet, SInt32> TFunc_Instances_TextField_maxScrollVGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_mouseWheelEnabledGet, bool> TFunc_Instances_TextField_mouseWheelEnabledGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_mouseWheelEnabledSet, Value, bool> TFunc_Instances_TextField_mouseWheelEnabledSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_multilineGet, bool> TFunc_Instances_TextField_multilineGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_multilineSet, Value, bool> TFunc_Instances_TextField_multilineSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_numLinesGet, SInt32> TFunc_Instances_TextField_numLinesGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_restrictGet, Value> TFunc_Instances_TextField_restrictGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_restrictSet, Value, const Value&> TFunc_Instances_TextField_restrictSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_scrollHGet, SInt32> TFunc_Instances_TextField_scrollHGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_scrollHSet, Value, SInt32> TFunc_Instances_TextField_scrollHSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_scrollVGet, SInt32> TFunc_Instances_TextField_scrollVGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_scrollVSet, Value, SInt32> TFunc_Instances_TextField_scrollVSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_selectableGet, bool> TFunc_Instances_TextField_selectableGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_selectableSet, Value, bool> TFunc_Instances_TextField_selectableSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_selectionBeginIndexGet, SInt32> TFunc_Instances_TextField_selectionBeginIndexGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_selectionEndIndexGet, SInt32> TFunc_Instances_TextField_selectionEndIndexGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_sharpnessGet, Value::Number> TFunc_Instances_TextField_sharpnessGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_sharpnessSet, Value, Value::Number> TFunc_Instances_TextField_sharpnessSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_styleSheetGet, Value> TFunc_Instances_TextField_styleSheetGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_styleSheetSet, Value, Instances::StyleSheet*> TFunc_Instances_TextField_styleSheetSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_textGet, ASString> TFunc_Instances_TextField_textGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_textSet, Value, const ASString&> TFunc_Instances_TextField_textSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_textColorGet, UInt32> TFunc_Instances_TextField_textColorGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_textColorSet, Value, UInt32> TFunc_Instances_TextField_textColorSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_textHeightGet, Value::Number> TFunc_Instances_TextField_textHeightGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_textWidthGet, Value::Number> TFunc_Instances_TextField_textWidthGet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_thicknessGet, Value::Number> TFunc_Instances_TextField_thicknessGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_thicknessSet, Value, Value::Number> TFunc_Instances_TextField_thicknessSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_typeGet, ASString> TFunc_Instances_TextField_typeGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_typeSet, Value, const ASString&> TFunc_Instances_TextField_typeSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_useRichTextClipboardGet, bool> TFunc_Instances_TextField_useRichTextClipboardGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_useRichTextClipboardSet, Value, bool> TFunc_Instances_TextField_useRichTextClipboardSet;
typedef ThunkFunc0<Instances::TextField, Instances::TextField::mid_wordWrapGet, bool> TFunc_Instances_TextField_wordWrapGet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_wordWrapSet, Value, bool> TFunc_Instances_TextField_wordWrapSet;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_appendText, Value, const ASString&> TFunc_Instances_TextField_appendText;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getCharBoundaries, Value, SInt32> TFunc_Instances_TextField_getCharBoundaries;
typedef ThunkFunc2<Instances::TextField, Instances::TextField::mid_getCharIndexAtPoint, SInt32, Value::Number, Value::Number> TFunc_Instances_TextField_getCharIndexAtPoint;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getFirstCharInParagraph, SInt32, SInt32> TFunc_Instances_TextField_getFirstCharInParagraph;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getImageReference, Value, const ASString&> TFunc_Instances_TextField_getImageReference;
typedef ThunkFunc2<Instances::TextField, Instances::TextField::mid_getLineIndexAtPoint, SInt32, Value::Number, Value::Number> TFunc_Instances_TextField_getLineIndexAtPoint;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getLineIndexOfChar, SInt32, SInt32> TFunc_Instances_TextField_getLineIndexOfChar;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getLineLength, SInt32, SInt32> TFunc_Instances_TextField_getLineLength;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getLineMetrics, Value, SInt32> TFunc_Instances_TextField_getLineMetrics;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getLineOffset, SInt32, SInt32> TFunc_Instances_TextField_getLineOffset;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getLineText, ASString, SInt32> TFunc_Instances_TextField_getLineText;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_getParagraphLength, SInt32, SInt32> TFunc_Instances_TextField_getParagraphLength;
typedef ThunkFunc2<Instances::TextField, Instances::TextField::mid_getTextFormat, Value, SInt32, SInt32> TFunc_Instances_TextField_getTextFormat;
typedef ThunkFunc1<Instances::TextField, Instances::TextField::mid_replaceSelectedText, Value, const ASString&> TFunc_Instances_TextField_replaceSelectedText;
typedef ThunkFunc3<Instances::TextField, Instances::TextField::mid_replaceText, Value, SInt32, SInt32, const ASString&> TFunc_Instances_TextField_replaceText;
typedef ThunkFunc2<Instances::TextField, Instances::TextField::mid_setSelection, Value, SInt32, SInt32> TFunc_Instances_TextField_setSelection;
typedef ThunkFunc3<Instances::TextField, Instances::TextField::mid_setTextFormat, Value, Instances::TextFormat*, SInt32, SInt32> TFunc_Instances_TextField_setTextFormat;

template <> const TFunc_Instances_TextField_alwaysShowSelectionGet::TMethod TFunc_Instances_TextField_alwaysShowSelectionGet::Method = &Instances::TextField::alwaysShowSelectionGet;
template <> const TFunc_Instances_TextField_alwaysShowSelectionSet::TMethod TFunc_Instances_TextField_alwaysShowSelectionSet::Method = &Instances::TextField::alwaysShowSelectionSet;
template <> const TFunc_Instances_TextField_antiAliasTypeGet::TMethod TFunc_Instances_TextField_antiAliasTypeGet::Method = &Instances::TextField::antiAliasTypeGet;
template <> const TFunc_Instances_TextField_antiAliasTypeSet::TMethod TFunc_Instances_TextField_antiAliasTypeSet::Method = &Instances::TextField::antiAliasTypeSet;
template <> const TFunc_Instances_TextField_autoSizeGet::TMethod TFunc_Instances_TextField_autoSizeGet::Method = &Instances::TextField::autoSizeGet;
template <> const TFunc_Instances_TextField_autoSizeSet::TMethod TFunc_Instances_TextField_autoSizeSet::Method = &Instances::TextField::autoSizeSet;
template <> const TFunc_Instances_TextField_backgroundGet::TMethod TFunc_Instances_TextField_backgroundGet::Method = &Instances::TextField::backgroundGet;
template <> const TFunc_Instances_TextField_backgroundSet::TMethod TFunc_Instances_TextField_backgroundSet::Method = &Instances::TextField::backgroundSet;
template <> const TFunc_Instances_TextField_backgroundColorGet::TMethod TFunc_Instances_TextField_backgroundColorGet::Method = &Instances::TextField::backgroundColorGet;
template <> const TFunc_Instances_TextField_backgroundColorSet::TMethod TFunc_Instances_TextField_backgroundColorSet::Method = &Instances::TextField::backgroundColorSet;
template <> const TFunc_Instances_TextField_borderGet::TMethod TFunc_Instances_TextField_borderGet::Method = &Instances::TextField::borderGet;
template <> const TFunc_Instances_TextField_borderSet::TMethod TFunc_Instances_TextField_borderSet::Method = &Instances::TextField::borderSet;
template <> const TFunc_Instances_TextField_borderColorGet::TMethod TFunc_Instances_TextField_borderColorGet::Method = &Instances::TextField::borderColorGet;
template <> const TFunc_Instances_TextField_borderColorSet::TMethod TFunc_Instances_TextField_borderColorSet::Method = &Instances::TextField::borderColorSet;
template <> const TFunc_Instances_TextField_bottomScrollVGet::TMethod TFunc_Instances_TextField_bottomScrollVGet::Method = &Instances::TextField::bottomScrollVGet;
template <> const TFunc_Instances_TextField_caretIndexGet::TMethod TFunc_Instances_TextField_caretIndexGet::Method = &Instances::TextField::caretIndexGet;
template <> const TFunc_Instances_TextField_condenseWhiteGet::TMethod TFunc_Instances_TextField_condenseWhiteGet::Method = &Instances::TextField::condenseWhiteGet;
template <> const TFunc_Instances_TextField_condenseWhiteSet::TMethod TFunc_Instances_TextField_condenseWhiteSet::Method = &Instances::TextField::condenseWhiteSet;
template <> const TFunc_Instances_TextField_contextMenuGet::TMethod TFunc_Instances_TextField_contextMenuGet::Method = &Instances::TextField::contextMenuGet;
template <> const TFunc_Instances_TextField_defaultTextFormatGet::TMethod TFunc_Instances_TextField_defaultTextFormatGet::Method = &Instances::TextField::defaultTextFormatGet;
template <> const TFunc_Instances_TextField_defaultTextFormatSet::TMethod TFunc_Instances_TextField_defaultTextFormatSet::Method = &Instances::TextField::defaultTextFormatSet;
template <> const TFunc_Instances_TextField_displayAsPasswordGet::TMethod TFunc_Instances_TextField_displayAsPasswordGet::Method = &Instances::TextField::displayAsPasswordGet;
template <> const TFunc_Instances_TextField_displayAsPasswordSet::TMethod TFunc_Instances_TextField_displayAsPasswordSet::Method = &Instances::TextField::displayAsPasswordSet;
template <> const TFunc_Instances_TextField_embedFontsGet::TMethod TFunc_Instances_TextField_embedFontsGet::Method = &Instances::TextField::embedFontsGet;
template <> const TFunc_Instances_TextField_embedFontsSet::TMethod TFunc_Instances_TextField_embedFontsSet::Method = &Instances::TextField::embedFontsSet;
template <> const TFunc_Instances_TextField_gridFitTypeGet::TMethod TFunc_Instances_TextField_gridFitTypeGet::Method = &Instances::TextField::gridFitTypeGet;
template <> const TFunc_Instances_TextField_gridFitTypeSet::TMethod TFunc_Instances_TextField_gridFitTypeSet::Method = &Instances::TextField::gridFitTypeSet;
template <> const TFunc_Instances_TextField_htmlTextGet::TMethod TFunc_Instances_TextField_htmlTextGet::Method = &Instances::TextField::htmlTextGet;
template <> const TFunc_Instances_TextField_htmlTextSet::TMethod TFunc_Instances_TextField_htmlTextSet::Method = &Instances::TextField::htmlTextSet;
template <> const TFunc_Instances_TextField_lengthGet::TMethod TFunc_Instances_TextField_lengthGet::Method = &Instances::TextField::lengthGet;
template <> const TFunc_Instances_TextField_maxCharsGet::TMethod TFunc_Instances_TextField_maxCharsGet::Method = &Instances::TextField::maxCharsGet;
template <> const TFunc_Instances_TextField_maxCharsSet::TMethod TFunc_Instances_TextField_maxCharsSet::Method = &Instances::TextField::maxCharsSet;
template <> const TFunc_Instances_TextField_maxScrollHGet::TMethod TFunc_Instances_TextField_maxScrollHGet::Method = &Instances::TextField::maxScrollHGet;
template <> const TFunc_Instances_TextField_maxScrollVGet::TMethod TFunc_Instances_TextField_maxScrollVGet::Method = &Instances::TextField::maxScrollVGet;
template <> const TFunc_Instances_TextField_mouseWheelEnabledGet::TMethod TFunc_Instances_TextField_mouseWheelEnabledGet::Method = &Instances::TextField::mouseWheelEnabledGet;
template <> const TFunc_Instances_TextField_mouseWheelEnabledSet::TMethod TFunc_Instances_TextField_mouseWheelEnabledSet::Method = &Instances::TextField::mouseWheelEnabledSet;
template <> const TFunc_Instances_TextField_multilineGet::TMethod TFunc_Instances_TextField_multilineGet::Method = &Instances::TextField::multilineGet;
template <> const TFunc_Instances_TextField_multilineSet::TMethod TFunc_Instances_TextField_multilineSet::Method = &Instances::TextField::multilineSet;
template <> const TFunc_Instances_TextField_numLinesGet::TMethod TFunc_Instances_TextField_numLinesGet::Method = &Instances::TextField::numLinesGet;
template <> const TFunc_Instances_TextField_restrictGet::TMethod TFunc_Instances_TextField_restrictGet::Method = &Instances::TextField::restrictGet;
template <> const TFunc_Instances_TextField_restrictSet::TMethod TFunc_Instances_TextField_restrictSet::Method = &Instances::TextField::restrictSet;
template <> const TFunc_Instances_TextField_scrollHGet::TMethod TFunc_Instances_TextField_scrollHGet::Method = &Instances::TextField::scrollHGet;
template <> const TFunc_Instances_TextField_scrollHSet::TMethod TFunc_Instances_TextField_scrollHSet::Method = &Instances::TextField::scrollHSet;
template <> const TFunc_Instances_TextField_scrollVGet::TMethod TFunc_Instances_TextField_scrollVGet::Method = &Instances::TextField::scrollVGet;
template <> const TFunc_Instances_TextField_scrollVSet::TMethod TFunc_Instances_TextField_scrollVSet::Method = &Instances::TextField::scrollVSet;
template <> const TFunc_Instances_TextField_selectableGet::TMethod TFunc_Instances_TextField_selectableGet::Method = &Instances::TextField::selectableGet;
template <> const TFunc_Instances_TextField_selectableSet::TMethod TFunc_Instances_TextField_selectableSet::Method = &Instances::TextField::selectableSet;
template <> const TFunc_Instances_TextField_selectionBeginIndexGet::TMethod TFunc_Instances_TextField_selectionBeginIndexGet::Method = &Instances::TextField::selectionBeginIndexGet;
template <> const TFunc_Instances_TextField_selectionEndIndexGet::TMethod TFunc_Instances_TextField_selectionEndIndexGet::Method = &Instances::TextField::selectionEndIndexGet;
template <> const TFunc_Instances_TextField_sharpnessGet::TMethod TFunc_Instances_TextField_sharpnessGet::Method = &Instances::TextField::sharpnessGet;
template <> const TFunc_Instances_TextField_sharpnessSet::TMethod TFunc_Instances_TextField_sharpnessSet::Method = &Instances::TextField::sharpnessSet;
template <> const TFunc_Instances_TextField_styleSheetGet::TMethod TFunc_Instances_TextField_styleSheetGet::Method = &Instances::TextField::styleSheetGet;
template <> const TFunc_Instances_TextField_styleSheetSet::TMethod TFunc_Instances_TextField_styleSheetSet::Method = &Instances::TextField::styleSheetSet;
template <> const TFunc_Instances_TextField_textGet::TMethod TFunc_Instances_TextField_textGet::Method = &Instances::TextField::textGet;
template <> const TFunc_Instances_TextField_textSet::TMethod TFunc_Instances_TextField_textSet::Method = &Instances::TextField::textSet;
template <> const TFunc_Instances_TextField_textColorGet::TMethod TFunc_Instances_TextField_textColorGet::Method = &Instances::TextField::textColorGet;
template <> const TFunc_Instances_TextField_textColorSet::TMethod TFunc_Instances_TextField_textColorSet::Method = &Instances::TextField::textColorSet;
template <> const TFunc_Instances_TextField_textHeightGet::TMethod TFunc_Instances_TextField_textHeightGet::Method = &Instances::TextField::textHeightGet;
template <> const TFunc_Instances_TextField_textWidthGet::TMethod TFunc_Instances_TextField_textWidthGet::Method = &Instances::TextField::textWidthGet;
template <> const TFunc_Instances_TextField_thicknessGet::TMethod TFunc_Instances_TextField_thicknessGet::Method = &Instances::TextField::thicknessGet;
template <> const TFunc_Instances_TextField_thicknessSet::TMethod TFunc_Instances_TextField_thicknessSet::Method = &Instances::TextField::thicknessSet;
template <> const TFunc_Instances_TextField_typeGet::TMethod TFunc_Instances_TextField_typeGet::Method = &Instances::TextField::typeGet;
template <> const TFunc_Instances_TextField_typeSet::TMethod TFunc_Instances_TextField_typeSet::Method = &Instances::TextField::typeSet;
template <> const TFunc_Instances_TextField_useRichTextClipboardGet::TMethod TFunc_Instances_TextField_useRichTextClipboardGet::Method = &Instances::TextField::useRichTextClipboardGet;
template <> const TFunc_Instances_TextField_useRichTextClipboardSet::TMethod TFunc_Instances_TextField_useRichTextClipboardSet::Method = &Instances::TextField::useRichTextClipboardSet;
template <> const TFunc_Instances_TextField_wordWrapGet::TMethod TFunc_Instances_TextField_wordWrapGet::Method = &Instances::TextField::wordWrapGet;
template <> const TFunc_Instances_TextField_wordWrapSet::TMethod TFunc_Instances_TextField_wordWrapSet::Method = &Instances::TextField::wordWrapSet;
template <> const TFunc_Instances_TextField_appendText::TMethod TFunc_Instances_TextField_appendText::Method = &Instances::TextField::appendText;
template <> const TFunc_Instances_TextField_getCharBoundaries::TMethod TFunc_Instances_TextField_getCharBoundaries::Method = &Instances::TextField::getCharBoundaries;
template <> const TFunc_Instances_TextField_getCharIndexAtPoint::TMethod TFunc_Instances_TextField_getCharIndexAtPoint::Method = &Instances::TextField::getCharIndexAtPoint;
template <> const TFunc_Instances_TextField_getFirstCharInParagraph::TMethod TFunc_Instances_TextField_getFirstCharInParagraph::Method = &Instances::TextField::getFirstCharInParagraph;
template <> const TFunc_Instances_TextField_getImageReference::TMethod TFunc_Instances_TextField_getImageReference::Method = &Instances::TextField::getImageReference;
template <> const TFunc_Instances_TextField_getLineIndexAtPoint::TMethod TFunc_Instances_TextField_getLineIndexAtPoint::Method = &Instances::TextField::getLineIndexAtPoint;
template <> const TFunc_Instances_TextField_getLineIndexOfChar::TMethod TFunc_Instances_TextField_getLineIndexOfChar::Method = &Instances::TextField::getLineIndexOfChar;
template <> const TFunc_Instances_TextField_getLineLength::TMethod TFunc_Instances_TextField_getLineLength::Method = &Instances::TextField::getLineLength;
template <> const TFunc_Instances_TextField_getLineMetrics::TMethod TFunc_Instances_TextField_getLineMetrics::Method = &Instances::TextField::getLineMetrics;
template <> const TFunc_Instances_TextField_getLineOffset::TMethod TFunc_Instances_TextField_getLineOffset::Method = &Instances::TextField::getLineOffset;
template <> const TFunc_Instances_TextField_getLineText::TMethod TFunc_Instances_TextField_getLineText::Method = &Instances::TextField::getLineText;
template <> const TFunc_Instances_TextField_getParagraphLength::TMethod TFunc_Instances_TextField_getParagraphLength::Method = &Instances::TextField::getParagraphLength;
template <> const TFunc_Instances_TextField_getTextFormat::TMethod TFunc_Instances_TextField_getTextFormat::Method = &Instances::TextField::getTextFormat;
template <> const TFunc_Instances_TextField_replaceSelectedText::TMethod TFunc_Instances_TextField_replaceSelectedText::Method = &Instances::TextField::replaceSelectedText;
template <> const TFunc_Instances_TextField_replaceText::TMethod TFunc_Instances_TextField_replaceText::Method = &Instances::TextField::replaceText;
template <> const TFunc_Instances_TextField_setSelection::TMethod TFunc_Instances_TextField_setSelection::Method = &Instances::TextField::setSelection;
template <> const TFunc_Instances_TextField_setTextFormat::TMethod TFunc_Instances_TextField_setTextFormat::Method = &Instances::TextField::setTextFormat;

namespace Instances
{
    TextField::TextField(InstanceTraits::Traits& t)
    : Instances::InteractiveObject(t)
//##protect##"instance::TextField::TextField()$data"
//##protect##"instance::TextField::TextField()$data"
    {
//##protect##"instance::TextField::TextField()$code"
//##protect##"instance::TextField::TextField()$code"
    }

    void TextField::alwaysShowSelectionGet(bool& result)
    {
//##protect##"instance::TextField::alwaysShowSelectionGet()"
        result = GetTextField()->DoesAlwaysShowSelection();
//##protect##"instance::TextField::alwaysShowSelectionGet()"
    }
    void TextField::alwaysShowSelectionSet(Value& result, bool value)
    {
//##protect##"instance::TextField::alwaysShowSelectionSet()"
        SF_UNUSED1(result);
        GetTextField()->SetAlwaysShowSelection(value);
//##protect##"instance::TextField::alwaysShowSelectionSet()"
    }
    void TextField::antiAliasTypeGet(ASString& result)
    {
//##protect##"instance::TextField::antiAliasTypeGet()"
        result = GetVM().GetStringManager().CreateConstString(
            GetTextField()->IsAAForReadability() ? "advanced" : "normal");
//##protect##"instance::TextField::antiAliasTypeGet()"
    }
    void TextField::antiAliasTypeSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::antiAliasTypeSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        if (value == "normal")
            ptxtDisp->ClearAAForReadability();
        else if (value == "advanced")
            ptxtDisp->SetAAForReadability();
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::antiAliasTypeSet()"
    }
    void TextField::autoSizeGet(ASString& result)
    {
//##protect##"instance::TextField::autoSizeGet()"
        GFx::TextField* ptxtDisp = GetTextField();
        if (!ptxtDisp->IsAutoSize())
            result = GetVM().GetStringManager().CreateConstString("none");
        else
        {
            switch(ptxtDisp->GetAlignment())
            {
            case Text::DocView::Align_Left:
                result = GetVM().GetStringManager().CreateConstString("left");
                break;
            case Text::DocView::Align_Right:
                result = GetVM().GetStringManager().CreateConstString("right");
                break;
            case Text::DocView::Align_Center:
                result = GetVM().GetStringManager().CreateConstString("center");
                break;
            default:  SF_ASSERT(0); // unknown
            }
        }
//##protect##"instance::TextField::autoSizeGet()"
    }
    void TextField::autoSizeSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::autoSizeSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        Text::DocView::ViewAlignment oldAlignment = ptxtDisp->GetAlignment();
        bool oldAutoSize = ptxtDisp->IsAutoSize();
        if (value == "none")
        {
            ptxtDisp->ClearAutoSize();
            ptxtDisp->SetAlignment(Text::DocView::Align_Left);
        }
        else 
        {
            ptxtDisp->SetAutoSize();
            if (value == "left")
                ptxtDisp->SetAlignment(Text::DocView::Align_Left);
            else if (value == "right")
                ptxtDisp->SetAlignment(Text::DocView::Align_Right);
            else if (value == "center")
                ptxtDisp->SetAlignment(Text::DocView::Align_Center);
        }
        if ((oldAlignment != ptxtDisp->GetAlignment()) || (oldAutoSize != ptxtDisp->IsAutoSize()))
            UpdateAutosizeSettings();
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::autoSizeSet()"
    }
    void TextField::backgroundGet(bool& result)
    {
//##protect##"instance::TextField::backgroundGet()"
        result = GetTextField()->HasBackground();
//##protect##"instance::TextField::backgroundGet()"
    }
    void TextField::backgroundSet(Value& result, bool value)
    {
//##protect##"instance::TextField::backgroundSet()"
        SF_UNUSED1(result);
        GetTextField()->SetBackground(value);
//##protect##"instance::TextField::backgroundSet()"
    }
    void TextField::backgroundColorGet(UInt32& result)
    {
//##protect##"instance::TextField::backgroundColorGet()"
        result = GetTextField()->GetBackgroundColor24();
//##protect##"instance::TextField::backgroundColorGet()"
    }
    void TextField::backgroundColorSet(Value& result, UInt32 value)
    {
//##protect##"instance::TextField::backgroundColorSet()"
        SF_UNUSED1(result);
        GetTextField()->SetBackgroundColor(value);
//##protect##"instance::TextField::backgroundColorSet()"
    }
    void TextField::borderGet(bool& result)
    {
//##protect##"instance::TextField::borderGet()"
        result = GetTextField()->HasBorder();
//##protect##"instance::TextField::borderGet()"
    }
    void TextField::borderSet(Value& result, bool value)
    {
//##protect##"instance::TextField::borderSet()"
        SF_UNUSED1(result);
        GetTextField()->SetBorder(value);
//##protect##"instance::TextField::borderSet()"
    }
    void TextField::borderColorGet(UInt32& result)
    {
//##protect##"instance::TextField::borderColorGet()"
        result = GetTextField()->GetBorderColor24();
//##protect##"instance::TextField::borderColorGet()"
    }
    void TextField::borderColorSet(Value& result, UInt32 value)
    {
//##protect##"instance::TextField::borderColorSet()"
        SF_UNUSED1(result);
        GetTextField()->SetBorderColor(value);
//##protect##"instance::TextField::borderColorSet()"
    }
    void TextField::bottomScrollVGet(SInt32& result)
    {
//##protect##"instance::TextField::bottomScrollVGet()"
        result = GetTextField()->GetBottomVScroll() + 1;
//##protect##"instance::TextField::bottomScrollVGet()"
    }
    void TextField::caretIndexGet(SInt32& result)
    {
//##protect##"instance::TextField::caretIndexGet()"
        result = static_cast<SInt32>(GetTextField()->GetCaretIndex());
//##protect##"instance::TextField::caretIndexGet()"
    }
    void TextField::condenseWhiteGet(bool& result)
    {
//##protect##"instance::TextField::condenseWhiteGet()"
        result = GetTextField()->IsCondenseWhite();
//##protect##"instance::TextField::condenseWhiteGet()"
    }
    void TextField::condenseWhiteSet(Value& result, bool value)
    {
//##protect##"instance::TextField::condenseWhiteSet()"
        SF_UNUSED1(result);
        GetTextField()->SetCondenseWhite(value);
//##protect##"instance::TextField::condenseWhiteSet()"
    }
    void TextField::contextMenuGet(Value& result)
    {
//##protect##"instance::TextField::contextMenuGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::TextField::contextMenuGet()");
//##protect##"instance::TextField::contextMenuGet()"
    }
    void TextField::defaultTextFormatGet(Value& result)
    {
//##protect##"instance::TextField::defaultTextFormatGet()"
        GFx::TextField* pthis = GetTextField();
        const Text::TextFormat*      ptextFmt = pthis->GetDefaultTextFormat();
        const Text::ParagraphFormat* pparaFmt = pthis->GetDefaultParagraphFormat();

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Instances::TextFormat> tfmt;
        asvm.ConstructInstance(tfmt, asvm.TextFormatClass, 0);
        SF_ASSERT(tfmt);

        SF_ASSERT(ptextFmt && pparaFmt);
        tfmt->SetTextFormat(*pparaFmt, *ptextFmt);
        result = Value(tfmt);
//##protect##"instance::TextField::defaultTextFormatGet()"
    }
    void TextField::defaultTextFormatSet(Value& result, Instances::TextFormat* value)
    {
//##protect##"instance::TextField::defaultTextFormatSet()"
        SF_UNUSED1(result);
        GFx::TextField* pthis = GetTextField();
        if (pthis->HasStyleSheet()) // doesn't work if style sheet is set
            return;

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        Text::TextFormat fmt(asvm.GetMovieImpl()->GetHeap());
        Text::ParagraphFormat paraFmt;

        value->GetTextFormat(&paraFmt, &fmt);

        const Text::TextFormat*      ptextFmt = pthis->GetDefaultTextFormat();
        const Text::ParagraphFormat* pparaFmt = pthis->GetDefaultParagraphFormat();
        pthis->SetDefaultTextFormat(ptextFmt->Merge(fmt));
        pthis->SetDefaultParagraphFormat(pparaFmt->Merge(paraFmt));
//##protect##"instance::TextField::defaultTextFormatSet()"
    }
    void TextField::displayAsPasswordGet(bool& result)
    {
//##protect##"instance::TextField::displayAsPasswordGet()"
        result = GetTextField()->IsPassword();
//##protect##"instance::TextField::displayAsPasswordGet()"
    }
    void TextField::displayAsPasswordSet(Value& result, bool value)
    {
//##protect##"instance::TextField::displayAsPasswordSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        bool oldPasswd = ptxtDisp->IsPassword();
        if (oldPasswd != value)
        {
            ptxtDisp->SetPassword(value);
            if (value)
                ptxtDisp->SetPasswordMode();
            else
                ptxtDisp->ClearPasswordMode();
            ptxtDisp->ForceCompleteReformat();
        }
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::displayAsPasswordSet()"
    }
    void TextField::embedFontsGet(bool& result)
    {
//##protect##"instance::TextField::embedFontsGet()"
        result = !GetTextField()->DoesUseDeviceFont();
//##protect##"instance::TextField::embedFontsGet()"
    }
    void TextField::embedFontsSet(Value& result, bool value)
    {
//##protect##"instance::TextField::embedFontsSet()"
        SF_UNUSED1(result);
        if (value)
            GetTextField()->ClearUseDeviceFont();
        else
            GetTextField()->SetUseDeviceFont();
//##protect##"instance::TextField::embedFontsSet()"
    }
    void TextField::gridFitTypeGet(ASString& result)
    {
//##protect##"instance::TextField::gridFitTypeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("TextField::gridFitTypeGet()");
//##protect##"instance::TextField::gridFitTypeGet()"
    }
    void TextField::gridFitTypeSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::gridFitTypeSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("TextField::gridFitTypeSet()");
//##protect##"instance::TextField::gridFitTypeSet()"
    }
    void TextField::htmlTextGet(ASString& result)
    {
//##protect##"instance::TextField::htmlTextGet()"
        result = GetTextField()->GetText(true);
//##protect##"instance::TextField::htmlTextGet()"
    }
    void TextField::htmlTextSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::htmlTextSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        ptxtDisp->SetHtml(true);
        ptxtDisp->SetTextValue(value.ToCStr(), true);
//##protect##"instance::TextField::htmlTextSet()"
    }
    void TextField::lengthGet(SInt32& result)
    {
//##protect##"instance::TextField::lengthGet()"
        result = static_cast<SInt32>(GetTextField()->GetTextLength());
//##protect##"instance::TextField::lengthGet()"
    }
    void TextField::maxCharsGet(SInt32& result)
    {
//##protect##"instance::TextField::maxCharsGet()"
        GFx::TextField* ptxtDisp = GetTextField();
        result = 0;
        if (ptxtDisp->HasMaxLength())
            result = ptxtDisp->GetMaxLength();
//##protect##"instance::TextField::maxCharsGet()"
    }
    void TextField::maxCharsSet(Value& result, SInt32 value)
    {
//##protect##"instance::TextField::maxCharsSet()"
        SF_UNUSED1(result);
        if (value >= 0)
            GetTextField()->SetMaxLength(value);
//##protect##"instance::TextField::maxCharsSet()"
    }
    void TextField::maxScrollHGet(SInt32& result)
    {
//##protect##"instance::TextField::maxScrollHGet()"
        result = (SInt32)GetTextField()->GetMaxHScroll();
//##protect##"instance::TextField::maxScrollHGet()"
    }
    void TextField::maxScrollVGet(SInt32& result)
    {
//##protect##"instance::TextField::maxScrollVGet()"
        result = GetTextField()->GetMaxVScroll() + 1;
//##protect##"instance::TextField::maxScrollVGet()"
    }
    void TextField::mouseWheelEnabledGet(bool& result)
    {
//##protect##"instance::TextField::mouseWheelEnabledGet()"
        result = GetTextField()->IsMouseWheelEnabled();
//##protect##"instance::TextField::mouseWheelEnabledGet()"
    }
    void TextField::mouseWheelEnabledSet(Value& result, bool value)
    {
//##protect##"instance::TextField::mouseWheelEnabledSet()"
        SF_UNUSED1(result);
        GetTextField()->SetMouseWheelEnabled(value);
//##protect##"instance::TextField::mouseWheelEnabledSet()"
    }
    void TextField::multilineGet(bool& result)
    {
//##protect##"instance::TextField::multilineGet()"
        result = GetTextField()->IsMultiline();
//##protect##"instance::TextField::multilineGet()"
    }
    void TextField::multilineSet(Value& result, bool value)
    {
//##protect##"instance::TextField::multilineSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        bool oldMultiline = ptxtDisp->IsMultiline();
        if (oldMultiline != value)
        {
            if (value)
                ptxtDisp->SetMultiline();
            else
                ptxtDisp->ClearMultiline();
            UpdateAutosizeSettings();
        }
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::multilineSet()"
    }
    void TextField::numLinesGet(SInt32& result)
    {
//##protect##"instance::TextField::numLinesGet()"
        result = GetTextField()->GetLinesCount();
//##protect##"instance::TextField::numLinesGet()"
    }
    void TextField::restrictGet(Value& result)
    {
//##protect##"instance::TextField::restrictGet()"
        const String* restr = GetTextField()->GetRestrict();
        if (restr)
            result = GetVM().GetStringManager().CreateString(*restr);
        else
            result.SetNull();
//##protect##"instance::TextField::restrictGet()"
    }
    void TextField::restrictSet(Value& result, const Value& value)
    {
//##protect##"instance::TextField::restrictSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        if (value.IsNull() || value.IsUndefined())
            ptxtDisp->ClearRestrict();
        else
        {
            ASString rstr = GetVM().GetStringManager().CreateEmptyString();
            value.Convert2String(rstr).DoNotCheck();
            ptxtDisp->SetRestrict(rstr);
        }
//##protect##"instance::TextField::restrictSet()"
    }
    void TextField::scrollHGet(SInt32& result)
    {
//##protect##"instance::TextField::scrollHGet()"
        result = (SInt32)GetTextField()->GetHScrollOffset();
//##protect##"instance::TextField::scrollHGet()"
    }
    void TextField::scrollHSet(Value& result, SInt32 value)
    {
//##protect##"instance::TextField::scrollHSet()"
        SF_UNUSED1(result);
        if (value < 0) value = 0;
        GFx::TextField* ptxtDisp = GetTextField();
        ptxtDisp->SetHScrollOffset((Double)value);
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::scrollHSet()"
    }
    void TextField::scrollVGet(SInt32& result)
    {
//##protect##"instance::TextField::scrollVGet()"
        result = GetTextField()->GetVScrollOffset() + 1;
//##protect##"instance::TextField::scrollVGet()"
    }
    void TextField::scrollVSet(Value& result, SInt32 value)
    {
//##protect##"instance::TextField::scrollVSet()"
        SF_UNUSED(result);
        if (value < 1) value = 1;
        GFx::TextField* ptxtDisp = GetTextField();
        ptxtDisp->SetVScrollOffset((unsigned)(value - 1));
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::scrollVSet()"
    }
    void TextField::selectableGet(bool& result)
    {
//##protect##"instance::TextField::selectableGet()"
        result = GetTextField()->IsSelectable();
//##protect##"instance::TextField::selectableGet()"
    }
    void TextField::selectableSet(Value& result, bool value)
    {
//##protect##"instance::TextField::selectableSet()"
        SF_UNUSED1(result);
        GetTextField()->SetSelectable(value);
//##protect##"instance::TextField::selectableSet()"
    }
    void TextField::selectionBeginIndexGet(SInt32& result)
    {
//##protect##"instance::TextField::selectionBeginIndexGet()"
        GFx::TextField* ptxtDisp = GetTextField();
        result = static_cast<SInt32>(ptxtDisp->GetBeginIndex());
//##protect##"instance::TextField::selectionBeginIndexGet()"
    }
    void TextField::selectionEndIndexGet(SInt32& result)
    {
//##protect##"instance::TextField::selectionEndIndexGet()"
        GFx::TextField* ptxtDisp = GetTextField();
        result = static_cast<SInt32>(ptxtDisp->GetEndIndex());
//##protect##"instance::TextField::selectionEndIndexGet()"
    }
    void TextField::sharpnessGet(Value::Number& result)
    {
//##protect##"instance::TextField::sharpnessGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("TextField::sharpnessGet()");
//##protect##"instance::TextField::sharpnessGet()"
    }
    void TextField::sharpnessSet(Value& result, Value::Number value)
    {
//##protect##"instance::TextField::sharpnessSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("TextField::sharpnessSet()");
//##protect##"instance::TextField::sharpnessSet()"
    }
    void TextField::styleSheetGet(Value& result)
    {
//##protect##"instance::TextField::styleSheetGet()"
        result.SetUndefined();

#ifdef GFX_ENABLE_CSS

        AvmTextField* patf = ToAvmTextField(GetTextField());
        if (patf->GetCSSData() && patf->GetCSSData()->pASStyleSheet.GetPtr())
            result = patf->GetCSSData()->pASStyleSheet;

#else

        SF_UNUSED1(result);
        WARN_NOT_SUPPORTED_MISSING_DEPENDENCY("TextField::styleSheetGet()");

#endif

//##protect##"instance::TextField::styleSheetGet()"
    }
    void TextField::styleSheetSet(Value& result, Instances::StyleSheet* value)
    {
//##protect##"instance::TextField::styleSheetSet()"

#ifdef GFX_ENABLE_CSS
        SF_UNUSED1(result);

        GFx::TextField* ptf = GetTextField();
        AvmTextField* patf = ToAvmTextField(GetTextField());

        if (value)
        {
            if (!ptf->GetCSSData())
                ptf->SetCSSData(new AvmTextField::CSSHolder);
            patf->GetCSSData()->pASStyleSheet = value;

            // Make the textfield read-only
            if (ptf->HasEditorKit())
            {
                ptf->GetEditorKit()->SetReadOnly();
            }

            patf->SetDirtyFlag();
        }
        else if (patf->GetCSSData())
            patf->GetCSSData()->pASStyleSheet = NULL;

        ptf->CollectUrlZones();
        ptf->UpdateUrlStyles();
        ptf->SetNeedUpdateLayoutFlag();

#else

        SF_UNUSED2(result, value);
        WARN_NOT_SUPPORTED_MISSING_DEPENDENCY("TextField::styleSheetSet()");

#endif

//##protect##"instance::TextField::styleSheetSet()"
    }
    void TextField::textGet(ASString& result)
    {
//##protect##"instance::TextField::textGet()"
        result = GetTextField()->GetText(false);
//##protect##"instance::TextField::textGet()"
    }
    void TextField::textSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::textSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        ptxtDisp->SetHtml(false);
        ptxtDisp->SetText(ASString(value).ToCStr(), false);
//##protect##"instance::TextField::textSet()"
    }
    void TextField::textColorGet(UInt32& result)
    {
//##protect##"instance::TextField::textColorGet()"
        result = GetTextField()->GetTextColor32();
//##protect##"instance::TextField::textColorGet()"
    }
    void TextField::textColorSet(Value& result, UInt32 value)
    {
//##protect##"instance::TextField::textColorSet()"
        SF_UNUSED1(result);
        GetTextField()->SetTextColor(value);
//##protect##"instance::TextField::textColorSet()"
    }
    void TextField::textHeightGet(Value::Number& result)
    {
//##protect##"instance::TextField::textHeightGet()"
        result = GetTextField()->GetTextHeight();
//##protect##"instance::TextField::textHeightGet()"
    }
    void TextField::textWidthGet(Value::Number& result)
    {
//##protect##"instance::TextField::textWidthGet()"
        result = GetTextField()->GetTextWidth();
//##protect##"instance::TextField::textWidthGet()"
    }
    void TextField::thicknessGet(Value::Number& result)
    {
//##protect##"instance::TextField::thicknessGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("TextField::thicknessGet()");
//##protect##"instance::TextField::thicknessGet()"
    }
    void TextField::thicknessSet(Value& result, Value::Number value)
    {
//##protect##"instance::TextField::thicknessSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("TextField::thicknessSet()");
//##protect##"instance::TextField::thicknessSet()"
    }
    void TextField::typeGet(ASString& result)
    {
//##protect##"instance::TextField::typeGet()"
        result = GetVM().GetStringManager().CreateConstString(
            GetTextField()->IsReadOnly() ? "dynamic" : "input");
//##protect##"instance::TextField::typeGet()"
    }
    void TextField::typeSet(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::typeSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        if (value == "dynamic")
        {
            if (ptxtDisp->HasEditorKit())
                ptxtDisp->GetEditorKit()->SetReadOnly();
        }
        else if (value == "input" && !ptxtDisp->HasStyleSheet())
        {
            Text::EditorKit* peditor = ptxtDisp->CreateEditorKit();
            peditor->ClearReadOnly();
        }
        ptxtDisp->ForceReformat();
//##protect##"instance::TextField::typeSet()"
    }
    void TextField::useRichTextClipboardGet(bool& result)
    {
//##protect##"instance::TextField::useRichTextClipboardGet()"
        result = GetTextField()->DoesUseRichClipboard();
//##protect##"instance::TextField::useRichTextClipboardGet()"
    }
    void TextField::useRichTextClipboardSet(Value& result, bool value)
    {
//##protect##"instance::TextField::useRichTextClipboardSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        ptxtDisp->SetUseRichClipboard(value);
        if (ptxtDisp->HasEditorKit())
        {
            if (ptxtDisp->DoesUseRichClipboard())
                ptxtDisp->GetEditorKit()->SetUseRichClipboard();
            else
                ptxtDisp->GetEditorKit()->ClearUseRichClipboard();
        }
//##protect##"instance::TextField::useRichTextClipboardSet()"
    }
    void TextField::wordWrapGet(bool& result)
    {
//##protect##"instance::TextField::wordWrapGet()"
        result = GetTextField()->IsWordWrap();
//##protect##"instance::TextField::wordWrapGet()"
    }
    void TextField::wordWrapSet(Value& result, bool value)
    {
//##protect##"instance::TextField::wordWrapSet()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        bool oldWordWrap = ptxtDisp->IsWordWrap();
        if (oldWordWrap != value)
        {
            if (value)
                ptxtDisp->SetWordWrap();
            else
                ptxtDisp->ClearWordWrap();
			UpdateAutosizeSettings();
        }
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::wordWrapSet()"
    }
    void TextField::appendText(Value& result, const ASString& newText)
    {
//##protect##"instance::TextField::appendText()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();
        if (ptxtDisp->HasStyleSheet()) // doesn't work if style sheet is set
            return;
        ptxtDisp->AppendText(newText.ToCStr());
        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::appendText()"
    }
    void TextField::getCharBoundaries(Value& result, SInt32 charIndex)
    {
//##protect##"instance::TextField::getCharBoundaries()"
        RectF charBounds;
        charBounds.Clear();
        if (GetTextField()->GetCharBoundaries(&charBounds, charIndex))
        {
            Value argv[4];
            argv[0].SetNumber(Alg::IRound(TwipsToPixels(charBounds.x1)));
            argv[1].SetNumber(Alg::IRound(TwipsToPixels(charBounds.y1)));
            argv[2].SetNumber(Alg::IRound(TwipsToPixels(charBounds.Width())));
            argv[3].SetNumber(Alg::IRound(TwipsToPixels(charBounds.Height())));

            ASVM& asvm = static_cast<ASVM&>(GetVM());
            SPtr<Rectangle> rect;
            asvm.ConstructInstance(rect, asvm.RectangleClass, 4, argv);
            SF_ASSERT(rect);

            result = Value(rect);
        }
//##protect##"instance::TextField::getCharBoundaries()"
    }
    void TextField::getCharIndexAtPoint(SInt32& result, Value::Number x, Value::Number y)
    {
//##protect##"instance::TextField::getCharIndexAtPoint()"
        UPInt pos = GetTextField()->GetCharIndexAtPoint(float(PixelsToTwips(x)), float(PixelsToTwips(y)));
        if (!Alg::IsMax(pos))
            result = static_cast<SInt32>(pos);
        else
            result = -1;
//##protect##"instance::TextField::getCharIndexAtPoint()"
    }
    void TextField::getFirstCharInParagraph(SInt32& result, SInt32 charIndex)
    {
//##protect##"instance::TextField::getFirstCharInParagraph()"
        if (charIndex < 0)
            result = -1;
        else {
            UPInt off = GetTextField()->GetFirstCharInParagraph(unsigned(charIndex));
            if (!Alg::IsMax(off))
                result = static_cast<SInt32>(off);
            else
                result = -1;
        }
//##protect##"instance::TextField::getFirstCharInParagraph()"
    }
    void TextField::getImageReference(Value& result, const ASString& id)
    {
//##protect##"instance::TextField::getImageReference()"
        SF_UNUSED2(result, id);
        WARN_NOT_IMPLEMENTED("TextField::getImageReference()");
//##protect##"instance::TextField::getImageReference()"
    }
    void TextField::getLineIndexAtPoint(SInt32& result, Value::Number x, Value::Number y)
    {
//##protect##"instance::TextField::getLineIndexAtPoint()"
        unsigned  pos = GetTextField()->GetLineIndexAtPoint(float(PixelsToTwips(x)), float(PixelsToTwips(y)));
        if (!Alg::IsMax(pos))
            result = pos;
        else
            result = -1;
//##protect##"instance::TextField::getLineIndexAtPoint()"
    }
    void TextField::getLineIndexOfChar(SInt32& result, SInt32 charIndex)
    {
//##protect##"instance::TextField::getLineIndexOfChar()"
        if (charIndex < 0)
            result = -1;
        else {
            unsigned off = GetTextField()->GetLineIndexOfChar(unsigned(charIndex));
            if (!Alg::IsMax(off))
                result = off;
            else
                result = -1;
        }
//##protect##"instance::TextField::getLineIndexOfChar()"
    }
    void TextField::getLineLength(SInt32& result, SInt32 lineIndex)
    {
//##protect##"instance::TextField::getLineLength()"
        if (lineIndex < 0)
            result = -1;
        else {
            UPInt len = GetTextField()->GetLineLength(unsigned(lineIndex));
            if (!Alg::IsMax(len))
                result = static_cast<SInt32>(len);
            else
                result = -1;
        }
//##protect##"instance::TextField::getLineLength()"
    }
    void TextField::getLineMetrics(Value& result, SInt32 lineIndex)
    {
//##protect##"instance::TextField::getLineMetrics()"
        Text::DocView::LineMetrics metrics;
        if (GetTextField()->GetLineMetrics(unsigned(lineIndex), &metrics))
        {
            Value argv[6];
            argv[0].SetNumber(Alg::IRound(TwipsToPixels(metrics.Ascent)));
            argv[1].SetNumber(Alg::IRound(TwipsToPixels(metrics.Descent)));
            argv[2].SetNumber(Alg::IRound(TwipsToPixels(metrics.Height)));
            argv[3].SetNumber(Alg::IRound(TwipsToPixels(metrics.Leading)));
            argv[4].SetNumber(Alg::IRound(TwipsToPixels(metrics.Width)));
            argv[5].SetNumber(Alg::IRound(TwipsToPixels(metrics.FirstCharXOff)));

            ASVM& asvm = static_cast<ASVM&>(GetVM());
            SPtr<TextLineMetrics> tlm;

            SPtr<AS3::Object> obj = asvm.GetClass("flash.text.TextLineMetrics");
            asvm.ConstructInstance(tlm, obj, 6, argv);
            SF_ASSERT(tlm);

            result = Value(tlm);
        }
//##protect##"instance::TextField::getLineMetrics()"
    }
    void TextField::getLineOffset(SInt32& result, SInt32 lineIndex)
    {
//##protect##"instance::TextField::getLineOffset()"
        if (lineIndex < 0)
            result= -1;
        else {
            UPInt off = GetTextField()->GetLineOffset(unsigned(lineIndex));
            if (!Alg::IsMax(off))
                result = static_cast<SInt32>(off);
            else
                result = -1;
        }
//##protect##"instance::TextField::getLineOffset()"
    }
    void TextField::getLineText(ASString& result, SInt32 lineIndex)
    {
//##protect##"instance::TextField::getLineText()"
        UPInt len = 0;
        const wchar_t* ptext = GetTextField()->GetLineText(unsigned(lineIndex), &len);
        if (ptext)
        {
            String str;
            str.AppendString(ptext, (SPInt)len);
            result = GetVM().GetStringManager().CreateString(str);
        }
        else
            result = GetVM().GetStringManager().CreateConstString("");

//##protect##"instance::TextField::getLineText()"
    }
    void TextField::getParagraphLength(SInt32& result, SInt32 charIndex)
    {
//##protect##"instance::TextField::getParagraphLength()"
        result = static_cast<SInt32>(GetTextField()->GetParagraphLength(charIndex));
//##protect##"instance::TextField::getParagraphLength()"
    }
    void TextField::getTextFormat(Value& result, SInt32 beginIndex, SInt32 endIndex)
    {
//##protect##"instance::TextField::getTextFormat()"
        if (beginIndex == -1)
            beginIndex = 0;
        if (endIndex == -1)
            endIndex = beginIndex + 1;
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Instances::TextFormat> tfmt;
        asvm.ConstructInstance(tfmt, asvm.TextFormatClass, 0);
        SF_ASSERT(tfmt);

        if (beginIndex <= endIndex)
        {
            Text::TextFormat textFmt(asvm.GetMovieImpl()->GetHeap());
            Text::ParagraphFormat paraFmt;
            GetTextField()->GetTextAndParagraphFormat(&textFmt, &paraFmt, beginIndex, endIndex);

            tfmt->SetTextFormat(paraFmt, textFmt);
        }
        result = tfmt;
//##protect##"instance::TextField::getTextFormat()"
    }
    void TextField::replaceSelectedText(Value& result, const ASString& value)
    {
//##protect##"instance::TextField::replaceSelectedText()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();

        if (ptxtDisp->HasStyleSheet())
            return;

        const Text::TextFormat* ptextFmt = ptxtDisp->GetDefaultTextFormat();
        const Text::ParagraphFormat* pparaFmt = ptxtDisp->GetDefaultParagraphFormat();

        unsigned len = value.GetLength();
        UPInt startPos = ptxtDisp->GetEditorKit()->GetBeginSelection();
        UPInt endPos   = ptxtDisp->GetEditorKit()->GetEndSelection();

        wchar_t buf[1024];
        if (len < sizeof(buf)/sizeof(buf[0]))
        {
            UTF8Util::DecodeString(buf, value.ToCStr());
            ptxtDisp->ReplaceText(buf, startPos, endPos);
        }
        else {
            wchar_t* pbuf = (wchar_t*)SF_ALLOC((len + 1) * sizeof(wchar_t), StatMV_Text_Mem);
            UTF8Util::DecodeString(pbuf, value.ToCStr());
            ptxtDisp->ReplaceText(pbuf, startPos, endPos);
            SF_FREE(pbuf);
        }
        ptxtDisp->GetEditorKit()->SetCursorPos(startPos + len, false);

        if (pparaFmt)
            ptxtDisp->SetParagraphFormat(*pparaFmt, startPos, startPos + len);
        if (ptextFmt)
            ptxtDisp->SetTextFormat(*ptextFmt, startPos, startPos + len);

        ptxtDisp->SetDirtyFlag();
//##protect##"instance::TextField::replaceSelectedText()"
    }
    void TextField::replaceText(Value& result, SInt32 beginIndex, SInt32 endIndex, const ASString& newText)
    {
//##protect##"instance::TextField::replaceText()"
        SF_UNUSED1(result);
        GFx::TextField* ptxtDisp = GetTextField();

        if (ptxtDisp->HasStyleSheet())
            return;

        unsigned len = newText.GetLength();
        unsigned startPos = unsigned(beginIndex);
        unsigned endPos   = unsigned(endIndex);
        if (beginIndex >= 0 && endIndex >= 0 && startPos <= endPos)
        {
            const Text::TextFormat* ptextFmt;
            const Text::ParagraphFormat* pparaFmt;
            UPInt prevLen = ptxtDisp->GetTextLength();
            UPInt newLen  = prevLen - (endPos - startPos) + len;
            if (startPos >= prevLen)
            {
                ptextFmt = ptxtDisp->GetDefaultTextFormat();
                pparaFmt = ptxtDisp->GetDefaultParagraphFormat();
            }
            else
                ptxtDisp->GetTextAndParagraphFormat(&ptextFmt, &pparaFmt, startPos);
            if (ptextFmt) ptextFmt->AddRef(); // save format from possible releasing
            if (pparaFmt) pparaFmt->AddRef(); // save format from possible releasing

            wchar_t buf[1024];
            if (len < sizeof(buf)/sizeof(buf[0]))
            {
                UTF8Util::DecodeString(buf, newText.ToCStr());
                ptxtDisp->ReplaceText(buf, startPos, endPos);
            }
            else {
                wchar_t* pbuf = (wchar_t*)SF_ALLOC((len + 1) * sizeof(wchar_t), StatMV_Text_Mem);
                UTF8Util::DecodeString(pbuf, newText.ToCStr());
                ptxtDisp->ReplaceText(pbuf, startPos, endPos);
                SF_FREE(pbuf);
            }

            if (ptxtDisp->HasEditorKit())
            {
                if (ptxtDisp->GetEditorKit()->GetCursorPos() > newLen)
                    ptxtDisp->GetEditorKit()->SetCursorPos(newLen, false);
            }

            if (pparaFmt)
                ptxtDisp->SetParagraphFormat(*pparaFmt, startPos, startPos + len);
            if (ptextFmt)	
                ptxtDisp->SetTextFormat(*ptextFmt, startPos, startPos + len);
			
            if (ptextFmt) ptextFmt->Release();
            if (pparaFmt) pparaFmt->Release();
            ptxtDisp->SetDirtyFlag();
        }
//##protect##"instance::TextField::replaceText()"
    }
    void TextField::setSelection(Value& result, SInt32 beginIndex, SInt32 endIndex)
    {
//##protect##"instance::TextField::setSelection()"
        SF_UNUSED1(result);
        GetTextField()->SetSelection(beginIndex, endIndex);
//##protect##"instance::TextField::setSelection()"
    }
    void TextField::setTextFormat(Value& result, Instances::TextFormat* format, SInt32 beginIndex, SInt32 endIndex)
    {
//##protect##"instance::TextField::setTextFormat()"
        SF_UNUSED1(result);
        if (!format)
            return; // ?exception?
        if (beginIndex == -1)
            beginIndex = 0;
        if (endIndex == -1)
            endIndex = SF_MAX_SINT32;
        if (beginIndex <= endIndex)
        {
            GFx::TextField* pthis = GetTextField();
            ASVM& asvm = static_cast<ASVM&>(GetVM());
            Text::TextFormat fmt(asvm.GetMovieImpl()->GetHeap());
            Text::ParagraphFormat paraFmt;
            
            format->GetTextFormat(&paraFmt, &fmt);

            pthis->SetTextFormat(fmt, (unsigned)beginIndex, (unsigned)endIndex);
            pthis->SetParagraphFormat(paraFmt, (unsigned)beginIndex, (unsigned)endIndex);
            pthis->SetDirtyFlag();
        }
//##protect##"instance::TextField::setTextFormat()"
    }

//##protect##"instance$methods"
    void TextField::InitInstance(bool extCall)
    {
        if (!extCall)
        {
            TextField::CreateStageObject();
            GFx::TextField* tf = GetTextField();
            tf->SetWidth(100);
            tf->SetHeight(100);
            tf->SetTextValue("", true);
        }
    }

    GFx::DisplayObject* TextField::CreateStageObject()
    {
        if (!pDispObj)
        {
            MovieRoot* proot = static_cast<const ASVM&>(GetVM()).GetMovieRoot();

            CharacterCreateInfo ccinfo = 
                proot->GetMovieDefImpl()->GetCharacterCreateInfo(
                    ResourceId(CharacterDef::CharId_EmptyTextField));
            SF_ASSERT(ccinfo.pCharDef);

            // figure out MovieDefImpl from current call frame.
            const VMAbcFile& abcFile = GetVM().GetCurrCallFrame().GetFile();
            
            ccinfo.pBindDefImpl = static_cast<const ASVM::AbcFileWithMovieDef&>(abcFile.GetAbcFile()).pDefImpl;
            pDispObj = *static_cast<GFx::DisplayObject*>(proot->GetASSupport()->
                CreateCharacterInstance(
                    proot->GetMovieImpl(), ccinfo, NULL, 
                    ResourceId(CharacterDef::CharId_EmptyTextField)));
            ToAvmDisplayObj(pDispObj)->AssignAS3Obj(this);
        }
        return pDispObj;
    }

    void TextField::UpdateAutosizeSettings()
    {
        GFx::TextField* ptf = GetTextField();
        const bool autoSizeByX = (ptf->IsAutoSize() && !ptf->IsWordWrap());
        const bool autoSizeByY = (ptf->IsAutoSize());
        if (autoSizeByX)
            ptf->SetAutoSizeX();
        else
            ptf->ClearAutoSizeX();
        if (autoSizeByY)
            ptf->SetAutoSizeY();
        else
            ptf->ClearAutoSizeY();
        ptf->SetNeedUpdateGeomData();
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TextField::ti[TextField::ThunkInfoNum] = {
        {TFunc_Instances_TextField_alwaysShowSelectionGet::Func, &BooleanCI, "alwaysShowSelection", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_alwaysShowSelectionSet::Func, NULL, "alwaysShowSelection", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_antiAliasTypeGet::Func, &StringCI, "antiAliasType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_antiAliasTypeSet::Func, NULL, "antiAliasType", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_autoSizeGet::Func, &StringCI, "autoSize", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_autoSizeSet::Func, NULL, "autoSize", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_backgroundGet::Func, &BooleanCI, "background", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_backgroundSet::Func, NULL, "background", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_backgroundColorGet::Func, &uintCI, "backgroundColor", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_backgroundColorSet::Func, NULL, "backgroundColor", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_borderGet::Func, &BooleanCI, "border", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_borderSet::Func, NULL, "border", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_borderColorGet::Func, &uintCI, "borderColor", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_borderColorSet::Func, NULL, "borderColor", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_bottomScrollVGet::Func, &int_CI, "bottomScrollV", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_caretIndexGet::Func, &int_CI, "caretIndex", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_condenseWhiteGet::Func, &BooleanCI, "condenseWhite", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_condenseWhiteSet::Func, NULL, "condenseWhite", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_defaultTextFormatGet::Func, &TextFormatCI, "defaultTextFormat", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_defaultTextFormatSet::Func, NULL, "defaultTextFormat", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_displayAsPasswordGet::Func, &BooleanCI, "displayAsPassword", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_displayAsPasswordSet::Func, NULL, "displayAsPassword", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_embedFontsGet::Func, &BooleanCI, "embedFonts", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_embedFontsSet::Func, NULL, "embedFonts", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_gridFitTypeGet::Func, &StringCI, "gridFitType", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_gridFitTypeSet::Func, NULL, "gridFitType", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_htmlTextGet::Func, &StringCI, "htmlText", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_htmlTextSet::Func, NULL, "htmlText", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_lengthGet::Func, &int_CI, "length", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_maxCharsGet::Func, &int_CI, "maxChars", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_maxCharsSet::Func, NULL, "maxChars", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_maxScrollHGet::Func, &int_CI, "maxScrollH", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_maxScrollVGet::Func, &int_CI, "maxScrollV", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_mouseWheelEnabledGet::Func, &BooleanCI, "mouseWheelEnabled", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_mouseWheelEnabledSet::Func, NULL, "mouseWheelEnabled", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_multilineGet::Func, &BooleanCI, "multiline", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_multilineSet::Func, NULL, "multiline", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_numLinesGet::Func, &int_CI, "numLines", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_restrictGet::Func, &ObjectCI, "restrict", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_restrictSet::Func, NULL, "restrict", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_scrollHGet::Func, &int_CI, "scrollH", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_scrollHSet::Func, NULL, "scrollH", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_scrollVGet::Func, &int_CI, "scrollV", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_scrollVSet::Func, NULL, "scrollV", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_selectableGet::Func, &BooleanCI, "selectable", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_selectableSet::Func, NULL, "selectable", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_selectionBeginIndexGet::Func, &int_CI, "selectionBeginIndex", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_selectionEndIndexGet::Func, &int_CI, "selectionEndIndex", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_sharpnessGet::Func, &NumberCI, "sharpness", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_sharpnessSet::Func, NULL, "sharpness", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_styleSheetGet::Func, &StyleSheetCI, "styleSheet", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_styleSheetSet::Func, NULL, "styleSheet", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_textGet::Func, &StringCI, "text", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_textSet::Func, NULL, "text", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_textColorGet::Func, &uintCI, "textColor", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_textColorSet::Func, NULL, "textColor", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_textHeightGet::Func, &NumberCI, "textHeight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_textWidthGet::Func, &NumberCI, "textWidth", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_thicknessGet::Func, &NumberCI, "thickness", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_thicknessSet::Func, NULL, "thickness", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_typeGet::Func, &StringCI, "type", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_typeSet::Func, NULL, "type", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_useRichTextClipboardGet::Func, &BooleanCI, "useRichTextClipboard", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_useRichTextClipboardSet::Func, NULL, "useRichTextClipboard", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_wordWrapGet::Func, &BooleanCI, "wordWrap", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextField_wordWrapSet::Func, NULL, "wordWrap", NULL, CT_Set, 1, 1},
        {TFunc_Instances_TextField_appendText::Func, NULL, "appendText", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getCharBoundaries::Func, &RectangleCI, "getCharBoundaries", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getCharIndexAtPoint::Func, &int_CI, "getCharIndexAtPoint", NULL, CT_Method, 2, 2},
        {TFunc_Instances_TextField_getFirstCharInParagraph::Func, &int_CI, "getFirstCharInParagraph", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getImageReference::Func, &DisplayObjectCI, "getImageReference", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getLineIndexAtPoint::Func, &int_CI, "getLineIndexAtPoint", NULL, CT_Method, 2, 2},
        {TFunc_Instances_TextField_getLineIndexOfChar::Func, &int_CI, "getLineIndexOfChar", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getLineLength::Func, &int_CI, "getLineLength", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getLineMetrics::Func, &TextLineMetricsCI, "getLineMetrics", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getLineOffset::Func, &int_CI, "getLineOffset", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getLineText::Func, &StringCI, "getLineText", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getParagraphLength::Func, &int_CI, "getParagraphLength", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_getTextFormat::Func, &TextFormatCI, "getTextFormat", NULL, CT_Method, 0, 2},
        {TFunc_Instances_TextField_replaceSelectedText::Func, NULL, "replaceSelectedText", NULL, CT_Method, 1, 1},
        {TFunc_Instances_TextField_replaceText::Func, NULL, "replaceText", NULL, CT_Method, 3, 3},
        {TFunc_Instances_TextField_setSelection::Func, NULL, "setSelection", NULL, CT_Method, 2, 2},
        {TFunc_Instances_TextField_setTextFormat::Func, NULL, "setTextFormat", NULL, CT_Method, 1, 3},
    };

    TextField::TextField(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextField::TextField()"
//##protect##"InstanceTraits::TextField::TextField()"
        SetMemSize(sizeof(Instances::TextField));

    }

    Pickable<Instances::TextField> TextField::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextField>(new(t.Alloc()) Instances::TextField(t));
    }

    void TextField::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    TextField::TextField(VM& vm)
    : Traits(vm, TextFieldCI)
    {
//##protect##"ClassTraits::TextField::TextField()"
//##protect##"ClassTraits::TextField::TextField()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextField(vm, TextFieldCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextField::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextField(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFieldCI = {
    ClassInfo::CompileTime,
    "TextField", "flash.text", &InteractiveObjectCI,
    ClassTraits::TextField::MakeClassTraits,
    0,
    0,
    InstanceTraits::TextField::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::TextField::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

