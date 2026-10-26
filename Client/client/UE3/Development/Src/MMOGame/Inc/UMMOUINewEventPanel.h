#ifndef _UMMOUINEWEVENTPANEL_H_
#define _UMMOUINEWEVENTPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowNewEvent(INT type, const FString& text);

#endif