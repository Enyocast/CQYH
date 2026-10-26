//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_OutputProgressEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_OutputProgressEvent_H
#define INC_AS3_Obj_Events_OutputProgressEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class OutputProgressEvent;
}

namespace InstanceTraits
{
    class OutputProgressEvent;
}

namespace Classes
{
    class OutputProgressEvent;
}
    
namespace ClassTraits
{
    class OutputProgressEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::OutputProgressEvent"; }
#endif
    public:
        typedef Classes::OutputProgressEvent ClassType;

    public:
        OutputProgressEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class OutputProgressEvent : public Class
    {
        friend class ClassTraits::OutputProgressEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::OutputProgressEvent"; }
#endif
    public:
        typedef OutputProgressEvent SelfType;
        typedef OutputProgressEvent ClassType;
        
    private:
        OutputProgressEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_OUTPUT_PROGRESS() const { return OUTPUT_PROGRESS; }


    protected:
        // AS3 API members.
        const char* OUTPUT_PROGRESS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

