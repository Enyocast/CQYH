virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

UBOOL GetItemFilterFrame( UItem* item , INT label , INT filterTab );
void GrayItem( BYTE ContainerID, INT SlotID, struct FClientItemInfo *pItemInfo );
void BagSlotChangeEx(BYTE ContainerID,INT SlotID);

void HideMsg();

INT GetEmptySlot(BYTE desContainerID,BYTE ItemDuration,INT m_nTemplateID,INT m_nCurDur);