#ifndef _H_ORDER_MGR_H_
#define _H_ORDER_MGR_H_



class COrderMgr
{
public:
    static COrderMgr & GetInstance();
    
    BOOL    Init();
    BOOL    UnInit();

    BOOL    MainLoop();

protected:
    COrderMgr();
    ~COrderMgr();

    static COrderMgr    m_Instance;
private:
    INT32   m_nTickCount;
};







#endif //_H_ORDER_MGR_H_
