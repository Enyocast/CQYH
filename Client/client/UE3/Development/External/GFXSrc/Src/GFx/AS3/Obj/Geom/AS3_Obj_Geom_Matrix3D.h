//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Matrix3D.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Matrix3D_H
#define INC_AS3_Obj_Geom_Matrix3D_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_DisplayObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
    typedef Scaleform::Render::Matrix4x4<Double> Matrix4DDouble;
    namespace Instances
    {
        class Vector_double;
        class Vector3D;
        class Vector_Vector3D;
    }
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Matrix3D;
}

namespace InstanceTraits
{
    class Matrix3D;
}

namespace Classes
{
    class Matrix3D;
}

namespace Instances
{
    class Matrix3D : public Instances::Object
    {
        friend class InstanceTraits::Matrix3D;
        
    public:
        typedef Matrix3D SelfType;
        typedef Classes::Matrix3D ClassType;
        typedef InstanceTraits::Matrix3D TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Matrix3D"; }
#endif
    protected:
        Matrix3D(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        void SetMatrix3D(const Matrix4DDouble& m)   { mat4 = m; }
        const Matrix4DDouble &GetMatrix3D() const   { return mat4; }
        Matrix4DDouble &GetMatrix3D()               { return mat4; }
        Matrix4F  GetMatrix3DF() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_determinantGet, 
            mid_positionGet, 
            mid_positionSet, 
            mid_rawDataGet, 
            mid_rawDataSet, 
            mid_append, 
            mid_appendRotation, 
            mid_appendScale, 
            mid_appendTranslation, 
            mid_clone, 
            mid_decompose, 
            mid_deltaTransformVector, 
            mid_identity, 
            mid_interpolate, 
            mid_interpolateTo, 
            mid_invert, 
            mid_pointAt, 
            mid_prepend, 
            mid_prependRotation, 
            mid_prependScale, 
            mid_prependTranslation, 
            mid_recompose, 
            mid_transformVector, 
            mid_transformVectors, 
            mid_transpose, 
        };
        void determinantGet(Value::Number& result);
        void positionGet(Value& result);
        void positionSet(Value& result, Instances::Vector3D* value);
        void rawDataGet(Value& result);
        void rawDataSet(Value& result, Instances::Vector_double* value);
        void append(Value& result, Instances::Matrix3D* lhs);
        void appendRotation(Value& result, Value::Number degrees, Instances::Vector3D* axis, Instances::Vector3D* pivotPoint);
        void appendScale(Value& result, Value::Number xScale, Value::Number yScale, Value::Number zScale);
        void appendTranslation(Value& result, Value::Number x, Value::Number y, Value::Number z);
        void clone(Value& result);
        void decompose(Value& result, const ASString& orientationStyle);
        void deltaTransformVector(Value& result, Instances::Vector3D* v);
        void identity(Value& result);
        void interpolate(Value& result, Instances::Matrix3D* thisMat, Instances::Matrix3D* toMat, Value::Number percent);
        void interpolateTo(Value& result, Instances::Matrix3D* toMat, Value::Number percent);
        void invert(bool& result);
        void pointAt(Value& result, Instances::Vector3D* pos, Instances::Vector3D* at, Instances::Vector3D* up);
        void prepend(Value& result, Instances::Matrix3D* rhs);
        void prependRotation(Value& result, Value::Number degrees, Instances::Vector3D* axis, Instances::Vector3D* pivotPoint);
        void prependScale(Value& result, Value::Number xScale, Value::Number yScale, Value::Number zScale);
        void prependTranslation(Value& result, Value::Number x, Value::Number y, Value::Number z);
        void recompose(bool& result, Instances::Vector_Vector3D* components, const ASString& orientationStyle);
        void transformVector(Value& result, Instances::Vector3D* v);
        void transformVectors(Value& result, Instances::Vector_double* vin, Instances::Vector_double* vout);
        void transpose(Value& result);

//##protect##"instance$data"
        Matrix4DDouble mat4;    // kept in GFx format, which is transposed from Flash
        GFx::DisplayObject* pDispObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Matrix3D : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Matrix3D"; }
#endif
    public:
        Matrix3D(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Matrix3D> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 25 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Matrix3D : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Matrix3D"; }
#endif
    public:
        typedef Classes::Matrix3D ClassType;

    public:
        Matrix3D(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

