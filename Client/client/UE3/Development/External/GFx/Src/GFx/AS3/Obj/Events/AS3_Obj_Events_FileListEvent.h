//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_FileListEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_FileListEvent_H
#define INC_AS3_Obj_Events_FileListEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FileListEvent;
}

namespace InstanceTraits
{
    class FileListEvent;
}

namespace Classes
{
    class FileListEvent;
}

namespace Instances
{
    class FileListEvent : public Instances::Event
    {
        friend class InstanceTraits::FileListEvent;
        
    public:
        typedef FileListEvent SelfType;
        typedef Classes::FileListEvent ClassType;
        typedef InstanceTraits::FileListEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::FileListEvent"; }
#endif
    protected:
        FileListEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Instances::Array* get_files() const { return files; }


    protected:
        // AS3 API members.
        SPtr<Instances::Array> files;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class FileListEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::FileListEvent"; }
#endif
    public:
        FileListEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::FileListEvent> MakeInstance(Traits& t);

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
    class FileListEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FileListEvent"; }
#endif
    public:
        typedef Classes::FileListEvent ClassType;

    public:
        FileListEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class FileListEvent : public Class
    {
        friend class ClassTraits::FileListEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::FileListEvent"; }
#endif
    public:
        typedef FileListEvent SelfType;
        typedef FileListEvent ClassType;
        
    private:
        FileListEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_DIRECTORY_LISTING() const { return DIRECTORY_LISTING; }
        const char* get_SELECT_MULTIPLE() const { return SELECT_MULTIPLE; }


    protected:
        // AS3 API members.
        const char* DIRECTORY_LISTING;
        const char* SELECT_MULTIPLE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

