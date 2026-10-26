//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageAlign.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_StageAlign_H
#define INC_AS3_Obj_Display_StageAlign_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StageAlign;
}

namespace InstanceTraits
{
    class StageAlign;
}

namespace Classes
{
    class StageAlign;
}
    
namespace ClassTraits
{
    class StageAlign : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageAlign"; }
#endif
    public:
        typedef Classes::StageAlign ClassType;

    public:
        StageAlign(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StageAlign : public Class
    {
        friend class ClassTraits::StageAlign;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageAlign"; }
#endif
    public:
        typedef StageAlign SelfType;
        typedef StageAlign ClassType;
        
    private:
        StageAlign(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BOTTOM() const { return BOTTOM; }
        const char* get_BOTTOM_LEFT() const { return BOTTOM_LEFT; }
        const char* get_BOTTOM_RIGHT() const { return BOTTOM_RIGHT; }
        const char* get_LEFT() const { return LEFT; }
        const char* get_RIGHT() const { return RIGHT; }
        const char* get_TOP() const { return TOP; }
        const char* get_TOP_LEFT() const { return TOP_LEFT; }
        const char* get_TOP_RIGHT() const { return TOP_RIGHT; }


    protected:
        // AS3 API members.
        const char* BOTTOM;
        const char* BOTTOM_LEFT;
        const char* BOTTOM_RIGHT;
        const char* LEFT;
        const char* RIGHT;
        const char* TOP;
        const char* TOP_LEFT;
        const char* TOP_RIGHT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

