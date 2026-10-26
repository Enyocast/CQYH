//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BitmapDataChannel.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_BitmapDataChannel_H
#define INC_AS3_Obj_Display_BitmapDataChannel_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BitmapDataChannel;
}

namespace InstanceTraits
{
    class BitmapDataChannel;
}

namespace Classes
{
    class BitmapDataChannel;
}
    
namespace ClassTraits
{
    class BitmapDataChannel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BitmapDataChannel"; }
#endif
    public:
        typedef Classes::BitmapDataChannel ClassType;

    public:
        BitmapDataChannel(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class BitmapDataChannel : public Class
    {
        friend class ClassTraits::BitmapDataChannel;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::BitmapDataChannel"; }
#endif
    public:
        typedef BitmapDataChannel SelfType;
        typedef BitmapDataChannel ClassType;
        
    private:
        BitmapDataChannel(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_ALPHA() const { return ALPHA; }
        UInt32 get_BLUE() const { return BLUE; }
        UInt32 get_GREEN() const { return GREEN; }
        UInt32 get_RED() const { return RED; }


    protected:
        // AS3 API members.
        const UInt32 ALPHA;
        const UInt32 BLUE;
        const UInt32 GREEN;
        const UInt32 RED;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

