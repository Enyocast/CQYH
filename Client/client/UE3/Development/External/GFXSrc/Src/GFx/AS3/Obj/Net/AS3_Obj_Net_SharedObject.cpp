//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Net_SharedObject.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Net_SharedObject.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "AS3_Obj_Net_NetConnection.h"
#include "../../AS3_MovieRoot.h"
#include "Kernel/SF_String.h"
#include "AS3_Obj_Net_SharedObjectFlushStatus.h"
#include "Kernel/SF_MsgFormat.h"
#include "../AS3_Obj_Array.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"

//#define SF_DEBUG_ASSHAREDOBJECTLOADER

#ifdef GFX_AS3_ENABLE_SHAREDOBJECT
//
// Custom visitor for SharedObject that loads data into a 
// Object instance.
//
class ASSharedObjectLoader : public SharedObjectVisitor
{
public:
    ASSharedObjectLoader(VM* pvm, Instances::Object* psobj) 
        : pVM(pvm), pData(psobj), bArrayIsTop(false) {}

    virtual void Begin();
    virtual void PushObject( const String& name );
    virtual void PushArray( const String& name );
    virtual void AddProperty( const String& name, const String& value, GFx::Value::ValueType type);
    virtual void PopObject();
    virtual void PopArray();
    virtual void End();

private:
    VM*                         pVM;
    Instances::Object*          pData;
    Array<Instances::Object*>   ObjectStack;
    bool                        bArrayIsTop;
};

void ASSharedObjectLoader::Begin()
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE(1, "ASSharedObjectLoader::Begin");
#endif // SF_DEBUG_ASSHAREDOBJECTLOADER

    ObjectStack.Clear();

    // Initialize root element
    ObjectStack.PushBack(pData);
}


void ASSharedObjectLoader::PushObject( const String& name )
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE1(1, "ASSharedObjectLoader::PushObject('%s')", name.ToCStr());
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    SF_ASSERT(ObjectStack.GetSize() > 0);
    Object* ptop = ObjectStack.Back();

    // Push an object to stack
    SPtr<Instances::Object> pobj = pVM->MakeObject();

    if (bArrayIsTop)
    {
        Instances::Array* ptoparr = static_cast<Instances::Array*>(ptop);
        ptoparr->PushBack(Value(pobj));
    }
    else
    {
        ptop->SetProperty(Multiname(*pVM, StringDataPtr(name.ToCStr(), name.GetLength())), Value(pobj)).DoNotCheck();
    }

    bArrayIsTop = false;
    ObjectStack.PushBack(pobj);
}


void ASSharedObjectLoader::PushArray( const String& name )
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE1(1, "ASSharedObjectLoader::PushArray('%s')", name.ToCStr());
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    SF_ASSERT(ObjectStack.GetSize() > 0);
    Object* ptop = ObjectStack.Back();

    // Push an array to stack
    SPtr<Instances::Array> parr = pVM->MakeArray();

    if (bArrayIsTop)
    {
        Instances::Array* ptoparr = static_cast<Instances::Array*>(ptop);
        ptoparr->PushBack(Value(parr));
    }
    else
    {
        ptop->SetProperty(Multiname(*pVM, StringDataPtr(name.ToCStr(), name.GetLength())), Value(parr)).DoNotCheck() ;
    }

    bArrayIsTop = true;
    ObjectStack.PushBack(parr);
}


void ASSharedObjectLoader::AddProperty(const String &name, 
                                        const String &value, 
                                        GFx::Value::ValueType type)
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE2(1, "ASSharedObjectLoader::PushProperty('%s', '%s')", 
        name.ToCStr(), value.ToCStr());
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    SF_ASSERT(ObjectStack.GetSize() > 0);
    Object* ptop = ObjectStack.Back();

    // Add property to top element
    Value v;
    switch (type)
    {
    case GFx::Value::VT_Int:
        {
            v.SetSInt32(atoi(value.ToCStr()));
            break;
        }
    case GFx::Value::VT_UInt:
        {
            v.SetUInt32(atoi(value.ToCStr()));
            break;
        }
    case GFx::Value::VT_Number:
        {
            v.SetNumber(atof(value.ToCStr()));
            break;
        }
    case GFx::Value::VT_String:
        {
            v.Assign(pVM->GetStringManager().CreateString(value));
            break;
        }
    case GFx::Value::VT_Boolean:
        {
            v.SetBool( !SFstrncmp(value.ToCStr(), "true", 4) );
            break;
        }
    case GFx::Value::VT_Undefined:
        {
            v.SetUndefined();
            break;
        }
    case GFx::Value::VT_Null:
        {
            v.SetNull();
            break;
        }
    default:
        {
            SF_ASSERT(0); // Unknown case
        }
    }

    if (bArrayIsTop)
    {
        Instances::Array* ptoparr = static_cast<Instances::Array*>(ptop);
        ptoparr->PushBack(v);
    }
    else
    {
        ptop->SetProperty(Multiname(*pVM, StringDataPtr(name.ToCStr(), name.GetLength())), v).DoNotCheck();
    }
}


void ASSharedObjectLoader::PopObject()
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE(1, "ASSharedObjectLoader::PopObject");
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    // Root should not be popped
    SF_ASSERT(ObjectStack.GetSize() > 1);
    ObjectStack.PopBack();
    // Evaluate current state
    Instances::Object* ptop = ObjectStack.Back();
    
    bArrayIsTop = ptop->GetTraitsType() == Traits_Array && 
        ptop->GetTraits().IsInstanceTraits();
}


void ASSharedObjectLoader::PopArray()
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE(1, "ASSharedObjectLoader::PopArray");
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    PopObject();
}


void ASSharedObjectLoader::End()
{
#ifdef SF_DEBUG_ASSHAREDOBJECTLOADER
    SF_DEBUG_MESSAGE(1, "ASSharedObjectLoader::End");
#endif  // SF_DEBUG_ASSHAREDOBJECTLOADER

    // Check stack state; only root element must exist
    SF_ASSERT(bArrayIsTop == false);
    SF_ASSERT(ObjectStack.GetSize() == 1);
}

//////////////////////////////////////////////////////////////////////////

#endif  // GFX_AS3_ENABLE_SHAREDOBJECT

//##protect##"methods"

// Values of default arguments.
namespace Impl
{

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Instances::SharedObject, Instances::SharedObject::mid_connect, 1, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Instances::SharedObject, Instances::SharedObject::mid_setProperty, 1, const Value&>(AS3::StringManager&)
    {
        return Value::GetNull();
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Classes::SharedObject, Classes::SharedObject::mid_getLocal, 1, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

    template <>
    SF_INLINE
    ASString GetMethodDefArg<Classes::SharedObject, Classes::SharedObject::mid_getRemote, 1, const ASString&>(AS3::StringManager& sm)
    {
        return sm.CreateConstString("null");
    }

    template <>
    SF_INLINE
    Value GetMethodDefArg<Classes::SharedObject, Classes::SharedObject::mid_getRemote, 2, const Value&>(AS3::StringManager&)
    {
        return Value(false);
    }

} // namespace Impl
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_clientGet, Value> TFunc_Instances_SharedObject_clientGet;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_clientSet, Value, const Value&> TFunc_Instances_SharedObject_clientSet;
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_dataGet, Value> TFunc_Instances_SharedObject_dataGet;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_defaultObjectEncodingSet, Value, UInt32> TFunc_Instances_SharedObject_defaultObjectEncodingSet;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_fpsSet, Value, Value::Number> TFunc_Instances_SharedObject_fpsSet;
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_objectEncodingGet, UInt32> TFunc_Instances_SharedObject_objectEncodingGet;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_objectEncodingSet, Value, UInt32> TFunc_Instances_SharedObject_objectEncodingSet;
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_sizeGet, UInt32> TFunc_Instances_SharedObject_sizeGet;
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_clear, Value> TFunc_Instances_SharedObject_clear;
typedef ThunkFunc0<Instances::SharedObject, Instances::SharedObject::mid_close, Value> TFunc_Instances_SharedObject_close;
typedef ThunkFunc2<Instances::SharedObject, Instances::SharedObject::mid_connect, Value, Instances::NetConnection*, const ASString&> TFunc_Instances_SharedObject_connect;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_flush, ASString, SInt32> TFunc_Instances_SharedObject_flush;
typedef ThunkFunc2<Instances::SharedObject, Instances::SharedObject::mid_send, Value, unsigned, const Value*> TFunc_Instances_SharedObject_send;
typedef ThunkFunc1<Instances::SharedObject, Instances::SharedObject::mid_setDirty, Value, const ASString&> TFunc_Instances_SharedObject_setDirty;
typedef ThunkFunc2<Instances::SharedObject, Instances::SharedObject::mid_setProperty, Value, const ASString&, const Value&> TFunc_Instances_SharedObject_setProperty;

template <> const TFunc_Instances_SharedObject_clientGet::TMethod TFunc_Instances_SharedObject_clientGet::Method = &Instances::SharedObject::clientGet;
template <> const TFunc_Instances_SharedObject_clientSet::TMethod TFunc_Instances_SharedObject_clientSet::Method = &Instances::SharedObject::clientSet;
template <> const TFunc_Instances_SharedObject_dataGet::TMethod TFunc_Instances_SharedObject_dataGet::Method = &Instances::SharedObject::dataGet;
template <> const TFunc_Instances_SharedObject_defaultObjectEncodingSet::TMethod TFunc_Instances_SharedObject_defaultObjectEncodingSet::Method = &Instances::SharedObject::defaultObjectEncodingSet;
template <> const TFunc_Instances_SharedObject_fpsSet::TMethod TFunc_Instances_SharedObject_fpsSet::Method = &Instances::SharedObject::fpsSet;
template <> const TFunc_Instances_SharedObject_objectEncodingGet::TMethod TFunc_Instances_SharedObject_objectEncodingGet::Method = &Instances::SharedObject::objectEncodingGet;
template <> const TFunc_Instances_SharedObject_objectEncodingSet::TMethod TFunc_Instances_SharedObject_objectEncodingSet::Method = &Instances::SharedObject::objectEncodingSet;
template <> const TFunc_Instances_SharedObject_sizeGet::TMethod TFunc_Instances_SharedObject_sizeGet::Method = &Instances::SharedObject::sizeGet;
template <> const TFunc_Instances_SharedObject_clear::TMethod TFunc_Instances_SharedObject_clear::Method = &Instances::SharedObject::clear;
template <> const TFunc_Instances_SharedObject_close::TMethod TFunc_Instances_SharedObject_close::Method = &Instances::SharedObject::close;
template <> const TFunc_Instances_SharedObject_connect::TMethod TFunc_Instances_SharedObject_connect::Method = &Instances::SharedObject::connect;
template <> const TFunc_Instances_SharedObject_flush::TMethod TFunc_Instances_SharedObject_flush::Method = &Instances::SharedObject::flush;
template <> const TFunc_Instances_SharedObject_send::TMethod TFunc_Instances_SharedObject_send::Method = &Instances::SharedObject::send;
template <> const TFunc_Instances_SharedObject_setDirty::TMethod TFunc_Instances_SharedObject_setDirty::Method = &Instances::SharedObject::setDirty;
template <> const TFunc_Instances_SharedObject_setProperty::TMethod TFunc_Instances_SharedObject_setProperty::Method = &Instances::SharedObject::setProperty;

namespace Instances
{
    SharedObject::SharedObject(InstanceTraits::Traits& t)
    : Instances::EventDispatcher(t)
//##protect##"instance::SharedObject::SharedObject()$data"
//##protect##"instance::SharedObject::SharedObject()$data"
    {
//##protect##"instance::SharedObject::SharedObject()$code"
//##protect##"instance::SharedObject::SharedObject()$code"
    }

    void SharedObject::clientGet(Value& result)
    {
//##protect##"instance::SharedObject::clientGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::clientGet()");
//##protect##"instance::SharedObject::clientGet()"
    }
    void SharedObject::clientSet(Value& result, const Value& value)
    {
//##protect##"instance::SharedObject::clientSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::clientSet()");
//##protect##"instance::SharedObject::clientSet()"
    }
    void SharedObject::dataGet(Value& result)
    {
//##protect##"instance::SharedObject::dataGet()"

        result.Assign(DataObj);

//##protect##"instance::SharedObject::dataGet()"
    }
    void SharedObject::defaultObjectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"instance::SharedObject::defaultObjectEncodingSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::defaultObjectEncodingSet()");
//##protect##"instance::SharedObject::defaultObjectEncodingSet()"
    }
    void SharedObject::fpsSet(Value& result, Value::Number value)
    {
//##protect##"instance::SharedObject::fpsSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::fpsSet()");
//##protect##"instance::SharedObject::fpsSet()"
    }
    void SharedObject::objectEncodingGet(UInt32& result)
    {
//##protect##"instance::SharedObject::objectEncodingGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::objectEncodingGet()");
//##protect##"instance::SharedObject::objectEncodingGet()"
    }
    void SharedObject::objectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"instance::SharedObject::objectEncodingSet()"
        SF_UNUSED2(result, value);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::objectEncodingSet()");
//##protect##"instance::SharedObject::objectEncodingSet()"
    }
    void SharedObject::sizeGet(UInt32& result)
    {
//##protect##"instance::SharedObject::sizeGet()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::sizeGet()");
//##protect##"instance::SharedObject::sizeGet()"
    }
    void SharedObject::clear(Value& result)
    {
//##protect##"instance::SharedObject::clear()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::clear()");
//##protect##"instance::SharedObject::clear()"
    }
    void SharedObject::close(Value& result)
    {
//##protect##"instance::SharedObject::close()"
        SF_UNUSED1(result);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::close()");
//##protect##"instance::SharedObject::close()"
    }
    void SharedObject::connect(Value& result, Instances::NetConnection* myConnection, const ASString& params)
    {
//##protect##"instance::SharedObject::connect()"
        SF_UNUSED3(result, myConnection, params);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::connect()");
//##protect##"instance::SharedObject::connect()"
    }
    void SharedObject::flush(ASString& result, SInt32 minDiskSpace)
    {
//##protect##"instance::SharedObject::flush()"

#ifdef GFX_AS3_ENABLE_SHAREDOBJECT
        SF_UNUSED1(minDiskSpace);

        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* proot = vm.GetMovieRoot();
        SF_ASSERT(proot);
        MovieImpl* pmovie = proot->GetMovieImpl();

        bool ok = false;
        Ptr<SharedObjectManagerBase> psoMgr = pmovie->GetSharedObjectManager();
        if (psoMgr)
        {
            Ptr<SharedObjectVisitor> pwriter = *psoMgr->CreateWriter(Name, 
                LocalPath, pmovie->GetFileOpener());
            ok = FlushImpl(pwriter);
            if (!ok)
                vm.ThrowError(VM::Error(VM::eFileWriteError, vm SF_DEBUG_ARG("Unable to flush shared object data!")));
            else
            {
                result = vm.GetStringManager().CreateConstString("flushed");
            }
        }
        else
        {
            vm.ThrowError(VM::Error(VM::eFileWriteError, vm SF_DEBUG_ARG("SharedObjectManager state is not installed!")));
        }
#else
        SF_UNUSED2(result, minDiskSpace);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::flush()");
#endif

//##protect##"instance::SharedObject::flush()"
    }
    void SharedObject::send(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::SharedObject::send()"
        SF_UNUSED3(result, argc, argv);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::send()");
//##protect##"instance::SharedObject::send()"
    }
    void SharedObject::setDirty(Value& result, const ASString& propertyName)
    {
//##protect##"instance::SharedObject::setDirty()"
        SF_UNUSED2(result, propertyName);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::setDirty()");
//##protect##"instance::SharedObject::setDirty()"
    }
    void SharedObject::setProperty(Value& result, const ASString& propertyName, const Value& value)
    {
//##protect##"instance::SharedObject::setProperty()"
        SF_UNUSED3(result, propertyName, value);
        WARN_NOT_IMPLEMENTED("instance::SharedObject::setProperty()");
//##protect##"instance::SharedObject::setProperty()"
    }

//##protect##"instance$methods"

    bool    SharedObject::SetNameAndLocalPath(const ASString& name, const ASString& localPath)
    {
        const char* pstr;
        UInt32 c = name.GetFirstCharAt(0, &pstr);
        while (c)
        {
            switch (c)
            {
            case '~':
            case '%':
            case '&':
            case '\\':
            case ';':
            case ':':
            case '"':
            case '\'':
            case ',':
            case '<':
            case '>':
            case '?':
            case '#':
                return false;
            }
            // Check whitespace
            if (SFiswspace((wchar_t)c))
                return false;
            c = name.GetNextChar(&pstr);
        }
        Name = name.ToCStr();
        LocalPath = localPath.ToCStr();
        return true;
    }

#ifdef GFX_AS3_ENABLE_SHAREDOBJECT
    bool SharedObject::FlushImpl(SharedObjectVisitor* writer)
    {
        if (!writer)
            return false;

        // Visit all members and notify writer
        bool hasData = DataObj.GetPtr() != NULL;
        SF_ASSERT(hasData);
        SF_UNUSED(hasData);
        Instances::Object* pdataObj = DataObj.GetPtr();
        SF_ASSERT(pdataObj);

        struct DataWriter
        {
            // Hash is required to avoid infinite loops when objects have
            // circular references. If an object has been visited we do 
            // not visit it again.
            HashIdentity<Instances::Object*, Instances::Object*>  VisitedObjects;
            VM                      *pVM;
            SharedObjectVisitor     *pWriter;

            DataWriter(VM *pvm, SharedObjectVisitor* pwriter) : pVM(pvm), pWriter(pwriter) {}

            void    VisitMembers(Instances::Object *pdataObj)
            {
                bool isArray = (pdataObj->GetTraitsType() == Traits_Array && 
                    pdataObj->GetTraits().IsInstanceTraits());

                if (!isArray)
                {
                    // We visit only dynamic attributes
                    const AS3::Object::DynAttrsType* dynAttrs = pdataObj->GetDynamicAttrs();
                    if (dynAttrs)
                    {
                        AS3::Object::DynAttrsType::ConstIterator it = dynAttrs->Begin();
                        for (; !it.IsEnd(); ++it)
                        {
                            // Include "DontEnum" properties.
                            const ASString& name = it->First.GetName();
                            const AS3::Value& asval = it->Second;

                            Visit(String(name.ToCStr(), name.GetLength()), asval);
                        }
                    }
                }
                else
                {
                    Instances::Array* arr  = static_cast<Instances::Array*>(pdataObj);
                    unsigned sz = (unsigned)arr->GetSize();
                    for (unsigned i=0; i < sz; i++)
                    {
                        const AS3::Value& asval = arr->At(i);
                        String name;
                        Format(name, "{0}", i);

                        Visit(name, asval);
                    }
                }
            }

            void Visit(const String& name, const Value& val)
            {
                switch (val.GetKind())
                {
                case Value::kNumber:
                    {
                        // writeout number                    
                        DoubleFormatter f(val.AsNumber());
                        f.Convert();
                        String sval(f, f.GetSize());

                        pWriter->AddProperty( name, sval, 
                            GFx::Value::VT_Number);
                        break;
                    }
                case Value::kInt:
                    {
                        // writeout int
                        LongFormatter f(val.AsInt());
                        f.Convert();
                        String sval(f, f.GetSize());

                        pWriter->AddProperty( name, sval, 
                            GFx::Value::VT_Int);
                        break;
                    }
                case Value::kUInt:
                    {
                        // writeout int
                        LongFormatter f(val.AsInt());
                        f.Convert();
                        String sval(f, f.GetSize());

                        pWriter->AddProperty( name, sval, 
                            GFx::Value::VT_Int);
                        break;
                    }
                case Value::kString:
                    {
                        // writeout string
                        String sval(val.AsString().ToCStr());
                        pWriter->AddProperty( name, sval, 
                            GFx::Value::VT_String);
                        break;
                    }
                case Value::kUndefined:
                    {
                        // writeout undefined
                        pWriter->AddProperty( name, "",
                            GFx::Value::VT_Undefined);
                        break;
                    }
                case Value::kBoolean:
                    {
                        // writeout boolean                    
                        pWriter->AddProperty( name, 
                            val.AsBool() ? "true" : "false", GFx::Value::VT_Boolean);
                        break;
                    }
                case Value::kObject:
                    {
                        if (val.IsNull())
                        {
                            // writeout null
                            pWriter->AddProperty( name, "", GFx::Value::VT_Null);
                            break;
                        }

                        // special case for Array
                        Instances::Object* pobj = (Instances::Object*)val.GetObject();
                        if (VisitedObjects.Get(pobj)) break;
                        VisitedObjects.Add(pobj, pobj);

                        if (pobj->GetTraitsType() == Traits_Array && 
                            pobj->GetTraits().IsInstanceTraits())
                        {
                            // writeout array
                            pWriter->PushArray( name );
                            VisitMembers(pobj);
                            pWriter->PopArray();
                        }
                        else
                        {
                            // writeout object
                            pWriter->PushObject( name );
                            VisitMembers(pobj);
                            pWriter->PopObject();
                        }
                        break;
                    }
                default:;
                }
            }
        } visitor(&GetVM(), writer);

        writer->Begin();
        visitor.VisitMembers(pdataObj);
        writer->End();

        return true;
    }
#endif // GFX_AS3_ENABLE_SHAREDOBJECT

//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo SharedObject::ti[SharedObject::ThunkInfoNum] = {
        {TFunc_Instances_SharedObject_clientGet::Func, &ObjectCI, "client", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SharedObject_clientSet::Func, NULL, "client", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SharedObject_dataGet::Func, &ObjectCI, "data", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SharedObject_defaultObjectEncodingSet::Func, NULL, "defaultObjectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SharedObject_fpsSet::Func, NULL, "fps", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SharedObject_objectEncodingGet::Func, &uintCI, "objectEncoding", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SharedObject_objectEncodingSet::Func, NULL, "objectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Instances_SharedObject_sizeGet::Func, &uintCI, "size", NULL, CT_Get, 0, 0},
        {TFunc_Instances_SharedObject_clear::Func, NULL, "clear", NULL, CT_Method, 0, 0},
        {TFunc_Instances_SharedObject_close::Func, NULL, "close", NULL, CT_Method, 0, 0},
        {TFunc_Instances_SharedObject_connect::Func, NULL, "connect", NULL, CT_Method, 1, 2},
        {TFunc_Instances_SharedObject_flush::Func, &StringCI, "flush", NULL, CT_Method, 0, 1},
        {TFunc_Instances_SharedObject_send::Func, NULL, "send", NULL, CT_Method, 0, 1023},
        {TFunc_Instances_SharedObject_setDirty::Func, NULL, "setDirty", NULL, CT_Method, 1, 1},
        {TFunc_Instances_SharedObject_setProperty::Func, NULL, "setProperty", NULL, CT_Method, 1, 2},
    };

    SharedObject::SharedObject(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::SharedObject::SharedObject()"
//##protect##"InstanceTraits::SharedObject::SharedObject()"
        SetMemSize(sizeof(Instances::SharedObject));

    }

    Pickable<Instances::SharedObject> SharedObject::MakeInstance(Traits& t)
    {
        return Pickable<Instances::SharedObject>(new(t.Alloc()) Instances::SharedObject(t));
    }

    void SharedObject::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    SharedObject::SharedObject(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::SharedObject::SharedObject()"
//##protect##"class_::SharedObject::SharedObject()"
    }
    void SharedObject::getLocal(Value& result, const ASString& name, const ASString& localPath, bool secure)
    {
//##protect##"class_::SharedObject::getLocal()"

#ifdef GFX_AS3_ENABLE_SHAREDOBJECT
        SF_UNUSED1(secure);

        ASString strFullPath = GetStringManager().CreateString(localPath.ToCStr());
        strFullPath += ":";
        strFullPath += name;

        SPtr<Instances::SharedObject>* psavedObj = SharedObjects.Get(strFullPath);
        if (psavedObj)
        {
            // Found a stored shared obj; return it
            result = *psavedObj;
            return;
        }

        InstanceTraits::SharedObject& itr = static_cast<InstanceTraits::SharedObject&>(GetInstanceTraits());
        SPtr<Instances::SharedObject> pthis = itr.MakeInstance(itr);

        // If name and directory aren't formatted correctly, fail
        if (!pthis->SetNameAndLocalPath(name, localPath))
        {
            result.SetNull();
            return;
        }

        ASVM& vm = static_cast<ASVM&>(GetVM());
        MovieRoot* proot = vm.GetMovieRoot();
        SF_ASSERT(proot);
        MovieImpl* pmovie = proot->GetMovieImpl();

        SPtr<Instances::Object> pdataObj = vm.MakeObject();        
        ASSharedObjectLoader   loader(&vm, pdataObj);

        Ptr<SharedObjectManagerBase> psoMgr = pmovie->GetSharedObjectManager();
        FileOpenerBase*  pfileopener = pmovie->GetFileOpener();
        Scaleform::String strName(name.ToCStr());
        Scaleform::String strLocalPath(localPath.ToCStr());
        if (!psoMgr || !psoMgr->LoadSharedObject(strName, strLocalPath, &loader, pfileopener))
        {
            result.SetNull();
            return;
        }
        else
        {
            pthis->SetDataObject(pdataObj);
            result = pthis;
            // Store for future lookup
            SharedObjects.Add(strFullPath, pthis);
        }
#else
        SF_UNUSED4(result, name, localPath, secure);
        WARN_NOT_IMPLEMENTED("class_::SharedObject::getLocal()");
#endif  //GFX_AS3_ENABLE_SHAREDOBJECT

//##protect##"class_::SharedObject::getLocal()"
    }
    void SharedObject::getRemote(Value& result, const ASString& name, const ASString& remotePath, const Value& persistence, bool secure)
    {
//##protect##"class_::SharedObject::getRemote()"
        SF_UNUSED5(result, name, remotePath, persistence, secure);
        WARN_NOT_IMPLEMENTED("class_::SharedObject::getRemote()");
//##protect##"class_::SharedObject::getRemote()"
    }
//##protect##"class_$methods"

    void SharedObject::ForEachChild_GC(Collector* prcc, GcOp op) const
    {
        Class::ForEachChild_GC(prcc, op);
        SOLookupType::ConstIterator it = SharedObjects.Begin();
        while(it != SharedObjects.End())
        {   
            const SPtr<Instances::SharedObject>& sobj = it->Second;
            AS3::ForEachChild_GC<Instances::SharedObject, Mem_Stat>(prcc, sobj, op SF_DEBUG_ARG(*this));
            ++it;
        }
    }

//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc3<Classes::SharedObject, Classes::SharedObject::mid_getLocal, Value, const ASString&, const ASString&, bool> TFunc_Classes_SharedObject_getLocal;
typedef ThunkFunc4<Classes::SharedObject, Classes::SharedObject::mid_getRemote, Value, const ASString&, const ASString&, const Value&, bool> TFunc_Classes_SharedObject_getRemote;

template <> const TFunc_Classes_SharedObject_getLocal::TMethod TFunc_Classes_SharedObject_getLocal::Method = &Classes::SharedObject::getLocal;
template <> const TFunc_Classes_SharedObject_getRemote::TMethod TFunc_Classes_SharedObject_getRemote::Method = &Classes::SharedObject::getRemote;

namespace ClassTraits
{
    const ThunkInfo SharedObject::ti[SharedObject::ThunkInfoNum] = {
        {TFunc_Classes_SharedObject_getLocal::Func, &SharedObjectCI, "getLocal", NULL, CT_Method, 1, 3},
        {TFunc_Classes_SharedObject_getRemote::Func, &SharedObjectCI, "getRemote", NULL, CT_Method, 1, 4},
    };
    SharedObject::SharedObject(VM& vm)
    : Traits(vm, SharedObjectCI)
    {
//##protect##"ClassTraits::SharedObject::SharedObject()"
//##protect##"ClassTraits::SharedObject::SharedObject()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::SharedObject(vm, SharedObjectCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::SharedObject(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> SharedObject::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) SharedObject(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo SharedObjectCI = {
    ClassInfo::CompileTime,
    "SharedObject", "flash.net", &EventDispatcherCI,
    ClassTraits::SharedObject::MakeClassTraits,
    ClassTraits::SharedObject::ThunkInfoNum,
    0,
    InstanceTraits::SharedObject::ThunkInfoNum,
    0,
    ClassTraits::SharedObject::ti,
    NULL,
    InstanceTraits::SharedObject::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

