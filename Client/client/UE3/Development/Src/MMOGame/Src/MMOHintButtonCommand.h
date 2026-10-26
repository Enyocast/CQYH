#ifndef _MMOHINTBUTTONCOMMAND_H_
#define _MMOHINTBUTTONCOMMAND_H_
#include "stdafx.h"

	class IMMOHintButtonCommand 
	{
	public:
		IMMOHintButtonCommand(){};
		virtual ~IMMOHintButtonCommand(){};

		virtual void Click() = 0;


	protected:

	};

	class MMOHintButtonCommand_ArenaQueue :public IMMOHintButtonCommand
	{
	public:
		MMOHintButtonCommand_ArenaQueue(){};
		virtual ~MMOHintButtonCommand_ArenaQueue(){};

		virtual void Click();
	protected:

	};
#endif