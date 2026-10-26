
virtual void Init();
void InitMc();
virtual void PostOnShow(UBOOL v);
void OnNativeGameEvent( struct MMOGameEvent* evt );

void ResetUI();
void CloseAllPopUpPanel();

//
void ResetCurOperation();
//检查是否为可以升级
UBOOL CheckCanGo( FString &errStrName, FString &errorHint );
void ConfirmLevelUpEquip();
void NotifyLevelUpResult( INT succeedType, INT duribilityEnum );
void InitSuccessConfirmBox( INT propAdd, INT duribilityEnum );
void InitFaildCrashConfirmBox();
void InitFaildUnchangedConfirmBox();

void ShowLevelUpResultConfirmBox( UBOOL isToShow );

//放入装备
UBOOL SetLevelUpEquip( INT bagSlotCon, INT bagSlotID );
UBOOL SetLevelUpConsume( INT idx, INT bagSlotCon, INT bagSlotID );
UBOOL SetLevelUpHelpItem( INT idx, INT bagSlotCon, INT bagSlotID );

void UnSetLevelUpEquip();
void UnSetLevelUpConsume( INT idx );
void UnSetLevelUpHelpItem( INT idx );

void ResetAllLevelUpConsumes();
void ResetAllLevelUpHelpItems();

UBOOL AutoSetLevelUpConsumes( INT bagSlotCon, INT bagSlotID );
UBOOL AutoSetLevelUpHelpItems( INT bagSlotCon, INT bagSlotID );

UBOOL IsItemCanLevelUp( const UItem *pItem );
UBOOL IsItemConsumeForLevelUp( const UItem *pItem );
UBOOL IsItemCanHelpLevelUp( const UItem *pItem );

UBOOL IsCurLevelUpEquip( INT bagSlotCon, INT bagSlotID );
INT IsCurLevelUpConsumeItem( INT bagSlotCon, INT bagSlotID );
INT IsCurLevelUpHelpItem( INT bagSlotCon, INT bagSlotID );

void GrayAllBagItemsNoNeed( UBOOL isToGray );
UBOOL IsNeedToGray( UItem *pItemInBag, const FClientItemInfo *pItemInfo );