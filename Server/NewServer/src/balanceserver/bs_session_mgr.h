#ifndef _BS_SESSION_MGR_H_
#define _BS_SESSION_MGR_H_

#include <list>
#include "base_list.h"
#include "server_def.h"
#include "id_object_pool.h"

class INet;
class ISocketSession;

struct BASE_SESSION : BASE_LIST_NODE
{
	UINT32              dwType;
	ISocketSession*     pSocketSession;
	UINT64              qwTimer;
};

struct MS_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};

struct GD_SESSION : BASE_SESSION
{
	UINT8               bConnected;
};

class CBSSessionMgr
{
public:
	CBSSessionMgr();
	~CBSSessionMgr();

	BOOL Init(INet* pExternalNet, INet* pInternalNet);
	BOOL UnInit(void);
	static CBSSessionMgr& GetInstance(void);
	
	inline MS_SESSION& GetMSSession(void);
	inline GD_SESSION& GetGDSession(void);

	inline INT32 GetServerState(void);
	inline void SetServerState(INT32 eServerState);

	inline INT32 GetCurPointerIndex(void);
	inline void  SetCurPointerIndex(INT32 nIndex);

	BOOL CheckSession(void);
	BOOL CloseAllSession(void);

	BOOL MainLoop(void);
private:
	static CBSSessionMgr                    ms_Instance;
	INT32                                   m_eServerState;
	INT32									m_nCurPointerIndex;
	UINT64									m_qwLastPingTick;
	UINT64                                  m_qwLastStatisTick;

	INet*                                   m_pExternalNet;
	INet*                                   m_pInternalNet;
	
	GD_SESSION								m_GDSession;
	MS_SESSION								m_MSSession;
};

inline	INT32	CBSSessionMgr::GetServerState()
{
	return m_eServerState;
}

inline	void	CBSSessionMgr::SetServerState(INT32 nServerState)
{
	m_eServerState = nServerState;
}

inline	INT32	CBSSessionMgr::GetCurPointerIndex()
{
	return m_nCurPointerIndex;
}

inline void CBSSessionMgr::SetCurPointerIndex(INT32 nIndex)
{
	m_nCurPointerIndex = nIndex;
}

inline MS_SESSION& CBSSessionMgr::GetMSSession()
{
	return m_MSSession;
}

inline GD_SESSION& CBSSessionMgr::GetGDSession()
{
	return m_GDSession;
}

#endif // _BS_SESSION_MGR_H_