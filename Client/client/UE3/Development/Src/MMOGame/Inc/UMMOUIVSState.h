
virtual void Init();
//void InitPanelMc();
void SetTitleName();

virtual void PreOnShow(UBOOL show);

void UpdateVSPkSideStaticInfo();
void UpdateVSPkStateInfo();

void OnNativeGameEvent( struct MMOGameEvent* evt );