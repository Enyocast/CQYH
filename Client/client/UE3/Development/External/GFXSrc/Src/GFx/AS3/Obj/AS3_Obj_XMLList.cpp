//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_XMLList.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_XMLList.h"
#include "../AS3_VM.h"
#include "../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Array.h"
#include "AS3_Obj_XML.h"
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
    ASString GetMethodDefArg<Instances::XMLList, Instances::XMLList::mid_AS3descendants, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::XMLList, Instances::XMLList::mid_AS3elements, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::XMLList, Instances::XMLList::mid_AS3processingInstructions, 0, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("*");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::XMLList, Instances::XMLList::mid_AS3namespace_, 0, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

} // namespace Impl
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_prototypeGet, Value> TFunc_Instances_XMLList_prototypeGet;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_prototypeSet, Value, const Value&> TFunc_Instances_XMLList_prototypeSet;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3toString, ASString> TFunc_Instances_XMLList_AS3toString;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3valueOf, Value> TFunc_Instances_XMLList_AS3valueOf;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3hasOwnProperty, bool, const ASString&> TFunc_Instances_XMLList_AS3hasOwnProperty;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3propertyIsEnumerable, bool, const ASString&> TFunc_Instances_XMLList_AS3propertyIsEnumerable;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3attribute, Value, const Value&> TFunc_Instances_XMLList_AS3attribute;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3attributes, Value> TFunc_Instances_XMLList_AS3attributes;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3child, Value, const Value&> TFunc_Instances_XMLList_AS3child;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3children, Value> TFunc_Instances_XMLList_AS3children;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3comments, Value> TFunc_Instances_XMLList_AS3comments;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3contains, bool, const Value&> TFunc_Instances_XMLList_AS3contains;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3copy, Value> TFunc_Instances_XMLList_AS3copy;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3descendants, Value, const ASString&> TFunc_Instances_XMLList_AS3descendants;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3elements, Value, const ASString&> TFunc_Instances_XMLList_AS3elements;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3hasComplexContent, bool> TFunc_Instances_XMLList_AS3hasComplexContent;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3hasSimpleContent, bool> TFunc_Instances_XMLList_AS3hasSimpleContent;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3name, Value> TFunc_Instances_XMLList_AS3name;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3normalize, Value> TFunc_Instances_XMLList_AS3normalize;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3parent, Value> TFunc_Instances_XMLList_AS3parent;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3processingInstructions, Value, const ASString&> TFunc_Instances_XMLList_AS3processingInstructions;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3text, Value> TFunc_Instances_XMLList_AS3text;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3toXMLString, ASString> TFunc_Instances_XMLList_AS3toXMLString;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3addNamespace, Value, const Value&> TFunc_Instances_XMLList_AS3addNamespace;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3appendChild, Value, const Value&> TFunc_Instances_XMLList_AS3appendChild;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3childIndex, SInt32> TFunc_Instances_XMLList_AS3childIndex;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3inScopeNamespaces, Value> TFunc_Instances_XMLList_AS3inScopeNamespaces;
typedef ThunkFunc2<Instances::XMLList, Instances::XMLList::mid_AS3insertChildAfter, Value, const Value&, const Value&> TFunc_Instances_XMLList_AS3insertChildAfter;
typedef ThunkFunc2<Instances::XMLList, Instances::XMLList::mid_AS3insertChildBefore, Value, const Value&, const Value&> TFunc_Instances_XMLList_AS3insertChildBefore;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3nodeKind, ASString> TFunc_Instances_XMLList_AS3nodeKind;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3namespace_, Value, const Value&> TFunc_Instances_XMLList_AS3namespace_;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3localName, Value> TFunc_Instances_XMLList_AS3localName;
typedef ThunkFunc0<Instances::XMLList, Instances::XMLList::mid_AS3namespaceDeclarations, Value> TFunc_Instances_XMLList_AS3namespaceDeclarations;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3prependChild, Value, const Value&> TFunc_Instances_XMLList_AS3prependChild;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3removeNamespace, Value, const Value&> TFunc_Instances_XMLList_AS3removeNamespace;
typedef ThunkFunc2<Instances::XMLList, Instances::XMLList::mid_AS3replace, Value, const Value&, const Value&> TFunc_Instances_XMLList_AS3replace;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3setChildren, Value, const Value&> TFunc_Instances_XMLList_AS3setChildren;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3setLocalName, Value, const Value&> TFunc_Instances_XMLList_AS3setLocalName;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3setName, Value, const Value&> TFunc_Instances_XMLList_AS3setName;
typedef ThunkFunc1<Instances::XMLList, Instances::XMLList::mid_AS3setNamespace, Value, const Value&> TFunc_Instances_XMLList_AS3setNamespace;

template <> const TFunc_Instances_XMLList_prototypeGet::TMethod TFunc_Instances_XMLList_prototypeGet::Method = &Instances::XMLList::prototypeGet;
template <> const TFunc_Instances_XMLList_prototypeSet::TMethod TFunc_Instances_XMLList_prototypeSet::Method = &Instances::XMLList::prototypeSet;
template <> const TFunc_Instances_XMLList_AS3toString::TMethod TFunc_Instances_XMLList_AS3toString::Method = &Instances::XMLList::AS3toString;
template <> const TFunc_Instances_XMLList_AS3valueOf::TMethod TFunc_Instances_XMLList_AS3valueOf::Method = &Instances::XMLList::AS3valueOf;
template <> const TFunc_Instances_XMLList_AS3hasOwnProperty::TMethod TFunc_Instances_XMLList_AS3hasOwnProperty::Method = &Instances::XMLList::AS3hasOwnProperty;
template <> const TFunc_Instances_XMLList_AS3propertyIsEnumerable::TMethod TFunc_Instances_XMLList_AS3propertyIsEnumerable::Method = &Instances::XMLList::AS3propertyIsEnumerable;
template <> const TFunc_Instances_XMLList_AS3attribute::TMethod TFunc_Instances_XMLList_AS3attribute::Method = &Instances::XMLList::AS3attribute;
template <> const TFunc_Instances_XMLList_AS3attributes::TMethod TFunc_Instances_XMLList_AS3attributes::Method = &Instances::XMLList::AS3attributes;
template <> const TFunc_Instances_XMLList_AS3child::TMethod TFunc_Instances_XMLList_AS3child::Method = &Instances::XMLList::AS3child;
template <> const TFunc_Instances_XMLList_AS3children::TMethod TFunc_Instances_XMLList_AS3children::Method = &Instances::XMLList::AS3children;
template <> const TFunc_Instances_XMLList_AS3comments::TMethod TFunc_Instances_XMLList_AS3comments::Method = &Instances::XMLList::AS3comments;
template <> const TFunc_Instances_XMLList_AS3contains::TMethod TFunc_Instances_XMLList_AS3contains::Method = &Instances::XMLList::AS3contains;
template <> const TFunc_Instances_XMLList_AS3copy::TMethod TFunc_Instances_XMLList_AS3copy::Method = &Instances::XMLList::AS3copy;
template <> const TFunc_Instances_XMLList_AS3descendants::TMethod TFunc_Instances_XMLList_AS3descendants::Method = &Instances::XMLList::AS3descendants;
template <> const TFunc_Instances_XMLList_AS3elements::TMethod TFunc_Instances_XMLList_AS3elements::Method = &Instances::XMLList::AS3elements;
template <> const TFunc_Instances_XMLList_AS3hasComplexContent::TMethod TFunc_Instances_XMLList_AS3hasComplexContent::Method = &Instances::XMLList::AS3hasComplexContent;
template <> const TFunc_Instances_XMLList_AS3hasSimpleContent::TMethod TFunc_Instances_XMLList_AS3hasSimpleContent::Method = &Instances::XMLList::AS3hasSimpleContent;
template <> const TFunc_Instances_XMLList_AS3name::TMethod TFunc_Instances_XMLList_AS3name::Method = &Instances::XMLList::AS3name;
template <> const TFunc_Instances_XMLList_AS3normalize::TMethod TFunc_Instances_XMLList_AS3normalize::Method = &Instances::XMLList::AS3normalize;
template <> const TFunc_Instances_XMLList_AS3parent::TMethod TFunc_Instances_XMLList_AS3parent::Method = &Instances::XMLList::AS3parent;
template <> const TFunc_Instances_XMLList_AS3processingInstructions::TMethod TFunc_Instances_XMLList_AS3processingInstructions::Method = &Instances::XMLList::AS3processingInstructions;
template <> const TFunc_Instances_XMLList_AS3text::TMethod TFunc_Instances_XMLList_AS3text::Method = &Instances::XMLList::AS3text;
template <> const TFunc_Instances_XMLList_AS3toXMLString::TMethod TFunc_Instances_XMLList_AS3toXMLString::Method = &Instances::XMLList::AS3toXMLString;
template <> const TFunc_Instances_XMLList_AS3addNamespace::TMethod TFunc_Instances_XMLList_AS3addNamespace::Method = &Instances::XMLList::AS3addNamespace;
template <> const TFunc_Instances_XMLList_AS3appendChild::TMethod TFunc_Instances_XMLList_AS3appendChild::Method = &Instances::XMLList::AS3appendChild;
template <> const TFunc_Instances_XMLList_AS3childIndex::TMethod TFunc_Instances_XMLList_AS3childIndex::Method = &Instances::XMLList::AS3childIndex;
template <> const TFunc_Instances_XMLList_AS3inScopeNamespaces::TMethod TFunc_Instances_XMLList_AS3inScopeNamespaces::Method = &Instances::XMLList::AS3inScopeNamespaces;
template <> const TFunc_Instances_XMLList_AS3insertChildAfter::TMethod TFunc_Instances_XMLList_AS3insertChildAfter::Method = &Instances::XMLList::AS3insertChildAfter;
template <> const TFunc_Instances_XMLList_AS3insertChildBefore::TMethod TFunc_Instances_XMLList_AS3insertChildBefore::Method = &Instances::XMLList::AS3insertChildBefore;
template <> const TFunc_Instances_XMLList_AS3nodeKind::TMethod TFunc_Instances_XMLList_AS3nodeKind::Method = &Instances::XMLList::AS3nodeKind;
template <> const TFunc_Instances_XMLList_AS3namespace_::TMethod TFunc_Instances_XMLList_AS3namespace_::Method = &Instances::XMLList::AS3namespace_;
template <> const TFunc_Instances_XMLList_AS3localName::TMethod TFunc_Instances_XMLList_AS3localName::Method = &Instances::XMLList::AS3localName;
template <> const TFunc_Instances_XMLList_AS3namespaceDeclarations::TMethod TFunc_Instances_XMLList_AS3namespaceDeclarations::Method = &Instances::XMLList::AS3namespaceDeclarations;
template <> const TFunc_Instances_XMLList_AS3prependChild::TMethod TFunc_Instances_XMLList_AS3prependChild::Method = &Instances::XMLList::AS3prependChild;
template <> const TFunc_Instances_XMLList_AS3removeNamespace::TMethod TFunc_Instances_XMLList_AS3removeNamespace::Method = &Instances::XMLList::AS3removeNamespace;
template <> const TFunc_Instances_XMLList_AS3replace::TMethod TFunc_Instances_XMLList_AS3replace::Method = &Instances::XMLList::AS3replace;
template <> const TFunc_Instances_XMLList_AS3setChildren::TMethod TFunc_Instances_XMLList_AS3setChildren::Method = &Instances::XMLList::AS3setChildren;
template <> const TFunc_Instances_XMLList_AS3setLocalName::TMethod TFunc_Instances_XMLList_AS3setLocalName::Method = &Instances::XMLList::AS3setLocalName;
template <> const TFunc_Instances_XMLList_AS3setName::TMethod TFunc_Instances_XMLList_AS3setName::Method = &Instances::XMLList::AS3setName;
template <> const TFunc_Instances_XMLList_AS3setNamespace::TMethod TFunc_Instances_XMLList_AS3setNamespace::Method = &Instances::XMLList::AS3setNamespace;

namespace Instances
{
    XMLList::XMLList(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::XMLList::XMLList()$data"
//##protect##"instance::XMLList::XMLList()$data"
    {
//##protect##"instance::XMLList::XMLList()$code"
//##protect##"instance::XMLList::XMLList()$code"
    }

    void XMLList::prototypeGet(Value& result)
    {
//##protect##"instance::XMLList::prototypeGet()"
        InstanceTraits::XMLList& itr = static_cast<InstanceTraits::XMLList&>(GetInstanceTraits());
        Pickable<Instances::XMLList> r = itr.MakeInstance(itr);
        result = r;
//##protect##"instance::XMLList::prototypeGet()"
    }
    void XMLList::prototypeSet(Value& result, const Value& p)
    {
//##protect##"instance::XMLList::prototypeSet()"
        SF_UNUSED2(result, p);
//##protect##"instance::XMLList::prototypeSet()"
    }
    void XMLList::AS3toString(ASString& result)
    {
//##protect##"instance::XMLList::AS3toString()"
        SF_UNUSED1(result);
#if 0
        if (_this.IsObject() && _this.GetObject())
        {
            Class* _class = vm.GetClass(ClassTraits::XMLList::Info.Name);

            if (_class)
            {
                // If this object is a prototype object.
                if (_this.GetObject() == &_class->GetPrototype())
                {
                    // This method is called on a prototype object.
                    result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
                    return;
                }

                // If this object is of class XML.
                if (vm.GetClassTraits(_this).IsOfType(_class->GetClassTraits()))
                {
                    ASString r = vm.GetStringManager().CreateEmptyString();
                    SelfType& o = static_cast<SelfType&>(*_this.GetObject());

                    o.AS3toString(r);
                    if (vm.IsException())
                        return;

                    result = r;

                    return;
                }
            }
        }

        vm.ThrowTypeError(VM::Error(VM::eConvertNullToObjectError, vm));
#endif
//##protect##"instance::XMLList::AS3toString()"
    }
    void XMLList::AS3valueOf(Value& result)
    {
//##protect##"instance::XMLList::AS3valueOf()"
        result = this;
//##protect##"instance::XMLList::AS3valueOf()"
    }
    void XMLList::AS3hasOwnProperty(bool& result, const ASString& p)
    {
//##protect##"instance::XMLList::AS3hasOwnProperty()"
        SF_UNUSED1(p);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XMLList::AS3hasOwnProperty()"
    }
    void XMLList::AS3propertyIsEnumerable(bool& result, const ASString& p)
    {
//##protect##"instance::XMLList::AS3propertyIsEnumerable()"
        SF_UNUSED1(p);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XMLList::AS3propertyIsEnumerable()"
    }
    void XMLList::AS3attribute(Value& result, const Value& arg)
    {
//##protect##"instance::XMLList::AS3attribute()"
        SF_UNUSED1(arg);
       result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3attribute()"
    }
    void XMLList::AS3attributes(Value& result)
    {
//##protect##"instance::XMLList::AS3attributes()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3attributes()"
    }
    void XMLList::AS3child(Value& result, const Value& propertyName)
    {
//##protect##"instance::XMLList::AS3child()"
        SF_UNUSED1(propertyName);
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3child()"
    }
    void XMLList::AS3children(Value& result)
    {
//##protect##"instance::XMLList::AS3children()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3children()"
    }
    void XMLList::AS3comments(Value& result)
    {
//##protect##"instance::XMLList::AS3comments()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3comments()"
    }
    void XMLList::AS3contains(bool& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3contains()"
        SF_UNUSED1(value);
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XMLList::AS3contains()"
    }
    void XMLList::AS3copy(Value& result)
    {
//##protect##"instance::XMLList::AS3copy()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3copy()"
    }
    void XMLList::AS3descendants(Value& result, const ASString& name)
    {
//##protect##"instance::XMLList::AS3descendants()"
        SF_UNUSED1(name);
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3descendants()"
    }
    void XMLList::AS3elements(Value& result, const ASString& name)
    {
//##protect##"instance::XMLList::AS3elements()"
        SF_UNUSED1(name);
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3elements()"
    }
    void XMLList::AS3hasComplexContent(bool& result)
    {
//##protect##"instance::XMLList::AS3hasComplexContent()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XMLList::AS3hasComplexContent()"
    }
    void XMLList::AS3hasSimpleContent(bool& result)
    {
//##protect##"instance::XMLList::AS3hasSimpleContent()"
        result = AS3::DefaultValue<bool>(GetStringManager());
//##protect##"instance::XMLList::AS3hasSimpleContent()"
    }
    void XMLList::AS3name(Value& result)
    {
//##protect##"instance::XMLList::AS3name()"
        result = AS3::DefaultValue<Instances::Object*>(GetStringManager());
//##protect##"instance::XMLList::AS3name()"
    }
    void XMLList::AS3normalize(Value& result)
    {
//##protect##"instance::XMLList::AS3normalize()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3normalize()"
    }
    void XMLList::AS3parent(Value& result)
    {
//##protect##"instance::XMLList::AS3parent()"
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XMLList::AS3parent()"
    }
    void XMLList::AS3processingInstructions(Value& result, const ASString& name)
    {
//##protect##"instance::XMLList::AS3processingInstructions()"
        SF_UNUSED1(name);
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3processingInstructions()"
    }
    void XMLList::AS3text(Value& result)
    {
//##protect##"instance::XMLList::AS3text()"
        result = AS3::DefaultValue<Instances::XMLList*>(GetStringManager());
//##protect##"instance::XMLList::AS3text()"
    }
    void XMLList::AS3toXMLString(ASString& result)
    {
//##protect##"instance::XMLList::AS3toXMLString()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("XMLList::toXMLString()");
//##protect##"instance::XMLList::AS3toXMLString()"
    }
    void XMLList::AS3addNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3addNamespace()"
        SF_UNUSED1(ns);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XMLList::AS3addNamespace()"
    }
    void XMLList::AS3appendChild(Value& result, const Value& child)
    {
//##protect##"instance::XMLList::AS3appendChild()"
        SF_UNUSED1(child);
        result = AS3::DefaultValue<Instances::XML*>(GetStringManager());
//##protect##"instance::XMLList::AS3appendChild()"
    }
    void XMLList::AS3childIndex(SInt32& result)
    {
//##protect##"instance::XMLList::AS3childIndex()"
        result = AS3::DefaultValue<int>(GetStringManager());
//##protect##"instance::XMLList::AS3childIndex()"
    }
    void XMLList::AS3inScopeNamespaces(Value& result)
    {
//##protect##"instance::XMLList::AS3inScopeNamespaces()"
        result = AS3::DefaultValue<Instances::Array*>(GetStringManager());
//##protect##"instance::XMLList::AS3inScopeNamespaces()"
    }
    void XMLList::AS3insertChildAfter(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XMLList::AS3insertChildAfter()"
        SF_UNUSED2(child1, child2);
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XMLList::AS3insertChildAfter()"
    }
    void XMLList::AS3insertChildBefore(Value& result, const Value& child1, const Value& child2)
    {
//##protect##"instance::XMLList::AS3insertChildBefore()"
        SF_UNUSED2(child1, child2);
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XMLList::AS3insertChildBefore()"
    }
    void XMLList::AS3nodeKind(ASString& result)
    {
//##protect##"instance::XMLList::AS3nodeKind()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("XMLList::nodeKind()");
//##protect##"instance::XMLList::AS3nodeKind()"
    }
    void XMLList::AS3namespace_(Value& result, const Value& prefix)
    {
//##protect##"instance::XMLList::AS3namespace_()"
        SF_UNUSED1(prefix);
        result = AS3::DefaultValue<Value>(GetStringManager());
//##protect##"instance::XMLList::AS3namespace_()"
    }
    void XMLList::AS3localName(Value& result)
    {
//##protect##"instance::XMLList::AS3localName()"
        result = AS3::DefaultValue<Instances::Object*>(GetStringManager());
//##protect##"instance::XMLList::AS3localName()"
    }
    void XMLList::AS3namespaceDeclarations(Value& result)
    {
//##protect##"instance::XMLList::AS3namespaceDeclarations()"
        result = AS3::DefaultValue<Instances::Array*>(GetStringManager());
//##protect##"instance::XMLList::AS3namespaceDeclarations()"
    }
    void XMLList::AS3prependChild(Value& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3prependChild()"
        SF_UNUSED2(result, value);
        NOT_IMPLEMENTED("XMLList::prependChild()");
//##protect##"instance::XMLList::AS3prependChild()"
    }
    void XMLList::AS3removeNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3removeNamespace()"
        SF_UNUSED2(result, ns);
        NOT_IMPLEMENTED("XMLList::removeNamespace()");
//##protect##"instance::XMLList::AS3removeNamespace()"
    }
    void XMLList::AS3replace(Value& result, const Value& propertyName, const Value& value)
    {
//##protect##"instance::XMLList::AS3replace()"
        SF_UNUSED3(result, propertyName, value);
        NOT_IMPLEMENTED("XMLList::replace()");
//##protect##"instance::XMLList::AS3replace()"
    }
    void XMLList::AS3setChildren(Value& result, const Value& value)
    {
//##protect##"instance::XMLList::AS3setChildren()"
        SF_UNUSED2(result, value);
        NOT_IMPLEMENTED("XMLList::setChildren()");
//##protect##"instance::XMLList::AS3setChildren()"
    }
    void XMLList::AS3setLocalName(Value& result, const Value& name)
    {
//##protect##"instance::XMLList::AS3setLocalName()"
        SF_UNUSED2(result, name);
        NOT_IMPLEMENTED("XMLList::setLocalName()");
//##protect##"instance::XMLList::AS3setLocalName()"
    }
    void XMLList::AS3setName(Value& result, const Value& name)
    {
//##protect##"instance::XMLList::AS3setName()"
        SF_UNUSED2(result, name);
        NOT_IMPLEMENTED("XMLList::setName()");
//##protect##"instance::XMLList::AS3setName()"
    }
    void XMLList::AS3setNamespace(Value& result, const Value& ns)
    {
//##protect##"instance::XMLList::AS3setNamespace()"
        SF_UNUSED2(result, ns);
        NOT_IMPLEMENTED("XMLList::setNamespace()");
//##protect##"instance::XMLList::AS3setNamespace()"
    }

//##protect##"instance$methods"
    void XMLList::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Instances::Object::ForEachChild_GC(prcc, op);

        const UPInt size = List.GetSize();
        for (UPInt i = 0; i < size; ++i)
            AS3::ForEachChild_GC(prcc, List[i], op SF_DEBUG_ARG(*this));
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo XMLList::ti[XMLList::ThunkInfoNum] = {
        {TFunc_Instances_XMLList_prototypeGet::Func, &XMLListCI, "prototype", NULL, CT_Get, 0, 0},
        {TFunc_Instances_XMLList_prototypeSet::Func, NULL, "prototype", NULL, CT_Set, 1, 1},
        {TFunc_Instances_XMLList_AS3toString::Func, &StringCI, "toString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3valueOf::Func, &XMLListCI, "valueOf", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3hasOwnProperty::Func, &BooleanCI, "hasOwnProperty", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3propertyIsEnumerable::Func, &BooleanCI, "propertyIsEnumerable", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3attribute::Func, &XMLListCI, "attribute", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3attributes::Func, &XMLListCI, "attributes", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3child::Func, &XMLListCI, "child", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3children::Func, &XMLListCI, "children", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3comments::Func, &XMLListCI, "comments", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3contains::Func, &BooleanCI, "contains", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3copy::Func, &XMLListCI, "copy", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3descendants::Func, &XMLListCI, "descendants", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XMLList_AS3elements::Func, &XMLListCI, "elements", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XMLList_AS3hasComplexContent::Func, &BooleanCI, "hasComplexContent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3hasSimpleContent::Func, &BooleanCI, "hasSimpleContent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3name::Func, &ObjectCI, "name", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3normalize::Func, &XMLListCI, "normalize", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3parent::Func, NULL, "parent", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3processingInstructions::Func, &XMLListCI, "processingInstructions", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XMLList_AS3text::Func, &XMLListCI, "text", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3toXMLString::Func, &StringCI, "toXMLString", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3addNamespace::Func, &XMLCI, "addNamespace", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3appendChild::Func, &XMLCI, "appendChild", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3childIndex::Func, &int_CI, "childIndex", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3inScopeNamespaces::Func, &ArrayCI, "inScopeNamespaces", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3insertChildAfter::Func, NULL, "insertChildAfter", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3insertChildBefore::Func, NULL, "insertChildBefore", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3nodeKind::Func, &StringCI, "nodeKind", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3namespace_::Func, NULL, "namespace", NS_AS3, CT_Method, 0, 1},
        {TFunc_Instances_XMLList_AS3localName::Func, &ObjectCI, "localName", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3namespaceDeclarations::Func, &ArrayCI, "namespaceDeclarations", NS_AS3, CT_Method, 0, 0},
        {TFunc_Instances_XMLList_AS3prependChild::Func, &XMLCI, "prependChild", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3removeNamespace::Func, &XMLCI, "removeNamespace", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3replace::Func, &XMLCI, "replace", NS_AS3, CT_Method, 2, 2},
        {TFunc_Instances_XMLList_AS3setChildren::Func, &XMLCI, "setChildren", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setLocalName::Func, NULL, "setLocalName", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setName::Func, NULL, "setName", NS_AS3, CT_Method, 1, 1},
        {TFunc_Instances_XMLList_AS3setNamespace::Func, NULL, "setNamespace", NS_AS3, CT_Method, 1, 1},
    };

    XMLList::XMLList(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::XMLList::XMLList()"
        SetTraitsType(Traits_XMLList);
//##protect##"InstanceTraits::XMLList::XMLList()"
        SetMemSize(sizeof(Instances::XMLList));

    }

    Pickable<Instances::XMLList> XMLList::MakeInstance(Traits& t)
    {
        return Pickable<Instances::XMLList>(new(t.Alloc()) Instances::XMLList(t));
    }

    void XMLList::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
    void XMLList::toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv)
    {
#ifdef SF_ENABLE_XML

        if (_this.IsObject() && _this.GetObject() == &vm.GetClassXMLList().GetPrototype())
            // This method is called on a prototype object.
            result = vm.GetStringManager().GetBuiltin(AS3Builtin_empty_);
        else
        {
            const Traits& tr = vm.GetValueTraits(_this);
            const BuiltinTraitsType tt = tr.GetTraitsType();

            if (tt != Traits_XMLList || tr.IsClassTraits())
                return vm.ThrowTypeError(VM::Error(VM::eInvokeOnIncompatibleObjectError, vm));

            Instances::XMLList* obj = static_cast<Instances::XMLList*>(_this.GetObject());
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
    XMLList::XMLList(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::XMLList::XMLList()"
//##protect##"class_::XMLList::XMLList()"
    }
//##protect##"class_$methods"
    // Created manually.
    const ThunkInfo XMLList::f[1] = {
        {&InstanceTraits::XML::toStringProto, &StringCI, "toString", NULL, CT_Method, 0, 0},
    };

    void XMLList::InitPrototype(AS3::Object& obj) const
    {
        if (GetParentClass())
            GetParentClass()->InitPrototype(obj);

        //InitPrototypeFromVTable(obj);
        InitPrototypeFromVTableCheckType(obj);

        for (unsigned i = 0; i < NUMBEROF(f); ++i)
            AddDynamicFunc(obj, f[i]);

        AddConstructor(obj);
    }
//##protect##"class_$methods"

} // namespace Classes


namespace ClassTraits
{
    XMLList::XMLList(VM& vm)
    : Traits(vm, XMLListCI)
    {
//##protect##"ClassTraits::XMLList::XMLList()"
        SetTraitsType(Traits_XMLList);
//##protect##"ClassTraits::XMLList::XMLList()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::XMLList(vm, XMLListCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::XMLList(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> XMLList::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) XMLList(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo XMLListCI = {
    ClassInfo::CompileTime | ClassInfo::DynamicObject,
    "XMLList", "", &ObjectCI,
    ClassTraits::XMLList::MakeClassTraits,
    0,
    0,
    InstanceTraits::XMLList::ThunkInfoNum,
    0,
    NULL,
    NULL,
    InstanceTraits::XMLList::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

