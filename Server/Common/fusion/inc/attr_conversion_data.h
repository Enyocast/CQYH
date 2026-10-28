#ifndef _ATTR_CONVERSION_DATA_H_
#define _ATTR_CONVERSION_DATA_H_

#include "data_manager.h"
#include "attribute_def.h"

class CLuaScript;

// attributes1
struct ATTR_LEVEL
{
	INT32 m_nLevel;
	INT32 m_nClass;

	INT32 m_nMainAttr[catTotal];

	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ATTR_LEVEL* pData, CTabFile* pTabConfig, INT32 nRow);
};

//#define MAX_NODE_COUNT 8
//
//struct ATTR_CONV
//{
//	INT32 m_nAttrID;
//	INT32 m_nClass;
//	INT32 m_nMainAttrParam[catEndMainAttr];
//	INT32 m_nValue;
//	INT32 m_nCombatParam;
//	INT32 m_nConstParam;
//	BOOL m_bAffectedByMainAttr;
//
//	static BOOL ReadLine(INT32& rnID, const char*& rpcszName, ATTR_CONV* pData, CTabFile* pTabConfig, INT32 nRow);
//};
//
//class CAttrConv
//{
//public:
//	CAttrConv(void);
//	virtual ~CAttrConv(void);
//
//	typedef std::list<INT32> TAttrList;
//
//	void Init(void);
//
//	static CAttrConv& GetInstance(void);
//
//	void AddAffectedAttr(INT32 nClass, INT32 nMainAttr, INT32 nAffectedAttr);
//
//	TAttrList* GetAffectedAttrList(INT32 nClass, INT32 nMainAttr);
//
//private:
//	static CAttrConv m_sInstance;
//
//	typedef std::map<INT32, TAttrList> TAttrConvMap;
//
//	TAttrConvMap m_AttrConvMap;
//};

#endif	// _ATTR_CONVERSION_DATA_H_
