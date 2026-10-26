#ifndef _UMMOUIACHIEVEMENTPANEL_H_
#define _UMMOUIACHIEVEMENTPANEL_H_

virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateAchievementCagetory(int type);
void UpdateAchievementSummary(int type);
void UpdateAchievementData(int baseClass, int subClass);
void UpdateAchievementList(int baseClass, int subClass);

void _UpdateCommonAchievementInfo(UGFxObject* dataProvider, int& index, UINT32 id);
void _UpdateKillNpcAchievementInfo(UGFxObject* dataProvider, int& index, UINT32 id);
void _UpdateGuildAchievementInfo(UGFxObject* dataProvider, int& index, UINT32 id);

void ShowAchievementListByClass(int baseClass, int subClass);
void ShowAchievementListById(int id);

void SetRewardAchievementId(int id);

#endif