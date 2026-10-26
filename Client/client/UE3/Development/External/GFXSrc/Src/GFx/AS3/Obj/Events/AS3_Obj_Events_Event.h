//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_Event.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_Event_H
#define INC_AS3_Obj_Events_Event_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Event;
}

namespace InstanceTraits
{
    class Event;
}

namespace Classes
{
    class Event;
}

namespace Instances
{
    class Event : public Instances::Object
    {
        friend class InstanceTraits::Event;
        
    public:
        typedef Event SelfType;
        typedef Classes::Event ClassType;
        typedef InstanceTraits::Event TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Event"; }
#endif
    protected:
        Event(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        void AS3Constructor(unsigned argc, const Value* argv);
        virtual const char*     GetEventName() const { return "Event"; }
        virtual AS3::Object*    GetEventClass() const;
    public:
        bool IsPropagationStopped() const    { return PropagationStopped || ImmPropagationStopped; }
        bool IsImmPropagationStopped() const { return ImmPropagationStopped; }
        bool IsDefaultPrevented() const      { return DefaultPrevented; }

        virtual SPtr<Instances::Event> Clone() const;
        void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bubblesGet, 
            mid_cancelableGet, 
            mid_currentTargetGet, 
            mid_eventPhaseGet, 
            mid_targetGet, 
            mid_typeGet, 
            mid_clone, 
            mid_formatToString, 
            mid_isDefaultPrevented, 
            mid_preventDefault, 
            mid_stopImmediatePropagation, 
            mid_stopPropagation, 
            mid_toString, 
        };
        void bubblesGet(bool& result);
        void cancelableGet(bool& result);
        void currentTargetGet(Value& result);
        void eventPhaseGet(UInt32& result);
        void targetGet(Value& result);
        void typeGet(ASString& result);
        void clone(Value& result);
        void formatToString(Value& result, unsigned argc, const Value* const argv);
        void isDefaultPrevented(bool& result);
        void preventDefault(Value& result);
        void stopImmediatePropagation(Value& result);
        void stopPropagation(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
    public:
        ASString        Type;
        SPtr<Object>    CurrentTarget;
        SPtr<Object>    Target;
        enum
        {
            Phase_Capture = 1,
            Phase_Target  = 2,
            Phase_Bubble  = 3
        };
        unsigned        Phase;
        bool            Bubbles             :1;
        bool            Cancelable          :1;
        bool            DefaultPrevented    :1;
        bool            PropagationStopped  :1;
        bool            ImmPropagationStopped  :1;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Event : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Event"; }
#endif
    public:
        Event(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Event> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 13 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Event : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Event"; }
#endif
    public:
        typedef Classes::Event ClassType;

    public:
        Event(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 38 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Event : public Class
    {
        friend class ClassTraits::Event;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Event"; }
#endif
    public:
        typedef Event SelfType;
        typedef Event ClassType;
        
    private:
        Event(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ACTIVATE() const { return ACTIVATE; }
        const char* get_ADDED() const { return ADDED; }
        const char* get_ADDED_TO_STAGE() const { return ADDED_TO_STAGE; }
        const char* get_CANCEL() const { return CANCEL; }
        const char* get_CHANGE() const { return CHANGE; }
        const char* get_CLOSE() const { return CLOSE; }
        const char* get_CLOSING() const { return CLOSING; }
        const char* get_COMPLETE() const { return COMPLETE; }
        const char* get_CONNECT() const { return CONNECT; }
        const char* get_DEACTIVATE() const { return DEACTIVATE; }
        const char* get_DISPLAYING() const { return DISPLAYING; }
        const char* get_ENTER_FRAME() const { return ENTER_FRAME; }
        const char* get_EXITING() const { return EXITING; }
        const char* get_EXIT_FRAME() const { return EXIT_FRAME; }
        const char* get_FRAME_CONSTRUCTED() const { return FRAME_CONSTRUCTED; }
        const char* get_FULLSCREEN() const { return FULLSCREEN; }
        const char* get_HTML_BOUNDS_CHANGE() const { return HTML_BOUNDS_CHANGE; }
        const char* get_HTML_DOM_INITIALIZE() const { return HTML_DOM_INITIALIZE; }
        const char* get_HTML_RENDER() const { return HTML_RENDER; }
        const char* get_ID3() const { return ID3; }
        const char* get_INIT() const { return INIT; }
        const char* get_LOCATION_CHANGE() const { return LOCATION_CHANGE; }
        const char* get_MOUSE_LEAVE() const { return MOUSE_LEAVE; }
        const char* get_NETWORK_CHANGE() const { return NETWORK_CHANGE; }
        const char* get_OPEN() const { return OPEN; }
        const char* get_REMOVED() const { return REMOVED; }
        const char* get_REMOVED_FROM_STAGE() const { return REMOVED_FROM_STAGE; }
        const char* get_RENDER() const { return RENDER; }
        const char* get_RESIZE() const { return RESIZE; }
        const char* get_SCROLL() const { return SCROLL; }
        const char* get_SELECT() const { return SELECT; }
        const char* get_SOUND_COMPLETE() const { return SOUND_COMPLETE; }
        const char* get_TAB_CHILDREN_CHANGE() const { return TAB_CHILDREN_CHANGE; }
        const char* get_TAB_ENABLED_CHANGE() const { return TAB_ENABLED_CHANGE; }
        const char* get_TAB_INDEX_CHANGE() const { return TAB_INDEX_CHANGE; }
        const char* get_UNLOAD() const { return UNLOAD; }
        const char* get_USER_IDLE() const { return USER_IDLE; }
        const char* get_USER_PRESENT() const { return USER_PRESENT; }


    protected:
        // AS3 API members.
        const char* ACTIVATE;
        const char* ADDED;
        const char* ADDED_TO_STAGE;
        const char* CANCEL;
        const char* CHANGE;
        const char* CLOSE;
        const char* CLOSING;
        const char* COMPLETE;
        const char* CONNECT;
        const char* DEACTIVATE;
        const char* DISPLAYING;
        const char* ENTER_FRAME;
        const char* EXITING;
        const char* EXIT_FRAME;
        const char* FRAME_CONSTRUCTED;
        const char* FULLSCREEN;
        const char* HTML_BOUNDS_CHANGE;
        const char* HTML_DOM_INITIALIZE;
        const char* HTML_RENDER;
        const char* ID3;
        const char* INIT;
        const char* LOCATION_CHANGE;
        const char* MOUSE_LEAVE;
        const char* NETWORK_CHANGE;
        const char* OPEN;
        const char* REMOVED;
        const char* REMOVED_FROM_STAGE;
        const char* RENDER;
        const char* RESIZE;
        const char* SCROLL;
        const char* SELECT;
        const char* SOUND_COMPLETE;
        const char* TAB_CHILDREN_CHANGE;
        const char* TAB_ENABLED_CHANGE;
        const char* TAB_INDEX_CHANGE;
        const char* UNLOAD;
        const char* USER_IDLE;
        const char* USER_PRESENT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

