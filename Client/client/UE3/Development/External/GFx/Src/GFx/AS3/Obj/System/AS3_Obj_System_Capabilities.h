//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_System_Capabilities.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_System_Capabilities_H
#define INC_AS3_Obj_System_Capabilities_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Capabilities;
}

namespace InstanceTraits
{
    class Capabilities;
}

namespace Classes
{
    class Capabilities;
}
    
namespace ClassTraits
{
    class Capabilities : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Capabilities"; }
#endif
    public:
        typedef Classes::Capabilities ClassType;

    public:
        Capabilities(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 27 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Capabilities : public Class
    {
        friend class ClassTraits::Capabilities;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Capabilities"; }
#endif
    public:
        typedef Capabilities SelfType;
        typedef Capabilities ClassType;
        
    private:
        Capabilities(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"

        void getOSName(ASString& result);

//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_avHardwareDisableGet, 
            mid_hasAccessibilityGet, 
            mid_hasAudioGet, 
            mid_hasAudioEncoderGet, 
            mid_hasEmbeddedVideoGet, 
            mid_hasIMEGet, 
            mid_hasMP3Get, 
            mid_hasPrintingGet, 
            mid_hasScreenBroadcastGet, 
            mid_hasScreenPlaybackGet, 
            mid_hasStreamingAudioGet, 
            mid_hasStreamingVideoGet, 
            mid_hasTLSGet, 
            mid_hasVideoEncoderGet, 
            mid_isDebuggerGet, 
            mid_languageGet, 
            mid_localFileReadDisableGet, 
            mid_manufacturerGet, 
            mid_osGet, 
            mid_pixelAspectRatioGet, 
            mid_playerTypeGet, 
            mid_screenColorGet, 
            mid_screenDPIGet, 
            mid_screenResolutionXGet, 
            mid_screenResolutionYGet, 
            mid_serverStringGet, 
            mid_versionGet, 
        };
        void avHardwareDisableGet(bool& result);
        void hasAccessibilityGet(bool& result);
        void hasAudioGet(bool& result);
        void hasAudioEncoderGet(bool& result);
        void hasEmbeddedVideoGet(bool& result);
        void hasIMEGet(bool& result);
        void hasMP3Get(bool& result);
        void hasPrintingGet(bool& result);
        void hasScreenBroadcastGet(bool& result);
        void hasScreenPlaybackGet(bool& result);
        void hasStreamingAudioGet(bool& result);
        void hasStreamingVideoGet(bool& result);
        void hasTLSGet(bool& result);
        void hasVideoEncoderGet(bool& result);
        void isDebuggerGet(bool& result);
        void languageGet(ASString& result);
        void localFileReadDisableGet(bool& result);
        void manufacturerGet(ASString& result);
        void osGet(ASString& result);
        void pixelAspectRatioGet(Value::Number& result);
        void playerTypeGet(ASString& result);
        void screenColorGet(ASString& result);
        void screenDPIGet(Value::Number& result);
        void screenResolutionXGet(Value::Number& result);
        void screenResolutionYGet(Value::Number& result);
        void serverStringGet(ASString& result);
        void versionGet(ASString& result);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

