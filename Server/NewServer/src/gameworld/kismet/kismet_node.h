#ifndef _KISMET_NODE_H_
#define _KISMET_NODE_H_

#include "scene_kismet_def.h"

#pragma warning(disable:4200)

#define KIS_MAX_NODE_INPUT_POINT    (8)
#define KIS_MAX_NODE_OUTPUT_POINT   (8)
#define KIS_MAX_NODE_VAR_POINT      (8)
#define KIS_MAX_NODE_PROPERTY       (8)

#define KIS_MAX_POINT_LINK          (8)
#define KIS_MAX_POINT_VAR           (8)

#define KIS_MAX_SEQUENCE_EVENT      (16)
#define KIS_MAX_LIST_SEQUENCE       (16)
#define KIS_MAX_LIST_VARAIBLE       (256)
#define KIS_FILE_NAME_LEN           (256)
#define KIS_MAX_EVENT_NODE          (64)

#define KIS_INVALID_TIMER_ID        (-1)
#define KIS_MAX_TIMER               (16)

struct KIS_NODE;
struct KIS_LINK;
struct KIS_LINK_POINT;
struct KIS_VAR_POINT;
struct KIS_PROP_POINT;
struct PROP_VAR_LINK;
struct KIS_INSTANCE;
class CScene;

typedef UINT32 (*KIS_FUNC)(CScene* poScene, KIS_INSTANCE* pKisInstance, INT32 nInputPoint, KIS_PROP_POINT* nPropList[], 
                           INT32 nPropPointCount, KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount);

typedef UINT32 (*KIS_EVENT)(INT32 nEventType, CScene* poScene, KIS_INSTANCE* pKisInstance, 
                            KIS_PROP_POINT* nPropList[], INT32 nPropPointCount, 
                            KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount,
                            INT32 nOriginatorType, INT32 nOriginatorID, INT32 nInstigatorType, INT32 nInstigatorID);

struct KIS_NODE
{
    INT32                   nNodeType;

    KIS_LINK_POINT*         pInputPointList[KIS_MAX_NODE_INPUT_POINT];
    INT32                   nInputPointCount;

    KIS_LINK_POINT*         pOutputPointList[KIS_MAX_NODE_OUTPUT_POINT];
    INT32                   nOutputPointCount;

    KIS_PROP_POINT*         pPropList[KIS_MAX_NODE_PROPERTY];
    INT32                   nPropCount;

    KIS_VAR_POINT*          pVarPointList[KIS_MAX_NODE_VAR_POINT];
    INT32                   nVarPointCount;

    PROP_VAR_LINK*          pPropVarLink[KIS_MAX_NODE_VAR_POINT];
    INT32                   nPropVarLinkCount;

    INT32                   nMaxTriggerCount;
};

struct KIS_LINK
{
    BOOL                    bHasImpulse;
    INT32                   nTimerID;
    INT32                   nDelayTime;
    KIS_NODE*               pInputNode;
    INT32                   nInputPoint;
    KIS_NODE*               pOutputNode;
};

struct KIS_LINK_POINT
{
    KIS_LINK*               pLinkList[KIS_MAX_POINT_LINK];
    INT32                   nLinkCount;
};

struct KIS_VAR_POINT
{
    INT32                   nVarCount;
    INT32                   nVarIDList[KIS_MAX_POINT_VAR];
};

struct KIS_PROP_POINT
{
    INT32                   nPropCount;
    INT32                   nPropType;
    INT32                   nValueList[KIS_MAX_POINT_VAR];
};

struct PROP_VAR_LINK
{
    INT32                   nPropIndex;
    INT32                   nVarIndex;
};

struct KIS_SEQUENCE
{
    KIS_NODE*               pNodePool;
    INT32                   nNodeCount;
};

struct KIS_EVENT_NODE
{
    KIS_NODE*               pNode;
    INT32                   nTriggerCount;
    INT32                   nNextEvent;
};

struct KIS_TEMPLATE
{
    KIS_SEQUENCE*           pSequenceList[KIS_MAX_LIST_SEQUENCE];
    INT32                   nSeqCount;

    INT32                   nVarInitList[KIS_MAX_LIST_VARAIBLE];
    INT32                   nVarTypeList[KIS_MAX_LIST_VARAIBLE];
    INT32                   nVarCount;

    KIS_EVENT_NODE          EventNodePool[KIS_MAX_EVENT_NODE];
    INT32                   nEventNodeCount;
    INT32                   pEventList[kotEventEnd - kotEventBegin];
};

struct KIS_INSTANCE
{
    KIS_TEMPLATE*           pTemplate;
    CScene*                 poScene; 

    INT32                   nVarList[KIS_MAX_LIST_VARAIBLE];
    INT32                   nTimerList[KIS_MAX_TIMER];
    KIS_EVENT_NODE          EventNodePool[KIS_MAX_EVENT_NODE];

    std::list<KIS_LINK*>    ActiveLinkList[2];
    INT32                   nCurrentActiveLinkList;
};

BOOL kisInit(void);
BOOL kisUnInit(void);

KIS_TEMPLATE* kisLoad(char* pcData, INT32 nSize);
BOOL kisFree(KIS_TEMPLATE* pTemplate);
BOOL kisReload(KIS_TEMPLATE* pTemplate);

KIS_INSTANCE* kisCreateList(CScene* poScene, KIS_TEMPLATE* pTemplate);
BOOL kisDestroyList(KIS_INSTANCE* pKisInstance);

BOOL kisTriggerEvent(INT32 nNodeType, INT32 nEventType, KIS_INSTANCE* pSequenceList, INT32 nOriginatorType, INT32 nOriginatorID,
                     INT32 nInstigatorType, INT32 nInstigatorID, INT32 nCurrentTime);
BOOL kisActivateList(KIS_INSTANCE* pSequenceList, INT32 nCurrentTime);

#endif  // _KISMET_NODE_H_