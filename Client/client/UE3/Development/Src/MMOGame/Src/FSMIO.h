/**
 *
 * 游戏有限虚拟机(FSM)——IO接口
 * jimZhang@sdna.com 2014.5.7 
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

#ifndef __FSMIO_H__
#define __FSMIO_H__

#include "stdafx.h"
#include "MMOSingleton.h"
#include "FSMCtrl_TargetTips.h"

class AActor;
class UMMOAbility;
class AMMOPlayerController;

class FSMIO_CDTime
{
public:
	void ResetCD_SafeZoneDelayTime();
	void ResetCD_CheckWeaponBindTime(FLOAT CheckTime);
	void ResetCD_AbilityRespondTime(FLOAT bRespondTime=0.2f);
	void ResetCD_SwitchRespondTime(FLOAT bRespondTime);
	void ResetCD_MoveDelay(FLOAT fDelayTime);
	void ResetCD_MoveDelay_Frame(INT nDelayFrame);
	void ResetCD_WalkAndRunDelay(FLOAT fWalkDelayTime,FLOAT fRunDelayTime);

};

class FSMIO_State
{
public:
	void ClearAllState();
};

class FSMIO_Ability
{
public:
	UMMOAbility* GetDefaultAbility();
	UBOOL CanUseAnyAbility(class UMMOAbility* InAbility);
	void SetCurrentAbility(class UMMOAbility* InAbility);

};

class FSMIO_Target
{
public:
	//设置目标
	void SetDesirePos(FVector Pos, INT NPCTempleteID);
	void SetDesireActor(AActor* Target);
	void SetCacheAbility(UMMOAbility* Ability);
	void SetDesireAbility(UMMOAbility* Ability);
	void SetDesireFClassAbility(UMMOAbility* Ability,UBOOL bAddOrRemove);
	void SetDesireTarget(UMMOAbility* Ability,AActor* Target);
	void SetDesireActor_FromAbility();
	void SetUITargetActor(INT nUITargetMMOActorID);
	
	
	void SetInputText();
	//取消攻击
	void ClearDesireActor();
	void ClearDesireAbility(UMMOAbility* Ability);
	void ClearDesireTarget(UMMOAbility* Ability);
	UMMOAbility* GetDesireAbility();
	//设置选择目标
	void SetSelectMMOActor(AActor* Actor);
	void UpdateDesireAbility(int slotId, int abilityId);

	//设置目标actor
	void SetTargetActor(AActor* TargetActor);
	void SetDropActor(AActor* TargetActor);
	//当一个actor消亡
	void ClearActor(AActor* Actor);

	void SetKeepRunning(UBOOL bRunning);
	void ToggleKeepRunning();

	//获取当前目标
	AMMOActor*	GetTargetMMOActor();
	AMMOActor*	GetDesireMMOActor();
	AMMOActor*	GetAttackMMOActor();
	AMMOActor*	GetSelectMMOActor();
	AActor*		GetDesireActor();
};

class FSMIO_Ctrl
{
public:
//	void SetMoveCtrl(UBOOL bMoveCtrl);
//	void SetActionCtrl(UBOOL bActionCtrl);
//	void SetSelectCtrl(UBOOL bSelectCtrl);
	void  SetKeyType(KEY_TYPE KeyType);
	void  SetAlwaysWalk(UBOOL bFlag);
	UBOOL GetAlwaysWalk();
	void  SetAlwaysWalkBase(UBOOL bFlag);
	UBOOL GetAlwaysWalkBase();
	void  SetGuildBattle(UBOOL bActive);
	UBOOL GetGuildBattle();
	void StartNavigation();
	UMMOAbility* GetLeftBtnBindAbility(UBOOL bRelease);
	UMMOAbility* GetRightBtnBindAbility(UBOOL bRelease);
	void AbilityKeyDown();
	void AbilityKeyUp();
	void UpdateMoving();
	void SetInputText();
private:
	void PrimaryKeyDown();
	void PrimaryKeyUp();
	void SecondaryKeyDown();
	void SecondaryKeyUp();
	void OtherKeyUp();



};

class FSMIO_Trigger
{
public:
	void  SetWaitingSendMove(UBOOL bFlag);
	UBOOL GetWaitingSendMove();

	void  SetShowTips(UBOOL bShow, UBOOL bForce=FALSE);

};



class FSMIO : public SingletonMeyers<FSMIO>
{
public:
	FSMIO_State		State;
	FSMIO_Target	Target;
	FSMIO_CDTime	CDTime;
	FSMIO_Ability	Ability;
	FSMIO_Ctrl		Ctrl;
	FSMIO_Trigger	Trigger;
};

#endif