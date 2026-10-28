#ifndef _QUEUE_MATCH_DEF_H_
#define _QUEUE_MATCH_DEF_H_
#define MAX_BATTLE_TEMPLATE_COUNT	(32)
#define MAX_ARENA_GROUP_COUNT		(32)
#define MAX_ARENA_MATCH_GROUP		(3)
#define MAX_ARENA_TEMPLATE_COUNT	(32)

#define MAX_ABNORMAL_LEAVE_TIME		(120)
#define MAX_JOIN_CONFIRM_TIME		(60)

enum BATTLE_TEMPLATE_TYPE
{
	bttInvalid = -1, 
	bttFixed,
	btt5V5,
	btt10V10,
	btt15V15,
	btt10V10V10,
	btt20V20,
	bttTotal
};

enum BATTLE_FACTION
{
	bfInvalid = -1,
	bfFirst,
	bfSecond,
	bfThrid,
	bfFourth,
	bfTotal
};

enum QUEUE_STATE
{
	qsInvalid = -1,
	qsNotInQueue,
	qsInQueue,
	qsQueueConfirm,
	qsTotal
};

struct QUEUE_DATA
{
	UINT8		byQueue;
	UINT32		dwJoinConfirmTimeOut;
	UINT32		dwJoinSceneTempID;
	UINT32		dwJoinSceneID;
	UINT32		dwJoinSide;
};

#endif