//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextLineMetrics.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextLineMetrics_H
#define INC_AS3_Obj_Text_TextLineMetrics_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextLineMetrics;
}

namespace InstanceTraits
{
    class TextLineMetrics;
}

namespace Classes
{
    class TextLineMetrics;
}

namespace Instances
{
    class TextLineMetrics : public Instances::Object
    {
        friend class InstanceTraits::TextLineMetrics;
        
    public:
        typedef TextLineMetrics SelfType;
        typedef Classes::TextLineMetrics ClassType;
        typedef InstanceTraits::TextLineMetrics TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextLineMetrics"; }
#endif
    protected:
        TextLineMetrics(InstanceTraits::Traits& t);

//##protect##"instance$methods"
        virtual void AS3Constructor(unsigned argc, const Value* argv);
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_ascent() const { return ascent; }
        Value::Number get_descent() const { return descent; }
        Value::Number get_height() const { return height; }
        Value::Number get_leading() const { return leading; }
        Value::Number get_width() const { return width; }
        Value::Number get_x() const { return x; }


    protected:
        // AS3 API members.
        Value::Number ascent;
        Value::Number descent;
        Value::Number height;
        Value::Number leading;
        Value::Number width;
        Value::Number x;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TextLineMetrics : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextLineMetrics"; }
#endif
    public:
        TextLineMetrics(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextLineMetrics> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 6 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TextLineMetrics : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextLineMetrics"; }
#endif
    public:
        typedef Classes::TextLineMetrics ClassType;

    public:
        TextLineMetrics(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

