#include "stdafx.h"
#include "btnod.h"

static BT_NODE_FUNC     s_pNodeFunc = NULL;

BOOL BTNod_addChild(BTNod* thiz, BTNod* child)
{
    BTNod* nod = NULL;
    INT32 childIndex = 0;
    LOG_PROCESS_ERROR(thiz);
    LOG_PROCESS_ERROR(child);

    if(NULL == thiz->child)
    {
        LOG_PROCESS_ERROR(0 == thiz->childrenCount);
        thiz->child = child;
    }
    else
    {
        nod = thiz->child;

        childIndex = 0;
        while (nod)
        {
            if(NULL == nod->sibling)
            {
                LOG_PROCESS_ERROR(childIndex + 1 == thiz->childrenCount);

                nod->sibling = child;
                break;
            }
            
            ++childIndex;
            LOG_PROCESS_ERROR(childIndex < MAX_BT_CHILD_COUNT); // avoid infinite loop

            nod = nod->sibling;
        }
    }

    thiz->childrenCount++;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL BTNod_removeChild(BTNod* thiz, BTNod* child)
{
    BTNod* elder = NULL;
    BTNod* nod = NULL;
    INT32 childIndex = 0;

    LOG_PROCESS_ERROR(thiz);
    LOG_PROCESS_ERROR(child);

    LOG_PROCESS_ERROR(thiz->child);

    if(child == thiz->child)
    {
        thiz->child = child->sibling;
    }
    else
    {
        nod = thiz->child;
        //for (childIndex = 0; childIndex < thiz->childrenCount; childIndex++)
        //{
        //    PROCESS_ERROR(nod);
        //    if (nod->sibling == child)
        //    {
        //        LOG_PROCESS_ERROR(childIndex + 1 < thiz->childrenCount);
        //        nod->sibling = nod->sibling->sibling;
        //        break;
        //    }
        //    nod = nod->sibling;
        //}

        childIndex = 0;
        while (nod)
        {
            if(child == nod->sibling)
            {
                LOG_PROCESS_ERROR(childIndex + 1 < thiz->childrenCount);

                nod->sibling = nod->sibling->sibling;
                break;
            }

            ++childIndex;
            LOG_PROCESS_ERROR(childIndex < MAX_BT_CHILD_COUNT); // avoid infinite loop

            nod = nod->sibling;
        }
    }

    thiz->childrenCount--;

    return TRUE;
Exit0:
    return FALSE;
}

BTNod* BTNod_GetChild(BTNod* thiz, INT32 nIndex)
{
    BTNod* pResult = NULL;
    BTNod* nod = NULL;

    LOG_PROCESS_ERROR(thiz);
    LOG_PROCESS_ERROR(nIndex >= 0 && nIndex < thiz->childrenCount);

    LOG_PROCESS_ERROR(thiz->child);

    nod = thiz->child;
    while (nod && nIndex--)
    {
        nod = nod->sibling;
    }
    pResult = nod;

    return pResult;
Exit0:
    return NULL;
}


BTNod* BTNod_FindTagNode(BTNod* root, INT32 nTag, BOOL nDepthFirst = FALSE)
{
    BTNod* pResult = NULL;

    BTNod* nod = NULL;
    BTNod* child_nod = NULL;

    BTNod* aChildrenArray[ MAX_BT_CHILD_COUNT ] = { NULL };
    INT32 nChildrenCount = 0;
    INT32 childIndex = 0;

    LOG_PROCESS_ERROR(root);
    LOG_PROCESS_ERROR(nTag > 0);

    nod = root->child;
    if (FALSE == nDepthFirst) // 广度优先
    {
        while (nod)
        {
            if(nod->nodeTag == nTag)
            {
                pResult = nod;
                break;
            }

            aChildrenArray[ nChildrenCount++ ] = nod;

            nod = nod->sibling;
            LOG_PROCESS_ERROR(nChildrenCount < MAX_BT_CHILD_COUNT);
        }

        for (childIndex=0; childIndex < nChildrenCount; ++childIndex)
        {
            child_nod = BTNod_FindTagNode(aChildrenArray[childIndex], nTag);
            if(child_nod && child_nod->nodeTag == nTag)
            {
                pResult = child_nod;
                break;
            }
        }

    } 
    else  // 深度优先
    {
        while (nod)
        {
            if(nod->nodeTag == nTag)
            {
                pResult = nod;
                break;
            }

            child_nod = BTNod_FindTagNode(nod, nTag);
            if(child_nod && child_nod->nodeTag == nTag)
            {
                pResult = child_nod;
                break;
            }

            nod = nod->sibling;
        }
    }

    return pResult;
Exit0:
    return NULL;
}


BOOL BTNodInsertChildAtTag(BTNod* parent, INT32 nTag, BTNod* newChild)
{
    BTNod* nod = NULL;
    INT32 childIndex = 0;

    LOG_PROCESS_ERROR(parent);
    LOG_PROCESS_ERROR(newChild);
    LOG_PROCESS_ERROR(NULL == newChild->sibling); // allow child, but no sibling

    if(NULL == parent->child)
    {
        parent->child = newChild;   // directly add to tail
        ++ parent->childrenCount;

        PROCESS_SUCCESS(TRUE);
    }

    if(parent->child->nodeTag >= nTag)
    {
        newChild->sibling = parent->child;

        parent->child = newChild;
        ++ parent->childrenCount;
    }
    else
    {
        nod = parent->child;

        //for (childIndex = 0; childIndex < parent->childrenCount; childIndex++)
        //{
        //    if(NULL == nod->sibling)              // add tail if not found tag
        //    {
        //        nod->sibling = newChild;
        //    }
        //    else if (nod->sibling->flag >= nTag) // means Tag don't exist
        //    {
        //        LOG_PROCESS_ERROR(childIndex + 1 < parent->childrenCount);
        //        newChild->sibling = nod->sibling;
        //        nod->sibling = newChild;
        //        break;
        //    }
        //    nod = nod->sibling;
        //}

        childIndex = 0;
        while (nod)
        {
            LOG_PROCESS_ERROR(nod != newChild);

            if(NULL == nod->sibling)              // add tail if not found tag
            {
                LOG_PROCESS_ERROR(childIndex + 1 == parent->childrenCount);

                nod->sibling = newChild;
                ++ parent->childrenCount;
                break;
            }
            else if (nod->sibling->nodeTag >= nTag) // means Tag don't exist
            {
                LOG_PROCESS_ERROR(childIndex + 1 < parent->childrenCount);
                newChild->sibling = nod->sibling;

                nod->sibling = newChild;
                ++ parent->childrenCount;
                break;
            }

            ++childIndex;
            LOG_PROCESS_ERROR(childIndex < MAX_BT_CHILD_COUNT); // avoid infinite loop

            LOG_PROCESS_ERROR(nod != nod->sibling);
            nod = nod->sibling;
        }
    }

Exit1:

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL BTCtxPushNod(BTCtx& ctx, BTNod* nod)
{
    LOG_PROCESS_ERROR(ctx.callFrameCount < MAX_CALL_FRAME);

    ctx.callFrame[ctx.callFrameCount].nod = nod;
    ctx.callFrame[ctx.callFrameCount].child = NULL;
    ++ctx.callFrameCount;

    return TRUE;
Exit0:

    return FALSE;
}

inline BOOL BTCtxPopNod(BTCtx& ctx)
{
    LOG_PROCESS_ERROR( ctx.callFrameCount > 0 );
    ctx.callFrameCount--;

    return TRUE;
Exit0:
    return FALSE;
}

void BTCtx_run(BTCtx& ctx)
{
    INT32 nRetCode = 0;

    while (ctx.callFrameCount > 0)
    {
        char szNodeInfo[256];
        BTCtx::CallFrame& callFrame = ctx.callFrame[ctx.callFrameCount - 1];

        LOG_PROCESS_ERROR(callFrame.nod);

        if (ctx.debugging)
        {
            for (INT32 i = 0; i < ctx.callFrameCount - 1; i++)
                szNodeInfo[i] = '\t';
        }

        switch (callFrame.nod->type)
        {
        case btSelector:
            if (callFrame.child == NULL)
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSelector children %d", callFrame.nod->childrenCount);
                    INF(szNodeInfo);
                }
                if (callFrame.nod->child)
                {
                    callFrame.child = callFrame.nod->child;
                    ctx.returnValue = brvError;

                    nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else
                {
                    ctx.returnValue = brvFail;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSelector return %d", ctx.returnValue);
                        INF(szNodeInfo);
                    }

                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            else if (callFrame.child->sibling && ctx.returnValue == brvFail)
            {
                callFrame.child = callFrame.child->sibling;

                nRetCode = BTCtxPushNod(ctx, callFrame.child);
                LOG_PROCESS_ERROR(nRetCode);
            }
            else
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSelector return %d", ctx.returnValue);
                    INF(szNodeInfo);
                }

                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        case btSequencer:
            if (callFrame.child == NULL)
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSequencer children %d", callFrame.nod->childrenCount);
                    INF(szNodeInfo);
                }

                if (callFrame.nod->child)
                {
                    callFrame.child = callFrame.nod->child;
                    ctx.returnValue = brvError;

                    nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else
                {
                    ctx.returnValue = brvSuccess;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSequencer return %d", ctx.returnValue);
                        INF(szNodeInfo);
                    }

                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            else if (callFrame.child->sibling && ctx.returnValue == brvSuccess)
            {
                callFrame.child = callFrame.child->sibling;

                nRetCode = BTCtxPushNod(ctx, callFrame.child);
                LOG_PROCESS_ERROR(nRetCode);
            }
            else
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btSequencer return %d", ctx.returnValue);
                    INF(szNodeInfo);
                }

                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        case btParallel:
            if (callFrame.child == NULL)
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btParallel children %d", callFrame.nod->childrenCount);
                    INF(szNodeInfo);
                }

                if (callFrame.nod->child)
                {
                    callFrame.child = callFrame.nod->child;
                    ctx.returnValue = brvError;

                    nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else
                {
                    ctx.returnValue = brvSuccess;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btParallel return %d", ctx.returnValue);
                        INF(szNodeInfo);
                    }

                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            else if (callFrame.child->sibling)
            {
                callFrame.child = callFrame.child->sibling;

                nRetCode = BTCtxPushNod(ctx, callFrame.child);
                LOG_PROCESS_ERROR(nRetCode);
            }
            else
            {
                ctx.returnValue = brvSuccess;

                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btParallel return %d", ctx.returnValue);
                    INF(szNodeInfo);
                }

                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        case btDebug:
            if (callFrame.child == NULL)
            {
                LOG_PROCESS_ERROR( callFrame.nod->childrenCount == 1 && callFrame.nod->child );
                callFrame.child = callFrame.nod->child;
                ctx.returnValue = brvError;
                ctx.debugging = TRUE;

                nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                LOG_PROCESS_ERROR(nRetCode);
            }
            else
            {
                ctx.debugging = FALSE;
                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        case btNot:
            if (callFrame.child == NULL)
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btNot children %d", callFrame.nod->childrenCount);
                    INF(szNodeInfo);
                }

                callFrame.child = callFrame.nod->child;
                ctx.returnValue = brvError;

                nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                LOG_PROCESS_ERROR(nRetCode);
            }
            else
            {
                ctx.returnValue = !ctx.returnValue;

                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btNot return %d", ctx.returnValue);
                    INF(szNodeInfo);
                }

                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        case btRepeat:
            if (callFrame.child == NULL)
            {
                if ( callFrame.nod->childrenCount > 0 && callFrame.nod->child )
                {
                    INT32 nRepeatTimes = callFrame.nod->params[0];
                    LOG_PROCESS_ERROR( nRepeatTimes > 0 && nRepeatTimes < BT_REPEAT_MAX_TIMES );
                    LOG_PROCESS_ERROR( callFrame.nod->childrenCount == 1 );

                    callFrame.nod->repeatCounter = nRepeatTimes;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRepeat times %d", callFrame.nod->params[0]);
                        INF(szNodeInfo);
                    }

                    callFrame.child = callFrame.nod->child;
                    ctx.returnValue = brvError;

                    nRetCode = BTCtxPushNod(ctx, callFrame.nod->child);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else // if(nod->childrenCount == 0 || NULL==callFrame.nod->child) // error?
                {
                    ctx.returnValue = brvSuccess;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRepeat times %d do nothing return %d", callFrame.nod->params[0], ctx.returnValue);
                        INF(szNodeInfo);
                    }

                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            else
            {
                --callFrame.nod->repeatCounter;
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRepeat times (%d/%d) return %d", 
                        callFrame.nod->params[0] - callFrame.nod->repeatCounter, callFrame.nod->params[0], ctx.returnValue);
                    INF(szNodeInfo);
                }

				if (callFrame.nod->repeatCounter > 0 && ctx.returnValue == brvSuccess)
                {
                    callFrame.child = callFrame.nod->child;
                    nRetCode = BTCtxPushNod(ctx, callFrame.nod->child );
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else
                {
                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            break;
        case btRandom:
            if (callFrame.child == NULL)
            {
                if ( callFrame.nod->childrenCount >= 1 && callFrame.nod->child )
                {
                    INT32 nTotalWeight = 0;
                    INT32 nCounter = 0;
                    BTNod* pNode = callFrame.nod->child;
                    while ( pNode )
                    {
                        LOG_PROCESS_ERROR( callFrame.nod->params[nCounter] > 0 );
                        nTotalWeight += callFrame.nod->params[nCounter];
                        pNode = pNode->sibling;
                        ++nCounter;
                    }
                    LOG_PROCESS_ERROR( nTotalWeight > 0 );

                    INT32 nRandom = rand() % nTotalWeight;
                    nCounter = 0;
                    pNode = callFrame.nod->child;
                    while ( pNode )
                    {
                        nRandom -= callFrame.nod->params[nCounter];
                        if ( nRandom < 0 )
                        {
                            break;
                        }
                        pNode = pNode->sibling;
                        ++nCounter;
                    }

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRandom choose child %d on (%d/%d)", nCounter, callFrame.nod->params[nCounter], nTotalWeight );
                        INF(szNodeInfo);
                    }

                    callFrame.child = pNode;
                    ctx.returnValue = brvError;

                    nRetCode = BTCtxPushNod(ctx, pNode);
                    LOG_PROCESS_ERROR(nRetCode);
                }
                else// if(nod->childrenCount == 0 || NULL==callFrame.nod->child ) // error?
                {
                    ctx.returnValue = brvFail;

                    if (ctx.debugging)
                    {
                        snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRandom no child to choose return %d", ctx.returnValue);
                        INF(szNodeInfo);
                    }

                    nRetCode = BTCtxPopNod(ctx);
                    LOG_PROCESS_ERROR( nRetCode );
                }
            }
            else
            {
                if (ctx.debugging)
                {
                    snprintf(szNodeInfo + ctx.callFrameCount - 1, 200, "btRandom return %d", ctx.returnValue);
                    INF(szNodeInfo);
                }
                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );
            }
            break;
        default:
            {
                LOG_PROCESS_ERROR(s_pNodeFunc);

                ctx.returnValue = s_pNodeFunc(&ctx, callFrame.nod);
                LOG_PROCESS_ERROR(ctx.returnValue != brvError);

                nRetCode = BTCtxPopNod(ctx);
                LOG_PROCESS_ERROR( nRetCode );

                PROCESS_SUCCESS(ctx.returnValue == brvRunning);
            }
            break;
        }

    }

    PROCESS_ERROR(ctx.returnValue == brvSuccess);
Exit1:

	return;
Exit0:
    if (ctx.returnValue == brvError)
    {
        if (ctx.callFrameCount >= 1 && ctx.callFrame[ctx.callFrameCount - 1].nod)
            CRI("bt node %d error", ctx.callFrame[ctx.callFrameCount - 1].nod->type);
        else
            CRI("unknown bt node error");
    }

    ctx.callFrameCount = 0;

	return;
}

void registerNodeFunc(BT_NODE_FUNC pNodeFunc)
{
    s_pNodeFunc = pNodeFunc;
}
