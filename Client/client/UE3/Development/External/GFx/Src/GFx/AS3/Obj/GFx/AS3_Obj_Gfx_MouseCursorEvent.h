//##protect##"disclaimer"
/**********************************************************************

Filename    :   .h
Content     :   
Created     :   Jul, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_MouseCursorEvent_H
#define INC_AS3_Obj_Gfx_MouseCursorEvent_H

#include "../Events/AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MouseCursorEvent;
}

namespace InstanceTraits
{
    class MouseCursorEvent;
}

namespace Classes
{
    class MouseCursorEvent;
}

namespace Instances
{
    class MouseCursorEvent : public Instances::Event
    {
        friend class InstanceTraits::MouseCursorEvent;
        
    public:
        typedef MouseCursorEvent SelfType;
        typedef Classes::MouseCursorEvent ClassType;
        typedef InstanceTraits::MouseCursorEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::MouseCursorEvent"; }
#endif
    protected:
        MouseCursorEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void SetControllerIdx(UInt32 mi)  { mouseIdx = mi; }
        void SetCursor(const ASString& c) { cursor = c; }
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_cursor() const { return cursor; }
        UInt32 get_mouseIdx() const { return mouseIdx; }


    protected:
        // AS3 API members.
        ASString cursor;
        UInt32 mouseIdx;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class MouseCursorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::MouseCursorEvent"; }
#endif
    public:
        MouseCursorEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::MouseCursorEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class MouseCursorEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MouseCursorEvent"; }
#endif
    public:
        typedef Classes::MouseCursorEvent ClassType;

    public:
        MouseCursorEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class MouseCursorEvent : public Class
    {
        friend class ClassTraits::MouseCursorEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::MouseCursorEvent"; }
#endif
    public:
        typedef MouseCursorEvent SelfType;
        typedef MouseCursorEvent ClassType;
        
    private:
        MouseCursorEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CURSOR_CHANGE() const { return CURSOR_CHANGE; }


    protected:
        // AS3 API members.
        const char* CURSOR_CHANGE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

