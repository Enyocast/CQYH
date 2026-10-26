//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_AVM1Movie.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_AVM1Movie_H
#define INC_AS3_Obj_Display_AVM1Movie_H

#include "AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class AVM1Movie;
}

namespace InstanceTraits
{
    class AVM1Movie;
}

namespace Classes
{
    class AVM1Movie;
}

namespace Instances
{
    class AVM1Movie : public Instances::DisplayObject
    {
        friend class InstanceTraits::AVM1Movie;
        
    public:
        typedef AVM1Movie SelfType;
        typedef Classes::AVM1Movie ClassType;
        typedef InstanceTraits::AVM1Movie TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::AVM1Movie"; }
#endif
    protected:
        AVM1Movie(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class AVM1Movie : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::AVM1Movie"; }
#endif
    public:
        AVM1Movie(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::AVM1Movie> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class AVM1Movie : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::AVM1Movie"; }
#endif
    public:
        typedef Classes::AVM1Movie ClassType;

    public:
        AVM1Movie(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

