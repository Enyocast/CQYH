//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Object.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Object_H
#define INC_AS3_Obj_Object_H

#include "../AS3_Instance.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace InstanceTraits
{
    class Interface;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Object;
}

namespace InstanceTraits
{
    class Object;
}

namespace Classes
{
    class Object;
}

namespace Instances
{
    class Object : public Instance
    {
        friend class InstanceTraits::Object;
        
    public:
        typedef Object SelfType;
        typedef Classes::Object ClassType;
        typedef InstanceTraits::Object TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Object"; }
#endif
    protected:
        Object(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        friend class Instances::Namespace;
        friend class InstanceTraits::Traits;
        friend class InstanceTraits::Interface;

    private:
        Object(VM& vm);

    public:
        //static void toString(Object& _this, Value& result, unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_AS3isPrototypeOf, 
            mid_AS3hasOwnProperty, 
            mid_AS3propertyIsEnumerable, 
            mid_hasOwnPropertyProto, 
            mid_propertyIsEnumerableProto, 
            mid_setPropertyIsEnumerableProto, 
            mid_isPrototypeOfProto, 
            mid_toStringProto, 
            mid_toLocaleStringProto, 
            mid_valueOfProto, 
        };
        static void AS3isPrototypeOf(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3hasOwnProperty(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void AS3propertyIsEnumerable(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void hasOwnPropertyProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void propertyIsEnumerableProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void setPropertyIsEnumerableProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void isPrototypeOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void toLocaleStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
        static void valueOfProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Object : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Object"; }
#endif
    public:
        Object(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Object> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Object : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Object"; }
#endif
    public:
        typedef Classes::Object ClassType;

    public:
        Object(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Object : public Class
    {
        friend class ClassTraits::Object;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Object"; }
#endif
    public:
        typedef Object SelfType;
        typedef Object ClassType;
        
    private:
        Object(ClassTraits::Traits& t);
    public:
        virtual void InitPrototype(AS3::Object& obj) const;
        enum { ThunkInfoNum = 7 };
        static const ThunkInfo ti[ThunkInfoNum];
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        // Implementation of Construct for Object differs from the default one.
        virtual void Construct(Value& result, unsigned argc, const Value* argv, bool extCall = false);
        // Set up values of slots ...
        virtual void SetupSlotValues(Object& for_obj) const;

        void toStringProto(ASString& result);
//##protect##"class_$methods"

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
namespace InstanceTraits
{
    class Interface : public Traits
    {
    public:
        Interface(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Object> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);
    };
}
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

