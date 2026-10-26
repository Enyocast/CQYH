//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageScaleMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_StageScaleMode_H
#define INC_AS3_Obj_Display_StageScaleMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StageScaleMode;
}

namespace InstanceTraits
{
    class StageScaleMode;
}

namespace Classes
{
    class StageScaleMode;
}
    
namespace ClassTraits
{
    class StageScaleMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageScaleMode"; }
#endif
    public:
        typedef Classes::StageScaleMode ClassType;

    public:
        StageScaleMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StageScaleMode : public Class
    {
        friend class ClassTraits::StageScaleMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageScaleMode"; }
#endif
    public:
        typedef StageScaleMode SelfType;
        typedef StageScaleMode ClassType;
        
    private:
        StageScaleMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_EXACT_FIT() const { return EXACT_FIT; }
        const char* get_NO_BORDER() const { return NO_BORDER; }
        const char* get_NO_SCALE() const { return NO_SCALE; }
        const char* get_SHOW_ALL() const { return SHOW_ALL; }


    protected:
        // AS3 API members.
        const char* EXACT_FIT;
        const char* NO_BORDER;
        const char* NO_SCALE;
        const char* SHOW_ALL;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

