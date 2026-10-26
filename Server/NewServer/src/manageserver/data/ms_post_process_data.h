//  Allan Tao[5.8.2014] 

#ifndef _H_MS_POST_PROCESS_DATA_H_
#define _H_MS_POST_PROCESS_DATA_H_


struct MS_MASTER_GIFT_TEMPLATE;
struct GUILD_BUILDING_DATA;
struct ACHIEVEMENT_DATA;
struct  GUILD_ACHIEVEMENT;
struct GUILD_ACHI_CDTN;

BOOL g_ProcessMasterGift(MS_MASTER_GIFT_TEMPLATE* pData, BOOL bInit);
BOOL g_ProcessAchievement(ACHIEVEMENT_DATA* pData, BOOL bInit);
BOOL g_ProcessGuildAchievement(GUILD_ACHIEVEMENT *pData, BOOL bInit);
BOOL g_ProcessGuildAchiCdtn(GUILD_ACHI_CDTN *pData, BOOL bInit);

#endif // !_H_MS_POST_PROCESS_DATA_H_







