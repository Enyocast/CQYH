//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_SharedObject.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Net_SharedObject_H
#define INC_AS3_Obj_Net_SharedObject_H

#include "../Events/AS3_Obj_Events_EventDispatcher.h"
//##protect##"includes"
#include "GFx/GFx_SharedObject.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
namespace Instances
{
    class NetConnection;
    class SharedObject;
}
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SharedObject;
}

namespace InstanceTraits
{
    class SharedObject;
}

namespace Classes
{
    class SharedObject;
}

namespace Instances
{
    class SharedObject : public Instances::EventDispatcher
    {
        friend class InstanceTraits::SharedObject;
        
    public:
        typedef SharedObject SelfType;
        typedef Classes::SharedObject ClassType;
        typedef InstanceTraits::SharedObject TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SharedObject"; }
#endif
    protected:
        SharedObject(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        const String& GetName() const { return Name; }
        const String& GetLocalPath() const { return LocalPath; }

        bool    SetNameAndLocalPath(const ASString& name, const ASString& localPath);
        // Special setter to initialize the 'data' member
        void    SetDataObject(Object* pobj) { DataObj = pobj; }

    protected:
#ifdef GFX_AS3_ENABLE_SHAREDOBJECT
        bool    FlushImpl(SharedObjectVisitor* writer);
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_clientGet, 
            mid_clientSet, 
            mid_dataGet, 
            mid_defaultObjectEncodingSet, 
            mid_fpsSet, 
            mid_objectEncodingGet, 
            mid_objectEncodingSet, 
            mid_sizeGet, 
            mid_clear, 
            mid_close, 
            mid_connect, 
            mid_flush, 
            mid_send, 
            mid_setDirty, 
            mid_setProperty, 
        };
        void clientGet(Value& result);
        void clientSet(Value& result, const Value& value);
        void dataGet(Value& result);
        void defaultObjectEncodingSet(Value& result, UInt32 value);
        void fpsSet(Value& result, Value::Number value);
        void objectEncodingGet(UInt32& result);
        void objectEncodingSet(Value& result, UInt32 value);
        void sizeGet(UInt32& result);
        void clear(Value& result);
        void close(Value& result);
        void connect(Value& result, Instances::NetConnection* myConnection, const ASString& params);
        void flush(ASString& result, SInt32 minDiskSpace);
        void send(Value& result, unsigned argc, const Value* const argv);
        void setDirty(Value& result, const ASString& propertyName);
        void setProperty(Value& result, const ASString& propertyName, const Value& value);

//##protect##"instance$data"
    protected:
        SPtr<Object>    DataObj;
        String          Name;
        String          LocalPath;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SharedObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SharedObject"; }
#endif
    public:
        SharedObject(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SharedObject> MakeInstance(Traits& t);

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
    class SharedObject : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SharedObject"; }
#endif
    public:
        typedef Classes::SharedObject ClassType;

    public:
        SharedObject(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SharedObject : public Class
    {
        friend class ClassTraits::SharedObject;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SharedObject"; }
#endif
    public:
        typedef SharedObject SelfType;
        typedef SharedObject ClassType;
        
    private:
        SharedObject(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
    public:
        virtual void    ForEachChild_GC(Collector* prcc, GcOp op) const;
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_getLocal, 
            mid_getRemote, 
        };
        void getLocal(Value& result, const ASString& name, const ASString& localPath, bool secure);
        void getRemote(Value& result, const ASString& name, const ASString& remotePath, const Value& persistence, bool secure);

//##protect##"class_$data"
    protected:
        typedef ASStringHash< SPtr<Instances::SharedObject> >     SOLookupType;
        SOLookupType        SharedObjects;

//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

