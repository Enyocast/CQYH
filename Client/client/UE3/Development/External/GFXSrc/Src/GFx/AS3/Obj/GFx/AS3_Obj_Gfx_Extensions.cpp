//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_Extensions.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Gfx_Extensions.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    Extensions::Extensions(ClassTraits::Traits& t)
    : Class(t)
    , EDGEAA_INHERIT(0)
    , EDGEAA_ON(1)
    , EDGEAA_OFF(2)
    , EDGEAA_DISABLE(3)
    {
//##protect##"class_::Extensions::Extensions()"
//##protect##"class_::Extensions::Extensions()"
    }
    void Extensions::enabledSet(Value& result, bool value)
    {
//##protect##"class_::Extensions::enabledSet()"
        
        SF_UNUSED(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.ExtensionsEnabled = value;

//##protect##"class_::Extensions::enabledSet()"
    }
    void Extensions::enabledGet(bool& result)
    {
//##protect##"class_::Extensions::enabledGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        result = asvm.ExtensionsEnabled;

//##protect##"class_::Extensions::enabledGet()"
    }
    void Extensions::noInvisibleAdvanceSet(Value& result, bool value)
    {
//##protect##"class_::Extensions::noInvisibleAdvanceSet()"
        
        SF_UNUSED1(result);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            proot->SetNoInvisibleAdvanceFlag(value);
        }

//##protect##"class_::Extensions::noInvisibleAdvanceSet()"
    }
    void Extensions::noInvisibleAdvanceGet(bool& result)
    {
//##protect##"class_::Extensions::noInvisibleAdvanceGet()"
        
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            result = proot->IsNoInvisibleAdvanceFlagSet();
        }

//##protect##"class_::Extensions::noInvisibleAdvanceGet()"
    }
    void Extensions::getTopMostEntity(Value& result, Value::Number x, Value::Number y, bool testAll)
    {
//##protect##"class_::Extensions::getTopMostEntity()"
        SF_UNUSED4(result, x, y, testAll);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        MovieImpl* proot = asvm.GetMovieImpl();

        // three parameters version: _x and _y in _root coordinates, optional boolean - testAll
        x = PixelsToTwips(x);
        y = PixelsToTwips(y);
        PointF mousePos;

        if (proot->GetMainContainer())
        {
            // x and y vars are in _root coords. Need to transform them
            // into world coords
            Matrix2F m = proot->GetMainContainer()->GetWorldMatrix();
            PointF a;
            a.SetPoint(float(x), float(y));
            m.Transform(&mousePos, a);
        }
        else
        {
            result.SetNull();
            return;
        }
        GFx::InteractiveObject* ptopCh = proot->GetTopMostEntity(mousePos, 0, testAll);
        if (ptopCh)
        {
            AvmInteractiveObj* avobj = ToAvmInteractiveObj(ptopCh);
            avobj->CreateASInstance(true);
            result = avobj->GetAS3Obj();
        }
        else
            result.SetNull();
//##protect##"class_::Extensions::getTopMostEntity()"
    }
    void Extensions::getMouseTopMostEntity(Value& result, bool testAll, UInt32 mouseIndex)
    {
//##protect##"class_::Extensions::getMouseTopMostEntity()"
        SF_UNUSED3(result, testAll, mouseIndex);

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        MovieImpl* proot = asvm.GetMovieImpl();
			

        if (mouseIndex >= proot->GetMouseCursorCount())
            return; // invalid index of mouse
        SF_ASSERT(proot->GetMouseState(mouseIndex)); // only first mouse is supported for now
        PointF mousePos;
        mousePos = proot->GetMouseState(mouseIndex)->GetLastPosition();
        
		// oscar@snda
		GFx::InteractiveObject* ptopCh = 0;
// 		if(proot->pExtIntfHandler)
// 		{
// 			ptopCh = proot->pExtIntfHandler->GetTopMostEntity(mousePos, mouseIndex, testAll);
// 		}

		if(!ptopCh)
		{
			ptopCh = proot->GetTopMostEntity(mousePos, mouseIndex, testAll);
		}

		// oscar@snda

        if (ptopCh)
        {
            AvmInteractiveObj* avobj = ToAvmInteractiveObj(ptopCh);
            avobj->CreateASInstance(true);
            result = avobj->GetAS3Obj();
        }
        else
            result.SetNull();
//##protect##"class_::Extensions::getMouseTopMostEntity()"
    }
    void Extensions::setMouseCursorType(Value& result, const ASString& cursor, UInt32 mouseIndex)
    {
//##protect##"class_::Extensions::setMouseCursorType()"
        SF_UNUSED3(result, cursor, mouseIndex);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.GetMovieRoot()->SetMouseCursorType(cursor, mouseIndex);
//##protect##"class_::Extensions::setMouseCursorType()"
    }
    void Extensions::getMouseCursorType(ASString& result, UInt32 mouseIndex)
    {
//##protect##"class_::Extensions::getMouseCursorType()"
        SF_UNUSED2(result, mouseIndex);
        ASVM& asvm = static_cast<ASVM&>(GetVM());
        asvm.GetMovieRoot()->GetMouseCursorType(result, mouseIndex);
//##protect##"class_::Extensions::getMouseCursorType()"
    }
    void Extensions::getEdgeAAMode(UInt32& result, Instances::DisplayObject* dispObj)
    {
//##protect##"class_::Extensions::getEdgeAAMode()"

        GFx::DisplayObject* pd = dispObj->pDispObj;
        SF_ASSERT(pd);
        switch (pd->GetRenderNode()->GetEdgeAAMode())
        {
        case EdgeAA_On:         result = EDGEAA_ON;         break;
        case EdgeAA_Off:        result = EDGEAA_OFF;        break;
        case EdgeAA_Disable:    result = EDGEAA_DISABLE;    break;
        default:                result = EDGEAA_INHERIT;    break;
        }

//##protect##"class_::Extensions::getEdgeAAMode()"
    }
    void Extensions::setEdgeAAMode(Value& result, Instances::DisplayObject* dispObj, UInt32 mode)
    {
//##protect##"class_::Extensions::setEdgeAAMode()"

        SF_UNUSED(result);
        GFx::DisplayObject* pd = dispObj->pDispObj;
        SF_ASSERT(pd);
        EdgeAAMode edgeAA = EdgeAA_Inherit;
        if (mode == EDGEAA_DISABLE) 
            edgeAA = EdgeAA_Disable;
        else
        {
            if (mode == EDGEAA_ON)      edgeAA = EdgeAA_On;
            else if (mode == EDGEAA_OFF)  edgeAA = EdgeAA_Off;
        }
        pd->GetRenderNode()->SetEdgeAAMode(edgeAA);

//##protect##"class_::Extensions::setEdgeAAMode()"
    }
    void Extensions::numControllersGet(UInt32& result)
    {
//##protect##"class_::Extensions::numControllersGet()"

        ASVM& asvm = static_cast<ASVM&>(GetVM());
        if (asvm.ExtensionsEnabled)
        {
            MovieImpl* proot = asvm.GetMovieImpl();
            result = proot->GetControllerCount();
        }

//##protect##"class_::Extensions::numControllersGet()"
    }
    void Extensions::visibleRectGet(Value& result)
    {
//##protect##"class_::Extensions::visibleRectGet()"
		ASVM& vm = static_cast<ASVM&>(GetVM());
		MovieImpl* proot = vm.GetMovieImpl();
		RectF visibleRect = proot->GetVisibleFrameRect();
        // Create Rectangle object
        Value params[] = { Value(visibleRect.X1()), 
                           Value(visibleRect.Y1()), 
                           Value(visibleRect.Width()), 
                           Value(visibleRect.Height()) 
        };
        static_cast<ASVM&>(GetVM()).RectangleClass->Construct(result, 4, params, true); 
//##protect##"class_::Extensions::visibleRectGet()"
    }
    void Extensions::isScaleformGet(bool& result)
    {
//##protect##"class_::Extensions::isScaleformGet()"
        result = true;
//##protect##"class_::Extensions::isScaleformGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::Extensions, Classes::Extensions::mid_enabledSet, Value, bool> TFunc_Classes_Extensions_enabledSet;
typedef ThunkFunc0<Classes::Extensions, Classes::Extensions::mid_enabledGet, bool> TFunc_Classes_Extensions_enabledGet;
typedef ThunkFunc1<Classes::Extensions, Classes::Extensions::mid_noInvisibleAdvanceSet, Value, bool> TFunc_Classes_Extensions_noInvisibleAdvanceSet;
typedef ThunkFunc0<Classes::Extensions, Classes::Extensions::mid_noInvisibleAdvanceGet, bool> TFunc_Classes_Extensions_noInvisibleAdvanceGet;
typedef ThunkFunc3<Classes::Extensions, Classes::Extensions::mid_getTopMostEntity, Value, Value::Number, Value::Number, bool> TFunc_Classes_Extensions_getTopMostEntity;
typedef ThunkFunc2<Classes::Extensions, Classes::Extensions::mid_getMouseTopMostEntity, Value, bool, UInt32> TFunc_Classes_Extensions_getMouseTopMostEntity;
typedef ThunkFunc2<Classes::Extensions, Classes::Extensions::mid_setMouseCursorType, Value, const ASString&, UInt32> TFunc_Classes_Extensions_setMouseCursorType;
typedef ThunkFunc1<Classes::Extensions, Classes::Extensions::mid_getMouseCursorType, ASString, UInt32> TFunc_Classes_Extensions_getMouseCursorType;
typedef ThunkFunc1<Classes::Extensions, Classes::Extensions::mid_getEdgeAAMode, UInt32, Instances::DisplayObject*> TFunc_Classes_Extensions_getEdgeAAMode;
typedef ThunkFunc2<Classes::Extensions, Classes::Extensions::mid_setEdgeAAMode, Value, Instances::DisplayObject*, UInt32> TFunc_Classes_Extensions_setEdgeAAMode;
typedef ThunkFunc0<Classes::Extensions, Classes::Extensions::mid_numControllersGet, UInt32> TFunc_Classes_Extensions_numControllersGet;
typedef ThunkFunc0<Classes::Extensions, Classes::Extensions::mid_visibleRectGet, Value> TFunc_Classes_Extensions_visibleRectGet;
typedef ThunkFunc0<Classes::Extensions, Classes::Extensions::mid_isScaleformGet, bool> TFunc_Classes_Extensions_isScaleformGet;

template <> const TFunc_Classes_Extensions_enabledSet::TMethod TFunc_Classes_Extensions_enabledSet::Method = &Classes::Extensions::enabledSet;
template <> const TFunc_Classes_Extensions_enabledGet::TMethod TFunc_Classes_Extensions_enabledGet::Method = &Classes::Extensions::enabledGet;
template <> const TFunc_Classes_Extensions_noInvisibleAdvanceSet::TMethod TFunc_Classes_Extensions_noInvisibleAdvanceSet::Method = &Classes::Extensions::noInvisibleAdvanceSet;
template <> const TFunc_Classes_Extensions_noInvisibleAdvanceGet::TMethod TFunc_Classes_Extensions_noInvisibleAdvanceGet::Method = &Classes::Extensions::noInvisibleAdvanceGet;
template <> const TFunc_Classes_Extensions_getTopMostEntity::TMethod TFunc_Classes_Extensions_getTopMostEntity::Method = &Classes::Extensions::getTopMostEntity;
template <> const TFunc_Classes_Extensions_getMouseTopMostEntity::TMethod TFunc_Classes_Extensions_getMouseTopMostEntity::Method = &Classes::Extensions::getMouseTopMostEntity;
template <> const TFunc_Classes_Extensions_setMouseCursorType::TMethod TFunc_Classes_Extensions_setMouseCursorType::Method = &Classes::Extensions::setMouseCursorType;
template <> const TFunc_Classes_Extensions_getMouseCursorType::TMethod TFunc_Classes_Extensions_getMouseCursorType::Method = &Classes::Extensions::getMouseCursorType;
template <> const TFunc_Classes_Extensions_getEdgeAAMode::TMethod TFunc_Classes_Extensions_getEdgeAAMode::Method = &Classes::Extensions::getEdgeAAMode;
template <> const TFunc_Classes_Extensions_setEdgeAAMode::TMethod TFunc_Classes_Extensions_setEdgeAAMode::Method = &Classes::Extensions::setEdgeAAMode;
template <> const TFunc_Classes_Extensions_numControllersGet::TMethod TFunc_Classes_Extensions_numControllersGet::Method = &Classes::Extensions::numControllersGet;
template <> const TFunc_Classes_Extensions_visibleRectGet::TMethod TFunc_Classes_Extensions_visibleRectGet::Method = &Classes::Extensions::visibleRectGet;
template <> const TFunc_Classes_Extensions_isScaleformGet::TMethod TFunc_Classes_Extensions_isScaleformGet::Method = &Classes::Extensions::isScaleformGet;

namespace ClassTraits
{
    const MemberInfo Extensions::mi[Extensions::MemberInfoNum] = {
        {"EDGEAA_INHERIT", OFFSETOF(Classes::Extensions, EDGEAA_INHERIT), SlotInfo::BT_UInt, 1},
        {"EDGEAA_ON", OFFSETOF(Classes::Extensions, EDGEAA_ON), SlotInfo::BT_UInt, 1},
        {"EDGEAA_OFF", OFFSETOF(Classes::Extensions, EDGEAA_OFF), SlotInfo::BT_UInt, 1},
        {"EDGEAA_DISABLE", OFFSETOF(Classes::Extensions, EDGEAA_DISABLE), SlotInfo::BT_UInt, 1},
    };

    const ThunkInfo Extensions::ti[Extensions::ThunkInfoNum] = {
        {TFunc_Classes_Extensions_enabledSet::Func, NULL, "enabled", NULL, CT_Set, 1, 1},
        {TFunc_Classes_Extensions_enabledGet::Func, &BooleanCI, "enabled", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Extensions_noInvisibleAdvanceSet::Func, NULL, "noInvisibleAdvance", NULL, CT_Set, 1, 1},
        {TFunc_Classes_Extensions_noInvisibleAdvanceGet::Func, &BooleanCI, "noInvisibleAdvance", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Extensions_getTopMostEntity::Func, &DisplayObjectCI, "getTopMostEntity", NULL, CT_Method, 2, 3},
        {TFunc_Classes_Extensions_getMouseTopMostEntity::Func, &DisplayObjectCI, "getMouseTopMostEntity", NULL, CT_Method, 0, 2},
        {TFunc_Classes_Extensions_setMouseCursorType::Func, NULL, "setMouseCursorType", NULL, CT_Method, 1, 2},
        {TFunc_Classes_Extensions_getMouseCursorType::Func, &StringCI, "getMouseCursorType", NULL, CT_Method, 0, 1},
        {TFunc_Classes_Extensions_getEdgeAAMode::Func, &uintCI, "getEdgeAAMode", NULL, CT_Method, 1, 1},
        {TFunc_Classes_Extensions_setEdgeAAMode::Func, NULL, "setEdgeAAMode", NULL, CT_Method, 2, 2},
        {TFunc_Classes_Extensions_numControllersGet::Func, &uintCI, "numControllers", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Extensions_visibleRectGet::Func, &RectangleCI, "visibleRect", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Extensions_isScaleformGet::Func, &BooleanCI, "isScaleform", NULL, CT_Get, 0, 0},
    };
    Extensions::Extensions(VM& vm)
    : Traits(vm, ExtensionsCI)
    {
//##protect##"ClassTraits::Extensions::Extensions()"
//##protect##"ClassTraits::Extensions::Extensions()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, ExtensionsCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Extensions(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Extensions::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Extensions(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ExtensionsCI = {
    ClassInfo::CompileTime,
    "Extensions", "scaleform.gfx", &ObjectCI,
    ClassTraits::Extensions::MakeClassTraits,
    ClassTraits::Extensions::ThunkInfoNum,
    ClassTraits::Extensions::MemberInfoNum,
    0,
    0,
    ClassTraits::Extensions::ti,
    ClassTraits::Extensions::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

