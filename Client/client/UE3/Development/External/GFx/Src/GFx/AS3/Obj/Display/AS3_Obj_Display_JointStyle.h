//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_JointStyle.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_JointStyle_H
#define INC_AS3_Obj_Display_JointStyle_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class JointStyle;
}

namespace InstanceTraits
{
    class JointStyle;
}

namespace Classes
{
    class JointStyle;
}
    
namespace ClassTraits
{
    class JointStyle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::JointStyle"; }
#endif
    public:
        typedef Classes::JointStyle ClassType;

    public:
        JointStyle(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class JointStyle : public Class
    {
        friend class ClassTraits::JointStyle;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::JointStyle"; }
#endif
    public:
        typedef JointStyle SelfType;
        typedef JointStyle ClassType;
        
    private:
        JointStyle(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BEVEL() const { return BEVEL; }
        const char* get_MITER() const { return MITER; }
        const char* get_ROUND() const { return ROUND; }


    protected:
        // AS3 API members.
        const char* BEVEL;
        const char* MITER;
        const char* ROUND;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

