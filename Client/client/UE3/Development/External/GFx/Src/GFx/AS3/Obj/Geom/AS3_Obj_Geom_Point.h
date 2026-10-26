//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Point.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Point_H
#define INC_AS3_Obj_Geom_Point_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Point;
}

namespace InstanceTraits
{
    class Point;
}

namespace Classes
{
    class Point;
}

namespace Instances
{
    class Point : public Instances::Object
    {
        friend class InstanceTraits::Point;
        
    public:
        typedef Point SelfType;
        typedef Classes::Point ClassType;
        typedef InstanceTraits::Point TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Point"; }
#endif
    protected:
        Point(InstanceTraits::Traits& t);

//##protect##"instance$methods"
	virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_x() const { return x; }
        Value::Number get_y() const { return y; }

        // AS3 API methods.
        enum MethodID {
            mid_lengthGet, 
            mid_add, 
            mid_clone, 
            mid_equals, 
            mid_normalize, 
            mid_offset, 
            mid_subtract, 
            mid_toString, 
        };
        void lengthGet(Value::Number& result);
        void add(Value& result, Instances::Point* v);
        void clone(Value& result);
        void equals(bool& result, Instances::Point* toCompare);
        void normalize(Value& result, Value::Number thickness);
        void offset(Value& result, Value::Number dx, Value::Number dy);
        void subtract(Value& result, Instances::Point* v);
        void toString(ASString& result);

    protected:
        // AS3 API members.
        Value::Number x;
        Value::Number y;

//##protect##"instance$data"
    public:
        Value::Number GetX() {return x;};
        Value::Number GetY() {return y;};
        void SetX(Value::Number value) { x = value; }
        void SetY(Value::Number value) { y = value; }
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Point : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Point"; }
#endif
    public:
        Point(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Point> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 8 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Point : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Point"; }
#endif
    public:
        typedef Classes::Point ClassType;

    public:
        Point(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Point : public Class
    {
        friend class ClassTraits::Point;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Point"; }
#endif
    public:
        typedef Point SelfType;
        typedef Point ClassType;
        
    private:
        Point(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_distance, 
            mid_interpolate, 
            mid_polar, 
        };
        void distance(Value::Number& result, Instances::Point* pt1, Instances::Point* pt2);
        void interpolate(Value& result, Instances::Point* pt1, Instances::Point* pt2, Value::Number f);
        void polar(Value& result, Value::Number len, Value::Number angle);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

