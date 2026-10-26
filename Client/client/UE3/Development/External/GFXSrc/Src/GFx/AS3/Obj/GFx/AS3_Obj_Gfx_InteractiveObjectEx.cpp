//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_InteractiveObjectEx.cpp
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_InteractiveObjectEx.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../../AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    InteractiveObjectEx::InteractiveObjectEx(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::InteractiveObjectEx::InteractiveObjectEx()"
//##protect##"class_::InteractiveObjectEx::InteractiveObjectEx()"
    }
    void InteractiveObjectEx::setHitTestDisable(Value& result, Instances::InteractiveObject* o, bool f)
    {
//##protect##"class_::InteractiveObjectEx::setHitTestDisable()"
        SF_UNUSED3(result, o, f);
        if (o && o->pDispObj && o->pDispObj->IsInteractiveObject())
        {
            o->pDispObj->CharToInteractiveObject_Unsafe()->SetHitTestDisableFlag(f);
        }
//##protect##"class_::InteractiveObjectEx::setHitTestDisable()"
    }
    void InteractiveObjectEx::getHitTestDisable(bool& result, Instances::InteractiveObject* o)
    {
//##protect##"class_::InteractiveObjectEx::getHitTestDisable()"
        SF_UNUSED2(result, o);
        if (o && o->pDispObj && o->pDispObj->IsInteractiveObject())
        {
            result = o->pDispObj->CharToInteractiveObject_Unsafe()->IsHitTestDisableFlagSet();
        }
        else
            result = false;
//##protect##"class_::InteractiveObjectEx::getHitTestDisable()"
    }
    void InteractiveObjectEx::setTopmostLevel(Value& result, Instances::InteractiveObject* o, bool f)
    {
//##protect##"class_::InteractiveObjectEx::setTopmostLevel()"
        SF_UNUSED3(result, o, f);
        if (o && o->pDispObj && o->pDispObj->IsInteractiveObject())
        {
            GFx::InteractiveObject* iobj = o->pDispObj->CharToInteractiveObject_Unsafe();
            iobj->SetTopmostLevelFlag(f);
            if (iobj->IsTopmostLevelFlagSet())
                static_cast<ASVM&>(GetVM()).GetMovieImpl()->AddTopmostLevelCharacter(iobj);
            else
                static_cast<ASVM&>(GetVM()).GetMovieImpl()->RemoveTopmostLevelCharacter(iobj);
        }
//##protect##"class_::InteractiveObjectEx::setTopmostLevel()"
    }
    void InteractiveObjectEx::getTopmostLevel(bool& result, Instances::InteractiveObject* o)
    {
//##protect##"class_::InteractiveObjectEx::getTopmostLevel()"
        SF_UNUSED2(result, o);
        if (o && o->pDispObj && o->pDispObj->IsInteractiveObject())
        {
            result = o->pDispObj->CharToInteractiveObject_Unsafe()->IsTopmostLevelFlagSet();
        }
        else
            result = false;
//##protect##"class_::InteractiveObjectEx::getTopmostLevel()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc2<Classes::InteractiveObjectEx, Classes::InteractiveObjectEx::mid_setHitTestDisable, Value, Instances::InteractiveObject*, bool> TFunc_Classes_InteractiveObjectEx_setHitTestDisable;
typedef ThunkFunc1<Classes::InteractiveObjectEx, Classes::InteractiveObjectEx::mid_getHitTestDisable, bool, Instances::InteractiveObject*> TFunc_Classes_InteractiveObjectEx_getHitTestDisable;
typedef ThunkFunc2<Classes::InteractiveObjectEx, Classes::InteractiveObjectEx::mid_setTopmostLevel, Value, Instances::InteractiveObject*, bool> TFunc_Classes_InteractiveObjectEx_setTopmostLevel;
typedef ThunkFunc1<Classes::InteractiveObjectEx, Classes::InteractiveObjectEx::mid_getTopmostLevel, bool, Instances::InteractiveObject*> TFunc_Classes_InteractiveObjectEx_getTopmostLevel;

template <> const TFunc_Classes_InteractiveObjectEx_setHitTestDisable::TMethod TFunc_Classes_InteractiveObjectEx_setHitTestDisable::Method = &Classes::InteractiveObjectEx::setHitTestDisable;
template <> const TFunc_Classes_InteractiveObjectEx_getHitTestDisable::TMethod TFunc_Classes_InteractiveObjectEx_getHitTestDisable::Method = &Classes::InteractiveObjectEx::getHitTestDisable;
template <> const TFunc_Classes_InteractiveObjectEx_setTopmostLevel::TMethod TFunc_Classes_InteractiveObjectEx_setTopmostLevel::Method = &Classes::InteractiveObjectEx::setTopmostLevel;
template <> const TFunc_Classes_InteractiveObjectEx_getTopmostLevel::TMethod TFunc_Classes_InteractiveObjectEx_getTopmostLevel::Method = &Classes::InteractiveObjectEx::getTopmostLevel;

namespace ClassTraits
{
    const ThunkInfo InteractiveObjectEx::ti[InteractiveObjectEx::ThunkInfoNum] = {
        {TFunc_Classes_InteractiveObjectEx_setHitTestDisable::Func, NULL, "setHitTestDisable", NULL, CT_Method, 2, 2},
        {TFunc_Classes_InteractiveObjectEx_getHitTestDisable::Func, &BooleanCI, "getHitTestDisable", NULL, CT_Method, 1, 1},
        {TFunc_Classes_InteractiveObjectEx_setTopmostLevel::Func, NULL, "setTopmostLevel", NULL, CT_Method, 2, 2},
        {TFunc_Classes_InteractiveObjectEx_getTopmostLevel::Func, &BooleanCI, "getTopmostLevel", NULL, CT_Method, 1, 1},
    };
    InteractiveObjectEx::InteractiveObjectEx(VM& vm)
    : Traits(vm, InteractiveObjectExCI)
    {
//##protect##"ClassTraits::InteractiveObjectEx::InteractiveObjectEx()"
//##protect##"ClassTraits::InteractiveObjectEx::InteractiveObjectEx()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, InteractiveObjectExCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::InteractiveObjectEx(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> InteractiveObjectEx::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) InteractiveObjectEx(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo InteractiveObjectExCI = {
    ClassInfo::CompileTime,
    "InteractiveObjectEx", "scaleform.gfx", &ObjectCI,
    ClassTraits::InteractiveObjectEx::MakeClassTraits,
    ClassTraits::InteractiveObjectEx::ThunkInfoNum,
    0,
    0,
    0,
    ClassTraits::InteractiveObjectEx::ti,
    NULL,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

