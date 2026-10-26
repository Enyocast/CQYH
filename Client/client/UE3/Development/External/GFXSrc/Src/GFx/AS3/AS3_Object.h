/**************************************************************************

Filename    :   AS3_Object.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_Object_H
#define INC_AS3_Object_H


#include "AS3_Value.h"
#include "AS3_Slot.h"
#include "Kernel/SF_AutoPtr.h"

///////////////////////////////////////////////////////////////////////////////
#define MEMBER(clss, mbr) (((clss *)1)->mbr)
#define OFFSETOF(clss, mbr) ((UPInt)&(MEMBER(clss, mbr)) - 1)
#define NUMBEROF(a) sizeof(a) / sizeof(a[0])

#ifdef GFX_AS_ENABLE_USERDATA
namespace Scaleform { namespace GFx {
    class ASUserData;
    class Movie;
}}
#endif

namespace Scaleform { namespace GFx { namespace AS3 
{
    
///////////////////////////////////////////////////////////////////////////
typedef ArrayLH<Abc::Multiname> MultinamesType;

///////////////////////////////////////////////////////////////////////////
namespace Instances
{
    class Object;
    class Array;
    class Function;
}

///////////////////////////////////////////////////////////////////////////
class NamespaceSet : public GASRefCountBase
{
#ifdef GFX_AS3_VERBOSE
public:
    virtual const char* GetAS3ObjectType() const { return "NamespaceSet"; }
#endif
public:
    NamespaceSet(VM& vm);
    
public:
    bool Contains(const Instances::Namespace& ns) const;
    
public:
    typedef ArrayLH<SPtr<Instances::Namespace> > TContainer;

    const TContainer& GetNamespaces() const
    {
        return Namespaces;
    }
    void Add(Instances::Namespace& ns);
    
public:
    virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
    
private:
    TContainer  Namespaces;
};

///////////////////////////////////////////////////////////////////////////
// Multiname should be completely initialized by the time we use it.
// So, the "run-time" part is irrelevant for this class.

namespace TR
{
    class StackReader;
}

class Multiname : public Abc::HasMultinameKind
{
    friend class StackReader;
    friend class TR::StackReader;
    
public:
    typedef Abc::MultinameKind MultinameKind;
    
public:
    Multiname(Instances::Namespace& ns, const Value& name = Value::GetUndefined());
    Multiname(NamespaceSet& nss, const Value& name = Value::GetUndefined());
    Multiname(VMAbcFile& file, const Abc::Multiname& mn);
    // Creates a multi-name from a sting with includes a namespace,
    // as in "flash.display.Stage", where "flash.display" is a namespace.
    Multiname(const VM& vm, const StringDataPtr& qname);

public:
    bool IsAnyType() const
    {
        return Name.IsNullOrUndefined() || (Name.IsString() && Name.AsString().IsEmpty());
    }

    bool IsAnyNamespace() const
    {
        return IsQName() && Obj.GetPtr() == NULL;
    }

public:
    bool ContainsNamespace(const Instances::Namespace& ns) const;

    const Value& GetName() const
    {
        return Name;
    }
    Instances::Namespace& GetNamespace() const;
    NamespaceSet& GetNamespaceSet() const;

protected:
    // Used by op-stack Read() to resolve name components.
    void SetRTNamespace(Instances::Namespace& ns);

    void SetRTName(const Value& nameVal)
    {
        SF_ASSERT(IsNameLate());
        Name = nameVal;
        // Keep MN_NameLate flag. We will use it during code generation.
        // setKind((MultinameKind)(GetKind() & ~Abc::MN_NameLate));
    }
    void PickRTName(Value& nameVal)
    {
        SF_ASSERT(IsNameLate());
        Name.Pick(nameVal);
        // Keep MN_NameLate flag. We will use it during code generation.
        // setKind((MultinameKind)(GetKind() & ~Abc::MN_NameLate));
    }
    void PickRTNameUnsafe(ValueStack& vs)
    {
        SF_ASSERT(IsNameLate());
        Name.PickUnsafe(vs);
        // Keep MN_NameLate flag. We will use it during code generation.
        // setKind((MultinameKind)(GetKind() & ~Abc::MN_NameLate));
    }
    
private:
    SPtr<GASRefCountBase> Obj;

    // Name is a value because of Array's indices.
    Value Name;
};

///////////////////////////////////////////////////////////////////////////
// PropRef is a property reference within Object, combining object
// pointer with a SlotInfo in it. Returned by various FindProperty methods.

class PropRef
{
public:
    PropRef()
    : pSI(NULL)
    , SlotIndex(0)
    {
    }
    PropRef(Object* _object, const SlotInfo* si, UPInt index)
    : pSI(si)
    , SlotIndex(index)
    , This(_object)
    {
    }
    PropRef(const Value& _this, const SlotInfo* si, UPInt index)
    : pSI(si)
    , SlotIndex(index)
    , This(_this)
    {
    }
    PropRef(Object* _object, Value* v)
    : pValue(SetValueFlag(v))
    , This(_object)
    {
    }
    PropRef(const Value& _this, Value* v)
    : pValue(SetValueFlag(v))
    , This(_this)
    {
    }
    
public:
    operator bool() const
    {
        return IsFound();
    }
    
    bool IsFound() const
    {
        return !(This.IsUndefined() || (IsAsValue() && GetAsValue() == NULL));
    }
    bool IsAsValue() const
    {
        return ((UPInt)pValue & ValueFlagMask) != 0;
    }

    const Value& GetThis() const
    {
        return This;
    }
    Value& GetThis()
    {
        return This;
    }

    UPInt GetSlotIndex() const
    {
        SF_ASSERT(!IsAsValue());
        return SlotIndex;
    }
    const SlotInfo* GetAsSlotInfo() const
    {
        SF_ASSERT(!IsAsValue());
        return pSI;
    }
    Value* GetAsValue() const
    {
        SF_ASSERT(IsAsValue());
        return reinterpret_cast<Value*>((UPInt)pValue & ~ValueFlagMask);
    }

    // Get name for debugging purposes.
    SF_DEBUG_CODE(ASString GetName() const;)
    // Can throw exceptions.
    CheckResult GetSlotValueUnsafe(VM& vm, Value& value, SlotInfo::ValTarget vtt = SlotInfo::valGet) const
    {
        SF_ASSERT(pSI);
        bool result = true;
        if (IsAsValue())
            value.AssignUnsafe(*GetAsValue());
        else
            result = pSI->GetSlotValueUnsafe(vm, value, This, NULL, vtt);

        return result;
    }
    CheckResult GetSlotValueUnsafe(VM& vm, Value& value, const VTable& vt) const
    {
        SF_ASSERT(pSI);
        bool result = true;
        if (IsAsValue())
            value.AssignUnsafe(*GetAsValue());
        else
            result = pSI->GetSlotValueUnsafe(vm, value, This, &vt);

        return result;
    }
    // Can throw exceptions.        
    CheckResult SetSlotValue(VM& vm, const Value& value) const
    {
        SF_ASSERT(pSI);
        bool result = true;
        if (IsAsValue())
            GetAsValue()->Assign(value);
        else
            result = const_cast<SlotInfo*>(pSI)->SetSlotValue(vm, value, This);

        return result;
    }
    
private:
    enum {ValueFlagMask = 1U};

    static Value* SetValueFlag(Value* v)
    {
        return reinterpret_cast<Value*>((UPInt)v | ValueFlagMask);
    }

private:
    union {
        const SlotInfo* pSI;
        Value*          pValue;
    };
    UPInt   SlotIndex;
    Value   This; // This value represents an object of generic type.
}; // class PropRef


///////////////////////////////////////////////////////////////////////////

// These are the different Built-in traits types that Object instance
// can have. These can be used for efficient TypeOf testing for built-in
// classes.

enum BuiltinTraitsType
{
    // *** VM Types
    Traits_Unknown,
    Traits_Boolean,
    Traits_SInt,
    Traits_UInt,
    Traits_Number,
    Traits_String,
    Traits_Namespace,
    Traits_Array,
    Traits_Date,
    Traits_Function,
    Traits_Dictionary,
    Traits_Vector_object,
    Traits_QName,
    Traits_XML,
    Traits_XMLList,

    // *** Flash-required types that need fast checking.
    
    // Display object types (must be listed within _Begin/_End range)
    Traits_DisplayObject_Begin,
    Traits_DisplayObject = Traits_DisplayObject_Begin,    
    Traits_InteractiveObject,
    Traits_SimpleButton,
    Traits_Shape,
    Traits_MorphShape,
    Traits_AVM1Movie,
    Traits_Bitmap,    
    // Following items must be derived from DisplayObjectContainer.
    Traits_DisplayObjectContainer,
    Traits_Sprite,
    Traits_MovieClip,
    Traits_Stage,
    Traits_Loader,    
    Traits_DisplayObject_End
};


///////////////////////////////////////////////////////////////////////////
// Forward declarations.

namespace ClassTraits
{
    class Traits;
    class Function;
}

namespace Instances
{
    class GlobalObject;
    class GlobalObjectCPP;
}

namespace InstanceTraits
{
    class UserDefined;
    class UserDefinedCPP;
    class UDBase;
}

///////////////////////////////////////////////////////////////////////////
class VTable;
enum FindPropAttr { FindGet, FindSet };

///////////////////////////////////////////////////////////////////////////
const SlotInfo* 
FindDynamicSlot(const SlotContainerType& sc, const ASString& name, const Instances::Namespace& ns);

const SlotInfo* 
FindFixedSlot(const Traits& t, const ASString& name, const Instances::Namespace& ns, UPInt& index, Object* obj);

const ClassTraits::Traits* 
FindFixedTraits(const Traits& t, const ASString& name, const Instances::Namespace& ns, UPInt& index);

// Pass an object if this function is called on an object.
// *index* is a slot index in given traits. Not valid if function returns NULL.
const SlotInfo* 
FindFixedSlot(VM& vm, const Traits& t, const Multiname& mn, UPInt& index, Object* obj);

const ClassTraits::Traits* 
FindFixedTraits(VM& vm, const Traits& t, const Multiname& mn);

///////////////////////////////////////////////////////////////////////////
// Seems to be similar to the ScriptObject in Tamarin ...
class Object : public GASRefCountBase
{
    friend void SetSlotObjectCpp(Object* const obj, UInt32 offset, const Value& v);
    friend class VM; // Because of Class& GetClass().
    friend class SlotInfo; // Because of GetDynamicValue().
    friend class Class; // Because of AddDynamicFunc().
    friend class Instance; // Because of Object(VM& vm);

public:
    // Storing attributes with a key saves memory (comparing to storing with a value).
    struct DynAttrsKey
    {
        enum {
            DoNotEnumMask = 0x1,
        };

        DynAttrsKey(const ASString& name, UInt32 flags = 0) 
            : Flags(flags)
            , Name(name) 
        {}

        struct HashFunctor
        {
            UPInt operator()(const DynAttrsKey& key) const
            { return key.Name.GetHash(); }
        };

        bool operator == (const DynAttrsKey& other) const
        { return (Name == other.Name); }

        const ASString& GetName() const { return Name; }
        bool IsDoNotEnum() const { return (Flags & DoNotEnumMask) != 0; }
        void SetDoNotEnum(bool v = true) const
        {
            // Conditionally set or clear bits without branching.
            Flags = (Flags & ~DoNotEnumMask) | (-static_cast<SInt32>(v) & DoNotEnumMask);
        }

    private:
        mutable UInt32  Flags;
        ASString        Name;
    };

    typedef HashLH<DynAttrsKey, Value, DynAttrsKey::HashFunctor> DynAttrsType;

public:
    // "t" - traits used to create this object ...
    explicit Object(Traits& t);
    virtual ~Object();

private:
    // This constructor should be used only by Namespace.
    Object(VM& vm);
    
public:
    // (dynamic properties are always in the public namespace in
    // ActionScript 3.0; a run-time error is signaled if an attempt is add a non-public property).
    
    // ECMA [[Put]]
    // Can throw exceptions.
    virtual CheckResult SetProperty(const Multiname& prop_name, const Value& value);
    // Can throw exceptions.
    // This method will return false if property wasn't found or we've got an exception.
    virtual CheckResult GetProperty(const Multiname& prop_name, Value& value);
    // No check is performed.
    virtual void GetDynamicProperty(AbsoluteIndex ind, Value& value);

    // ECMA [[Delete]]
    // Return "true" on success ...
    // Can throw exceptions.
    virtual CheckResult DeleteProperty(const Multiname& prop_name);
    
    // ECMA [[DefaultValue]]
    // Can throw exceptions.
	void GetDefaultValueUnsafe(Value& result, Value::Hint hint = Value::hintNone);
    
    // called as a function ...
    // "Call" can be called on any object.
    // Can throw exceptions.
    virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
    // It is a delayed version of the C++ constructor.
    virtual void AS3Constructor(unsigned argc, const Value* argv);
    
    // ECMA [[Construct]]
    // called as constructor, a la new ClassName() ...
    virtual void Construct(Value& result, unsigned argc, const Value* argv, bool extCall = false) = 0;

    // invoked after instance is created and traits are initialized.
    virtual void InitInstance(bool /*extCall*/ = false) {}
    
    ASString GetName() const;

public:
    // Dynamic attributes are always in the public namespace ...
    void AddDynamicSlotValuePair(const ASString& prop_name, const Value& v,
        SlotInfo::Attribute a = SlotInfo::aNone);
    // Version, which takes prop_name as a Value is required for Dictionary to work properly.
    virtual void AddDynamicSlotValuePair(const Value& prop_name, const Value& v,
        SlotInfo::Attribute a = SlotInfo::aNone);
    // Can throw exceptions.
    CheckResult DeleteDynamicSlotValuePair(const Multiname& mn);
    // Delete/set undefined dynamic value.

protected:
    // Analogue to Add2VT(), but adds function to dynamic values.
    void AddDynamicFunc(const ThunkInfo& func);

public:
	// This is a wrapper, which will execute "valueOf"
	// It can throw exceptions.
	void ValueOfUnsafe(Value& result);

    ASRefCountCollector *GetCollector() const
    {
        return reinterpret_cast<ASRefCountCollector*>(GASRefCountBase::GetCollector());
    }
    
    virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
    void ForEachChild_GC_NoValues(Collector* prcc, GcOp op) const;

    const Class& GetClass() const;
    
    virtual const ScopeStackType* GetStoredScope() const { return NULL; }

    bool IsDynamic() const;
    
public:
    virtual void GetNextPropertyName(Value& name, GlobalSlotIndex ind) const;

    // GetNextDynPropIndex is used for hasnext/hasnext2 opcode
    // implementation, which iterates on the object.
    // If there are no more properties, then the result index is 0,
    // which is an invalid SlotIndex.    
    virtual GlobalSlotIndex GetNextDynPropIndex(GlobalSlotIndex ind) const;

    // Get the value of the property that is at position index + 1.
    // Can throw exceptions.
    virtual void GetNextPropertyValue(Value& value, GlobalSlotIndex ind);

public:
    // These slot related methods are provided for convenience.

    // Can throw exceptions.
    CheckResult GetSlotValueUnsafe(SlotIndex ind, Value& value);
    CheckResult GetSlotValueUnsafe(GlobalSlotIndex ind, Value& value);

    // Set a value in this object referenced by a slot.
    // Can throw exceptions.        
    CheckResult SetSlotValue(SlotIndex ind, const Value& value);

public:
    // Object's Traits are not supposed to be changed elsewhere ...
    const Traits& GetTraits() const
    {
        SF_ASSERT(pTraits.GetPtr());
        return *pTraits;
    }
    // Fix address in case lower bit is used for GC purposes.
    // This method is safe to call inside of ForEachChild_GC().
    const Traits& GetTraitsSafe() const
    {
        SF_ASSERT(pTraits.GetPtr());
        return *(Traits*)((UPInt)pTraits.GetPtr() & (SF_MAX_UPINT - 1));
    }
    // Non-const version is public because we need to create instances of
    // classes outside of traits them self.
    // Non-const GetTraits() is not safe, but we need it.
    Traits& GetTraits()
    {
        SF_ASSERT(pTraits.GetPtr());
        return *pTraits;
    }

    VM& GetVM() const;
    // This method is safe to call inside of ForEachChild_GC().
    VM& GetVMSafe() const;

    BuiltinTraitsType GetTraitsType() const;

    VTable& GetVT();

public:
    ASString GetASString(const char *pstr) const;
    ASString GetASString(const char *pstr, UPInt length) const;
    ASString GetASString(const String& str) const;

public:
    // These methods are safe to be public.

    // AS3 methods.
    void constructor(Value& result);

public:
    // !!! This method should not be used in Object::hasOwnProperty() because it
    // looks into static properties and into a prototype chain.
    // This method is not const because it can cause on demand object initialization.
    void FindProperty(PropRef& result, const Multiname& mn, FindPropAttr attr = FindGet);

    // Searches traits on object; searchTraits are typically instance traits
    // of this object, but may also be traits for a base (when searching super).
    SF_INLINE
    const SlotInfo* FindFixedSlot(const ASString& name, 
                                  const Instances::Namespace& ns,
                                  UPInt& index)
    {
        return AS3::FindFixedSlot(GetTraits(), name, ns, index, this);
    }

    SF_INLINE const Value* FindDynamicSlot(const ASString& name) const
    {
        return DynAttrs.Get(name);
    }

    virtual PropRef FindDynamicSlot(const Multiname& mn);

    const DynAttrsType* GetDynamicAttrs() const
    {
        return &DynAttrs;
    }

public:
    virtual const SlotInfo* InitializeOnDemand(
        const SlotInfo* si,
        const ASString& name,
        const Instances::Namespace& ns,
        UPInt& index);
    
#ifdef GFX_AS_ENABLE_USERDATA
public:
    ASUserData* GetUserData() const { return pUserDataHolder ? pUserDataHolder->pUserData : NULL; }
    void        SetUserData(Movie* pmovieView, ASUserData* puserData, bool isdobj);
#endif

protected:    
    Class& GetClass();
    StringManager& GetStringManager() const;
    const Value& GetGlobalObject() const;
    bool IsException() const;

#ifdef GFX_AS_ENABLE_USERDATA
protected:
    struct UserDataHolder : public NewOverrideBase<StatMV_VM_Instance_Mem>
    {
        Movie*          pMovieView;
        ASUserData*     pUserData;
        UserDataHolder(Movie* pmovieView, ASUserData* puserData) :
        pMovieView(pmovieView), pUserData(puserData) {}
        void    NotifyDestroy(Object* pthis) const;
    };
#endif

#ifdef GFX_AS3_VERBOSE
public:
    // returns 'true' if 'this' is an instance of AS3::Object.
    // Needed for ObjectCollector (not garbage collector).
    virtual bool IsAS3Object() const { return true; }
    virtual const char* GetAS3ObjectType() const { return "Object"; }
#endif

//protected:
public:
    // Can throw exceptions.
    void ExecutePropertyUnsafe(const ASString& name, Value& result, unsigned argc, const Value* argv);
	void ExecuteValueUnsafe(Value& value, Value& result, unsigned argc, const Value* argv);
    
private:
    Object(const Object&);

private:
    void Set(SPtr<Object>& o, const Value& v)
    {
        SF_ASSERT(v.IsObject());
        o = v.GetObject();
    }
    void Set(Value& value, const Value& v)
    {
        value = v;
    }

    // Can throw exceptions.
    CheckResult GetSlotValueUnsafe(const ASString& prop_name, Instances::Namespace& ns, Value& value);

private:
    SPtr<Traits>    pTraits;
    DynAttrsType    DynAttrs;
#ifdef GFX_AS_ENABLE_USERDATA
    UserDataHolder* pUserDataHolder;
#endif
}; // class Object

///////////////////////////////////////////////////////////////////////////
inline 
Value::operator SPtr<Object>() const
{
    SF_ASSERT(IsObject());
    return SPtr<Object>(static_cast<Object*>(value));
}

inline 
void Value::AddRefObject() const
{
    if (value.VS._1.VObj)
        value.VS._1.VObj->AddRef();
}

inline 
void Value::AddRefClosure() const
{
    if (value.VS._2.VObj)
        value.VS._2.VObj->AddRef();
}

///////////////////////////////////////////////////////////////////////////
SF_INLINE
ASStringNode* GetSlotStringNode(Object* const obj, UInt32 offset)
{
    char* addr = (char*)obj + offset;
    ASStringNode** node = (ASStringNode**)addr;
    return *node;
}
SF_INLINE
const char* GetSlotConstChar(Object* const obj, UInt32 offset)
{
    char* addr = (char*)obj + offset;
    const char** str = (const char**)addr;
    return *str;
}
SF_INLINE
Value::Number GetSlotNumber(Object* const obj, UInt32 offset)
{
    return *(Value::Number*)((char*)obj + offset);
}
SF_INLINE
UInt32 GetSlotUInt(Object* const obj, UInt32 offset)
{
    return *(UInt32*)((char*)obj + offset);
}
SF_INLINE
SInt32 GetSlotSInt(Object* const obj, UInt32 offset)
{
    return *(SInt32*)((char*)obj + offset);
}
SF_INLINE
bool GetSlotBoolean(Object* const obj, UInt32 offset)
{
    return *(bool*)((char*)obj + offset);
}
SF_INLINE
Value& GetSlotValue(Object* const obj, UInt32 offset)
{
    return *(Value*)((char*)obj + offset);
}
SF_INLINE
STPtr& GetSlotObjectAS(Object* const obj, UInt32 offset)
{
    return *(STPtr*)((char*)obj + offset);
}
SF_INLINE
SPtr<Object>& GetSlotObjectCpp(Object* const obj, UInt32 offset)
{
    return *(SPtr<Object>*)((char*)obj + offset);
}

SF_INLINE
void SetSlotStringNode(Object* const obj, UInt32 offset, ASStringNode* v)
{
    char* addr = (char*)obj + offset;
    ASStringNode** node = (ASStringNode**)addr;

    if (*node)
        (*node)->Release();

    *(ASStringNode**)addr = v;
    if (*node)
        (*node)->AddRef();
}
SF_INLINE
void SetSlotNumber(Object* const obj, UInt32 offset, Value::Number v)
{
    *(Value::Number*)((char*)obj + offset) = v;
}
SF_INLINE
void SetSlotUInt(Object* const obj, UInt32 offset, UInt32 v)
{
    *(UInt32*)((char*)obj + offset) = v;
}
SF_INLINE
void SetSlotSInt(Object* const obj, UInt32 offset, SInt32 v)
{
    *(SInt32*)((char*)obj + offset) = v;
}
SF_INLINE
void SetSlotBoolean(Object* const obj, UInt32 offset, bool v)
{
    *(bool*)((char*)obj + offset) = v;
}
SF_INLINE
void SetSlotValue(Object* const obj, UInt32 offset, const Value& v)
{
    (*(Value*)((char*)obj + offset)) = v;
}
SF_INLINE
void SetSlotObjectAS(Object* const obj, UInt32 offset, const Value& v)
{
    (*(STPtr*)((char*)obj + offset)).SetValue(v);
}
SF_INLINE
void SetSlotObjectCpp(Object* const obj, UInt32 offset, const Value& v)
{
    obj->Set(*(SPtr<Object>*)((char*)obj + offset), v);
}

///////////////////////////////////////////////////////////////////////////
const ClassTraits::Traits* FindGOTraits(VM& vm, const TGlobalObjects& go, const Multiname& mn);

///////////////////////////////////////////////////////////////////////////
void FindScopeProperty(PropRef& result, VM& vm, const UPInt baseSSInd, const ScopeStackType& scope_stack, const Multiname& mn);

///////////////////////////////////////////////////////////////////////////
void FindGOProperty(PropRef& result, VM& vm, const TGlobalObjects& go, const Multiname& mn, const ClassTraits::Traits* ctr);

///////////////////////////////////////////////////////////////////////////
// Try to locate own property. If that is not possible, then look into stored scope chain (if available).
// This function is similar to Object::FindProperty().
// The difference is that it can handle primitive values.
// It can throw exceptions.
void FindObjProperty(PropRef& result, VM& vm, const Value& scope, const Multiname& mn, FindPropAttr attr = FindGet);
void FindPropertyWith(PropRef& result, VM& vm, const Value& scope, const Multiname& mn, FindPropAttr attr = FindGet);

// This function will find a function with name prop_name on value _this and execute it.
// Return false if function is not found or exception is thrown.
CheckResult ExecutePropertyUnsafe(VM& vm, const Multiname& prop_name, const Value& _this, Value& result, unsigned argc, const Value* argv);

// Put property value.
// This method is similar to Object::SetProperty().
// It can throw exceptions.
CheckResult SetProperty(VM& vm, const Value& _this, const Multiname& prop_name, const Value& value);
// Get property value.
// It can throw exceptions.
// This method will return false if property wasn't found or we've got an exception.
CheckResult GetPropertyUnsafe(VM& vm, const Value& _this, const Multiname& prop_name, Value& value);

///////////////////////////////////////////////////////////////////////////
// Can throw exceptions.
// ot - Origination Traits.
CheckResult GetSuperProperty(VM& vm, const Traits* ot, Value& result, const Value& _this, const Multiname& mn, SlotInfo::ValTarget vtt = SlotInfo::valGet);
// Can throw exceptions.        
// ot - Origination Traits.
CheckResult SetSuperProperty(VM& vm, const Traits* ot, const Value& object, const Multiname& mn, const Value& value);

///////////////////////////////////////////////////////////////////////////
// Can throw exceptions.
// This function will run "toString" method on _this.
CheckResult ToString(VM& vm, const Value& _this, ASString& result);

///////////////////////////////////////////////////////////////////////////
namespace InstanceTraits
{
    class Traits;
}

// Class is a synonym for datatype ...
// Static part of the object ...
// !!! May not be moveable ...
// ??? It is a base class for all Classes. Theoretically, it is supposed to be abstract ...
class Class : public Object
{
    friend class ClassTraits::Traits;

#ifdef GFX_AS3_VERBOSE
private:
    virtual const char* GetAS3ObjectType() const { return "Class"; }
#endif
    
public:
    typedef Class ClassType;

public:
    // "t" are traits used to create this Class ...
    Class(ClassTraits::Traits& t);
    virtual ~Class();
    
public:

    virtual void Construct(Value& _this, unsigned argc, const Value* argv, bool extCall = false);
    virtual CheckResult PreInit(const Value& _this) const;
    virtual void PostInit(const Value& _this, unsigned argc, const Value* argv) const;

    // Get a class for a generic.
    virtual Class& ApplyTypeArgs(unsigned argc, const Value* argv);

    virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
    
public:
    Class* GetParentClass() const
    {
        return ParentClass;
    }
    
    Object& GetPrototype();

    const ClassTraits::Traits& GetClassTraits() const;
    ClassTraits::Traits& GetClassTraits();
    const InstanceTraits::Traits& GetInstanceTraits() const;
    InstanceTraits::Traits& GetInstanceTraits();

public:
    // Type conversion collection of methods ...

    virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);

    typedef Value (Class::*ConvertFunc)(const Value& v SF_DEBUG_ARG(const Traits& ot)) const;

    // Add methods from VTable to a prototype object.
    // Raw methods are added, no proxies.
    void InitPrototypeFromVTable(AS3::Object& obj, ConvertFunc f = &Class::ConvertCopy) const;
    // Run methods through a CheckType proxy.
    void InitPrototypeFromVTableCheckType(AS3::Object& obj) const;

    // InitPrototype() has to be overloaded if prototype methods do not match regular methods.
    // For example, in the Object instance.
    virtual void InitPrototype(AS3::Object& obj) const;
    // Create a prototype object.
    virtual Pickable<Object> MakePrototype() const;

protected:
    // Add "constructor" to the prototype object.
    void AddConstructor(AS3::Object& obj) const;

    void SetPrototype(Pickable<AS3::Object> p)
    {
        SF_ASSERT(!pPrototype.GetPtr());
        pPrototype = p;
        SF_ASSERT(pPrototype.GetPtr());
    }
    // Object::AddDynamicFunc() is protected. So, we need a wrapper.
    static void AddDynamicFunc(Object& obj, const ThunkInfo& func)
    {
        obj.AddDynamicFunc(func);
    }
    
private:
    // Converters.
    Value ConvertCopy(const Value& v SF_DEBUG_ARG(const Traits& ot)) const;
    Value ConvertCheckType(const Value& v SF_DEBUG_ARG(const Traits& ot)) const;

public:
    // AS3 methods.
    void lengthGet(SInt32& result);
    void prototypeGet(Value& result);
    void toString(ASString& result);

private:
    // This member is not *const* because Class is Object and we need to 
    // be able to change properties of Objects ...
    SPtr<Class>     ParentClass; 
        
protected:
    SInt32          Length;
    
private:
    SPtr<Object>    pPrototype;
}; // class Class

class ClassCallConstruct : public Class
{
public:
    ClassCallConstruct(ClassTraits::Traits& t) : Class(t) {}

public:
    virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
}; // class ClassCallConstruct

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_Object_H

