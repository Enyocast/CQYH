//##protect##"disclaimer"
/**********************************************************************

Filename    :   .h
Content     :   
Created     :   Jul, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_GamePad_H
#define INC_AS3_Obj_Gfx_GamePad_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class GamePad;
}

namespace InstanceTraits
{
    class GamePad;
}

namespace Classes
{
    class GamePad;
}
    
namespace ClassTraits
{
    class GamePad : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GamePad"; }
#endif
    public:
        typedef Classes::GamePad ClassType;

    public:
        GamePad(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 29 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class GamePad : public Class
    {
        friend class ClassTraits::GamePad;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::GamePad"; }
#endif
    public:
        typedef GamePad SelfType;
        typedef GamePad ClassType;
        
    private:
        GamePad(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const Value& get_PAD_NONE() const { return PAD_NONE; }
        const Value& get_PAD_BACK() const { return PAD_BACK; }
        const Value& get_PAD_START() const { return PAD_START; }
        const Value& get_PAD_A() const { return PAD_A; }
        const Value& get_PAD_B() const { return PAD_B; }
        const Value& get_PAD_X() const { return PAD_X; }
        const Value& get_PAD_Y() const { return PAD_Y; }
        const Value& get_PAD_R1() const { return PAD_R1; }
        const Value& get_PAD_L1() const { return PAD_L1; }
        const Value& get_PAD_R2() const { return PAD_R2; }
        const Value& get_PAD_L2() const { return PAD_L2; }
        const Value& get_PAD_UP() const { return PAD_UP; }
        const Value& get_PAD_DOWN() const { return PAD_DOWN; }
        const Value& get_PAD_RIGHT() const { return PAD_RIGHT; }
        const Value& get_PAD_LEFT() const { return PAD_LEFT; }
        const Value& get_PAD_PLUS() const { return PAD_PLUS; }
        const Value& get_PAD_MINUS() const { return PAD_MINUS; }
        const Value& get_PAD_1() const { return PAD_1; }
        const Value& get_PAD_2() const { return PAD_2; }
        const Value& get_PAD_H() const { return PAD_H; }
        const Value& get_PAD_C() const { return PAD_C; }
        const Value& get_PAD_Z() const { return PAD_Z; }
        const Value& get_PAD_O() const { return PAD_O; }
        const Value& get_PAD_T() const { return PAD_T; }
        const Value& get_PAD_S() const { return PAD_S; }
        const Value& get_PAD_SELECT() const { return PAD_SELECT; }
        const Value& get_PAD_HOME() const { return PAD_HOME; }
        const Value& get_PAD_RT() const { return PAD_RT; }
        const Value& get_PAD_LT() const { return PAD_LT; }

        // AS3 API methods.
        enum MethodID {
            mid_supportsAnalogEvents, 
        };
        void supportsAnalogEvents(bool& result);

    protected:
        // AS3 API members.
        Value PAD_NONE;
        Value PAD_BACK;
        Value PAD_START;
        Value PAD_A;
        Value PAD_B;
        Value PAD_X;
        Value PAD_Y;
        Value PAD_R1;
        Value PAD_L1;
        Value PAD_R2;
        Value PAD_L2;
        Value PAD_UP;
        Value PAD_DOWN;
        Value PAD_RIGHT;
        Value PAD_LEFT;
        Value PAD_PLUS;
        Value PAD_MINUS;
        Value PAD_1;
        Value PAD_2;
        Value PAD_H;
        Value PAD_C;
        Value PAD_Z;
        Value PAD_O;
        Value PAD_T;
        Value PAD_S;
        Value PAD_SELECT;
        Value PAD_HOME;
        Value PAD_RT;
        Value PAD_LT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

