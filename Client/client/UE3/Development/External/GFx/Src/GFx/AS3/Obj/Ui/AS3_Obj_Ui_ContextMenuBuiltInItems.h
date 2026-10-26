//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_ContextMenuBuiltInItems.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_ContextMenuBuiltInItems_H
#define INC_AS3_Obj_Ui_ContextMenuBuiltInItems_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ContextMenuBuiltInItems;
}

namespace InstanceTraits
{
    class ContextMenuBuiltInItems;
}

namespace Classes
{
    class ContextMenuBuiltInItems;
}

namespace Instances
{
    class ContextMenuBuiltInItems : public Instances::Object
    {
        friend class InstanceTraits::ContextMenuBuiltInItems;
        
    public:
        typedef ContextMenuBuiltInItems SelfType;
        typedef Classes::ContextMenuBuiltInItems ClassType;
        typedef InstanceTraits::ContextMenuBuiltInItems TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ContextMenuBuiltInItems"; }
#endif
    protected:
        ContextMenuBuiltInItems(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_forwardAndBack() const { return forwardAndBack; }
        bool get_loop() const { return loop; }
        bool get_play() const { return play; }
        bool get_print() const { return print; }
        bool get_quality() const { return quality; }
        bool get_rewind() const { return rewind; }
        bool get_save() const { return save; }
        bool get_zoom() const { return zoom; }


    protected:
        // AS3 API members.
        bool forwardAndBack;
        bool loop;
        bool play;
        bool print;
        bool quality;
        bool rewind;
        bool save;
        bool zoom;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ContextMenuBuiltInItems : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ContextMenuBuiltInItems"; }
#endif
    public:
        ContextMenuBuiltInItems(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ContextMenuBuiltInItems> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ContextMenuBuiltInItems : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ContextMenuBuiltInItems"; }
#endif
    public:
        typedef Classes::ContextMenuBuiltInItems ClassType;

    public:
        ContextMenuBuiltInItems(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

