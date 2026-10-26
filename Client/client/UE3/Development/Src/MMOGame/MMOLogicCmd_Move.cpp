#include "StdAfx.h"
#include "MMOLogicCmd_Move.h"

#if 0


LogicCmd_Move::LogicCmd_Move(const FVector& targetPosition)
: _targetPosition(targetPosition)
{
	_cmdType = LCT_Move;
}
//------------------------------------------------------------------------
LogicCmd_Move::~LogicCmd_Move(void)
{
}
//------------------------------------------------------------------------
bool LogicCmd_Move::Modify( const MMO::LogicCommand* pCmd )
{
	if(pCmd != NULL && pCmd->GetCommandID() == LCT_StopMove)
	{
		//CObjectCommand_StopMove *pStopCmd = (CObjectCommand_StopMove*)pCmd;
		//INT nEndNodeIndex	= pStopCmd->GetEndNodeIndex();
		//if(m_nNodeCount > nEndNodeIndex)
		//{
		//	m_nNodeCount = nEndNodeIndex + 1;
		//	m_paposNode[nEndNodeIndex]	= *(pStopCmd->GetEndPos());
		//}
		return true;
	}
	return false;
}
//------------------------------------------------------------------------
// LogicCmd_Move_Factory
//------------------------------------------------------------------------
MMO::LogicCommand* LogicCmd_Move_Factory::Create( const LogicCommandParameter& par )
{
	LogicCmd_Move_Parameter para = any_cast<LogicCmd_Move_Parameter>(par.CommandData);
	LogicCmd_Move* cmd = new LogicCmd_Move(para.TargetPos);
	return cmd;
}
//------------------------------------------------------------------------
// LogicCmd_StopMove
//------------------------------------------------------------------------
LogicCmd_StopMove::LogicCmd_StopMove(void)
{
	_cmdType = LCT_StopMove;
}
//------------------------------------------------------------------------
LogicCmd_StopMove::~LogicCmd_StopMove(void)
{
}
//------------------------------------------------------------------------
bool LogicCmd_StopMove::Modify( const MMO::LogicCommand* pCmd )
{	
	return false;
}
//------------------------------------------------------------------------
// LogicCmd_StopMove_Factory
//------------------------------------------------------------------------
MMO::LogicCommand* LogicCmd_StopMove_Factory::Create( const LogicCommandParameter& par )
{
	LogicCmd_Move_Parameter para = any_cast<LogicCmd_Move_Parameter>(par.CommandData);
	LogicCmd_StopMove* cmd = new LogicCmd_StopMove();
	cmd->SetTargetPosition(para.TargetPos);
	return cmd;
}
#endif