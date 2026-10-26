//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Rectangle.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Rectangle_H
#define INC_AS3_Obj_Geom_Rectangle_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Point;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Rectangle;
}

namespace InstanceTraits
{
    class Rectangle;
}

namespace Classes
{
    class Rectangle;
}

namespace Instances
{
    class Rectangle : public Instances::Object
    {
        friend class InstanceTraits::Rectangle;
        
    public:
        typedef Rectangle SelfType;
        typedef Classes::Rectangle ClassType;
        typedef InstanceTraits::Rectangle TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Rectangle"; }
#endif
    protected:
        Rectangle(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        Value::Number GetX() const { return x; }
        Value::Number GetY() const { return y; }
        Value::Number GetWidth() const { return width; }
        Value::Number GetHeight() const { return height; }
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_height() const { return height; }
        Value::Number get_width() const { return width; }
        Value::Number get_x() const { return x; }
        Value::Number get_y() const { return y; }

        // AS3 API methods.
        enum MethodID {
            mid_bottomGet, 
            mid_bottomSet, 
            mid_bottomRightGet, 
            mid_bottomRightSet, 
            mid_leftGet, 
            mid_leftSet, 
            mid_rightGet, 
            mid_rightSet, 
            mid_sizeGet, 
            mid_sizeSet, 
            mid_topGet, 
            mid_topSet, 
            mid_topLeftGet, 
            mid_topLeftSet, 
            mid_clone, 
            mid_contains, 
            mid_containsPoint, 
            mid_containsRect, 
            mid_equals, 
            mid_inflate, 
            mid_inflatePoint, 
            mid_intersection, 
            mid_intersects, 
            mid_isEmpty, 
            mid_offset, 
            mid_offsetPoint, 
            mid_setEmpty, 
            mid_toString, 
            mid_union_, 
        };
        void bottomGet(Value::Number& result);
        void bottomSet(Value& result, Value::Number value);
        void bottomRightGet(Value& result);
        void bottomRightSet(Value& result, Instances::Point* value);
        void leftGet(Value::Number& result);
        void leftSet(Value& result, Value::Number value);
        void rightGet(Value::Number& result);
        void rightSet(Value& result, Value::Number value);
        void sizeGet(Value& result);
        void sizeSet(Value& result, Instances::Point* value);
        void topGet(Value::Number& result);
        void topSet(Value& result, Value::Number value);
        void topLeftGet(Value& result);
        void topLeftSet(Value& result, Instances::Point* value);
        void clone(Value& result);
        void contains(bool& result, Value::Number x, Value::Number y);
        void containsPoint(bool& result, Instances::Point* point);
        void containsRect(bool& result, Instances::Rectangle* rect);
        void equals(bool& result, Instances::Rectangle* toCompare);
        void inflate(Value& result, Value::Number dx, Value::Number dy);
        void inflatePoint(Value& result, Instances::Point* point);
        void intersection(Value& result, Instances::Rectangle* toIntersect);
        void intersects(bool& result, Instances::Rectangle* toIntersect);
        void isEmpty(bool& result);
        void offset(Value& result, Value::Number dx, Value::Number dy);
        void offsetPoint(Value& result, Instances::Point* point);
        void setEmpty(Value& result);
        void toString(ASString& result);
        void union_(Value& result, Instances::Rectangle* toUnion);

    protected:
        // AS3 API members.
        Value::Number height;
        Value::Number width;
        Value::Number x;
        Value::Number y;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Rectangle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Rectangle"; }
#endif
    public:
        Rectangle(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Rectangle> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 29 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Rectangle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Rectangle"; }
#endif
    public:
        typedef Classes::Rectangle ClassType;

    public:
        Rectangle(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

