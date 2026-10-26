#ifndef _MS_TEAM_MGR_H_
#define _MS_TEAM_MGR_H_

#include <list>

typedef std::list<UINT32> listDugeon2Team;

class CMSTeamMgr
{
	CMSTeamMgr();
	~CMSTeamMgr();

	BOOL Init();
	BOOL Uninit();

	inline CMSTeamMgr& GetInstance();

	INT32 AddTeamToDegeon(INT32 nDugeonID, UINT32 dwTeamID);
	INT32 RemoveTeamFromDegeon(INT32 nDugeonID, UINT32 dwTeamID);


private:

	CMSTeamMgr& m_Instance;

};

inline CMSTeamMgr& CMSTeamMgr::GetInstance()
{
	return m_Instance;
}

#endif // _MS_TEAM_MGR_H_