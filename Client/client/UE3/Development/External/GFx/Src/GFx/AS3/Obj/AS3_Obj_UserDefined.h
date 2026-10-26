/**************************************************************************

Filename    :   AS3_Obj_UserDefined.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
#ifndef INC_AS3_Obj_UserDefined_H
#define INC_AS3_Obj_UserDefined_H

//#include "AS3_Obj_Object.h"
#include "../AS3_UDBase.h"

namespace Scaleform { namespace GFx { namespace AS3 
{
    
namespace InstanceTraits
{
    class UserDefined : public UDBase
    {
        friend class Instances::GlobalObjectScript; // Because of SetScript().

    public:
        UserDefined(VMAbcFile& file, const Traits* pt, const Abc::ClassInfo& info);

    public:
        virtual void AS3Constructor(const AS3::Traits& ot, const Value& _this, unsigned argc, const Value* argv) const;
        // Determines whether these traits implement the specified interface class.        
        virtual bool SupportsInterface(const Traits&) const;
        virtual VMAbcFile* GetFilePtr() const;
        
    public:
        virtual CheckResult PreInit(const Value& _this) const;
        virtual void PostInit(const Value& _this, unsigned argc, const Value* argv) const;

    public:
        // Set up values of slots ...
        virtual CheckResult SetupSlotValues(AS3::Object& for_obj) const;
        virtual void InitOnDemand() const;

        VMAbcFile& GetFile() const;
        bool HasScriptSetUp() const
        {
            return (Script.GetPtr() != NULL);
        }
        Instances::GlobalObjectScript& GetScript() const
        {
            SF_ASSERT(HasScriptSetUp());
            return *Script;
        }
        const Abc::ClassInfo& GetClassInfo() const { return class_info; }

    private:
        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;

        void SetScript(Instances::GlobalObjectScript& script);

    private:
        UserDefined& operator =(const UserDefined&);

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::UserDefined"; }
#endif
    private:
        SPtr<Instances::GlobalObjectScript> Script;
        const Abc::ClassInfo& class_info;
    };
    
} // namespace InstanceTraits

namespace Classes
{
    class UserDefined;
}

namespace ClassTraits
{
    class UserDefined : public Traits
    {
    public:
        // This constructor doesn't set parent traits to prevent troubles 
        // related to recursive dependencies.
        UserDefined(VMAbcFile& file, VM& vm, const Abc::ClassInfo& info);
        ~UserDefined();

    public:
        virtual VMAbcFile* GetFilePtr() const;

        Pickable<Classes::UserDefined> MakeClass();

        virtual unsigned GetFixedMemSize() const;
        virtual void ForEachChild_GC(Collector* prcc, RefCountBaseGC<Mem_Stat>::GcOp op) const;

    public:
        // We MAY NOT register slots in the constructor because of possible recursion.
        // Traits have to be registered first and filled up with slots after that.
        // Can throw exceptions.
        CheckResult RegisterSlots();

        // Set up values of slots ...
        virtual CheckResult SetupSlotValues(AS3::Object& for_obj) const;
        VMAbcFile& GetFile() const { return *File; }
        const Abc::ClassInfo& GetClassInfo() const { return class_info; }

        CheckResult Initialize();

    private:
        // Can throw exceptions.
        static const Traits* GetSuperClassTraits(VMAbcFile& file, const Abc::ClassInfo& info);

    private:
        UserDefined& operator =(const UserDefined&);

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::UserDefined"; }
#endif
    private:
        SPtr<VMAbcFile> File;
        // We cannot get rid of the class_info member.
        // class_info from InstanceTraits cannot be used because InstanceTraits are not alway available.
        const Abc::ClassInfo& class_info;
    };

} // namespace ClassTraits

namespace Classes
{
    class UserDefined : public UDBase
    {
        friend class ClassTraits::UserDefined; // Because of CallStaticConstructor().

    public:
        typedef UserDefined Self;
        
    public:
        UserDefined(ClassTraits::UserDefined& t);
        virtual ~UserDefined();

        // Placement new/delete.
        SF_MEMORY_DEFINE_PLACEMENT_NEW
        void  operator delete (void* ptr) { SF_FREE(ptr); }
        
    public:
        VMAbcFile& GetFile() const
        {
            return static_cast<const ClassTraits::UserDefined&>(GetClassTraits()).GetFile();
        }
        const Abc::ClassInfo& GetClassInfo() const
        {
            return static_cast<const ClassTraits::UserDefined&>(GetClassTraits()).GetClassInfo();
        }

    public:
        virtual void PostInit(const Value& _this, unsigned argc, const Value* argv) const;

    private:
        Self& GetSelf()
        {
            return *this;
        }
        void CallStaticConstructor();
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::UserDefined"; }
        virtual Scaleform::String GetAS3ObjectName() const { return Scaleform::String(GetTraits().GetQualifiedName().ToCStr()); }
#endif
    };
    
} // namespace Classes

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif // INC_AS3_Obj_UserDefined_H
