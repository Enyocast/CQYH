//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_XMLList.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_XMLList_H
#define INC_AS3_Obj_XMLList_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class XML;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class XMLList;
}

namespace InstanceTraits
{
    class XMLList;
}

namespace Classes
{
    class XMLList;
}

namespace Instances
{
    class XMLList : public Instances::Object
    {
        friend class InstanceTraits::XMLList;
        
    public:
        typedef XMLList SelfType;
        typedef Classes::XMLList ClassType;
        typedef InstanceTraits::XMLList TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::XMLList"; }
#endif
    protected:
        XMLList(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_prototypeGet, 
            mid_prototypeSet, 
            mid_AS3toString, 
            mid_AS3valueOf, 
            mid_AS3hasOwnProperty, 
            mid_AS3propertyIsEnumerable, 
            mid_AS3attribute, 
            mid_AS3attributes, 
            mid_AS3child, 
            mid_AS3children, 
            mid_AS3comments, 
            mid_AS3contains, 
            mid_AS3copy, 
            mid_AS3descendants, 
            mid_AS3elements, 
            mid_AS3hasComplexContent, 
            mid_AS3hasSimpleContent, 
            mid_AS3name, 
            mid_AS3normalize, 
            mid_AS3parent, 
            mid_AS3processingInstructions, 
            mid_AS3text, 
            mid_AS3toXMLString, 
            mid_AS3addNamespace, 
            mid_AS3appendChild, 
            mid_AS3childIndex, 
            mid_AS3inScopeNamespaces, 
            mid_AS3insertChildAfter, 
            mid_AS3insertChildBefore, 
            mid_AS3nodeKind, 
            mid_AS3namespace_, 
            mid_AS3localName, 
            mid_AS3namespaceDeclarations, 
            mid_AS3prependChild, 
            mid_AS3removeNamespace, 
            mid_AS3replace, 
            mid_AS3setChildren, 
            mid_AS3setLocalName, 
            mid_AS3setName, 
            mid_AS3setNamespace, 
        };
        void prototypeGet(Value& result);
        void prototypeSet(Value& result, const Value& p);
        void AS3toString(ASString& result);
        void AS3valueOf(Value& result);
        void AS3hasOwnProperty(bool& result, const ASString& p);
        void AS3propertyIsEnumerable(bool& result, const ASString& p);
        void AS3attribute(Value& result, const Value& arg);
        void AS3attributes(Value& result);
        void AS3child(Value& result, const Value& propertyName);
        void AS3children(Value& result);
        void AS3comments(Value& result);
        void AS3contains(bool& result, const Value& value);
        void AS3copy(Value& result);
        void AS3descendants(Value& result, const ASString& name);
        void AS3elements(Value& result, const ASString& name);
        void AS3hasComplexContent(bool& result);
        void AS3hasSimpleContent(bool& result);
        void AS3name(Value& result);
        void AS3normalize(Value& result);
        void AS3parent(Value& result);
        void AS3processingInstructions(Value& result, const ASString& name);
        void AS3text(Value& result);
        void AS3toXMLString(ASString& result);
        void AS3addNamespace(Value& result, const Value& ns);
        void AS3appendChild(Value& result, const Value& child);
        void AS3childIndex(SInt32& result);
        void AS3inScopeNamespaces(Value& result);
        void AS3insertChildAfter(Value& result, const Value& child1, const Value& child2);
        void AS3insertChildBefore(Value& result, const Value& child1, const Value& child2);
        void AS3nodeKind(ASString& result);
        void AS3namespace_(Value& result, const Value& prefix);
        void AS3localName(Value& result);
        void AS3namespaceDeclarations(Value& result);
        void AS3prependChild(Value& result, const Value& value);
        void AS3removeNamespace(Value& result, const Value& ns);
        void AS3replace(Value& result, const Value& propertyName, const Value& value);
        void AS3setChildren(Value& result, const Value& value);
        void AS3setLocalName(Value& result, const Value& name);
        void AS3setName(Value& result, const Value& name);
        void AS3setNamespace(Value& result, const Value& ns);

//##protect##"instance$data"
        ArrayLH_POD<SPtr<XML> > List;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class XMLList : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::XMLList"; }
#endif
    public:
        XMLList(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::XMLList> MakeInstance(Traits& t);

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
    class XMLList : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::XMLList"; }
#endif
    public:
        typedef Classes::XMLList ClassType;

    public:
        XMLList(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class XMLList : public Class
    {
        friend class ClassTraits::XMLList;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::XMLList"; }
#endif
    public:
        typedef XMLList SelfType;
        typedef XMLList ClassType;
        
    private:
        XMLList(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        virtual void InitPrototype(AS3::Object& obj) const;       
//##protect##"class_$methods"

//##protect##"class_$data"
        static const ThunkInfo f[1];
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

