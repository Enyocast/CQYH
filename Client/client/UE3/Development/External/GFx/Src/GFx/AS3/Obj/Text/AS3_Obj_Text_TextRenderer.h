//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextRenderer.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextRenderer_H
#define INC_AS3_Obj_Text_TextRenderer_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextRenderer;
}

namespace InstanceTraits
{
    class TextRenderer;
}

namespace Classes
{
    class TextRenderer;
}
    
namespace ClassTraits
{
    class TextRenderer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextRenderer"; }
#endif
    public:
        typedef Classes::TextRenderer ClassType;

    public:
        TextRenderer(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextRenderer : public Class
    {
        friend class ClassTraits::TextRenderer;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextRenderer"; }
#endif
    public:
        typedef TextRenderer SelfType;
        typedef TextRenderer ClassType;
        
    private:
        TextRenderer(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

