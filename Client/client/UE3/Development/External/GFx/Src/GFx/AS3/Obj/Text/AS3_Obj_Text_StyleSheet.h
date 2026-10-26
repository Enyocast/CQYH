//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_StyleSheet.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_StyleSheet_H
#define INC_AS3_Obj_Text_StyleSheet_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "GFx/Text/Text_StyleSheet.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances 
{
    class TextFormat;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StyleSheet;
}

namespace InstanceTraits
{
    class StyleSheet;
}

namespace Classes
{
    class StyleSheet;
}

namespace Instances
{
    class StyleSheet : public Instances::EventDispatcher
    {
        friend class InstanceTraits::StyleSheet;
        
    public:
        typedef StyleSheet SelfType;
        typedef Classes::StyleSheet ClassType;
        typedef InstanceTraits::StyleSheet TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::StyleSheet"; }
#endif
    protected:
        StyleSheet(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_styleNamesGet, 
            mid_clear, 
            mid_getStyle, 
            mid_parseCSS, 
            mid_setStyle, 
            mid_transform, 
        };
        void styleNamesGet(Value& result);
        void clear(Value& result);
        void getStyle(Value& result, const ASString& styleName);
        void parseCSS(Value& result, const ASString& CSSText);
        void setStyle(Value& result, const ASString& styleName, const Value& styleObject);
        void transform(Value& result, const Value& formatObject);

//##protect##"instance$data"

#ifdef GFX_ENABLE_CSS
        Text::StyleManager* GetTextStyleManager() { return &CSS; }

    protected:
        Text::StyleManager   CSS;
#endif

//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class StyleSheet : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::StyleSheet"; }
#endif
    public:
        StyleSheet(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::StyleSheet> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class StyleSheet : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StyleSheet"; }
#endif
    public:
        typedef Classes::StyleSheet ClassType;

    public:
        StyleSheet(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

