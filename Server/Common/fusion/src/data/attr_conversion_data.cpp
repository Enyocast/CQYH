#include "stdafx.h"
#include "attr_conversion_data.h"
#include "char_def.h"
#include "string_def.h"
#include "script_mgr.h"

BOOL ATTR_LEVEL::ReadLine(INT32& rnID, const char*& rpcszName, ATTR_LEVEL* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	memset(pData, 0, sizeof(ATTR_LEVEL));

	READ_INT("Level", m_nLevel);
	READ_INT_EXPR("Class", m_nClass);

	for (INT32 i = 2; i < pTabConfig->GetColCount(); i++)
	{
		INT32 nNameValue = 0;

		nRetCode = g_pReadDataScript->CallFunction("read_int_expr", "s:d", pTabConfig->GetColName(i), &nNameValue);
		LOG_PROCESS_ERROR(nRetCode);

		LOG_PROCESS_ERROR(nNameValue < catTotal);

		if (nNameValue == catRunSpeed || nNameValue == catWalkSpeed)
		{
			READ_SPEED(pTabConfig->GetColName(i), m_nMainAttr[nNameValue]);
		}
		else
		{
			nRetCode = pTabConfig->ReadData(i, nRow, pData->m_nMainAttr[nNameValue]);
			LOG_PROCESS_ERROR(nRetCode);
		}
	}

	rnID = MakeAttrKey(pData->m_nLevel, pData->m_nClass);

	return TRUE;
Exit0:
	return FALSE;

}

//BOOL ATTR_CONV::ReadLine(INT32& rnID, const char*& rpcszName, ATTR_CONV* pData, CTabFile* pTabConfig, INT32 nRow)
//{
//	char szAttrName[MAX_ATTR_NAME_LEN] = { 0 };
//	CLuaScript* poScript = NULL;
//	pData->m_bAffectedByMainAttr = FALSE;
//
//	READ_START();
//
//	READ_INT_EXPR("Class", m_nClass);
//	READ_INT_EXPR("AttrName", m_nAttrID);
//	READ_INT("catValue", m_nMainAttrParam[catValue]);
//	READ_INT("catCombatParam", m_nMainAttrParam[catCombatParam]);
//
//	READ_INT("ConstParam", m_nConstParam);
//
//	rnID = MakeAttrKey(pData->m_nAttrID, pData->m_nClass);
//
//	return TRUE;
//Exit0:
//	return FALSE;
//}
//
////////////////////////////////////////////////////////////////////////////
//
//CAttrConv CAttrConv::m_sInstance;
//
//CAttrConv::CAttrConv(void)
//{
//
//}
//
//CAttrConv::~CAttrConv(void)
//{
//
//}
//
//CAttrConv& CAttrConv::GetInstance(void)
//{
//	return m_sInstance;
//}
//
//void CAttrConv::Init(void)
//{
//}
//
//void CAttrConv::AddAffectedAttr(INT32 nClass, INT32 nMainAttr, INT32 nAffectedAttr)
//{
//	DBG("---- AddAffectedAttr, class: %d, main attr: %d, affected attr: %d", nClass, nMainAttr, nAffectedAttr);
//
//	TAttrList* list = GetAffectedAttrList(nClass, nMainAttr);
//	if (list == NULL)
//	{
//		TAttrList list;
//		list.push_back(nAffectedAttr);
//
//		m_AttrConvMap[MakeAttrKey(nMainAttr, nClass)] = list;
//
//		return;
//	}
//
//	list->push_back(nAffectedAttr);
//}
//
//CAttrConv::TAttrList* CAttrConv::GetAffectedAttrList(INT32 nClass, INT32 nMainAttr)
//{
//	TAttrConvMap::iterator itr = m_AttrConvMap.find(MakeAttrKey(nMainAttr, nClass));
//	if (itr == m_AttrConvMap.end())
//		return NULL;
//
//	return &itr->second;
//}
