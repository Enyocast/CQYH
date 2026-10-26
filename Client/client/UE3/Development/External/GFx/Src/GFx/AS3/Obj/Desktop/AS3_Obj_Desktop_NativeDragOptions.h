//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_NativeDragOptions.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_NativeDragOptions_H
#define INC_AS3_Obj_Desktop_NativeDragOptions_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NativeDragOptions;
}

namespace InstanceTraits
{
    class NativeDragOptions;
}

namespace Classes
{
    class NativeDragOptions;
}

namespace Instances
{
    class NativeDragOptions : public Instances::Object
    {
        friend class InstanceTraits::NativeDragOptions;
        
    public:
        typedef NativeDragOptions SelfType;
        typedef Classes::NativeDragOptions ClassType;
        typedef InstanceTraits::NativeDragOptions TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NativeDragOptions"; }
#endif
    protected:
        NativeDragOptions(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_allowCopy() const { return allowCopy; }
        bool get_allowLink() const { return allowLink; }
        bool get_allowMove() const { return allowMove; }


    protected:
        // AS3 API members.
        bool allowCopy;
        bool allowLink;
        bool allowMove;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NativeDragOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NativeDragOptions"; }
#endif
    public:
        NativeDragOptions(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NativeDragOptions> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class NativeDragOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NativeDragOptions"; }
#endif
    public:
        typedef Classes::NativeDragOptions ClassType;

    public:
        NativeDragOptions(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

