//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_BlendMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_BlendMode_H
#define INC_AS3_Obj_Display_BlendMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef DIFFERENCE
#undef DIFFERENCE
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class BlendMode;
}

namespace InstanceTraits
{
    class BlendMode;
}

namespace Classes
{
    class BlendMode;
}
    
namespace ClassTraits
{
    class BlendMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::BlendMode"; }
#endif
    public:
        typedef Classes::BlendMode ClassType;

    public:
        BlendMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 14 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class BlendMode : public Class
    {
        friend class ClassTraits::BlendMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::BlendMode"; }
#endif
    public:
        typedef BlendMode SelfType;
        typedef BlendMode ClassType;
        
    private:
        BlendMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ADD() const { return ADD; }
        const char* get_ALPHA() const { return ALPHA; }
        const char* get_DARKEN() const { return DARKEN; }
        const char* get_DIFFERENCE() const { return DIFFERENCE; }
        const char* get_ERASE() const { return ERASE; }
        const char* get_HARDLIGHT() const { return HARDLIGHT; }
        const char* get_INVERT() const { return INVERT; }
        const char* get_LAYER() const { return LAYER; }
        const char* get_LIGHTEN() const { return LIGHTEN; }
        const char* get_MULTIPLY() const { return MULTIPLY; }
        const char* get_NORMAL() const { return NORMAL; }
        const char* get_OVERLAY() const { return OVERLAY; }
        const char* get_SCREEN() const { return SCREEN; }
        const char* get_SUBTRACT() const { return SUBTRACT; }


    protected:
        // AS3 API members.
        const char* ADD;
        const char* ALPHA;
        const char* DARKEN;
        const char* DIFFERENCE;
        const char* ERASE;
        const char* HARDLIGHT;
        const char* INVERT;
        const char* LAYER;
        const char* LIGHTEN;
        const char* MULTIPLY;
        const char* NORMAL;
        const char* OVERLAY;
        const char* SCREEN;
        const char* SUBTRACT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

