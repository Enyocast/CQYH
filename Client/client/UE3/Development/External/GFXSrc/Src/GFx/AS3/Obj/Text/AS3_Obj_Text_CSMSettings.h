//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_CSMSettings.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_CSMSettings_H
#define INC_AS3_Obj_Text_CSMSettings_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class CSMSettings;
}

namespace InstanceTraits
{
    class CSMSettings;
}

namespace Classes
{
    class CSMSettings;
}

namespace Instances
{
    class CSMSettings : public Instances::Object
    {
        friend class InstanceTraits::CSMSettings;
        
    public:
        typedef CSMSettings SelfType;
        typedef Classes::CSMSettings ClassType;
        typedef InstanceTraits::CSMSettings TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::CSMSettings"; }
#endif
    protected:
        CSMSettings(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        Value::Number get_fontSize() const { return fontSize; }
        Value::Number get_insideCutoff() const { return insideCutoff; }
        Value::Number get_outsideCutoff() const { return outsideCutoff; }


    protected:
        // AS3 API members.
        Value::Number fontSize;
        Value::Number insideCutoff;
        Value::Number outsideCutoff;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class CSMSettings : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::CSMSettings"; }
#endif
    public:
        CSMSettings(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::CSMSettings> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 3 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class CSMSettings : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::CSMSettings"; }
#endif
    public:
        typedef Classes::CSMSettings ClassType;

    public:
        CSMSettings(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

