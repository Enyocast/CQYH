#include "stdafx.h"
#include "ai_manager.h"

#include "zlib.h"

#include "string_def.h"
#include "lua_script.h"
#include "script_mgr.h"
#include "btnod.h"
#include "bt_manager.h"

CAIManager CAIManager::ms_Instance;
const NEW_AI_DATA* g_pcLoadingNewAIData = NULL;

CAIManager::CAIManager()
{
    memset(m_TemplateData, 0, sizeof(m_TemplateData));
    m_nCurrentDataIndex = 0;
}

CAIManager::~CAIManager()
{
    UnInit();
}

BOOL CAIManager::Init(void)
{
    INT32 nRetCode = 0;

    memset(m_TemplateData, 0, sizeof(m_TemplateData));
    m_nCurrentDataIndex = 0;

    nRetCode = Reload();
    LOG_PROCESS_ERROR(nRetCode);

    return TRUE;
Exit0:

    return FALSE;
}

BOOL CAIManager::UnInit(void)
{

    return TRUE;
}

CAIManager& CAIManager::GetInstance(void)
{
    return ms_Instance;
}

BOOL CAIManager::Reload(void)
{
    INT32 nRetCode = 0;
    CLoadAIData LoadAIData;
    UINT64 qwStartTick = GetTickCountEx();

    LoadAIData.m_nFailCount = 0;
    LoadAIData.m_nDataIndex = (m_nCurrentDataIndex + 1) % 2;

    nRetCode = CDataManager<NEW_AI_DATA>::GetInstance().Traverse(LoadAIData);
    LOG_PROCESS_ERROR(nRetCode);

    m_nCurrentDataIndex = LoadAIData.m_nDataIndex;

    INF("read %d / %d ai template successfully (cost %d ms)",
        CDataManager<NEW_AI_DATA>::GetInstance().GetDataCount() - LoadAIData.m_nFailCount,
        CDataManager<NEW_AI_DATA>::GetInstance().GetDataCount(),
        GetTickCountEx() - qwStartTick);

    return TRUE;
Exit0:
    return FALSE;
}
//
//BOOL _ExportBT(char* pszPointer, BTNod* pNode, INT32 nLevel)
//{
//    INT32 nRetCode = 0;
//    BTNod* pChild = NULL;
//
//    LOG_PROCESS_ERROR(pszPointer);
//    LOG_PROCESS_ERROR(pNode);
//
//    *(INT32*)pszPointer = nLevel;
//    pszPointer += sizeof(INT32);
//
//    memcpy(pszPointer, pNode, sizeof(BTNod));
//    pszPointer += sizeof(BTNod);
//
//    pChild = pNode->child;
//    while (pChild)
//    {
//        nRetCode = _ExportBT(pszPointer, pChild, nLevel + 1);
//        LOG_PROCESS_ERROR(nRetCode);
//
//        pChild = pChild->sibling;
//    }
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}
//
//BOOL _ImportBT(char* pszPointer, BTNod* pNode, INT32 nLevel)
//{
//    INT32 nRetCode = 0;
//    BTNod* pChild = NULL;
//
//    LOG_PROCESS_ERROR(pszPointer);
//    LOG_PROCESS_ERROR(pNode);
//
//    if (*(INT32*)pszPointer == nLevel + 1)
//    {
//        
//    }
//    else if (*(INT32*)pszPointer == nLevel)
//    {
//        pszPointer += sizeof(INT32);
//
//        memcpy(pNode, pszPointer, sizeof(BTNod));
//        pszPointer += sizeof(BTNod);
//
//        pChild = pNode->child;
//        while (pChild)
//        {
//            nRetCode = _ImportBT(pszPointer, pChild, nLevel + 1);
//            LOG_PROCESS_ERROR(nRetCode);
//
//            pChild = pChild->sibling;
//        }
//    }
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}

BOOL CAIManager::CLoadAIData::operator()(const NEW_AI_DATA* pAIData)
{
    BOOL nRetCode = FALSE;
    char szFilePath[MAX_PATH];
    char szCacheFileName[MAX_PATH];
    AI_TEMPLATE* pAITemplate = NULL;
    AI_TEMPLATE* pOldAITemplate = NULL;
    IFile* pReadCacheFile = NULL;
    char* pszFileData = NULL;
    BOOL bLoaded = FALSE;
    BOOL bNewScript = FALSE;
    FILE* pWriteCacheFile = NULL;
    //static char s_szFileData[1024 * 1024];
    //char* pszPointer = s_szFileData;

    LOG_PROCESS_ERROR(pAIData);

#ifdef _ROBOT
    if (pAIData->nAIID != 99 && pAIData->nAIID != 10)
        return TRUE;
#else
    if (pAIData->nAIID == 99 || pAIData->nAIID == 10)
        return TRUE;
#endif  // _ROBOT

    LOG_PROCESS_ERROR(pAIData->nAIID >= 0 && pAIData->nAIID < MAX_AI_ID);
    pAITemplate = &CAIManager::GetInstance().m_TemplateData[m_nDataIndex][pAIData->nAIID];
    pOldAITemplate = &CAIManager::GetInstance().m_TemplateData[(m_nDataIndex + 1) % 2][pAIData->nAIID];

    pAITemplate->dwDataCRC = crc32(0, (const Bytef*)pAIData, sizeof(NEW_AI_DATA));
    g_pcLoadingNewAIData = pAIData;

    snprintf(szFilePath, MAX_PATH, "%s/%s/main.lua", NEW_AI_SCRIPT_FOLDER, pAIData->szScriptName);

    pAITemplate->pScript = CScriptMgr::GetInstance().FindScript(szFilePath);
    if (pAITemplate->pScript == NULL)
    {
        pAITemplate->pScript = CScriptMgr::GetInstance().NewScript(szFilePath);
        LOG_PROCESS_ERROR(pAITemplate->pScript);

        bNewScript = TRUE;
    }

    pAITemplate->dwScriptCRC = pAITemplate->pScript->GetCRC();

    if (pOldAITemplate->dwScriptCRC == pAITemplate->dwScriptCRC &&
        pOldAITemplate->dwDataCRC == pAITemplate->dwDataCRC)
    {
        for (INT32 nIndex = evtAIBegin; nIndex < evtAIEnd; ++ nIndex )
        {
            if (pAITemplate->pTreeList[nIndex - evtAIBegin] != NULL)
            {
                CBTManager::GetInstance().DestroyBT(pAITemplate->pTreeList[nIndex - evtAIBegin]);
                pAITemplate->pTreeList[nIndex - evtAIBegin] = NULL;
            }
            pAITemplate->pTreeList[nIndex - evtAIBegin] = CBTManager::GetInstance().CopyBT(pOldAITemplate->pTreeList[nIndex - evtAIBegin]);
        }

        bLoaded = TRUE;
    }

    if (!bLoaded)
    {
        if (!bNewScript)
        {
            nRetCode = pAITemplate->pScript->Execute();
            LOG_PROCESS_ERROR(nRetCode);
        }

        for (INT32 nIndex = evtAIBegin; nIndex < evtAIEnd; ++ nIndex )
        {
            if (pAITemplate->pTreeList[nIndex - evtAIBegin] != NULL)
            {
                CBTManager::GetInstance().DestroyBT(pAITemplate->pTreeList[nIndex - evtAIBegin]);
                pAITemplate->pTreeList[nIndex - evtAIBegin] = NULL;
            }

            if (pAITemplate->pScript->IsTableExist(g_BTEventName[nIndex]))
            {
                nRetCode = pAITemplate->pScript->CallFunction(LOAD_BEHAVIOR_TREE, "s:o", g_BTEventName[nIndex], &pAITemplate->pTreeList[nIndex - evtAIBegin]);
                if (FALSE == nRetCode || NULL == pAITemplate->pTreeList[nIndex - evtAIBegin])
                {
                    CRI("AIID=%d, script=%s, tree=%s existed but loaded nothing", 
                        pAIData->nAIID, pAIData->szScriptName, g_BTEventName[nIndex]);
                }
                else
                {
#ifdef _ROBOT
					CBTManager::GetInstance().PrintBT(pAITemplate->pTreeList[nIndex - evtAIBegin], 0);
#endif	// _ROBOT
                }
            }
        }
    }

    g_pcLoadingNewAIData = NULL;

    return TRUE;
Exit0:
    if (pAIData)
        CRI("failed to generate ai %d template data", pAIData->nAIID);
    m_nFailCount++;

    if (pReadCacheFile)
        pReadCacheFile->Close();
    if (pWriteCacheFile)
        fclose(pWriteCacheFile);

    return TRUE;
}

