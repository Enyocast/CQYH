//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_PixelSnapping.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_PixelSnapping_H
#define INC_AS3_Obj_Display_PixelSnapping_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class PixelSnapping;
}

namespace InstanceTraits
{
    class PixelSnapping;
}

namespace Classes
{
    class PixelSnapping;
}
    
namespace ClassTraits
{
    class PixelSnapping : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::PixelSnapping"; }
#endif
    public:
        typedef Classes::PixelSnapping ClassType;

    public:
        PixelSnapping(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class PixelSnapping : public Class
    {
        friend class ClassTraits::PixelSnapping;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::PixelSnapping"; }
#endif
    public:
        typedef PixelSnapping SelfType;
        typedef PixelSnapping ClassType;
        
    private:
        PixelSnapping(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ALWAYS() const { return ALWAYS; }
        const char* get_AUTO() const { return AUTO; }
        const char* get_NEVER() const { return NEVER; }


    protected:
        // AS3 API members.
        const char* ALWAYS;
        const char* AUTO;
        const char* NEVER;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

