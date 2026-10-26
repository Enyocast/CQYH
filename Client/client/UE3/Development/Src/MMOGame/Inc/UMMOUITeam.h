
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

virtual void Init();
virtual void UnInit();

virtual void OnFocusLost();

void UpdateTeamTargetUI();

void _UpdateMyTeamMember();

void SetNearPlayerPage();

void SetCurNearPlayerPage();