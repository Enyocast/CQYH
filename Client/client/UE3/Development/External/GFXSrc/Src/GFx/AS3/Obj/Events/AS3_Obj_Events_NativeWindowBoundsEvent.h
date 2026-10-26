//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_NativeWindowBoundsEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_NativeWindowBoundsEvent_H
#define INC_AS3_Obj_Events_NativeWindowBoundsEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeWindowBoundsEvent;
}

namespace InstanceTraits
{
    class NativeWindowBoundsEvent;
}

namespace Classes
{
    class NativeWindowBoundsEvent;
}
    
namespace ClassTraits
{
    class NativeWindowBoundsEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeWindowBoundsEvent"; }
#endif
    public:
        typedef Classes::NativeWindowBoundsEvent ClassType;

    public:
        NativeWindowBoundsEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class NativeWindowBoundsEvent : public Class
    {
        friend class ClassTraits::NativeWindowBoundsEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::NativeWindowBoundsEvent"; }
#endif
    public:
        typedef NativeWindowBoundsEvent SelfType;
        typedef NativeWindowBoundsEvent ClassType;
        
    private:
        NativeWindowBoundsEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_MOVE() const { return MOVE; }
        const char* get_MOVING() const { return MOVING; }
        const char* get_RESIZE() const { return RESIZE; }
        const char* get_RESIZING() const { return RESIZING; }


    protected:
        // AS3 API members.
        const char* MOVE;
        const char* MOVING;
        const char* RESIZE;
        const char* RESIZING;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

