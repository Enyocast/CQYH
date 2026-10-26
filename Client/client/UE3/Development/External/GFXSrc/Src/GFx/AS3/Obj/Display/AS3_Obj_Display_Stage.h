//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Stage.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_Stage_H
#define INC_AS3_Obj_Display_Stage_H

#include "AS3_Obj_Display_DisplayObjectContainer.h"
//##protect##"includes"
#include "GFx/AS3/AS3_AvmStage.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class NativeWindow;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Stage;
}

namespace InstanceTraits
{
    class Stage;
}

namespace Classes
{
    class Stage;
}

namespace Instances
{
    class Stage : public Instances::DisplayObjectContainer
    {
        friend class InstanceTraits::Stage;
        
    public:
        typedef Stage SelfType;
        typedef Classes::Stage ClassType;
        typedef InstanceTraits::Stage TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Stage"; }
#endif
    protected:
        Stage(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        ~Stage();
    public:
        AS3::Stage* GetStageObj() 
        {
            return static_cast<AS3::Stage*>(pDispObj.GetPtr());
        }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_alignGet, 
            mid_alignSet, 
            mid_autoOrientsGet, 
            mid_deviceOrientationGet, 
            mid_displayStateGet, 
            mid_displayStateSet, 
            mid_focusGet, 
            mid_focusSet, 
            mid_frameRateGet, 
            mid_frameRateSet, 
            mid_fullScreenHeightGet, 
            mid_fullScreenSourceRectGet, 
            mid_fullScreenSourceRectSet, 
            mid_fullScreenWidthGet, 
            mid_heightGet, 
            mid_heightSet, 
            mid_mouseChildrenGet, 
            mid_mouseChildrenSet, 
            mid_nativeWindowGet, 
            mid_numChildrenGet, 
            mid_orientationGet, 
            mid_qualityGet, 
            mid_qualitySet, 
            mid_scaleModeGet, 
            mid_scaleModeSet, 
            mid_showDefaultContextMenuGet, 
            mid_showDefaultContextMenuSet, 
            mid_stageFocusRectGet, 
            mid_stageFocusRectSet, 
            mid_stageHeightGet, 
            mid_stageHeightSet, 
            mid_stageWidthGet, 
            mid_stageWidthSet, 
            mid_tabChildrenGet, 
            mid_tabChildrenSet, 
            mid_textSnapshotGet, 
            mid_widthGet, 
            mid_widthSet, 
            mid_addChild, 
            mid_addChildAt, 
            mid_addEventListener, 
            mid_assignFocus, 
            mid_dispatchEvent, 
            mid_hasEventListener, 
            mid_invalidate, 
            mid_isFocusInaccessible, 
            mid_removeChildAt, 
            mid_removeEventListener, 
            mid_setChildIndex, 
            mid_setOrientation, 
            mid_swapChildrenAt, 
            mid_willTrigger, 
        };
        void alignGet(ASString& result);
        void alignSet(Value& result, const ASString& value);
        void autoOrientsGet(bool& result);
        void deviceOrientationGet(ASString& result);
        void displayStateGet(ASString& result);
        void displayStateSet(Value& result, const ASString& value);
        void focusGet(Value& result);
        void focusSet(Value& result, Instances::InteractiveObject* value);
        void frameRateGet(Value::Number& result);
        void frameRateSet(Value& result, Value::Number value);
        void fullScreenHeightGet(UInt32& result);
        void fullScreenSourceRectGet(Value& result);
        void fullScreenSourceRectSet(Value& result, Instances::Rectangle* value);
        void fullScreenWidthGet(UInt32& result);
        void heightGet(Value::Number& result);
        void heightSet(Value& result, Value::Number value);
        void mouseChildrenGet(bool& result);
        void mouseChildrenSet(Value& result, bool value);
        void nativeWindowGet(Value& result);
        void numChildrenGet(SInt32& result);
        void orientationGet(ASString& result);
        void qualityGet(ASString& result);
        void qualitySet(Value& result, const ASString& value);
        void scaleModeGet(ASString& result);
        void scaleModeSet(Value& result, const ASString& value);
        void showDefaultContextMenuGet(bool& result);
        void showDefaultContextMenuSet(Value& result, bool value);
        void stageFocusRectGet(bool& result);
        void stageFocusRectSet(Value& result, bool value);
        void stageHeightGet(SInt32& result);
        void stageHeightSet(Value& result, SInt32 value);
        void stageWidthGet(SInt32& result);
        void stageWidthSet(Value& result, SInt32 value);
        void tabChildrenGet(bool& result);
        void tabChildrenSet(Value& result, bool value);
        void textSnapshotGet(Value& result);
        void widthGet(Value::Number& result);
        void widthSet(Value& result, Value::Number value);
        void addChild(Value& result, Instances::DisplayObject* child);
        void addChildAt(Value& result, Instances::DisplayObject* child, SInt32 index);
        void addEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture, SInt32 priority, bool useWeakReference);
        void assignFocus(Value& result, Instances::InteractiveObject* objectToFocus, const ASString& direction);
        void dispatchEvent(bool& result, Instances::Event* event);
        void hasEventListener(bool& result, const ASString& type);
        void invalidate(Value& result);
        void isFocusInaccessible(bool& result);
        void removeChildAt(Value& result, SInt32 index);
        void removeEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture);
        void setChildIndex(Value& result, Instances::DisplayObject* child, SInt32 index);
        void setOrientation(Value& result, const ASString& newOrientation);
        void swapChildrenAt(Value& result, SInt32 index1, SInt32 index2);
        void willTrigger(bool& result, const ASString& type);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Stage : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Stage"; }
#endif
    public:
        Stage(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Stage> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 56 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Stage : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Stage"; }
#endif
    public:
        typedef Classes::Stage ClassType;

    public:
        Stage(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Stage : public Class
    {
        friend class ClassTraits::Stage;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Stage"; }
#endif
    public:
        typedef Stage SelfType;
        typedef Stage ClassType;
        
    private:
        Stage(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_supportsOrientationChangeGet, 
        };
        void supportsOrientationChangeGet(bool& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

