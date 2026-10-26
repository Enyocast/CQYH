//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundLoaderContext.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_SoundLoaderContext_H
#define INC_AS3_Obj_Media_SoundLoaderContext_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SoundLoaderContext;
}

namespace InstanceTraits
{
    class SoundLoaderContext;
}

namespace Classes
{
    class SoundLoaderContext;
}

namespace Instances
{
    class SoundLoaderContext : public Instances::Object
    {
        friend class InstanceTraits::SoundLoaderContext;
        
    public:
        typedef SoundLoaderContext SelfType;
        typedef Classes::SoundLoaderContext ClassType;
        typedef InstanceTraits::SoundLoaderContext TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SoundLoaderContext"; }
#endif
    protected:
        SoundLoaderContext(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_bufferTime() const { return bufferTime; }
        bool get_checkPolicyFile() const { return checkPolicyFile; }


    protected:
        // AS3 API members.
        Value::Number bufferTime;
        bool checkPolicyFile;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SoundLoaderContext : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SoundLoaderContext"; }
#endif
    public:
        SoundLoaderContext(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SoundLoaderContext> MakeInstance(Traits& t);

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
    class SoundLoaderContext : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SoundLoaderContext"; }
#endif
    public:
        typedef Classes::SoundLoaderContext ClassType;

    public:
        SoundLoaderContext(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

