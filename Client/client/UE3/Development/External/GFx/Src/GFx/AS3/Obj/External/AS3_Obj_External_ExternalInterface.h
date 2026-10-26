//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_External_ExternalInterface.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_External_ExternalInterface_H
#define INC_AS3_Obj_External_ExternalInterface_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ExternalInterface;
}

namespace InstanceTraits
{
    class ExternalInterface;
}

namespace Classes
{
    class ExternalInterface;
}
    
namespace ClassTraits
{
    class ExternalInterface : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ExternalInterface"; }
#endif
    public:
        typedef Classes::ExternalInterface ClassType;

    public:
        ExternalInterface(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ExternalInterface : public Class
    {
        friend class ClassTraits::ExternalInterface;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ExternalInterface"; }
#endif
    public:
        typedef ExternalInterface SelfType;
        typedef ExternalInterface ClassType;
        
    private:
        ExternalInterface(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_availableGet, 
            mid_marshallExceptionsGet, 
            mid_marshallExceptionsSet, 
            mid_objectIDGet, 
            mid_addCallback, 
            mid_call, 
        };
        void availableGet(bool& result);
        void marshallExceptionsGet(bool& result);
        void marshallExceptionsSet(Value& result, bool value);
        void objectIDGet(ASString& result);
        void addCallback(Value& result, const ASString& functionName, const Value& closure);
        void call(Value& result, unsigned argc, const Value* const argv);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

