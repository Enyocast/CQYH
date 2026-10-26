//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_int.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_int_H
#define INC_AS3_Obj_int_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class int_;
}

namespace InstanceTraits
{
    class int_;
}

namespace Classes
{
    class int_;
}

namespace InstanceTraits
{
    class int_ : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::int_"; }
#endif
    public:
        int_(VM& vm, const ClassInfo& ci);

    public: 
        virtual void MakeObject(Value& result, Traits& t);

        static void AS3toExponential(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3toFixed(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3toPrecision(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3toString(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3valueOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toLocaleStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toExponentialProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toFixedProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toPrecisionProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        enum { ThunkInfoNum = 5 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class int_ : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::int_"; }
#endif
    public:
        typedef Classes::int_ ClassType;

    public:
        int_(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
        virtual bool Coerce(const Value& value, Value& result) const;
        bool CoerceValue(const Value& value, Value& result) const;
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class int_ : public Class
    {
        friend class ClassTraits::int_;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::int_"; }
#endif
    public:
        typedef int_ SelfType;
        typedef int_ ClassType;
        
    private:
        int_(ClassTraits::Traits& t);
    public:
        virtual void InitPrototype(AS3::Object& obj) const;
        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
    public:
        /* Future development.
        // Reuse prototype object from the Number class.
        virtual AS3::Object* int_::MakePrototype() const
        {
            return &GetVM().GetClassNumber().GetPrototype();
        }
        */
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual void Construct(Value& result, unsigned argc, const Value* argv, bool extCall = false);
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        SInt32 get_MIN_VALUE() const { return MIN_VALUE; }
        SInt32 get_MAX_VALUE() const { return MAX_VALUE; }


    protected:
        // AS3 API members.
        const SInt32 MIN_VALUE;
        const SInt32 MAX_VALUE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

