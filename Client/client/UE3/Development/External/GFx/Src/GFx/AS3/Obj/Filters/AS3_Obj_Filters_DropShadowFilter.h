//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_DropShadowFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_DropShadowFilter_H
#define INC_AS3_Obj_Filters_DropShadowFilter_H

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
    class DropShadowFilter;
}

namespace InstanceTraits
{
    class DropShadowFilter;
}

namespace Classes
{
    class DropShadowFilter;
}

namespace Instances
{
    class DropShadowFilter : public Instances::BitmapFilter
    {
        friend class InstanceTraits::DropShadowFilter;
        
    public:
        typedef DropShadowFilter SelfType;
        typedef Classes::DropShadowFilter ClassType;
        typedef InstanceTraits::DropShadowFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::DropShadowFilter"; }
#endif
    protected:
        DropShadowFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        Render::ShadowFilter* GetShadowFilterData() const { return (Render::ShadowFilter*)GetFilterData(); }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_alphaGet, 
            mid_alphaSet, 
            mid_angleGet, 
            mid_angleSet, 
            mid_blurXGet, 
            mid_blurXSet, 
            mid_blurYGet, 
            mid_blurYSet, 
            mid_colorGet, 
            mid_colorSet, 
            mid_distanceGet, 
            mid_distanceSet, 
            mid_hideObjectGet, 
            mid_hideObjectSet, 
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
        void angleGet(Value::Number& result);
        void angleSet(Value& result, Value::Number value);
        void blurXGet(Value::Number& result);
        void blurXSet(Value& result, Value::Number value);
        void blurYGet(Value::Number& result);
        void blurYSet(Value& result, Value::Number value);
        void colorGet(UInt32& result);
        void colorSet(Value& result, UInt32 value);
        void distanceGet(Value::Number& result);
        void distanceSet(Value& result, Value::Number value);
        void hideObjectGet(bool& result);
        void hideObjectSet(Value& result, bool value);
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
    class DropShadowFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::DropShadowFilter"; }
#endif
    public:
        DropShadowFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::DropShadowFilter> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 23 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class DropShadowFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DropShadowFilter"; }
#endif
    public:
        typedef Classes::DropShadowFilter ClassType;

    public:
        DropShadowFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

