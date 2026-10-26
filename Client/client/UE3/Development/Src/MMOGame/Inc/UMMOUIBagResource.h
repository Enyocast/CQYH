virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void NativeOnShow(UBOOL v);

virtual void BagSlotChangeEx(INT ContainerID, INT SlotID);

virtual UBOOL OnEsc();

UBOOL GetItemFilterFrame( UItem* item , INT label , INT filterTab );
void GrayItem( BYTE ContainerID, INT SlotID, struct FClientItemInfo *pItemInfo );
void BagSlotChangeEx(BYTE ContainerID,INT SlotID);

void HideMsg();

void ClearUI();

void InitSlot();

void BagPageRefresh();

void BagTab(INT tabId);

void GrayAllInBagNotInNpcShop(BOOL usToGray);
BOOL GrayItemInBagNotInNpcShop(FClientItemInfo *pItemInfo,UItem *pItemInBag);

void InitBagResourcePageTab();
void UpdateBagResourcePageTab();
void UpdateBageBagResourcePageTabEnable(BOOL v1,BOOL v2, BOOL v3);

void HideBage_Msg();

UBOOL UseContainerItem( INT conIdx, INT slotIdx );

void DeleteItem( INT ConId , INT SlotId , INT TemplateId );

void LockItem( BYTE ContainerID, INT SlotID, INT isToLockIn );

void ClearItemSlot(BYTE ContainerID,INT SlotID);

void HintItem( BYTE ContainerID, INT RealSlotID, struct FClientItemInfo *pItemInfo );

void SetSellBtnEnable(BOOL v);

INT GetCurrentPageSlotId(INT realSlotId);

void HideAllHint();

void NotifyHideBagResource();

BOOL MoveItemToBag(BYTE SlotType,BYTE ContainerID,INT SlotID);

void InitShowPanelList();

void ShowPanelPos();
void UpdatePos(UMMOUIBase* leftPanel);
void UpdatePosByBag();