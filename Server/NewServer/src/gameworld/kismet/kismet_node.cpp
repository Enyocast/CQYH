#include "stdafx.h"
#include "kismet_node.h"

extern KIS_FUNC     g_KismetFuncList[kotActionEnd - kotActionBegin];
extern KIS_EVENT    g_KismetEventList[kotEventEnd - kotEventBegin];

BOOL kisInit(void)
{
    return TRUE;
}

BOOL kisUnInit(void)
{
    return TRUE;
}

KIS_INSTANCE* kisCreateList(CScene* poScene, KIS_TEMPLATE* pTemplate)
{
    KIS_INSTANCE* pResult = NULL;

    LOG_PROCESS_ERROR(poScene);
    LOG_PROCESS_ERROR(pTemplate);

    pResult = new KIS_INSTANCE;
    LOG_PROCESS_ERROR(pResult);

    pResult->pTemplate = pTemplate;
    memcpy(pResult->nVarList, pTemplate->nVarInitList, sizeof(pResult->nVarList));
    memcpy(pResult->EventNodePool, pTemplate->EventNodePool, sizeof(pResult->EventNodePool));
    pResult->poScene = poScene;
    pResult->nCurrentActiveLinkList = 0;

    return pResult;
Exit0:
    SAFE_DELETE(pResult);

    return NULL;
}

BOOL kisDestroyList(KIS_INSTANCE* pKisInstance)
{
    LOG_PROCESS_ERROR(pKisInstance);

    SAFE_DELETE(pKisInstance);

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL _kisActivePoint(KIS_INSTANCE* pKisInstance, KIS_LINK_POINT* pLinkPoint, INT32 nCurrentTime)
{
    INT32 nNextLinkList = pKisInstance->nCurrentActiveLinkList + 1;
    nNextLinkList %= 2;

    for (INT32 nLnkIndex = 0; nLnkIndex < pLinkPoint->nLinkCount; nLnkIndex++)
    {
        KIS_LINK* pLink = pLinkPoint->pLinkList[nLnkIndex];
        LOG_PROCESS_ERROR(pLink);

        pLink->bHasImpulse = true;
        if (pLink->nDelayTime > 0)
        {
            LOG_PROCESS_ERROR(pLink->nTimerID > KIS_INVALID_TIMER_ID && pLink->nTimerID < KIS_MAX_TIMER);
            pKisInstance->nTimerList[pLink->nTimerID] = nCurrentTime + pLink->nDelayTime;
        }
        pKisInstance->ActiveLinkList[nNextLinkList].push_back(pLink);
    }

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL _kisCheckLink(KIS_INSTANCE* pKisInstance, KIS_LINK* pLink, INT32 nCurrentTime)
{
    INT32 nOutputMask;
    INT32 nRetCode = 0;

    LOG_PROCESS_ERROR(pKisInstance);
    LOG_PROCESS_ERROR(pLink);

    LOG_PROCESS_ERROR(pLink->nTimerID >= KIS_INVALID_TIMER_ID && pLink->nTimerID < KIS_MAX_TIMER);
    LOG_PROCESS_ERROR(pLink->bHasImpulse);

    if (pLink->nTimerID == KIS_INVALID_TIMER_ID || 
         pKisInstance->nTimerList[pLink->nTimerID] < nCurrentTime)
    {
        KIS_NODE* pNode = pLink->pOutputNode;
        LOG_PROCESS_ERROR(pNode);
        LOG_PROCESS_ERROR(pNode->nNodeType >= kotActionBegin && pNode->nNodeType < kotActionEnd);

        KIS_FUNC pFunc = g_KismetFuncList[pNode->nNodeType - kotActionBegin];
        LOG_PROCESS_ERROR(pFunc);

        nOutputMask = pFunc(pKisInstance->poScene, pKisInstance, pLink->nInputPoint, pNode->pPropList, pNode->nPropCount, 
            pNode->pVarPointList, pNode->nVarPointCount);

        for (INT32 nOutputIndex = 0; nOutputIndex < pNode->nOutputPointCount; nOutputIndex++)
        {
            KIS_LINK_POINT* pOutputLinkPoint = pNode->pOutputPointList[nOutputIndex];
            LOG_PROCESS_ERROR(pOutputLinkPoint);

            if (nOutputMask & (1 << nOutputIndex))
            {
                nRetCode = _kisActivePoint(pKisInstance, pOutputLinkPoint, nCurrentTime);
                LOG_PROCESS_ERROR(nRetCode);
            }
        }
    }
    else
    {
        INT32 nNextLinkList = pKisInstance->nCurrentActiveLinkList + 1;
        nNextLinkList %= 2;

        pKisInstance->ActiveLinkList[nNextLinkList].push_back(pLink);
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL kisTriggerEvent(INT32 nNodeType, INT32 nEventType, KIS_INSTANCE* pKisInstance, INT32 nOriginatorType, INT32 nOriginatorID, 
                     INT32 nInstigatorType, INT32 nInstigatorID, INT32 nCurrentTime)
{
    INT32 nRetCode = 0;
    KIS_TEMPLATE* pTemplate = NULL;
    INT32 nEventNode = 0;
    KIS_EVENT_NODE* pEventNode = NULL;
    BOOL bFound = FALSE;
    UINT32 dwOutputPoint = 0;
    KIS_EVENT pEventFunc = NULL;

    LOG_PROCESS_ERROR(nNodeType >= kotEventBegin && nNodeType < kotEventEnd);
    LOG_PROCESS_ERROR(pKisInstance);

    pTemplate = pKisInstance->pTemplate;
    LOG_PROCESS_ERROR(pTemplate);

    nEventNode = pTemplate->pEventList[nNodeType - kotEventBegin];
    while (nEventNode > 0 && !bFound)
    {
        pEventNode = pKisInstance->EventNodePool + nEventNode;

        if (pEventNode->nTriggerCount >= pEventNode->pNode->nMaxTriggerCount)
        {
            nEventNode = pEventNode->nNextEvent;
            continue;
        }

        for (INT32 nVPIndex = 0; nVPIndex < pEventNode->pNode->nVarPointCount && !bFound; nVPIndex++)
        {
            for (INT32 nVarIndex = 0; nVarIndex < pEventNode->pNode->pVarPointList[nVPIndex]->nVarCount && !bFound; nVarIndex++)
            {
                INT32 nVarID = pEventNode->pNode->pVarPointList[nVPIndex]->nVarIDList[nVarIndex];
                LOG_PROCESS_ERROR(nVarID > 0 && nVarID <= pTemplate->nVarCount);

                if (pKisInstance->nVarList[nVarID] == nOriginatorID &&
                    pTemplate->nVarTypeList[nVarID] == nOriginatorType)
                {
                    pEventNode->nTriggerCount++;
                    bFound =  TRUE;
                }
            }
        }

        if (!bFound)
            nEventNode = pEventNode->nNextEvent;
    }

    PROCESS_ERROR(bFound);

    pEventFunc = g_KismetEventList[nNodeType - kotEventBegin];
    LOG_PROCESS_ERROR(pEventFunc);

    dwOutputPoint = pEventFunc(nEventType, pKisInstance->poScene, pKisInstance, 
        pEventNode->pNode->pPropList, pEventNode->pNode->nPropCount, 
        pEventNode->pNode->pVarPointList, pEventNode->pNode->nVarPointCount,
        nOriginatorType, nOriginatorType, nInstigatorType, nInstigatorID);

    for (INT32 nOutputIndex = 0; nOutputIndex < pEventNode->pNode->nOutputPointCount; nOutputIndex++)
    {
        if (!(dwOutputPoint & (1 << nOutputIndex)))
            continue;
        KIS_LINK_POINT* pOutputLinkPoint = pEventNode->pNode->pOutputPointList[nOutputIndex];
        LOG_PROCESS_ERROR(pOutputLinkPoint);

        nRetCode = _kisActivePoint(pKisInstance, pOutputLinkPoint, nCurrentTime);
        LOG_PROCESS_ERROR(nRetCode);
    }

    return TRUE;
Exit0:
    return FALSE;
}

BOOL kisActivateList(KIS_INSTANCE* pKisInstance, INT32 nCurrentTime)
{
    INT32 nRetCode = 0;
    KIS_TEMPLATE* pTemplate = NULL;

    LOG_PROCESS_ERROR(pKisInstance);

    pTemplate = pKisInstance->pTemplate;
    LOG_PROCESS_ERROR(pTemplate);

    for (INT32 nSeqIndex = 0; nSeqIndex < pTemplate->nSeqCount; nSeqIndex++)
    {
        KIS_SEQUENCE* pSequence = pTemplate->pSequenceList[nSeqIndex];
        LOG_PROCESS_ERROR(pSequence);

        std::list<KIS_LINK*>& rActiveLinkList = pKisInstance->ActiveLinkList[pKisInstance->nCurrentActiveLinkList];

        for (std::list<KIS_LINK*>::iterator it = rActiveLinkList.begin(); it != rActiveLinkList.end(); ++it)
        {
            nRetCode = _kisCheckLink(pKisInstance, *it, nCurrentTime);
            LOG_PROCESS_ERROR(nRetCode);
        }

        rActiveLinkList.clear();
        pKisInstance->nCurrentActiveLinkList++;
        pKisInstance->nCurrentActiveLinkList %= 2;
    }

    return TRUE;
Exit0:
    return FALSE;
}
