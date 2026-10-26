/**************************************************************************

Filename    :   AS3_SoundObject.h
Content     :   GFx audio: AS3 sound
Created     :   March 2011
Authors     :   Vladislav Merker

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_GFX_AS3SOUNDOBJECT_H
#define INC_GFX_AS3SOUNDOBJECT_H

#include "GFxConfig.h"
#ifdef GFX_ENABLE_SOUND

#include "Kernel/SF_RefCount.h"
#include "GFx/AS3/AS3_Object.h"
#include "GFx/AS3/AS3_MovieRoot.h"
#include "GFx/GFx_PlayerImpl.h"

namespace Scaleform { namespace GFx { namespace AS3 {

namespace Instances {
    class Sound;
    class SoundChannel;
}

//////////////////////////////////////////////////////////////////////////
//

class SoundObject : public RefCountBase<SoundObject,StatMV_ActionScript_Mem>, public ASSoundIntf
{
public:
    SoundObject(ASVM& asvm, Instances::Sound* psound);
    ~SoundObject();

    void         AttachToTarget(Sprite* psprite);
    void         DetachFromTarget();
    Sprite*      GetSprite();

    void         ReleaseTarget();
    void         ExecuteOnSoundComplete();

    bool         HasPrivateOverride() { return true; }
    int          PrivateVolume()      { return GetVolume(); }
    int          PrivatePan()         { return GetPan(); }

    void         AttachResource(SoundResource* presource);
    void         LoadFile(const String& url, bool streaming = false);
    void         Play(int startTime, int loops);
    void         Stop();
    void         SetVolume(int volume);
    int          GetVolume();
    void         SetPan(int pan);
    int          GetPan();

    float        GetPosition();
    float        GetDuration();
    unsigned     GetBytesLoaded();
    unsigned     GetBytesTotal();

protected:
    int          Volume;
    int          Pan;

    AS3::Instances::Sound*  pSound;

    Ptr<Sound::SoundSample> pSample;
    Ptr<SoundResource>      pResource;
    Ptr<CharacterHandle>    pTargetHandle;
    MovieImpl*              pMovieRoot;
};

}}} // namespace Scaleform::GFx::AS3

#endif // GFX_ENABLE_SOUND

#endif // INC_GFX_AS3SOUNDOBJECT_H
