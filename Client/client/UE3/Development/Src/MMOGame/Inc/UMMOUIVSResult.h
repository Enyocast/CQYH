
virtual void Init();
//void InitPanelMc();
void SetTitleName();

virtual void PreOnShow(UBOOL show);

void OnNativeGameEvent( struct MMOGameEvent* evt );

void ResetWaitQueueHintMsgBtns();
void ResetAllPopupBox();
void PopupConfirmQuitWaitQueue();

void UpdateTimeOut( INT isToShowType );
void UpdateResultInfo();