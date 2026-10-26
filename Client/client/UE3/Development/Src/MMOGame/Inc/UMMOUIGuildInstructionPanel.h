#ifndef _UMMOUIGUILDINSTRUCTIONPANEL_H_
#define _UMMOUIGUILDINSTRUCTIONPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void SetInstruction(const FString& key);

#endif