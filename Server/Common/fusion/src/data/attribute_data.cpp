#include "stdafx.h"
#include "attribute_data.h"
#include "attribute_def.h"

BOOL ATTRIBUTE_DATA::ReadLine(INT32& rnID, const char*& rpcszName, ATTRIBUTE_DATA* pData, CTabFile* pTabConfig, INT32 nRow)
{
	READ_START();

	READ_INT("AttributeID", m_nAttributeID);
	READ_INT_EXPR("Key", m_nKey);
	READ_INT_EXPR("Param1", m_nParam[0]);
    READ_INT("Param2", m_nParam[1]);
    READ_INT("Param3", m_nParam[2]);
    READ_INT("Pow", m_nPow);
    READ_STR("Tip", m_szDesc);

	READ_END(m_nAttributeID);
}
