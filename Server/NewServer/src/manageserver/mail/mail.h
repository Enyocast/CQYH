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
    UINT8 byAttachLocked;   //Whether locked. After the client requests an attachment, MS locks it and updates the database, then sends its data to GS; GS notifies MS after adding it successfully
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
