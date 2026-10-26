#ifndef _UMMOUIJOURNEYTRACEPANEL_H_
#define _UMMOUIJOURNEYTRACEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdateJourneyTraceList();
	void UpdateJourneyTraceInfo(INT journeyId, INT expandType);
	void UpdateJourneyQuestData(INT questId);
	void UpdateJourneyQuestState(INT questEvent, INT questId);
	void UpdateJourneyQuestLevel(INT oldLevel, INT newLevel);
	void PlayJourneySound(INT index);

protected:
	UGFxObject* _CreateJourneyElement(INT journeyType, INT journeyStar, const FString& hintText, UBOOL isComplete, UBOOL isExpand);
	void _SetJourneyElementExpand(UGFxObject* journeyElement, UBOOL isExpand);
	void _AddAcceptedQuestObject(UGFxObject* journeyElement, INT questId, INT& index);
	void _AddAvailableQuestObject(UGFxObject* journeyElement, INT questId, INT& index);
	void _AddMonsterObject(UGFxObject* journeyElement, INT monsterId, const FString& monsterName, INT monsterType, INT mapId, const FString& mapRegion, FVector2D point);
	void _AddBossObject(UGFxObject* journeyElement, INT bossId, const FString& bossName, INT bossType, INT mapId, const FString& mapRegion, FVector2D point);
	void _AddAwardString(INT itemId, INT itemCount, FString& awardsString);
	void _AddAchievementObject(UGFxObject* journeyElement, INT id, INT& index);

#endif