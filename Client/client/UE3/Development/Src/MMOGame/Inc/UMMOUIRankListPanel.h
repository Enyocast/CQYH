enum Ranking
{
	Ranking_Deafult,
	Ranking_Down,
	Ranking_Up,
};
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void LoadPersonMenuData();
void LoadGuildMenuData();
void LoadTournamentMenuData();
void LoadPowerMenuData();
void LoadActivityMenuData();

void UpdateRankList();

void UpdatePersonLevelRank();
void UpdatePersonPowerRank();
void UpdatePersonRichRank();
void UpdatePersonAchievementRank();
void UpdatePersonMasterRank();
void UpdatePersonExpRank();

void UpdateGuildLevelRank();
void UpdateGuildFoundRank();
void UpdateGuildResourceRank();
void updateGuildPowerRank();
void UpdateGuildWarRank();

void UpdateActivityRank_JCYT(); //就层妖塔
void UpdateActivetyRank_BQBZ(); //比奇霸主
void UpdateActivetyRank_Arena1v1(); //1v1擂台

void UpdateTournamentLadderRank();
void UpdateTournamentCorpsRank();
void UpdateTournamentFB0Rank();
void UpdateTournamentKillRank();
void UpdateTournamentPKRank();

virtual void UnInit();
int GetCurrentRangeIndex();
void RankListClear();
void SetSelectRadioButton(INT index);
void SetSelectCategoryButton(INT index);

void UpdateMaxPage(  INT curPage, INT maxPage );

void UpdateRangeBtn(int currentPage);

FString GetSelfRankStr(bool isGuild);

void UpdateTimeText();

INT64 GetExp(INT level,INT64 exp);

INT GetRanking(UINT8 lastRank, INT currentRank);

void SetCurrentActivity();

void CheckShowRank(float DeltaTime);

INT _currentActivityType;

