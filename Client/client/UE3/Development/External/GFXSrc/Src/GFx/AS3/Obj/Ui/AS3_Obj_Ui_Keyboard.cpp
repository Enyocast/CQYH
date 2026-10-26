//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Ui_Keyboard.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Ui_Keyboard.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include "../AS3_Obj_Array.h"
#include "GFx/AS3/AS3_MovieRoot.h"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"
//##protect##"methods"

namespace Classes
{
    Keyboard::Keyboard(ClassTraits::Traits& t)
    : Class(t)
    , A(65)
    , ALTERNATE(18)
    , B(66)
    , BACKQUOTE(192)
    , BACKSLASH(220)
    , BACKSPACE(8)
    , C(67)
    , CAPS_LOCK(20)
    , COMMA(188)
    , COMMAND(15)
    , CONTROL(17)
    , D(68)
    , DELETE(46)
    , DOWN(40)
    , E(69)
    , END(35)
    , ENTER(13)
    , EQUAL(187)
    , ESCAPE(27)
    , F(70)
    , F1(112)
    , F10(121)
    , F11(122)
    , F12(123)
    , F13(124)
    , F14(125)
    , F15(126)
    , F2(113)
    , F3(114)
    , F4(115)
    , F5(116)
    , F6(117)
    , F7(118)
    , F8(119)
    , F9(120)
    , G(71)
    , H(72)
    , HOME(36)
    , I(73)
    , INSERT(45)
    , J(74)
    , K(75)
    , KEYNAME_BEGIN("Begin")
    , KEYNAME_BREAK("Break")
    , KEYNAME_CLEARDISPLAY("ClrDsp")
    , KEYNAME_CLEARLINE("ClrLn")
    , KEYNAME_DELETE("Delete")
    , KEYNAME_DELETECHAR("DelChr")
    , KEYNAME_DELETELINE("DelLn")
    , KEYNAME_DOWNARROW("Down")
    , KEYNAME_END("End")
    , KEYNAME_EXECUTE("Exec")
    , KEYNAME_F1("F1")
    , KEYNAME_F10("F10")
    , KEYNAME_F11("F11")
    , KEYNAME_F12("F12")
    , KEYNAME_F13("F13")
    , KEYNAME_F14("F14")
    , KEYNAME_F15("F15")
    , KEYNAME_F16("F16")
    , KEYNAME_F17("F17")
    , KEYNAME_F18("F18")
    , KEYNAME_F19("F19")
    , KEYNAME_F2("F2")
    , KEYNAME_F20("F20")
    , KEYNAME_F21("F21")
    , KEYNAME_F22("F22")
    , KEYNAME_F23("F23")
    , KEYNAME_F24("F24")
    , KEYNAME_F25("F25")
    , KEYNAME_F26("F26")
    , KEYNAME_F27("F27")
    , KEYNAME_F28("F28")
    , KEYNAME_F29("F29")
    , KEYNAME_F3("F3")
    , KEYNAME_F30("F30")
    , KEYNAME_F31("F31")
    , KEYNAME_F32("F32")
    , KEYNAME_F33("F33")
    , KEYNAME_F34("F34")
    , KEYNAME_F35("F35")
    , KEYNAME_F4("F4")
    , KEYNAME_F5("F5")
    , KEYNAME_F6("F6")
    , KEYNAME_F7("F7")
    , KEYNAME_F8("F8")
    , KEYNAME_F9("F9")
    , KEYNAME_FIND("Find")
    , KEYNAME_HELP("Help")
    , KEYNAME_HOME("Home")
    , KEYNAME_INSERT("Insert")
    , KEYNAME_INSERTCHAR("InsChr")
    , KEYNAME_INSERTLINE("InsLn")
    , KEYNAME_LEFTARROW("Left")
    , KEYNAME_MENU("Menu")
    , KEYNAME_MODESWITCH("ModeSw")
    , KEYNAME_NEXT("Next")
    , KEYNAME_PAGEDOWN("PgDn")
    , KEYNAME_PAGEUP("PgUp")
    , KEYNAME_PAUSE("Pause")
    , KEYNAME_PREV("Prev")
    , KEYNAME_PRINT("Print")
    , KEYNAME_PRINTSCREEN("PrntScrn")
    , KEYNAME_REDO("Redo")
    , KEYNAME_RESET("Reset")
    , KEYNAME_RIGHTARROW("Right")
    , KEYNAME_SCROLLLOCK("ScrlLck")
    , KEYNAME_SELECT("Select")
    , KEYNAME_STOP("Stop")
    , KEYNAME_SYSREQ("SysReq")
    , KEYNAME_SYSTEM("Sys")
    , KEYNAME_UNDO("Undo")
    , KEYNAME_UPARROW("Up")
    , KEYNAME_USER("User")
    , L(76)
    , LEFT(37)
    , LEFTBRACKET(219)
    , M(77)
    , MINUS(189)
    , N(78)
    , NUMBER_0(48)
    , NUMBER_1(49)
    , NUMBER_2(50)
    , NUMBER_3(51)
    , NUMBER_4(52)
    , NUMBER_5(53)
    , NUMBER_6(54)
    , NUMBER_7(55)
    , NUMBER_8(56)
    , NUMBER_9(57)
    , NUMPAD(21)
    , NUMPAD_0(96)
    , NUMPAD_1(97)
    , NUMPAD_2(98)
    , NUMPAD_3(99)
    , NUMPAD_4(100)
    , NUMPAD_5(101)
    , NUMPAD_6(102)
    , NUMPAD_7(103)
    , NUMPAD_8(104)
    , NUMPAD_9(105)
    , NUMPAD_ADD(107)
    , NUMPAD_DECIMAL(110)
    , NUMPAD_DIVIDE(111)
    , NUMPAD_ENTER(108)
    , NUMPAD_MULTIPLY(106)
    , NUMPAD_SUBTRACT(109)
    , O(79)
    , P(80)
    , PAGE_DOWN(34)
    , PAGE_UP(33)
    , PERIOD(190)
    , Q(81)
    , QUOTE(222)
    , R(82)
    , RIGHT(39)
    , RIGHTBRACKET(221)
    , S(83)
    , SEMICOLON(186)
    , SHIFT(16)
    , SLASH(191)
    , SPACE(32)
    , STRING_BEGIN("\xEF\x9C\xAA")
    , STRING_BREAK("\xEF\x9C\xB2")
    , STRING_CLEARDISPLAY("\xEF\x9C\xBA")
    , STRING_CLEARLINE("\xEF\x9C\xB9")
    , STRING_DELETE("\xEF\x9C\xA8")
    , STRING_DELETECHAR("\xEF\x9C\xBE")
    , STRING_DELETELINE("\xEF\x9C\xBC")
    , STRING_DOWNARROW("\xEF\x9C\x81")
    , STRING_END("\xEF\x9C\xAB")
    , STRING_EXECUTE("\xEF\x9D\x82")
    , STRING_F1("\xEF\x9C\x84")
    , STRING_F10("\xEF\x9C\x8D")
    , STRING_F11("\xEF\x9C\x8E")
    , STRING_F12("\xEF\x9C\x8F")
    , STRING_F13("\xEF\x9C\x90")
    , STRING_F14("\xEF\x9C\x91")
    , STRING_F15("\xEF\x9C\x92")
    , STRING_F16("\xEF\x9C\x93")
    , STRING_F17("\xEF\x9C\x94")
    , STRING_F18("\xEF\x9C\x95")
    , STRING_F19("\xEF\x9C\x96")
    , STRING_F2("\xEF\x9C\x85")
    , STRING_F20("\xEF\x9C\x97")
    , STRING_F21("\xEF\x9C\x98")
    , STRING_F22("\xEF\x9C\x99")
    , STRING_F23("\xEF\x9C\x9A")
    , STRING_F24("\xEF\x9C\x9B")
    , STRING_F25("\xEF\x9C\x9C")
    , STRING_F26("\xEF\x9C\x9D")
    , STRING_F27("\xEF\x9C\x9E")
    , STRING_F28("\xEF\x9C\x9F")
    , STRING_F29("\xEF\x9C\xA0")
    , STRING_F3("\xEF\x9C\x86")
    , STRING_F30("\xEF\x9C\xA1")
    , STRING_F31("\xEF\x9C\xA2")
    , STRING_F32("\xEF\x9C\xA3")
    , STRING_F33("\xEF\x9C\xA4")
    , STRING_F34("\xEF\x9C\xA5")
    , STRING_F35("\xEF\x9C\xA6")
    , STRING_F4("\xEF\x9C\x87")
    , STRING_F5("\xEF\x9C\x88")
    , STRING_F6("\xEF\x9C\x89")
    , STRING_F7("\xEF\x9C\x8A")
    , STRING_F8("\xEF\x9C\x8B")
    , STRING_F9("\xEF\x9C\x8C")
    , STRING_FIND("\xEF\x9D\x85")
    , STRING_HELP("\xEF\x9D\x86")
    , STRING_HOME("\xEF\x9C\xA9")
    , STRING_INSERT("\xEF\x9C\xA7")
    , STRING_INSERTCHAR("\xEF\x9C\xBD")
    , STRING_INSERTLINE("\xEF\x9C\xBB")
    , STRING_LEFTARROW("\xEF\x9C\x82")
    , STRING_MENU("\xEF\x9C\xB5")
    , STRING_MODESWITCH("\xEF\x9D\x87")
    , STRING_NEXT("\xEF\x9D\x80")
    , STRING_PAGEDOWN("\xEF\x9C\xAD")
    , STRING_PAGEUP("\xEF\x9C\xAC")
    , STRING_PAUSE("\xEF\x9C\xB0")
    , STRING_PREV("\xEF\x9C\xBF")
    , STRING_PRINT("\xEF\x9C\xB8")
    , STRING_PRINTSCREEN("\xEF\x9C\xAE")
    , STRING_REDO("\xEF\x9D\x84")
    , STRING_RESET("\xEF\x9C\xB3")
    , STRING_RIGHTARROW("\xEF\x9C\x83")
    , STRING_SCROLLLOCK("\xEF\x9C\xAF")
    , STRING_SELECT("\xEF\x9D\x81")
    , STRING_STOP("\xEF\x9C\xB4")
    , STRING_SYSREQ("\xEF\x9C\xB1")
    , STRING_SYSTEM("\xEF\x9C\xB7")
    , STRING_UNDO("\xEF\x9D\x83")
    , STRING_UPARROW("\xEF\x9C\x80")
    , STRING_USER("\xEF\x9C\xB6")
    , T(84)
    , TAB(9)
    , U(85)
    , UP(38)
    , V(86)
    , W(87)
    , X(88)
    , Y(89)
    , Z(90)
    {
//##protect##"class_::Keyboard::Keyboard()"
//##protect##"class_::Keyboard::Keyboard()"
    }
    void Keyboard::capsLockGet(bool& result)
    {
//##protect##"class_::Keyboard::capsLockGet()"
        SF_UNUSED1(result);
        ASVM& vm = static_cast<ASVM&>(GetVM());
        // only zero keyboard is supported for now
        KeyboardState* ks = vm.GetMovieImpl()->GetKeyboardState(0); 
        KeyModifiers sks = ks->GetKeyModifiers();
        result = sks.IsCapsToggled();
//##protect##"class_::Keyboard::capsLockGet()"
    }
    void Keyboard::numLockGet(bool& result)
    {
//##protect##"class_::Keyboard::numLockGet()"
        ASVM& vm = static_cast<ASVM&>(GetVM());
        // only zero keyboard is supported for now
        KeyboardState* ks = vm.GetMovieImpl()->GetKeyboardState(0); 
        KeyModifiers sks = ks->GetKeyModifiers();
        result = sks.IsNumToggled();
//##protect##"class_::Keyboard::numLockGet()"
    }
    void Keyboard::isAccessible(bool& result)
    {
//##protect##"class_::Keyboard::isAccessible()"
        SF_UNUSED1(result);
        result = false; //@TODO
//##protect##"class_::Keyboard::isAccessible()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc0<Classes::Keyboard, Classes::Keyboard::mid_capsLockGet, bool> TFunc_Classes_Keyboard_capsLockGet;
typedef ThunkFunc0<Classes::Keyboard, Classes::Keyboard::mid_numLockGet, bool> TFunc_Classes_Keyboard_numLockGet;
typedef ThunkFunc0<Classes::Keyboard, Classes::Keyboard::mid_isAccessible, bool> TFunc_Classes_Keyboard_isAccessible;

template <> const TFunc_Classes_Keyboard_capsLockGet::TMethod TFunc_Classes_Keyboard_capsLockGet::Method = &Classes::Keyboard::capsLockGet;
template <> const TFunc_Classes_Keyboard_numLockGet::TMethod TFunc_Classes_Keyboard_numLockGet::Method = &Classes::Keyboard::numLockGet;
template <> const TFunc_Classes_Keyboard_isAccessible::TMethod TFunc_Classes_Keyboard_isAccessible::Method = &Classes::Keyboard::isAccessible;

namespace ClassTraits
{
    const MemberInfo Keyboard::mi[Keyboard::MemberInfoNum] = {
        {"A", OFFSETOF(Classes::Keyboard, A), SlotInfo::BT_UInt, 1},
        {"ALTERNATE", OFFSETOF(Classes::Keyboard, ALTERNATE), SlotInfo::BT_UInt, 1},
        {"B", OFFSETOF(Classes::Keyboard, B), SlotInfo::BT_UInt, 1},
        {"BACKQUOTE", OFFSETOF(Classes::Keyboard, BACKQUOTE), SlotInfo::BT_UInt, 1},
        {"BACKSLASH", OFFSETOF(Classes::Keyboard, BACKSLASH), SlotInfo::BT_UInt, 1},
        {"BACKSPACE", OFFSETOF(Classes::Keyboard, BACKSPACE), SlotInfo::BT_UInt, 1},
        {"C", OFFSETOF(Classes::Keyboard, C), SlotInfo::BT_UInt, 1},
        {"CAPS_LOCK", OFFSETOF(Classes::Keyboard, CAPS_LOCK), SlotInfo::BT_UInt, 1},
        {"CharCodeStrings", OFFSETOF(Classes::Keyboard, CharCodeStrings), SlotInfo::BT_ObjectCpp, 1},
        {"COMMA", OFFSETOF(Classes::Keyboard, COMMA), SlotInfo::BT_UInt, 1},
        {"COMMAND", OFFSETOF(Classes::Keyboard, COMMAND), SlotInfo::BT_UInt, 1},
        {"CONTROL", OFFSETOF(Classes::Keyboard, CONTROL), SlotInfo::BT_UInt, 1},
        {"D", OFFSETOF(Classes::Keyboard, D), SlotInfo::BT_UInt, 1},
        {"DELETE", OFFSETOF(Classes::Keyboard, DELETE), SlotInfo::BT_UInt, 1},
        {"DOWN", OFFSETOF(Classes::Keyboard, DOWN), SlotInfo::BT_UInt, 1},
        {"E", OFFSETOF(Classes::Keyboard, E), SlotInfo::BT_UInt, 1},
        {"END", OFFSETOF(Classes::Keyboard, END), SlotInfo::BT_UInt, 1},
        {"ENTER", OFFSETOF(Classes::Keyboard, ENTER), SlotInfo::BT_UInt, 1},
        {"EQUAL", OFFSETOF(Classes::Keyboard, EQUAL), SlotInfo::BT_UInt, 1},
        {"ESCAPE", OFFSETOF(Classes::Keyboard, ESCAPE), SlotInfo::BT_UInt, 1},
        {"F", OFFSETOF(Classes::Keyboard, F), SlotInfo::BT_UInt, 1},
        {"F1", OFFSETOF(Classes::Keyboard, F1), SlotInfo::BT_UInt, 1},
        {"F10", OFFSETOF(Classes::Keyboard, F10), SlotInfo::BT_UInt, 1},
        {"F11", OFFSETOF(Classes::Keyboard, F11), SlotInfo::BT_UInt, 1},
        {"F12", OFFSETOF(Classes::Keyboard, F12), SlotInfo::BT_UInt, 1},
        {"F13", OFFSETOF(Classes::Keyboard, F13), SlotInfo::BT_UInt, 1},
        {"F14", OFFSETOF(Classes::Keyboard, F14), SlotInfo::BT_UInt, 1},
        {"F15", OFFSETOF(Classes::Keyboard, F15), SlotInfo::BT_UInt, 1},
        {"F2", OFFSETOF(Classes::Keyboard, F2), SlotInfo::BT_UInt, 1},
        {"F3", OFFSETOF(Classes::Keyboard, F3), SlotInfo::BT_UInt, 1},
        {"F4", OFFSETOF(Classes::Keyboard, F4), SlotInfo::BT_UInt, 1},
        {"F5", OFFSETOF(Classes::Keyboard, F5), SlotInfo::BT_UInt, 1},
        {"F6", OFFSETOF(Classes::Keyboard, F6), SlotInfo::BT_UInt, 1},
        {"F7", OFFSETOF(Classes::Keyboard, F7), SlotInfo::BT_UInt, 1},
        {"F8", OFFSETOF(Classes::Keyboard, F8), SlotInfo::BT_UInt, 1},
        {"F9", OFFSETOF(Classes::Keyboard, F9), SlotInfo::BT_UInt, 1},
        {"G", OFFSETOF(Classes::Keyboard, G), SlotInfo::BT_UInt, 1},
        {"H", OFFSETOF(Classes::Keyboard, H), SlotInfo::BT_UInt, 1},
        {"HOME", OFFSETOF(Classes::Keyboard, HOME), SlotInfo::BT_UInt, 1},
        {"I", OFFSETOF(Classes::Keyboard, I), SlotInfo::BT_UInt, 1},
        {"INSERT", OFFSETOF(Classes::Keyboard, INSERT), SlotInfo::BT_UInt, 1},
        {"J", OFFSETOF(Classes::Keyboard, J), SlotInfo::BT_UInt, 1},
        {"K", OFFSETOF(Classes::Keyboard, K), SlotInfo::BT_UInt, 1},
        {"KEYNAME_BEGIN", OFFSETOF(Classes::Keyboard, KEYNAME_BEGIN), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_BREAK", OFFSETOF(Classes::Keyboard, KEYNAME_BREAK), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_CLEARDISPLAY", OFFSETOF(Classes::Keyboard, KEYNAME_CLEARDISPLAY), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_CLEARLINE", OFFSETOF(Classes::Keyboard, KEYNAME_CLEARLINE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_DELETE", OFFSETOF(Classes::Keyboard, KEYNAME_DELETE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_DELETECHAR", OFFSETOF(Classes::Keyboard, KEYNAME_DELETECHAR), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_DELETELINE", OFFSETOF(Classes::Keyboard, KEYNAME_DELETELINE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_DOWNARROW", OFFSETOF(Classes::Keyboard, KEYNAME_DOWNARROW), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_END", OFFSETOF(Classes::Keyboard, KEYNAME_END), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_EXECUTE", OFFSETOF(Classes::Keyboard, KEYNAME_EXECUTE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F1", OFFSETOF(Classes::Keyboard, KEYNAME_F1), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F10", OFFSETOF(Classes::Keyboard, KEYNAME_F10), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F11", OFFSETOF(Classes::Keyboard, KEYNAME_F11), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F12", OFFSETOF(Classes::Keyboard, KEYNAME_F12), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F13", OFFSETOF(Classes::Keyboard, KEYNAME_F13), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F14", OFFSETOF(Classes::Keyboard, KEYNAME_F14), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F15", OFFSETOF(Classes::Keyboard, KEYNAME_F15), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F16", OFFSETOF(Classes::Keyboard, KEYNAME_F16), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F17", OFFSETOF(Classes::Keyboard, KEYNAME_F17), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F18", OFFSETOF(Classes::Keyboard, KEYNAME_F18), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F19", OFFSETOF(Classes::Keyboard, KEYNAME_F19), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F2", OFFSETOF(Classes::Keyboard, KEYNAME_F2), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F20", OFFSETOF(Classes::Keyboard, KEYNAME_F20), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F21", OFFSETOF(Classes::Keyboard, KEYNAME_F21), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F22", OFFSETOF(Classes::Keyboard, KEYNAME_F22), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F23", OFFSETOF(Classes::Keyboard, KEYNAME_F23), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F24", OFFSETOF(Classes::Keyboard, KEYNAME_F24), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F25", OFFSETOF(Classes::Keyboard, KEYNAME_F25), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F26", OFFSETOF(Classes::Keyboard, KEYNAME_F26), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F27", OFFSETOF(Classes::Keyboard, KEYNAME_F27), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F28", OFFSETOF(Classes::Keyboard, KEYNAME_F28), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F29", OFFSETOF(Classes::Keyboard, KEYNAME_F29), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F3", OFFSETOF(Classes::Keyboard, KEYNAME_F3), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F30", OFFSETOF(Classes::Keyboard, KEYNAME_F30), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F31", OFFSETOF(Classes::Keyboard, KEYNAME_F31), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F32", OFFSETOF(Classes::Keyboard, KEYNAME_F32), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F33", OFFSETOF(Classes::Keyboard, KEYNAME_F33), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F34", OFFSETOF(Classes::Keyboard, KEYNAME_F34), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F35", OFFSETOF(Classes::Keyboard, KEYNAME_F35), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F4", OFFSETOF(Classes::Keyboard, KEYNAME_F4), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F5", OFFSETOF(Classes::Keyboard, KEYNAME_F5), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F6", OFFSETOF(Classes::Keyboard, KEYNAME_F6), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F7", OFFSETOF(Classes::Keyboard, KEYNAME_F7), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F8", OFFSETOF(Classes::Keyboard, KEYNAME_F8), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_F9", OFFSETOF(Classes::Keyboard, KEYNAME_F9), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_FIND", OFFSETOF(Classes::Keyboard, KEYNAME_FIND), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_HELP", OFFSETOF(Classes::Keyboard, KEYNAME_HELP), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_HOME", OFFSETOF(Classes::Keyboard, KEYNAME_HOME), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_INSERT", OFFSETOF(Classes::Keyboard, KEYNAME_INSERT), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_INSERTCHAR", OFFSETOF(Classes::Keyboard, KEYNAME_INSERTCHAR), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_INSERTLINE", OFFSETOF(Classes::Keyboard, KEYNAME_INSERTLINE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_LEFTARROW", OFFSETOF(Classes::Keyboard, KEYNAME_LEFTARROW), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_MENU", OFFSETOF(Classes::Keyboard, KEYNAME_MENU), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_MODESWITCH", OFFSETOF(Classes::Keyboard, KEYNAME_MODESWITCH), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_NEXT", OFFSETOF(Classes::Keyboard, KEYNAME_NEXT), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PAGEDOWN", OFFSETOF(Classes::Keyboard, KEYNAME_PAGEDOWN), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PAGEUP", OFFSETOF(Classes::Keyboard, KEYNAME_PAGEUP), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PAUSE", OFFSETOF(Classes::Keyboard, KEYNAME_PAUSE), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PREV", OFFSETOF(Classes::Keyboard, KEYNAME_PREV), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PRINT", OFFSETOF(Classes::Keyboard, KEYNAME_PRINT), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_PRINTSCREEN", OFFSETOF(Classes::Keyboard, KEYNAME_PRINTSCREEN), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_REDO", OFFSETOF(Classes::Keyboard, KEYNAME_REDO), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_RESET", OFFSETOF(Classes::Keyboard, KEYNAME_RESET), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_RIGHTARROW", OFFSETOF(Classes::Keyboard, KEYNAME_RIGHTARROW), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_SCROLLLOCK", OFFSETOF(Classes::Keyboard, KEYNAME_SCROLLLOCK), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_SELECT", OFFSETOF(Classes::Keyboard, KEYNAME_SELECT), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_STOP", OFFSETOF(Classes::Keyboard, KEYNAME_STOP), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_SYSREQ", OFFSETOF(Classes::Keyboard, KEYNAME_SYSREQ), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_SYSTEM", OFFSETOF(Classes::Keyboard, KEYNAME_SYSTEM), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_UNDO", OFFSETOF(Classes::Keyboard, KEYNAME_UNDO), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_UPARROW", OFFSETOF(Classes::Keyboard, KEYNAME_UPARROW), SlotInfo::BT_ConstChar, 1},
        {"KEYNAME_USER", OFFSETOF(Classes::Keyboard, KEYNAME_USER), SlotInfo::BT_ConstChar, 1},
        {"L", OFFSETOF(Classes::Keyboard, L), SlotInfo::BT_UInt, 1},
        {"LEFT", OFFSETOF(Classes::Keyboard, LEFT), SlotInfo::BT_UInt, 1},
        {"LEFTBRACKET", OFFSETOF(Classes::Keyboard, LEFTBRACKET), SlotInfo::BT_UInt, 1},
        {"M", OFFSETOF(Classes::Keyboard, M), SlotInfo::BT_UInt, 1},
        {"MINUS", OFFSETOF(Classes::Keyboard, MINUS), SlotInfo::BT_UInt, 1},
        {"N", OFFSETOF(Classes::Keyboard, N), SlotInfo::BT_UInt, 1},
        {"NUMBER_0", OFFSETOF(Classes::Keyboard, NUMBER_0), SlotInfo::BT_UInt, 1},
        {"NUMBER_1", OFFSETOF(Classes::Keyboard, NUMBER_1), SlotInfo::BT_UInt, 1},
        {"NUMBER_2", OFFSETOF(Classes::Keyboard, NUMBER_2), SlotInfo::BT_UInt, 1},
        {"NUMBER_3", OFFSETOF(Classes::Keyboard, NUMBER_3), SlotInfo::BT_UInt, 1},
        {"NUMBER_4", OFFSETOF(Classes::Keyboard, NUMBER_4), SlotInfo::BT_UInt, 1},
        {"NUMBER_5", OFFSETOF(Classes::Keyboard, NUMBER_5), SlotInfo::BT_UInt, 1},
        {"NUMBER_6", OFFSETOF(Classes::Keyboard, NUMBER_6), SlotInfo::BT_UInt, 1},
        {"NUMBER_7", OFFSETOF(Classes::Keyboard, NUMBER_7), SlotInfo::BT_UInt, 1},
        {"NUMBER_8", OFFSETOF(Classes::Keyboard, NUMBER_8), SlotInfo::BT_UInt, 1},
        {"NUMBER_9", OFFSETOF(Classes::Keyboard, NUMBER_9), SlotInfo::BT_UInt, 1},
        {"NUMPAD", OFFSETOF(Classes::Keyboard, NUMPAD), SlotInfo::BT_UInt, 1},
        {"NUMPAD_0", OFFSETOF(Classes::Keyboard, NUMPAD_0), SlotInfo::BT_UInt, 1},
        {"NUMPAD_1", OFFSETOF(Classes::Keyboard, NUMPAD_1), SlotInfo::BT_UInt, 1},
        {"NUMPAD_2", OFFSETOF(Classes::Keyboard, NUMPAD_2), SlotInfo::BT_UInt, 1},
        {"NUMPAD_3", OFFSETOF(Classes::Keyboard, NUMPAD_3), SlotInfo::BT_UInt, 1},
        {"NUMPAD_4", OFFSETOF(Classes::Keyboard, NUMPAD_4), SlotInfo::BT_UInt, 1},
        {"NUMPAD_5", OFFSETOF(Classes::Keyboard, NUMPAD_5), SlotInfo::BT_UInt, 1},
        {"NUMPAD_6", OFFSETOF(Classes::Keyboard, NUMPAD_6), SlotInfo::BT_UInt, 1},
        {"NUMPAD_7", OFFSETOF(Classes::Keyboard, NUMPAD_7), SlotInfo::BT_UInt, 1},
        {"NUMPAD_8", OFFSETOF(Classes::Keyboard, NUMPAD_8), SlotInfo::BT_UInt, 1},
        {"NUMPAD_9", OFFSETOF(Classes::Keyboard, NUMPAD_9), SlotInfo::BT_UInt, 1},
        {"NUMPAD_ADD", OFFSETOF(Classes::Keyboard, NUMPAD_ADD), SlotInfo::BT_UInt, 1},
        {"NUMPAD_DECIMAL", OFFSETOF(Classes::Keyboard, NUMPAD_DECIMAL), SlotInfo::BT_UInt, 1},
        {"NUMPAD_DIVIDE", OFFSETOF(Classes::Keyboard, NUMPAD_DIVIDE), SlotInfo::BT_UInt, 1},
        {"NUMPAD_ENTER", OFFSETOF(Classes::Keyboard, NUMPAD_ENTER), SlotInfo::BT_UInt, 1},
        {"NUMPAD_MULTIPLY", OFFSETOF(Classes::Keyboard, NUMPAD_MULTIPLY), SlotInfo::BT_UInt, 1},
        {"NUMPAD_SUBTRACT", OFFSETOF(Classes::Keyboard, NUMPAD_SUBTRACT), SlotInfo::BT_UInt, 1},
        {"O", OFFSETOF(Classes::Keyboard, O), SlotInfo::BT_UInt, 1},
        {"P", OFFSETOF(Classes::Keyboard, P), SlotInfo::BT_UInt, 1},
        {"PAGE_DOWN", OFFSETOF(Classes::Keyboard, PAGE_DOWN), SlotInfo::BT_UInt, 1},
        {"PAGE_UP", OFFSETOF(Classes::Keyboard, PAGE_UP), SlotInfo::BT_UInt, 1},
        {"PERIOD", OFFSETOF(Classes::Keyboard, PERIOD), SlotInfo::BT_UInt, 1},
        {"Q", OFFSETOF(Classes::Keyboard, Q), SlotInfo::BT_UInt, 1},
        {"QUOTE", OFFSETOF(Classes::Keyboard, QUOTE), SlotInfo::BT_UInt, 1},
        {"R", OFFSETOF(Classes::Keyboard, R), SlotInfo::BT_UInt, 1},
        {"RIGHT", OFFSETOF(Classes::Keyboard, RIGHT), SlotInfo::BT_UInt, 1},
        {"RIGHTBRACKET", OFFSETOF(Classes::Keyboard, RIGHTBRACKET), SlotInfo::BT_UInt, 1},
        {"S", OFFSETOF(Classes::Keyboard, S), SlotInfo::BT_UInt, 1},
        {"SEMICOLON", OFFSETOF(Classes::Keyboard, SEMICOLON), SlotInfo::BT_UInt, 1},
        {"SHIFT", OFFSETOF(Classes::Keyboard, SHIFT), SlotInfo::BT_UInt, 1},
        {"SLASH", OFFSETOF(Classes::Keyboard, SLASH), SlotInfo::BT_UInt, 1},
        {"SPACE", OFFSETOF(Classes::Keyboard, SPACE), SlotInfo::BT_UInt, 1},
        {"STRING_BEGIN", OFFSETOF(Classes::Keyboard, STRING_BEGIN), SlotInfo::BT_ConstChar, 1},
        {"STRING_BREAK", OFFSETOF(Classes::Keyboard, STRING_BREAK), SlotInfo::BT_ConstChar, 1},
        {"STRING_CLEARDISPLAY", OFFSETOF(Classes::Keyboard, STRING_CLEARDISPLAY), SlotInfo::BT_ConstChar, 1},
        {"STRING_CLEARLINE", OFFSETOF(Classes::Keyboard, STRING_CLEARLINE), SlotInfo::BT_ConstChar, 1},
        {"STRING_DELETE", OFFSETOF(Classes::Keyboard, STRING_DELETE), SlotInfo::BT_ConstChar, 1},
        {"STRING_DELETECHAR", OFFSETOF(Classes::Keyboard, STRING_DELETECHAR), SlotInfo::BT_ConstChar, 1},
        {"STRING_DELETELINE", OFFSETOF(Classes::Keyboard, STRING_DELETELINE), SlotInfo::BT_ConstChar, 1},
        {"STRING_DOWNARROW", OFFSETOF(Classes::Keyboard, STRING_DOWNARROW), SlotInfo::BT_ConstChar, 1},
        {"STRING_END", OFFSETOF(Classes::Keyboard, STRING_END), SlotInfo::BT_ConstChar, 1},
        {"STRING_EXECUTE", OFFSETOF(Classes::Keyboard, STRING_EXECUTE), SlotInfo::BT_ConstChar, 1},
        {"STRING_F1", OFFSETOF(Classes::Keyboard, STRING_F1), SlotInfo::BT_ConstChar, 1},
        {"STRING_F10", OFFSETOF(Classes::Keyboard, STRING_F10), SlotInfo::BT_ConstChar, 1},
        {"STRING_F11", OFFSETOF(Classes::Keyboard, STRING_F11), SlotInfo::BT_ConstChar, 1},
        {"STRING_F12", OFFSETOF(Classes::Keyboard, STRING_F12), SlotInfo::BT_ConstChar, 1},
        {"STRING_F13", OFFSETOF(Classes::Keyboard, STRING_F13), SlotInfo::BT_ConstChar, 1},
        {"STRING_F14", OFFSETOF(Classes::Keyboard, STRING_F14), SlotInfo::BT_ConstChar, 1},
        {"STRING_F15", OFFSETOF(Classes::Keyboard, STRING_F15), SlotInfo::BT_ConstChar, 1},
        {"STRING_F16", OFFSETOF(Classes::Keyboard, STRING_F16), SlotInfo::BT_ConstChar, 1},
        {"STRING_F17", OFFSETOF(Classes::Keyboard, STRING_F17), SlotInfo::BT_ConstChar, 1},
        {"STRING_F18", OFFSETOF(Classes::Keyboard, STRING_F18), SlotInfo::BT_ConstChar, 1},
        {"STRING_F19", OFFSETOF(Classes::Keyboard, STRING_F19), SlotInfo::BT_ConstChar, 1},
        {"STRING_F2", OFFSETOF(Classes::Keyboard, STRING_F2), SlotInfo::BT_ConstChar, 1},
        {"STRING_F20", OFFSETOF(Classes::Keyboard, STRING_F20), SlotInfo::BT_ConstChar, 1},
        {"STRING_F21", OFFSETOF(Classes::Keyboard, STRING_F21), SlotInfo::BT_ConstChar, 1},
        {"STRING_F22", OFFSETOF(Classes::Keyboard, STRING_F22), SlotInfo::BT_ConstChar, 1},
        {"STRING_F23", OFFSETOF(Classes::Keyboard, STRING_F23), SlotInfo::BT_ConstChar, 1},
        {"STRING_F24", OFFSETOF(Classes::Keyboard, STRING_F24), SlotInfo::BT_ConstChar, 1},
        {"STRING_F25", OFFSETOF(Classes::Keyboard, STRING_F25), SlotInfo::BT_ConstChar, 1},
        {"STRING_F26", OFFSETOF(Classes::Keyboard, STRING_F26), SlotInfo::BT_ConstChar, 1},
        {"STRING_F27", OFFSETOF(Classes::Keyboard, STRING_F27), SlotInfo::BT_ConstChar, 1},
        {"STRING_F28", OFFSETOF(Classes::Keyboard, STRING_F28), SlotInfo::BT_ConstChar, 1},
        {"STRING_F29", OFFSETOF(Classes::Keyboard, STRING_F29), SlotInfo::BT_ConstChar, 1},
        {"STRING_F3", OFFSETOF(Classes::Keyboard, STRING_F3), SlotInfo::BT_ConstChar, 1},
        {"STRING_F30", OFFSETOF(Classes::Keyboard, STRING_F30), SlotInfo::BT_ConstChar, 1},
        {"STRING_F31", OFFSETOF(Classes::Keyboard, STRING_F31), SlotInfo::BT_ConstChar, 1},
        {"STRING_F32", OFFSETOF(Classes::Keyboard, STRING_F32), SlotInfo::BT_ConstChar, 1},
        {"STRING_F33", OFFSETOF(Classes::Keyboard, STRING_F33), SlotInfo::BT_ConstChar, 1},
        {"STRING_F34", OFFSETOF(Classes::Keyboard, STRING_F34), SlotInfo::BT_ConstChar, 1},
        {"STRING_F35", OFFSETOF(Classes::Keyboard, STRING_F35), SlotInfo::BT_ConstChar, 1},
        {"STRING_F4", OFFSETOF(Classes::Keyboard, STRING_F4), SlotInfo::BT_ConstChar, 1},
        {"STRING_F5", OFFSETOF(Classes::Keyboard, STRING_F5), SlotInfo::BT_ConstChar, 1},
        {"STRING_F6", OFFSETOF(Classes::Keyboard, STRING_F6), SlotInfo::BT_ConstChar, 1},
        {"STRING_F7", OFFSETOF(Classes::Keyboard, STRING_F7), SlotInfo::BT_ConstChar, 1},
        {"STRING_F8", OFFSETOF(Classes::Keyboard, STRING_F8), SlotInfo::BT_ConstChar, 1},
        {"STRING_F9", OFFSETOF(Classes::Keyboard, STRING_F9), SlotInfo::BT_ConstChar, 1},
        {"STRING_FIND", OFFSETOF(Classes::Keyboard, STRING_FIND), SlotInfo::BT_ConstChar, 1},
        {"STRING_HELP", OFFSETOF(Classes::Keyboard, STRING_HELP), SlotInfo::BT_ConstChar, 1},
        {"STRING_HOME", OFFSETOF(Classes::Keyboard, STRING_HOME), SlotInfo::BT_ConstChar, 1},
        {"STRING_INSERT", OFFSETOF(Classes::Keyboard, STRING_INSERT), SlotInfo::BT_ConstChar, 1},
        {"STRING_INSERTCHAR", OFFSETOF(Classes::Keyboard, STRING_INSERTCHAR), SlotInfo::BT_ConstChar, 1},
        {"STRING_INSERTLINE", OFFSETOF(Classes::Keyboard, STRING_INSERTLINE), SlotInfo::BT_ConstChar, 1},
        {"STRING_LEFTARROW", OFFSETOF(Classes::Keyboard, STRING_LEFTARROW), SlotInfo::BT_ConstChar, 1},
        {"STRING_MENU", OFFSETOF(Classes::Keyboard, STRING_MENU), SlotInfo::BT_ConstChar, 1},
        {"STRING_MODESWITCH", OFFSETOF(Classes::Keyboard, STRING_MODESWITCH), SlotInfo::BT_ConstChar, 1},
        {"STRING_NEXT", OFFSETOF(Classes::Keyboard, STRING_NEXT), SlotInfo::BT_ConstChar, 1},
        {"STRING_PAGEDOWN", OFFSETOF(Classes::Keyboard, STRING_PAGEDOWN), SlotInfo::BT_ConstChar, 1},
        {"STRING_PAGEUP", OFFSETOF(Classes::Keyboard, STRING_PAGEUP), SlotInfo::BT_ConstChar, 1},
        {"STRING_PAUSE", OFFSETOF(Classes::Keyboard, STRING_PAUSE), SlotInfo::BT_ConstChar, 1},
        {"STRING_PREV", OFFSETOF(Classes::Keyboard, STRING_PREV), SlotInfo::BT_ConstChar, 1},
        {"STRING_PRINT", OFFSETOF(Classes::Keyboard, STRING_PRINT), SlotInfo::BT_ConstChar, 1},
        {"STRING_PRINTSCREEN", OFFSETOF(Classes::Keyboard, STRING_PRINTSCREEN), SlotInfo::BT_ConstChar, 1},
        {"STRING_REDO", OFFSETOF(Classes::Keyboard, STRING_REDO), SlotInfo::BT_ConstChar, 1},
        {"STRING_RESET", OFFSETOF(Classes::Keyboard, STRING_RESET), SlotInfo::BT_ConstChar, 1},
        {"STRING_RIGHTARROW", OFFSETOF(Classes::Keyboard, STRING_RIGHTARROW), SlotInfo::BT_ConstChar, 1},
        {"STRING_SCROLLLOCK", OFFSETOF(Classes::Keyboard, STRING_SCROLLLOCK), SlotInfo::BT_ConstChar, 1},
        {"STRING_SELECT", OFFSETOF(Classes::Keyboard, STRING_SELECT), SlotInfo::BT_ConstChar, 1},
        {"STRING_STOP", OFFSETOF(Classes::Keyboard, STRING_STOP), SlotInfo::BT_ConstChar, 1},
        {"STRING_SYSREQ", OFFSETOF(Classes::Keyboard, STRING_SYSREQ), SlotInfo::BT_ConstChar, 1},
        {"STRING_SYSTEM", OFFSETOF(Classes::Keyboard, STRING_SYSTEM), SlotInfo::BT_ConstChar, 1},
        {"STRING_UNDO", OFFSETOF(Classes::Keyboard, STRING_UNDO), SlotInfo::BT_ConstChar, 1},
        {"STRING_UPARROW", OFFSETOF(Classes::Keyboard, STRING_UPARROW), SlotInfo::BT_ConstChar, 1},
        {"STRING_USER", OFFSETOF(Classes::Keyboard, STRING_USER), SlotInfo::BT_ConstChar, 1},
        {"T", OFFSETOF(Classes::Keyboard, T), SlotInfo::BT_UInt, 1},
        {"TAB", OFFSETOF(Classes::Keyboard, TAB), SlotInfo::BT_UInt, 1},
        {"U", OFFSETOF(Classes::Keyboard, U), SlotInfo::BT_UInt, 1},
        {"UP", OFFSETOF(Classes::Keyboard, UP), SlotInfo::BT_UInt, 1},
        {"V", OFFSETOF(Classes::Keyboard, V), SlotInfo::BT_UInt, 1},
        {"W", OFFSETOF(Classes::Keyboard, W), SlotInfo::BT_UInt, 1},
        {"X", OFFSETOF(Classes::Keyboard, X), SlotInfo::BT_UInt, 1},
        {"Y", OFFSETOF(Classes::Keyboard, Y), SlotInfo::BT_UInt, 1},
        {"Z", OFFSETOF(Classes::Keyboard, Z), SlotInfo::BT_UInt, 1},
    };

    const ThunkInfo Keyboard::ti[Keyboard::ThunkInfoNum] = {
        {TFunc_Classes_Keyboard_capsLockGet::Func, &BooleanCI, "capsLock", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Keyboard_numLockGet::Func, &BooleanCI, "numLock", NULL, CT_Get, 0, 0},
        {TFunc_Classes_Keyboard_isAccessible::Func, &BooleanCI, "isAccessible", NULL, CT_Method, 0, 0},
    };
    Keyboard::Keyboard(VM& vm)
    : Traits(vm, KeyboardCI)
    {
//##protect##"ClassTraits::Keyboard::Keyboard()"
//##protect##"ClassTraits::Keyboard::Keyboard()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::Object(vm, KeyboardCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::Keyboard(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> Keyboard::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) Keyboard(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo KeyboardCI = {
    ClassInfo::CompileTime,
    "Keyboard", "flash.ui", &ObjectCI,
    ClassTraits::Keyboard::MakeClassTraits,
    ClassTraits::Keyboard::ThunkInfoNum,
    ClassTraits::Keyboard::MemberInfoNum,
    0,
    0,
    ClassTraits::Keyboard::ti,
    ClassTraits::Keyboard::mi,
    NULL,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

