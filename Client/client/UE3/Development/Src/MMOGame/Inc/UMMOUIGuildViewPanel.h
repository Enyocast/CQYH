#ifndef _UMMOUIGUILDVIEWPANEL_H_
#define _UMMOUIGUILDVIEWPANEL_H_

virtual void Init();
virtual void PostOnShow(UBOOL v);
virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

void ShowGuildViewPanel();
void PageUp();
void PageDown();
void UpdateGuildViewList(INT type, INT size);
void UpdateGuildViewInfo(INT id);
void UpdateGuildBuildingList(INT id);
void FindGuild(UBOOL isId, const FString& content);
void UpdateGuildLeaveCD();

void UpdateGuildFindList(INT id, 
	const FString& guildName, 
	INT level, 
	INT memberCount,
	const FString& leaderName,
	const FString& creatorName,
	INT createTime, 
	const FString& announce,
	INT protectionTime);

void ApplyForJoint(INT id);

// 标志是否从GuildMain打开的
void SetNpcCalled(UBOOL npcCalled);

#endif