/**
 *
 * 游戏虚拟机(FSM)————目标物体信息状态机
 * Add by jimZhang@sdna.com 2014.5.9 
 * 
 * 用来触发一些鼠标拣选物体需要显示的信息
 * 
 */

#ifndef __FSMCTRL_TARGETTIPS_H__
#define __FSMCTRL_TARGETTIPS_H__
#include "FSMCtrl.h"

struct MMOGameEvent_TargetEvent : public MMOGameEvent
{
public:

	enum ETargetChangeType
	{
		ETCT_DesiredTarget,
		ETCT_CurrentTarget
	};

	MMOGameEvent_TargetEvent(ETargetChangeType evtType, AMMOActor* currentTarget, AMMOActor* desiredTarget = 0)
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

//目标物体弹出tips

//目标的头像条-------------------------------------------------------------------------------
class FSMCtrl_TargetInfoHUD: public IFSMCtrl
{
public:
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//传送门tips---------------------------------------------------------------------------------
class FSMCtrl_TeleportTips: public IFSMCtrl
{
public:
	FSMCtrl_TeleportTips();
	UBOOL	Update(FLOAT DelTime);
	void	Action();

private:
	UBOOL	IsShowTips;
};

//Doodad的tips-------------------------------------------------------------------------------
class FSMCtrl_DoodadTips: public IFSMCtrl
{
public:
	FSMCtrl_DoodadTips();
	UBOOL	Update(FLOAT DelTime);
	void	Action();

private:
	UBOOL	IsShowTips;
};

#endif