#include "StdAfx.h"
#include "MMOLogicCommand.h"

#if 0


LogicCommand::LogicFactoryMap LogicCommand::g_logicFactoryMap;
//------------------------------------------------------------------------
void LogicCommand::RegisterLogicCommandFactory( int commandTypeID, ILogicCommandFactory* factory )
{
	g_logicFactoryMap[commandTypeID] = factory;
}
//------------------------------------------------------------------------
ILogicCommandFactory* LogicCommand::GetLogicCommandFactory( int commandTypeID )
{
	LogicFactoryMap::const_iterator i = g_logicFactoryMap.find(commandTypeID);
	if(i != g_logicFactoryMap.end())
	{
		return i->second;
	}

	return 0;
}
//------------------------------------------------------------------------
LogicCommand::LogicCommand(void)
: _logicCount(0)
, _startTime(0)
, _cmdType(LCT_Invalid)
{
}
//------------------------------------------------------------------------
LogicCommand::~LogicCommand(void)
{
}
//------------------------------------------------------------------------
void LogicCommand::SetLogicCount( INT logicCount )
{
	_logicCount = logicCount;
}
//------------------------------------------------------------------------
void LogicCommand::SetStartTime( UINT startTime )
{
	_startTime = startTime;
}
//------------------------------------------------------------------------
UINT LogicCommand::GetStartTime() const
{
	return _startTime;
}
//------------------------------------------------------------------------
INT LogicCommand::GetLogicCount() const
{
	return _logicCount;
}
//------------------------------------------------------------------------
void LogicCommand::CleanUp()
{
	_startTime = UINT_MAX;
	_logicCount	= -1;

}
//------------------------------------------------------------------------
bool LogicCommand::Modify( const MMO::LogicCommand* pCmd )
{
	return true;
}

#endif