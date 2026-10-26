/********************************************************************
	created:	18:9:2013   10:02
	file:		role_guild_data.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GUILD_H_
#define _H_GUILD_H_

#include "guild_def.h"

struct GUILD_BUY_AURA_RECORD
{
    INT32       nType;
    INT32       nTime;
    INT8        byCount;
};

class CRole;

class CRoleGuildData
{
public:
    CRoleGuildData();
    ~CRoleGuildData();

    BOOL    Init(CRole *poRole);
    BOOL    UnInit();

    BOOL    Save(char *pData, UINT32 &rdwSize);
    BOOL    Load_v_1(const char *pcData, UINT32 dwSize);
    BOOL    Load_v_2(const char *pcData, UINT32 dwSize);
    BOOL    Load_v_3(const char *pcData, UINT32 dwSize);

    BOOL    CheckAddRecord(INT32 nType, UINT8 byLimitCount);

    BOOL    AddBuyAuraCount(INT32 nType);
    INT32   GetBuyAuraCount(INT32 nType);

    INT32   CalculateFundLimit(INT32 nPosition, INT32 nMoney);
    INT32   CalculateResLimit(INT32 nPosition, INT32 nRes);


    GUILD_BUY_AURA_RECORD   *GetFirstRecord();
    GUILD_BUY_AURA_RECORD   *GetNextRecord();
    
    inline INT32   GetSalary()      { return m_nSalary; }
    inline void    SetSalary(INT32 nSalary)      { m_nSalary = nSalary; }

    inline UINT32   GetCD()     { return m_dwCD; }
    void    SetCD(UINT32 dwCD);

    BOOL    CanRewardAchievement(INT32 nID);
    char*   GetAchievementList()    { return m_Achievement; }
    BOOL    SetAchievementReward(INT32 nID);

private:
    typedef std::list<GUILD_BUY_AURA_RECORD>     GUILD_AURA__RECORD_LIST;
    GUILD_AURA__RECORD_LIST         m_RecordList;
    GUILD_AURA__RECORD_LIST::iterator   m_Cursor;

    INT32       m_nDonateMoneyPerDay;
    INT32       m_nDonateMoneyDayTime;    // day
    INT32       m_nDonateResPerDay;
    INT32       m_nDonateResDayTime;

    INT32       m_nSalary;

    UINT32      m_dwCD;

    char        m_Achievement[GUILD_MAX_ACHI_ARRAY_LENGTH];


    CRole       *m_poRole;
};









#endif //_H_GUILD_H_



