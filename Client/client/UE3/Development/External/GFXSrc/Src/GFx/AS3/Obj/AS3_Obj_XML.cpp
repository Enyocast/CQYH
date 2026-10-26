//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_XML.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_XML.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Array.h"
#include "AS3_Obj_XMLList.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::XML, Instances::XML::mid_AS3descendants, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::XML, Instances::XML::mid_AS3elements, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::XML, Instances::XML::mid_AS3namespace_, 0, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::XML, Instances::XML::mid_AS3processingInstructions, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Classes::XML, Classes::XML::mid_AS3setSettings, 0, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Classes::XML, Classes::XML::mid_setSettings, 0, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

} // namespace Impl
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3toString, ASString> TFunc_Instances_XML_AS3toString;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3hasOwnProperty, bool, const ASString&> TFunc_Instances_XML_AS3hasOwnProperty;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3propertyIsEnumerable, bool, const ASString&> TFunc_Instances_XML_AS3propertyIsEnumerable;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3addNamespace, Value, const Value&> TFunc_Instances_XML_AS3addNamespace;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3appendChild, Value, const Value&> TFunc_Instances_XML_AS3appendChild;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3attribute, Value, const Value&> TFunc_Instances_XML_AS3attribute;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3attributes, Value> TFunc_Instances_XML_AS3attributes;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3child, Value, const Value&> TFunc_Instances_XML_AS3child;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3childIndex, SInt32> TFunc_Instances_XML_AS3childIndex;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3children, Value> TFunc_Instances_XML_AS3children;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3comments, Value> TFunc_Instances_XML_AS3comments;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3contains, bool, const Value&> TFunc_Instances_XML_AS3contains;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3copy, Value> TFunc_Instances_XML_AS3copy;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3descendants, Value, const ASString&> TFunc_Instances_XML_AS3descendants;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3elements, Value, const ASString&> TFunc_Instances_XML_AS3elements;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3hasComplexContent, bool> TFunc_Instances_XML_AS3hasComplexContent;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3hasSimpleContent, bool> TFunc_Instances_XML_AS3hasSimpleContent;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3inScopeNamespaces, Value> TFunc_Instances_XML_AS3inScopeNamespaces;
typedef ThunkFunc2<Instances::XML, Instances::XML::mid_AS3insertChildAfter, Value, const Value&, const Value&> TFunc_Instances_XML_AS3insertChildAfter;
typedef ThunkFunc2<Instances::XML, Instances::XML::mid_AS3insertChildBefore, Value, const Value&, const Value&> TFunc_Instances_XML_AS3insertChildBefore;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3localName, Value> TFunc_Instances_XML_AS3localName;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3name, Value> TFunc_Instances_XML_AS3name;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3namespace_, Value, const Value&> TFunc_Instances_XML_AS3namespace_;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3namespaceDeclarations, Value> TFunc_Instances_XML_AS3namespaceDeclarations;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3nodeKind, ASString> TFunc_Instances_XML_AS3nodeKind;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3normalize, Value> TFunc_Instances_XML_AS3normalize;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3parent, Value> TFunc_Instances_XML_AS3parent;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3processingInstructions, Value, const ASString&> TFunc_Instances_XML_AS3processingInstructions;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3prependChild, Value, const Value&> TFunc_Instances_XML_AS3prependChild;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3removeNamespace, Value, const Value&> TFunc_Instances_XML_AS3removeNamespace;
typedef ThunkFunc2<Instances::XML, Instances::XML::mid_AS3replace, Value, const Value&, const Value&> TFunc_Instances_XML_AS3replace;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3setChildren, Value, const Value&> TFunc_Instances_XML_AS3setChildren;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3setLocalName, Value, const Value&> TFunc_Instances_XML_AS3setLocalName;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3setName, Value, const Value&> TFunc_Instances_XML_AS3setName;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3setNamespace, Value, const Value&> TFunc_Instances_XML_AS3setNamespace;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3text, Value> TFunc_Instances_XML_AS3text;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3toXMLString, ASString> TFunc_Instances_XML_AS3toXMLString;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3notification, Value> TFunc_Instances_XML_AS3notification;
typedef ThunkFunc1<Instances::XML, Instances::XML::mid_AS3setNotification, Value, const Value&> TFunc_Instances_XML_AS3setNotification;
typedef ThunkFunc0<Instances::XML, Instances::XML::mid_AS3valueOf, Value> TFunc_Instances_XML_AS3valueOf;

template <> const TFunc_Instances_XML_AS3toString::TMethod TFunc_Instances_XML_AS3toString::Method = &Instances::XML::AS3toString;
template <> const TFunc_Instances_XML_AS3hasOwnProperty::TMethod TFunc_Instances_XML_AS3hasOwnProperty::Method = &Instances::XML::AS3hasOwnProperty;
template <> const TFunc_Instances_XML_AS3propertyIsEnumerable::TMethod TFunc_Instances_XML_AS3propertyIsEnumerable::Method = &Instances::XML::AS3propertyIsEnumerable;
template <> const TFunc_Instances_XML_AS3addNamespace::TMethod TFunc_Instances_XML_AS3addNamespace::Method = &Instances::XML::AS3addNamespace;
template <> const TFunc_Instances_XML_AS3appendChild::TMethod TFunc_Instances_XML_AS3appendChild::Method = &Instances::XML::AS3appendChild;
template <> const TFunc_Instances_XML_AS3attribute::TMethod TFunc_Instances_XML_AS3attribute::Method = &Instances::XML::AS3attribute;
template <> const TFunc_Instances_XML_AS3attributes::TMethod TFunc_Instances_XML_AS3attributes::Method = &Instances::XML::AS3attributes;
template <> const TFunc_Instances_XML_AS3child::TMethod TFunc_Instances_XML_AS3child::Method = &Instances::XML::AS3child;
template <> const TFunc_Instances_XML_AS3childIndex::TMethod TFunc_Instances_XML_AS3childIndex::Method = &Instances::XML::AS3childIndex;
template <> const TFunc_Instances_XML_AS3children::TMethod TFunc_Instances_XML_AS3children::Method = &Instances::XML::AS3children;
template <> const TFunc_Instances_XML_AS3comments::TMethod TFunc_Instances_XML_AS3comments::Method = &Instances::XML::AS3comments;
template <> const TFunc_Instances_XML_AS3contains::TMethod TFunc_Instances_XML_AS3contains::Method = &Instances::XML::AS3contains;
template <> const TFunc_Instances_XML_AS3copy::TMethod TFunc_Instances_XML_AS3copy::Method = &Instances::XML::AS3copy;
template <> const TFunc_Instances_XML_AS3descendants::TMethod TFunc_Instances_XML_AS3descendants::Method = &Instances::XML::AS3descendants;
template <> const TFunc_Instances_XML_AS3elements::TMethod TFunc_Instances_XML_AS3elements::Method = &Instances::XML::AS3elements;
template <> const TFunc_Instances_XML_AS3hasComplexContent::TMethod TFunc_Instances_XML_AS3hasComplexContent::Method = &Instances::XML::AS3hasComplexContent;
template <> const TFunc_Instances_XML_AS3hasSimpleContent::TMethod TFunc_Instances_XML_AS3hasSimpleContent::Method = &Instances::XML::AS3hasSimpleContent;
template <> const TFunc_Instances_XML_AS3inScopeNamespaces::TMethod TFunc_Instances_XML_AS3inScopeNamespaces::Method = &Instances::XML::AS3inScopeNamespaces;
template <> const TFunc_Instances_XML_AS3insertChildAfter::TMethod TFunc_Instances_XML_AS3insertChildAfter::Method = &Instances::XML::AS3insertChildAfter;
template <> const TFunc_Instances_XML_AS3insertChildBefore::TMethod TFunc_Instances_XML_AS3insertChildBefore::Method = &Instances::XML::AS3insertChildBefore;
template <> const TFunc_Instances_XML_AS3localName::TMethod TFunc_Instances_XML_AS3localName::Method = &Instances::XML::AS3localName;
template <> const TFunc_Instances_XML_AS3name::TMethod TFunc_Instances_XML_AS3name::Method = &Instances::XML::AS3name;
template <> const TFunc_Instances_XML_AS3namespace_::TMethod TFunc_Instances_XML_AS3namespace_::Method = &Instances::XML::AS3namespace_;
template <> const TFunc_Instances_XML_AS3namespaceDeclarations::TMethod TFunc_Instances_XML_AS3namespaceDeclarations::Method = &Instances::XML::AS3namespaceDeclarations;
template <> const TFunc_Instances_XML_AS3nodeKind::TMethod TFunc_Instances_XML_AS3nodeKind::Method = &Instances::XML::AS3nodeKind;
template <> const TFunc_Instances_XML_AS3normalize::TMethod TFunc_Instances_XML_AS3normalize::Method = &Instances::XML::AS3normalize;
template <> const TFunc_Instances_XML_AS3parent::TMethod TFunc_Instances_XML_AS3parent::Method = &Instances::XML::AS3parent;
template <> const TFunc_Instances_XML_AS3processingInstructions::TMethod TFunc_Instances_XML_AS3processingInstructions::Method = &Instances::XML::AS3processingInstructions;
template <> const TFunc_Instances_XML_AS3prependChild::TMethod TFunc_Instances_XML_AS3prependChild::Method = &Instances::XML::AS3prependChild;
template <> const TFunc_Instances_XML_AS3removeNamespace::TMethod TFunc_Instances_XML_AS3removeNamespace::Method = &Instances::XML::AS3removeNamespace;
template <> const TFunc_Instances_XML_AS3replace::TMethod TFunc_Instances_XML_AS3replace::Method = &Instances::XML::AS3replace;
template <> const TFunc_Instances_XML_AS3setChildren::TMethod TFunc_Instances_XML_AS3setChildren::Method = &Instances::XML::AS3setChildren;
template <> const TFunc_Instances_XML_AS3setLocalName::TMethod TFunc_Instances_XML_AS3setLocalName::Method = &Instances::XML::AS3setLocalName;
template <> const TFunc_Instances_XML_AS3setName::TMethod TFunc_Instances_XML_AS3setName::Method = &Instances::XML::AS3setName;
template <> const TFunc_Instances_XML_AS3setNamespace::TMethod TFunc_Instances_XML_AS3setNamespace::Method = &Instances::XML::AS3setNamespace;
template <> const TFunc_Instances_XML_AS3text::TMethod TFunc_Instances_XML_AS3text::Method = &Instances::XML::AS3text;
template <> const TFunc_Instances_XML_AS3toXMLString::TMethod TFunc_Instances_XML_AS3toXMLString::Method = &Instances::XML::AS3toXMLString;
template <> const TFunc_Instances_XML_AS3notification::TMethod TFunc_Instances_XML_AS3notification::Method = &Instances::XML::AS3notification;
template <> const TFunc_Instances_XML_AS3setNotification::TMethod TFunc_Instances_XML_AS3setNotification::Method = &Instances::XML::AS3setNotification;
template <> const TFunc_Instances_XML_AS3valueOf::TMethod TFunc_Instances_XML_AS3valueOf::Method = &Instances::XML::AS3valueOf;

namespace Instances
{
    XML::XML(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::XML::XML()$data"
//##protect##"instance::XML::XML()$data"
    {
//##protect##"instance::XML::XML()$code"
//##protect##"instance::XML::XML()$code"
    }

    void XML::AS3toString(ASString& result)
    {
//##protect##"instance::XML::AS3toString()"
        StringManager& sm = GetVM().GetStringManager();
        // Disabled for the time being.
        // Root.Convert2String(result, sm).DoNotCheck();
        result = sm.CreateEmptyString();
//##protect##"instance::XML::AS3toString()"
    }
    void XML::AS3hasOwnProperty(bool& result, const ASString& p)
    {
//##protect##"instance::XML::AS3hasOwnProperty()"
        SF_UNUSED1(p);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XML::AS3hasOwnProperty()"
    }
    void XML::AS3propertyIsEnumerable(bool& result, const ASString& p)
    {
//##protect##"instance::XML::AS3propertyIsEnumerable()"
        SF_UNUSED1(p);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XML::AS3propertyIsEnumerable()"
    }
    void XML::AS3addNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XML::AS3addNamespace()"
        SF_UNUSED1(ns);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3addNamespace()"
    }
    void XML::AS3appendChild(Value& result, const Value& child)
    {
//##protect##"instance::XML::AS3appendChild()"
        SF_UNUSED1(child);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3appendChild()"
    }
    void XML::AS3attribute(Value& result, const Value& arg)
    {
//##protect##"instance::XML::AS3attribute()"
        SF_UNUSED2(result, arg);
//##protect##"instance::XML::AS3attribute()"
    }
    void XML::AS3attributes(Value& result)
    {
//##protect##"instance::XML::AS3attributes()"
        SF_UNUSED1(result);
//##protect##"instance::XML::AS3attributes()"
    }
    void XML::AS3child(Value& result, const Value& propertyName)
    {
//##protect##"instance::XML::AS3child()"
        SF_UNUSED2(result, propertyName);
//##protect##"instance::XML::AS3child()"
    }
    void XML::AS3childIndex(SInt32& result)
    {
//##protect##"instance::XML::AS3childIndex()"
        result = AS3::DefaultValue<int>(GetStringManager());
//##protect##"instance::XML::AS3childIndex()"
    }
    void XML::AS3children(Value& result)
    {
//##protect##"instance::XML::AS3children()"
        SF_UNUSED1(result);
//##protect##"instance::XML::AS3children()"
    }
    void XML::AS3comments(Value& result)
    {
//##protect##"instance::XML::AS3comments()"
        SF_UNUSED1(result);
//##protect##"instance::XML::AS3comments()"
    }
    void XML::AS3contains(bool& result, const Value& value)
    {
//##protect##"instance::XML::AS3contains()"
        SF_UNUSED1(value);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XML::AS3contains()"
    }
    void XML::AS3copy(Value& result)
    {
//##protect##"instance::XML::AS3copy()"
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3copy()"
    }
    void XML::AS3descendants(Value& result, const ASString& name)
    {
//##protect##"instance::XML::AS3descendants()"
        SF_UNUSED2(result, name);
//##protect##"instance::XML::AS3descendants()"
    }
    void XML::AS3elements(Value& result, const ASString& name)
    {
//##protect##"instance::XML::AS3elements()"
        SF_UNUSED2(result, name);
//##protect##"instance::XML::AS3elements()"
    }
    void XML::AS3hasComplexContent(bool& result)
    {
//##protect##"instance::XML::AS3hasComplexContent()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XML::AS3hasComplexContent()"
    }
    void XML::AS3hasSimpleContent(bool& result)
    {
//##protect##"instance::XML::AS3hasSimpleContent()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XML::AS3hasSimpleContent()"
    }
    void XML::AS3inScopeNamespaces(Value& result)
    {
//##protect##"instance::XML::AS3inScopeNamespaces()"
        result = AS3::DefaultValue<Instances::Array*>(GetStringManager());
//##protect##"instance::XML::AS3inScopeNamespaces()"
    }
    void XML::AS3insertChildAfter(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XML::AS3insertChildAfter()"
        SF_UNUSED3(result, child1, child2);
//##protect##"instance::XML::AS3insertChildAfter()"
    }
    void XML::AS3insertChildBefore(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XML::AS3insertChildBefore()"
        SF_UNUSED3(result, child1, child2);
//##protect##"instance::XML::AS3insertChildBefore()"
    }
    void XML::AS3localName(Value& result)
    {
//##protect##"instance::XML::AS3localName()"
        result = AS3::DefaultValue<Instances::Object*>(GetStringManager());
//##protect##"instance::XML::AS3localName()"
    }
    void XML::AS3name(Value& result)
    {
//##protect##"instance::XML::AS3name()"
        result = AS3::DefaultValue<Instances::Object*>(GetStringManager());
//##protect##"instance::XML::AS3name()"
    }
    void XML::AS3namespace_(Value& result, const Value& prefix)
    {
//##protect##"instance::XML::AS3namespace_()"
        SF_UNUSED2(result, prefix);
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XML::AS3namespace_()"
    }
    void XML::AS3namespaceDeclarations(Value& result)
    {
//##protect##"instance::XML::AS3namespaceDeclarations()"
        result = AS3::DefaultValue<Instances::Array*>(GetStringManager());
//##protect##"instance::XML::AS3namespaceDeclarations()"
    }
    void XML::AS3nodeKind(ASString& result)
    {
//##protect##"instance::XML::AS3nodeKind()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("XML::nodeKind()");
//##protect##"instance::XML::AS3nodeKind()"
    }
    void XML::AS3normalize(Value& result)
    {
//##protect##"instance::XML::AS3normalize()"
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3normalize()"
    }
    void XML::AS3parent(Value& result)
    {
//##protect##"instance::XML::AS3parent()"
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XML::AS3parent()"
    }
    void XML::AS3processingInstructions(Value& result, const ASString& name)
    {
//##protect##"instance::XML::AS3processingInstructions()"
        SF_UNUSED2(result, name);
//##protect##"instance::XML::AS3processingInstructions()"
    }
    void XML::AS3prependChild(Value& result, const Value& value)
    {
//##protect##"instance::XML::AS3prependChild()"
        SF_UNUSED2(result, value);
//##protect##"instance::XML::AS3prependChild()"
    }
    void XML::AS3removeNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XML::AS3removeNamespace()"
        SF_UNUSED2(result, ns);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3removeNamespace()"
    }
    void XML::AS3replace(Value& result, const Value& propertyName, const Value& value)
    {
//##protect##"instance::XML::AS3replace()"
        SF_UNUSED3(result, propertyName, value);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3replace()"
    }
    void XML::AS3setChildren(Value& result, const Value& value)
    {
//##protect##"instance::XML::AS3setChildren()"
        SF_UNUSED2(result, value);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3setChildren()"
    }
    void XML::AS3setLocalName(Value& result, const Value& name)
    {
//##protect##"instance::XML::AS3setLocalName()"
        SF_UNUSED2(result, name);
        NOT_IMPLEMENTED("XML::setLocalName()");
//##protect##"instance::XML::AS3setLocalName()"
    }
    void XML::AS3setName(Value& result, const Value& name)
    {
//##protect##"instance::XML::AS3setName()"
        SF_UNUSED2(result, name);
        NOT_IMPLEMENTED("XML::setName()");
//##protect##"instance::XML::AS3setName()"
    }
    void XML::AS3setNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XML::AS3setNamespace()"
        SF_UNUSED2(result, ns);
        NOT_IMPLEMENTED("XML::setNamespace()");
//##protect##"instance::XML::AS3setNamespace()"
    }
    void XML::AS3text(Value& result)
    {
//##protect##"instance::XML::AS3text()"
        SF_UNUSED1(result);
//##protect##"instance::XML::AS3text()"
    }
    void XML::AS3toXMLString(ASString& result)
    {
//##protect##"instance::XML::AS3toXMLString()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("XML::toXMLString()");
//##protect##"instance::XML::AS3toXMLString()"
    }
    void XML::AS3notification(Value& result)
    {
//##protect##"instance::XML::AS3notification()"
        result = AS3::DefaultValue<Instances::Function*>(GetStringManager());
//##protect##"instance::XML::AS3notification()"
    }
    void XML::AS3setNotification(Value& result, const Value& f)
    {
//##protect##"instance::XML::AS3setNotification()"
        SF_UNUSED2(result, f);
        NOT_IMPLEMENTED("XML::setNotification()");
//##protect##"instance::XML::AS3setNotification()"
    }
    void XML::AS3valueOf(Value& result)
    {
//##protect##"instance::XML::AS3valueOf()"
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XML::AS3valueOf()"
    }

//##protect##"instance$methods"
    void XML::AS3Constructor(unsigned argc, const Value* argv)
    {
        if (argc > 0)
        {
            VM& vm = GetVM();
            const Value& v = argv[0];
            const Traits& tr = vm.GetValueTraits(v);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (v.IsNullOrUndefined() || tr.IsClassTraits())
                goto error;

            switch (tt)
            {
            case Traits_Boolean:
            case Traits_SInt:
            case Traits_UInt:
            case Traits_Number:
            case Traits_String:
                {
                    StringManager& sm = vm.GetStringManager();
                    ASString str = sm.CreateEmptyString();
                    if (!v.Convert2String(str))
                        return;
                    Root = str;
                }
                return;
            case Traits_XML:
                // Make a copy.
                Root = static_cast<Instances::XML*>(v.GetObject())->Root;
                return;
            case Traits_XMLList:
                {
                    const Instances::XMLList& list = static_cast<const Instances::XMLList&>(*v.GetObject());

                    if (list.List.GetSize() == 1)
                        Root = list.List[0];
                    else
                        goto error;
                }
                return;
            default:
                break;
            }

            error:
                return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));
        }
    }

    void XML::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);

        AS3::ForEachChild_GC(prcc, Root, op SF_DEBUG_ARG(*this));
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo XML::ti[XML::ThunkInfoNum] = {
        {TFunc_Instances_XML_AS3toString::Func, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3hasOwnProperty::Func, &BooleanCI, "hasOwnProperty", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3propertyIsEnumerable::Func, &BooleanCI, "propertyIsEnumerable", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3addNamespace::Func, &XMLCI, "addNamespace", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3appendChild::Func, &XMLCI, "appendChild", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3attribute::Func, &XMLListCI, "attribute", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3attributes::Func, &XMLListCI, "attributes", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3child::Func, &XMLListCI, "child", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3childIndex::Func, &int_CI, "childIndex", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3children::Func, &XMLListCI, "children", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3comments::Func, &XMLListCI, "comments", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3contains::Func, &BooleanCI, "contains", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3copy::Func, &XMLCI, "copy", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3descendants::Func, &XMLListCI, "descendants", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XML_AS3elements::Func, &XMLListCI, "elements", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XML_AS3hasComplexContent::Func, &BooleanCI, "hasComplexContent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3hasSimpleContent::Func, &BooleanCI, "hasSimpleContent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3inScopeNamespaces::Func, &ArrayCI, "inScopeNamespaces", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3insertChildAfter::Func, NULL, "insertChildAfter", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XML_AS3insertChildBefore::Func, NULL, "insertChildBefore", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XML_AS3localName::Func, &ObjectCI, "localName", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3name::Func, &ObjectCI, "name", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3namespace_::Func, NULL, "namespace", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XML_AS3namespaceDeclarations::Func, &ArrayCI, "namespaceDeclarations", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3nodeKind::Func, &StringCI, "nodeKind", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3normalize::Func, &XMLCI, "normalize", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3parent::Func, NULL, "parent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3processingInstructions::Func, &XMLListCI, "processingInstructions", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XML_AS3prependChild::Func, &XMLCI, "prependChild", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3removeNamespace::Func, &XMLCI, "removeNamespace", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3replace::Func, &XMLCI, "replace", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XML_AS3setChildren::Func, &XMLCI, "setChildren", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3setLocalName::Func, NULL, "setLocalName", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3setName::Func, NULL, "setName", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3setNamespace::Func, NULL, "setNamespace", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3text::Func, &XMLListCI, "text", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3toXMLString::Func, &StringCI, "toXMLString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3notification::Func, &FunctionCI, "notification", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XML_AS3setNotification::Func, NULL, "setNotification", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XML_AS3valueOf::Func, &XMLCI, "valueOf", NS_AS3, CT_Method, 0, 0},
    };

    XML::XML(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::XML::XML()"
        SetTraitsType(Traits_XML);
//##protect##"InstanceTraits::XML::XML()"
        SetMemSize(sizeof(Instances::XML));

    }

    Pickable<Instances::XML> XML::MakeInstance(Traits& t)
    {
        return Pickable<Instances::XML>(new(t.Alloc()) Instances::XML(t));
    }

    void XML::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
    void XML::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
#ifdef SF_ENABLE_XML

        if (_this.IsObject() && _this.GetObject() == &vm.GetClassXML().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else
        {
            const Traits& tr = vm.GetValueTraits(_this);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (tt != Traits_XML || tr.IsClassTraits())
                return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

            Instances::XML* obj = static_cast<Instances::XML*>(_this.GetObject());
            ASString str = vm.GetStringManager().CreateEmptyString();

            obj->AS3toString(str);
            // We do not check for exception here on purpose. There should be not much harm.
            result = str;
        }
#else
        SF_UNUSED4(ti, _this, argc, argv);
        result = vm.GetStringManager().CreateEmptyString();
#endif
    }
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    XML::XML(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::XML::XML()"
        SetDefaultValues();
//##protect##"class_::XML::XML()"
    }
    void XML::ignoreCommentsGet(bool& result)
    {
//##protect##"class_::XML::ignoreCommentsGet()"
        result = IgnoreComments;
//##protect##"class_::XML::ignoreCommentsGet()"
    }
    void XML::ignoreCommentsSet(Value& result, bool newIgnore)
    {
//##protect##"class_::XML::ignoreCommentsSet()"
        SF_UNUSED1(result);
        IgnoreComments = newIgnore;
//##protect##"class_::XML::ignoreCommentsSet()"
    }
    void XML::ignoreProcessingInstructionsGet(bool& result)
    {
//##protect##"class_::XML::ignoreProcessingInstructionsGet()"
        result = IgnoreProcessingInstructions;
//##protect##"class_::XML::ignoreProcessingInstructionsGet()"
    }
    void XML::ignoreProcessingInstructionsSet(Value& result, bool newIgnore)
    {
//##protect##"class_::XML::ignoreProcessingInstructionsSet()"
        SF_UNUSED1(result);
        IgnoreProcessingInstructions = newIgnore;
//##protect##"class_::XML::ignoreProcessingInstructionsSet()"
    }
    void XML::ignoreWhitespaceGet(bool& result)
    {
//##protect##"class_::XML::ignoreWhitespaceGet()"
        result = IgnoreWhitespace;
//##protect##"class_::XML::ignoreWhitespaceGet()"
    }
    void XML::ignoreWhitespaceSet(Value& result, bool newIgnore)
    {
//##protect##"class_::XML::ignoreWhitespaceSet()"
        SF_UNUSED1(result);
        IgnoreWhitespace = newIgnore;
//##protect##"class_::XML::ignoreWhitespaceSet()"
    }
    void XML::prettyPrintingGet(bool& result)
    {
//##protect##"class_::XML::prettyPrintingGet()"
        result = PrettyPrinting;
//##protect##"class_::XML::prettyPrintingGet()"
    }
    void XML::prettyPrintingSet(Value& result, bool newPretty)
    {
//##protect##"class_::XML::prettyPrintingSet()"
        SF_UNUSED1(result);
        PrettyPrinting = newPretty;
//##protect##"class_::XML::prettyPrintingSet()"
    }
    void XML::prettyIndentGet(SInt32& result)
    {
//##protect##"class_::XML::prettyIndentGet()"
        result = PrettyIndent;
//##protect##"class_::XML::prettyIndentGet()"
    }
    void XML::prettyIndentSet(Value& result, SInt32 newIndent)
    {
//##protect##"class_::XML::prettyIndentSet()"
        SF_UNUSED1(result);
        PrettyIndent = newIndent;
//##protect##"class_::XML::prettyIndentSet()"
    }
    void XML::AS3settings(Value& result)
    {
//##protect##"class_::XML::AS3settings()"
        VM& vm = GetVM();
        StringManager& sm = vm.GetStringManager();
        Pickable<Instances::Object> obj = vm.MakeObject();

        result = obj;
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreComments"), Value(IgnoreComments));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreProcessingInstructions"), Value(IgnoreComments));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreWhitespace"), Value(IgnoreWhitespace));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("prettyPrinting"), Value(PrettyPrinting));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("prettyIndent"), Value(PrettyIndent));
//##protect##"class_::XML::AS3settings()"
    }
    void XML::settings(Value& result)
    {
//##protect##"class_::XML::settings()"
        AS3settings(result);
//##protect##"class_::XML::settings()"
    }
    void XML::AS3setSettings(Value& result, const Value& o)
    {
//##protect##"class_::XML::AS3setSettings()"
        SF_UNUSED1(result);

#if 0
        if (o.IsNullOrUndefined())
            SetDefaultValues();
        else
        {
            VM& vm = GetVM();
            PropRef prop;
            Value ic;
            Value ipi;
            Value iw;
            Value pp;
            Value pi;

            FindObjProperty(prop, vm, o, Multiname(vm, "ignoreComments"));
            if (prop && prop.GetSlotValueUnsafe(vm, ic) && ic.IsBool())
                IgnoreComments = ic;

            FindObjProperty(prop, vm, o, Multiname(vm, "ignoreProcessingInstructions"));
            if (prop && prop.GetSlotValueUnsafe(vm, ipi) && ipi.IsBool())
                IgnoreProcessingInstructions = ipi;

            FindObjProperty(prop, vm, o, Multiname(vm, "ignoreWhitespace"));
            if (prop && prop.GetSlotValueUnsafe(vm, iw) && iw.IsBool())
                IgnoreWhitespace = iw;

            FindObjProperty(prop, vm, o, Multiname(vm, "prettyPrinting"));
            if (prop && prop.GetSlotValueUnsafe(vm, pp) && pp.IsBool())
                PrettyPrinting = pp;

            FindObjProperty(prop, vm, o, Multiname(vm, "prettyIndent"));
            if (prop && prop.GetSlotValueUnsafe(vm, pi) && pi.IsInt())
                PrettyIndent = pi;
        }
#else
        if (o.IsObject() && !o.IsNull())
        {
            AS3::Object& obj = *o.GetObject();
            VM& vm = GetVM();
            StringManager& sm = vm.GetStringManager();
            const Value* v;

            v = obj.FindDynamicSlot(sm.CreateConstString("ignoreComments"));
            if (v && v->IsBool())
                IgnoreComments = *v;

            v = obj.FindDynamicSlot(sm.CreateConstString("ignoreProcessingInstructions"));
            if (v && v->IsBool())
                IgnoreProcessingInstructions = *v;

            v = obj.FindDynamicSlot(sm.CreateConstString("ignoreWhitespace"));
            if (v && v->IsBool())
                IgnoreWhitespace = *v;

            v = obj.FindDynamicSlot(sm.CreateConstString("prettyPrinting"));
            if (v && v->IsBool())
                PrettyPrinting = *v;

            v = obj.FindDynamicSlot(sm.CreateConstString("prettyIndent"));
            if (v && v->IsInt())
                PrettyPrinting = *v;
        }
        else
            SetDefaultValues();
#endif
//##protect##"class_::XML::AS3setSettings()"
    }
    void XML::setSettings(Value& result, const Value& o)
    {
//##protect##"class_::XML::setSettings()"
        AS3setSettings(result, o);
//##protect##"class_::XML::setSettings()"
    }
    void XML::AS3defaultSettings(Value& result)
    {
//##protect##"class_::XML::AS3defaultSettings()"
        VM& vm = GetVM();
        StringManager& sm = vm.GetStringManager();
        Pickable<Instances::Object> obj = vm.MakeObject();

        result = obj;
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreComments"), Value(true));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreProcessingInstructions"), Value(true));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("ignoreWhitespace"), Value(true));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("prettyPrinting"), Value(true));
        obj->AddDynamicSlotValuePair(sm.CreateConstString("prettyIndent"), Value(SInt32(2)));
//##protect##"class_::XML::AS3defaultSettings()"
    }
    void XML::defaultSettings(Value& result)
    {
//##protect##"class_::XML::defaultSettings()"
        AS3defaultSettings(result);
//##protect##"class_::XML::defaultSettings()"
    }
//##protect##"class_$methods"
    void XML::Call(const Value& /*_this*/, Value& result, unsigned argc, const Value* const argv)
    {
        // The same logic as in Construct.
        Construct(result, argc, argv);
    }

    // Created manually.
    const ThunkInfo XML::f[1] = {
        {&InstanceTraits::XML::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    void XML::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        //InitPrototypeFromVTable(obj);
        InitPrototypeFromVTableCheckType(obj);

        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

        AddConstructor(obj);
    }

    void XML::SetDefaultValues()
    {
        IgnoreComments = true;
        IgnoreProcessingInstructions = true;
        IgnoreWhitespace = true;
        PrettyPrinting = true;
        PrettyIndent = 2;
    }
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::XML, Classes::XML::mid_ignoreCommentsGet, bool> TFunc_Classes_XML_ignoreCommentsGet;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_ignoreCommentsSet, Value, bool> TFunc_Classes_XML_ignoreCommentsSet;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_ignoreProcessingInstructionsGet, bool> TFunc_Classes_XML_ignoreProcessingInstructionsGet;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_ignoreProcessingInstructionsSet, Value, bool> TFunc_Classes_XML_ignoreProcessingInstructionsSet;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_ignoreWhitespaceGet, bool> TFunc_Classes_XML_ignoreWhitespaceGet;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_ignoreWhitespaceSet, Value, bool> TFunc_Classes_XML_ignoreWhitespaceSet;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_prettyPrintingGet, bool> TFunc_Classes_XML_prettyPrintingGet;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_prettyPrintingSet, Value, bool> TFunc_Classes_XML_prettyPrintingSet;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_prettyIndentGet, SInt32> TFunc_Classes_XML_prettyIndentGet;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_prettyIndentSet, Value, SInt32> TFunc_Classes_XML_prettyIndentSet;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_AS3settings, Value> TFunc_Classes_XML_AS3settings;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_settings, Value> TFunc_Classes_XML_settings;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_AS3setSettings, Value, const Value&> TFunc_Classes_XML_AS3setSettings;
typedef ThunkFunc1<Classes::XML, Classes::XML::mid_setSettings, Value, const Value&> TFunc_Classes_XML_setSettings;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_AS3defaultSettings, Value> TFunc_Classes_XML_AS3defaultSettings;
typedef ThunkFunc0<Classes::XML, Classes::XML::mid_defaultSettings, Value> TFunc_Classes_XML_defaultSettings;

template <> const TFunc_Classes_XML_ignoreCommentsGet::TMethod TFunc_Classes_XML_ignoreCommentsGet::Method = &Classes::XML::ignoreCommentsGet;
template <> const TFunc_Classes_XML_ignoreCommentsSet::TMethod TFunc_Classes_XML_ignoreCommentsSet::Method = &Classes::XML::ignoreCommentsSet;
template <> const TFunc_Classes_XML_ignoreProcessingInstructionsGet::TMethod TFunc_Classes_XML_ignoreProcessingInstructionsGet::Method = &Classes::XML::ignoreProcessingInstructionsGet;
template <> const TFunc_Classes_XML_ignoreProcessingInstructionsSet::TMethod TFunc_Classes_XML_ignoreProcessingInstructionsSet::Method = &Classes::XML::ignoreProcessingInstructionsSet;
template <> const TFunc_Classes_XML_ignoreWhitespaceGet::TMethod TFunc_Classes_XML_ignoreWhitespaceGet::Method = &Classes::XML::ignoreWhitespaceGet;
template <> const TFunc_Classes_XML_ignoreWhitespaceSet::TMethod TFunc_Classes_XML_ignoreWhitespaceSet::Method = &Classes::XML::ignoreWhitespaceSet;
template <> const TFunc_Classes_XML_prettyPrintingGet::TMethod TFunc_Classes_XML_prettyPrintingGet::Method = &Classes::XML::prettyPrintingGet;
template <> const TFunc_Classes_XML_prettyPrintingSet::TMethod TFunc_Classes_XML_prettyPrintingSet::Method = &Classes::XML::prettyPrintingSet;
template <> const TFunc_Classes_XML_prettyIndentGet::TMethod TFunc_Classes_XML_prettyIndentGet::Method = &Classes::XML::prettyIndentGet;
template <> const TFunc_Classes_XML_prettyIndentSet::TMethod TFunc_Classes_XML_prettyIndentSet::Method = &Classes::XML::prettyIndentSet;
template <> const TFunc_Classes_XML_AS3settings::TMethod TFunc_Classes_XML_AS3settings::Method = &Classes::XML::AS3settings;
template <> const TFunc_Classes_XML_settings::TMethod TFunc_Classes_XML_settings::Method = &Classes::XML::settings;
template <> const TFunc_Classes_XML_AS3setSettings::TMethod TFunc_Classes_XML_AS3setSettings::Method = &Classes::XML::AS3setSettings;
template <> const TFunc_Classes_XML_setSettings::TMethod TFunc_Classes_XML_setSettings::Method = &Classes::XML::setSettings;
template <> const TFunc_Classes_XML_AS3defaultSettings::TMethod TFunc_Classes_XML_AS3defaultSettings::Method = &Classes::XML::AS3defaultSettings;
template <> const TFunc_Classes_XML_defaultSettings::TMethod TFunc_Classes_XML_defaultSettings::Method = &Classes::XML::defaultSettings;

namespace ClassTraits
{
    const ThunkInfo XML::ti[XML::ThunkInfoNum] = {
        {TFunc_Classes_XML_ignoreCommentsGet::Func, &BooleanCI, "ignoreComments", NULL, CT_Get, 0, 0},
        {TFunc_Classes_XML_ignoreCommentsSet::Func, NULL, "ignoreComments", NULL, CT_Set, 1, 1},
        {TFunc_Classes_XML_ignoreProcessingInstructionsGet::Func, &BooleanCI, "ignoreProcessingInstructions", NULL, CT_Get, 0, 0},
        {TFunc_Classes_XML_ignoreProcessingInstructionsSet::Func, NULL, "ignoreProcessingInstructions", NULL, CT_Set, 1, 1},
        {TFunc_Classes_XML_ignoreWhitespaceGet::Func, &BooleanCI, "ignoreWhitespace", NULL, CT_Get, 0, 0},
        {TFunc_Classes_XML_ignoreWhitespaceSet::Func, NULL, "ignoreWhitespace", NULL, CT_Set, 1, 1},
        {TFunc_Classes_XML_prettyPrintingGet::Func, &BooleanCI, "prettyPrinting", NULL, CT_Get, 0, 0},
        {TFunc_Classes_XML_prettyPrintingSet::Func, NULL, "prettyPrinting", NULL, CT_Set, 1, 1},
        {TFunc_Classes_XML_prettyIndentGet::Func, &int_CI, "prettyIndent", NULL, CT_Get, 0, 0},
        {TFunc_Classes_XML_prettyIndentSet::Func, NULL, "prettyIndent", NULL, CT_Set, 1, 1},
        {TFunc_Classes_XML_AS3settings::Func, &ObjectCI, "settings", NS_AS3, CT_Method, 0, 0},
        {TFunc_Classes_XML_settings::Func, &ObjectCI, "settings", NULL, CT_Method, 0, 0},
        {TFunc_Classes_XML_AS3setSettings::Func, NULL, "setSettings", NS_AS3, CT_Method, 0, 1},
        {TFunc_Classes_XML_setSettings::Func, NULL, "setSettings", NULL, CT_Method, 0, 1},
        {TFunc_Classes_XML_AS3defaultSettings::Func, &ObjectCI, "defaultSettings", NS_AS3, CT_Method, 0, 0},
        {TFunc_Classes_XML_defaultSettings::Func, &ObjectCI, "defaultSettings", NULL, CT_Method, 0, 0},
    };
    XML::XML(VM& vm)
    : Traits(vm, XMLCI)
    {
//##protect##"ClassTraits::XML::XML()"
        SetTraitsType(Traits_XML);
//##protect##"ClassTraits::XML::XML()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::XML(vm, XMLCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::XML(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XML::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XML(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "XML", "", &ObjectCI,
    ClassTraits::XML::MakeClassTraits,
    ClassTraits::XML::ThunkInfoNum,
    0,
    InstanceTraits::XML::ThunkInfoNum,
    0,
    ClassTraits::XML::ti,
    NULL,
    InstanceTraits::XML::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

