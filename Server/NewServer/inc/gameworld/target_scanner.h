#ifndef _TARGET_SCANNER_H_
#define _TARGET_SCANNER_H_

#include "spell_def.h"
#include "spell_data.h"
#include "base_list.h"

class CSpell;
class CSceneObject;
class CCharacter;
class CRegion;
class CBullet;
class CScene;
class CSpellInstance;
class CDoodad;
class CMissile;

struct TARGET_NODE : public BASE_LIST_NODE
{
	BOOL bIsLocked;
	UINT32 dwTargetID;
	INT64 qwTargetDist;
};

struct PLACED_GRID : public BASE_LIST_NODE
{
	INT64 llGridX;
	INT64 llGridY;
};

class CTargetScanner
{
public:
	CTargetScanner(void);
	~CTargetScanner(void);

	BOOL Init(CCharacter* poCaster, INT32 eType, INT32 nParam1, INT32 nParam2, INT32 nParam3, INT32 nDirection, INT32 nTargetObjTypeLimit, INT32 nRelationshipLimit, INT32 nStanceLimit, BOOL bTargetDeadLimit, BOOL bUseWeaponRange, BOOL bIgnoreObstacle, INT32 nTargetCheckNode);
	BOOL Init(CCharacter* poCaster, CSpell* poSpell, INT32 nDirection);
	BOOL Init(CCharacter* poCaster, CMissile* poMissile, CSpell* poSpell, INT32 nDirection, INT64 llTargetX, INT64 llTargetY, INT64 llTargetZ);

	void ResetScanner(CSpellInstance* poSpell);
	void UnInit(void);

	void ClearTarget(void);

	inline UINT32 GetLockedTarget(void);
	void LockTarget(CCharacter* poTarget);

	inline void SetCenterPt(INT64 x, INT64 y, INT64 z);
	inline void GetCenterPt(INT64& x ,INT64& y, INT64& z);

	inline void SetTargetPt(INT64 x, INT64 y, INT64 z);
	inline void GetTargetPt(INT64& x ,INT64& y, INT64& z);

	inline INT64 GetTargetX(void);
	inline INT64 GetTargetY(void);
	inline INT64 GetTargetZ(void);

	inline INT64 GetCenterX(void);
	inline INT64 GetCenterY(void);
	inline INT64 GetCenterZ(void);

	inline INT32 GetRangeType(void);

	inline INT32 GetConvertedParam1(void);
	inline INT32 GetConvertedParam2(void);

	inline INT32 GetParam1(void);
	inline INT32 GetParam2(void);
	inline INT32 GetParam3(void);

	inline BOOL UseWeaponRange(void);
	inline BOOL IgnoreTargetRadius(void);

	inline INT32 GetTargetCount(void);

	inline INT32 GetTargetCheckNode(void);

	inline void SetDirection(INT32 nDirection);
	inline INT32 GetDirection(void);

	inline INT32 GetTargetObjTypeLimit(void);
	inline INT32 GetRelationshipLimit(void);
	inline INT32 GetStanceLimit(void);
	inline BOOL IsCorpseValid(void);

	void AddSkippedGrid(INT64 llX, INT64 llY);

	BOOL Scan(CRegion* poRegion, CCharacter* poCaster);

	BOOL operator()(CCharacter* poTarget);
	BOOL operator()(CDoodad* poDoodad);
	BOOL operator()(CRegion* poRegion);

	INT64 CheckTarget(CCharacter* poCaster, CCharacter* poTarget);

	void BeginTarget(void);
	TARGET_NODE* NextTarget(void);
	TARGET_NODE* LoopNextTarget(void);

	TARGET_NODE* AddTarget(UINT32 dwObjID, INT64 qwDistSq, INT64 llTargetX, INT64 llTargetY, INT64 llTargetZ);
	BOOL AddDoodad(CDoodad* poDoodad);

	CBullet* DoSingleBullet(CSpellInstance* poSpell, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, INT32 nBulletType, BOOL bTargetLocked);
	CBullet* DoSingleBullet(CMissile* poMissile, CCharacter* poCaster, CCharacter* poTarget, CSceneObject* poFromObj, INT32 nBulletType);

	INT32 DoBullet(CMissile* poMissile, CCharacter* poCaster, INT32 nBulletType);
	INT32 DoBullet(CSpellInstance* poSpell, CCharacter* poCaster, INT32 nBulletType);

protected:
	typedef BOOL (CTargetScanner::*SelectFunc)(CCharacter* target, INT64& llRangeSq);
	static SelectFunc m_SelectFuncs[sprtTotal];

	BOOL _CircleSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _RingSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _SectorSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _ArcSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _RectangleSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _RearHalfCircle(CCharacter* target, INT64& llRangeSq);

	BOOL _GridLineSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridRectSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridCrossSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridXSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridUSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridSingleSelector(CCharacter* target, INT64& llRangeSq);
	BOOL _GridLineTransverse(CCharacter* target, INT64& llRangeSq);

	// 自己新增代码
	BOOL _GridMultiLineSelector(CCharacter* target, INT64& llRangeSq);

	typedef BOOL (CTargetScanner::*DoodadSelectFunc)(CDoodad* target);
	static DoodadSelectFunc m_DoodadSelectFuncs[sprtTotal];

//	static BOOL _DoodadCircleSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* target);
//	static BOOL _DoodadRingSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* target);
//	static BOOL _DoodadSectorSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* target);
//	static BOOL _DoodadArcSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* target);
//	static BOOL _DoodadRectangleSelector(CTargetScanner* inst, CCharacter* caster, CDoodad* target);
//	static BOOL _DoodadRearHalfCircle(CTargetScanner* inst, CCharacter* caster, CDoodad* target);

	BOOL _DoodadGridLineSelector(CDoodad* target);
	BOOL _DoodadGridRectSelector(CDoodad* target);
	BOOL _DoodadGridCrossSelector(CDoodad* target);
	BOOL _DoodadGridXSelector(CDoodad* target);
	BOOL _DoodadGridUSelector(CDoodad* target);
	BOOL _DoodadGridSingleSelector(CDoodad* target);
	BOOL _DoodadGridLineTransverse(CDoodad* target);


private:
	CBaseList m_TargetList;
	TARGET_NODE* m_pItrNode;
	TARGET_NODE* m_pLockedTargetNode;

	CBaseList m_DoodadList;

	CBaseList m_PlacedGridList;

	INT32 m_nSceneID;
	INT32 m_nSceneTemplateID;

	CCharacter* m_poCaster;

	INT64 m_llCenterX;
	INT64 m_llCenterY;
	INT64 m_llCenterZ;

	INT64 m_llTargetX;
	INT64 m_llTargetY;
	INT64 m_llTargetZ;

	BOOL m_bIgnoreTargetRadius;
	BOOL m_bIgnoreObstacle;
	INT32 m_nDirection;    // +184
	INT32 m_eRangeType;    // +188
	INT32 m_nParam1;	   // +192
	INT32 m_nParam2;	   // +196
	INT32 m_nParam3;	   // +200
	INT32 m_nTargetObjTypeLimit;
	INT32 m_nRelationshipLimit;
	INT32 m_nStanceLimit;
	BOOL m_bCorpseValid;
	BOOL m_bUseWeaponRange;
	INT32 m_nTargetCheckNode;

	INT32 m_nTargetCount;

};

#include "target_scanner_inl.h"

#endif // _target_scanner_h__
