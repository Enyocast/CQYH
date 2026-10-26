//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_Timer.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Utils_Timer_H
#define INC_AS3_Obj_Utils_Timer_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "../Events/AS3_Obj_Events_TimerEvent.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
    class IntervalTimer;
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Timer;
}

namespace InstanceTraits
{
    class Timer;
}

namespace Classes
{
    class Timer;
}

namespace Instances
{
    class Timer : public Instances::EventDispatcher
    {
        friend class InstanceTraits::Timer;
        
    public:
        typedef Timer SelfType;
        typedef Classes::Timer ClassType;
        typedef InstanceTraits::Timer TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Timer"; }
#endif
    protected:
        Timer(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        void AS3Constructor(unsigned argc, const Value* argv);
        SPtr<Instances::TimerEvent> CreateTimerEventObject(const ASString& type);
    public:
        void ExecuteEvent();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_currentCountGet, 
            mid_delayGet, 
            mid_delaySet, 
            mid_repeatCountGet, 
            mid_repeatCountSet, 
            mid_runningGet, 
            mid_reset, 
            mid_start, 
            mid_stop, 
        };
        void currentCountGet(SInt32& result);
        void delayGet(Value::Number& result);
        void delaySet(Value& result, Value::Number value);
        void repeatCountGet(SInt32& result);
        void repeatCountSet(Value& result, SInt32 value);
        void runningGet(bool& result);
        void reset(Value& result);
        void start(Value& result);
        void stop(Value& result);

//##protect##"instance$data"
        SInt32              RepeatCount;
        SInt32              CurrentCount;
        Value::Number       Delay;
        Ptr<IntervalTimer>  pCoreTimer;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Timer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Timer"; }
#endif
    public:
        Timer(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Timer> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 9 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Timer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Timer"; }
#endif
    public:
        typedef Classes::Timer ClassType;

    public:
        Timer(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

