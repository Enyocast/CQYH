#ifndef _H_MS_GUILD_ACHI_MGR_H_
#define _H_MS_GUILD_ACHI_MGR_H_

#include "guild_achievement.h"
#include "guild_def.h"
#include "base_list.h"

class CMsGuild;

class CMSGuildAchiMgr
{
public:
    BOOL    Init();
    BOOL    UnInit();
    static CMSGuildAchiMgr & GetInstance();
protected:
    CMSGuildAchiMgr();
    ~CMSGuildAchiMgr();

    static CMSGuildAchiMgr  m_Instance;

public:

    BOOL AddAchiType(INT32 nType, INT32 nParam1, INT32 nAchiID);
    //BOOL DelAchiType(INT32 nType, INT32 nParam1, INT32 nAchiID);
    BOOL Clear();

    void RecordAchiCondition(INT32 nType, CMsGuild *poMsGuild);



private:
    CBaseList    m_con[GUILD_ACHI_TYPE_NUM];


    struct ACHI_CONDITION : BASE_LIST_NODE
    {
        INT32   nConditionType;
        INT32   nParam1;

        INT32   nAchievementID;
    };
};










#endif //_H_MS_GUILD_ACHI_MGR_H_

