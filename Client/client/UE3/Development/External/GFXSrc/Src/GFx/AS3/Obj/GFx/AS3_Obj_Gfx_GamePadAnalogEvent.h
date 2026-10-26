//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_GamePadAnalogEvent.h
Content     :   
Created     :   Jun, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_GamePadAnalogEvent_H
#define INC_AS3_Obj_Gfx_GamePadAnalogEvent_H

#include "../Events/AS3_Obj_Events_Event.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class GamePadAnalogEvent;
}

namespace InstanceTraits
{
    class GamePadAnalogEvent;
}

namespace Classes
{
    class GamePadAnalogEvent;
}

namespace Instances
{
    class GamePadAnalogEvent : public Instances::Event
    {
        friend class InstanceTraits::GamePadAnalogEvent;
        
    public:
        typedef GamePadAnalogEvent SelfType;
        typedef Classes::GamePadAnalogEvent ClassType;
        typedef InstanceTraits::GamePadAnalogEvent TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::GamePadAnalogEvent"; }
#endif
    protected:
        GamePadAnalogEvent(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
        virtual AS3::Object* GetEventClass() const;
        virtual SPtr<Instances::Event> Clone() const;
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_codeGet, 
            mid_codeSet, 
            mid_controllerIdxGet, 
            mid_controllerIdxSet, 
            mid_xvalueGet, 
            mid_xvalueSet, 
            mid_yvalueGet, 
            mid_yvalueSet, 
            mid_clone, 
            mid_toString, 
        };
        void codeGet(UInt32& result);
        void codeSet(Value& result, UInt32 value);
        void controllerIdxGet(UInt32& result);
        void controllerIdxSet(Value& result, UInt32 value);
        void xvalueGet(Value::Number& result);
        void xvalueSet(Value& result, Value::Number value);
        void yvalueGet(Value::Number& result);
        void yvalueSet(Value& result, Value::Number value);
        void clone(Value& result);
        void toString(ASString& result);

//##protect##"instance$data"
    public:
        UInt32  Code;
        UInt32  ControllerIdx;
        Double  XValue, YValue;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class GamePadAnalogEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::GamePadAnalogEvent"; }
#endif
    public:
        GamePadAnalogEvent(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::GamePadAnalogEvent> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 10 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class GamePadAnalogEvent : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::GamePadAnalogEvent"; }
#endif
    public:
        typedef Classes::GamePadAnalogEvent ClassType;

    public:
        GamePadAnalogEvent(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 1 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class GamePadAnalogEvent : public Class
    {
        friend class ClassTraits::GamePadAnalogEvent;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::GamePadAnalogEvent"; }
#endif
    public:
        typedef GamePadAnalogEvent SelfType;
        typedef GamePadAnalogEvent ClassType;
        
    private:
        GamePadAnalogEvent(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        const char* get_CHANGE() const { return CHANGE; }


    protected:
        // AS3 API members.
        const char* CHANGE;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

