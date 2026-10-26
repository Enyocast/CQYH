//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_IMEEventEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   (c) 2011 Scaleform Corp. All Rights Reserved.

Notes       :    

Licensees may use this file in accordance with the valid Scaleform
Commercial License Agreement provided with the software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING 
THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR ANY PURPOSE.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_IMEEventEx_H
#define INC_AS3_Obj_Gfx_IMEEventEx_H

#include "../Events/AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IMEEventEx;
}

namespace InstanceTraits
{
    class IMEEventEx;
}

namespace Classes
{
    class IMEEventEx;
}

namespace Instances
{
    class IMEEventEx : public Instances::Event
    {
        friend class InstanceTraits::IMEEventEx;
        
    public:
        typedef IMEEventEx SelfType;
        typedef Classes::IMEEventEx ClassType;
        typedef InstanceTraits::IMEEventEx TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::IMEEventEx"; }
#endif
    protected:
        IMEEventEx(InstanceTraits::Traits& t);

//##protect##"instance$methods"
	public: 
		void SetMessage(const char* messageName) { message = messageName;}
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_message() const { return message; }


    protected:
        // AS3 API members.
        ASString message;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class IMEEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::IMEEventEx"; }
#endif
    public:
        IMEEventEx(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::IMEEventEx> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class IMEEventEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IMEEventEx"; }
#endif
    public:
        typedef Classes::IMEEventEx ClassType;

    public:
        IMEEventEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class IMEEventEx : public Class
    {
        friend class ClassTraits::IMEEventEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::IMEEventEx"; }
#endif
    public:
        typedef IMEEventEx SelfType;
        typedef IMEEventEx ClassType;
        
    private:
        IMEEventEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_SET_CURRENT_INPUT_LANGUAGE() const { return SET_CURRENT_INPUT_LANGUAGE; }
        const char* get_SET_SUPPORTED_LANGUAGES() const { return SET_SUPPORTED_LANGUAGES; }
        const char* get_SET_SUPPORTED_IMENAMES() const { return SET_SUPPORTED_IMENAMES; }
        const char* get_SET_IMENAME() const { return SET_IMENAME; }
        const char* get_SET_CURRENT_LANGUAGE() const { return SET_CURRENT_LANGUAGE; }
        const char* get_REMOVE_STATUS_WINDOW() const { return REMOVE_STATUS_WINDOW; }
        const char* get_DISPLAY_STATUS_WINDOW() const { return DISPLAY_STATUS_WINDOW; }
        const char* get_SET_CONVERSION_STATUS() const { return SET_CONVERSION_STATUS; }


    protected:
        // AS3 API members.
        const char* SET_CURRENT_INPUT_LANGUAGE;
        const char* SET_SUPPORTED_LANGUAGES;
        const char* SET_SUPPORTED_IMENAMES;
        const char* SET_IMENAME;
        const char* SET_CURRENT_LANGUAGE;
        const char* REMOVE_STATUS_WINDOW;
        const char* DISPLAY_STATUS_WINDOW;
        const char* SET_CONVERSION_STATUS;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

