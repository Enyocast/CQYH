#ifndef _UMMOUIGUILDMAINPANEL_H_
#define _UMMOUIGUILDMAINPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void UpdateGuildBaseInfo();
void ChangeGuildNotice(const FString& notice);
void UpdateGuildNotice(const FString& notice);
void ViewMoreEvents();
void UpdateGuildEvents(const FString& events);
void UpdateGuildMoneyEvents(const FString& events);

void UpdateGuildFullMemberList();
void UpdateGuildPendingMemberList();
void AgreeToJoin(INT id);
void RefuseToJoin(INT id);
void InviteMember(const FString& roleName);
void ExpelMember(INT id);
void ChangePost(INT roleId, INT post);
void FullMemberRightClick(INT posX, INT posY, INT roleId);
void AllianceRightClick(INT posX, INT posY, INT guildId);
void EnemyRightClick(INT posX, INT posY, INT guildId);
void RequestGuildPendingMemberList();
void ShowOnlineMember(UBOOL isShow);
void SortMember(INT type, UBOOL isUp);

void LeaderDemise(const FString& roleName);
void DisbandGuild(const FString& text);
void UpdateGuildRights(INT post);
void ModifyGuildStorageRights(INT post, UGFxObject* object);
void UpdateGuildStorageRights(INT post);
void UpdateGuildStorageState();
void UpdateGuildSalary();
void UpdatePlayerMoney(INT money);
void Contribute(INT money);
void DistributeSalary(UGFxObject* object);

void UpdateGuildAllyList();
void UpdateGuildEnemyList();
void UpdateGuildApplyAllyList();
void ApplyAlly(const FString& guildName, INT timeType);
void ApplyEnemy(const FString& guildName, INT timeType);
void AgreeAlly(INT id);
void RefuseAlly(INT id);
void UpdateGuildWarInfo();
void UpdateGuildWarSearchState(UBOOL isSearching);
void UpdateGuildWarSearchInfo(INT matchConsume, INT matchCount);

void ExpelConfirm(INT roleId);
void QuitConfirm();

void InviteToJoinGuild(INT roleId);
void ForbidChat(INT roleId, UBOOL isForbid);
void SetForeignApplyDayType(INT foreignType, INT dayType);

void UpdateGuildWarCD();

void ChallengeConfirm(const FString& guildName);
void SetShowPage(INT page, INT subPage);

void AllyCancelConfirm(INT id);

// 公会活动
void UpdateGuildActivityList();

#endif