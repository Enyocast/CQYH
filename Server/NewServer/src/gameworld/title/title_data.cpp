#include "stdafx.h"
#include "title_data.h"
#include "char_modifier.h"
#include "modifier_file_def.h"
#include "modifier_tree.h"
#include "modifier_def.h"
#include "attribute_def.h"
#include "script_mgr.h"


BOOL TITLE_TEMPLATE::ReadLine(INT32& rnID, const char*& rpcszName, TITLE_TEMPLATE* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("ID", m_nTemplateID);
	READ_STR("TitleName", m_szName);
	READ_INT("ValidTime", m_nValidTime);
    READ_INT("pow", nPow);
	pData->m_nAttrNum = 0;
	for (INT32 i=0; i<TitleAttrTableSize; ++i)
	{
		TCHAR szFieldName[256];
		snprintf(szFieldName, 256, "AttrType%d", i+1);
		READ_INT_EXPR(szFieldName, pData->m_Attr[i].shAttrType);

		snprintf(szFieldName, 256, "AttrValue%d", i+1);
		READ_INT(szFieldName, m_Attr[i].shParam);

		if (pData->m_Attr[i].shAttrType > 0)
		{
			++pData->m_nAttrNum;
		}
	}

	pData->m_nNodeCount = 0;
	memset(pData->m_nNodeIDs, 0, sizeof(pData->m_nNodeIDs));

	for (UINT8 i=0; i < pData->m_nAttrNum; ++i)
	{
		ModifierNode* node = CModifierTree::GetInstance().GetExtraNode(pData->m_nNodeIDs[i]);
		LOG_PROCESS_ERROR(node);

		node->nType = mttCharacter;
		node->nKey = cmi_A;

		node->Param[0].nParam = pData->m_Attr[i].shAttrType;
		node->Param[1].nParam = pData->m_Attr[i].shParam;

		pData->m_nNodeCount++;
	}

	for (INT32 i=0; i<TitleConditionTableSize; ++i)
	{
		TCHAR szFieldName[256];
		snprintf(szFieldName, 256, "ConditionType%d", i+1);
		READ_INT(szFieldName, m_Condition[i].shConType);

		snprintf(szFieldName, 256, "ConditionValue%d", i+1);
		READ_INT(szFieldName, m_Condition[i].shConValue);
	}

	rpcszName = pData->m_szName;
	READ_END(m_nTemplateID);
}



const TITLE_TEMPLATE* GetTitleTemplate(INT8 nTemplateID)
{
	return CDataManager<TITLE_TEMPLATE>::GetInstance().GetData(nTemplateID);
}

















