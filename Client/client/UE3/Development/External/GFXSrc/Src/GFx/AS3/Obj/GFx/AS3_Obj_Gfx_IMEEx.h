//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_IMEEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_IMEEx_H
#define INC_AS3_Obj_Gfx_IMEEx_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "AS3_Obj_Gfx_IMECandidateListStyle.h"
#include "../../../AS3/Obj/Display/AS3_Obj_Display_Sprite.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IMEEx;
}

namespace InstanceTraits
{
    class IMEEx;
}

namespace Classes
{
    class IMEEx;
}
    
namespace ClassTraits
{
    class IMEEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IMEEx"; }
#endif
    public:
        typedef Classes::IMEEx ClassType;

    public:
        IMEEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 5 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IMEEx : public Class
    {
        friend class ClassTraits::IMEEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IMEEx"; }
#endif
    public:
        typedef IMEEx SelfType;
        typedef IMEEx ClassType;
        
    private:
        IMEEx(ClassTraits::Traits& t);
       
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
            mid_getIMECandidateListStyle, 
            mid_setIMECandidateListStyle, 
            mid_SendLangBarMessage, 
            mid_GetOSVersion, 
            mid_GetCompositionString, 
        };
        void getIMECandidateListStyle(Value& result);
        void setIMECandidateListStyle(Value& result, Instances::IMECandidateListStyle* style);
        void SendLangBarMessage(Value& result, Instances::Sprite* mc, const ASString& command, const ASString& message);
        void GetOSVersion(ASString& result);
        void GetCompositionString(ASString& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

