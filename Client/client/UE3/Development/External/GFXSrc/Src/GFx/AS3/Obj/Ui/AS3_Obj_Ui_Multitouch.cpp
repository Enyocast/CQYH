//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_Multitouch.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_Multitouch.h"
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
    Multitouch::Multitouch(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Multitouch::Multitouch()"
//##protect##"class_::Multitouch::Multitouch()"
    }
    void Multitouch::inputModeGet(ASString& result)
    {
//##protect##"class_::Multitouch::inputModeGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        switch(asvm.GetMovieImpl()->GetMultitouchInputMode())
        {
        case MovieImpl::MTI_TouchPoint:
            result = asvm.GetStringManager().CreateConstString("touchPoint");
            break;
        case MovieImpl::MTI_Gesture:
            result = asvm.GetStringManager().CreateConstString("gesture");
            break;
        case MovieImpl::MTI_Mixed:
            result = asvm.GetStringManager().CreateConstString("mixed");
            break;
        default:
            result = asvm.GetStringManager().CreateConstString("none");
            break;
        }
//##protect##"class_::Multitouch::inputModeGet()"
    }
    void Multitouch::inputModeSet(Value& result, const ASString& value)
    {
//##protect##"class_::Multitouch::inputModeSet()"
        SF_UNUSED2(result, value);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        MovieImpl::MultitouchInputMode m = MovieImpl::MTI_None;
        if (value == "touchPoint")
            m = MovieImpl::MTI_TouchPoint;
        else if (value == "gesture")
            m = MovieImpl::MTI_Gesture;
        else if (value == "mixed")
            m = MovieImpl::MTI_Mixed;
        asvm.GetMovieImpl()->SetMultitouchInputMode(m);
//##protect##"class_::Multitouch::inputModeSet()"
    }
    void Multitouch::maxTouchPointsGet(SInt32& result)
    {
//##protect##"class_::Multitouch::maxTouchPointsGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        result = asvm.GetMovieImpl()->GetMaxTouchPoints();
//##protect##"class_::Multitouch::maxTouchPointsGet()"
    }
    void Multitouch::supportedGesturesGet(Value& result)
    {
//##protect##"class_::Multitouch::supportedGesturesGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        UInt32 m = asvm.GetMovieImpl()->GetSupportedGesturesMask();
        ASString str(asvm.GetStringManager().CreateEmptyString());
        if (m & MovieImpl::MTG_Pan)
            str += "pan"; //@TODO: should be a vector!
        result = str;
//##protect##"class_::Multitouch::supportedGesturesGet()"
    }
    void Multitouch::supportsGestureEventsGet(bool& result)
    {
//##protect##"class_::Multitouch::supportsGestureEventsGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        UInt32 m = asvm.GetMovieImpl()->GetSupportedGesturesMask();
        result = (m != 0);
//##protect##"class_::Multitouch::supportsGestureEventsGet()"
    }
    void Multitouch::supportsTouchEventsGet(bool& result)
    {
//##protect##"class_::Multitouch::supportsTouchEventsGet()"
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        UInt32 m = asvm.GetMovieImpl()->GetMaxTouchPoints();
        result = (m != 0 && (asvm.GetMovieImpl()->GetMultitouchInputMode() & MovieImpl::MTI_TouchPoint) != 0);
//##protect##"class_::Multitouch::supportsTouchEventsGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::Multitouch, Classes::Multitouch::mid_inputModeGet, ASString> TFunc_Classes_Multitouch_inputModeGet;
typedef ThunkFunc1<Classes::Multitouch, Classes::Multitouch::mid_inputModeSet, Value, const ASString&> TFunc_Classes_Multitouch_inputModeSet;
typedef ThunkFunc0<Classes::Multitouch, Classes::Multitouch::mid_maxTouchPointsGet, SInt32> TFunc_Classes_Multitouch_maxTouchPointsGet;
typedef ThunkFunc0<Classes::Multitouch, Classes::Multitouch::mid_supportedGesturesGet, Value> TFunc_Classes_Multitouch_supportedGesturesGet;
typedef ThunkFunc0<Classes::Multitouch, Classes::Multitouch::mid_supportsGestureEventsGet, bool> TFunc_Classes_Multitouch_supportsGestureEventsGet;
typedef ThunkFunc0<Classes::Multitouch, Classes::Multitouch::mid_supportsTouchEventsGet, bool> TFunc_Classes_Multitouch_supportsTouchEventsGet;

template <> const TFunc_Classes_Multitouch_inputModeGet::TMethod TFunc_Classes_Multitouch_inputModeGet::Method = &Classes::Multitouch::inputModeGet;
template <> const TFunc_Classes_Multitouch_inputModeSet::TMethod TFunc_Classes_Multitouch_inputModeSet::Method = &Classes::Multitouch::inputModeSet;
template <> const TFunc_Classes_Multitouch_maxTouchPointsGet::TMethod TFunc_Classes_Multitouch_maxTouchPointsGet::Method = &Classes::Multitouch::maxTouchPointsGet;
template <> const TFunc_Classes_Multitouch_supportedGesturesGet::TMethod TFunc_Classes_Multitouch_supportedGesturesGet::Method = &Classes::Multitouch::supportedGesturesGet;
template <> const TFunc_Classes_Multitouch_supportsGestureEventsGet::TMethod TFunc_Classes_Multitouch_supportsGestureEventsGet::Method = &Classes::Multitouch::supportsGestureEventsGet;
template <> const TFunc_Classes_Multitouch_supportsTouchEventsGet::TMethod TFunc_Classes_Multitouch_supportsTouchEventsGet::Method = &Classes::Multitouch::supportsTouchEventsGet;

namespace ClassTraits
{
    const ThunkInfo Multitouch::ti[Multitouch::ThunkInfoNum] = {
        {TFunc_Classes_Multitouch_inputModeGet::Func, &StringCI, "inputMode", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Multitouch_inputModeSet::Func, NULL, "inputMode", NULL, CT_Set, 1, 1},
        {TFunc_Classes_Multitouch_maxTouchPointsGet::Func, &int_CI, "maxTouchPoints", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Multitouch_supportedGesturesGet::Func, &ObjectCI, "supportedGestures", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Multitouch_supportsGestureEventsGet::Func, &BooleanCI, "supportsGestureEvents", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Multitouch_supportsTouchEventsGet::Func, &BooleanCI, "supportsTouchEvents", NULL, CT_Get, 0, 0},
    };
    Multitouch::Multitouch(VM& vm)
    : Traits(vm, MultitouchCI)
    {
//##protect##"ClassTraits::Multitouch::Multitouch()"
//##protect##"ClassTraits::Multitouch::Multitouch()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, MultitouchCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Multitouch(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Multitouch::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Multitouch(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MultitouchCI = {
    ClassInfo::CompileTime,
    "Multitouch", "flash.ui", &ObjectCI,
    ClassTraits::Multitouch::MakeClassTraits,
    ClassTraits::Multitouch::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::Multitouch::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

