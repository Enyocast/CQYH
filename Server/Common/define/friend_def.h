#ifndef _FRIEND_DEF_H_
#define _FRIEND_DEF_H_

// tolua_begin

#define MAX_FRIEND_COUNT (200)
#define MAX_FRIEND_GROUP_COUNT (10)
#define FRIEND_GROUP_ENEMY  (21)
#define FRIEND_GROUP_NAME_LEN (25)
#define SIGNATURE_LEN (37)

#define MAX_PERSONAL_ENEMY_COUNT (40)


enum FRIEND_STATE
{
    FS_ONLINE,
    FS_BUSY,
    FS_AFK,
    FS_OFFLINE
};

// tolua_end

#endif // _FRIEND_DEF_H_
