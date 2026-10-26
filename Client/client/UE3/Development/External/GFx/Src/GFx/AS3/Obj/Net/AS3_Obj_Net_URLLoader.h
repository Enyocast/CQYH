//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_URLLoader.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_URLLoader_H
#define INC_AS3_Obj_Net_URLLoader_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class URLRequest;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class URLLoader;
}

namespace InstanceTraits
{
    class URLLoader;
}

namespace Classes
{
    class URLLoader;
}

namespace Instances
{
    class URLLoader : public Instances::EventDispatcher
    {
        friend class InstanceTraits::URLLoader;
        
    public:
        typedef URLLoader SelfType;
        typedef Classes::URLLoader ClassType;
        typedef InstanceTraits::URLLoader TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::URLLoader"; }
#endif
    protected:
        URLLoader(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        void ExecuteOpenEvent();
        void ExecuteProgressEvent(UInt32 bytesLoaded, UInt32 totalBytes);
        void ExecuteCompleteEvent();
        void ExecuteErrorEvent(const char* errorStr);
        bool IsLoadingVariables() const;
        bool IsLoadingText() const;
        bool IsLoadingBinary() const;
        void SetVariablesDataString(const char* pdata);
        void SetTextString(const char* pdata);
        void SetBinaryData(const ArrayPOD<UByte>& binaryData);
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        UInt32 get_bytesLoaded() const { return bytesLoaded; }
        UInt32 get_bytesTotal() const { return bytesTotal; }
        const Value& get_data() const { return data; }
        const ASString& get_dataFormat() const { return dataFormat; }

        // AS3 API methods.
        enum MethodID {
            mid_addEventListener, 
            mid_close, 
            mid_load, 
        };
        void addEventListener(Value& result, const ASString& type, const Value& listener, bool useCapture, SInt32 priority, bool useWeakReference);
        void close(Value& result);
        void load(Value& result, Instances::URLRequest* request);

    protected:
        // AS3 API members.
        UInt32 bytesLoaded;
        UInt32 bytesTotal;
        Value data;
        ASString dataFormat;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class URLLoader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::URLLoader"; }
#endif
    public:
        URLLoader(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::URLLoader> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 4 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class URLLoader : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::URLLoader"; }
#endif
    public:
        typedef Classes::URLLoader ClassType;

    public:
        URLLoader(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

