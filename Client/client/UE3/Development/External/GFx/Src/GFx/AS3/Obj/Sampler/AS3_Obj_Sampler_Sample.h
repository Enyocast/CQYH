//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_Sample.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Sampler_Sample_H
#define INC_AS3_Obj_Sampler_Sample_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Sample;
}

namespace InstanceTraits
{
    class Sample;
}

namespace Classes
{
    class Sample;
}

namespace Instances
{
    class Sample : public Instances::Object
    {
        friend class InstanceTraits::Sample;
        
    public:
        typedef Sample SelfType;
        typedef Classes::Sample ClassType;
        typedef InstanceTraits::Sample TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Sample"; }
#endif
    protected:
        Sample(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::Array* get_stack() const { return stack; }
        Value::Number get_time() const { return time; }


    protected:
        // AS3 API members.
        SPtr<Instances::Array> stack;
        const Value::Number time;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Sample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Sample"; }
#endif
    public:
        Sample(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Sample> MakeInstance(Traits& t);

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
    class Sample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Sample"; }
#endif
    public:
        typedef Classes::Sample ClassType;

    public:
        Sample(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

