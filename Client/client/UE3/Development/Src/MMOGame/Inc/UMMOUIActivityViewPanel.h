#ifndef _UMMOUIACTIVITYPANEL_H_
#define _UMMOUIACTIVITYPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void UpdateActivityState(INT nActivityID);
	void SortActivity(INT nType);
	void FilterActivityType(INT nType);
	void FilterActivityRewardType(INT nType);
	
	void SetActivityDetailInfo(INT nActivityID);
	void SetFBDetailInfo(INT nFBID);
	void SetActivityTeamList(INT nActivityID, INT nPage, UBOOL bForce = FALSE);

	void RefreshActivityList();
	void UpdateRewardBarInfo();
	void UpdateHuoYueValue();
	void RefreshActivityTeamList();
	void ShowActivityTeamTips(UBOOL bShow);
	void UpdateActivityTeamTips(INT nTeamId);
	void AutoSetTeamTipsPosition();

private:
	void UpdateRewardItemInfo(INT nActivityID);

#endif