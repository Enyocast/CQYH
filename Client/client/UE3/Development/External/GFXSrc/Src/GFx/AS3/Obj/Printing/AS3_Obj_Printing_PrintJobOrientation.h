//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJobOrientation.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Printing_PrintJobOrientation_H
#define INC_AS3_Obj_Printing_PrintJobOrientation_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class PrintJobOrientation;
}

namespace InstanceTraits
{
    class PrintJobOrientation;
}

namespace Classes
{
    class PrintJobOrientation;
}
    
namespace ClassTraits
{
    class PrintJobOrientation : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::PrintJobOrientation"; }
#endif
    public:
        typedef Classes::PrintJobOrientation ClassType;

    public:
        PrintJobOrientation(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class PrintJobOrientation : public Class
    {
        friend class ClassTraits::PrintJobOrientation;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::PrintJobOrientation"; }
#endif
    public:
        typedef PrintJobOrientation SelfType;
        typedef PrintJobOrientation ClassType;
        
    private:
        PrintJobOrientation(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_LANDSCAPE() const { return LANDSCAPE; }
        const char* get_PORTRAIT() const { return PORTRAIT; }


    protected:
        // AS3 API members.
        const char* LANDSCAPE;
        const char* PORTRAIT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

