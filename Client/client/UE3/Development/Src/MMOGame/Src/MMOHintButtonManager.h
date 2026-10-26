
#ifndef _MMOHINTBUTTONMANAGER_H_
#define _MMOHINTBUTTONMANAGER_H_

#include "MMOSingleton.h"
#include "MMOUtil.h"


	//struct MMOGameEvent_BattleTeam : public MMOGameEvent
	//{
	//public:
	//	enum EBattleTeamEventType
	//	{
	//		EBET_UpdateMemberList,
	//		EBET_InviteEnterTeam,
	//	};
	//
	//	MMOGameEvent_BattleTeam(EBattleTeamEventType evtType)
	//		: EvtType(evtType)
	//		, roleID(0)
	//		, roleName(TEXT(""))
	//	{
	//	}
	//
	//	virtual EGameEvent GetEventType() const
	//	{
	//		return GameEvent_BattleTeam;
	//	}
	//
	//	EBattleTeamEventType EvtType;
	//
	//	INT roleID;
	//	FString roleName;
	//};

	enum EHintButtonType
	{
		EHintButtonType_ArenaQueueHint,

		EHintButtonType_Count,
	};

	class IMMOHintButtonCommand;

	class MMOHintButtonManager : public SingletonMeyers<MMOHintButtonManager>
	{
	public:

		MMOHintButtonManager();
		virtual ~MMOHintButtonManager();

		void Init();
		void Shutdown();

		void AddNewButton( EHintButtonType type , INT time , UBOOL add  );
		void RemoveButton( EHintButtonType type );

		void ClickButton( INT pos );

		void ClearAllButton();

	protected:
		typedef	std::map< INT , FString, M_UE3_STL_ALLOC_MAP(INT, FString)  > HintIconMap;
		typedef std::vector< INT, M_UE3_STL_ALLOC(INT) > HintPosVec;
		typedef std::map< INT , IMMOHintButtonCommand*, M_UE3_STL_ALLOC_MAP(INT, IMMOHintButtonCommand*) > HintButtonCommandMap;

		HintIconMap _HintIconMap;
		HintPosVec	_HintPosVec;
		HintButtonCommandMap	_HintCommandMap;

	};
#endif