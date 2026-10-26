#ifndef _MESSAGE_HANDLE_ACTIVITY_H_
#define _MESSAGE_HANDLE_ACTIVITY_H_

public:
	void Send_GetActivityReward(INT nIndex);
	void Send_QueryActivityTeamList(INT nActivity, INT nPage, UINT nActivityType);
	void Send_ChangeTeamActivity(INT nActivity, UINT nActivityType);
private:
	M_DECL_PARSE_FUN(m2c_activity_query_team);
	M_DECL_PARSE_FUN(m2c_activity_change_dungeon);
	M_DECL_PARSE_FUN(g2c_activity_change);
	M_DECL_PARSE_FUN(g2c_activity_reward);

#define M_INIT_MSGHANDLER_ACTIVITY\
	MREG_PARSE_FUN(m2c_activity_query_team);\
	MREG_PARSE_FUN(m2c_activity_change_dungeon);\
	MREG_PARSE_FUN(g2c_activity_change);\
	MREG_PARSE_FUN(g2c_activity_reward);

#endif