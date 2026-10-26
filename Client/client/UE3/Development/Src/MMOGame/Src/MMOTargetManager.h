/**
 * jimZhang@sdna.com 2013.1.22 
 *
 * 暗黑3来袭，技能施放和角色控制要做到细腻人性化，智能化
 * 总述1-4技能，鼠标左右键技能，鼠标左键兼做行走控制
 * 轻按1-4和鼠标右键技能键，如果是典型指向技能，会检测鼠标所指位置，
 * 如有敌人，则走过去对敌人施放技能
 * 如无敌人，则相当于走过去
 * 按住1-4和鼠标右键技能键，如果是典型指向技能，会检测鼠标所指位置，
 * 相当于一路A过去，
 */

#ifndef __MMOTARGETMANAGER_H__
#define __MMOTARGETMANAGER_H__

#include "stdafx.h"
#include <list>
#include <vector>
#include <map>
#include "MMOSingleton.h"

using namespace std;

class UMMOAbility;
class AMMOPlayerController;

struct MMOGameEvent_TargetChange : public MMOGameEvent
{
public:

	enum ETargetChangeType
	{
		ETCT_DesiredTarget,
		ETCT_CurrentTarget
	};

	MMOGameEvent_TargetChange(ETargetChangeType evtType, AMMOActor* currentTarget, AMMOActor* desiredTarget = 0)
		: EventType(evtType)
		, CurrentTarget(currentTarget)
		, DesiredTarget(desiredTarget)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_TargetChange;
	}

	ETargetChangeType EventType;
	class AMMOActor* CurrentTarget;
	class AMMOActor* DesiredTarget;

};



class MMOTargetManager : public SingletonMeyers<MMOTargetManager>
{

	enum CTRL_STATE
	{
		CS_IDLE,					//待机态
		CS_MOVE,					//移动态
		CS_BATTLEMOVE,				//战斗态
	};

	enum DESIRE_STATE				//状态触发
	{
		DS_NORMAL,					//低电平				
		DS_TRIGGER,					//升触发
		DS_HOLDON,					//高电平
		DS_RELEASE,					//降触发	
	};

	enum SEARCH_TYPE
	{
		ST_CLOSED_ALL,				//靠的最近的所有类型obj
		ST_CLOSED_DAMAGEABLE,		//靠的最近的可攻击类型
		ST_CLOSED_FRIENDLY,			//靠的最近的友好类型
		ST_INNER_ALL,				//在范围内的先被检测到的所有类型
		ST_INNER_DAMAGEABLE,		//在范围内的先被检测到的可攻击类型
		ST_INNER_FRIENDLY,			//在范围内的先被检测到的友好类型	
	};

public:
	MMOTargetManager();
	virtual ~MMOTargetManager(){};

private://各种状态
	UBOOL			stateInterrupt;			//顺序中断，用于相同判定状态下，根据重要顺序性判定，这是唯一依赖排列的，是串行的，其余的条件全是并行的，对执行先后无影响
	
	AMMOPlayer*		stateMainPlayer;		//主角
	AMMOPlayerController*	stateController;//主控制
	UBOOL			stateStallState	;		//摆摊状态

	UMMOAbility*	stateLeftBtnAbility;	//左键装备的技能
	UMMOAbility*	stateDesireAbility;		//按键施放的技能（初始）
	UMMOAbility*	stateAbility;			//按键施放的技能（能用）
	UBOOL			stateKeyPressed;		//按下键	
	UBOOL			stateShiftDown;			//shift是否按下
	UBOOL			stateLeftBtnDown;		//鼠标左键是否按下
	UBOOL			stateLeftBtn;			//鼠标左键激发的技能
	UBOOL			stateAbilityEnable;		//是否可以用技能
	UBOOL			stateMoveEnable;		//可以行走
	UBOOL			stateMoveKeyDown;		//移动按键有按
	UBOOL			statePathOptimize;		//寻路点是否为不为直线或者优化过
	UBOOL			stateIsShowTips;		//显示物体tips
	UBOOL			statePickTarget;		//当前技能是否pickTarget

	AActor*			stateLastTargetActor;	//上一帧目标actor
	AActor*			stateTargetActor;		//目标actor
	AMMOActor*		stateLastTargetMMOActor;//上一帧目标mmoactor
	AMMOActor*		stateTargetMMOActor;	//目标mmoactor
	INT				stateTargetMMOActorID;		//
	INT				stateLastTargetMMOActorID;	//
	AMMOPlayer*		stateTargetMMOPlayer;	//目标mmoplayer
	ANPC*			stateTargetNPC;			//目标npc
// 	ADropItemActor* stateTargetItem;		//目标捡取物
	ATeleportOrig*	stateTeleportOrig;		//目标传送点
	ATeleportNetNode* stateTeleportNetNode;	//目标传送网点
	AMMODoodadActor*  stateDoodadActor;	//doodad指针		
	UBOOL			stateAttackble;			//目标是否可攻击
	UBOOL			stateIsDead;			//目标是否死亡
	FVector			stateTargetPos;			//目标点

	AActor*			stateDesireActor;		//初始目标actor
	AMMOActor*		stateDesireMMOActor;	//初始目标mmoactor
	AMMOActor*		stateLastDesireMMOActor;//上一帧初始目标mmoactor
	AMMOPlayer*		stateDesireMMOPlayer;	//初始目标mmoplayer
	ANPC*			stateDesireNPC;			//初始目标npc
	INT				stateDesireNPCTempleteID;//初始目标npctempleteID
	//AMMODropActor* stateDesireItem;		//初始目标捡取物
	UBOOL			stateDesireAttackble;	//初始目标是否可攻击
	FVector			stateDesirePos;			//初始目标点
	FLOAT			stateSetFocusDelayTime; //申请选择消息延时

	AMMOActor*		stateAttackMMOActor;	//攻击目标mmoactor
	AMMOActor*		stateSelectMMOActor;	//选中的mmoactor目标

	AActor*			stateFocusActor;		//焦点actor
	AMMOActor*		stateFocusMMOActor;		//焦点mmoactor
	AMMOPlayer*		stateFocusMMOPlayer;	//焦点mmoplayer


	CTRL_STATE		stateCtrlState;			//角色控制状态，根据研究暗黑3得到两个状态，加上一个待机态
	DESIRE_STATE	stateDesireState;		//按键状态

	FLOAT			statePressedTime;		//按键累计时间;
	FLOAT			stateFastTime;			//快循环计时;
	FLOAT			stateSlowTime;			//慢循环计时;
	FLOAT			stateAiCdTime;			//ai控制型cd;
	FLOAT			stateAbilityRespondTime;//等待技能消息回应时间;
	FLOAT			stateAiInSafeZoneTime;	//ai控制在安全区收刀时间;
	FLOAT			stateWarningTime;		//警告即使器


private:
	FVector			LastMouseHitNavMeshLocation;			//上次/帧鼠标拾取点
	FLOAT			TimeQTE;								//QTE计时;
	INT				AresFlag;								//gm 自动进化战神模式
	INT				AresIndex;								//gm 自动进化战神模式序号
	FLOAT			AresDeltaTime;							//步骤间隔时间

private://各种状态
	//按shift键施法
	UBOOL	stateShiftAbility();
	//原地释放技能
	UBOOL	stateStayAndUseAbility();
	//追击并释放技能
	UBOOL	stateMoveToAndUseAbility();
	//搜索敌人并释放技能
	UBOOL   stateSearchAndUseAbility();
	//走近并交互
	UBOOL	stateMoveToAndInteract();
// 	//走近并摆摊
// 	UBOOL	stateMoveToAndStall();
// 	//走近捡东西
// 	UBOOL	stateMoveToPickItem();
	//走到目标点
	UBOOL	stateMoveToPoint();
	//走到指定坐标点
	UBOOL	stateMoveToDesirePoint();
	//选中显示第三方头像
	UBOOL	stateShowInfo();
	//选中物体tips显示
	UBOOL	stateShowTips();
	//选中物体脚底光标显示
	UBOOL	stateShowSelectMark();
	//键盘控制移动
	UBOOL	stateMoveByKey();
	//自动寻怪
	UBOOL	stateSearchEnemy();
	//自动切换键状态
	UBOOL	stateAIContral();
	//自动检测在安全区内收刀
	UBOOL	stateAIInSafeZone();
	//自动是否要释放解qte技能
	UBOOL	stateAIBossQTE();
	//摆摊时候点击处理
	UBOOL	stateClickStallState();
	//特殊的定时提示，比如主武器的耐久度不等间隔警示
	UBOOL	stateStackWarningState();
	//智能清除分解，鉴定，修理等状态，
	UBOOL	stateReleaseOperation();
	//gm 组合测试，自动成为战神
	UBOOL	stateUpdateAres();

private:
	FVector			OptimizeTargetPos(FVector TargetPos );	//获取优化点
	UMMOAbility*	OptimizeAbility(UMMOAbility* Ability);	//获取优化技能
	INT				OptimizeTargetID(FRotator Rotator, FVector Location,FLOAT Radius, SEARCH_TYPE SType);	//获取优化的目标 
	FVector			OptimizeMoveOffset(BYTE* pMode );

public:
	UMMOAbility*	GetDefaultAbility();	//获取各种职业默认技能

public://各种方法
	void	Clear();
	void	AITick(FLOAT DeltaTime);
	UBOOL	UpdateState(FLOAT DeltaTime);
	void	SetDesirePos(FVector Pos,INT NPCTempleteID=0);
	void	SetDesireTarget(UMMOAbility* Ability,AActor* Target,UBOOL bLeftMouseBtn=FALSE);
	void	ClearDesireTarget(UMMOAbility* Ability = NULL);
	
	void	ClearActor(AActor* Actor);

	AActor*	GetDesireActor();

	void	SetTargetActor(AActor* TargetActor);
	AMMOActor*	GetTargetMMOActor();
	AMMOActor*	GetLastTargetMMOActor();

	void	SetFocusActor(AActor* FocusActor);
	AActor*	GetFocusActor();

	AMMOActor*	GetSelectMMOActor();
	void	SetSelectMMOActor(AMMOActor* SelectActor);

	void	EnterScene();
	void	ResetSafeZoneDelayTime();
	void	StartAres(){if(AresFlag<=0)AresFlag=1;};

};







#endif