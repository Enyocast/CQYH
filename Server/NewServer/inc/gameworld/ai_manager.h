#ifndef _AI_MANAGER_H_
#define _AI_MANAGER_H_

#include "ai_data.h"
#include "bt_event.h"

class CLuaScript;
struct BTNod;
class CRole;
class CNpc;

struct AI_TEMPLATE
{
    CLuaScript* pScript;
    BTNod*  pTreeList[evtAIEnd - evtAIBegin];
    UINT32      dwScriptCRC;
    UINT32      dwDataCRC;
};

class CAIManager
{
public:
	CAIManager();
	~CAIManager();

	BOOL Init(void);
	BOOL UnInit(void);
	static CAIManager& GetInstance(void);
    BOOL Reload(void);

    inline const AI_TEMPLATE* GetTemplate(INT32 nAIID);

private:
    struct CLoadAIData
    {
        INT32 m_nFailCount;
        INT32 m_nDataIndex;
        BOOL operator()(const NEW_AI_DATA* pAIData);
    };

    struct CCharTraverser
    {
        BOOL operator()(UINT32 dwRoleID, CRole* pRole);
        BOOL operator()(UINT32 dwNpcID, CNpc* pNpc);
    };

private:
    static CAIManager   ms_Instance;
    AI_TEMPLATE         m_TemplateData[2][MAX_AI_ID];
    INT32               m_nCurrentDataIndex;

    friend class CGlobalDataManager;
};

inline const AI_TEMPLATE* CAIManager::GetTemplate(INT32 nAIID)
{
    LOG_PROCESS_ERROR(nAIID > 0 && nAIID < MAX_AI_ID);
    return &m_TemplateData[m_nCurrentDataIndex][nAIID];
Exit0:
    return NULL;
}

#endif // _AI_MANAGER_H_
