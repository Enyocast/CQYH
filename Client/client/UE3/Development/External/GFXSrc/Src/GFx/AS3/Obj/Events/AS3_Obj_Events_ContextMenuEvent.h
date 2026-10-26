//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_ContextMenuEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_ContextMenuEvent_H
#define INC_AS3_Obj_Events_ContextMenuEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class InteractiveObject;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ContextMenuEvent;
}

namespace InstanceTraits
{
    class ContextMenuEvent;
}

namespace Classes
{
    class ContextMenuEvent;
}
    
namespace ClassTraits
{
    class ContextMenuEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ContextMenuEvent"; }
#endif
    public:
        typedef Classes::ContextMenuEvent ClassType;

    public:
        ContextMenuEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ContextMenuEvent : public Class
    {
        friend class ClassTraits::ContextMenuEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ContextMenuEvent"; }
#endif
    public:
        typedef ContextMenuEvent SelfType;
        typedef ContextMenuEvent ClassType;
        
    private:
        ContextMenuEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_MENU_ITEM_SELECT() const { return MENU_ITEM_SELECT; }
        const char* get_MENU_SELECT() const { return MENU_SELECT; }


    protected:
        // AS3 API members.
        const char* MENU_ITEM_SELECT;
        const char* MENU_SELECT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

