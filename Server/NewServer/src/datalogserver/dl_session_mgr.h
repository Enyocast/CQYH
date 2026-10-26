#ifndef _DL_SESSION_MGR_H_
#define _DL_SESSION_MGR_H_

#include <list>
#include "base_list.h"
#include "server_def.h"
#include "id_object_pool.h"

class INet;
class ISocketSession;

struct BASE_SESSION : BASE_LIST_NODE
{
	UINT8               byType;
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
};

struct MS_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};

struct GS_SESSION : BASE_SESSION
{
	UINT32				dwSessionID;
};

struct GD_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};


class CDLSessionMgr
{
public:
	CDLSessionMgr();
	~CDLSessionMgr();

	BOOL Init(INet* pInternalNet);
	BOOL UnInit(void);
	static CDLSessionMgr& GetInstance(void);
	
	inline MS_SESSION& GetMSSession(void);
	inline GD_SESSION& GetGDSession(void);
	inline GS_SESSION* GetGSSession(UINT32 dwGSSessionID);


	inline INT32 GetServerState(void);
	inline void SetServerState(INT32 eServerState);

	BOOL CheckSession(void);
	BOOL CloseAllSession(void);

	BOOL MainLoop(void);
private:
	static CDLSessionMgr                    ms_Instance;
	INT32                                   m_eServerState;
	UINT64									m_qwLastPingTick;
	UINT64                                  m_qwLastStatisTick;

	INet*                                   m_pInternalNet;
	
	GS_SESSION								m_GSSession[MAX_GS_SESSION_COUNT];
	MS_SESSION								m_MSSession;
	GD_SESSION								m_GDSession;
};

inline	INT32	CDLSessionMgr::GetServerState()
{
	return m_eServerState;
}

inline	void	CDLSessionMgr::SetServerState(INT32 nServerState)
{
	m_eServerState = nServerState;
}

inline MS_SESSION& CDLSessionMgr::GetMSSession()
{
	return m_MSSession;
}

inline GD_SESSION& CDLSessionMgr::GetGDSession()
{
	return m_GDSession;
}

inline GS_SESSION* CDLSessionMgr::GetGSSession(UINT32 dwGSSessionID)
{
	LOG_PROCESS_ERROR(dwGSSessionID > 0 && dwGSSessionID < MAX_GS_SESSION_COUNT);

	return m_GSSession + dwGSSessionID;
Exit0:
	return NULL;
}

#endif // _DL_SESSION_MGR_H_