
virtual void Init();
virtual void PostOnShow(UBOOL v);
void DeleteRoleForever(INT nRoleID);
void UnddeleteRole(INT nRoleID);

virtual void OnNativeGameEvent(struct MMOGameEvent* evt);