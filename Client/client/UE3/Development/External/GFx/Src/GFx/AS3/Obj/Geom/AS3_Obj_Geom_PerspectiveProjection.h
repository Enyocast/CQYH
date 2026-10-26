//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_PerspectiveProjection.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_PerspectiveProjection_H
#define INC_AS3_Obj_Geom_PerspectiveProjection_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_DisplayObject.h"

#define DEFAULT_STAGE_WIDTH 500.f
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
    class PerspectiveProjection;
}

namespace InstanceTraits
{
    class PerspectiveProjection;
}

namespace Classes
{
    class PerspectiveProjection;
}

namespace Instances
{
    class PerspectiveProjection : public Instances::Object
    {
        friend class InstanceTraits::PerspectiveProjection;
        
    public:
        typedef PerspectiveProjection SelfType;
        typedef Classes::PerspectiveProjection ClassType;
        typedef InstanceTraits::PerspectiveProjection TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::PerspectiveProjection"; }
#endif
    protected:
        PerspectiveProjection(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv); 
    public:
        Double CalculateFocalLength(float stageWidth);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_projectionCenterGet, 
            mid_projectionCenterSet, 
            mid_focalLengthGet, 
            mid_focalLengthSet, 
            mid_fieldOfViewGet, 
            mid_fieldOfViewSet, 
            mid_toMatrix3D, 
        };
        void projectionCenterGet(Value& result);
        void projectionCenterSet(Value& result, Instances::Point* value);
        void focalLengthGet(Value::Number& result);
        void focalLengthSet(Value& result, Value::Number value);
        void fieldOfViewGet(Value::Number& result);
        void fieldOfViewSet(Value& result, Value::Number value);
        void toMatrix3D(Value& result);

//##protect##"instance$data"
        PointF projectionCenter;
        Double focalLength;
        Double fieldOfView;
    public:
        GFx::DisplayObject* pDispObj;
        PointF &GetProjectionCenter()   { return projectionCenter; }

        Double GetFOV() const           { return fieldOfView; }
        void SetFOV(Double f)           { fieldOfView = f; }

        Double GetFocalLength() const   { return focalLength; }
        void SetFocalLength(Double f)   { focalLength = f; }

//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class PerspectiveProjection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::PerspectiveProjection"; }
#endif
    public:
        PerspectiveProjection(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::PerspectiveProjection> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 7 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class PerspectiveProjection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::PerspectiveProjection"; }
#endif
    public:
        typedef Classes::PerspectiveProjection ClassType;

    public:
        PerspectiveProjection(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

