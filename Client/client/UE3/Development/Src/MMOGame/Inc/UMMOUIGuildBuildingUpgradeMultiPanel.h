#ifndef _UMMOUIGUILDBUILDINGUPGRADEMULTIPANEL_H_
#define _UMMOUIGUILDBUILDINGUPGRADEMULTIPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildBuildingUpgradePanel(UINT32 buildingType);
void UpdateGuildBuildingList(UINT32 buildingType);
void UpdateGuildBuildingData(UINT64 buildingId);

void DeleteConfirm(UINT64 buildingId);

#endif