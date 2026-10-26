//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_ColorMatrixFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_ColorMatrixFilter_H
#define INC_AS3_Obj_Filters_ColorMatrixFilter_H

#include "AS3_Obj_Filters_BitmapFilter.h"
//##protect##"includes"
#include "Render/Render_Filters.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ColorMatrixFilter;
}

namespace InstanceTraits
{
    class ColorMatrixFilter;
}

namespace Classes
{
    class ColorMatrixFilter;
}

namespace Instances
{
    class ColorMatrixFilter : public Instances::BitmapFilter
    {
        friend class InstanceTraits::ColorMatrixFilter;
        
    public:
        typedef ColorMatrixFilter SelfType;
        typedef Classes::ColorMatrixFilter ClassType;
        typedef InstanceTraits::ColorMatrixFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ColorMatrixFilter"; }
#endif
    protected:
        ColorMatrixFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        bool IsValidArrayObject(const Value& v) const;
        Render::ColorMatrixFilter* GetColorMatrixFilterData() const { return (Render::ColorMatrixFilter*)GetFilterData(); };
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_matrixGet, 
            mid_matrixSet, 
            mid_clone, 
        };
        void matrixGet(Value& result);
        void matrixSet(Value& result, Instances::Array* value);
        void clone(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ColorMatrixFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ColorMatrixFilter"; }
#endif
    public:
        ColorMatrixFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ColorMatrixFilter> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ColorMatrixFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ColorMatrixFilter"; }
#endif
    public:
        typedef Classes::ColorMatrixFilter ClassType;

    public:
        ColorMatrixFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

