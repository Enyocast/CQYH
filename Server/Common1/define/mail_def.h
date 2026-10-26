#ifndef _MAIL_DEF_H_
#define _MAIL_DEF_H_

static const UINT32 MAX_MAIL_COUNT = 50;

static const UINT32 MAX_MAIL_LIST_COUNT = 50;

static const INT32 MAIL_COST = 20;

static const INT32 MAIL_EXPIRE_DAYS = 30;

enum MAIL_TYPE
{
    MAILTYPE_USER,
    MAILTYPE_SYSTEM
};

#define BUFFER_ATTACH_LEN 64


#endif // _MAIL_DEF_H_
