//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Transform.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy, Ankur Mohan

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_Transform.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Geom_ColorTransform.h"
#include "../../AS3_MovieRoot.h"
#include "AS3_Obj_Geom_Matrix.h"
#include "AS3_Obj_Geom_Matrix3D.h"
#include "AS3_Obj_Geom_PerspectiveProjection.h"
#include "AS3_Obj_Geom_Rectangle.h"
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
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_colorTransformGet, Value> TFunc_Instances_Transform_colorTransformGet;
typedef ThunkFunc1<Instances::Transform, Instances::Transform::mid_colorTransformSet, Value, Instances::ColorTransform*> TFunc_Instances_Transform_colorTransformSet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_concatenatedColorTransformGet, Value> TFunc_Instances_Transform_concatenatedColorTransformGet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_concatenatedMatrixGet, Value> TFunc_Instances_Transform_concatenatedMatrixGet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_matrixGet, Value> TFunc_Instances_Transform_matrixGet;
typedef ThunkFunc1<Instances::Transform, Instances::Transform::mid_matrixSet, Value, Instances::Matrix*> TFunc_Instances_Transform_matrixSet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_matrix3DGet, Value> TFunc_Instances_Transform_matrix3DGet;
typedef ThunkFunc1<Instances::Transform, Instances::Transform::mid_matrix3DSet, Value, Instances::Matrix3D*> TFunc_Instances_Transform_matrix3DSet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_perspectiveProjectionGet, Value> TFunc_Instances_Transform_perspectiveProjectionGet;
typedef ThunkFunc1<Instances::Transform, Instances::Transform::mid_perspectiveProjectionSet, Value, Instances::PerspectiveProjection*> TFunc_Instances_Transform_perspectiveProjectionSet;
typedef ThunkFunc0<Instances::Transform, Instances::Transform::mid_pixelBoundsGet, Value> TFunc_Instances_Transform_pixelBoundsGet;
typedef ThunkFunc1<Instances::Transform, Instances::Transform::mid_getRelativeMatrix3D, Value, Instances::DisplayObject*> TFunc_Instances_Transform_getRelativeMatrix3D;

template <> const TFunc_Instances_Transform_colorTransformGet::TMethod TFunc_Instances_Transform_colorTransformGet::Method = &Instances::Transform::colorTransformGet;
template <> const TFunc_Instances_Transform_colorTransformSet::TMethod TFunc_Instances_Transform_colorTransformSet::Method = &Instances::Transform::colorTransformSet;
template <> const TFunc_Instances_Transform_concatenatedColorTransformGet::TMethod TFunc_Instances_Transform_concatenatedColorTransformGet::Method = &Instances::Transform::concatenatedColorTransformGet;
template <> const TFunc_Instances_Transform_concatenatedMatrixGet::TMethod TFunc_Instances_Transform_concatenatedMatrixGet::Method = &Instances::Transform::concatenatedMatrixGet;
template <> const TFunc_Instances_Transform_matrixGet::TMethod TFunc_Instances_Transform_matrixGet::Method = &Instances::Transform::matrixGet;
template <> const TFunc_Instances_Transform_matrixSet::TMethod TFunc_Instances_Transform_matrixSet::Method = &Instances::Transform::matrixSet;
template <> const TFunc_Instances_Transform_matrix3DGet::TMethod TFunc_Instances_Transform_matrix3DGet::Method = &Instances::Transform::matrix3DGet;
template <> const TFunc_Instances_Transform_matrix3DSet::TMethod TFunc_Instances_Transform_matrix3DSet::Method = &Instances::Transform::matrix3DSet;
template <> const TFunc_Instances_Transform_perspectiveProjectionGet::TMethod TFunc_Instances_Transform_perspectiveProjectionGet::Method = &Instances::Transform::perspectiveProjectionGet;
template <> const TFunc_Instances_Transform_perspectiveProjectionSet::TMethod TFunc_Instances_Transform_perspectiveProjectionSet::Method = &Instances::Transform::perspectiveProjectionSet;
template <> const TFunc_Instances_Transform_pixelBoundsGet::TMethod TFunc_Instances_Transform_pixelBoundsGet::Method = &Instances::Transform::pixelBoundsGet;
template <> const TFunc_Instances_Transform_getRelativeMatrix3D::TMethod TFunc_Instances_Transform_getRelativeMatrix3D::Method = &Instances::Transform::getRelativeMatrix3D;

namespace Instances
{
    Transform::Transform(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::Transform::Transform()$data"
        ,pDispObj(NULL)
//##protect##"instance::Transform::Transform()$data"
    {
//##protect##"instance::Transform::Transform()$code"
//##protect##"instance::Transform::Transform()$code"
    }

    void Transform::colorTransformGet(Value& result)
    {
//##protect##"instance::Transform::colorTransformGet()"
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		SPtr<ColorTransform> pcolorTransform;
		Value argv[8];
        const Cxform& cx = pDispObj->GetCxform();
		argv[0].SetNumber(cx.M[0][0]);
		argv[1].SetNumber(cx.M[0][1]);
		argv[2].SetNumber(cx.M[0][2]);
		argv[3].SetNumber(cx.M[0][3]);
		argv[4].SetNumber(cx.M[1][0] * 255);
		argv[5].SetNumber(cx.M[1][1] * 255);
		argv[6].SetNumber(cx.M[1][2] * 255);
		argv[7].SetNumber(cx.M[1][3] * 255);

		if (asvm.ConstructInstance(pcolorTransform, asvm.ColorTransformClass, 8, argv))
		{
			
		}
		result = pcolorTransform;
//##protect##"instance::Transform::colorTransformGet()"
    }
    void Transform::colorTransformSet(Value& result, Instances::ColorTransform* value)
    {
//##protect##"instance::Transform::colorTransformSet()"
		result.SetUndefined();
        if (pDispObj)
        {
            if (value)
            {
                Render::Cxform cxform;

                cxform.M[0][0] = (float)value->get_redMultiplier();
                cxform.M[0][1] = (float)value->get_greenMultiplier();
                cxform.M[0][2] = (float)value->get_blueMultiplier();
                cxform.M[0][3] = (float)value->get_alphaMultiplier();
                cxform.M[1][0] = (float)value->get_redOffset();
                cxform.M[1][1] = (float)value->get_greenOffset();
                cxform.M[1][2] = (float)value->get_blueOffset();
                cxform.M[1][3] = (float)value->get_alphaOffset();
                cxform.Normalize();
                pDispObj->SetCxform(cxform);
            }
            pDispObj->SetAcceptAnimMoves(false);
        }
//##protect##"instance::Transform::colorTransformSet()"
    }
    void Transform::concatenatedColorTransformGet(Value& result)
    {
//##protect##"instance::Transform::concatenatedColorTransformGet()"
		SPtr<ColorTransform> pcolorTransform;
		Render::Cxform cform;
		Value argv[8];

		ASVM& asvm = static_cast<ASVM&>(GetVM());
		Scaleform::GFx::DisplayObject* currObject = pDispObj;
		
		while (currObject != NULL)
		{
			cform.Append(currObject->GetCxform());
			currObject = currObject->GetParent();
		}
		
		argv[0].SetNumber(cform.M[0][0]);
		argv[1].SetNumber(cform.M[0][1]);
		argv[2].SetNumber(cform.M[0][2]);
		argv[3].SetNumber(cform.M[0][3]);
		argv[4].SetNumber(cform.M[1][0] * 255);
		argv[5].SetNumber(cform.M[1][1] * 255);
		argv[6].SetNumber(cform.M[1][2] * 255);
		argv[7].SetNumber(cform.M[1][3] * 255);

		if (asvm.ConstructInstance(pcolorTransform, asvm.ColorTransformClass, 8, argv))
		{
	
		}

		result = pcolorTransform;
//##protect##"instance::Transform::concatenatedColorTransformGet()"
    }
    void Transform::concatenatedMatrixGet(Value& result)
    {
//##protect##"instance::Transform::concatenatedMatrixGet()"
		SPtr<Matrix> pmatrix;
		GFx::DisplayObjectBase::Matrix gmatrix;
		Value argv[6];

		ASVM& asvm = static_cast<ASVM&>(GetVM());
		Scaleform::GFx::DisplayObject* currObject = pDispObj;

		while (currObject != NULL)
		{
			gmatrix.Append(currObject->GetMatrix());
			currObject = currObject->GetParent();
		}

		argv[0].SetNumber(gmatrix.Sx());
		argv[1].SetNumber(gmatrix.Shy());
		argv[2].SetNumber(gmatrix.Shx());
		argv[3].SetNumber(gmatrix.Sy());
		argv[4].SetNumber(TwipsToPixels(gmatrix.Tx()));
		argv[5].SetNumber(TwipsToPixels(gmatrix.Ty()));

		if (asvm.ConstructInstance(pmatrix, asvm.MatrixClass, 6, argv))
		{

		}
		result = pmatrix;
//##protect##"instance::Transform::concatenatedMatrixGet()"
    }
    void Transform::matrixGet(Value& result)
    {
//##protect##"instance::Transform::matrixGet()"
		ASVM& asvm = static_cast<ASVM&>(GetVM());
		SPtr<Matrix> pmatrix;
		Value argv[6];

		Scaleform::GFx::DisplayObjectBase::Matrix mat = pDispObj->GetMatrix(); 
		
		argv[0].SetNumber(mat.Sx());
		argv[1].SetNumber(mat.Shy());
		argv[2].SetNumber(mat.Shx());
		argv[3].SetNumber(mat.Sy());
		argv[4].SetNumber(TwipsToPixels(mat.Tx()));
		argv[5].SetNumber(TwipsToPixels(mat.Ty()));

		if (asvm.ConstructInstance(pmatrix, asvm.MatrixClass, 6, argv))
		{

		}
		result = pmatrix;
//##protect##"instance::Transform::matrixGet()"
    }
    void Transform::matrixSet(Value& result, Instances::Matrix* value)
    {
//##protect##"instance::Transform::matrixSet()"
		result.SetUndefined();
		if (pDispObj)
		{
            if (value)
            {
                Scaleform::GFx::DisplayObjectBase::Matrix mat;
                float a = (float)value->get_a();
                float b = (float)value->get_b();
                float c = (float)value->get_c();
                float d = (float)value->get_d();
                float tx = PixelsToTwips((float)value->get_tx());
                float ty = PixelsToTwips((float)value->get_ty());

                mat.SetMatrix(a,c,tx,b,d,ty);
                pDispObj->SetMatrix(mat);

                Scaleform::GFx::DisplayObjectBase::GeomDataType geomData;
                pDispObj->GetGeomData(geomData);
                geomData.X          = (int)mat.Tx();
                geomData.Y          = (int)mat.Ty();
                geomData.Rotation   = mat.GetRotationDouble()*180/SF_MATH_PI;
                geomData.XScale     = mat.GetXScaleDouble()*100;
                geomData.YScale     = mat.GetYScaleDouble()*100;
                pDispObj->SetGeomData(geomData);
            }
            pDispObj->SetAcceptAnimMoves(false);
		}
//##protect##"instance::Transform::matrixSet()"
    }
    void Transform::matrix3DGet(Value& result)
    {
//##protect##"instance::Transform::matrix3DGet()"
		if (pDispObj)
		{
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Matrix3D> pmatrix3D;
        Value argv[16];

        Matrix3F mat = pDispObj->GetMatrix3D(); 
        Matrix4F mat4(mat);

        int i;
        for(i=0;i<16;i++)
            argv[i].SetNumber((Double)mat4[i]);     // matrix data should be provided in GFx format 
		if (asvm.ConstructInstance(pmatrix3D, asvm.Matrix3DClass, 16, argv))
        {
            pmatrix3D->pDispObj = pDispObj;
        }
        result = pmatrix3D;
		}
//##protect##"instance::Transform::matrix3DGet()"
    }
    void Transform::matrix3DSet(Value& result, Instances::Matrix3D* value)
    {
//##protect##"instance::Transform::matrix3DSet()"
        result.SetUndefined();
        if (pDispObj)
        {
            if (value)
            {
                Matrix4F mat4 = value->GetMatrix3DF();
                Matrix3F mat(mat4);

                mat.Tx() = PixelsToTwips(mat.Tx());
                mat.Ty() = PixelsToTwips(mat.Ty());
                mat.Tz() = PixelsToTwips(mat.Tz());
                pDispObj->SetMatrix3D(mat);

                Scaleform::GFx::DisplayObjectBase::GeomDataType geomData;
                pDispObj->GetGeomData(geomData);
                geomData.X          = (int)mat.Tx();
                geomData.Y          = (int)mat.Ty();
                geomData.Z          = (int)mat.Tz();

                float ex, ey, ez;
                mat.GetRotation(&ex, &ey, &ez);

                geomData.Rotation   = SF_RADTODEG(ez);
                geomData.XRotation   = SF_RADTODEG(ex);
                geomData.YRotation   = SF_RADTODEG(ey);
                geomData.XScale     = mat.GetXScale()*100;
                geomData.YScale     = mat.GetYScale()*100;
                geomData.ZScale     = mat.GetZScale()*100;
                pDispObj->SetGeomData(geomData);
            }
            else if (pDispObj->Is3D())
                pDispObj->Clear3D();    // Setting matrix3D to NULL in AS clears all 3D from the object and it's children
            pDispObj->SetAcceptAnimMoves(false);
        }
//##protect##"instance::Transform::matrix3DSet()"
    }
    void Transform::perspectiveProjectionGet(Value& result)
    {
//##protect##"instance::Transform::perspectiveProjectionGet()"
		if (pDispObj && pDispObj->GetPerspectiveDataPtr())
		{
			ASVM& asvm = static_cast<ASVM&>(GetVM());
			SPtr<PerspectiveProjection> pPerspectiveProjection;
			Value argv[4];	// fov, focalLength, projCtrX, projCtrY

            bool bIsRoot = (asvm.GetMovieRoot()->GetRootMovie() == pDispObj);

            argv[0].SetNumber(pDispObj->GetFOV());
			argv[1].SetNumber(TwipsToPixels(pDispObj->GetFocalLength()));

            PointF ctr = (pDispObj->GetParent()) ? pDispObj->GetParent()->GlobalToLocal(pDispObj->GetProjectionCenter()) :
                pDispObj->GetProjectionCenter();
            if (bIsRoot && ctr.x==0 && ctr.y==0)
                ctr = asvm.GetMovieImpl()->GetVisibleFrameRectInTwips().Center();
            argv[2].SetNumber(TwipsToPixels(ctr.x));
            argv[3].SetNumber(TwipsToPixels(ctr.y));
			
            if (asvm.ConstructInstance(pPerspectiveProjection, asvm.PerspectiveProjectionClass, 4, argv))
			{
                pPerspectiveProjection->pDispObj = pDispObj;
                if (bIsRoot)
                    pPerspectiveProjection->SetFocalLength(pPerspectiveProjection->CalculateFocalLength(asvm.GetMovieImpl()->GetVisibleFrameRect().Width()));
			}
			result = pPerspectiveProjection;
		}
//##protect##"instance::Transform::perspectiveProjectionGet()"
    }
    void Transform::perspectiveProjectionSet(Value& result, Instances::PerspectiveProjection* value)
    {
//##protect##"instance::Transform::perspectiveProjectionSet()"
        result.SetUndefined();
        if (value && pDispObj)
        {
            ASVM& asvm = static_cast<ASVM&>(GetVM());

            // always use actual stage width for focalLength calc (whether root or stage not)
            float stageWidth = asvm.GetMovieImpl()->GetVisibleFrameRect().Width();
            value->SetFocalLength(value->CalculateFocalLength(stageWidth));

            value->pDispObj = pDispObj;

            pDispObj->SetFocalLength((float)PixelsToTwips(value->GetFocalLength()));
            pDispObj->SetFOV((float)value->GetFOV());
            
            PointF ctr = (pDispObj->GetParent()) ? pDispObj->GetParent()->LocalToGlobal(PixelsToTwips(value->GetProjectionCenter())) :
                PixelsToTwips(value->GetProjectionCenter());
            pDispObj->SetProjectionCenter(ctr);
        }
//##protect##"instance::Transform::perspectiveProjectionSet()"
    }
    void Transform::pixelBoundsGet(Value& result)
    {
//##protect##"instance::Transform::pixelBoundsGet()"
        if (pDispObj)
		{
			ASVM& asvm = static_cast<ASVM&>(GetVM());
			SPtr<Rectangle> prectangle;
			Value argv[4];

			Render::RectF bounds = pDispObj->GetBounds(pDispObj->GetMatrix());

			argv[0].SetNumber(Alg::IRound(TwipsToPixels(bounds.TopLeft().x)));
			argv[1].SetNumber(Alg::IRound(TwipsToPixels(bounds.TopLeft().y)));
			argv[2].SetNumber(Alg::IRound(TwipsToPixels(bounds.Width())));
			argv[3].SetNumber(Alg::IRound(TwipsToPixels(bounds.Height())));

			if (asvm.ConstructInstance(prectangle, asvm.RectangleClass, 4, argv))
			{

			}
			result = prectangle;
		}
//##protect##"instance::Transform::pixelBoundsGet()"
    }
    void Transform::getRelativeMatrix3D(Value& result, Instances::DisplayObject* relativeTo)
    {
//##protect##"instance::Transform::getRelativeMatrix3D()"
    // Returns a Matrix3D object, which can transform the space of a specified display object in relation to the current 
    // display object's space. You can use the getRelativeMatrix3D() method to move one three-dimensional display object 
    // relative to another three-dimensional display object.

        if (!relativeTo)
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("relativeTo")));

        // make sure relativeTo's stage obj exists
        if (!relativeTo->pDispObj)
            relativeTo->CreateStageObject();
        SF_ASSERT(relativeTo->pDispObj);

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<Matrix3D> pmatrix3D;
        Value argv[16];

        // Get the matrix of the current display object
        Matrix3F matCur = pDispObj->GetWorldMatrix3D();

        // Get the matrix of the relativeTo display object
        Matrix3F matRelTo = relativeTo->pDispObj->GetWorldMatrix3D();

        // Compute A Matrix3D object that can be used to transform the space from the relativeTo display object 
        // to the current display object space
        Matrix3F relMat = matRelTo.GetInverse() * matCur;   // apply matCur then matRelTo inverse

        // create return result
        Matrix4F mat4(relMat);

        int i;
        for(i=0;i<16;i++)
            argv[i].SetNumber((Double)mat4[i]);

        if (asvm.ConstructInstance(pmatrix3D, asvm.Matrix3DClass, 16, argv))
        {
            pmatrix3D->pDispObj = pDispObj;
        }
        result = pmatrix3D;

//##protect##"instance::Transform::getRelativeMatrix3D()"
    }

//##protect##"instance$methods"
	void Transform::AS3Constructor(unsigned argc, const Value* argv)
	{
		SF_UNUSED2(argc, argv);
	}
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo Transform::ti[Transform::ThunkInfoNum] = {
        {TFunc_Instances_Transform_colorTransformGet::Func, &ColorTransformCI, "colorTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_colorTransformSet::Func, NULL, "colorTransform", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Transform_concatenatedColorTransformGet::Func, &ColorTransformCI, "concatenatedColorTransform", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_concatenatedMatrixGet::Func, &MatrixCI, "concatenatedMatrix", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_matrixGet::Func, &MatrixCI, "matrix", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_matrixSet::Func, NULL, "matrix", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Transform_matrix3DGet::Func, &Matrix3DCI, "matrix3D", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_matrix3DSet::Func, NULL, "matrix3D", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Transform_perspectiveProjectionGet::Func, &PerspectiveProjectionCI, "perspectiveProjection", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_perspectiveProjectionSet::Func, NULL, "perspectiveProjection", NULL, CT_Set, 1, 1},
        {TFunc_Instances_Transform_pixelBoundsGet::Func, &RectangleCI, "pixelBounds", NULL, CT_Get, 0, 0},
        {TFunc_Instances_Transform_getRelativeMatrix3D::Func, &Matrix3DCI, "getRelativeMatrix3D", NULL, CT_Method, 1, 1},
    };

    Transform::Transform(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::Transform::Transform()"
//##protect##"InstanceTraits::Transform::Transform()"
        SetMemSize(sizeof(Instances::Transform));

    }

    Pickable<Instances::Transform> Transform::MakeInstance(Traits& t)
    {
        return Pickable<Instances::Transform>(new(t.Alloc()) Instances::Transform(t));
    }

    void Transform::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    Transform::Transform(VM& vm)
    : Traits(vm, TransformCI)
    {
//##protect##"ClassTraits::Transform::Transform()"
//##protect##"ClassTraits::Transform::Transform()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Transform(vm, TransformCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Transform::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Transform(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo TransformCI = {
    ClassInfo::CompileTime,
    "Transform", "flash.geom", &ObjectCI,
    ClassTraits::Transform::MakeClassTraits,
    0,
    0,
    InstanceTraits::Transform::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::Transform::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

