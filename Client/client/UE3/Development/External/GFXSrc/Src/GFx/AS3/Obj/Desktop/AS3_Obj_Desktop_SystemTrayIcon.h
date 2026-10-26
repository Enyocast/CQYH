//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_SystemTrayIcon.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_SystemTrayIcon_H
#define INC_AS3_Obj_Desktop_SystemTrayIcon_H

#include "AS3_Obj_Desktop_InteractiveIcon.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class NativeMenu;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SystemTrayIcon;
}

namespace InstanceTraits
{
    class SystemTrayIcon;
}

namespace Classes
{
    class SystemTrayIcon;
}
    
namespace ClassTraits
{
    class SystemTrayIcon : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SystemTrayIcon"; }
#endif
    public:
        typedef Classes::SystemTrayIcon ClassType;

    public:
        SystemTrayIcon(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SystemTrayIcon : public Class
    {
        friend class ClassTraits::SystemTrayIcon;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SystemTrayIcon"; }
#endif
    public:
        typedef SystemTrayIcon SelfType;
        typedef SystemTrayIcon ClassType;
        
    private:
        SystemTrayIcon(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        Value::Number get_MAX_TIP_LENGTH() const { return MAX_TIP_LENGTH; }


    protected:
        // AS3 API members.
        const Value::Number MAX_TIP_LENGTH;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

