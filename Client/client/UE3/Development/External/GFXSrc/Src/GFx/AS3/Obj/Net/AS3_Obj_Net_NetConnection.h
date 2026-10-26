//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_NetConnection.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_NetConnection_H
#define INC_AS3_Obj_Net_NetConnection_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class NetConnection;
}

namespace InstanceTraits
{
    class NetConnection;
}

namespace Classes
{
    class NetConnection;
}

namespace Instances
{
    class NetConnection : public Instances::EventDispatcher
    {
        friend class InstanceTraits::NetConnection;
        
    public:
        typedef NetConnection SelfType;
        typedef Classes::NetConnection ClassType;
        typedef InstanceTraits::NetConnection TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::NetConnection"; }
#endif
    protected:
        NetConnection(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_clientGet, 
            mid_clientSet, 
            mid_connectedGet, 
            mid_connectedProxyTypeGet, 
            mid_defaultObjectEncodingSet, 
            mid_objectEncodingGet, 
            mid_objectEncodingSet, 
            mid_proxyTypeGet, 
            mid_proxyTypeSet, 
            mid_uriGet, 
            mid_usingTLSGet, 
            mid_addHeader, 
            mid_call, 
            mid_close, 
            mid_connect, 
        };
        void clientGet(Value& result);
        void clientSet(Value& result, const Value& value);
        void connectedGet(bool& result);
        void connectedProxyTypeGet(ASString& result);
        void defaultObjectEncodingSet(Value& result, UInt32 value);
        void objectEncodingGet(UInt32& result);
        void objectEncodingSet(Value& result, UInt32 value);
        void proxyTypeGet(ASString& result);
        void proxyTypeSet(Value& result, const ASString& value);
        void uriGet(ASString& result);
        void usingTLSGet(bool& result);
        void addHeader(Value& result, const ASString& operation, bool mustUnderstand, const Value& param);
        void call(Value& result, unsigned argc, const Value* const argv);
        void close(Value& result);
        void connect(Value& result, unsigned argc, const Value* const argv);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class NetConnection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::NetConnection"; }
#endif
    public:
        NetConnection(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::NetConnection> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 15 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class NetConnection : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::NetConnection"; }
#endif
    public:
        typedef Classes::NetConnection ClassType;

    public:
        NetConnection(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

