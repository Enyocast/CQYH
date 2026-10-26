
virtual void Init();
virtual void PostOnShow(UBOOL v);

void OnNativeGameEvent( struct MMOGameEvent* evt );

void UpdateFee( const struct EquipComposeTemplate *composeTemplate );
void UpdateConsume( const struct EquipComposeTemplate *composeTemplate );
void NotifyComposeResult( INT result );
void NotifyComposeSuccessAnimPlayedOver();