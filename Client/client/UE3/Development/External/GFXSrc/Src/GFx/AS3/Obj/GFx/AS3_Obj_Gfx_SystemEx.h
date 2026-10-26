//##protect##"disclaimer"
/**********************************************************************

Filename    :   AS3_Obj_Gfx_SystemEx.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**********************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_SystemEx_H
#define INC_AS3_Obj_Gfx_SystemEx_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class SystemEx;
}

namespace InstanceTraits
{
    class SystemEx;
}

namespace Classes
{
    class SystemEx;
}
    
namespace ClassTraits
{
    class SystemEx : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::SystemEx"; }
#endif
    public:
        typedef Classes::SystemEx ClassType;

    public:
        SystemEx(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 4 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 8 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class SystemEx : public Class
    {
        friend class ClassTraits::SystemEx;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::SystemEx"; }
#endif
    public:
        typedef SystemEx SelfType;
        typedef SystemEx ClassType;
        
    private:
        SystemEx(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_REPORT_SHORT_FILENAMES() const { return REPORT_SHORT_FILENAMES; }
        UInt32 get_REPORT_NO_CIRCULAR_REFERENCES() const { return REPORT_NO_CIRCULAR_REFERENCES; }
        UInt32 get_REPORT_SUPPRESS_OVERALL_STATS() const { return REPORT_SUPPRESS_OVERALL_STATS; }
        UInt32 get_REPORT_ONLY_ANON_OBJ_ADDRESSES() const { return REPORT_ONLY_ANON_OBJ_ADDRESSES; }

        // AS3 API methods.
        enum MethodID {
            mid_actionVerboseSet, 
            mid_actionVerboseGet, 
            mid_setBackgroundAlpha, 
            mid_getStackTrace, 
            mid_getCodeFileName, 
            mid_getCodeFileNames, 
            mid_describeType, 
            mid_printObjectsReport, 
        };
        void actionVerboseSet(Value& result, bool verbose);
        void actionVerboseGet(bool& result);
        void setBackgroundAlpha(Value& result, Value::Number value);
        void getStackTrace(ASString& result);
        void getCodeFileName(ASString& result);
        void getCodeFileNames(Value& result);
        void describeType(ASString& result, const Value& v);
        void printObjectsReport(Value& result, bool runGarbageCollector, UInt32 reportFlags, const ASString& swfFilter);

    protected:
        // AS3 API members.
        const UInt32 REPORT_SHORT_FILENAMES;
        const UInt32 REPORT_NO_CIRCULAR_REFERENCES;
        const UInt32 REPORT_SUPPRESS_OVERALL_STATS;
        const UInt32 REPORT_ONLY_ANON_OBJ_ADDRESSES;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

