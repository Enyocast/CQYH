#ifndef _GLOBAL_DATA_MANAGER_H_
#define _GLOBAL_DATA_MANAGER_H_


#include <string>
#include <list>
#include <map>
#include "thread.h"
#include "circle_list.h"

#define CACHE_FILE_TAG      'cach'
#define CACHE_FILE_VERSION  (2)

struct LOADED_DATA
{
    LOADED_DATA() { pData = NULL; }
    ~LOADED_DATA() { SAFE_DELETE(pData); }
    INT32       nRowIndex;
    INT32       nID;
    const char* pcszName;
    void*       pData;
};

struct LOADED_DATA_LIST
{
    LOADED_DATA_LIST() {}
    ~LOADED_DATA_LIST()
    {
        for (std::list<LOADED_DATA*>::iterator it = DataList.begin();
            it != DataList.end(); ++it)
        {
            LOADED_DATA* pLoadedData = *it;
            SAFE_DELETE(pLoadedData);
        }
    }
    char                    szConfigName[256];
    BOOL                    bInit;
    BOOL                    bOnlyLoadCache;
    BOOL                    bLoaded;
    BOOL                    bSkipped;
    UINT64                  qwStartTick;
    INT32                   nRowCount;
    std::list<LOADED_DATA*> DataList;
};

struct DATA_CACHE_HEADER
{
    UINT32          dwTag;
    UINT32          dwVersion;
    UINT32          dwCRC;
    UINT32          dwFileSize;
    UINT32          dwDataSize;
};

enum LOAD_TASK_TYPE
{
    lttInvalid,

    lttLoadData,
    lttLoadScript,
    lttLoadAI,

    lttTotal
};

struct LOAD_TASK
{
    INT32       nTaskType;
    void*       pTaskData;
};

class CGlobalDataManager
{
public:
    CGlobalDataManager();
    ~CGlobalDataManager();

    BOOL Init(void);
    BOOL UnInit(void);
    BOOL MainLoop(void);

    static CGlobalDataManager& GetInstance(void);

    BOOL AddDataManager(const char* pcszConfigName, void* pDataManager);
    BOOL PushTask(LOAD_TASK* pLoadTask);
    BOOL ReloadAllData(BOOL bThread);
	BOOL PostProcessAllData(void);

	inline INT32 GetDataCount(void);
	void GetDataCRC(UINT32* pdwCRCList);

	INT64 PrintMemoryStat(void);

private:
    static THREAD_DECLARE(_LoadThread)(void * pParam);

    void _LoadingData(LOAD_TASK* pLoadTask);
    void _LoadedData(LOAD_TASK* pLoadTask);

private:
    static CGlobalDataManager       ms_Instance;
    std::list<std::string>          m_LoadDataList;
    std::map<std::string, void*>    m_LoadDataMap;

    CCircleList                     m_LoadingList;
    CCircleList                     m_LoadedList;
	INT32							m_nLoadedCount;

    CThread                         m_LoadThread;
    BOOL                            m_bStop;
};

inline INT32 CGlobalDataManager::GetDataCount(void)
{
	return (INT32)m_LoadDataMap.size();
}

#endif  // _GLOBAL_DATA_MANAGER_H_