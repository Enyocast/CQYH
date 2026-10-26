//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenu.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_ContextMenu_H
#define INC_AS3_Obj_Ui_ContextMenu_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "AS3_Obj_Ui_ContextMenuBuiltInItems.h"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ContextMenu;
}

namespace InstanceTraits
{
    class ContextMenu;
}

namespace Classes
{
    class ContextMenu;
}

namespace Instances
{
    class ContextMenu : public Instances::EventDispatcher
    {
        friend class InstanceTraits::ContextMenu;
        
    public:
        typedef ContextMenu SelfType;
        typedef Classes::ContextMenu ClassType;
        typedef InstanceTraits::ContextMenu TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ContextMenu"; }
#endif
    protected:
        ContextMenu(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_builtInItemsGet, 
            mid_builtInItemsSet, 
            mid_customItemsGet, 
            mid_customItemsSet, 
            mid_clone, 
            mid_hideBuiltInItems, 
        };
        void builtInItemsGet(Value& result);
        void builtInItemsSet(Value& result, Instances::ContextMenuBuiltInItems* value);
        void customItemsGet(Value& result);
        void customItemsSet(Value& result, Instances::Array* value);
        void clone(Value& result);
        void hideBuiltInItems(Value& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ContextMenu : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ContextMenu"; }
#endif
    public:
        ContextMenu(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ContextMenu> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 5 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ContextMenu : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ContextMenu"; }
#endif
    public:
        typedef Classes::ContextMenu ClassType;

    public:
        ContextMenu(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

