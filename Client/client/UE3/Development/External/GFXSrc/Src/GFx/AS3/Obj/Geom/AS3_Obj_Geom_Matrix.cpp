//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Matrix.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Matrix.h"
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

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createBox, 2, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createBox, 3, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createBox, 4, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createGradientBox, 2, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createGradientBox, 3, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

    template <>
    SF_INLINE
    Value::Number GetMethodDefArg<Instances::Matrix, Instances::Matrix::mid_createGradientBox, 4, Value::Number>(AS3::StringManager&)
    {
        return 0;
    }

} // namespace Impl
typedef ThunkFunc0<Instances::Matrix, Instances::Matrix::mid_clone, Value> TFunc_Instances_Matrix_clone;
typedef ThunkFunc1<Instances::Matrix, Instances::Matrix::mid_concat, Value, Instances::Matrix*> TFunc_Instances_Matrix_concat;
typedef ThunkFunc5<Instances::Matrix, Instances::Matrix::mid_createBox, Value, Value::Number, Value::Number, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix_createBox;
typedef ThunkFunc5<Instances::Matrix, Instances::Matrix::mid_createGradientBox, Value, Value::Number, Value::Number, Value::Number, Value::Number, Value::Number> TFunc_Instances_Matrix_createGradientBox;
typedef ThunkFunc1<Instances::Matrix, Instances::Matrix::mid_deltaTransformPoint, Value, Instances::Point*> TFunc_Instances_Matrix_deltaTransformPoint;
typedef ThunkFunc0<Instances::Matrix, Instances::Matrix::mid_identity, Value> TFunc_Instances_Matrix_identity;
typedef ThunkFunc0<Instances::Matrix, Instances::Matrix::mid_invert, Value> TFunc_Instances_Matrix_invert;
typedef ThunkFunc1<Instances::Matrix, Instances::Matrix::mid_rotate, Value, Value::Number> TFunc_Instances_Matrix_rotate;
typedef ThunkFunc2<Instances::Matrix, Instances::Matrix::mid_scale, Value, Value::Number, Value::Number> TFunc_Instances_Matrix_scale;
typedef ThunkFunc0<Instances::Matrix, Instances::Matrix::mid_toString, ASString> TFunc_Instances_Matrix_toString;
typedef ThunkFunc1<Instances::Matrix, Instances::Matrix::mid_transformPoint, Value, Instances::Point*> TFunc_Instances_Matrix_transformPoint;
typedef ThunkFunc2<Instances::Matrix, Instances::Matrix::mid_translate, Value, Value::Number, Value::Number> TFunc_Instances_Matrix_translate;

template <> const TFunc_Instances_Matrix_clone::TMethod TFunc_Instances_Matrix_clone::Method = &Instances::Matrix::clone;
template <> const TFunc_Instances_Matrix_concat::TMethod TFunc_Instances_Matrix_concat::Method = &Instances::Matrix::concat;
template <> const TFunc_Instances_Matrix_createBox::TMethod TFunc_Instances_Matrix_createBox::Method = &Instances::Matrix::createBox;
template <> const TFunc_Instances_Matrix_createGradientBox::TMethod TFunc_Instances_Matrix_createGradientBox::Method = &Instances::Matrix::createGradientBox;
template <> const TFunc_Instances_Matrix_deltaTransformPoint::TMethod TFunc_Instances_Matrix_deltaTransformPoint::Method = &Instances::Matrix::deltaTransformPoint;
template <> const TFunc_Instances_Matrix_identity::TMethod TFunc_Instances_Matrix_identity::Method = &Instances::Matrix::identity;
template <> const TFunc_Instances_Matrix_invert::TMethod TFunc_Instances_Matrix_invert::Method = &Instances::Matrix::invert;
template <> const TFunc_Instances_Matrix_rotate::TMethod TFunc_Instances_Matrix_rotate::Method = &Instances::Matrix::rotate;
template <> const TFunc_Instances_Matrix_scale::TMethod TFunc_Instances_Matrix_scale::Method = &Instances::Matrix::scale;
template <> const TFunc_Instances_Matrix_toString::TMethod TFunc_Instances_Matrix_toString::Method = &Instances::Matrix::toString;
template <> const TFunc_Instances_Matrix_transformPoint::TMethod TFunc_Instances_Matrix_transformPoint::Method = &Instances::Matrix::transformPoint;
template <> const TFunc_Instances_Matrix_translate::TMethod TFunc_Instances_Matrix_translate::Method = &Instances::Matrix::translate;

namespace Instances
{
    Matrix::Matrix(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , a()
    , b()
    , c()
    , d()
    , tx()
    , ty()
//##protect##"instance::Matrix::Matrix()$data"
//##protect##"instance::Matrix::Matrix()$data"
    {
//##protect##"instance::Matrix::Matrix()$code"
//##protect##"instance::Matrix::Matrix()$code"
    }

    void Matrix::clone(Value& result)
    {
//##protect##"instance::Matrix::clone()"
		Value args[] = {Value(a), Value(b), Value(c), Value(d), Value(tx), Value(ty)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Matrix", 6, args).DoNotCheck();
//##protect##"instance::Matrix::clone()"
    }
    void Matrix::concat(Value& result, Instances::Matrix* m)
    {
//##protect##"instance::Matrix::concat()"
		if (!m)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		result.SetUndefined();
		Matrix2DDouble m2d = GetMatrix();
		m2d.Append(m->GetMatrix());
		SetMatrix(m2d);
//##protect##"instance::Matrix::concat()"
    }
    void Matrix::createBox(Value& result, Value::Number scaleX, Value::Number scaleY, Value::Number rotation, Value::Number tx, Value::Number ty)
    {
//##protect##"instance::Matrix::createBox()"
        Matrix2DDouble m = GetMatrix();
		m.AppendRotation(rotation);
		m.AppendScaling(scaleX, scaleY);
		m.AppendTranslation(tx, ty);
		SetMatrix(m);
		result.SetUndefined();
//##protect##"instance::Matrix::createBox()"
    }
    void Matrix::createGradientBox(Value& result, Value::Number width, Value::Number height, Value::Number rotation, Value::Number tx, Value::Number ty)
    {
//##protect##"instance::Matrix::createGradientBox()"
        Matrix2DDouble m;
        float w = float(width);
        float h = float(height);
        float r = float(rotation);
        float txn = (w * 0.5f) + float(tx);
        float tyn = (h * 0.5f) + float(ty);

        w *= GradientBoxMagicNumber; 
        h *= GradientBoxMagicNumber;
		result.SetUndefined();
        m.AppendRotation(r);
        m.AppendScaling(w, h);
        m.AppendTranslation(txn, tyn);

        SetMatrix(m);
//##protect##"instance::Matrix::createGradientBox()"
    }
    void Matrix::deltaTransformPoint(Value& result, Instances::Point* point)
    {
//##protect##"instance::Matrix::deltaTransformPoint()"
		// The difference between this function and transformPoint is that here we don't add the translation
		if (!point)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
		}
		Value::Number px = point->GetX();
		Value::Number py = point->GetY();

		Value args[] = {Value(a*px + c*py), Value(b*px + d*py)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Matrix::deltaTransformPoint()"
    }
    void Matrix::identity(Value& result)
    {
//##protect##"instance::Matrix::identity()"
		SetMatrix(Matrix2DDouble());
		result.SetUndefined();
//##protect##"instance::Matrix::identity()"
    }
    void Matrix::invert(Value& result)
    {
//##protect##"instance::Matrix::invert()"
		result.SetUndefined();
		Matrix2DDouble m(a,c,tx,b,d,ty);
		m.Invert();
		SetMatrix(m);
//##protect##"instance::Matrix::invert()"
    }
    void Matrix::rotate(Value& result, Value::Number angle)
    {
//##protect##"instance::Matrix::rotate()"
		result.SetUndefined();
		Matrix2DDouble m(a,c,tx,b,d,ty);
	    m.AppendRotation(angle);
		SetMatrix(m);
//##protect##"instance::Matrix::rotate()"
    }
    void Matrix::scale(Value& result, Value::Number sx, Value::Number sy)
    {
//##protect##"instance::Matrix::scale()"
		result.SetUndefined();
		Matrix2DDouble m(a,c,tx,b,d,ty);
		m.AppendScaling(sx, sy);
		SetMatrix(m);
//##protect##"instance::Matrix::scale()"
    }
    void Matrix::toString(ASString& result)
    {
//##protect##"instance::Matrix::toString()"
		result += GetStringManager().CreateConstString("(a=") + GetVM().AsString(Value(a)) + 
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("b=") + 
			GetVM().AsString(Value(b)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("c=") + 
			GetVM().AsString(Value(c)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("d=") + 
			GetVM().AsString(Value(d)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("tx=") + 
			GetVM().AsString(Value(tx)) +
			GetStringManager().CreateConstString(", ") + 
			GetStringManager().CreateConstString("ty=") + 
			GetVM().AsString(Value(ty)) +
			GetStringManager().CreateConstString(")");
//##protect##"instance::Matrix::toString()"
    }
    void Matrix::transformPoint(Value& result, Instances::Point* point)
    {
//##protect##"instance::Matrix::transformPoint()"
		if (!point)
		{
            return (GetVM().ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, GetVM())));
			
		}
		Value::Number px = point->GetX();
		Value::Number py = point->GetY();

		Value args[] = {Value(a*px + c*py + tx), Value(b*px + d*py + ty)};
		GetVM().ConstructBuiltinValue(result, "flash.geom.Point", 2, args).DoNotCheck();
//##protect##"instance::Matrix::transformPoint()"
    }
    void Matrix::translate(Value& result, Value::Number dx, Value::Number dy)
    {
//##protect##"instance::Matrix::translate()"
		result.SetUndefined();
		Matrix2DDouble m(a,c,tx,b,d,ty);
		m.AppendTranslation(dx, dy);
		SetMatrix(m);
//##protect##"instance::Matrix::translate()"
    }

//##protect##"instance$methods"
    // Some magic number used for scaling coefficients in CreateGradientBox.
    // This number was deduced empirically; in reality it may be more complex
    // and depend on something else
    const float Matrix::GradientBoxMagicNumber = 1.0f/1638.4f;

    void Matrix::SetMatrix(const Matrix2DDouble& m)
    {
        a = m.Sx();
        b = m.Shy();
        c = m.Shx();
        d = m.Sy();
        tx = m.Tx();
        ty = m.Ty();
    }

	Matrix2DDouble Matrix::GetMatrix() const
	{
		Matrix2DDouble m;

		m.Sx() = a;
		m.Shy() = b;
		m.Shx() = c;
		m.Sy() = d;
		m.Tx() = tx;
		m.Ty() = ty;

		return m;
	}

    Matrix2DFloat Matrix::GetMatrixF() const
    {
        Matrix2DFloat m;

        m.Sx() = float(a);
        m.Shy() = float(b);
        m.Shx() = float(c);
        m.Sy() = float(d);
        m.Tx() = float(tx);
        m.Ty() = float(ty);

        return m;
    }

	void Matrix::AS3Constructor(unsigned argc, const Value* argv)
	{
		// Initialize to default values
		a = 1; b = 0; c = 0; d = 1; tx = 0; ty = 0;
		if (argc > 0)
		{
			// According to doc, x will not be modified if there is an exception
			if (!argv[0].Convert2Number(a))
			{
				return;
			}
			if (argc > 1)
			{
				if (!argv[1].Convert2Number(b))
				{
					return;
				}
				if (argc > 2)
				{
					if (!argv[2].Convert2Number(c))
					{
						return;
					}
					if (argc > 3)
					{
						if (!argv[3].Convert2Number(d))
						{
							return;
						}
						if (argc > 4)
						{
							if (!argv[4].Convert2Number(tx))
							{
								return;
							}
							if (argc > 5)
							{
								if (!argv[5].Convert2Number(ty))
								{
									return;
								}
							}
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
    const ThunkInfo Matrix::ti[Matrix::ThunkInfoNum] = {
        {TFunc_Instances_Matrix_clone::Func, &MatrixCI, "clone", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Matrix_concat::Func, NULL, "concat", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Matrix_createBox::Func, NULL, "createBox", NULL, CT_Method, 2, 5},
        {TFunc_Instances_Matrix_createGradientBox::Func, NULL, "createGradientBox", NULL, CT_Method, 2, 5},
        {TFunc_Instances_Matrix_deltaTransformPoint::Func, &PointCI, "deltaTransformPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Matrix_identity::Func, NULL, "identity", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Matrix_invert::Func, NULL, "invert", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Matrix_rotate::Func, NULL, "rotate", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Matrix_scale::Func, NULL, "scale", NULL, CT_Method, 2, 2},
        {TFunc_Instances_Matrix_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_Matrix_transformPoint::Func, &PointCI, "transformPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_Matrix_translate::Func, NULL, "translate", NULL, CT_Method, 2, 2},
    };
    const MemberInfo Matrix::mi[Matrix::MemberInfoNum] = {
        {"a", OFFSETOF(Instances::Matrix, a), SlotInfo::BT_Number, 0},
        {"b", OFFSETOF(Instances::Matrix, b), SlotInfo::BT_Number, 0},
        {"c", OFFSETOF(Instances::Matrix, c), SlotInfo::BT_Number, 0},
        {"d", OFFSETOF(Instances::Matrix, d), SlotInfo::BT_Number, 0},
        {"tx", OFFSETOF(Instances::Matrix, tx), SlotInfo::BT_Number, 0},
        {"ty", OFFSETOF(Instances::Matrix, ty), SlotInfo::BT_Number, 0},
    };


    Matrix::Matrix(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Matrix::Matrix()"
//##protect##"InstanceTraits::Matrix::Matrix()"
        SetMemSize(sizeof(Instances::Matrix));

    }

    Pickable<Instances::Matrix> Matrix::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Matrix>(new(t.Alloc()) Instances::Matrix(t));
    }

    void Matrix::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Matrix::Matrix(VM& vm)
    : Traits(vm, MatrixCI)
    {
//##protect##"ClassTraits::Matrix::Matrix()"
//##protect##"ClassTraits::Matrix::Matrix()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Matrix(vm, MatrixCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Matrix::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Matrix(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MatrixCI = {
    ClassInfo::CompileTime,
    "Matrix", "flash.geom", &ObjectCI,
    ClassTraits::Matrix::MakeClassTraits,
    0,
    0,
    InstanceTraits::Matrix::ThunkInfoNum,
    InstanceTraits::Matrix::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::Matrix::ti,
    InstanceTraits::Matrix::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

