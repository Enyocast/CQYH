//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Math.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Math_H
#define INC_AS3_Obj_Math_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Math;
}

namespace InstanceTraits
{
    class Math;
}

namespace Classes
{
    class Math;
}
    
namespace ClassTraits
{
    class Math : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Math"; }
#endif
    public:
        typedef Classes::Math ClassType;

    public:
        Math(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 18 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Math : public Class
    {
        friend class ClassTraits::Math;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Math"; }
#endif
    public:
        typedef Math SelfType;
        typedef Math ClassType;
        
    private:
        Math(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
#undef max
#undef min

        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual void Construct(Value& _this, unsigned argc, const Value* argv, bool extCall = false);
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        Value::Number get_LN10() const { return LN10; }
        Value::Number get_E() const { return E; }
        Value::Number get_LN2() const { return LN2; }
        Value::Number get_LOG10E() const { return LOG10E; }
        Value::Number get_LOG2E() const { return LOG2E; }
        Value::Number get_PI() const { return PI; }
        Value::Number get_SQRT1_2() const { return SQRT1_2; }
        Value::Number get_SQRT2() const { return SQRT2; }

        // AS3 API methods.
        enum MethodID {
            mid_abs, 
            mid_acos, 
            mid_asin, 
            mid_atan, 
            mid_atan2, 
            mid_ceil, 
            mid_cos, 
            mid_exp, 
            mid_floor, 
            mid_log, 
            mid_round, 
            mid_sin, 
            mid_sqrt, 
            mid_tan, 
            mid_pow, 
            mid_max, 
            mid_min, 
            mid_random, 
        };
        void abs(Value::Number& result, Value::Number x);
        void acos(Value::Number& result, Value::Number x);
        void asin(Value::Number& result, Value::Number x);
        void atan(Value::Number& result, Value::Number x);
        void atan2(Value::Number& result, Value::Number y, Value::Number x);
        void ceil(Value::Number& result, Value::Number x);
        void cos(Value::Number& result, Value::Number x);
        void exp(Value::Number& result, Value::Number x);
        void floor(Value::Number& result, Value::Number x);
        void log(Value::Number& result, Value::Number x);
        void round(Value::Number& result, Value::Number x);
        void sin(Value::Number& result, Value::Number x);
        void sqrt(Value::Number& result, Value::Number x);
        void tan(Value::Number& result, Value::Number x);
        void pow(Value::Number& result, Value::Number x, Value::Number y);
        void max(Value& result, unsigned argc, const Value* const argv);
        void min(Value& result, unsigned argc, const Value* const argv);
        void random(Value::Number& result);

    protected:
        // AS3 API members.
        const Value::Number LN10;
        const Value::Number E;
        const Value::Number LN2;
        const Value::Number LOG10E;
        const Value::Number LOG2E;
        const Value::Number PI;
        const Value::Number SQRT1_2;
        const Value::Number SQRT2;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

