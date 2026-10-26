#ifndef _IMESSAGE_NOTIFIER_H_
#define _IMESSAGE_NOTIFIER_H_

#include "net.h"
class CRole;

class IMessageNotifier
{
public:
    virtual BOOL SendToUser(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize) = 0;
    virtual BOOL SendToUsers(UINT32 dwGTSessionID, UINT32 dwClientSessionIDList[], INT32 nSessionCount, PACKET_BUFFER* pData, UINT32 dwSize) = 0;
    virtual BOOL SendToMS(PACKET_BUFFER* pData, UINT32 dwSize) = 0;
	virtual BOOL SendToDL(PACKET_BUFFER* pData, UINT32 dwSize) = 0;

    virtual BOOL ReturnSelectRole(UINT32 dwClientSessionID) = 0;
    virtual BOOL SaveRoleData(CRole* poRole, BOOL bSaveFile) = 0;
	virtual BOOL UnlockRole(CRole* poRole) = 0;
    virtual BOOL _KickUser(UINT32 dwClientSessionID) = 0;

	virtual BOOL Logout(UINT32 dwClientSessionID) = 0;
};

#endif	// _IMESSAGE_NOTIFIER_H_
