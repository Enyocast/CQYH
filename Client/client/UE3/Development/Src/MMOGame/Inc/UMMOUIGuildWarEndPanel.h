#ifndef _UMMOUIGUILDWARPANEL_H_
#define _UMMOUIGUILDWARPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildWarEndList();
void UpdateGuildWarEndTime();

#endif