//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Rectangle.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Rectangle.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Geom_Point.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_bottomGet, Value::Number> TFunc_Instances_Rectangle_bottomGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_bottomSet, Value, Value::Number> TFunc_Instances_Rectangle_bottomSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_bottomRightGet, Value> TFunc_Instances_Rectangle_bottomRightGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_bottomRightSet, Value, Instances::Point*> TFunc_Instances_Rectangle_bottomRightSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_leftGet, Value::Number> TFunc_Instances_Rectangle_leftGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_leftSet, Value, Value::Number> TFunc_Instances_Rectangle_leftSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_rightGet, Value::Number> TFunc_Instances_Rectangle_rightGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_rightSet, Value, Value::Number> TFunc_Instances_Rectangle_rightSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_sizeGet, Value> TFunc_Instances_Rectangle_sizeGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_sizeSet, Value, Instances::Point*> TFunc_Instances_Rectangle_sizeSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_topGet, Value::Number> TFunc_Instances_Rectangle_topGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_topSet, Value, Value::Number> TFunc_Instances_Rectangle_topSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_topLeftGet, Value> TFunc_Instances_Rectangle_topLeftGet;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_topLeftSet, Value, Instances::Point*> TFunc_Instances_Rectangle_topLeftSet;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_clone, Value> TFunc_Instances_Rectangle_clone;
typedef ThunkFunc2<Instances::Rectangle, Instances::Rectangle::mid_contains, bool, Value::Number, Value::Number> TFunc_Instances_Rectangle_contains;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_containsPoint, bool, Instances::Point*> TFunc_Instances_Rectangle_containsPoint;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_containsRect, bool, Instances::Rectangle*> TFunc_Instances_Rectangle_containsRect;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_equals, bool, Instances::Rectangle*> TFunc_Instances_Rectangle_equals;
typedef ThunkFunc2<Instances::Rectangle, Instances::Rectangle::mid_inflate, Value, Value::Number, Value::Number> TFunc_Instances_Rectangle_inflate;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_inflatePoint, Value, Instances::Point*> TFunc_Instances_Rectangle_inflatePoint;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_intersection, Value, Instances::Rectangle*> TFunc_Instances_Rectangle_intersection;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_intersects, bool, Instances::Rectangle*> TFunc_Instances_Rectangle_intersects;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_isEmpty, bool> TFunc_Instances_Rectangle_isEmpty;
typedef ThunkFunc2<Instances::Rectangle, Instances::Rectangle::mid_offset, Value, Value::Number, Value::Number> TFunc_Instances_Rectangle_offset;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_offsetPoint, Value, Instances::Point*> TFunc_Instances_Rectangle_offsetPoint;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_setEmpty, Value> TFunc_Instances_Rectangle_setEmpty;
typedef ThunkFunc0<Instances::Rectangle, Instances::Rectangle::mid_toString, ASString> TFunc_Instances_Rectangle_toString;
typedef ThunkFunc1<Instances::Rectangle, Instances::Rectangle::mid_union_, Value, Instances::Rectangle*> TFunc_Instances_Rectangle_union_;

template <> const TFunc_Instances_Rectangle_bottomGet::TMethod TFunc_Instances_Rectangle_bottomGet::Method = &Instances::Rectangle::bottomGet;
template <> const TFunc_Instances_Rectangle_bottomSet::TMethod TFunc_Instances_Rectangle_bottomSet::Method = &Instances::Rectangle::bottomSet;
template <> const TFunc_Instances_Rectangle_bottomRightGet::TMethod TFunc_Instances_Rectangle_bottomRightGet::Method = &Instances::Rectangle::bottomRightGet;
template <> const TFunc_Instances_Rectangle_bottomRightSet::TMethod TFunc_Instances_Rectangle_bottomRightSet::Method = &Instances::Rectangle::bottomRightSet;
template <> const TFunc_Instances_Rectangle_leftGet::TMethod TFunc_Instances_Rectangle_leftGet::Method = &Instances::Rectangle::leftGet;
template <> const TFunc_Instances_Rectangle_leftSet::TMethod TFunc_Instances_Rectangle_leftSet::Method = &Instances::Rectangle::leftSet;
template <> const TFunc_Instances_Rectangle_rightGet::TMethod TFunc_Instances_Rectangle_rightGet::Method = &Instances::Rectangle::rightGet;
template <> const TFunc_Instances_Rectangle_rightSet::TMethod TFunc_Instances_Rectangle_rightSet::Method = &Instances::Rectangle::rightSet;
template <> const TFunc_Instances_Rectangle_sizeGet::TMethod TFunc_Instances_Rectangle_sizeGet::Method = &Instances::Rectangle::sizeGet;
template <> const TFunc_Instances_Rectangle_sizeSet::TMethod TFunc_Instances_Rectangle_sizeSet::Method = &Instances::Rectangle::sizeSet;
template <> const TFunc_Instances_Rectangle_topGet::TMethod TFunc_Instances_Rectangle_topGet::Method = &Instances::Rectangle::topGet;
template <> const TFunc_Instances_Rectangle_topSet::TMethod TFunc_Instances_Rectangle_topSet::Method = &Instances::Rectangle::topSet;
template <> const TFunc_Instances_Rectangle_topLeftGet::TMethod TFunc_Instances_Rectangle_topLeftGet::Method = &Instances::Rectangle::topLeftGet;
template <> const TFunc_Instances_Rectangle_topLeftSet::TMethod TFunc_Instances_Rectangle_topLeftSet::Method = &Instances::Rectangle::topLeftSet;
template <> const TFunc_Instances_Rectangle_clone::TMethod TFunc_Instances_Rectangle_clone::Method = &Instances::Rectangle::clone;
template <> const TFunc_Instances_Rectangle_contains::TMethod TFunc_Instances_Rectangle_contains::Method = &Instances::Rectangle::contains;
template <> const TFunc_Instances_Rectangle_containsPoint::TMethod TFunc_Instances_Rectangle_containsPoint::Method = &Instances::Rectangle::containsPoint;
template <> const TFunc_Instances_Rectangle_containsRect::TMethod TFunc_Instances_Rectangle_containsRect::Method = &Instances::Rectangle::containsRect;
template <> const TFunc_Instances_Rectangle_equals::TMethod TFunc_Instances_Rectangle_equals::Method = &Instances::Rectangle::equals;
template <> const TFunc_Instances_Rectangle_inflate::TMethod TFunc_Instances_Rectangle_inflate::Method = &Instances::Rectangle::inflate;
template <> const TFunc_Instances_Rectangle_inflatePoint::TMethod TFunc_Instances_Rectangle_inflatePoint::Method = &Instances::Rectangle::inflatePoint;
template <> const TFunc_Instances_Rectangle_intersection::TMethod TFunc_Instances_Rectangle_intersection::Method = &Instances::Rectangle::intersection;
template <> const TFunc_Instances_Rectangle_intersects::TMethod TFunc_Instances_Rectangle_intersects::Method = &Instances::Rectangle::intersects;
template <> const TFunc_Instances_Rectangle_isEmpty::TMethod TFunc_Instances_Rectangle_isEmpty::Method = &Instances::Rectangle::isEmpty;
template <> const TFunc_Instances_Rectangle_offset::TMethod TFunc_Instances_Rectangle_offset::Method = &Instances::Rectangle::offset;
template <> const TFunc_Instances_Rectangle_offsetPoint::TMethod TFunc_Instances_Rectangle_offsetPoint::Method = &Instances::Rectangle::offsetPoint;
template <> const TFunc_Instances_Rectangle_setEmpty::TMethod TFunc_Instances_Rectangle_setEmpty::Method = &Instances::Rectangle::setEmpty;
template <> const TFunc_Instances_Rectangle_toString::TMethod TFunc_Instances_Rectangle_toString::Method = &Instances::Rectangle::toString;
template <> const TFunc_Instances_Rectangle_union_::TMethod TFunc_Instances_Rectangle_union_::Method = &Instances::Rectangle::union_;

namespace Instances
{
    Rectangle::Rectangle(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , height()
    , width()
    , x()
    , y()
//##protect##"instance::Rectangle::Rectangle()$data"
//##protect##"instance::Rectangle::Rectangle()$data"
    {
//##protect##"instance::Rectangle::Rectangle()$code"
//##protect##"instance::Rectangle::Rectangle()$code"
    }

    void Rectangle::bottomGet(Value::Number& result)
    {
//##protect##"instance::Rectangle::bottomGet()"
        result = y+height;
//##protect##"instance::Rectangle::bottomGet()"
    }
    void Rectangle::bottomSet(Value& result, Value::Number value)
    {
//##protect##"instance::Rectangle::bottomSet()"
		height = value - y;
		result.SetUndefined();
//##protect##"instance::Rectangle::bottomSet()"
    }
    void Rectangle::bottomRightGet(Value& result)
    {
//##protect##"instance::Rectangle::bottomRightGet()"
		Value args[] = {Value(x + width), Value(y + height)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Rectangle::bottomRightGet()"
    }
    void Rectangle::bottomRightSet(Value& result, Instances::Point* value)
    {
//##protect##"instance::Rectangle::bottomRightSet()"
		if (!value)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
        width = value->GetX() - x;
		height = value->GetY() - y;
		result.SetUndefined();
//##protect##"instance::Rectangle::bottomRightSet()"
    }
    void Rectangle::leftGet(Value::Number& result)
    {
//##protect##"instance::Rectangle::leftGet()"
        result = x;
//##protect##"instance::Rectangle::leftGet()"
    }
    void Rectangle::leftSet(Value& result, Value::Number value)
    {
//##protect##"instance::Rectangle::leftSet()"
		width += (x-value);
        x = value;
		result.SetUndefined();
		 
//##protect##"instance::Rectangle::leftSet()"
    }
    void Rectangle::rightGet(Value::Number& result)
    {
//##protect##"instance::Rectangle::rightGet()"
       result = x + width;
//##protect##"instance::Rectangle::rightGet()"
    }
    void Rectangle::rightSet(Value& result, Value::Number value)
    {
//##protect##"instance::Rectangle::rightSet()"
        width = value - x;
		result.SetUndefined();
//##protect##"instance::Rectangle::rightSet()"
    }
    void Rectangle::sizeGet(Value& result)
    {
//##protect##"instance::Rectangle::sizeGet()"
		Value args[] = {Value(width), Value(height)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Rectangle::sizeGet()"
    }
    void Rectangle::sizeSet(Value& result, Instances::Point* value)
    {
//##protect##"instance::Rectangle::sizeSet()"
		if (!value)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
        width = value->GetX();
		height = value->GetY();
		result.SetUndefined();
//##protect##"instance::Rectangle::sizeSet()"
    }
    void Rectangle::topGet(Value::Number& result)
    {
//##protect##"instance::Rectangle::topGet()"
        result = y;
//##protect##"instance::Rectangle::topGet()"
    }
    void Rectangle::topSet(Value& result, Value::Number value)
    {
//##protect##"instance::Rectangle::topSet()"
        height += y - value;
		y = value;
		result.SetUndefined();
//##protect##"instance::Rectangle::topSet()"
    }
    void Rectangle::topLeftGet(Value& result)
    {
//##protect##"instance::Rectangle::topLeftGet()"
		Value args[] = {Value(x), Value(y)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Rectangle::topLeftGet()"
    }
    void Rectangle::topLeftSet(Value& result, Instances::Point* value)
    {
//##protect##"instance::Rectangle::topLeftSet()"
		if (!value)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
        width += x - value->GetX();
		height += y - value->GetY();
		x = value->GetX();
		y = value->GetY();
		result.SetUndefined();
//##protect##"instance::Rectangle::topLeftSet()"
    }
    void Rectangle::clone(Value& result)
    {
//##protect##"instance::Rectangle::clone()"
		Value args[] = {Value(x), Value(y), Value(width), Value(height)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck();
//##protect##"instance::Rectangle::clone()"
    }
    void Rectangle::contains(bool& result, Value::Number x, Value::Number y)
    {
//##protect##"instance::Rectangle::contains()"
		// note that bottom and right edges are not contained.
		Value::Number right = this->x + width;
		Value::Number bottom = this->y + height;
		result = ((x < right) && (x >= this->x) && (y < bottom) && (y >= this->y));
//##protect##"instance::Rectangle::contains()"
    }
    void Rectangle::containsPoint(bool& result, Instances::Point* point)
    {
//##protect##"instance::Rectangle::containsPoint()"
		if (!point)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		Value::Number px = point->GetX();
		Value::Number py = point->GetY();
		return contains(result, px, py);
//##protect##"instance::Rectangle::containsPoint()"
    }
    void Rectangle::containsRect(bool& result, Instances::Rectangle* rect)
    {
//##protect##"instance::Rectangle::containsRect()"
		// special case for 0 width/height rectangles. 
		if (!rect)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		if ((rect->GetHeight() == 0) && (rect->GetWidth() == 0))
		{
			if (x < rect->GetX() && y < rect->GetY())
			{
				result = true;
				return;
			}
			result = false;
			return;
		}
		Value::Number x2 = rect->GetX();
		Value::Number y2 = rect->GetY();
		Value::Number right2 = rect->GetWidth() + x2;
		Value::Number bottom2 = rect->GetHeight() + y2;

		Value::Number x1 = x;
		Value::Number y1 = y;
		Value::Number right1 = width + x1;
		Value::Number bottom1 = height + y1;

		result = ((right1 >= right2) && (bottom1 >= bottom2) && (x1 <= x2) && (y1 <= y2));
//##protect##"instance::Rectangle::containsRect()"
    }
    void Rectangle::equals(bool& result, Instances::Rectangle* toCompare)
    {
//##protect##"instance::Rectangle::equals()"
		if (!toCompare)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
       result = ((x == toCompare->GetX()) && (y == toCompare->GetY()) && (width == toCompare->GetWidth()) 
		   && (height == toCompare->GetHeight()));
//##protect##"instance::Rectangle::equals()"
    }
    void Rectangle::inflate(Value& result, Value::Number dx, Value::Number dy)
    {
//##protect##"instance::Rectangle::inflate()"
		result.SetUndefined();
        x = x - dx; width = width + 2*dx;
		y = y - dy; height = height + 2*dy;
//##protect##"instance::Rectangle::inflate()"
    }
    void Rectangle::inflatePoint(Value& result, Instances::Point* point)
    {
//##protect##"instance::Rectangle::inflatePoint()"
		if (!point)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		result.SetUndefined();
		Value::Number dx = point->GetX();
		Value::Number dy = point->GetY();

		x = x - dx; width = width + 2*dx;
		y = y - dy; height = height + 2*dy;
//##protect##"instance::Rectangle::inflatePoint()"
    }
    void Rectangle::intersection(Value& result, Instances::Rectangle* toIntersect)
    {
//##protect##"instance::Rectangle::intersection()"
		bool res1;
		if (!toIntersect)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		intersects(res1, toIntersect);
		if (!res1)
		{
			const Value::Number zero = MakeValueNumber(0.0);
			Value args[] = {Value(zero), Value(zero), Value(zero), Value(zero)};
			return GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck();
		}

		Value::Number x1		= toIntersect->GetX();
		Value::Number y1		= toIntersect->GetY();
		Value::Number right1	= x1 + toIntersect->GetWidth();
		Value::Number bottom1	= y1 + toIntersect->GetHeight();

		x1 = x > x1? x: x1;
		right1 = x + width > right1? right1: x+width;
		y1 = y > y1? y: y1;
		bottom1 = y + height > bottom1? bottom1: y + height;

		Value args[] = {Value(x1), Value(y1), Value(right1 - x1), Value(bottom1 - y1)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck();

//##protect##"instance::Rectangle::intersection()"
    }
    void Rectangle::intersects(bool& result, Instances::Rectangle* toIntersect)
    {
//##protect##"instance::Rectangle::intersects()"
		// If either rectangle is empty, return false;
		if (!toIntersect)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		bool res;
		toIntersect->isEmpty(res);
		if (res)
		{
			result = false;
			return;
		}

		isEmpty(res);
		if (res)
		{
			result = false;
			return;
		}

		Value::Number bottom = y + height;
		Value::Number right = x + width;

		Value::Number x2 = toIntersect->GetX();
		Value::Number y2 = toIntersect->GetY();
		Value::Number bottom2 = toIntersect->GetY() + toIntersect->GetHeight();
		Value::Number right2 = toIntersect->GetX() + toIntersect->GetWidth();


		if ( (bottom >= y2)&&(bottom2 >= y) )
			if ( (right2 >= x)&&(right >= x2) )
			{
				result = true;
				return;
			}
		result = false;

//##protect##"instance::Rectangle::intersects()"
    }
    void Rectangle::isEmpty(bool& result)
    {
//##protect##"instance::Rectangle::isEmpty()"
        if (width <= 0 || height <= 0)
		{
			result = true;
			return;
		}
		result = false;
//##protect##"instance::Rectangle::isEmpty()"
    }
    void Rectangle::offset(Value& result, Value::Number dx, Value::Number dy)
    {
//##protect##"instance::Rectangle::offset()"
		result.SetUndefined();
		x += dx;
		y += dy;
//##protect##"instance::Rectangle::offset()"
    }
    void Rectangle::offsetPoint(Value& result, Instances::Point* point)
    {
//##protect##"instance::Rectangle::offsetPoint()"
		if (!point)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		result.SetUndefined();
		x += point->GetX();
		y += point->GetY();
//##protect##"instance::Rectangle::offsetPoint()"
    }
    void Rectangle::setEmpty(Value& result)
    {
//##protect##"instance::Rectangle::setEmpty()"
        bool res;
		isEmpty(res);
		result.SetBool(res);
//##protect##"instance::Rectangle::setEmpty()"
    }
    void Rectangle::toString(ASString& result)
    {
//##protect##"instance::Rectangle::toString()"
		result += GetStringManager().CreateConstString("(x=") + GetVM().AsString(Value(x)) + 
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("y=") + 
			GetVM().AsString(Value(y)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("w=") + 
			GetVM().AsString(Value(width)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("h=") + 
			GetVM().AsString(Value(height)) +
			GetStringManager().CreateConstString(")");
//##protect##"instance::Rectangle::toString()"
    }
    void Rectangle::union_(Value& result, Instances::Rectangle* toUnion)
    {
//##protect##"instance::Rectangle::union_()"
		// if either of the rectangles is empty, return the other rectangle
		if (!toUnion)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		bool res;
		toUnion->isEmpty(res);
		if (res)
		{
			Value args[] = {Value(x), Value(y), Value(width), Value(height)};
			return(GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck());
		}

		isEmpty(res);
		if (res)
		{
			Value args[] = {Value(toUnion->GetX()), Value(toUnion->GetY()), Value(toUnion->GetWidth()), Value(toUnion->GetHeight())};
			return(GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck());
		}

		Value::Number x1 = x; Value::Number y1 = y; Value::Number right1 = x + width; Value::Number bottom1 = y + height;
		Value::Number x2 = toUnion->GetX(); Value::Number y2 = toUnion->GetY(); 
		Value::Number right2 = x2 + toUnion->GetWidth(); Value::Number bottom2 = y2 + toUnion->GetHeight();

		Value::Number x3,y3, bottom3, right3;

		x3		= x1 > x2? x2:x1;
		right3	= right1 > right2? right1: right2;
		y3		= y1 > y2? y2:y1;
		bottom3	= bottom1 > bottom2? bottom1: bottom2;

		Value args[] = {Value(x3), Value(y3), Value(right3 - x3), Value(bottom3 - y3)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Rectangle", 4, args).DoNotCheck();
//##protect##"instance::Rectangle::union_()"
    }

//##protect##"instance$methods"
    void Rectangle::AS3Constructor(unsigned argc, const Value* argv)
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
                if (argc > 2)
                {
                    if (!argv[2].Convert2Number(width))
                    {
                        return;
                    }
                    if (argc > 3)
                    {
                        if (!argv[3].Convert2Number(height))
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Rectangle::ti[Rectangle::ThunkInfoNum] = {
        {TFunc_Instances_Rectangle_bottomGet::Func, &NumberCI, "bottom", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_bottomSet::Func, NULL, "bottom", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_bottomRightGet::Func, &PointCI, "bottomRight", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_bottomRightSet::Func, NULL, "bottomRight", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_leftGet::Func, &NumberCI, "left", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_leftSet::Func, NULL, "left", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_rightGet::Func, &NumberCI, "right", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_rightSet::Func, NULL, "right", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_sizeGet::Func, &PointCI, "size", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_sizeSet::Func, NULL, "size", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_topGet::Func, &NumberCI, "top", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_topSet::Func, NULL, "top", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_topLeftGet::Func, &PointCI, "topLeft", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Rectangle_topLeftSet::Func, NULL, "topLeft", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Rectangle_clone::Func, &RectangleCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Rectangle_contains::Func, &BooleanCI, "contains", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Rectangle_containsPoint::Func, &BooleanCI, "containsPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_containsRect::Func, &BooleanCI, "containsRect", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_equals::Func, &BooleanCI, "equals", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_inflate::Func, NULL, "inflate", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Rectangle_inflatePoint::Func, NULL, "inflatePoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_intersection::Func, &RectangleCI, "intersection", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_intersects::Func, &BooleanCI, "intersects", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_isEmpty::Func, &BooleanCI, "isEmpty", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Rectangle_offset::Func, NULL, "offset", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Rectangle_offsetPoint::Func, NULL, "offsetPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Rectangle_setEmpty::Func, NULL, "setEmpty", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Rectangle_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Rectangle_union_::Func, &RectangleCI, "union", NULL, CT_Method, 1, 1},
    };
    const MemberInfo Rectangle::mi[Rectangle::MemberInfoNum] = {
        {"height", OFFSETOF(Instances::Rectangle, height), SlotInfo::BT_Number, 0},
        {"width", OFFSETOF(Instances::Rectangle, width), SlotInfo::BT_Number, 0},
        {"x", OFFSETOF(Instances::Rectangle, x), SlotInfo::BT_Number, 0},
        {"y", OFFSETOF(Instances::Rectangle, y), SlotInfo::BT_Number, 0},
    };


    Rectangle::Rectangle(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Rectangle::Rectangle()"
//##protect##"InstanceTraits::Rectangle::Rectangle()"
        SetMemSize(sizeof(Instances::Rectangle));

    }

    Pickable<Instances::Rectangle> Rectangle::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Rectangle>(new(t.Alloc()) Instances::Rectangle(t));
    }

    void Rectangle::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Rectangle::Rectangle(VM& vm)
    : Traits(vm, RectangleCI)
    {
//##protect##"ClassTraits::Rectangle::Rectangle()"
//##protect##"ClassTraits::Rectangle::Rectangle()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Rectangle(vm, RectangleCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Rectangle::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Rectangle(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo RectangleCI = {
    ClassInfo::CompileTime,
    "Rectangle", "flash.geom", &ObjectCI,
    ClassTraits::Rectangle::MakeClassTraits,
    0,
    0,
    InstanceTraits::Rectangle::ThunkInfoNum,
    InstanceTraits::Rectangle::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::Rectangle::ti,
    InstanceTraits::Rectangle::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

