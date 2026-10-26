//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_GlowFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_GlowFilter_H
#define INC_AS3_Obj_Filters_GlowFilter_H

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
    class GlowFilter;
}

namespace InstanceTraits
{
    class GlowFilter;
}

namespace Classes
{
    class GlowFilter;
}

namespace Instances
{
    class GlowFilter : public Instances::BitmapFilter
    {
        friend class InstanceTraits::GlowFilter;
        
    public:
        typedef GlowFilter SelfType;
        typedef Classes::GlowFilter ClassType;
        typedef InstanceTraits::GlowFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GlowFilter"; }
#endif
    protected:
        GlowFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        Render::GlowFilter* GetGlowFilterData() const { return (Render::GlowFilter*)GetFilterData(); }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_alphaGet, 
            mid_alphaSet, 
            mid_blurXGet, 
            mid_blurXSet, 
            mid_blurYGet, 
            mid_blurYSet, 
            mid_colorGet, 
            mid_colorSet, 
            mid_innerGet, 
            mid_innerSet, 
            mid_knockoutGet, 
            mid_knockoutSet, 
            mid_qualityGet, 
            mid_qualitySet, 
            mid_strengthGet, 
            mid_strengthSet, 
            mid_clone, 
        };
        void alphaGet(Value::Number& result);
        void alphaSet(Value& result, Value::Number value);
        void blurXGet(Value::Number& result);
        void blurXSet(Value& result, Value::Number value);
        void blurYGet(Value::Number& result);
        void blurYSet(Value& result, Value::Number value);
        void colorGet(UInt32& result);
        void colorSet(Value& result, UInt32 value);
        void innerGet(bool& result);
        void innerSet(Value& result, bool value);
        void knockoutGet(bool& result);
        void knockoutSet(Value& result, bool value);
        void qualityGet(SInt32& result);
        void qualitySet(Value& result, SInt32 value);
        void strengthGet(Value::Number& result);
        void strengthSet(Value& result, Value::Number value);
        void clone(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class GlowFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::GlowFilter"; }
#endif
    public:
        GlowFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::GlowFilter> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 17 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class GlowFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GlowFilter"; }
#endif
    public:
        typedef Classes::GlowFilter ClassType;

    public:
        GlowFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

