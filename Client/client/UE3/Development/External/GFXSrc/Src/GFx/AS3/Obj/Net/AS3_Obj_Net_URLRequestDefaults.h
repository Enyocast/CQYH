//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLRequestDefaults.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLRequestDefaults_H
#define INC_AS3_Obj_Net_URLRequestDefaults_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLRequestDefaults;
}

namespace InstanceTraits
{
    class URLRequestDefaults;
}

namespace Classes
{
    class URLRequestDefaults;
}
    
namespace ClassTraits
{
    class URLRequestDefaults : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLRequestDefaults"; }
#endif
    public:
        typedef Classes::URLRequestDefaults ClassType;

    public:
        URLRequestDefaults(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class URLRequestDefaults : public Class
    {
        friend class ClassTraits::URLRequestDefaults;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::URLRequestDefaults"; }
#endif
    public:
        typedef URLRequestDefaults SelfType;
        typedef URLRequestDefaults ClassType;
        
    private:
        URLRequestDefaults(ClassTraits::Traits& t);
       
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

