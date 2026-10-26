
//virtual void Init();
void InitByParent( class UMMOUIBase *parentPanel );
void InitMc();
virtual void UnInit();

virtual void PostOnShow(UBOOL v);

void InitToDefaultShow();

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateDetail( INT enhanceClassID, INT playerLv, INT curSelSlotID);

void UnSetEnhanceConsumeItem();
UBOOL SetEnhanceConsumeItem( INT containerID, INT slotID );

void GrayAllInBagNoNeedForEnhance( UBOOL isToGray );
UBOOL IsNeedToGrayForEquipSlotEnhance( UItem *pItemInBag, INT slotID );

void UpdateCurSuccessRate();

void CallAsToSelectEnhanceSlot( INT slotID, UBOOL isToSelected );

void ShowEquipSlotTips( INT enhanceClassID, INT enhanceLv, INT slotID );
void ShowActiveTips();
FString FormatEnhanceGuideTips();