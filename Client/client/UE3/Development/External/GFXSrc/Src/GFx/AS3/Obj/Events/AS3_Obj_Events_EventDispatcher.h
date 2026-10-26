//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_EventDispatcher.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_EventDispatcher_H
#define INC_AS3_Obj_Events_EventDispatcher_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_Input.h"
#include "Kernel/SF_ArrayStaticBuff.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Event;
    class MouseEvent;
    class KeyboardEvent;
    class FocusEvent;
    class TouchEvent;
    class GestureEvent;
    class DisplayObject;
    class ProgressEvent;
    class IOErrorEvent;
    class AppLifecycleEvent;
    class StageOrientationEvent;
    class NetStatusEvent;
    class GamePadAnalogEvent;
    class MouseCursorEvent;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class EventDispatcher;
}

namespace InstanceTraits
{
    class EventDispatcher;
}

namespace Classes
{
    class EventDispatcher;
}

namespace Instances
{
    class EventDispatcher : public Instances::Object
    {
        friend class InstanceTraits::EventDispatcher;
        
    public:
        typedef EventDispatcher SelfType;
        typedef Classes::EventDispatcher ClassType;
        typedef InstanceTraits::EventDispatcher TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::EventDispatcher"; }
#endif
    protected:
        EventDispatcher(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        struct Listener
        {
            unsigned    Priority;
            Value       mFunction;    

            Listener():Priority(0) {}
            Listener(unsigned p, const Value& v):Priority(p), mFunction(v) {}
            ~Listener() {}
        };
        typedef ArrayLH<Listener> ListenersArray;

        struct ListenersHash : ASStringHash<ListenersArray*>
        {
            ~ListenersHash()
            {
                for (Iterator it = Begin(); it != End(); ++it)
                {
                    delete it->Second;
                }
            }
            void         ForEachChild_GC(Collector* prcc, GcOp op, const VM& vm, const EventDispatcher& ed, bool useCapture) const;
        };

        struct EventDispatcherImpl : public NewOverrideBase<StatMV_ActionScript_Mem_EventDispatcherImpl>
        {
            ListenersHash   CaptureListeners;
            ListenersHash   Listeners;
            enum 
            {
                Flag_EnterFrame         = 0x1,
                Flag_Activate           = 0x2,
                Flag_Deactivate         = 0x4,
                Flag_Render             = 0x8,
                Flag_Resize				= 0x10,
                Flag_FrameConstructed   = 0x20,
                Flag_ExitFrame          = 0x40
            };
            UInt16          Flags;
            UInt8           CaptureButtonHandlersCnt;
            UInt8           ButtonHandlersCnt;

            EventDispatcherImpl() : Flags(0), 
                CaptureButtonHandlersCnt(0), ButtonHandlersCnt(0) {}
        };
    protected:
        virtual void         ForEachChild_GC(Collector* prcc, GcOp op) const;

    public:
        ~EventDispatcher();
        
        typedef ArrayStaticBuff<SPtr<DisplayObject>, 32> EventFlowArrayType;

        SPtr<Instances::Event>          CreateEventObject(
            const ASString& type, bool bubbles = false, bool cancelable = false);
        SPtr<Instances::ProgressEvent>  CreateProgressEventObject(const ASString& type);
        SPtr<Instances::FocusEvent>     CreateFocusEventObject(const ASString& type,
            Instances::DisplayObject* relatedObj, unsigned controllerIdx, 
            bool shiftKey = false, unsigned keyCode = 0);
        SPtr<Instances::IOErrorEvent>   CreateIOErrorEventObject(const char* errText);
#ifdef GFX_ENABLE_MOBILE_APP_SUPPORT
        SPtr<Instances::AppLifecycleEvent> CreateAppLifecycleEventObject(
            const ASString& type, bool bubbles, bool cancelable, const ASString& event);
        SPtr<Instances::StageOrientationEvent> CreateStageOrientationEventObject(
            const ASString& type, bool bubbles, bool cancelable, const ASString& beforeOr, const ASString& afterOr);
#endif
        SPtr<Instances::NetStatusEvent> CreateNetStatusEvent(const ASString& code, const ASString& level);
        SPtr<Instances::MouseCursorEvent> CreateMouseCursorEventObject(
            const ASString& cursor, unsigned controllerIdx);

        // return false, if default action is prevented; true, otherwise
        bool Dispatch(const GFx::EventId& evtId, GFx::DisplayObject* dispObject);
        // return false, if default action is prevented; true, otherwise
        bool Dispatch(Instances::Event* evtObj, GFx::DisplayObject* dispObject);
        // return false, if default action is prevented; true, otherwise.
        // If dispObject is specified (can be NULL) and exception is thrown then
        // "ExecutionAborted" flag is set for it.
        bool DispatchToTarget(const ASString& type, Instances::Object* target, bool useCapture,
                              GFx::DisplayObject* dispObject);

        bool MayHaveEnterFrameHandler() const;
        bool MayHaveFrameConstructedHandler() const;
        bool MayHaveExitFrameHandler() const;
        // Checks if 'this' has a listener for the specified event
        bool HasEventHandler(const ASString& type, bool useCapture) const;
        bool HasButtonHandlers() const;

        bool MayHaveActivateHandler() const;
        bool MayHaveDeactivateHandler() const;
        bool MayHaveRenderHandler() const;

        // Checks if 'this' OR ANY OF ITS PARENTS (in the case of display object) has the event
        bool WillTrigger(const ASString& type, bool useCapture) const;

        // removes all listeners which functions belong to the specified moviedefimpl
        void RemoveListenersForMovieDef(MovieDefImpl*);
    protected:
        void RemoveListenersForMovieDef(MovieDefImpl* defimpl, ListenersHash& hash);
        void DoDispatchEvent(Event* evt, GFx::DisplayObject* dispObject);
        void CaptureEventFlow(GFx::DisplayObject* dispObject, 
            EventFlowArrayType& evtFlowArray);
        // returns false if propagation was stopped
        bool ExecuteCapturePhase(
            Instances::Event* evtObj, EventFlowArrayType& evtFlowArray);
        // returns false if propagation was stopped
        bool ExecuteBubblePhase(
            Instances::Event* evtObj, EventFlowArrayType& evtFlowArray);
        // returns false if exception was thrown during the execution of the event.
        // Use evtObj->IsPropagationStopped() to determine if propagation was stopped
        bool DispatchSingleEvent(Instances::Event* evtObj, bool useCapture);
        void OnRemoveEventListener(const ASString& evtType, bool useCapture, UPInt listenersArrSize);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_addEventListener, 
            mid_dispatchEvent, 
            mid_hasEventListener, 
            mid_removeEventListener, 
            mid_willTrigger, 
        };
        void addEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture, SInt32 priority, bool useWeakReference);
        void dispatchEvent(bool& result, Instances::Event* event);
        void hasEventListener(bool& result, const ASString& type);
        void removeEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture);
        void willTrigger(bool& result, const ASString& type);

//##protect##"instance$data"
        // We need an explicit reference to VM because there is no way to get
        // it via regular call GetVM() or GetVMSafe() inside of
        // ForEachChild_GC(). (Traits may be deleted at this time)
        AS3::VM&                        VMRef;
        AutoPtr<EventDispatcherImpl>    pImpl;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class EventDispatcher : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::EventDispatcher"; }
#endif
    public:
        EventDispatcher(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::EventDispatcher> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 10 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class EventDispatcher : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::EventDispatcher"; }
#endif
    public:
        typedef Classes::EventDispatcher ClassType;

    public:
        EventDispatcher(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class EventDispatcher : public Class
    {
        friend class ClassTraits::EventDispatcher;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::EventDispatcher"; }
#endif
    public:
        typedef EventDispatcher SelfType;
        typedef EventDispatcher ClassType;
        
    private:
        EventDispatcher(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
    public:
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

        void CacheEventTraits();

        SPtr<Instances::Event>           CreateEventObject(const ASString& type, bool bubbles = false, bool cancelable = false);
        SPtr<Instances::MouseEvent>      CreateMouseEventObject(
            const GFx::EventId& evtId, const ASString& type, Instances::Object* target);
        SPtr<Instances::KeyboardEvent>   CreateKeyboardEventObject(
            const GFx::EventId& evtId, const ASString& type, Instances::Object* target);
        SPtr<Instances::ProgressEvent>   CreateProgressEventObject(const ASString& type);
        SPtr<Instances::FocusEvent>      CreateFocusEventObject(const ASString& type, 
            Instances::DisplayObject* relatedObj, unsigned controllerIdx, bool shiftKey = false, unsigned keyCode = 0);
        SPtr<Instances::IOErrorEvent>    CreateIOErrorEventObject(const char* errText);
#ifdef GFX_ENABLE_ANALOG_GAMEPAD
        SPtr<Instances::GamePadAnalogEvent> CreateGamePadAnalogEventObject(
            const GFx::EventId& evtId, const ASString& type, Instances::Object* target);
#endif
#ifdef GFX_MULTITOUCH_SUPPORT_ENABLE
        SPtr<Instances::TouchEvent>      CreateTouchEventObject(
            const GFx::EventId& evtId, const ASString& type, Instances::Object* target);
        SPtr<Instances::GestureEvent>    CreateGestureEventObject(
            const GFx::EventId& evtId, Instances::Object* target);
#endif
        SPtr<Instances::NetStatusEvent>  CreateNetStatusEvent(const ASString& code, const ASString& level);
        SPtr<Instances::MouseCursorEvent> CreateMouseCursorEventObject(
            const ASString& cursor, unsigned controllerIdx);

#if defined(GFX_ENABLE_MOBILE_APP_SUPPORT)
        SPtr<Instances::StageOrientationEvent> CreateStageOrientationEventObject(
            const ASString& type, bool bubbles, bool cancelable, const ASString& beforeOr, const ASString& afterOr);
        SPtr<Instances::AppLifecycleEvent> CreateAppLifecycleEventObject(
            const ASString& type, bool bubbles, bool cancelable, const ASString& event);
#endif
//##protect##"class_$methods"

//##protect##"class_$data"
        SPtr<InstanceTraits::Traits> EventTraits;
        SPtr<InstanceTraits::Traits> MouseEventTraits;
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

