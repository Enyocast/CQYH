//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_IME.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_IME.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
#include "GFx/IME/GFx_IMEManager.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    IME::IME(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::IME::IME()"
//##protect##"class_::IME::IME()"
    }
    void IME::conversionModeSet(Value& result, const ASString& value)
    {
//##protect##"class_::IME::conversionModeSet()"
#ifndef SF_NO_IME_SUPPORT		
		SF_UNUSED(result);
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl(); 
		Ptr<IMEManagerBase> pimeManager = pmovieImpl->GetIMEManager();
		UInt32 fdwConversion = 0;

		if(pimeManager)
		{
			if (!SFstrcmp(value.ToCStr(), "ALPHANUMERIC_FULL"))
			{
				fdwConversion = 0;
			}
			if (!SFstrcmp(value.ToCStr(), "ALPHANUMERIC_HALF"))
			{
				fdwConversion = 0x01;
			}
			if (!SFstrcmp(value.ToCStr(), "JAPANESE_HIRAGANA"))
			{
				fdwConversion = 0x04;
			}
			if (!SFstrcmp(value.ToCStr(), "JAPANESE_KATAKANA_FULL"))
			{
				fdwConversion = 0x08;
			}
			if (!SFstrcmp(value.ToCStr(), "JAPANESE_KATAKANA_HALF"))
			{
				fdwConversion = 0x016;
			}
			pimeManager->SetConversionMode(fdwConversion);
		}
#else
		SF_UNUSED2(result, value);
#endif
//##protect##"class_::IME::conversionModeSet()"
    }
    void IME::conversionModeGet(ASString& result)
    {
//##protect##"class_::IME::conversionModeGet()"
#ifndef SF_NO_IME_SUPPORT		
		// Try to get IME Manager.
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl(); 
		Ptr<IMEManagerBase> pimeManager = pmovieImpl->GetIMEManager();
		result = "UNKNOWN";

		if(pimeManager)
		{
			result = pimeManager->GetConversionMode();
		}
#else
		SF_UNUSED(result);
#endif
//##protect##"class_::IME::conversionModeGet()"
    }
    void IME::enabledGet(bool& result)
    {
//##protect##"class_::IME::enabledGet()"
#ifndef SF_NO_IME_SUPPORT
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl(); 
		Ptr<IMEManagerBase> pimeManager = pmovieImpl->GetIMEManager();
		if(pimeManager)
		{
			result = pimeManager->GetEnabled();
		}
#else
		SF_UNUSED(result);
#endif
//##protect##"class_::IME::enabledGet()"
    }
    void IME::enabledSet(Value& result, bool value)
    {
//##protect##"class_::IME::enabledSet()"
#ifndef SF_NO_IME_SUPPORT
		SF_UNUSED(result);
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		MovieImpl* pmovieImpl = asvm.GetMovieImpl(); 
		Ptr<IMEManagerBase> pimeManager = pmovieImpl->GetIMEManager();
		if(pimeManager)
		{
			pimeManager->SetEnabled(value);
		}
#else
		SF_UNUSED2(result, value);
#endif
//##protect##"class_::IME::enabledSet()"
    }
    void IME::doConversion(Value& result)
    {
//##protect##"class_::IME::doConversion()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::IME::doConversion()");
//##protect##"class_::IME::doConversion()"
    }
    void IME::setCompositionString(Value& result, const ASString& composition)
    {
//##protect##"class_::IME::setCompositionString()"
        SF_UNUSED2(result, composition);
        WARN_NOT_IMPLEMENTED("class_::IME::setCompositionString()");
//##protect##"class_::IME::setCompositionString()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::IME, Classes::IME::mid_conversionModeSet, Value, const ASString&> TFunc_Classes_IME_conversionModeSet;
typedef ThunkFunc0<Classes::IME, Classes::IME::mid_conversionModeGet, ASString> TFunc_Classes_IME_conversionModeGet;
typedef ThunkFunc0<Classes::IME, Classes::IME::mid_enabledGet, bool> TFunc_Classes_IME_enabledGet;
typedef ThunkFunc1<Classes::IME, Classes::IME::mid_enabledSet, Value, bool> TFunc_Classes_IME_enabledSet;
typedef ThunkFunc0<Classes::IME, Classes::IME::mid_doConversion, Value> TFunc_Classes_IME_doConversion;
typedef ThunkFunc1<Classes::IME, Classes::IME::mid_setCompositionString, Value, const ASString&> TFunc_Classes_IME_setCompositionString;

template <> const TFunc_Classes_IME_conversionModeSet::TMethod TFunc_Classes_IME_conversionModeSet::Method = &Classes::IME::conversionModeSet;
template <> const TFunc_Classes_IME_conversionModeGet::TMethod TFunc_Classes_IME_conversionModeGet::Method = &Classes::IME::conversionModeGet;
template <> const TFunc_Classes_IME_enabledGet::TMethod TFunc_Classes_IME_enabledGet::Method = &Classes::IME::enabledGet;
template <> const TFunc_Classes_IME_enabledSet::TMethod TFunc_Classes_IME_enabledSet::Method = &Classes::IME::enabledSet;
template <> const TFunc_Classes_IME_doConversion::TMethod TFunc_Classes_IME_doConversion::Method = &Classes::IME::doConversion;
template <> const TFunc_Classes_IME_setCompositionString::TMethod TFunc_Classes_IME_setCompositionString::Method = &Classes::IME::setCompositionString;

namespace ClassTraits
{
    const ThunkInfo IME::ti[IME::ThunkInfoNum] = {
        {TFunc_Classes_IME_conversionModeSet::Func, NULL, "conversionMode", NULL, CT_Set, 1, 1},
        {TFunc_Classes_IME_conversionModeGet::Func, &StringCI, "conversionMode", NULL, CT_Get, 0, 0},
        {TFunc_Classes_IME_enabledGet::Func, &BooleanCI, "enabled", NULL, CT_Get, 0, 0},
        {TFunc_Classes_IME_enabledSet::Func, NULL, "enabled", NULL, CT_Set, 1, 1},
        {TFunc_Classes_IME_doConversion::Func, NULL, "doConversion", NULL, CT_Method, 0, 0},
        {TFunc_Classes_IME_setCompositionString::Func, NULL, "setCompositionString", NULL, CT_Method, 1, 1},
    };
    IME::IME(VM& vm)
    : Traits(vm, IMECI)
    {
//##protect##"ClassTraits::IME::IME()"
//##protect##"ClassTraits::IME::IME()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, IMECI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::IME(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> IME::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) IME(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo IMECI = {
    ClassInfo::CompileTime,
    "IME", "flash.system", &EventDispatcherCI,
    ClassTraits::IME::MakeClassTraits,
    ClassTraits::IME::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::IME::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

