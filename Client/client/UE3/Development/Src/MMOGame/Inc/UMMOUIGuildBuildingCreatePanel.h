#ifndef _UMMOUIGUILDBUILDINGCREATEPANEL_H_
#define _UMMOUIGUILDBUILDINGCREATEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildBuildingCreatePanel(UINT32 npcId, UINT32 npcTempId);
void UpdateGuildBuildingList(UINT32 npcTempId);
void UpdateGuildBuildingData(UINT32 buildingType);

#endif