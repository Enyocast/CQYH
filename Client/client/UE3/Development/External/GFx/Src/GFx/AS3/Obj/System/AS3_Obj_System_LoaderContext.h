//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_LoaderContext.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_LoaderContext_H
#define INC_AS3_Obj_System_LoaderContext_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "AS3_Obj_System_SecurityDomain.h"
#include "AS3_Obj_System_ApplicationDomain.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class LoaderContext;
}

namespace InstanceTraits
{
    class LoaderContext;
}

namespace Classes
{
    class LoaderContext;
}

namespace Instances
{
    class LoaderContext : public Instances::Object
    {
        friend class InstanceTraits::LoaderContext;
        
    public:
        typedef LoaderContext SelfType;
        typedef Classes::LoaderContext ClassType;
        typedef InstanceTraits::LoaderContext TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::LoaderContext"; }
#endif
    protected:
        LoaderContext(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_allowLoadBytesCodeExecution() const { return allowLoadBytesCodeExecution; }
        Instances::ApplicationDomain* get_applicationDomain() const { return applicationDomain; }
        bool get_checkPolicyFile() const { return checkPolicyFile; }
        Instances::SecurityDomain* get_securityDomain() const { return securityDomain; }


    protected:
        // AS3 API members.
        bool allowLoadBytesCodeExecution;
        SPtr<Instances::ApplicationDomain> applicationDomain;
        bool checkPolicyFile;
        SPtr<Instances::SecurityDomain> securityDomain;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class LoaderContext : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::LoaderContext"; }
#endif
    public:
        LoaderContext(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::LoaderContext> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class LoaderContext : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::LoaderContext"; }
#endif
    public:
        typedef Classes::LoaderContext ClassType;

    public:
        LoaderContext(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

