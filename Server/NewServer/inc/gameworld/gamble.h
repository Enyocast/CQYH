#ifndef _GAMBLE_H_
#define _GAMBLE_H_

#include "item_def.h"

struct GAMBLE_DATA;
class CRole;

class CGamble
{
public:
	CGamble();
	void Clear();
	void SetOwner(CRole* role);
	BOOL Load_v_1(const char* pcData, UINT32 dwSize);
	BOOL Save(const char* pcData, UINT32& rdwSize);
	
	const DROP_CHANCE_DATA* GetDropChangeData(const GAMBLE_DATA* data);
	INT32 GetDropGambleItem();
	INT32 GetJieDian();
	
	void ClearValue(INT32 nGambleType, INT32 nGambleLevel);
	
	UINT32 GetTotalValue(INT32 nGambleType, INT32 nGambleLevel);
	UINT32 GetValue(INT32 nGambleType, INT32 nGambleLevel);
	void SetValue(INT32 nGambleType, INT32 nGambleLevel, UINT32 dwVar);
	
	INT32 GetNextID(INT32 nGambleType, INT32 nGambleLevel);
	void SetNextID(INT32 nGambleType, INT32 nGambleLevel, INT32 nVar);
	
private:
	UINT32 dwValue[egtTotal][GAMBLE_LEVEL_COUNT];
	UINT32 dwTotalValue[egtTotal][GAMBLE_LEVEL_COUNT];
	INT32 nNextID[egtTotal][GAMBLE_LEVEL_COUNT];
	
	CRole* m_pOwner;
};

#endif	// _GAMBLE_H_