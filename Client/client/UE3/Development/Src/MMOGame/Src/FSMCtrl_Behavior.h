/**
 *
 * 游戏虚拟机(FSM)————角色基础行为状态机
 * Add by jimZhang@sdna.com 2014.5.7 
 * 
 * 用来驱动一些较原子级别的行为，如连移动到一个，移动到一个avtor，攻击一个目标等等
 *
 */

#ifndef __FSMCTRL_BEHAVIOR_H__
#define __FSMCTRL_BEHAVIOR_H__
#include "FSMCtrl.h"

//自动施法----------------------------------------------------
class FSMCtrl_AiAbility: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};
//shift键原地使用技能-----------------------------------------------------------------------------------------------------
class FSMCtrl_ShiftAbility: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//原地释放技能------------------------------------------------------------------------------------------------------------
class FSMCtrl_StayAndUseAbility: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//走向目标并释放技能------------------------------------------------------------------------------------------------------
class FSMCtrl_MoveToAndUseAbility: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//走近并交互--------------------------------------------------------------------------------------------------------------
class FSMCtrl_MoveToAndInteract: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//走到目标点，鼠标按住的情况下，高速操控走向的目标点----------------------------------------------------------------------
class FSMCtrl_MoveToPoint: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//焦点激活------------------------------
class FSMCtrl_FocusActor: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//测试------------------------------
class FSMCtrl_Test: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
private:
	FLOAT	m_DelTime;
};




#endif