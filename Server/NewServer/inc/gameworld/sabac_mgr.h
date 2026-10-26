#ifndef _SABAC_MGR_H_
#define _SABAC_MGR_H_

#include <list>
#include "server_def.h"

struct ENROLL_SABAC_DATA
{
	UINT32				dwGuildID;
	UINT32				dwEnrollTime;
};

class CSabacMgr
{
public:
	CSabacMgr();
	~CSabacMgr();

	BOOL Init(void);
	BOOL UnInit(void);
	static CSabacMgr& GetInstance(void);

	void Enroll(UINT32 dwGuildID, UINT32 dwEnrollTime, INT32 nServerGroup);

	INT32 GetEnrolledGuildCount(INT32 nServerGroup);
	const ENROLL_SABAC_DATA* GetFirstGuild(INT32 nServerGroup);
	const ENROLL_SABAC_DATA* GetNextGuild(INT32 nServerGroup);

	BOOL HasEnrolledGuildToday(INT32 nServerGroup);

	inline void SetOccupyGuildID(INT32 nServerGroup, UINT32 dwGuildID);
	inline UINT32 GetOccupyGuildID(INT32 nServerGroup);

private:
	static CSabacMgr		ms_Instance;

	typedef std::list<ENROLL_SABAC_DATA>	ENROLL_LIST;
	ENROLL_LIST				m_EnrollList[MAX_SERVER_GROUP_COUNT];
	ENROLL_LIST::iterator	m_Iterator[MAX_SERVER_GROUP_COUNT];

	UINT32					m_dwOccupyGuildID[MAX_SERVER_GROUP_COUNT];
};

inline void CSabacMgr::SetOccupyGuildID(INT32 nServerGroup, UINT32 dwGuildID)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_dwOccupyGuildID[nServerGroup] = dwGuildID;
Exit0:
	return;
}

inline UINT32 CSabacMgr::GetOccupyGuildID(INT32 nServerGroup)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	return m_dwOccupyGuildID[nServerGroup];
Exit0:
	return 0;
}

#endif	// _SABAC_MGR_H_