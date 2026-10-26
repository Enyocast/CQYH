#include "stdafx.h"
#include "btnod.h"

enum TEST_BT_ACTION
{
    tbaInvalid,

    tbaReturnSuccess = btUserDefine,
    tbaReturnFail,
    tbaReturnError,
    tbaReturnRunning,
    tbaSetPoint,

    tbaTotal
};

UINT32 g_dwCheckPoint = 0;


INT32 bfReturnSuccess(BTCtx* ctx, INT32 nParam[])
{
    return brvSuccess;
}

INT32 bfReturnFail(BTCtx* ctx, INT32 nParam[])
{
    return brvFail;
}

INT32 bfReturnError(BTCtx* ctx, INT32 nParam[])
{
    return brvError;
}

INT32 bfReturnRunning(BTCtx* ctx, INT32 nParam[])
{
    return brvRunning;
}

INT32 bfSetPoint(BTCtx* ctx, INT32 nParam[])
{
    LOG_PROCESS_ERROR(nParam[0] >= 0 && nParam[0] < 32);

    g_dwCheckPoint |= (1 << nParam[0]);

    return brvSuccess;
Exit0:
    return brvError;
}

INT32 _NodeFunc(BTCtx* ctx, BTNod* nod)
{
    INT32 nResult = brvError;
    INT32 nRetCode = 0;

    switch (nod->type)
    {
    case tbaReturnSuccess:
        nResult = bfReturnSuccess(ctx, nod->params);
        break;
    case tbaReturnFail:
        nResult = bfReturnFail(ctx, nod->params);
        break;
    case tbaReturnError:
        nResult = bfReturnError(ctx, nod->params);
        break;
    case tbaReturnRunning:
        nResult = bfReturnRunning(ctx, nod->params);
        break;
    case tbaSetPoint:
        nResult = bfSetPoint(ctx, nod->params);
        break;
    default:
        LOG_PROCESS_ERROR(FALSE);
        break;
    }

Exit0:
    return nResult;
}

struct TEST_NODE
{
    INT32 nType;
    INT32 nParam0;
    INT32 nParam1;
    INT32 nParam2;
    INT32 nParam3;
};

struct BTNodeTestCase
{
    UINT32      dwCheckPoint;
    TEST_NODE   ParentNode;
    TEST_NODE   ChildNode[4];
};

BTNodeTestCase g_TestCase[] =
{
    {
        0x00000000,
        {btSelector},
    },
    {
        0x00000000,
        {btSequencer},
    },
    {
        0x00000000,
        {btParallel},
    },
    {
        0x00000001,
        {btSelector}, { 
            {tbaSetPoint, 0}, 
            {tbaReturnSuccess}, 
            {tbaSetPoint, 1}, 
        },
    },
    {
        0x00000001,
        {btSelector}, { 
            {tbaReturnFail}, 
            {tbaSetPoint, 0}, 
        },
    },
    {
        0x00000003,
        {btSequencer}, { 
            {tbaSetPoint, 0}, 
            {tbaReturnSuccess}, 
            {tbaSetPoint, 1}, 
        },
    },
    {
        0x00000001,
        {btSequencer}, { 
            {tbaSetPoint, 0}, 
            {tbaReturnFail}, 
            {tbaSetPoint, 1}, 
        },
    },
    {
        0x00000003,
        {btParallel}, { 
            {tbaSetPoint, 0}, 
            {tbaReturnSuccess}, 
            {tbaReturnFail}, 
            {tbaSetPoint, 1}, 
        },
    },
};

BOOL TestBT(void)
{
    INT32 nRetCode = 0;

    registerNodeFunc(_NodeFunc);

    for (int i = 0; i < sizeof(g_TestCase) / sizeof(g_TestCase[0]); i++)
    {
        BTCtx ctx = {0};

        BTNod* pRoot = new BTNod;
        LOG_PROCESS_ERROR(pRoot);

        memset(pRoot, 0, sizeof(*pRoot));
        pRoot->type = g_TestCase[i].ParentNode.nType;
        pRoot->params[0] = g_TestCase[i].ParentNode.nParam0;
        pRoot->params[1] = g_TestCase[i].ParentNode.nParam1;
        pRoot->params[2] = g_TestCase[i].ParentNode.nParam2;
        pRoot->params[3] = g_TestCase[i].ParentNode.nParam3;


        for (int j = 0; j < 4; j++)
        {
            if (g_TestCase[i].ChildNode[j].nType)
            {
                BTNod* pChild = new BTNod;
                LOG_PROCESS_ERROR(pChild);

                memset(pChild, 0, sizeof(*pChild));
                pChild->type = g_TestCase[i].ChildNode[j].nType;
                pChild->params[0] = g_TestCase[i].ChildNode[j].nParam0;
                pChild->params[1] = g_TestCase[i].ChildNode[j].nParam1;
                pChild->params[2] = g_TestCase[i].ChildNode[j].nParam2;
                pChild->params[3] = g_TestCase[i].ChildNode[j].nParam3;

                nRetCode = BTNod_addChild(pRoot, pChild);
            }
        }

        ctx.callFrame[0].nod = pRoot;
        ctx.callFrameCount = 1;
        g_dwCheckPoint = 0;
        
        BTCtx_run(ctx);

        LOG_PROCESS_ERROR(g_dwCheckPoint == g_TestCase[i].dwCheckPoint);
    }

    return true;
Exit0:
    return false;
}