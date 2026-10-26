virtual void Init();
void InitActiveSkillMc();
virtual void PreOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

public:
	//UBOOL IsShowFitWeaponSkillHint( INT skillSetIdx );
	void ConverterConfirmShow();
	void OnClickOneKeyMerge();
	void OnClickLevelState(INT nLevelIndex,INT nPanelIndex);
	void OnClickActivateBlood(INT nTypeIndex);