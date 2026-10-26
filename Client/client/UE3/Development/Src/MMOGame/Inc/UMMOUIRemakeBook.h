
virtual void Init();
//void InitPanelMc();
void SetTitleName();

virtual void PreOnShow(UBOOL show);

void OnNativeGameEvent( struct MMOGameEvent* evt );
void OnBagSlotChanged( INT bagId, INT slotId, INT itemID );

void UpdateConsumption();

//void ResetUI();
void UpdateRemakeFee();
void HandleRemakeResult( INT isSuccess, INT remakedItemID );
