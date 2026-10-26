#include "stdafx.h"
#include "kismet_node.h"

// Prop:
//      N/A
// Var:
//      0 : volumn list
// Output:
//      0 : touched volume
//      1 : untouched volume
//      2 : empty
UINT32 _keRoleTouchVolumn(INT32 nEventType, CScene* poScene, KIS_INSTANCE* pKisInstance, 
                        KIS_PROP_POINT* nPropList[], INT32 nPropPointCount, 
                        KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount,
                        INT32 nOriginatorType, INT32 nOriginatorID, INT32 nInstigatorType, INT32 nInstigatorID)
{
    UINT32 dwOutputMask = 0;

    dwOutputMask = 1 << nEventType;

    return dwOutputMask;
}

// Prop:
//      N/A
// Var:
//      0 : npc group list
// Output:
//      0 : npc group die
UINT32 _keNpcGroupDie(INT32 nEventType, CScene* poScene, KIS_INSTANCE* pKisInstance, 
                    KIS_PROP_POINT* nPropList[], INT32 nPropPointCount, 
                    KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount,
                    INT32 nOriginatorType, INT32 nOriginatorID, INT32 nInstigatorType, INT32 nInstigatorID)
{
    UINT32 dwOutputMask = 0;

    dwOutputMask = 1 << nEventType;

    return dwOutputMask;
}

// Prop:
//      N/A
// Var:
//      0 : npc list
// Output:
//      0 : npc die
UINT32 _keNpcDie(INT32 nEventType, CScene* poScene, KIS_INSTANCE* pKisInstance, 
                 KIS_PROP_POINT* nPropList[], INT32 nPropPointCount, 
                 KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount,
                 INT32 nOriginatorType, INT32 nOriginatorID, INT32 nInstigatorType, INT32 nInstigatorID)
{
    UINT32 dwOutputMask = 0;

    dwOutputMask = 1 << nEventType;

    return dwOutputMask;
}

// Prop:
//      N/A
// Var:
//      0 : door list
// Output:
//      0 : door opened
//      1 : door closed
//      2 : door toggled
UINT32 _keDoor(INT32 nEventType, CScene* poScene, KIS_INSTANCE* pKisInstance, 
                 KIS_PROP_POINT* nPropList[], INT32 nPropPointCount, 
                 KIS_VAR_POINT* pVarPointList[], INT32 nVarPointCount,
                 INT32 nOriginatorType, INT32 nOriginatorID, INT32 nInstigatorType, INT32 nInstigatorID)
{
    UINT32 dwOutputMask = 0;

    dwOutputMask = 1 << nEventType;

    return dwOutputMask;
}

KIS_EVENT    g_KismetEventList[kotEventEnd - kotEventBegin] = 
{
    _keRoleTouchVolumn,
    _keNpcGroupDie,
    _keNpcDie,
    _keDoor,
};
