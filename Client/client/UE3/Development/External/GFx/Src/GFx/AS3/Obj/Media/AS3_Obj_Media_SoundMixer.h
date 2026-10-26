//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundMixer.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_SoundMixer_H
#define INC_AS3_Obj_Media_SoundMixer_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class ByteArray;
    class SoundTransform;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SoundMixer;
}

namespace InstanceTraits
{
    class SoundMixer;
}

namespace Classes
{
    class SoundMixer;
}
    
namespace ClassTraits
{
    class SoundMixer : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SoundMixer"; }
#endif
    public:
        typedef Classes::SoundMixer ClassType;

    public:
        SoundMixer(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SoundMixer : public Class
    {
        friend class ClassTraits::SoundMixer;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SoundMixer"; }
#endif
    public:
        typedef SoundMixer SelfType;
        typedef SoundMixer ClassType;
        
    private:
        SoundMixer(ClassTraits::Traits& t);
       
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

