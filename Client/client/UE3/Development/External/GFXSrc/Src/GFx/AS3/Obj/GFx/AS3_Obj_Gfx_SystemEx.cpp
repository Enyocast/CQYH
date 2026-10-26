//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_SystemEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_SystemEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    SystemEx::SystemEx(ClassTraits::Traits& t)
    : Class(t)
    , REPORT_SHORT_FILENAMES(0x1)
    , REPORT_NO_CIRCULAR_REFERENCES(0x2)
    , REPORT_SUPPRESS_OVERALL_STATS(0x4)
    , REPORT_ONLY_ANON_OBJ_ADDRESSES(0x8)
    {
//##protect##"class_::SystemEx::SystemEx()"
//##protect##"class_::SystemEx::SystemEx()"
    }
    void SystemEx::actionVerboseSet(Value& result, bool verbose)
    {
//##protect##"class_::SystemEx::actionVerboseSet()"

        SF_UNUSED1(result);
        static_cast<ASVM&>(GetVM()).GetMovieImpl()->SetVerboseAction(verbose);

        FlashUI& ui = GetVM().GetUI();
        ui.SetNeedToCheckOpCode(verbose);
//##protect##"class_::SystemEx::actionVerboseSet()"
    }
    void SystemEx::actionVerboseGet(bool& result)
    {
//##protect##"class_::SystemEx::actionVerboseGet()"

        result = static_cast<ASVM&>(GetVM()).GetMovieImpl()->IsVerboseAction();

//##protect##"class_::SystemEx::actionVerboseGet()"
    }
    void SystemEx::setBackgroundAlpha(Value& result, Value::Number value)
    {
//##protect##"class_::SystemEx::setBackgroundAlpha()"

        SF_UNUSED1(result);
        static_cast<ASVM&>(GetVM()).GetMovieImpl()->SetBackgroundAlpha(static_cast<float>(value));

//##protect##"class_::SystemEx::setBackgroundAlpha()"
    }
    void SystemEx::getStackTrace(ASString& result)
    {
//##protect##"class_::SystemEx::getStackTrace()"

        GetVM().GetStackTraceASString(result);

//##protect##"class_::SystemEx::getStackTrace()"
    }
    void SystemEx::getCodeFileName(ASString& result)
    {
//##protect##"class_::SystemEx::getCodeFileName()"

        GetVM().GetCodeFileName(result);

//##protect##"class_::SystemEx::getCodeFileName()"
    }
    void SystemEx::getCodeFileNames(Value& result)
    {
//##protect##"class_::SystemEx::getCodeFileNames()"
        SF_UNUSED1(result);

        Scaleform::Array<SPtr<VMAbcFile> > srcArr;
        UPInt n = GetVM().GetAllLoadedAbcFiles(&srcArr);

        SPtr<Instances::Array> destArr = GetVM().MakeArray();

        for (UPInt i = 0; i < n; ++i)
        {
            const Scaleform::String& name = srcArr[i]->GetAbcFile().GetName();
            Value v(GetVM().GetStringManager().CreateString(name.ToCStr()));
            destArr->PushBack(v);
        }
        result = destArr;
        
//##protect##"class_::SystemEx::getCodeFileNames()"
    }
    void SystemEx::describeType(ASString& result, const Value& v)
    {
//##protect##"class_::SystemEx::describeType()"
        result = GetVM().describeTypeEx(v);
//##protect##"class_::SystemEx::describeType()"
    }
    void SystemEx::printObjectsReport(Value& result, bool runGarbageCollector, UInt32 reportFlags, const ASString& swfFilter)
    {
//##protect##"class_::SystemEx::printObjectsReport()"
        SF_UNUSED1(result);

        MovieImpl* pmovieImpl = static_cast<ASVM&>(GetVM()).GetMovieImpl();
        if (runGarbageCollector)
            pmovieImpl->ForceCollectGarbage();
        pmovieImpl->PrintObjectsReport(reportFlags, NULL, swfFilter.ToCStr());

//##protect##"class_::SystemEx::printObjectsReport()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::SystemEx, Classes::SystemEx::mid_actionVerboseSet, Value, bool> TFunc_Classes_SystemEx_actionVerboseSet;
typedef ThunkFunc0<Classes::SystemEx, Classes::SystemEx::mid_actionVerboseGet, bool> TFunc_Classes_SystemEx_actionVerboseGet;
typedef ThunkFunc1<Classes::SystemEx, Classes::SystemEx::mid_setBackgroundAlpha, Value, Value::Number> TFunc_Classes_SystemEx_setBackgroundAlpha;
typedef ThunkFunc0<Classes::SystemEx, Classes::SystemEx::mid_getStackTrace, ASString> TFunc_Classes_SystemEx_getStackTrace;
typedef ThunkFunc0<Classes::SystemEx, Classes::SystemEx::mid_getCodeFileName, ASString> TFunc_Classes_SystemEx_getCodeFileName;
typedef ThunkFunc0<Classes::SystemEx, Classes::SystemEx::mid_getCodeFileNames, Value> TFunc_Classes_SystemEx_getCodeFileNames;
typedef ThunkFunc1<Classes::SystemEx, Classes::SystemEx::mid_describeType, ASString, const Value&> TFunc_Classes_SystemEx_describeType;
typedef ThunkFunc3<Classes::SystemEx, Classes::SystemEx::mid_printObjectsReport, Value, bool, UInt32, const ASString&> TFunc_Classes_SystemEx_printObjectsReport;

template <> const TFunc_Classes_SystemEx_actionVerboseSet::TMethod TFunc_Classes_SystemEx_actionVerboseSet::Method = &Classes::SystemEx::actionVerboseSet;
template <> const TFunc_Classes_SystemEx_actionVerboseGet::TMethod TFunc_Classes_SystemEx_actionVerboseGet::Method = &Classes::SystemEx::actionVerboseGet;
template <> const TFunc_Classes_SystemEx_setBackgroundAlpha::TMethod TFunc_Classes_SystemEx_setBackgroundAlpha::Method = &Classes::SystemEx::setBackgroundAlpha;
template <> const TFunc_Classes_SystemEx_getStackTrace::TMethod TFunc_Classes_SystemEx_getStackTrace::Method = &Classes::SystemEx::getStackTrace;
template <> const TFunc_Classes_SystemEx_getCodeFileName::TMethod TFunc_Classes_SystemEx_getCodeFileName::Method = &Classes::SystemEx::getCodeFileName;
template <> const TFunc_Classes_SystemEx_getCodeFileNames::TMethod TFunc_Classes_SystemEx_getCodeFileNames::Method = &Classes::SystemEx::getCodeFileNames;
template <> const TFunc_Classes_SystemEx_describeType::TMethod TFunc_Classes_SystemEx_describeType::Method = &Classes::SystemEx::describeType;
template <> const TFunc_Classes_SystemEx_printObjectsReport::TMethod TFunc_Classes_SystemEx_printObjectsReport::Method = &Classes::SystemEx::printObjectsReport;

namespace ClassTraits
{
    const MemberInfo SystemEx::mi[SystemEx::MemberInfoNum] = {
        {"REPORT_SHORT_FILENAMES", OFFSETOF(Classes::SystemEx, REPORT_SHORT_FILENAMES), SlotInfo::BT_UInt, 1},
        {"REPORT_NO_CIRCULAR_REFERENCES", OFFSETOF(Classes::SystemEx, REPORT_NO_CIRCULAR_REFERENCES), SlotInfo::BT_UInt, 1},
        {"REPORT_SUPPRESS_OVERALL_STATS", OFFSETOF(Classes::SystemEx, REPORT_SUPPRESS_OVERALL_STATS), SlotInfo::BT_UInt, 1},
        {"REPORT_ONLY_ANON_OBJ_ADDRESSES", OFFSETOF(Classes::SystemEx, REPORT_ONLY_ANON_OBJ_ADDRESSES), SlotInfo::BT_UInt, 1},
    };

    const ThunkInfo SystemEx::ti[SystemEx::ThunkInfoNum] = {
        {TFunc_Classes_SystemEx_actionVerboseSet::Func, NULL, "actionVerbose", NULL, CT_Set, 1, 1},
        {TFunc_Classes_SystemEx_actionVerboseGet::Func, &BooleanCI, "actionVerbose", NULL, CT_Get, 0, 0},
        {TFunc_Classes_SystemEx_setBackgroundAlpha::Func, NULL, "setBackgroundAlpha", NULL, CT_Method, 1, 1},
        {TFunc_Classes_SystemEx_getStackTrace::Func, &StringCI, "getStackTrace", NULL, CT_Method, 0, 0},
        {TFunc_Classes_SystemEx_getCodeFileName::Func, &StringCI, "getCodeFileName", NULL, CT_Method, 0, 0},
        {TFunc_Classes_SystemEx_getCodeFileNames::Func, &ArrayCI, "getCodeFileNames", NULL, CT_Method, 0, 0},
        {TFunc_Classes_SystemEx_describeType::Func, &StringCI, "describeType", NULL, CT_Method, 1, 1},
        {TFunc_Classes_SystemEx_printObjectsReport::Func, NULL, "printObjectsReport", NULL, CT_Method, 0, 3},
    };
    SystemEx::SystemEx(VM& vm)
    : Traits(vm, SystemExCI)
    {
//##protect##"ClassTraits::SystemEx::SystemEx()"
//##protect##"ClassTraits::SystemEx::SystemEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SystemExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SystemEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SystemEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SystemEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SystemExCI = {
    ClassInfo::CompileTime,
    "SystemEx", "scaleform.gfx", &ObjectCI,
    ClassTraits::SystemEx::MakeClassTraits,
    ClassTraits::SystemEx::ThunkInfoNum,
    ClassTraits::SystemEx::MemberInfoNum,
    0,
    0,
    ClassTraits::SystemEx::ti,
    ClassTraits::SystemEx::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

