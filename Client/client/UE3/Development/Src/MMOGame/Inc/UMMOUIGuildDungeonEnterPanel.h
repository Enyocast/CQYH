#ifndef _UMMOUIGUILDDUNGEONENTERPANEL_H_
#define _UMMOUIGUILDDUNGEONENTERPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildDungeonEnterPanel(UINT32 dungeonId);
void UpdateGuildDungeonData(UINT32 dungeonId);

#endif