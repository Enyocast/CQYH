//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_DataEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_DataEvent_H
#define INC_AS3_Obj_Events_DataEvent_H

#include "AS3_Obj_Events_TextEvent.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DataEvent;
}

namespace InstanceTraits
{
    class DataEvent;
}

namespace Classes
{
    class DataEvent;
}
    
namespace ClassTraits
{
    class DataEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DataEvent"; }
#endif
    public:
        typedef Classes::DataEvent ClassType;

    public:
        DataEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class DataEvent : public Class
    {
        friend class ClassTraits::DataEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::DataEvent"; }
#endif
    public:
        typedef DataEvent SelfType;
        typedef DataEvent ClassType;
        
    private:
        DataEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DATA() const { return DATA; }
        const char* get_UPLOAD_COMPLETE_DATA() const { return UPLOAD_COMPLETE_DATA; }


    protected:
        // AS3 API members.
        const char* DATA;
        const char* UPLOAD_COMPLETE_DATA;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

