//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Accessibility_AccessibilityProperties.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Accessibility_AccessibilityProperties_H
#define INC_AS3_Obj_Accessibility_AccessibilityProperties_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AccessibilityProperties;
}

namespace InstanceTraits
{
    class AccessibilityProperties;
}

namespace Classes
{
    class AccessibilityProperties;
}

namespace Instances
{
    class AccessibilityProperties : public Instances::Object
    {
        friend class InstanceTraits::AccessibilityProperties;
        
    public:
        typedef AccessibilityProperties SelfType;
        typedef Classes::AccessibilityProperties ClassType;
        typedef InstanceTraits::AccessibilityProperties TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::AccessibilityProperties"; }
#endif
    protected:
        AccessibilityProperties(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_description() const { return description; }
        bool get_forceSimple() const { return forceSimple; }
        const ASString& get_name() const { return name; }
        bool get_noAutoLabeling() const { return noAutoLabeling; }
        const ASString& get_shortcut() const { return shortcut; }
        bool get_silent() const { return silent; }


    protected:
        // AS3 API members.
        ASString description;
        bool forceSimple;
        ASString name;
        bool noAutoLabeling;
        ASString shortcut;
        bool silent;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class AccessibilityProperties : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::AccessibilityProperties"; }
#endif
    public:
        AccessibilityProperties(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::AccessibilityProperties> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 6 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class AccessibilityProperties : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AccessibilityProperties"; }
#endif
    public:
        typedef Classes::AccessibilityProperties ClassType;

    public:
        AccessibilityProperties(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

