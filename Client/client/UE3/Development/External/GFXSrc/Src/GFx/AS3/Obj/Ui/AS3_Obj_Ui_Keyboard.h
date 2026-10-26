//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_Keyboard.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Ui_Keyboard_H
#define INC_AS3_Obj_Ui_Keyboard_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
#ifdef ALTERNATE
#undef ALTERNATE
#endif

#ifdef DELETE
#undef DELETE
#endif
//##protect##"forward_declaration"

namespace ClassTraits
{
    class Keyboard;
}

namespace InstanceTraits
{
    class Keyboard;
}

namespace Classes
{
    class Keyboard;
}
    
namespace ClassTraits
{
    class Keyboard : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::Keyboard"; }
#endif
    public:
        typedef Classes::Keyboard ClassType;

    public:
        Keyboard(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { MemberInfoNum = 244 };
        static const MemberInfo mi[MemberInfoNum];
        enum { ThunkInfoNum = 3 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class Keyboard : public Class
    {
        friend class ClassTraits::Keyboard;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::Keyboard"; }
#endif
    public:
        typedef Keyboard SelfType;
        typedef Keyboard ClassType;
        
    private:
        Keyboard(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
//##protect##"class_$methods"

    public:
        // AS3 API member getters.
        UInt32 get_A() const { return A; }
        UInt32 get_ALTERNATE() const { return ALTERNATE; }
        UInt32 get_B() const { return B; }
        UInt32 get_BACKQUOTE() const { return BACKQUOTE; }
        UInt32 get_BACKSLASH() const { return BACKSLASH; }
        UInt32 get_BACKSPACE() const { return BACKSPACE; }
        UInt32 get_C() const { return C; }
        UInt32 get_CAPS_LOCK() const { return CAPS_LOCK; }
        Instances::Array* get_CharCodeStrings() const { return CharCodeStrings; }
        UInt32 get_COMMA() const { return COMMA; }
        UInt32 get_COMMAND() const { return COMMAND; }
        UInt32 get_CONTROL() const { return CONTROL; }
        UInt32 get_D() const { return D; }
        UInt32 get_DELETE() const { return DELETE; }
        UInt32 get_DOWN() const { return DOWN; }
        UInt32 get_E() const { return E; }
        UInt32 get_END() const { return END; }
        UInt32 get_ENTER() const { return ENTER; }
        UInt32 get_EQUAL() const { return EQUAL; }
        UInt32 get_ESCAPE() const { return ESCAPE; }
        UInt32 get_F() const { return F; }
        UInt32 get_F1() const { return F1; }
        UInt32 get_F10() const { return F10; }
        UInt32 get_F11() const { return F11; }
        UInt32 get_F12() const { return F12; }
        UInt32 get_F13() const { return F13; }
        UInt32 get_F14() const { return F14; }
        UInt32 get_F15() const { return F15; }
        UInt32 get_F2() const { return F2; }
        UInt32 get_F3() const { return F3; }
        UInt32 get_F4() const { return F4; }
        UInt32 get_F5() const { return F5; }
        UInt32 get_F6() const { return F6; }
        UInt32 get_F7() const { return F7; }
        UInt32 get_F8() const { return F8; }
        UInt32 get_F9() const { return F9; }
        UInt32 get_G() const { return G; }
        UInt32 get_H() const { return H; }
        UInt32 get_HOME() const { return HOME; }
        UInt32 get_I() const { return I; }
        UInt32 get_INSERT() const { return INSERT; }
        UInt32 get_J() const { return J; }
        UInt32 get_K() const { return K; }
        const char* get_KEYNAME_BEGIN() const { return KEYNAME_BEGIN; }
        const char* get_KEYNAME_BREAK() const { return KEYNAME_BREAK; }
        const char* get_KEYNAME_CLEARDISPLAY() const { return KEYNAME_CLEARDISPLAY; }
        const char* get_KEYNAME_CLEARLINE() const { return KEYNAME_CLEARLINE; }
        const char* get_KEYNAME_DELETE() const { return KEYNAME_DELETE; }
        const char* get_KEYNAME_DELETECHAR() const { return KEYNAME_DELETECHAR; }
        const char* get_KEYNAME_DELETELINE() const { return KEYNAME_DELETELINE; }
        const char* get_KEYNAME_DOWNARROW() const { return KEYNAME_DOWNARROW; }
        const char* get_KEYNAME_END() const { return KEYNAME_END; }
        const char* get_KEYNAME_EXECUTE() const { return KEYNAME_EXECUTE; }
        const char* get_KEYNAME_F1() const { return KEYNAME_F1; }
        const char* get_KEYNAME_F10() const { return KEYNAME_F10; }
        const char* get_KEYNAME_F11() const { return KEYNAME_F11; }
        const char* get_KEYNAME_F12() const { return KEYNAME_F12; }
        const char* get_KEYNAME_F13() const { return KEYNAME_F13; }
        const char* get_KEYNAME_F14() const { return KEYNAME_F14; }
        const char* get_KEYNAME_F15() const { return KEYNAME_F15; }
        const char* get_KEYNAME_F16() const { return KEYNAME_F16; }
        const char* get_KEYNAME_F17() const { return KEYNAME_F17; }
        const char* get_KEYNAME_F18() const { return KEYNAME_F18; }
        const char* get_KEYNAME_F19() const { return KEYNAME_F19; }
        const char* get_KEYNAME_F2() const { return KEYNAME_F2; }
        const char* get_KEYNAME_F20() const { return KEYNAME_F20; }
        const char* get_KEYNAME_F21() const { return KEYNAME_F21; }
        const char* get_KEYNAME_F22() const { return KEYNAME_F22; }
        const char* get_KEYNAME_F23() const { return KEYNAME_F23; }
        const char* get_KEYNAME_F24() const { return KEYNAME_F24; }
        const char* get_KEYNAME_F25() const { return KEYNAME_F25; }
        const char* get_KEYNAME_F26() const { return KEYNAME_F26; }
        const char* get_KEYNAME_F27() const { return KEYNAME_F27; }
        const char* get_KEYNAME_F28() const { return KEYNAME_F28; }
        const char* get_KEYNAME_F29() const { return KEYNAME_F29; }
        const char* get_KEYNAME_F3() const { return KEYNAME_F3; }
        const char* get_KEYNAME_F30() const { return KEYNAME_F30; }
        const char* get_KEYNAME_F31() const { return KEYNAME_F31; }
        const char* get_KEYNAME_F32() const { return KEYNAME_F32; }
        const char* get_KEYNAME_F33() const { return KEYNAME_F33; }
        const char* get_KEYNAME_F34() const { return KEYNAME_F34; }
        const char* get_KEYNAME_F35() const { return KEYNAME_F35; }
        const char* get_KEYNAME_F4() const { return KEYNAME_F4; }
        const char* get_KEYNAME_F5() const { return KEYNAME_F5; }
        const char* get_KEYNAME_F6() const { return KEYNAME_F6; }
        const char* get_KEYNAME_F7() const { return KEYNAME_F7; }
        const char* get_KEYNAME_F8() const { return KEYNAME_F8; }
        const char* get_KEYNAME_F9() const { return KEYNAME_F9; }
        const char* get_KEYNAME_FIND() const { return KEYNAME_FIND; }
        const char* get_KEYNAME_HELP() const { return KEYNAME_HELP; }
        const char* get_KEYNAME_HOME() const { return KEYNAME_HOME; }
        const char* get_KEYNAME_INSERT() const { return KEYNAME_INSERT; }
        const char* get_KEYNAME_INSERTCHAR() const { return KEYNAME_INSERTCHAR; }
        const char* get_KEYNAME_INSERTLINE() const { return KEYNAME_INSERTLINE; }
        const char* get_KEYNAME_LEFTARROW() const { return KEYNAME_LEFTARROW; }
        const char* get_KEYNAME_MENU() const { return KEYNAME_MENU; }
        const char* get_KEYNAME_MODESWITCH() const { return KEYNAME_MODESWITCH; }
        const char* get_KEYNAME_NEXT() const { return KEYNAME_NEXT; }
        const char* get_KEYNAME_PAGEDOWN() const { return KEYNAME_PAGEDOWN; }
        const char* get_KEYNAME_PAGEUP() const { return KEYNAME_PAGEUP; }
        const char* get_KEYNAME_PAUSE() const { return KEYNAME_PAUSE; }
        const char* get_KEYNAME_PREV() const { return KEYNAME_PREV; }
        const char* get_KEYNAME_PRINT() const { return KEYNAME_PRINT; }
        const char* get_KEYNAME_PRINTSCREEN() const { return KEYNAME_PRINTSCREEN; }
        const char* get_KEYNAME_REDO() const { return KEYNAME_REDO; }
        const char* get_KEYNAME_RESET() const { return KEYNAME_RESET; }
        const char* get_KEYNAME_RIGHTARROW() const { return KEYNAME_RIGHTARROW; }
        const char* get_KEYNAME_SCROLLLOCK() const { return KEYNAME_SCROLLLOCK; }
        const char* get_KEYNAME_SELECT() const { return KEYNAME_SELECT; }
        const char* get_KEYNAME_STOP() const { return KEYNAME_STOP; }
        const char* get_KEYNAME_SYSREQ() const { return KEYNAME_SYSREQ; }
        const char* get_KEYNAME_SYSTEM() const { return KEYNAME_SYSTEM; }
        const char* get_KEYNAME_UNDO() const { return KEYNAME_UNDO; }
        const char* get_KEYNAME_UPARROW() const { return KEYNAME_UPARROW; }
        const char* get_KEYNAME_USER() const { return KEYNAME_USER; }
        UInt32 get_L() const { return L; }
        UInt32 get_LEFT() const { return LEFT; }
        UInt32 get_LEFTBRACKET() const { return LEFTBRACKET; }
        UInt32 get_M() const { return M; }
        UInt32 get_MINUS() const { return MINUS; }
        UInt32 get_N() const { return N; }
        UInt32 get_NUMBER_0() const { return NUMBER_0; }
        UInt32 get_NUMBER_1() const { return NUMBER_1; }
        UInt32 get_NUMBER_2() const { return NUMBER_2; }
        UInt32 get_NUMBER_3() const { return NUMBER_3; }
        UInt32 get_NUMBER_4() const { return NUMBER_4; }
        UInt32 get_NUMBER_5() const { return NUMBER_5; }
        UInt32 get_NUMBER_6() const { return NUMBER_6; }
        UInt32 get_NUMBER_7() const { return NUMBER_7; }
        UInt32 get_NUMBER_8() const { return NUMBER_8; }
        UInt32 get_NUMBER_9() const { return NUMBER_9; }
        UInt32 get_NUMPAD() const { return NUMPAD; }
        UInt32 get_NUMPAD_0() const { return NUMPAD_0; }
        UInt32 get_NUMPAD_1() const { return NUMPAD_1; }
        UInt32 get_NUMPAD_2() const { return NUMPAD_2; }
        UInt32 get_NUMPAD_3() const { return NUMPAD_3; }
        UInt32 get_NUMPAD_4() const { return NUMPAD_4; }
        UInt32 get_NUMPAD_5() const { return NUMPAD_5; }
        UInt32 get_NUMPAD_6() const { return NUMPAD_6; }
        UInt32 get_NUMPAD_7() const { return NUMPAD_7; }
        UInt32 get_NUMPAD_8() const { return NUMPAD_8; }
        UInt32 get_NUMPAD_9() const { return NUMPAD_9; }
        UInt32 get_NUMPAD_ADD() const { return NUMPAD_ADD; }
        UInt32 get_NUMPAD_DECIMAL() const { return NUMPAD_DECIMAL; }
        UInt32 get_NUMPAD_DIVIDE() const { return NUMPAD_DIVIDE; }
        UInt32 get_NUMPAD_ENTER() const { return NUMPAD_ENTER; }
        UInt32 get_NUMPAD_MULTIPLY() const { return NUMPAD_MULTIPLY; }
        UInt32 get_NUMPAD_SUBTRACT() const { return NUMPAD_SUBTRACT; }
        UInt32 get_O() const { return O; }
        UInt32 get_P() const { return P; }
        UInt32 get_PAGE_DOWN() const { return PAGE_DOWN; }
        UInt32 get_PAGE_UP() const { return PAGE_UP; }
        UInt32 get_PERIOD() const { return PERIOD; }
        UInt32 get_Q() const { return Q; }
        UInt32 get_QUOTE() const { return QUOTE; }
        UInt32 get_R() const { return R; }
        UInt32 get_RIGHT() const { return RIGHT; }
        UInt32 get_RIGHTBRACKET() const { return RIGHTBRACKET; }
        UInt32 get_S() const { return S; }
        UInt32 get_SEMICOLON() const { return SEMICOLON; }
        UInt32 get_SHIFT() const { return SHIFT; }
        UInt32 get_SLASH() const { return SLASH; }
        UInt32 get_SPACE() const { return SPACE; }
        const char* get_STRING_BEGIN() const { return STRING_BEGIN; }
        const char* get_STRING_BREAK() const { return STRING_BREAK; }
        const char* get_STRING_CLEARDISPLAY() const { return STRING_CLEARDISPLAY; }
        const char* get_STRING_CLEARLINE() const { return STRING_CLEARLINE; }
        const char* get_STRING_DELETE() const { return STRING_DELETE; }
        const char* get_STRING_DELETECHAR() const { return STRING_DELETECHAR; }
        const char* get_STRING_DELETELINE() const { return STRING_DELETELINE; }
        const char* get_STRING_DOWNARROW() const { return STRING_DOWNARROW; }
        const char* get_STRING_END() const { return STRING_END; }
        const char* get_STRING_EXECUTE() const { return STRING_EXECUTE; }
        const char* get_STRING_F1() const { return STRING_F1; }
        const char* get_STRING_F10() const { return STRING_F10; }
        const char* get_STRING_F11() const { return STRING_F11; }
        const char* get_STRING_F12() const { return STRING_F12; }
        const char* get_STRING_F13() const { return STRING_F13; }
        const char* get_STRING_F14() const { return STRING_F14; }
        const char* get_STRING_F15() const { return STRING_F15; }
        const char* get_STRING_F16() const { return STRING_F16; }
        const char* get_STRING_F17() const { return STRING_F17; }
        const char* get_STRING_F18() const { return STRING_F18; }
        const char* get_STRING_F19() const { return STRING_F19; }
        const char* get_STRING_F2() const { return STRING_F2; }
        const char* get_STRING_F20() const { return STRING_F20; }
        const char* get_STRING_F21() const { return STRING_F21; }
        const char* get_STRING_F22() const { return STRING_F22; }
        const char* get_STRING_F23() const { return STRING_F23; }
        const char* get_STRING_F24() const { return STRING_F24; }
        const char* get_STRING_F25() const { return STRING_F25; }
        const char* get_STRING_F26() const { return STRING_F26; }
        const char* get_STRING_F27() const { return STRING_F27; }
        const char* get_STRING_F28() const { return STRING_F28; }
        const char* get_STRING_F29() const { return STRING_F29; }
        const char* get_STRING_F3() const { return STRING_F3; }
        const char* get_STRING_F30() const { return STRING_F30; }
        const char* get_STRING_F31() const { return STRING_F31; }
        const char* get_STRING_F32() const { return STRING_F32; }
        const char* get_STRING_F33() const { return STRING_F33; }
        const char* get_STRING_F34() const { return STRING_F34; }
        const char* get_STRING_F35() const { return STRING_F35; }
        const char* get_STRING_F4() const { return STRING_F4; }
        const char* get_STRING_F5() const { return STRING_F5; }
        const char* get_STRING_F6() const { return STRING_F6; }
        const char* get_STRING_F7() const { return STRING_F7; }
        const char* get_STRING_F8() const { return STRING_F8; }
        const char* get_STRING_F9() const { return STRING_F9; }
        const char* get_STRING_FIND() const { return STRING_FIND; }
        const char* get_STRING_HELP() const { return STRING_HELP; }
        const char* get_STRING_HOME() const { return STRING_HOME; }
        const char* get_STRING_INSERT() const { return STRING_INSERT; }
        const char* get_STRING_INSERTCHAR() const { return STRING_INSERTCHAR; }
        const char* get_STRING_INSERTLINE() const { return STRING_INSERTLINE; }
        const char* get_STRING_LEFTARROW() const { return STRING_LEFTARROW; }
        const char* get_STRING_MENU() const { return STRING_MENU; }
        const char* get_STRING_MODESWITCH() const { return STRING_MODESWITCH; }
        const char* get_STRING_NEXT() const { return STRING_NEXT; }
        const char* get_STRING_PAGEDOWN() const { return STRING_PAGEDOWN; }
        const char* get_STRING_PAGEUP() const { return STRING_PAGEUP; }
        const char* get_STRING_PAUSE() const { return STRING_PAUSE; }
        const char* get_STRING_PREV() const { return STRING_PREV; }
        const char* get_STRING_PRINT() const { return STRING_PRINT; }
        const char* get_STRING_PRINTSCREEN() const { return STRING_PRINTSCREEN; }
        const char* get_STRING_REDO() const { return STRING_REDO; }
        const char* get_STRING_RESET() const { return STRING_RESET; }
        const char* get_STRING_RIGHTARROW() const { return STRING_RIGHTARROW; }
        const char* get_STRING_SCROLLLOCK() const { return STRING_SCROLLLOCK; }
        const char* get_STRING_SELECT() const { return STRING_SELECT; }
        const char* get_STRING_STOP() const { return STRING_STOP; }
        const char* get_STRING_SYSREQ() const { return STRING_SYSREQ; }
        const char* get_STRING_SYSTEM() const { return STRING_SYSTEM; }
        const char* get_STRING_UNDO() const { return STRING_UNDO; }
        const char* get_STRING_UPARROW() const { return STRING_UPARROW; }
        const char* get_STRING_USER() const { return STRING_USER; }
        UInt32 get_T() const { return T; }
        UInt32 get_TAB() const { return TAB; }
        UInt32 get_U() const { return U; }
        UInt32 get_UP() const { return UP; }
        UInt32 get_V() const { return V; }
        UInt32 get_W() const { return W; }
        UInt32 get_X() const { return X; }
        UInt32 get_Y() const { return Y; }
        UInt32 get_Z() const { return Z; }

        // AS3 API methods.
        enum MethodID {
            mid_capsLockGet, 
            mid_numLockGet, 
            mid_isAccessible, 
        };
        void capsLockGet(bool& result);
        void numLockGet(bool& result);
        void isAccessible(bool& result);

    protected:
        // AS3 API members.
        const UInt32 A;
        const UInt32 ALTERNATE;
        const UInt32 B;
        const UInt32 BACKQUOTE;
        const UInt32 BACKSLASH;
        const UInt32 BACKSPACE;
        const UInt32 C;
        const UInt32 CAPS_LOCK;
        SPtr<Instances::Array> CharCodeStrings;
        const UInt32 COMMA;
        const UInt32 COMMAND;
        const UInt32 CONTROL;
        const UInt32 D;
        const UInt32 DELETE;
        const UInt32 DOWN;
        const UInt32 E;
        const UInt32 END;
        const UInt32 ENTER;
        const UInt32 EQUAL;
        const UInt32 ESCAPE;
        const UInt32 F;
        const UInt32 F1;
        const UInt32 F10;
        const UInt32 F11;
        const UInt32 F12;
        const UInt32 F13;
        const UInt32 F14;
        const UInt32 F15;
        const UInt32 F2;
        const UInt32 F3;
        const UInt32 F4;
        const UInt32 F5;
        const UInt32 F6;
        const UInt32 F7;
        const UInt32 F8;
        const UInt32 F9;
        const UInt32 G;
        const UInt32 H;
        const UInt32 HOME;
        const UInt32 I;
        const UInt32 INSERT;
        const UInt32 J;
        const UInt32 K;
        const char* KEYNAME_BEGIN;
        const char* KEYNAME_BREAK;
        const char* KEYNAME_CLEARDISPLAY;
        const char* KEYNAME_CLEARLINE;
        const char* KEYNAME_DELETE;
        const char* KEYNAME_DELETECHAR;
        const char* KEYNAME_DELETELINE;
        const char* KEYNAME_DOWNARROW;
        const char* KEYNAME_END;
        const char* KEYNAME_EXECUTE;
        const char* KEYNAME_F1;
        const char* KEYNAME_F10;
        const char* KEYNAME_F11;
        const char* KEYNAME_F12;
        const char* KEYNAME_F13;
        const char* KEYNAME_F14;
        const char* KEYNAME_F15;
        const char* KEYNAME_F16;
        const char* KEYNAME_F17;
        const char* KEYNAME_F18;
        const char* KEYNAME_F19;
        const char* KEYNAME_F2;
        const char* KEYNAME_F20;
        const char* KEYNAME_F21;
        const char* KEYNAME_F22;
        const char* KEYNAME_F23;
        const char* KEYNAME_F24;
        const char* KEYNAME_F25;
        const char* KEYNAME_F26;
        const char* KEYNAME_F27;
        const char* KEYNAME_F28;
        const char* KEYNAME_F29;
        const char* KEYNAME_F3;
        const char* KEYNAME_F30;
        const char* KEYNAME_F31;
        const char* KEYNAME_F32;
        const char* KEYNAME_F33;
        const char* KEYNAME_F34;
        const char* KEYNAME_F35;
        const char* KEYNAME_F4;
        const char* KEYNAME_F5;
        const char* KEYNAME_F6;
        const char* KEYNAME_F7;
        const char* KEYNAME_F8;
        const char* KEYNAME_F9;
        const char* KEYNAME_FIND;
        const char* KEYNAME_HELP;
        const char* KEYNAME_HOME;
        const char* KEYNAME_INSERT;
        const char* KEYNAME_INSERTCHAR;
        const char* KEYNAME_INSERTLINE;
        const char* KEYNAME_LEFTARROW;
        const char* KEYNAME_MENU;
        const char* KEYNAME_MODESWITCH;
        const char* KEYNAME_NEXT;
        const char* KEYNAME_PAGEDOWN;
        const char* KEYNAME_PAGEUP;
        const char* KEYNAME_PAUSE;
        const char* KEYNAME_PREV;
        const char* KEYNAME_PRINT;
        const char* KEYNAME_PRINTSCREEN;
        const char* KEYNAME_REDO;
        const char* KEYNAME_RESET;
        const char* KEYNAME_RIGHTARROW;
        const char* KEYNAME_SCROLLLOCK;
        const char* KEYNAME_SELECT;
        const char* KEYNAME_STOP;
        const char* KEYNAME_SYSREQ;
        const char* KEYNAME_SYSTEM;
        const char* KEYNAME_UNDO;
        const char* KEYNAME_UPARROW;
        const char* KEYNAME_USER;
        const UInt32 L;
        const UInt32 LEFT;
        const UInt32 LEFTBRACKET;
        const UInt32 M;
        const UInt32 MINUS;
        const UInt32 N;
        const UInt32 NUMBER_0;
        const UInt32 NUMBER_1;
        const UInt32 NUMBER_2;
        const UInt32 NUMBER_3;
        const UInt32 NUMBER_4;
        const UInt32 NUMBER_5;
        const UInt32 NUMBER_6;
        const UInt32 NUMBER_7;
        const UInt32 NUMBER_8;
        const UInt32 NUMBER_9;
        const UInt32 NUMPAD;
        const UInt32 NUMPAD_0;
        const UInt32 NUMPAD_1;
        const UInt32 NUMPAD_2;
        const UInt32 NUMPAD_3;
        const UInt32 NUMPAD_4;
        const UInt32 NUMPAD_5;
        const UInt32 NUMPAD_6;
        const UInt32 NUMPAD_7;
        const UInt32 NUMPAD_8;
        const UInt32 NUMPAD_9;
        const UInt32 NUMPAD_ADD;
        const UInt32 NUMPAD_DECIMAL;
        const UInt32 NUMPAD_DIVIDE;
        const UInt32 NUMPAD_ENTER;
        const UInt32 NUMPAD_MULTIPLY;
        const UInt32 NUMPAD_SUBTRACT;
        const UInt32 O;
        const UInt32 P;
        const UInt32 PAGE_DOWN;
        const UInt32 PAGE_UP;
        const UInt32 PERIOD;
        const UInt32 Q;
        const UInt32 QUOTE;
        const UInt32 R;
        const UInt32 RIGHT;
        const UInt32 RIGHTBRACKET;
        const UInt32 S;
        const UInt32 SEMICOLON;
        const UInt32 SHIFT;
        const UInt32 SLASH;
        const UInt32 SPACE;
        const char* STRING_BEGIN;
        const char* STRING_BREAK;
        const char* STRING_CLEARDISPLAY;
        const char* STRING_CLEARLINE;
        const char* STRING_DELETE;
        const char* STRING_DELETECHAR;
        const char* STRING_DELETELINE;
        const char* STRING_DOWNARROW;
        const char* STRING_END;
        const char* STRING_EXECUTE;
        const char* STRING_F1;
        const char* STRING_F10;
        const char* STRING_F11;
        const char* STRING_F12;
        const char* STRING_F13;
        const char* STRING_F14;
        const char* STRING_F15;
        const char* STRING_F16;
        const char* STRING_F17;
        const char* STRING_F18;
        const char* STRING_F19;
        const char* STRING_F2;
        const char* STRING_F20;
        const char* STRING_F21;
        const char* STRING_F22;
        const char* STRING_F23;
        const char* STRING_F24;
        const char* STRING_F25;
        const char* STRING_F26;
        const char* STRING_F27;
        const char* STRING_F28;
        const char* STRING_F29;
        const char* STRING_F3;
        const char* STRING_F30;
        const char* STRING_F31;
        const char* STRING_F32;
        const char* STRING_F33;
        const char* STRING_F34;
        const char* STRING_F35;
        const char* STRING_F4;
        const char* STRING_F5;
        const char* STRING_F6;
        const char* STRING_F7;
        const char* STRING_F8;
        const char* STRING_F9;
        const char* STRING_FIND;
        const char* STRING_HELP;
        const char* STRING_HOME;
        const char* STRING_INSERT;
        const char* STRING_INSERTCHAR;
        const char* STRING_INSERTLINE;
        const char* STRING_LEFTARROW;
        const char* STRING_MENU;
        const char* STRING_MODESWITCH;
        const char* STRING_NEXT;
        const char* STRING_PAGEDOWN;
        const char* STRING_PAGEUP;
        const char* STRING_PAUSE;
        const char* STRING_PREV;
        const char* STRING_PRINT;
        const char* STRING_PRINTSCREEN;
        const char* STRING_REDO;
        const char* STRING_RESET;
        const char* STRING_RIGHTARROW;
        const char* STRING_SCROLLLOCK;
        const char* STRING_SELECT;
        const char* STRING_STOP;
        const char* STRING_SYSREQ;
        const char* STRING_SYSTEM;
        const char* STRING_UNDO;
        const char* STRING_UPARROW;
        const char* STRING_USER;
        const UInt32 T;
        const UInt32 TAB;
        const UInt32 U;
        const UInt32 UP;
        const UInt32 V;
        const UInt32 W;
        const UInt32 X;
        const UInt32 Y;
        const UInt32 Z;

//##protect##"class_$data"
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

