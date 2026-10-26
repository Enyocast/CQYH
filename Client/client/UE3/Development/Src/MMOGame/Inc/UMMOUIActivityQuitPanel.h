#ifndef _UMMOUIACTIVITYQUITPANEL_H_
#define _UMMOUIACTIVITYQUITPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	void  UpdateQuitDataPanel();
	void  UpdateQuitActivityList();
	void  UpdateQuitRewardItem();
	void  UpdateQuitRememberToday();
	void  UpdateQuitActivityValue();
	void  SortActivity(INT nType);

#endif