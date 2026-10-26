#ifndef _ROLE_KICK_MGR_H_
#define _ROLE_KICK_MGR_H_

#ifndef _ROBOT
#include "base_list.h"

class CRoleKickMgr
{
public:
	CRoleKickMgr();
	~CRoleKickMgr() {}

	BOOL AddToKickList(UINT32 dwRoleID);
	BOOL KickPendingRoles(void);

	static CRoleKickMgr& GetInstance();

private:
	std::list<UINT32>					m_lstKickRole;
	static CRoleKickMgr					ms_Instance;
};

#endif _ROBOT

#endif //_ROLE_KICK_MGR_H_
