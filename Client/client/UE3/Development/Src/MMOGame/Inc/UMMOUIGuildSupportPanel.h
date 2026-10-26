#ifndef _UMMOUIGUILDSUPPORTPANEL_H_
#define _UMMOUIGUILDSUPPORTPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildSupportPanel();
void UpdateGuildSupportList();

#endif