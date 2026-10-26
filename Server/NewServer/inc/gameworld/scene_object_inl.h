#ifndef _SCENE_OBJECT_INL_H_
#define _SCENE_OBJECT_INL_H_

#include "math_ex.h"

#ifdef __linux__
#include <limits.h>
#endif

inline INT32 CSceneObject::GetGameFrame(void)
{
    return m_nGameFrame;
}

inline UINT32 CSceneObject::GetObjID(void)
{
	return m_dwObjID;
}

inline void CSceneObject::SetFaceDirection(INT32 nFaceDirection)
{
    m_nFaceDirection = nFaceDirection;
}

inline BASE_LIST_NODE& CSceneObject::GetRegionListNode(void)
{
    return m_RegionListNode;
}

inline void CSceneObject::SetScene(CScene* poScene)
{
	m_poScene = poScene;
}

inline CScene* CSceneObject::GetScene(void)
{
	return m_poScene;
}

inline void CSceneObject::SetRegion(CRegion* poRegion)
{
	m_poRegion = poRegion;
}

inline CRegion* CSceneObject::GetRegion(void)
{
	return m_poRegion;
}

inline void CSceneObject::SetZone(const ZONE_DATA* pcZone)
{
	m_pcZone = pcZone;
}

inline const ZONE_DATA* CSceneObject::GetZone(void)
{
	return m_pcZone;
}

inline void CSceneObject::SetGrid(const GRID_DATA* pcGrid)
{
    m_pcGrid = pcGrid;
}

inline const GRID_DATA* CSceneObject::GetGrid(void)
{
    return m_pcGrid;
}

inline void CSceneObject::SetGridInstance(GRID_INSTANCE_DATA* pGridInstance)
{
	m_pGridInstance = pGridInstance;
}

inline GRID_INSTANCE_DATA* CSceneObject::GetGridInstance(void)
{
	return m_pGridInstance;
}

inline void CSceneObject::SetX(INT64 llX)
{
	m_llX = llX;
}

inline void CSceneObject::SetY(INT64 llY)
{
	m_llY = llY;
}

inline void CSceneObject::SetZ(INT64 llZ)
{
	m_llZ = llZ;
}

inline INT64 CSceneObject::GetX(void)
{
	return m_llX;
}

inline INT64 CSceneObject::GetY(void)
{
	return m_llY;
}

inline INT64 CSceneObject::GetZ(void)
{
	return m_llZ;
}

inline INT64 CSceneObject::GetDistance3D(CSceneObject* poSceneObject)
{
    LOG_PROCESS_ERROR(poSceneObject);

    return g_GetDistance3D(m_llX, m_llY, m_llZ, poSceneObject->GetX(), poSceneObject->GetY(), poSceneObject->GetZ());
Exit0:

    return LLONG_MAX;
}

inline INT64 CSceneObject::GetDistance3D(INT64 llX, INT64 llY, INT64 llZ)
{
	return g_GetDistance3D(m_llX, m_llY, m_llZ, llX, llY, llZ);
}

inline INT32 CSceneObject::GetFaceDirection(void)
{
	return m_nFaceDirection;
}

inline BOOL CSceneObject::IsDeleteSelf(void)
{
    return m_bDeleteSelf;
}

inline BOOL CSceneObject::IsRotating(void)
{
	return m_IsRotating;
}

inline INT32 CSceneObject::GetBodyType(void)
{
	return m_nBodyType;
}

inline INT32 CSceneObject::GetRadius(void)
{
	if (m_nBodyType == body3x3)
		return GRID_WIDTH * 3 / 2;
	return GRID_WIDTH / 2;
}

#endif // _SCENE_OBJECT_INL_H_
