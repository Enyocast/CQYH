/********************************************************************
	created:	7:6:2013   16:50
	file:		time_washout_mgr.h
	author:		Allan Tao
	
	purpose:	时间定时淘汰，用于各种记录申请
*********************************************************************/


#ifndef _H_TIME_WASHOUT_MGR_H_
#define _H_TIME_WASHOUT_MGR_H_


struct WASHOUT_BASE 
{
    WASHOUT_BASE    *pPrev;
    WASHOUT_BASE    *pNext;

    UINT8       byType;
    UINT32      dwWashOutTime;
};


struct GUILD_MEMBER_APP : WASHOUT_BASE
{
    UINT32      dwRoleID;
    UINT32      dwGuildID;
};

struct GUILD_ALLIANCE_APP : WASHOUT_BASE 
{
    UINT32      dwSelfGuildID;
    UINT32      dwTargetGuildID;
};



class CTimeWashoutMgr
{
public:
    CTimeWashoutMgr();
    ~CTimeWashoutMgr();

    static CTimeWashoutMgr &GetInstance();
    


    BOOL Init();

    BOOL PushBack(WASHOUT_BASE *pNode);

    BOOL Remove(WASHOUT_BASE *pNode);

    BOOL MainLoop();



private:
    static CTimeWashoutMgr  m_Instance;

private:
    // 因为现在时间类型少，就用最简单的方式来做 Allan Tao[7.6.2013] 
    // 暂定只有24小时一种 Allan Tao[7.6.2013] 
    WASHOUT_BASE    *m_pTimerHeader[1];






};






#endif //_H_TIME_WASHOUT_MGR_H_





