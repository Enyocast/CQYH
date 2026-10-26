//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Security_SignerTrustSettings.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Security_SignerTrustSettings_H
#define INC_AS3_Obj_Security_SignerTrustSettings_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SignerTrustSettings;
}

namespace InstanceTraits
{
    class SignerTrustSettings;
}

namespace Classes
{
    class SignerTrustSettings;
}
    
namespace ClassTraits
{
    class SignerTrustSettings : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SignerTrustSettings"; }
#endif
    public:
        typedef Classes::SignerTrustSettings ClassType;

    public:
        SignerTrustSettings(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SignerTrustSettings : public Class
    {
        friend class ClassTraits::SignerTrustSettings;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SignerTrustSettings"; }
#endif
    public:
        typedef SignerTrustSettings SelfType;
        typedef SignerTrustSettings ClassType;
        
    private:
        SignerTrustSettings(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CODE_SIGNING() const { return CODE_SIGNING; }
        const char* get_PLAYLIST_SIGNING() const { return PLAYLIST_SIGNING; }
        const char* get_SIGNING() const { return SIGNING; }


    protected:
        // AS3 API members.
        const char* CODE_SIGNING;
        const char* PLAYLIST_SIGNING;
        const char* SIGNING;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

