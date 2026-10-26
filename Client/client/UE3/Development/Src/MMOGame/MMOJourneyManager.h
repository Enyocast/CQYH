#ifndef _MMOJOURNEYMANAGER_H_
#define _MMOJOURNEYMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "UnString.h"
#include "MMOFacade.h"
#include "MMODataManager.h"
#include "MMOJourneyData.h"

struct MMOGameEvent_Journey : public MMOGameEvent
{
public:
	enum EJourneyEventType
	{
		EJET_LevelChange,
		EJET_KillMonster,
		EJET_KillBoss,
		EJET_ReputationChange,
		EJET_GetAwards,
		EJET_AddAchievement,
		EJET_RemoveAchievement,
		EJET_UpdateAchievement,
		EJET_UpdateAchievementRewards,
	};

	MMOGameEvent_Journey(EJourneyEventType eventType, UINT32 value1 = 0, UINT32 value2 = 0, UINT32 value3 = 0)
		: EventType(eventType)
		, _Value1(value1)
		, _Value2(value2)
		, _Value3(value3)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_Journey;
	}

	EJourneyEventType EventType;
	UINT32 _Value1;
	UINT32 _Value2;
	UINT32 _Value3;
};


class MMOJourneyManager : public SingletonMeyers<MMOJourneyManager>, public INativeGameEventHandler
{
public:
	MMOJourneyManager();
	virtual ~MMOJourneyManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void ActivateJourneyType(JourneyType journeyType);
	void DeactiveJourneyType(JourneyType journeyType);
	void NotifyPlayerLevelChange(INT lastLevel, INT curLevel);

	void SetJourneyTraceExpand(UBOOL expand);
	UBOOL IsJourneyTraceExpand();

	void LoadData(UINT32 journeyData);
	void SaveData();

protected:
	UBOOL _IsExpand;
};

#endif