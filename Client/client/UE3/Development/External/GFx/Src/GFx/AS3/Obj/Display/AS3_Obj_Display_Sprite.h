//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Sprite.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Sprite_H
#define INC_AS3_Obj_Display_Sprite_H

#include "AS3_Obj_Display_DisplayObjectContainer.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Graphics;
    class SoundTransform;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Sprite;
}

namespace InstanceTraits
{
    class Sprite;
}

namespace Classes
{
    class Sprite;
}

namespace Instances
{
    class Sprite : public Instances::DisplayObjectContainer
    {
        friend class InstanceTraits::Sprite;
        
    public:
        typedef Sprite SelfType;
        typedef Classes::Sprite ClassType;
        typedef InstanceTraits::Sprite TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Sprite"; }
#endif
    protected:
        Sprite(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        ~Sprite();

        virtual void InitInstance(bool extCall);
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual GFx::DisplayObject* CreateStageObject();

        virtual void        AS3Constructor(unsigned argc, const Value* argv);
    public:
        virtual bool        HasFrameScript() const { return false; }
        virtual bool        GetFrameScript(unsigned, Value*) { return false; }
        virtual bool        IsMovieClip() const { return false; }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_buttonModeGet, 
            mid_buttonModeSet, 
            mid_dropTargetGet, 
            mid_graphicsGet, 
            mid_hitAreaGet, 
            mid_hitAreaSet, 
            mid_soundTransformGet, 
            mid_soundTransformSet, 
            mid_useHandCursorGet, 
            mid_useHandCursorSet, 
            mid_startDrag, 
            mid_stopDrag, 
        };
        void buttonModeGet(bool& result);
        void buttonModeSet(Value& result, bool value);
        void dropTargetGet(Value& result);
        void graphicsGet(Value& result);
        void hitAreaGet(Value& result);
        void hitAreaSet(Value& result, Instances::Sprite* value);
        void soundTransformGet(Value& result);
        void soundTransformSet(Value& result, Instances::SoundTransform* value);
        void useHandCursorGet(bool& result);
        void useHandCursorSet(Value& result, bool value);
        void startDrag(Value& result, bool lockCenter, Instances::Rectangle* bounds);
        void stopDrag(Value& result);

//##protect##"instance$data"
        SPtr<Graphics> pGraphics;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Sprite : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Sprite"; }
#endif
    public:
        Sprite(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Sprite> MakeInstance(Traits& t);

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
    class Sprite : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Sprite"; }
#endif
    public:
        typedef Classes::Sprite ClassType;

    public:
        Sprite(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

