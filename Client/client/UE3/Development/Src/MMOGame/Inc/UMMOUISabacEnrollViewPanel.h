#ifndef _UMMOUISABACENROLLVIEWPANEL_H_
#define _UMMOUISABACENROLLVIEWPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void PageUp();
void PageDown();
void UpdateSabacEnrollList();

#endif