//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_IMEEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_IMEEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
#include "GFx/IME/GFx_IMEManager.h"
#include "AS3_Obj_Gfx_IMECandidateListStyle.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    IMEEx::IMEEx(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::IMEEx::IMEEx()"
//##protect##"class_::IMEEx::IMEEx()"
    }
    void IMEEx::getIMECandidateListStyle(Value& result)
    {
//##protect##"class_::IMEEx::getIMECandidateListStyle()"
#ifndef SF_NO_IME_SUPPORT		
		GFx::IMECandidateListStyle st; 

		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   
	
		if (pmovieImpl)
		{
			pmovieImpl->GetIMECandidateListStyle(&st);
		
			SPtr<AS3::Instances::IMECandidateListStyle> pobj;
			Class* candListStyleVal = GetVM().GetClass("scaleform.gfx.IMECandidateListStyle");
			if ( asvm.ConstructInstance(pobj, candListStyleVal, 0))
			{
				if (st.HasTextColor())
				{
					UInt32 c = (st.GetTextColor() & 0xFFFFFFu);
					pobj->set_textColor(c);
				}
				if (st.HasBackgroundColor())
				{
					UInt32 c = (st.GetBackgroundColor() & 0xFFFFFFu);
					pobj->set_backgroundColor(c);
				}
				if (st.HasIndexBackgroundColor())
				{
					UInt32 c = (st.GetIndexBackgroundColor() & 0xFFFFFFu);
					pobj->set_indexBackgroundColor(c);
				}
				if (st.HasSelectedTextColor())
				{
					UInt32 c = (st.GetSelectedTextColor() & 0xFFFFFFu);
					pobj->set_selectedTextColor(c);
				}
				if (st.HasSelectedBackgroundColor())
				{
					UInt32 c = (st.GetSelectedBackgroundColor() & 0xFFFFFFu);
					pobj->set_selectedBackgroundColor(c);
				}
				if (st.HasSelectedIndexBackgroundColor())
				{
					UInt32 c = (st.GetSelectedIndexBackgroundColor() & 0xFFFFFFu);
					pobj->set_selectedIndexBackgroundColor(c);
				}
				if (st.HasFontSize())
				{
					UInt32 c = st.GetFontSize();
					pobj->set_fontSize(c); 

				}
				// Reading Window Styles

				if (st.HasReadingWindowTextColor())
				{
					UInt32 c = st.GetReadingWindowTextColor();
					pobj->set_readingWindowTextColor(c);
				}

				if (st.HasReadingWindowBackgroundColor())
				{
					UInt32 c = st.GetReadingWindowBackgroundColor();
					pobj->set_readinwWindowBackgroundColor(c); 
				}

				if (st.HasReadingWindowFontSize())
				{
					UInt32 c = st.GetReadingWindowFontSize();
					pobj->set_readingWindowFontSize(c);
				}
			}
			result = Value(pobj);
		}
#else
		SF_UNUSED(result);
#endif
//##protect##"class_::IMEEx::getIMECandidateListStyle()"
    }
    void IMEEx::setIMECandidateListStyle(Value& result, Instances::IMECandidateListStyle* style)
    {
//##protect##"class_::IMEEx::setIMECandidateListStyle()"
#ifndef SF_NO_IME_SUPPORT		
		GFx::IMECandidateListStyle st; 

		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   

		if (pmovieImpl)
		{
			int c;
			if ((c = style->get_textColor()) != -1)
			{
				st.SetTextColor(c);
			}
			if ((c = style->get_selectedTextColor()) != -1)
			{
				st.SetSelectedTextColor(c);
			}
			if ((c = style->get_selectedTextColor()) != -1)
			{
				st.SetSelectedTextColor(c);
			}
			if ((c = style->get_fontSize()) != -1)
			{
				st.SetFontSize(c);
			}
			if ((c = style->get_backgroundColor()) != -1)
			{
				st.SetBackgroundColor(c);
			}
			if ((c = style->get_selectedBackgroundColor()) != -1)
			{
				st.SetSelectedBackgroundColor(c);
			}
			if ((c = style->get_indexBackgroundColor()) != -1)
			{
				st.SetIndexBackgroundColor(c);
			}
			if ((c = style->get_selectedIndexBackgroundColor()) != -1)
			{
				st.SetSelectedIndexBackgroundColor(c);
			}
			if ((c = style->get_readingWindowTextColor()) != -1)
			{
				st.SetReadingWindowTextColor(c);
			}
			if ((c = style->get_readingWindowBackgroundColor()) != -1)
			{
				st.SetReadingWindowBackgroundColor(c);
			}
			if ((c = style->get_readingWindowFontSize()) != -1)
			{
				st.SetReadingWindowFontSize(c);
			}
			pmovieImpl->SetIMECandidateListStyle(st);
		}
		result.SetUndefined();
#else
		SF_UNUSED2(result, style);
#endif
//##protect##"class_::IMEEx::setIMECandidateListStyle()"
    }
    void IMEEx::SendLangBarMessage(Value& result, Instances::Sprite* mc, const ASString& command, const ASString& message)
    {
//##protect##"class_::IMEEx::SendLangBarMessage()"
#ifndef SF_NO_IME_SUPPORT
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   
		if (pmovieImpl)
		{
			GFx::IMEManagerBase* pimeManager = pmovieImpl->GetIMEManager();
			if (pimeManager)
			{

				GFx::DisplayObject *pdispObj = mc->pDispObj;
				pimeManager->SendLangBarMessage(pdispObj, command, message);
			}
		}
		result.SetUndefined();
#else
		SF_UNUSED4(result, mc, command, message);
#endif
//##protect##"class_::IMEEx::SendLangBarMessage()"
    }
    void IMEEx::GetOSVersion(ASString& result)
    {
//##protect##"class_::IMEEx::GetOSVersion()"
#ifndef SF_NO_IME_SUPPORT
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   
		if (pmovieImpl)
		{
			GFx::IMEManagerBase* pimeManager = pmovieImpl->GetIMEManager();
			if (pimeManager)
			{

				Scaleform::String version = pimeManager->GetWindowsVersion();
				result = version;
			}
		}
#else
		SF_UNUSED(result);
#endif
//##protect##"class_::IMEEx::GetOSVersion()"
    }
    void IMEEx::GetCompositionString(ASString& result)
    {
//##protect##"class_::IMEEx::GetCompositionString()"
#ifndef SF_NO_IME_SUPPORT
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl();   
		if (pmovieImpl)
		{
			GFx::IMEManagerBase* pimeManager = pmovieImpl->GetIMEManager();
			if (pimeManager)
			{
				const wchar_t* pcompString = pimeManager->GetCompositionString();
				Scaleform::String compString(pcompString);
				result = compString;
			}
		}
#else
		SF_UNUSED(result);
#endif
//##protect##"class_::IMEEx::GetCompositionString()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::IMEEx, Classes::IMEEx::mid_getIMECandidateListStyle, Value> TFunc_Classes_IMEEx_getIMECandidateListStyle;
typedef ThunkFunc1<Classes::IMEEx, Classes::IMEEx::mid_setIMECandidateListStyle, Value, Instances::IMECandidateListStyle*> TFunc_Classes_IMEEx_setIMECandidateListStyle;
typedef ThunkFunc3<Classes::IMEEx, Classes::IMEEx::mid_SendLangBarMessage, Value, Instances::Sprite*, const ASString&, const ASString&> TFunc_Classes_IMEEx_SendLangBarMessage;
typedef ThunkFunc0<Classes::IMEEx, Classes::IMEEx::mid_GetOSVersion, ASString> TFunc_Classes_IMEEx_GetOSVersion;
typedef ThunkFunc0<Classes::IMEEx, Classes::IMEEx::mid_GetCompositionString, ASString> TFunc_Classes_IMEEx_GetCompositionString;

template <> const TFunc_Classes_IMEEx_getIMECandidateListStyle::TMethod TFunc_Classes_IMEEx_getIMECandidateListStyle::Method = &Classes::IMEEx::getIMECandidateListStyle;
template <> const TFunc_Classes_IMEEx_setIMECandidateListStyle::TMethod TFunc_Classes_IMEEx_setIMECandidateListStyle::Method = &Classes::IMEEx::setIMECandidateListStyle;
template <> const TFunc_Classes_IMEEx_SendLangBarMessage::TMethod TFunc_Classes_IMEEx_SendLangBarMessage::Method = &Classes::IMEEx::SendLangBarMessage;
template <> const TFunc_Classes_IMEEx_GetOSVersion::TMethod TFunc_Classes_IMEEx_GetOSVersion::Method = &Classes::IMEEx::GetOSVersion;
template <> const TFunc_Classes_IMEEx_GetCompositionString::TMethod TFunc_Classes_IMEEx_GetCompositionString::Method = &Classes::IMEEx::GetCompositionString;

namespace ClassTraits
{
    const ThunkInfo IMEEx::ti[IMEEx::ThunkInfoNum] = {
        {TFunc_Classes_IMEEx_getIMECandidateListStyle::Func, &IMECandidateListStyleCI, "getIMECandidateListStyle", NULL, CT_Method, 0, 0},
        {TFunc_Classes_IMEEx_setIMECandidateListStyle::Func, NULL, "setIMECandidateListStyle", NULL, CT_Method, 1, 1},
        {TFunc_Classes_IMEEx_SendLangBarMessage::Func, NULL, "SendLangBarMessage", NULL, CT_Method, 3, 3},
        {TFunc_Classes_IMEEx_GetOSVersion::Func, &StringCI, "GetOSVersion", NULL, CT_Method, 0, 0},
        {TFunc_Classes_IMEEx_GetCompositionString::Func, &StringCI, "GetCompositionString", NULL, CT_Method, 0, 0},
    };
    IMEEx::IMEEx(VM& vm)
    : Traits(vm, IMEExCI)
    {
//##protect##"ClassTraits::IMEEx::IMEEx()"
//##protect##"ClassTraits::IMEEx::IMEEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, IMEExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IMEEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IMEEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IMEEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMEExCI = {
    ClassInfo::CompileTime,
    "IMEEx", "scaleform.gfx", &EventDispatcherCI,
    ClassTraits::IMEEx::MakeClassTraits,
    ClassTraits::IMEEx::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::IMEEx::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

