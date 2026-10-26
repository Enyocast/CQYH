//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_Screen.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Display_Screen.h"
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
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo Screen_ti[3] = {
        {ThunkInfo::EmptyFunc, &RectangleCI, "bounds", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "colorDepth", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &RectangleCI, "visibleBounds", NULL, CT_Get, 0, 0},
    };

} // namespace InstanceTraits

namespace Classes
{
    Screen::Screen(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Screen::Screen()"
//##protect##"class_::Screen::Screen()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo Screen_ti[1] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "getScreensForRectangle", NULL, CT_Method, 1, 1},
    };
    Screen::Screen(VM& vm)
    : Traits(vm, ScreenCI)
    {
//##protect##"ClassTraits::Screen::Screen()"
//##protect##"ClassTraits::Screen::Screen()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, ScreenCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Screen(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Screen::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Screen(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ScreenCI = {
    ClassInfo::CompileTime,
    "Screen", "flash.display", &EventDispatcherCI,
    ClassTraits::Screen::MakeClassTraits,
    1,
    0,
    3,
    0,
    ClassTraits::Screen_ti,
    NULL,
    InstanceTraits::Screen_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

