/********************************************************************
	created:	27:6:2014   10:51
	file:		arena.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_ARENA_H_
#define _H_ARENA_H_

class CRole;

class CArena
{
public:
    CArena();
    ~CArena();

    BOOL    Init(CRole *pOwner);
    BOOL    UnInit();

    BOOL    Load_v_1(const char* pcData, UINT32 dwSize);
    BOOL    Save(const char* pcData, UINT32& rdwSize);

    BOOL    IsInSeason();
    BOOL    JoinNewSeason();
    BOOL    QuitSeason();

    INT32   GetSeasonNum()      { return m_nSeasonNum; }

    UINT8   GetCurSeasonVicTime()   { return m_byCurSeasonVictoryTimes; }
    UINT8   GetPointSeasonVicTime() { return m_byPointSeasonVictoryTimes; }

    BOOL    CanGetCommonReward();
    BOOL    GetCommonReward(UINT32 dwItemID, INT32 nMoney);

    BOOL    Win();
    BOOL    Defeated();


    INT32   GetHP()             { return m_nHP; }
    void    SetHP(INT32 nHp)    { m_nHP = nHp; }


private:
    CRole       *m_pOwner;
    INT32       m_nJoinTime;
    INT32       m_nSeasonNum;
    UINT8       m_bIsInSeason;

    UINT8       m_byCurSeasonVictoryTimes;
    UINT8       m_byPointSeasonVictoryTimes;

    INT32       m_nCurSeasonEndTime;
    INT32       m_nPointSeasonEndTime;

    INT32       m_nHP;



};









#endif //_H_ARENA_H_





