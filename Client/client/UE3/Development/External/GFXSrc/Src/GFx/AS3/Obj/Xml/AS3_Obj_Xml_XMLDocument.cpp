//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLDocument.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Xml_XMLDocument.h"
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
    XMLDocument::XMLDocument(InstanceTraits::Traits& t)
    : Instances::XMLNode(t)
    , docTypeDecl()
    , idMap()
    , ignoreWhite(false)
    , xmlDecl()
//##protect##"instance::XMLDocument::XMLDocument()$data"
//##protect##"instance::XMLDocument::XMLDocument()$data"
    {
//##protect##"instance::XMLDocument::XMLDocument()$code"
//##protect##"instance::XMLDocument::XMLDocument()$code"
    }


//##protect##"instance$methods"
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo XMLDocument::ti[XMLDocument::ThunkInfoNum] = {
        {ThunkInfo::EmptyFunc, &XMLNodeCI, "createElement", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &XMLNodeCI, "createTextNode", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, NULL, "parseXML", NULL, CT_Method, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };
    const MemberInfo XMLDocument::mi[XMLDocument::MemberInfoNum] = {
        {"docTypeDecl", OFFSETOF(Instances::XMLDocument, docTypeDecl), SlotInfo::BT_ObjectCpp, 0},
        {"idMap", OFFSETOF(Instances::XMLDocument, idMap), SlotInfo::BT_ObjectCpp, 0},
        {"ignoreWhite", OFFSETOF(Instances::XMLDocument, ignoreWhite), SlotInfo::BT_Boolean, 0},
        {"xmlDecl", OFFSETOF(Instances::XMLDocument, xmlDecl), SlotInfo::BT_ObjectCpp, 0},
    };


    XMLDocument::XMLDocument(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::XMLDocument::XMLDocument()"
//##protect##"InstanceTraits::XMLDocument::XMLDocument()"
        SetMemSize(sizeof(Instances::XMLDocument));

    }

    Pickable<Instances::XMLDocument> XMLDocument::MakeInstance(Traits& t)
    {
        return Pickable<Instances::XMLDocument>(new(t.Alloc()) Instances::XMLDocument(t));
    }

    void XMLDocument::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits


namespace ClassTraits
{
    XMLDocument::XMLDocument(VM& vm)
    : Traits(vm, XMLDocumentCI)
    {
//##protect##"ClassTraits::XMLDocument::XMLDocument()"
//##protect##"ClassTraits::XMLDocument::XMLDocument()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::XMLDocument(vm, XMLDocumentCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLDocument::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLDocument(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLDocumentCI = {
    ClassInfo::CompileTime,
    "XMLDocument", "flash.xml", &XMLNodeCI,
    ClassTraits::XMLDocument::MakeClassTraits,
    0,
    0,
    InstanceTraits::XMLDocument::ThunkInfoNum,
    InstanceTraits::XMLDocument::MemberInfoNum,
    NULL,
    NULL,
    InstanceTraits::XMLDocument::ti,
    InstanceTraits::XMLDocument::mi,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

