#ifndef _UMMOUIGUILDWELFAREUPGRADEPANEL_H_
#define _UMMOUIGUILDWELFAREUPGRADEPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildWelfareUpgradePanel(UINT32 welfareId);
void UpdateGuildWelfareData(UINT32 welfareId);

#endif