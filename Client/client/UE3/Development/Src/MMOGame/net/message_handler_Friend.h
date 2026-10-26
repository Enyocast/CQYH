#ifndef __MESSAGE_HANDLER_FRIEND_H__
#define __MESSAGE_HANDLER_FRIEND_H__

public:
	void Request_FriendList();
	void RequestAddFriend( FString RoleName , INT RoleId  );
	void RequestFriendChangeInfo( FString szSignature , INT byFriendState  );
	void RequestDelFriend( INT RoleId  );

	void SendFriendChat( INT roleId , FString ChatContent );
	void SendMoveToBlackList( INT roleId , FString roleName );
	void SendRemoveFromBlackList( INT roleId );

	void ChangeFriendGroup( INT RoleId, INT GroupId  );
	void ChangeFriendGroupName( FString GroupName , INT GroupId );
	void ChangeFriendInfo( );

	void SendAddEnemy(INT nRoleID);
	void SendDeleteEnemy(INT nRoleID);
private:

	M_DECL_PARSE_FUN(g2c_friend_group_list);
	M_DECL_PARSE_FUN(m2c_friend_list);
	M_DECL_PARSE_FUN( m2c_friend_info_change);
	M_DECL_PARSE_FUN(m2c_friend_add);
	M_DECL_PARSE_FUN(m2c_friend_del);
	M_DECL_PARSE_FUN(m2c_friend_added_by);
	M_DECL_PARSE_FUN(m2c_friend_deleted_by);
	M_DECL_PARSE_FUN(m2c_self_info);
	M_DECL_PARSE_FUN(m2c_friend_chat);
	M_DECL_PARSE_FUN(g2c_sync_shield_list);
	M_DECL_PARSE_FUN(g2c_shield_ack);
	M_DECL_PARSE_FUN(g2c_unshield_ack);
	M_DECL_PARSE_FUN(m2c_personal_enemy_add);
	M_DECL_PARSE_FUN(m2c_personal_enemy_del);
	M_DECL_PARSE_FUN(g2c_sync_msg_paopao);
	M_DECL_PARSE_FUN(m2c_sync_friend_intimacy);
	M_DECL_PARSE_FUN(m2c_h5_url);

#define M_INIT_MSGHANDLER_FRIEND \
	MREG_PARSE_FUN(g2c_friend_group_list);\
	MREG_PARSE_FUN(m2c_friend_list);\
	MREG_PARSE_FUN(m2c_friend_info_change);\
	MREG_PARSE_FUN(m2c_friend_add);\
	MREG_PARSE_FUN(m2c_friend_del);\
	MREG_PARSE_FUN(m2c_friend_added_by);\
	MREG_PARSE_FUN(m2c_friend_deleted_by);\
	MREG_PARSE_FUN(m2c_self_info);\
	MREG_PARSE_FUN(m2c_friend_chat);\
	MREG_PARSE_FUN(g2c_sync_shield_list);\
	MREG_PARSE_FUN(g2c_shield_ack);\
	MREG_PARSE_FUN(g2c_unshield_ack);\
	MREG_PARSE_FUN(m2c_personal_enemy_add);\
	MREG_PARSE_FUN(g2c_sync_msg_paopao);\
	MREG_PARSE_FUN(m2c_personal_enemy_del);\
	MREG_PARSE_FUN(m2c_sync_friend_intimacy);\
	MREG_PARSE_FUN(m2c_h5_url);

#endif