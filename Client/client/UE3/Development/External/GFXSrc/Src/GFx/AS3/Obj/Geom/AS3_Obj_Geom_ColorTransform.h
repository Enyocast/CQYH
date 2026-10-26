//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Geom_ColorTransform.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Geom_ColorTransform_H
#define INC_AS3_Obj_Geom_ColorTransform_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ColorTransform;
}

namespace InstanceTraits
{
    class ColorTransform;
}

namespace Classes
{
    class ColorTransform;
}

namespace Instances
{
    class ColorTransform : public Instances::Object
    {
        friend class InstanceTraits::ColorTransform;
        
    public:
        typedef ColorTransform SelfType;
        typedef Classes::ColorTransform ClassType;
        typedef InstanceTraits::ColorTransform TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ColorTransform"; }
#endif
    protected:
        ColorTransform(InstanceTraits::Traits& t);

//##protect##"instance$methods"
		virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_alphaMultiplier() const { return alphaMultiplier; }
        Value::Number get_alphaOffset() const { return alphaOffset; }
        Value::Number get_blueMultiplier() const { return blueMultiplier; }
        Value::Number get_blueOffset() const { return blueOffset; }
        Value::Number get_greenMultiplier() const { return greenMultiplier; }
        Value::Number get_greenOffset() const { return greenOffset; }
        Value::Number get_redMultiplier() const { return redMultiplier; }
        Value::Number get_redOffset() const { return redOffset; }

        // AS3 API methods.
        enum MethodID {
            mid_colorGet, 
            mid_colorSet, 
            mid_concat, 
            mid_toString, 
        };
        void colorGet(UInt32& result);
        void colorSet(Value& result, UInt32 value);
        void concat(Value& result, Instances::ColorTransform* second);
        void toString(ASString& result);

    protected:
        // AS3 API members.
        Value::Number alphaMultiplier;
        Value::Number alphaOffset;
        Value::Number blueMultiplier;
        Value::Number blueOffset;
        Value::Number greenMultiplier;
        Value::Number greenOffset;
        Value::Number redMultiplier;
        Value::Number redOffset;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ColorTransform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ColorTransform"; }
#endif
    public:
        ColorTransform(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ColorTransform> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 8 };
        static const MemberInfo mi[MemberInfoNum];
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
    class ColorTransform : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ColorTransform"; }
#endif
    public:
        typedef Classes::ColorTransform ClassType;

    public:
        ColorTransform(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

