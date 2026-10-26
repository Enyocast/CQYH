//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_Multitouch.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_Multitouch_H
#define INC_AS3_Obj_Ui_Multitouch_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Multitouch;
}

namespace InstanceTraits
{
    class Multitouch;
}

namespace Classes
{
    class Multitouch;
}
    
namespace ClassTraits
{
    class Multitouch : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Multitouch"; }
#endif
    public:
        typedef Classes::Multitouch ClassType;

    public:
        Multitouch(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Multitouch : public Class
    {
        friend class ClassTraits::Multitouch;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Multitouch"; }
#endif
    public:
        typedef Multitouch SelfType;
        typedef Multitouch ClassType;
        
    private:
        Multitouch(ClassTraits::Traits& t);
       
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
            mid_inputModeGet, 
            mid_inputModeSet, 
            mid_maxTouchPointsGet, 
            mid_supportedGesturesGet, 
            mid_supportsGestureEventsGet, 
            mid_supportsTouchEventsGet, 
        };
        void inputModeGet(ASString& result);
        void inputModeSet(Value& result, const ASString& value);
        void maxTouchPointsGet(SInt32& result);
        void supportedGesturesGet(Value& result);
        void supportsGestureEventsGet(bool& result);
        void supportsTouchEventsGet(bool& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

