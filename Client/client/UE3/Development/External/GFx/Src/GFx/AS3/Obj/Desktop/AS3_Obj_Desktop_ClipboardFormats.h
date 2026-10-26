//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardFormats.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_ClipboardFormats_H
#define INC_AS3_Obj_Desktop_ClipboardFormats_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ClipboardFormats;
}

namespace InstanceTraits
{
    class ClipboardFormats;
}

namespace Classes
{
    class ClipboardFormats;
}
    
namespace ClassTraits
{
    class ClipboardFormats : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ClipboardFormats"; }
#endif
    public:
        typedef Classes::ClipboardFormats ClassType;

    public:
        ClipboardFormats(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ClipboardFormats : public Class
    {
        friend class ClassTraits::ClipboardFormats;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ClipboardFormats"; }
#endif
    public:
        typedef ClipboardFormats SelfType;
        typedef ClipboardFormats ClassType;
        
    private:
        ClipboardFormats(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_HTML_FORMAT() const { return HTML_FORMAT; }
        const char* get_TEXT_FORMAT() const { return TEXT_FORMAT; }


    protected:
        // AS3 API members.
        const char* HTML_FORMAT;
        const char* TEXT_FORMAT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

