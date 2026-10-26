#ifndef _BT_MANAGER_H_
#define _BT_MANAGER_H_

#include "btnod.h"
#include "lua_script.h"
#include "base_list.h"
#include "bt_event.h"

#define ACTION_NAME_LEN     (128)

#define CREATE_NODE(__parent__, __type__, __param0__, __param1__, __param2__, __param3__)   \
	CBTManager::GetInstance().CreateBTNod(__parent__, __type__, 0, #__type__, __param0__, __param1__, __param2__, __param3__, 0)

#define CREATE_TAG_NODE(__parent__, __type__, __tag__, __param0__, __param1__, __param2__, __param3__)   \
    CBTManager::GetInstance().CreateBTNod(__parent__, __type__, __tag__, #__type__, __param0__, __param1__, __param2__, __param3__, 0)

class CCharacter;
class CScene;

enum BT_OWNER_TYPE
{
    botInvalid,

    botAI,
    botScene,

    botTotal,

    botAIBit = 1 << botAI,
    botSceneBit = 1 << botScene,

    botAll = botAIBit | botSceneBit
};

enum BT_NODE_TAG
{
    bntInvalid = 0,

    bntHead,

    // idle
    bntSelfInCombat,
    bntScanEnemy,
    bntDetectHate,
    bntWander,

    // fight
    bntTargetOutOfHome,
    bntTargetDie,
    bntFlee,
    bntChangeTarget,

    bntFightMove,
    bntChase,
    bntFightWander,

    bntScanNearby,

    bntHealSelf,
    bntHealFriend,
    bntBreakCastingEnemy,

    bntDebuffSelf,
    bntBuffSelf,

    bntNormalSpellToTarget,
    bntNormalSpellToNearestEnemy,

    bntTotal,
};

enum BT_RUNNING_TYPE
{
    brtInvalid,

    brtWait,
    brtSyncMove,
    brtSyncRotate,
    brtStepAround,
    brtWaitSelect,
    brtWaitCasting,
	brtWaitBreaking,
	brtWaitMessage,
    brtWaitMSGuildData,

    brtTotal
};

#pragma pack(push, 1)
struct BTCustomCtx : BTCtx
{
    unsigned        eEventType      : 6;
    unsigned        eOwnerType      : 2;
    unsigned        eRunningType    : 8;
    unsigned        uReserved       : 16;
    INT32           nWaitFrame;
    UINT32          dwRoleID;
    union
    {
        void*           poOwner;
        CCharacter*     poChar;
        CScene*         poScene;
    };
    CLuaScript*     poScript;
    BASE_LIST_NODE  ListNode;
};
#pragma pack(pop)

typedef INT32 (*BT_ACTION_FUNC)(BTCustomCtx* pProcessor, INT32 nParam[]);
class CRole;

class CBTManager
{
public:
	CBTManager();
	~CBTManager();

	BOOL Init(void);
	BOOL UnInit(void);

	static CBTManager& GetInstance(void);
	BOOL Reload(void);

	BTNod* CreateBTNod(BTNod* pParent, INT32 nType, INT32 nTag, const char* pcszName, 
		INT32 nParam0, INT32 nParam1, INT32 nParam2, INT32 nParam3, INT32 nLuaParam);
	BOOL DestroyBT(BTNod* pRoot, INT32 nLayer = 0);
	BTNod* CopyBT( BTNod* pRoot );
	void PrintBT(BTNod* pRoot, INT32 nLayer);

	INT32 FindBTActionByName(const char* pcszName);
	INT32 RegisterBTAction(const char* pcszName);
	const char* GetBTActionName( INT32 nActionID );

    BOOL CallBTAction(INT32 nBTNodeType, INT32 nParam[]);
    BOOL TestBTAction(CRole* poRole, INT32 nBTNodeType, INT32 nParam[]);

    BOOL GetCtxRoleID();

private:
    static INT32 _NodeFunc(BTCtx* ctx, BTNod* nod);

private:
    static CBTManager       ms_Instance;

    // bt action
    struct ACTION_FUNC_ENTRY
    {
        INT32           nActionID;
        char            szName[ACTION_NAME_LEN];
        BT_ACTION_FUNC  pCFunc;
        INT16           eOwnerMask;
        INT16           bLuaFunc;
    };
    static ACTION_FUNC_ENTRY    ms_ActionFuncList[btTotal];

    struct ltstr
    {
        bool operator()(const char* s1, const char* s2) const 
        {
            return strncmp(s1, s2, SCRIPT_NAME_LEN) < 0;
        }
    };
    typedef std::map<const char*, ACTION_FUNC_ENTRY*, ltstr>     MAP_ACTION_NAME_2_FUNC;
    //typedef std::map< std::string, ACTION_FUNC_ENTRY* >     MAP_ACTION_NAME_2_FUNC;
    MAP_ACTION_NAME_2_FUNC      m_mapActionName2Func;

    INT32                       m_nActionIDGenerator;
    BTCustomCtx*                m_pCurrentCtx;
};

#endif	// _BT_MANAGER_H_