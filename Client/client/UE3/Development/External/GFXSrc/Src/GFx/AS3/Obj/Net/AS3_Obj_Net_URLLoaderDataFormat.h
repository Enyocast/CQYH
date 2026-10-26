//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLLoaderDataFormat.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLLoaderDataFormat_H
#define INC_AS3_Obj_Net_URLLoaderDataFormat_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef BINARY
#undef BINARY
#endif

#ifdef TEXT
#undef TEXT
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLLoaderDataFormat;
}

namespace InstanceTraits
{
    class URLLoaderDataFormat;
}

namespace Classes
{
    class URLLoaderDataFormat;
}
    
namespace ClassTraits
{
    class URLLoaderDataFormat : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLLoaderDataFormat"; }
#endif
    public:
        typedef Classes::URLLoaderDataFormat ClassType;

    public:
        URLLoaderDataFormat(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class URLLoaderDataFormat : public Class
    {
        friend class ClassTraits::URLLoaderDataFormat;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::URLLoaderDataFormat"; }
#endif
    public:
        typedef URLLoaderDataFormat SelfType;
        typedef URLLoaderDataFormat ClassType;
        
    private:
        URLLoaderDataFormat(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BINARY() const { return BINARY; }
        const char* get_TEXT() const { return TEXT; }
        const char* get_VARIABLES() const { return VARIABLES; }


    protected:
        // AS3 API members.
        const char* BINARY;
        const char* TEXT;
        const char* VARIABLES;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

