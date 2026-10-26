
virtual void Init();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);

void UpdateMaxPage(  INT curPage, INT maxPage );

void UpdateShopData();

virtual void UnitWidget(); // TODO: remove this
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual UBOOL OnDragDropOnPanel(class UGFxObject* SrcSlotMC,class UGFxObject* DestSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,BYTE DestSlotType,BYTE DestContainerID,INT DestSlotID);

void UpdateShopType();

void SetSlotEnable();

void UpdateBlackMarketItemCount(INT id, INT count);

void UpdateItemSlot( UGFxObject* itemSlotMc, UBOOL show, const FString& itemName, BYTE currencyType0, INT sellPrice0 , BYTE currencyType1, INT sellPrice1 ,INT itemCount,INT limitType = 0,FString objName = "");

void ClearAllItemSlot( INT itemSize);

void UpdateCoolDown();

void NotifyGrayItemInBag(BOOL v);

BOOL ShowMessageBox(INT ShopItemId,BYTE SlotType,INT ItemCount=1,INT ItemTempId=0);