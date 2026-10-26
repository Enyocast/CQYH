//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_SecurityPanel.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_SecurityPanel_H
#define INC_AS3_Obj_System_SecurityPanel_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SecurityPanel;
}

namespace InstanceTraits
{
    class SecurityPanel;
}

namespace Classes
{
    class SecurityPanel;
}
    
namespace ClassTraits
{
    class SecurityPanel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SecurityPanel"; }
#endif
    public:
        typedef Classes::SecurityPanel ClassType;

    public:
        SecurityPanel(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 7 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SecurityPanel : public Class
    {
        friend class ClassTraits::SecurityPanel;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SecurityPanel"; }
#endif
    public:
        typedef SecurityPanel SelfType;
        typedef SecurityPanel ClassType;
        
    private:
        SecurityPanel(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CAMERA() const { return CAMERA; }
        const char* get_DEFAULT() const { return DEFAULT; }
        const char* get_DISPLAY() const { return DISPLAY; }
        const char* get_LOCAL_STORAGE() const { return LOCAL_STORAGE; }
        const char* get_MICROPHONE() const { return MICROPHONE; }
        const char* get_PRIVACY() const { return PRIVACY; }
        const char* get_SETTINGS_MANAGER() const { return SETTINGS_MANAGER; }


    protected:
        // AS3 API members.
        const char* CAMERA;
        const char* DEFAULT;
        const char* DISPLAY;
        const char* LOCAL_STORAGE;
        const char* MICROPHONE;
        const char* PRIVACY;
        const char* SETTINGS_MANAGER;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

