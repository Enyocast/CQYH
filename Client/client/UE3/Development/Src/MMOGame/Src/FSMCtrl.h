/**
 *
 * 游戏有限虚拟机(FSM)——控制集
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

#ifndef __FSMCTRL_H__
#define __FSMCTRL_H__

#include "stdafx.h"
#include <list>
#include <vector>
#include <map>
#include "MMOSingleton.h"

using namespace std;

class AActor;
class UMMOAbility;
class AMMOPlayerController;

#define ADD_FSM_CTRL(ctrl) ctrl g_##ctrl##_Unvisible_Instance;


class IFSMCtrl
{
public:
	IFSMCtrl();
	virtual UBOOL Update(FLOAT DelTime) = 0;
	virtual void Action() = 0;

};


class FSMCtrlManager : public SingletonMeyers<FSMCtrlManager>
{
private:
	std::vector<IFSMCtrl*> IFSMCtrlList;
	typedef std::vector<IFSMCtrl*>::iterator FSMCtrlIterator;
public:
	void AddFSMCtrl(IFSMCtrl* pFSMCtrl);
	void Update(FLOAT DelTime);

};

#endif