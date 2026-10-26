//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Microphone.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Media_Microphone.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Media_SoundTransform.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl

namespace InstanceTraits
{
    const ThunkInfo Microphone_ti[16] = {
        {ThunkInfo::EmptyFunc, &NumberCI, "activityLevel", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &NumberCI, "gain", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "gain", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &int_CI, "index", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &BooleanCI, "muted", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "name", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "rate", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "rate", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &NumberCI, "silenceLevel", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &int_CI, "silenceTimeout", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &SoundTransformCI, "soundTransform", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "soundTransform", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "useEchoSuppression", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "setLoopBack", NULL, CT_Method, 0, 1},
        {ThunkInfo::EmptyFunc, NULL, "setSilenceLevel", NULL, CT_Method, 1, 2},
        {ThunkInfo::EmptyFunc, NULL, "setUseEchoSuppression", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits

namespace Classes
{
    Microphone::Microphone(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::Microphone::Microphone()"
//##protect##"class_::Microphone::Microphone()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const ThunkInfo Microphone_ti[1] = {
        {ThunkInfo::EmptyFunc, &MicrophoneCI, "getMicrophone", NULL, CT_Method, 0, 1},
    };
    Microphone::Microphone(VM& vm)
    : Traits(vm, MicrophoneCI)
    {
//##protect##"ClassTraits::Microphone::Microphone()"
//##protect##"ClassTraits::Microphone::Microphone()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, MicrophoneCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Microphone(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Microphone::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Microphone(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo MicrophoneCI = {
    ClassInfo::CompileTime,
    "Microphone", "flash.media", &EventDispatcherCI,
    ClassTraits::Microphone::MakeClassTraits,
    1,
    0,
    16,
    0,
    ClassTraits::Microphone_ti,
    NULL,
    InstanceTraits::Microphone_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

