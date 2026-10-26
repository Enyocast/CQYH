
virtual void Init();
void InitWeaponSkillSettingPanelMc();
INT GetCurOperationSkillSlot();
void AutoCheckAndSetWeaponSkillLeveUpItem( UMMOAbility *weaponSkill );
virtual void PreOnShow(UBOOL show);
void OnNativeGameEvent( struct MMOGameEvent* evt );

UBOOL CheckReplaceWeaponSkill( INT skillSlotIdx, INT containerID, INT slotID );
