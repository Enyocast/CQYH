//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Filesystem_FileMode.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Filesystem_FileMode_H
#define INC_AS3_Obj_Filesystem_FileMode_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FileMode;
}

namespace InstanceTraits
{
    class FileMode;
}

namespace Classes
{
    class FileMode;
}
    
namespace ClassTraits
{
    class FileMode : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FileMode"; }
#endif
    public:
        typedef Classes::FileMode ClassType;

    public:
        FileMode(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FileMode : public Class
    {
        friend class ClassTraits::FileMode;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FileMode"; }
#endif
    public:
        typedef FileMode SelfType;
        typedef FileMode ClassType;
        
    private:
        FileMode(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_APPEND() const { return APPEND; }
        const char* get_READ() const { return READ; }
        const char* get_UPDATE() const { return UPDATE; }
        const char* get_WRITE() const { return WRITE; }


    protected:
        // AS3 API members.
        const char* APPEND;
        const char* READ;
        const char* UPDATE;
        const char* WRITE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

