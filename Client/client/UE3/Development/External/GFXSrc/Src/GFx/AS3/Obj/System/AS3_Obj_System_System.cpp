//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_System.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_System_System.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
    namespace Classes
    {
        class IME;
    }

    void escapeMultiByteInternal(VM& vm, ASString& result, const ASString& value)
    {
        bool useCodePage = false;

        const Multiname mn(vm, "flash.utils.System");
        const ClassTraits::Traits* ctr = vm.Resolve2ClassTraits(mn);
        if (ctr && ctr->IsValid())
        {
            const Class& cl = ctr->GetClass();
            const Classes::System& clSystem = static_cast<const Classes::System&>(cl);
            useCodePage = clSystem.get_useCodePage();
        }

        String escapedStr;
        if (useCodePage)
        {
            // If System.useCodePage is true, the escaped string is encoded in the system code page.
            ASUtils::Escape(value.ToCStr(), value.GetSize(), &escapedStr);
        }
        else
        {
            // If System.useCodePage is false, the escaped string is encoded in UTF-8
            ASUtils::AS3::Escape(value.ToCStr(), value.GetSize(), escapedStr);
        }
        result = vm.GetStringManager().CreateString(escapedStr.ToCStr(), escapedStr.GetSize());
    }
    void unescapeMultiByteInternal(VM& vm, ASString& result, const ASString& value)
    {
        bool useCodePage = false;

        const Multiname mn(vm, "flash.utils.System");
        const ClassTraits::Traits* ctr = vm.Resolve2ClassTraits(mn);
        if (ctr && ctr->IsValid())
        {
            const Class& cl = ctr->GetClass();
            const Classes::System& clSystem = static_cast<const Classes::System&>(cl);
            useCodePage = clSystem.get_useCodePage();
        }

        String unescapedStr;
        bool ok = true;
        if (useCodePage)
        {
            // If System.useCodePage is true, the escaped string is decoded from the system code page.
            ASUtils::Unescape(value.ToCStr(), value.GetSize(), &unescapedStr);
        }
        else
        {
            // If System.useCodePage is false, the escaped string is decoded from UTF-8.
            ok = ASUtils::AS3::Unescape(value.ToCStr(), value.GetSize(), unescapedStr);
        }

        if (ok)
            result = vm.GetStringManager().CreateString(unescapedStr.ToCStr(), unescapedStr.GetSize());
    }
//##protect##"methods"

namespace Classes
{
    System::System(ClassTraits::Traits& t)
    : Class(t)
    , useCodePage()
    {
//##protect##"class_::System::System()"
//##protect##"class_::System::System()"
    }
    void System::imeGet(Value& result)
    {
//##protect##"class_::System::imeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::System::imeGet()");
//##protect##"class_::System::imeGet()"
    }
    void System::totalMemoryGet(UInt32& result)
    {
//##protect##"class_::System::totalMemoryGet()"
        result = static_cast<UInt32>(Memory::pGlobalHeap->GetTotalFootprint());
//##protect##"class_::System::totalMemoryGet()"
    }
    void System::exit(Value& result, UInt32 code)
    {
//##protect##"class_::System::exit()"
        SF_UNUSED2(result, code);
        static_cast<ASVM&>(GetVM()).GetMovieImpl()->RequestExit();
//##protect##"class_::System::exit()"
    }
    void System::gc(Value& result)
    {
//##protect##"class_::System::gc()"
        SF_UNUSED1(result);
        GetVM().GetGC().ScheduleCollect();
//##protect##"class_::System::gc()"
    }
    void System::pause(Value& result)
    {
//##protect##"class_::System::pause()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::System::pause()");
//##protect##"class_::System::pause()"
    }
    void System::resume(Value& result)
    {
//##protect##"class_::System::resume()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("class_::System::resume()");
//##protect##"class_::System::resume()"
    }
    void System::setClipboard(Value& result, const ASString& string)
    {
//##protect##"class_::System::setClipboard()"
        SF_UNUSED2(result, string);
        WARN_NOT_IMPLEMENTED("class_::System::setClipboard()");
//##protect##"class_::System::setClipboard()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::System, Classes::System::mid_imeGet, Value> TFunc_Classes_System_imeGet;
typedef ThunkFunc0<Classes::System, Classes::System::mid_totalMemoryGet, UInt32> TFunc_Classes_System_totalMemoryGet;
typedef ThunkFunc1<Classes::System, Classes::System::mid_exit, Value, UInt32> TFunc_Classes_System_exit;
typedef ThunkFunc0<Classes::System, Classes::System::mid_gc, Value> TFunc_Classes_System_gc;
typedef ThunkFunc0<Classes::System, Classes::System::mid_pause, Value> TFunc_Classes_System_pause;
typedef ThunkFunc0<Classes::System, Classes::System::mid_resume, Value> TFunc_Classes_System_resume;
typedef ThunkFunc1<Classes::System, Classes::System::mid_setClipboard, Value, const ASString&> TFunc_Classes_System_setClipboard;

template <> const TFunc_Classes_System_imeGet::TMethod TFunc_Classes_System_imeGet::Method = &Classes::System::imeGet;
template <> const TFunc_Classes_System_totalMemoryGet::TMethod TFunc_Classes_System_totalMemoryGet::Method = &Classes::System::totalMemoryGet;
template <> const TFunc_Classes_System_exit::TMethod TFunc_Classes_System_exit::Method = &Classes::System::exit;
template <> const TFunc_Classes_System_gc::TMethod TFunc_Classes_System_gc::Method = &Classes::System::gc;
template <> const TFunc_Classes_System_pause::TMethod TFunc_Classes_System_pause::Method = &Classes::System::pause;
template <> const TFunc_Classes_System_resume::TMethod TFunc_Classes_System_resume::Method = &Classes::System::resume;
template <> const TFunc_Classes_System_setClipboard::TMethod TFunc_Classes_System_setClipboard::Method = &Classes::System::setClipboard;

namespace ClassTraits
{
    const MemberInfo System::mi[System::MemberInfoNum] = {
        {"useCodePage", OFFSETOF(Classes::System, useCodePage), SlotInfo::BT_Boolean, 0},
    };

    const ThunkInfo System::ti[System::ThunkInfoNum] = {
        {TFunc_Classes_System_imeGet::Func, &IMECI, "ime", NULL, CT_Get, 0, 0},
        {TFunc_Classes_System_totalMemoryGet::Func, &uintCI, "totalMemory", NULL, CT_Get, 0, 0},
        {TFunc_Classes_System_exit::Func, NULL, "exit", NULL, CT_Method, 1, 1},
        {TFunc_Classes_System_gc::Func, NULL, "gc", NULL, CT_Method, 0, 0},
        {TFunc_Classes_System_pause::Func, NULL, "pause", NULL, CT_Method, 0, 0},
        {TFunc_Classes_System_resume::Func, NULL, "resume", NULL, CT_Method, 0, 0},
        {TFunc_Classes_System_setClipboard::Func, NULL, "setClipboard", NULL, CT_Method, 1, 1},
    };
    System::System(VM& vm)
    : Traits(vm, SystemCI)
    {
//##protect##"ClassTraits::System::System()"
//##protect##"ClassTraits::System::System()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, SystemCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::System(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> System::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) System(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SystemCI = {
    ClassInfo::CompileTime,
    "System", "flash.system", &ObjectCI,
    ClassTraits::System::MakeClassTraits,
    ClassTraits::System::ThunkInfoNum,
    ClassTraits::System::MemberInfoNum,
    0,
    0,
    ClassTraits::System::ti,
    ClassTraits::System::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

