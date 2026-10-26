virtual void Init();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void BattleTeamOneToOne();
void BattleTeamFiveToFive();

void UpdateTeamInfo();
void UpdateMemberList();

void ClickOwnPanel( INT tab );
void ClickAddMember();