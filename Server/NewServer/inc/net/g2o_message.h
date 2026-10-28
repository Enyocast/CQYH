#ifndef _g2o_MESSAGE_H_
#define _g2o_MESSAGE_H_

#include "internal_message_header.h"

#pragma pack(push, 1)
namespace InternalMessage
{
	enum G2O_MESSAGE_ID
	{
		g2o_begin = g2o_message_begin,

		g2o_register,

		g2o_chat_message,

		g2o_cast_spell,
		g2o_spell_effect,
		g2o_learn_spell,

		g2o_accept_quest,
		g2o_complete_quest,
		g2o_abandon_quest,
		g2o_complete_achievement,

		g2o_level_up,

		g2o_die,

		g2o_create_scene,
		g2o_destory_scene,

		g2o_log_item,
        g2o_stat_item,
        g2o_rune_item,
        g2o_change_item,

		g2o_buy_conslot,

		g2o_gm_command,

		g2o_role_logout,

		g2o_add_money,
		g2o_sub_money,

		g2o_role_position,

		g2o_npc_die,
        g2o_npc_money,
		g2o_consecutive_kill_npc_count,
		g2o_momentary_kill_npc_count,

		g2o_client_hardware_info,
		g2o_client_fps_info,

		g2o_role_anti_cheat_info,

		g2o_end = g2o_message_end
	};

	struct GL_MESSAGE_HEADER : MESSAGE_HEADER
	{
		UINT32	dwTime;
		INT32	nGroupID;
	};

	struct G2O_REGISTER : MESSAGE_HEADER
	{
		UINT32      dwGSSessionID;
	};

	struct G2O_CHAT_MESSAGE : GL_MESSAGE_HEADER
	{
		UINT32		dwSourceID;
		UINT32		dwTargetID;
		INT32		nMessageSize;
		char		szMessage[0];
	};

	struct G2O_CAST_SPELL : GL_MESSAGE_HEADER
	{
		UINT32		dwCasterID;
		UINT8		byCasterLevel;
		UINT32		dwTargetID;
		UINT32		dwSpellID;
		UINT8		bySpellLevel;
		UINT8		byRuneSlot;
		UINT8		bySpellSerial;
		INT32		nTargetX;
		INT32		nTargetY;
		INT32		nTargetZ;
		INT32		nMp;
		INT32		nCdRemain;
		INT32		nErrCode;
		UINT32		dwClientTime;
		UINT8		byFromServer;
		UINT8		byShiftPressed;
	};

	struct G2O_SPELL_EFFECT : GL_MESSAGE_HEADER
	{
		UINT32		dwCasterID;
		UINT32		dwTargetID;
		UINT32		dwSpellID;
		UINT8		bySpellLevel;
		UINT8		byRuneSlot;
		UINT8		bySpellSerial;
		INT32		nParam1;
		INT32		nParam2;
		INT16		wFlag;
	};

	struct G2O_LEARN_SPELL : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nSpellID;
		UINT8		bySpellLevel;
		UINT8		byRoleLevel;
		INT32		nRoleExp;
	};

	struct G2O_ACCEPT_QUEST : GL_MESSAGE_HEADER
	{
		UINT32		dwSrcID;
		INT32		nQuestID;
	};

	struct G2O_COMPLETE_QUEST : GL_MESSAGE_HEADER
	{
		UINT32		dwSrcID;
		INT32		nQuestID;
	};

	struct G2O_ABANDON_QUEST : GL_MESSAGE_HEADER
	{
		UINT32		dwSrcID;
		INT32		nQuestID;
	};

	struct G2O_COMPLETE_ACHIEVEMENT : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nAchievementID;
	};

	struct G2O_LEVEL_UP : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nLevel;
		INT32		nLevelOnlineTime;
		INT32		nTotalOnlineTime;
	};

	struct G2O_DIE : GL_MESSAGE_HEADER
	{
		INT32		nSceneTemplateID;
		INT32		nSceneID;

		UINT32		dwKillerID;
		INT32		nKillerType;
		INT32		nKillLevel;
		INT32		nKillClass;

		UINT32		dwVicID;
		INT32		nVicLevel;
		INT32		nVicClass;

		INT64		llX;
		INT64		llY;
		INT64		llZ;

		char		szKillerName[ROLE_NAME_LEN];
		char		szVicName[ROLE_NAME_LEN];
	};

	struct G2O_CREATE_SCENE : GL_MESSAGE_HEADER
	{
		INT32		nSceneID;
		INT32		nTemplateID;
	};
		
	struct G2O_DESTORY_SCENE : GL_MESSAGE_HEADER
	{
		INT32		nSceneID;
		INT32		nTemplateID;
	};

	struct G2O_BUY_CONSLOT : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nConSize;
		INT32		nConType;
	};

    struct G2O_LOG_ITEM : GL_MESSAGE_HEADER
    {
        UINT64      qwItemGuid;
        UINT32      dwRoleID;
        INT32       nItemTemplateID;
        INT32       nItemCount;
        INT32       nReason;
        INT32       nAction;
        UINT64      qwUserDefinedID;
    };

    struct G2O_STAT_ITEM : GL_MESSAGE_HEADER
    {
        INT32       nItemTemplateID;
        INT32       nItemCount;
        INT32       nAction;
    };

    struct G2O_RUNE_ITEM : GL_MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nRoleLevel;
        INT32       nEquipTemplateID;
        INT32       nRuneItemID;
        INT32       nRuneID;
    };

    struct G2O_CHANGE_ITEM : GL_MESSAGE_HEADER
    {
        UINT32      dwRoleID;
        INT32       nReason;
        UINT64      qwItemGuid;
        INT32       nItemTemplateID;
        char        szItem[0];
    };

	struct G2O_GM_COMMAND : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		BOOL		bResult;
		char		szName[ROLE_NAME_LEN];
		char		szCommand[0];
	};

 	struct G2O_ROLE_LOGOUT : GL_MESSAGE_HEADER
 	{
		UINT32		dwRoleID;
		UINT32		dwSessionID;
		BOOL		bInJump;
		char		szGuildName[GUILD_NAME_LEN];
		UINT32		dwSize;
 		char		szData[0];
 	};

	struct G2O_ADD_MONEY: GL_MESSAGE_HEADER
	{
		UINT32		dwSrcRoleID;
		UINT32		dwTarRoleID;
		INT32		nMoneyType;
		INT32		nMoneyCount;
		INT32		nReason;
		INT32		nParam;
	};

	struct G2O_SUB_MONEY: GL_MESSAGE_HEADER
	{
		UINT32		dwSrcRoleID;
        UINT32		dwTarRoleID;
		INT32		nMoneyType;
		INT32		nMoneyCount;
		INT32		nReason;
		INT32		nParam;
	};

	struct G2O_ROLE_POSITION : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nSceneTemplateID;
		INT32		nSceneID;
		INT32		nX;
		INT32		nY;
		INT32		nZ;
	};

	struct G2O_NPC_DIE : GL_MESSAGE_HEADER
	{
		UINT32		dwNpcTemplateID;
		BOOL		bDieIDMonitor;
	};

    struct G2O_NPC_MONEY : GL_MESSAGE_HEADER
    {
        UINT32      dwNpcTemplateID;
        BOOL        bMoneyStat;
        INT32       nMoneyCount;
    };

	struct G2O_CONSECUTIVE_KILL_NPC_COUNT : GL_MESSAGE_HEADER
	{
		INT32		nConsecutiveKillNpcCount;
	};
	struct G2O_MOMENTARY_KILL_NPC_COUNT : GL_MESSAGE_HEADER
	{
		INT32		nMomentaryKillNpcCount;		
	};

	struct  G2O_CLIENT_HARDWARE_INFO : GL_MESSAGE_HEADER
	{
		struct stCpuInfo
		{
			UINT8	NumberOfCores;
			UINT8	NumberOfLogicalProcessors;
			UINT16	Family;
			UINT16	Level;
			UINT16	Revision;
			UINT16	AddressWidth;
			UINT16	MaxClockSpeed;
			UINT16	L2CacheSize;
			UINT16	L3CacheSize;
			char	Name[MAX_DEVICE_STRING_LEN];
			char	Version[MAX_DEVICE_STRING_LEN];
			char	Stepping[MAX_DEVICE_STRING_LEN];
		};

		struct stMemoryInfo
		{
			UINT16 MemoryType;
			UINT32 Speed;
			UINT64 Capacity;
		};

		struct stDiskInfo
		{
			char	Model[MAX_DEVICE_STRING_LEN];
			char	MediaType[MAX_DEVICE_STRING_LEN];
			UINT64	Size;
		};

		struct stNetworkAdapterInfo
		{
			char	Name[MAX_DEVICE_STRING_LEN];
			char	AdapterType[MAX_DEVICE_STRING_LEN];
			char	NetworkAdapterInfo[MAX_NETWORK_ADAPTERINFO_STRING_LEN];
		};

		struct stVideoInfo
		{
			char	VideoProcessor[MAX_DEVICE_STRING_LEN];
			char	Name[MAX_DEVICE_STRING_LEN];
			UINT16	VideoMemoryType;
			UINT32	AdapterRAM;
			UINT32	CurrentBitsPerPixel;
			UINT32	CurrentHorizontalResolution;
			UINT32	CurrentRefreshRate;
			UINT32	CurrentVerticalResolution;
		};

		UINT32					dwRoleID;

		stCpuInfo				stcpuinfo;
		stMemoryInfo			stmemoryinfo;
		stDiskInfo				stdiskinfo;
		stVideoInfo				stvideoinfo;
		stNetworkAdapterInfo	stnetworkadapterinfo;
	};

	struct G2O_CLIENT_FPS_INFO : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		UINT8		byGameFps;
		UINT8		byCpuFps;
		UINT8		byGpuFps;
		UINT16		wGateDelay;
		UINT16		wGameDelay;
	};

	struct G2O_ROLE_ANTI_CHEAT_INFO : GL_MESSAGE_HEADER
	{
		UINT32		dwRoleID;
		INT32		nSceneTemplateID;
		UINT32		dwJigsawSn;
		UINT8		byAction;
		INT32		nErrCode;
		INT32		nImageIndex;
		INT32		nRealAnswer;
		INT32		nRealAnswerBlockX;
		INT32		nRealAnswerBlockY;
		INT32		nRoleAnswer;
	};

};
#pragma pack(pop)

#endif  // _g2o_MESSAGE_H_