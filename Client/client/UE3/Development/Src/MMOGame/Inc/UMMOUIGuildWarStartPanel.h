#ifndef _UMMOUIGUILDWARSTARTPANEL_H_
#define _UMMOUIGUILDWARSTARTPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildWarStartPanel(INT targetGuildId);

#endif