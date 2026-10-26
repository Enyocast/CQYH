#include "stdafx.h"
#include "dl_message_notifier.h"

BOOL CDLMessageNotifier::SendToUser(UINT32 dwClientSessionID, PACKET_BUFFER* pData, UINT32 dwSize)
{
	return FALSE;
}

BOOL CDLMessageNotifier::SendToUsers(UINT32 dwGTSessionID, UINT32 dwClientSessionIDList[], INT32 nSessionCount, PACKET_BUFFER* pData, UINT32 dwSize)
{
    return FALSE;
}

BOOL CDLMessageNotifier::SendToMS(PACKET_BUFFER* pData, UINT32 dwSize)
{
	return FALSE;
}

BOOL CDLMessageNotifier::SendToDL(PACKET_BUFFER* pData, UINT32 dwSize)
{
	return FALSE;
}

BOOL CDLMessageNotifier::ReturnSelectRole(UINT32 dwClientSessionID)
{
    return FALSE;
}

BOOL CDLMessageNotifier::SaveRoleData(CRole* poRole, BOOL bSaveFile)
{
	return FALSE;
}

BOOL CDLMessageNotifier::UnlockRole(CRole* poRole)
{
	return FALSE;
}

BOOL CDLMessageNotifier::_KickUser(UINT32 dwClientSessionID)
{
	return FALSE;
}

BOOL CDLMessageNotifier::Logout(UINT32 dwClientSessionID)
{
	return FALSE;
}

