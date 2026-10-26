
virtual void Init();
//void InitPanelMc();
void SetTitleName();

virtual void PreOnShow(UBOOL show);

void OnNativeGameEvent( struct MMOGameEvent* evt );
void OnBagSlotChanged( INT bagId, INT slotId, INT itemID );

void UpdateConsumption();
void UpdateRemakeBookConsumption();
void UpdateRemakeMedicineConsumption();

void UpdateRemakeFee();
//void ResetUI();

void HandleRemakeResult( INT remakeType, INT isSuccess, INT remakedItemID );
void HandleRemakeMedicineResult( INT isSuccess, INT remakedItemID );
void HandleRemakeBookResult( INT isSuccess, INT remakedItemID );
