#include "stdafx.h"
#include "kismet_node.h"

#include "scene.h"
#include "scene_file_mgr.h"
#include "npc.h"
//
//#define SET_OUTPUT(__point__)                   \
//    do                                          \
//    {                                           \
//        dwOutputMask |= (1 << (__point__));    \
//    } while (0)
//
//#define GET_VAR(__point__, __index__)           \
//    pKisInstance->nVarList[pVarPointList[__point__]->nVarIDList[__index__]]
//
//// Input:
////      0 : spawn npc group
//// Prop:
////      N/A
//// Var:
////      0 : npc group id
//// Output:
////      0 : spawned successfully
//UINT32 _kfSpawnNpcGroup(CScene* poScene, KIS_INSTANCE* pKisInstance, INT32 nInputPoint, KIS_PROP_POINT* nPropList[], 
//                        INT32 nPropPointCount, KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount)
//{
//    INT32 nRetCode = 0;
//    UINT32 dwOutputMask = 0;
//
//    LOG_PROCESS_ERROR(poScene);
//    LOG_PROCESS_ERROR(pKisInstance);
//
//    if (nInputPoint == 0)
//    {
//        LOG_PROCESS_ERROR(pVarPointList[0]);
//        for (INT32 nVarIndex = 0; nVarIndex < pVarPointList[0]->nVarCount; nVarIndex++)
//        {
//            INT32 nValue = GET_VAR(0, nVarIndex);
//
//            nRetCode = poScene->SpawnNpcMediumGroup(nValue);
//            LOG_PROCESS_ERROR(nRetCode);
//        }
//        SET_OUTPUT(0);
//    }
//
//Exit0:
//
//    return dwOutputMask;
//}
//
//// Input:
////      0 : spawn single npc
//// Prop:
////      N/A
//// Var:
////      0 : single npc id
//// Output:
////      0 : spawned successfully
//UINT32 _kfSpawnSingleNpc(CScene* poScene, KIS_INSTANCE* pKisInstance, INT32 nInputPoint, KIS_PROP_POINT* nPropList[], 
//                        INT32 nPropPointCount, KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount)
//{
//    INT32 nRetCode = 0;
//    UINT32 dwOutputMask = 0;
//    CNpc* poNpc = NULL;
//
//    LOG_PROCESS_ERROR(poScene);
//    LOG_PROCESS_ERROR(pKisInstance);
//
//    if (nInputPoint == 0)
//    {
//        CSceneStaticData* pStaticData = poScene->GetStaticData();
//        LOG_PROCESS_ERROR(pStaticData);
//
//        LOG_PROCESS_ERROR(pVarPointList[0]);
//        for (INT32 nVarIndex = 0; nVarIndex < pVarPointList[0]->nVarCount; nVarIndex++)
//        {
//            INT32 nValue = GET_VAR(0, nVarIndex);
//
//            const NPC_SINGLE_SPAWN* pSingleNpc = pStaticData->GetSingleNpc(nValue);
//            LOG_PROCESS_ERROR(pSingleNpc);
//
//            poNpc = poScene->SpawnNpc(pSingleNpc->nNpcTemplateID, 
//                pSingleNpc->nX, pSingleNpc->nY, pSingleNpc->nZ, pSingleNpc->shDirection, FALSE, 
//                nstSingle, pSingleNpc->AutoServerID, nValue);
//            LOG_PROCESS_ERROR(poNpc);
//        }
//        SET_OUTPUT(0);
//    }
//
//Exit0:
//
//    return dwOutputMask;
//}
//
//// Input:
////      0 : open door
////      1 : close door
////      2 : toggle door
//// Prop:
////      N/A
//// Var:
////      0 : door id
//// Output:
////      0 : door opened
////      1 : door closed
////      2 : door toggled
//UINT32 _kfOperateDoor(CScene* poScene, KIS_INSTANCE* pKisInstance, INT32 nInputPoint, KIS_PROP_POINT* nPropList[], 
//                         INT32 nPropPointCount, KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount)
//{
//    INT32 nRetCode = 0;
//    UINT32 dwOutputMask = 0;
//
//    LOG_PROCESS_ERROR(poScene);
//    LOG_PROCESS_ERROR(pKisInstance);
//
//    if (nInputPoint == 0)
//    {
//        LOG_PROCESS_ERROR(pVarPointList[0]);
//        for (INT32 nVarIndex = 0; nVarIndex < pVarPointList[0]->nVarCount; nVarIndex++)
//        {
//            INT32 nValue = GET_VAR(0, nVarIndex);
//
//            if (!poScene->IsDoorClosed(nValue))
//                SET_OUTPUT(2);
//
//            poScene->SetDoorState(nValue, FALSE);
//        }
//        SET_OUTPUT(0);
//    }
//    else if (nInputPoint == 1)
//    {
//        LOG_PROCESS_ERROR(pVarPointList[0]);
//        for (INT32 nVarIndex = 0; nVarIndex < pVarPointList[0]->nVarCount; nVarIndex++)
//        {
//            INT32 nValue = GET_VAR(0, nVarIndex);
//
//            if (poScene->IsDoorClosed(nValue))
//                SET_OUTPUT(2);
//
//            poScene->SetDoorState(nValue, FALSE);
//        }
//        SET_OUTPUT(1);
//    }
//    else if (nInputPoint == 2)
//    {
//        LOG_PROCESS_ERROR(pVarPointList[0]);
//        for (INT32 nVarIndex = 0; nVarIndex < pVarPointList[0]->nVarCount; nVarIndex++)
//        {
//            INT32 nValue = GET_VAR(0, nVarIndex);
//
//            poScene->SetDoorState(nValue, !poScene->IsDoorClosed(nValue));
//            if (poScene->IsDoorClosed(nValue))
//                SET_OUTPUT(1);
//            else
//                SET_OUTPUT(0);
//        }
//
//        SET_OUTPUT(2);
//    }
//
//Exit0:
//
//    return dwOutputMask;
//}
//
//KIS_FUNC     g_KismetFuncList[kotActionEnd - kotActionBegin] =
//{
//    _kfSpawnNpcGroup,
//    _kfSpawnSingleNpc,
//    _kfOperateDoor,
//};
