//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_SyncEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_SyncEvent_H
#define INC_AS3_Obj_Events_SyncEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SyncEvent;
}

namespace InstanceTraits
{
    class SyncEvent;
}

namespace Classes
{
    class SyncEvent;
}
    
namespace ClassTraits
{
    class SyncEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SyncEvent"; }
#endif
    public:
        typedef Classes::SyncEvent ClassType;

    public:
        SyncEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SyncEvent : public Class
    {
        friend class ClassTraits::SyncEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SyncEvent"; }
#endif
    public:
        typedef SyncEvent SelfType;
        typedef SyncEvent ClassType;
        
    private:
        SyncEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_SYNC() const { return SYNC; }


    protected:
        // AS3 API members.
        const char* SYNC;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

