
//virtual void Init();

// virtual void PostOnShow(UBOOL v);
//virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void Show(UBOOL V, INT displayPriority = -1);
virtual void SetVisible(UBOOL bValue = TRUE);
UGFxObject* AddNewMessageBox( INT type , FString boxName , UBOOL twoButton = TRUE );
UGFxObject* CreateAutoAdjustFunction();