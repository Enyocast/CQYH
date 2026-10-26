#ifndef _MMO_BOSSBLOODMANAGER_H_
#define _MMO_BOSSBLOODMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "MMOGameClasses.h"
#include "common.h"

struct MMOGameEvent_BossBlood : public MMOGameEvent
{
public:
	enum EBossBlood_Event
	{
		EBossBlood_Event_Appear,
		EBossBlood_Event_Destroy,
	};

	MMOGameEvent_BossBlood(EBossBlood_Event eventType)
		: eventBoss(eventType),nCurHp(0),nMaxHp(1),nLevel(1)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_DynamicBossBlood;
	}

	FString title;
	INT     nCurHp;
	INT     nMaxHp;
	INT     nLevel;
	EBossBlood_Event eventBoss;
	BYTE	byteQuality;
};

class MMOBossBloodManager: public SingletonMeyers<MMOBossBloodManager>, public INativeGameEventHandler
{
public:
	void Init();
	void Shutdown();

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
	void SetBossID(INT nBoss);
	INT  GetBossID();

private:
	INT  nBossID;
};

#endif