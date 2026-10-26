//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Gfx_IMECandidateListStyle.h
Content     :   
Created     :   Jan, 2011
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Gfx_IMECandidateListStyle_H
#define INC_AS3_Obj_Gfx_IMECandidateListStyle_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class IMECandidateListStyle;
}

namespace InstanceTraits
{
    class IMECandidateListStyle;
}

namespace Classes
{
    class IMECandidateListStyle;
}

namespace Instances
{
    class IMECandidateListStyle : public Instances::Object
    {
        friend class InstanceTraits::IMECandidateListStyle;
        
    public:
        typedef IMECandidateListStyle SelfType;
        typedef Classes::IMECandidateListStyle ClassType;
        typedef InstanceTraits::IMECandidateListStyle TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::IMECandidateListStyle"; }
#endif
    protected:
        IMECandidateListStyle(InstanceTraits::Traits& t);

//##protect##"instance$methods"
	public:
		inline void set_textColor(SInt32 _textColor) {textColor = _textColor; }
		inline void set_selectedTextColor(SInt32 _selectedTextColor) {selectedTextColor = _selectedTextColor; }
		inline void set_fontSize(SInt32 _fontSize) { fontSize = _fontSize; }
		inline void set_backgroundColor(SInt32 _bcColor) { backgroundColor = _bcColor; }
		inline void set_selectedBackgroundColor(SInt32 _bcColor) { selectedBackgroundColor = _bcColor; }
		inline void set_indexBackgroundColor(SInt32 _indexBkColor) { indexBackgroundColor = _indexBkColor; }
		inline void set_selectedIndexBackgroundColor(SInt32 _selectedIndexBkColor) { selectedIndexBackgroundColor = _selectedIndexBkColor; }
		inline void set_readingWindowTextColor(SInt32 _readingWindowTxtColor) { readingWindowTextColor = _readingWindowTxtColor; }
		inline void set_readinwWindowBackgroundColor(SInt32 _readingWindowBkColor) { readingWindowBackgroundColor = _readingWindowBkColor; }
		inline void set_readingWindowFontSize(SInt32 _readingWindowFontSize) { readingWindowFontSize = _readingWindowFontSize; }

//##protect##"instance$methods"

    public:
        // AS3 API member getters.
        SInt32 get_textColor() const { return textColor; }
        SInt32 get_selectedTextColor() const { return selectedTextColor; }
        SInt32 get_fontSize() const { return fontSize; }
        SInt32 get_backgroundColor() const { return backgroundColor; }
        SInt32 get_selectedBackgroundColor() const { return selectedBackgroundColor; }
        SInt32 get_indexBackgroundColor() const { return indexBackgroundColor; }
        SInt32 get_selectedIndexBackgroundColor() const { return selectedIndexBackgroundColor; }
        SInt32 get_readingWindowTextColor() const { return readingWindowTextColor; }
        SInt32 get_readingWindowBackgroundColor() const { return readingWindowBackgroundColor; }
        SInt32 get_readingWindowFontSize() const { return readingWindowFontSize; }


    protected:
        // AS3 API members.
        SInt32 textColor;
        SInt32 selectedTextColor;
        SInt32 fontSize;
        SInt32 backgroundColor;
        SInt32 selectedBackgroundColor;
        SInt32 indexBackgroundColor;
        SInt32 selectedIndexBackgroundColor;
        SInt32 readingWindowTextColor;
        SInt32 readingWindowBackgroundColor;
        SInt32 readingWindowFontSize;

//##protect##"instance$data"
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class IMECandidateListStyle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::IMECandidateListStyle"; }
#endif
    public:
        IMECandidateListStyle(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::IMECandidateListStyle> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { MemberInfoNum = 10 };
        static const MemberInfo mi[MemberInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class IMECandidateListStyle : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::IMECandidateListStyle"; }
#endif
    public:
        typedef Classes::IMECandidateListStyle ClassType;

    public:
        IMECandidateListStyle(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}
//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

