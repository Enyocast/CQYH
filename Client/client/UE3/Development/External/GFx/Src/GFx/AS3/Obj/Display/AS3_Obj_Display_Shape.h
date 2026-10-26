//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Shape.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Shape_H
#define INC_AS3_Obj_Display_Shape_H

#include "AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Graphics;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Shape;
}

namespace InstanceTraits
{
    class Shape;
}

namespace Classes
{
    class Shape;
}

namespace Instances
{
    class Shape : public Instances::DisplayObject
    {
        friend class InstanceTraits::Shape;
        
    public:
        typedef Shape SelfType;
        typedef Classes::Shape ClassType;
        typedef InstanceTraits::Shape TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Shape"; }
#endif
    protected:
        Shape(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void InitInstance(bool extCall);
        virtual GFx::DisplayObject* CreateStageObject();

        ~Shape();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_graphicsGet, 
        };
        void graphicsGet(Value& result);

//##protect##"instance$data"
        SPtr<Graphics> pGraphics;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Shape : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Shape"; }
#endif
    public:
        Shape(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Shape> MakeInstance(Traits& t);

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
    class Shape : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Shape"; }
#endif
    public:
        typedef Classes::Shape ClassType;

    public:
        Shape(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

