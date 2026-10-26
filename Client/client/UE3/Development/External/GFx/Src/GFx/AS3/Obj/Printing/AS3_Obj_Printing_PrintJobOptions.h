//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Printing_PrintJobOptions.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Printing_PrintJobOptions_H
#define INC_AS3_Obj_Printing_PrintJobOptions_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class PrintJobOptions;
}

namespace InstanceTraits
{
    class PrintJobOptions;
}

namespace Classes
{
    class PrintJobOptions;
}

namespace Instances
{
    class PrintJobOptions : public Instances::Object
    {
        friend class InstanceTraits::PrintJobOptions;
        
    public:
        typedef PrintJobOptions SelfType;
        typedef Classes::PrintJobOptions ClassType;
        typedef InstanceTraits::PrintJobOptions TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::PrintJobOptions"; }
#endif
    protected:
        PrintJobOptions(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        bool get_printAsBitmap() const { return printAsBitmap; }


    protected:
        // AS3 API members.
        bool printAsBitmap;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class PrintJobOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::PrintJobOptions"; }
#endif
    public:
        PrintJobOptions(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::PrintJobOptions> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class PrintJobOptions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::PrintJobOptions"; }
#endif
    public:
        typedef Classes::PrintJobOptions ClassType;

    public:
        PrintJobOptions(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

