#ifndef _MAIL_H_
#define _MAIL_H_

#include "string_def.h"
#include "base_list.h"
#include "mail_def.h"


#pragma pack(push, 1)
struct SimpleAttach
{
    INT32 nItemID;
    INT32 nItemCount;
};
struct MailAttach
{
    UINT8 byAttachLocked;   //是否被锁定。客户端发出取附件请求后，MS先锁定附件，更新数据库锁定状态，然后告诉GS附件信息，GS加成功后再通知MS
    UINT8 byAttachType;
    UINT8 byAttachLen;
    union
    {
        SimpleAttach sa;
        char buffer[BUFFER_ATTACH_LEN];
    };
};
#pragma pack(pop)

struct MailInfo : public BASE_LIST_NODE
{
    UINT32 dwMailID;
    UINT32 dwMailTime;
    UINT32 dwSenderRoleID;
    UINT32 dwReceiverRoleID;
    UINT8 byMailType;
    UINT8 byNew;
    char szSenderRoleName[ROLE_NAME_LEN];
    char szMailSubject[MAIL_SUBJECT_LEN];
    char szMailContent[MAIL_CONTENT_LEN];
    MailAttach ma;
};

#endif // _MAIL_H_
