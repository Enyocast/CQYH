/**************************************************************************

Filename    :   AS3_Obj_Global.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "AS3_Obj_Global.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
#include "../AS3_AsString.h" // For logging.

#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/AS3/AS3_IntervalTimer.h"

#include "AS3_Obj_Number.h"
#include "AS3_Obj_int.h"
#include "AS3_Obj_uint.h"
#include "AS3_Obj_Boolean.h"
#include "AS3_Obj_String.h"
#include "AS3_Obj_Array.h"
#include "AS3_Obj_QName.h"
#include "AS3_Obj_XML.h"
#include "AS3_Obj_XMLList.h"
#include "AS3_Obj_UserDefined.h" // Because of GlobalObjectScript::InitUserDefinedClassTraits()

namespace Scaleform { namespace GFx { namespace AS3 
{

void escapeMultiByteInternal(VM& vm, ASString& result, const ASString& value);
void unescapeMultiByteInternal(VM& vm, ASString& result, const ASString& value);

//##markup##"obj_global_cpp$package_methods_initialization"
//##begin##"obj_global_cpp$package_methods_initialization"
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_decodeURI;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_decodeURIComponent;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_encodeURI;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_encodeURIComponent;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, bool, Value::Number> TFunc_Instances_GlobalObjectCPP_isNaN;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, bool, Value::Number> TFunc_Instances_GlobalObjectCPP_isFinite;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_parseInt;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, Value::Number, const ASString&> TFunc_Instances_GlobalObjectCPP_parseFloat;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_escape;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_unescape;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, bool, const Value&> TFunc_Instances_GlobalObjectCPP_isXMLName;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_trace;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_print;

template <> const TFunc_Instances_GlobalObjectCPP_decodeURI::TMethod TFunc_Instances_GlobalObjectCPP_decodeURI::Method = &Instances::GlobalObjectCPP::decodeURI;
template <> const TFunc_Instances_GlobalObjectCPP_decodeURIComponent::TMethod TFunc_Instances_GlobalObjectCPP_decodeURIComponent::Method = &Instances::GlobalObjectCPP::decodeURIComponent;
template <> const TFunc_Instances_GlobalObjectCPP_encodeURI::TMethod TFunc_Instances_GlobalObjectCPP_encodeURI::Method = &Instances::GlobalObjectCPP::encodeURI;
template <> const TFunc_Instances_GlobalObjectCPP_encodeURIComponent::TMethod TFunc_Instances_GlobalObjectCPP_encodeURIComponent::Method = &Instances::GlobalObjectCPP::encodeURIComponent;
template <> const TFunc_Instances_GlobalObjectCPP_isNaN::TMethod TFunc_Instances_GlobalObjectCPP_isNaN::Method = &Instances::GlobalObjectCPP::isNaN;
template <> const TFunc_Instances_GlobalObjectCPP_isFinite::TMethod TFunc_Instances_GlobalObjectCPP_isFinite::Method = &Instances::GlobalObjectCPP::isFinite;
template <> const TFunc_Instances_GlobalObjectCPP_parseInt::TMethod TFunc_Instances_GlobalObjectCPP_parseInt::Method = &Instances::GlobalObjectCPP::parseInt;
template <> const TFunc_Instances_GlobalObjectCPP_parseFloat::TMethod TFunc_Instances_GlobalObjectCPP_parseFloat::Method = &Instances::GlobalObjectCPP::parseFloat;
template <> const TFunc_Instances_GlobalObjectCPP_escape::TMethod TFunc_Instances_GlobalObjectCPP_escape::Method = &Instances::GlobalObjectCPP::escape;
template <> const TFunc_Instances_GlobalObjectCPP_unescape::TMethod TFunc_Instances_GlobalObjectCPP_unescape::Method = &Instances::GlobalObjectCPP::unescape;
template <> const TFunc_Instances_GlobalObjectCPP_isXMLName::TMethod TFunc_Instances_GlobalObjectCPP_isXMLName::Method = &Instances::GlobalObjectCPP::isXMLName;
template <> const TFunc_Instances_GlobalObjectCPP_trace::TMethod TFunc_Instances_GlobalObjectCPP_trace::Method = &Instances::GlobalObjectCPP::trace;
template <> const TFunc_Instances_GlobalObjectCPP_print::TMethod TFunc_Instances_GlobalObjectCPP_print::Method = &Instances::GlobalObjectCPP::print;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_fscommand;

template <> const TFunc_Instances_GlobalObjectCPP_fscommand::TMethod TFunc_Instances_GlobalObjectCPP_fscommand::Method = &Instances::GlobalObjectCPP::fscommand;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, Value, UInt32> TFunc_Instances_GlobalObjectCPP_clearInterval;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, Value, UInt32> TFunc_Instances_GlobalObjectCPP_clearTimeout;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, Value, const Value&> TFunc_Instances_GlobalObjectCPP_describeType;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_escapeMultiByte;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, Value, const ASString&> TFunc_Instances_GlobalObjectCPP_getDefinitionByName;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const Value&> TFunc_Instances_GlobalObjectCPP_getQualifiedClassName;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const Value&> TFunc_Instances_GlobalObjectCPP_getQualifiedSuperclassName;
typedef ThunkFunc0<Instances::GlobalObjectCPP, __LINE__, SInt32> TFunc_Instances_GlobalObjectCPP_getTimer;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_setInterval;
typedef ThunkFunc2<Instances::GlobalObjectCPP, __LINE__, Value, unsigned, const Value*> TFunc_Instances_GlobalObjectCPP_setTimeout;
typedef ThunkFunc1<Instances::GlobalObjectCPP, __LINE__, ASString, const ASString&> TFunc_Instances_GlobalObjectCPP_unescapeMultiByte;

template <> const TFunc_Instances_GlobalObjectCPP_clearInterval::TMethod TFunc_Instances_GlobalObjectCPP_clearInterval::Method = &Instances::GlobalObjectCPP::clearInterval;
template <> const TFunc_Instances_GlobalObjectCPP_clearTimeout::TMethod TFunc_Instances_GlobalObjectCPP_clearTimeout::Method = &Instances::GlobalObjectCPP::clearTimeout;
template <> const TFunc_Instances_GlobalObjectCPP_describeType::TMethod TFunc_Instances_GlobalObjectCPP_describeType::Method = &Instances::GlobalObjectCPP::describeType;
template <> const TFunc_Instances_GlobalObjectCPP_escapeMultiByte::TMethod TFunc_Instances_GlobalObjectCPP_escapeMultiByte::Method = &Instances::GlobalObjectCPP::escapeMultiByte;
template <> const TFunc_Instances_GlobalObjectCPP_getDefinitionByName::TMethod TFunc_Instances_GlobalObjectCPP_getDefinitionByName::Method = &Instances::GlobalObjectCPP::getDefinitionByName;
template <> const TFunc_Instances_GlobalObjectCPP_getQualifiedClassName::TMethod TFunc_Instances_GlobalObjectCPP_getQualifiedClassName::Method = &Instances::GlobalObjectCPP::getQualifiedClassName;
template <> const TFunc_Instances_GlobalObjectCPP_getQualifiedSuperclassName::TMethod TFunc_Instances_GlobalObjectCPP_getQualifiedSuperclassName::Method = &Instances::GlobalObjectCPP::getQualifiedSuperclassName;
template <> const TFunc_Instances_GlobalObjectCPP_getTimer::TMethod TFunc_Instances_GlobalObjectCPP_getTimer::Method = &Instances::GlobalObjectCPP::getTimer;
template <> const TFunc_Instances_GlobalObjectCPP_setInterval::TMethod TFunc_Instances_GlobalObjectCPP_setInterval::Method = &Instances::GlobalObjectCPP::setInterval;
template <> const TFunc_Instances_GlobalObjectCPP_setTimeout::TMethod TFunc_Instances_GlobalObjectCPP_setTimeout::Method = &Instances::GlobalObjectCPP::setTimeout;
template <> const TFunc_Instances_GlobalObjectCPP_unescapeMultiByte::TMethod TFunc_Instances_GlobalObjectCPP_unescapeMultiByte::Method = &Instances::GlobalObjectCPP::unescapeMultiByte;

//##end##"obj_global_cpp$package_methods_initialization"

namespace Instances
{
    ///////////////////////////////////////////////////////////////////////
    GlobalObject::GlobalObject(InstanceTraits::Traits& t)
    : Instances::Object(t)
    {
    }

    void GlobalObject::Construct(Value& _this, unsigned argc, const Value* argv, bool extCall)
    {
        SF_UNUSED4(_this, argc, argv, extCall);
        GetVM().ThrowTypeError(VM::Error(VM::eConstructOfNonFunctionError, GetVM()));
    }

    void GlobalObject::Call(const Value& _this, Value& result, unsigned argc, const Value* const argv)
    {
        SF_UNUSED4(result, _this, argc, argv);
        GetVM().ThrowTypeError(VM::Error(VM::eCallOfNonFunctionError, GetVM()
            SF_DEBUG_ARG(GetVM().GetValueTraits(_this).GetName().ToCStr())
            ));
    }

    GlobalObject::~GlobalObject()
    {
    }

    ///////////////////////////////////////////////////////////////////////
    GlobalObjectScript::GlobalObjectScript(InstanceTraits::GlobalObjectScript& t)
    : GlobalObject(t)
    , Initialized(false)
    {
        // Set up slot values ...
        t.SetupSlotValues(GetFile(), GetScript(), *this).DoNotCheck();
    }

    GlobalObjectScript::~GlobalObjectScript()
    {
    }

    void GlobalObjectScript::Execute()
    {
        // Do not call it twice.
        if (Initialized)
            return;

        const SInt32 mbi_ind = GetFile().GetMethodBodyInfoInd(GetScript().GetMethodInfoInd());

        // We do not need to pass arguments to the constructor. It is the Global Object ...
        SF_DEBUG_CODE(static const char* name = "Global Object constructor. Method ind: ";)

        GetVM().AddFrame(
            Value(this), // GlobalObjectScript are already tracked.
            GetFile(),
            mbi_ind,
            Value(this), 
            0, // No args ...
            NULL,
            true, // discard_result
#if 0
            NULL, // No saved scope ...
#else
            &GetTraits().GetStoredScopeStack(),
#endif
            &GetTraits() // That seems to be correct because this function is originated in this class. No inheritance involved.
            SF_DEBUG_ARG(GetStringManager().CreateConstString(name) + Scaleform::AsString(mbi_ind))
            ); 

        if (GetVM().IsException())
            // Oops. Exception.
            return;

        // We assume that the CallFrame above will be executed.
        Initialized = true;
    }

    void GlobalObjectScript::InitUserDefinedClassTraits()
    {
        // This method will set up Script Object with InstanceTraits::UserDefined.
        // It does nothing else.

        using namespace Abc;

        const Abc::ScriptInfo& si = GetScript();
        VMAbcFile& file = GetFile();
        const TraitTable& tt = file.GetTraits();

        for (UPInt i = 0; i < si.GetTraitsCount(); ++i)
        {
            const TraitInfo& ti = si.GetTraitInfo(tt, AbsoluteIndex(i));

            if (ti.GetType() != TraitInfo::tClass)
                continue;

            const Abc::Multiname& name = ti.GetTypeName(file.GetAbcFile());
            const Instances::Namespace& ns = file.GetInternedNamespace(name.GetNamespaceInd());
            ASString str_name = file.GetInternedString(name.GetNameInd());

            // Skip Scaleform classes.
            if (IsScaleformGFx(ns))
                continue;

            const ClassTraits::UserDefined* cud = static_cast<const ClassTraits::UserDefined*>(GetVM().GetRegisteredClassTraits(str_name, ns));

            // Filter out classes, which are defined in other files. This happens.
            if (cud && (&cud->GetFile() == &file))
            {
                InstanceTraits::UserDefined& iud = static_cast<InstanceTraits::UserDefined&>(cud->GetInstanceTraits());

                if (!iud.HasScriptSetUp())
                    iud.SetScript(*this);
//                 else
//                     SF_ASSERT(false);
            }
//             else
//                 SF_ASSERT(false);
        }
    }

    const SlotInfo* GlobalObjectScript::InitializeOnDemand(
        const SlotInfo* si,
        const ASString&,
        const Namespace&,
        UPInt&)
    {
        if (si)
            InitOnDemand();

        return si;
    }

    void GlobalObjectScript::InitOnDemand()
    {
        if (!Initialized)
        {
            // Oops. We need to execute the script.

            // Put a CallFrame.
            Execute();

            if (GetVM().IsException())
                return;

            // Execute just this one CallFrame.
            GetVM().ExecuteCode();

            // This is not necessary. It will be done by Init().
            // Initialized = true;
        }
    }

#ifdef GFX_AS3_VERBOSE
    Scaleform::String GlobalObjectScript::GetAS3ObjectName() const 
    { 
        return Scaleform::String(GetFile().GetAbcFile().GetName()); 
    }
#endif

    ///////////////////////////////////////////////////////////////////////
    MemberInfo GlobalObjectCPP::mi[GlobalObjectCPP::MemberInfoNum] = {
        {"Infinity", OFFSETOF(Instances::GlobalObjectCPP, PositiveInfinity), SlotInfo::BT_Number, 1},
        {"-Infinity", OFFSETOF(Instances::GlobalObjectCPP, NegativeInfinity), SlotInfo::BT_Number, 1},
        {"NaN", OFFSETOF(Instances::GlobalObjectCPP, NaN), SlotInfo::BT_Number, 1},
        {"undefined", OFFSETOF(Instances::GlobalObjectCPP, undefined), SlotInfo::BT_Value, 1},
    };

    GlobalObjectCPP::GlobalObjectCPP(
        VM& vm,
        InstanceTraits::Traits& t
        )
    : GlobalObject(t)
    , PositiveInfinity(NumberUtil::POSITIVE_INFINITY())
    , NegativeInfinity(NumberUtil::NEGATIVE_INFINITY())
    , NaN(NumberUtil::NaN())
    , undefined() // Value is undefined by default.
    {
#ifdef GFX_AS3_SUPPORT
        RegisterClassInfoTable(Classes::ClassRegistrationTable);
#endif

#ifdef SF_AS3_CLASS_AS_SLOT
        AddFixedSlot(vm.GetClassObject());
        AddFixedSlot(vm.GetClassClass());
        AddFixedSlot(vm.GetClassNamespace());
        AddFixedSlot(vm.GetClassFunction());
        // ??? Shouldn't be exposed.
//         AddFixedSlot(vm.GetClassMethodClosure());
        AddFixedSlot(vm.GetClassBoolean());
        AddFixedSlot(vm.GetClassNumber());
        AddFixedSlot(vm.GetClassInt());
        AddFixedSlot(vm.GetClassUInt());
        AddFixedSlot(vm.GetClassString());
        AddFixedSlot(vm.GetClassArray());
#ifdef SF_ENABLE_XML
        AddFixedSlot(vm.GetClassQName());
        AddFixedSlot(vm.GetClassXML());
        AddFixedSlot(vm.GetClassXMLList());
#endif
#else
        SF_UNUSED1(vm);
#endif
        
//##markup##"obj_global_cpp$package_methods_registration"
//##begin##"obj_global_cpp$package_methods_registration"
        {
            const ClassInfo Info = {ClassInfo::CompileTime, "", "", NULL, NULL};
            static const ThunkInfo f[] = {
                {TFunc_Instances_GlobalObjectCPP_decodeURI::Func, &StringCI, "decodeURI", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_decodeURIComponent::Func, &StringCI, "decodeURIComponent", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_encodeURI::Func, &StringCI, "encodeURI", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_encodeURIComponent::Func, &StringCI, "encodeURIComponent", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_isNaN::Func, &BooleanCI, "isNaN", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_isFinite::Func, &BooleanCI, "isFinite", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_parseInt::Func, &NumberCI, "parseInt", NULL, CT_Method, 0, 2},
                {TFunc_Instances_GlobalObjectCPP_parseFloat::Func, &NumberCI, "parseFloat", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_escape::Func, &StringCI, "escape", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_unescape::Func, &StringCI, "unescape", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_isXMLName::Func, &BooleanCI, "isXMLName", NULL, CT_Method, 0, 1},
                {TFunc_Instances_GlobalObjectCPP_trace::Func, NULL, "trace", NULL, CT_Method, 0, 1023},
                {TFunc_Instances_GlobalObjectCPP_print::Func, NULL, "print", NULL, CT_Method, 0, 1023},
            };
            for (unsigned i = 0; i < NUMBEROF(f); ++i)
                Add2VT(Info, f[i]);
        }
#ifndef SF_AS3_NO_FLASH
        {
            const ClassInfo Info = {ClassInfo::CompileTime, "", "flash.system", NULL, NULL};
            static const ThunkInfo f[] = {
                {TFunc_Instances_GlobalObjectCPP_fscommand::Func, NULL, "fscommand", NULL, CT_Method, 0, 1023},
            };
            for (unsigned i = 0; i < NUMBEROF(f); ++i)
                Add2VT(Info, f[i]);
        }
#endif
#ifndef SF_AS3_NO_FLASH
        {
            const ClassInfo Info = {ClassInfo::CompileTime, "", "flash.utils", NULL, NULL};
            static const ThunkInfo f[] = {
                {TFunc_Instances_GlobalObjectCPP_clearInterval::Func, NULL, "clearInterval", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_clearTimeout::Func, NULL, "clearTimeout", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_describeType::Func, &XMLCI, "describeType", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_escapeMultiByte::Func, &StringCI, "escapeMultiByte", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_getDefinitionByName::Func, &ObjectCI, "getDefinitionByName", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_getQualifiedClassName::Func, &StringCI, "getQualifiedClassName", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_getQualifiedSuperclassName::Func, &StringCI, "getQualifiedSuperclassName", NULL, CT_Method, 1, 1},
                {TFunc_Instances_GlobalObjectCPP_getTimer::Func, &int_CI, "getTimer", NULL, CT_Method, 0, 0},
                {TFunc_Instances_GlobalObjectCPP_setInterval::Func, &uintCI, "setInterval", NULL, CT_Method, 0, 1023},
                {TFunc_Instances_GlobalObjectCPP_setTimeout::Func, &uintCI, "setTimeout", NULL, CT_Method, 0, 1023},
                {TFunc_Instances_GlobalObjectCPP_unescapeMultiByte::Func, &StringCI, "unescapeMultiByte", NULL, CT_Method, 1, 1},
            };
            for (unsigned i = 0; i < NUMBEROF(f); ++i)
                Add2VT(Info, f[i]);
        }
#endif

//##end##"obj_global_cpp$package_methods_registration"

        for (unsigned i = 0; i < GlobalObjectCPP::MemberInfoNum; ++i)
            t.AddSlot(mi[i]);
    }
    
    GlobalObjectCPP::~GlobalObjectCPP()
    {
    }

    void GlobalObjectCPP::RegisterClassInfoTable(const ClassInfo* table[])
    {
        for (unsigned i = 0; table[i] != NULL; ++i)
            CIRegistrationHash.Add(table[i]->Name, table[i]);
    }

    void GlobalObjectCPP::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        GlobalObject::ForEachChild_GC(prcc, op);

        // All values are registered with Traits and will be visited automatically.
        // AS3::ForEachChild_GC(prcc, Values, op);

        UPInt size = CTraits.GetSize();
        for (UPInt i = 0; i < size; ++i)
            AS3::ForEachChild_GC(prcc, CTraits[i], op SF_DEBUG_ARG(*this));
    }
     
    ClassTraits::Traits* GlobalObjectCPP::GetClassTraits(
        const ASString& name,
        const Namespace& ns
        )
    {
        const ClassInfo* inh = NULL;
        if (CIRegistrationHash.Get(name.ToCStr(), &inh) && inh && ns.GetUri() == inh->PkgName)
        {
            Pickable<ClassTraits::Traits> tr;

            // Create ClassTraits.
            tr = (*inh->Factory)(GetVM());
            // It should be registered outside of this method.
            //GetVM().RegisterClassTraits(name, ns, *tr);

            CTraits.PushBack(tr);

            return tr.GetPtr();
        }

        // That shouldn't happen.
        // It actually can happen if we are searching in a wrong namespace.
        //SF_ASSERT(false);

        return NULL;
    }

#ifdef SF_AS3_CLASS_AS_SLOT
    const SlotInfo* GlobalObjectCPP::InitializeOnDemand(
        const SlotInfo* si,
        const ASString& name,
        const Namespace& ns,
        UPInt& index
        )
    {
        if (si || ns.GetKind() != Abc::NS_Public)
            return si;

        const ClassTraits::Traits* tr = GetVM().Resolve2ClassTraits(name, ns);
        if (tr)
        {
            Class& class_ = tr->GetInstanceTraits().GetClass();

            // Add Class to slots.
            si = &AddFixedSlot(class_, Pickable<const Namespace>(&ns, PickValue), index);
        }

        return si;
    }
#endif

    //////////////////////////////////////////////////////////////////////
//##markup##"obj_global_cpp$package_methods"
//##begin##"obj_global_cpp$package_methods"
    void GlobalObjectCPP::decodeURI(ASString& result, const ASString& uri)
    {
//##protect##"instance::::decodeURI()"
        String unescapedStr;
        if (!ASUtils::AS3::Unescape(uri.ToCStr(), uri.GetSize(), unescapedStr))
        {
            VM& vm = GetVM();
            vm.ThrowURIError(VM::Error(VM::eInvalidURIError, vm
                SF_DEBUG_ARG("decodeURI")
                ));
        }
        else
            result = GetVM().GetStringManager().CreateString(unescapedStr.ToCStr(), unescapedStr.GetSize());
//##protect##"instance::::decodeURI()"
    }
    void GlobalObjectCPP::decodeURIComponent(ASString& result, const ASString& uri)
    {
//##protect##"instance::::decodeURIComponent()"
        String unescapedStr;
        if (!ASUtils::AS3::Unescape(uri.ToCStr(), uri.GetSize(), unescapedStr))
        {
            VM& vm = GetVM();
            vm.ThrowURIError(VM::Error(VM::eInvalidURIError, vm
                SF_DEBUG_ARG("decodeURI")
                ));
        }
        else
            result = GetVM().GetStringManager().CreateString(unescapedStr.ToCStr(), unescapedStr.GetSize());
//##protect##"instance::::decodeURIComponent()"
    }
    void GlobalObjectCPP::encodeURI(ASString& result, const ASString& uri)
    {
//##protect##"instance::::encodeURI()"
        String encodedStr;
        ASUtils::AS3::EncodeURI(uri.ToCStr(), uri.GetSize(), encodedStr);
        result = GetVM().GetStringManager().CreateString(encodedStr);
//##protect##"instance::::encodeURI()"
    }
    void GlobalObjectCPP::encodeURIComponent(ASString& result, const ASString& uri)
    {
//##protect##"instance::::encodeURIComponent()"
        String encodedStr;
        ASUtils::AS3::EncodeURIComponent(uri.ToCStr(), uri.GetSize(), encodedStr);
        result = GetVM().GetStringManager().CreateString(encodedStr);
//##protect##"instance::::encodeURIComponent()"
    }
    void GlobalObjectCPP::isNaN(bool& result, Value::Number n)
    {
//##protect##"instance::::isNaN()"
        result = NumberUtil::IsNaN(n);
//##protect##"instance::::isNaN()"
    }
    void GlobalObjectCPP::isFinite(bool& result, Value::Number n)
    {
//##protect##"instance::::isFinite()"
        result = !NumberUtil::IsNaNOrInfinity(n);
//##protect##"instance::::isFinite()"
    }
    void GlobalObjectCPP::parseInt(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::parseInt()"
        ASString str = GetStringManager().GetBuiltin(AS3Builtin_NaN);

        if (argc >= 1)
            if (!argv[0].Convert2String(str))
                return;

        SInt32      radix = 0;
        UInt32      len = str.GetSize();
        UInt32      offset = 0;
        
        if (!len)
        {
            result = Value(NumberUtil::NaN());
            return;
        }

        if (argc >= 2)
            if (!argv[1].Convert2Int32(radix))
                return;

        result = Value(NumberUtil::StringToInt(str.ToCStr(), len, radix, &offset));

//##protect##"instance::::parseInt()"
    }
    void GlobalObjectCPP::parseFloat(Value::Number& result, const ASString& str)
    {
//##protect##"instance::::parseFloat()"
        UInt32    len = str.GetSize();
        UInt32    offset = 0;
        const char* cstr = str.ToCStr();

        offset = static_cast<UInt32>(UTF8Util::GetByteIndex(ASUtils::SkipWhiteSpace(cstr), cstr, len));
        const char* numstr = cstr + offset;

        if (!strncmp(numstr, "0x", 2) || !strncmp(numstr, "0X", 2))
            // Ignore heximal.
            result = 0;
        else
            result = Value(NumberUtil::StringToDouble(numstr, len - offset, &offset));
//##protect##"instance::::parseFloat()"
    }
    void GlobalObjectCPP::escape(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::escape()"
        if (argc > 0)
        {
            const Value& v = argv[0];

            if (v.IsNullOrUndefined())
                result = GetVM().GetStringManager().GetBuiltin(AS3Builtin_null);
            else
            {
                ASString s = GetStringManager().CreateEmptyString();

                if (v.Convert2String(s))
                {
                    String escapedStr;
                    ASUtils::AS3::Escape(s.ToCStr(), s.GetSize(), escapedStr);
                    result = GetVM().GetStringManager().CreateString(escapedStr.ToCStr(), escapedStr.GetSize());
                }
            }
        }
        else
            result = GetVM().GetStringManager().GetBuiltin(AS3Builtin_undefined);
//##protect##"instance::::escape()"
    }
    void GlobalObjectCPP::unescape(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::unescape()"
        //NOT_IMPLEMENTED("::unescape()");

        if (argc > 0)
        {
            const Value& v = argv[0];

            if (v.IsNullOrUndefined())
                result = GetVM().GetStringManager().GetBuiltin(AS3Builtin_null);
            else
            {
                ASString s = GetStringManager().CreateEmptyString();

                if (v.Convert2String(s))
                {
                    String unescapedStr;
                    ASUtils::AS3::Unescape(s.ToCStr(), s.GetSize(), unescapedStr);
                    result = GetVM().GetStringManager().CreateString(unescapedStr.ToCStr(), unescapedStr.GetSize());
                }
            }
        }
        else
            result = GetVM().GetStringManager().GetBuiltin(AS3Builtin_undefined);
//##protect##"instance::::unescape()"
    }
    void GlobalObjectCPP::isXMLName(bool& result, const Value& str)
    {
//##protect##"instance::::isXMLName()"
        SF_UNUSED2(result, str);
        NOT_IMPLEMENTED("::isXMLName()");
//##protect##"instance::::isXMLName()"
    }
    void GlobalObjectCPP::trace(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::trace()"
        // Redirect call to the *System*. Do it the same way as in AVMPlus.
        // !!! There is no trace in flash.system.
        //ClassSystem->trace(result, argc, argv);

        SF_UNUSED1(result);
        StringBuffer r;
        VM& vm = GetVM();

        for(unsigned i = 0; i < argc; ++i)
        {
            if (i > 0)
                r.AppendChar(' ');

            ASString tmp(GetStringManager().CreateEmptyString());
            if (!argv[i].Convert2String(tmp))
                // Oops. Exception.
                return;

            r.AppendString(String(tmp.ToCStr(), tmp.GetSize()));
        }

        r.AppendString("\n");
        vm.GetUI().Output(FlashUI::Output_Message, r);
//##protect##"instance::::trace()"
    }
    void GlobalObjectCPP::print(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::print()"
        trace(result, argc, argv);
//##protect##"instance::::print()"
    }
#ifndef SF_AS3_NO_FLASH
    void GlobalObjectCPP::fscommand(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::fscommand()"
        SF_UNUSED(result);
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        GFx::FSCommandHandler *phandler = proot->pFSCommandHandler;
        if (phandler && (argc > 0))
        {
            ASString command(argv[0].AsString());
            ASString args((argc > 1) ? argv[1].AsString() :
                                       GetVM().GetStringManager().GetBuiltin(AS3Builtin_empty_));
            phandler->Callback(proot, command.ToCStr(), args.ToCStr());
        }
//##protect##"instance::::fscommand()"
    }
    void GlobalObjectCPP::clearInterval(Value& result, UInt32 id)
    {
//##protect##"instance::::clearInterval()"
        SF_UNUSED2(result, id);
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        proot->ClearIntervalTimer(int(id));
//##protect##"instance::::clearInterval()"
    }
    void GlobalObjectCPP::clearTimeout(Value& result, UInt32 id)
    {
//##protect##"instance::::clearTimeout()"
        SF_UNUSED1(result);
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        proot->ClearIntervalTimer(int(id));
//##protect##"instance::::clearTimeout()"
    }
    void GlobalObjectCPP::describeType(Value& result, const Value& value)
    {
//##protect##"instance::::describeType()"
        SF_UNUSED2(result, value);
        NOT_IMPLEMENTED("::describeType()");
//##protect##"instance::::describeType()"
    }
    void GlobalObjectCPP::escapeMultiByte(ASString& result, const ASString& value)
    {
//##protect##"instance::::escapeMultiByte()"
        escapeMultiByteInternal(GetVM(), result, value);
//##protect##"instance::::escapeMultiByte()"
    }
    void GlobalObjectCPP::getDefinitionByName(Value& result, const ASString& name)
    {
//##protect##"instance::::getDefinitionByName()"
        Value _class;
        // !!! GetVM().GetClass() shouldn't be used here because definition
        // can be located in a script and require initialization on demand.
        if (GetVM().GetClassUnsafe(name.ToCStr(), _class))
            _class.Swap(result);
//##protect##"instance::::getDefinitionByName()"
    }
    void GlobalObjectCPP::getQualifiedClassName(ASString& result, const Value& value)
    {
//##protect##"instance::::getQualifiedClassName()"
        const InstanceTraits::Traits& itr = GetVM().GetInstanceTraits(value);
        result = itr.GetQualifiedName();
//##protect##"instance::::getQualifiedClassName()"
    }
    void GlobalObjectCPP::getQualifiedSuperclassName(ASString& result, const Value& value)
    {
//##protect##"instance::::getQualifiedSuperclassName()"
        const InstanceTraits::Traits& itr = GetVM().GetInstanceTraits(value);

        if (itr.GetParent())
            result = itr.GetParent()->GetQualifiedName();
        else
            result = GetVM().GetStringManager().GetBuiltin(AS3Builtin_null);
//##protect##"instance::::getQualifiedSuperclassName()"
    }
    void GlobalObjectCPP::getTimer(SInt32& result)
    {
//##protect##"instance::::getTimer()"
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();
        result = (SInt32)proot->GetASTimerMs();

        // For testing of as3vm.
        //result = (SInt32)(Scaleform::Timer::GetTicks() % 100000000) / 1000;
//##protect##"instance::::getTimer()"
    }
    void GlobalObjectCPP::setInterval(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::setInterval()"
        if (argc < 2)
            return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("GlobalObjectCPP::setInterval") SF_DEBUG_ARG(2) SF_DEBUG_ARG(1023) SF_DEBUG_ARG(argc)));

        UInt32 delay;
        if (!argv[1].Convert2UInt32(delay))
            return;
        Ptr<IntervalTimer> timer = *SF_HEAP_NEW(GetVM().GetMemoryHeap()) IntervalTimer(argv[0], delay);
        if (argc > 2)
            timer->SetArguments(argc - 2, &argv[2]);
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();

        result = Value((UInt32)proot->AddIntervalTimer(timer));
        timer->Start(proot);
//##protect##"instance::::setInterval()"
    }
    void GlobalObjectCPP::setTimeout(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::::setTimeout()"
        SF_UNUSED3(result, argc, argv);
        if (argc < 2)
            return GetVM().ThrowArgumentError(VM::Error(VM::eWrongArgumentCountError, GetVM() SF_DEBUG_ARG("GlobalObjectCPP::setTimeout") SF_DEBUG_ARG(2) SF_DEBUG_ARG(1023) SF_DEBUG_ARG(argc)));

        UInt32 delay;
        if (!argv[1].Convert2UInt32(delay))
            return;
        Ptr<IntervalTimer> timer = *SF_HEAP_NEW(GetVM().GetMemoryHeap()) IntervalTimer(argv[0], delay, true);
        if (argc > 2)
            timer->SetArguments(argc - 2, &argv[2]);
        MovieImpl* proot = static_cast<const ASVM&>(GetVM()).GetMovieImpl();

        result = Value((UInt32)proot->AddIntervalTimer(timer));
        timer->Start(proot);
//##protect##"instance::::setTimeout()"
    }
    void GlobalObjectCPP::unescapeMultiByte(ASString& result, const ASString& value)
    {
//##protect##"instance::::unescapeMultiByte()"
        unescapeMultiByteInternal(GetVM(), result, value);
//##protect##"instance::::unescapeMultiByte()"
    }

#endif
//##end##"obj_global_cpp$package_methods"
    
    ///////////////////////////////////////////////////////////////////////////
    void GlobalObjectCPP::Execute()
    {
        ; // Do nothing.
    }

#ifdef SF_AS3_CLASS_AS_SLOT
    void GlobalObjectCPP::AddFixedSlot(Class& cl)
    {
        UPInt index = 0;
        ASString name = cl.GetName();
        VM& vm = GetVM();
        ClassTraits::Traits* ctr = &cl.GetClassTraits();

        AddFixedSlotValuePair(
            name, 
            vm.MakePublicNamespace(),
            ctr, 
            Value(&cl),
            index
            );
    }

    const SlotInfo& GlobalObjectCPP::AddFixedSlotValuePair(const ASString& prop_name, Pickable<const Instances::Namespace> ns,
        const ClassTraits::Traits* ctr, const Value& v, UPInt& index)
    {
        Values.PushBack(v);
        Traits& tr = GetTraits();

        // Add to Traits and bind ...
        tr.AddSlotValueCPP(prop_name, ns, ctr);
        // No dynamic slots should be added at this point.
        SF_ASSERT(Values.GetSize() == tr.GetFixedValueSlotNumber());

        // We MAY NOT use Resolve2ClassTraits here because this method can 
        // be called from GlobalObjectCPP.
        // if (GetVM().ClassTraitsSet.Get(prop_name, *ns) == NULL)
        GetVM().ClassTraitsSet.Add(prop_name, *ns, VM::TClassTraitsCache::ValueType(const_cast<ClassTraits::Traits*>(ctr)));

        index = tr.GetSlotInfoNum() - 1;
        return tr.GetSlotInfo(AbsoluteIndex(index));

    }
#endif

} // namespace Instances

namespace InstanceTraits
{
    GlobalObject::GlobalObject(VM& vm)
    : Traits(vm, Info)
    {
        SetConstructor(Pickable<Class>(&vm.GetClassObject(), PickValue));

        // Magic logic.
        // Global objects do not have stored scope.
        ClearInitScope();
    }

    void GlobalObject::MakeObject(Value& result, Traits& t)
    {
        SF_UNUSED2(result, t);
    }

    bool GlobalObject::IsGlobal() const
    {
        return true;
    }

    // Let's not set Abc flag.
    const ClassInfo GlobalObject::Info = {ClassInfo::CompileTime | ClassInfo::DynamicObject, "global", "", NULL, NULL};

    ///////////////////////////////////////////////////////////////////////////
    GlobalObjectScript::GlobalObjectScript(
        VMAbcFile& file, 
        VM& vm, 
        const Abc::ScriptInfo& script
        ) 
        : GlobalObject(vm)
        , File(&file)
        , Script(script)
    {
        // Instance size will be set by AddSlots().

        const Abc::HasTraits& object_traits = script;

        // MemSize doesn't depend on parent.
        if (!AddSlots(object_traits, file, GetFixedMemSize()))
            return;
    }

    void GlobalObjectScript::ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const
    {
        GlobalObject::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC<VMAbcFile, Mem_Stat>(prcc, File, op SF_DEBUG_ARG(*this));
    }

    Pickable<Instances::GlobalObjectScript> GlobalObjectScript::MakeInstance()
    {
        // Placement new.
        return Pickable<Instances::GlobalObjectScript>(new(Alloc()) Instances::GlobalObjectScript(*this));
    }

    unsigned GlobalObjectScript::GetFixedMemSize() const
    {
        return sizeof(Instances::GlobalObjectScript);
    }

    VMAbcFile* GlobalObjectScript::GetFilePtr() const
    {
        return File;
    }

} // InstanceTraits

///////////////////////////////////////////////////////////////////////////
ASStringNode* VM::CreateConstStringNode(const char* msg)
{
    ASStringNode* snode;

    if (msg == NULL || SFstrlen(msg) == 0)
        snode = GetStringManager().GetEmptyStringNode();
    else
        snode = GetStringManager().GetStringManager()->
                    CreateConstStringNode(msg, SFstrlen(msg), 0);

    return snode;
}

}}} // namespace Scaleform { namespace GFx { namespace AS3
