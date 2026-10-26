
virtual void Init();
void InitWeaponSkillPanelMc();
virtual void PreOnShow(UBOOL show);

void OnNativeGameEvent( struct MMOGameEvent* evt );
void PrePutWeapon();

void GrayAllBagNotEquip( UBOOL isToGray );
UBOOL IsNeedToGray( UItem *pItemInBag, const FClientItemInfo *pItemInfo );
FString CheckAllConditionsToGo();

void PopupConfirmBox(const FString& MessageTxt);
void TryGetWeaponSkill( UBOOL isNeedCheckConfirm );
void NotifyTryWeaponSkillResult( INT result );

//
UBOOL SetCurWeapon( INT containerID, INT slotID );
void UnSetCurWeapon();

void UpdateCurWeaponSkills();
//void SetWeaponSkillSlotBySkill( INT idx, UBOOL isSkillActive, class UMMOAbility *pWeaponSkill );
void UpdateFee();
void UpdateGuildNeeds();
//
void UpdateConsumeItem();
UBOOL IsWeaponSkillConsumeItem( INT itemID );
void SetCurConsumeID( INT item );
void UnSetCurConsumeID();
INT GetCurConsumeID();
//UBOOL AutoPutTryGetWeaponSkillItemConsume( INT bagSlotCon, INT bagSlotID );
//UBOOL SetWeaponSkillConsumeItem( INT idx, INT contID, INT slotID );
//UBOOL CheckConsumeItemForWeaponSkill( INT contID, INT slotID );
//
//void ResetAllPuttedWeaponSkillConsumeItem();
//void UnSetWeaponSkillConsumeItem( INT idx );

//
void UpdateTryGetWeaponSkillBtn();

void ChangeToSealMode( UBOOL isToSet );
void ChangeToNoOpMode( UBOOL isToSet );
void ChangeToGuildMode( UBOOL isToSet );
//
void ResetAllPopupBox();

void OnClickAutoChangeSkillChkBtn();