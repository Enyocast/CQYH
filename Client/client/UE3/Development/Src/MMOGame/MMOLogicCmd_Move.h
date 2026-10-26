#ifndef __LOGICCMD_MOVE_H__
#define __LOGICCMD_MOVE_H__

#if 0

#include "MMOLogicCommand.h"

//------------------------------------------------------------------------
// 角色移动操作命令参数
//------------------------------------------------------------------------
struct LogicCmd_Move_Parameter
{
	FVector TargetPos;
};
//------------------------------------------------------------------------
// 角色移动操作命令
//------------------------------------------------------------------------
class LogicCmd_Move : public LogicCommand
{
public:
	LogicCmd_Move(const FVector& targetPosition);
	virtual ~LogicCmd_Move(void);

	virtual bool Modify(const MMO::LogicCommand* pCmd);

	const FVector& GetTargetPosition() const { return _targetPosition; }
	void SetTargetPosition(const FVector& val) { _targetPosition = val; }

protected:

	FVector _targetPosition;
};

//------------------------------------------------------------------------
// LogicCmd_Move_Factory
//------------------------------------------------------------------------
class LogicCmd_Move_Factory : public ILogicCommandFactory
{
public:

	virtual MMO::LogicCommand* Create(const LogicCommandParameter& par);

};

//------------------------------------------------------------------------
// 角色停止移动操作命令
//------------------------------------------------------------------------
class LogicCmd_StopMove : public LogicCommand
{
public:
	LogicCmd_StopMove(void);
	virtual ~LogicCmd_StopMove(void);

	virtual bool Modify(const MMO::LogicCommand* pCmd);

	const FVector& GetTargetPosition() const { return _targetPosition; }
	void SetTargetPosition(const FVector& val) { _targetPosition = val; }

protected:

	FVector _targetPosition;
};

//------------------------------------------------------------------------
// LogicCmd_Move_Factory
//------------------------------------------------------------------------
class LogicCmd_StopMove_Factory : public ILogicCommandFactory
{
public:

	virtual MMO::LogicCommand* Create(const LogicCommandParameter& par);

};

#endif

#endif