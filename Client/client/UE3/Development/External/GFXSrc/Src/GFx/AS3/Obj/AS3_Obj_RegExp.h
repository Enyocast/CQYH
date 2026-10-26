//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_RegExp.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_RegExp_H
#define INC_AS3_Obj_RegExp_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class RegExp;
}

namespace InstanceTraits
{
    class RegExp;
}

namespace Classes
{
    class RegExp;
}

namespace Instances
{
    class RegExp : public Instances::Object
    {
        friend class InstanceTraits::RegExp;
        
    public:
        typedef RegExp SelfType;
        typedef Classes::RegExp ClassType;
        typedef InstanceTraits::RegExp TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::RegExp"; }
#endif
    protected:
        RegExp(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_sourceGet, 
            mid_globalGet, 
            mid_ignoreCaseGet, 
            mid_multilineGet, 
            mid_lastIndexGet, 
            mid_lastIndexSet, 
            mid_dotallGet, 
            mid_extendedGet, 
            mid_AS3exec, 
            mid_AS3test, 
        };
        void sourceGet(ASString& result);
        void globalGet(bool& result);
        void ignoreCaseGet(bool& result);
        void multilineGet(bool& result);
        void lastIndexGet(SInt32& result);
        void lastIndexSet(Value& result, SInt32 i);
        void dotallGet(bool& result);
        void extendedGet(bool& result);
        void AS3exec(Value& result, const ASString& s);
        void AS3test(bool& result, const ASString& s);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class RegExp : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::RegExp"; }
#endif
    public:
        RegExp(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::RegExp> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 10 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class RegExp : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::RegExp"; }
#endif
    public:
        typedef Classes::RegExp ClassType;

    public:
        RegExp(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class RegExp : public Class
    {
        friend class ClassTraits::RegExp;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::RegExp"; }
#endif
    public:
        typedef RegExp SelfType;
        typedef RegExp ClassType;
        
    private:
        RegExp(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual Pickable<AS3::Object> MakePrototype() const;
        virtual void InitPrototype(AS3::Object& obj) const;       
//##protect##"class_$methods"

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

