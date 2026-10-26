#ifndef _MM_SESSION_MGR_H_
#define _MM_SESSION_MGR_H_

#include <list>
#include "base_list.h"

#include "id_object_pool.h"

#include "server_def.h"
#include "string_def.h"
#include "role_def.h"

class INet;
class ISocketSession;

struct MM_BASE_SESSION : BASE_LIST_NODE
{
	UINT32              dwType;
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
	UINT32				dwReportTime;
};

struct MG_SESSION : MM_BASE_SESSION
{
	UINT32				dwSessionID;
	UINT8               bConnected;
};

struct MS_SESSION : MM_BASE_SESSION
{
	UINT8               bConnected;
};

struct GD_SESSION : MM_BASE_SESSION
{
	UINT8               bConnected;
};

class CMMSessionMgr
{
public:
	CMMSessionMgr();
	~CMMSessionMgr();

	BOOL Init(INet* pNet);
	BOOL UnInit(void);
	static CMMSessionMgr& GetInstance(void);

	inline MG_SESSION* NewMGSession(ISocketSession* pSession);
	inline void DelMGSession(MG_SESSION* pGTSession);
	inline MG_SESSION* GetMGSession(UINT32 dwMGSessionID);
	inline MS_SESSION& GetMSSession(void);
	inline GD_SESSION& GetGDSession(void);

	inline INT32 GetServerState(void);
	inline void SetServerState(INT32 eServerState);

	BOOL CheckSession();
	BOOL CloseAllSession();

	BOOL MainLoop(void);
private:
	static CMMSessionMgr					ms_Instance;
	INT32                                   m_eServerState;
	UINT64                                  m_qwLastPingTick;

	INet*                                   m_pNet;

	MG_SESSION                              m_MGSession[MAX_MG_SESSION_COUNT];
	MS_SESSION                              m_MSSession;
	GD_SESSION                              m_GDSession;
};

inline MG_SESSION* CMMSessionMgr::GetMGSession(UINT32 dwMGSessionID)
{
	LOG_PROCESS_ERROR(dwMGSessionID < MAX_MG_SESSION_COUNT);
	return m_MGSession + dwMGSessionID;
Exit0:
	return NULL;
}

inline MG_SESSION* CMMSessionMgr::NewMGSession(ISocketSession* pSession)
{
	for (INT32 nIndex = 1; nIndex < MAX_MG_SESSION_COUNT; ++nIndex)
	{
		if (m_MGSession[nIndex].pSocketSession == NULL)
		{
			m_MGSession[nIndex].pSocketSession = pSession;
			return m_MGSession + nIndex;
		}
	}

	return NULL;
}

inline void CMMSessionMgr::DelMGSession(MG_SESSION* pMGSession)
{
	LOG_PROCESS_ERROR(pMGSession);
	pMGSession->pSocketSession = NULL;
Exit0:
	return;
}

inline MS_SESSION& CMMSessionMgr::GetMSSession(void)
{
	return m_MSSession;
}

inline GD_SESSION& CMMSessionMgr::GetGDSession(void)
{
	return m_GDSession;
}

inline INT32 CMMSessionMgr::GetServerState(void)
{
	return m_eServerState;
}

inline void CMMSessionMgr::SetServerState(INT32 eServerState)
{
	LOG_PROCESS_ERROR(eServerState > sgsInvalid && eServerState < sgsTotal);
	m_eServerState = eServerState;
Exit0:
	return;
}

#endif  // _MM_SESSION_MGR_H_