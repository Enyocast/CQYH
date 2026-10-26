#ifndef __LOGICCOMMAND_H__
#define __LOGICCOMMAND_H__

#if 0

#include "MMOAny.h"


class ILogicCommandFactory;

//------------------------------------------------------------------------
// 逻辑操作命令类型
//------------------------------------------------------------------------
enum ELogicCommandType
{
	LCT_Invalid = -1,
	LCT_Action,				// 动作
	LCT_StopAction,			// 停止动作
	LCT_Move,				// 移动
	LCT_StopMove,			// 中止移动
	LCT_AbilityUse,			// 直接使用技能
	LCT_AbilitySpell,		// 分解技能聚气
	LCT_AbilityCast,		// 分解技能发招
	LCT_AbilityGuide,		// 分解技能引导
	LCT_LifeAbility,		// 生活技能
	LCT_Max
};

//------------------------------------------------------------------------
// 逻辑操作命令参数
//------------------------------------------------------------------------
struct LogicCommandParameter
{
	int CommandTypeID;
	int LogicCount;
	Any CommandData;
};

//------------------------------------------------------------------------
// 逻辑操作命令数据结构封装
//------------------------------------------------------------------------
class LogicCommand// : public FUseSystemMallocForNew
{
public:

	LogicCommand(void);
	virtual ~LogicCommand(void);

	UINT GetStartTime() const;
	INT GetLogicCount() const;

	void CleanUp();

	ELogicCommandType GetCommandID() const { return _cmdType; }
	void SetCommandID(ELogicCommandType val) { _cmdType = val; }

	virtual bool Modify(const MMO::LogicCommand* pCmd);

	static void RegisterLogicCommandFactory(int commandTypeID, ILogicCommandFactory* factory);
	static ILogicCommandFactory* GetLogicCommandFactory(int commandTypeID);

protected:

	// 起始时间
	UINT	_startTime;

	// 逻辑计数
	INT		_logicCount;

	// 技能类型
	ELogicCommandType _cmdType;

	// 逻辑命令工厂管理
	typedef std::map<int, ILogicCommandFactory*> LogicFactoryMap;
	static LogicFactoryMap g_logicFactoryMap;

	void SetStartTime(UINT startTime);
	void SetLogicCount(INT logicCount);
};

//------------------------------------------------------------------------
// 逻辑操作命令对象工厂
//------------------------------------------------------------------------
class ILogicCommandFactory
{
public:

	virtual MMO::LogicCommand* Create(const LogicCommandParameter& par) = 0;
};

template<class FactoryType, int CmdTypeID>
struct TRegLogicCmdFactory
{
	FactoryType Factory;

	TRegLogicCmdFactory()
	{
		LogicCommand::RegisterLogicCommandFactory(CmdTypeID, &Factory);
	}
};

#define M_REG_LOGIC_CMD_FACTORY(CmdTypeID, FactoryClass) static MMO::TRegLogicCmdFactory<FactoryClass, CmdTypeID> g_##FactoryClass;


#endif
#endif