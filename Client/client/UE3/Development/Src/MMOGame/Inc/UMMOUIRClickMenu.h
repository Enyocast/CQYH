virtual void Init();

virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);
virtual void AddLine();

UBOOL ChangeMenu(INT RoleId, const FString& RoleName, INT index, BYTE type);

void  _MenuFormat(INT nType);
UBOOL _MenuFormatByTargetInfo(INT roleId, const FString& RoleName);
UBOOL _MenuFormatByMyTeam(INT index);
UBOOL _MenuFormatByTeamMate(INT index);
UBOOL _MenuFormatByNearPlayer(INT index);
UBOOL _MenuFormatByFriendGroup(INT index, const FString& groupName);
UBOOL _MenuFormatByAttention(INT index, const FString& roleName);
UBOOL _MenuFormatByFriend(INT roleId, const FString& roleName);
UBOOL _MenuFormatByBattleMember(INT index);
UBOOL _MenuFormatByBlack(INT Index);
UBOOL _MenuFormatByGuildMember(INT roleId);
UBOOL _MenuFormatByChatPlayer(INT roleId, const FString& playerName);
UBOOL _MenuFormatByRankListPlayer(INT roleId, const FString& roleName);
UBOOL _MenuFormatByRankListGuild(INT guildId, const FString& guildName);
UBOOL _MenuFormatByMasterPlayer(INT roleId, const FString& playerName);
UBOOL _MenuFormatByDungeon(const FString& title);
UBOOL _MenuFormatByBattleEnter(const FString& title);
UBOOL _MenuFormatByMapChangeLine(const FString& title);
UBOOL _MenuFormatByGuildAlliance(INT guildId, const FString& guildName);
UBOOL _MenuFormatByAuctionPlayer(INT roleId, const FString& playerName);
UBOOL _MenuFormatByGuildEnemy(INT guildId, const FString& guildName);

void _GuildMenuFormat();

//
bool AddMenuItem_Guild(FScriptDelegate &func);

void ModifyPos( INT x , INT y , INT height , INT width );
virtual void OnFocusLost();


BOOL CheckSkipCapture();