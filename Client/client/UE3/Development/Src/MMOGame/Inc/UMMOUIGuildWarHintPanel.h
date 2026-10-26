#ifndef _UMMOUIGUILDWARHINTPANEL_H_
#define _UMMOUIGUILDWARHINTPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildWarHintInfo(const FString& attackGuildName, const FString& defendGuildName, const FString& timeTitle, INT32 lastTime);
void UpdateGuildWarHintTime(UINT8 state);

#endif