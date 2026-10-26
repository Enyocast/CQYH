
#ifndef _H_SERVER_MGR_H_
#define _H_SERVER_MGR_H_

#include "server_def.h"

class CServerMgr
{
public:
    static CServerMgr & GetInstance();

    BOOL    Init();
    BOOL    UnInit();

    void    ResetSelectedServer();
    BOOL    UpdateSelectServer();

    INT32   GetSelectedNum()        { return m_nSelectedSessionNum; }
    UINT32  GetSessionIDByIndex(INT32 nIndex);

    BOOL    IsServerSelected()      { return m_nSelectedSessionNum > 0; }
    BOOL    IsSingleSelected()      { return m_nSelectedSessionNum == 1; }
    BOOL    IsMultiSelected()       { return m_nSelectedSessionNum > 1; }


protected:
    


private:
    static CServerMgr   m_Instance;

    INT32   m_nSelectedSessionNum;
    UINT32  m_SessionIDList[MAX_GM_SESSION_COUNT];

};









#endif //_H_SERVER_MGR_H_

