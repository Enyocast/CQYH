//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityImplementation.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Accessibility_AccessibilityImplementation_H
#define INC_AS3_Obj_Accessibility_AccessibilityImplementation_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Rectangle;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AccessibilityImplementation;
}

namespace InstanceTraits
{
    class AccessibilityImplementation;
}

namespace Classes
{
    class AccessibilityImplementation;
}

namespace Instances
{
    class AccessibilityImplementation : public Instances::Object
    {
        friend class InstanceTraits::AccessibilityImplementation;
        
    public:
        typedef AccessibilityImplementation SelfType;
        typedef Classes::AccessibilityImplementation ClassType;
        typedef InstanceTraits::AccessibilityImplementation TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::AccessibilityImplementation"; }
#endif
    protected:
        AccessibilityImplementation(InstanceTraits::Traits& t);

//##protect##"instance$methods"
#ifdef errno
#undef errno
#endif
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        UInt32 get_errno() const { return errno; }
        bool get_stub() const { return stub; }


    protected:
        // AS3 API members.
        UInt32 errno;
        bool stub;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class AccessibilityImplementation : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::AccessibilityImplementation"; }
#endif
    public:
        AccessibilityImplementation(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::AccessibilityImplementation> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 12 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class AccessibilityImplementation : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AccessibilityImplementation"; }
#endif
    public:
        typedef Classes::AccessibilityImplementation ClassType;

    public:
        AccessibilityImplementation(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

