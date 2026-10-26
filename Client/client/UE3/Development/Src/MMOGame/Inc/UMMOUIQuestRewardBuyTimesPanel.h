#ifndef _UMMOUIQUESTREWARDBUYTIMESPANEL_H_
#define _UMMOUIQUESTREWARDBUYTIMESPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateRewardQuestBuyTimesConsume(INT times);

#endif