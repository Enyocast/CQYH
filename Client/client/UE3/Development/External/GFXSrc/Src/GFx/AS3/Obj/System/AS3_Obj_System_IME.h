//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_IME.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_IME_H
#define INC_AS3_Obj_System_IME_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IME;
}

namespace InstanceTraits
{
    class IME;
}

namespace Classes
{
    class IME;
}
    
namespace ClassTraits
{
    class IME : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IME"; }
#endif
    public:
        typedef Classes::IME ClassType;

    public:
        IME(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IME : public Class
    {
        friend class ClassTraits::IME;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IME"; }
#endif
    public:
        typedef IME SelfType;
        typedef IME ClassType;
        
    private:
        IME(ClassTraits::Traits& t);
       
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
            mid_conversionModeSet, 
            mid_conversionModeGet, 
            mid_enabledGet, 
            mid_enabledSet, 
            mid_doConversion, 
            mid_setCompositionString, 
        };
        void conversionModeSet(Value& result, const ASString& value);
        void conversionModeGet(ASString& result);
        void enabledGet(bool& result);
        void enabledSet(Value& result, bool value);
        void doConversion(Value& result);
        void setCompositionString(Value& result, const ASString& composition);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

