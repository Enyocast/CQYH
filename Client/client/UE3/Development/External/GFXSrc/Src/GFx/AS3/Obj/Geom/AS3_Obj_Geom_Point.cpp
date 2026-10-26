//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Point.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Point.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Point, Instances::Point::mid_lengthGet, Value::Number> TFunc_Instances_Point_lengthGet;
typedef ThunkFunc1<Instances::Point, Instances::Point::mid_add, Value, Instances::Point*> TFunc_Instances_Point_add;
typedef ThunkFunc0<Instances::Point, Instances::Point::mid_clone, Value> TFunc_Instances_Point_clone;
typedef ThunkFunc1<Instances::Point, Instances::Point::mid_equals, bool, Instances::Point*> TFunc_Instances_Point_equals;
typedef ThunkFunc1<Instances::Point, Instances::Point::mid_normalize, Value, Value::Number> TFunc_Instances_Point_normalize;
typedef ThunkFunc2<Instances::Point, Instances::Point::mid_offset, Value, Value::Number, Value::Number> TFunc_Instances_Point_offset;
typedef ThunkFunc1<Instances::Point, Instances::Point::mid_subtract, Value, Instances::Point*> TFunc_Instances_Point_subtract;
typedef ThunkFunc0<Instances::Point, Instances::Point::mid_toString, ASString> TFunc_Instances_Point_toString;

template <> const TFunc_Instances_Point_lengthGet::TMethod TFunc_Instances_Point_lengthGet::Method = &Instances::Point::lengthGet;
template <> const TFunc_Instances_Point_add::TMethod TFunc_Instances_Point_add::Method = &Instances::Point::add;
template <> const TFunc_Instances_Point_clone::TMethod TFunc_Instances_Point_clone::Method = &Instances::Point::clone;
template <> const TFunc_Instances_Point_equals::TMethod TFunc_Instances_Point_equals::Method = &Instances::Point::equals;
template <> const TFunc_Instances_Point_normalize::TMethod TFunc_Instances_Point_normalize::Method = &Instances::Point::normalize;
template <> const TFunc_Instances_Point_offset::TMethod TFunc_Instances_Point_offset::Method = &Instances::Point::offset;
template <> const TFunc_Instances_Point_subtract::TMethod TFunc_Instances_Point_subtract::Method = &Instances::Point::subtract;
template <> const TFunc_Instances_Point_toString::TMethod TFunc_Instances_Point_toString::Method = &Instances::Point::toString;

namespace Instances
{
    Point::Point(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , x()
    , y()
//##protect##"instance::Point::Point()$data"
//##protect##"instance::Point::Point()$data"
    {
//##protect##"instance::Point::Point()$code"
//##protect##"instance::Point::Point()$code"
    }

    void Point::lengthGet(Value::Number& result)
    {
//##protect##"instance::Point::lengthGet()"
        result = sqrt(x*x + y*y);
//##protect##"instance::Point::lengthGet()"
    }
    void Point::add(Value& result, Instances::Point* v)
    {
//##protect##"instance::Point::add()"
		if (!v)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		Value args[] = {Value(x + v->x), Value(y + v->y)};
		// by calling NoNotCheck, we avoid throwing an exception if the return value of 
		// ConstructBuiltinValue is not compared to anything. Safe since this is the last 
		// line in the code.
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Point::add()"
    }
    void Point::clone(Value& result)
    {
//##protect##"instance::Point::clone()"
		Value args[] = {Value(x), Value(y)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Point::clone()"
    }
    void Point::equals(bool& result, Instances::Point* toCompare)
    {
//##protect##"instance::Point::equals()"
		if (!toCompare)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
        result = ((x == toCompare->x) && (y == toCompare->y));
//##protect##"instance::Point::equals()"
    }
    void Point::normalize(Value& result, Value::Number thickness)
    {
//##protect##"instance::Point::normalize()"
		// Modifies the original point, don't create a new one!
		if (x == 0 && y == 0)
		{
			// Replicate flash player's behavior in this case.
			x = 0;
			y = 0;
			result.SetUndefined();
			return;
		}
		double tmp = x*thickness/sqrt(x*x+y*y);
		y = y*thickness/sqrt(x*x+y*y);
		x = tmp;
		result.SetUndefined();
//##protect##"instance::Point::normalize()"
    }
    void Point::offset(Value& result, Value::Number dx, Value::Number dy)
    {
//##protect##"instance::Point::offset()"
		// Modifies the original point, don't create a new one!
		x += dx;
		y += dy;
		result.SetUndefined();
//##protect##"instance::Point::offset()"
    }
    void Point::subtract(Value& result, Instances::Point* v)
    {
//##protect##"instance::Point::subtract()"
		// Creates new point
		if (!v)
		{
			return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		Value args[] = {Value(x - v->x), Value(y - v->y)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Point::subtract()"
    }
    void Point::toString(ASString& result)
    {
//##protect##"instance::Point::toString()"
		result += GetStringManager().CreateConstString("(x=") + GetVM().AsString(Value(x)) + 
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("y=") + 
			GetVM().AsString(Value(y)) +
			GetStringManager().CreateConstString(")");
//##protect##"instance::Point::toString()"
    }

//##protect##"instance$methods"
    void Point::AS3Constructor(unsigned argc, const Value* argv)
    {

        if (argc > 0)
        {
            // According to doc, x will not be modified if there is an exception
            if (!argv[0].Convert2Number(x))
            {
                return;
            }
            if (argc > 1)
            {
                if (!argv[1].Convert2Number(y))
                {
                    return;
                }
            }
        }
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Point::ti[Point::ThunkInfoNum] = {
        {TFunc_Instances_Point_lengthGet::Func, &NumberCI, "length", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Point_add::Func, &PointCI, "add", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Point_clone::Func, &PointCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Point_equals::Func, &BooleanCI, "equals", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Point_normalize::Func, NULL, "normalize", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Point_offset::Func, NULL, "offset", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Point_subtract::Func, &PointCI, "subtract", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Point_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo Point::mi[Point::MemberInfoNum] = {
        {"x", OFFSETOF(Instances::Point, x), SlotInfo::BT_Number, 0},
        {"y", OFFSETOF(Instances::Point, y), SlotInfo::BT_Number, 0},
    };


    Point::Point(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Point::Point()"
//##protect##"InstanceTraits::Point::Point()"
        SetMemSize(sizeof(Instances::Point));

    }

    Pickable<Instances::Point> Point::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Point>(new(t.Alloc()) Instances::Point(t));
    }

    void Point::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    Point::Point(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Point::Point()"
//##protect##"class_::Point::Point()"
    }
    void Point::distance(Value::Number& result, Instances::Point* pt1, Instances::Point* pt2)
    {
//##protect##"class_::Point::distance()"
        result = Value(MakeValueNumber(sqrt((pt1->GetX() - pt2->GetX())*(pt1->GetX() - pt2->GetX()) + 
			(pt1->GetY() - pt2->GetY())*(pt1->GetY() - pt2->GetY()))));
//##protect##"class_::Point::distance()"
    }
    void Point::interpolate(Value& result, Instances::Point* pt1, Instances::Point* pt2, Value::Number f)
    {
//##protect##"class_::Point::interpolate()"
		Value args[] = {Value((pt2->GetX() - pt1->GetX())*f + pt1->GetX()), Value((pt2->GetY() - pt1->GetY())*f + pt1->GetY())};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"class_::Point::interpolate()"
    }
    void Point::polar(Value& result, Value::Number len, Value::Number angle)
    {
//##protect##"class_::Point::polar()"
		Value args[] = {Value(MakeValueNumber(len*cos(angle))), Value(MakeValueNumber(len*sin(angle)))};
		if (!GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args))
			return;
//##protect##"class_::Point::polar()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc2<Classes::Point, Classes::Point::mid_distance, Value::Number, Instances::Point*, Instances::Point*> TFunc_Classes_Point_distance;
typedef ThunkFunc3<Classes::Point, Classes::Point::mid_interpolate, Value, Instances::Point*, Instances::Point*, Value::Number> TFunc_Classes_Point_interpolate;
typedef ThunkFunc2<Classes::Point, Classes::Point::mid_polar, Value, Value::Number, Value::Number> TFunc_Classes_Point_polar;

template <> const TFunc_Classes_Point_distance::TMethod TFunc_Classes_Point_distance::Method = &Classes::Point::distance;
template <> const TFunc_Classes_Point_interpolate::TMethod TFunc_Classes_Point_interpolate::Method = &Classes::Point::interpolate;
template <> const TFunc_Classes_Point_polar::TMethod TFunc_Classes_Point_polar::Method = &Classes::Point::polar;

namespace ClassTraits
{
    const ThunkInfo Point::ti[Point::ThunkInfoNum] = {
        {TFunc_Classes_Point_distance::Func, &NumberCI, "distance", NULL, CT_Method, 2, 2},
        {TFunc_Classes_Point_interpolate::Func, &PointCI, "interpolate", NULL, CT_Method, 3, 3},
        {TFunc_Classes_Point_polar::Func, &PointCI, "polar", NULL, CT_Method, 2, 2},
    };
    Point::Point(VM& vm)
    : Traits(vm, PointCI)
    {
//##protect##"ClassTraits::Point::Point()"
//##protect##"ClassTraits::Point::Point()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Point(vm, PointCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Point(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Point::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Point(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PointCI = {
    ClassInfo::CompileTime,
    "Point", "flash.geom", &ObjectCI,
    ClassTraits::Point::MakeClassTraits,
    ClassTraits::Point::ThunkInfoNum,
    0,
    InstanceTraits::Point::ThunkInfoNum,
    InstanceTraits::Point::MemberInfoNum,
    ClassTraits::Point::ti,
    NULL,
    InstanceTraits::Point::ti,
    InstanceTraits::Point::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

