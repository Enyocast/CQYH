#ifndef _SPIRIT_H_
#define _SPIRIT_H_

#include "spirit_def.h"

class CRole;

struct CAir
{
	INT32 nTemplateID;
	INT32 nExp;
};

class CSpirit
{
public:
	CSpirit();
	~CSpirit();
	
	INT32 Init(CRole* poRole);
	INT32 UnInit();

	BOOL Load_v_1(const char* pData, UINT32 dwSize);
	BOOL Save(const char* pData, UINT32& rdwSize);  

	INT32 MainLoop();

	/************************** overal **********************************************/

	INT32 ChangeSoul2Pts(BOOL bUseMoney, BOOL bIsOnline);

	inline INT32 GetLevel();
	INT32 SetLevel(INT32 nLevel);

	inline INT32 GetSpirit();

	INT32  GetPow();

	inline UINT32 GetNextExp2PtsTime();
	inline void SetNextExp2PtsTime(UINT32 dwNextExp2PtsTime);

	inline void SetExp(INT32 nExp);

	/************************** airsea **********************************************/

	INT32 SetProductAirLevel(INT32 nLevel);

	INT32 ProductAir(INT32 nIndex);

	INT32 AddAir(INT32 nTemplateID, INT32 nExp);
	INT32 MergeAir(INT32 nSrcCon);
	INT32 MoveAir(INT32 nSrcType, INT32 nSrcIndex, INT32 nTarType, INT32 nTarIndex);
	INT32 ExchangeAir(INT32 nAirID);
	INT32 AddSlot(INT32 nType, INT32 nCount);
	INT32 SetAir(INT32 nBagType, INT32 nTemplateID, INT32 nExp, INT32 nIndex);

	inline INT32 GetBagContainerSize();
	inline void SetBagContainerSize(INT32 nSize);

	inline INT32 GetStallContainerSize();
	inline void SetStallContainerSize(INT32 nSize);

	inline INT32 GetEquipContainerSize();
	inline void SetEquipContainerSize(INT32 nSize);

	INT32  GetHigherAirLevelIndex();

	CAir* GetAir(INT32 nBagType, INT32 nBagIndex);
	void GetAirBegin();
	CAir* GetAirNext();

	/************************** bloodsea **********************************************/
	
	INT32 BrushBloodSlot(INT32 nPage, INT32 nSlot);
	INT32 OpenBlood(INT32 nPage);
	INT32 SetBlood(INT32 nPage, INT32 nSlot, INT32 nNewNumber);
	inline INT32 GetBlood(INT32 nPage, INT32 nSlot);
	inline INT32 GetBloodState();

	INT32 SetBloodOpen(INT32 nPage);
	INT32 IsBloodOpen(INT32 nPage);
private:

	/************************** overal **********************************************/

	/************************** airsea **********************************************/

	INT32 _MergeAir(INT32 nSrcIndex, INT32 TarIndex);

	inline BOOL _GetProductAirLevel(INT32 nIndex);
	inline void _ClearProductAirLevel(INT32 nIndex);

	/************************** bloodsea **********************************************/

	INT32 _CanBrush(INT32 nPage, INT32 nSlot);

private:

	CRole*	m_pOwner;

	INT32 m_nLevel;
	INT32 m_nExp;

	UINT32 m_dwNextExp2PtsTime;				// 下次转化时间(自然转换)

	UINT32 m_dwDailyUseMoneyChangeCount;	// 每天使用金币转换次数
	UINT32 m_dwNextScanTimer;				// 下次扫描时间(用于每日重置)
	INT32  m_nTotalMoneyCost;				// 魂转修炼点消耗金币
	/************************** airsea **********************************************/

	CAir  m_BagContainer[MAX_AIRSEA_BAG_CONTAINER_SIZE];
	CAir  m_StallContainer[MAX_AIRSEA_STALL_CONTAINER_SIZE];
	CAir  m_EquipContainer[MAX_AIRSEA_EQUIP_CONTAINER_SIZE];

	INT32 m_nBagContainerSize;
	INT32 m_nStallContainerSize;
	INT32 m_nEquipContainerSize;

	INT32 m_nProductAirLevel;		// 练气等级

	/************************** bloodsea **********************************************/
	INT32 m_nBloodSlot[MAX_BLOODSEA_PAGE][MAX_BLOODSEA_SLOT_PER_PAGE];
	INT32 m_nBloodState;
};

inline INT32 CSpirit::GetLevel()
{
	return m_nLevel;
}

inline INT32 CSpirit::GetSpirit()
{
	return m_nLevel/3;
}

inline UINT32 CSpirit::GetNextExp2PtsTime()
{
	return m_dwNextExp2PtsTime;
}

inline void CSpirit::SetNextExp2PtsTime(UINT32 dwNextExp2PtsTime)
{
	m_dwNextExp2PtsTime = dwNextExp2PtsTime;
}

inline void CSpirit::SetExp(INT32 nExp)
{
	m_nExp = nExp;
}

inline INT32 CSpirit::GetBagContainerSize()
{
	return m_nBagContainerSize;
}

inline INT32 CSpirit::GetStallContainerSize()
{
	return m_nStallContainerSize;
}

inline INT32 CSpirit::GetEquipContainerSize()
{
	return m_nEquipContainerSize;
}

inline void CSpirit::SetBagContainerSize(INT32 nBagContainerSize)
{
	m_nBagContainerSize = nBagContainerSize;
}

inline void CSpirit::SetStallContainerSize(INT32 nStallContainerSize)
{
	m_nStallContainerSize = nStallContainerSize;
}

inline void CSpirit::SetEquipContainerSize(INT32 nEquipContainerSize)
{
	m_nEquipContainerSize = nEquipContainerSize;
}

inline INT32 CSpirit::GetBloodState()
{
	return m_nBloodState;
}

inline BOOL CSpirit::_GetProductAirLevel(INT32 nIndex)
{
	return m_nProductAirLevel & (1 << nIndex);
}

inline void CSpirit::_ClearProductAirLevel(INT32 nIndex)
{
	m_nProductAirLevel = m_nProductAirLevel & ~(1 << nIndex);
}

inline INT32 CSpirit::GetBlood(INT32 nPage, INT32 nSlot)
{
	LOG_PROCESS_ERROR(nPage >= 0 && nPage < MAX_BLOODSEA_PAGE);
	LOG_PROCESS_ERROR(nSlot >= 0 && nSlot < MAX_BLOODSEA_SLOT_PER_PAGE);

	return 	m_nBloodSlot[nPage][nSlot];
Exit0:
	return 0;
}

#endif // _SPIRIT_H_
