//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLVariables.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_URLVariables.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc1<Instances::URLVariables, Instances::URLVariables::mid_decode, Value, const ASString&> TFunc_Instances_URLVariables_decode;
typedef ThunkFunc0<Instances::URLVariables, Instances::URLVariables::mid_toString, ASString> TFunc_Instances_URLVariables_toString;

template <> const TFunc_Instances_URLVariables_decode::TMethod TFunc_Instances_URLVariables_decode::Method = &Instances::URLVariables::decode;
template <> const TFunc_Instances_URLVariables_toString::TMethod TFunc_Instances_URLVariables_toString::Method = &Instances::URLVariables::toString;

namespace Instances
{
    URLVariables::URLVariables(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::URLVariables::URLVariables()$data"
    , Data(GetVM().GetStringManager().CreateEmptyString())
//##protect##"instance::URLVariables::URLVariables()$data"
    {
//##protect##"instance::URLVariables::URLVariables()$code"
//##protect##"instance::URLVariables::URLVariables()$code"
    }

    void URLVariables::decode(Value& result, const ASString& source)
    {
//##protect##"instance::URLVariables::decode()"
        SF_UNUSED2(result, source);
        // parser state machine
        bool parseName = true;

        StringBuffer name, value;
        const char* pstr;
        UInt32 c = source.GetFirstCharAt(0, &pstr);
        while (c)
        {
            if ((UInt32)'\r' == c)
            {
                // flash converts LF to CR, but console printing
                // required LFs
                c = '\n';
            }
            if ((UInt32)'&' == c)
            {
                StringManager& sm = GetVM().GetStringManager();

                SetProperty(Multiname(
                    GetVM().GetPublicNamespace(), sm.CreateString(name.ToCStr())), 
                    Value(sm.CreateString(value.ToCStr()))).DoNotCheck();
                name.Clear();
                value.Clear();
                parseName = true;
            }
            else if (parseName)
            {
                if ((UInt32)'=' == c)
                {
                    parseName = false;
                }
                else
                {
                    name.AppendChar(c);
                }
            }
            else
            {
                value.AppendChar(c);
            }
            c = source.GetNextChar(&pstr);
        }
        // clean up stragglers
        if (name.GetLength() > 0)
        {
            StringManager& sm = GetVM().GetStringManager();

            SetProperty(Multiname(
                GetVM().GetPublicNamespace(), sm.CreateString(name.ToCStr())), 
                Value(sm.CreateString(value.ToCStr()))).DoNotCheck();
        }    
//##protect##"instance::URLVariables::decode()"
    }
    void URLVariables::toString(ASString& result)
    {
//##protect##"instance::URLVariables::toString()"
        SF_UNUSED1(result);
        result = Data;
//##protect##"instance::URLVariables::toString()"
    }

//##protect##"instance$methods"
    void URLVariables::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc >= 1)
        {
            const Value& v = argv[0];

            if (v.Convert2String(Data))
            {
                Value r;
                decode(r, Data);
            }
        }
    }

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo URLVariables::ti[URLVariables::ThunkInfoNum] = {
        {TFunc_Instances_URLVariables_decode::Func, NULL, "decode", NULL, CT_Method, 1, 1},
        {TFunc_Instances_URLVariables_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    URLVariables::URLVariables(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::URLVariables::URLVariables()"
//##protect##"InstanceTraits::URLVariables::URLVariables()"
        SetMemSize(sizeof(Instances::URLVariables));

    }

    Pickable<Instances::URLVariables> URLVariables::MakeInstance(Traits& t)
    {
        return Pickable<Instances::URLVariables>(new(t.Alloc()) Instances::URLVariables(t));
    }

    void URLVariables::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    URLVariables::URLVariables(VM& vm)
    : Traits(vm, URLVariablesCI)
    {
//##protect##"ClassTraits::URLVariables::URLVariables()"
//##protect##"ClassTraits::URLVariables::URLVariables()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::URLVariables(vm, URLVariablesCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> URLVariables::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) URLVariables(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo URLVariablesCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "URLVariables", "flash.net", &ObjectCI,
    ClassTraits::URLVariables::MakeClassTraits,
    0,
    0,
    InstanceTraits::URLVariables::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::URLVariables::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

