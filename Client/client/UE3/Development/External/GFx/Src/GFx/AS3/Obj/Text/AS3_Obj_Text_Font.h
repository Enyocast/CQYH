//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_Font.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_Font_H
#define INC_AS3_Obj_Text_Font_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_FontResource.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Font;
}

namespace InstanceTraits
{
    class Font;
}

namespace Classes
{
    class Font;
}

namespace Instances
{
    class Font : public Instances::Object
    {
        friend class InstanceTraits::Font;
        
    public:
        typedef Font SelfType;
        typedef Classes::Font ClassType;
        typedef InstanceTraits::Font TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Font"; }
#endif
    protected:
        Font(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        friend class Classes::Font;

        virtual void InitInstance(bool extCall);
        virtual bool CreateLibraryObject();
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_fontNameGet, 
            mid_fontStyleGet, 
            mid_fontTypeGet, 
            mid_hasGlyphs, 
        };
        void fontNameGet(Value& result);
        void fontStyleGet(Value& result);
        void fontTypeGet(Value& result);
        void hasGlyphs(bool& result, const ASString& str);

//##protect##"instance$data"
    protected:
        Ptr<Render::Font>       pFont;

        // the following members will be used only if pFont is NULL
        ASString fontName, fontStyle, fontType;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Font : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Font"; }
#endif
    public:
        Font(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Font> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Font : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Font"; }
#endif
    public:
        typedef Classes::Font ClassType;

    public:
        Font(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Font : public Class
    {
        friend class ClassTraits::Font;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Font"; }
#endif
    public:
        typedef Font SelfType;
        typedef Font ClassType;
        
    private:
        Font(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_enumerateFonts, 
            mid_registerFont, 
        };
        void enumerateFonts(Value& result, bool enumerateDeviceFonts);
        void registerFont(Value& result, Class* font);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

