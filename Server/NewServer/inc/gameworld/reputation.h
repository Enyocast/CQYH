#ifndef _REPUTATION_H_
#define _REPUTATION_H_

#include "npc_def.h"

class CRole;

class CReputation
{
public:
    CReputation();
    ~CReputation();

    BOOL Init(CRole* poOwner);
    BOOL UnInit(void);

    BOOL Load_v_1(const char* pcData, UINT32 dwSize);
	BOOL Save(char* pData, UINT32& rdwSize);

    INT32 GetValue(INT32 nForceID);
    void SetValue(INT32 nForceID, INT32 nNewValue);
    void ModifyValue(INT32 nForceID, INT32 nValue);

	inline UINT64 GetActiveState(void);
	void ActiveForce(INT32 nForceID);

	INT32 ReceiveAward(INT32 nForceID);
	inline UINT64 GetAwardState(void);

private:
    BOOL _LoadInitData(void);

    CRole*  m_poOwner;
	UINT64	m_qwActiveState;
	UINT64	m_qwAwardState;
    INT32   m_nValueList[MAX_NPC_FORCE_ID];
};

inline UINT64 CReputation::GetActiveState(void)
{
	return m_qwActiveState;
}

inline UINT64 CReputation::GetAwardState(void)
{
	return m_qwAwardState;
}

#endif  // _REPUTATION_H_