//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_DeleteObjectSample.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Sampler_DeleteObjectSample_H
#define INC_AS3_Obj_Sampler_DeleteObjectSample_H

#include "AS3_Obj_Sampler_Sample.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class DeleteObjectSample;
}

namespace InstanceTraits
{
    class DeleteObjectSample;
}

namespace Classes
{
    class DeleteObjectSample;
}

namespace Instances
{
    class DeleteObjectSample : public Instances::Sample
    {
        friend class InstanceTraits::DeleteObjectSample;
        
    public:
        typedef DeleteObjectSample SelfType;
        typedef Classes::DeleteObjectSample ClassType;
        typedef InstanceTraits::DeleteObjectSample TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::DeleteObjectSample"; }
#endif
    protected:
        DeleteObjectSample(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_id() const { return id; }
        Value::Number get_size() const { return size; }


    protected:
        // AS3 API members.
        const Value::Number id;
        const Value::Number size;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class DeleteObjectSample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::DeleteObjectSample"; }
#endif
    public:
        DeleteObjectSample(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::DeleteObjectSample> MakeInstance(Traits& t);

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
    class DeleteObjectSample : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::DeleteObjectSample"; }
#endif
    public:
        typedef Classes::DeleteObjectSample ClassType;

    public:
        DeleteObjectSample(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

