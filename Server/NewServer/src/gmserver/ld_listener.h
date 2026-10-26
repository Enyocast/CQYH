#ifndef _H_LD_LISTENER_H_
#define _H_LD_LISTENER_H_

#include "gm_svr_def.h"


struct LD_REG_DATA
{
    UINT32      dwUserID;
    INT32       nGroupID;
};

class CLDListener
{
public:
    static CLDListener & GetInstance();

    BOOL    Init();
    BOOL    UnInit();

    void    ChangeGroupID(UINT32 dwUserID, INT32 nGroupID);
    void    RegisterGroupID(UINT32 dwUserID, INT32 nGroupID);
    void    UnRegisterGroupID(UINT32 dwUserID);
    BOOL    _IsExistLD(UINT32 dwUserID);

    INT32   GetLDRegNum()       { return m_nLDNum; }
    LD_REG_DATA * GetLDRegData(INT32 nIndex)    { LOG_PROCESS_ERROR(nIndex < m_nLDNum);  return &m_LDRegList[nIndex]; Exit0: return NULL; }

protected:
    CLDListener();
    ~CLDListener();

    static CLDListener    m_Instance;
private:

    INT32       m_nLDNum;
    LD_REG_DATA m_LDRegList[MAX_GM_USER];


};






#endif //_H_LD_LISTENER_H_
