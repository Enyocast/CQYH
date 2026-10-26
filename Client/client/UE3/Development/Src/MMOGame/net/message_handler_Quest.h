#ifndef __MESSAGE_HANDLER_QUEST_H__
#define __MESSAGE_HANDLER_QUEST_H__

public:
	void Send_AcceptQuest(INT questId, INT questType, INT shareSrcId);
	void Send_AbandonQuest(INT QuestId);
	void Send_CompleteQuest(INT QuestId, INT selectaward);
	void Send_ShareQuest(INT QuestId);
	void Send_QuestNPCTalk(INT questID, INT npcServerID);
	void Send_Explore();
	void Send_FlyToTarget(INT questId, INT destIndex);
	void Send_GenerateCircleQuestList();
	void Send_RefreshRewardQuestList(UBOOL useMoney);
	void Send_UpgradeAwardQuestLimit(INT maxLimit);
	void Send_CompleteAllRewardQuest();
	void Send_Recycle(INT itemTempId, INT index);

M_DECL_PARSE_FUN(g2c_accept_quest);
M_DECL_PARSE_FUN(g2c_abandon_quest);
M_DECL_PARSE_FUN(g2c_complete_quest);
M_DECL_PARSE_FUN(g2c_sync_quest_list);
M_DECL_PARSE_FUN(g2c_share_quest);
M_DECL_PARSE_FUN(g2c_notify_next_circle_quest);
M_DECL_PARSE_FUN(g2c_buy_daily_quest_complete_time);
M_DECL_PARSE_FUN(g2c_brush_daily_quest);
M_DECL_PARSE_FUN(g2c_quest_recycle);
M_DECL_PARSE_FUN(g2c_set_quest_failed);

#define M_INIT_MSGHANDLER_QUEST \
	MREG_PARSE_FUN(g2c_accept_quest); \
	MREG_PARSE_FUN(g2c_abandon_quest); \
	MREG_PARSE_FUN(g2c_complete_quest); \
	MREG_PARSE_FUN(g2c_sync_quest_list); \
	MREG_PARSE_FUN(g2c_share_quest); \
	MREG_PARSE_FUN(g2c_notify_next_circle_quest); \
	MREG_PARSE_FUN(g2c_buy_daily_quest_complete_time); \
	MREG_PARSE_FUN(g2c_brush_daily_quest); \
	MREG_PARSE_FUN(g2c_quest_recycle); \
	MREG_PARSE_FUN(g2c_set_quest_failed); \

#endif