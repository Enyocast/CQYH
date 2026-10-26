//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BevelFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_BevelFilter_H
#define INC_AS3_Obj_Filters_BevelFilter_H

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
    class BevelFilter;
}

namespace InstanceTraits
{
    class BevelFilter;
}

namespace Classes
{
    class BevelFilter;
}

namespace Instances
{
    class BevelFilter : public Instances::BitmapFilter
    {
        friend class InstanceTraits::BevelFilter;
        
    public:
        typedef BevelFilter SelfType;
        typedef Classes::BevelFilter ClassType;
        typedef InstanceTraits::BevelFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::BevelFilter"; }
#endif
    protected:
        BevelFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual Render::BevelFilter* GetBevelFilterData() const { return (Render::BevelFilter*)GetFilterData(); };
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_angleGet, 
            mid_angleSet, 
            mid_blurXGet, 
            mid_blurXSet, 
            mid_blurYGet, 
            mid_blurYSet, 
            mid_distanceGet, 
            mid_distanceSet, 
            mid_highlightAlphaGet, 
            mid_highlightAlphaSet, 
            mid_highlightColorGet, 
            mid_highlightColorSet, 
            mid_knockoutGet, 
            mid_knockoutSet, 
            mid_qualityGet, 
            mid_qualitySet, 
            mid_shadowAlphaGet, 
            mid_shadowAlphaSet, 
            mid_shadowColorGet, 
            mid_shadowColorSet, 
            mid_strengthGet, 
            mid_strengthSet, 
            mid_typeGet, 
            mid_typeSet, 
            mid_clone, 
        };
        void angleGet(Value::Number& result);
        void angleSet(Value& result, Value::Number value);
        void blurXGet(Value::Number& result);
        void blurXSet(Value& result, Value::Number value);
        void blurYGet(Value::Number& result);
        void blurYSet(Value& result, Value::Number value);
        void distanceGet(Value::Number& result);
        void distanceSet(Value& result, Value::Number value);
        void highlightAlphaGet(Value::Number& result);
        void highlightAlphaSet(Value& result, Value::Number value);
        void highlightColorGet(UInt32& result);
        void highlightColorSet(Value& result, UInt32 value);
        void knockoutGet(bool& result);
        void knockoutSet(Value& result, bool value);
        void qualityGet(SInt32& result);
        void qualitySet(Value& result, SInt32 value);
        void shadowAlphaGet(Value::Number& result);
        void shadowAlphaSet(Value& result, Value::Number value);
        void shadowColorGet(UInt32& result);
        void shadowColorSet(Value& result, UInt32 value);
        void strengthGet(Value::Number& result);
        void strengthSet(Value& result, Value::Number value);
        void typeGet(ASString& result);
        void typeSet(Value& result, const ASString& value);
        void clone(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class BevelFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::BevelFilter"; }
#endif
    public:
        BevelFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::BevelFilter> MakeInstance(Traits& t);

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
    class BevelFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BevelFilter"; }
#endif
    public:
        typedef Classes::BevelFilter ClassType;

    public:
        BevelFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

