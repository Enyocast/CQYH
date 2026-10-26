//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filters_BitmapFilterType.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filters_BitmapFilterType_H
#define INC_AS3_Obj_Filters_BitmapFilterType_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BitmapFilterType;
}

namespace InstanceTraits
{
    class BitmapFilterType;
}

namespace Classes
{
    class BitmapFilterType;
}
    
namespace ClassTraits
{
    class BitmapFilterType : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BitmapFilterType"; }
#endif
    public:
        typedef Classes::BitmapFilterType ClassType;

    public:
        BitmapFilterType(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class BitmapFilterType : public Class
    {
        friend class ClassTraits::BitmapFilterType;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::BitmapFilterType"; }
#endif
    public:
        typedef BitmapFilterType SelfType;
        typedef BitmapFilterType ClassType;
        
    private:
        BitmapFilterType(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_FULL() const { return FULL; }
        const char* get_INNER() const { return INNER; }
        const char* get_OUTER() const { return OUTER; }


    protected:
        // AS3 API members.
        const char* FULL;
        const char* INNER;
        const char* OUTER;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

