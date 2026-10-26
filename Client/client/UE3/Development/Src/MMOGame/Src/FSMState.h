/**
 *
 * 游戏有限虚拟机(FSM)——状态集
 * jimZhang@sdna.com 2014.5.6 
 * 
 * Doule-Level Extensible Finite State Machine
 * 双层可扩展有限虚拟机
 *  
 * 1.底层状态是有限的公共基础状态，底层状态可作为上层状态的输入。同层状态不可作为输入。
 * 2.上层状态是特定状态，不可作为底层状态和同层旁支的输入。
 * 3.状态的刷新有两种方式，自取型和触发型，因其存贮方式的不同（自存型和它存型）。
 * 4.触发型状态刷新提供可扩展接口，状态的更新只依赖自身储存的标志。
 * 5.状态判定模块和可以用底层和上层的状态作为输入。
 * 6.状态执行模块由状态判定模块唯一直接调用。
 *
 */

#ifndef __FSMSTATE_H__
#define __FSMSTATE_H__

#include "stdafx.h"
#include <list>
#include <vector>
#include <map>
#include "MMOSingleton.h"

using namespace std;

#define EPSILON			0.0001f
#define CLICK_TIME		0.3f
#define TIME_SYNC_FAST 	0.125f
#define TIME_SYNC_SLOW 	0.5f

class UMMOAbility;
class AMMOPlayerController;


enum GAME_CONTROL_TYPE
{
	GC_MIR2,					//热血传奇
	GC_DIABLO3,					//暗黑3
	GC_LOL,						//英雄联盟
	GC_MIRFOREVER,				//传奇永恒
};

enum KEY_TYPE
{
	KT_NONE,					//无
	KT_PRIMARY,					//主键
	KT_SECONDARY,				//次键
	KT_ELSE,					//其他
};


class IFSMState
{
public:
	IFSMState();
	virtual void Init() = 0;
	virtual void Update(FLOAT DelTime) = 0;
};


class FSMStateManager : public SingletonMeyers<FSMStateManager>
{
private:
	std::vector<IFSMState*> IFSMStateList;
	typedef std::vector<IFSMState*>::iterator FSMStateIterator;
public:
	void Init();
	void AddGameState(IFSMState* pState);
	void Update(FLOAT DelTime);
};


//鼠键输入系列状态----------------------------------------------------------------
class FSMState_Input: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	UBOOL		ShiftDown;					//shift是否按下
	UBOOL		LeftBtnDown;				//鼠标左键是否按下
	UBOOL		RightBtnDown;				//鼠标右键是否按下
	UBOOL		CtrlBtnDown;				//Ctrl是否按下
	UBOOL		AltBtnDown;					//Alt是否按下

	UBOOL		ShiftDown_Last;				
	UBOOL		LeftBtnDown_Last;			
	UBOOL		RightBtnDown_Last;			
	UBOOL		CtrlBtnDown_Last;		
	UBOOL		AltBtnDown_Last;					
};



//主角相关系列状态-------------------------------------------------------------
class FSMState_Charactor: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	AMMOPlayer*				MainPlayer;		//主角
	AMMOPlayerController*	Controller;		//主控制
	UBOOL					MoveEnable;		//主角可否移动
	UBOOL					MoveEnableInAdvance;	//主角可否发布移动命令
	UBOOL					IsDead;
	INT						AbilityActionNum;//等待执行的技能action数	
	INT						nCannotInterruptLevel;//打断标志和标志等级
};



//各种倒计时系列状态----------------------------------------------------------
class FSMState_CDTime: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	FLOAT			KeyPressedTime;			//按键累计时间;
	FLOAT			FastTime;				//快循环计时;
	FLOAT			SlowTime;				//慢循环计时;
	FLOAT			RotationCDTime;			//旋转CD时间;
	FLOAT			AiCdTime;				//ai控制型cd;
	FLOAT			AbilityRespondTime;		//等待技能消息回应时间;
	FLOAT			SwitchRespondTime;		//开关技能锁定时间
	FLOAT			AiInSafeZoneTime;		//ai控制在安全区收刀时间;
	FLOAT			CheckWeaponBindTime;	//检查武器绑定时间;
	FLOAT			AiBossQTETime;			//boss qte的检测时间
	FLOAT			WarningTime;			//警告计时器
	FLOAT			FocusTime;				//焦点激活倒计时
	FLOAT			WalkDelayTime;		//释放了魔法类技能，有一定的行走cd
	FLOAT			RunDelayTime;		//释放了魔法类技能，有一定的行走cd
	FLOAT			MoveDelayTime;		//移动限制
	FLOAT			MoveDelayFrame;		//移动限制帧数
	FLOAT			DoAIAbilityCD;		//ai施法间隔时间
};



//技能系列状态----------------------------------------------------------------
class FSMState_Ability: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	//UMMOAbility*	GetDefaultAbility();
	//UMMOAbility*	OptimizeAbility(UMMOAbility* Ability);
	//void SetDesireAbility(UMMOAbility*	Ability);
public:
	UMMOAbility*	DesireFClassAbility;			//按键施放的技能（设定F）
	UMMOAbility*	DesireAbility;			//按键施放的技能（设定）
	UMMOAbility*	UsableAbility;			//按键施放的技能（能用）
	UMMOAbility*	CurrentAbility;			//当前施放的技能（能用）
	UMMOAbility*	CacheAbility;			//缓存的技能
	UBOOL			PickTarget;				//原地施放技能标志
	UBOOL			AbilityEnable;			//是否可以施放当前技能
};



//目标系列状态----------------------------------------------------------------
class FSMState_Target: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	void SetTargetActor(AActor* TargetActor);
	void ClearActor(AActor* Actor);
	FVector SmoothTargetPos(FVector TargetPos);
	FVector OptimizeTargetPos(FVector TargetPos);
	INT		OptimizeTargetID(FRotator Rotator,FVector Location,FLOAT Radius);

	INT OptimizeDoodadID(const FVector& Location,FLOAT Radius);


public:
	//当前的
	AActor*			CurTargetActor;			//当前鼠标指定的目标actor
	AActor*			LastTargetActor;		//上次鼠标指定的目标actor
	AMMOActor*		CurTargetMMOActor;		//当前鼠标指定的目标mmoactor
	AMMOActor*		LastTargetMMOActor;		//上次鼠标指定的目标mmoactor
	INT				CurTargetMMOActorID;
	INT				LastTargetMMOActorID;
	AMMOPlayer*		CurTargetMMOPlayer;		//当前鼠标指定的目标player
	ANPC*			CurTargetNPC;			//当前鼠标指定的目标npc
	FVector			CurTargetPos;			//当前目标点(平滑过)
	FVector			CurOptimizeTargetPos;	//当前目标点(优化过)
	UBOOL			TargetAttackble;		//当前目标是否可以攻击
	UBOOL			TargetIsDead;			//当前目标是否死亡

	//锁定的
	AActor*			DesireActor;			//锁定的目标actor
	AMMOActor*		DesireMMOActor;			//锁定的目标mmoactor
	AMMOActor*		LastDesireMMOActor;		//上次锁定的目标mmoactor
	AMMOPlayer*		DesireMMOPlayer;		//锁定的目标mmoplayer
	ANPC*			DesireNPC;				//锁定的目标npc
	INT				DesireNPCTempleteID;	//锁定目标npctempleteID
	FVector			DesirePos;				//锁定目标点
	UBOOL			DesireAttackble;		//锁定目标是否可攻击
	TScriptInterface<IIInteractableActor>	DesireInteractableActor; //锁定可交互的对象
	UBOOL			DesireMMOActorChangeFlag; //锁定切换标志

	//技能锁定目标
	AMMOActor*		AbilityTargetMMOActor;	//技能锁定目标

	AMMOActor*		AttackMMOActor;			//攻击目标mmoactor
	AMMOActor*		SelectMMOActor;			//选择目标mmoactor

	FVector			LastMouseHitNavMeshLocation;			//上次/帧鼠标拾取点
	FVector			LastMainPlayerPos;						//上次角色位置点
	FVector			LastOffsetDes;			//上次角色的朝向

	//ui锁定
	INT				UITargetMMOActorID;
	//tips相关
	UBOOL			CaptureInput;
	UBOOL			ShowUITipsFlag;
	//
	FLOAT			UpdateSceneHintTime;
	INT				UpdateSceneHintID;

};

//触发事件标志----------------------------------------------------------
class FSMState_Trigger: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	UBOOL			IsTargetTrigger;		//当前目标触发事件
	UBOOL			IsDesireTrigger;		//锁定目标触发事件
	UBOOL			IsDesirePosTrigger;		//锁定地点触发事件
	UBOOL			IsWaitingSendMove;		//等待成功发送移动消息
	FLOAT			DelayTimeWaitingSendMove;
};

//控制系列状态----------------------------------------------------------
class FSMState_Ctrl: public IFSMState
{
public:
	void Init();
	void Update(FLOAT DelTime);
public:
	UBOOL				IsBattleState;			//战斗状态
	UBOOL				IsGuildBattle;			//公会战状态
	//GAME_CONTROL_TYPE	GameControlType;		//游戏操控方式
	KEY_TYPE			KeyType;				//键种类
	KEY_TYPE			KeyType_Keeping;		//键种类,持续态

	UBOOL				IsSelectCtrl;			//选择控制
	UBOOL				IsMoveCtrl;				//移动控制
	UBOOL				IsActionCtrl;			//行动控制

	UBOOL				state_Switching_Flag;	//状态切换标志
	UBOOL				state_Standby;			//待机状态
	UBOOL				state_Moving;			//移动状态
	UBOOL				state_Attack;			//攻击状态
	UBOOL				state_Interact;			//交互状态
	UBOOL				state_AiDesire;			//搜寻状态

	UBOOL				state_AlwaysWalk;		//强制走状态
	UBOOL				state_AlwaysWalkBase;	//强制走状态基础态

	UBOOL				state_OpenPrivateChat;	//智能打开私聊

	UBOOL				ctrlFlag_IgnoreShiftBtn;//免shift键
	UBOOL				ctrlFlag_DDCS;			//刀刀刺杀
	UBOOL				ctrlFlag_ZNBY;			//智能半月
	UBOOL				ctrlFlag_ZDZR;			//自动逐日
	UBOOL				ctrlFlag_ZDLH;			//自动烈火
	UBOOL				ctrlFlag_ZDYS;			//自动隐身
	UBOOL				ctrlFlag_ZDKD;			//自动开盾
	FLOAT				ctrlAttackAi_LastDelay;	//LastServerLocation的延迟时间
	FLOAT				ctrlAttackAi_LockTime;	//刚静止后的锁定时间，防止因为serverlocation的移动，产生的空挥

	UBOOL				IsWantToSendRequest4000Or4001Ability;

	UBOOL				ctrlKeepRunning;		//保持向前跑动
	FVector				vecRotation;			//保持向前方向向量
};


namespace FSM{
	extern FSMState_Input			Input;
	extern FSMState_Charactor		Char;
	extern FSMState_Ability			Ability;
	extern FSMState_CDTime			CDTime;
	extern FSMState_Target			Target;
	extern FSMState_Trigger			Trigger;
	extern FSMState_Ctrl			Ctrl;
}









#endif