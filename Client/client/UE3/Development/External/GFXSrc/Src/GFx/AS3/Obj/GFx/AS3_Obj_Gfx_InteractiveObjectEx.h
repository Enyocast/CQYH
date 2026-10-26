//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_InteractiveObjectEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_InteractiveObjectEx_H
#define INC_AS3_Obj_Gfx_InteractiveObjectEx_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../Display/AS3_Obj_Display_InteractiveObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class InteractiveObjectEx;
}

namespace InstanceTraits
{
    class InteractiveObjectEx;
}

namespace Classes
{
    class InteractiveObjectEx;
}
    
namespace ClassTraits
{
    class InteractiveObjectEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::InteractiveObjectEx"; }
#endif
    public:
        typedef Classes::InteractiveObjectEx ClassType;

    public:
        InteractiveObjectEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class InteractiveObjectEx : public Class
    {
        friend class ClassTraits::InteractiveObjectEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::InteractiveObjectEx"; }
#endif
    public:
        typedef InteractiveObjectEx SelfType;
        typedef InteractiveObjectEx ClassType;
        
    private:
        InteractiveObjectEx(ClassTraits::Traits& t);
       
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
            mid_setHitTestDisable, 
            mid_getHitTestDisable, 
            mid_setTopmostLevel, 
            mid_getTopmostLevel, 
        };
        void setHitTestDisable(Value& result, Instances::InteractiveObject* o, bool f);
        void getHitTestDisable(bool& result, Instances::InteractiveObject* o);
        void setTopmostLevel(Value& result, Instances::InteractiveObject* o, bool f);
        void getTopmostLevel(bool& result, Instances::InteractiveObject* o);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

