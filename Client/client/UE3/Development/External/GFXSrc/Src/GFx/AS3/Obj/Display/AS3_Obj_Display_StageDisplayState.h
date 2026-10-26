//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageDisplayState.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_StageDisplayState_H
#define INC_AS3_Obj_Display_StageDisplayState_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StageDisplayState;
}

namespace InstanceTraits
{
    class StageDisplayState;
}

namespace Classes
{
    class StageDisplayState;
}
    
namespace ClassTraits
{
    class StageDisplayState : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageDisplayState"; }
#endif
    public:
        typedef Classes::StageDisplayState ClassType;

    public:
        StageDisplayState(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StageDisplayState : public Class
    {
        friend class ClassTraits::StageDisplayState;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageDisplayState"; }
#endif
    public:
        typedef StageDisplayState SelfType;
        typedef StageDisplayState ClassType;
        
    private:
        StageDisplayState(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_FULL_SCREEN() const { return FULL_SCREEN; }
        const char* get_FULL_SCREEN_INTERACTIVE() const { return FULL_SCREEN_INTERACTIVE; }
        const char* get_NORMAL() const { return NORMAL; }


    protected:
        // AS3 API members.
        const char* FULL_SCREEN;
        const char* FULL_SCREEN_INTERACTIVE;
        const char* NORMAL;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

