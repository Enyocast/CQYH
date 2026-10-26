//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_FocusManager.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_FocusManager_H
#define INC_AS3_Obj_Gfx_FocusManager_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
#include "../Display/AS3_Obj_Display_MovieClip.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FocusManager;
}

namespace InstanceTraits
{
    class FocusManager;
}

namespace Classes
{
    class FocusManager;
}
    
namespace ClassTraits
{
    class FocusManager : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FocusManager"; }
#endif
    public:
        typedef Classes::FocusManager ClassType;

    public:
        FocusManager(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 16 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FocusManager : public Class
    {
        friend class ClassTraits::FocusManager;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FocusManager"; }
#endif
    public:
        typedef FocusManager SelfType;
        typedef FocusManager ClassType;
        
    private:
        FocusManager(ClassTraits::Traits& t);
       
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
            mid_alwaysEnableArrowKeysSet, 
            mid_alwaysEnableArrowKeysGet, 
            mid_disableFocusKeysSet, 
            mid_disableFocusKeysGet, 
            mid_moveFocus, 
            mid_findFocus, 
            mid_setFocus, 
            mid_getFocus, 
            mid_numFocusGroupsGet, 
            mid_setFocusGroupMask, 
            mid_getFocusGroupMask, 
            mid_setControllerFocusGroup, 
            mid_getControllerFocusGroup, 
            mid_getControllerMaskByFocusGroup, 
            mid_getModalClip, 
            mid_setModalClip, 
        };
        void alwaysEnableArrowKeysSet(Value& result, bool enable);
        void alwaysEnableArrowKeysGet(bool& result);
        void disableFocusKeysSet(Value& result, bool disable);
        void disableFocusKeysGet(bool& result);
        void moveFocus(Value& result, const ASString& keyToSimulate, Instances::InteractiveObject* startFromMovie, bool includeFocusEnabledChars, UInt32 controllerIdx);
        void findFocus(Value& result, const ASString& keyToSimulate, Instances::DisplayObjectContainer* parentMovie, bool loop, Instances::InteractiveObject* startFromMovie, bool includeFocusEnabledChars, UInt32 controllerIdx);
        void setFocus(Value& result, Instances::InteractiveObject* obj, UInt32 controllerIdx);
        void getFocus(Value& result, UInt32 controllerIdx);
        void numFocusGroupsGet(UInt32& result);
        void setFocusGroupMask(Value& result, Instances::InteractiveObject* obj, UInt32 mask);
        void getFocusGroupMask(UInt32& result, Instances::InteractiveObject* obj);
        void setControllerFocusGroup(bool& result, UInt32 controllerIdx, UInt32 focusGroupIdx);
        void getControllerFocusGroup(UInt32& result, UInt32 controllerIdx);
        void getControllerMaskByFocusGroup(UInt32& result, UInt32 focusGroupIdx);
        void getModalClip(Value& result, UInt32 controllerIdx);
        void setModalClip(Value& result, Instances::Sprite* mc, UInt32 controllerIdx);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

