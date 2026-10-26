//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_KeyLocation.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_KeyLocation_H
#define INC_AS3_Obj_Ui_KeyLocation_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class KeyLocation;
}

namespace InstanceTraits
{
    class KeyLocation;
}

namespace Classes
{
    class KeyLocation;
}
    
namespace ClassTraits
{
    class KeyLocation : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::KeyLocation"; }
#endif
    public:
        typedef Classes::KeyLocation ClassType;

    public:
        KeyLocation(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class KeyLocation : public Class
    {
        friend class ClassTraits::KeyLocation;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::KeyLocation"; }
#endif
    public:
        typedef KeyLocation SelfType;
        typedef KeyLocation ClassType;
        
    private:
        KeyLocation(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_LEFT() const { return LEFT; }
        UInt32 get_NUM_PAD() const { return NUM_PAD; }
        UInt32 get_RIGHT() const { return RIGHT; }
        UInt32 get_STANDARD() const { return STANDARD; }


    protected:
        // AS3 API members.
        const UInt32 LEFT;
        const UInt32 NUM_PAD;
        const UInt32 RIGHT;
        const UInt32 STANDARD;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

