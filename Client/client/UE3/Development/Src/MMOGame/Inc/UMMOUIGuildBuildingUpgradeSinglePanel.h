#ifndef _UMMOUIGUILDBUILDINGUPGRADESINGLEPANEL_H_
#define _UMMOUIGUILDBUILDINGUPGRADESINGLEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildBuildingUpgradePanel(UINT32 buildingType);
void ShowGuildBuildingUpgradePanel(UINT32 npcId, UINT32 npcTempId);
void UpdateGuildBuildingData(UINT64 buildingId, UINT32 npcId);
void DeleteConfirm(UINT64 buildingId, UINT32 npcId);

#endif