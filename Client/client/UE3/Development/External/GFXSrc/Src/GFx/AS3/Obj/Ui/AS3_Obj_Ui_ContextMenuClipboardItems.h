//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuClipboardItems.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_ContextMenuClipboardItems_H
#define INC_AS3_Obj_Ui_ContextMenuClipboardItems_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ContextMenuClipboardItems;
}

namespace InstanceTraits
{
    class ContextMenuClipboardItems;
}

namespace Classes
{
    class ContextMenuClipboardItems;
}

namespace Instances
{
    class ContextMenuClipboardItems : public Instances::Object
    {
        friend class InstanceTraits::ContextMenuClipboardItems;
        
    public:
        typedef ContextMenuClipboardItems SelfType;
        typedef Classes::ContextMenuClipboardItems ClassType;
        typedef InstanceTraits::ContextMenuClipboardItems TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ContextMenuClipboardItems"; }
#endif
    protected:
        ContextMenuClipboardItems(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_clear() const { return clear; }
        bool get_copy() const { return copy; }
        bool get_cut() const { return cut; }
        bool get_paste() const { return paste; }
        bool get_selectAll() const { return selectAll; }


    protected:
        // AS3 API members.
        bool clear;
        bool copy;
        bool cut;
        bool paste;
        bool selectAll;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ContextMenuClipboardItems : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ContextMenuClipboardItems"; }
#endif
    public:
        ContextMenuClipboardItems(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ContextMenuClipboardItems> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 5 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ContextMenuClipboardItems : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ContextMenuClipboardItems"; }
#endif
    public:
        typedef Classes::ContextMenuClipboardItems ClassType;

    public:
        ContextMenuClipboardItems(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

