#ifndef _UMMOUIGUILDWELFAREPANEL_H_
#define _UMMOUIGUILDWELFAREPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildWelfarePurchaseList();
void UpdateGuildWelfarePurchasePage();
void PageUp();
void PageDown();

#endif