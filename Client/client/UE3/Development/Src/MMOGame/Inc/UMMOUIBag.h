
virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void BagFilter();

//新cd导致的整体检索刷新，只针对该cd
void UpdateAllBagSlotCDByItemUse( INT type , INT cdID );
void SetBagSlotCD( INT containerId , INT slotId );
UBOOL GetItemFilterFrame( UItem* item , INT label , INT filterTab );
void GrayItem( BYTE ContainerID, INT SlotID, struct FClientItemInfo *pItemInfo );
void HintItem( BYTE ContainerID, INT SlotID, struct FClientItemInfo *pItemInfo );
void SetChainPay( );
void SetChainPayText();

void LostFocus();

void OpenPack(INT itemId);
UBOOL UseContainerItem( INT conIdx, INT slotIdx );
//
UBOOL OnBagItemRightClickToShortcut( UItem* pItemInBag, FClientItemInfo *pItemInBagInfo, class UGFxObject* mc, BYTE slotType, BYTE containerID, INT slotID, UBOOL bDefault );

void ClearItemSlot(BYTE ContainerID,INT SlotID);

void SetBagWeight();

BOOL CanUseDoubleClickItem();

BOOL CheckWeight(UItem* item, UItem* itemDest);
void BagPageRefresh();

UBOOL OnRightMouseClickInExpContainer( INT slotIdx );
void ExpContainerChanged(INT containerID,INT slotID);
void NotifyExpContainerFillIn( INT value );
void AutoUnloadCurExpContainer();
//UBOOL UnloadExpContainer( INT toContainerID, INT toSlotID );
//UBOOL LoadExpContainer( INT containerID, INT slotID );
void GrayAllInBagNotInNpcShop(BOOL usToGray);
BOOL GrayItemInBagNotInNpcShop(FClientItemInfo *pItemInfo,UItem *pItemInBag);

void cleanAllCD();

void ChangeResBagBtn();

BOOL MoveItemToBagResource(BYTE SlotType,BYTE ContainerID,INT SlotID);