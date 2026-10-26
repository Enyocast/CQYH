#ifndef _UMMOUIQUESTITEMCOLLECTIONPANEL_H_
#define _UMMOUIQUESTITEMCOLLECTIONPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

UBOOL SetCollectionItem(INT containerId, INT slotId);
UBOOL ClearCollectionItem();
void ShowItemCollectionPanel(INT questId);

#endif