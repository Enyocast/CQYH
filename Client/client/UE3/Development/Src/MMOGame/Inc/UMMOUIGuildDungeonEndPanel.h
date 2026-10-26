#ifndef _UMMOUIGUILDDUNGEONENDPANEL_H_
#define _UMMOUIGUILDDUNGEONENDPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildDungeonAwardList();
void SetGuildDungeonBoss(UINT32 bossId);

#endif