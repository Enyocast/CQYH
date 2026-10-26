
virtual void Init();
virtual void UnInit();
virtual void PostInit();

void PreLoadPanels();

virtual INT GetPanelPriority(FName viewName);
virtual FString GetPanelPriorityAndSWF(FName viewName, INT& inPriority);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);