
//virtual void PostOnShow(UBOOL v);
//virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
//
virtual void Init();
//virtual void UnInit();
//
//virtual void OnFocusLost();

void ActiveCurChatMessageFilterChannel( EChat_Channel channel );
void TurnFilterChannel( INT idx );
void RefreshChatChannel();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

FString GetTrumpet();
void ProcessTrumpet(FLOAT tickTime);

void ResetTrumpet();

FString CreateTrumpet(FString msg);

void processTrumpetCDTimes(FLOAT tickTime);

void CreateDropDownList(class UGFxObject* ChatDropDown);

void SendPrivateChatMessage(FString inContent);

EChat_Channel GetChannelType(FString context);

FString ParseSendMessage(EChat_Channel type , FString content);

void AppendInpt(BYTE type, BYTE cid, INT sid, UBOOL def);

BOOL GetTrumpetByGm();


virtual void PostOnShow(UBOOL v);

void UpdateChatDropDownList();
void ShowTrumpet();

void checkInput();

void SetPopFaceTips(UGFxObject* object);

void ShowChatErrorMsg(FString msg);