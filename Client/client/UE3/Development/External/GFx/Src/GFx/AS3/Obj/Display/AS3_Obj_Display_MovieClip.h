//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_MovieClip.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_MovieClip_H
#define INC_AS3_Obj_Display_MovieClip_H

#include "AS3_Obj_Display_Sprite.h"
//##protect##"includes"
#include "GFx/GFx_Sprite.h"
//#include "GFx/AS3/AS3_AvmSprite.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class Scene;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class MovieClip;
}

namespace InstanceTraits
{
    class MovieClip;
}

namespace Classes
{
    class MovieClip;
}

namespace Instances
{
    class MovieClip : public Instances::Sprite
    {
        friend class InstanceTraits::MovieClip;
        
    public:
        typedef MovieClip SelfType;
        typedef Classes::MovieClip ClassType;
        typedef InstanceTraits::MovieClip TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::MovieClip"; }
#endif
    protected:
        MovieClip(InstanceTraits::Traits& t);

//##protect##"instance$methods"
       virtual void         ForEachChild_GC(Collector* prcc, GcOp op) const;
       
       SPtr<Instances::Scene>           CreateFakeScene();
       const MovieDataDef::SceneInfo*   GetSceneInfo(unsigned frameNumber) const;
       const MovieDataDef::SceneInfo*   GetSceneInfoByName(const ASString& name) const;
       bool                 GetLabeledFrame(GFx::Sprite* spr, const Value& frame, const Value& scene, unsigned* targetFrame);

    public:
        virtual bool        HasFrameScript() const;
        virtual bool        GetFrameScript(unsigned frame, Value* pmethod);
        virtual bool        IsMovieClip() const { return true; }

//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_currentFrameGet, 
            mid_currentFrameLabelGet, 
            mid_currentLabelGet, 
            mid_currentLabelsGet, 
            mid_currentSceneGet, 
            mid_enabledGet, 
            mid_enabledSet, 
            mid_framesLoadedGet, 
            mid_scenesGet, 
            mid_totalFramesGet, 
            mid_trackAsMenuGet, 
            mid_trackAsMenuSet, 
            mid_addFrameScript, 
            mid_gotoAndPlay, 
            mid_gotoAndStop, 
            mid_nextFrame, 
            mid_nextScene, 
            mid_play, 
            mid_prevFrame, 
            mid_prevScene, 
            mid_stop, 
        };
        void currentFrameGet(SInt32& result);
        void currentFrameLabelGet(Value& result);
        void currentLabelGet(Value& result);
        void currentLabelsGet(Value& result);
        void currentSceneGet(Value& result);
        void enabledGet(bool& result);
        void enabledSet(Value& result, bool value);
        void framesLoadedGet(SInt32& result);
        void scenesGet(Value& result);
        void totalFramesGet(SInt32& result);
        void trackAsMenuGet(bool& result);
        void trackAsMenuSet(Value& result, bool value);
        void addFrameScript(Value& result, unsigned argc, const Value* const argv);
        void gotoAndPlay(Value& result, const Value& frame, const Value& scene);
        void gotoAndStop(Value& result, const Value& frame, const Value& scene);
        void nextFrame(Value& result);
        void nextScene(Value& result);
        void play(Value& result);
        void prevFrame(Value& result);
        void prevScene(Value& result);
        void stop(Value& result);

//##protect##"instance$data"
        // This class contains associations of frame numbers with corresponding
        // ActionScript method to be called when appropriate frame is executed.
        // Contains a sorted by frame number array of descriptors along with
        // a bitset that indicates presence of action at the corresponding frame
        // (for quick check, before going to do sorted array search).
        class FrameScript
        {
        public:
            struct Descr
            {
                Value    Method;
                unsigned Frame;  // number of frame

                Descr():Frame(0) {}
                Descr(unsigned f, const Value& frMethod):Method(frMethod), Frame(f) {}
                Descr(const Descr& o): Method(o.Method), Frame(o.Frame) {}

                bool operator < (const Descr& f) const { return Frame < f.Frame; }
            };
        private:
            UByte*  pData;
            UInt16  DescrCnt; // number of Descr elements
            UInt16  FrameCnt; // total number of frames (pData[DescrCnt - 1].Number + 1))

            Descr*  GetDescs() const                        { return reinterpret_cast<Descr*>(pData + 4*((FrameCnt + 31)/32)); }
            UPInt   GetDescSize(unsigned newDescrCnt) const { return sizeof(Descr) * newDescrCnt + 4*((FrameCnt + 31)/32); }
        public:
            FrameScript() : pData(NULL), DescrCnt(0), FrameCnt(0) {}
            ~FrameScript();

            // initial setup
            void Set(MemoryHeap* pheap, unsigned totalFrames, unsigned cnt, const Descr*);

            // gets descr by frame number. Frame number is 0-based
            const Descr* Get(unsigned frameNum);

            // Release all records. Necessary to do before AVM shutdown.
            void Clear();

            bool IsEmpty() const { return DescrCnt == 0; }

            void ForEachChild_GC(Collector* prcc, GcOp op
                                 SF_DEBUG_ARG(const MovieClip& owner)) const;
        };

        FrameScript mFrameScript;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class MovieClip : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::MovieClip"; }
#endif
    public:
        MovieClip(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::MovieClip> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 21 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class MovieClip : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::MovieClip"; }
#endif
    public:
        typedef Classes::MovieClip ClassType;

    public:
        MovieClip(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

