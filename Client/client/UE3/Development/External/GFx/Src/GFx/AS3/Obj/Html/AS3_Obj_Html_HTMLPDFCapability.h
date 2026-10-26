//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Html_HTMLPDFCapability.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Html_HTMLPDFCapability_H
#define INC_AS3_Obj_Html_HTMLPDFCapability_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class HTMLPDFCapability;
}

namespace InstanceTraits
{
    class HTMLPDFCapability;
}

namespace Classes
{
    class HTMLPDFCapability;
}
    
namespace ClassTraits
{
    class HTMLPDFCapability : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::HTMLPDFCapability"; }
#endif
    public:
        typedef Classes::HTMLPDFCapability ClassType;

    public:
        HTMLPDFCapability(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 5 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class HTMLPDFCapability : public Class
    {
        friend class ClassTraits::HTMLPDFCapability;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::HTMLPDFCapability"; }
#endif
    public:
        typedef HTMLPDFCapability SelfType;
        typedef HTMLPDFCapability ClassType;
        
    private:
        HTMLPDFCapability(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        SInt32 get_ERROR_CANNOT_LOAD_READER() const { return ERROR_CANNOT_LOAD_READER; }
        SInt32 get_ERROR_INSTALLED_READER_NOT_FOUND() const { return ERROR_INSTALLED_READER_NOT_FOUND; }
        SInt32 get_ERROR_INSTALLED_READER_TOO_OLD() const { return ERROR_INSTALLED_READER_TOO_OLD; }
        SInt32 get_ERROR_PREFERRED_READER_TOO_OLD() const { return ERROR_PREFERRED_READER_TOO_OLD; }
        SInt32 get_STATUS_OK() const { return STATUS_OK; }


    protected:
        // AS3 API members.
        const SInt32 ERROR_CANNOT_LOAD_READER;
        const SInt32 ERROR_INSTALLED_READER_NOT_FOUND;
        const SInt32 ERROR_INSTALLED_READER_TOO_OLD;
        const SInt32 ERROR_PREFERRED_READER_TOO_OLD;
        const SInt32 STATUS_OK;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

