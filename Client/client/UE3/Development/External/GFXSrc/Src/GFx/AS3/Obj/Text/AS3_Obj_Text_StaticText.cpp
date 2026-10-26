//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_StaticText.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Text_StaticText.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//#include "GFx/AS3/AS3_MovieRoot.h"
#include "Kernel/SF_HeapNew.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::StaticText, Instances::StaticText::mid_textGet, ASString> TFunc_Instances_StaticText_textGet;

template <> const TFunc_Instances_StaticText_textGet::TMethod TFunc_Instances_StaticText_textGet::Method = &Instances::StaticText::textGet;

namespace Instances
{
    StaticText::StaticText(InstanceTraits::Traits& t)
    : Instances::DisplayObject(t)
//##protect##"instance::StaticText::StaticText()$data"
//##protect##"instance::StaticText::StaticText()$data"
    {
//##protect##"instance::StaticText::StaticText()$code"
//##protect##"instance::StaticText::StaticText()$code"
    }

    void StaticText::textGet(ASString& result)
    {
//##protect##"instance::StaticText::textGet()"
        SF_UNUSED1(result);
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
        StaticTextCharacter* pch = GetStaticTextChar();
        GFx::StaticTextSnapshotData* snapShot = SF_HEAP_NEW(GetVM().GetMemoryHeap()) GFx::StaticTextSnapshotData();
        snapShot->Add(pch);
        UPInt n = snapShot->GetCharCount();
        result = GetVM().GetStringManager().CreateString(snapShot->GetSubString(0, n, true));
        delete snapShot;
#endif // #ifdef GFX_AS_ENABLE_TEXTSNAPSHOT    
//##protect##"instance::StaticText::textGet()"
    }

//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo StaticText::ti[StaticText::ThunkInfoNum] = {
        {TFunc_Instances_StaticText_textGet::Func, &StringCI, "text", NULL, CT_Get, 0, 0},
    };

    StaticText::StaticText(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::StaticText::StaticText()"
//##protect##"InstanceTraits::StaticText::StaticText()"
        SetMemSize(sizeof(Instances::StaticText));

    }

    Pickable<Instances::StaticText> StaticText::MakeInstance(Traits& t)
    {
        return Pickable<Instances::StaticText>(new(t.Alloc()) Instances::StaticText(t));
    }

    void StaticText::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    StaticText::StaticText(VM& vm)
    : Traits(vm, StaticTextCI)
    {
//##protect##"ClassTraits::StaticText::StaticText()"
//##protect##"ClassTraits::StaticText::StaticText()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::StaticText(vm, StaticTextCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> StaticText::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) StaticText(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo StaticTextCI = {
    ClassInfo::CompileTime,
    "StaticText", "flash.text", &DisplayObjectCI,
    ClassTraits::StaticText::MakeClassTraits,
    0,
    0,
    InstanceTraits::StaticText::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::StaticText::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

