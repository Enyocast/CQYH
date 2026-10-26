
virtual void Init();
void InitMc();
virtual void UnInit();

virtual void PreOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

UGFxObject *GetTradeSlot( INT containID, INT slotID );
UGFxObject *GetTradeSlotName( INT containID, INT slotID );
void SetIsTgLocked( UBOOL isToLock );