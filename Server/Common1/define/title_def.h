#ifndef _H_TITLE_DEF_H_
#define _H_TITLE_DEF_H_
#define INVALID_TITLE_ID (0)
#define MAX_TITLE_LIST_NUM  (128)
#define NA_TITLE_EXPIRE_TIME (0xFFFFFFFF)

enum TITLE_DEL_TYPE
{
    TITLE_DEL_TYPE_NONE = 0,
    DEL_BY_EXPIRE,
    DEL_BY_UNEQUIP,
};

enum TITLE_PRE_COND
{
    TITLE_PRE_COND_NONE     = 0,
    TITLE_NEDD_LEVEL        = 1,
    TITLE_SPIRIT_LEVEL      = 2,        // 境界
    TITLE_NEED_VIP          = 3,
    TITLE_NEDD_EVIL_VALUE   = 4,        // 善恶值

};


#endif //_H_TITLE_DEF_H_

