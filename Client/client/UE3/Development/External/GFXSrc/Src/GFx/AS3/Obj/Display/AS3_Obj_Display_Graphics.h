//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Graphics.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy, Artem Bolgar, Prasad Silva

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Graphics_H
#define INC_AS3_Obj_Display_Graphics_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_DrawingContext.h"
#include "GFx/GFx_DisplayObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class BitmapData;
    class Matrix;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Graphics;
}

namespace InstanceTraits
{
    class Graphics;
}

namespace Classes
{
    class Graphics;
}

namespace Instances
{
    class Graphics : public Instances::Object
    {
        friend class InstanceTraits::Graphics;
        
    public:
        typedef Graphics SelfType;
        typedef Classes::Graphics ClassType;
        typedef InstanceTraits::Graphics TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Graphics"; }
#endif
    protected:
        Graphics(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        void AcquirePath(bool newShapeFlag);
        void CreateGradientHelper(unsigned argc, const Value* const argv, Render::ComplexFill* complexFill);
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_beginBitmapFill, 
            mid_beginFill, 
            mid_beginGradientFill, 
            mid_clear, 
            mid_curveTo, 
            mid_drawCircle, 
            mid_drawEllipse, 
            mid_drawRect, 
            mid_drawRoundRect, 
            mid_drawRoundRectComplex, 
            mid_endFill, 
            mid_lineGradientStyle, 
            mid_lineStyle, 
            mid_lineTo, 
            mid_moveTo, 
        };
        void beginBitmapFill(Value& result, Instances::BitmapData* bitmap, Instances::Matrix* matrix, bool repeat, bool smooth);
        void beginFill(Value& result, UInt32 color, Value::Number alpha);
        void beginGradientFill(Value& result, unsigned argc, const Value* const argv);
        void clear(Value& result);
        void curveTo(Value& result, Value::Number controlX, Value::Number controlY, Value::Number anchorX, Value::Number anchorY);
        void drawCircle(Value& result, Value::Number x, Value::Number y, Value::Number radius);
        void drawEllipse(Value& result, Value::Number x, Value::Number y, Value::Number width, Value::Number height);
        void drawRect(Value& result, Value::Number x, Value::Number y, Value::Number width, Value::Number height);
        void drawRoundRect(Value& result, Value::Number x, Value::Number y, Value::Number width, Value::Number height, Value::Number ellipseWidth, Value::Number ellipseHeight);
        void drawRoundRectComplex(Value& result, unsigned argc, const Value* const argv);
        void endFill(Value& result);
        void lineGradientStyle(Value& result, unsigned argc, const Value* const argv);
        void lineStyle(Value& result, unsigned argc, const Value* const argv);
        void lineTo(Value& result, Value::Number x, Value::Number y);
        void moveTo(Value& result, Value::Number x, Value::Number y);

//##protect##"instance$data"
    public:
        Ptr<DrawingContext> pDrawing;
        GFx::DisplayObject* pDispObj;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Graphics : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Graphics"; }
#endif
    public:
        Graphics(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Graphics> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 15 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Graphics : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Graphics"; }
#endif
    public:
        typedef Classes::Graphics ClassType;

    public:
        Graphics(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

