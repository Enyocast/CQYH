#ifndef _FCM_H
#define _FCM_H

#include "string_def.h"
#include "free_object_pool.h"
#include "circle_list.h"

struct FCM_CALLBACK
{
    char szUserName[USER_NAME_LEN];
    INT32 nOnlineMinutes, nOfflineMinutes;
};

class CFCMSDKBase;
class CFcmMgr
{
public:
    static CFcmMgr& GetInstance()
    {
        static CFcmMgr ms_Instance;
        return ms_Instance;
    }

    BOOL Init();
    BOOL UnInit();
    BOOL MainLoop();

    void SetOnline(const char* szUserID, UINT32 dwIP);
    void SetOffline(const char* szUserID, UINT32 dwIP);
    void QueryFcmState(const char* szUserID, UINT32 dwIP);

    BOOL PushCallback(const char* szUserID, INT32 nOnlineMinutes, INT32 nOfflineMinutes);
    BOOL PopCallback(FCM_CALLBACK& cb);

private:
    CFCMSDKBase* m_poFCM;

    CFreeObjectPool<FCM_CALLBACK> m_callback_pool;
    CCircleList m_callback_list;

    CFcmMgr() :m_poFCM(NULL) {}
};

#endif // _FCM_H
