//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Vector3D.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Vector3D_H
#define INC_AS3_Obj_Geom_Vector3D_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Vector3D;
}

namespace InstanceTraits
{
    class Vector3D;
}

namespace Classes
{
    class Vector3D;
}

namespace Instances
{
    class Vector3D : public Instances::Object
    {
        friend class InstanceTraits::Vector3D;
        
    public:
        typedef Vector3D SelfType;
        typedef Classes::Vector3D ClassType;
        typedef InstanceTraits::Vector3D TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Vector3D"; }
#endif
    protected:
        Vector3D(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_lengthGet, 
            mid_lengthSquaredGet, 
            mid_xSet, 
            mid_xGet, 
            mid_ySet, 
            mid_yGet, 
            mid_zSet, 
            mid_zGet, 
            mid_wSet, 
            mid_wGet, 
            mid_add, 
            mid_clone, 
            mid_crossProduct, 
            mid_decrementBy, 
            mid_dotProduct, 
            mid_equals, 
            mid_incrementBy, 
            mid_nearEquals, 
            mid_negate, 
            mid_normalize, 
            mid_project, 
            mid_scaleBy, 
            mid_subtract, 
            mid_toString, 
        };
        void lengthGet(Value::Number& result);
        void lengthSquaredGet(Value::Number& result);
        void xSet(Value& result, Value::Number value);
        void xGet(Value::Number& result);
        void ySet(Value& result, Value::Number value);
        void yGet(Value::Number& result);
        void zSet(Value& result, Value::Number value);
        void zGet(Value::Number& result);
        void wSet(Value& result, Value::Number value);
        void wGet(Value::Number& result);
        void add(Value& result, Instances::Vector3D* v);
        void clone(Value& result);
        void crossProduct(Value& result, Instances::Vector3D* v);
        void decrementBy(Value& result, Instances::Vector3D* v);
        void dotProduct(Value::Number& result, Instances::Vector3D* a);
        void equals(bool& result, Instances::Vector3D* toCompare, bool allFour);
        void incrementBy(Value& result, Instances::Vector3D* v);
        void nearEquals(bool& result, Instances::Vector3D* toCompare, Value::Number tolerance, bool allFour);
        void negate(Value& result);
        void normalize(Value::Number& result);
        void project(Value& result);
        void scaleBy(Value& result, Value::Number s);
        void subtract(Value& result, Instances::Vector3D* v);
        void toString(ASString& result);

//##protect##"instance$data"
        Value::Number x;
        Value::Number y;
        Value::Number z;
        Value::Number w;

        Value::Number GetX() {return x;};
        Value::Number GetY() {return y;};
        Value::Number GetZ() {return z;};
		Value::Number GetW() {return w;};
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Vector3D : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Vector3D"; }
#endif
    public:
        Vector3D(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Vector3D> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 24 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Vector3D : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Vector3D"; }
#endif
    public:
        typedef Classes::Vector3D ClassType;

    public:
        Vector3D(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Vector3D : public Class
    {
        friend class ClassTraits::Vector3D;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Vector3D"; }
#endif
    public:
        typedef Vector3D SelfType;
        typedef Vector3D ClassType;
        
    private:
        Vector3D(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        Instances::Vector3D* get_X_AXIS() const { return X_AXIS; }
        Instances::Vector3D* get_Y_AXIS() const { return Y_AXIS; }
        Instances::Vector3D* get_Z_AXIS() const { return Z_AXIS; }

        // AS3 API methods.
        enum MethodID {
            mid_angleBetween, 
            mid_distance, 
        };
        void angleBetween(Value::Number& result, Instances::Vector3D* a, Instances::Vector3D* b);
        void distance(Value::Number& result, Instances::Vector3D* pt1, Instances::Vector3D* pt2);

    protected:
        // AS3 API members.
        SPtr<Instances::Vector3D> X_AXIS;
        SPtr<Instances::Vector3D> Y_AXIS;
        SPtr<Instances::Vector3D> Z_AXIS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

