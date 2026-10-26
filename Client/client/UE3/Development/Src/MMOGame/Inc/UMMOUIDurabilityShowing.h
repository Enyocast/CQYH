
virtual void Init();
void InitMc();

virtual void UnInit();

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void PostOnShow(UBOOL v);
void DescideShow();

EEquipDurComp CvtEquipSlot2DurabilityComponent( ENORMAL_EQUIP_SLOT equipSlotID );
void UpdateAllEquipDurState();
void UpdateEquipDurState( ENORMAL_EQUIP_SLOT componentID );
void SetEquipDurabilityStateFromTwo( EEquipDurComp durComponentID );
void SetEquipDurabilityState( ENORMAL_EQUIP_SLOT componentID, struct ItemInfo *pEquipItemInfo, UItem *pItem );

void UpdatePosition();