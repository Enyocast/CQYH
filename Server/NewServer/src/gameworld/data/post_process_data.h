#ifndef _POST_PROCESS_DATA_H_
#define _POST_PROCESS_DATA_H_

struct ATTRIBUTE_DATA;
struct EQUIP_DATA;
struct SET_DATA;
struct SOUL_DATA;
struct REFINE_ATTR_DATA;
struct SHOP_DATA;
struct AURA_ENTRY;
struct MISSILE_DATA;
struct QUEST_DATA;
struct SPELL_PROGRESS_DATA;
struct SPELL_VAR;
struct SPELL_ENTRY;
struct ADVENTURE_DATA;
struct ATTR_CONV;
struct GUILD_BUILDING_DATA;
struct GUILD_DUNGEON_DATA;
struct GUILD_WELFARE_DATA;
struct ACHIEVEMENT_DATA;
struct HANDBOOK_DATA;
struct RUNE_DATA;
struct KILL_NPC_QUEST_DATA;
struct TITLE_TEMPLATE;

BOOL g_ProcessAttributeData(ATTRIBUTE_DATA* pData, BOOL bInit);
BOOL g_ProcessEquipData(EQUIP_DATA* pData, BOOL bInit);
BOOL g_ProcessSetData(SET_DATA* pData, BOOL bInit);
BOOL g_ProcessSoulData(SOUL_DATA* pData, BOOL bInit);
BOOL g_ProcessRefineAttrData(REFINE_ATTR_DATA* pData, BOOL bInit);
BOOL g_ProcessShopData(SHOP_DATA* pData, BOOL bInit);
BOOL g_ProcessAuraData(AURA_ENTRY* pData, BOOL bInit);
BOOL g_ProcessMissileData(MISSILE_DATA* pData, BOOL bInit);
BOOL g_ProcessQuestData(QUEST_DATA* pData, BOOL bInit);
BOOL g_ProcessSpellProgressData(SPELL_PROGRESS_DATA* pData, BOOL bInit);
BOOL g_ProcessSpellVar(SPELL_VAR* pData, BOOL bInit);
BOOL g_ProcessSpellEntry(SPELL_ENTRY* pData, BOOL bInit);
BOOL g_ProcessAdventureData(ADVENTURE_DATA* pData, BOOL bInit);
BOOL g_ProcessGuildBuilding(GUILD_BUILDING_DATA* pData, BOOL bInit);
BOOL g_ProcessGuildDungeon(GUILD_DUNGEON_DATA* pData, BOOL bInit);
BOOL g_ProcessGuildWelfare(GUILD_WELFARE_DATA* pData, BOOL bInit);
BOOL g_ProcessAchievementData(ACHIEVEMENT_DATA* pData, BOOL bInit);
BOOL g_ProcessHandbookData(HANDBOOK_DATA* pData, BOOL bInit);
BOOL g_ProcessRuneData(RUNE_DATA* pData, BOOL bInit);
BOOL g_ProcessKillNpcQuestData(KILL_NPC_QUEST_DATA* pData, BOOL bInit);
BOOL g_ProcessTitleTemplate(TITLE_TEMPLATE* pData, BOOL bInit);

#endif  // _POST_PROCESS_DATA_H_