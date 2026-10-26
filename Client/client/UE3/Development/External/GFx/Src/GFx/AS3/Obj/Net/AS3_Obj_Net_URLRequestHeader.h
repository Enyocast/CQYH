//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestHeader.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLRequestHeader_H
#define INC_AS3_Obj_Net_URLRequestHeader_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLRequestHeader;
}

namespace InstanceTraits
{
    class URLRequestHeader;
}

namespace Classes
{
    class URLRequestHeader;
}

namespace Instances
{
    class URLRequestHeader : public Instances::Object
    {
        friend class InstanceTraits::URLRequestHeader;
        
    public:
        typedef URLRequestHeader SelfType;
        typedef Classes::URLRequestHeader ClassType;
        typedef InstanceTraits::URLRequestHeader TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::URLRequestHeader"; }
#endif
    protected:
        URLRequestHeader(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_name() const { return name; }
        const ASString& get_value() const { return value; }


    protected:
        // AS3 API members.
        ASString name;
        ASString value;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class URLRequestHeader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::URLRequestHeader"; }
#endif
    public:
        URLRequestHeader(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::URLRequestHeader> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class URLRequestHeader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLRequestHeader"; }
#endif
    public:
        typedef Classes::URLRequestHeader ClassType;

    public:
        URLRequestHeader(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

