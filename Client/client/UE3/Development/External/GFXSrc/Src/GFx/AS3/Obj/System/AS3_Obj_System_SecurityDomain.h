//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_SecurityDomain.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_SecurityDomain_H
#define INC_AS3_Obj_System_SecurityDomain_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SecurityDomain;
}

namespace InstanceTraits
{
    class SecurityDomain;
}

namespace Classes
{
    class SecurityDomain;
}

namespace Instances
{
    class SecurityDomain : public Instances::Object
    {
        friend class InstanceTraits::SecurityDomain;
        
    public:
        typedef SecurityDomain SelfType;
        typedef Classes::SecurityDomain ClassType;
        typedef InstanceTraits::SecurityDomain TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SecurityDomain"; }
#endif
    protected:
        SecurityDomain(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SecurityDomain : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SecurityDomain"; }
#endif
    public:
        SecurityDomain(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SecurityDomain> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class SecurityDomain : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SecurityDomain"; }
#endif
    public:
        typedef Classes::SecurityDomain ClassType;

    public:
        SecurityDomain(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SecurityDomain : public Class
    {
        friend class ClassTraits::SecurityDomain;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SecurityDomain"; }
#endif
    public:
        typedef SecurityDomain SelfType;
        typedef SecurityDomain ClassType;
        
    private:
        SecurityDomain(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_currentDomainGet, 
        };
        void currentDomainGet(Value& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

