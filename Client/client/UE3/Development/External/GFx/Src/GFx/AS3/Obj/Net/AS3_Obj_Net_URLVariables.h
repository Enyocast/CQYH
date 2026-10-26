//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLVariables.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLVariables_H
#define INC_AS3_Obj_Net_URLVariables_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLVariables;
}

namespace InstanceTraits
{
    class URLVariables;
}

namespace Classes
{
    class URLVariables;
}

namespace Instances
{
    class URLVariables : public Instances::Object
    {
        friend class InstanceTraits::URLVariables;
        
    public:
        typedef URLVariables SelfType;
        typedef Classes::URLVariables ClassType;
        typedef InstanceTraits::URLVariables TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::URLVariables"; }
#endif
    protected:
        URLVariables(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
    public:
        void SetDataString(const ASString& s) { Data = s; }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_decode, 
            mid_toString, 
        };
        void decode(Value& result, const ASString& source);
        void toString(ASString& result);

//##protect##"instance$data"
    protected:
        ASString Data;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class URLVariables : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::URLVariables"; }
#endif
    public:
        URLVariables(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::URLVariables> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class URLVariables : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLVariables"; }
#endif
    public:
        typedef Classes::URLVariables ClassType;

    public:
        URLVariables(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

