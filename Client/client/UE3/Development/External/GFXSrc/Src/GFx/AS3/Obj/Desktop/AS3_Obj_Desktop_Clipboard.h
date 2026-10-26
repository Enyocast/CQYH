//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Desktop_Clipboard.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Desktop_Clipboard_H
#define INC_AS3_Obj_Desktop_Clipboard_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Clipboard;
}

namespace InstanceTraits
{
    class Clipboard;
}

namespace Classes
{
    class Clipboard;
}

namespace Instances
{
    class Clipboard : public Instances::Object
    {
        friend class InstanceTraits::Clipboard;
        
    public:
        typedef Clipboard SelfType;
        typedef Classes::Clipboard ClassType;
        typedef InstanceTraits::Clipboard TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::Clipboard"; }
#endif
    protected:
        Clipboard(InstanceTraits::Traits& t);

//##protect##"instance$methods"
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_formatsGet, 
            mid_clear, 
            mid_clearData, 
            mid_getData, 
            mid_hasFormat, 
            mid_setData, 
            mid_setDataHandler, 
        };
        void formatsGet(Value& result);
        void clear(Value& result);
        void clearData(Value& result, const ASString& format);
        void getData(Value& result, const ASString& format, const ASString& transferMode);
        void hasFormat(bool& result, const ASString& format);
        void setData(bool& result, const ASString& format, const Value& data, bool serializable);
        void setDataHandler(bool& result, const ASString& format, const Value& handler, bool serializable);

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class Clipboard : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::Clipboard"; }
#endif
    public:
        Clipboard(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::Clipboard> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 7 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class Clipboard : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Clipboard"; }
#endif
    public:
        typedef Classes::Clipboard ClassType;

    public:
        Clipboard(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

