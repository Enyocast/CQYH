#ifndef _MESSAGE_NOTIFIER_H_
#define _MESSAGE_NOTIFIER_H_

#include "gameworld/imessage_notifier.h"

class CDLMessageNotifier : public IMessageNotifier
{
	virtual BOOL SendToUser(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize);
    virtual BOOL SendToUsers(UINT32 dwGTSessionID, UINT32 dwClientSessionIDList[], INT32 nSessionCount, PACKET_BUFFER* pData, UINT32 dwSize);
	virtual BOOL SendToMS(PACKET_BUFFER* pData, UINT32 dwSize);
	virtual BOOL SendToDL(PACKET_BUFFER* pData, UINT32 dwSize);

    virtual BOOL ReturnSelectRole(UINT32 dwClientSessionID);
    virtual BOOL SaveRoleData(CRole* poRole, BOOL bSaveFile);
	virtual BOOL UnlockRole(CRole* poRole);
    virtual BOOL _KickUser(UINT32 dwClientSessionID);

	virtual BOOL Logout(UINT32 dwClientSessionID);
};

#endif	// _MESSAGE_NOTIFIER_H_
