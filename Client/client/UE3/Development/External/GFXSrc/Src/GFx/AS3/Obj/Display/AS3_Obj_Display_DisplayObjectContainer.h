//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_DisplayObjectContainer.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_DisplayObjectContainer_H
#define INC_AS3_Obj_Display_DisplayObjectContainer_H

#include "AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"
#include "GFx/GFx_DisplayObjContainer.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class TextSnapshot;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DisplayObjectContainer;
}

namespace InstanceTraits
{
    class DisplayObjectContainer;
}

namespace Classes
{
    class DisplayObjectContainer;
}

namespace Instances
{
    class DisplayObjectContainer : public Instances::InteractiveObject
    {
        friend class InstanceTraits::DisplayObjectContainer;
        
    public:
        typedef DisplayObjectContainer SelfType;
        typedef Classes::DisplayObjectContainer ClassType;
        typedef InstanceTraits::DisplayObjectContainer TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::DisplayObjectContainer"; }
#endif
    protected:
        DisplayObjectContainer(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        ~DisplayObjectContainer();
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_mouseChildrenGet, 
            mid_mouseChildrenSet, 
            mid_numChildrenGet, 
            mid_tabChildrenGet, 
            mid_tabChildrenSet, 
            mid_textSnapshotGet, 
            mid_addChild, 
            mid_addChildAt, 
            mid_areInaccessibleObjectsUnderPoint, 
            mid_contains, 
            mid_getChildAt, 
            mid_getChildByName, 
            mid_getChildIndex, 
            mid_getObjectsUnderPoint, 
            mid_removeChild, 
            mid_removeChildAt, 
            mid_setChildIndex, 
            mid_swapChildren, 
            mid_swapChildrenAt, 
        };
        void mouseChildrenGet(bool& result);
        void mouseChildrenSet(Value& result, bool value);
        void numChildrenGet(SInt32& result);
        void tabChildrenGet(bool& result);
        void tabChildrenSet(Value& result, bool value);
        void textSnapshotGet(Value& result);
        void addChild(Value& result, Instances::DisplayObject* child);
        void addChildAt(Value& result, Instances::DisplayObject* child, SInt32 index);
        void areInaccessibleObjectsUnderPoint(bool& result, Instances::Point* point);
        void contains(bool& result, Instances::DisplayObject* child);
        void getChildAt(Value& result, SInt32 index);
        void getChildByName(Value& result, const ASString& name);
        void getChildIndex(SInt32& result, Instances::DisplayObject* child);
        void getObjectsUnderPoint(Value& result, Instances::Point* point);
        void removeChild(Value& result, unsigned argc, const Value* const argv);
        void removeChildAt(Value& result, SInt32 index);
        void setChildIndex(Value& result, Instances::DisplayObject* child, SInt32 index);
        void swapChildren(Value& result, Instances::DisplayObject* child1, Instances::DisplayObject* child2);
        void swapChildrenAt(Value& result, SInt32 index1, SInt32 index2);

//##protect##"instance$data"
        GFx::DisplayObjContainer* GetDisplayObjContainer() const 
        { 
            SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
            return pDispObj->CharToDisplayObjContainer_Unsafe(); 
        }
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class DisplayObjectContainer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::DisplayObjectContainer"; }
#endif
    public:
        DisplayObjectContainer(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::DisplayObjectContainer> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 19 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class DisplayObjectContainer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DisplayObjectContainer"; }
#endif
    public:
        typedef Classes::DisplayObjectContainer ClassType;

    public:
        DisplayObjectContainer(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

