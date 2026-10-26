//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_InteractiveObject.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_InteractiveObject_H
#define INC_AS3_Obj_Display_InteractiveObject_H

#include "AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
#include "GFx/GFx_InteractiveObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class NativeMenu;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class InteractiveObject;
}

namespace InstanceTraits
{
    class InteractiveObject;
}

namespace Classes
{
    class InteractiveObject;
}

namespace Instances
{
    class InteractiveObject : public Instances::DisplayObject
    {
        friend class InstanceTraits::InteractiveObject;
        
    public:
        typedef InteractiveObject SelfType;
        typedef Classes::InteractiveObject ClassType;
        typedef InstanceTraits::InteractiveObject TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::InteractiveObject"; }
#endif
    protected:
        InteractiveObject(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
    public:
        GFx::InteractiveObject* GetIntObj() 
        {
            return static_cast<GFx::InteractiveObject*>(pDispObj.GetPtr());
        }
        ~InteractiveObject();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_contextMenuGet, 
            mid_contextMenuSet, 
            mid_doubleClickEnabledGet, 
            mid_doubleClickEnabledSet, 
            mid_focusRectGet, 
            mid_focusRectSet, 
            mid_mouseEnabledGet, 
            mid_mouseEnabledSet, 
            mid_tabEnabledGet, 
            mid_tabEnabledSet, 
            mid_tabIndexGet, 
            mid_tabIndexSet, 
        };
        void contextMenuGet(Value& result);
        void contextMenuSet(Value& result, const Value& value);
        void doubleClickEnabledGet(bool& result);
        void doubleClickEnabledSet(Value& result, bool value);
        void focusRectGet(Value& result);
        void focusRectSet(Value& result, const Value& value);
        void mouseEnabledGet(bool& result);
        void mouseEnabledSet(Value& result, bool value);
        void tabEnabledGet(bool& result);
        void tabEnabledSet(Value& result, bool value);
        void tabIndexGet(SInt32& result);
        void tabIndexSet(Value& result, SInt32 value);

//##protect##"instance$data"
    protected:
        SPtr<AS3::Object> pContextMenu;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class InteractiveObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::InteractiveObject"; }
#endif
    public:
        InteractiveObject(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::InteractiveObject> MakeInstance(Traits& t);

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
    class InteractiveObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::InteractiveObject"; }
#endif
    public:
        typedef Classes::InteractiveObject ClassType;

    public:
        InteractiveObject(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

