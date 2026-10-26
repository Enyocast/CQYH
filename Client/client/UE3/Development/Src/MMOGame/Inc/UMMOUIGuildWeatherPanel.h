#ifndef _UMMOUIGUILDWEATHERPANEL_H_
#define _UMMOUIGUILDWEATHERPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildWeatherInfo();

#endif