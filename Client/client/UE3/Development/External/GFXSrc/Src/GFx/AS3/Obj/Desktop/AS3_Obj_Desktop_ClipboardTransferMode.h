//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_ClipboardTransferMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_ClipboardTransferMode_H
#define INC_AS3_Obj_Desktop_ClipboardTransferMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ClipboardTransferMode;
}

namespace InstanceTraits
{
    class ClipboardTransferMode;
}

namespace Classes
{
    class ClipboardTransferMode;
}
    
namespace ClassTraits
{
    class ClipboardTransferMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ClipboardTransferMode"; }
#endif
    public:
        typedef Classes::ClipboardTransferMode ClassType;

    public:
        ClipboardTransferMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ClipboardTransferMode : public Class
    {
        friend class ClassTraits::ClipboardTransferMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ClipboardTransferMode"; }
#endif
    public:
        typedef ClipboardTransferMode SelfType;
        typedef ClipboardTransferMode ClassType;
        
    private:
        ClipboardTransferMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CLONE_ONLY() const { return CLONE_ONLY; }
        const char* get_CLONE_PREFERRED() const { return CLONE_PREFERRED; }
        const char* get_ORIGINAL_ONLY() const { return ORIGINAL_ONLY; }
        const char* get_ORIGINAL_PREFERRED() const { return ORIGINAL_PREFERRED; }


    protected:
        // AS3 API members.
        const char* CLONE_ONLY;
        const char* CLONE_PREFERRED;
        const char* ORIGINAL_ONLY;
        const char* ORIGINAL_PREFERRED;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

