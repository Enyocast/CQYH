//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_System.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_System_H
#define INC_AS3_Obj_System_System_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class System;
}

namespace InstanceTraits
{
    class System;
}

namespace Classes
{
    class System;
}
    
namespace ClassTraits
{
    class System : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::System"; }
#endif
    public:
        typedef Classes::System ClassType;

    public:
        System(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 7 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class System : public Class
    {
        friend class ClassTraits::System;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::System"; }
#endif
    public:
        typedef System SelfType;
        typedef System ClassType;
        
    private:
        System(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        bool get_useCodePage() const { return useCodePage; }

        // AS3 API methods.
        enum MethodID {
            mid_imeGet, 
            mid_totalMemoryGet, 
            mid_exit, 
            mid_gc, 
            mid_pause, 
            mid_resume, 
            mid_setClipboard, 
        };
        void imeGet(Value& result);
        void totalMemoryGet(UInt32& result);
        void exit(Value& result, UInt32 code);
        void gc(Value& result);
        void pause(Value& result);
        void resume(Value& result);
        void setClipboard(Value& result, const ASString& string);

    protected:
        // AS3 API members.
        bool useCodePage;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

