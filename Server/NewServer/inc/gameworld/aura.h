#ifndef _AURA_H_
#define _AURA_H_

#include "aura_data.h"
#include "read_data_helper.h"

class CAura
{
public:
	CAura(void);
	virtual ~CAura(void);
	virtual void UnInit(void) { }

	virtual void SetAttr(INT32 eAttrType, INT32 nVal);
	virtual CAura* MakeCopy(void);

	inline void SetID(INT32 nID);
	inline INT32 GetID(void);
	inline INT32 GetAttr(INT32 eAttrType);

	inline void CopyTo(CAura* p);
	inline void CopyData(AURA_ENTRY* pData);

	inline INT32 GetDurationFrm(void);
	inline INT32 GetIntervalFrm(void);
	inline INT32 GetDelayFrm(void);
	inline INT32 GetEffectMinFrm(void);

	inline const AURA_ENTRY* GetData(void);

protected:
	AURA_ENTRY m_Data;
};

class CAuraTemplate : public CAura
{
public:
	CAuraTemplate(void);
	virtual ~CAuraTemplate(void) { }

	virtual void SetAttr(INT32 eAttrType, INT32 nVal);
	virtual CAura* MakeCopy(void);

	inline void InitAttr(INT32 eAttrType, INT32 nVal);
	inline void InitWithData(AURA_ENTRY* pData);
};

class CAuraEntryCopy : public CAura
{
public:
	CAuraEntryCopy(void);
	virtual ~CAuraEntryCopy(void) { }
	virtual void UnInit(void) { delete this; }

	virtual CAura* MakeCopy(void);
};

#include "aura_inl.h"

#endif // _aura_h__
