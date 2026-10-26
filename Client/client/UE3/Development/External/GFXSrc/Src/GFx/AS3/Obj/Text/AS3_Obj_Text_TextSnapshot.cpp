//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextSnapshot.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_TextSnapshot.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
class TextSnapshotGlyphVisitor : public StaticTextSnapshotData::GlyphVisitor
{
public:
    TextSnapshotGlyphVisitor(VM* vm, Instances::Array* parr) : pVM(vm), pArray(parr) {}

    void OnVisit()
    {
        // Create new object
        SPtr<Instances::Object> pobj = pVM->MakeObject();

        StringManager& sm = pVM->GetStringManager();
        Value val;

        // Fill object
        val.SetUInt32((unsigned)GetRunIndex());
        pobj->AddDynamicSlotValuePair(sm.CreateString("indexInRun"), val);

        val.SetBool(IsSelected());
        pobj->AddDynamicSlotValuePair(sm.CreateConstString("selected"), val);

        pobj->AddDynamicSlotValuePair(sm.CreateString("font"), sm.CreateString(GetFontName()));

        val.SetNumber((float)GetColor().ToColor32());
        pobj->AddDynamicSlotValuePair(sm.CreateConstString("color"), val);

        val.SetNumber(GetHeight());
        pobj->AddDynamicSlotValuePair(sm.CreateConstString("height"), val);

        const Render::Matrix2F& mat = GetMatrix();
        val.SetNumber(TwipsToPixels(mat.Sx()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_a"), val);
        val.SetNumber(TwipsToPixels(mat.Shy()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_b"), val);
        val.SetNumber(TwipsToPixels(mat.Shx()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_c"), val);
        val.SetNumber(TwipsToPixels(mat.Sy()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_d"), val);
        val.SetNumber(TwipsToPixels(mat.Tx()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_tx"), val);
        val.SetNumber(TwipsToPixels(mat.Ty()));
        pobj->AddDynamicSlotValuePair(sm.CreateString("matrix_ty"), val);

        const Render::PointF& bl = GetCorners().BottomLeft();
        const Render::PointF& br = GetCorners().BottomRight();
        const Render::PointF& tl = GetCorners().TopLeft();
        const Render::PointF& tr = GetCorners().TopRight();
        val.SetNumber(TwipsToPixels(bl.x));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner0x"), val);
        val.SetNumber(TwipsToPixels(bl.y));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner0y"), val);
        val.SetNumber(TwipsToPixels(br.x));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner1x"), val);
        val.SetNumber(TwipsToPixels(br.y));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner1y"), val);
        val.SetNumber(TwipsToPixels(tr.x));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner2x"), val);
        val.SetNumber(TwipsToPixels(tr.y));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner2y"), val);
        val.SetNumber(TwipsToPixels(tl.x));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner3x"), val);
        val.SetNumber(TwipsToPixels(tl.y));
        pobj->AddDynamicSlotValuePair(sm.CreateString("corner3y"), val);

        // Add to array
        pArray->PushBack(Value(pobj));
    }

    private:
        VM* pVM;
        Instances::Array* pArray;
	};
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::TextSnapshot, Instances::TextSnapshot::mid_hitTestTextNearPos, 2, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    UInt32 GetMethodDefArg<Instances::TextSnapshot, Instances::TextSnapshot::mid_setSelectColor, 0, UInt32>(AS3::StringManager&)
    {
        return 0xFFFF00;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::TextSnapshot, Instances::TextSnapshot::mid_charCountGet, SInt32> TFunc_Instances_TextSnapshot_charCountGet;
typedef ThunkFunc3<Instances::TextSnapshot, Instances::TextSnapshot::mid_findText, SInt32, SInt32, const ASString&, bool> TFunc_Instances_TextSnapshot_findText;
typedef ThunkFunc2<Instances::TextSnapshot, Instances::TextSnapshot::mid_getSelected, bool, SInt32, SInt32> TFunc_Instances_TextSnapshot_getSelected;
typedef ThunkFunc1<Instances::TextSnapshot, Instances::TextSnapshot::mid_getSelectedText, ASString, bool> TFunc_Instances_TextSnapshot_getSelectedText;
typedef ThunkFunc3<Instances::TextSnapshot, Instances::TextSnapshot::mid_getText, ASString, SInt32, SInt32, bool> TFunc_Instances_TextSnapshot_getText;
typedef ThunkFunc2<Instances::TextSnapshot, Instances::TextSnapshot::mid_getTextRunInfo, Value, SInt32, SInt32> TFunc_Instances_TextSnapshot_getTextRunInfo;
typedef ThunkFunc3<Instances::TextSnapshot, Instances::TextSnapshot::mid_hitTestTextNearPos, Value::Number, Value::Number, Value::Number, Value::Number> TFunc_Instances_TextSnapshot_hitTestTextNearPos;
typedef ThunkFunc1<Instances::TextSnapshot, Instances::TextSnapshot::mid_setSelectColor, Value, UInt32> TFunc_Instances_TextSnapshot_setSelectColor;
typedef ThunkFunc3<Instances::TextSnapshot, Instances::TextSnapshot::mid_setSelected, Value, SInt32, SInt32, bool> TFunc_Instances_TextSnapshot_setSelected;

template <> const TFunc_Instances_TextSnapshot_charCountGet::TMethod TFunc_Instances_TextSnapshot_charCountGet::Method = &Instances::TextSnapshot::charCountGet;
template <> const TFunc_Instances_TextSnapshot_findText::TMethod TFunc_Instances_TextSnapshot_findText::Method = &Instances::TextSnapshot::findText;
template <> const TFunc_Instances_TextSnapshot_getSelected::TMethod TFunc_Instances_TextSnapshot_getSelected::Method = &Instances::TextSnapshot::getSelected;
template <> const TFunc_Instances_TextSnapshot_getSelectedText::TMethod TFunc_Instances_TextSnapshot_getSelectedText::Method = &Instances::TextSnapshot::getSelectedText;
template <> const TFunc_Instances_TextSnapshot_getText::TMethod TFunc_Instances_TextSnapshot_getText::Method = &Instances::TextSnapshot::getText;
template <> const TFunc_Instances_TextSnapshot_getTextRunInfo::TMethod TFunc_Instances_TextSnapshot_getTextRunInfo::Method = &Instances::TextSnapshot::getTextRunInfo;
template <> const TFunc_Instances_TextSnapshot_hitTestTextNearPos::TMethod TFunc_Instances_TextSnapshot_hitTestTextNearPos::Method = &Instances::TextSnapshot::hitTestTextNearPos;
template <> const TFunc_Instances_TextSnapshot_setSelectColor::TMethod TFunc_Instances_TextSnapshot_setSelectColor::Method = &Instances::TextSnapshot::setSelectColor;
template <> const TFunc_Instances_TextSnapshot_setSelected::TMethod TFunc_Instances_TextSnapshot_setSelected::Method = &Instances::TextSnapshot::setSelected;

namespace Instances
{
    TextSnapshot::TextSnapshot(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::TextSnapshot::TextSnapshot()$data"
//##protect##"instance::TextSnapshot::TextSnapshot()$data"
    {
//##protect##"instance::TextSnapshot::TextSnapshot()$code"
//##protect##"instance::TextSnapshot::TextSnapshot()$code"
    }

    void TextSnapshot::charCountGet(SInt32& result)
    {
//##protect##"instance::TextSnapshot::charCountGet()"
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        result = static_cast<SInt32>(GetSnapshotData().GetCharCount());
#else
        result = 0;
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::charCountGet()"
    }
    void TextSnapshot::findText(SInt32& result, SInt32 beginIndex, const ASString& textToFind, bool caseSensitive)
    {
//##protect##"instance::TextSnapshot::findText()"
        SF_UNUSED3(beginIndex, textToFind, caseSensitive);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        String query(textToFind.ToCStr(), textToFind.GetSize());
        result = GetSnapshotData().FindText(beginIndex, query, caseSensitive);
#else
        result = 0;
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::findText()"
    }
    void TextSnapshot::getSelected(bool& result, SInt32 beginIndex, SInt32 endIndex)
    {
//##protect##"instance::TextSnapshot::getSelected()"
        SF_UNUSED2(beginIndex,endIndex);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        if (endIndex <= beginIndex)
            endIndex = beginIndex + 1;
        result = GetSnapshotData().IsSelected(beginIndex, endIndex);
#else
        result = false;
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::getSelected()"
    }
    void TextSnapshot::getSelectedText(ASString& result, bool includeLineEndings)
    {
//##protect##"instance::TextSnapshot::getSelectedText()"
        SF_UNUSED2(result, includeLineEndings);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        String selectedText = GetSnapshotData().GetSelectedText(includeLineEndings);
        result = GetVM().GetStringManager().CreateString(selectedText);
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::getSelectedText()"
    }
    void TextSnapshot::getText(ASString& result, SInt32 beginIndex, SInt32 endIndex, bool includeLineEndings)
    {
//##protect##"instance::TextSnapshot::getText()"
        SF_UNUSED4(result,beginIndex,endIndex,includeLineEndings);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        if (endIndex <= beginIndex)
            endIndex = beginIndex + 1;
        String subStr = GetSnapshotData().GetSubString(beginIndex, endIndex, includeLineEndings);
        result = GetVM().GetStringManager().CreateString(subStr);
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::getText()"
    }
    void TextSnapshot::getTextRunInfo(Value& result, SInt32 beginIndex, SInt32 endIndex)
    {
//##protect##"instance::TextSnapshot::getTextRunInfo()"
        SF_UNUSED3(result, beginIndex,endIndex);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        VM& vm = GetVM();
        SPtr<Instances::Array> parr = vm.MakeArray();
        TextSnapshotGlyphVisitor visitor(&vm, parr);
        GetSnapshotData().Visit(&visitor, beginIndex, endIndex);
        result = parr;
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::getTextRunInfo()"
    }
    void TextSnapshot::hitTestTextNearPos(Value::Number& result, Value::Number x, Value::Number y, Value::Number maxDistance)
    {
//##protect##"instance::TextSnapshot::hitTestTextNearPos()"
        SF_UNUSED4(result, x, y, maxDistance);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        int idx = GetSnapshotData().HitTestTextNearPos(
            float(PixelsToTwips(x)), float(PixelsToTwips(y)), float(PixelsToTwips(maxDistance)));
        result = Value::Number(idx);
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::hitTestTextNearPos()"
    }
    void TextSnapshot::setSelectColor(Value& result, UInt32 hexColor)
    {
//##protect##"instance::TextSnapshot::setSelectColor()"
        SF_UNUSED2(result, hexColor);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        Color color(hexColor);
        color.SetAlpha(255);
        GetSnapshotData().SetSelectColor(color);
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::setSelectColor()"
    }
    void TextSnapshot::setSelected(Value& result, SInt32 beginIndex, SInt32 endIndex, bool select)
    {
//##protect##"instance::TextSnapshot::setSelected()"
        SF_UNUSED4(result, beginIndex, endIndex, select);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        if (endIndex <= beginIndex)
            endIndex = beginIndex + 1;
        GetSnapshotData().SetSelected(beginIndex, endIndex, select);
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance::TextSnapshot::setSelected()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo TextSnapshot::ti[TextSnapshot::ThunkInfoNum] = {
        {TFunc_Instances_TextSnapshot_charCountGet::Func, &int_CI, "charCount", NULL, CT_Get, 0, 0},
        {TFunc_Instances_TextSnapshot_findText::Func, &int_CI, "findText", NULL, CT_Method, 3, 3},
        {TFunc_Instances_TextSnapshot_getSelected::Func, &BooleanCI, "getSelected", NULL, CT_Method, 2, 2},
        {TFunc_Instances_TextSnapshot_getSelectedText::Func, &StringCI, "getSelectedText", NULL, CT_Method, 0, 1},
        {TFunc_Instances_TextSnapshot_getText::Func, &StringCI, "getText", NULL, CT_Method, 2, 3},
        {TFunc_Instances_TextSnapshot_getTextRunInfo::Func, &ArrayCI, "getTextRunInfo", NULL, CT_Method, 2, 2},
        {TFunc_Instances_TextSnapshot_hitTestTextNearPos::Func, &NumberCI, "hitTestTextNearPos", NULL, CT_Method, 2, 3},
        {TFunc_Instances_TextSnapshot_setSelectColor::Func, NULL, "setSelectColor", NULL, CT_Method, 0, 1},
        {TFunc_Instances_TextSnapshot_setSelected::Func, NULL, "setSelected", NULL, CT_Method, 3, 3},
    };

    TextSnapshot::TextSnapshot(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::TextSnapshot::TextSnapshot()"
//##protect##"InstanceTraits::TextSnapshot::TextSnapshot()"
        SetMemSize(sizeof(Instances::TextSnapshot));

    }

    Pickable<Instances::TextSnapshot> TextSnapshot::MakeInstance(Traits& t)
    {
        return Pickable<Instances::TextSnapshot>(new(t.Alloc()) Instances::TextSnapshot(t));
    }

    void TextSnapshot::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    TextSnapshot::TextSnapshot(VM& vm)
    : Traits(vm, TextSnapshotCI)
    {
//##protect##"ClassTraits::TextSnapshot::TextSnapshot()"
//##protect##"ClassTraits::TextSnapshot::TextSnapshot()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::TextSnapshot(vm, TextSnapshotCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> TextSnapshot::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) TextSnapshot(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TextSnapshotCI = {
    ClassInfo::CompileTime,
    "TextSnapshot", "flash.text", &ObjectCI,
    ClassTraits::TextSnapshot::MakeClassTraits,
    0,
    0,
    InstanceTraits::TextSnapshot::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::TextSnapshot::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

