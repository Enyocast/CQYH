//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilterQuality.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_BitmapFilterQuality_H
#define INC_AS3_Obj_Filters_BitmapFilterQuality_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BitmapFilterQuality;
}

namespace InstanceTraits
{
    class BitmapFilterQuality;
}

namespace Classes
{
    class BitmapFilterQuality;
}
    
namespace ClassTraits
{
    class BitmapFilterQuality : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BitmapFilterQuality"; }
#endif
    public:
        typedef Classes::BitmapFilterQuality ClassType;

    public:
        BitmapFilterQuality(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class BitmapFilterQuality : public Class
    {
        friend class ClassTraits::BitmapFilterQuality;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::BitmapFilterQuality"; }
#endif
    public:
        typedef BitmapFilterQuality SelfType;
        typedef BitmapFilterQuality ClassType;
        
    private:
        BitmapFilterQuality(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        SInt32 get_HIGH() const { return HIGH; }
        SInt32 get_LOW() const { return LOW; }
        SInt32 get_MEDIUM() const { return MEDIUM; }


    protected:
        // AS3 API members.
        const SInt32 HIGH;
        const SInt32 LOW;
        const SInt32 MEDIUM;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

