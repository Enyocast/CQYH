//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLNode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Xml_XMLNode_H
#define INC_AS3_Obj_Xml_XMLNode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class XMLNode;
}

namespace InstanceTraits
{
    class XMLNode;
}

namespace Classes
{
    class XMLNode;
}

namespace Instances
{
    class XMLNode : public Instances::Object
    {
        friend class InstanceTraits::XMLNode;
        
    public:
        typedef XMLNode SelfType;
        typedef Classes::XMLNode ClassType;
        typedef InstanceTraits::XMLNode TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::XMLNode"; }
#endif
    protected:
        XMLNode(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::XMLNode* get_firstChild() const { return firstChild; }
        Instances::XMLNode* get_lastChild() const { return lastChild; }
        Instances::XMLNode* get_nextSibling() const { return nextSibling; }
        const ASString& get_nodeName() const { return nodeName; }
        UInt32 get_nodeType() const { return nodeType; }
        const ASString& get_nodeValue() const { return nodeValue; }
        Instances::XMLNode* get_parentNode() const { return parentNode; }
        Instances::XMLNode* get_previousSibling() const { return previousSibling; }


    protected:
        // AS3 API members.
        SPtr<Instances::XMLNode> firstChild;
        SPtr<Instances::XMLNode> lastChild;
        SPtr<Instances::XMLNode> nextSibling;
        ASString nodeName;
        UInt32 nodeType;
        ASString nodeValue;
        SPtr<Instances::XMLNode> parentNode;
        SPtr<Instances::XMLNode> previousSibling;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class XMLNode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::XMLNode"; }
#endif
    public:
        XMLNode(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::XMLNode> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 14 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class XMLNode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::XMLNode"; }
#endif
    public:
        typedef Classes::XMLNode ClassType;

    public:
        XMLNode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

