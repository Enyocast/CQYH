//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_DisplayObjectContainer.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_DisplayObjectContainer.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "../Geom/AS3_Obj_Geom_Point.h"
#include "../Text/AS3_Obj_Text_TextSnapshot.h"
#include "GFx/AS3/AS3_AvmSprite.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_mouseChildrenGet, bool> TFunc_Instances_DisplayObjectContainer_mouseChildrenGet;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_mouseChildrenSet, Value, bool> TFunc_Instances_DisplayObjectContainer_mouseChildrenSet;
typedef ThunkFunc0<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_numChildrenGet, SInt32> TFunc_Instances_DisplayObjectContainer_numChildrenGet;
typedef ThunkFunc0<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_tabChildrenGet, bool> TFunc_Instances_DisplayObjectContainer_tabChildrenGet;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_tabChildrenSet, Value, bool> TFunc_Instances_DisplayObjectContainer_tabChildrenSet;
typedef ThunkFunc0<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_textSnapshotGet, Value> TFunc_Instances_DisplayObjectContainer_textSnapshotGet;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_addChild, Value, Instances::DisplayObject*> TFunc_Instances_DisplayObjectContainer_addChild;
typedef ThunkFunc2<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_addChildAt, Value, Instances::DisplayObject*, SInt32> TFunc_Instances_DisplayObjectContainer_addChildAt;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_areInaccessibleObjectsUnderPoint, bool, Instances::Point*> TFunc_Instances_DisplayObjectContainer_areInaccessibleObjectsUnderPoint;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_contains, bool, Instances::DisplayObject*> TFunc_Instances_DisplayObjectContainer_contains;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_getChildAt, Value, SInt32> TFunc_Instances_DisplayObjectContainer_getChildAt;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_getChildByName, Value, const ASString&> TFunc_Instances_DisplayObjectContainer_getChildByName;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_getChildIndex, SInt32, Instances::DisplayObject*> TFunc_Instances_DisplayObjectContainer_getChildIndex;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_getObjectsUnderPoint, Value, Instances::Point*> TFunc_Instances_DisplayObjectContainer_getObjectsUnderPoint;
typedef ThunkFunc2<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_removeChild, Value, unsigned, const Value*> TFunc_Instances_DisplayObjectContainer_removeChild;
typedef ThunkFunc1<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_removeChildAt, Value, SInt32> TFunc_Instances_DisplayObjectContainer_removeChildAt;
typedef ThunkFunc2<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_setChildIndex, Value, Instances::DisplayObject*, SInt32> TFunc_Instances_DisplayObjectContainer_setChildIndex;
typedef ThunkFunc2<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_swapChildren, Value, Instances::DisplayObject*, Instances::DisplayObject*> TFunc_Instances_DisplayObjectContainer_swapChildren;
typedef ThunkFunc2<Instances::DisplayObjectContainer, Instances::DisplayObjectContainer::mid_swapChildrenAt, Value, SInt32, SInt32> TFunc_Instances_DisplayObjectContainer_swapChildrenAt;

template <> const TFunc_Instances_DisplayObjectContainer_mouseChildrenGet::TMethod TFunc_Instances_DisplayObjectContainer_mouseChildrenGet::Method = &Instances::DisplayObjectContainer::mouseChildrenGet;
template <> const TFunc_Instances_DisplayObjectContainer_mouseChildrenSet::TMethod TFunc_Instances_DisplayObjectContainer_mouseChildrenSet::Method = &Instances::DisplayObjectContainer::mouseChildrenSet;
template <> const TFunc_Instances_DisplayObjectContainer_numChildrenGet::TMethod TFunc_Instances_DisplayObjectContainer_numChildrenGet::Method = &Instances::DisplayObjectContainer::numChildrenGet;
template <> const TFunc_Instances_DisplayObjectContainer_tabChildrenGet::TMethod TFunc_Instances_DisplayObjectContainer_tabChildrenGet::Method = &Instances::DisplayObjectContainer::tabChildrenGet;
template <> const TFunc_Instances_DisplayObjectContainer_tabChildrenSet::TMethod TFunc_Instances_DisplayObjectContainer_tabChildrenSet::Method = &Instances::DisplayObjectContainer::tabChildrenSet;
template <> const TFunc_Instances_DisplayObjectContainer_textSnapshotGet::TMethod TFunc_Instances_DisplayObjectContainer_textSnapshotGet::Method = &Instances::DisplayObjectContainer::textSnapshotGet;
template <> const TFunc_Instances_DisplayObjectContainer_addChild::TMethod TFunc_Instances_DisplayObjectContainer_addChild::Method = &Instances::DisplayObjectContainer::addChild;
template <> const TFunc_Instances_DisplayObjectContainer_addChildAt::TMethod TFunc_Instances_DisplayObjectContainer_addChildAt::Method = &Instances::DisplayObjectContainer::addChildAt;
template <> const TFunc_Instances_DisplayObjectContainer_areInaccessibleObjectsUnderPoint::TMethod TFunc_Instances_DisplayObjectContainer_areInaccessibleObjectsUnderPoint::Method = &Instances::DisplayObjectContainer::areInaccessibleObjectsUnderPoint;
template <> const TFunc_Instances_DisplayObjectContainer_contains::TMethod TFunc_Instances_DisplayObjectContainer_contains::Method = &Instances::DisplayObjectContainer::contains;
template <> const TFunc_Instances_DisplayObjectContainer_getChildAt::TMethod TFunc_Instances_DisplayObjectContainer_getChildAt::Method = &Instances::DisplayObjectContainer::getChildAt;
template <> const TFunc_Instances_DisplayObjectContainer_getChildByName::TMethod TFunc_Instances_DisplayObjectContainer_getChildByName::Method = &Instances::DisplayObjectContainer::getChildByName;
template <> const TFunc_Instances_DisplayObjectContainer_getChildIndex::TMethod TFunc_Instances_DisplayObjectContainer_getChildIndex::Method = &Instances::DisplayObjectContainer::getChildIndex;
template <> const TFunc_Instances_DisplayObjectContainer_getObjectsUnderPoint::TMethod TFunc_Instances_DisplayObjectContainer_getObjectsUnderPoint::Method = &Instances::DisplayObjectContainer::getObjectsUnderPoint;
template <> const TFunc_Instances_DisplayObjectContainer_removeChild::TMethod TFunc_Instances_DisplayObjectContainer_removeChild::Method = &Instances::DisplayObjectContainer::removeChild;
template <> const TFunc_Instances_DisplayObjectContainer_removeChildAt::TMethod TFunc_Instances_DisplayObjectContainer_removeChildAt::Method = &Instances::DisplayObjectContainer::removeChildAt;
template <> const TFunc_Instances_DisplayObjectContainer_setChildIndex::TMethod TFunc_Instances_DisplayObjectContainer_setChildIndex::Method = &Instances::DisplayObjectContainer::setChildIndex;
template <> const TFunc_Instances_DisplayObjectContainer_swapChildren::TMethod TFunc_Instances_DisplayObjectContainer_swapChildren::Method = &Instances::DisplayObjectContainer::swapChildren;
template <> const TFunc_Instances_DisplayObjectContainer_swapChildrenAt::TMethod TFunc_Instances_DisplayObjectContainer_swapChildrenAt::Method = &Instances::DisplayObjectContainer::swapChildrenAt;

namespace Instances
{
    DisplayObjectContainer::DisplayObjectContainer(InstanceTraits::Traits& t)
    : Instances::InteractiveObject(t)
//##protect##"instance::DisplayObjectContainer::DisplayObjectContainer()$data"
//##protect##"instance::DisplayObjectContainer::DisplayObjectContainer()$data"
    {
//##protect##"instance::DisplayObjectContainer::DisplayObjectContainer()$code"
//##protect##"instance::DisplayObjectContainer::DisplayObjectContainer()$code"
    }

    void DisplayObjectContainer::mouseChildrenGet(bool& result)
    {
//##protect##"instance::DisplayObjectContainer::mouseChildrenGet()"
        SF_UNUSED1(result);
        result = !GetDisplayObjContainer()->IsMouseChildrenDisabledFlagSet();
//##protect##"instance::DisplayObjectContainer::mouseChildrenGet()"
    }
    void DisplayObjectContainer::mouseChildrenSet(Value& result, bool value)
    {
//##protect##"instance::DisplayObjectContainer::mouseChildrenSet()"
        SF_UNUSED2(result, value);
        GetDisplayObjContainer()->SetMouseChildrenDisabledFlag(!value);
//##protect##"instance::DisplayObjectContainer::mouseChildrenSet()"
    }
    void DisplayObjectContainer::numChildrenGet(SInt32& result)
    {
//##protect##"instance::DisplayObjectContainer::numChildrenGet()"
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* spr = pDispObj->CharToDisplayObjContainer_Unsafe();
        SF_ASSERT(spr);
        result = (int)spr->GetNumChildren();
//##protect##"instance::DisplayObjectContainer::numChildrenGet()"
    }
    void DisplayObjectContainer::tabChildrenGet(bool& result)
    {
//##protect##"instance::DisplayObjectContainer::tabChildrenGet()"
        SF_UNUSED1(result);
        result = !GetDisplayObjContainer()->IsTabChildrenDisabledFlagSet();
//##protect##"instance::DisplayObjectContainer::tabChildrenGet()"
    }
    void DisplayObjectContainer::tabChildrenSet(Value& result, bool value)
    {
//##protect##"instance::DisplayObjectContainer::tabChildrenSet()"
        SF_UNUSED2(result, value);
        GetDisplayObjContainer()->SetTabChildrenDisabledFlag(!value);

        // fire tabChildrenChange event
        SPtr<Event> e = 
            CreateEventObject(GetVM().GetStringManager().CreateConstString("tabChildrenChange"), true, false);
        Dispatch(e, pDispObj);

//##protect##"instance::DisplayObjectContainer::tabChildrenSet()"
    }
    void DisplayObjectContainer::textSnapshotGet(Value& result)
    {
//##protect##"instance::DisplayObjectContainer::textSnapshotGet()"
        SF_UNUSED(result);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        SPtr<TextSnapshot> ts;

        SPtr<AS3::Object> obj = asvm.GetClass("flash.text.TextSnapshot");
        asvm.ConstructInstance(ts, obj);
        SF_ASSERT(ts);

        SF_ASSERT(pDispObj && pDispObj->IsSprite());
        Sprite* psprite = pDispObj->CharToSprite_Unsafe();
        ts->ProcessSnapshot(psprite);
        result = ts;
#endif // #ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
//##protect##"instance::DisplayObjectContainer::textSnapshotGet()"
    }
    void DisplayObjectContainer::addChild(Value& result, Instances::DisplayObject* child)
    {
//##protect##"instance::DisplayObjectContainer::addChild()"
        SF_UNUSED2(result, child);
        if (!child)
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("child")));
        if (child == this)
            return GetVM().ThrowArgumentError(VM::Error(VM::eAddObjectItselfError, GetVM()));

        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        SF_ASSERT(container);
        
        // make sure child's stage obj exists
        if (!child->pDispObj)
            child->CreateStageObject();
        SF_ASSERT(child->pDispObj);

        ToAvmDisplayObjContainer(container)->AddChild(child->pDispObj);
        result = child;
//##protect##"instance::DisplayObjectContainer::addChild()"
    }
    void DisplayObjectContainer::addChildAt(Value& result, Instances::DisplayObject* child, SInt32 index)
    {
//##protect##"instance::DisplayObjectContainer::addChildAt()"
        SF_UNUSED2(result, child);
        if (!child)
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("child")));
        if (child == this)
            return GetVM().ThrowArgumentError(VM::Error(VM::eAddObjectItselfError, GetVM()));

        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        SF_ASSERT(container);

        // make sure child's stage obj exists
        if (!child->pDispObj)
            child->CreateStageObject();
        SF_ASSERT(child->pDispObj);

        result.SetNull();
        if (index < 0 || index > (SInt32)container->GetNumChildren())
            GetVM().ThrowRangeError(VM::Error(VM::eParamRangeError, GetVM()));
        else
        {
            ToAvmDisplayObjContainer(container)->AddChildAt(child->pDispObj, index);
            result = child;
        }
//##protect##"instance::DisplayObjectContainer::addChildAt()"
    }
    void DisplayObjectContainer::areInaccessibleObjectsUnderPoint(bool& result, Instances::Point* point)
    {
//##protect##"instance::DisplayObjectContainer::areInaccessibleObjectsUnderPoint()"
        SF_UNUSED2(result, point);
        WARN_NOT_IMPLEMENTED("DisplayObjectContainer::areInaccessibleObjectsUnderPoint()");
//##protect##"instance::DisplayObjectContainer::areInaccessibleObjectsUnderPoint()"
    }
    void DisplayObjectContainer::contains(bool& result, Instances::DisplayObject* child)
    {
//##protect##"instance::DisplayObjectContainer::contains()"
        SF_UNUSED2(result, child);
        if (!child)
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("child")));

        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        result = container->Contains(child->pDispObj);
//##protect##"instance::DisplayObjectContainer::contains()"
    }
    void DisplayObjectContainer::getChildAt(Value& result, SInt32 index)
    {
//##protect##"instance::DisplayObjectContainer::getChildAt()"
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        SPtr<DisplayObject> obj = ToAvmDisplayObjContainer(container)->GetAS3ChildAt(index);
        if (!obj)
            GetVM().ThrowRangeError(VM::Error(VM::eParamRangeError, GetVM()));
        else
            result = obj;
//##protect##"instance::DisplayObjectContainer::getChildAt()"
    }
    void DisplayObjectContainer::getChildByName(Value& result, const ASString& name)
    {
//##protect##"instance::DisplayObjectContainer::getChildByName()"
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        SPtr<DisplayObject> obj = ToAvmDisplayObjContainer(container)->GetAS3ChildByName(name);
        if (!obj)
            result.SetNull();
        else
            result = obj;
//##protect##"instance::DisplayObjectContainer::getChildByName()"
    }
    void DisplayObjectContainer::getChildIndex(SInt32& result, Instances::DisplayObject* child)
    {
//##protect##"instance::DisplayObjectContainer::getChildIndex()"
        SF_UNUSED2(result, child);
        if (!child)
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("child")));

        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        
        SPInt idx = container->GetChildIndex(child->pDispObj);
        if (idx < 0)
            return GetVM().ThrowArgumentError(VM::Error(VM::eMustBeChildError, GetVM() SF_DEBUG_ARG("DisplayObject")));
        
        result = (SInt32)idx;
//##protect##"instance::DisplayObjectContainer::getChildIndex()"
    }
    void DisplayObjectContainer::getObjectsUnderPoint(Value& result, Instances::Point* point)
    {
//##protect##"instance::DisplayObjectContainer::getObjectsUnderPoint()"
        SF_UNUSED2(result, point);
        
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        // convert the point from stage coord space to conttainer's space
        GFx::DisplayObject::Matrix m = container->GetWorldMatrix();
        PointF pt((float)PixelsToTwips(point->GetX()), (float)PixelsToTwips(point->GetY()));
        Render::PointF p = m.TransformByInverse(pt);
        ArrayDH<Ptr<DisplayObjectBase> > arr(GetVM().GetMemoryHeap());
        ToAvmDisplayObjContainer(container)->GetObjectsUnderPoint(&arr, p);

        // Create an array
        SPtr<Instances::Array> asArray = GetVM().MakeArray();

        for (UPInt i = 0, n = arr.GetSize(); i < n; ++i)
        {
            if (arr[i]->IsScriptableObject())
            {
                AvmDisplayObj* avobj = ToAvmDisplayObj(arr[i]->CharToScriptableObject_Unsafe());
                if (!avobj->GetAS3Obj())
                    avobj->CreateASInstance(true); // make sure AS3 instance exists
                asArray->PushBack(Value(avobj->GetAS3Obj()));
            }
        }
        result = asArray;
//##protect##"instance::DisplayObjectContainer::getObjectsUnderPoint()"
    }
    void DisplayObjectContainer::removeChild(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::DisplayObjectContainer::removeChild()"
        SF_UNUSED(result);
        if (argc < 1 || argv[0].IsNullOrUndefined() || !argv[0].IsObject())
            return GetVM().ThrowTypeError(VM::Error(VM::eNullPointerError, GetVM() SF_DEBUG_ARG("child")));

        //@TODO: revise:        
        // 1) do we need to throw exception if type is wrong?
        AS3::Object* object = argv[0].GetObject();
        if (!object || !AreDisplayObjectTraits(object))
            return result.SetUndefined();
        SF_ASSERT(GetVM().IsOfType(argv[0], "flash.display.DisplayObject"));

        Instances::DisplayObject* child = static_cast<Instances::DisplayObject*>(object);
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        SF_ASSERT(container);

        // make sure child's stage obj exists
        if (child->pDispObj)
        {
            AvmDisplayObjContainer* avmObj = ToAvmDisplayObjContainer(container);
            avmObj->RemoveChild(child->pDispObj);
        }
        // do we need to addref child here??? (!AB) 
        result = child;
//##protect##"instance::DisplayObjectContainer::removeChild()"
    }
    void DisplayObjectContainer::removeChildAt(Value& result, SInt32 index)
    {
//##protect##"instance::DisplayObjectContainer::removeChildAt()"
        SF_UNUSED(result);
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        SF_ASSERT(container);

        result.SetNull();

        // make sure child's stage obj exists
        AvmDisplayObjContainer* avmObj = ToAvmDisplayObjContainer(container);
        
        GFx::DisplayObjectBase* dobj_ = container->GetChildAt(index);
        if (dobj_)
        {
            GFx::DisplayObject* dobj = static_cast<GFx::DisplayObject*>(dobj_);
            //ToAvmDisplayObj(dobj)->CreateASInstance(true);
            //SF_ASSERT(ToAvmDisplayObj(dobj)->GetAS3Obj());
            if (ToAvmDisplayObj(dobj)->GetAS3Obj()) //?AB
                // do we need to addref child here??? (!AB) 
                result = ToAvmDisplayObj(dobj)->GetAS3Obj();
        }
        else
        {
            GetVM().ThrowRangeError(VM::Error(VM::eParamRangeError, GetVM()));
            return;
        }
        avmObj->RemoveChildAt(index);

//##protect##"instance::DisplayObjectContainer::removeChildAt()"
    }
    void DisplayObjectContainer::setChildIndex(Value& result, Instances::DisplayObject* child, SInt32 index)
    {
//##protect##"instance::DisplayObjectContainer::setChildIndex()"
        SF_UNUSED3(result, child, index);
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();
        
        if (child->pDispObj)
        {
            if (index < 0) index = 0; //?
            AvmDisplayObjContainer* avmObj = ToAvmDisplayObjContainer(container);
            avmObj->SetChildIndex(child->pDispObj, (unsigned)index);
        }
//##protect##"instance::DisplayObjectContainer::setChildIndex()"
    }
    void DisplayObjectContainer::swapChildren(Value& result, Instances::DisplayObject* child1, Instances::DisplayObject* child2)
    {
//##protect##"instance::DisplayObjectContainer::swapChildren()"
        SF_UNUSED3(result, child1, child2);
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        if (child1->pDispObj && child2->pDispObj)
        {
            AvmDisplayObjContainer* avmObj = ToAvmDisplayObjContainer(container);
            avmObj->SwapChildren(child1->pDispObj, child2->pDispObj);
        }
//##protect##"instance::DisplayObjectContainer::swapChildren()"
    }
    void DisplayObjectContainer::swapChildrenAt(Value& result, SInt32 index1, SInt32 index2)
    {
//##protect##"instance::DisplayObjectContainer::swapChildrenAt()"
        SF_UNUSED3(result, index1, index2);
        SF_ASSERT(pDispObj && pDispObj->IsDisplayObjContainer());
        GFx::DisplayObjContainer* container = pDispObj->CharToDisplayObjContainer_Unsafe();

        if (index1 < 0) index1 = 0; //?
        if (index2 < 0) index2 = 0; //?
        AvmDisplayObjContainer* avmObj = ToAvmDisplayObjContainer(container);
        avmObj->SwapChildrenAt((unsigned)index1, (unsigned)index2);
//##protect##"instance::DisplayObjectContainer::swapChildrenAt()"
    }

//##protect##"instance$methods"
    DisplayObjectContainer::~DisplayObjectContainer()
    {
    }

    void DisplayObjectContainer::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        InteractiveObject::ForEachChild_GC(prcc, op);
        if (HasDisplayObject())
        {
            GFx::DisplayObjContainer* dobj = GetDisplayObjContainer();
            unsigned n = dobj->GetNumChildren();
            for (unsigned i = 0; i < n; ++i)
            {
                GFx::DisplayObjectBase* chb = dobj->GetChildAt(i);
                GFx::DisplayObject* ch = chb->CharToScriptableObject();
                if (ch)
                {
                    SPtr<Instances::DisplayObject>* pas3 = ToAvmDisplayObj(ch)->GetCollectibleAS3Ptr();
                    //!AB: we don't need to "release" or "disable" the collectible pointer we are getting
                    // from 'ch'. The only reason to iterate through it here is to get its children during
                    // 'mark' or 'scan' operations.
                    if (pas3 && (prcc->IsInCollect() || (!Collector::IsDisableOp(op) && !Collector::IsReleaseOp(op))))
                    {
                        AS3::ForEachChild_GC<DisplayObject, Mem_Stat>(prcc, *pas3, op SF_DEBUG_ARG(*this));
                    }
                }
            }
        }
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo DisplayObjectContainer::ti[DisplayObjectContainer::ThunkInfoNum] = {
        {TFunc_Instances_DisplayObjectContainer_mouseChildrenGet::Func, &BooleanCI, "mouseChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObjectContainer_mouseChildrenSet::Func, NULL, "mouseChildren", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_numChildrenGet::Func, &int_CI, "numChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObjectContainer_tabChildrenGet::Func, &BooleanCI, "tabChildren", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObjectContainer_tabChildrenSet::Func, NULL, "tabChildren", NULL, CT_Set, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_textSnapshotGet::Func, &TextSnapshotCI, "textSnapshot", NULL, CT_Get, 0, 0},
        {TFunc_Instances_DisplayObjectContainer_addChild::Func, &DisplayObjectCI, "addChild", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_addChildAt::Func, &DisplayObjectCI, "addChildAt", NULL, CT_Method, 2, 2},
        {TFunc_Instances_DisplayObjectContainer_areInaccessibleObjectsUnderPoint::Func, &BooleanCI, "areInaccessibleObjectsUnderPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_contains::Func, &BooleanCI, "contains", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_getChildAt::Func, &DisplayObjectCI, "getChildAt", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_getChildByName::Func, &DisplayObjectCI, "getChildByName", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_getChildIndex::Func, &int_CI, "getChildIndex", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_getObjectsUnderPoint::Func, &ArrayCI, "getObjectsUnderPoint", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_removeChild::Func, &DisplayObjectCI, "removeChild", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_DisplayObjectContainer_removeChildAt::Func, &DisplayObjectCI, "removeChildAt", NULL, CT_Method, 1, 1},
        {TFunc_Instances_DisplayObjectContainer_setChildIndex::Func, NULL, "setChildIndex", NULL, CT_Method, 2, 2},
        {TFunc_Instances_DisplayObjectContainer_swapChildren::Func, NULL, "swapChildren", NULL, CT_Method, 2, 2},
        {TFunc_Instances_DisplayObjectContainer_swapChildrenAt::Func, NULL, "swapChildrenAt", NULL, CT_Method, 2, 2},
    };

    DisplayObjectContainer::DisplayObjectContainer(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::DisplayObjectContainer::DisplayObjectContainer()"
        SetTraitsType(Traits_DisplayObjectContainer);
//##protect##"InstanceTraits::DisplayObjectContainer::DisplayObjectContainer()"
        SetMemSize(sizeof(Instances::DisplayObjectContainer));

    }

    Pickable<Instances::DisplayObjectContainer> DisplayObjectContainer::MakeInstance(Traits& t)
    {
        return Pickable<Instances::DisplayObjectContainer>(new(t.Alloc()) Instances::DisplayObjectContainer(t));
    }

    void DisplayObjectContainer::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    DisplayObjectContainer::DisplayObjectContainer(VM& vm)
    : Traits(vm, DisplayObjectContainerCI)
    {
//##protect##"ClassTraits::DisplayObjectContainer::DisplayObjectContainer()"
        SetTraitsType(Traits_DisplayObjectContainer);
//##protect##"ClassTraits::DisplayObjectContainer::DisplayObjectContainer()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::DisplayObjectContainer(vm, DisplayObjectContainerCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DisplayObjectContainer::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DisplayObjectContainer(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DisplayObjectContainerCI = {
    ClassInfo::CompileTime,
    "DisplayObjectContainer", "flash.display", &InteractiveObjectCI,
    ClassTraits::DisplayObjectContainer::MakeClassTraits,
    0,
    0,
    InstanceTraits::DisplayObjectContainer::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::DisplayObjectContainer::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

