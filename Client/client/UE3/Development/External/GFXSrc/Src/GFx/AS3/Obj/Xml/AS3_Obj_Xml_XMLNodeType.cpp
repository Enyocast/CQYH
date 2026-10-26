//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLNodeType.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Xml_XMLNodeType.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    XMLNodeType::XMLNodeType(ClassTraits::Traits& t)
    : Class(t)
    , ELEMENT_NODE(1)
    , TEXT_NODE(3)
    {
//##protect##"class_::XMLNodeType::XMLNodeType()"
//##protect##"class_::XMLNodeType::XMLNodeType()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    const MemberInfo XMLNodeType::mi[XMLNodeType::MemberInfoNum] = {
        {"ELEMENT_NODE", OFFSETOF(Classes::XMLNodeType, ELEMENT_NODE), SlotInfo::BT_UInt, 1},
        {"TEXT_NODE", OFFSETOF(Classes::XMLNodeType, TEXT_NODE), SlotInfo::BT_UInt, 1},
    };

    XMLNodeType::XMLNodeType(VM& vm)
    : Traits(vm, XMLNodeTypeCI)
    {
//##protect##"ClassTraits::XMLNodeType::XMLNodeType()"
//##protect##"ClassTraits::XMLNodeType::XMLNodeType()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, XMLNodeTypeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::XMLNodeType(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLNodeType::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLNodeType(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLNodeTypeCI = {
    ClassInfo::CompileTime,
    "XMLNodeType", "flash.xml", &ObjectCI,
    ClassTraits::XMLNodeType::MakeClassTraits,
    0,
    ClassTraits::XMLNodeType::MemberInfoNum,
    0,
    0,
    NULL,
    ClassTraits::XMLNodeType::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

