#include "stdafx.h"
#include "title_data.h"
#include "attribute_def.h"
#include "attribute_data.h"
#include "script_mgr.h"

BOOL TITLE_TEMPLATE::ReadLine(INT32& rnID, const char*& rpcszName, TITLE_TEMPLATE* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("ID", m_nTemplateID);
	READ_STR("TitleName", m_szName);
	READ_INT("ValidTime", m_nValidTime);
    READ_INT("pow", nPow);
    for (INT32 i = 0; i < TitleAttrTableSize; ++i)
    {
        char szFieldName[256];
        snprintf(szFieldName, 256, "AttrID%d", i + 1);
        READ_INT_EXPR(szFieldName, m_nAttrID[i]);
    }

	for (INT32 i=0; i<TitleConditionTableSize; ++i)
	{
		char szFieldName[256];
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

















