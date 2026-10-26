#ifndef _DOODAD_H_
#define _DOODAD_H_

#include "scene_object.h"

class CCharacter;
struct DOODAD_DATA;
struct DOODAD_SPAWN_POINT;

enum DOODAD_STATE
{
	dsInvalid,

	dsAlive,
	dsDead,

	dsTotal
};

class CDoodad : public CSceneObject
{
public:
	CDoodad();
	virtual ~CDoodad();

	BOOL Init(UINT32 dwObjID, INT32 nTemplateID);
	BOOL UnInit(void);
	BOOL MainLoop(void);

	virtual INT32 GetObjType(void);
	inline const DOODAD_DATA* GetDoodadData(void);
	BOOL SetTemplateID(INT32 nTemplateID);
	inline void SetSpawnPoint(const DOODAD_SPAWN_POINT* pcSpawnPoint);
	inline const DOODAD_SPAWN_POINT* GetSpawnPoint(void);

	inline INT32 GetOpenCount(void);
	BOOL CanOpen(CCharacter* poChar);
	void OnOpen(CCharacter* poChar, INT32 nDelayFrame);

protected:
	void _OnOpen(CCharacter* poChar);

private:
	const DOODAD_DATA*		    m_pDoodadData;
	INT32                       m_eState;
	INT32                       m_nOpenCount;
	INT32                       m_nOpenTimer;
	UINT32                      m_dwOpenCharID;
	const DOODAD_SPAWN_POINT*   m_pcSpawnPoint;
	INT32                       m_nReviveTimer;
	INT32						m_nDestroyTimer;
};

inline const DOODAD_DATA* CDoodad::GetDoodadData(void)
{
	return m_pDoodadData;
}

inline INT32 CDoodad::GetOpenCount(void)
{
	return m_nOpenCount;
}

inline const DOODAD_SPAWN_POINT* CDoodad::GetSpawnPoint(void)
{
	return m_pcSpawnPoint;
}

inline void CDoodad::SetSpawnPoint(const DOODAD_SPAWN_POINT* pcSpawnPoint)
{
	m_pcSpawnPoint = pcSpawnPoint;
}
#endif	// _DOODAD_H_
