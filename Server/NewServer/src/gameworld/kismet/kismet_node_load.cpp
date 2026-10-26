#include "stdafx.h"
#include "kismet_node.h"

#include "scene_kismet_def.h"

#ifdef _WIN32
    #pragma warning(disable:4200)
#endif  // WIN32

struct KD_VAR
{
    INT32           nType;
    INT32           nVarID;
    INT32           nInitValue;
    INT32           nObjectType;
};

struct KD_VAR_HEADER
{
    INT32           nTag;
    INT32           nVarCount;
    KD_VAR         VarList[0];
};

struct KD_SEQUENCE_HEADER
{
    INT32           nTag;
    INT32           nID;
    INT32           nNodeCount;
};

struct KD_NODE_HEADER
{
    INT32           nType;
    INT32           nNodeID;
    INT32           nOutputPointCount;
};

struct KD_LINK_DATA
{
    INT32           nNodeID;
    INT32           nInputPoint;
};

struct KD_OUTPUT_POINT
{
    INT32           nDelayTime;
    INT32           nLinkCount;
    KD_LINK_DATA    LinkList[0];
};

struct KD_VAR_POINT_HEADER
{
    INT32           nVarPointCount;
};

struct KD_VAR_POINT
{
    INT32           nVarCount;
    INT32           VarIDList[0];
};

struct KD_PROP_HEADER 
{
    INT32           nTag;
    INT32           nPropCount;
    INT32           nPropList[0];
};

struct KD_PROP_VAR_LINK_DATA
{
    INT32           nPropIndex;
    INT32           nVarIndex;
};

struct KD_PROP_VAR_LINK_HEADER
{
    INT32           nTag;
    INT32           nLinkCount;
    KD_PROP_VAR_LINK_DATA   LinkList[0];
};

struct KD_TRIGGER_DATA
{
    INT32           nMaxTriggerCount;
    INT32           nReTriggerDelay;
};
//
//
//BOOL KismetGenerateBTNode( KIS_NODE* pNode, char* pText, char* pEnd, INT32 nDepth )
//{
//    INT32 nRetCode = FALSE;
//
//    LOG_PROCESS_ERROR( pNode );
//    for ( INT32 i = 0; i < pNode->nOutputPointCount; ++i )
//    {
//        LOG_PROCESS_ERROR( kotSeqAct_BTNode == pNode->nNodeType );
//        
//        KIS_LINK_POINT* pLinkGroup = pNode->pOutputPointList[i];
//        LOG_PROCESS_ERROR( pLinkGroup );
//
//        for ( INT32 j = 0; j < pLinkGroup->nLinkCount; ++j )
//        {
//            KIS_LINK* pLink = pLinkGroup->pLinkList[j];
//            LOG_PROCESS_ERROR( pLink );
//
//            KIS_NODE* pChild = pLink->pOutputNode;            
//            LOG_PROCESS_ERROR( pChild );
//
//            for ( INT32 k=0; k < nDepth; ++k )
//                _snprintf( pText + strlen(pText), pEnd - pText, "\t" );
//            //_snprintf( pText + strlen(pText), pEnd - pText, 
//            //    "{ %s, param={%s, %s, %s, %s} },",
//            //    pChild->pPropList[0] );  //TODO: type string
//
//
//            nRetCode = KismetGenerateBTNode( pChild, pText + strlen(pText), pEnd, nDepth+1 );
//            LOG_PROCESS_ERROR( nRetCode );
//        }
//    }
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}
//BOOL KismetGenerateBTScript( KIS_NODE* pNode )
//{
//    INT32 nRetCode = FALSE;
//    char pText[ 1024 * 1024 ] = { 0 }; 
//
//    LOG_PROCESS_ERROR( pNode );
//
//    // generate BTNode table
//    _snprintf( pText+strlen(pText), sizeof(pText)-strlen(pText), "\n" );
//    _snprintf( pText+strlen(pText), sizeof(pText)-strlen(pText), "init_tree\n" ); // TODO:
//    _snprintf( pText+strlen(pText), sizeof(pText)-strlen(pText), "={\n" );
//    for ( INT32 i = 0; i < pNode->nOutputPointCount; ++i )
//    {
//        KIS_LINK_POINT* pLinkGroup = pNode->pOutputPointList[i];
//        LOG_PROCESS_ERROR( pLinkGroup );
//
//        for ( INT32 j = 0; j< pLinkGroup->nLinkCount; ++j )
//        {
//            KIS_LINK* pLink = pLinkGroup->pLinkList[j];
//            LOG_PROCESS_ERROR( pLink );
//
//            KIS_NODE* pNode = pLink->pOutputNode;
//            LOG_PROCESS_ERROR( pNode );
//
//            nRetCode = KismetGenerateBTNode( pNode, pText+strlen(pText), pText+sizeof(pText), 1 );
//            LOG_PROCESS_ERROR( nRetCode );
//        }
//    }
//    _snprintf( pText+strlen(pText), sizeof(pText)-strlen(pText), "}\n" );
//
//    // generate BTStarter function
//    _snprintf( pText+strlen(pText), sizeof(pText)-strlen(pText), "\n" );
//
//    // get file name, and save it
//
//    return TRUE;
//Exit0:
//    return FALSE;
//}

KIS_TEMPLATE* kisLoad(char* pcData, INT32 nSize)
{
    KIS_TEMPLATE* pResult = NULL;
    KD_VAR_HEADER* pVarHeader = NULL;
    KD_SEQUENCE_HEADER* pSeqHeader = NULL;
    KD_VAR_POINT_HEADER* pVarPointHeader = NULL;
    KD_VAR_POINT* pVarPoint = NULL;
    KD_PROP_HEADER* pPropHeader = NULL;
    KD_PROP_VAR_LINK_HEADER* pPropVarLinkHeader = NULL;
    KD_TRIGGER_DATA* pTriggerData = NULL;

    KIS_SEQUENCE* pSequence = NULL;
    KIS_LINK_POINT* pInputLinkPoint = NULL;
    KIS_LINK_POINT* pOutputLinkPoint = NULL;
    KIS_NODE* pInputNode = NULL;
    KIS_NODE* pOutputNode = NULL;

    INT32 nTimerID = 0;
    char* pcEnd = pcData + nSize;

    LOG_PROCESS_ERROR(pcData);

    pResult = new KIS_TEMPLATE;
    LOG_PROCESS_ERROR(pResult);

    memset(pResult, 0, sizeof(KIS_TEMPLATE));

    // variable table
    pVarHeader = (KD_VAR_HEADER*)pcData;
    pcData += sizeof(KD_VAR_HEADER) + pVarHeader->nVarCount * sizeof(pVarHeader->VarList[0]);
    LOG_PROCESS_ERROR(pcData <= pcEnd);

    pResult->nVarCount = pVarHeader->nVarCount;
    for (INT32 nVarIndex = 0; nVarIndex < pVarHeader->nVarCount; nVarIndex++)
    {
        pResult->nVarInitList[nVarIndex + 1] = pVarHeader->VarList[nVarIndex].nInitValue;
        if (pVarHeader->VarList[nVarIndex].nType == kotSequenceVariableObject)
        {
            pResult->nVarTypeList[nVarIndex + 1] = pVarHeader->VarList[nVarIndex].nObjectType;
        }
        else
        {
            pResult->nVarTypeList[nVarIndex + 1] = pVarHeader->VarList[nVarIndex].nType;
        }
    }

    pResult->nSeqCount = 0;
    // sequence
    while (pcData != pcEnd)
    {
        pSeqHeader = (KD_SEQUENCE_HEADER*)pcData;
        pcData += sizeof(KD_SEQUENCE_HEADER);
        LOG_PROCESS_ERROR(pcData <= pcEnd);

        if (pSeqHeader->nNodeCount == 0)
            continue;

        pSequence = new KIS_SEQUENCE;
        LOG_PROCESS_ERROR(pSequence);
        memset(pSequence, 0, sizeof(KIS_SEQUENCE));

        pResult->pSequenceList[pResult->nSeqCount++] = pSequence;

        pSequence->pNodePool = new KIS_NODE[pSeqHeader->nNodeCount + 1];
        LOG_PROCESS_ERROR(pSequence->pNodePool);

        memset(pSequence->pNodePool, 0, sizeof(KIS_NODE) * (pSeqHeader->nNodeCount + 1));

        pSequence->nNodeCount = pSeqHeader->nNodeCount;
        for (INT32 nNodeIndex = 0; nNodeIndex < pSeqHeader->nNodeCount; nNodeIndex++)
        {
            KD_NODE_HEADER* pNodeHeader = (KD_NODE_HEADER*)pcData;
            pcData += sizeof(KD_NODE_HEADER);
            LOG_PROCESS_ERROR(pcData <= pcEnd);

            LOG_PROCESS_ERROR(pNodeHeader->nNodeID <= pSeqHeader->nNodeCount);
            pInputNode = pSequence->pNodePool + pNodeHeader->nNodeID;

            // link
            pInputNode->nNodeType = pNodeHeader->nType;

            pInputNode->nOutputPointCount = pNodeHeader->nOutputPointCount;
            for (INT32 nPointIndex = 0; nPointIndex < pNodeHeader->nOutputPointCount; nPointIndex++)
            {
                KD_OUTPUT_POINT* pPoint = (KD_OUTPUT_POINT*)pcData;
                pcData += sizeof(KD_OUTPUT_POINT) + sizeof(KD_LINK_DATA) * pPoint->nLinkCount;
                LOG_PROCESS_ERROR(pcData <= pcEnd);

                pOutputLinkPoint = new KIS_LINK_POINT;
                LOG_PROCESS_ERROR(pOutputLinkPoint);
                memset(pOutputLinkPoint, 0, sizeof(KIS_LINK_POINT));

                pInputNode->pOutputPointList[nPointIndex] = pOutputLinkPoint;

                pOutputLinkPoint->nLinkCount = pPoint->nLinkCount;
                for (INT32 nLnkIndex = 0; nLnkIndex < pPoint->nLinkCount; nLnkIndex++)
                {
                    KIS_LINK* pLink = new KIS_LINK;
                    LOG_PROCESS_ERROR(pLink);

                    pOutputLinkPoint->pLinkList[nLnkIndex] = pLink;

                    pLink->bHasImpulse = false;
                    pLink->nDelayTime = pPoint->nDelayTime;
                    pLink->nInputPoint = pPoint->LinkList[nLnkIndex].nInputPoint;
                    if (pLink->nDelayTime > 0)
                        pLink->nTimerID = nTimerID++;
                    else
                        pLink->nTimerID = KIS_INVALID_TIMER_ID;
                    pLink->pInputNode = pInputNode;

                    LOG_PROCESS_ERROR(pPoint->LinkList[nLnkIndex].nNodeID <= pSequence->nNodeCount);
                    pOutputNode = pSequence->pNodePool + pPoint->LinkList[nLnkIndex].nNodeID;
                    pLink->pOutputNode = pOutputNode;

                    if (pOutputNode->pInputPointList[pLink->nInputPoint] == NULL)
                    {
                        pOutputLinkPoint = new KIS_LINK_POINT;
                        pOutputNode->pInputPointList[pLink->nInputPoint] = pOutputLinkPoint;
                        pOutputLinkPoint->nLinkCount = 0;
                    }
                    else
                    {
                        pOutputLinkPoint = pOutputNode->pInputPointList[pLink->nInputPoint];
                    }
                    pOutputLinkPoint->pLinkList[pOutputLinkPoint->nLinkCount++] = pLink;
                }
            }

            // var
            pVarPointHeader = (KD_VAR_POINT_HEADER*)pcData;
            pcData += sizeof(KD_VAR_POINT_HEADER);
            LOG_PROCESS_ERROR(pcData <= pcEnd);

            pInputNode->nVarPointCount = pVarPointHeader->nVarPointCount;
            for (INT32 nPointIndex = 0; nPointIndex < pVarPointHeader->nVarPointCount; nPointIndex++)
            {
                pVarPoint = (KD_VAR_POINT*)pcData;
                pcData += sizeof(KD_VAR_POINT) + pVarPoint->nVarCount * sizeof(pVarPoint->VarIDList[0]);
                LOG_PROCESS_ERROR(pcData <= pcEnd);

                pInputNode->pVarPointList[nPointIndex] = new KIS_VAR_POINT;
                LOG_PROCESS_ERROR(pInputNode->pVarPointList[nPointIndex]);

                pInputNode->pVarPointList[nPointIndex]->nVarCount = pVarPoint->nVarCount;
                for (INT32 nVarIndex = 0; nVarIndex < pVarPoint->nVarCount; nVarIndex++)
                {
                    pInputNode->pVarPointList[nPointIndex]->nVarIDList[nVarIndex] = pVarPoint->VarIDList[nVarIndex];
                }
            }

            // prop
            pPropHeader = (KD_PROP_HEADER*)pcData;
            pcData += sizeof(KD_PROP_HEADER) + pPropHeader->nPropCount * sizeof(pPropHeader->nPropList[0]);
            LOG_PROCESS_ERROR(pcData <= pcEnd);

            pInputNode->nPropCount = pPropHeader->nPropCount;
            for (INT32 nPointIndex = 0; nPointIndex < pPropHeader->nPropCount; nPointIndex++)
            {
                pInputNode->pPropList[nPointIndex] = new KIS_PROP_POINT;
                LOG_PROCESS_ERROR(pInputNode->pPropList[nPointIndex]);

                pInputNode->pPropList[nPointIndex]->nPropCount = 1;
                pInputNode->pPropList[nPointIndex]->nPropType = kotSequenceVariableInt;
                pInputNode->pPropList[nPointIndex]->nValueList[0] = pPropHeader->nPropList[nPointIndex];
            }

            // prop var link
            pPropVarLinkHeader = (KD_PROP_VAR_LINK_HEADER*)pcData;
            pcData += sizeof(KD_PROP_VAR_LINK_HEADER) + pPropVarLinkHeader->nLinkCount * sizeof(KD_PROP_VAR_LINK_DATA);
            LOG_PROCESS_ERROR(pcData <= pcEnd);

            memcpy(pInputNode->pPropVarLink, pPropVarLinkHeader->LinkList, 
                pPropVarLinkHeader->nLinkCount * sizeof(KD_PROP_VAR_LINK_DATA));

            // trigger
            if (pNodeHeader->nType >= kotEventBegin && pNodeHeader->nType < kotEventEnd)
            {
                pTriggerData = (KD_TRIGGER_DATA*)pcData;
                pcData += sizeof(KD_TRIGGER_DATA);

                pInputNode->nMaxTriggerCount = pTriggerData->nMaxTriggerCount;
            }
        }
    }

    LOG_PROCESS_ERROR(pcData == pcEnd);

    // link event
    for (INT32 nSeqIndex = 0; nSeqIndex < pResult->nSeqCount; nSeqIndex++)
    {
        KIS_SEQUENCE* pSequence = pResult->pSequenceList[nSeqIndex];
        LOG_PROCESS_ERROR(pSequence);

        for (INT32 nNodeIndex = 1; nNodeIndex <= pSequence->nNodeCount; nNodeIndex++)
        {
            KIS_NODE* pNode = pSequence->pNodePool + nNodeIndex;
            LOG_PROCESS_ERROR(pNode);

            if (pNode->nNodeType >= kotEventBegin && pNode->nNodeType < kotEventEnd)
            {
                INT32 nEventNode = ++pResult->nEventNodeCount;
                LOG_PROCESS_ERROR(nEventNode < KIS_MAX_EVENT_NODE);

                pResult->EventNodePool[nEventNode].pNode = pNode;
                pResult->EventNodePool[nEventNode].nTriggerCount = 0;
                pResult->EventNodePool[nEventNode].nNextEvent = 0;

                if (pResult->pEventList[pNode->nNodeType - kotEventBegin] == 0)
                {
                    pResult->pEventList[pNode->nNodeType - kotEventBegin] = nEventNode;
                }
                else
                {
                    INT32 nTemp = pResult->pEventList[pNode->nNodeType - kotEventBegin];
                    while (pResult->EventNodePool[nTemp].nNextEvent != 0)
                        nTemp = pResult->EventNodePool[nTemp].nNextEvent;
                    pResult->EventNodePool[nTemp].nNextEvent = nEventNode;
                }
            }
        }
    }

    //// generate bt script
    //for (INT32 nSeqIndex = 0; nSeqIndex < pResult->nSeqCount; nSeqIndex++)
    //{
    //    KIS_SEQUENCE* pSequence = pResult->pSequenceList[nSeqIndex];
    //    LOG_PROCESS_ERROR(pSequence);

    //    for (INT32 nNodeIndex = 1; nNodeIndex <= pSequence->nNodeCount; nNodeIndex++)
    //    {
    //        KIS_NODE* pNode = pSequence->pNodePool + nNodeIndex;
    //        LOG_PROCESS_ERROR(pNode);

    //        if (pNode->nNodeType >= kotEventBegin && pNode->nNodeType < kotEventEnd)
    //        {
    //            if ( pNode->nNodeType == kotSeqEvent_BTStarter )
    //            {
    //                INT32 nRetCode = KismetGenerateBTScript( pNode );
    //                LOG_PROCESS_ERROR( nRetCode );
    //            }
    //        }
    //    }
    //}

    return pResult;
Exit0:
    kisFree(pResult);

    return NULL;
}

BOOL kisFree(KIS_TEMPLATE* pTemplate)
{

    return FALSE;
}

BOOL kisReload(KIS_TEMPLATE* pTemplate)
{

    return TRUE;
}
