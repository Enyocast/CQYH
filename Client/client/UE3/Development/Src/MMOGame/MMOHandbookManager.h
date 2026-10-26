#ifndef _MMOHANDBOOKMANAGER_H_
#define _MMOHANDBOOKMANAGER_H_

#include "MMOSingleton.h"
#include "MMOGameEvent.h"
#include "UnString.h"
#include "MMOFacade.h"
#include "MMODataManager.h"
#include "MMOHandbookData.h"

enum HandbookClass
{
	HC_Invalid = 0,
	HC_Monster,
	HC_Npc,
	HC_Map,
	HC_Item,
	HC_Equip,
	HC_Rune,
	HC_Spirit,
};

enum HandbookUiType
{
	HUT_Invalid = 0,
	HUT_Monster,
	HUT_Npc,
	HUT_Map,
	HUT_Story,
	HUT_Compose,
	HUT_Stone,
	HUT_Equip,
	HUT_Suit,
	HUT_Rune,
	HUT_Spirit,
};

struct MMOGameEvent_Handbook : public MMOGameEvent
{
public:
	enum EHandbookEventType
	{
		EHET_UpdateHandbookInfo,
	};

	MMOGameEvent_Handbook(EHandbookEventType eventType, UINT32 value1 = 0, UINT32 value2 = 0, UINT32 value3 = 0)
		: _EventType(eventType), _Value1(value1), _Value2(value2), _Value3(value3)
	{
	}

	virtual EGameEvent GetEventType() const
	{
		return GameEvent_Handbook;
	}

	EHandbookEventType _EventType;
	UINT32 _Value1;
	UINT32 _Value2;
	UINT32 _Value3;
};


class MMOHandbookManager : public SingletonMeyers<MMOHandbookManager>, public INativeGameEventHandler
{
public:
	MMOHandbookManager();
	virtual ~MMOHandbookManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);

	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void PlayHandbookSound(UINT32 type, UINT32 index);
	void StopHandbookSound(UINT32 type, UINT32 index);

	void NotifySyncHandbookInfo(ROLE_DB_ACHIEVEMENT_DATA* list);
	void NotifyUpdateHandbookInfo(INT32 type, INT32 index);
	void NotifyUseStoryScroll(INT itemId);

protected:

};

#endif