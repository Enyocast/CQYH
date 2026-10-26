//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_ApplicationDomain.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_ApplicationDomain_H
#define INC_AS3_Obj_System_ApplicationDomain_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ApplicationDomain;
}

namespace InstanceTraits
{
    class ApplicationDomain;
}

namespace Classes
{
    class ApplicationDomain;
}

namespace Instances
{
    class ApplicationDomain : public Instances::Object
    {
        friend class InstanceTraits::ApplicationDomain;
        
    public:
        typedef ApplicationDomain SelfType;
        typedef Classes::ApplicationDomain ClassType;
        typedef InstanceTraits::ApplicationDomain TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ApplicationDomain"; }
#endif
    protected:
        ApplicationDomain(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_parentDomainGet, 
            mid_getDefinition, 
            mid_hasDefinition, 
        };
        void parentDomainGet(Value& result);
        void getDefinition(Value& result, const ASString& name);
        void hasDefinition(bool& result, const ASString& name);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ApplicationDomain : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ApplicationDomain"; }
#endif
    public:
        ApplicationDomain(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ApplicationDomain> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ApplicationDomain : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ApplicationDomain"; }
#endif
    public:
        typedef Classes::ApplicationDomain ClassType;

    public:
        ApplicationDomain(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

