/**
 *
 * 游戏虚拟机(FSM)————角色AI行为状态机
 * Add by jimZhang@sdna.com 2014.5.9 
 * 
 * 用来驱动一些较复杂的行为逻辑，如连续自动打怪，Attack到一个地方等
 * 
 */

#ifndef __FSMCTRL_AI_H__
#define __FSMCTRL_AI_H__
#include "FSMCtrl.h"

//Keep Running----------------------------------------------------
class FSMCtrl_KeepRunning: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//自动做doodad----------------------------------------------------
class FSMCtrl_SearchDoodad: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};


//进出安全区表演Ai----------------------------------------------------
class FSMCtrl_AIInSafeZone: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//快速查看玩家信息----------------------------------------------------
class FSMCtrl_ShowPlayerInfo: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
};

//玩家头顶名字按钮----------------------------------------------------
class FSMCtrl_ShowHintBtn: public IFSMCtrl
{
public:	
	UBOOL	Update(FLOAT DelTime);
	void	Action();
private:
	UBOOL   _bShowHintBtn;
};

#endif