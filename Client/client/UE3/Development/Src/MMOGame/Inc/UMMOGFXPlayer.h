
virtual void Init();
virtual void PostInit();
virtual void UnInit();
void DeleteEventAdapter();
UBOOL IsAllHide();
void ShowAllUI(UBOOL inShow);
// void RegisterUI(class UMMOUIBase* ui, FName friendlyName);
virtual void OnClose();

virtual UBOOL OnDragDropOnPanel(class UGFxObject* SrcSlotMC,class UGFxObject* DestSlotMC,BYTE SrcSlotType,BYTE SrcContainerID,INT SrcSlotID,BYTE DestSlotType,BYTE DestContainerID,INT DestSlotID);

virtual INT GetPanelPriority(FName viewName) { return 2; } // 默认显示在中间
virtual FString GetPanelPriorityAndSWF(FName viewName, INT& inPriority) {inPriority=2; return FString("");};
