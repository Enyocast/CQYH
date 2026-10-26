//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_HTTPStatusEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_HTTPStatusEvent_H
#define INC_AS3_Obj_Events_HTTPStatusEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class HTTPStatusEvent;
}

namespace InstanceTraits
{
    class HTTPStatusEvent;
}

namespace Classes
{
    class HTTPStatusEvent;
}
    
namespace ClassTraits
{
    class HTTPStatusEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::HTTPStatusEvent"; }
#endif
    public:
        typedef Classes::HTTPStatusEvent ClassType;

    public:
        HTTPStatusEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class HTTPStatusEvent : public Class
    {
        friend class ClassTraits::HTTPStatusEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::HTTPStatusEvent"; }
#endif
    public:
        typedef HTTPStatusEvent SelfType;
        typedef HTTPStatusEvent ClassType;
        
    private:
        HTTPStatusEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_HTTP_RESPONSE_STATUS() const { return HTTP_RESPONSE_STATUS; }
        const char* get_HTTP_STATUS() const { return HTTP_STATUS; }


    protected:
        // AS3 API members.
        const char* HTTP_RESPONSE_STATUS;
        const char* HTTP_STATUS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

