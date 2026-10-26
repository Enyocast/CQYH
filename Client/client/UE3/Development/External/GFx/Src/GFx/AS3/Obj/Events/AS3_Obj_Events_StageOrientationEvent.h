//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Events_StageOrientationEvent.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Events_StageOrientationEvent_H
#define INC_AS3_Obj_Events_StageOrientationEvent_H

#include "AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class StageOrientationEvent;
}

namespace InstanceTraits
{
    class StageOrientationEvent;
}

namespace Classes
{
    class StageOrientationEvent;
}

namespace Instances
{
    class StageOrientationEvent : public Instances::Event
    {
        friend class InstanceTraits::StageOrientationEvent;
        
    public:
        typedef StageOrientationEvent SelfType;
        typedef Classes::StageOrientationEvent ClassType;
        typedef InstanceTraits::StageOrientationEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::StageOrientationEvent"; }
#endif
    protected:
        StageOrientationEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void ForEachChild_GC(Collector* prcc, GcOp op) const;
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_afterOrientationGet, 
            mid_beforeOrientationGet, 
            mid_clone, 
            mid_toString, 
        };
        void afterOrientationGet(Value& result);
        void beforeOrientationGet(Value& result);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
        Value BeforeOrientation;
        Value AfterOrientation;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class StageOrientationEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::StageOrientationEvent"; }
#endif
    public:
        StageOrientationEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::StageOrientationEvent> MakeInstance(Traits& t);

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
    class StageOrientationEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::StageOrientationEvent"; }
#endif
    public:
        typedef Classes::StageOrientationEvent ClassType;

    public:
        StageOrientationEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 2 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class StageOrientationEvent : public Class
    {
        friend class ClassTraits::StageOrientationEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::StageOrientationEvent"; }
#endif
    public:
        typedef StageOrientationEvent SelfType;
        typedef StageOrientationEvent ClassType;
        
    private:
        StageOrientationEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_ORIENTATION_CHANGE() const { return ORIENTATION_CHANGE; }
        const char* get_ORIENTATION_CHANGING() const { return ORIENTATION_CHANGING; }


    protected:
        // AS3 API members.
        const char* ORIENTATION_CHANGE;
        const char* ORIENTATION_CHANGING;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

