virtual void Init();

virtual void PreOnShow(UBOOL show);
virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void NativeOnShow(UBOOL v);
virtual void PostOnShow(UBOOL v);
void ResetMsg();

bool CheckGoldStoreOrder(INT money,INT count);
void HideGoldStore_Msg();

void UpdateMyLogs();

void ShowDefaultPrice();
void FristShowPrice();