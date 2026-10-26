//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Xml_XMLDocument.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Xml_XMLDocument_H
#define INC_AS3_Obj_Xml_XMLDocument_H

#include "AS3_Obj_Xml_XMLNode.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class XMLDocument;
}

namespace InstanceTraits
{
    class XMLDocument;
}

namespace Classes
{
    class XMLDocument;
}

namespace Instances
{
    class XMLDocument : public Instances::XMLNode
    {
        friend class InstanceTraits::XMLDocument;
        
    public:
        typedef XMLDocument SelfType;
        typedef Classes::XMLDocument ClassType;
        typedef InstanceTraits::XMLDocument TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::XMLDocument"; }
#endif
    protected:
        XMLDocument(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::Object* get_docTypeDecl() const { return docTypeDecl; }
        Instances::Object* get_idMap() const { return idMap; }
        bool get_ignoreWhite() const { return ignoreWhite; }
        Instances::Object* get_xmlDecl() const { return xmlDecl; }


    protected:
        // AS3 API members.
        SPtr<Instances::Object> docTypeDecl;
        SPtr<Instances::Object> idMap;
        bool ignoreWhite;
        SPtr<Instances::Object> xmlDecl;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class XMLDocument : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::XMLDocument"; }
#endif
    public:
        XMLDocument(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::XMLDocument> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class XMLDocument : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::XMLDocument"; }
#endif
    public:
        typedef Classes::XMLDocument ClassType;

    public:
        XMLDocument(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

