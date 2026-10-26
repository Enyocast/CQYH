#ifndef _UMMOUIGUILDWARVIEWPANEL_H_
#define _UMMOUIGUILDWARVIEWPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildViewInfo();
void UpdateGuildBuildingList();
void ShowGuildWarInfoPanel();

#endif