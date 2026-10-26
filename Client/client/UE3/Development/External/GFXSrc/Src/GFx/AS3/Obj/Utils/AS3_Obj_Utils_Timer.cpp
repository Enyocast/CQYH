//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Timer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_Timer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_IntervalTimer.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_currentCountGet, SInt32> TFunc_Instances_Timer_currentCountGet;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_delayGet, Value::Number> TFunc_Instances_Timer_delayGet;
typedef ThunkFunc1<Instances::Timer, Instances::Timer::mid_delaySet, Value, Value::Number> TFunc_Instances_Timer_delaySet;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_repeatCountGet, SInt32> TFunc_Instances_Timer_repeatCountGet;
typedef ThunkFunc1<Instances::Timer, Instances::Timer::mid_repeatCountSet, Value, SInt32> TFunc_Instances_Timer_repeatCountSet;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_runningGet, bool> TFunc_Instances_Timer_runningGet;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_reset, Value> TFunc_Instances_Timer_reset;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_start, Value> TFunc_Instances_Timer_start;
typedef ThunkFunc0<Instances::Timer, Instances::Timer::mid_stop, Value> TFunc_Instances_Timer_stop;

template <> const TFunc_Instances_Timer_currentCountGet::TMethod TFunc_Instances_Timer_currentCountGet::Method = &Instances::Timer::currentCountGet;
template <> const TFunc_Instances_Timer_delayGet::TMethod TFunc_Instances_Timer_delayGet::Method = &Instances::Timer::delayGet;
template <> const TFunc_Instances_Timer_delaySet::TMethod TFunc_Instances_Timer_delaySet::Method = &Instances::Timer::delaySet;
template <> const TFunc_Instances_Timer_repeatCountGet::TMethod TFunc_Instances_Timer_repeatCountGet::Method = &Instances::Timer::repeatCountGet;
template <> const TFunc_Instances_Timer_repeatCountSet::TMethod TFunc_Instances_Timer_repeatCountSet::Method = &Instances::Timer::repeatCountSet;
template <> const TFunc_Instances_Timer_runningGet::TMethod TFunc_Instances_Timer_runningGet::Method = &Instances::Timer::runningGet;
template <> const TFunc_Instances_Timer_reset::TMethod TFunc_Instances_Timer_reset::Method = &Instances::Timer::reset;
template <> const TFunc_Instances_Timer_start::TMethod TFunc_Instances_Timer_start::Method = &Instances::Timer::start;
template <> const TFunc_Instances_Timer_stop::TMethod TFunc_Instances_Timer_stop::Method = &Instances::Timer::stop;

namespace Instances
{
    Timer::Timer(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::Timer::Timer()$data"
    , RepeatCount(0), CurrentCount(0), Delay(0), pCoreTimer(NULL)
//##protect##"instance::Timer::Timer()$data"
    {
//##protect##"instance::Timer::Timer()$code"
//##protect##"instance::Timer::Timer()$code"
    }

    void Timer::currentCountGet(SInt32& result)
    {
//##protect##"instance::Timer::currentCountGet()"
        SF_UNUSED1(result);
        if (pCoreTimer)
            result = pCoreTimer->GetCurrentCount();
        else
            result = CurrentCount;
//##protect##"instance::Timer::currentCountGet()"
    }
    void Timer::delayGet(Value::Number& result)
    {
//##protect##"instance::Timer::delayGet()"
        SF_UNUSED1(result);
        result = Delay;
//##protect##"instance::Timer::delayGet()"
    }
    void Timer::delaySet(Value& result, Value::Number value)
    {
//##protect##"instance::Timer::delaySet()"
        SF_UNUSED2(result, value);
        Delay = value;
//##protect##"instance::Timer::delaySet()"
    }
    void Timer::repeatCountGet(SInt32& result)
    {
//##protect##"instance::Timer::repeatCountGet()"
        SF_UNUSED1(result);
        result = RepeatCount;
//##protect##"instance::Timer::repeatCountGet()"
    }
    void Timer::repeatCountSet(Value& result, SInt32 value)
    {
//##protect##"instance::Timer::repeatCountSet()"
        SF_UNUSED2(result, value);
        RepeatCount = value;
//##protect##"instance::Timer::repeatCountSet()"
    }
    void Timer::runningGet(bool& result)
    {
//##protect##"instance::Timer::runningGet()"
        SF_UNUSED1(result);
        if (pCoreTimer && pCoreTimer->IsActive())
            result = true;
        else
            result = false;
//##protect##"instance::Timer::runningGet()"
    }
    void Timer::reset(Value& result)
    {
//##protect##"instance::Timer::reset()"
        stop(result);
        CurrentCount = 0;
//##protect##"instance::Timer::reset()"
    }
    void Timer::start(Value& result)
    {
//##protect##"instance::Timer::start()"
        SF_UNUSED1(result);

        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        if (pCoreTimer)
        {
            if (pCoreTimer->IsActive())
                return; // already active? do nothing!
            CurrentCount = (SInt32)pCoreTimer->GetCurrentCount();
            pCoreTimer = NULL;
        }
        pCoreTimer = *SF_HEAP_NEW(GetVM().GetMemoryHeap()) 
            IntervalTimer(this, (unsigned)Delay, CurrentCount, RepeatCount);

        proot->AddIntervalTimer(pCoreTimer);
        pCoreTimer->Start(proot);

//##protect##"instance::Timer::start()"
    }
    void Timer::stop(Value& result)
    {
//##protect##"instance::Timer::stop()"
        SF_UNUSED1(result);
        if (pCoreTimer && pCoreTimer->IsActive())
        {
            MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
            proot->ClearIntervalTimer(int(pCoreTimer->GetId()));
        }
        pCoreTimer = NULL;
//##protect##"instance::Timer::stop()"
    }

//##protect##"instance$methods"
    void Timer::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc < 1)
        {
            return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("Timer::AS3Constructor") SF_DEBUG_ARG(1) SF_DEBUG_ARG(1) SF_DEBUG_ARG(argc)));
        }
        argv[0].Convert2Number(Delay).DoNotCheck();
        if (argc >= 2)
        {
            argv[1].Convert2Int32(RepeatCount).DoNotCheck();
        }
    }

    void Timer::ExecuteEvent()
    {
        SF_ASSERT(pCoreTimer);

        CurrentCount = (SInt32)pCoreTimer->GetCurrentCount();

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<TimerEvent> efe = CreateTimerEventObject(asvm.GetBuiltin(AS3Builtin_timer));
        efe->Target  = this;
        DispatchSingleEvent(efe, false);

        //!AB consider efe->IsDefaultPrevented() ?

        if (CurrentCount >= RepeatCount)
        {
            // dispatch TIMER_COMPLETE
            SPtr<TimerEvent> efe = CreateTimerEventObject(asvm.GetBuiltin(AS3Builtin_timerComplete));
            efe->Target  = this;
            DispatchSingleEvent(efe, false);
        }
    }

    SPtr<Instances::TimerEvent> Timer::CreateTimerEventObject(const ASString& type)
    {
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Instances::TimerEvent> evt;
        Value params[] = { Value(type), Value(false), Value(false) };
        asvm.ConstructInstance(evt, asvm.TimerEventClass, 3, params);
        SF_ASSERT(evt);
        return evt;
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Timer::ti[Timer::ThunkInfoNum] = {
        {TFunc_Instances_Timer_currentCountGet::Func, &int_CI, "currentCount", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Timer_delayGet::Func, &NumberCI, "delay", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Timer_delaySet::Func, NULL, "delay", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Timer_repeatCountGet::Func, &int_CI, "repeatCount", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Timer_repeatCountSet::Func, NULL, "repeatCount", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Timer_runningGet::Func, &BooleanCI, "running", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Timer_reset::Func, NULL, "reset", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Timer_start::Func, NULL, "start", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Timer_stop::Func, NULL, "stop", NULL, CT_Method, 0, 0},
    };

    Timer::Timer(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Timer::Timer()"
//##protect##"InstanceTraits::Timer::Timer()"
        SetMemSize(sizeof(Instances::Timer));

    }

    Pickable<Instances::Timer> Timer::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Timer>(new(t.Alloc()) Instances::Timer(t));
    }

    void Timer::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Timer::Timer(VM& vm)
    : Traits(vm, TimerCI)
    {
//##protect##"ClassTraits::Timer::Timer()"
//##protect##"ClassTraits::Timer::Timer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Timer(vm, TimerCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Timer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Timer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TimerCI = {
    ClassInfo::CompileTime,
    "Timer", "flash.utils", &EventDispatcherCI,
    ClassTraits::Timer::MakeClassTraits,
    0,
    0,
    InstanceTraits::Timer::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Timer::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

