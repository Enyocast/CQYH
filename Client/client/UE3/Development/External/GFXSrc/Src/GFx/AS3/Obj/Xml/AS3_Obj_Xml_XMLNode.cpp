//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLNode.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Xml_XMLNode.h"
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

namespace Instances
{
    XMLNode::XMLNode(InstanceTraits::Traits& t)
    : Instances::Object(t)
    , firstChild()
    , lastChild()
    , nextSibling()
    , nodeName(AS3::DefaultValue<ASString>(GetStringManager()))
    , nodeType()
    , nodeValue(AS3::DefaultValue<ASString>(GetStringManager()))
    , parentNode()
    , previousSibling()
//##protect##"instance::XMLNode::XMLNode()$data"
//##protect##"instance::XMLNode::XMLNode()$data"
    {
//##protect##"instance::XMLNode::XMLNode()$code"
//##protect##"instance::XMLNode::XMLNode()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo XMLNode::ti[XMLNode::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &ObjectCI, "attributes", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "attributes", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &ArrayCI, "childNodes", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "localName", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "namespaceURI", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "prefix", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "appendChild", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &XMLNodeCI, "cloneNode", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "getNamespaceForPrefix", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "getPrefixForNamespace", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "hasChildNodes", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "insertBefore", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "removeNode", NULL, CT_Method, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo XMLNode::mi[XMLNode::MemberInfoNum] = {
        {"firstChild", OFFSETOF(Instances::XMLNode, firstChild), SlotInfo::BT_ObjectCpp, 0},
        {"lastChild", OFFSETOF(Instances::XMLNode, lastChild), SlotInfo::BT_ObjectCpp, 0},
        {"nextSibling", OFFSETOF(Instances::XMLNode, nextSibling), SlotInfo::BT_ObjectCpp, 0},
        {"nodeName", OFFSETOF(Instances::XMLNode, nodeName), SlotInfo::BT_String, 0},
        {"nodeType", OFFSETOF(Instances::XMLNode, nodeType), SlotInfo::BT_UInt, 0},
        {"nodeValue", OFFSETOF(Instances::XMLNode, nodeValue), SlotInfo::BT_String, 0},
        {"parentNode", OFFSETOF(Instances::XMLNode, parentNode), SlotInfo::BT_ObjectCpp, 0},
        {"previousSibling", OFFSETOF(Instances::XMLNode, previousSibling), SlotInfo::BT_ObjectCpp, 0},
    };


    XMLNode::XMLNode(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::XMLNode::XMLNode()"
//##protect##"InstanceTraits::XMLNode::XMLNode()"
        SetMemSize(sizeof(Instances::XMLNode));

    }

    Pickable<Instances::XMLNode> XMLNode::MakeInstance(Traits& t)
    {
        return Pickable<Instances::XMLNode>(new(t.Alloc()) Instances::XMLNode(t));
    }

    void XMLNode::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    XMLNode::XMLNode(VM& vm)
    : Traits(vm, XMLNodeCI)
    {
//##protect##"ClassTraits::XMLNode::XMLNode()"
//##protect##"ClassTraits::XMLNode::XMLNode()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::XMLNode(vm, XMLNodeCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLNode::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLNode(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLNodeCI = {
    ClassInfo::CompileTime,
    "XMLNode", "flash.xml", &ObjectCI,
    ClassTraits::XMLNode::MakeClassTraits,
    0,
    0,
    InstanceTraits::XMLNode::ThunkInfoNum,
    InstanceTraits::XMLNode::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::XMLNode::ti,
    InstanceTraits::XMLNode::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

