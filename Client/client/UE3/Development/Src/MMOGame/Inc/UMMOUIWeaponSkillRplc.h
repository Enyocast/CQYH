
virtual void Init();
void InitPanelMc();
virtual void PreOnShow(UBOOL show);

void ResetCachedRplcWeaponRune();

void OnNativeGameEvent( struct MMOGameEvent* evt );
void PrePutWeapon();

void GrayAllBagNotEquip( UBOOL isToGray );
UBOOL IsNeedToGray( UItem *pItemInBag, const FClientItemInfo *pItemInfo );

FString CheckAllConditionsToTry();
FString CheckAllConditionsToReplace();

//
void NotifyReplaceWeaponSkillResult( INT result );

void ReplaceWeaponSkill( INT checkConfirmState );
UBOOL PopupReplaceConfirmInfoBox();
UBOOL PopupReplaceConfirmSideEfctBox();
void PopupConfirmBox( const FString& MessageTxt, INT messageBoxCallState );

//
UBOOL PopupTryReplaceConfirmRareSkillBox();
//
void TryReplaceWeaponSkill( INT checkConfirmState );
void NotifyTryReplaceWeaponSkillResult( INT result );

//
UBOOL SetCurWeapon( INT containerID, INT slotID );
void UnSetCurWeapon();

void UpdateAllWeaponSkills();
void UpdateCurWeaponSkills();
void UpdateRplcCacheWeaponSkills();

void UpdateFee();
void UpdateGuildNeeds();
//
void UpdateConsumeItem();
UBOOL IsWeaponSkillConsumeItem( INT itemID );
void SetCurConsumeID( INT item );
void UnSetCurConsumeID();
INT GetCurConsumeID();

//
void UpdateReplaceWeaponSkillBtn();
void UpdateTryReplaceWeaponSkillBtn();

void ChangeToGuildMode( UBOOL isToSet );
//
void ResetAllPopupBox();