//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeDragEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_NativeDragEvent_H
#define INC_AS3_Obj_Events_NativeDragEvent_H

#include "AS3_Obj_Events_MouseEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class NativeDragOptions;
    class Clipboard;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeDragEvent;
}

namespace InstanceTraits
{
    class NativeDragEvent;
}

namespace Classes
{
    class NativeDragEvent;
}

namespace Instances
{
    class NativeDragEvent : public Instances::MouseEvent
    {
        friend class InstanceTraits::NativeDragEvent;
        
    public:
        typedef NativeDragEvent SelfType;
        typedef Classes::NativeDragEvent ClassType;
        typedef InstanceTraits::NativeDragEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NativeDragEvent"; }
#endif
    protected:
        NativeDragEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::NativeDragOptions* get_allowedActions() const { return allowedActions; }
        Instances::Clipboard* get_clipboard() const { return clipboard; }
        const ASString& get_dropAction() const { return dropAction; }


    protected:
        // AS3 API members.
        SPtr<Instances::NativeDragOptions> allowedActions;
        SPtr<Instances::Clipboard> clipboard;
        ASString dropAction;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NativeDragEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NativeDragEvent"; }
#endif
    public:
        NativeDragEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NativeDragEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class NativeDragEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeDragEvent"; }
#endif
    public:
        typedef Classes::NativeDragEvent ClassType;

    public:
        NativeDragEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 7 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NativeDragEvent : public Class
    {
        friend class ClassTraits::NativeDragEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NativeDragEvent"; }
#endif
    public:
        typedef NativeDragEvent SelfType;
        typedef NativeDragEvent ClassType;
        
    private:
        NativeDragEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_NATIVE_DRAG_COMPLETE() const { return NATIVE_DRAG_COMPLETE; }
        const char* get_NATIVE_DRAG_DROP() const { return NATIVE_DRAG_DROP; }
        const char* get_NATIVE_DRAG_ENTER() const { return NATIVE_DRAG_ENTER; }
        const char* get_NATIVE_DRAG_EXIT() const { return NATIVE_DRAG_EXIT; }
        const char* get_NATIVE_DRAG_OVER() const { return NATIVE_DRAG_OVER; }
        const char* get_NATIVE_DRAG_START() const { return NATIVE_DRAG_START; }
        const char* get_NATIVE_DRAG_UPDATE() const { return NATIVE_DRAG_UPDATE; }


    protected:
        // AS3 API members.
        const char* NATIVE_DRAG_COMPLETE;
        const char* NATIVE_DRAG_DROP;
        const char* NATIVE_DRAG_ENTER;
        const char* NATIVE_DRAG_EXIT;
        const char* NATIVE_DRAG_OVER;
        const char* NATIVE_DRAG_START;
        const char* NATIVE_DRAG_UPDATE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

