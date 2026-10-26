

virtual void PostOnShow(UBOOL v);
//virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void Init();
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowChatHint(INT roldId = 0);
void HideChatHint();

void UpdateHeadImg(UINT32 roleId);