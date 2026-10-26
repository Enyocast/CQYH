//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_XMLSignatureValidator.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Security_XMLSignatureValidator.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../Utils/AS3_Obj_Utils_ByteArray.h"
#include "../AS3_Obj_XML.h"
#include "AS3_Obj_Security_IURIDereferencer.h"
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
    const ThunkInfo XMLSignatureValidator_ti[15] = {
        {ThunkInfo::EmptyFunc, &StringCI, "digestStatus", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "identityStatus", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "referencesStatus", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "revocationCheckSetting", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "revocationCheckSetting", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "signerCN", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &StringCI, "signerDN", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &ArrayCI, "signerExtendedKeyUsages", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, &ArrayCI, "signerTrustSettings", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "uriDereferencer", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &BooleanCI, "useSystemTrustStore", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "useSystemTrustStore", NULL, CT_Set, 1, 1},
        {ThunkInfo::EmptyFunc, &StringCI, "validityStatus", NULL, CT_Get, 0, 0},
        {ThunkInfo::EmptyFunc, NULL, "addCertificate", NULL, CT_Method, 2, 2},
        {ThunkInfo::EmptyFunc, NULL, "verify", NULL, CT_Method, 1, 1},
    };

} // namespace InstanceTraits


namespace ClassTraits
{
    XMLSignatureValidator::XMLSignatureValidator(VM& vm)
    : Traits(vm, XMLSignatureValidatorCI)
    {
//##protect##"ClassTraits::XMLSignatureValidator::XMLSignatureValidator()"
//##protect##"ClassTraits::XMLSignatureValidator::XMLSignatureValidator()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::EventDispatcher(vm, XMLSignatureValidatorCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Class(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLSignatureValidator::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLSignatureValidator(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLSignatureValidatorCI = {
    ClassInfo::CompileTime,
    "XMLSignatureValidator", "flash.security", &EventDispatcherCI,
    ClassTraits::XMLSignatureValidator::MakeClassTraits,
    0,
    0,
    15,
    0,
    NULL,
    NULL,
    InstanceTraits::XMLSignatureValidator_ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

