//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_TextFieldEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_TextFieldEx_H
#define INC_AS3_Obj_Gfx_TextFieldEx_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "../Text/AS3_Obj_Text_TextField.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextFieldEx;
}

namespace InstanceTraits
{
    class TextFieldEx;
}

namespace Classes
{
    class TextFieldEx;
}
    
namespace ClassTraits
{
    class TextFieldEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextFieldEx"; }
#endif
    public:
        typedef Classes::TextFieldEx ClassType;

    public:
        TextFieldEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 7 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class TextFieldEx : public Class
    {
        friend class ClassTraits::TextFieldEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::TextFieldEx"; }
#endif
    public:
        typedef TextFieldEx SelfType;
        typedef TextFieldEx ClassType;
        
    private:
        TextFieldEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_VALIGN_NONE() const { return VALIGN_NONE; }
        const char* get_VALIGN_TOP() const { return VALIGN_TOP; }
        const char* get_VALIGN_CENTER() const { return VALIGN_CENTER; }
        const char* get_VALIGN_BOTTOM() const { return VALIGN_BOTTOM; }
        const char* get_TEXTAUTOSZ_NONE() const { return TEXTAUTOSZ_NONE; }
        const char* get_TEXTAUTOSZ_SHRINK() const { return TEXTAUTOSZ_SHRINK; }
        const char* get_TEXTAUTOSZ_FIT() const { return TEXTAUTOSZ_FIT; }

        // AS3 API methods.
        enum MethodID {
            mid_appendHtml, 
            mid_setVerticalAlign, 
            mid_getVerticalAlign, 
            mid_setTextAutoSize, 
            mid_getTextAutoSize, 
            mid_setIMEEnabled, 
        };
        void appendHtml(Value& result, Instances::TextField* textField, const ASString& newHtml);
        void setVerticalAlign(Value& result, Instances::TextField* textField, const ASString& valign);
        void getVerticalAlign(ASString& result, Instances::TextField* textField);
        void setTextAutoSize(Value& result, Instances::TextField* textField, const ASString& autoSz);
        void getTextAutoSize(ASString& result, Instances::TextField* textField);
        void setIMEEnabled(Value& result, Instances::TextField* textField, bool isEnabled);

    protected:
        // AS3 API members.
        const char* VALIGN_NONE;
        const char* VALIGN_TOP;
        const char* VALIGN_CENTER;
        const char* VALIGN_BOTTOM;
        const char* TEXTAUTOSZ_NONE;
        const char* TEXTAUTOSZ_SHRINK;
        const char* TEXTAUTOSZ_FIT;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

