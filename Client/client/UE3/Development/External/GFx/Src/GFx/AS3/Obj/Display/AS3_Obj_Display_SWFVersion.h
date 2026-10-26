//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_SWFVersion.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_SWFVersion_H
#define INC_AS3_Obj_Display_SWFVersion_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SWFVersion;
}

namespace InstanceTraits
{
    class SWFVersion;
}

namespace Classes
{
    class SWFVersion;
}
    
namespace ClassTraits
{
    class SWFVersion : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SWFVersion"; }
#endif
    public:
        typedef Classes::SWFVersion ClassType;

    public:
        SWFVersion(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 9 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SWFVersion : public Class
    {
        friend class ClassTraits::SWFVersion;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SWFVersion"; }
#endif
    public:
        typedef SWFVersion SelfType;
        typedef SWFVersion ClassType;
        
    private:
        SWFVersion(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_FLASH1() const { return FLASH1; }
        UInt32 get_FLASH2() const { return FLASH2; }
        UInt32 get_FLASH3() const { return FLASH3; }
        UInt32 get_FLASH4() const { return FLASH4; }
        UInt32 get_FLASH5() const { return FLASH5; }
        UInt32 get_FLASH6() const { return FLASH6; }
        UInt32 get_FLASH7() const { return FLASH7; }
        UInt32 get_FLASH8() const { return FLASH8; }
        UInt32 get_FLASH9() const { return FLASH9; }


    protected:
        // AS3 API members.
        const UInt32 FLASH1;
        const UInt32 FLASH2;
        const UInt32 FLASH3;
        const UInt32 FLASH4;
        const UInt32 FLASH5;
        const UInt32 FLASH6;
        const UInt32 FLASH7;
        const UInt32 FLASH8;
        const UInt32 FLASH9;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

