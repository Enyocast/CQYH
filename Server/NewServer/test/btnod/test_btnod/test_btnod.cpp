// test_net_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "btnod.h"
#include "profile.h"
#include "process_error.h"
#include "object_pool.h"

#define output( ... ) DBG( __VA_ARGS__ )
//#define output( ... )

enum
{
    batStart = btUserDefine,
    batSuccess,
    batFail,
    batRunning,
    batEnd,
};
int bfReturnSuccess( BTCtx* ctx, INT32 nParam[] )
{
    output( "BTNod %d Succ\n", "sucess" );
    return brvSuccess;
}
int bfReturnFail( BTCtx* ctx, INT32 nParam[] )
{
    output( "BTNod %d Fail\n", "fail" );
    return brvFail;
}
int bfReturnRunning( BTCtx* ctx, INT32 nParam[] )
{
    static int s;
    PROCESS_ERROR( (s++) % 2 );

    output( "BTNod %s Succ\n", "success" );
    return brvSuccess;
Exit0:
    output( "BTNod %s Running\n", "running" ); 
    return brvRunning;
}

typedef int (*btFunc)( BTCtx* ctx, INT32 nParam[] );
struct  
{
    int btActionID;
    btFunc pFunc;
}g_ActionFuncList[btTotal] = 
{
    {btInvalid,     NULL    },
    {btSequencer,   NULL    },
    {btSelector,    NULL    },
    {btParallel,    NULL    },
    {btNot,         NULL    },
    {btDebug,       NULL    },
    {btUserDefine,  NULL    },

    {batSuccess, bfReturnSuccess,},
    {batFail,    bfReturnFail },
    {batRunning, bfReturnRunning },
};

struct BTTestCtx : BTCtx
{

};
INT32 _NodeFunc(BTCtx* ctx, BTNod* nod)
{
    INT32 nResult = brvError;
    INT32 nRetCode = 0;
    INT32 nParam[MAX_BT_PARAM];
    BTTestCtx* pCtx = (BTTestCtx*)ctx;

    LOG_PROCESS_ERROR( pCtx );
    LOG_PROCESS_ERROR(nod->type > batStart && nod->type < batEnd);

    nResult = g_ActionFuncList[nod->type].pFunc(pCtx, nParam);

Exit0:
    return nResult;
}

CObjectPool<BTNod> g_BTNodPool;

BOOL nodNewChild( BTNod* nod, int depth )
{
    if( 0 >= depth )
        return TRUE;

    BTNod* child = g_BTNodPool.New();
    PROCESS_ERROR( child );
    
    memset( child, 0, sizeof(BTNod) );
    BTNod_addChild( nod, child );
    if( depth > 1 )
        child->type = btSequencer;
    else
        child->type = batFail;

    return nodNewChild( child, depth - 1 );
Exit0:
    return FALSE;
}

BOOL nodDeleteChild( BTNod* nod )
{
    BOOL nRetCode = FALSE;
    BTNod* pNode = NULL;
    if ( NULL == nod )
    {
        return TRUE;
    }

    if ( nod->child )
    {
        nRetCode = nodDeleteChild( nod->child );
        PROCESS_ERROR( nRetCode );

        BOOL nRetCode = g_BTNodPool.Delete( nod->child );
        PROCESS_ERROR( nRetCode );
    }

    if ( nod->sibling )
    {
        BOOL nRetCode = nodDeleteChild( nod->sibling );
        PROCESS_ERROR( nRetCode );
    }


Exit0:
    return FALSE;
}
int _tmain(int argc, _TCHAR* argv[])
{
    int nRetCode = 0;
    int run_times = 1;
    int nod_depth = 10;
    int nod_width = 10;
    if( argc > 1 )
    {
        run_times = atoi( argv[1] );
    }
    if( argc > 2 )
    {
        nod_depth = atoi( argv[2] );
    }
    if( argc > 3 )
    {
        nod_width = atoi( argv[3] );
    }

    nRetCode = g_BTNodPool.Init( 1024 * 64 );
    PROCESS_ERROR(nRetCode);

    nRetCode = CLog::GetInstance().Init("test_btnod", lltAll, lotConsole | lotFile, TRUE, 0 );
    LOG_PROCESS_ERROR(nRetCode);

    // init
    registerNodeFunc( _NodeFunc );

    BTNod** nodRoot = new(std::nothrow) BTNod*[run_times];
    LOG_PROCESS_ERROR(nodRoot);

    PROFILE_START();

    DBG("run %d times, nod_width=%d, nod_depth=%d", run_times, nod_width, nod_depth );
    PROFILE_POINT( 0 );

    // do
    for( int i = 0; i < run_times; ++i )
    {
        // create
        nodRoot[i] = g_BTNodPool.New();
        PROCESS_ERROR( nodRoot[i] );
        memset( nodRoot[i], 0, sizeof( BTNod ) );
        nodRoot[i]->type = btSequencer;
        for( int j = 0; j< nod_width; ++j )
        {
            BOOL ret = nodNewChild( nodRoot[i], nod_depth );
            PROCESS_ERROR( ret );
        }
    }
    PROFILE_POINT( 0 );

    for ( int i = 0; i < run_times; ++i )
    {
        // run
        for( int j = 0; j<10; ++j )
        {
            BTCtx ctx;
            memset( &ctx, 0, sizeof(ctx) );

            ctx.callFrame[ctx.callFrameCount].nod = nodRoot[i];
            ctx.callFrame[ctx.callFrameCount++].child = NULL;

            BTCtx_run( ctx );
        }
    }
    PROFILE_POINT( 0 );

    PROFILE_END();

    // uninit

    for ( int i = 0; i < run_times; ++i )
    {  
        nRetCode = nodDeleteChild(nodRoot[i]);
        LOG_PROCESS_ERROR( nRetCode );
    }

    nRetCode = g_BTNodPool.UnInit();
    PROCESS_ERROR(nRetCode);

    DBG("all btnod run ok!\n");
    return 0;
Exit0:
    DBG("btnod error!\n");
    return -1;
}
