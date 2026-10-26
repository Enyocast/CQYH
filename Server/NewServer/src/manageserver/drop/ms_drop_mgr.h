#ifndef _MS_DROP_MGR_H_
#define _MS_DROP_MGR_H_

struct DROP_LIMIT
{
    UINT32 dwStartTime;
    INT32 nLimitDuration;
    INT32 nLimitCount;
    INT32 nCurCount;
};

class CMsDropMgr
{
public:
    static CMsDropMgr& GetInstance() { return ms_Instance; };

    BOOL Init();
    BOOL UnInit();
    BOOL MainLoop(void);
    void OnDrop(INT32 itemid, INT32 itemcount);
    BOOL SendAllDropLimits(UINT32 dwGSSessionID);

    void PrintLimitInfo() const;

private:
    static CMsDropMgr ms_Instance;

    void _CheckExpire(DROP_LIMIT& droplimit);

    typedef std::map<INT32, DROP_LIMIT> DROP_LIMIT_MAP;
    DROP_LIMIT_MAP m_drop_limit_map;

    UINT32 m_last_check_time;

    CMsDropMgr() : m_last_check_time(0) {}
};

#endif // _MS_DROP_MGR_H_
