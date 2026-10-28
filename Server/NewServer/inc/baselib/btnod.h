#ifndef __BTNod_H__
#define __BTNod_H__

#define BTNOD_DEBUG 1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BTNod 子节点容器
enum
{
	MAX_BT_CHILD_COUNT = 64,
    MAX_CALL_FRAME = 16,
    MAX_BT_PARAM = 4,
    BT_NODE_NAME_LEN = 32,
    BT_REPEAT_MAX_TIMES = 32,
};

// 行为树节点可能返回的状态
enum BT_RETURN_VALUE 
{
    brvError = -1,

    brvFail,
    brvSuccess,
    brvRunning,

    brvTotal
};

enum BTN_TYPE 
{
    btInvalid	    = 0,

    btSelector,
    btSequencer,
    btParallel,
    btNot,
    btDebug,
    btRandom,
    btRepeat,

    btUserDefine,

    btTotal         = 1024
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BTNod
{	                
	INT16           type;	// refer to BTN_TYPE
    INT16           childrenCount;  // redundant record, can remove
    BTNod*          child;
    BTNod*          sibling;

    INT32           params[MAX_BT_PARAM];

    union 
    {
        INT32       flag;
        struct 
        {
            unsigned    luaParam    : 8;
            unsigned    repeatCounter    : 8;
            unsigned    nodeTag     : 16;
        };
    };
};                  

struct BTCtx
{
    struct CallFrame
    {
        BTNod*      nod;
        BTNod*      child;
    };
    CallFrame   callFrame[MAX_CALL_FRAME];

    UINT8       callFrameCount;
    UINT8       debugging;
    INT16       returnValue;
};

BOOL BTNod_addChild( BTNod* thiz, BTNod* child );
BOOL BTNod_removeChild( BTNod* thiz, BTNod* child );

BTNod* BTNod_GetChild( BTNod* thiz, INT32 nIndex );

// add tail if tag not exist
BOOL BTNodInsertChildAtTag( BTNod* parent, INT32 nTag, BTNod* newChild );

void BTCtx_run( BTCtx& thiz );

typedef INT32 (*BT_NODE_FUNC)(BTCtx* ctx, BTNod* node);
void registerNodeFunc(BT_NODE_FUNC pNodeFunc);

#endif // __BTNod_H__
