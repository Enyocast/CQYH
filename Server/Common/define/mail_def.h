#ifndef _MAIL_DEF_H_
#define _MAIL_DEF_H_

static const UINT32 MAX_MAIL_COUNT = 50;

static const UINT32 MAX_MAIL_LIST_COUNT = 50;

static const INT32 MAIL_COST = 20;

static const INT32 MAIL_EXPIRE_DAYS = 30;

static const INT32 MAX_MAIL_CD_TIME = 86400 * 5;

enum MAIL_TYPE
{
    MAILTYPE_USER,
    MAILTYPE_SYSTEM
};

#define BUFFER_ATTACH_LEN 64

enum
{
    ATTACHTYPE_NONE,        //没有附件
    ATTACHTYPE_SIMPLE,      //简单附件，只有道具ID和数量，这种附件不可以是装备
    ATTACHTYPE_BUFFER,      //GS生成好的道具信息，一个ItemInfo结构
    ATTACHTYPE_COUNT
};



#endif // _MAIL_DEF_H_
