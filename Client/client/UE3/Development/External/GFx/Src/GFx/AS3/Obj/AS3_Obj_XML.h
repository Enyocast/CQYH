//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_XML.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_XML_H
#define INC_AS3_Obj_XML_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class XML;
}

namespace InstanceTraits
{
    class XML;
}

namespace Classes
{
    class XML;
}

namespace Instances
{
    class XML : public Instances::Object
    {
        friend class InstanceTraits::XML;
        
    public:
        typedef XML SelfType;
        typedef Classes::XML ClassType;
        typedef InstanceTraits::XML TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::XML"; }
#endif
    protected:
        XML(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_AS3toString, 
            mid_AS3hasOwnProperty, 
            mid_AS3propertyIsEnumerable, 
            mid_AS3addNamespace, 
            mid_AS3appendChild, 
            mid_AS3attribute, 
            mid_AS3attributes, 
            mid_AS3child, 
            mid_AS3childIndex, 
            mid_AS3children, 
            mid_AS3comments, 
            mid_AS3contains, 
            mid_AS3copy, 
            mid_AS3descendants, 
            mid_AS3elements, 
            mid_AS3hasComplexContent, 
            mid_AS3hasSimpleContent, 
            mid_AS3inScopeNamespaces, 
            mid_AS3insertChildAfter, 
            mid_AS3insertChildBefore, 
            mid_AS3localName, 
            mid_AS3name, 
            mid_AS3namespace_, 
            mid_AS3namespaceDeclarations, 
            mid_AS3nodeKind, 
            mid_AS3normalize, 
            mid_AS3parent, 
            mid_AS3processingInstructions, 
            mid_AS3prependChild, 
            mid_AS3removeNamespace, 
            mid_AS3replace, 
            mid_AS3setChildren, 
            mid_AS3setLocalName, 
            mid_AS3setName, 
            mid_AS3setNamespace, 
            mid_AS3text, 
            mid_AS3toXMLString, 
            mid_AS3notification, 
            mid_AS3setNotification, 
            mid_AS3valueOf, 
        };
        void AS3toString(ASString& result);
        void AS3hasOwnProperty(bool& result, const ASString& p);
        void AS3propertyIsEnumerable(bool& result, const ASString& p);
        void AS3addNamespace(Value& result, const Value& ns);
        void AS3appendChild(Value& result, const Value& child);
        void AS3attribute(Value& result, const Value& arg);
        void AS3attributes(Value& result);
        void AS3child(Value& result, const Value& propertyName);
        void AS3childIndex(SInt32& result);
        void AS3children(Value& result);
        void AS3comments(Value& result);
        void AS3contains(bool& result, const Value& value);
        void AS3copy(Value& result);
        void AS3descendants(Value& result, const ASString& name);
        void AS3elements(Value& result, const ASString& name);
        void AS3hasComplexContent(bool& result);
        void AS3hasSimpleContent(bool& result);
        void AS3inScopeNamespaces(Value& result);
        void AS3insertChildAfter(Value& result, const Value& child1, const Value& child2);
        void AS3insertChildBefore(Value& result, const Value& child1, const Value& child2);
        void AS3localName(Value& result);
        void AS3name(Value& result);
        void AS3namespace_(Value& result, const Value& prefix);
        void AS3namespaceDeclarations(Value& result);
        void AS3nodeKind(ASString& result);
        void AS3normalize(Value& result);
        void AS3parent(Value& result);
        void AS3processingInstructions(Value& result, const ASString& name);
        void AS3prependChild(Value& result, const Value& value);
        void AS3removeNamespace(Value& result, const Value& ns);
        void AS3replace(Value& result, const Value& propertyName, const Value& value);
        void AS3setChildren(Value& result, const Value& value);
        void AS3setLocalName(Value& result, const Value& name);
        void AS3setName(Value& result, const Value& name);
        void AS3setNamespace(Value& result, const Value& ns);
        void AS3text(Value& result);
        void AS3toXMLString(ASString& result);
        void AS3notification(Value& result);
        void AS3setNotification(Value& result, const Value& f);
        void AS3valueOf(Value& result);

//##protect##"instance$data"
        Value Root;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class XML : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::XML"; }
#endif
    public:
        XML(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::XML> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 40 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
        // Prototype related functions.
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class XML : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::XML"; }
#endif
    public:
        typedef Classes::XML ClassType;

    public:
        XML(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 16 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class XML : public Class
    {
        friend class ClassTraits::XML;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::XML"; }
#endif
    public:
        typedef XML SelfType;
        typedef XML ClassType;
        
    private:
        XML(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual void InitPrototype(AS3::Object& obj) const;

        void SetDefaultValues();
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_ignoreCommentsGet, 
            mid_ignoreCommentsSet, 
            mid_ignoreProcessingInstructionsGet, 
            mid_ignoreProcessingInstructionsSet, 
            mid_ignoreWhitespaceGet, 
            mid_ignoreWhitespaceSet, 
            mid_prettyPrintingGet, 
            mid_prettyPrintingSet, 
            mid_prettyIndentGet, 
            mid_prettyIndentSet, 
            mid_AS3settings, 
            mid_settings, 
            mid_AS3setSettings, 
            mid_setSettings, 
            mid_AS3defaultSettings, 
            mid_defaultSettings, 
        };
        void ignoreCommentsGet(bool& result);
        void ignoreCommentsSet(Value& result, bool newIgnore);
        void ignoreProcessingInstructionsGet(bool& result);
        void ignoreProcessingInstructionsSet(Value& result, bool newIgnore);
        void ignoreWhitespaceGet(bool& result);
        void ignoreWhitespaceSet(Value& result, bool newIgnore);
        void prettyPrintingGet(bool& result);
        void prettyPrintingSet(Value& result, bool newPretty);
        void prettyIndentGet(SInt32& result);
        void prettyIndentSet(Value& result, SInt32 newIndent);
        void AS3settings(Value& result);
        void settings(Value& result);
        void AS3setSettings(Value& result, const Value& o);
        void setSettings(Value& result, const Value& o);
        void AS3defaultSettings(Value& result);
        void defaultSettings(Value& result);

//##protect##"class_$data"
        bool IgnoreComments;
        bool IgnoreProcessingInstructions;
        bool IgnoreWhitespace;
        bool PrettyPrinting;
        SInt32 PrettyIndent;
        static const ThunkInfo f[1];
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

