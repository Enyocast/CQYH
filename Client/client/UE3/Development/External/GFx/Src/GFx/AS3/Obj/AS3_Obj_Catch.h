//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Catch.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Catch_H
#define INC_AS3_Obj_Catch_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Catch;
}

namespace InstanceTraits
{
    class Catch;
}

namespace Classes
{
    class Catch;
}

namespace Instances
{
    class Catch : public Instances::Object
    {
        friend class InstanceTraits::Catch;
        
    public:
        typedef Catch SelfType;
        typedef Classes::Catch ClassType;
        typedef InstanceTraits::Catch TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Catch"; }
#endif
    protected:
        Catch(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Catch : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Catch"; }
#endif
    public:
        Catch(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Catch> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

//##protect##"instance_traits$methods"
        Catch(VMAbcFile& file, VM& vm, const Abc::MethodBodyInfo::ExceptionInfo& e);
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Catch : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Catch"; }
#endif
    public:
        typedef Classes::Catch ClassType;

    public:
        Catch(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Catch : public Class
    {
        friend class ClassTraits::Catch;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Catch"; }
#endif
    public:
        typedef Catch SelfType;
        typedef Catch ClassType;
        
    private:
        Catch(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
    public:
        Pickable<Instances::Catch> MakeInstance(VMAbcFile& file, const Abc::MethodBodyInfo::ExceptionInfo& e);
//##protect##"class_$methods"

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

