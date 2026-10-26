#ifndef _THREAT_LIST_H_
#define _THREAT_LIST_H_

#include "base_list.h"
#include <vector>

class CCharacter;

struct THREAT_NODE : BASE_LIST_NODE
{
	UINT32 dwCharID;
	THREAT_NODE* pPairNode;

	union
	{
		INT32 nThreatValue;
		INT32 nLastUpdateLoop;
	};
};

class CThreatList
{
public:
	CThreatList();
	~CThreatList();

    BOOL Init(CCharacter* poOwner);
	BOOL UnInit(void);
	BOOL MainLoop(void);

	BOOL ModifyThreatValue(CCharacter* poCharacter, INT32 nValue);
	BOOL ModifyChainThreatValue(CCharacter* poCharacter, INT32 nValue);
	BOOL Clear(void);
	BOOL IsEmpty(void);
	BOOL CheckThreat(UINT32 dwCharID);
    BOOL CheckThreaten(UINT32 dwCharID);

	void RemoveThreatNode(UINT32 dwCharID);

	CCharacter* GetFirstTarget(void);

	inline CBaseList& GetThreatList(void) {  return m_ThreatList; }
    inline CBaseList& GetThreatenList(void){ return m_ThreatenList; }

    inline void SetFadeTime(INT32 nThreatenFadeTime, INT32 nThreatFadeTime);

private:
	CBaseList m_ThreatList;
	CBaseList m_ThreatenList;

	CCharacter* m_pOwner;

    INT32       m_nThreatenFadeTime;
    INT32       m_nThreatFadeTime;
};

inline void CThreatList::SetFadeTime(INT32 nThreatenFadeTime, INT32 nThreatFadeTime)
{
    m_nThreatenFadeTime = nThreatenFadeTime; 
    m_nThreatFadeTime = nThreatFadeTime;
}

#endif	// _THREAT_LIST_H_
