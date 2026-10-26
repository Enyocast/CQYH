virtual void Init();

virtual void UnInit();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void PostOnShow(UBOOL v);

void UpdateMasterInfo(BOOL update = TRUE);

void HideUI();
