//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilter.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_BitmapFilter_H
#define INC_AS3_Obj_Filters_BitmapFilter_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "Render/Render_States.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BitmapFilter;
}

namespace InstanceTraits
{
    class BitmapFilter;
}

namespace Classes
{
    class BitmapFilter;
}

namespace Instances
{
    class BitmapFilter : public Instances::Object
    {
        friend class InstanceTraits::BitmapFilter;
        
    public:
        typedef BitmapFilter SelfType;
        typedef Classes::BitmapFilter ClassType;
        typedef InstanceTraits::BitmapFilter TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::BitmapFilter"; }
#endif
    protected:
        BitmapFilter(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        Render::Filter* GetFilterData() const { return FilterData; };
        void            SetFilterData(Render::Filter* filter) { FilterData = filter; } 
    protected:
        Ptr<Render::Filter>     FilterData;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_clone, 
        };
        void clone(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class BitmapFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::BitmapFilter"; }
#endif
    public:
        BitmapFilter(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::BitmapFilter> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class BitmapFilter : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BitmapFilter"; }
#endif
    public:
        typedef Classes::BitmapFilter ClassType;

    public:
        BitmapFilter(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

