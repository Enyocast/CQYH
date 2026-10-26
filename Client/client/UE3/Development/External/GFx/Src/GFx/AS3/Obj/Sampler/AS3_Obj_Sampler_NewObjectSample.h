//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_NewObjectSample.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Sampler_NewObjectSample_H
#define INC_AS3_Obj_Sampler_NewObjectSample_H

#include "AS3_Obj_Sampler_Sample.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NewObjectSample;
}

namespace InstanceTraits
{
    class NewObjectSample;
}

namespace Classes
{
    class NewObjectSample;
}

namespace Instances
{
    class NewObjectSample : public Instances::Sample
    {
        friend class InstanceTraits::NewObjectSample;
        
    public:
        typedef NewObjectSample SelfType;
        typedef Classes::NewObjectSample ClassType;
        typedef InstanceTraits::NewObjectSample TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NewObjectSample"; }
#endif
    protected:
        NewObjectSample(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_id() const { return id; }
        Class* get_type() const { return type; }


    protected:
        // AS3 API members.
        const Value::Number id;
        SPtr<Class> type;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NewObjectSample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NewObjectSample"; }
#endif
    public:
        NewObjectSample(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NewObjectSample> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class NewObjectSample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NewObjectSample"; }
#endif
    public:
        typedef Classes::NewObjectSample ClassType;

    public:
        NewObjectSample(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

