//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_DockIcon.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Desktop_DockIcon.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
namespace Classes
{
    class NativeMenu;
}
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo DockIcon_ti[6] = {
        {ThunkInfo::EmptyFunc, &ArrayCI, "bitmaps", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bitmaps", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "height", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "menu", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "width", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "bounce", NULL, CT_Method, 0, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    DockIcon::DockIcon(VM& vm)
    : Traits(vm, DockIconCI)
    {
//##protect##"ClassTraits::DockIcon::DockIcon()"
//##protect##"ClassTraits::DockIcon::DockIcon()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, DockIconCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> DockIcon::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) DockIcon(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo DockIconCI = {
    ClassInfo::CompileTime,
    "DockIcon", "flash.desktop", &InteractiveIconCI,
    ClassTraits::DockIcon::MakeClassTraits,
    0,
    0,
    6,
    0,
    NULL,
    NULL,
    InstanceTraits::DockIcon_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

