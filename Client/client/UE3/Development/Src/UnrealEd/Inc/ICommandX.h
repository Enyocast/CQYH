// *************************************************************************************
// 
// 	Copyright (c) 2007 XGames
// 
// 	All Rights Reserved 
// 
// 	Created by		:		Oscar.Ken
// 	Create Date		:		2008-03-04
// *************************************************************************************

#pragma once
#include "RefObject.h"
#include <stack>
#include <vector>
#include "../../MMOGame/MMOAny.h"

SmartPointer(ICommandX);

class _EngineExport ICommandX : public RefObject
{
public:

	ICommandX();
	virtual ~ICommandX();
	virtual ICommandXPtr Execute() = 0;
};

//--------------------------------------------------------------------------------------

typedef std::stack<ICommandXPtr> CommandStackContainer;

class _EngineExport CommandStack
{
public:

	CommandStack()
	{
	}

	CommandStack(const CommandStack& src)
		: _commandStack(src._commandStack)
	{
	}

	void Push(ICommandXPtr spCmd, bool bExecute = true)
	{
		if(bExecute)
		{
			_commandStack.push(spCmd->Execute());
		}
		else
		{
			_commandStack.push(spCmd);
		}
	}

	ICommandXPtr Top()
	{
		return _commandStack.top();
	}

	void Pop()
	{
		_commandStack.pop();
	}

	void Clear()
	{
		while(!_commandStack.empty())
		{
			_commandStack.pop();
		}
	}

	const CommandStack& operator =(const CommandStack& src)
	{
		if(&src != this)
		{
			_commandStack = src._commandStack;
		}
		return *this;
	}

	size_t Count() const
	{
		return _commandStack.size();
	}

	bool IsEmpty() const
	{
		return _commandStack.empty();
	}

protected:

	CommandStackContainer		_commandStack;
};

//--------------------------------------------------------------------------------------

class _EngineExport BatchCommand : public ICommandX
{
public:

	BatchCommand();
	virtual ~BatchCommand();

	BatchCommand(const CommandStack& commands)
		:_commands(commands)
	{
		_commands = commands;
	}

	ICommandXPtr Execute()
	{
		CommandStack cmds;
		while(_commands.Count() > 0)
		{
			ICommandXPtr cmd = _commands.Top();
			_commands.Pop();
			cmds.Push(cmd);
		}
		return OGRE_NEW BatchCommand(cmds); 
	}

protected:

	CommandStack _commands;
};

SmartPointer(BatchCommand);

//--------------------------------------------------------------------------------------

class _EngineExport ICommandXExecuteObserver
{
public:

	virtual void OnCommandExecuted(const class CommandHistory* cmdHist) = 0;
};

typedef std::vector<ICommandXExecuteObserver*>		CommandExecuteObserverVector;

//--------------------------------------------------------------------------------------	

class _EngineExport CommandHistory: public RefObject
{
public:

	CommandHistory()
		: _isBatchMode(false)
	{

	}

	bool IsUndoEnable() const
	{
		return !_commandsUndo.IsEmpty();
	}

	bool IsRedoEnable() const
	{
		return !_commandsRedo.IsEmpty();
	}

	void Undo()
	{
		if(IsBatchMode())	// if the command hasn't been completed
		{
			EndBatch();
			Undo();
		}

		ICommandXPtr cmd = _commandsUndo.Top();
		_commandsRedo.Push(cmd);
		_commandsUndo.Pop();

		NotifyCommandExecuted();
	}

	void Redo()
	{
		if(IsBatchMode())	// if the command hasn't been completed
		{
			Undo();
		}
		ICommandXPtr cmd = _commandsRedo.Top();
		_commandsUndo.Push(cmd);
		_commandsRedo.Pop();

		NotifyCommandExecuted();
	}

	void Clear()
	{
		EndBatch();

		bool doNotify = !_commandsRedo.IsEmpty() || !_commandsUndo.IsEmpty();

		_commandsRedo.Clear();
		_commandsUndo.Clear();

		if(doNotify)
		{
			NotifyCommandExecuted();
		}
	}

	void AddCommand(ICommandXPtr cmd, bool execute = true)
	{
		if(_isBatchMode)
		{
			_commandsBatch.Push(cmd, execute);
		}
		else
		{
			_commandsUndo.Push(cmd, execute);
		}
		_commandsRedo.Clear();

		NotifyCommandExecuted();
	}

	bool IsBatchMode() const
	{
		return _isBatchMode;
	}

	void BeginBatch()
	{
		_isBatchMode = true;
	}

	void EndBatch()
	{
		if(!_commandsBatch.IsEmpty())
		{
			BatchCommandPtr cmd(OGRE_NEW BatchCommand(_commandsBatch));
			_commandsUndo.Push(cmd, false);				
			_commandsRedo.Clear();
			_commandsBatch.Clear();
			NotifyCommandExecuted();
		}
		_isBatchMode = false;
	}

	void AddCommandExecuteObserver(ICommandXExecuteObserver* pObserver)
	{
		CommandExecuteObserverVector::iterator i = std::find(_cmdExecuteObservers.begin(), _cmdExecuteObservers.end(), pObserver);
		if(i == _cmdExecuteObservers.end())
		{
			_cmdExecuteObservers.push_back(pObserver);
		}
		else
		{
			OGRE_EXCEPT(Exception::ERR_DUPLICATE_ITEM, "Observer already exist!", "CommandHistory::AddCommandExecuteObserver");
		}
	}

	void RemoveCommandExecuteObserver(ICommandXExecuteObserver* pObserver)
	{
		CommandExecuteObserverVector::iterator i = std::find(_cmdExecuteObservers.begin(), _cmdExecuteObservers.end(), pObserver);
		if(i != _cmdExecuteObservers.end())
		{
			_cmdExecuteObservers.erase(i);
		}
		else
		{
			OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Observer not exist!", "CommandHistory::RemoveCommandExecuteObserver");
		}
	}

protected:

	void NotifyCommandExecuted()
	{
		for(CommandExecuteObserverVector::iterator i = _cmdExecuteObservers.begin(); i != _cmdExecuteObservers.end(); ++i)
		{
			(*i)->OnCommandExecuted(this);
		}
	}

	CommandExecuteObserverVector	_cmdExecuteObservers;

	bool				_isBatchMode;

	CommandStack		_commandsRedo;
	CommandStack		_commandsUndo;
	CommandStack		_commandsBatch;
};


//--------------------------------------------------------------------------------

/**
* 动态编辑接口，如鼠标移动物体
* 将鼠标按下下弹起之间所有的移动整合成一个Command以方便undo/redo
*/
class IActiveEdit : public RefObject
{
public:

	virtual ICommandXPtr GetCommand() = 0;
	virtual void Execute(const Any& contex) = 0;
};

SmartPointer(IActiveEdit);

//--------------------------------------------------------------------------------

///
/// AbstractActiveEdit
///
class AbstractActiveEdit : public IActiveEdit
{
public:

	AbstractActiveEdit()
		: _isDirty(false)
	{
	}

protected:

	bool	_isDirty;
};
