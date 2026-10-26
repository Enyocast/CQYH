
virtual void Init();
void InitMakeUpPanelMc();
void InitUpgradePanelMc();
void SetTitleName();

virtual void PreOnShow(UBOOL show);

void OnNativeGameEvent( struct MMOGameEvent* evt );

void UpdatePanel();

void ResetUI();
void ResetPanel( INT tabIdx );
//
void GrayAllInBagNoNeed( UBOOL isToGray );

//ºÏ³É
void ResetMakeUp();

UBOOL SetMakeUpItemComsuption( int containerID, int slotID );
UBOOL UnsetMakeUpItemComsuption();

UBOOL OnRightMouseClickMakeUp( class UGFxObject* mc, BYTE SlotType, BYTE ContainerID, INT SlotID, UBOOL bDefault );
UBOOL OnDragDropMakeUp( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC, BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID, BYTE destSlotType, BYTE destContainerID, INT destSlotID );
void BagSlotChangeOnMakeUp( INT bagId, INT slotId, INT itemID );

void UpdateMakeUpDetails();
void UpdateMakeUpFee();

UBOOL IsNeedToGrayForMakeUp( UItem *pItemInBag, const struct FClientItemInfo *pItemInfo );
void GrayAllInBagNoNeedForMakeUp( UBOOL isToGray );

void HandleMakeUpResult( INT result );

//Éý¼¶
void ResetUpgrade();

UBOOL SetToUpgradeItem( int containerID, int slotID );
UBOOL UnsetToUpgradeItem();

UBOOL OnRightMouseClickUpgrade( class UGFxObject* mc, BYTE SlotType, BYTE ContainerID, INT SlotID, UBOOL bDefault );
UBOOL OnDragDropUpgrade( class UGFxObject* srcSlotMC,class UGFxObject* destSlotMC, BYTE srcSlotType, BYTE srcContainerID, INT srcSlotID, BYTE destSlotType, BYTE destContainerID, INT destSlotID );
void BagSlotChangeOnUpgrade( INT bagId, INT slotId, INT itemID );

void UpdateUpgradeDetails();
void UpdateUpgradeFee();

UBOOL IsNeedToGrayForUpgrade( UItem *pItemInBag, const struct FClientItemInfo *pItemInfo );
void GrayAllInBagNoNeedForUpgrade( UBOOL isToGray );

void HandleUpgradeResult( INT result );