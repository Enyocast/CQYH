#ifndef _H_GUILD_DB_DEF_V_1_H_
#define _H_GUILD_DB_DEF_V_1_H_

#if defined(WIN32) | defined(WIN64)
	#pragma warning(disable:4200)
#endif  // WIN32

#pragma pack(push, 1)

namespace GUILD_DEF_VER_1
{
    enum GUILD_DB_DATA_BLOCK_TYPE
    {
        gbtInvalid = -1,

        gbtBase,
        gbtWelfare,
        gbtBuilding,
        gbtDiplomat,
        gbtDungeon,
        gbtStorage,
        gbtHistory,
        gbtStorageHistory,

        gbtTotal
    };

    struct GUILD_DB_DATA_BLOCK
    {
        UINT8	byBlockType;
        UINT32	dwBlockSize;
        UINT32	dwStartOffset;
    };

    struct GUILD_DB_DATA  // ¥Û‘º52531
    {
        UINT32	dwLen;		// including length dword
        UINT32	dwCRC;		// calculate from version
        UINT32	dwVersion;
        UINT32  dwGuildID;
        GUILD_DB_DATA_BLOCK	BlockTable[gbtTotal];
        char    GuildData[0];
    };


    struct GUILD_DB_BASE 
    {
        UINT32      dwRoutineConsumeTime;
        INT32       nState;
        INT32       nMoney;
        INT32       nWood;
        INT32       nHerb;
        INT32       nCrystal;
        INT32       nSilver;
        UINT32      dwCalculateResourceTime;
        UINT16      wStorageRight[7];       // GUILD_POSITION_COUNT
        INT32       nVariables[256];        // MAX_GUILD_VARIABLE_COUNT
        UINT32      dwSabacEnrollTime;
        UINT8       byOccupiedSabac;
    };

    struct GUILD_DB_WELFARE_UPGRADE 
    {
        UINT8       byType;
        UINT32      dwTime;
    };

    struct GUILD_DB_WELFARE
    {
        UINT8       WelfareAuraLevel[64];       // GUILD_MAX_WELFARE_AURA_COUNT
        UINT8       byUpgradeWelfareNum;
        char        szUpgradeList[0];   // GUILD_DB_WELFARE_UPGRADE
    };

    struct GUILD_DB_BUILDING_DATA 
    {
        UINT64      qwNpcNameID;
        UINT32      dwReviveTime;
        UINT8       byType;
        UINT8       byLevel;
    };

    struct GUILD_DB_BUILDING_UPGRADE 
    {
        UINT64      qwNpcNameID;
        UINT8       byType;
        UINT32      dwTime;
    };

    struct GUILD_DB_BUILDING
    {
        UINT16      wBuildingBufferLength;
        UINT16      wUpgradeBufferLength;
        UINT8       byBuildingNum;
        UINT8       byUpgradeBuildingNum;
        char        Building[0];      // GUILD_DB_BUILDING_DATA, GUILD_DB_BUILDING_UPGRADE
    };

    struct GUILD_DB_DIPLOMAT_DATA 
    {
        UINT32      dwGuildID;
        UINT32      dwEndTime;
    };

    struct GUILD_DB_DIPLOMAT
    {
        UINT32      dwActiveEnemy;
        UINT8       byAllianceNum;
        UINT8       byEnemyNum;

        UINT32      dwRevengeGuildID;
        UINT32      dwAimID;
        UINT32      dwAttackCD;
        UINT32      dwIntruderID;
        UINT32      dwProtectionTime;

        UINT8       byMatchWarCount;
        UINT32      dwMatchWarTime;
        char        Buffer[0];      // GUILD_DB_DIPLOMAT_DATA(GUILD_MAX_ALLIANCE_NUM, GUILD_MAX_ENEMY_NUM)
    };

    struct GUILD_DB_DUNGEON_DATA
    {
        UINT32      dwTemplateID;
        UINT32      dwOwnerID;
        UINT32      dwLeaderID;
        UINT32      dwCreateTime;
    };

    struct GUILD_DB_DUNGEON         // max 32
    {
        UINT8       byDungeonNum;
        char        Data[0];        // GUILD_DB_DUNGEON_DATA
    };

    struct GUILD_DB_STORAGE_ITEM 
    {
        UINT8       byItemSize;
        UINT8       byConSlot;
        UINT8       byItemSlot;
        char        ItemData[0];
    };

    struct GUILD_DB_STORAGE             // max 6*56=336
    {
        UINT16      wItemLength;
        char        Data[0];        // GUILD_DB_STORAGE_ITEM
    };

    struct GUILD_DB_HISTORY_EVENT 
    {
        INT32       nType;
        UINT32      param1;
        UINT32      param2;
        UINT32      param3;
        UINT32      param4;
        UINT32      dwOccurTime;
    };

    struct GUILD_DB_HISTORY             // max 150 , chest history max 100
    {
        UINT16      wNum;
        GUILD_DB_HISTORY_EVENT  Event[0];
    };

    struct GUILD_DB_STORAGE_EVENT 
    {
        UINT8       byItemSize;
        UINT8       byType;
        UINT32      dwRoleID;
        UINT32      dwOccurTime;
        char        ItemBuffer[0];
    };

    struct GUILD_DB_STORAGE_HISTORY             // max 100
    {
        UINT32      dwLength;
        char        Data[0];        // GUILD_DB_STORAGE_EVENT
    };




};

#pragma pack(pop)


#endif //_H_GUILD_DB_DEF_V_1_H_


