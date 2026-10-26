//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Sampler_StackFrame.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Sampler_StackFrame_H
#define INC_AS3_Obj_Sampler_StackFrame_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StackFrame;
}

namespace InstanceTraits
{
    class StackFrame;
}

namespace Classes
{
    class StackFrame;
}

namespace Instances
{
    class StackFrame : public Instances::Object
    {
        friend class InstanceTraits::StackFrame;
        
    public:
        typedef StackFrame SelfType;
        typedef Classes::StackFrame ClassType;
        typedef InstanceTraits::StackFrame TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::StackFrame"; }
#endif
    protected:
        StackFrame(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const char* get_file() const { return file; }
        UInt32 get_line() const { return line; }
        const char* get_name() const { return name; }


    protected:
        // AS3 API members.
        const char* file;
        const UInt32 line;
        const char* name;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class StackFrame : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::StackFrame"; }
#endif
    public:
        StackFrame(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::StackFrame> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 3 };
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
    class StackFrame : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StackFrame"; }
#endif
    public:
        typedef Classes::StackFrame ClassType;

    public:
        StackFrame(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

