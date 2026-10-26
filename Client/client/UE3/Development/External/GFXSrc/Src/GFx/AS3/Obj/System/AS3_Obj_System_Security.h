//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_Security.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_Security_H
#define INC_AS3_Obj_System_Security_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Security;
}

namespace InstanceTraits
{
    class Security;
}

namespace Classes
{
    class Security;
}
    
namespace ClassTraits
{
    class Security : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Security"; }
#endif
    public:
        typedef Classes::Security ClassType;

    public:
        Security(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 5 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Security : public Class
    {
        friend class ClassTraits::Security;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Security"; }
#endif
    public:
        typedef Security SelfType;
        typedef Security ClassType;
        
    private:
        Security(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_APPLICATION() const { return APPLICATION; }
        const char* get_LOCAL_TRUSTED() const { return LOCAL_TRUSTED; }
        const char* get_LOCAL_WITH_FILE() const { return LOCAL_WITH_FILE; }
        const char* get_LOCAL_WITH_NETWORK() const { return LOCAL_WITH_NETWORK; }
        const char* get_REMOTE() const { return REMOTE; }


    protected:
        // AS3 API members.
        const char* APPLICATION;
        const char* LOCAL_TRUSTED;
        const char* LOCAL_WITH_FILE;
        const char* LOCAL_WITH_NETWORK;
        const char* REMOTE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

