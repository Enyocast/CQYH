//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_TextFieldEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_TextFieldEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    TextFieldEx::TextFieldEx(ClassTraits::Traits& t)
    : Class(t)
    , VALIGN_NONE("none")
    , VALIGN_TOP("top")
    , VALIGN_CENTER("center")
    , VALIGN_BOTTOM("bottom")
    , TEXTAUTOSZ_NONE("none")
    , TEXTAUTOSZ_SHRINK("shrink")
    , TEXTAUTOSZ_FIT("fit")
    {
//##protect##"class_::TextFieldEx::TextFieldEx()"
//##protect##"class_::TextFieldEx::TextFieldEx()"
    }
    void TextFieldEx::appendHtml(Value& result, Instances::TextField* textField, const ASString& newHtml)
    {
//##protect##"class_::TextFieldEx::appendHtml()"
        
        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (ptxtDisp->HasStyleSheet()) // doesn't work if style sheet is set
                return;
            Text::StyledText::HTMLImageTagInfoArray imageInfoArray(Memory::GetHeapByAddress(ptxtDisp));
            ptxtDisp->AppendHtml(newHtml.ToCStr(), SF_MAX_UPINT, false, &imageInfoArray);
            if (imageInfoArray.GetSize() > 0)
            {
                ptxtDisp->ProcessImageTags(imageInfoArray);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::appendHtml()"
    }
    void TextFieldEx::setVerticalAlign(Value& result, Instances::TextField* textField, const ASString& valign)
    {
//##protect##"class_::TextFieldEx::setVerticalAlign()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (valign == "none")
                ptxtDisp->SetVAlignment(Text::DocView::VAlign_None);
            else 
            {
                if (valign == "top")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Top);
                else if (valign == "bottom")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Bottom);
                else if (valign == "center")
                    ptxtDisp->SetVAlignment(Text::DocView::VAlign_Center);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::setVerticalAlign()"
    }
    void TextFieldEx::getVerticalAlign(ASString& result, Instances::TextField* textField)
    {
//##protect##"class_::TextFieldEx::getVerticalAlign()"

        GFx::TextField* ptxtDisp = textField->GetTextField();
        switch (ptxtDisp->GetVAlignment())
        {
        case Text::DocView::VAlign_Bottom:  result = "bottom"; break;
        case Text::DocView::VAlign_Center:  result = "center"; break;
        case Text::DocView::VAlign_Top:     result = "top"; break;
        default:                            result = "none"; break;
        }

//##protect##"class_::TextFieldEx::getVerticalAlign()"
    }
    void TextFieldEx::setTextAutoSize(Value& result, Instances::TextField* textField, const ASString& autoSz)
    {
//##protect##"class_::TextFieldEx::setTextAutoSize()"

        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            GFx::TextField* ptxtDisp = textField->GetTextField();
            if (autoSz == "none")
                ptxtDisp->SetTextAutoSize(Text::DocView::TAS_None);
            else 
            {
                if (autoSz == "shrink")
                    ptxtDisp->SetTextAutoSize(Text::DocView::TAS_Shrink);
                else if (autoSz == "fit")
                    ptxtDisp->SetTextAutoSize(Text::DocView::TAS_Fit);
            }
            ptxtDisp->SetDirtyFlag();
        }

//##protect##"class_::TextFieldEx::setTextAutoSize()"
    }
    void TextFieldEx::getTextAutoSize(ASString& result, Instances::TextField* textField)
    {
//##protect##"class_::TextFieldEx::getTextAutoSize()"

        GFx::TextField* ptxtDisp = textField->GetTextField();
        switch (ptxtDisp->GetTextAutoSize())
        {
        case Text::DocView::TAS_Shrink:     result = "shrink"; break;
        case Text::DocView::TAS_Fit:        result = "fit"; break;
        default:                            result = "none"; break;
        }

//##protect##"class_::TextFieldEx::getTextAutoSize()"
    }
    void TextFieldEx::setIMEEnabled(Value& result, Instances::TextField* textField, bool isEnabled)
    {
//##protect##"class_::TextFieldEx::setIMEEnabled()"
		SF_UNUSED(result);
		GFx::TextField* pgfxTextField = textField->GetTextField();
		pgfxTextField->SetIMEDisabledFlag(!isEnabled);
//##protect##"class_::TextFieldEx::setIMEEnabled()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc2<Classes::TextFieldEx, Classes::TextFieldEx::mid_appendHtml, Value, Instances::TextField*, const ASString&> TFunc_Classes_TextFieldEx_appendHtml;
typedef ThunkFunc2<Classes::TextFieldEx, Classes::TextFieldEx::mid_setVerticalAlign, Value, Instances::TextField*, const ASString&> TFunc_Classes_TextFieldEx_setVerticalAlign;
typedef ThunkFunc1<Classes::TextFieldEx, Classes::TextFieldEx::mid_getVerticalAlign, ASString, Instances::TextField*> TFunc_Classes_TextFieldEx_getVerticalAlign;
typedef ThunkFunc2<Classes::TextFieldEx, Classes::TextFieldEx::mid_setTextAutoSize, Value, Instances::TextField*, const ASString&> TFunc_Classes_TextFieldEx_setTextAutoSize;
typedef ThunkFunc1<Classes::TextFieldEx, Classes::TextFieldEx::mid_getTextAutoSize, ASString, Instances::TextField*> TFunc_Classes_TextFieldEx_getTextAutoSize;
typedef ThunkFunc2<Classes::TextFieldEx, Classes::TextFieldEx::mid_setIMEEnabled, Value, Instances::TextField*, bool> TFunc_Classes_TextFieldEx_setIMEEnabled;

template <> const TFunc_Classes_TextFieldEx_appendHtml::TMethod TFunc_Classes_TextFieldEx_appendHtml::Method = &Classes::TextFieldEx::appendHtml;
template <> const TFunc_Classes_TextFieldEx_setVerticalAlign::TMethod TFunc_Classes_TextFieldEx_setVerticalAlign::Method = &Classes::TextFieldEx::setVerticalAlign;
template <> const TFunc_Classes_TextFieldEx_getVerticalAlign::TMethod TFunc_Classes_TextFieldEx_getVerticalAlign::Method = &Classes::TextFieldEx::getVerticalAlign;
template <> const TFunc_Classes_TextFieldEx_setTextAutoSize::TMethod TFunc_Classes_TextFieldEx_setTextAutoSize::Method = &Classes::TextFieldEx::setTextAutoSize;
template <> const TFunc_Classes_TextFieldEx_getTextAutoSize::TMethod TFunc_Classes_TextFieldEx_getTextAutoSize::Method = &Classes::TextFieldEx::getTextAutoSize;
template <> const TFunc_Classes_TextFieldEx_setIMEEnabled::TMethod TFunc_Classes_TextFieldEx_setIMEEnabled::Method = &Classes::TextFieldEx::setIMEEnabled;

namespace ClassTraits
{
    const MemberInfo TextFieldEx::mi[TextFieldEx::MemberInfoNum] = {
        {"VALIGN_NONE", OFFSETOF(Classes::TextFieldEx, VALIGN_NONE), SlotInfo::BT_ConstChar, 1},
        {"VALIGN_TOP", OFFSETOF(Classes::TextFieldEx, VALIGN_TOP), SlotInfo::BT_ConstChar, 1},
        {"VALIGN_CENTER", OFFSETOF(Classes::TextFieldEx, VALIGN_CENTER), SlotInfo::BT_ConstChar, 1},
        {"VALIGN_BOTTOM", OFFSETOF(Classes::TextFieldEx, VALIGN_BOTTOM), SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_NONE", OFFSETOF(Classes::TextFieldEx, TEXTAUTOSZ_NONE), SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_SHRINK", OFFSETOF(Classes::TextFieldEx, TEXTAUTOSZ_SHRINK), SlotInfo::BT_ConstChar, 1},
        {"TEXTAUTOSZ_FIT", OFFSETOF(Classes::TextFieldEx, TEXTAUTOSZ_FIT), SlotInfo::BT_ConstChar, 1},
    };

    const ThunkInfo TextFieldEx::ti[TextFieldEx::ThunkInfoNum] = {
        {TFunc_Classes_TextFieldEx_appendHtml::Func, NULL, "appendHtml", NULL, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_setVerticalAlign::Func, NULL, "setVerticalAlign", NULL, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_getVerticalAlign::Func, &StringCI, "getVerticalAlign", NULL, CT_Method, 1, 1},
        {TFunc_Classes_TextFieldEx_setTextAutoSize::Func, NULL, "setTextAutoSize", NULL, CT_Method, 2, 2},
        {TFunc_Classes_TextFieldEx_getTextAutoSize::Func, &StringCI, "getTextAutoSize", NULL, CT_Method, 1, 1},
        {TFunc_Classes_TextFieldEx_setIMEEnabled::Func, NULL, "setIMEEnabled", NULL, CT_Method, 2, 2},
    };
    TextFieldEx::TextFieldEx(VM& vm)
    : Traits(vm, TextFieldExCI)
    {
//##protect##"ClassTraits::TextFieldEx::TextFieldEx()"
//##protect##"ClassTraits::TextFieldEx::TextFieldEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, TextFieldExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::TextFieldEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextFieldEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextFieldEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextFieldExCI = {
    ClassInfo::CompileTime,
    "TextFieldEx", "scaleform.gfx", &ObjectCI,
    ClassTraits::TextFieldEx::MakeClassTraits,
    ClassTraits::TextFieldEx::ThunkInfoNum,
    ClassTraits::TextFieldEx::MemberInfoNum,
    0,
    0,
    ClassTraits::TextFieldEx::ti,
    ClassTraits::TextFieldEx::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

