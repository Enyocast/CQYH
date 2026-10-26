//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Error.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Error_H
#define INC_AS3_Obj_Error_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Error;
}

namespace InstanceTraits
{
    class Error;
}

namespace Classes
{
    class Error;
}

namespace Instances
{
    class Error : public Instances::Object
    {
        friend class InstanceTraits::Error;
        
    public:
        typedef Error SelfType;
        typedef Classes::Error ClassType;
        typedef InstanceTraits::Error TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Error"; }
#endif
    protected:
        Error(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        Error(InstanceTraits::Traits& t, int id SF_DEBUG_ARG(const ASString& msg));

    public:
        virtual void AS3Constructor(unsigned argc, const Value* argv);

        const ASString& GetMessage() const
        {
            return message;
        }
        const ASString& GetErrorName() const
        {
            return name;
        }
        int GetID() const
        {
            return ID;
        }
        
    private:
        //
        void SetMessage(ASStringNode* id)
        {
            message.AssignNode(id);
        }
        void SetMessage(const ASString& id)
        {
            message = id;
        }
        //
        void SetErrorName(ASStringNode* id)
        {
            name.AssignNode(id);
        }
        void SetErrorName(const ASString& id)
        {
            name = id;
        }
        void SetID(int id)
        {
            ID = id;
        }
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        const ASString& get_message() const { return message; }
        const ASString& get_name() const { return name; }

        // AS3 API methods.
        enum MethodID {
            mid_errorIDGet, 
            mid_getStackTrace, 
            mid_toStringProto, 
        };
        void errorIDGet(SInt32& result);
        void getStackTrace(ASString& result);
        void toStringProto(ASString& result);

    protected:
        // AS3 API members.
        ASString message;
        ASString name;

//##protect##"instance$data"
        int ID;
#ifdef GFX_AS3_VERBOSE
        ASString StackTrace;
#endif
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Error : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Error"; }
#endif
    public:
        Error(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Error> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
        Pickable<Instances::Error> MakeInstance(Traits& t, int id SF_DEBUG_ARG(const ASString& msg))
        {
            return Pickable<Instances::Error>(new(t.Alloc()) Instances::Error(*this, id SF_DEBUG_ARG(msg)));
        }
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Error : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Error"; }
#endif
    public:
        typedef Classes::Error ClassType;

    public:
        Error(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Error : public Class
    {
        friend class ClassTraits::Error;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Error"; }
#endif
    public:
        typedef Error SelfType;
        typedef Error ClassType;
        
    private:
        Error(ClassTraits::Traits& t);
    public:
        virtual void InitPrototype(AS3::Object& obj) const;
        enum { ThunkInfoNum = 1 };
        static const ThunkInfo ti[ThunkInfoNum];
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
        virtual Pickable<AS3::Object> MakePrototype() const;
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_getErrorMessage, 
            mid_throwError, 
        };
        void getErrorMessage(ASString& result, SInt32 index);
        void throwError(Value& result, unsigned argc, const Value* const argv);

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

