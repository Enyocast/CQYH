//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_Extensions.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_Extensions_H
#define INC_AS3_Obj_Gfx_Extensions_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../Text/AS3_Obj_Text_TextField.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Extensions;
}

namespace InstanceTraits
{
    class Extensions;
}

namespace Classes
{
    class Extensions;
}
    
namespace ClassTraits
{
    class Extensions : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Extensions"; }
#endif
    public:
        typedef Classes::Extensions ClassType;

    public:
        Extensions(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 13 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Extensions : public Class
    {
        friend class ClassTraits::Extensions;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Extensions"; }
#endif
    public:
        typedef Extensions SelfType;
        typedef Extensions ClassType;
        
    private:
        Extensions(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_EDGEAA_INHERIT() const { return EDGEAA_INHERIT; }
        UInt32 get_EDGEAA_ON() const { return EDGEAA_ON; }
        UInt32 get_EDGEAA_OFF() const { return EDGEAA_OFF; }
        UInt32 get_EDGEAA_DISABLE() const { return EDGEAA_DISABLE; }

        // AS3 API methods.
        enum MethodID {
            mid_enabledSet, 
            mid_enabledGet, 
            mid_noInvisibleAdvanceSet, 
            mid_noInvisibleAdvanceGet, 
            mid_getTopMostEntity, 
            mid_getMouseTopMostEntity, 
            mid_setMouseCursorType, 
            mid_getMouseCursorType, 
            mid_getEdgeAAMode, 
            mid_setEdgeAAMode, 
            mid_numControllersGet, 
            mid_visibleRectGet, 
            mid_isScaleformGet, 
        };
        void enabledSet(Value& result, bool value);
        void enabledGet(bool& result);
        void noInvisibleAdvanceSet(Value& result, bool value);
        void noInvisibleAdvanceGet(bool& result);
        void getTopMostEntity(Value& result, Value::Number x, Value::Number y, bool testAll);
        void getMouseTopMostEntity(Value& result, bool testAll, UInt32 mouseIndex);
        void setMouseCursorType(Value& result, const ASString& cursor, UInt32 mouseIndex);
        void getMouseCursorType(ASString& result, UInt32 mouseIndex);
        void getEdgeAAMode(UInt32& result, Instances::DisplayObject* dispObj);
        void setEdgeAAMode(Value& result, Instances::DisplayObject* dispObj, UInt32 mode);
        void numControllersGet(UInt32& result);
        void visibleRectGet(Value& result);
        void isScaleformGet(bool& result);

    protected:
        // AS3 API members.
        const UInt32 EDGEAA_INHERIT;
        const UInt32 EDGEAA_ON;
        const UInt32 EDGEAA_OFF;
        const UInt32 EDGEAA_DISABLE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

