#ifndef _UMMOUINEWSTALLUPGRADEPANEL_H_
#define _UMMOUINEWSTALLUPGRADEPANEL_H_

virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateHintText();
void UpdateTimeList();
void UpdateCost(int timeType);

#endif