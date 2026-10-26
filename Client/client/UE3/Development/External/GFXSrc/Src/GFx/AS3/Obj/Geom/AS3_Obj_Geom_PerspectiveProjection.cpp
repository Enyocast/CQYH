//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_PerspectiveProjection.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Geom_PerspectiveProjection.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Geom_Point.h"
#include "GFx/GFx_PlayerImpl.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Matrix3D;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_projectionCenterGet, Value> TFunc_Instances_PerspectiveProjection_projectionCenterGet;
typedef ThunkFunc1<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_projectionCenterSet, Value, Instances::Point*> TFunc_Instances_PerspectiveProjection_projectionCenterSet;
typedef ThunkFunc0<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_focalLengthGet, Value::Number> TFunc_Instances_PerspectiveProjection_focalLengthGet;
typedef ThunkFunc1<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_focalLengthSet, Value, Value::Number> TFunc_Instances_PerspectiveProjection_focalLengthSet;
typedef ThunkFunc0<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_fieldOfViewGet, Value::Number> TFunc_Instances_PerspectiveProjection_fieldOfViewGet;
typedef ThunkFunc1<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_fieldOfViewSet, Value, Value::Number> TFunc_Instances_PerspectiveProjection_fieldOfViewSet;
typedef ThunkFunc0<Instances::PerspectiveProjection, Instances::PerspectiveProjection::mid_toMatrix3D, Value> TFunc_Instances_PerspectiveProjection_toMatrix3D;

template <> const TFunc_Instances_PerspectiveProjection_projectionCenterGet::TMethod TFunc_Instances_PerspectiveProjection_projectionCenterGet::Method = &Instances::PerspectiveProjection::projectionCenterGet;
template <> const TFunc_Instances_PerspectiveProjection_projectionCenterSet::TMethod TFunc_Instances_PerspectiveProjection_projectionCenterSet::Method = &Instances::PerspectiveProjection::projectionCenterSet;
template <> const TFunc_Instances_PerspectiveProjection_focalLengthGet::TMethod TFunc_Instances_PerspectiveProjection_focalLengthGet::Method = &Instances::PerspectiveProjection::focalLengthGet;
template <> const TFunc_Instances_PerspectiveProjection_focalLengthSet::TMethod TFunc_Instances_PerspectiveProjection_focalLengthSet::Method = &Instances::PerspectiveProjection::focalLengthSet;
template <> const TFunc_Instances_PerspectiveProjection_fieldOfViewGet::TMethod TFunc_Instances_PerspectiveProjection_fieldOfViewGet::Method = &Instances::PerspectiveProjection::fieldOfViewGet;
template <> const TFunc_Instances_PerspectiveProjection_fieldOfViewSet::TMethod TFunc_Instances_PerspectiveProjection_fieldOfViewSet::Method = &Instances::PerspectiveProjection::fieldOfViewSet;
template <> const TFunc_Instances_PerspectiveProjection_toMatrix3D::TMethod TFunc_Instances_PerspectiveProjection_toMatrix3D::Method = &Instances::PerspectiveProjection::toMatrix3D;

namespace Instances
{
    PerspectiveProjection::PerspectiveProjection(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$data"
    , focalLength(0)
    , fieldOfView(0)
    , pDispObj(NULL)
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$data"
    {
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$code"
        
        // set AS3 defaults
        projectionCenter.x = DEFAULT_STAGE_WIDTH/2.f;
        projectionCenter.y = DEFAULT_STAGE_WIDTH/2.f;

        fieldOfView = DEFAULT_FLASH_FOV;
        focalLength = CalculateFocalLength(DEFAULT_STAGE_WIDTH);
//##protect##"instance::PerspectiveProjection::PerspectiveProjection()$code"
    }

    void PerspectiveProjection::projectionCenterGet(Value& result)
    {
//##protect##"instance::PerspectiveProjection::projectionCenterGet()"
        Value params[] = { Value(projectionCenter.x), Value(projectionCenter.y) };
        static_cast<ASVM&>(GetVM()).PointClass->Construct(result, 2, params, true);
//##protect##"instance::PerspectiveProjection::projectionCenterGet()"
    }
    void PerspectiveProjection::projectionCenterSet(Value& result, Instances::Point* value)
    {
//##protect##"instance::PerspectiveProjection::projectionCenterSet()"
    result.SetUndefined();
    projectionCenter.x = (float)value->get_x();
    projectionCenter.y = (float)value->get_y();
    if (pDispObj)
        pDispObj->SetProjectionCenter(PixelsToTwips(projectionCenter));
//##protect##"instance::PerspectiveProjection::projectionCenterSet()"
    }
    void PerspectiveProjection::focalLengthGet(Value::Number& result)
    {
//##protect##"instance::PerspectiveProjection::focalLengthGet()"
        result = focalLength;
//##protect##"instance::PerspectiveProjection::focalLengthGet()"
    }
    void PerspectiveProjection::focalLengthSet(Value& result, Value::Number value)
    {
//##protect##"instance::PerspectiveProjection::focalLengthSet()"
        result.SetUndefined();
        focalLength = (float)value;
        if (pDispObj)
            pDispObj->SetFocalLength(PixelsToTwips(focalLength));
//##protect##"instance::PerspectiveProjection::focalLengthSet()"
    }
    void PerspectiveProjection::fieldOfViewGet(Value::Number& result)
    {
//##protect##"instance::PerspectiveProjection::fieldOfViewGet()"
        result = fieldOfView;
//##protect##"instance::PerspectiveProjection::fieldOfViewGet()"
    }
    void PerspectiveProjection::fieldOfViewSet(Value& result, Value::Number value)
    {
//##protect##"instance::PerspectiveProjection::fieldOfViewSet()"
        result.SetUndefined();
        fieldOfView = (float)value;
        if (pDispObj)
            pDispObj->SetFOV(fieldOfView);
//##protect##"instance::PerspectiveProjection::fieldOfViewSet()"
    }
    void PerspectiveProjection::toMatrix3D(Value& result)
    {
//##protect##"instance::PerspectiveProjection::toMatrix3D()"
        Matrix4F mat4;
        float displayWidth;
        if (pDispObj)
        {
            const RectF &vfr = pDispObj->GetMovieImpl()->GetVisibleFrameRectInTwips();
            displayWidth = TwipsToPixels(fabsf(vfr.Width()));     
        }
        else
            // default Flash stage size
            displayWidth = 500;

        float fovYAngle = (float)SF_DEGTORAD(fieldOfView);
        float pixelPerUnitRatio = displayWidth*.5f;    
        float eyeZ = (focalLength == 0) ? (pixelPerUnitRatio/tanf(fovYAngle/2.f)) : (float)focalLength;

        // build transposed simple persp matrix that Flash prints out
        mat4 = Matrix4F::Scaling(eyeZ, eyeZ, 1);
        mat4.M[3][2] = 1;
        mat4.M[3][3] = 0;
        Value args[16];
        int i;
        for(i=0;i<16;i++)
            args[i].SetNumber(mat4[i]);
        GetVM().ConstructBuiltinValue(result, "flash.geom.Matrix3D", 16, args).DoNotCheck();
//##protect##"instance::PerspectiveProjection::toMatrix3D()"
    }

//##protect##"instance$methods"

    Double PerspectiveProjection::CalculateFocalLength(float stageWidth)
    {
        return (stageWidth/2.f) / tan((SF_MATH_PI/180.f)*(fieldOfView/2.f));     // == 250/tan((Pi/180)*(55/2)) = 480.25
    }

	void PerspectiveProjection::AS3Constructor(unsigned argc, const Value* argv) 
    {
        // fov, focalLength, projCtrX, projCtrY
        if (argc > 0)
        {
            Value::Number tmp;
            if (!argv[0].Convert2Number(tmp))
                return;
            if (tmp != 0)
                fieldOfView = tmp;
            if (argc > 1)
            {
                if (!argv[1].Convert2Number(tmp))
                    return;
                if (tmp != 0)
                    focalLength = tmp;
                if (argc > 2)
                {
                    Value::Number x, y;
                    if (!argv[2].Convert2Number(x))
                        return;
                    if (!argv[3].Convert2Number(y))
                        return;
                    if (x != 0 && y != 0)
                    {
                        projectionCenter.x = (float)x;
                        projectionCenter.y = (float)y;
                    }
                }
            }
        }
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo PerspectiveProjection::ti[PerspectiveProjection::ThunkInfoNum] = {
        {TFunc_Instances_PerspectiveProjection_projectionCenterGet::Func, &PointCI, "projectionCenter", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_projectionCenterSet::Func, NULL, "projectionCenter", NULL, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_focalLengthGet::Func, &NumberCI, "focalLength", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_focalLengthSet::Func, NULL, "focalLength", NULL, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_fieldOfViewGet::Func, &NumberCI, "fieldOfView", NULL, CT_Get, 0, 0},
        {TFunc_Instances_PerspectiveProjection_fieldOfViewSet::Func, NULL, "fieldOfView", NULL, CT_Set, 1, 1},
        {TFunc_Instances_PerspectiveProjection_toMatrix3D::Func, &Matrix3DCI, "toMatrix3D", NULL, CT_Method, 0, 0},
    };

    PerspectiveProjection::PerspectiveProjection(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::PerspectiveProjection::PerspectiveProjection()"
//##protect##"InstanceTraits::PerspectiveProjection::PerspectiveProjection()"
        SetMemSize(sizeof(Instances::PerspectiveProjection));

    }

    Pickable<Instances::PerspectiveProjection> PerspectiveProjection::MakeInstance(Traits& t)
    {
        return Pickable<Instances::PerspectiveProjection>(new(t.Alloc()) Instances::PerspectiveProjection(t));
    }

    void PerspectiveProjection::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    PerspectiveProjection::PerspectiveProjection(VM& vm)
    : Traits(vm, PerspectiveProjectionCI)
    {
//##protect##"ClassTraits::PerspectiveProjection::PerspectiveProjection()"
//##protect##"ClassTraits::PerspectiveProjection::PerspectiveProjection()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::PerspectiveProjection(vm, PerspectiveProjectionCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> PerspectiveProjection::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) PerspectiveProjection(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo PerspectiveProjectionCI = {
    ClassInfo::CompileTime,
    "PerspectiveProjection", "flash.geom", &ObjectCI,
    ClassTraits::PerspectiveProjection::MakeClassTraits,
    0,
    0,
    InstanceTraits::PerspectiveProjection::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::PerspectiveProjection::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

