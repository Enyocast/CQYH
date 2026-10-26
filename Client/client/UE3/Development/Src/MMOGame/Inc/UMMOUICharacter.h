
virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void UnInit();

void UpdateAttributePanel();
void UpdateBattlePoint();
void UpdateBattlePoint(INT pow);
void LockItem( BYTE ContainerID, INT SlotID, INT isToLockIn );

BOOL CheckWeight(UItem* item, UItem* itemDest);

void UpdateArmor();