#ifndef _UMMOUIGUILDTERRITORYPANEL_H_
#define _UMMOUIGUILDTERRITORYPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildTerritoryPanel();

void UpdateGuildTerritoryInfo();
void UpdateGuildTerritoryUpgradeList();

void UpdateGuildBuildingList();

void PageUp();
void PageDown();
void UpdateGuildWelfarePage();
void UpdateGuildWelfareList();

void CancelUpgradeBuildingConfirm(UINT64 id);
void CancelUpgradeWelfareConfirm(INT welfareId);

#endif