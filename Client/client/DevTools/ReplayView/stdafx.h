
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

#include <vector>
#include <map>

#define FDECLARE_CLASS(x)
#define FINLINE __forceinline
#define ACHAR char
#define WCHAR wchar_t
#define FStringA CStringA
#define FStringW CStringW
#define NCHAR TCHAR
#define FString CString
#define _FT _T
#define _FTA(x) x
#define _FTW(x) L ## x
#include <sys/stat.h>
#include "FMod_MemFile.h"

typedef UINT UBOOL;		// Boolean 0 (false) or 1 (true).
typedef INT NAME_INDEX;
typedef std::vector<INT> STLIntVector;
typedef std::map<INT, INT> STLInt2IntMap;
class FVector 
{
    FLOAT X,Y,Z;
};
class AMMOPlayer
{
    INT id;
};

enum EClientVariableType
{
    ECVT_GAME_CONFIG        =0,
};

#define M_DECL_PARSE_FUN(msgID)
#define MREG_PARSE_FUN(msg) message_names[msg] = #msg;

//#include "../../UE3/Development/Src/MMOGame/net/message_handler.h"
#include "c2g_message.h"
#include "g2c_message.h"
#include "c2m_message.h"
#include "m2c_message.h"
#include "c2t_message.h"
#include "t2c_message.h"
#include "b2c_message.h"
using namespace ExternalMessage;

class net_message_object
{
#include "message_handler_Chat.h"
#include "message_handler_Combat.h"
#include "message_handler_Drop.h"
#include "message_handler_Item.h"
#include "message_handler_Soul.h"
#include "message_handler_Login.h"
#include "message_handler_Quest.h"
#include "message_handler_Stall.h"
#include "message_handler_Team.h"
#include "message_handler_Friend.h"
#include "message_handler_Scene.h"
#include "message_handler_NPC.h"
#include "message_handler_Trade.h"
#include "message_handler_Shop.h"
#include "message_handler_Mail.h"
#include "message_handler_Arena.h"
#include "message_handler_MasterStudent.h"
#include "message_handler_Achievement.h"
#include "message_handler_BattleTeam.h"
#include "message_handler_Guild.h"
#include "message_handler_EquipSlot.h"
#include "message_handler_Weather.h"
#include "message_handler_Heaven.h"
#include "message_handler_EquipDecompose.h"
#include "message_handler_Activity.h"
#include "message_handler_PlayerInfo.h"
//#include "message_handler_UndergroundTrade.h"
#include "message_handler_Ranklist.h"
#include "message_handler_Mall.h"

    std::map< DWORD, CString > message_names;

public:
    net_message_object()
    {
        M_INIT_MSGHANDLER_LOGIN;
        M_INIT_MSGHANDLER_STALL;
        M_INIT_MSGHANDLER_ITEM;
        M_INIT_MSGHANDLER_TEAM;
        M_INIT_MSGHANDLER_CHAT;
        M_INIT_MSGHANDLER_FRIEND;
        M_INIT_MSGHANDLER_COMBAT;
        M_INIT_MSGHANDLER_DROP;
        M_INIT_MSGHANDLER_QUEST;
        M_INIT_MSGHANDLER_SCENE;
        M_INIT_MSGHANDLER_NPC;
        M_INIT_MSGHANDLER_TRADE;
        M_INIT_MSGHANDLER_SHOP;
        M_INIT_MSGHANDLER_MAIL;
        M_INIT_MSGHANDLER_MASTER;
        M_INIT_MSGHANDLER_ACHIEVEMENT;
        //M_INIT_MSGHANDLER_BATTLETEAM;
        M_INIT_MSGHANDLER_GUILD;
        M_INIT_MSGHANDLER_PLAYERINFO;
        M_INIT_MSGHANDLER_ARENA;
        M_INIT_MSGHANDLER_SOUL;
        M_INIT_MSGHANDLER_WEATHER;
        //M_INIT_MSGHANDLER_UNDERGROUNDTRADE;
        M_INIT_MSGHANDLER_RANKLIST;
        M_INIT_MSGHANDLER_HEAVEN;
        M_INIT_MSGHANDLER_MALL;

        MREG_PARSE_FUN(g2c_ping_ack);
        MREG_PARSE_FUN(t2c_ping_ack);
        MREG_PARSE_FUN(g2c_sync_game_data_begin);
        MREG_PARSE_FUN(g2c_exp_change);
        MREG_PARSE_FUN(g2c_role_level_up);
        MREG_PARSE_FUN(g2c_sync_game_data_end);

        MREG_PARSE_FUN(g2c_return_select_role);

        MREG_PARSE_FUN(g2c_error_notify);
        MREG_PARSE_FUN(g2c_frame_signal);
        MREG_PARSE_FUN(g2c_gpk_dyn_code);
        MREG_PARSE_FUN(g2c_gpk_auth_data);
        MREG_PARSE_FUN(g2c_char_move);
        MREG_PARSE_FUN(g2c_char_passive_move);
        MREG_PARSE_FUN(g2c_char_stop);
        MREG_PARSE_FUN(g2c_object_rotate);
        MREG_PARSE_FUN(g2c_sync_container_sizes);
        //MREG_PARSE_FUN(g2c_refine_item);
        //MREG_PARSE_FUN(g2c_transfer_refine_item);
        MREG_PARSE_FUN(g2c_refine);
        MREG_PARSE_FUN(g2c_sync_refine);
        MREG_PARSE_FUN(g2c_char_appear);
        MREG_PARSE_FUN(g2c_sync_char_list);
        MREG_PARSE_FUN(g2c_sync_role_data);
        MREG_PARSE_FUN(g2c_sync_attr_list);
        MREG_PARSE_FUN(g2c_sync_attr_change);
        MREG_PARSE_FUN(g2c_sync_role_avatar);
        MREG_PARSE_FUN(g2c_sync_hero_avatar);
        MREG_PARSE_FUN(g2c_object_disappear);
        MREG_PARSE_FUN(g2c_object_disappear_list);
        MREG_PARSE_FUN(g2c_sync_role_pos);

        MREG_PARSE_FUN(m2c_sync_role_info);

        MREG_PARSE_FUN(g2c_sync_item_bag);
        MREG_PARSE_FUN(g2c_item_delete);
        MREG_PARSE_FUN(g2c_item_change);
        MREG_PARSE_FUN(g2c_item_swap);

        MREG_PARSE_FUN(g2c_sync_reputation);
        MREG_PARSE_FUN(g2c_sync_title);
        MREG_PARSE_FUN(g2c_add_title);
        MREG_PARSE_FUN(g2c_del_title);
        MREG_PARSE_FUN(g2c_sync_pk_value);
        MREG_PARSE_FUN(g2c_sync_equip_title);
        MREG_PARSE_FUN(g2c_modify_reputation);



        MREG_PARSE_FUN(g2c_sync_spell_book);
        MREG_PARSE_FUN(g2c_role_learn_spell);
        MREG_PARSE_FUN(g2c_self_hifreq_sync);
        MREG_PARSE_FUN(g2c_region_hifreq_sync);

        //Doodad
        MREG_PARSE_FUN(g2c_sync_doodad_list);
        MREG_PARSE_FUN(g2c_operate_doodad_begin);
        MREG_PARSE_FUN(g2c_operate_doodad_end);
        MREG_PARSE_FUN(g2c_sync_doodad_open_count);




        MREG_PARSE_FUN(g2c_sync_door_state);


        //金钱同步
        MREG_PARSE_FUN(g2c_sync_money);
        MREG_PARSE_FUN(g2c_money_change);

        MREG_PARSE_FUN(t2c_ping_ack);
        MREG_PARSE_FUN(m2c_error_notify);

        //mount
        MREG_PARSE_FUN(g2c_sync_mount_list);
        MREG_PARSE_FUN(g2c_activate_mount);
        MREG_PARSE_FUN(g2c_char_on_mount);
        MREG_PARSE_FUN(g2c_char_off_mount);

        //hero
        MREG_PARSE_FUN(g2c_sync_hero_data);
        MREG_PARSE_FUN(g2c_hero_exp_change);
        MREG_PARSE_FUN(g2c_hero_level_up);
        MREG_PARSE_FUN(g2c_sync_hero_attr_list);
        MREG_PARSE_FUN(g2c_hero_attr_change);
        MREG_PARSE_FUN(g2c_hire_hero);
        MREG_PARSE_FUN(g2c_fire_hero);
        MREG_PARSE_FUN(g2c_summon_hero);
        MREG_PARSE_FUN(g2c_change_hero_ai);
        MREG_PARSE_FUN(g2c_recall_hero);
        MREG_PARSE_FUN(g2c_decompose);

        MREG_PARSE_FUN(g2c_compose);

        MREG_PARSE_FUN(g2c_draw_debug_line);
    }
    const TCHAR* GetMsgName(DWORD id)
    {
        std::map< DWORD, CString >::iterator itr = message_names.find(id);
        if (itr != message_names.end())
            return itr->second;
        return _T("ID未注册");
    }
};

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


