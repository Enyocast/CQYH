
public:
	void OnClickOneKeyMerge();
	void OnClickBtnPractiseGas(INT nBtnIndex);
	void UpdateHeavenGasMainPanel();
	void InitContainer(UMMOGFXPlayer*GFXPlayer);
	void UpdateSlotState(UMMOGFXPlayer*GFXPlayer,INT nContainerID,INT nSlotID);
	void UpdateSlotItem(UMMOGFXPlayer*GFXPlayer,INT nContainerID,INT nSlotID);
	void UpdateTargetState(UMMOGFXPlayer*GFXPlayer);
	void UpdateEquipSlotStateShow(UMMOGFXPlayer*GFXPlayer,INT nContainerID,INT nSlotID);
	void UpdateGasEquipPower();
	void OnStartDragGas(INT nContainerID,INT nSlotID,BOOL bSelected);
private:
	void UpdateContainerSlot(UMMOGFXPlayer*GFXPlayer,UGFxObject* mc,ESlotPanelType panelType,INT nContainerID,INT nSlotID);
	void ConfirmMergeHint();
	void ConfirmMergePurple();