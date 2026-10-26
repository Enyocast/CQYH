//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Text_TextSnapshot.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Text_TextSnapshot_H
#define INC_AS3_Obj_Text_TextSnapshot_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
#include "GFx/GFx_Sprite.h"
#include "GFx/GFx_StaticText.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class TextSnapshot;
}

namespace InstanceTraits
{
    class TextSnapshot;
}

namespace Classes
{
    class TextSnapshot;
}

namespace Instances
{
    class TextSnapshot : public Instances::Object
    {
        friend class InstanceTraits::TextSnapshot;
        
    public:
        typedef TextSnapshot SelfType;
        typedef Classes::TextSnapshot ClassType;
        typedef InstanceTraits::TextSnapshot TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::TextSnapshot"; }
#endif
    protected:
        TextSnapshot(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT
        void                    ProcessSnapshot(Sprite* sprite) { sprite->GetTextSnapshot(&SnapshotData); }
        StaticTextSnapshotData& GetSnapshotData() { return SnapshotData; }
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_charCountGet, 
            mid_findText, 
            mid_getSelected, 
            mid_getSelectedText, 
            mid_getText, 
            mid_getTextRunInfo, 
            mid_hitTestTextNearPos, 
            mid_setSelectColor, 
            mid_setSelected, 
        };
        void charCountGet(SInt32& result);
        void findText(SInt32& result, SInt32 beginIndex, const ASString& textToFind, bool caseSensitive);
        void getSelected(bool& result, SInt32 beginIndex, SInt32 endIndex);
        void getSelectedText(ASString& result, bool includeLineEndings);
        void getText(ASString& result, SInt32 beginIndex, SInt32 endIndex, bool includeLineEndings);
        void getTextRunInfo(Value& result, SInt32 beginIndex, SInt32 endIndex);
        void hitTestTextNearPos(Value::Number& result, Value::Number x, Value::Number y, Value::Number maxDistance);
        void setSelectColor(Value& result, UInt32 hexColor);
        void setSelected(Value& result, SInt32 beginIndex, SInt32 endIndex, bool select);

//##protect##"instance$data"
    protected:
#ifdef GFX_AS_ENABLE_TEXTSNAPSHOT
        StaticTextSnapshotData SnapshotData;
#endif // GFX_AS_ENABLE_TEXTSNAPSHOT
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class TextSnapshot : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::TextSnapshot"; }
#endif
    public:
        TextSnapshot(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::TextSnapshot> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 9 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class TextSnapshot : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::TextSnapshot"; }
#endif
    public:
        typedef Classes::TextSnapshot ClassType;

    public:
        TextSnapshot(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

