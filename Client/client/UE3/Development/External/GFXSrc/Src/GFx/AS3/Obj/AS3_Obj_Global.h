/**************************************************************************

Filename    :   AS3_Obj_Global.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#ifndef INC_AS3_Obj_Global_H
#define INC_AS3_Obj_Global_H

#include "AS3_Obj_Object.h"

namespace Scaleform { namespace GFx { namespace AS3 
{
///////////////////////////////////////////////////////////////////////////////
// Forward declaration

class VMAbcFile;

namespace InstanceTraits
{
    class GlobalObjectScript;
}

///////////////////////////////////////////////////////////////////////////
namespace Instances
{
    ///////////////////////////////////////////////////////////////////////////
    class GlobalObject : public Instances::Object
    {
    protected:
        GlobalObject(InstanceTraits::Traits& t);
        virtual ~GlobalObject();

    public:
        virtual void Execute() = 0;

    protected:
        virtual void Construct(Value& _this, unsigned argc, const Value* argv, bool extCall = false);
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GlobalObject"; }
#endif
    };

    ///////////////////////////////////////////////////////////////////////////
    class GlobalObjectScript : public GlobalObject
    {
        friend class InstanceTraits::GlobalObjectScript;
        friend class InstanceTraits::UserDefined; // Because of InitOnDemand().

    protected:
        GlobalObjectScript(InstanceTraits::GlobalObjectScript& t);

    public:
        virtual ~GlobalObjectScript();

    public:
        virtual void Execute();
        void InitUserDefinedClassTraits();

        VMAbcFile& GetFile() const;
        const Abc::ScriptInfo& GetScript() const;

    protected:
        virtual const SlotInfo* InitializeOnDemand(
            const SlotInfo* si,
            const ASString& name,
            const Namespace& ns,
            UPInt& index);

    private:
        void InitOnDemand();

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GlobalObjectScript"; }
        virtual Scaleform::String GetAS3ObjectName() const; 
#endif
    private:
        bool Initialized;
    };

    ///////////////////////////////////////////////////////////////////////////
    struct ConstStringKey
    {
        const char *pChar;

        ConstStringKey(const char *pc)
        {
            pChar = pc;
        }
        bool operator == (const ConstStringKey& c) const
        {
            return strcmp(pChar, c.pChar) == 0;
        }
        bool operator != (const ConstStringKey& c) const
        {
            return strcmp(pChar, c.pChar) != 0;
        }
    };

    class ConstStringHashFn
    {
    public:

        size_t  operator()(const ConstStringKey& data) const
        { 
            size_t  size = strlen(data.pChar);
            return String::BernsteinHashFunction(data.pChar, size);
        }
    };

    template <class U>
    class ConstStringHash : public Hash<ConstStringKey, U, ConstStringHashFn, AllocatorGH<ConstStringKey, Mem_Stat> > {};

    ///////////////////////////////////////////////////////////////////////////
    class GlobalObjectCPP : public GlobalObject
    {
        friend class AS3::VM; // Because of exceptions ...
        friend class ThunkGenVT;

    public:
        typedef GlobalObjectCPP Self;
        
    public:
        GlobalObjectCPP(VM& vm, InstanceTraits::Traits& t);
        ~GlobalObjectCPP();

    public:
#ifdef SF_AS3_CLASS_AS_SLOT
        const Value& GetValueArray(AbsoluteIndex ind) const
        {
            return Values[ind.Get()];
        }
        void SetValueArray(AbsoluteIndex ind, const Value& v)
        {
            Values[ind.Get()] = v;
        }
#endif

#ifdef SF_AS3_CLASS_AS_SLOT
        // Add to fixed slots.
        const SlotInfo& AddFixedSlotValuePair(const ASString& prop_name, Pickable<const Instances::Namespace> ns,
            const ClassTraits::Traits* ctr, const Value& v, UPInt& index);
        // This method will also register Traits of a class.
        const SlotInfo& AddFixedSlot(Class& cl, Pickable<const Namespace> ns, UPInt& index)
        {
            return AddFixedSlotValuePair(cl.GetName(), ns, &cl.GetClassTraits(), Value(&cl), index);
        }
        // Add class slot to public namespace; used for TopLevel classes.
        // This method will also register Traits of a class.
        void AddFixedSlot(Class& cl);

        virtual const SlotInfo* InitializeOnDemand(
            const SlotInfo* si,
            const ASString& name,
            const Namespace& ns,
            UPInt& index);
#endif

        ClassTraits::Traits* GetClassTraits(
            const ASString& name,
            const Namespace& ns);

        void RegisterClassInfoTable(const ClassInfo* table[]);

    public:
        //
        virtual void Execute();

        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        
    public:
        // AS3 API ...

//##markup##"obj_global_h$package_methods"
//##begin##"obj_global_h$package_methods"
        void decodeURI(ASString& result, const ASString& uri);
        void decodeURIComponent(ASString& result, const ASString& uri);
        void encodeURI(ASString& result, const ASString& uri);
        void encodeURIComponent(ASString& result, const ASString& uri);
        void isNaN(bool& result, Value::Number n);
        void isFinite(bool& result, Value::Number n);
        void parseInt(Value& result, unsigned argc, const Value* const argv);
        void parseFloat(Value::Number& result, const ASString& str);
        void escape(Value& result, unsigned argc, const Value* const argv);
        void unescape(Value& result, unsigned argc, const Value* const argv);
        void isXMLName(bool& result, const Value& str);
        void trace(Value& result, unsigned argc, const Value* const argv);
        void print(Value& result, unsigned argc, const Value* const argv);
#ifndef SF_AS3_NO_FLASH
        void fscommand(Value& result, unsigned argc, const Value* const argv);
        void clearInterval(Value& result, UInt32 id);
        void clearTimeout(Value& result, UInt32 id);
        void describeType(Value& result, const Value& value);
        void escapeMultiByte(ASString& result, const ASString& value);
        void getDefinitionByName(Value& result, const ASString& name);
        void getQualifiedClassName(ASString& result, const Value& value);
        void getQualifiedSuperclassName(ASString& result, const Value& value);
        void getTimer(SInt32& result);
        void setInterval(Value& result, unsigned argc, const Value* const argv);
        void setTimeout(Value& result, unsigned argc, const Value* const argv);
        void unescapeMultiByte(ASString& result, const ASString& value);

#endif
//##end##"obj_global_h$package_methods"

    private:
        void Add2VT(const ClassInfo& ci, const ThunkInfo& func)
        {
            GetTraits().Add2VT(ci, func);
        }

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GlobalObjectCPP"; }
#endif
    private:
        ConstStringHash<const ClassInfo*> CIRegistrationHash;

        // AS3 API members ...
        const Value::Number PositiveInfinity;
        const Value::Number NegativeInfinity;
        const Value::Number NaN;
        const Value         undefined;
        enum { MemberInfoNum = 4 };
        static MemberInfo mi[MemberInfoNum];

        // Values is used instead of a tail to store fixed properties.
#ifdef SF_AS3_CLASS_AS_SLOT
        ValueArray          Values;
#endif
        ArrayLH<SPtr<ClassTraits::Traits> > CTraits;
    };

} // namespace Instances

///////////////////////////////////////////////////////////////////////////
namespace InstanceTraits
{
    ///////////////////////////////////////////////////////////////////////////
    class GlobalObject : public Traits
    {
    public:
        GlobalObject(VM& vm);

    public:
        virtual void MakeObject(Value& result, Traits& t);
        virtual bool IsGlobal() const;

        static const ClassInfo Info;
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::GlobalObject"; }
#endif
    };

    ///////////////////////////////////////////////////////////////////////////
    class GlobalObjectScript : public GlobalObject
    {
    public:
        GlobalObjectScript(
            VMAbcFile& file,
            VM& vm, 
            const Abc::ScriptInfo& script
            );

    public:
        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;
        virtual unsigned GetFixedMemSize() const;
        virtual VMAbcFile* GetFilePtr() const;

        Pickable<Instances::GlobalObjectScript> MakeInstance();

        VMAbcFile& GetFile() const
        {
            return *File;
        }
        const Abc::ScriptInfo& GetScript() const
        {
            return Script;
        }

    private:
        GlobalObjectScript& operator =(const GlobalObjectScript&);

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::GlobalObjectScript"; }
#endif
    private:
        SPtr<VMAbcFile> File;
        const Abc::ScriptInfo& Script;
    };

} // namespace InstanceTraits

namespace Instances
{
    inline
    VMAbcFile& GlobalObjectScript::GetFile() const
    {
        return static_cast<const InstanceTraits::GlobalObjectScript&>(GetTraits()).GetFile();
    }

    inline
    const Abc::ScriptInfo& GlobalObjectScript::GetScript() const
    {
        return static_cast<const InstanceTraits::GlobalObjectScript&>(GetTraits()).GetScript();
    }
}

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif // INC_AS3_Obj_Global_H
