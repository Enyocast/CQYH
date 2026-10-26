//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Display_FrameLabel.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Display_FrameLabel_H
#define INC_AS3_Obj_Display_FrameLabel_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_MovieDef.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class FrameLabel;
}

namespace InstanceTraits
{
    class FrameLabel;
}

namespace Classes
{
    class FrameLabel;
}

namespace Instances
{
    class FrameLabel : public Instances::Object
    {
        friend class InstanceTraits::FrameLabel;
        
    public:
        typedef FrameLabel SelfType;
        typedef Classes::FrameLabel ClassType;
        typedef InstanceTraits::FrameLabel TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::FrameLabel"; }
#endif
    protected:
        FrameLabel(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void Set(UInt32 sceneOff, const MovieDataDef::FrameLabelInfo* frameLabelInfo)
        {
            FrameNumber = frameLabelInfo->Number + 1 - sceneOff; // 1-based
            FrameName   = frameLabelInfo->Name;
        }
        void Set(UInt32 frameNum, const ASString& frameName)
        {
            FrameNumber = frameNum;
            FrameName   = frameName;
        }
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_frameGet, 
            mid_nameGet, 
        };
        void frameGet(SInt32& result);
        void nameGet(ASString& result);

//##protect##"instance$data"
        UInt32                              FrameNumber;
        ASString                            FrameName;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class FrameLabel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::FrameLabel"; }
#endif
    public:
        FrameLabel(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::FrameLabel> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class FrameLabel : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::FrameLabel"; }
#endif
    public:
        typedef Classes::FrameLabel ClassType;

    public:
        FrameLabel(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

