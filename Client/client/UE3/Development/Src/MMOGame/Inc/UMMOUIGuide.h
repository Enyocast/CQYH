#ifndef _UMMOUIGUIDE_H_
#define _UMMOUIGUIDE_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void SetGuideEnable(UBOOL isEnable);
void UpdateGuideInfo();

#endif