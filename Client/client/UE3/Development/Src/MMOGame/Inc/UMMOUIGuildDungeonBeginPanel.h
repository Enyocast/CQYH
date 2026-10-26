#ifndef _UMMOUIGUILDDUNGEONBEGINPANEL_H_
#define _UMMOUIGUILDDUNGEONBEGINPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildDungeonList();
void UpdateGuildMemberList();

#endif