//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_StaticText.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_StaticText_H
#define INC_AS3_Obj_Text_StaticText_H

#include "../Display/AS3_Obj_Display_DisplayObject.h"
//##protect##"includes"
#include "GFx/GFx_StaticText.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StaticText;
}

namespace InstanceTraits
{
    class StaticText;
}

namespace Classes
{
    class StaticText;
}

namespace Instances
{
    class StaticText : public Instances::DisplayObject
    {
        friend class InstanceTraits::StaticText;
        
    public:
        typedef StaticText SelfType;
        typedef Classes::StaticText ClassType;
        typedef InstanceTraits::StaticText TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::StaticText"; }
#endif
    protected:
        StaticText(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        GFx::StaticTextCharacter* GetStaticTextChar() const 
        { 
            SF_ASSERT(pDispObj && pDispObj->GetType() == CharacterDef::StaticText);
            return static_cast<GFx::StaticTextCharacter*>(pDispObj.GetPtr()); 
        }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_textGet, 
        };
        void textGet(ASString& result);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class StaticText : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::StaticText"; }
#endif
    public:
        StaticText(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::StaticText> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class StaticText : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StaticText"; }
#endif
    public:
        typedef Classes::StaticText ClassType;

    public:
        StaticText(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

