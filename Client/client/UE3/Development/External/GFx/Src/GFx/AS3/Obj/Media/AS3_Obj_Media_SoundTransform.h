//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Media_SoundTransform.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Media_SoundTransform_H
#define INC_AS3_Obj_Media_SoundTransform_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SoundTransform;
}

namespace InstanceTraits
{
    class SoundTransform;
}

namespace Classes
{
    class SoundTransform;
}

namespace Instances
{
    class SoundTransform : public Instances::Object
    {
        friend class InstanceTraits::SoundTransform;
        
    public:
        typedef SoundTransform SelfType;
        typedef Classes::SoundTransform ClassType;
        typedef InstanceTraits::SoundTransform TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::SoundTransform"; }
#endif
    protected:
        SoundTransform(InstanceTraits::Traits& t);

//##protect##"instance$methods"
#ifdef GFX_ENABLE_SOUND
        virtual void AS3Constructor(unsigned argc, const Value* argv);
#endif
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_leftToLeftGet, 
            mid_leftToLeftSet, 
            mid_leftToRightGet, 
            mid_leftToRightSet, 
            mid_panGet, 
            mid_panSet, 
            mid_rightToLeftGet, 
            mid_rightToLeftSet, 
            mid_rightToRightGet, 
            mid_rightToRightSet, 
            mid_volumeGet, 
            mid_volumeSet, 
        };
        void leftToLeftGet(Value::Number& result);
        void leftToLeftSet(Value& result, Value::Number value);
        void leftToRightGet(Value::Number& result);
        void leftToRightSet(Value& result, Value::Number value);
        void panGet(Value::Number& result);
        void panSet(Value& result, Value::Number value);
        void rightToLeftGet(Value::Number& result);
        void rightToLeftSet(Value& result, Value::Number value);
        void rightToRightGet(Value::Number& result);
        void rightToRightSet(Value& result, Value::Number value);
        void volumeGet(Value::Number& result);
        void volumeSet(Value& result, Value::Number value);

//##protect##"instance$data"
#ifdef GFX_ENABLE_SOUND
        Value::Number Volume;
        Value::Number Pan;
#endif
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class SoundTransform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::SoundTransform"; }
#endif
    public:
        SoundTransform(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::SoundTransform> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 12 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class SoundTransform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SoundTransform"; }
#endif
    public:
        typedef Classes::SoundTransform ClassType;

    public:
        SoundTransform(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

