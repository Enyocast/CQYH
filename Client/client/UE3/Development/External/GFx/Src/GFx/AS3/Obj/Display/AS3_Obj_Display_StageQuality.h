//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_StageQuality.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_StageQuality_H
#define INC_AS3_Obj_Display_StageQuality_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StageQuality;
}

namespace InstanceTraits
{
    class StageQuality;
}

namespace Classes
{
    class StageQuality;
}
    
namespace ClassTraits
{
    class StageQuality : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageQuality"; }
#endif
    public:
        typedef Classes::StageQuality ClassType;

    public:
        StageQuality(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StageQuality : public Class
    {
        friend class ClassTraits::StageQuality;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageQuality"; }
#endif
    public:
        typedef StageQuality SelfType;
        typedef StageQuality ClassType;
        
    private:
        StageQuality(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_BEST() const { return BEST; }
        const char* get_HIGH() const { return HIGH; }
        const char* get_LOW() const { return LOW; }
        const char* get_MEDIUM() const { return MEDIUM; }


    protected:
        // AS3 API members.
        const char* BEST;
        const char* HIGH;
        const char* LOW;
        const char* MEDIUM;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

