//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_LineScaleMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_LineScaleMode_H
#define INC_AS3_Obj_Display_LineScaleMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class LineScaleMode;
}

namespace InstanceTraits
{
    class LineScaleMode;
}

namespace Classes
{
    class LineScaleMode;
}
    
namespace ClassTraits
{
    class LineScaleMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::LineScaleMode"; }
#endif
    public:
        typedef Classes::LineScaleMode ClassType;

    public:
        LineScaleMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class LineScaleMode : public Class
    {
        friend class ClassTraits::LineScaleMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::LineScaleMode"; }
#endif
    public:
        typedef LineScaleMode SelfType;
        typedef LineScaleMode ClassType;
        
    private:
        LineScaleMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_HORIZONTAL() const { return HORIZONTAL; }
        const char* get_NONE() const { return NONE; }
        const char* get_NORMAL() const { return NORMAL; }
        const char* get_VERTICAL() const { return VERTICAL; }


    protected:
        // AS3 API members.
        const char* HORIZONTAL;
        const char* NONE;
        const char* NORMAL;
        const char* VERTICAL;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

