virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
void OnUpdateCDTime();
void UnInit();
void Init();

public:
	void UpdatePanelInfo();

	void UpdateMasterInfoList();
	void UpdateMasterApplyList();
	void UpdateMasterPosterList();
	void UpdateStudentApplyList();
	void UpdateStudentPosterList();

	void CloseAllPopUpPanel();
	
	BYTE GetCurPanelType();
	void SetCurPanelType(BYTE type);

	void UpdateClickItem(INT id);

	void UpdateMasterApplyListSelected(INT id);
	void UpdateStudentApplyListSelected(INT id);

	void CheckCDTime();

	void ShowTwitterCheckBox();