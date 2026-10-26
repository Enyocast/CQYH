//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Matrix.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Matrix_H
#define INC_AS3_Obj_Geom_Matrix_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
typedef Scaleform::Render::Matrix2x4<Double> Matrix2DDouble;
typedef Scaleform::Render::Matrix2F          Matrix2DFloat;
namespace Instances
{
    class Point;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Matrix;
}

namespace InstanceTraits
{
    class Matrix;
}

namespace Classes
{
    class Matrix;
}

namespace Instances
{
    class Matrix : public Instances::Object
    {
        friend class InstanceTraits::Matrix;
        
    public:
        typedef Matrix SelfType;
        typedef Classes::Matrix ClassType;
        typedef InstanceTraits::Matrix TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Matrix"; }
#endif
    protected:
        Matrix(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        void SetMatrix(const Matrix2DDouble& m);
        Matrix2DDouble GetMatrix() const;
        Matrix2DFloat  GetMatrixF() const;
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_a() const { return a; }
        Value::Number get_b() const { return b; }
        Value::Number get_c() const { return c; }
        Value::Number get_d() const { return d; }
        Value::Number get_tx() const { return tx; }
        Value::Number get_ty() const { return ty; }

        // AS3 API methods.
        enum MethodID {
            mid_clone, 
            mid_concat, 
            mid_createBox, 
            mid_createGradientBox, 
            mid_deltaTransformPoint, 
            mid_identity, 
            mid_invert, 
            mid_rotate, 
            mid_scale, 
            mid_toString, 
            mid_transformPoint, 
            mid_translate, 
        };
        void clone(Value& result);
        void concat(Value& result, Instances::Matrix* m);
        void createBox(Value& result, Value::Number scaleX, Value::Number scaleY, Value::Number rotation, Value::Number tx, Value::Number ty);
        void createGradientBox(Value& result, Value::Number width, Value::Number height, Value::Number rotation, Value::Number tx, Value::Number ty);
        void deltaTransformPoint(Value& result, Instances::Point* point);
        void identity(Value& result);
        void invert(Value& result);
        void rotate(Value& result, Value::Number angle);
        void scale(Value& result, Value::Number sx, Value::Number sy);
        void toString(ASString& result);
        void transformPoint(Value& result, Instances::Point* point);
        void translate(Value& result, Value::Number dx, Value::Number dy);

    protected:
        // AS3 API members.
        Value::Number a;
        Value::Number b;
        Value::Number c;
        Value::Number d;
        Value::Number tx;
        Value::Number ty;

//##protect##"instance$data"
    public:
        const static float GradientBoxMagicNumber;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Matrix : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Matrix"; }
#endif
    public:
        Matrix(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Matrix> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 6 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 12 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Matrix : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Matrix"; }
#endif
    public:
        typedef Classes::Matrix ClassType;

    public:
        Matrix(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

