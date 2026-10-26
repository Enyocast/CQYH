
virtual void Init();
virtual void UnInit();
virtual void PostOnShow(UBOOL v);

//void UpdateFriendsList();
//void UpdateRecentsList();
//void UpdateGuildsList();

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateList();