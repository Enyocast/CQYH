//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_Sound.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_Sound_H
#define INC_AS3_Obj_Media_Sound_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "GFx/AS3/Audio/AS3_SoundObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class ID3Info;
    class URLRequest;
    class SoundChannel;
    class SoundLoaderContext;
    class SoundTransform;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Sound;
}

namespace InstanceTraits
{
    class Sound;
}

namespace Classes
{
    class Sound;
}

namespace Instances
{
    class Sound : public Instances::EventDispatcher
    {
        friend class InstanceTraits::Sound;
        
    public:
        typedef Sound SelfType;
        typedef Classes::Sound ClassType;
        typedef InstanceTraits::Sound TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Sound"; }
#endif
    protected:
        Sound(InstanceTraits::Traits& t);

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void InitInstance(bool extCall);
        bool CreateLibraryObject();
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

    public:
        void DispatchEventOpen();
        void DispatchEventComplete();
        void DispatchEventSoundComplete();
        void DispatchEventIOError();
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bytesLoadedGet, 
            mid_bytesTotalGet, 
            mid_id3Get, 
            mid_isBufferingGet, 
            mid_lengthGet, 
            mid_urlGet, 
            mid_close, 
            mid_load, 
            mid_play, 
        };
        void bytesLoadedGet(UInt32& result);
        void bytesTotalGet(SInt32& result);
        void id3Get(Value& result);
        void isBufferingGet(bool& result);
        void lengthGet(Value::Number& result);
        void urlGet(ASString& result);
        void close(Value& result);
        void load(Value& result, Instances::URLRequest* stream, Instances::SoundLoaderContext* context);
        void play(Value& result, Value::Number startTime, SInt32 loops, Instances::SoundTransform* sndTransform);

//##protect##"instance$data"
#ifdef GFX_ENABLE_SOUND
        Ptr<SoundObject>   pSoundObject;
        Ptr<SoundResource> pSoundResource;
        String             SoundURL;
        bool               Streaming;
        SPtr<Instances::SoundChannel> pChannel;
#endif
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Sound : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Sound"; }
#endif
    public:
        Sound(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Sound> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 9 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Sound : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Sound"; }
#endif
    public:
        typedef Classes::Sound ClassType;

    public:
        Sound(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

