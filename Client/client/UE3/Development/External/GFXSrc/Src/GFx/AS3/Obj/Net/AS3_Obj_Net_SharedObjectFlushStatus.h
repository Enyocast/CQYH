//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_SharedObjectFlushStatus.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_SharedObjectFlushStatus_H
#define INC_AS3_Obj_Net_SharedObjectFlushStatus_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SharedObjectFlushStatus;
}

namespace InstanceTraits
{
    class SharedObjectFlushStatus;
}

namespace Classes
{
    class SharedObjectFlushStatus;
}
    
namespace ClassTraits
{
    class SharedObjectFlushStatus : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SharedObjectFlushStatus"; }
#endif
    public:
        typedef Classes::SharedObjectFlushStatus ClassType;

    public:
        SharedObjectFlushStatus(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SharedObjectFlushStatus : public Class
    {
        friend class ClassTraits::SharedObjectFlushStatus;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SharedObjectFlushStatus"; }
#endif
    public:
        typedef SharedObjectFlushStatus SelfType;
        typedef SharedObjectFlushStatus ClassType;
        
    private:
        SharedObjectFlushStatus(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_FLUSHED() const { return FLUSHED; }
        const char* get_PENDING() const { return PENDING; }


    protected:
        // AS3 API members.
        const char* FLUSHED;
        const char* PENDING;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

