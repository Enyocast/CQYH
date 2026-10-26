#ifndef _UMMOUIWEATHERCHANGEPANEL_H_
#define _UMMOUIWEATHERCHANGEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void SetWeatherChangeTip(const FString& content);

#endif