//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_ID3Info.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_ID3Info_H
#define INC_AS3_Obj_Media_ID3Info_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ID3Info;
}

namespace InstanceTraits
{
    class ID3Info;
}

namespace Classes
{
    class ID3Info;
}

namespace Instances
{
    class ID3Info : public Instances::Object
    {
        friend class InstanceTraits::ID3Info;
        
    public:
        typedef ID3Info SelfType;
        typedef Classes::ID3Info ClassType;
        typedef InstanceTraits::ID3Info TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ID3Info"; }
#endif
    protected:
        ID3Info(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_album() const { return album; }
        const ASString& get_artist() const { return artist; }
        const ASString& get_comment() const { return comment; }
        const ASString& get_genre() const { return genre; }
        const ASString& get_songName() const { return songName; }
        const ASString& get_track() const { return track; }
        const ASString& get_year() const { return year; }


    protected:
        // AS3 API members.
        ASString album;
        ASString artist;
        ASString comment;
        ASString genre;
        ASString songName;
        ASString track;
        ASString year;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ID3Info : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ID3Info"; }
#endif
    public:
        ID3Info(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ID3Info> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 7 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ID3Info : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ID3Info"; }
#endif
    public:
        typedef Classes::ID3Info ClassType;

    public:
        ID3Info(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

