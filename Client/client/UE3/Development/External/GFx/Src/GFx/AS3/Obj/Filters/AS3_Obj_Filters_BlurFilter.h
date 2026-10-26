//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BlurFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_BlurFilter_H
#define INC_AS3_Obj_Filters_BlurFilter_H

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
    class BlurFilter;
}

namespace InstanceTraits
{
    class BlurFilter;
}

namespace Classes
{
    class BlurFilter;
}

namespace Instances
{
    class BlurFilter : public Instances::BitmapFilter
    {
        friend class InstanceTraits::BlurFilter;
        
    public:
        typedef BlurFilter SelfType;
        typedef Classes::BlurFilter ClassType;
        typedef InstanceTraits::BlurFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::BlurFilter"; }
#endif
    protected:
        BlurFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        Render::BlurFilter* GetBlurFilterData() const { return (Render::BlurFilter*)GetFilterData(); }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_blurXGet, 
            mid_blurXSet, 
            mid_blurYGet, 
            mid_blurYSet, 
            mid_qualityGet, 
            mid_qualitySet, 
            mid_clone, 
        };
        void blurXGet(Value::Number& result);
        void blurXSet(Value& result, Value::Number value);
        void blurYGet(Value::Number& result);
        void blurYSet(Value& result, Value::Number value);
        void qualityGet(SInt32& result);
        void qualitySet(Value& result, SInt32 value);
        void clone(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class BlurFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::BlurFilter"; }
#endif
    public:
        BlurFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::BlurFilter> MakeInstance(Traits& t);

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
    class BlurFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BlurFilter"; }
#endif
    public:
        typedef Classes::BlurFilter ClassType;

    public:
        BlurFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

