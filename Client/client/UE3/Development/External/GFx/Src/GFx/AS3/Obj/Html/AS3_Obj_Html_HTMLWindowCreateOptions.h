//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLWindowCreateOptions.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Html_HTMLWindowCreateOptions_H
#define INC_AS3_Obj_Html_HTMLWindowCreateOptions_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class HTMLWindowCreateOptions;
}

namespace InstanceTraits
{
    class HTMLWindowCreateOptions;
}

namespace Classes
{
    class HTMLWindowCreateOptions;
}

namespace Instances
{
    class HTMLWindowCreateOptions : public Instances::Object
    {
        friend class InstanceTraits::HTMLWindowCreateOptions;
        
    public:
        typedef HTMLWindowCreateOptions SelfType;
        typedef Classes::HTMLWindowCreateOptions ClassType;
        typedef InstanceTraits::HTMLWindowCreateOptions TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::HTMLWindowCreateOptions"; }
#endif
    protected:
        HTMLWindowCreateOptions(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_fullscreen() const { return fullscreen; }
        Value::Number get_height() const { return height; }
        bool get_locationBarVisible() const { return locationBarVisible; }
        bool get_menuBarVisible() const { return menuBarVisible; }
        bool get_resizable() const { return resizable; }
        bool get_scrollBarsVisible() const { return scrollBarsVisible; }
        bool get_statusBarVisible() const { return statusBarVisible; }
        bool get_toolBarVisible() const { return toolBarVisible; }
        Value::Number get_width() const { return width; }
        Value::Number get_x() const { return x; }
        Value::Number get_y() const { return y; }


    protected:
        // AS3 API members.
        bool fullscreen;
        Value::Number height;
        bool locationBarVisible;
        bool menuBarVisible;
        bool resizable;
        bool scrollBarsVisible;
        bool statusBarVisible;
        bool toolBarVisible;
        Value::Number width;
        Value::Number x;
        Value::Number y;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class HTMLWindowCreateOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::HTMLWindowCreateOptions"; }
#endif
    public:
        HTMLWindowCreateOptions(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::HTMLWindowCreateOptions> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 11 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class HTMLWindowCreateOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::HTMLWindowCreateOptions"; }
#endif
    public:
        typedef Classes::HTMLWindowCreateOptions ClassType;

    public:
        HTMLWindowCreateOptions(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

