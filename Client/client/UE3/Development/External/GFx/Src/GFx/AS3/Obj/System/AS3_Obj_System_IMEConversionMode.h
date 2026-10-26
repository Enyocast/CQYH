//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_IMEConversionMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_IMEConversionMode_H
#define INC_AS3_Obj_System_IMEConversionMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IMEConversionMode;
}

namespace InstanceTraits
{
    class IMEConversionMode;
}

namespace Classes
{
    class IMEConversionMode;
}
    
namespace ClassTraits
{
    class IMEConversionMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IMEConversionMode"; }
#endif
    public:
        typedef Classes::IMEConversionMode ClassType;

    public:
        IMEConversionMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IMEConversionMode : public Class
    {
        friend class ClassTraits::IMEConversionMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IMEConversionMode"; }
#endif
    public:
        typedef IMEConversionMode SelfType;
        typedef IMEConversionMode ClassType;
        
    private:
        IMEConversionMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ALPHANUMERIC_FULL() const { return ALPHANUMERIC_FULL; }
        const char* get_ALPHANUMERIC_HALF() const { return ALPHANUMERIC_HALF; }
        const char* get_CHINESE() const { return CHINESE; }
        const char* get_JAPANESE_HIRAGANA() const { return JAPANESE_HIRAGANA; }
        const char* get_JAPANESE_KATAKANA_FULL() const { return JAPANESE_KATAKANA_FULL; }
        const char* get_JAPANESE_KATAKANA_HALF() const { return JAPANESE_KATAKANA_HALF; }
        const char* get_KOREAN() const { return KOREAN; }
        const char* get_UNKNOWN() const { return UNKNOWN; }


    protected:
        // AS3 API members.
        const char* ALPHANUMERIC_FULL;
        const char* ALPHANUMERIC_HALF;
        const char* CHINESE;
        const char* JAPANESE_HIRAGANA;
        const char* JAPANESE_KATAKANA_FULL;
        const char* JAPANESE_KATAKANA_HALF;
        const char* KOREAN;
        const char* UNKNOWN;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

