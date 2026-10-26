//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SimpleButton.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_SimpleButton_H
#define INC_AS3_Obj_Display_SimpleButton_H

#include "AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
class AvmButton;

namespace Instances
{
    class SoundTransform;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SimpleButton;
}

namespace InstanceTraits
{
    class SimpleButton;
}

namespace Classes
{
    class SimpleButton;
}

namespace Instances
{
    class SimpleButton : public Instances::InteractiveObject
    {
        friend class InstanceTraits::SimpleButton;
        
    public:
        typedef SimpleButton SelfType;
        typedef Classes::SimpleButton ClassType;
        typedef InstanceTraits::SimpleButton TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SimpleButton"; }
#endif
    protected:
        SimpleButton(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        AvmButton*                  GetAvmButton() const;
        virtual void                AS3Constructor(unsigned argc, const Value* argv);
        virtual void                InitInstance(bool extCall = false);
        virtual GFx::DisplayObject* CreateStageObject();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_downStateGet, 
            mid_downStateSet, 
            mid_enabledGet, 
            mid_enabledSet, 
            mid_hitTestStateGet, 
            mid_hitTestStateSet, 
            mid_overStateGet, 
            mid_overStateSet, 
            mid_soundTransformGet, 
            mid_soundTransformSet, 
            mid_trackAsMenuGet, 
            mid_trackAsMenuSet, 
            mid_upStateGet, 
            mid_upStateSet, 
            mid_useHandCursorGet, 
            mid_useHandCursorSet, 
        };
        void downStateGet(Value& result);
        void downStateSet(Value& result, Instances::DisplayObject* value);
        void enabledGet(bool& result);
        void enabledSet(Value& result, bool value);
        void hitTestStateGet(Value& result);
        void hitTestStateSet(Value& result, Instances::DisplayObject* value);
        void overStateGet(Value& result);
        void overStateSet(Value& result, Instances::DisplayObject* value);
        void soundTransformGet(Value& result);
        void soundTransformSet(Value& result, Instances::SoundTransform* value);
        void trackAsMenuGet(bool& result);
        void trackAsMenuSet(Value& result, bool value);
        void upStateGet(Value& result);
        void upStateSet(Value& result, Instances::DisplayObject* value);
        void useHandCursorGet(bool& result);
        void useHandCursorSet(Value& result, bool value);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SimpleButton : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SimpleButton"; }
#endif
    public:
        SimpleButton(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SimpleButton> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 16 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class SimpleButton : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SimpleButton"; }
#endif
    public:
        typedef Classes::SimpleButton ClassType;

    public:
        SimpleButton(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

