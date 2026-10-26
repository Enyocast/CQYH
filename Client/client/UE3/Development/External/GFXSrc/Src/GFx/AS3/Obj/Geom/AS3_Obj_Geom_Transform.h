//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_Transform.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_Transform_H
#define INC_AS3_Obj_Geom_Transform_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_DisplayObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class ColorTransform;
    class Matrix;
    class Matrix3D;
    class Rectangle;
    class DisplayObject;
    class Vector3D;
	class PerspectiveProjection;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Transform;
}

namespace InstanceTraits
{
    class Transform;
}

namespace Classes
{
    class Transform;
}

namespace Instances
{
    class Transform : public Instances::Object
    {
        friend class InstanceTraits::Transform;
        
    public:
        typedef Transform SelfType;
        typedef Classes::Transform ClassType;
        typedef InstanceTraits::Transform TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Transform"; }
#endif
    protected:
        Transform(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_colorTransformGet, 
            mid_colorTransformSet, 
            mid_concatenatedColorTransformGet, 
            mid_concatenatedMatrixGet, 
            mid_matrixGet, 
            mid_matrixSet, 
            mid_matrix3DGet, 
            mid_matrix3DSet, 
            mid_perspectiveProjectionGet, 
            mid_perspectiveProjectionSet, 
            mid_pixelBoundsGet, 
            mid_getRelativeMatrix3D, 
        };
        void colorTransformGet(Value& result);
        void colorTransformSet(Value& result, Instances::ColorTransform* value);
        void concatenatedColorTransformGet(Value& result);
        void concatenatedMatrixGet(Value& result);
        void matrixGet(Value& result);
        void matrixSet(Value& result, Instances::Matrix* value);
        void matrix3DGet(Value& result);
        void matrix3DSet(Value& result, Instances::Matrix3D* value);
        void perspectiveProjectionGet(Value& result);
        void perspectiveProjectionSet(Value& result, Instances::PerspectiveProjection* value);
        void pixelBoundsGet(Value& result);
        void getRelativeMatrix3D(Value& result, Instances::DisplayObject* relativeTo);

//##protect##"instance$data"
	public:
		GFx::DisplayObject* pDispObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Transform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Transform"; }
#endif
    public:
        Transform(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Transform> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

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
    class Transform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Transform"; }
#endif
    public:
        typedef Classes::Transform ClassType;

    public:
        Transform(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

