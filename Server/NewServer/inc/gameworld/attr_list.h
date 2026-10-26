#ifndef _ATTR_LIST_H_
#define _ATTR_LIST_H_

#include "attribute_def.h"

class CCharacter;

// RESULT = A * B / RATE_MAX + C

class CAttrList
{
public:
	CAttrList(void);

	void Init(void);

	void ResetExAttrBase(void);

	inline INT32 GetAttr(INT32 eAttrType);

	inline INT32 ForceGetAttr(INT32 eAttrType);

	inline void SetAttrA(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);
	inline INT32 GetAttrA(INT32 eAttrType);
	inline void AddAttrA(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);

	inline void SetAttrB(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);
	inline INT32 GetAttrB(INT32 eAttrType);
	inline void AddAttrB(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);

    inline INT32 GetAttrBase(INT32 eAttrType);
	inline void SetAttrBase(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);
	inline void AddAttrBase(CCharacter* pSelf, INT32 eAttrType, INT32 nValue);

	inline void CopyAttr(INT32 nList[], INT32 nCount);
	inline void CopyTo(CAttrList* pList);
	inline void EnableAttr(INT32 eAttrType, BOOL bEnable);

	void CalculateAll(CCharacter* pSelf);
	void ReCalculateAttr(CCharacter* pSelf, INT32 eAttrType);

private:
	BOOL m_bAttrEnabled[catTotal];
	INT32 m_nAttrList[catTotal];
	INT32 m_nAttrListBase[catTotal];
	INT32 m_nAttrListA[catTotal];
	INT32 m_nAttrListB[catTotal];
};

#include "attr_list_inl.h"

#endif // _attr_list_h__
