#ifndef _UMMOUIQUESTREWARDPANEL_H_
#define _UMMOUIQUESTREWARDPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateRewardQuestList();
void UpdateRewardQuestDetail();
void UpdateRewardQuestAvailableLimit();
void UpdateRewardQuestRefreshTime();

void RefreshNowConfirm(UBOOL isAutoRefresh);
void CompleteAllConfirm();
void UpgradeLimitConfirm();
void AbandonLowConfirm(INT questId);
void AbandonHighConfirm(INT questId);

void ShowCompleteQuest(UBOOL visible);

#endif