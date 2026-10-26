#ifndef _SERVER_VAR_H_
#define _SERVER_VAR_H_

#include "variable_def.h"
#include "server_def.h"

class CServerVar
{
public:
    CServerVar();
    ~CServerVar();

    BOOL Init(void);
    BOOL UnInit(void);
    static CServerVar& GetInstance(void);

	INT32 GetVariable(INT32 nServerGroup, UINT64 qwKey);
	void SetVariable(INT32 nServerGroup, UINT64 qwKey, INT32 nValue);

	inline BOOL GetFirstVariable(INT32 nServerGroup, UINT64& rqwKey, INT32& rnValue);
	inline BOOL GetNextVariable(INT32 nServerGroup, UINT64& rqwKey, INT32& rnValue);

private:
    static BOOL _Load(std::list<void*>& rResult, void* pUserData);

private:
    static CServerVar ms_Instance;

	typedef std::map<UINT64, INT32> SERVER_VAR_MAP;
	SERVER_VAR_MAP				m_VarList[MAX_SERVER_GROUP_COUNT];
	SERVER_VAR_MAP::iterator	m_Iterator;
};

inline BOOL CServerVar::GetFirstVariable(INT32 nServerGroup, UINT64& rqwKey, INT32& rnValue)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	m_Iterator = m_VarList[nServerGroup].begin();
	PROCESS_ERROR(m_Iterator != m_VarList[nServerGroup].end());

	rqwKey = m_Iterator->first;
	rnValue = m_Iterator->second;

	return TRUE;
Exit0:
	return FALSE;
}

inline BOOL CServerVar::GetNextVariable(INT32 nServerGroup, UINT64& rqwKey, INT32& rnValue)
{
	LOG_PROCESS_ERROR(nServerGroup >= 0 && nServerGroup < MAX_SERVER_GROUP_COUNT);

	++m_Iterator;
	PROCESS_ERROR(m_Iterator != m_VarList[nServerGroup].end());

	rqwKey = m_Iterator->first;
	rnValue = m_Iterator->second;

	return TRUE;
Exit0:
	return FALSE;
}

#endif  // _SERVER_VAR_H_