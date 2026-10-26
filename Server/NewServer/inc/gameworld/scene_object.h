#ifndef _SCENE_OBJECT_H_
#define _SCENE_OBJECT_H_

#include "base_list.h"
#include "block_handler.h"
#include "scene_def.h"

class CScene;
class CRegion;
class CBlockHandler;

struct GRID_DATA;
struct ZONE_DATA;
struct GRID_INSTANCE_DATA;

class CSceneObject
{
public:
	CSceneObject();
	virtual ~CSceneObject();

    BOOL Init(UINT32 dwObjID);
    BOOL UnInit(void);
    BOOL MainLoop(void);
    BOOL CheckLoop(void);
    inline INT32 GetGameFrame(void);

    virtual INT32 GetObjType(void) = 0;
	inline UINT32 GetObjID(void);
	inline BASE_LIST_NODE& GetRegionListNode(void);
	inline BOOL IsDeleteSelf(void);
	void DeleteSelf(void);

	virtual BOOL RotateTo(INT32 nFaceDirection, INT32 nDurationFrm);
	inline BOOL IsRotating(void);
	inline INT32 GetFaceDirection(void);
	inline void SetFaceDirection(INT32 nFaceDirection);

	inline void SetScene(CScene* poScene);
	inline CScene* GetScene(void);

	inline void SetRegion(CRegion* poRegion);
	inline CRegion* GetRegion(void);

	inline void SetZone(const ZONE_DATA* pcZone);
	inline const ZONE_DATA* GetZone(void);

	inline void SetGrid(const GRID_DATA* pcGrid);
    inline const GRID_DATA* GetGrid(void);

	inline void SetGridInstance(GRID_INSTANCE_DATA* pGridInstance);
	inline GRID_INSTANCE_DATA* GetGridInstance(void);

	inline void SetX(INT64 llX);
	inline void SetY(INT64 llY);
	inline void SetZ(INT64 llZ);

	inline INT64 GetX(void);
	inline INT64 GetY(void);
	inline INT64 GetZ(void);

	inline INT64 GetDistance3D(CSceneObject* poSceneObject);
	inline INT64 GetDistance3D(INT64 llX, INT64 llY, INT64 llZ);
	inline INT32 GetRadius(void);

	void SetBodyType(INT32 nBodyType);
	inline INT32 GetBodyType(void);

	BOOL CheckGridCharRef(INT32 nBodyType);
	BOOL CheckGridCharRef(CScene* poScene, INT64 llX, INT64 llY, INT64 llZ);
	BOOL CheckAdjGridCharRef(INT64 llX, INT64 llY, INT64 llZ);
	BOOL SetGridCharRef(void);
	BOOL ClearGridCharRef(void);

	BOOL CanTeleport(void);

protected:
	virtual BOOL _GridMove(INT64 llDestX, INT64 llDestY);
	virtual BOOL _ChangeRegion(CRegion* poDestRegion);

protected:
	UINT32		        m_dwObjID;
	INT32		        m_nGameFrame;
	BASE_LIST_NODE      m_RegionListNode;
	BOOL                m_bDeleteSelf;

	CScene*		        m_poScene;
	CRegion*	        m_poRegion;
    const GRID_DATA*    m_pcGrid;
	const ZONE_DATA*	m_pcZone;
	GRID_INSTANCE_DATA*	m_pGridInstance;
	INT64		        m_llX, m_llY, m_llZ;
	INT32		        m_nFaceDirection;
	BOOL	            m_IsRotating;
	INT32	            m_nOmiga;
	INT32	            m_nDestDirection;
	INT32				m_nBodyType;
};

void GetOffsetedPos(INT64 llX, INT64 llY, INT32 nDirection, INT32 nHOffsetGrids, INT32 nVOffsetGrids, INT64& llOutX, INT64& llOutY);

#include "scene_object_inl.h"

#endif	// _SCENE_OBJECT_H_
