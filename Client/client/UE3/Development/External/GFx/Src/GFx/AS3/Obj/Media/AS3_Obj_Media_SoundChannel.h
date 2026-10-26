//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundChannel.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_SoundChannel_H
#define INC_AS3_Obj_Media_SoundChannel_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "GFx/AS3/Audio/AS3_SoundObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class SoundTransform;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SoundChannel;
}

namespace InstanceTraits
{
    class SoundChannel;
}

namespace Classes
{
    class SoundChannel;
}

namespace Instances
{
    class SoundChannel : public Instances::EventDispatcher
    {
        friend class InstanceTraits::SoundChannel;
        
    public:
        typedef SoundChannel SelfType;
        typedef Classes::SoundChannel ClassType;
        typedef InstanceTraits::SoundChannel TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SoundChannel"; }
#endif
    protected:
        SoundChannel(InstanceTraits::Traits& t);

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
    public:
        void DispatchEventSoundComplete();
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_leftPeakGet, 
            mid_positionGet, 
            mid_rightPeakGet, 
            mid_soundTransformGet, 
            mid_soundTransformSet, 
            mid_stop, 
        };
        void leftPeakGet(Value::Number& result);
        void positionGet(Value::Number& result);
        void rightPeakGet(Value::Number& result);
        void soundTransformGet(Value& result);
        void soundTransformSet(Value& result, Instances::SoundTransform* value);
        void stop(Value& result);

//##protect##"instance$data"
#ifdef GFX_ENABLE_SOUND
        Ptr<SoundObject> pSoundObject;
#endif
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SoundChannel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SoundChannel"; }
#endif
    public:
        SoundChannel(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SoundChannel> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 6 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class SoundChannel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SoundChannel"; }
#endif
    public:
        typedef Classes::SoundChannel ClassType;

    public:
        SoundChannel(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

