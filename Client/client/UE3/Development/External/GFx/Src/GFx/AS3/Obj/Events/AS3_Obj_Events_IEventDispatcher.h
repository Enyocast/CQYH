//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_IEventDispatcher.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_IEventDispatcher_H
#define INC_AS3_Obj_Events_IEventDispatcher_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Event;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IEventDispatcher;
}

namespace InstanceTraits
{
    class IEventDispatcher;
}

namespace Classes
{
    class IEventDispatcher;
}
    
namespace ClassTraits
{
    class IEventDispatcher : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IEventDispatcher"; }
#endif
    public:
        typedef Classes::IEventDispatcher ClassType;

    public:
        IEventDispatcher(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

