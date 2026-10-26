#ifndef _UMMOUIGUILDWARRECORDPANEL_H_
#define _UMMOUIGUILDWARRECORDPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildWarRecordList();
void NoMoreGuildWarRecord();

#endif