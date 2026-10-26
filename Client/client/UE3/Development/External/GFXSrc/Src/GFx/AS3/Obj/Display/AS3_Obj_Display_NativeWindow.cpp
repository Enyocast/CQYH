//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_NativeWindow.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_NativeWindow.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class Rectangle;
    class Point;
    class NativeMenu;
    class Stage;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo NativeWindow_ti[44] = {
        {ThunkInfo::EmptyFunc, &BooleanCI, "active", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "alwaysInFront", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "alwaysInFront", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &RectangleCI, "bounds", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bounds", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "closed", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "displayState", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "height", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "height", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "maximizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &PointCI, "maxSize", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "maxSize", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "minimizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &PointCI, "minSize", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minSize", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "resizable", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StageCI, "stage", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "systemChrome", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "title", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "title", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "transparent", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "type", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "visible", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "visible", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "width", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "width", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "x", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "x", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "y", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "y", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "activate", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "close", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &PointCI, "globalToScreen", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "maximize", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "minimize", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "notifyUser", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "orderInBackOf", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "orderInFrontOf", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "orderToBack", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "orderToFront", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "restore", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "startMove", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "startResize", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    NativeWindow::NativeWindow(VM& vm)
    : Traits(vm, NativeWindowCI)
    {
//##protect##"ClassTraits::NativeWindow::NativeWindow()"
//##protect##"ClassTraits::NativeWindow::NativeWindow()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, NativeWindowCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> NativeWindow::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) NativeWindow(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo NativeWindowCI = {
    ClassInfo::CompileTime,
    "NativeWindow", "flash.display", &EventDispatcherCI,
    ClassTraits::NativeWindow::MakeClassTraits,
    0,
    0,
    44,
    0,
    NULL,
    NULL,
    InstanceTraits::NativeWindow_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

