//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_QName.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_QName_H
#define INC_AS3_Obj_QName_H

#include "AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class QName;
}

namespace InstanceTraits
{
    class QName;
}

namespace Classes
{
    class QName;
}

namespace Instances
{
    class QName : public Instances::Object
    {
        friend class InstanceTraits::QName;
        
    public:
        typedef QName SelfType;
        typedef Classes::QName ClassType;
        typedef InstanceTraits::QName TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::QName"; }
#endif
    protected:
        QName(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;

        const Value& GetUri() const
        {
            return Uri;
        }
        
        ASString MakeStringInternal() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_localNameGet, 
            mid_uriGet, 
            mid_AS3valueOf, 
            mid_AS3toString, 
            mid_toStringProto, 
        };
        void localNameGet(ASString& result);
        void uriGet(Value& result);
        void AS3valueOf(Value& result);
        void AS3toString(ASString& result);
        static void toStringProto(const ThunkInfo& ti, VM& vm, const Value& _this, Value& result, unsigned argc, const Value* argv);

//##protect##"instance$data"
        ASString    LocalName;
        Value       Uri;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class QName : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::QName"; }
#endif
    public:
        QName(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::QName> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

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
    class QName : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::QName"; }
#endif
    public:
        typedef Classes::QName ClassType;

    public:
        QName(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class QName : public Class
    {
        friend class ClassTraits::QName;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::QName"; }
#endif
    public:
        typedef QName SelfType;
        typedef QName ClassType;
        
    private:
        QName(ClassTraits::Traits& t);
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
        virtual void Construct(Value& _this, unsigned argc, const Value* argv, bool extCall = false);
        virtual void Call(const Value& _this, Value& result, unsigned argc, const Value* const argv);
//##protect##"class_$methods"

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

